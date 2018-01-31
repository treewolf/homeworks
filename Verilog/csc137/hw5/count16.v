//incomplete for the user to customize as per instructions on homework
// converts unary to binary
module CoderMod(Q, C);
	input [0:15] Q;
	output [3:0] C;

	//or();
	//figure out your encoded name
endmodule

// clock changes on every other.
module RippleMod(CLK, Q);
	input CLK;
	output [0:15] Q;

	reg [0:15] Q;

	// positive edge detects when CLK is 1 (positive), and executing only when positive
	always @(posedge CLK) begin
		Q[0] <= Q[15];
		Q[1] <= Q[0];
		Q[2] <= Q[1];
		Q[3] <= Q[2];
		Q[4] <= Q[3];
		Q[5] <= Q[4];
		Q[6] <= Q[5];
		Q[7] <= Q[6];
		Q[8] <= Q[7];
		Q[9] <= Q[8];
		Q[10] <= Q[9];
		Q[11] <= Q[10];
		Q[12] <= Q[11];
		Q[13] <= Q[12];
		Q[14] <= Q[13];
		Q[15] <= Q[14];
	end

	initial begin	// set flip flops to 1000 (binary)
		Q[0] = 1; Q[1] = 0; Q[2] = 0; Q[3] = 0;
		Q[4] = 0; Q[5] = 0; Q[6] = 0; Q[7] = 0;
		Q[8] = 0; Q[9] = 0; Q[10] = 0; Q[11] = 0;
		Q[12] = 0; Q[13] = 0; Q[14] = 0; Q[15] = 0;
	end
endmodule


// CLK is switch bit
// Q is unary representation
// C is binary 
module TestMod;
	reg CLK;
	wire [0:15] Q;
	wire [3:0] C;

	always begin	// this is clock wave. #1 is effectively half a cycle when used with posedge in a loop (postive edge detector)
		CLK = 0;	// 0 for half cycle (#1)
		#1;
		CLK = 1;	// 1 for half cycle (#1)
		#1;
	end

	RippleMod my_ripple(CLK, Q);
	CoderMod my_coder(Q, C);

	initial #36 $finish;

	initial begin
		$display("Time\tCLK\tQ\t\t\tC\tC");
		$monitor("%2d\t%b\t%b%b%b%b%b%b%b%b%b%b%b%b%b%b%b%b\t%b\t%d", $time, CLK, Q[0],Q[1],Q[2],Q[3],Q[4],Q[5],Q[6],Q[7],Q[8],Q[9],Q[10],Q[11],Q[12],Q[13],Q[14],Q[15], C, C); 
	end
endmodule
