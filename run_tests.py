import os

def run_cmd(cmd):
    res = os.system(cmd)
    assert(res == 0)


def run_yosys_to_coreir(file_name):
    run_cmd("yosys -p \"to_coreir\" -ql yosys_to_coreir.log -m ./to_coreir.so {0}".format(file_name))

run_yosys_to_coreir("./test/samples/first_test/test.v")
	
