module AssignR(a, b, clk);

   input a;
   input wire clk;
   
   output reg b;

   reg 	      c;

   //assign b = a;
   always@(posedge clk) begin
      b <= a;
      
   end
   
endmodule // AssignR

module UseR(a, b, clk, c);
   input a;
   input b;
   input clk;

   output c;
   
   

   AssignR asg(
	       .a(a),
	       .b(b),
	       .clk(clk)
	       );
   
endmodule
