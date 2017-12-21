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

#include <string>
#include <map>
#include <set>

using namespace CoreIR;
using namespace std;

USING_YOSYS_NAMESPACE
PRIVATE_NAMESPACE_BEGIN

void print_cell_info(RTLIL::Cell* const cell);

// Extending node used to extend
void addExtend(CoreIR::Context* const c) {
  
}

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

Namespace* CoreIRLoadLibrary_rtlil(CoreIR::Context* const c) {
  auto rtLib = c->newNamespace("rtlil");



  vector<string> rtlilBinops{"and", "or", "xor", "xnor", "shl", "shr", "sshl", "sshr", "logic_and", "logic_or", "eqx", "nex", "lt", "le", "eq", "ne", "ge", "gt", "add", "sub", "mul", "div", "mod", "pow"};

  for (auto& name : rtlilBinops) {
    Params binopParams = {{"A_SIGNED", c->Bool()},
                          {"B_SIGNED", c->Bool()},
                          {"A_WIDTH", c->Int()},
                          {"B_WIDTH", c->Int()},
                          {"Y_WIDTH", c->Int()}};
    TypeGen* logic_andTP =
      rtLib->newTypeGen(
                        name,
                        binopParams,
                        [](Context* c, Values genargs) {
                          uint a_width = genargs.at("A_WIDTH")->get<int>();
                          uint b_width = genargs.at("B_WIDTH")->get<int>();
                          uint y_width = genargs.at("Y_WIDTH")->get<int>();

                          return c->Record({
                              {"A", c->BitIn()->Arr(a_width)},
                                {"B", c->BitIn()->Arr(b_width)},
                                  {"Y",c->Bit()->Arr(y_width)}});
                        });

    rtLib->newGeneratorDecl(name, logic_andTP, binopParams);
    
  }

  vector<string> rtlilUnops{"not", "pos", "neg", "reduce_and", "reduce_or", "reduce_xor", "reduce_xnor", "reduce_bool", "logic_not"};

  for (auto& name : rtlilUnops) {
    Params binopParams = {{"A_SIGNED", c->Bool()},
                          {"A_WIDTH", c->Int()},
                          {"Y_WIDTH", c->Int()}};
    TypeGen* logic_andTP =
      rtLib->newTypeGen(
                        name,
                        binopParams,
                        [](Context* c, Values genargs) {
                          uint a_width = genargs.at("A_WIDTH")->get<int>();
                          uint y_width = genargs.at("Y_WIDTH")->get<int>();

                          return c->Record({
                              {"A", c->BitIn()->Arr(a_width)},
                                {"Y",c->Bit()->Arr(y_width)}});
                        });

    rtLib->newGeneratorDecl(name, logic_andTP, binopParams);
    
  }

  Params muxParams = {{"WIDTH", c->Int()}};
  TypeGen* muxTP =
    rtLib->newTypeGen(
                      "rtMux",
                      muxParams,
                      [](Context* c, Values genargs) {
                        uint width = genargs.at("WIDTH")->get<int>();

                        return c->Record({
                            {"A", c->BitIn()->Arr(width)},
                              {"B", c->BitIn()->Arr(width)},
                                {"S", c->BitIn()},
                                  {"Y",c->Bit()->Arr(width)}});
                      });

  rtLib->newGeneratorDecl("rtMux", muxTP, muxParams);

  Params dffParams = {{"WIDTH", c->Int()}, {"CLK_POLARITY", c->Bool()}};
  TypeGen* dffTP =
    rtLib->newTypeGen(
                      "dff",
                      dffParams,
                      [](Context* c, Values genargs) {
                        uint width = genargs.at("WIDTH")->get<int>();

                        return c->Record({
                            {"CLK", c->BitIn()},
                              {"D", c->BitIn()->Arr(width)},
                                {"Q", c->Bit()->Arr(width)}});
                      });

  rtLib->newGeneratorDecl("dff", dffTP, dffParams);
    
  return rtLib;
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

  cout << "Cell: " <<
    RTLIL::id2cstr(cell->name) <<
    RTLIL::id2cstr(cell->type) << endl;

  for (auto& param : cell->parameters) {
    cout << "\tParam: " <<
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

    

    if (isRTLILBinop(cellTp)) {
      string opName = cellTp.substr(1, cellTp.size());
      cout << "opName = " << opName << endl;
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
      cout << "opName = " << opName << endl;
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
      cout << "opName = " << opName << endl;
      string instName = coreirSafeName(cellName);

      int width = getIntParam(cell, "\\WIDTH");

      // Change to just mux?
      auto inst = def->addInstance(instName, "rtlil.rtMux",
                                   {{"WIDTH", CoreIR::Const::make(c, width)}});

      instMap[cell] = inst;
      
    } else if (cellTp == "$dff") {

      // string opName = cellTp.substr(1, cellTp.size());
      // cout << "opName = " << opName << endl;
      string instName = coreirSafeName(cellName);

      int width = getIntParam(cell, "\\WIDTH");
      int polarity = getIntParam(cell, "\\CLK_POLARITY");

      auto inst = def->addInstance(instName, "rtlil.dff",
                                   {{"WIDTH", CoreIR::Const::make(c, width)},
                                       {"CLK_POLARITY", CoreIR::Const::make(c, (bool) polarity)}});

      instMap[cell] = inst;

    } else {

      string instName = coreirSafeName(cellName);

      string cellTypeStr = id2cstr(cell->type);
      if (modMap.find(cellTypeStr) == end(modMap)) {
        cout << "Unsupported Cell type = " << id2cstr(cell->name) << " : " << id2cstr(cell->type) << ", skipping." << endl;

        print_cell_info(cell);

        assert(false);
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
    assert(wireOffset == 0);

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
  for (auto cell : rmod->cells()) {
    for (auto conn : cell->connections()) {
      if (cell->output(conn.first)) {
        for (auto bit : sigmap(conn.second)) {
          //for (auto bit : conn.second) {
          sigbit_to_driver_index[bit] = cell;
          sigbit_to_driver_port_index[bit] = id2cstr(conn.first);
        }
      }
    }
  }

  for (auto wire : rmod->wires()) {
    if (wire->port_input) {
      for (auto bit : sigmap(wire)) {
        sigbit_to_driver_port_index[bit] = id2cstr(wire->name);
      }
    }
  }

  // Add connections from inputs to drivers
  for (auto cell : rmod->cells()) {
    for (auto conn : cell->connections()) {
      if (cell->input(conn.first)) {
        for (auto bit : sigmap(conn.second)) {
          Cell* driver = sigbit_to_driver_index[bit];
          string port = sigbit_to_driver_port_index[bit];

          // From driver to the current bit
          Select* to = instanceSelect(cell,
                                      id2cstr(conn.first),
                                      bit.offset,
                                      instMap);

          Select* from = nullptr;
          if (driver != nullptr) {
            from = instanceSelect(driver, port, bit.offset, instMap);
          } else {

            from = def->sel("self")->sel(port);
            if (!isBitType(from->getType())) {
              from = from->sel(bit.offset);
            } else {
              assert(bit.offset == 0);
            }
          }

          assert(from != nullptr);

          def->connect(from, to);
        }
      }
    }
  }

  for (auto wire : rmod->wires()) {
    if (wire->port_output) {
      for (auto bit : sigmap(wire)) {
        Select* from = nullptr;

        assert(from != nullptr);

        // E.g. self->out0
        Select* to = cast<Select>(def->sel(id2cstr(wire->name)));
        if (!isBitType(to->getType())) {
          to = to->sel(bit.offset);
        } else {
          assert(bit.offset == 0);
        }

        def->connect(from, to);
      }
    }
  }

  return;

  // for (auto& conn : rmod->connections()) {

  //   SigSpec portSig = conn.first;
  //   SigSpec resSig = conn.second;

  //   assert(portSig.is_wire());
  //   assert(resSig.is_wire());

  //   Wire* w = portSig.as_wire();
  //   Wire* r = resSig.as_wire();
  //   cout << "w = " << id2cstr(w->name) << endl;
  //   cout << "r = " << id2cstr(w->name) << endl;

  //   assert(w->port_input || w->port_output);

  // }

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


  // NOTE: This may not handle cross connections correctly, not sure how to
  // get those offsets

  // NOTE: I also have not tested one to many connections
  cout << "All wires" << endl;
  for (auto wire : rmod->wires()) {
    cout << "\t" << id2cstr(wire->name) << endl;
    int i = 0;

    if (wire->port_output) {
      cout << "### output = " << id2cstr(wire->name) << endl;
    } else if (wire->port_input) {
      cout << "### input = " << id2cstr(wire->name) << endl;

      for (auto& bit : sigmap(wire)) {

        Cell* driverCell = sigbit_to_driver_index[bit];
        assert(driverCell == nullptr);

        Cell* receiverCell = sigbit_to_receiver_index[bit];
        
        if (receiverCell != nullptr) {

          string driverPort = id2cstr(wire->name);
          string receiverPort = sigbit_to_receiver_port_index[bit];

          // NOTE: What should bit.offset be here?
          auto driverSelPort = def->sel("self")->sel(driverPort);
          Select* driverSel = driverSelPort;
          if ((driverSelPort->getType()->getKind() == Type::TK_Bit) ||
              (driverSelPort->getType()->getKind() == Type::TK_BitIn)) {
            assert(bit.offset == 0);
          } else {
            driverSel = driverSelPort->sel(bit.offset);
          }

          // NOTE: What should bit.offset be here?
          auto receiverSel =
            instanceSelect(receiverCell, receiverPort, bit.offset, instMap);

          def->connect(driverSel, receiverSel);
        }
        i++;

      }
      
    } else {

      for (auto& bit : sigmap(wire)) {

        // cout << "\t\tBit wire = " << id2cstr(bit.wire->name) << endl;
        // cout << "\t\tDrivers" << endl;
        Cell* driverCell = sigbit_to_driver_index[bit];

        // if (driverCell != nullptr) {
        //   cout << "\t\t" << id2cstr(wire->name) << " " << bit.offset << " = " << id2cstr(sigbit_to_driver_index[bit]->name) << "." << sigbit_to_driver_port_index[bit] << endl;
        // } else {
        //   cout << "\t\t" << id2cstr(wire->name) << " " << bit.offset << " = NULL;" << endl;
        // }

        //cout << "\t\tReceivers" << endl;
        Cell* receiverCell = sigbit_to_receiver_index[bit];

        // if (receiverCell != nullptr) {
        //   cout << "\t\t" << id2cstr(wire->name) << " " << bit.offset << " = " << id2cstr(sigbit_to_receiver_index[bit]->name) << "." << sigbit_to_receiver_port_index[bit] << endl;
        // } else {
        //   cout << "\t\t" << id2cstr(wire->name) << " " << bit.offset << " = NULL;" << endl;
        // }

        if ((receiverCell != nullptr) &&
            (driverCell != nullptr)) {

          string driverPort = sigbit_to_driver_port_index[bit];
          string receiverPort = sigbit_to_receiver_port_index[bit];

          // NOTE: What should bit.offset be here?
          auto driverSel =
            instanceSelect(driverCell, driverPort, bit.offset, instMap);

          // NOTE: What should bit.offset be here?
          auto receiverSel =
            instanceSelect(receiverCell, receiverPort, bit.offset, instMap);

          def->connect(driverSel, receiverSel);
        } else {
          cout << "Wire = " << id2cstr(wire->name) << endl;
          //assert(wire->port_input || wire->port_output);
        }
      
        i++;
      }
    }
  }

}


struct ToCoreIRPass : public Yosys::Pass {
	ToCoreIRPass() : Pass("to_coreir") { }

  virtual void execute(std::vector<std::string>, RTLIL::Design *design) {


    
    // Seems like wires are everything 

    // for (auto it : design->modules()) {

    //   printModuleInfo(it);

    // }

    // return;
    //assert(false);

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

      buildSelectMap(rmod, instMap, c, def);
      //cout << "Adding connections for module = " << mod->getName() << endl;

      //addConnections(rmod, instMap, def);
      mod->setDef(def);
    }

    assert(modMap.size() > 0);

    CoreIR::Module* top = begin(modMap)->second;
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
