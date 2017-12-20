module example(input clk, input [1:0] a, output reg [1:0] y);

   always @(posedge clk)
     y <= a;
   

endmodule
