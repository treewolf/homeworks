module AdderSubtractor(x, y, s, c0, c4, c5, E);
	input [4:0] x, y;   
	input c0;
        output [4:0] s; 
        output c4, c5;
	output E;      
                      
        //cannot reuse temp to save memory, must create all new temps
        wire [3:0] temp;       
	wire [5:0] xord;                   

	xor(xord[0], y[0], c0);
	xor(xord[1], y[1], c0);
	xor(xord[2], y[2], c0);
	xor(xord[3], y[3], c0);
	xor(xord[4], y[4], c0);

        //x y cin sum cout
        FullAdder fulladder0(x[0], xord[0], c0, s[0], temp[0]);
        FullAdder fulladder1(x[1], xord[1], temp[0], s[1], temp[1]);
        FullAdder fulladder2(x[2], xord[2], temp[1], s[2], temp[2]);
        FullAdder fulladder3(x[3], xord[3], temp[2], s[3], temp[3]);
        FullAdder fulladder4(x[4], xord[4], temp[3], s[4], c5);

	assign c4 = temp[3];
	xor(E, c5, temp[3]);
	
endmodule

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
	and(temp[0], x, y);
	and(temp[1], x, c);
	and(temp[2], y, c);	

	// get out
	or(cout, temp[0], temp[1], temp[2]);
endmodule

// Gives Sum
module Parity(x, y, c, sum);
	input x;
	input y;
	input c;
	output sum;

	//module meat
	wire temp;
	xor(temp, x, y);
	xor(sum, temp, c);
endmodule 

module TestMod;
	parameter STDIN = 32'h8000_0000;
	wire cout;	
	wire [4:0] s;
        wire c5;
	wire E;
        reg [4:0] x;
	reg [4:0] y;
	reg c0;

	//elements 0-1 = x,y. 2 = plus or minus. 3 = enterline/clr
	reg [7:0] str [0:3];

	//instanstiate class
	AdderSubtractor add_sub(x, y, s, c0, c4, c5, E);

	// Get all needed user input
	initial begin
		$display("Enter X (range 00 ~ 15):");
		str[0] = $fgetc( STDIN );
		str[1] = $fgetc( STDIN );
		str[0] = (str[0] - 48) * 10;
		x = str[0] + (str[1] - 48);
	
		// clear input stream	
		str[3] = $fgetc( STDIN );	
		
		$display("Enter Y (range 00 ~ 15):");
		str[0] = $fgetc( STDIN );
                str[1] = $fgetc( STDIN );
               	str[0] = (str[0] - 48) * 10;
		y = str[0] + (str[1] - 48);

		//clear input stream
		str[3] = $fgetc( STDIN ); 

		//add or subtract input
		$display("Enter either '+' or '-':");
		str[2] = $fgetc( STDIN );

		//clear input stream
		str[3] = $fgetc( STDIN );

		//determine if add or subtract
		if(str[2]== 8'b00101011)
			c0 = 0;
		else
			c0 = 1;

	
		//let program think, needs one cycle	
		#1;
		$display("X = %b (%d)	Y = %b (%d)	C0 = %d", x, x, y, y, c0);
		$display("Result=%b (as unsigned %d)", s, s);
		$display("C4=%d C5=%d E=%d", c4, c5, E);
		if (E == 0)
			$display("Since E is 0, C5 is not needed.");
		else
			$display("Since E is 1, correct with C5 in front: %b%b", c5, s);

	end
endmodule

