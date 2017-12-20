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

// Extending node used to extend
void addExtend(CoreIR::Context* const c) {
  
}

Namespace* CoreIRLoadLibrary_rtlil(CoreIR::Context* const c) {
  auto rtLib = c->newNamespace("rtlil");



  Params logic_and_args = {{"width",c->Int()}};
  TypeGen* logic_andTP = rtLib->newTypeGen(
    "logic_and_type", //name for the typegen
    logic_and_args,
    [](Context* c, Values genargs) { //Function to compute type
      uint width = genargs.at("width")->get<int>();

      return c->Record({
          {"in0", c->BitIn()->Arr(width)},
            {"in1", c->BitIn()->Arr(width)},
              {"out",c->Bit()}});
    });

  rtLib->newGeneratorDecl("logic_and", logic_andTP, logic_and_args);

  Params logic_or_args = {{"width",c->Int()}};
  TypeGen* logic_orTP = rtLib->newTypeGen(
    "logic_or_type", //name for the typegen
    logic_or_args,
    [](Context* c, Values genargs) { //Function to compute type
      uint width = genargs.at("width")->get<int>();

      return c->Record({
          {"in0", c->BitIn()->Arr(width)},
            {"in1", c->BitIn()->Arr(width)},
              {"out",c->Bit()}});
    });

  rtLib->newGeneratorDecl("logic_or", logic_orTP, logic_or_args);
  
  return rtLib;
}

int getIntParam(Cell* const cell, const std::string& str) {
  auto param = cell->parameters.find(str);
  assert(param != std::end(cell->parameters));

  return param->second.as_int();
}

std::string coreirSafeName(const std::string cellName) {
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

  return instName;
}

std::map<string, CoreIR::Module*>
buildModuleMap(RTLIL::Design * const design,
               CoreIR::Context* const c,
               Namespace* const g) {

  map<string, CoreIR::Module*> modMap;
  for (auto &it : design->modules_) {

    if (design->selected_module(it.first)) {

        
      RTLIL::Module* rmod = it.second;

      //cout << "Ports" << endl;
      for (auto& conn : rmod->ports) {
        cout << id2cstr(conn) << endl;
      }

      cout << "# of Connections = " << rmod->connections().size() << endl;
      for (auto& conn : rmod->connections()) {
        RTLIL::SigSig s = conn;
        auto lhs = s.first;
        auto rhs = s.second;

        //cout << "\tLHS width = " << lhs.size() << endl;
        //cout << "\tRHS width = " << lhs.size() << endl;
      }

      vector<pair<string, Type*> > args;

      //cout << "Wires" << endl;
      for (auto &wire_iter : rmod->wires_) {
        RTLIL::Wire *wire = wire_iter.second;
        //cout << "\t" << id2cstr(wire->name) << ", port in = " << wire->port_input << ", port out = " << wire->port_output << ", width = " << wire->width << endl;

        if (wire->port_output) {

          if (wire->width > 1) {
            args.push_back({id2cstr(wire->name), c->Array(wire->width, c->Bit())});
          } else {
            args.push_back({id2cstr(wire->name), c->Bit()});
          }
        }

        if (wire->port_input) {
          if (wire->width > 1) {
            args.push_back({id2cstr(wire->name), c->Array(wire->width, c->BitIn())});
          } else {
            args.push_back({id2cstr(wire->name), c->BitIn()});
          }
        }

      }

      modMap[id2cstr(it.first)] =
        g->newModuleDecl(id2cstr(it.first), c->Record(args));

    }
  }

  return modMap;
}

void print_cell_info(RTLIL::Cell* const cell) {

  string cellTp = RTLIL::id2cstr(cell->type);
  string cellName = RTLIL::id2cstr(cell->name);
        
  cout << cellName << endl;

  cout << "Cell: %s : %s\n" << 
    RTLIL::id2cstr(cell->name) <<
    RTLIL::id2cstr(cell->type) << endl;

  for (auto& param : cell->parameters) {
    cout << "\tParam: %s = %s\n" <<
      RTLIL::id2cstr(param.first) << 
      param.second.as_string().c_str() << endl;
  }

}

