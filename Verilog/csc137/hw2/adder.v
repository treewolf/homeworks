module AdderMod(s[1], s[0], cin, o[1], o[0]);
	input [1:0] s;	// s[1] is y and s[0] is x
	input cin;	// majority, 1 vs 0 in terms of count
	output [1:0] o;	//o[1] is c out and o[0] is Sum

	wire [4:0] y; 	//xnor - 1 if both are same, else 0 
	assign y[0] = s[0] & s[1];	// holds x and y 
	assign y[1] = s[0] & cin;	// holds x and cin
	assign y[2] = s[1] & cin;	// holds y and cin
	assign o[1] = y[0] | y[1] | y[2];	// holds cout
	assign y[3] = s[0] ^ s[1];	// holds x xor y
	assign o[0] = y[3] ^ cin;	// holds cin xor (x xor y)
endmodule

module TestMod;
	reg [1:0] s;
	reg cin;
	wire [1:0] o;

	AdderMod addthis(s[1], s[0], cin, o[1], o[0]);

	initial begin
		$display("Cin\tX\tY\t->\tCout\tSum");
		$monitor("%d\t%d\t%d\t\t%d\t%d", cin, s[0], s[1], o[1], o[0]);
	end

	initial begin	//set loop for only 8 cycles
		#7;
		$finish;
	end

	always begin
		cin = 0; #4;
		cin = 1; #4;
	end

	always begin
		s[0] = 0; #2;
		s[0] = 1; #2;
	end

	always begin
		s[1] = 0; #1;
		s[1] = 1; #1;
	end
endmodule

