module MuxMod(s[1], s[0], d[0], d[1], d[2], d[3], o);
	input [1:0] s; 
	input [3:0] d;
	output o;

	//input HERE: follow the model shown in the directions
	wire [3:0] andd;
	assign andd[0] = ~s[1] & ~s[0] & d[0];
	assign andd[1] = ~s[1] & s[0] & d[1];
	assign andd[2] = s[1] & ~s[0] & d[2];
	assign andd[3] = s[1] & s[0] & d[3];
	assign o = andd[0] | andd[1] | andd[2] | andd[3];	
endmodule

module TestMod;

	// t variables are to help with bit conversions
	reg [1:0] s; 
	reg [3:0] d;
	reg [5:0] t;
	wire o;

	MuxMod my_mux(s[1], s[0], d[0], d[1], d[2], d[3], o);


	initial begin
		$display("Time\ts1\ts0\td0\td1\td2\td3\to");
		$display("--------------------------------------------------------------");
		$monitor("%0d\t%b\t%b\t%b\t%b\t%b\t%b\t%b", $time, s[1], s[0], d[0], d[1], d[2], d[3], o);
	end

	initial begin

		// repeat loop to set variables, cuz lazy
		// $time is 64 bit. shift right to get the correct bit, and set as least significant.
		// then zero everything out with AND except the least significant bit.
		
		repeat (64) begin
			
			// must have monitor inside repeat, else repeat will finish, and monitor will only have 0 and 32. look into			
			$monitor("%0d\t%b\t%b\t%b\t%b\t%b\t%b\t%b", $time, s[1], s[0], d[0], d[1], d[2], d[3], o);
			
			t[5] = ($time >> 5) & 59'b1;
			if(t[5] == 0)	s[1] = 0;
			else	s[1] = 1;
			
			t[4] = ($time >> 4) & 60'b1;
			if(t[4] == 0)	s[0] = 0;
			else	s[0] = 1;
			
			t[3] = ($time >> 3) & 61'b1;
			if(t[3] == 0)	d[0] = 0;
			else	d[0] = 1;
			
			t[2] = ($time >> 2) & 62'b1;
			if(t[2] == 0)	d[1] = 0;
			else	d[1] = 1;

			t[1] = ($time >> 1) & 63'b1;
			if(t[1] == 0)	d[2] = 0;
			else	d[2] = 1;

			t[0] = $time & 64'b1;
			if(t[0] == 0)	d[3] = 0;
			else	d[3] = 1;
			
			#1;
		end						
	end
endmodule
