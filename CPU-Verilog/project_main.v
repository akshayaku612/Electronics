//Declare the ports of Half adder module
module half_adder(A, B, S, C);
    //what are the input ports.
    input A;
    input B;
    //What are the output ports.
    output S;
    output C;
    //reg S,C; NOT NEEDED will cause error
     //Implement the Sum and Carry equations using Structural verilog
     xor x1(S,A,B); //XOR operation (S is output not a input)
     and a1(C,A,B); //AND operation 
 endmodule

//Declare the ports for the full adder module
module full_adder( A, B, Cin, S, Cout); // (Port names)

    //what are the input ports.
    input A;
    input B;
    input Cin;

    //What are the output ports.
    output S;
    output Cout;
    //reg  A,B,Cin; //(Doesn't need to be reg, it will cause an error
    wire Sa1, Ca1, Ca2;    
     //Two instances of half adders used to make a full adder
     half_adder a1(.A(A),.B(B),.S(Sa1),.C(Ca1)); //S to Sa1 to match diagram
     half_adder a2(.A(Sa1),.B(Cin),.S(S),.C(Ca2));
     or  o1(Cout,Ca1,Ca2);
 endmodule

module my16bitadder(output [15:0] O, output c, input [15:0] A, B, input S);
//wires for connecting output to input
	wire Cout0in1, Cout1in2, Cout2in3, Cout3in4, Cout4in5, Cout5in6, Cout6in7, Cout7in8,
 	Cout8in9, Cout9in10, Cout10in11, Cout11in12, Cout12in13, Cout13in14, Cout14in15;

	full_adder Add0 ( A[0], B[0], S, O[0], Cout0in1); 
	full_adder Add1 ( A[1], B[1], Cout0in1, O[1], Cout1in2); 
	full_adder Add2 ( A[2], B[2], Cout1in2, O[2], Cout2in3); 
	full_adder Add3 ( A[3], B[3], Cout2in3, O[3], Cout3in4); 
	full_adder Add4 ( A[4], B[4], Cout3in4, O[4], Cout4in5); 
	full_adder Add5 ( A[5], B[5], Cout4in5, O[5], Cout5in6); 
	full_adder Add6 ( A[6], B[6], Cout5in6, O[6], Cout6in7); 
	full_adder Add7 ( A[7], B[7], Cout6in7, O[7], Cout7in8); 
	full_adder Add8 ( A[8], B[8], Cout7in8, O[8], Cout8in9); 
	full_adder Add9 ( A[9], B[9], Cout8in9, O[9], Cout9in10); 
	full_adder Add10 ( A[10], B[10], Cout9in10, O[10], Cout10in11); 
	full_adder Add11 ( A[11], B[11], Cout10in11, O[11], Cout11in12);
	full_adder Add12 ( A[12], B[12], Cout11in12, O[12], Cout12in13); 
	full_adder Add13 ( A[13], B[13], Cout12in13, O[13], Cout13in14); 
	full_adder Add14 ( A[14], B[14], Cout13in14, O[14], Cout14in15);  
	full_adder Add15 ( A[15], B[15], Cout14in15, O[15], c);
endmodule

module my8bitmultiplier(output reg[15:0] O, output reg Done, output Cout, input [7:0] A, B, input Load,Clk,Reset,Cin);
reg[1:0] state;
reg[15:0] A_reg, B_reg, A_temp, O_reg, B_temp;
wire[15:0] O_temp;

my16bitadder dut1(O_temp, Cout, A_temp, B_temp, Cin);

always@(posedge Clk)
begin
if(Reset)
state <= 0;
else
case(state)
	0: if(Load)begin
		A_reg <= A; 
		B_reg <= B; 
		O_reg <= A; 
		state <= 1;
                Done <= 0;
                O <= 0;
		end
	1: begin
		A_temp <= A_reg; 
		B_temp <= O_reg; 
		B_reg <= B_reg - 1; 
		state <= 2;
		end
	2: begin
		O_reg <= O_temp;
		if(B_reg>1) state <= 1;
		else begin
			state <= 3; 
			Done <= 1;
			O <= O_temp;
			end
		end
	3: begin
		Done <= 0; 
		state <= 0;
		end

