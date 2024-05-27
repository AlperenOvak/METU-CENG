`timescale 1ns / 1ps

module lab4_2(

							input [1:0] mode,
							input [5:0] userID,
							input CLK,
							output reg [1:0] selectedAreaId,
							output reg [5:0] numberOfInsideUser, 
							output reg [5:0] listOutput,
							output reg AlreadyInside, 	
							output reg NotInside   
    );

//locals
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
// list variables
reg [5:0] AreaIndex;
reg [5:0] loudAreaIndex;
reg [5:0] quietAreaIndex;
reg [5:0] individualAreaIndex;
reg [5:0] zoomRoomsIndex;
reg [1:0] var;
integer i; 

// Initialize all areas to empty
initial begin
	var = 0;
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
	loudAreaIndex = 6'b0;
	quietAreaIndex = 6'b0;
	individualAreaIndex = 6'b0;
	zoomRoomsIndex = 6'b0;
	AreaIndex = 6'b0;

end

always @(posedge CLK) begin
    
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

	case (selectedAreaId)
        2'b00: AreaIndex = loudAreaIndex;
        2'b01: AreaIndex = quietAreaIndex;
        2'b10: AreaIndex = individualAreaIndex;
        2'b11: AreaIndex = zoomRoomsIndex;
        default: AreaIndex = loudAreaIndex;
    endcase

    AlreadyInside = 1'b0;
    NotInside = 1'b0;

    case (mode)
        // Student Entrance Mode
        2'b01: begin
			loudAreaIndex = 0;
			quietAreaIndex = 0;
			individualAreaIndex = 0;
			zoomRoomsIndex = 0;

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
			loudAreaIndex = 0;
			quietAreaIndex = 0;
			individualAreaIndex = 0;
			zoomRoomsIndex = 0;

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
			loudAreaIndex = 0;
			quietAreaIndex = 0;
			individualAreaIndex = 0;
			zoomRoomsIndex = 0;

            if (selectedArea[userIndex]) begin
                AlreadyInside = 1'b1;
            end else begin
                NotInside = 1'b1;
            end
        end

        // List Mode
        2'b11: begin
            listOutput = 6'bxxxxxx;
			var = 0;
			case (selectedAreaId)
    		    2'b00: begin quietAreaIndex = 0; individualAreaIndex = 0; zoomRoomsIndex=0; end
    		    2'b01: begin loudAreaIndex = 0; individualAreaIndex = 0; zoomRoomsIndex=0; end 
    		    2'b10: begin loudAreaIndex = 0; quietAreaIndex = 0; zoomRoomsIndex=0; end 
    		    2'b11: begin loudAreaIndex = 0; quietAreaIndex = 0; individualAreaIndex=0; end
    		    default: begin quietAreaIndex = 0; individualAreaIndex = 0; zoomRoomsIndex=0; end
    		endcase
            for (i = AreaIndex; i < 16 ; i = i + 1) begin
				if(var == 0) begin
					if (selectedArea[i]) begin
						case (selectedAreaId)
    					    2'b00: loudAreaIndex = i+1;
    					    2'b01: quietAreaIndex = i+1;
    					    2'b10: individualAreaIndex = i+1;
    					    2'b11: zoomRoomsIndex = i+1;
    					    default: loudAreaIndex = i+1;
    					endcase
						listOutput = {selectedAreaId, i[3:0]};
						var = 1;
					end
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