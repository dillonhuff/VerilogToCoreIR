module generated #(
                   parameter DataWidth = 16
) (input [DataWidth - 1 : 0] loadVal,
   output [DataWidth - 1 : 0] resVal,
   input                      clk);

   reg [DataWidth - 1 : 0]    tmp;

   always @(posedge clk) begin
      tmp <= loadVal;
   end

   assign resVal = tmp + 1;

endmodule // generated

module user(input [6:0] val,
            output [6:0] resVal,
            input        clk);

   generated #(.DataWidth(7)) genVal(
                                     .loadVal(val),
                                     .resVal(resVal),
                                     .clk(clk)
                                     );
   
endmodule // user

   
