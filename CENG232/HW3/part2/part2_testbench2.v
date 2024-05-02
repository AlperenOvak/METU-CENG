`timescale 1ns / 1ps

module SeatingSystemTestbench;
    // Inputs
    reg [5:0] money;
    reg CLK;
    reg plugAvailability;
    reg [1:0] selectedArea;

    // Outputs
    wire [5:0] moneyLeft;
    wire [4:0] seatLeft;
    wire seatUnavailable;
    wire insufficientFund;
    wire notExactFund;
    wire invalidPlugSeat;
    wire plugSeatUnavailable;
    wire seatReady;
	 
	 // Vars for test
	 integer grade,i, gradeLocal;
    reg caseFailed;

    // Instantiate the Unit Under Test (UUT)
     lab3_2 SeatingSystem (
        .money(money),
        .CLK(CLK),
        .plugAvailability(plugAvailability),
        .selectedArea(selectedArea),
        .moneyLeft(moneyLeft),
        .seatLeft(seatLeft),
        .seatUnavailable(seatUnavailable),
        .insufficientFund(insufficientFund),
        .notExactFund(notExactFund),
        .invalidPlugSeat(invalidPlugSeat),
        .plugSeatUnavailable(plugSeatUnavailable),
        .seatReady(seatReady)
    );

    // Clock generation
    initial CLK = 1;
	 always #5 CLK = ~CLK;

    // Test scenarios
	 initial begin
		 $display("Starting Testbench");
		 grade = 0;
		 caseFailed = 1;
			
		 /////////////////////////////////////
		 //////// TESTS FOR LOUD AREA ////////
		 /////////////////////////////////////
	 
		 // Test Case 1: Attempt to reserve a seat with plug in the Loud area - invalidPlugseat
		 // No seatLeft and moneyLeft checks ??
		 #1;
		 caseFailed = 0;
		 // Set the inputs
		 selectedArea = 0'b00;
		 plugAvailability = 1; 
		 //money=30;
		 
		 #10;
		 gradeLocal = 0; // Set local grade
		 $display("Attempt to reserve a seat with plug in the Loud area - invalidPlugseat");
		  $display("Values before checks: moneyLeft ==%0d, seatLeft ==%0d,invalidPlugSeat=%0d, plugSeatUnavailable=%0d, notExactFund=%0d, insufficientFund=%0d, seatUnavailable=%0d, seatReady=%0d", moneyLeft, seatLeft, invalidPlugSeat, plugSeatUnavailable, notExactFund, insufficientFund, seatUnavailable, seatReady);
		 if (seatLeft == 15) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (invalidPlugSeat == 1) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (plugSeatUnavailable == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (notExactFund == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (insufficientFund == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatUnavailable == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatReady == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (caseFailed) begin
			  $display("Failed Case 1");
			  gradeLocal = gradeLocal >> 2;
		 end
		 else $display("Passed Case 1");
		 grade = grade + gradeLocal;
		 
		 // 1 continued, insufficient amount of money is given as input
		 caseFailed = 0;
		 // Set the inputs
		 selectedArea = 0'b00;
		 plugAvailability = 0; 
		 money=3; 
		 
		 #10;
		 gradeLocal = 0; // Set local grade
		 $display("Insufficient amount of money is given as input");
		  $display("Values before checks: moneyLeft ==%0d, seatLeft ==%0d,invalidPlugSeat=%0d, plugSeatUnavailable=%0d, notExactFund=%0d, insufficientFund=%0d, seatUnavailable=%0d, seatReady=%0d", moneyLeft, seatLeft, invalidPlugSeat, plugSeatUnavailable, notExactFund, insufficientFund, seatUnavailable, seatReady);
		 if (moneyLeft == 3) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatLeft == 15) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (invalidPlugSeat == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (plugSeatUnavailable == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (notExactFund == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (insufficientFund == 1) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatUnavailable == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatReady == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (caseFailed) begin
			  $display("Failed Case 1.1");
			  gradeLocal = gradeLocal >> 2;
		 end
		 else $display("Passed Case 1.1");
		 grade = grade + gradeLocal;
		 
		 // 1.1 continued, reserve a seat
		 caseFailed = 0;
		 // Set the inputs
		 selectedArea = 0'b00;
		 plugAvailability = 0; 
		 money=30;
		 
		 #10;
		 gradeLocal = 0; // Set local grade
		 $display("A seat is reserved successfully");
		  $display("Values before checks: moneyLeft ==%0d, seatLeft ==%0d,invalidPlugSeat=%0d, plugSeatUnavailable=%0d, notExactFund=%0d, insufficientFund=%0d, seatUnavailable=%0d, seatReady=%0d", moneyLeft, seatLeft, invalidPlugSeat, plugSeatUnavailable, notExactFund, insufficientFund, seatUnavailable, seatReady);
		 if (moneyLeft == 20) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatLeft == 14) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (invalidPlugSeat == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (plugSeatUnavailable == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (notExactFund == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (insufficientFund == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatUnavailable == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatReady == 1) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (caseFailed) begin
			  $display("Failed Case 1.2");
			  gradeLocal = gradeLocal >> 2;
		 end
		 else $display("Passed Case 1.2");
		 grade = grade + gradeLocal;
		 
		 #140; // reserve all seats after 14 more clcok cycle
		 $display("All seats are reserved successfully after 14 more clock cycle");
		 $display("Values before checks: moneyLeft ==%0d, seatLeft ==%0d,invalidPlugSeat=%0d, plugSeatUnavailable=%0d, notExactFund=%0d, insufficientFund=%0d, seatUnavailable=%0d, seatReady=%0d", moneyLeft, seatLeft, invalidPlugSeat, plugSeatUnavailable, notExactFund, insufficientFund, seatUnavailable, seatReady);
		 #10; // attempt to reserve one more seat when all are reserved
		 $display("Attempt to reserve one more seat when all are reserved");
		 $display("Values before checks: moneyLeft ==%0d, seatLeft ==%0d,invalidPlugSeat=%0d, plugSeatUnavailable=%0d, notExactFund=%0d, insufficientFund=%0d, seatUnavailable=%0d, seatReady=%0d", moneyLeft, seatLeft, invalidPlugSeat, plugSeatUnavailable, notExactFund, insufficientFund, seatUnavailable, seatReady);

		 plugAvailability = 1;
		 $display("Attempt to reserve one more seat with a plug when all seats are reserved, prioritizes seatUnavailable error rather than invalidPlugSeat");
		 $display("Values before checks: moneyLeft ==%0d, seatLeft ==%0d,invalidPlugSeat=%0d, plugSeatUnavailable=%0d, notExactFund=%0d, insufficientFund=%0d, seatUnavailable=%0d, seatReady=%0d", moneyLeft, seatLeft, invalidPlugSeat, plugSeatUnavailable, notExactFund, insufficientFund, seatUnavailable, seatReady);

		 $display(" ");
		 
		 /////////////////////////////////////
		 //////// TESTS FOR QUIET AREA ///////
		 /////////////////////////////////////
		 
		 // Test Case 5: Successfully reserve a seat with plug from the quiet area
		 #1;
		 caseFailed = 0;
		 // Set the inputs
		 selectedArea = 0'b01;
		 plugAvailability = 1; 
		 money = 21;
		 #10;
		 gradeLocal = 0; // Set local grade
		 $display("Reserve a seat with plug");
		 $display("Values before checks: moneyLeft ==%0d, seatLeft ==%0d,invalidPlugSeat=%0d, plugSeatUnavailable=%0d, notExactFund=%0d, insufficientFund=%0d, seatUnavailable=%0d, seatReady=%0d", moneyLeft, seatLeft, invalidPlugSeat, plugSeatUnavailable, notExactFund, insufficientFund, seatUnavailable, seatReady);
		 // Check outputs
		 if (moneyLeft == 1) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatLeft == 9) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (invalidPlugSeat == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (plugSeatUnavailable == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (notExactFund == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (insufficientFund == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatUnavailable == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatReady == 1) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (caseFailed) begin
			  $display("Failed Case 5");
			  gradeLocal = gradeLocal >> 2;
		 end
		 else $display("Passed Case 5");
		 grade = grade + gradeLocal;
		 
		 // 5 continued, Reserve a seat with plug
		 caseFailed = 0;
		 // Set the inputs
		 selectedArea = 0'b01;
		 plugAvailability = 1; 
		 money = 21;
		 #10;
		 gradeLocal = 0; // Set local grade
		 $display("Reserve a seat with plug");
		 $display("Values before checks: moneyLeft ==%0d, seatLeft ==%0d,invalidPlugSeat=%0d, plugSeatUnavailable=%0d, notExactFund=%0d, insufficientFund=%0d, seatUnavailable=%0d, seatReady=%0d", moneyLeft, seatLeft, invalidPlugSeat, plugSeatUnavailable, notExactFund, insufficientFund, seatUnavailable, seatReady);
		 // Check outputs
		 if (moneyLeft == 1) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatLeft == 8) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (invalidPlugSeat == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (plugSeatUnavailable == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (notExactFund == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (insufficientFund == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatUnavailable == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatReady == 1) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (caseFailed) begin
			  $display("Failed Case 5.1");
			  gradeLocal = gradeLocal >> 2;
		 end
		 else $display("Passed Case 5.1");
		 grade = grade + gradeLocal;
		 
		 // 5.1 continued, Reserve a seat with non-plug
		 caseFailed = 0;
		 // Set the inputs
		 selectedArea = 0'b01;
		 plugAvailability = 0; 
		 money = 21;
		 #10;
		 gradeLocal = 0; // Set local grade
		 $display("Reserve a seat with non-plug");
		 $display("Values before checks: moneyLeft ==%0d, seatLeft ==%0d,invalidPlugSeat=%0d, plugSeatUnavailable=%0d, notExactFund=%0d, insufficientFund=%0d, seatUnavailable=%0d, seatReady=%0d", moneyLeft, seatLeft, invalidPlugSeat, plugSeatUnavailable, notExactFund, insufficientFund, seatUnavailable, seatReady);
		 // Check outputs
		 if (moneyLeft == 1) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatLeft == 14) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (invalidPlugSeat == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (plugSeatUnavailable == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (notExactFund == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (insufficientFund == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatUnavailable == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatReady == 1) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (caseFailed) begin
			  $display("Failed Case 5.2");
			  gradeLocal = gradeLocal >> 2;
		 end
		 else $display("Passed Case 5.2");
		 grade = grade + gradeLocal;
		 
		 // 5.2 continued, Reserve a seat with non-plug
		 caseFailed = 0;
		 // Set the inputs
		 selectedArea = 0'b01;
		 plugAvailability = 0; 
		 money = 21;
		 #10;
		 gradeLocal = 0; // Set local grade
		 $display("Reserve a seat with non-plug");
		 $display("Values before checks: moneyLeft ==%0d, seatLeft ==%0d,invalidPlugSeat=%0d, plugSeatUnavailable=%0d, notExactFund=%0d, insufficientFund=%0d, seatUnavailable=%0d, seatReady=%0d", moneyLeft, seatLeft, invalidPlugSeat, plugSeatUnavailable, notExactFund, insufficientFund, seatUnavailable, seatReady);
		 // Check outputs
		 if (moneyLeft == 1) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatLeft == 13) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (invalidPlugSeat == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (plugSeatUnavailable == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (notExactFund == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (insufficientFund == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatUnavailable == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatReady == 1) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (caseFailed) begin
			  $display("Failed Case 5.3");
			  gradeLocal = gradeLocal >> 2;
		 end
		 else $display("Passed Case 5.3");
		 grade = grade + gradeLocal;
		 
		 // 5.3 continued, Not enough money for seat without plug
		 caseFailed = 0;
		 // Set the inputs
		 selectedArea = 0'b01;
		 plugAvailability = 0; 
		 money = 8;
		 #10;
		 gradeLocal = 0; // Set local grade
		 $display("Not enough money for seat without plug");
		 $display("Values before checks: moneyLeft ==%0d, seatLeft ==%0d,invalidPlugSeat=%0d, plugSeatUnavailable=%0d, notExactFund=%0d, insufficientFund=%0d, seatUnavailable=%0d, seatReady=%0d", moneyLeft, seatLeft, invalidPlugSeat, plugSeatUnavailable, notExactFund, insufficientFund, seatUnavailable, seatReady);
		 // Check outputs
		 if (moneyLeft == 8) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatLeft == 13) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (invalidPlugSeat == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (plugSeatUnavailable == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (notExactFund == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (insufficientFund == 1) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatUnavailable == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatReady == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (caseFailed) begin
			  $display("Failed Case 5.4");
			  gradeLocal = gradeLocal >> 2;
		 end
		 else $display("Passed Case 5.4");
		 grade = grade + gradeLocal;
		 
		 // 5.4 continued, Not enough money for seat with plug
		 caseFailed = 0;
		 // Set the inputs
		 selectedArea = 0'b01;
		 plugAvailability = 1; 
		 money = 8;
		 #10;
		 gradeLocal = 0; // Set local grade
		 $display("Not enough money for seat with plug");
		 $display("Values before checks: moneyLeft ==%0d, seatLeft ==%0d,invalidPlugSeat=%0d, plugSeatUnavailable=%0d, notExactFund=%0d, insufficientFund=%0d, seatUnavailable=%0d, seatReady=%0d", moneyLeft, seatLeft, invalidPlugSeat, plugSeatUnavailable, notExactFund, insufficientFund, seatUnavailable, seatReady);
		 // Check outputs
		 if (moneyLeft == 8) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatLeft == 8) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (invalidPlugSeat == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (plugSeatUnavailable == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (notExactFund == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (insufficientFund == 1) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatUnavailable == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatReady == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (caseFailed) begin
			  $display("Failed Case 5.5");
			  gradeLocal = gradeLocal >> 2;
		 end
		 else $display("Passed Case 5.5");
		 grade = grade + gradeLocal;
		 
		 // 5.5 continued, Reserve a seat without plug
		 caseFailed = 0;
		 // Set the inputs
		 selectedArea = 0'b01;
		 plugAvailability = 0; 
		 money = 21;
		 #10;
		 gradeLocal = 0; // Set local grade
		 $display("Reserve a seat without plug");
		 $display("Values before checks: moneyLeft ==%0d, seatLeft ==%0d,invalidPlugSeat=%0d, plugSeatUnavailable=%0d, notExactFund=%0d, insufficientFund=%0d, seatUnavailable=%0d, seatReady=%0d", moneyLeft, seatLeft, invalidPlugSeat, plugSeatUnavailable, notExactFund, insufficientFund, seatUnavailable, seatReady);
		 // Check outputs
		 if (moneyLeft == 1) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatLeft == 12) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (invalidPlugSeat == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (plugSeatUnavailable == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (notExactFund == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (insufficientFund == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatUnavailable == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatReady == 1) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (caseFailed) begin
			  $display("Failed Case 5.6");
			  gradeLocal = gradeLocal >> 2;
		 end
		 else $display("Passed Case 5.6");
		 grade = grade + gradeLocal;
		 
		 #120; // Change the value with 100 to check plugSeatUnavailable output
		 $display("Reserve all non-plug seats");
		 $display("Values before checks: moneyLeft ==%0d, seatLeft ==%0d,invalidPlugSeat=%0d, plugSeatUnavailable=%0d, notExactFund=%0d, insufficientFund=%0d, seatUnavailable=%0d, seatReady=%0d", moneyLeft, seatLeft, invalidPlugSeat, plugSeatUnavailable, notExactFund, insufficientFund, seatUnavailable, seatReady);
		 #10;
		 $display("Reserve one more non-plug seats when non-exist, seatUnavailable");
		 $display("Values before checks: moneyLeft ==%0d, seatLeft ==%0d,invalidPlugSeat=%0d, plugSeatUnavailable=%0d, notExactFund=%0d, insufficientFund=%0d, seatUnavailable=%0d, seatReady=%0d", moneyLeft, seatLeft, invalidPlugSeat, plugSeatUnavailable, notExactFund, insufficientFund, seatUnavailable, seatReady);

		 // 5.6 continued, Reserve a seat with plug
		 caseFailed = 0;
		 // Set the inputs
		 selectedArea = 0'b01;
		 plugAvailability = 1; 
		 money = 21;
		 #10;
		 gradeLocal = 0; // Set local grade
		 $display("Reserve a seat with plug");
		 $display("Values before checks: moneyLeft ==%0d, seatLeft ==%0d,invalidPlugSeat=%0d, plugSeatUnavailable=%0d, notExactFund=%0d, insufficientFund=%0d, seatUnavailable=%0d, seatReady=%0d", moneyLeft, seatLeft, invalidPlugSeat, plugSeatUnavailable, notExactFund, insufficientFund, seatUnavailable, seatReady);
		 // Check outputs
		 if (moneyLeft == 1) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatLeft == 7) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (invalidPlugSeat == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (plugSeatUnavailable == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (notExactFund == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (insufficientFund == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatUnavailable == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatReady == 1) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (caseFailed) begin
			  $display("Failed Case 5.7");
			  gradeLocal = gradeLocal >> 2;
		 end
		 else $display("Passed Case 5.7");
		 grade = grade + gradeLocal;
		 
		 #70;
		 $display("Reserve all plug seats");
		 $display("Values before checks: moneyLeft ==%0d, seatLeft ==%0d,invalidPlugSeat=%0d, plugSeatUnavailable=%0d, notExactFund=%0d, insufficientFund=%0d, seatUnavailable=%0d, seatReady=%0d", moneyLeft, seatLeft, invalidPlugSeat, plugSeatUnavailable, notExactFund, insufficientFund, seatUnavailable, seatReady);
		 #10;
		 $display("Reserve one more non-plug seats when non-exist, plugSeatUnavailable. If all seats are reserved, gives seatUnavailable as specified in PDF");
		 $display("Values before checks: moneyLeft ==%0d, seatLeft ==%0d,invalidPlugSeat=%0d, plugSeatUnavailable=%0d, notExactFund=%0d, insufficientFund=%0d, seatUnavailable=%0d, seatReady=%0d", moneyLeft, seatLeft, invalidPlugSeat, plugSeatUnavailable, notExactFund, insufficientFund, seatUnavailable, seatReady);

		 
		 $display(" ");

		 /////////////////////////////////////
		 ///// TESTS FOR INDIVIDUAL AREA /////
		 /////////////////////////////////////
		 
		 // Test Case 11: ATTEMPY TO RESERVE W INSUFFICIENT MONEY
		 #1;
		 caseFailed = 0;
		 // Set the inputs
		 selectedArea = 0'b11;
		 money = 30;
		 #10;
		 gradeLocal = 0; // Set local grade
		 $display("Reserve a seat successfully");
		  $display("Values before checks: moneyLeft ==%0d, seatLeft ==%0d,invalidPlugSeat=%0d, plugSeatUnavailable=%0d, notExactFund=%0d, insufficientFund=%0d, seatUnavailable=%0d, seatReady=%0d", moneyLeft, seatLeft, invalidPlugSeat, plugSeatUnavailable, notExactFund, insufficientFund, seatUnavailable, seatReady);
		 // Check outputs
		 if (moneyLeft == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatLeft == 19) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (invalidPlugSeat == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (plugSeatUnavailable == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (notExactFund == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (insufficientFund == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatUnavailable == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatReady == 1) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (caseFailed) begin
			  $display("Failed Case 11");
			  gradeLocal = gradeLocal >> 2;
		 end
		 else $display("Passed Case 11");
		 grade = grade + gradeLocal; 
		 
		 // 11 continued
		 caseFailed = 0;
		 // Set the inputs
		 selectedArea = 0'b11;
		 money = 30;
		 #10;
		 gradeLocal = 0; // Set local grade
		 $display("Reserve a seat successfully");
		  $display("Values before checks: moneyLeft ==%0d, seatLeft ==%0d,invalidPlugSeat=%0d, plugSeatUnavailable=%0d, notExactFund=%0d, insufficientFund=%0d, seatUnavailable=%0d, seatReady=%0d", moneyLeft, seatLeft, invalidPlugSeat, plugSeatUnavailable, notExactFund, insufficientFund, seatUnavailable, seatReady);
		 // Check outputs
		 if (moneyLeft == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatLeft == 18) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (invalidPlugSeat == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (plugSeatUnavailable == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (notExactFund == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (insufficientFund == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatUnavailable == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatReady == 1) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (caseFailed) begin
			  $display("Failed Case 11.1");
			  gradeLocal = gradeLocal >> 2;
		 end
		 else $display("Passed Case 11.1");
		 grade = grade + gradeLocal; 
		 
		 // 11.1 continued
		 caseFailed = 0;
		 // Set the inputs
		 selectedArea = 0'b11;
		 money = 3;
		 #10;
		 gradeLocal = 0; // Set local grade
		 $display("The exact amount of money was not given");
		  $display("Values before checks: moneyLeft ==%0d, seatLeft ==%0d,invalidPlugSeat=%0d, plugSeatUnavailable=%0d, notExactFund=%0d, insufficientFund=%0d, seatUnavailable=%0d, seatReady=%0d", moneyLeft, seatLeft, invalidPlugSeat, plugSeatUnavailable, notExactFund, insufficientFund, seatUnavailable, seatReady);
		 // Check outputs
		 if (moneyLeft == 3) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatLeft == 18) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (invalidPlugSeat == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (plugSeatUnavailable == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (notExactFund == 1) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (insufficientFund == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatUnavailable == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatReady == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (caseFailed) begin
			  $display("Failed Case 11.2");
			  gradeLocal = gradeLocal >> 2;
		 end
		 else $display("Passed Case 11.2");
		 grade = grade + gradeLocal; 
		 
		 // 11.2 continued
		 caseFailed = 0;
		 // Set the inputs
		 selectedArea = 0'b11;
		 money = 30;
		 #10;
		 gradeLocal = 0; // Set local grade
		 $display("Reserve a seat successfully");
		  $display("Values before checks: moneyLeft ==%0d, seatLeft ==%0d,invalidPlugSeat=%0d, plugSeatUnavailable=%0d, notExactFund=%0d, insufficientFund=%0d, seatUnavailable=%0d, seatReady=%0d", moneyLeft, seatLeft, invalidPlugSeat, plugSeatUnavailable, notExactFund, insufficientFund, seatUnavailable, seatReady);
		 // Check outputs
		 if (moneyLeft == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatLeft == 17) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (invalidPlugSeat == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (plugSeatUnavailable == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (notExactFund == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (insufficientFund == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatUnavailable == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatReady == 1) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (caseFailed) begin
			  $display("Failed Case 11.3");
			  gradeLocal = gradeLocal >> 2;
		 end
		 else $display("Passed Case 11.3");
		 grade = grade + gradeLocal; 
		 
		 #170;
		 $display("All seats are reserved successfully after 17 more clock cycle");
		 $display("Values before checks: moneyLeft ==%0d, seatLeft ==%0d,invalidPlugSeat=%0d, plugSeatUnavailable=%0d, notExactFund=%0d, insufficientFund=%0d, seatUnavailable=%0d, seatReady=%0d", moneyLeft, seatLeft, invalidPlugSeat, plugSeatUnavailable, notExactFund, insufficientFund, seatUnavailable, seatReady);
		 #10;
		 $display("Attempt to reserve one more seat when all are reserved");
		 $display("Values before checks: moneyLeft ==%0d, seatLeft ==%0d,invalidPlugSeat=%0d, plugSeatUnavailable=%0d, notExactFund=%0d, insufficientFund=%0d, seatUnavailable=%0d, seatReady=%0d", moneyLeft, seatLeft, invalidPlugSeat, plugSeatUnavailable, notExactFund, insufficientFund, seatUnavailable, seatReady);


	end



endmodule