bool isBinaryComparator(const std::string& cellTp) {
  return (cellTp == "$eq") || (cellTp == "$lt") || (cellTp == "$gt") ||
    (cellTp == "$le") || (cellTp == "$ge") || (cellTp == "$ne") || (cellTp == "$logic_and") || (cellTp == "$logic_or");
}

bool isArithBinop(const std::string& cellTp) {
  return (cellTp == "$add") || (cellTp == "$sub") || (cellTp == "$shl") || (cellTp == "$shr");
}

std::string coreirOpName(const std::string& cellTp) {
  if (cellTp == "$logic_and") {
    return "rtlil.logic_and";
  }

  if (cellTp == "$logic_or") {
    return "rtlil.logic_or";
  }
  
  if (cellTp == "$eq") {
    return "coreir.eq";
  }

  if (cellTp == "$shl") {
    return "coreir.shl";
  }

  if (cellTp == "$shr") {
    return "coreir.lshr";
  }
  
  if (cellTp == "$ne") {
    return "coreir.neq";
  }
  
  if (cellTp == "$le") {
    return "coreir.ule";
  }

  if (cellTp == "$ge") {
    return "coreir.uge";
  }

  if (cellTp == "$lt") {
    return "coreir.ult";
  }

  if (cellTp == "$gt") {
    return "coreir.ugt";
  }

  if (cellTp == "$add") {
    return "coreir.add";
  }

  if (cellTp == "$sub") {
    return "coreir.sub";
  }
  
  assert(false);
}

void addBinaryComparator(const std::string& cellTp,
                         Cell* const cell,
                         std::map<Cell*, CoreIR::Instance*>& instMap,
                         CoreIR::ModuleDef* const def,
                         CoreIR::Context* const c) {
  // cout << "Add cell = " << cellName << endl;
  // print_cell_info(cell);

  string cellName = id2cstr(cell->name);
  
  int widthA = getIntParam(cell, "\\A_WIDTH");
  int widthB = getIntParam(cell, "\\B_WIDTH");
  int widthY = getIntParam(cell, "\\Y_WIDTH");

  int maxWidth = max(widthA, widthB);

  string instName = coreirSafeName(cellName);

  // TODO: Check that the operation is not bitwise
  
  string coreName = coreirOpName(cellTp);
  auto inst = def->addInstance(instName, coreName, {{"width", CoreIR::Const::make(c, maxWidth)}});

  instMap[cell] = inst;
}

