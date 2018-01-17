module simple_bus_array(input[3:0] in0,
                        output [3:0] res0,
                        output [3:0] res1,
                        output [3:0] res2,
                        output [3:0] res3);

   localparam ARRWIDTH = 4;
   
   logic [3:0]                       bus [ARRWIDTH - 1:0];


   always @(*) begin   
      bus[0] <= in0;
      
      bus[1] <= in0;
      
      bus[2] <= in0;
      
      bus[3] <= in0;
      
   end

   assign res0 = bus[0];
   assign res1 = bus[1];
   assign res2 = bus[2];
   assign res3 = bus[3];
   
endmodule
