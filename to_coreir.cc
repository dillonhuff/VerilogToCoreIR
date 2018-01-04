// This is free and unencumbered software released into the public domain.
//
// Anyone is free to copy, modify, publish, use, compile, sell, or
// distribute this software, either in source code form or as a compiled
// binary, for any purpose, commercial or non-commercial, and by any
// means.

#include "kernel/yosys.h"
#include "kernel/sigtools.h"

#include "algorithm.h"

#include "coreir.h"
#include "coreir/libs/rtlil.h"

#include <string>
#include <map>
#include <set>

using namespace CoreIR;
using namespace std;

USING_YOSYS_NAMESPACE
PRIVATE_NAMESPACE_BEGIN

void print_cell_info(RTLIL::Cell* const cell);

bool isRTLILBinop(const std::string& cellTp) {
  if (cellTp[0] == '$') {
    string opName = cellTp.substr(1, cellTp.size());
    vector<string> rtlilBinops{"and", "or", "xor", "xnor", "shl", "shr", "sshl", "sshr", "logic_and", "logic_or", "eqx", "nex", "lt", "le", "eq", "ne", "ge", "gt", "add", "sub", "mul", "div", "mod", "pow"};

    for (auto& e : rtlilBinops) {
      if (e == opName) {
        return true;
      }
    }
  }

  return false;
}

bool isRTLILUnop(const std::string& cellTp) {
  if (cellTp[0] == '$') {
    string opName = cellTp.substr(1, cellTp.size());

  vector<string> rtlilUnops{"not", "pos", "neg", "reduce_and", "reduce_or", "reduce_xor", "reduce_xnor", "reduce_bool", "logic_not"};

    for (auto& e : rtlilUnops) {
      if (e == opName) {
        return true;
      }
    }
  }

  return false;
}

int getIntParam(Cell* const cell, const std::string& str) {
  auto param = cell->parameters.find(str);

  if (param == std::end(cell->parameters)) {
    cout << "Cannot find parameter " << str << " in " << endl;
    print_cell_info(cell);
    assert(false);
  }

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
    } else if (cellName[i] == '\\') {
      instName += "__BACKSLASH__";
    } else if (cellName[i] == '=') {
      instName += "__EQUALS__";
    } else {
      instName += cellName[i];
    }

  }

  return instName;
}

void addModule(const std::string& modName,
               RTLIL::Module* rmod,
               std::map<string, CoreIR::Module*>& modMap,
               RTLIL::Design * const design,
               CoreIR::Context* const c,
               Namespace* const g) {

      cout << "Ports" << endl;
      for (auto& conn : rmod->ports) {
        cout << "\t" << id2cstr(conn) << endl;
      }

      cout << "Parameters" << endl;
      for (auto& param : rmod->avail_parameters) {
        cout << "\t" << id2cstr(param) << endl;
      }
      
      cout << "# of Connections in " << id2cstr(rmod->name) << " = " << rmod->connections().size() << endl;
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

      modMap[modName] =
        g->newModuleDecl(modName, c->Record(args));


}

std::map<string, CoreIR::Module*>
buildModuleMap(RTLIL::Design * const design,
               CoreIR::Context* const c,
               Namespace* const g) {

  map<string, CoreIR::Module*> modMap;
  for (auto &it : design->modules_) {

    if (design->selected_module(it.first)) {

      cout << "Reading module " << id2cstr(it.second->name) << endl;
        
      RTLIL::Module* rmod = it.second;

      addModule(id2cstr(it.first), rmod, modMap, design, c, g);

    }
  }

  return modMap;
}

void print_cell_info(RTLIL::Cell* const cell) {

  string cellTp = RTLIL::id2cstr(cell->type);
  string cellName = RTLIL::id2cstr(cell->name);
        
  cout << cellName << endl;

  cout << "Cell: " <<
    RTLIL::id2cstr(cell->name) << " : " << 
    RTLIL::id2cstr(cell->type) << endl;

  for (auto& param : cell->parameters) {
    cout << "\tParam: " <<
      RTLIL::id2cstr(param.first) << 
      param.second.as_string().c_str() << endl;
  }

  for (auto& conn : cell->connections()) {
    cout << "\tPort: " << id2cstr(conn.first) << " : " << conn.second.size() << endl;
  }

}

