module cb_unq1 (
clk, reset,
in_0,
in_1,
in_2,
in_3,
in_4,
in_5,
in_6,
in_7,
in_8,
in_9,
out,
config_addr,
config_data,
config_en
);

  input  clk;
  input  reset;
  input  config_en;
  input [31:0] config_data;


  /* verilator lint_off UNUSED */
  input [31:0] config_addr;
  /* verilator lint_on UNUSED */

  output reg [15:0] out;
  input [15:0] in_0;
  input [15:0] in_1;
  input [15:0] in_2;
  input [15:0] in_3;
  input [15:0] in_4;
  input [15:0] in_5;
  input [15:0] in_6;
  input [15:0] in_7;
  input [15:0] in_8;
  input [15:0] in_9;



  /* verilator lint_off UNUSED */
  reg [31:0] config_cb;
  /* verilator lint_on UNUSED */
  always @(posedge clk or posedge reset) begin
    if (reset==1'b1) begin
        config_cb <= 4'd13;
    end else begin
      if (config_en==1'b1) begin
         case (config_addr[31:24])
           8'd0: config_cb[31:0] <= config_data;
         endcase
      end
    end
  end

  always @(*) begin
    case (config_cb[3:0])
        4'd0: out = in_0;
        4'd1: out = in_1;
        4'd2: out = in_2;
        4'd3: out = in_3;
        4'd4: out = in_4;
        4'd5: out = in_5;
        4'd6: out = in_6;
        4'd7: out = in_7;
        4'd8: out = in_8;
        4'd9: out = in_9;
        default: out = 16'd0;
    endcase
  end
endmodule