endcase
end
endmodule


module  ram(we, d, q, addr);
input we;
input [15:0] d;
input [7:0] addr;
output reg [15:0] q;

reg [15:0] mem[0:255];
always@(*)
begin
case(we)
    1: mem[addr] <= d;
    0: q<= mem[addr];
    endcase
end
endmodule 

//input clk;
//output reg[15:0] Mul;
module alu(A, B, opALU, Rout);
input [15:0] A;
input [15:0] B;
input [1:0] opALU;
output reg [15:0] Rout;

my16bitadder add (O, M, A, B, S);
my8bitmultiplier dut(Mul, done, cout, A [7:0] , B [7:0], 0, clk, reset1, 0);

always @(*)
begin
case(opALU)
2'b00: Rout <= A|B;
2'b01: Rout <= O;
2'b10: Rout <= Mul;
2'b11: Rout <= ~A;
endcase
end

endmodule

/*module ctr (clk, rst, zflag, opcode, muxPC, muxMAR, muxACC, loadMAR, loadPC, loadACC, loadMDR, loadIR, opALU, MemRW, reset1, load1, ovr);
   input clk;
   input rst;
   input zflag;
   output reg load1;
   output reg reset1;
   input ovr;
   input [7:0]opcode;
   output reg muxPC;
   output reg muxMAR;
   output reg muxACC;
   output reg loadMAR;
   output reg loadPC;
   output reg loadACC;
   output reg loadMDR;
   output reg loadIR;
   output reg opALU;
   output reg MemRW;  
   reg [4:0] state1, state2;
   
parameter op_add=8'b001;
parameter op_or= 8'b010;
parameter op_jump=8'b011;
parameter op_jumpz=8'b100;
parameter op_load=8'b101;
parameter op_store=8'b110;
parameter op_mull=8'b1001;
parameter op_neg=8'b1010;

parameter Fetch_1=4'b0001, Fetch_2=4'b0010, Fetch_3=4'b0011, Decode=4'b0100, ExecADD_1=4'b0101, ExecADD_2=4'b0110, ExecOR_1=4'b0111, 
	ExecOR_2=4'b1000, ExecLoad_1=4'b1001, ExecLoad_2=4'b1010,ExecStore_1=4'b1011, ExecJump=4'b1100, Mull1=4'b1101, Mull2=4'b1110, Mull3=4'b1111;

always@(posedge clk)
begin
 if (rst) begin
	state1 <= Fetch_1;
	muxPC<= 0;
	muxMAR<= 0;
	muxACC<=0;
	loadMAR<=0;
	loadPC<=0;
	loadACC<=0;
	loadMDR<=0;
	loadIR<=0;
	opALU<=0;
	MemRW<=0; reset1<= 0; load1 <=0; end
	
 else begin
   	state1 <= state2;
	muxPC<=0;
	muxMAR<=0;
	muxACC<=0;
	loadMAR<=0;
	loadPC<=0;
	loadACC<=0;
	loadMDR<=0;
	loadIR<=0;
	opALU<=0;
	MemRW<=0; reset1<= 0; load1 <=0;
end
end

always@(*) begin
case(state1)

Fetch_1: begin
muxMAR<=0;
muxPC<=0; 
muxACC<=0; 
loadPC<=1;
loadMAR<=1;
loadMDR<=0;
loadIR<=0; 
loadACC<=0;
opALU<=0;
MemRW<=0;
reset1<= 0;
load1 <=0;
state2<=Fetch_2; 
end

Fetch_2: begin
muxMAR<=0;
muxPC<=0; muxACC<=0;
loadPC<=0; loadMAR<=0;
loadMDR<=1;
loadIR<=0; 
loadACC<=0;
opALU<=0;
MemRW<=0; reset1<= 0;
load1 <=0;
state2<=Fetch_3;
end

Fetch_3: begin
muxMAR<=0;
muxPC<=0;
muxACC<=0;
loadPC<=0; 
loadMAR<=0;
loadMDR<=0;loadIR<=1; 
loadACC<=0;
opALU<=0;
MemRW<=0; 
reset1<= 0;
load1 <=0;
state2<=Decode;
end


Mull1: begin
reset1 <= 1;
load1 <=0; 
muxMAR<=0; 
muxPC<=0; 
muxACC<=0; 
loadPC<=0; 
loadMAR<=0;
loadMDR<=1;
loadIR<=0; 
loadACC<=0;
opALU<=0; 
MemRW<=0;
state2<=Mull2;
end

Mull2: begin
reset1 <=0;
load1 <=1; 
muxMAR<=0;
muxPC<=0;
muxACC<=0;
loadPC<=0;
loadMAR<=0;
loadMDR<=0;
loadIR<=0; 
loadACC<=1;
opALU<=0; 
MemRW<=0;
state2<=Mull3;
end

Mull3: begin
load1 <=0;
muxMAR<=0;
muxPC<=0;
muxACC<=2;
loadPC<=0;
loadMAR<=0;
loadMDR<=0; 
loadIR<=0; 
loadACC<=0;
opALU<=0;
MemRW<=0;

if(ovr) begin
loadACC<=1;
state2<= Fetch_1;end
else
state2<= Mull3;
end

ExecADD_1: begin
muxMAR<=0;
muxPC<=0; 
muxACC<=0;
loadPC<=0;
loadMAR<=0;
loadMDR<=1; 
loadIR<=0;
loadACC<=0;
opALU<=0; 
MemRW<=0; 
reset1<= 0; 
load1 <=0;
state2<=ExecADD_2;
end

ExecOR_1: begin
muxMAR<=0;
muxPC<=0; muxACC<=0;
loadPC<=0;
loadMAR<=0;
loadMDR<=1;
loadIR<=0; 
loadACC<=0; 
opALU<=0; 
MemRW<=0; 
reset1<= 0; 
load1 <=0;
state2 <= ExecOR_2;
end

Decode: begin
muxMAR<=1;
muxPC<=0; muxACC<=0; 
loadPC<=0; 
loadMAR<=1;
loadMDR<=0;
loadIR<=0;
loadACC<=0;
opALU<=0;
MemRW<=0; 
reset1<= 0; 
load1 <=0;
if(opcode==op_add)
state2<=ExecADD_1;
else if(opcode==op_or)
state2<=ExecOR_1;
else if(opcode==op_load)
state2<=ExecLoad_1;
else if(opcode==op_store)
state2<=ExecStore_1;
else if((opcode==op_jump) | (opcode==op_jumpz & zflag))
state2<=ExecJump;
else if(opcode==op_jumpz & !zflag)
state2<=Fetch_1;
else if(opcode==op_mull)
state2<=Mull1;
else
state2<=Fetch_1;
end

ExecOR_2: begin
muxMAR<=0;
muxPC<=0;
muxACC<=0; loadPC<=0;
loadMAR<=0;
loadMDR<=0;
loadIR<=0; 
loadACC<=1;
opALU<=0; MemRW<=0;
reset1<= 0;
load1 <=0;
state2 <= Fetch_1;
end

ExecADD_2: begin
muxMAR<=0; 
muxPC<=0;
muxACC<=0;
loadPC<=0;
loadMAR<=0;
loadMDR<=0; 
loadIR<=0; 
loadACC<=1; 
opALU<=1; 
MemRW<=0; 
reset1<= 0; 
load1 <=0;
state2 <= Fetch_1;
end

ExecLoad_1: begin
muxMAR<=0;
muxPC<=0;
muxACC<=0;
loadPC<=0; loadMAR<=0;
loadMDR<=1;
loadIR<=0; 
loadACC<=0; 
opALU<=0; 
MemRW<=0; 
reset1<= 0; 
load1 <=0;
state2 <= ExecLoad_2;
end

ExecLoad_2: begin
muxMAR<=0;
muxPC<=0;
muxACC<=1;
loadPC<=0;
loadMAR<=0;
loadMDR<=0;
loadIR<=0; 
loadACC<=1;
opALU<=0; 
MemRW<=0; 
reset1<= 0;
load1 <=0;
state2 <= Fetch_1;
end

ExecJump: begin
muxMAR<=0;
muxPC<=1;
muxACC<=0;
loadPC<=1;
loadMAR<=0;
loadMDR<=0; 
loadIR<=0;
loadACC<=0;
opALU<=0;
MemRW<=0;
reset1<= 0; load1 <=0;
state2 <= Fetch_1;
end

ExecStore_1: begin
muxMAR<=0; 
muxPC<=0;
muxACC<=0;
loadPC<=0; loadMAR<=0;
loadMDR<=0;
loadIR<=0; 
loadACC<=0;
opALU<=0; 
MemRW<=1; 
reset1<= 0; 
load1 <=0;
state2 <= Fetch_1;
end

default: begin
muxMAR<=0;
muxPC<=0;
muxACC<=0;
loadPC<=0; 
loadMAR<=0; 
loadMDR<=0;
loadIR<=0; 
loadACC<=0; 
opALU<=0; 
MemRW<=0; 
reset1<= 0; 
load1 <=0;
state2 <= Fetch_1;
end
endcase
end



endmodule

*/
module ctr (clk, rst, zflag, opcode, muxPC, muxMAR, muxACC, loadMAR, loadPC, loadACC, loadMDR, loadIR, opALU, MemRW, rst2, ld, Done);
   input clk;
   input rst;
   input zflag;
   output reg ld;
   output reg rst2;
   input Done;
   input [7:0]opcode;
   output reg muxPC;
   output reg muxMAR;
   output reg muxACC;
   output reg loadMAR;
   output reg loadPC;
   output reg loadACC;
   output reg loadMDR;
   output reg loadIR;
   output reg opALU;
   output reg MemRW;  
   reg [4:0] pstate, nstate;
   

