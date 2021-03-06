//
//--------------------------------------------------------------------------------
//          THIS FILE WAS AUTOMATICALLY GENERATED BY THE GENESIS2 ENGINE        
//  FOR MORE INFORMATION: OFER SHACHAM (CHIP GENESIS INC / STANFORD VLSI GROUP)
//    !! THIS VERSION OF GENESIS2 IS NOT FOR ANY COMMERCIAL USE !!
//     FOR COMMERCIAL LICENSE CONTACT SHACHAM@ALUMNI.STANFORD.EDU
//--------------------------------------------------------------------------------
//
//  
//	-----------------------------------------------
//	|            Genesis Release Info             |
//	|  $Change: 11904 $ --- $Date: 2013/08/03 $   |
//	-----------------------------------------------
//	
//
//  Source file: /Users/dillon/VerilogWorkspace/CGRAGenerator/hardware/generator_z/memory_tile/memory_tile.vp
//  Source template: memory_tile
//
// --------------- Begin Pre-Generation Parameters Status Report ---------------
//
//	From 'generate' statement (priority=5):
// Parameter registered_outputs 	= BUS16:00000 BUS1:00000
// Parameter feedthrough_outputs 	= BUS16:00000 BUS1:00000
// Parameter gen_mem_for_busname 	= BUS16
// Parameter ddepth 	= 1024
// Parameter sb_fs 	= 10000#10000#10000
// Parameter cb_connections 	= 1111111111
// Parameter control_busname 	= BUS1
// Parameter bus_config 	= BUS16:16b#1_4:1_4:1_4:1_4:1_4 BUS1:1b#1_4:1_4:1_4:1_4:1_4
//
//		---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
//
//	From Command Line input (priority=4):
//
//		---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
//
//	From XML input (priority=3):
//
//		---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
//
//	From Config File input (priority=2):
//
// ---------------- End Pre-Generation Pramameters Status Report ----------------

///////////////////////////////////////////////////////////////////
// CGRA memory tile generator with SBs CBs
//
//////////////////////////////////////////////////////////////////

// bus_config (_GENESIS2_INHERITANCE_PRIORITY_) = BUS16:16b#1_4:1_4:1_4:1_4:1_4 BUS1:1b#1_4:1_4:1_4:1_4:1_4
//

// all_segments_for_all_tiles (_GENESIS2_DECLARATION_PRIORITY_) = 1
//

// gen_mem_for_busname (_GENESIS2_INHERITANCE_PRIORITY_) = BUS16
//
// control_busname (_GENESIS2_INHERITANCE_PRIORITY_) = BUS1
//
// ddepth (_GENESIS2_INHERITANCE_PRIORITY_) = 0x400
//

// sides (_GENESIS2_DECLARATION_PRIORITY_) = 4
//
// feedthrough_outputs (_GENESIS2_INHERITANCE_PRIORITY_) = BUS16:00000 BUS1:00000
//
// registered_outputs (_GENESIS2_INHERITANCE_PRIORITY_) = BUS16:00000 BUS1:00000
//
// is_bidi (_GENESIS2_DECLARATION_PRIORITY_) = 0
//
// sb_fs (_GENESIS2_INHERITANCE_PRIORITY_) = 10000#10000#10000
//

// cb_connections (_GENESIS2_INHERITANCE_PRIORITY_) = 0x423a35c7
//

// mem_tile_height (_GENESIS2_DECLARATION_PRIORITY_) = 2
//



