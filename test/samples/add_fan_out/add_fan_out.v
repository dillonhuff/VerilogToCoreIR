module add_fan_out(input [1:0] in0,
                   input [1:0]  in1,
                   output [1:0] out0,
                   output [1:0] out1,
                   input        clk);

   reg [1:0]                    res0;
   reg [1:0]                    res1;

   always @(posedge clk)
     begin
        res0 <= in0 + in1;
        res1 <= in0 - in1;
     end

   assign out0 = res0;
   assign out1 = res1;
   
endmodule // add_fan_out

