`timescale 1ns / 1ps 
module lab3_2(
    		input [4:0] money,
			input CLK, 
			input [1:0] selectedArea,
    		input plugAvailability,
			output reg [5:0] moneyLeft,
			output reg [5:0] seatLeft,
			output reg seatUnavailable,
    		output reg insufficientFund,
    		output reg notExactFund,
    		output reg invalidPlugSeat,
    		output reg plugSeatUnavailable,
    		output reg seatReady
	);
	 

	// IMPLEMENT BELOWS
	
	// Parameters and variables

    reg [5:0] LOUD_SEATS = 15;
    reg [5:0] QUIET_SEATS_WITH_PLUG = 10;
    reg [5:0] QUIET_SEATS_WITHOUT_PLUG = 15;
    reg [5:0] INDIVIDUAL_SEATS = 20;
	
	initial begin

	seatUnavailable = 0;
    insufficientFund = 0;
    notExactFund = 0;
    invalidPlugSeat = 0;
    plugSeatUnavailable = 0;
    seatReady = 0;
	seatLeft = 0;
	moneyLeft = 0;

	end


    always @(posedge CLK) begin
	// Reset warnings
    seatUnavailable = 0;					 	// all
    invalidPlugSeat = 0;						// for Load 
    plugSeatUnavailable = 0;					// all
	notExactFund = 0;							// for Individual
	insufficientFund = 0;						// for Load or Quite
    seatReady = 0;
	moneyLeft = 0;
    
	if(selectedArea == 1) // Quite   
	begin 
		if(plugAvailability && QUIET_SEATS_WITH_PLUG > 0 && money >= 20)
		begin
			moneyLeft = money - 20;
			QUIET_SEATS_WITH_PLUG = QUIET_SEATS_WITH_PLUG - 1;
			seatLeft = QUIET_SEATS_WITH_PLUG;
			seatReady = 1;
		end

		else if(!plugAvailability && QUIET_SEATS_WITHOUT_PLUG > 0 && money >= 20)  
		begin
			moneyLeft = money - 20;
			QUIET_SEATS_WITHOUT_PLUG = QUIET_SEATS_WITHOUT_PLUG - 1;
			seatLeft = QUIET_SEATS_WITHOUT_PLUG;
			seatReady = 1;
		end

		else if((!plugAvailability && QUIET_SEATS_WITHOUT_PLUG == 0) || (!plugAvailability && QUIET_SEATS_WITHOUT_PLUG == 0 && QUIET_SEATS_WITH_PLUG == 0))
		begin
			seatUnavailable = 1;
			moneyLeft = money;
			seatLeft = 	QUIET_SEATS_WITHOUT_PLUG;
		end

		else if(plugAvailability && QUIET_SEATS_WITH_PLUG == 0 && QUIET_SEATS_WITHOUT_PLUG == 0)
		begin
			seatUnavailable = 1;	
			moneyLeft = money;
			seatLeft = 	QUIET_SEATS_WITH_PLUG;		
		end

		else if(plugAvailability && QUIET_SEATS_WITH_PLUG == 0 && QUIET_SEATS_WITHOUT_PLUG != 0)
		begin
			plugSeatUnavailable = 1;	
			moneyLeft = money;
			seatLeft = 	QUIET_SEATS_WITH_PLUG;		
		end

		else if (money < 20) 
		begin
            insufficientFund = 1;
			moneyLeft = money;

			if(plugAvailability)
			begin
				seatLeft = QUIET_SEATS_WITH_PLUG;
			end

			else if(!plugAvailability)
			begin
				seatLeft = QUIET_SEATS_WITHOUT_PLUG;
			end

		end
	end
	
	else if(selectedArea == 3) // Individual
	begin

		if(plugAvailability && INDIVIDUAL_SEATS > 0 && money == 30)
		begin
			moneyLeft = money - 30;
            INDIVIDUAL_SEATS = INDIVIDUAL_SEATS - 1;
			seatLeft = INDIVIDUAL_SEATS;
            seatReady = 1;
		end


		else if(!plugAvailability && INDIVIDUAL_SEATS > 0 && money == 30)
		begin
			moneyLeft = money - 30;
            INDIVIDUAL_SEATS = INDIVIDUAL_SEATS - 1;
            seatLeft = INDIVIDUAL_SEATS;
			seatReady = 1;
		end

		else if((plugAvailability||!plugAvailability) && INDIVIDUAL_SEATS == 0)
		begin
			seatUnavailable = 1;
			moneyLeft = money;
			seatLeft = INDIVIDUAL_SEATS;
		end


		else if (money != 20) 
		begin
            notExactFund = 1;
			moneyLeft = money;
			seatLeft = INDIVIDUAL_SEATS;
		end

	end

	else if(selectedArea == 0) // Loud
	begin
		
		if(!plugAvailability && LOUD_SEATS > 0 && money >= 10)
		begin
			moneyLeft = money - 10;
            LOUD_SEATS = LOUD_SEATS - 1;
			seatLeft = LOUD_SEATS;
            seatReady = 1;
		end

		else if(LOUD_SEATS == 0)
		begin
			seatUnavailable = 1;
			moneyLeft = money;
			seatLeft = LOUD_SEATS;
		end 

		else if(plugAvailability)
		begin
			invalidPlugSeat = 1;
			moneyLeft = money;
			seatLeft = LOUD_SEATS;
		end 

		else if (money < 20) 
		begin
            insufficientFund = 1;
			moneyLeft = money;
			seatLeft = LOUD_SEATS;
		end
	end

	end
endmodule
