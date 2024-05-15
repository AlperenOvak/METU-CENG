`timescale 1ns / 1ps

module ROM (
    input [2:0] addr,
    output reg [7:0] dataOut
);
    // ROM memory array
    reg [7:0] rom [0:7];
    
    // Initialize the ROM with predefined values
    initial begin
        rom[0] = 8'b00000000;
        rom[1] = 8'b00000001;
        rom[2] = 8'b00000010;
        rom[3] = 8'b00100011;
        rom[4] = 8'b11000100;
        rom[5] = 8'b01100101;
        rom[6] = 8'b00011110;
        rom[7] = 8'b01000101;
    end
    
    // Asynchronous read from ROM
    always @(*) begin
        dataOut = rom[addr];
    end

endmodule



module Bitwise_Manipulation_RAM (
    input mode,                     // 0 for write, 1 for read
    input [2:0] addr,               // RAM address
	input [1:0] operation,          // Operation code (AND, OR, XOR, NAND)
    input [7:0] dataIn,             // Input data
    input [7:0] romData,            // Data from ROM used in operations
    input CLK,                      // Clock signal
	output reg [7:0] dataOut        // Output data
);
	// RAM memory array
    reg [7:0] ram [0:7];

    // Initialize RAM content to zeros
    integer i;
    initial begin
        for (i = 0; i < 8; i = i + 1) begin
            ram[i] = 8'b00000000;
        end
    end
    
    // Write mode: perform bitwise operations
    always @(posedge CLK) begin
        if (mode == 0) begin // Write mode
            case (operation)
                2'b00: ram[addr] <= dataIn & romData;  // AND
                2'b01: ram[addr] <= dataIn | romData;  // OR
                2'b10: ram[addr] <= dataIn ^ romData;  // XOR
                2'b11: ram[addr] <= ~(dataIn & romData); // NAND
                default: ram[addr] <= 8'b00000000;     // Default case
            endcase
        end
    end

    // Read mode: read data from RAM
    always @(*) begin
        if (mode == 1) begin
            dataOut = ram[addr];
        end
    end
	
endmodule



module Combined_Memory_System (
    input mode,
    input [2:0] systemAddr,
    input [7:0] dataIn,
    input [1:0] operation,
	input CLK,
    output [7:0] systemOutput
);
	wire [7:0] romData;
    wire [7:0] ramDataOut;
    
    // Instantiate ROM module
    ROM rom_inst (
        .addr(systemAddr),
        .dataOut(romData)
    );

    // Instantiate Bitwise Manipulation RAM module
    Bitwise_Manipulation_RAM ram_inst (
        .mode(mode),
        .addr(systemAddr),
        .operation(operation),
        .dataIn(dataIn),
        .romData(romData),
        .CLK(CLK),
        .dataOut(ramDataOut)
    );

    // Output data from RAM module
    assign systemOutput = ramDataOut;
	 
endmodule

