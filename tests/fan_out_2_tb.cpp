#include "Vfan_out_2.h"
#include "verilated.h"

#include "tb_utils.h"

int main() {
  Vfan_out_2 top;
  top.in1 = 0;

  top.eval();

  assert(top.out1 == !top.in1);
  assert(top.out2 == !top.in1);

  printPassed("fan_out_2");
}
