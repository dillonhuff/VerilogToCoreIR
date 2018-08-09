import os

def run_cmd(cmd):
    res = os.system(cmd)
    assert(res == 0)


def yosys_to_coreir(file_name):
    run_cmd("yosys -p \"proc; memory -nomap; pmuxtree; to_coreir\" -ql yosys_to_coreir.log -m ./to_coreir.so {0}".format(file_name))

def coreir_to_verilog(file_name):
    run_cmd("coreir -i {0}.json -o {0}.v --load_libs rtlil".format(file_name))

def run_verilator_tb(top_module_name, verilog_files, cpp_test_file):
    v_command = "verilator -Wno-DECLFILENAME --cc {0} --exe {2} --top-module {1} -CFLAGS -std=c++14 -CFLAGS -march=native".format(verilog_files, top_module_name, cpp_test_file)
    verilate = os.system(v_command);

    if (verilate != 0):
        print 'ERROR: {0} verilation failure'.format(top_module_name),
        assert(False)

    m_command = "make -C obj_dir -j -f V{0}.mk V{0}".format(top_module_name)

    make_cmd = os.system(m_command)

    if (make_cmd != 0):
        print 'ERROR: {0} could not make verilated code'.format(top_module_name)
        assert(False)

    run_cmd = os.system('./obj_dir/V{0}'.format(top_module_name))

    if (run_cmd != 0):
        print 'ERROR: {0} tests failed'.format(top_module_name)
        assert(False)
    
yosys_to_coreir("./test/samples/first_test/test.v")
coreir_to_verilog("./uut")
run_verilator_tb("uut", "uut.v", "./tests/uut_tb.cpp")

yosys_to_coreir("./test/samples/fan_out_2/fan_out_2.v")
coreir_to_verilog("./fan_out_2")
run_verilator_tb("fan_out_2", "fan_out_2.v", "./tests/fan_out_2_tb.cpp")

yosys_to_coreir("./test/samples/register_assign/register_assign.v")
coreir_to_verilog("./register_assign")
run_verilator_tb("register_assign", "register_assign.v", "./tests/register_assign_tb.cpp")

yosys_to_coreir("./test/samples/cb_unq1/cb_unq1.v")
coreir_to_verilog("./cb_unq1")
run_verilator_tb("cb_unq1", "cb_unq1.v", "./tests/cb_unq1_tb.cpp")