map<Cell*, Instance*> buildInstanceMap(RTLIL::Module* const rmod,
                                       std::map<string, CoreIR::Module*>& modMap,
                                       CoreIR::Context* const c,
                                       CoreIR::ModuleDef* const def) {

  map<Cell*, Instance*> instMap;
  for (auto& cell_iter : rmod->cells_) {
    Cell* cell = cell_iter.second;

    string cellTp = RTLIL::id2cstr(cell->type);
    string cellName = RTLIL::id2cstr(cell->name);
        
    //cout << cellName << endl;

    // log("Cell: %s : %s\n",
    //     RTLIL::id2cstr(cell->name),
    //     RTLIL::id2cstr(cell->type));

    // for (auto& param : cell->parameters) {
    //   log("\tParam: %s = %s\n",
    //       RTLIL::id2cstr(param.first),
    //       param.second.as_string().c_str());
    // }

    

    if (isArithBinop(cellTp)) {

      // Reintroduce when casting is available
      // cout << "Arith cell = " << cellName << endl;
      // print_cell_info(cell);

      int widthA = getIntParam(cell, "\\A_WIDTH");
      int widthB = getIntParam(cell, "\\B_WIDTH");
      int widthY = getIntParam(cell, "\\Y_WIDTH");

      int maxWidth = max(widthA, widthB);

      
      //assert(widthA == widthB);

      // Even this is not necessarily true for shifts
      //assert(maxWidth <= widthY);

      string instName = coreirSafeName(cellName);

      string genName = coreirOpName(cellTp);
      auto inst = def->addInstance(instName, genName, {{"width", CoreIR::Const::make(c, widthY)}});

      instMap[cell] = inst;
    } else if (cellTp == "$and") {

      int widthA = getIntParam(cell, "\\A_WIDTH");
      int widthB = getIntParam(cell, "\\B_WIDTH");
      int widthY = getIntParam(cell, "\\Y_WIDTH");

      int maxWidth = max(widthA, widthB);

      
      //assert(widthA == widthB);
      assert(maxWidth == widthY);

      string instName = coreirSafeName(cellName);

      Instance* inst = nullptr;
      if (maxWidth > 1) {
        inst = def->addInstance(instName, "coreir.and", {{"width", CoreIR::Const::make(c, widthY)}});
      } else {
        inst = def->addInstance(instName, "corebit.and");
      }

      assert(inst != nullptr);

      instMap[cell] = inst;

    } else if (cellTp == "$or") {
      int widthA = getIntParam(cell, "\\A_WIDTH");
      int widthB = getIntParam(cell, "\\B_WIDTH");
      int widthY = getIntParam(cell, "\\Y_WIDTH");

      int maxWidth = max(widthA, widthB);

      //print_cell_info(cell);

      
      //assert(widthA == widthB);
      assert(maxWidth == widthY);

      string instName = coreirSafeName(cellName);

      Instance* inst = nullptr;
      if (maxWidth > 1) {
        inst = def->addInstance(instName, "coreir.or", {{"width", CoreIR::Const::make(c, widthY)}});
      } else {
        inst = def->addInstance(instName, "corebit.or");
      }

      assert(inst != nullptr);

      instMap[cell] = inst;
      
    } else if (cellTp == "$not") {

      int widthA = getIntParam(cell, "\\A_WIDTH");
      int widthY = getIntParam(cell, "\\Y_WIDTH");
      int maxWidth = widthA;

      //print_cell_info(cell);

      //assert(widthA == widthB);
      //assert(maxWidth == widthY);

      string instName = coreirSafeName(cellName);

      Instance* inst = nullptr;
      if (maxWidth > 1) {
        inst = def->addInstance(instName, "coreir.not", {{"width", CoreIR::Const::make(c, widthY)}});
      } else {
        inst = def->addInstance(instName, "corebit.not");
      }

      assert(inst != nullptr);

      instMap[cell] = inst;

    } else if (isBinaryComparator(cellTp)) {

      addBinaryComparator(cellTp, cell, instMap, def, c);
      
    } else if (cellTp == "$mux") {

      // print_cell_info(cell);

      string cellName = id2cstr(cell->name);
  
      int width = getIntParam(cell, "\\WIDTH");

      string instName = coreirSafeName(cellName);

      Instance* inst = nullptr;
      if (width == 1) {
        inst = def->addInstance(instName, "corebit.mux");
      } else {
        string coreName = "coreir.mux";
        inst = def->addInstance(instName, coreName, {{"width", CoreIR::Const::make(c, width)}});
      }

      assert(inst != nullptr);

      instMap[cell] = inst;
      
    } else if (cellTp == "$dff") {

      string cellName = id2cstr(cell->name);
  
      int width = getIntParam(cell, "\\WIDTH");

      string instName = coreirSafeName(cellName);

      Instance* inst = nullptr;
      string coreName = "coreir.reg";
      inst = def->addInstance(instName, coreName, {{"width", CoreIR::Const::make(c, width)}});

      assert(inst != nullptr);

      instMap[cell] = inst;

    } else {

      string instName = coreirSafeName(cellName);

      string cellTypeStr = id2cstr(cell->type);
      if (modMap.find(cellTypeStr) == end(modMap)) {
        cout << "Unsupported Cell type = " << id2cstr(cell->name) << " : " << id2cstr(cell->type) << ", skipping." << endl;

        print_cell_info(cell);
        //assert(false);
      } else {
        auto inst = def->addInstance(instName, modMap[cellTypeStr]);
        instMap[cell] = inst;
      }
    }
  }

  return instMap;
}

