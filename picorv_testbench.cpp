#include "coreir.h"
#include "coreir/libs/rtlil.h"
#include "coreir/passes/transform/deletedeadinstances.h"
#include "coreir/passes/transform/unpackconnections.h"
#include "coreir/passes/transform/packconnections.h"

using namespace CoreIR;
using namespace std;

std::vector<char> hexToBytes(const std::string& hex) {
  std::vector<char> bytes;

  for (unsigned int i = 0; i < hex.length(); i += 2) {
    std::string byteString = hex.substr(i, 2);
    char byte = (char) strtol(byteString.c_str(), NULL, 16);
    bytes.push_back(byte);
  }

  return bytes;
}

BitVector hexStringToBitVector(const std::string& str) {
  vector<char> addrBytes = hexToBytes(str);

  assert(addrBytes.size() == 4);

  reverse(addrBytes);

  BitVector configAddr(32, 0);

  int offset = 0;
  for (auto byte : addrBytes) {
    BitVec tmp(8, byte);
    for (uint i = 0; i < (uint) tmp.bitLength(); i++) {
      configAddr.set(offset, tmp.get(i));
      offset++;
    }
  }

  assert(offset == 32);

  return configAddr;
}

void processTop(const std::string& fileName,
                const std::string& topModName) {
  Context* c = newContext();

  CoreIRLoadLibrary_rtlil(c);

  Module* topMod = nullptr;

  if (!loadFromFile(c, fileName, &topMod)) {
    cout << "Could not Load from json!!" << endl;
    c->die();
  }

  topMod = c->getGlobal()->getModule(topModName);
  c->setTop(topMod);

  assert(topMod->hasDef());

  c->runPasses({"rungenerators",
        "removeconstduplicates",
        "flatten",
        "removeconstduplicates",
        "cullzexts",
        "clockifyinterface",
        "deletedeadinstances",
        "packconnections"});

  foldConstants(topMod);

  cout << "Flattened core" << endl;
  cout << "# of instances in " << topMod->getName() << " = " << topMod->getDef()->getInstances().size() << endl;

  if (!saveToFile(c->getGlobal(), "risc5Processed.json", topMod)) {
    cout << "Could not save to json!!" << endl;
    c->die();
  }

  cout << "Saved to file" << endl;

  SimulatorState state(topMod);
  state.setMainClock("self.clk");

  cout << "Got simulator state for top module" << endl;

  state.setClock("self.clk", 0, 1);

  state.setClock("self.pcpi_wr", 0, 0);

  state.setValue("self.irq", BitVec(32, 0));
  state.setValue("self.mem_rdata", BitVec(32, 0));
  state.setValue("self.mem_ready", BitVec(1, 0));

  state.setValue("self.pcpi_rd", BitVec(32, 0));
  state.setValue("self.pcpi_ready", BitVec(1, 0));
  state.setValue("self.pcpi_wait", BitVec(1, 0));
  state.setValue("self.resetn", BitVec(1, 0));
  
  cout << "Executing core" << endl;

  state.execute();
  state.execute();
  
  deleteContext(c);
}

