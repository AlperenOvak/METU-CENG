`timescale 1ns / 1ps 
module lab3_2(
    input [4:0] money,
    input CLK, 
    input [1:0] selectedArea, //00:exit, 01:enter, 1x: idle 
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

reg [5:0] entranceFee;
reg [5:0] plugNoSeatsLeft_0;
reg [5:0] plugSeatsLeft_0;
reg [5:0] plugNoSeatsLeft_1;
reg [5:0] plugSeatsLeft_1;
reg [5:0] plugNoSeatsLeft_2;
reg [5:0] plugSeatsLeft_2;

initial begin
    entranceFee = 0;
    moneyLeft = 0;
    seatLeft = 0;
    seatUnavailable = 0;
    insufficientFund = 0;
    notExactFund = 0;
    invalidPlugSeat = 0;
    plugSeatUnavailable = 0;
    seatReady = 0;
    plugNoSeatsLeft_0 = 15;
    plugSeatsLeft_0 = 0;
    plugNoSeatsLeft_1 = 15;
    plugSeatsLeft_1 = 10;
    plugNoSeatsLeft_2 = 0;
    plugSeatsLeft_2 = 20;
end

always @(posedge CLK) begin
    seatUnavailable = 0;
    insufficientFund = 0;
    notExactFund = 0;
    invalidPlugSeat = 0;
    plugSeatUnavailable = 0;
    seatReady = 0;
	 moneyLeft = 0;
    seatLeft = 0;
    if (selectedArea == 0) begin
            entranceFee = 10;
            seatLeft = plugNoSeatsLeft_0;
        
         if(plugSeatsLeft_0+plugNoSeatsLeft_0 > 0) begin
            if(plugAvailability == 1) begin
                invalidPlugSeat = 1;
            end
            else begin
                if(money >= entranceFee) begin
                    moneyLeft = money - entranceFee;
                    plugNoSeatsLeft_0 = plugNoSeatsLeft_0 - 1;
                    seatLeft = plugNoSeatsLeft_0;
                    seatReady = 1;
                end
                else begin
                    insufficientFund = 1;
                    moneyLeft = money;
                end
            end
        end
        else begin
            seatUnavailable = 1;
            moneyLeft = money;
        end
    end
    else if (selectedArea == 1) begin
            entranceFee = 20;
             if (plugAvailability == 1)
                begin
                    seatLeft = plugSeatsLeft_1;
                end
            else begin 
                seatLeft = plugNoSeatsLeft_1;
            end
        if(plugSeatsLeft_1+plugNoSeatsLeft_1 > 0) begin
            if(plugAvailability == 1) begin
                if(plugSeatsLeft_1 > 0) begin
                    if(money >= entranceFee) begin
                        moneyLeft = money - entranceFee;
                        plugSeatsLeft_1 = plugSeatsLeft_1 - 1;
                        seatLeft = plugSeatsLeft_1;
                        seatReady = 1;
                    end
                    else begin
                        insufficientFund = 1; //!!
                        moneyLeft = money;
                        seatLeft = plugSeatsLeft_1;
                    end
                end
                else begin
                    plugSeatUnavailable = 1;
                    moneyLeft = money;
                    seatLeft = plugSeatsLeft_1;
                end
            end
            else begin
                if(plugNoSeatsLeft_1 > 0) begin
                    if(money >= entranceFee) begin
                        moneyLeft = money - entranceFee;
                        plugNoSeatsLeft_1 = plugNoSeatsLeft_1 - 1;
                        seatLeft = plugNoSeatsLeft_1;
                        seatReady = 1;
                    end
                    else begin
                        insufficientFund = 1;
                        moneyLeft = money;
                    end
                end
                else begin
                    seatUnavailable = 1;
                    moneyLeft = money;
                    seatLeft = plugNoSeatsLeft_1;
                end
            end
        end
        else begin
            seatUnavailable = 1;
            moneyLeft = money;
        end
    end
    else begin
            entranceFee = 30;
            seatLeft = plugSeatsLeft_2;
            
        if(plugSeatsLeft_2+plugNoSeatsLeft_2> 0) begin
            if(plugSeatsLeft_2 > 0) begin
                if(money == entranceFee) begin
                    moneyLeft = money - entranceFee;
                    plugSeatsLeft_2 = plugSeatsLeft_2 - 1;
                    seatLeft = plugSeatsLeft_2;
                    seatReady = 1;
                end
                else begin
                    notExactFund = 1;
                    moneyLeft = money;
                end
            end
            else begin
                plugSeatUnavailable = 1;
                moneyLeft = money;
            end
        end
        else begin
            seatUnavailable = 1;
            moneyLeft = money;
        end
    end
end

endmodule
