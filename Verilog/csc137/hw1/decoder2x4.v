
module DecoderMod(s1, s0, o0, o1, o2, o3); //module definition
	input s1, s0;
	output o0, o1, o2, o3;

	//assign HERE: follow model shown in directions
	assign o0 = ~s0 & ~s1;
	assign o1 = s0 & ~s1;
	assign o2 = ~s0 & s1;
	assign o3 = s0 & s1;
endmodule

module TestMod;
	reg s1, s0; // s a 1-bit flip flop
	wire o0, o1, o2, o3;

	DecoderMod my_decoder(s1, s0, o0, o1, o2, o3);

	initial begin
		$monitor("%0d\t%b\t%b\t%b\t%b\t%b\t%b", $time, s1, s0, o0, o1, o2, o3);
		$display("Time\ts1\ts0\to0\to1\to2\to3");
		$display("-------------------------------------------------");
	end

	initial begin
		s0 = 0;
		s1 = 0;
		#1;
		s0 = 1;
		s1 = 0;
		#1;
		s0 = 0;
		s1 = 1;
		#1;
		s0 = 1;
		s1 = 1;
	end
endmodule
