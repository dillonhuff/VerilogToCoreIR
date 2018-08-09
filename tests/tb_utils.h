#pragma once

#include <iostream>

using namespace std;

#define POSEDGE(top, clk) (top).clk = 0; top.eval(); (top).clk = 1; top.eval();
#define NEGEDGE(top, clk) (top).clk = 1; top.eval(); (top).clk = 0; top.eval();

static inline void printPassed(const std::string& name) {
  cout << "#####################################" << endl;
  cout << "##### " << name << " tests passed #####" << endl;
  cout << "#####################################" << endl;
  
}