//These opcode representation need to be followed for proper operation
parameter op_add=8'b001;
parameter op_or= 8'b010;
parameter op_jump=8'b011;
parameter op_jumpz=8'b100;
parameter op_load=8'b101;
parameter op_store=8'b110;
parameter op_mult=8'b1001;

parameter Fetch_1=4'b0001, Fetch_2=4'b0010, Fetch_3=4'b0011, Decode=4'b0100, ExecADD_1=4'b0101, ExecADD_2=4'b0110, ExecOR_1=4'b0111, 
	ExecOR_2=4'b1000, ExecLoad_1=4'b1001, ExecLoad_2=4'b1010,ExecStore_1=4'b1011, ExecJump=4'b1100, Mult_1=4'b1101, Mult_2=4'b1110, Mult_3=4'b1111;

always@(posedge clk)
begin
 if (rst) begin
	pstate <= Fetch_1;
	muxPC<= 0;
	muxMAR<= 0;
	muxACC<=0;
	loadMAR<=0;
	loadPC<=0;
	loadACC<=0;
	loadMDR<=0;
	loadIR<=0;
	opALU<=0;
	MemRW<=0; rst2<= 0; ld <=0; end
	
 else begin
   	pstate <= nstate;
	muxPC<=0;
	muxMAR<=0;
	muxACC<=0;
	loadMAR<=0;
	loadPC<=0;
	loadACC<=0;
	loadMDR<=0;
	loadIR<=0;
	opALU<=0;
	MemRW<=0; rst2<= 0; ld <=0;
