
module  test_opt_reg  #(
  parameter DataWidth = 16
) (
  input                  clk,
  input        [DataWidth-1:0] data_in,
  output logic [DataWidth-1:0] res
);

   reg [DataWidth-1:0]         data_in_reg;

   always_ff @(posedge clk) begin

      data_in_reg <= data_in;
   
   end

   assign res = data_in_reg;

endmodule

module driver(input clk,
              input [15:0] in0,
              output [15:0] res);

   test_opt_reg #(.DataWidth(1))
   test_opt_reg_d(
                  .clk(clk),
                  .data_in(in0),
                  .res(res)
                  );

endmodule
