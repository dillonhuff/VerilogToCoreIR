module driverMod(output [3:0] out);

   assign out = 4'd3;
   
endmodule

// module simple_bus_array(input[3:0] in0,
//                         output [3:0] res0,
//                         output [3:0] res1,
//                         output [3:0] res2,
//                         output [3:0] res3);

//    localparam ARRWIDTH = 4;
   
//    // logic [3:0]                       bus [ARRWIDTH - 1:0];


//    // driverMod m0(.out(bus[0]));
//    // driverMod m1(.out(bus[1]));
//    // driverMod m2(.out(bus[2]));
//    // driverMod m3(.out(bus[3]));
   
//    // assign res0 = bus[0];
//    // assign res1 = bus[1];
//    // assign res2 = bus[2];
//    // assign res3 = bus[3];
   
// endmodule
