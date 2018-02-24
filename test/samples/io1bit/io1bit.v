module io1bit_unq1 (
                    pad,
                    p2f,
                    f2p,
                    mode
                    );

   inout pad;
   output p2f;
   input  f2p;
   input  mode;
   
   assign pad = (mode == 1'b1) ? f2p : 1'bz;
   assign p2f = pad;

endmodule
