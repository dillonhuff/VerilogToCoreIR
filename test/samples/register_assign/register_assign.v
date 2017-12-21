module register_assign(input clk, input [1:0] a, output [1:0] yout);

   reg [1:0] y;
   

   always @(posedge clk)
     y <= a;

   assign yout = y;
   

endmodule
