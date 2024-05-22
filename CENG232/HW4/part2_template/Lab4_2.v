`timescale 1ns / 1ps

module lab4_2(
    input [1:0] mode,        // Modes: 01 for Entrance, 00 for Exit, 10 for Search, 11 for List
    input [5:0] userID,      // Format: [AreaID(2 bits)][UserID(4 bits)]
    input CLK,
    output reg [1:0] selectedAreaId, // Shows user-selected area
    output reg [5:0] numberOfInsideUser, // Number of users inside current area
    output reg [5:0] listOutput, // Lists the IDs of students in the area
    output reg AlreadyInside, // Indicates if a student is inside
    output reg NotInside // Indicates if a student is not inside
);

// Local parameters and variables
reg [15:0] LoudArea;      // 16 seats in Loud area
reg [15:0] QuietArea;     // 16 seats in Quiet area
reg [15:0] IndividualArea;// 16 seats in Individual area
reg [15:0] ZoomRooms;     // 16 seats in Zoom rooms
reg [3:0] userIndex;
reg [15:0] selectedArea;
reg [5:0] areaCounts [3:0]; // Array to keep track of number of users inside each area
integer i; // Declare the integer for the loop outside

// Initialize all areas to empty
initial begin
    LoudArea = 16'b0;
    QuietArea = 16'b0;
    IndividualArea = 16'b0;
    ZoomRooms = 16'b0;
    selectedAreaId = 2'b00;
    numberOfInsideUser = 6'b0;
    listOutput = 6'b0;
    AlreadyInside = 1'b0;
    NotInside = 1'b0;
    areaCounts[0] = 6'b0; // Loud area
    areaCounts[1] = 6'b0; // Quiet area
    areaCounts[2] = 6'b0; // Individual area
    areaCounts[3] = 6'b0; // Zoom rooms
end

// Main always block
always @(posedge CLK) begin
    // Extract area ID and user ID
    selectedAreaId = userID[5:4];
    userIndex = userID[3:0];
    
    // Select the appropriate area
    case (selectedAreaId)
        2'b00: selectedArea = LoudArea;
        2'b01: selectedArea = QuietArea;
        2'b10: selectedArea = IndividualArea;
        2'b11: selectedArea = ZoomRooms;
        default: selectedArea = LoudArea;
    endcase

    // Reset flags
    AlreadyInside = 1'b0;
    NotInside = 1'b0;

    case (mode)
        // Student Entrance Mode
        2'b01: begin
            if (selectedArea[userIndex]) begin
                AlreadyInside = 1'b1;
            end else begin
                selectedArea[userIndex] = 1'b1;
                areaCounts[selectedAreaId] = areaCounts[selectedAreaId] + 1;
            end
        end

        // Student Exit Mode
        2'b00: begin
            if (selectedArea[userIndex]) begin
                selectedArea[userIndex] = 1'b0;
                areaCounts[selectedAreaId] = areaCounts[selectedAreaId] - 1;
            end else begin
                NotInside = 1'b1;
            end
        end

        // Search Mode
        2'b10: begin
            if (selectedArea[userIndex]) begin
                AlreadyInside = 1'b1;
            end else begin
                NotInside = 1'b1;
            end
        end

        // List Mode
        2'b11: begin
            listOutput = 6'b0;
            for (i = 0; i < 16; i = i + 1) begin
                if (selectedArea[i]) begin
                    listOutput = {selectedAreaId, i[3:0]};
                    // Assuming listOutput will hold the last student ID found
                end
            end
        end

        default: ;
    endcase

    // Update the selected area based on modifications
    case (selectedAreaId)
        2'b00: LoudArea = selectedArea;
        2'b01: QuietArea = selectedArea;
        2'b10: IndividualArea = selectedArea;
        2'b11: ZoomRooms = selectedArea;
    endcase

    // Update the number of inside users for the selected area
    numberOfInsideUser = areaCounts[selectedAreaId];
end

endmodule
