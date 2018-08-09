import os

def run_cmd(cmd):
    res = os.system(cmd)
    assert(res == 0)


def yosys_to_coreir(file_name):
    run_cmd("yosys -p \"to_coreir\" -ql yosys_to_coreir.log -m ./to_coreir.so {0}".format(file_name))

def coreir_to_verilog(file_name):
    run_cmd("coreir -i {0}.json -o {0}.v --load_libs rtlil".format(file_name))

yosys_to_coreir("./test/samples/first_test/test.v")
coreir_to_verilog("./uut")
run_verilator_tb("uut", "uut.v")
