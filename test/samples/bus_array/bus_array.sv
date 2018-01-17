module   test_pe_comp_unq1  #(
  parameter DataWidth = 16
) (
  input [8:0]                    op_code,

  input  [DataWidth-1:0]         op_a,
  input  [DataWidth-1:0]         op_b,
  input                          op_d_p,


  output logic [DataWidth-1:0]   res,
  output logic                   res_p
);

localparam DATA_MSB      = DataWidth - 1;

localparam PE_ADD_OP     = 6'h0;
localparam PE_SUB_OP     = 6'h1;
localparam PE_ABS_OP     = 6'h3;

localparam PE_GTE_MAX_OP = 6'h4;
localparam PE_LTE_MIN_OP = 6'h5;
localparam PE_EQ_OP      = 6'h6;

localparam PE_SEL_OP     = 6'h8;

localparam PE_RSHFT_OP   = 6'hF;
localparam PE_LSHFT_OP   = 6'h11;

localparam PE_MULT_0_OP  = 6'hB;
localparam PE_MULT_1_OP  = 6'hC;
localparam PE_MULT_2_OP  = 6'hD;
localparam PE_RELU       = 6'hE;

localparam PE_OR_OP      = 6'h12;
localparam PE_AND_OP     = 6'h13;
localparam PE_XOR_OP     = 6'h14;

logic [2*DataWidth-1:0] mult_res;

logic [8:0]        nc_op_code;
assign             nc_op_code = op_code;


logic [DATA_MSB:0] res_w;
logic              res_p_w;

logic                 is_signed;
//logic                 dual_mode;

logic                 cmpr_lte;
logic                 cmpr_gte;
logic                 cmpr_eq;

localparam NUM_ADDERS = 1;
localparam ADD_MSB = NUM_ADDERS - 1;

logic [DATA_MSB:0]  add_a     [ADD_MSB:0];
logic [DATA_MSB:0]  add_b     [ADD_MSB:0];
logic               add_c_in  [ADD_MSB:0];

logic [DATA_MSB:0]  add_res   [ADD_MSB:0];
logic               add_c_out [ADD_MSB:0];


genvar ggg;

generate
  for(ggg=0;ggg<NUM_ADDERS;ggg=ggg+1) begin : GEN_ADD
  test_full_add #(.DataWidth(DataWidth)) full_add
    (
      .a     (add_a[ggg]),
      .b     (add_b[ggg]),
      .c_in  (add_c_in[ggg]),

//      .dual_mode (dual_mode),

      .res   (add_res[ggg]),
      .c_out (add_c_out[ggg])
    );

  end

endgenerate

assign cmpr_eq   =  ~|(op_a ^ op_b);



test_cmpr  cmpr
(
  .a_msb     (op_a[DATA_MSB]),
  .b_msb     (op_b[DATA_MSB]),
  .diff_msb  (add_res[0][DATA_MSB]),
  .is_signed (is_signed),
  .eq        (cmpr_eq),

  .lte       (cmpr_lte),
  .gte       (cmpr_gte)
);



logic                 mult_c_out;

test_mult_add #(.DataWidth(DataWidth)) test_mult_add
(
  .is_signed (is_signed),

  .a  (op_a),
  .b  (op_b),

//  .dual_mode(dual_mode),

  .res   (mult_res),
  .c_out (mult_c_out)
);





logic [DATA_MSB:0] shift_res;

test_shifter_unq1 #(.DataWidth(DataWidth)) test_shifter
(
  .is_signed (is_signed),
  .dir_left(op_code[5:0]==PE_LSHFT_OP),

  .a  (op_a),
  .b   (op_b[$clog2(DataWidth)-1+0:0]),

  .res (shift_res)
);


assign is_signed   = op_code[6];
//assign dual_mode   = op_code[8]; //Save the OP code bit for half precision support


logic diff_sign;
assign diff_sign = add_res[0][DATA_MSB];


always_comb begin : proc_alu
  add_a[0] = op_a;
  add_b[0] = op_b;
  add_c_in[0] = 1'b0;


  res_w   = add_res[ADD_MSB];
  res_p_w = add_c_out[ADD_MSB];



  unique case (op_code[5:0])
    PE_ADD_OP: begin
        add_c_in[0] = op_d_p;
        res_p_w     = add_c_out[0];
      end
    PE_SUB_OP: begin
        add_b[0]    = ~op_b;
        add_c_in[0] = 1'b1;
      end
    PE_ABS_OP: begin
        add_a[0]    = ~op_a;
        add_c_in[0] = 1'b1;
        res_p_w     = op_a[DATA_MSB];

        res_w       = diff_sign ? op_a : add_res[0];
    end

    PE_GTE_MAX_OP: begin
        add_b[0]    = ~op_b;
        add_c_in[0] = 1'b1;
        res_p_w     = cmpr_gte;
        res_w       = res_p_w ? op_a : op_b;
      end
    PE_LTE_MIN_OP: begin
        add_b[0]    = ~op_b;
        add_c_in[0] = 1'b1;
        res_p_w     = cmpr_lte;
        res_w       = res_p_w ? op_a : op_b;
      end
    PE_EQ_OP: begin
        res_p_w = cmpr_eq;
        res_w   = op_b;
      end
    PE_SEL_OP: begin
        res_w = op_d_p ? op_a : op_b;
      end
    PE_RSHFT_OP: begin
        res_w = shift_res;
      end
    PE_LSHFT_OP: begin
        res_w = shift_res;
      end
    PE_MULT_0_OP: begin
        res_w   = mult_res[DATA_MSB:0];
        res_p_w = mult_c_out;
      end
    PE_MULT_1_OP: begin
        res_w   = mult_res[3*DataWidth/2-1:DataWidth/2];
        res_p_w = mult_c_out;
      end
    PE_MULT_2_OP: begin
        res_w   = mult_res[2*DataWidth-1:DataWidth];
        res_p_w = mult_c_out;
      end

    PE_RELU: begin
        res_w   = diff_sign ? mult_res[2*DataWidth-1:DataWidth] : op_a;
        res_p_w = op_a[DATA_MSB];
      end

    PE_OR_OP: begin
        res_w = op_a | op_b;
      end
    PE_AND_OP: begin
        res_w = op_a & op_b;
      end
    PE_XOR_OP: begin
        res_w = op_a ^ op_b;
      end


    default: begin
        res_w   = op_a;
        res_p_w = op_d_p;
      end
  endcase
end


assign res   = res_w;
assign res_p = res_p_w;

endmodule
