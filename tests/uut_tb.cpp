#include "Vuut.h"
#include "verilated.h"

#include "tb_utils.h"

#include <iostream>

using namespace std;

int main() {
  Vuut top;
  top.in1 = 100;
  top.in2 = 3;
  top.in3 = 7;

  top.eval();

  assert(top.out1 == (100 + 3 + 7));
  assert(top.out2 == (100 - 3));

  printPassed("uut");
  // cout << "#####################################" << endl;
  // cout << "##### uut tests passed" << endl;
  // cout << "#####################################" << endl;
}
