module io1bit_unq1 (
clk, 
//reset,
pad,
p2f,
f2p,
                    mode
// config_addr,
// config_data,
// tile_id,
);

  /* verilator lint_off UNUSED */
  input  clk;
//  input  reset;
  inout  pad;
  output p2f;
  input f2p;
   input mode;
   
  // input [31:0] config_data;
  // input [31:0] config_addr;
  // input [15:0] tile_id;
   
  /* verilator lint_on UNUSED */



  // reg config_en_pe;
  // always @(*) begin
  //   if (reset) begin
  //      config_en_pe = 1'b0;
  //   end else begin
  //      if ((config_addr[15:0]==tile_id)&&(config_addr[23:16]==8'd0)) begin
  //        config_en_pe = 1'b1;
  //      end else begin
  //        config_en_pe = 1'b0;
  //      end
  //   end
  // end

  // reg io_bit;
  // always @(posedge clk or posedge reset) begin
  //   if (reset==1'b1) begin
  //      io_bit = 1'b0;
  //   end else begin
  //      if (config_en_pe==1'b1) begin
  //        io_bit = config_data[0];
  //      end
  //   end
  // end

   //assign pad = (io_bit==1'b1)?f2p:1'bz;

   assign pad = (mode == 1'b1) ? f2p : 1'bz;
   assign p2f = pad;
endmodule
