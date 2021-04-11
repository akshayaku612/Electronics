//Declare the ports of Half adder module
module half_adder(A, B, S, C);

    //input ports.
    input A;
    input B;
    
    //output ports.
    output S;
    output C;

     //Implement the Sum and Carry equations using Structural verilog
     xor x1(S,A,B); //XOR operation (S is output not a input)
     and a1(C,A,B); //AND operation 
 endmodule

//Declare the ports for the full adder module
module full_adder( A, B, Cin, S, Cout); // (Port names)

    //input ports.
    input A;
    input B;
    input Cin;

    //output ports.
    output S;
    output Cout;

    wire Sa1, Ca1, Ca2;    
     //Two instances of half adders used to make a full adder
     half_adder a1(.A(A),.B(B),.S(Sa1),.C(Ca1));
     half_adder a2(.A(Sa1),.B(Cin),.S(S),.C(Ca2));
     or  o1(Cout,Ca1,Ca2);
 endmodule

module my32bitadder(output [31:0] O, output c, input [31:0] A, B, input S);
//wires for connecting output to input
	wire Cout0in1, Cout1in2, Cout2in3, Cout3in4, Cout4in5, Cout5in6, Cout6in7, Cout7in8,
 	Cout8in9, Cout9in10, Cout10in11, Cout11in12, Cout12in13, Cout13in14, Cout14in15, Cout15in16, Cout16in17, Cout17in18, Cout18in19, Cout19in20, Cout20in21,Cout21in22,Cout22in23, Cout23in24, Cout24in25, Cout25in26, Cout26in27, Cout27in28, Cout28in29, Cout29in30, Cout30in31;

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
        full_adder Add15 ( A[15], B[15], Cout14in15, O[15], Cout15in16); 
	full_adder Add16 ( A[16], B[16], Cout15in16, O[16], Cout16in17);
	full_adder Add17 ( A[17], B[17], Cout16in17, O[17], Cout17in18); 
	full_adder Add18 ( A[18], B[18], Cout17in18, O[18], Cout18in19); 
	full_adder Add19 ( A[19], B[19], Cout18in19, O[19], Cout19in20);
        full_adder Add20 ( A[20], B[20], Cout19in20, O[20], Cout20in21); 
	full_adder Add21 ( A[21], B[21], Cout20in21, O[21], Cout21in22);
	full_adder Add22 ( A[22], B[22], Cout21in22, O[22], Cout22in23); 
	full_adder Add23 ( A[23], B[23], Cout22in23, O[23], Cout23in24); 
	full_adder Add24 ( A[24], B[24], Cout23in24, O[24], Cout24in25);
        full_adder Add25 ( A[25], B[25], Cout24in25, O[25], Cout25in26); 
	full_adder Add26 ( A[26], B[26], Cout25in26, O[26], Cout26in27);
	full_adder Add27 ( A[27], B[27], Cout26in27, O[27], Cout27in28); 
	full_adder Add28 ( A[28], B[28], Cout27in28, O[28], Cout28in29); 
	full_adder Add29 ( A[29], B[29], Cout28in29, O[29], Cout29in30);   
	full_adder Add30 ( A[30], B[30], Cout29in30, O[30], Cout30in31);
        full_adder Add31 ( A[31], B[31], Cout30in31, O[31], c);
endmodule

module myexp(output reg[31:0] O, output reg Done, output Cout, input [15:0] A, B, input Load,Clk,Reset,Cin);
reg[1:0] state;
reg[31:0] A_reg, B_reg, A_temp, O_reg, B_temp, Exp_reg;
wire[31:0] O_temp;

my32bitadder dut1(O_temp, Cout, A_temp, B_temp, Cin);

always@(posedge Clk)
begin
if(Reset)
state <= 0;
else
case(state)
	0: if(Load)begin
		A_reg <= A; 
		B_reg <= A; 
		O_reg <= A; 
                Exp_reg<=B;
		state <= 1;
                Done <= 0;
                O <= 0;
		end
	1: begin
		if (Exp_reg > 1) 
			begin
			A_temp <= A_reg; 
			B_temp <= O_reg; 
			B_reg <= B_reg - 1; 
			state <= 2;
			end
		else    begin
			state <= 3; 
			Done <= 1;
			O <= O_temp;
			end
           end
	2: begin
		O_reg <= O_temp;
		if(B_reg > 1 && Exp_reg > 1) 
			state <= 1;
		else if ((B_reg == 1 || B_reg < 1) && Exp_reg > 1)
			begin
			A_reg <= O_temp; 
			B_reg <= A;
			Exp_reg <= Exp_reg - 1;
			state <= 1; 
			end
	   end
	3: begin
		Done <= 1; 
		state <= 0;
		end

endcase
end
endmodule



//Declare the ports of Half adder module
module fullsubtractor( input [15:0] x,input [15:0] y,output [15:0] O);

assign O =   y -  x;
 
endmodule

module mymodfunc(output reg[15:0] O, output reg Done, output Cout, input [15:0] A, B, input Load,Clk,Reset,Cin);
reg[1:0] state;
reg[15:0] A_reg, B_reg, A_temp, O_reg, B_temp;
wire[15:0] O_temp;

