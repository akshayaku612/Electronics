/////////////////////////////////////////////////////////////
// Created by: Synopsys DC Expert(TM) in wire load mode
// Version   : P-2019.03-SP1
// Date      : Wed Nov 17 21:48:08 2021
/////////////////////////////////////////////////////////////


module MyDesign ( clk, reset_b, dut_run, dut_busy, sram_dut_read_data, 
        dut_sram_read_address, wmem_dut_read_data, dut_wmem_read_address, 
        dut_sram_write_address, dut_sram_write_data, dut_sram_write_enable );
  input [15:0] sram_dut_read_data;
  output [11:0] dut_sram_read_address;
  input [15:0] wmem_dut_read_data;
  output [11:0] dut_wmem_read_address;
  output [11:0] dut_sram_write_address;
  output [15:0] dut_sram_write_data;
  input clk, reset_b, dut_run;
  output dut_busy, dut_sram_write_enable;
  wire   u1_next_state_0_, n49, n50, n51, n52, n53, n54, n55, n56, n57, n58,
         n155, n156, n157, n158, n159, n160, n161, n162, n163, n164, n165,
         n166, n167, n168, n170, n171, n172, n173, n174, n175, n176, n177,
         n178, n179, n180, n181, n182, n183, n184, n185, n186, n187, n188,
         n189, n190, n191, n192, n193, n194, n195, n196, n197, n198, n199,
         n200, n201, n202, n203, n204, n205, n206, n207, n208, n209, n210,
         n211, n212, n213, n214, n215, n216, n217, n218, n219, n220, n221,
         n222, n223, n224, n225, n226, n227, n228, n229, n230, n231, n232,
         n233, n234, n235, n236, n237, n238, n239, n240, n241, n242, n243,
         n244, n245, n246, n247, n248, n250, n251, n252, n253, n254, n255,
         n256, n257, n258, n259, n260, n261, n262, n263, n264, n265, n266,
         n267, n268, n269, n270, n271, n272, n273, n274, n275, n276, n277,
         n278, n279, n280, n281, n282, n283, n284, n285, n286, n287, n288,
         n289, n290, n291, n292, n293, n294, n295, n296, n297, n298, n299,
         n300;
  wire   [1:0] u1_current_state;
  wire   [3:0] u2_output_matrix;

  DFFR_X1 u1_current_state_reg_0_ ( .D(u1_next_state_0_), .CK(clk), .RN(
        reset_b), .Q(u1_current_state[0]), .QN(n299) );
  DFFR_X1 u1_current_state_reg_1_ ( .D(n53), .CK(clk), .RN(reset_b), .Q(
        u1_current_state[1]), .QN(n297) );
  DFF_X1 u2_output_matrix_reg_0_ ( .D(n52), .CK(clk), .Q(u2_output_matrix[0]), 
        .QN(n293) );
  DFF_X1 u2_output_matrix_reg_1_ ( .D(n51), .CK(clk), .Q(u2_output_matrix[1]), 
        .QN(n294) );
  DFF_X1 u2_output_matrix_reg_2_ ( .D(n50), .CK(clk), .Q(u2_output_matrix[2]), 
        .QN(n295) );
  DFF_X1 u2_output_matrix_reg_3_ ( .D(n49), .CK(clk), .Q(u2_output_matrix[3]), 
        .QN(n296) );
  DFFR_X1 u1_current_state_reg_2_ ( .D(n54), .CK(clk), .RN(reset_b), .Q(n298), 
        .QN(n300) );
  INV_X4 U72 ( .A(1'b1), .ZN(dut_sram_write_data[4]) );
  INV_X4 U73 ( .A(1'b1), .ZN(dut_sram_write_data[5]) );
  INV_X4 U74 ( .A(1'b1), .ZN(dut_sram_write_data[6]) );
  INV_X1 U75 ( .A(n239), .ZN(n242) );
  NAND2_X1 U76 ( .A1(n245), .A2(n246), .ZN(n267) );
  NAND2_X1 U77 ( .A1(n286), .A2(u1_current_state[1]), .ZN(n283) );
  NAND2_X1 U78 ( .A1(n55), .A2(n262), .ZN(n261) );
  NAND2_X1 U79 ( .A1(n56), .A2(n263), .ZN(n55) );
  OR2_X1 U80 ( .A1(n267), .A2(n266), .ZN(n56) );
  XNOR2_X1 U81 ( .A(n57), .B(wmem_dut_read_data[1]), .ZN(n227) );
  NAND3_X1 U82 ( .A1(n168), .A2(n166), .A3(n58), .ZN(n57) );
  AND2_X1 U83 ( .A1(n167), .A2(n165), .ZN(n58) );
  INV_X2 U84 ( .A(n233), .ZN(n235) );
  XNOR2_X1 U85 ( .A(n228), .B(n250), .ZN(n233) );
  NAND2_X1 U86 ( .A1(n237), .A2(n238), .ZN(n239) );
  NAND2_X2 U87 ( .A1(n282), .A2(n281), .ZN(n285) );
  NAND2_X2 U88 ( .A1(n282), .A2(n275), .ZN(n278) );
  NAND2_X2 U89 ( .A1(n282), .A2(n272), .ZN(n274) );
  NAND2_X2 U90 ( .A1(n282), .A2(n268), .ZN(n270) );
  NAND2_X2 U91 ( .A1(n261), .A2(n260), .ZN(n282) );
  AND4_X1 U92 ( .A1(n196), .A2(n195), .A3(n252), .A4(n255), .ZN(n266) );
  INV_X1 U93 ( .A(n262), .ZN(n264) );
  XNOR2_X1 U94 ( .A(n212), .B(wmem_dut_read_data[3]), .ZN(n213) );
  NAND4_X1 U95 ( .A1(n211), .A2(n210), .A3(n209), .A4(n208), .ZN(n212) );
  NAND2_X2 U96 ( .A1(n283), .A2(n155), .ZN(n54) );
  INV_X2 U97 ( .A(n276), .ZN(n219) );
  INV_X2 U98 ( .A(n158), .ZN(n271) );
  INV_X2 U99 ( .A(1'b1), .ZN(dut_sram_read_address[11]) );
  INV_X2 U100 ( .A(1'b1), .ZN(dut_sram_read_address[10]) );
  INV_X2 U101 ( .A(1'b1), .ZN(dut_sram_read_address[9]) );
  INV_X2 U102 ( .A(1'b1), .ZN(dut_sram_read_address[8]) );
  INV_X2 U103 ( .A(1'b1), .ZN(dut_sram_read_address[7]) );
  INV_X2 U104 ( .A(1'b1), .ZN(dut_sram_read_address[6]) );
  INV_X2 U105 ( .A(1'b1), .ZN(dut_sram_read_address[5]) );
  INV_X2 U106 ( .A(1'b1), .ZN(dut_sram_read_address[4]) );
  INV_X2 U107 ( .A(1'b1), .ZN(dut_sram_read_address[3]) );
  INV_X2 U108 ( .A(1'b1), .ZN(dut_sram_read_address[2]) );
  INV_X2 U109 ( .A(1'b1), .ZN(dut_sram_read_address[1]) );
  INV_X2 U110 ( .A(1'b1), .ZN(dut_sram_read_address[0]) );
  INV_X2 U111 ( .A(1'b1), .ZN(dut_wmem_read_address[11]) );
  INV_X2 U112 ( .A(1'b1), .ZN(dut_wmem_read_address[10]) );
  INV_X2 U113 ( .A(1'b1), .ZN(dut_wmem_read_address[9]) );
  INV_X2 U114 ( .A(1'b1), .ZN(dut_wmem_read_address[8]) );
  INV_X2 U115 ( .A(1'b1), .ZN(dut_wmem_read_address[7]) );
  INV_X2 U116 ( .A(1'b1), .ZN(dut_wmem_read_address[6]) );
  INV_X2 U117 ( .A(1'b1), .ZN(dut_wmem_read_address[5]) );
  INV_X2 U118 ( .A(1'b1), .ZN(dut_wmem_read_address[4]) );
  INV_X2 U119 ( .A(1'b1), .ZN(dut_wmem_read_address[3]) );
  INV_X2 U120 ( .A(1'b1), .ZN(dut_wmem_read_address[2]) );
  INV_X2 U121 ( .A(1'b1), .ZN(dut_wmem_read_address[1]) );
  INV_X2 U122 ( .A(1'b1), .ZN(dut_wmem_read_address[0]) );
  INV_X2 U123 ( .A(1'b1), .ZN(dut_sram_write_address[11]) );
  INV_X2 U124 ( .A(1'b1), .ZN(dut_sram_write_address[10]) );
  INV_X2 U125 ( .A(1'b1), .ZN(dut_sram_write_address[9]) );
  INV_X2 U126 ( .A(1'b1), .ZN(dut_sram_write_address[8]) );
  INV_X2 U127 ( .A(1'b1), .ZN(dut_sram_write_address[7]) );
  INV_X2 U128 ( .A(1'b1), .ZN(dut_sram_write_address[6]) );
  INV_X2 U129 ( .A(1'b1), .ZN(dut_sram_write_address[5]) );
  INV_X2 U130 ( .A(1'b1), .ZN(dut_sram_write_address[4]) );
  INV_X2 U131 ( .A(1'b1), .ZN(dut_sram_write_address[3]) );
  INV_X2 U132 ( .A(1'b1), .ZN(dut_sram_write_address[2]) );
  INV_X2 U133 ( .A(1'b1), .ZN(dut_sram_write_address[1]) );
  INV_X2 U134 ( .A(1'b1), .ZN(dut_sram_write_address[0]) );
  INV_X2 U135 ( .A(1'b1), .ZN(dut_sram_write_data[15]) );
  INV_X2 U136 ( .A(1'b1), .ZN(dut_sram_write_data[14]) );
  INV_X2 U137 ( .A(1'b1), .ZN(dut_sram_write_data[13]) );
  INV_X2 U138 ( .A(1'b1), .ZN(dut_sram_write_data[12]) );
  INV_X2 U139 ( .A(1'b1), .ZN(dut_sram_write_data[11]) );
  INV_X2 U140 ( .A(1'b1), .ZN(dut_sram_write_data[10]) );
  INV_X2 U141 ( .A(1'b1), .ZN(dut_sram_write_data[9]) );
  INV_X2 U142 ( .A(1'b1), .ZN(dut_sram_write_data[8]) );
  INV_X2 U143 ( .A(1'b1), .ZN(dut_sram_write_data[7]) );
  INV_X4 U192 ( .A(n283), .ZN(n201) );
  INV_X1 U193 ( .A(sram_dut_read_data[10]), .ZN(n156) );
  INV_X1 U194 ( .A(sram_dut_read_data[2]), .ZN(n176) );
  OR2_X1 U195 ( .A1(n290), .A2(n300), .ZN(n276) );
  AND2_X1 U196 ( .A1(n297), .A2(n298), .ZN(n157) );
  OR2_X1 U197 ( .A1(n54), .A2(n207), .ZN(n211) );
  OR2_X1 U198 ( .A1(n54), .A2(n200), .ZN(n205) );
  OR2_X1 U199 ( .A1(n54), .A2(n218), .ZN(n223) );
  OR2_X1 U200 ( .A1(n54), .A2(n156), .ZN(n162) );
  OR2_X1 U201 ( .A1(n54), .A2(n182), .ZN(n186) );
  OR2_X1 U202 ( .A1(n54), .A2(n176), .ZN(n180) );
  OR2_X1 U203 ( .A1(n54), .A2(n170), .ZN(n174) );
  OR2_X1 U204 ( .A1(n198), .A2(n197), .ZN(n257) );
  OR2_X1 U205 ( .A1(n194), .A2(n227), .ZN(n256) );
  AND3_X1 U206 ( .A1(n280), .A2(n279), .A3(n219), .ZN(n275) );
  AND3_X1 U207 ( .A1(n280), .A2(n279), .A3(n271), .ZN(n272) );
  AND3_X1 U208 ( .A1(n280), .A2(n279), .A3(n201), .ZN(n281) );
  AND3_X1 U209 ( .A1(n280), .A2(n279), .A3(n164), .ZN(n268) );
  NOR2_X2 U210 ( .A1(n292), .A2(n294), .ZN(dut_sram_write_data[1]) );
  NOR2_X2 U211 ( .A1(n292), .A2(n295), .ZN(dut_sram_write_data[2]) );
  NOR2_X2 U212 ( .A1(n292), .A2(n296), .ZN(dut_sram_write_data[3]) );
  INV_X2 U213 ( .A(n292), .ZN(dut_sram_write_enable) );
  NAND2_X2 U214 ( .A1(n288), .A2(n287), .ZN(dut_busy) );
  NOR2_X2 U215 ( .A1(n292), .A2(n293), .ZN(dut_sram_write_data[0]) );
  INV_X1 U216 ( .A(n54), .ZN(n164) );
  INV_X1 U217 ( .A(sram_dut_read_data[4]), .ZN(n207) );
  INV_X1 U218 ( .A(sram_dut_read_data[9]), .ZN(n218) );
  INV_X1 U219 ( .A(sram_dut_read_data[6]), .ZN(n200) );
  INV_X1 U220 ( .A(sram_dut_read_data[5]), .ZN(n182) );
  INV_X1 U221 ( .A(n213), .ZN(n214) );
  NOR2_X1 U222 ( .A1(n298), .A2(n299), .ZN(n286) );
  NAND2_X1 U223 ( .A1(n297), .A2(n298), .ZN(n155) );
  NAND2_X1 U224 ( .A1(n157), .A2(n299), .ZN(n158) );
  NAND2_X1 U225 ( .A1(n271), .A2(sram_dut_read_data[14]), .ZN(n161) );
  NAND2_X1 U226 ( .A1(n201), .A2(sram_dut_read_data[11]), .ZN(n160) );
  NAND2_X1 U227 ( .A1(n297), .A2(u1_current_state[0]), .ZN(n290) );
  NAND2_X1 U228 ( .A1(n219), .A2(sram_dut_read_data[15]), .ZN(n159) );
  AND4_X2 U229 ( .A1(n162), .A2(n161), .A3(n160), .A4(n159), .ZN(n163) );
  XNOR2_X1 U230 ( .A(n163), .B(wmem_dut_read_data[8]), .ZN(n226) );
  INV_X1 U231 ( .A(n226), .ZN(n194) );
  NAND2_X1 U232 ( .A1(n164), .A2(sram_dut_read_data[1]), .ZN(n168) );
  NAND2_X1 U233 ( .A1(n201), .A2(sram_dut_read_data[2]), .ZN(n167) );
  NAND2_X1 U234 ( .A1(n271), .A2(sram_dut_read_data[5]), .ZN(n166) );
  NAND2_X1 U235 ( .A1(n219), .A2(sram_dut_read_data[6]), .ZN(n165) );
  INV_X1 U236 ( .A(sram_dut_read_data[0]), .ZN(n170) );
  NAND2_X1 U237 ( .A1(n201), .A2(sram_dut_read_data[1]), .ZN(n173) );
  NAND2_X1 U238 ( .A1(n271), .A2(sram_dut_read_data[4]), .ZN(n172) );
  NAND2_X1 U239 ( .A1(n219), .A2(sram_dut_read_data[5]), .ZN(n171) );
  NAND4_X1 U240 ( .A1(n174), .A2(n173), .A3(n172), .A4(n171), .ZN(n175) );
  XNOR2_X1 U241 ( .A(n175), .B(wmem_dut_read_data[0]), .ZN(n250) );
  NAND2_X1 U242 ( .A1(n256), .A2(n250), .ZN(n196) );
  NAND2_X1 U243 ( .A1(n201), .A2(sram_dut_read_data[3]), .ZN(n179) );
  NAND2_X1 U244 ( .A1(n271), .A2(sram_dut_read_data[6]), .ZN(n178) );
  NAND2_X1 U245 ( .A1(n219), .A2(sram_dut_read_data[7]), .ZN(n177) );
  NAND4_X1 U246 ( .A1(n180), .A2(n179), .A3(n178), .A4(n177), .ZN(n181) );
  XNOR2_X1 U247 ( .A(n181), .B(wmem_dut_read_data[2]), .ZN(n198) );
  NAND2_X1 U248 ( .A1(n201), .A2(sram_dut_read_data[6]), .ZN(n185) );
  NAND2_X1 U249 ( .A1(n271), .A2(sram_dut_read_data[9]), .ZN(n184) );
  NAND2_X1 U250 ( .A1(n219), .A2(sram_dut_read_data[10]), .ZN(n183) );
  NAND4_X1 U251 ( .A1(n186), .A2(n185), .A3(n184), .A4(n183), .ZN(n187) );
  XNOR2_X1 U252 ( .A(n187), .B(wmem_dut_read_data[4]), .ZN(n197) );
  INV_X1 U253 ( .A(sram_dut_read_data[8]), .ZN(n188) );
  OR2_X1 U254 ( .A1(n54), .A2(n188), .ZN(n192) );
  NAND2_X1 U255 ( .A1(n201), .A2(sram_dut_read_data[9]), .ZN(n191) );
  NAND2_X1 U256 ( .A1(n271), .A2(sram_dut_read_data[12]), .ZN(n190) );
  NAND2_X1 U257 ( .A1(n219), .A2(sram_dut_read_data[13]), .ZN(n189) );
  NAND4_X1 U258 ( .A1(n192), .A2(n191), .A3(n190), .A4(n189), .ZN(n193) );
  XNOR2_X1 U259 ( .A(n193), .B(wmem_dut_read_data[6]), .ZN(n253) );
  NAND2_X1 U260 ( .A1(n257), .A2(n253), .ZN(n195) );
  NAND2_X1 U261 ( .A1(n227), .A2(n194), .ZN(n252) );
  NAND2_X1 U262 ( .A1(n198), .A2(n197), .ZN(n255) );
  XNOR2_X1 U263 ( .A(n198), .B(n197), .ZN(n199) );
  XNOR2_X1 U264 ( .A(n199), .B(n253), .ZN(n240) );
  NAND2_X1 U265 ( .A1(n201), .A2(sram_dut_read_data[7]), .ZN(n204) );
  NAND2_X1 U266 ( .A1(n271), .A2(sram_dut_read_data[10]), .ZN(n203) );
  NAND2_X1 U267 ( .A1(n219), .A2(sram_dut_read_data[11]), .ZN(n202) );
  NAND4_X1 U268 ( .A1(n205), .A2(n204), .A3(n203), .A4(n202), .ZN(n206) );
  XNOR2_X1 U269 ( .A(n206), .B(wmem_dut_read_data[5]), .ZN(n232) );
  NAND2_X1 U270 ( .A1(n201), .A2(sram_dut_read_data[5]), .ZN(n210) );
  NAND2_X1 U271 ( .A1(n271), .A2(sram_dut_read_data[8]), .ZN(n209) );
  NAND2_X1 U272 ( .A1(n219), .A2(sram_dut_read_data[9]), .ZN(n208) );
  NAND2_X1 U273 ( .A1(n232), .A2(n213), .ZN(n217) );
  INV_X1 U274 ( .A(n232), .ZN(n215) );
  NAND2_X1 U275 ( .A1(n215), .A2(n214), .ZN(n216) );
  NAND2_X1 U276 ( .A1(n217), .A2(n216), .ZN(n225) );
  NAND2_X1 U277 ( .A1(n201), .A2(sram_dut_read_data[10]), .ZN(n222) );
  NAND2_X1 U278 ( .A1(n271), .A2(sram_dut_read_data[13]), .ZN(n221) );
  NAND2_X1 U279 ( .A1(n219), .A2(sram_dut_read_data[14]), .ZN(n220) );
  NAND4_X1 U280 ( .A1(n223), .A2(n222), .A3(n221), .A4(n220), .ZN(n224) );
  XNOR2_X1 U281 ( .A(n224), .B(wmem_dut_read_data[7]), .ZN(n231) );
  XNOR2_X1 U282 ( .A(n225), .B(n231), .ZN(n234) );
  XNOR2_X1 U283 ( .A(n227), .B(n226), .ZN(n228) );
  OAI21_X1 U284 ( .B1(n240), .B2(n234), .A(n235), .ZN(n230) );
  NAND2_X1 U285 ( .A1(n240), .A2(n234), .ZN(n229) );
  NAND2_X1 U286 ( .A1(n230), .A2(n229), .ZN(n245) );
  FA_X1 U287 ( .A(n232), .B(n213), .CI(n231), .CO(n246) );
  NAND2_X1 U288 ( .A1(n234), .A2(n233), .ZN(n238) );
  INV_X1 U289 ( .A(n234), .ZN(n236) );
  NAND2_X1 U290 ( .A1(n236), .A2(n235), .ZN(n237) );
  NAND2_X1 U291 ( .A1(n239), .A2(n240), .ZN(n244) );
  INV_X1 U292 ( .A(n240), .ZN(n241) );
  NAND2_X1 U293 ( .A1(n242), .A2(n241), .ZN(n243) );
  NAND2_X1 U294 ( .A1(n244), .A2(n243), .ZN(n263) );
  INV_X1 U295 ( .A(n245), .ZN(n248) );
  INV_X1 U296 ( .A(n246), .ZN(n247) );
  NAND2_X1 U297 ( .A1(n248), .A2(n247), .ZN(n262) );
  INV_X1 U298 ( .A(n250), .ZN(n251) );
  NAND2_X1 U299 ( .A1(n252), .A2(n251), .ZN(n259) );
  INV_X1 U300 ( .A(n253), .ZN(n254) );
  NAND2_X1 U301 ( .A1(n255), .A2(n254), .ZN(n258) );
  NAND4_X1 U302 ( .A1(n259), .A2(n258), .A3(n257), .A4(n256), .ZN(n260) );
  NAND2_X1 U303 ( .A1(n264), .A2(n263), .ZN(n280) );
  INV_X1 U304 ( .A(reset_b), .ZN(n265) );
  AOI21_X1 U305 ( .B1(n267), .B2(n266), .A(n265), .ZN(n279) );
  NAND2_X1 U306 ( .A1(n54), .A2(u2_output_matrix[0]), .ZN(n269) );
  NAND2_X1 U307 ( .A1(n270), .A2(n269), .ZN(n52) );
  NAND2_X1 U308 ( .A1(n158), .A2(u2_output_matrix[2]), .ZN(n273) );
  NAND2_X1 U309 ( .A1(n274), .A2(n273), .ZN(n50) );
  NAND2_X1 U310 ( .A1(n276), .A2(u2_output_matrix[3]), .ZN(n277) );
  NAND2_X1 U311 ( .A1(n278), .A2(n277), .ZN(n49) );
  NAND2_X1 U312 ( .A1(n283), .A2(u2_output_matrix[1]), .ZN(n284) );
  NAND2_X1 U313 ( .A1(n285), .A2(n284), .ZN(n51) );
  NAND3_X1 U314 ( .A1(n299), .A2(u1_current_state[1]), .A3(n298), .ZN(n292) );
  MUX2_X1 U315 ( .A(n300), .B(u1_current_state[0]), .S(u1_current_state[1]), 
        .Z(n288) );
  INV_X1 U316 ( .A(n286), .ZN(n287) );
  NAND3_X1 U317 ( .A1(dut_run), .A2(n300), .A3(n299), .ZN(n289) );
  NAND3_X1 U318 ( .A1(n300), .A2(n299), .A3(u1_current_state[1]), .ZN(n291) );
  NAND3_X1 U319 ( .A1(n158), .A2(n289), .A3(n291), .ZN(u1_next_state_0_) );
  NAND2_X1 U320 ( .A1(n291), .A2(n290), .ZN(n53) );
endmodule

