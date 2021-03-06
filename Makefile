COREIR_HOME = /Users/dillon/CppWorkspace/coreir

test: to_coreir.so
	python run_tests.py
	yosys -p "hierarchy; proc; memory -nomap; pmuxtree; to_coreir" -m ./to_coreir.so ./test/samples/io1bit/io1bit.v
	yosys -p "proc; memory; pmuxtree; to_coreir" -m ./to_coreir.so ./test/samples/inout_inst/inout_inst.v
	yosys -p "proc; memory; pmuxtree; to_coreir" -m ./to_coreir.so ./test/samples/cb_unq1/cb_unq1.v
	yosys -p "proc; memory; pmuxtree; to_coreir" -m ./to_coreir.so ./test/samples/picorv/picorv32.v
	yosys -p "proc; memory -nomap; to_coreir" -ql test1.log -m ./to_coreir.so ./test/samples/sram/sram_512w_16b.v
	yosys -p "proc; memory -nomap; to_coreir" -ql test1.log -m ./to_coreir.so ./test/samples/simple_bus_array/simple_bus_array.sv
	yosys -p "proc; memory -nomap; to_coreir" -ql test1.log -m ./to_coreir.so ./test/samples/bus_array/bus_array.sv
	yosys -p "to_coreir" -ql test1.log -m ./to_coreir.so ./test/samples/generated/generated.v
	yosys -p "to_coreir" -ql test1.log -m ./to_coreir.so ./test/samples/passthrough/passthrough.v
	yosys -p "to_coreir" -ql test1.log -m ./to_coreir.so ./test/samples/single_wire/single_wire.v
	yosys -p "proc; opt; to_coreir" -ql test1.log -m ./to_coreir.so ./test/samples/add_fan_out/add_fan_out.v
	yosys -p "proc; opt; to_coreir" -ql test1.log -m ./to_coreir.so ./test/samples/constant/constant.v
	yosys -p "proc; opt; to_coreir" -ql test1.log -m ./to_coreir.so ./test/samples/sb_unq_slice/sb_unq_slice.v
	yosys -p "proc; opt; to_coreir" -ql test1.log -m ./to_coreir.so ./test/samples/adder/adder.v

	yosys -p "proc; opt; to_coreir" -ql test1.log -m ./to_coreir.so ./test/samples/rc_adder/rc_adder.v

	yosys -p "proc; opt; to_coreir" -m ./to_coreir.so ./test/samples/test_mult_add/test_mult_add.sv

	yosys -p "proc; pmuxtree; to_coreir" -ql test1.log -m ./to_coreir.so ./test/samples/genesis_verif/*.v

to_coreir.so: to_coreir.cc
	yosys-config --exec --cxx --cxxflags --ldflags -L$(COREIR_HOME)/lib/ -lcoreir -lcoreir-rtlil  -o $@ -shared $^ --ldlibs

clean:
	rm -f test1.log test2.log test3.log
	rm -f to_coreir.so to_coreir.d
