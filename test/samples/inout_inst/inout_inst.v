module io1bit_unq1 (
                    clk, 
                    pad,
                    p2f,
                    f2p,
                    mode
                    );

   /* verilator lint_off UNUSED */
   input  clk;
   inout pad;
   output p2f;
   input f2p;
   input mode;
   
   assign pad = (mode == 1'b1) ? f2p : 1'bz;

   assign p2f = pad;

endmodule

module user(
            input clk, 
            inout pad,
            output p2f,
            input f2p,
            input mode
            );

   io1bit_unq1 iobit(.clk(clk),
                     .pad(pad),
                     .p2f(p2f),
                     .f2p(f2p),
                     .mode(mode));
   
endmodule
            
