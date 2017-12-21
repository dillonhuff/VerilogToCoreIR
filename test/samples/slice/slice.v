module slice(input [1:0] conf,
             input  a,
             input b,
             output res);


   reg [1:0]        conf_reg;

   assign res = conf_reg[1] ? a : b;


endmodule // slice
