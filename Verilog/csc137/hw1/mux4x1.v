module MuxMod(s1, s0, d0, d1, d2, d3, o);
	input s1, s0, d0, d1, d2, d3;
	output o;

	//input HERE: follow the model shown in the directions
	assign and0 = ~s1 & ~s0 & d0;
	assign and1 = ~s1 & s0 & d1;
	assign and2 = s1 & ~s0 & d2;
	assign and3 = s1 & s0 & d3;
	assign o = and0 | and1 | and2 | and3;	
endmodule

module TestMod;

	// t variables are to help with bit conversions
	reg s1, s0, d0, d1, d2, d3, t5, t4, t3, t2, t1, t0;
	wire o;

	MuxMod my_mux(s1, s0, d0, d1, d2, d3, o);

	initial begin
		$display("Time\ts1\ts0\td0\td1\td2\td3\to");
		$display("--------------------------------------------------------------");
		$monitor("%0d\t%b\t%b\t%b\t%b\t%b\t%b\t%b", $time, s1, s0, d0, d1, d2, d3, o);
	end

	initial begin

		// repeat loop to set variables, cuz lazy
		// $time is 64 bit. shift right to get the correct bit, and set as least significant.
		// then zero everything out with AND except the least significant bit.
		
		repeat (64) begin
			
			// must have monitor inside repeat, else repeat will finish, and monitor will only have 0 and 32. look into			
			$monitor("%0d\t%b\t%b\t%b\t%b\t%b\t%b\t%b", $time, s1, s0, d0, d1, d2, d3, o);
			
			t5 = ($time >> 5) & 59'b1;
			if(t5 == 0)	s1 = 0;
			else	s1 = 1;
			
			t4 = ($time >> 4) & 60'b1;
			if(t4 == 0)	s0 = 0;
			else	s0 = 1;
			
			t3 = ($time >> 3) & 61'b1;
			if(t3 == 0)	d0 = 0;
			else	d0 = 1;
			
			t2 = ($time >> 2) & 62'b1;
			if(t2 == 0)	d1 = 0;
			else	d1 = 1;

			t1 = ($time >> 1) & 63'b1;
			if(t1 == 0)	d2 = 0;
			else	d2 = 1;

			t0 = $time & 64'b1;
			if(t0 == 0)	d3 = 0;
			else	d3 = 1;
			
			#1;
		end						
	end
endmodule
