#include "Vcb_unq1.h"
#include "verilated.h"

#include "tb_utils.h"

int main() {
  Vcb_unq1 top;
  top.config_en = 0;
  
  POSEDGE(top, reset);
  NEGEDGE(top, reset);

  assert(top.out == 0);

  top.config_addr = 0;
  top.config_en = 1;
  top.config_data = 4;

  POSEDGE(top, clk);

  top.config_en = 0;

  top.in_4 = 185;

  POSEDGE(top, clk);

  cout << "top out after programming = " << (int) top.out << endl;
  
  assert(top.out == top.in_4);

  top.config_addr = 0;
  top.config_en = 1;
  top.config_data = 8;

  POSEDGE(top, clk);

  top.config_en = 0;

  top.in_8 = 19;

  POSEDGE(top, clk);

  cout << "top out after programming = " << (int) top.out << endl;
  
  assert(top.out == top.in_8);

  top.in_8 = 7;

  NEGEDGE(top, clk);

  assert(top.out == top.in_8);
  
  printPassed("cb_unq1");
}
