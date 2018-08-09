module register_assign(input clk, input [1:0] a, output [1:0] yout);

   reg [1:0] y;
   

   always @(posedge clk) begin
     y <= a;
   end

   wire [1:0] y_tmp;
   
   assign yout = y;

endmodule