void printSigSigInfo(RTLIL::SigSig conn) {
      RTLIL::SigSpec fst = conn.first;
      RTLIL::SigSpec snd = conn.second;
          
      cout << "\tSigSpec fst" << endl;
      cout << "\t\tis wire  = " << fst.is_wire() << endl;
      cout << "\t\tis chunk = " << fst.is_chunk() << endl;

      cout << "\tSigSpec snd" << endl;
      cout << "\t\tis wire  = " << snd.is_wire() << endl;
      cout << "\t\tis chunk = " << snd.is_chunk() << endl;
}

void addConnections(RTLIL::Module* const rmod,
                    map<Cell*, Instance*>& instMap,
                    CoreIR::ModuleDef* const def) {

  auto* self = def->sel("self");

  for (auto& cell_iter : rmod->cells_) {
    Cell* cell = cell_iter.second;

    // Add connections to output ports
    cout << "Adding output connections" << endl;
    for (auto& conn : rmod->connections()) {

      RTLIL::SigSpec fst = conn.first;
      RTLIL::SigSpec snd = conn.second;
      
      assert(fst.is_wire());
      assert(snd.is_wire());

      Wire* wIn = fst.as_wire();

      cout << "\t\t Wire: " << id2cstr(wIn->name) << ", width = " <<
        wIn->width << ", " << "start_offset = " << wIn->start_offset <<
        ", port_id = " << wIn->port_id << endl;

      auto inName = wIn->name;

      Wire* w = snd.as_wire();

      string s = id2cstr(w->name);

      reverse(begin(s), end(s));
      string portName = s.substr(0, s.find("_"));
      string cellName = s.substr(s.find("_") + 1, s.size());

      reverse(begin(cellName), end(cellName));
      reverse(begin(portName), end(portName));

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

    for (auto conn : cell->connections()) {


      RTLIL::SigSpec ss = conn.second;
      
      cout << "\tSigSpec " << id2cstr(conn.first) << " size = " << ss.size() << ", is_wire = " << ss.is_wire() << ", is chunk = " << ss.is_chunk() << endl;

      if (ss.is_chunk() && !ss.is_wire()) {
        for (auto& sigChunk : ss.chunks()) {

          if (sigChunk.wire != nullptr) {
            cout << "Wire = " << id2cstr(sigChunk.wire->name) << endl;
          } else {
            cout << "Wire is null" << endl;

            for (auto& state : sigChunk.data) {
              cout << "State = " << state << endl;
            }
          }
        }
        continue;
        //assert(false);
      }

      assert(ss.is_wire());

      Wire* w = ss.as_wire();

      cout << "\t\t Wire: " << id2cstr(w->name) << ", width = " <<
        w->width << ", " << "start_offset = " << w->start_offset <<
        ", port_id = " << w->port_id << endl;


      Select* from = nullptr;
      Select* to = nullptr;

      string connName = id2cstr(conn.first);
      cout << "connName = " << connName << endl;
      if ((connName != "A") && (connName != "B")) {
        continue;
      }

      if (connName == "A") {
        to = inst->sel("in0");
      } else if (connName == "B") {
        to = inst->sel("in1");
      } else {
        assert(false);
      }
          
      if (w->port_input || w->port_output) {

        from = self->sel(id2cstr(w->name));

      } else {
        string s = id2cstr(w->name);


        cout << "s = " << s << endl;

      reverse(begin(s), end(s));
      string portName = s.substr(0, s.find("_"));
      string cellName = s.substr(s.find("_") + 1, s.size());

      reverse(begin(cellName), end(cellName));
      reverse(begin(portName), end(portName));

        // string cellName = s.substr(0, s.find("_"));
        // string portName = s.substr(s.find("_") + 1, s.size());

        auto targetCell = rmod->cells_[IdString(cellName)];

        assert(targetCell != nullptr);

        cout << "targetCell = " << id2cstr(targetCell->name) << endl;

        auto targetInst = instMap[targetCell];

        assert(targetInst != nullptr);

        // TODO: Create select string from the yosys port name instead of
        // "out"
        from = targetInst->sel("out");
      }

      assert(from != nullptr);
      assert(to != nullptr);

      def->connect(from, to);
          
    }

  }
}

void printModuleInfo(RTLIL::Module* const rmod) {
  cout << "########## Module info for module: " << id2cstr(rmod->name) << endl;

  SigMap sigmap(rmod);
  dict<SigBit, Cell*> sigbit_to_driver_index;
  for (auto cell : rmod->cells()) {
    for (auto conn : cell->connections()) {
      if (cell->output(conn.first)) {
        for (auto bit : sigmap(conn.second)) {
          sigbit_to_driver_index[bit] = cell;
        }
      }
    }
  }

  dict<SigBit, Cell*> sigbit_to_receiver_index;
  for (auto cell : rmod->cells()) {
    for (auto conn : cell->connections()) {
      if (cell->input(conn.first)) {
        for (auto bit : sigmap(conn.second)) {
          sigbit_to_receiver_index[bit] = cell;
        }
      }
    }
  }
  
  cout << "All wires" << endl;
  for (auto wire : rmod->wires()) {
    cout << "\t" << id2cstr(wire->name) << endl;
    int i = 0;
    for (auto& bit : sigmap(wire)) {

      cout << "\t\tDrivers" << endl;
      Cell* driverCell = sigbit_to_driver_index[bit];

      if (driverCell != nullptr) {
        cout << "\t\t" << id2cstr(wire->name) << " " << i << " = " << id2cstr(sigbit_to_driver_index[bit]->name) << endl;
      } else {
        cout << "\t\t" << id2cstr(wire->name) << " " << i << " = NULL;" << endl;
      }

      cout << "\t\tReceivers" << endl;
      Cell* receiverCell = sigbit_to_receiver_index[bit];

      if (receiverCell != nullptr) {
        cout << "\t\t" << id2cstr(wire->name) << " " << i << " = " << id2cstr(sigbit_to_receiver_index[bit]->name) << endl;
      } else {
        cout << "\t\t" << id2cstr(wire->name) << " " << i << " = NULL;" << endl;
      }
      
      i++;
    }
  }

  cout << "All connections" << endl;      

  for (auto conn : rmod->connections()) {
    SigSpec l = conn.first;
    SigSpec r = conn.second;

    cout << "\tSigSpec size = " << l.size() << ", is_wire = " << l.is_wire() << ", is chunk = " << l.is_chunk() << endl;
        
  }

}

struct ToCoreIRPass : public Yosys::Pass {
	ToCoreIRPass() : Pass("to_coreir") { }

  virtual void execute(std::vector<std::string>, RTLIL::Design *design) {


    
    // Seems like wires are everything 


    for (auto it : design->modules()) {

      printModuleInfo(it);

    }

    assert(false);

    Context* c = newContext();
    log_header(design, "Executing TOCOREIR pass (find stub nets).\n");

    // Find and create coreir stubs for all modules
    Namespace* g = c->getGlobal();

    CoreIRLoadLibrary_rtlil(c);

    map<string, CoreIR::Module*> modMap = buildModuleMap(design, c, g);

    // Now with all modules added create module definitions
    for (auto &it : design->modules_) {

      CoreIR::Module* mod = modMap[id2cstr(it.first)];

      SigMap assign_map(it.second);
      
      assert(mod != nullptr);

      CoreIR::ModuleDef* def = mod->newModuleDef();

      RTLIL::Module* rmod = it.second;

      map<Cell*, Instance*> instMap = buildInstanceMap(rmod, modMap, c, def);

      cout << "Adding connections for module = " << mod->getName() << endl;

      addConnections(rmod, instMap, def);
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