end

case(pstate)

Fetch_1: begin
muxMAR<=0;
 muxPC<=0; 
muxACC<=0; 
loadPC<=1;
 loadMAR<=1;
 loadMDR<=0;
 loadIR<=0; 
loadACC<=0;
 opALU<=0;
 MemRW<=0;
 rst2<= 0;
 ld <=0;
nstate<=Fetch_2; 
end

Fetch_2: begin
muxMAR<=0;
 muxPC<=0;
 muxACC<=0;
 loadPC<=0;
 loadMAR<=0;
 loadMDR<=1;
 loadIR<=0; 
loadACC<=0;
 opALU<=0;
 MemRW<=0;
 rst2<= 0;
 ld <=0;
nstate<=Fetch_3;
end

Fetch_3: begin
muxMAR<=0;
 muxPC<=0;
 muxACC<=0;
 loadPC<=0; 
loadMAR<=0;
 loadMDR<=0;
 loadIR<=1; 
loadACC<=0;
 opALU<=0;
 MemRW<=0; 
rst2<= 0;
 ld <=0;
nstate<=Decode;
end

Decode: begin
muxMAR<=1;
 muxPC<=0;
 muxACC<=0; 
loadPC<=0; 
loadMAR<=1;
 loadMDR<=0;
 loadIR<=0;
 loadACC<=0;
 opALU<=0;
 MemRW<=0; 
