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

   inout pad;
   output p2f;
   input  f2p;
   input  mode;
   
   assign pad = (mode == 1'b1) ? f2p : 1'bz;
   assign p2f = pad;

endmodule
