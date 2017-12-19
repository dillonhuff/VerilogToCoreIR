// This is free and unencumbered software released into the public domain.
//
// Anyone is free to copy, modify, publish, use, compile, sell, or
// distribute this software, either in source code form or as a compiled
// binary, for any purpose, commercial or non-commercial, and by any
// means.

#include "kernel/yosys.h"
#include "kernel/sigtools.h"

#include "coreir.h"

#include <string>
#include <map>
#include <set>

using namespace CoreIR;
using namespace std;

USING_YOSYS_NAMESPACE
PRIVATE_NAMESPACE_BEGIN

int getIntParam(Cell* const cell, const std::string& str) {
  auto param = cell->parameters.find(str);
  assert(param != std::end(cell->parameters));

  return param->second.as_int();
}

std::map<string, CoreIR::Module*>
buildModuleMap(RTLIL::Design * const design,
               CoreIR::Context* const c,
               Namespace* const g) {

  map<string, CoreIR::Module*> modMap;
  for (auto &it : design->modules_) {

    if (design->selected_module(it.first)) {

        
      RTLIL::Module* rmod = it.second;

      cout << "Ports" << endl;
      for (auto& conn : rmod->ports) {
        cout << id2cstr(conn) << endl;
      }

      cout << "# of Connections = " << rmod->connections().size() << endl;
      for (auto& conn : rmod->connections()) {
        RTLIL::SigSig s = conn;
        auto lhs = s.first;
        auto rhs = s.second;

        cout << "\tLHS width = " << lhs.size() << endl;
        cout << "\tRHS width = " << lhs.size() << endl;
      }

      vector<pair<string, Type*> > args;

      cout << "Wires" << endl;
      for (auto &wire_iter : rmod->wires_) {
        RTLIL::Wire *wire = wire_iter.second;
        cout << "\t" << id2cstr(wire->name) << ", port in = " << wire->port_input << ", port out = " << wire->port_output << ", width = " << wire->width << endl;

        if (wire->port_output) {
          args.push_back({id2cstr(wire->name), c->Array(wire->width, c->Bit())});
        }

        if (wire->port_input) {
          args.push_back({id2cstr(wire->name), c->Array(wire->width, c->BitIn())});
        }

      }

      modMap[id2cstr(it.first)] =
        g->newModuleDecl(id2cstr(it.first), c->Record(args));

    }
  }

  return modMap;
}

struct ToCoreIRPass : public Yosys::Pass {
	ToCoreIRPass() : Pass("to_coreir") { }

  virtual void execute(std::vector<std::string>, RTLIL::Design *design) {

    Context* c = newContext();
    log_header(design, "Executing TOCOREIR pass (find stub nets).\n");

    // Find and create coreir stubs for all modules
    Namespace* g = c->getGlobal();
    map<string, CoreIR::Module*> modMap = buildModuleMap(design, c, g);

    // Now with all modules added create module definitions
    for (auto &it : design->modules_) {

      CoreIR::Module* mod = modMap[id2cstr(it.first)];

      SigMap assign_map(it.second);
      
      assert(mod != nullptr);

      CoreIR::ModuleDef* def = mod->newModuleDef();

      auto* self = def->sel("self");

      RTLIL::Module* rmod = it.second;
      log("Cell list\n");

      map<Cell*, Instance*> instMap;
      for (auto& cell_iter : rmod->cells_) {
        Cell* cell = cell_iter.second;

        string cellTp = RTLIL::id2cstr(cell->type);
        string cellName = RTLIL::id2cstr(cell->name);
        
        cout << cellName << endl;

        log("Cell: %s : %s\n",
            RTLIL::id2cstr(cell->name),
            RTLIL::id2cstr(cell->type));

        for (auto& param : cell->parameters) {
          log("\tParam: %s = %s\n",
              RTLIL::id2cstr(param.first),
              param.second.as_string().c_str());
        }

        if (cellTp == "$add") {

          int widthA = getIntParam(cell, "\\A_WIDTH");
          int widthB = getIntParam(cell, "\\B_WIDTH");
          int widthY = getIntParam(cell, "\\Y_WIDTH");

          assert(widthA == widthB);
          assert(widthB == widthY);


          string instName = "";
          for (uint i = 0; i < cellName.size(); i++) {
            if (cellName[i] == '$') {
              instName += "__DOLLAR__";
            } else if (cellName[i] == ':') {
              instName += "__COLON__";
            } else if (cellName[i] == '.') {
              instName += "__DOT__";
            } else {
              instName += cellName[i];
            }

          }
          auto inst = def->addInstance(instName, "coreir.add", {{"width", CoreIR::Const::make(c, widthY)}});

          instMap[cell] = inst;
          
        } else {
          assert(false);
        }


        // Add connections to output ports
        cout << "Adding output connections" << endl;
        for (auto& conn : rmod->connections()) {
          RTLIL::SigSpec fst = conn.first;
          RTLIL::SigSpec snd = conn.second;
          
          //cout << "\tSigSpec " << id2cstr(conn.first) << " size = " << ss.size() << ", is_wire = " << ss.is_wire() << endl;

          assert(fst.is_wire());
          assert(snd.is_wire());

          Wire* wIn = fst.as_wire();

          cout << "\t\t Wire: " << id2cstr(wIn->name) << ", width = " <<
            wIn->width << ", " << "start_offset = " << wIn->start_offset <<
            ", port_id = " << wIn->port_id << endl;

          auto inName = wIn->name;

          Wire* w = snd.as_wire();

          string s = id2cstr(w->name);

          string cellName = s.substr(0, s.find("_"));
          string portName = s.substr(s.find("_") + 1, s.size());

          cout << "cellName = " << cellName << endl;
          cout << "portName = " << portName << endl;

          cout << "\t\t Wire: " << id2cstr(w->name) << ", width = " <<
            w->width << ", " << "start_offset = " << w->start_offset <<
            ", port_id = " << w->port_id << endl;

          assert(portName == "Y");

          auto targetCell = rmod->cells_[IdString(cellName)];

          assert(targetCell != nullptr);

          auto targetInst = instMap[targetCell];

          assert(targetInst != nullptr);

          def->connect(self->sel(id2cstr(inName)), targetInst->sel("out"));

        }
        
        // Add connections to instances
        cout << "Connections" << endl;

        auto* inst = instMap[cell];        

        for (auto& conn : cell->connections()) {

          RTLIL::SigSpec ss = conn.second;
          cout << "\tSigSpec " << id2cstr(conn.first) << " size = " << ss.size() << ", is_wire = " << ss.is_wire() << endl;

          assert(ss.is_wire());

          Wire* w = ss.as_wire();

          cout << "\t\t Wire: " << id2cstr(w->name) << ", width = " <<
              w->width << ", " << "start_offset = " << w->start_offset <<
              ", port_id = " << w->port_id << endl;


          if (w->port_input) {
            string connName = id2cstr(conn.first);

            if (connName == "A") {
              def->connect(self->sel(id2cstr(w->name)), inst->sel("in0"));
            } else if (connName == "B") {
              def->connect(self->sel(id2cstr(w->name)), inst->sel("in1"));
            } else {
              assert(false);
            }
          }
          
        }

      }
      
      mod->setDef(def);
    }

    assert(modMap.size() > 0);

    

    CoreIR::Module* top = begin(modMap)->second;
    if (!saveToFile(g, "verilog_to_coreir.json", top)) {
      cout << "Could not save to json!!" << endl;
      c->die();
    }
    
    deleteContext(c);
  }
} ToCoreIRPass;

PRIVATE_NAMESPACE_END