module memory_tile_unq1(
clk,
config_addr,
config_data,
out_0_BUS1_0_0,
in_0_BUS1_0_0,
out_0_BUS1_0_1,
in_0_BUS1_0_1,
out_0_BUS1_0_2,
in_0_BUS1_0_2,
out_0_BUS1_0_3,
in_0_BUS1_0_3,
out_0_BUS1_0_4,
in_0_BUS1_0_4,
out_0_BUS1_2_0,
in_0_BUS1_2_0,
out_0_BUS1_2_1,
in_0_BUS1_2_1,
out_0_BUS1_2_2,
in_0_BUS1_2_2,
out_0_BUS1_2_3,
in_0_BUS1_2_3,
out_0_BUS1_2_4,
in_0_BUS1_2_4,
out_0_BUS1_3_0,
in_0_BUS1_3_0,
out_0_BUS1_3_1,
in_0_BUS1_3_1,
out_0_BUS1_3_2,
in_0_BUS1_3_2,
out_0_BUS1_3_3,
in_0_BUS1_3_3,
out_0_BUS1_3_4,
in_0_BUS1_3_4,
out_0_BUS16_0_0,
in_0_BUS16_0_0,
out_0_BUS16_0_1,
in_0_BUS16_0_1,
out_0_BUS16_0_2,
in_0_BUS16_0_2,
out_0_BUS16_0_3,
in_0_BUS16_0_3,
out_0_BUS16_0_4,
in_0_BUS16_0_4,
out_0_BUS16_2_0,
in_0_BUS16_2_0,
out_0_BUS16_2_1,
in_0_BUS16_2_1,
out_0_BUS16_2_2,
in_0_BUS16_2_2,
out_0_BUS16_2_3,
in_0_BUS16_2_3,
out_0_BUS16_2_4,
in_0_BUS16_2_4,
out_0_BUS16_3_0,
in_0_BUS16_3_0,
out_0_BUS16_3_1,
in_0_BUS16_3_1,
out_0_BUS16_3_2,
in_0_BUS16_3_2,
out_0_BUS16_3_3,
in_0_BUS16_3_3,
out_0_BUS16_3_4,
in_0_BUS16_3_4,
out_1_BUS1_0_0,
in_1_BUS1_0_0,
out_1_BUS1_0_1,
in_1_BUS1_0_1,
out_1_BUS1_0_2,
in_1_BUS1_0_2,
out_1_BUS1_0_3,
in_1_BUS1_0_3,
out_1_BUS1_0_4,
in_1_BUS1_0_4,
out_1_BUS1_1_0,
in_1_BUS1_1_0,
out_1_BUS1_1_1,
in_1_BUS1_1_1,
out_1_BUS1_1_2,
in_1_BUS1_1_2,
out_1_BUS1_1_3,
in_1_BUS1_1_3,
out_1_BUS1_1_4,
in_1_BUS1_1_4,
out_1_BUS1_2_0,
in_1_BUS1_2_0,
out_1_BUS1_2_1,
in_1_BUS1_2_1,
out_1_BUS1_2_2,
in_1_BUS1_2_2,
out_1_BUS1_2_3,
in_1_BUS1_2_3,
out_1_BUS1_2_4,
in_1_BUS1_2_4,
out_1_BUS16_0_0,
in_1_BUS16_0_0,
out_1_BUS16_0_1,
in_1_BUS16_0_1,
out_1_BUS16_0_2,
in_1_BUS16_0_2,
out_1_BUS16_0_3,
in_1_BUS16_0_3,
out_1_BUS16_0_4,
in_1_BUS16_0_4,
out_1_BUS16_1_0,
in_1_BUS16_1_0,
out_1_BUS16_1_1,
in_1_BUS16_1_1,
out_1_BUS16_1_2,
in_1_BUS16_1_2,
out_1_BUS16_1_3,
in_1_BUS16_1_3,
out_1_BUS16_1_4,
in_1_BUS16_1_4,
out_1_BUS16_2_0,
in_1_BUS16_2_0,
out_1_BUS16_2_1,
in_1_BUS16_2_1,
out_1_BUS16_2_2,
in_1_BUS16_2_2,
out_1_BUS16_2_3,
in_1_BUS16_2_3,
out_1_BUS16_2_4,
in_1_BUS16_2_4,
chain_in,
chain_out,
chain_valid_out,
chain_wen_in,
reset,
tile_id
);

  input clk;
  input [31:0] config_addr;
  input [31:0] config_data;
  input chain_wen_in;
  output chain_valid_out;
  output [0:0] out_0_BUS1_0_0;
  input [0:0] in_0_BUS1_0_0;
  output [0:0] out_0_BUS1_0_1;
  input [0:0] in_0_BUS1_0_1;
  output [0:0] out_0_BUS1_0_2;
  input [0:0] in_0_BUS1_0_2;
  output [0:0] out_0_BUS1_0_3;
  input [0:0] in_0_BUS1_0_3;
  output [0:0] out_0_BUS1_0_4;
  input [0:0] in_0_BUS1_0_4;
  output [0:0] out_0_BUS1_2_0;
  input [0:0] in_0_BUS1_2_0;
  output [0:0] out_0_BUS1_2_1;
  input [0:0] in_0_BUS1_2_1;
  output [0:0] out_0_BUS1_2_2;
  input [0:0] in_0_BUS1_2_2;
  output [0:0] out_0_BUS1_2_3;
  input [0:0] in_0_BUS1_2_3;
  output [0:0] out_0_BUS1_2_4;
  input [0:0] in_0_BUS1_2_4;
  output [0:0] out_0_BUS1_3_0;
  input [0:0] in_0_BUS1_3_0;
  output [0:0] out_0_BUS1_3_1;
  input [0:0] in_0_BUS1_3_1;
  output [0:0] out_0_BUS1_3_2;
  input [0:0] in_0_BUS1_3_2;
  output [0:0] out_0_BUS1_3_3;
  input [0:0] in_0_BUS1_3_3;
  output [0:0] out_0_BUS1_3_4;
  input [0:0] in_0_BUS1_3_4;
  output [15:0] out_0_BUS16_0_0;
  input [15:0] in_0_BUS16_0_0;
  output [15:0] out_0_BUS16_0_1;
  input [15:0] in_0_BUS16_0_1;
  output [15:0] out_0_BUS16_0_2;
  input [15:0] in_0_BUS16_0_2;
  output [15:0] out_0_BUS16_0_3;
  input [15:0] in_0_BUS16_0_3;
  output [15:0] out_0_BUS16_0_4;
  input [15:0] in_0_BUS16_0_4;
  output [15:0] out_0_BUS16_2_0;
  input [15:0] in_0_BUS16_2_0;
  output [15:0] out_0_BUS16_2_1;
  input [15:0] in_0_BUS16_2_1;
  output [15:0] out_0_BUS16_2_2;
  input [15:0] in_0_BUS16_2_2;
  output [15:0] out_0_BUS16_2_3;
  input [15:0] in_0_BUS16_2_3;
  output [15:0] out_0_BUS16_2_4;
  input [15:0] in_0_BUS16_2_4;
  output [15:0] out_0_BUS16_3_0;
  input [15:0] in_0_BUS16_3_0;
  output [15:0] out_0_BUS16_3_1;
  input [15:0] in_0_BUS16_3_1;
  output [15:0] out_0_BUS16_3_2;
  input [15:0] in_0_BUS16_3_2;
  output [15:0] out_0_BUS16_3_3;
  input [15:0] in_0_BUS16_3_3;
  output [15:0] out_0_BUS16_3_4;
  input [15:0] in_0_BUS16_3_4;
  output [0:0] out_1_BUS1_0_0;
  input [0:0] in_1_BUS1_0_0;
  output [0:0] out_1_BUS1_0_1;
  input [0:0] in_1_BUS1_0_1;
  output [0:0] out_1_BUS1_0_2;
  input [0:0] in_1_BUS1_0_2;
  output [0:0] out_1_BUS1_0_3;
  input [0:0] in_1_BUS1_0_3;
  output [0:0] out_1_BUS1_0_4;
  input [0:0] in_1_BUS1_0_4;
  output [0:0] out_1_BUS1_1_0;
  input [0:0] in_1_BUS1_1_0;
  output [0:0] out_1_BUS1_1_1;
  input [0:0] in_1_BUS1_1_1;
  output [0:0] out_1_BUS1_1_2;
  input [0:0] in_1_BUS1_1_2;
  output [0:0] out_1_BUS1_1_3;
  input [0:0] in_1_BUS1_1_3;
  output [0:0] out_1_BUS1_1_4;
  input [0:0] in_1_BUS1_1_4;
  output [0:0] out_1_BUS1_2_0;
  input [0:0] in_1_BUS1_2_0;
  output [0:0] out_1_BUS1_2_1;
  input [0:0] in_1_BUS1_2_1;
  output [0:0] out_1_BUS1_2_2;
  input [0:0] in_1_BUS1_2_2;
  output [0:0] out_1_BUS1_2_3;
  input [0:0] in_1_BUS1_2_3;
  output [0:0] out_1_BUS1_2_4;
  input [0:0] in_1_BUS1_2_4;
  output [15:0] out_1_BUS16_0_0;
  input [15:0] in_1_BUS16_0_0;
  output [15:0] out_1_BUS16_0_1;
  input [15:0] in_1_BUS16_0_1;
  output [15:0] out_1_BUS16_0_2;
  input [15:0] in_1_BUS16_0_2;
  output [15:0] out_1_BUS16_0_3;
  input [15:0] in_1_BUS16_0_3;
  output [15:0] out_1_BUS16_0_4;
  input [15:0] in_1_BUS16_0_4;
  output [15:0] out_1_BUS16_1_0;
  input [15:0] in_1_BUS16_1_0;
  output [15:0] out_1_BUS16_1_1;
  input [15:0] in_1_BUS16_1_1;
  output [15:0] out_1_BUS16_1_2;
  input [15:0] in_1_BUS16_1_2;
  output [15:0] out_1_BUS16_1_3;
  input [15:0] in_1_BUS16_1_3;
  output [15:0] out_1_BUS16_1_4;
  input [15:0] in_1_BUS16_1_4;
  output [15:0] out_1_BUS16_2_0;
  input [15:0] in_1_BUS16_2_0;
  output [15:0] out_1_BUS16_2_1;
  input [15:0] in_1_BUS16_2_1;
  output [15:0] out_1_BUS16_2_2;
  input [15:0] in_1_BUS16_2_2;
  output [15:0] out_1_BUS16_2_3;
  input [15:0] in_1_BUS16_2_3;
  output [15:0] out_1_BUS16_2_4;
  input [15:0] in_1_BUS16_2_4;

  input [15:0] chain_in;
  output [15:0] chain_out;
  input [15:0] tile_id;
  input reset;



  reg config_en_sb_0_BUS1;
  always @(*) begin
    if (reset) begin
       config_en_sb_0_BUS1 <= 1'b0;
    end else begin
       if ((config_addr[15:0]==tile_id)&&(config_addr[23:16]==8'd0)) begin
         config_en_sb_0_BUS1 <= 1'b1;
       end else begin
         config_en_sb_0_BUS1 <= 1'b0;
       end
    end
  end
  reg config_en_sb_1_BUS1;
  always @(*) begin
    if (reset) begin
       config_en_sb_1_BUS1 <= 1'b0;
    end else begin
       if ((config_addr[15:0]==tile_id)&&(config_addr[23:16]==8'd1)) begin
         config_en_sb_1_BUS1 <= 1'b1;
       end else begin
         config_en_sb_1_BUS1 <= 1'b0;
       end
    end
  end
  reg config_en_sb_0_BUS16;
  always @(*) begin
    if (reset) begin
       config_en_sb_0_BUS16 <= 1'b0;
    end else begin
       if ((config_addr[15:0]==tile_id)&&(config_addr[23:16]==8'd2)) begin
         config_en_sb_0_BUS16 <= 1'b1;
       end else begin
         config_en_sb_0_BUS16 <= 1'b0;
       end
    end
  end
  reg config_en_sb_1_BUS16;
  always @(*) begin
    if (reset) begin
       config_en_sb_1_BUS16 <= 1'b0;
    end else begin
       if ((config_addr[15:0]==tile_id)&&(config_addr[23:16]==8'd3)) begin
         config_en_sb_1_BUS16 <= 1'b1;
       end else begin
         config_en_sb_1_BUS16 <= 1'b0;
       end
    end
  end

  reg config_en_mem;
  always @(*) begin
    if (reset) begin
       config_en_mem <= 1'b0;
    end else begin
       if ((config_addr[15:0]==tile_id)&&(config_addr[23:16]==8'd4)) begin
         config_en_mem <= 1'b1;
       end else begin
         config_en_mem <= 1'b0;
       end
    end
  end

  wire [15:0] rdata;
  wire valid;
  wire almost_full;

   wire [0:0] sb_wire_out_0_BUS1_0_0;
   wire [0:0] sb_wire_in_0_BUS1_0_0;
   wire [0:0] sb_wire_out_0_BUS1_0_1;
   wire [0:0] sb_wire_in_0_BUS1_0_1;
   wire [0:0] sb_wire_out_0_BUS1_0_2;
   wire [0:0] sb_wire_in_0_BUS1_0_2;
   wire [0:0] sb_wire_out_0_BUS1_0_3;
   wire [0:0] sb_wire_in_0_BUS1_0_3;
   wire [0:0] sb_wire_out_0_BUS1_0_4;
   wire [0:0] sb_wire_in_0_BUS1_0_4;
   wire [0:0] sb_wire_out_0_BUS1_1_0;
   wire [0:0] sb_wire_in_0_BUS1_1_0;
   wire [0:0] sb_wire_out_0_BUS1_1_1;
   wire [0:0] sb_wire_in_0_BUS1_1_1;
   wire [0:0] sb_wire_out_0_BUS1_1_2;
   wire [0:0] sb_wire_in_0_BUS1_1_2;
   wire [0:0] sb_wire_out_0_BUS1_1_3;
   wire [0:0] sb_wire_in_0_BUS1_1_3;
   wire [0:0] sb_wire_out_0_BUS1_1_4;
   wire [0:0] sb_wire_in_0_BUS1_1_4;
   wire [0:0] sb_wire_out_0_BUS1_2_0;
   wire [0:0] sb_wire_in_0_BUS1_2_0;
   wire [0:0] sb_wire_out_0_BUS1_2_1;
   wire [0:0] sb_wire_in_0_BUS1_2_1;
   wire [0:0] sb_wire_out_0_BUS1_2_2;
   wire [0:0] sb_wire_in_0_BUS1_2_2;
   wire [0:0] sb_wire_out_0_BUS1_2_3;
   wire [0:0] sb_wire_in_0_BUS1_2_3;
   wire [0:0] sb_wire_out_0_BUS1_2_4;
   wire [0:0] sb_wire_in_0_BUS1_2_4;
   wire [0:0] sb_wire_out_0_BUS1_3_0;
   wire [0:0] sb_wire_in_0_BUS1_3_0;
   wire [0:0] sb_wire_out_0_BUS1_3_1;
   wire [0:0] sb_wire_in_0_BUS1_3_1;
   wire [0:0] sb_wire_out_0_BUS1_3_2;
   wire [0:0] sb_wire_in_0_BUS1_3_2;
   wire [0:0] sb_wire_out_0_BUS1_3_3;
   wire [0:0] sb_wire_in_0_BUS1_3_3;
   wire [0:0] sb_wire_out_0_BUS1_3_4;
   wire [0:0] sb_wire_in_0_BUS1_3_4;
   wire [0:0] sb_wire_out_1_BUS1_0_0;
   wire [0:0] sb_wire_in_1_BUS1_0_0;
   wire [0:0] sb_wire_out_1_BUS1_0_1;
   wire [0:0] sb_wire_in_1_BUS1_0_1;
   wire [0:0] sb_wire_out_1_BUS1_0_2;
   wire [0:0] sb_wire_in_1_BUS1_0_2;
   wire [0:0] sb_wire_out_1_BUS1_0_3;
   wire [0:0] sb_wire_in_1_BUS1_0_3;
   wire [0:0] sb_wire_out_1_BUS1_0_4;
   wire [0:0] sb_wire_in_1_BUS1_0_4;
   wire [0:0] sb_wire_out_1_BUS1_1_0;
   wire [0:0] sb_wire_in_1_BUS1_1_0;
   wire [0:0] sb_wire_out_1_BUS1_1_1;
   wire [0:0] sb_wire_in_1_BUS1_1_1;
   wire [0:0] sb_wire_out_1_BUS1_1_2;
   wire [0:0] sb_wire_in_1_BUS1_1_2;
   wire [0:0] sb_wire_out_1_BUS1_1_3;
   wire [0:0] sb_wire_in_1_BUS1_1_3;
   wire [0:0] sb_wire_out_1_BUS1_1_4;
   wire [0:0] sb_wire_in_1_BUS1_1_4;
   wire [0:0] sb_wire_out_1_BUS1_2_0;
   wire [0:0] sb_wire_in_1_BUS1_2_0;
   wire [0:0] sb_wire_out_1_BUS1_2_1;
   wire [0:0] sb_wire_in_1_BUS1_2_1;
   wire [0:0] sb_wire_out_1_BUS1_2_2;
   wire [0:0] sb_wire_in_1_BUS1_2_2;
   wire [0:0] sb_wire_out_1_BUS1_2_3;
   wire [0:0] sb_wire_in_1_BUS1_2_3;
   wire [0:0] sb_wire_out_1_BUS1_2_4;
   wire [0:0] sb_wire_in_1_BUS1_2_4;
   wire [0:0] sb_wire_out_1_BUS1_3_0;
   wire [0:0] sb_wire_in_1_BUS1_3_0;
   wire [0:0] sb_wire_out_1_BUS1_3_1;
   wire [0:0] sb_wire_in_1_BUS1_3_1;
   wire [0:0] sb_wire_out_1_BUS1_3_2;
   wire [0:0] sb_wire_in_1_BUS1_3_2;
   wire [0:0] sb_wire_out_1_BUS1_3_3;
   wire [0:0] sb_wire_in_1_BUS1_3_3;
   wire [0:0] sb_wire_out_1_BUS1_3_4;
   wire [0:0] sb_wire_in_1_BUS1_3_4;
   wire [15:0] sb_wire_out_0_BUS16_0_0;
   wire [15:0] sb_wire_in_0_BUS16_0_0;
   wire [15:0] sb_wire_out_0_BUS16_0_1;
   wire [15:0] sb_wire_in_0_BUS16_0_1;
   wire [15:0] sb_wire_out_0_BUS16_0_2;
   wire [15:0] sb_wire_in_0_BUS16_0_2;
   wire [15:0] sb_wire_out_0_BUS16_0_3;
   wire [15:0] sb_wire_in_0_BUS16_0_3;
   wire [15:0] sb_wire_out_0_BUS16_0_4;
   wire [15:0] sb_wire_in_0_BUS16_0_4;
   wire [15:0] sb_wire_out_0_BUS16_1_0;
   wire [15:0] sb_wire_in_0_BUS16_1_0;
   wire [15:0] sb_wire_out_0_BUS16_1_1;
   wire [15:0] sb_wire_in_0_BUS16_1_1;
   wire [15:0] sb_wire_out_0_BUS16_1_2;
   wire [15:0] sb_wire_in_0_BUS16_1_2;
   wire [15:0] sb_wire_out_0_BUS16_1_3;
   wire [15:0] sb_wire_in_0_BUS16_1_3;
   wire [15:0] sb_wire_out_0_BUS16_1_4;
   wire [15:0] sb_wire_in_0_BUS16_1_4;
   wire [15:0] sb_wire_out_0_BUS16_2_0;
   wire [15:0] sb_wire_in_0_BUS16_2_0;
   wire [15:0] sb_wire_out_0_BUS16_2_1;
   wire [15:0] sb_wire_in_0_BUS16_2_1;
   wire [15:0] sb_wire_out_0_BUS16_2_2;
   wire [15:0] sb_wire_in_0_BUS16_2_2;
   wire [15:0] sb_wire_out_0_BUS16_2_3;
   wire [15:0] sb_wire_in_0_BUS16_2_3;
   wire [15:0] sb_wire_out_0_BUS16_2_4;
   wire [15:0] sb_wire_in_0_BUS16_2_4;
   wire [15:0] sb_wire_out_0_BUS16_3_0;
   wire [15:0] sb_wire_in_0_BUS16_3_0;
   wire [15:0] sb_wire_out_0_BUS16_3_1;
   wire [15:0] sb_wire_in_0_BUS16_3_1;
   wire [15:0] sb_wire_out_0_BUS16_3_2;
   wire [15:0] sb_wire_in_0_BUS16_3_2;
   wire [15:0] sb_wire_out_0_BUS16_3_3;
   wire [15:0] sb_wire_in_0_BUS16_3_3;
   wire [15:0] sb_wire_out_0_BUS16_3_4;
   wire [15:0] sb_wire_in_0_BUS16_3_4;
   wire [15:0] sb_wire_out_1_BUS16_0_0;
   wire [15:0] sb_wire_in_1_BUS16_0_0;
   wire [15:0] sb_wire_out_1_BUS16_0_1;
   wire [15:0] sb_wire_in_1_BUS16_0_1;
   wire [15:0] sb_wire_out_1_BUS16_0_2;
   wire [15:0] sb_wire_in_1_BUS16_0_2;
   wire [15:0] sb_wire_out_1_BUS16_0_3;
   wire [15:0] sb_wire_in_1_BUS16_0_3;
   wire [15:0] sb_wire_out_1_BUS16_0_4;
   wire [15:0] sb_wire_in_1_BUS16_0_4;
   wire [15:0] sb_wire_out_1_BUS16_1_0;
   wire [15:0] sb_wire_in_1_BUS16_1_0;
   wire [15:0] sb_wire_out_1_BUS16_1_1;
   wire [15:0] sb_wire_in_1_BUS16_1_1;
   wire [15:0] sb_wire_out_1_BUS16_1_2;
   wire [15:0] sb_wire_in_1_BUS16_1_2;
   wire [15:0] sb_wire_out_1_BUS16_1_3;
   wire [15:0] sb_wire_in_1_BUS16_1_3;
   wire [15:0] sb_wire_out_1_BUS16_1_4;
   wire [15:0] sb_wire_in_1_BUS16_1_4;
   wire [15:0] sb_wire_out_1_BUS16_2_0;
   wire [15:0] sb_wire_in_1_BUS16_2_0;
   wire [15:0] sb_wire_out_1_BUS16_2_1;
   wire [15:0] sb_wire_in_1_BUS16_2_1;
   wire [15:0] sb_wire_out_1_BUS16_2_2;
   wire [15:0] sb_wire_in_1_BUS16_2_2;
   wire [15:0] sb_wire_out_1_BUS16_2_3;
   wire [15:0] sb_wire_in_1_BUS16_2_3;
   wire [15:0] sb_wire_out_1_BUS16_2_4;
   wire [15:0] sb_wire_in_1_BUS16_2_4;
   wire [15:0] sb_wire_out_1_BUS16_3_0;
   wire [15:0] sb_wire_in_1_BUS16_3_0;
   wire [15:0] sb_wire_out_1_BUS16_3_1;
   wire [15:0] sb_wire_in_1_BUS16_3_1;
   wire [15:0] sb_wire_out_1_BUS16_3_2;
   wire [15:0] sb_wire_in_1_BUS16_3_2;
   wire [15:0] sb_wire_out_1_BUS16_3_3;
   wire [15:0] sb_wire_in_1_BUS16_3_3;
   wire [15:0] sb_wire_out_1_BUS16_3_4;
   wire [15:0] sb_wire_in_1_BUS16_3_4;

  sb_unq5  sb_inst_busBUS1_row0
  (
    .clk(clk),
    .reset(reset),
    .pe_output_0(valid),
    .pe_output_1(almost_full),
    .out_0_0(sb_wire_out_0_BUS1_0_0),
    .in_0_0(sb_wire_in_0_BUS1_0_0),      
    .out_0_1(sb_wire_out_0_BUS1_0_1),
    .in_0_1(sb_wire_in_0_BUS1_0_1),      
    .out_0_2(sb_wire_out_0_BUS1_0_2),
    .in_0_2(sb_wire_in_0_BUS1_0_2),      
    .out_0_3(sb_wire_out_0_BUS1_0_3),
    .in_0_3(sb_wire_in_0_BUS1_0_3),      
    .out_0_4(sb_wire_out_0_BUS1_0_4),
    .in_0_4(sb_wire_in_0_BUS1_0_4),      
    .out_1_0(sb_wire_out_0_BUS1_1_0),
    .in_1_0(sb_wire_in_0_BUS1_1_0),      
    .out_1_1(sb_wire_out_0_BUS1_1_1),
    .in_1_1(sb_wire_in_0_BUS1_1_1),      
    .out_1_2(sb_wire_out_0_BUS1_1_2),
    .in_1_2(sb_wire_in_0_BUS1_1_2),      
    .out_1_3(sb_wire_out_0_BUS1_1_3),
    .in_1_3(sb_wire_in_0_BUS1_1_3),      
    .out_1_4(sb_wire_out_0_BUS1_1_4),
    .in_1_4(sb_wire_in_0_BUS1_1_4),      
    .out_2_0(sb_wire_out_0_BUS1_2_0),
    .in_2_0(sb_wire_in_0_BUS1_2_0),      
    .out_2_1(sb_wire_out_0_BUS1_2_1),
    .in_2_1(sb_wire_in_0_BUS1_2_1),      
    .out_2_2(sb_wire_out_0_BUS1_2_2),
    .in_2_2(sb_wire_in_0_BUS1_2_2),      
    .out_2_3(sb_wire_out_0_BUS1_2_3),
    .in_2_3(sb_wire_in_0_BUS1_2_3),      
    .out_2_4(sb_wire_out_0_BUS1_2_4),
    .in_2_4(sb_wire_in_0_BUS1_2_4),      
    .out_3_0(sb_wire_out_0_BUS1_3_0),
    .in_3_0(sb_wire_in_0_BUS1_3_0),      
    .out_3_1(sb_wire_out_0_BUS1_3_1),
    .in_3_1(sb_wire_in_0_BUS1_3_1),      
    .out_3_2(sb_wire_out_0_BUS1_3_2),
    .in_3_2(sb_wire_in_0_BUS1_3_2),      
    .out_3_3(sb_wire_out_0_BUS1_3_3),
    .in_3_3(sb_wire_in_0_BUS1_3_3),      
    .out_3_4(sb_wire_out_0_BUS1_3_4),
    .in_3_4(sb_wire_in_0_BUS1_3_4),      
    .config_addr(config_addr),
    .config_data(config_data),
    .config_en(config_en_sb_0_BUS1)
  );
  sb_unq1  sb_inst_busBUS16_row0
  (
    .clk(clk),
    .reset(reset),
    .pe_output_0(rdata),
    .out_0_0(sb_wire_out_0_BUS16_0_0),
    .in_0_0(sb_wire_in_0_BUS16_0_0),      
    .out_0_1(sb_wire_out_0_BUS16_0_1),
    .in_0_1(sb_wire_in_0_BUS16_0_1),      
    .out_0_2(sb_wire_out_0_BUS16_0_2),
    .in_0_2(sb_wire_in_0_BUS16_0_2),      
    .out_0_3(sb_wire_out_0_BUS16_0_3),
    .in_0_3(sb_wire_in_0_BUS16_0_3),      
    .out_0_4(sb_wire_out_0_BUS16_0_4),
    .in_0_4(sb_wire_in_0_BUS16_0_4),      
    .out_1_0(sb_wire_out_0_BUS16_1_0),
    .in_1_0(sb_wire_in_0_BUS16_1_0),      
    .out_1_1(sb_wire_out_0_BUS16_1_1),
    .in_1_1(sb_wire_in_0_BUS16_1_1),      
    .out_1_2(sb_wire_out_0_BUS16_1_2),
    .in_1_2(sb_wire_in_0_BUS16_1_2),      
    .out_1_3(sb_wire_out_0_BUS16_1_3),
    .in_1_3(sb_wire_in_0_BUS16_1_3),      
    .out_1_4(sb_wire_out_0_BUS16_1_4),
    .in_1_4(sb_wire_in_0_BUS16_1_4),      
    .out_2_0(sb_wire_out_0_BUS16_2_0),
    .in_2_0(sb_wire_in_0_BUS16_2_0),      
    .out_2_1(sb_wire_out_0_BUS16_2_1),
    .in_2_1(sb_wire_in_0_BUS16_2_1),      
    .out_2_2(sb_wire_out_0_BUS16_2_2),
    .in_2_2(sb_wire_in_0_BUS16_2_2),      
    .out_2_3(sb_wire_out_0_BUS16_2_3),
    .in_2_3(sb_wire_in_0_BUS16_2_3),      
    .out_2_4(sb_wire_out_0_BUS16_2_4),
    .in_2_4(sb_wire_in_0_BUS16_2_4),      
    .out_3_0(sb_wire_out_0_BUS16_3_0),
    .in_3_0(sb_wire_in_0_BUS16_3_0),      
    .out_3_1(sb_wire_out_0_BUS16_3_1),
    .in_3_1(sb_wire_in_0_BUS16_3_1),      
    .out_3_2(sb_wire_out_0_BUS16_3_2),
    .in_3_2(sb_wire_in_0_BUS16_3_2),      
    .out_3_3(sb_wire_out_0_BUS16_3_3),
    .in_3_3(sb_wire_in_0_BUS16_3_3),      
    .out_3_4(sb_wire_out_0_BUS16_3_4),
    .in_3_4(sb_wire_in_0_BUS16_3_4),      
    .config_addr(config_addr),
    .config_data(config_data),
    .config_en(config_en_sb_0_BUS16)
  );
  sb_unq5  sb_inst_busBUS1_row1
  (
    .clk(clk),
    .reset(reset),
    .pe_output_0(valid),
    .pe_output_1(almost_full),
    .out_0_0(sb_wire_out_1_BUS1_0_0),
    .in_0_0(sb_wire_in_1_BUS1_0_0),      
    .out_0_1(sb_wire_out_1_BUS1_0_1),
    .in_0_1(sb_wire_in_1_BUS1_0_1),      
    .out_0_2(sb_wire_out_1_BUS1_0_2),
    .in_0_2(sb_wire_in_1_BUS1_0_2),      
    .out_0_3(sb_wire_out_1_BUS1_0_3),
    .in_0_3(sb_wire_in_1_BUS1_0_3),      
    .out_0_4(sb_wire_out_1_BUS1_0_4),
    .in_0_4(sb_wire_in_1_BUS1_0_4),      
    .out_1_0(sb_wire_out_1_BUS1_1_0),
    .in_1_0(sb_wire_in_1_BUS1_1_0),      
    .out_1_1(sb_wire_out_1_BUS1_1_1),
    .in_1_1(sb_wire_in_1_BUS1_1_1),      
    .out_1_2(sb_wire_out_1_BUS1_1_2),
    .in_1_2(sb_wire_in_1_BUS1_1_2),      
    .out_1_3(sb_wire_out_1_BUS1_1_3),
    .in_1_3(sb_wire_in_1_BUS1_1_3),      
    .out_1_4(sb_wire_out_1_BUS1_1_4),
    .in_1_4(sb_wire_in_1_BUS1_1_4),      
    .out_2_0(sb_wire_out_1_BUS1_2_0),
    .in_2_0(sb_wire_in_1_BUS1_2_0),      
    .out_2_1(sb_wire_out_1_BUS1_2_1),
    .in_2_1(sb_wire_in_1_BUS1_2_1),      
    .out_2_2(sb_wire_out_1_BUS1_2_2),
    .in_2_2(sb_wire_in_1_BUS1_2_2),      
    .out_2_3(sb_wire_out_1_BUS1_2_3),
    .in_2_3(sb_wire_in_1_BUS1_2_3),      
    .out_2_4(sb_wire_out_1_BUS1_2_4),
    .in_2_4(sb_wire_in_1_BUS1_2_4),      
    .out_3_0(sb_wire_out_1_BUS1_3_0),
    .in_3_0(sb_wire_in_1_BUS1_3_0),      
    .out_3_1(sb_wire_out_1_BUS1_3_1),
    .in_3_1(sb_wire_in_1_BUS1_3_1),      
    .out_3_2(sb_wire_out_1_BUS1_3_2),
    .in_3_2(sb_wire_in_1_BUS1_3_2),      
    .out_3_3(sb_wire_out_1_BUS1_3_3),
    .in_3_3(sb_wire_in_1_BUS1_3_3),      
    .out_3_4(sb_wire_out_1_BUS1_3_4),
    .in_3_4(sb_wire_in_1_BUS1_3_4),      
    .config_addr(config_addr),
    .config_data(config_data),
    .config_en(config_en_sb_1_BUS1)
  );
  sb_unq1  sb_inst_busBUS16_row1
  (
    .clk(clk),
    .reset(reset),
    .pe_output_0(rdata),
    .out_0_0(sb_wire_out_1_BUS16_0_0),
    .in_0_0(sb_wire_in_1_BUS16_0_0),      
    .out_0_1(sb_wire_out_1_BUS16_0_1),
    .in_0_1(sb_wire_in_1_BUS16_0_1),      
    .out_0_2(sb_wire_out_1_BUS16_0_2),
    .in_0_2(sb_wire_in_1_BUS16_0_2),      
    .out_0_3(sb_wire_out_1_BUS16_0_3),
    .in_0_3(sb_wire_in_1_BUS16_0_3),      
    .out_0_4(sb_wire_out_1_BUS16_0_4),
    .in_0_4(sb_wire_in_1_BUS16_0_4),      
    .out_1_0(sb_wire_out_1_BUS16_1_0),
    .in_1_0(sb_wire_in_1_BUS16_1_0),      
    .out_1_1(sb_wire_out_1_BUS16_1_1),
    .in_1_1(sb_wire_in_1_BUS16_1_1),      
    .out_1_2(sb_wire_out_1_BUS16_1_2),
    .in_1_2(sb_wire_in_1_BUS16_1_2),      
    .out_1_3(sb_wire_out_1_BUS16_1_3),
    .in_1_3(sb_wire_in_1_BUS16_1_3),      
    .out_1_4(sb_wire_out_1_BUS16_1_4),
    .in_1_4(sb_wire_in_1_BUS16_1_4),      
    .out_2_0(sb_wire_out_1_BUS16_2_0),
    .in_2_0(sb_wire_in_1_BUS16_2_0),      
    .out_2_1(sb_wire_out_1_BUS16_2_1),
    .in_2_1(sb_wire_in_1_BUS16_2_1),      
    .out_2_2(sb_wire_out_1_BUS16_2_2),
    .in_2_2(sb_wire_in_1_BUS16_2_2),      
    .out_2_3(sb_wire_out_1_BUS16_2_3),
    .in_2_3(sb_wire_in_1_BUS16_2_3),      
    .out_2_4(sb_wire_out_1_BUS16_2_4),
    .in_2_4(sb_wire_in_1_BUS16_2_4),      
    .out_3_0(sb_wire_out_1_BUS16_3_0),
    .in_3_0(sb_wire_in_1_BUS16_3_0),      
    .out_3_1(sb_wire_out_1_BUS16_3_1),
    .in_3_1(sb_wire_in_1_BUS16_3_1),      
    .out_3_2(sb_wire_out_1_BUS16_3_2),
    .in_3_2(sb_wire_in_1_BUS16_3_2),      
    .out_3_3(sb_wire_out_1_BUS16_3_3),
    .in_3_3(sb_wire_in_1_BUS16_3_3),      
    .out_3_4(sb_wire_out_1_BUS16_3_4),
    .in_3_4(sb_wire_in_1_BUS16_3_4),      
    .config_addr(config_addr),
    .config_data(config_data),
    .config_en(config_en_sb_1_BUS16)
  );

      assign  out_0_BUS1_0_0 = sb_wire_out_0_BUS1_0_0;
      assign  sb_wire_in_0_BUS1_0_0 = in_0_BUS1_0_0;
      assign  out_0_BUS1_0_1 = sb_wire_out_0_BUS1_0_1;
      assign  sb_wire_in_0_BUS1_0_1 = in_0_BUS1_0_1;
      assign  out_0_BUS1_0_2 = sb_wire_out_0_BUS1_0_2;
      assign  sb_wire_in_0_BUS1_0_2 = in_0_BUS1_0_2;
      assign  out_0_BUS1_0_3 = sb_wire_out_0_BUS1_0_3;
      assign  sb_wire_in_0_BUS1_0_3 = in_0_BUS1_0_3;
      assign  out_0_BUS1_0_4 = sb_wire_out_0_BUS1_0_4;
      assign  sb_wire_in_0_BUS1_0_4 = in_0_BUS1_0_4;
      assign  sb_wire_in_0_BUS1_1_0 = sb_wire_out_1_BUS1_3_0;
      assign  sb_wire_in_1_BUS1_3_0 = sb_wire_out_0_BUS1_1_0;
      assign  sb_wire_in_0_BUS1_1_1 = sb_wire_out_1_BUS1_3_1;
      assign  sb_wire_in_1_BUS1_3_1 = sb_wire_out_0_BUS1_1_1;
      assign  sb_wire_in_0_BUS1_1_2 = sb_wire_out_1_BUS1_3_2;
      assign  sb_wire_in_1_BUS1_3_2 = sb_wire_out_0_BUS1_1_2;
      assign  sb_wire_in_0_BUS1_1_3 = sb_wire_out_1_BUS1_3_3;
      assign  sb_wire_in_1_BUS1_3_3 = sb_wire_out_0_BUS1_1_3;
      assign  sb_wire_in_0_BUS1_1_4 = sb_wire_out_1_BUS1_3_4;
      assign  sb_wire_in_1_BUS1_3_4 = sb_wire_out_0_BUS1_1_4;
      assign  out_0_BUS1_2_0 = sb_wire_out_0_BUS1_2_0;
      assign  sb_wire_in_0_BUS1_2_0 = in_0_BUS1_2_0;
      assign  out_0_BUS1_2_1 = sb_wire_out_0_BUS1_2_1;
      assign  sb_wire_in_0_BUS1_2_1 = in_0_BUS1_2_1;
      assign  out_0_BUS1_2_2 = sb_wire_out_0_BUS1_2_2;
      assign  sb_wire_in_0_BUS1_2_2 = in_0_BUS1_2_2;
      assign  out_0_BUS1_2_3 = sb_wire_out_0_BUS1_2_3;
      assign  sb_wire_in_0_BUS1_2_3 = in_0_BUS1_2_3;
      assign  out_0_BUS1_2_4 = sb_wire_out_0_BUS1_2_4;
      assign  sb_wire_in_0_BUS1_2_4 = in_0_BUS1_2_4;
      assign  out_0_BUS1_3_0 = sb_wire_out_0_BUS1_3_0;
      assign  sb_wire_in_0_BUS1_3_0 = in_0_BUS1_3_0;
      assign  out_0_BUS1_3_1 = sb_wire_out_0_BUS1_3_1;
      assign  sb_wire_in_0_BUS1_3_1 = in_0_BUS1_3_1;
      assign  out_0_BUS1_3_2 = sb_wire_out_0_BUS1_3_2;
      assign  sb_wire_in_0_BUS1_3_2 = in_0_BUS1_3_2;
      assign  out_0_BUS1_3_3 = sb_wire_out_0_BUS1_3_3;
      assign  sb_wire_in_0_BUS1_3_3 = in_0_BUS1_3_3;
      assign  out_0_BUS1_3_4 = sb_wire_out_0_BUS1_3_4;
      assign  sb_wire_in_0_BUS1_3_4 = in_0_BUS1_3_4;
      assign  out_1_BUS1_0_0 = sb_wire_out_1_BUS1_0_0;
      assign  sb_wire_in_1_BUS1_0_0 = in_1_BUS1_0_0;
      assign  out_1_BUS1_0_1 = sb_wire_out_1_BUS1_0_1;
      assign  sb_wire_in_1_BUS1_0_1 = in_1_BUS1_0_1;
      assign  out_1_BUS1_0_2 = sb_wire_out_1_BUS1_0_2;
      assign  sb_wire_in_1_BUS1_0_2 = in_1_BUS1_0_2;
      assign  out_1_BUS1_0_3 = sb_wire_out_1_BUS1_0_3;
      assign  sb_wire_in_1_BUS1_0_3 = in_1_BUS1_0_3;
      assign  out_1_BUS1_0_4 = sb_wire_out_1_BUS1_0_4;
      assign  sb_wire_in_1_BUS1_0_4 = in_1_BUS1_0_4;
      assign  out_1_BUS1_1_0 = sb_wire_out_1_BUS1_1_0;
      assign  sb_wire_in_1_BUS1_1_0 = in_1_BUS1_1_0;
      assign  out_1_BUS1_1_1 = sb_wire_out_1_BUS1_1_1;
      assign  sb_wire_in_1_BUS1_1_1 = in_1_BUS1_1_1;
      assign  out_1_BUS1_1_2 = sb_wire_out_1_BUS1_1_2;
      assign  sb_wire_in_1_BUS1_1_2 = in_1_BUS1_1_2;
      assign  out_1_BUS1_1_3 = sb_wire_out_1_BUS1_1_3;
      assign  sb_wire_in_1_BUS1_1_3 = in_1_BUS1_1_3;
      assign  out_1_BUS1_1_4 = sb_wire_out_1_BUS1_1_4;
      assign  sb_wire_in_1_BUS1_1_4 = in_1_BUS1_1_4;
      assign  out_1_BUS1_2_0 = sb_wire_out_1_BUS1_2_0;
      assign  sb_wire_in_1_BUS1_2_0 = in_1_BUS1_2_0;
      assign  out_1_BUS1_2_1 = sb_wire_out_1_BUS1_2_1;
      assign  sb_wire_in_1_BUS1_2_1 = in_1_BUS1_2_1;
      assign  out_1_BUS1_2_2 = sb_wire_out_1_BUS1_2_2;
      assign  sb_wire_in_1_BUS1_2_2 = in_1_BUS1_2_2;
      assign  out_1_BUS1_2_3 = sb_wire_out_1_BUS1_2_3;
      assign  sb_wire_in_1_BUS1_2_3 = in_1_BUS1_2_3;
      assign  out_1_BUS1_2_4 = sb_wire_out_1_BUS1_2_4;
      assign  sb_wire_in_1_BUS1_2_4 = in_1_BUS1_2_4;
      assign  out_0_BUS16_0_0 = sb_wire_out_0_BUS16_0_0;
      assign  sb_wire_in_0_BUS16_0_0 = in_0_BUS16_0_0;
      assign  out_0_BUS16_0_1 = sb_wire_out_0_BUS16_0_1;
      assign  sb_wire_in_0_BUS16_0_1 = in_0_BUS16_0_1;
      assign  out_0_BUS16_0_2 = sb_wire_out_0_BUS16_0_2;
      assign  sb_wire_in_0_BUS16_0_2 = in_0_BUS16_0_2;
      assign  out_0_BUS16_0_3 = sb_wire_out_0_BUS16_0_3;
      assign  sb_wire_in_0_BUS16_0_3 = in_0_BUS16_0_3;
      assign  out_0_BUS16_0_4 = sb_wire_out_0_BUS16_0_4;
      assign  sb_wire_in_0_BUS16_0_4 = in_0_BUS16_0_4;
      assign  sb_wire_in_0_BUS16_1_0 = sb_wire_out_1_BUS16_3_0;
      assign  sb_wire_in_1_BUS16_3_0 = sb_wire_out_0_BUS16_1_0;
      assign  sb_wire_in_0_BUS16_1_1 = sb_wire_out_1_BUS16_3_1;
      assign  sb_wire_in_1_BUS16_3_1 = sb_wire_out_0_BUS16_1_1;
      assign  sb_wire_in_0_BUS16_1_2 = sb_wire_out_1_BUS16_3_2;
      assign  sb_wire_in_1_BUS16_3_2 = sb_wire_out_0_BUS16_1_2;
      assign  sb_wire_in_0_BUS16_1_3 = sb_wire_out_1_BUS16_3_3;
      assign  sb_wire_in_1_BUS16_3_3 = sb_wire_out_0_BUS16_1_3;
      assign  sb_wire_in_0_BUS16_1_4 = sb_wire_out_1_BUS16_3_4;
      assign  sb_wire_in_1_BUS16_3_4 = sb_wire_out_0_BUS16_1_4;
      assign  out_0_BUS16_2_0 = sb_wire_out_0_BUS16_2_0;
      assign  sb_wire_in_0_BUS16_2_0 = in_0_BUS16_2_0;
      assign  out_0_BUS16_2_1 = sb_wire_out_0_BUS16_2_1;
      assign  sb_wire_in_0_BUS16_2_1 = in_0_BUS16_2_1;
      assign  out_0_BUS16_2_2 = sb_wire_out_0_BUS16_2_2;
      assign  sb_wire_in_0_BUS16_2_2 = in_0_BUS16_2_2;
      assign  out_0_BUS16_2_3 = sb_wire_out_0_BUS16_2_3;
      assign  sb_wire_in_0_BUS16_2_3 = in_0_BUS16_2_3;
      assign  out_0_BUS16_2_4 = sb_wire_out_0_BUS16_2_4;
      assign  sb_wire_in_0_BUS16_2_4 = in_0_BUS16_2_4;
      assign  out_0_BUS16_3_0 = sb_wire_out_0_BUS16_3_0;
      assign  sb_wire_in_0_BUS16_3_0 = in_0_BUS16_3_0;
      assign  out_0_BUS16_3_1 = sb_wire_out_0_BUS16_3_1;
      assign  sb_wire_in_0_BUS16_3_1 = in_0_BUS16_3_1;
      assign  out_0_BUS16_3_2 = sb_wire_out_0_BUS16_3_2;
      assign  sb_wire_in_0_BUS16_3_2 = in_0_BUS16_3_2;
      assign  out_0_BUS16_3_3 = sb_wire_out_0_BUS16_3_3;
      assign  sb_wire_in_0_BUS16_3_3 = in_0_BUS16_3_3;
      assign  out_0_BUS16_3_4 = sb_wire_out_0_BUS16_3_4;
      assign  sb_wire_in_0_BUS16_3_4 = in_0_BUS16_3_4;
      assign  out_1_BUS16_0_0 = sb_wire_out_1_BUS16_0_0;
      assign  sb_wire_in_1_BUS16_0_0 = in_1_BUS16_0_0;
      assign  out_1_BUS16_0_1 = sb_wire_out_1_BUS16_0_1;
      assign  sb_wire_in_1_BUS16_0_1 = in_1_BUS16_0_1;
      assign  out_1_BUS16_0_2 = sb_wire_out_1_BUS16_0_2;
      assign  sb_wire_in_1_BUS16_0_2 = in_1_BUS16_0_2;
      assign  out_1_BUS16_0_3 = sb_wire_out_1_BUS16_0_3;
      assign  sb_wire_in_1_BUS16_0_3 = in_1_BUS16_0_3;
      assign  out_1_BUS16_0_4 = sb_wire_out_1_BUS16_0_4;
      assign  sb_wire_in_1_BUS16_0_4 = in_1_BUS16_0_4;
      assign  out_1_BUS16_1_0 = sb_wire_out_1_BUS16_1_0;
      assign  sb_wire_in_1_BUS16_1_0 = in_1_BUS16_1_0;
      assign  out_1_BUS16_1_1 = sb_wire_out_1_BUS16_1_1;
      assign  sb_wire_in_1_BUS16_1_1 = in_1_BUS16_1_1;
      assign  out_1_BUS16_1_2 = sb_wire_out_1_BUS16_1_2;
      assign  sb_wire_in_1_BUS16_1_2 = in_1_BUS16_1_2;
      assign  out_1_BUS16_1_3 = sb_wire_out_1_BUS16_1_3;
      assign  sb_wire_in_1_BUS16_1_3 = in_1_BUS16_1_3;
      assign  out_1_BUS16_1_4 = sb_wire_out_1_BUS16_1_4;
      assign  sb_wire_in_1_BUS16_1_4 = in_1_BUS16_1_4;
      assign  out_1_BUS16_2_0 = sb_wire_out_1_BUS16_2_0;
      assign  sb_wire_in_1_BUS16_2_0 = in_1_BUS16_2_0;
      assign  out_1_BUS16_2_1 = sb_wire_out_1_BUS16_2_1;
      assign  sb_wire_in_1_BUS16_2_1 = in_1_BUS16_2_1;
      assign  out_1_BUS16_2_2 = sb_wire_out_1_BUS16_2_2;
      assign  sb_wire_in_1_BUS16_2_2 = in_1_BUS16_2_2;
      assign  out_1_BUS16_2_3 = sb_wire_out_1_BUS16_2_3;
      assign  sb_wire_in_1_BUS16_2_3 = in_1_BUS16_2_3;
      assign  out_1_BUS16_2_4 = sb_wire_out_1_BUS16_2_4;
      assign  sb_wire_in_1_BUS16_2_4 = in_1_BUS16_2_4;



  reg config_en_cb_wdata;
  always @(*) begin
    if (reset) begin
       config_en_cb_wdata = 1'b0;
    end else begin
       if ((config_addr[15:0]==tile_id)&&(config_addr[23:16]==8'd5)) begin
         config_en_cb_wdata = 1'b1;
       end else begin
         config_en_cb_wdata = 1'b0;
       end
    end
  end
  wire [15:0] wdata;
  cb_unq3  cb_wdata
  (
    .clk(clk),
    .reset(reset),
    .out(wdata),
    .in_0(in_0_BUS16_2_0),
    .in_1(in_0_BUS16_2_1),
    .in_2(in_0_BUS16_2_2),
    .in_3(in_0_BUS16_2_3),
    .in_4(in_0_BUS16_2_4),
    .in_5(out_0_BUS16_2_0),
    .in_6(out_0_BUS16_2_1),
    .in_7(out_0_BUS16_2_2),
    .in_8(out_0_BUS16_2_3),
    .in_9(out_0_BUS16_2_4),
    .config_addr(config_addr),
    .config_data(config_data),
    .config_en(config_en_cb_wdata)
  );
  reg config_en_cb_waddr;
  always @(*) begin
    if (reset) begin
       config_en_cb_waddr = 1'b0;
    end else begin
       if ((config_addr[15:0]==tile_id)&&(config_addr[23:16]==8'd6)) begin
         config_en_cb_waddr = 1'b1;
       end else begin
         config_en_cb_waddr = 1'b0;
       end
    end
  end
  wire [15:0] waddr;
  cb_unq3  cb_waddr
  (
    .clk(clk),
    .reset(reset),
    .out(waddr),
    .in_0(in_0_BUS16_2_0),
    .in_1(in_0_BUS16_2_1),
    .in_2(in_0_BUS16_2_2),
    .in_3(in_0_BUS16_2_3),
    .in_4(in_0_BUS16_2_4),
    .in_5(out_0_BUS16_2_0),
    .in_6(out_0_BUS16_2_1),
    .in_7(out_0_BUS16_2_2),
    .in_8(out_0_BUS16_2_3),
    .in_9(out_0_BUS16_2_4),
    .config_addr(config_addr),
    .config_data(config_data),
    .config_en(config_en_cb_waddr)
  );
  reg config_en_cb_raddr;
  always @(*) begin
    if (reset) begin
       config_en_cb_raddr = 1'b0;
    end else begin
       if ((config_addr[15:0]==tile_id)&&(config_addr[23:16]==8'd7)) begin
         config_en_cb_raddr = 1'b1;
       end else begin
         config_en_cb_raddr = 1'b0;
       end
    end
  end
  wire [15:0] raddr;
  cb_unq3  cb_raddr
  (
    .clk(clk),
    .reset(reset),
    .out(raddr),
    .in_0(in_0_BUS16_2_0),
    .in_1(in_0_BUS16_2_1),
    .in_2(in_0_BUS16_2_2),
    .in_3(in_0_BUS16_2_3),
    .in_4(in_0_BUS16_2_4),
    .in_5(out_0_BUS16_2_0),
    .in_6(out_0_BUS16_2_1),
    .in_7(out_0_BUS16_2_2),
    .in_8(out_0_BUS16_2_3),
    .in_9(out_0_BUS16_2_4),
    .config_addr(config_addr),
    .config_data(config_data),
    .config_en(config_en_cb_raddr)
  );
  reg config_en_cb_ren;
  always @(*) begin
    if (reset) begin
       config_en_cb_ren = 1'b0;
    end else begin
       if ((config_addr[15:0]==tile_id)&&(config_addr[23:16]==8'd8)) begin
         config_en_cb_ren = 1'b1;
       end else begin
         config_en_cb_ren = 1'b0;
       end
    end
  end
  wire ren;
  cb_unq4  cb_ren
  (
    .clk(clk),
    .reset(reset),
    .out(ren),
    .in_0(in_0_BUS1_2_0),
    .in_1(in_0_BUS1_2_1),
    .in_2(in_0_BUS1_2_2),
    .in_3(in_0_BUS1_2_3),
    .in_4(in_0_BUS1_2_4),
    .in_5(out_0_BUS1_2_0),
    .in_6(out_0_BUS1_2_1),
    .in_7(out_0_BUS1_2_2),
    .in_8(out_0_BUS1_2_3),
    .in_9(out_0_BUS1_2_4),
    .config_addr(config_addr),
    .config_data(config_data),
    .config_en(config_en_cb_ren)
  );
  reg config_en_cb_wen;
  always @(*) begin
    if (reset) begin
       config_en_cb_wen = 1'b0;
    end else begin
       if ((config_addr[15:0]==tile_id)&&(config_addr[23:16]==8'd9)) begin
         config_en_cb_wen = 1'b1;
       end else begin
         config_en_cb_wen = 1'b0;
       end
    end
  end
  wire wen;
  cb_unq4  cb_wen
  (
    .clk(clk),
    .reset(reset),
    .out(wen),
    .in_0(in_0_BUS1_2_0),
    .in_1(in_0_BUS1_2_1),
    .in_2(in_0_BUS1_2_2),
    .in_3(in_0_BUS1_2_3),
    .in_4(in_0_BUS1_2_4),
    .in_5(out_0_BUS1_2_0),
    .in_6(out_0_BUS1_2_1),
    .in_7(out_0_BUS1_2_2),
    .in_8(out_0_BUS1_2_3),
    .in_9(out_0_BUS1_2_4),
    .config_addr(config_addr),
    .config_data(config_data),
    .config_en(config_en_cb_wen)
  );





  memory_core_unq1  memory_core
  (
      .clk(clk),
      .config_addr(config_addr),
      .config_data(config_data),
      .config_en(config_en_mem),
      .xdata_in(wdata),
      .data_out(rdata),
      .chain_in(chain_in),
      .chain_out(chain_out),
      .addr(raddr),
      .addr_w(waddr),
      .xwen(wen),
      .chain_wen_in(chain_wen_in),
      .ren(ren),
      .valid(valid),
      .chain_valid_out(chain_valid_out),
      .almost_full(almost_full),
      .reset(reset)
   );


endmodule