fullsubtractor dut1(B_temp,A_temp,O_temp);

always@(posedge Clk)
begin
if(Reset)
state <= 0;
else
case(state)
	0: if(Load)begin
		A_reg <= A;  
		O_reg <= A;
                B_reg <=B; 
		state <= 1;
                Done <= 0;
                O <= 0;
		end
	1: begin
		A_temp <= O_reg; 
		B_temp <= B_reg;  
		state <= 2;
		end
	2: begin
		O_reg <= O_temp;
		if(O_temp>B) state <= 1;
		else begin
			state <= 3; 
			Done <= 1;
			O <= O_temp;
			end
		end
	3: begin
		Done <= 1; 
		state <= 0;
		end

endcase
end
endmodule

module proj2(input [15:0] private_key, input [15:0] public_key, input [15:0] message_val, input clk, input Start, input Rst, output reg [15:0] Cal_val, reg Cal_done);
reg exp_Rst, mod_Rst, load_exp, load_mod, cin;
reg [31:0] message1, private1;
reg [15:0] public1;
wire myexp_done,mymod_done, exp_cout, mod_cout;
wire[31:0] exp_output;
wire[15:0] mod_output;
reg [3:0] state;
initial begin
cin<= 0;
end
myexp dut1(exp_output, myexp_done, exp_cout, message1, private1, load_exp, clk, exp_Rst, cin);
mymodfunc dut2(mod_output, mymod_done, mod_cout, exp_output[15:0], public1, load_mod, clk, mod_Rst, cin);

parameter Capture_state = 4'b0000;
parameter Exponent_state1 = 4'b0001;
parameter Exponent_state2 = 4'b0010;
parameter Exponent_state3 = 4'b0011;
parameter Mod_state1 = 4'b0100;
parameter Mod_state2 = 4'b0101;
parameter Mod_state3 = 4'b0110;
parameter Cal_done_state1 = 4'b0111;
parameter Cal_done_state2 = 4'b1000;
parameter Cal_done_state3 = 4'b1001;

always @(posedge clk) 
begin
if (Rst) begin
message1<=0;
private1<=0;
load_exp<=0;
exp_Rst<=0;
public1<=0;
load_mod<=0;
mod_Rst<=0;
Cal_val<=0;
Cal_done<=0;
state<=0;
end

else begin

case(state)

Capture_state: begin
if (Start) begin
Cal_done<=0;
private1<=private_key;
public1<=public_key;
message1<=message_val;
state<=Exponent_state1;
exp_Rst <= 1;
mod_Rst <= 1;
end
else state<=Capture_state;
end

Exponent_state1: begin
load_exp<=1;
exp_Rst<=0;
state <=Exponent_state2;
end

Exponent_state2: begin
load_exp<=0;
state<=Exponent_state3;
end

Exponent_state3: begin
if (myexp_done) begin 
state<=Mod_state1;
mod_Rst<=1;
end
else state<=Exponent_state2;
end

Mod_state1: begin
mod_Rst<=0;
load_mod<=1;
state<=Mod_state2;
end

Mod_state2: begin
load_mod<=0;
state<=Mod_state3;
end

Mod_state3: begin
if (mymod_done) begin
state<=Cal_done_state1;
end
else state<=Mod_state2;
end

Cal_done_state1: begin
Cal_val<=mod_output;
Cal_done<=1;
state<=Cal_done_state2;
end

Cal_done_state2: begin
state<=Cal_done_state3;
end

Cal_done_state3: begin
state<=Capture_state;
end

endcase
end
end
endmodule


module proj2_tb();
reg clk, Rst, Start;
wire Cal_done;
reg [15:0]private_key, public_key, message_val;
wire [15:0]Cal_val;

always@(proj2_tb.dut.state) begin
case(proj2_tb.dut.state)
 4'b0000: $display ($time,"Capture_state");
 4'b0001: $display ($time,"Exponent_state1");
 4'b0010: $display ($time,"Exponent_state2");
 4'b0011: $display ($time,"Exponent_state3");
4'b0100: $display ($time,"Mod_state1");
4'b0101: $display ($time,"Mod_state2");
4'b0110: $display ($time,"Mod_state3");
4'b0111: $display ($time,"Cal_done_state1");
4'b1000: $display ($time,"Cal_done_state2");
4'b1001: $display ($time,"Cal_done_state3");
default: $display($time,"Unrecognized State");
endcase
Start = 0;
end


always #5 clk = ~clk;

   initial 
   begin
   
   clk = 0;
   Rst = 0;
   #5 Rst = 1; #6 Rst = 0; Start = 1;
   message_val = 16'd9; private_key = 16'd3; public_key = 16'd33;
   #10000 $display ("Encryption \nC = %0d^%0d mod %0d = %0d\n\n", message_val, private_key, public_key, Cal_val);
   #10000 $display ("Inputs\nMessage:\t%0d\nPrivate key:\t%0d\nPublic key:\t%0d\n\nOutput=%0d\n",message_val,private_key,public_key,Cal_val);
   #5 Start = 0;
$finish;

   end 

proj2 dut(private_key, public_key, message_val, clk, Start,Rst, Cal_val, Cal_done);
endmodule