rst2<= 0; 
ld <=0;
if(opcode==op_add)
nstate<=ExecADD_1;
else if(opcode==op_or)
nstate<=ExecOR_1;
else if(opcode==op_load)
nstate<=ExecLoad_1;
else if(opcode==op_store)
nstate<=ExecStore_1;
else if((opcode==op_jump) | (opcode==op_jumpz & zflag))
nstate<=ExecJump;
else if(opcode==op_jumpz & !zflag)
nstate<=Fetch_1;
else if(opcode==op_mult)
nstate<=Mult_1;
else
nstate<=Fetch_1;
end


Mult_1: begin
rst2 <= 1;
 ld <=0; 
 muxMAR<=0; 
muxPC<=0; muxACC<=0; 
loadPC<=0; 
loadMAR<=0;
 loadMDR<=1;
 loadIR<=0; 
loadACC<=0;
 opALU<=0; 
MemRW<=0;
nstate<=Mult_2;
end
Mult_2: begin
rst2 <=0;
 ld <=1; 
  muxMAR<=0;
 muxPC<=0;
 muxACC<=0;
 loadPC<=0;
 loadMAR<=0;
 loadMDR<=0;
 loadIR<=0; 
loadACC<=1;
 opALU<=0; 
MemRW<=0;
nstate<=Mult_3;
end
Mult_3: begin
ld <=0;
 muxMAR<=0;
 muxPC<=0;
 muxACC<=2;
 loadPC<=0;
 loadMAR<=0;
 loadMDR<=0; 
loadIR<=0; 
loadACC<=0;
 opALU<=0;
 MemRW<=0;
if(Done) begin
loadACC<=1;
nstate<= Fetch_1;end
else
nstate<= Mult_3;
end

ExecADD_1: begin
muxMAR<=0;
 muxPC<=0; 
muxACC<=0;
 loadPC<=0;
 loadMAR<=0;
 loadMDR<=1; 
loadIR<=0;
 loadACC<=0;
 opALU<=0; 
MemRW<=0; 
rst2<= 0; 
ld <=0;
nstate<=ExecADD_2;
end

ExecADD_2: begin
muxMAR<=0; 
muxPC<=0;
 muxACC<=0;
 loadPC<=0;
 loadMAR<=0;
 loadMDR<=0; 
loadIR<=0; 
loadACC<=1; 
opALU<=1; 
MemRW<=0; 
rst2<= 0; 
ld <=0;
nstate <= Fetch_1;
end

ExecOR_1: begin
muxMAR<=0;
 muxPC<=0;
 muxACC<=0;
 loadPC<=0;
 loadMAR<=0;
 loadMDR<=1;
 loadIR<=0; 
loadACC<=0; 
opALU<=0; 
MemRW<=0; 
rst2<= 0; 
ld <=0;
nstate <= ExecOR_2;
end

ExecOR_2: begin
muxMAR<=0;
 muxPC<=0;
 muxACC<=0;
 loadPC<=0;
 loadMAR<=0;
 loadMDR<=0;
 loadIR<=0; 
loadACC<=1;
 opALU<=0;
 MemRW<=0;
 rst2<= 0;
 ld <=0;
nstate <= Fetch_1;
end

ExecLoad_1: begin
muxMAR<=0;
 muxPC<=0;
 muxACC<=0;
 loadPC<=0;
 loadMAR<=0;
 loadMDR<=1;
 loadIR<=0; 
loadACC<=0; 
opALU<=0; 
MemRW<=0; 
rst2<= 0; 
ld <=0;
nstate <= ExecLoad_2;
end

ExecLoad_2: begin
muxMAR<=0;
 muxPC<=0;
 muxACC<=1;
 loadPC<=0;
 loadMAR<=0;
 loadMDR<=0;
 loadIR<=0; 
