#include "Vcb_unq1.h"
#include "verilated.h"

#include "tb_utils.h"

int main() {
  Vcb_unq1 top;

  POSEDGE(top, reset);
  NEGEDGE(top, reset);
  POSEDGE(top, reset);

  assert(top.out == 0);
  // top.a = 3;

  // cout << "top.yout = " << (int) top.yout << endl;

  // POSEDGE(top, clk);

  // cout << "top.yout = " << (int) top.yout << endl;

  // assert(top.yout == 3);

  // top.a = 1;

  // NEGEDGE(top, clk);

  // assert(top.yout == 3);
  
  // POSEDGE(top, clk);

  // assert(top.yout == 1);
  
  printPassed("cb_unq1");
}
