test: to_coreir.so
	yosys -p "to_coreir" -ql test1.log -m ./to_coreir.so ./test/samples/passthrough/passthrough.v
	yosys -p "to_coreir" -ql test1.log -m ./to_coreir.so ./test/samples/single_wire/single_wire.v
	yosys -p "proc; opt; to_coreir" -ql test1.log -m ./to_coreir.so ./test/samples/register_assign/register_assign.v
	yosys -p "to_coreir" -ql test1.log -m ./to_coreir.so ./test/samples/first_test/test.v
	yosys -p "proc; opt; to_coreir" -ql test1.log -m ./to_coreir.so ./test/samples/fan_out_2/fan_out_2.v
	yosys -p "proc; opt; to_coreir" -ql test1.log -m ./to_coreir.so ./test/samples/add_fan_out/add_fan_out.v
	yosys -p "proc; opt; to_coreir" -ql test1.log -m ./to_coreir.so ./test/samples/constant/constant.v
	yosys -p "proc; opt; to_coreir" -ql test1.log -m ./to_coreir.so ./test/samples/sb_unq_slice/sb_unq_slice.v
	yosys -p "proc; opt; to_coreir" -ql test1.log -m ./to_coreir.so ./test/samples/adder/adder.v
	yosys -p "to_coreir" -ql test1.log -m ./to_coreir.so ./test/samples/genesis_verif/*.v

to_coreir.so: to_coreir.cc
	yosys-config --exec --cxx --cxxflags --ldflags -L/Users/dillon/CppWorkspace/coreir/lib/ -lcoreir  -o $@ -shared $^ --ldlibs

clean:
	rm -f test1.log test2.log test3.log
	rm -f to_coreir.so to_coreir.d