loadACC<=1;
 opALU<=0; 
MemRW<=0; 
rst2<= 0;
 ld <=0;
nstate <= Fetch_1;
end

ExecStore_1: begin
muxMAR<=0; 
muxPC<=0;
 muxACC<=0;
 loadPC<=0;
 loadMAR<=0;
 loadMDR<=0;
 loadIR<=0; 
loadACC<=0;
 opALU<=0; 
MemRW<=1; 
rst2<= 0; 
ld <=0;
nstate <= Fetch_1;
end

ExecJump: begin
muxMAR<=0;
 muxPC<=1;
 muxACC<=0;
 loadPC<=1;
 loadMAR<=0;
 loadMDR<=0; 
loadIR<=0;
 loadACC<=0;
 opALU<=0;
 MemRW<=0;
 rst2<= 0; ld <=0;
nstate <= Fetch_1;
end

default: begin
muxMAR<=0;
 muxPC<=0;
 muxACC<=0;
 loadPC<=0; 
loadMAR<=0; 
loadMDR<=0;
 loadIR<=0; 
loadACC<=0; 
opALU<=0; 
MemRW<=0; 
rst2<= 0; 
ld <=0;
nstate <= Fetch_1;
end
endcase
end



endmodule



module registers(clk, rst, PC_reg, PC_next, IR_reg, IR_next, ACC_reg, ACC_next, MDR_reg, MDR_next, MAR_reg, MAR_next, Zflag_reg, zflag_next);

input wire clk;
input wire rst;
output reg  [7:0]PC_reg; 
input wire  [7:0]PC_next;
input wire  [7:0]MAR_next;  
output reg Zflag_reg;
input wire  [15:0]ACC_next;  
output reg  [15:0]MDR_reg;  
output reg  [15:0]IR_reg;  
input wire  [15:0]IR_next;  
output reg  [15:0]ACC_reg;  
input wire  [15:0]MDR_next;  
output reg  [7:0]MAR_reg;  
input wire zflag_next;

always@(posedge clk)
begin
if(rst)begin 
PC_reg <= 0;
IR_reg <= 0;
ACC_reg <= 0;
MDR_reg <= 0;
MAR_reg <= 0;
Zflag_reg <= 0;
end
else begin
PC_reg <= PC_next;
IR_reg <= IR_next;
ACC_reg <= ACC_next;
MDR_reg <= MDR_next;
MAR_reg <= MAR_next;
Zflag_reg <= zflag_next;
end
end

endmodule

module datapath(clk, rst, muxPC, muxMAR, muxACC, loadMAR, loadPC, loadACC, loadMDR, loadIR, opALU, zflag, opcode, MemAddr, MemD, MemoA2, reset1, load1, ovr);
input clk;
input  rst;
input  muxPC;
input  muxMAR;
input  muxACC;
input  loadMAR;
input  loadPC;
input  loadACC;
input  loadMDR;
input  loadIR;
input  opALU;
input reset1;
input load1;
output ovr;
output   zflag; output   [7:0]opcode;
output   [7:0]MemAddr;
output   [15:0]MemD;
input   [15:0]MemoA2;

reg  [7:0]PC_next;
reg  [15:0]IR_next;  
reg  [15:0]ACC_next;  
reg  [15:0]MDR_next;  
reg  [7:0]MAR_next;  
reg zflag_next;

wire  [7:0]PC_reg;
wire  [15:0]IR_reg;  
wire  [15:0]ACC_reg;  
wire  [15:0]MDR_reg;  
wire  [7:0]MAR_reg;  
wire zflag_reg;

wire  [15:0]ALU_out; 
wire [15:0]out; 
//wire[15:0] Mul;

alu inst1(ACC_reg, MDR_reg, opALU, ALU_out);
registers inst2(clk, rst, PC_reg, PC_next, IR_reg, IR_next, ACC_reg, ACC_next, MDR_reg, MDR_next, MAR_reg, MAR_next, Zflag_reg, zflag_next);
//my8bitmultiplier dut(Mul, Done, Cout, MDR_reg , ACC_reg, Load, clk, reset1, Cin);

