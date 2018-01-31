module FullAdder(x, y, c, sum, cout);
	output cout;	
	output sum;		
	input c; 
	input x; 	
	input y;	

	//fulladder
	Majority majority(x, y, c, cout);
	Parity parity(x, y, c, sum);	
	
endmodule

// gives Carry out
module Majority(x, y, c, cout);
	input x;
	input y;
	input c;
	output cout;

	//module meat
	wire [2:0] temp;
	assign temp[0] = x & y;
	assign temp[1] = x & c;
	assign temp[2] = y & c;

	// get out
	assign cout = temp[0] | temp[1] | temp[2];
endmodule

// Gives Sum
module Parity(x, y, c, sum);
	input x;
	input y;
	input c;
	output sum;

	//module meat
	wire temp;
	assign temp = x ^ y;
	assign sum = temp ^ c;
endmodule 

//BigAdder
module BigAdder(x, y, s, c5);
	input [4:0] x, y;
	output [4:0] s;
	output c5;

	//cannot reuse temp to save memory, must creat all new temps
	wire [3:0] temp;
	
	//x y cin sum cout
	FullAdder fulladder0(x[0], y[0], 1'b0, s[0], temp[0]);
	FullAdder fulladder1(x[1], y[1], temp[0], s[1], temp[1]);
	FullAdder fulladder2(x[2], y[2], temp[1], s[2], temp[2]);
	FullAdder fulladder3(x[3], y[3], temp[2], s[3], temp[3]);
	FullAdder fulladder4(x[4], y[4], temp[3], s[4], c5);
endmodule

module TestMod;
	parameter STDIN = 32'h8000_0000;
	wire cout;	
	wire [4:0] s;
        wire c5;
        reg [4:0] x;
	reg [4:0] y;

	reg [7:0] str [0:2];

	//instanstiate class
	BigAdder big(x, y, s, c5);

	// Get all needed user input
	initial begin
		$display("Enter X:");
		str[0] = $fgetc( STDIN );
		str[1] = $fgetc( STDIN );
		str[0] = (str[0] - 48) * 10;
		x = str[0] + (str[1] - 48);
	
		// clear input stream	
		str[0] = $fgetc( STDIN );	
		$display("Enter Y:");
		str[0] = $fgetc( STDIN );
                str[1] = $fgetc( STDIN );
               	str[0] = (str[0] - 48) * 10;
		y = str[0] + (str[1] - 48);

		//clear input stream
		str[0] = $fgetc( STDIN ); 
	
		//let program think, needs one cycle	
		#1;
		$display("X = %d (%b)	Y = %d (%b)\nResult = %d, (%b)	C5 = %d", x, x, y, y, s, s, c5);
	end
endmodule

