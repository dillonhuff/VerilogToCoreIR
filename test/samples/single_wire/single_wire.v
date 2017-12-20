module single_wire(in0, in1, out);
   input wire in0;
   input wire in1;
   output wire out;

   assign out = in0 & in1;
   
   
endmodule // single_wire