map<Cell*, Instance*> buildInstanceMap(RTLIL::Module* const rmod,
                                       std::map<string, CoreIR::Module*>& modMap,
                                       CoreIR::Context* const c,
                                       CoreIR::Namespace* const g,
                                       CoreIR::ModuleDef* const def) {

  map<Cell*, Instance*> instMap;
  for (auto& cell_iter : rmod->cells_) {
    Cell* cell = cell_iter.second;

    string cellTp = RTLIL::id2cstr(cell->type);
    string cellName = RTLIL::id2cstr(cell->name);
        
    if (isRTLILBinop(cellTp)) {
      string opName = cellTp.substr(1, cellTp.size());
      //cout << "opName = " << opName << endl;
      string instName = coreirSafeName(cellName);

      int widthA = getIntParam(cell, "\\A_WIDTH");
      int widthB = getIntParam(cell, "\\B_WIDTH");
      int widthY = getIntParam(cell, "\\Y_WIDTH");
      int signedA = getIntParam(cell, "\\A_SIGNED");
      int signedB = getIntParam(cell, "\\B_SIGNED");

      auto inst = def->addInstance(instName, "rtlil." + opName,
                                   {{"A_SIGNED", CoreIR::Const::make(c, (bool) signedA)},
                                       {"B_SIGNED", CoreIR::Const::make(c, (bool) signedB)},
                                         {"A_WIDTH", CoreIR::Const::make(c, widthA)},
                                           {"B_WIDTH", CoreIR::Const::make(c, widthB)},
                                             {"Y_WIDTH", CoreIR::Const::make(c, widthY)}});

      instMap[cell] = inst;
      
      
    } else if (isRTLILUnop(cellTp)) {
      string opName = cellTp.substr(1, cellTp.size());
      //cout << "opName = " << opName << endl;
      string instName = coreirSafeName(cellName);

      int widthA = getIntParam(cell, "\\A_WIDTH");
      int widthY = getIntParam(cell, "\\Y_WIDTH");
      int signedA = getIntParam(cell, "\\A_SIGNED");

      auto inst = def->addInstance(instName, "rtlil." + opName,
                                   {{"A_SIGNED", CoreIR::Const::make(c, (bool) signedA)},
                                         {"A_WIDTH", CoreIR::Const::make(c, widthA)},
                                             {"Y_WIDTH", CoreIR::Const::make(c, widthY)}});

      instMap[cell] = inst;
      
    } else if (cellTp == "$mux") {
      string opName = cellTp.substr(1, cellTp.size());
      //cout << "opName = " << opName << endl;
      string instName = coreirSafeName(cellName);

      int width = getIntParam(cell, "\\WIDTH");

      // Change to just mux?
      auto inst = def->addInstance(instName, "rtlil.rtMux",
                                   {{"WIDTH", CoreIR::Const::make(c, width)}});

      instMap[cell] = inst;
      
    } else if (cellTp == "$dlatch") {

      string instName = coreirSafeName(cellName);

      int width = getIntParam(cell, "\\WIDTH");
      int polarity = getIntParam(cell, "\\EN_POLARITY");

      auto inst = def->addInstance(instName, "rtlil.dlatch",
                                   {{"WIDTH", CoreIR::Const::make(c, width)},
                                       {"EN_POLARITY", CoreIR::Const::make(c, (bool) polarity)}});

      instMap[cell] = inst;

    } else if (cellTp == "$dff") {

      string instName = coreirSafeName(cellName);

      int width = getIntParam(cell, "\\WIDTH");
      int polarity = getIntParam(cell, "\\CLK_POLARITY");

      auto inst = def->addInstance(instName, "rtlil.dff",
                                   {{"WIDTH", CoreIR::Const::make(c, width)},
                                       {"CLK_POLARITY", CoreIR::Const::make(c, (bool) polarity)}});

      instMap[cell] = inst;

    } else if (cellTp == "$adff") {

      string instName = coreirSafeName(cellName);

      int width = getIntParam(cell, "\\WIDTH");
      int polarity = getIntParam(cell, "\\CLK_POLARITY");
      int rstPolarity = getIntParam(cell, "\\ARST_POLARITY");
      int rstValue = getIntParam(cell, "\\ARST_VALUE");

      auto inst = def->addInstance(instName, "rtlil.adff",
                                   {{"WIDTH", CoreIR::Const::make(c, width)},
                                       {"CLK_POLARITY", CoreIR::Const::make(c, (bool) polarity)},
                                         {"ARST_POLARITY", CoreIR::Const::make(c, (bool) rstPolarity)},
                                           {"ARST_VALUE", CoreIR::Const::make(c, rstValue)}});

      instMap[cell] = inst;

    } else {

      string instName = coreirSafeName(cellName);

      string cellTypeStr = id2cstr(cell->type);
      if (modMap.find(cellTypeStr) == end(modMap)) {
        cout << "Unsupported Cell type = " << id2cstr(cell->name) << " : " << id2cstr(cell->type) << ", skipping." << endl;

        print_cell_info(cell);

        assert(false);
      } else {

        if (cell->parameters.size() == 0) {

          auto inst = def->addInstance(instName, modMap[cellTypeStr]);
          instMap[cell] = inst;
        } else {

          RTLIL::Module* containerMod = cell->module;
          Design* rtd = containerMod->design;

          RTLIL::Module* rtmod = rtd->modules_[cell->type];
          cout << "RTMOD = " << id2cstr(rtmod->name) << endl;

          auto modInstNameR = rtmod->derive(rtmod->design, cell->parameters);

          string modInstName = coreirSafeName(id2cstr(modInstNameR));
          cout << "Derived module instance name = " << modInstName << endl;

          if (modMap.find(modInstName) == end(modMap)) {
            // Add to coreir module map
            RTLIL::Module* genMod = rtmod->design->modules_[modInstNameR];

            addModule(modInstName, genMod, modMap, rtd, c, g);

            cout << "Generated module " << id2cstr(genMod->name) << " has " << genMod->avail_parameters.size() << " parameters" << endl;
          }

          auto inst = def->addInstance(instName, modMap[modInstName]);
          instMap[cell] = inst;
          
          //auto inst = def->addInstance();
        }
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

std::string coreirPort(Cell* const cell,
                       const std::string& portName) {
  string cellTp = id2cstr(cell->type);

  return portName;
}

bool isBitType(CoreIR::Type* const tp) {
  if ((tp->getKind() == Type::TK_Bit) ||
      (tp->getKind() == Type::TK_BitIn)) {
    return true;
  }

  return false;
}

CoreIR::Select* instanceSelect(Cell* const cell,
                               const std::string& portName,
                               const int wireOffset,
                               map<Cell*, CoreIR::Instance*>& instMap) {

  assert(cell != nullptr);

  Instance* inst = instMap[cell];

  if (inst == nullptr) {
    cout << "Error: Instance map does not contain " << endl;
    print_cell_info(cell);
    assert(false);
  }

  string coreIRPort = coreirPort(cell, portName);

  auto port = inst->sel(coreIRPort);

  if ((port->getType()->getKind() == Type::TK_Bit) ||
      (port->getType()->getKind() == Type::TK_BitIn)) {
    if (wireOffset != 0) {

      cout << "Error: Trying to select bit " << wireOffset << " from single bit port: " << port->toString() << ", portName = " << portName << endl;
      cout << "\tRTLIL Cell" << endl;
      print_cell_info(cell);
      cout << "\tRTLIL Port Name = " << portName << endl;
      cout << "\tWire offset     = " << wireOffset << endl;
      assert(false);
    }

    return port;
  }

  auto portBit = port->sel(wireOffset);

  return portBit;
}

void printModuleInfo(RTLIL::Module* const rmod) {
  cout << "########## Module info for module: " << id2cstr(rmod->name) << endl;

  SigMap sigmap(rmod);
  dict<SigBit, Cell*> sigbit_to_driver_index;
  dict<SigBit, string> sigbit_to_driver_port_index;
  for (auto cell : rmod->cells()) {
    for (auto conn : cell->connections()) {
      if (cell->output(conn.first)) {
        for (auto bit : sigmap(conn.second)) {
          sigbit_to_driver_index[bit] = cell;
          sigbit_to_driver_port_index[bit] = id2cstr(conn.first);
        }
      }
    }
  }

  dict<SigBit, Cell*> sigbit_to_receiver_index;
  dict<SigBit, string> sigbit_to_receiver_port_index;
  for (auto cell : rmod->cells()) {
    for (auto conn : cell->connections()) {
      if (cell->input(conn.first)) {
        for (auto bit : sigmap(conn.second)) {
          sigbit_to_receiver_index[bit] = cell;
          sigbit_to_receiver_port_index[bit] = id2cstr(conn.first);
        }
      }
    }
  }

  cout << "----All cell connections" << endl;
  for (auto cell : rmod->cells()) {
    cout << "\tConnections for " << id2cstr(cell->name) << endl;
    for (auto conn : cell->connections()) {
      cout << "\t\t" << id2cstr(conn.first) << " --> " << id2cstr(conn.second.as_wire()->name) << endl;
    }
  }
  
  cout << "All wires" << endl;
  for (auto wire : rmod->wires()) {
    cout << "\t" << id2cstr(wire->name) << endl;
    int i = 0;
    for (auto& bit : sigmap(wire)) {

      cout << "\t\tBit wire = " << id2cstr(bit.wire->name) << endl;
      cout << "\t\tDrivers" << endl;
      Cell* driverCell = sigbit_to_driver_index[bit];

      if (driverCell != nullptr) {
        cout << "\t\t" << id2cstr(wire->name) << " " << bit.offset << " = " << id2cstr(sigbit_to_driver_index[bit]->name) << "." << sigbit_to_driver_port_index[bit] << endl;
      } else {
        cout << "\t\t" << id2cstr(wire->name) << " " << bit.offset << " = NULL;" << endl;
      }

      cout << "\t\tReceivers" << endl;
      Cell* receiverCell = sigbit_to_receiver_index[bit];

      if (receiverCell != nullptr) {
        cout << "\t\t" << id2cstr(wire->name) << " " << bit.offset << " = " << id2cstr(sigbit_to_receiver_index[bit]->name) << "." << sigbit_to_receiver_port_index[bit] << endl;
      } else {
        cout << "\t\t" << id2cstr(wire->name) << " " << bit.offset << " = NULL;" << endl;
      }
      
      i++;
    }
  }

  cout << "All wire <-> wire connections" << endl;      

  for (auto conn : rmod->connections()) {
    SigSpec l = conn.first;
    SigSpec r = conn.second;

    if (l.is_wire() && r.is_wire()) {
      cout << "( " << id2cstr(l.as_wire()->name) << ", " << id2cstr(r.as_wire()->name) << " )" << endl;
      //cout << "\tSigSpec size = " << l.size() << ", is_wire = " << l.is_wire() << ", is chunk = " << l.is_chunk() << endl;
    }
        
  }

}

void
buildSelectMap(RTLIL::Module* const rmod,
               map<Cell*, CoreIR::Instance*>& instMap,
               CoreIR::Context* const c,
               ModuleDef* const def) {

  cout << "########## Module info for module: " << id2cstr(rmod->name) << endl;

  SigMap sigmap(rmod);

  // Build map from 
  dict<SigBit, Cell*> sigbit_to_driver_index;
  dict<SigBit, string> sigbit_to_driver_port_index;
  dict<SigBit, int> sigbit_to_driver_offset;

  for (auto cell : rmod->cells()) {
    for (auto conn : cell->connections()) {
      if (cell->output(conn.first)) {

        int i = 0;
        for (auto bit : sigmap(conn.second)) {
          //for (auto bit : conn.second) {
          sigbit_to_driver_index[bit] = cell;
          sigbit_to_driver_port_index[bit] = id2cstr(conn.first);
          sigbit_to_driver_offset[bit] = i;

          // if (bit.offset != i) {
          //   cout << "bit.offset = " << bit.offset << endl;
          //   cout << "i          = " << i << endl;
          //   assert(false);
          // }

          i++;
        }
      }
    }
  }

  for (auto wire : rmod->wires()) {
    if (wire->port_input) {
      int i = 0;
      for (auto bit : sigmap(wire)) {
        sigbit_to_driver_port_index[bit] = id2cstr(wire->name);
        sigbit_to_driver_offset[bit] = i;
        i++;
      }
    }
  }

  cout << "Adding input to driver connections" << endl;
  // Add connections from inputs to drivers
  for (auto cell : rmod->cells()) {
    for (auto conn : cell->connections()) {
      if (cell->input(conn.first)) {

        // Not sure if I really need this index variable or if the index is
        // stored somewhere else
        int i = 0;
        for (auto bit : sigmap(conn.second)) {

          if (bit.wire != nullptr) {
            

            Cell* driver = sigbit_to_driver_index[bit];

            // if (driver != nullptr) {
            // cout << "Driver for bit " << bit.data << " of wire " << id2cstr(bit.wire->name) << " = " << id2cstr(driver->name) << " : " << id2cstr(driver->type) << endl;
            // } else {
            //   cout << "Driver for bit " << bit.data << " of wire " << id2cstr(bit.wire->name) << " = NULL" << endl;
            // }

            if (sigbit_to_driver_port_index.find(bit) ==
                end(sigbit_to_driver_port_index)) {
              cout << "Bit " << bit.offset << " for wire " << id2cstr(bit.wire->name) << " has no port?" << endl;
              //assert(false);
              continue;
            }

            string port = sigbit_to_driver_port_index[bit];
            //cout << "offset = " << bit.offset << endl;

            //cout << "i = " << i << endl;
            // From driver to the current bit
            Select* to = instanceSelect(cell,
                                        id2cstr(conn.first),
                                        i,
                                        //bit.offset,
                                        instMap);
            //cout << "to = " << to->toString() << endl;

            Select* from = nullptr;
            if (driver != nullptr) {
              from = instanceSelect(driver, port, sigbit_to_driver_offset[bit], /*bit.offset*/ instMap);
            } else {

              from = def->sel("self")->sel(port);
              if (!isBitType(from->getType())) {
                // The sigbit
                assert(sigbit_to_driver_offset.find(bit) !=
                       end(sigbit_to_driver_offset));

                from = from->sel(sigbit_to_driver_offset[bit]);
              } else {
                assert(bit.offset == 0);
              }
            }

            assert(from != nullptr);

            //cout << "from = " << from->toString() << endl;

            def->connect(from, to);
          } else {
            //cout << "Wire is null, bit state = " << bit.data << endl;

            // Q: How do I know what offset the bit maps to in a wire if the bit
            // offset field is not set? For now use index variable
            
            // From driver to the current bit
            Select* to = instanceSelect(cell,
                                        id2cstr(conn.first),
                                        i,
                                        instMap);

            auto bitConst =
              def->addInstance(coreirSafeName(to->toString() + "$bit_const_" + to_string(i)),
                               "corebit.const",
                               {{"value", CoreIR::Const::make(c, bit.data == 1 ? true : false)}});;

            Select* from = bitConst->sel("out");

            def->connect(from, to);

          }
          i++;
        }
      }
    }
  }

  cout << "Adding output connections to wires" << endl;
  for (auto wire : rmod->wires()) {
    if (wire->port_output) {

      cout << "Wiring up inputs to output port " << id2cstr(wire->name) << endl;
      int i = 0;
      for (auto bit : sigmap(wire)) {

        if (bit.wire != nullptr) {
          //cout << "Bit wire = " << id2cstr(bit.wire->name) << ", offset = " << bit.offset << endl;

          if (sigbit_to_driver_port_index.find(bit) !=
              end(sigbit_to_driver_port_index)) {
        
            Cell* driver = sigbit_to_driver_index[bit];
            string port = sigbit_to_driver_port_index[bit];
            int offset = sigbit_to_driver_offset[bit];

            // if (driver != nullptr) {
            //   cout << "Driver cell = " << id2cstr(driver->name) << endl;
            // } else {
            //   cout << "Driver is NULL" << endl;
            // }
            //cout << "Driver port = " << port << endl;

            //cout << "Wiring up " << id2cstr(wire->name) << ", i = " << i << endl;
            Select* from = nullptr;
            if (driver != nullptr) {
              //cout << "Wiring up driver" << endl;
              from = instanceSelect(driver, port, offset /*bit.offset*/, instMap);
            } else {

              from = def->sel("self")->sel(port);
              if (!isBitType(from->getType())) {
                from = from->sel(offset); //from->sel(i); //bit.offset);
              } else {
                assert(bit.offset == 0);
              }
            }
        
            assert(from != nullptr);

            //cout << "Wiring to select" << endl;
            // E.g. self->out0
            Select* to = cast<Select>(def->sel("self")->sel(id2cstr(wire->name)));
            if (!isBitType(to->getType())) {
              //to = to->sel(bit.offset);
              to = to->sel(i);
            } else {
              assert(bit.offset == 0);
            }

            def->connect(from, to);
          } else {
            cout << "ERROR: No port for " << id2cstr(wire->name) << endl;
            //assert(false);
          }
        } else {
          cout << "Wire is null, data = " << bit.data << endl;
          assert(false);
        }
        i++;
      }
    }
  }

  return;

}


struct ToCoreIRPass : public Yosys::Pass {
	ToCoreIRPass() : Pass("to_coreir") { }

  virtual void execute(std::vector<std::string>, RTLIL::Design *design) {
    // Seems like wires are everything 

    // for (auto it : design->modules()) {

    //   printModuleInfo(it);

    // }

    // return;

    Context* c = newContext();
    log_header(design, "Executing TOCOREIR pass (find stub nets).\n");

    // Find and create coreir stubs for all modules
    Namespace* g = c->getGlobal();

    CoreIRLoadLibrary_rtlil(c);

    map<string, CoreIR::Module*> modMap = buildModuleMap(design, c, g);

    // Now with all modules added create module definitions
    for (auto &it : design->modules_) {

      CoreIR::Module* mod = modMap[id2cstr(it.first)];

      cout << "Parameters for " << mod->getName() << endl;
      for (auto& param : (it.second)->avail_parameters) {
        cout << "\t" << id2cstr(param) << endl;
      }
      SigMap assign_map(it.second);
      
      assert(mod != nullptr);

      CoreIR::ModuleDef* def = mod->newModuleDef();

      RTLIL::Module* rmod = it.second;

      map<Cell*, Instance*> instMap = buildInstanceMap(rmod, modMap, c, g, def);

      cout << "# of instances in " << mod->getName() << " = " << instMap.size() << endl;

      buildSelectMap(rmod, instMap, c, def);
      cout << "Setting definition for module = " << mod->getName() << endl;

      mod->setDef(def);
    }

    assert(modMap.size() > 0);

    CoreIR::Module* top = begin(modMap)->second;

    if (modMap.find("top") != end(modMap)) {
      top = modMap["top"];
    }

    string fileName = top->getName() + ".json";
    cout << "Saving to " << fileName << endl;
    if (!saveToFile(g, fileName, top)) {
      cout << "Could not save to json!!" << endl;
      c->die();
    }
    
    deleteContext(c);
  }
} ToCoreIRPass;

PRIVATE_NAMESPACE_END