always@(*)begin
if(loadPC)begin
if(muxPC)
PC_next <=  IR_reg[15:8]; 
else
PC_next <=  PC_reg + 1;
end
else
PC_next <= PC_reg;

if(loadMAR)begin
if(muxMAR)
MAR_next <= IR_reg[15:8];
else
MAR_next <= PC_reg  ;
end
else
MAR_next <= MAR_reg;

if(loadMDR)
MDR_next <= MemoA2;
else
MDR_next<= MDR_reg;


if(loadIR)
IR_next <= MDR_reg;
else
IR_next<=IR_reg;

if(loadACC)begin
if(muxACC==1)
ACC_next <= MDR_reg;
else if(muxACC==2)
ACC_next <= out;
else
ACC_next <= ALU_out;
end
else ACC_next <= ACC_reg;

if(ACC_reg==0)
zflag_next <= 1;
else
zflag_next <= 0;
end

assign zflag= zflag_next;
assign opcode = IR_reg[7:0];
assign MemAddr = MAR_reg;
assign MemD = ACC_reg;
endmodule

module proj1(clk, rst, MemRW_IO, MemAddr_IO, MemD_IO);   
   input clk;
   input rst;
   output MemRW_IO;
   output [7:0]MemAddr_IO;
   output [15:0]MemD_IO;
 
   wire zin;
   wire muxPC_in;
   wire muxMAR_in;
   wire muxACC_in;
   wire [7:0]op_in;
   wire muxPC_out;
   wire muxMAR_out;
   wire muxACC_out;
   wire loadMAR_out;
   wire loadPC_out;
   wire loadACC_out;
   wire loadMDR_out;
   wire loadIR_out;
   wire opALU_out;
   wire MemRW_out;
   wire in; 
   wire [15:0] a1;
   wire [7:0] addr;
   wire [15:0] a2;


   wire loadMAR_in;
   wire loadPC_in;
   wire loadACC_in;
   wire loadMDR_in;
   wire loadIR_in;
   wire opALU_in; 
   wire zflag_out;
   wire [7:0]opcode_output;
   wire [7:0]MemAddr;
   wire [15:0]MemD;
   wire [15:0]MemoA2;

ram inst3(in, a1, a2, addr);
ctr inst4(clk, rst, zin, op_in, muxPC_out, muxMAR_out, muxACC_out, loadMAR_out, loadPC_out, loadACC_out, loadMDR_out, loadIR_out, opALU_out, MemRW_out, reset1, load1, ovr);
datapath inst5(clk, rst, muxPC_in, muxMAR_in, muxACC_in, loadMAR_in, loadPC_in, loadACC_in, loadMDR_in, loadIR_in, opALU_in, zflag_out, opcode_output, MemAddr, MemD, MemoA2, reset1, load1,
 	ovr);

 assign a1 = MemD;
 assign addr = MemAddr;
 assign in = MemRW_out;
 assign muxPC_in = muxPC_out; 
 assign muxMAR_in = muxMAR_out;
 assign muxACC_in = muxACC_out;
 assign loadMAR_in = loadMAR_out;
 assign loadPC_in = loadPC_out;
 assign loadACC_in = loadACC_out;
 assign loadMDR_in = loadMDR_out;
 assign loadIR_in = loadIR_out;
 assign opALU_in = opALU_out;
 assign zin = zflag_out;
 assign op_in = opcode_output;
 assign MemAddr_IO = MemAddr;
 assign MemD_IO = MemD;
 assign MemoA2 = a2;
 assign MemRW_IO = MemRW_out;

endmodule

module proj1_tb;
	reg clk;
	reg rst;
	wire MemRW_IO;
	wire [7:0]MemAddr_IO;
	wire [15:0]MemD_IO;

always 
begin
      #5  clk = !clk;
end
		
initial 
begin
	clk=1'b0;
	rst=1'b1;
	$readmemh("memory.list", proj1_tb.dut.inst3.mem);
	#20 rst=1'b0;
	#435
	$display("Final value\n");
	$display("0x000e %d\n", proj1_tb.dut.inst3.mem[16'h000d]);
	$finish;
end

proj1 dut(clk, rst, MemRW_IO, MemAddr_IO, MemD_IO);	   

endmodule