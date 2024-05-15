`timescale 1ns / 1ps

module testbench;

    // IO
	 reg CLK; real result=0;
	 /*for ROM */
	 reg [2:0] ROM_Addr; wire [7:0] ROM_Res;
	 /*Bitwise_Manipulation_RAM*/ 
	 reg RAM_mode; reg [2:0] RAM_Addr; reg [7:0] RAM_dataIn; reg [1:0] RAM_operation; reg [7:0] RAM_romData; wire [7:0] RAM_dataOut;
	 /*Combined_Memory_System*/
	 reg System_mode; reg [2:0] System_Addr; reg [7:0] System_dataIn; reg [1:0] System_operation; wire [7:0] System_output;

	 // instantiate ROM
    ROM rom(
        .addr(ROM_Addr),
        .dataOut(ROM_Res)
    );
	 
	 // instantiate RAM
	 Bitwise_Manipulation_RAM ram(
        .mode(RAM_mode),
        .addr(RAM_Addr),
		  .operation(RAM_operation),
        .dataIn(RAM_dataIn),
        .romData(RAM_romData),
		  .CLK(CLK),
        .dataOut(RAM_dataOut)
    );
	 
	 // Instantiate Combined_Memory_System 
	Combined_Memory_System memory(
		 .mode(System_mode),
		 .systemAddr(System_Addr),
		 .dataIn(System_dataIn),
		 .operation(System_operation),
		 .CLK(CLK),
		 .systemOutput(System_output)
	);
	
	
		//Set initial values
		initial CLK = 0;
		always #5 CLK = ~CLK;	
		// to hold the expected binary results of bitwise ops
		reg [7:0] expected_result;

	
		initial begin
			$display("Rom test begin");

    		//////////////////
    		//// ROM TEST ////
    		//////////////////
		
    		#1 ROM_Addr = 3'b000;
    		#1
    		if (ROM_Res == 8'b00000000) begin
    		    result = result + 1;
    		    $display("Pass case 1");
    		    $display(ROM_Res);
    		end else begin
    		    $display("Error in case 1");
    		end // case 1
		
    		#1 ROM_Addr = 3'b001;
    		#1
    		if (ROM_Res == 8'b00000001) begin
    		    result = result + 1;
    		    $display("Pass case 2");
    		    $display(ROM_Res);
    		end else begin
    		    $display("Error in case 2");
    		end // case 2
		
    		#1 ROM_Addr = 3'b010;
    		#1
    		if (ROM_Res == 8'b00000010) begin
    		    result = result + 1;
    		    $display("Pass case 3");
    		    $display(ROM_Res);
    		end else begin
    		    $display("Error in case 3");
    		end // case 3
		
    		#1 ROM_Addr = 3'b011;
    		#1
    		if (ROM_Res == 8'b00100011) begin
    		    result = result + 1;
    		    $display("Pass case 4");
    		    $display(ROM_Res);
    		end else begin
    		    $display("Error in case 4");
    		end // case 4
		
    		#1 ROM_Addr = 3'b100;
    		#1
    		if (ROM_Res == 8'b11000100) begin
    		    result = result + 1;
    		    $display("Pass case 5");
    		    $display(ROM_Res);
    		end else begin
    		    $display("Error in case 5");
    		end // case 5
		
    		#1 ROM_Addr = 3'b101;
    		#1
    		if (ROM_Res == 8'b01100101) begin
    		    result = result + 1;
    		    $display("Pass case 6");
    		    $display(ROM_Res);
    		end else begin
    		    $display("Error in case 6");
    		end // case 6
		
    		#1 ROM_Addr = 3'b110;
    		#1
    		if (ROM_Res == 8'b00011110) begin
    		    result = result + 1;
    		    $display("Pass case 7");
    		    $display(ROM_Res);
    		end else begin
    		    $display("Error in case 7");
    		end // case 7
		
    		#1 ROM_Addr = 3'b111;
    		#1
    		if (ROM_Res == 8'b01000101) begin
    		    result = result + 1;
    		    $display("Pass case 8");
    		    $display(ROM_Res);
    		end else begin
    		    $display("Error in case 8");
    		end // case 8
		
    		$display("Ram test begin");

			//////////////////
			//// RAM TEST ////
			//////////////////
			#6
			RAM_mode=1'b1;//read mode
			RAM_Addr = 3'b001;
			#2
			if(RAM_dataOut == 0) result=result+1; else $display("Error in case 9"); /*case 9*/
			$display("RAM_dataOut: %b", RAM_dataOut);
			
			// Test writing to RAM w/ AND operation
			#1
			RAM_Addr = 3'b111;
			RAM_operation = 2'b00; // AND
			RAM_dataIn = 8'b01010111;
			RAM_romData = 8'b01010111;
			RAM_mode=1'b0;//write mode
			#1
			RAM_mode=1'b1;//read mode
			#1
			if(RAM_dataOut == RAM_dataIn & RAM_romData) result=result+1; else $display("Error in case 10"); /*case 10*/
			$display("RAM_dataOut: %b", RAM_dataOut);
			
			// Test writing to RAM w/ OR operation
			#1
			RAM_Addr = 3'b101;
			RAM_operation = 2'b01; // OR
			RAM_dataIn = 8'b11111000;
			RAM_romData = 8'b00000101;
			RAM_mode=1'b0;//write mode
			#10
			RAM_mode=1'b1;//read mode
			#10
			if(RAM_dataOut == (RAM_dataIn | RAM_romData)) result=result+1; else $display("Error in case 11"); /*case 11*/
			$display("RAM_dataOut: %b", RAM_dataOut);
			
			// Test writing to RAM w/ XOR operation
			#1
			RAM_Addr = 3'b011;
			RAM_operation = 2'b10; // XOR
			RAM_dataIn = 8'b11111000;
			RAM_romData = 8'b01100101;
			RAM_mode=1'b0;//write mode
			#10
			RAM_mode=1'b1;//read mode
			#10
			if(RAM_dataOut == (RAM_dataIn ^ RAM_romData)) result=result+1; else $display("Error in case 12"); /*case 12*/
			$display("RAM_dataOut: %b", RAM_dataOut);
			
			// Test writing to RAM w/ NAND operation
			#1
			RAM_Addr = 3'b110;
			RAM_operation = 2'b11; // NAND
			RAM_dataIn = 8'b11111000;
			RAM_romData = 8'b01100101;
			RAM_mode=1'b0;//write mode
			#20
			RAM_mode=1'b1;//read mode
			#10
			if(RAM_dataOut == ~(RAM_dataIn & RAM_romData)) result=result+1; else $display("Error in case 13"); /*case 13*/
			$display("RAM_dataOut: %b", RAM_dataOut);
			
			
			#2
			$display("Result is:%2.2f",result); // MAX 13
			$finish;
			
			
			
			
		end
		

		



endmodule
