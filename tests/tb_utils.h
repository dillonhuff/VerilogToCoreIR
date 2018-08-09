#pragma once

#include <iostream>

using namespace std;

static inline void printPassed(const std::string& name) {
  cout << "#####################################" << endl;
  cout << "##### " << name << " tests passed #####" << endl;
  cout << "#####################################" << endl;
  
}
