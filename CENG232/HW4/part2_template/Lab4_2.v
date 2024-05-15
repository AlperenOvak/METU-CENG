`timescale 1ns / 1ps

module lab4_2(

							input [1:0] mode,//Student Entrance Mode 01, Student Exit Mode 00,Search Mode 10,List Mode 11
							input [5:0] userID,//USERID
							input CLK,
							output reg [1:0] selectedAreaId,// show user selected area 
							output reg [5:0] numberOfInsideUser, //seatLeft
							output reg [5:0] listOutput,
							output reg AlreadyInside, //update 	
							output reg NotInside  //update 
    );

//locals

						

							initial begin
				
							end

							always @(posedge CLK)
							begin
							
							end

						endmodule