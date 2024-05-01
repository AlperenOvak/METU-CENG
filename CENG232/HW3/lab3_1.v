`timescale 1ns / 1ps

module ac_flip_flop(
    input A,
    input C,
    input clk,
    output reg Q
);

	initial begin
		Q = 1;
	end
	
	always @ (posedge clk)
		begin 
			if (A == 0 && C == 0) Q = 1;
			else if (A == 0 && C == 1) Q = ~Q;
			else if (A == 1 && C == 0) Q = Q;
			else Q = 1;
		end
		
endmodule

module ic1406(
    input A0,
    input A1,
    input A2,
    input clk,
    output Q0,
    output Q1,
    output Z
);
	
	wire t1;
	wire t2;
	wire A_1;
	wire C_1;
	wire C_2;
	
	assign t1 = A0 ^ A1;
	assign A_1 = ~(t1 | ~A2);
	assign C_1 = A0 && A1;
	assign t2 = ~A0 | ~A1;
	assign C_2 = t2 && ~A2;
	
	ac_flip_flop ac0(A_1,C_1,clk,Q0);
	ac_flip_flop ac1(C_1,C_2,clk,Q1);
	
	assign Z = Q0 ^ Q1;
	
endmodule

