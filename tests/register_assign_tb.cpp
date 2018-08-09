#include "Vregister_assign.h"
#include "verilated.h"

#include "tb_utils.h"

int main() {
  Vregister_assign top;
  top.in1 = 1;

  top.eval();

  assert(top.out1 == !top.in1);
  assert(top.out2 == !top.in1);

  printPassed("register_assign");
}
