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

reg [5:0] currentMoney;
reg [5:0] entranceFee;
reg [5:0] plugNoSeatsLeft_0;
reg [5:0] plugSeatsLeft_0;
reg [5:0] plugNoSeatsLeft_1;
reg [5:0] plugSeatsLeft_1;
reg [5:0] plugNoSeatsLeft_2;
reg [5:0] plugSeatsLeft_2;

initial begin
    currentMoney = money;
    entranceFee = (selectedArea * 10) + 10;
    plugNoSeatsLeft_0 = 15;
    plugSeatsLeft_0 = 0;
    plugNoSeatsLeft_1 = 15;
    plugSeatsLeft_1 = 10;
    plugNoSeatsLeft_2 = 0;
    plugSeatsLeft_2 = 20;
end

always @(posedge CLK) begin
    if (selectedArea == 0) begin
        if((plugSeatsLeft_0+plugNoSeatsLeft_0) > 0) begin
            if(plugAvailability == 1) begin
                invalidPlugSeat <= 1;
            end
            else begin
                if(currentMoney >= entranceFee) begin
                    currentMoney <= currentMoney - entranceFee;
                    plugNoSeatsLeft_0 <= plugNoSeatsLeft_0 - 1;
                    seatLeft <= plugNoSeatsLeft_0;
                    seatReady <= 1;
                end
                else begin
                    insufficientFund <= 1;
                end
            end
        end
        else begin
            seatUnavailable <= 1;
        end
    end
    else if (selectedArea == 1) begin
        if((plugSeatsLeft_1+plugNoSeatsLeft_1) > 0) begin
            if(plugAvailability == 1) begin
                if(plugSeatsLeft_1 > 0) begin
                    if(currentMoney == entranceFee) begin
                        currentMoney <= 0;
                        plugSeatsLeft_1 <= plugSeatsLeft_1 - 1;
                        seatLeft <= plugSeatsLeft_1;
                        seatReady <= 1;
                    end
                    else begin
                        notExactFund <= 1;
                    end
                end
                else begin
                    plugSeatUnavailable <= 1;
                end
            end
            else begin
                if(currentMoney == entranceFee) begin
                    currentMoney <= 0;
                    plugNoSeatsLeft_1 <= plugNoSeatsLeft_1 - 1;
                    seatLeft <= plugNoSeatsLeft_1;
                    seatReady <= 1;
                end
                else begin
                    notExactFund <= 1;
                end
            end
        end
        else begin
            seatUnavailable <= 1;
        end
    end
    else begin
        if((plugSeatsLeft_2+plugNoSeatsLeft_2) > 0) begin
            if(plugSeatsLeft_2 > 0) begin
                if(currentMoney >= entranceFee) begin
                    currentMoney <= currentMoney - entranceFee;
                    plugSeatsLeft_2 <= plugSeatsLeft_2 - 1;
                    seatLeft <= plugSeatsLeft_2;
                    seatReady <= 1;
                end
                else begin
                    insufficientFund <= 1;
                end
            end
            else begin
                plugSeatUnavailable <= 1;
            end
        end
        else begin
            seatUnavailable <= 1;
        end
    end
end

endmodule