void simulateState(const std::string& fileName,
                   const std::string& topModName) {

  Context* c = newContext();

  CoreIRLoadLibrary_rtlil(c);

  Module* topMod = nullptr;

  cout << "Loading " << topModName << " from file " << fileName << endl;

  if (!loadFromFile(c, fileName, &topMod)) {
    cout << "Could not Load from json!!" << endl;
    c->die();
  }

  topMod = c->getGlobal()->getModule(topModName);
  c->setTop(topMod);

  vector<BitVec> memory;
  for (int i = 0; i < 256; i++) {
    memory.push_back(BitVector(32, 0));
  }
  memory[0] = hexStringToBitVector("3fc00093"); //       li      x1,1020
  memory[1] = hexStringToBitVector("0000a023"); //       sw      x0,0(x1)
  memory[2] = hexStringToBitVector("0000a103"); // loop: lw      x2,0(x1)
  memory[3] = hexStringToBitVector("00110113"); //       addi    x2,x2,1
  memory[4] = hexStringToBitVector("0020a023"); //       sw      x2,0(x1)
  memory[5] = hexStringToBitVector("ff5ff06f"); //       j       <loop>

  SimulatorState state(topMod);
  state.setMainClock("self.clk");

  cout << "Got simulator state for top module" << endl;

  state.setClock("self.clk", 0, 1);
  state.setValue("self.mem_rdata", BitVec(32, 0));
  state.setValue("self.mem_ready", BitVec(1, 0));
  state.setValue("self.resetn", BitVec(1, 0));

  // Do these pcpi commands matter if we are not using a coprocessor?
  state.setClock("self.pcpi_wr", 0, 0);
  state.setValue("self.pcpi_rd", BitVec(32, 0));
  state.setValue("self.pcpi_ready", BitVec(1, 1));
  state.setValue("self.pcpi_wait", BitVec(1, 0));

  // Also not sure if irq matters
  //state.setValue("self.irq", BitVec(32, 0));

  cout << "Initializing" << endl;

  state.execute();

  cout << "Executing for real" << endl;
  state.setClock("self.clk", 0, 1);
  state.setValue("self.resetn", BitVec(1, 1));

  cout << "Executing core" << endl;

  uint nclks = 300;
  for (uint i = 0; i < nclks; i++) {

    //state.runHalfCycle();
    state.execute();

    // cout << "\tmem_valid = " << state.getBitVec("self.mem_valid") << endl;
    // cout << "\tmem_instr = " << state.getBitVec("self.mem_instr") << endl;
    // cout << "\tmem_addr = " << state.getBitVec("self.mem_addr") << endl;
    // cout << "\tmem_wdata = " << state.getBitVec("self.mem_wdata") << endl;
    // cout << "\tmem_wstrb = " << state.getBitVec("self.mem_wstrb") << endl;
    // cout << "\tmem_la_read = " << state.getBitVec("self.mem_la_read") << endl;
    // cout << "\tmem_la_write = " << state.getBitVec("self.mem_la_write") << endl;
    // cout << "\tmem_la_addr = " << state.getBitVec("self.mem_la_addr") << endl;
    // cout << "\tresetn = " << state.getBitVec("self.resetn") << endl;

    // cout << "\teoi = " << state.getBitVec("self.eoi") << endl;

    // cout << endl;
    // cout << "\tsum = " << memory[255] << endl;

    // cout << "REGISTER VALUES" << endl;
    // auto registers = state.getCircStates().back().registers;
    // for (auto r : registers) {
    //   cout << "\t" << r.first << " ";
    //   cout << r.second << endl;
    // }
    
    if ((state.getBitVec("self.mem_valid") == BitVec(1, 1)) &&
        (state.getBitVec("self.mem_ready") != BitVec(1, 1))) {
      //cout << "\tMem valid, mem_addr = " << state.getBitVec("self.mem_addr") << endl;

      if (state.getBitVec("self.mem_addr").to_type<int>() < 1024) {
        //cout << "\tSetting mem ready" << endl;
        state.setValue("self.mem_ready", BitVec(1, 1));

        int mem_addr = state.getBitVec("self.mem_addr").to_type<int>() >> 2;
        //cout << "Loading " << mem_addr << endl;
        state.setValue("self.mem_rdata", memory[mem_addr]);

        BitVector mem_wstrb = state.getBitVec("self.mem_wstrb");
        BitVector mem_wdata = state.getBitVec("self.mem_wdata");
        
        assert(mem_wstrb.bitLength() == 4);

        BitVec val = memory[mem_addr];        

        if (mem_wstrb.get(0)) {

          for (int i = 0; i < 8; i++) {
            val.set(i, mem_wdata.get(i));
          }

        }
        if (mem_wstrb.get(1)) {

          for (int i = 8; i < 16; i++) {
            val.set(i, mem_wdata.get(i));
          }

        }
        if (mem_wstrb.get(2)) {
          for (int i = 16; i < 24; i++) {
            val.set(i, mem_wdata.get(i));
          }
        }
        if (mem_wstrb.get(3)) {
          for (int i = 24; i < 32; i++) {
            val.set(i, mem_wdata.get(i));
          }
        }

        memory[mem_addr] = val;
        
      } else {
        state.setValue("self.mem_ready", BitVec(1, 0));
      }
    } else {
      state.setValue("self.mem_ready", BitVec(1, 0));
    }

    auto mem_addr = state.getBitVec("self.mem_addr");
    auto mem_rdata = state.getBitVec("self.mem_rdata");
    auto mem_wdata = state.getBitVec("self.mem_wdata");
    auto mem_wstrb = state.getBitVec("self.mem_wstrb");
    
    if ((state.getBitVec("self.mem_valid") == BitVec(1, 1)) &&
        (state.getBitVec("self.mem_ready") == BitVec(1, 1))) {
      
      if (state.getBitVec("self.mem_instr") == BitVec(1, 1)) {

        printf( "ifetch 0x%08x: 0x%08x\n", mem_addr.to_type<int>(), mem_rdata.to_type<int>());

      } else if (state.getBitVec("self.mem_wstrb") != BitVec(4, 0)) {

        printf( "write  0x%08x: 0x%08x (wstrb=", mem_addr.to_type<int>(), mem_wdata.to_type<int>());
        cout << mem_wstrb << ")\n";

      } else {

        printf( "read   0x%08x: 0x%08x\n", mem_addr.to_type<int>(), mem_rdata.to_type<int>());

      }

    }
  }
    
    
  deleteContext(c);

}

int main() {
  string fileName = "picorv32.json";

  string topMod = "picorv32";

  simulateState("picorv32.json", topMod);
}
