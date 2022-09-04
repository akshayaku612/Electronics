//Top-level module
module MyDesign(clk, reset_b, dut_run, dut_busy, sram_dut_read_data, dut_sram_read_address, wmem_dut_read_data, dut_wmem_read_address, dut_sram_write_address,dut_sram_write_data, dut_sram_write_enable);

//input nets
input clk;
input reset_b;
input dut_run;
input [15:0] sram_dut_read_data;
input [15:0] wmem_dut_read_data;

//output nets
output dut_busy;
output dut_sram_write_enable;
output [15:0]dut_sram_write_data;
output [11:0] dut_sram_write_address;
output [11:0] dut_wmem_read_address;
output [11:0] dut_sram_read_address;

wire [1:0] select_line;

//instances of controller and datapath    
controller u1 (clk, reset_b, dut_run, dut_busy, select_line,dut_sram_write_enable);
datapath u2 (clk,reset_b,sram_dut_read_data,wmem_dut_read_data, select_line,dut_sram_write_data, dut_sram_write_address,dut_sram_read_address,dut_wmem_read_address,dut_sram_write_enable);
    
endmodule


//Datapath module
module datapath(clk,reset_b,sram_dut_read_data,wmem_dut_read_data, select_line,dut_sram_write_data, dut_sram_write_address,dut_sram_read_address,dut_wmem_read_address,dut_sram_write_enable);

//Input nets
input [15:0] sram_dut_read_data;
input [15:0] wmem_dut_read_data;
input [1:0] select_line;
input clk;
input reset_b;
input dut_sram_write_enable;

//Output nets
output [15:0]dut_sram_write_data;
output reg [11:0] dut_sram_write_address;
output reg [11:0] dut_sram_read_address;
output reg [11:0] dut_wmem_read_address;

//Datapath internal nets
reg [15:0] A;
reg [8:0] B;
reg result;
wire [8:0] product;
reg [8:0] convolution_matrix;
reg [3:0] sum,output_matrix;

integer i;

//mux for selecting 3x3 convolution matrix from input matrix, computing the number of ones in the xor output, and writing the result after each computation
always@ (*)
    begin
        dut_sram_write_address={12{1'b0}};
        dut_sram_read_address={12{1'b0}};
        dut_wmem_read_address={12{1'b0}};
        sum={4{1'b0}};
        if (!reset_b) begin
	    convolution_matrix={9{1'b0}};
	    result=1'b0;
	end
        else begin

            //computing the number of ones in the xor product for each convolution
            for (i=0;i<9;i=i+1) begin
                sum=sum+product[i];
            end
            
            //comparing whether ones or zeros are more in the xor product ,computed for each convolution, and writing the value into result
            result=sum>=5;

            //selecting the specific 3x3 convolution matrix from the input matrix
            case(select_line) 
                2'b00:
                    convolution_matrix={sram_dut_read_data[10],sram_dut_read_data[9],sram_dut_read_data[8],sram_dut_read_data[6],sram_dut_read_data[5],sram_dut_read_data[4],sram_dut_read_data[2],sram_dut_read_data[1],sram_dut_read_data[0]};
                2'b01:
                    convolution_matrix={sram_dut_read_data[11],sram_dut_read_data[10],sram_dut_read_data[9],sram_dut_read_data[7],sram_dut_read_data[6],sram_dut_read_data[5],sram_dut_read_data[3],sram_dut_read_data[2],sram_dut_read_data[1]};
                2'b10:
                    convolution_matrix={sram_dut_read_data[14],sram_dut_read_data[13],sram_dut_read_data[12],sram_dut_read_data[10],sram_dut_read_data[9],sram_dut_read_data[8],sram_dut_read_data[6],sram_dut_read_data[5],sram_dut_read_data[4]}; 
                2'b11:
                    convolution_matrix={sram_dut_read_data[15],sram_dut_read_data[14],sram_dut_read_data[13],sram_dut_read_data[11],sram_dut_read_data[10],sram_dut_read_data[9],sram_dut_read_data[7],sram_dut_read_data[6],sram_dut_read_data[5]};                 
            endcase
        end     
    end


//Writes final result of the neural network into the SRAM when write_enable goes high
assign dut_sram_write_data=dut_sram_write_enable?{{12{1'b0}},output_matrix}:{16{1'b0}};

//Writing the final result for each convolution into the specific index in the output matrix
always@(posedge clk) begin
    case(select_line)
        2'b00: output_matrix[0]=result;
        2'b01: output_matrix[1]=result;
        2'b10: output_matrix[2]=result;
        2'b11: output_matrix[3]=result;
	default: output_matrix=4'b0000;
    endcase 
end

//Xnor between convolution and weight matrix
assign product=convolution_matrix ~^ wmem_dut_read_data[8:0];

endmodule


//Controller Module
module controller (clk, reset_b, dut_run, dut_busy, select_line,dut_sram_write_enable);

//Input nets
input clk;
input reset_b;
input dut_run;

//Output nets
output reg dut_busy;
output reg dut_sram_write_enable;
output reg [1:0] select_line;

//states
parameter [2:0] // synopsys enum states
   S0 = 3'b000,
   S1 = 3'b001,
   S2 = 3'b010,
   S3 = 3'b011,
   S4 = 3'b100,
   S5 = 3'b101,
   S6 = 3'b110;

reg [2:0] /* synopsys enum states */ current_state, next_state; // synopsys state_vector current_state

/*------- Sequential Logic ----*/
always@(posedge clk or negedge reset_b)
  if (!reset_b)   current_state <= S0;
  else  current_state <= next_state;

//Moore FSM
always@(*)
  begin  
    select_line=2'b00;
    dut_sram_write_enable=0;  

    case (current_state) // synopsys full_case parallel_case
        
        //idle state
        S0: begin 
                dut_busy=1'b0;
                if (dut_run) next_state = S1;
                else next_state = S0;
            end
        
        //read from SRAMs
        S1: begin 
                dut_busy=1'b1;
                next_state = S2;
            end

        //select 1st convolution    
        S2: begin 
                dut_busy=1'b1;
                select_line=2'b00;
                next_state = S3;
            end

        //select 2nd convolution    
        S3: begin 
                dut_busy=1'b1;
                select_line=2'b01;
                next_state = S4;
            end  

        //select 3rd convolution    
        S4: begin 
                dut_busy=1'b1;
                select_line=2'b10;
                next_state = S5;
            end

        //select 4th convolution    
        S5: begin 
                dut_busy=1'b1;
                select_line=2'b11;
                next_state = S6;
            end

        //write to SRAM    
        S6: begin 
                dut_busy=1'b1;
                dut_sram_write_enable=1;
                next_state = S0;
            end

        //Default state    
	    default: 
            begin
		        dut_busy=1'b0;
		        next_state=S0;
		        select_line=2'b00;
		        dut_sram_write_enable=1'b0;
	        end        
    endcase
  end

endmodule
