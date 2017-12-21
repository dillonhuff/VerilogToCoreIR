
module sb_unq5 (
                clk, reset,
                in0,
                in1,
                out_3_4,
                config_addr,
                config_data,
                config_en
                );

  input  clk;
  input  reset;
  input  config_en;
  input [31:0] config_data;

  // FIXME
  // Bits [31:24] are for switch box, [23:0] for connection box.
  // So bits  [23:0] go unused in this module.  Until this is fixed,
  // we have to let the linter know (verilator directives below) or it complains:
  // %Warning-UNUSED: .../sb_unq1.v:115: Bits of signal are not used: config_addr[23:0]
  /* verilator lint_off UNUSED */
  input [31:0] config_addr;
  /* verilator lint_on UNUSED */

  output [0:0] out_3_4;
   input [0:0] in0;

   input [0:0] in1;
   

  reg [95:0] config_sb;
  
  always @(posedge clk) begin
    if (reset==1'b1) begin

      config_sb <= 96'd0;

    end else begin
       config_sb <= 96'd1;
       
      // if (config_en==1'b1) begin
      //    case (config_addr[31:24])
      //      8'd0: config_sb[31:0] <= config_data;
      //      8'd1: config_sb[63:32] <= config_data;
      //      8'd2: config_sb[95:64] <= config_data;

      //      default: ;

      //    endcase
      // end
    end
  end

  assign out_3_4 = config_sb[79] ? in0 : in1; 

endmodule


