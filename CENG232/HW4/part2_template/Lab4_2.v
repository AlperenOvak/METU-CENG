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
reg [5:0] loudAreaCount;
reg [5:0] quietAreaCount;
reg [5:0] individualAreaCount;
reg [5:0] zoomRoomsCount;
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
    loudAreaCount = 6'b0;
    quietAreaCount = 6'b0;
    individualAreaCount = 6'b0;
    zoomRoomsCount = 6'b0;
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
                case (selectedAreaId)
                    2'b00: loudAreaCount = loudAreaCount + 1;
                    2'b01: quietAreaCount = quietAreaCount + 1;
                    2'b10: individualAreaCount = individualAreaCount + 1;
                    2'b11: zoomRoomsCount = zoomRoomsCount + 1;
                endcase
            end
        end

        // Student Exit Mode
        2'b00: begin
            if (selectedArea[userIndex]) begin
                selectedArea[userIndex] = 1'b0;
                case (selectedAreaId)
                    2'b00: loudAreaCount = loudAreaCount - 1;
                    2'b01: quietAreaCount = quietAreaCount - 1;
                    2'b10: individualAreaCount = individualAreaCount - 1;
                    2'b11: zoomRoomsCount = zoomRoomsCount - 1;
                endcase
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
    case (selectedAreaId)
        2'b00: numberOfInsideUser = loudAreaCount;
        2'b01: numberOfInsideUser = quietAreaCount;
        2'b10: numberOfInsideUser = individualAreaCount;
        2'b11: numberOfInsideUser = zoomRoomsCount;
    endcase
end

endmodule
