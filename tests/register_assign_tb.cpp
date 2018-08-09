#include "Vregister_assign.h"
#include "verilated.h"

#include "tb_utils.h"

int main() {
  Vregister_assign top;
  top.a = 3;

  cout << "top.yout = " << (int) top.yout << endl;

  POSEDGE(top, clk);

  cout << "top.yout = " << (int) top.yout << endl;

  assert(top.yout == 3);

  top.a = 1;

  NEGEDGE(top, clk);

  assert(top.yout == 3);
  
  POSEDGE(top, clk);

  assert(top.yout == 1);
  
  printPassed("register_assign");
}
