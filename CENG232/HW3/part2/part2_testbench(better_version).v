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
		 
		 #10;
		 gradeLocal = 0; // Set local grade
		 // $display("Values before checks: moneyLeft ==%0d, seatLeft ==%0d,invalidPlugSeat=%0d, plugSeatUnavailable=%0d, notExactFund=%0d, insufficientFund=%0d, seatUnavailable=%0d, seatReady=%0d", moneyLeft, seatLeft, invalidPlugSeat, plugSeatUnavailable, notExactFund, insufficientFund, seatUnavailable, seatReady);
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
		 
		 // Test Case 2: Attempt to reserve a seat without plug and adequate money in the Loud area - no problemo! (at least there should not be)
		 
		 #1;
		 caseFailed = 0;
		 // Set the inputs
		 selectedArea = 0'b00;
		 plugAvailability = 0; 
		 money = 22;
		 
		 #10;
		 gradeLocal = 0; // Set local grade
		 // $display("Values before checks: moneyLeft ==%0d, seatLeft ==%0d,invalidPlugSeat=%0d, plugSeatUnavailable=%0d, notExactFund=%0d, insufficientFund=%0d, seatUnavailable=%0d, seatReady=%0d", moneyLeft, seatLeft, invalidPlugSeat, plugSeatUnavailable, notExactFund, insufficientFund, seatUnavailable, seatReady);
		 if (seatLeft == 14) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (invalidPlugSeat == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (plugSeatUnavailable == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (notExactFund == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (insufficientFund == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatUnavailable == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatReady == 1) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (moneyLeft == 12) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (caseFailed) begin
			  $display("Failed Case 2");
			  gradeLocal = gradeLocal >> 2;
		 end
		 else $display("Passed Case 2");
		 grade = grade + gradeLocal;
		 
		 // Test Case 3: Attempt to reserve a seat without plug but inadequate money in the Loud area // Broke guy case
         
         #1;
		 caseFailed = 0;
		 // Set the inputs
		 selectedArea = 0'b00;
		 plugAvailability = 0; 
		 money = 2;
		 
		 #10;
		 gradeLocal = 0; // Set local grade
		 // $display("Values before checks: moneyLeft ==%0d, seatLeft ==%0d,invalidPlugSeat=%0d, plugSeatUnavailable=%0d, notExactFund=%0d, insufficientFund=%0d, seatUnavailable=%0d, seatReady=%0d", moneyLeft, seatLeft, invalidPlugSeat, plugSeatUnavailable, notExactFund, insufficientFund, seatUnavailable, seatReady);
		 if (seatLeft == 14) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (invalidPlugSeat == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (plugSeatUnavailable == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (notExactFund == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (insufficientFund == 1) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatUnavailable == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatReady == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (moneyLeft == 2) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (caseFailed) begin
			  $display("Failed Case 3");
			  gradeLocal = gradeLocal >> 2;
		 end
		 else $display("Passed Case 3");
		 grade = grade + gradeLocal;
		 
		 // Test Case 4: Attempt to reserve a seat in the Loud area but all seats are occupied // Metu library special
		 
		 #1;
		 caseFailed = 0;
		 // Set the inputs
		 selectedArea = 0'b00;
		 plugAvailability = 0; 
		 money = 13;
		 
		 #10;#10;#10;#10;#10;#10;#10;#10;#10;#10;#10;#10;#10;#10;#10;
		 gradeLocal = 0; // Set local grade
		 // $display("Values before checks: moneyLeft ==%0d, seatLeft ==%0d,invalidPlugSeat=%0d, plugSeatUnavailable=%0d, notExactFund=%0d, insufficientFund=%0d, seatUnavailable=%0d, seatReady=%0d", moneyLeft, seatLeft, invalidPlugSeat, plugSeatUnavailable, notExactFund, insufficientFund, seatUnavailable, seatReady);
		 if (seatLeft == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (invalidPlugSeat == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (plugSeatUnavailable == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (notExactFund == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (insufficientFund == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatUnavailable == 1) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatReady == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (moneyLeft == 13) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (caseFailed) begin
			  $display("Failed Case 4");
			  gradeLocal = gradeLocal >> 2;
		 end
		 else $display("Passed Case 4");
		 grade = grade + gradeLocal;
		 
		 //Loud seats are full -- reset them for new test cases
		 
		 
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
		 //$display("Values before checks: moneyLeft ==%0d, seatLeft ==%0d,invalidPlugSeat=%0d, plugSeatUnavailable=%0d, notExactFund=%0d, insufficientFund=%0d, seatUnavailable=%0d, seatReady=%0d", moneyLeft, seatLeft, invalidPlugSeat, plugSeatUnavailable, notExactFund, insufficientFund, seatUnavailable, seatReady);
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

         // Test Case 6: Successfully reserve a seat without plug from the quiet area
         
         #1;
		 caseFailed = 0;
		 // Set the inputs
		 selectedArea = 0'b01;
		 plugAvailability = 0; 
		 money = 22;
		 
		 #10;
		 gradeLocal = 0; // Set local grade
		 
		 if (moneyLeft == 2) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatLeft == 14) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (invalidPlugSeat == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (plugSeatUnavailable == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (notExactFund == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (insufficientFund == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatUnavailable == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatReady == 1) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (caseFailed) begin
			  $display("Failed Case 6");
			  gradeLocal = gradeLocal >> 2;
		 end
		 else $display("Passed Case 6");
		 grade = grade + gradeLocal;
         
         // Test Case 7: Unsuccessful try to reserve a seat with plug from the quiet area (not enough money)
         
         #1;
		 caseFailed = 0;
		 // Set the inputs
		 selectedArea = 0'b01;
		 plugAvailability = 1; 
		 money = 1;
		 
		 #10;
		 gradeLocal = 0; // Set local grade
		 
		 if (moneyLeft == 1) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatLeft == 9) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (invalidPlugSeat == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (plugSeatUnavailable == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (notExactFund == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (insufficientFund == 1) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatUnavailable == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatReady == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (caseFailed) begin
			  $display("Failed Case 7");
			  gradeLocal = gradeLocal >> 2;
		 end
		 else $display("Passed Case 7");
		 grade = grade + gradeLocal;
         
         // Test Case 8: Unsuccessful try to reserve a seat without plug from the quiet area (not enough money)
         
         #1;
		 caseFailed = 0;
		 // Set the inputs
		 selectedArea = 0'b01;
		 plugAvailability = 0; 
		 money = 1;
		 
		 #10;
		 gradeLocal = 0; // Set local grade
		 
		 if (moneyLeft == 1) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatLeft == 14) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (invalidPlugSeat == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (plugSeatUnavailable == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (notExactFund == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (insufficientFund == 1) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatUnavailable == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatReady == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (caseFailed) begin
			  $display("Failed Case 8");
			  gradeLocal = gradeLocal >> 2;
		 end
		 else $display("Passed Case 8");
		 grade = grade + gradeLocal;
         
         // Test Case 9: 3 Consecutive reservations for seats with plug from the quiet area
         
         #1;
		 caseFailed = 0;
		 // Set the inputs
		 selectedArea = 0'b01;
		 plugAvailability = 1; 
		 money = 21;
		 
		 #10;#10;#10;
		 gradeLocal = 0; // Set local grade
		 
		 if (moneyLeft == 1) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatLeft == 6) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (invalidPlugSeat == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (plugSeatUnavailable == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (notExactFund == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (insufficientFund == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatUnavailable == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatReady == 1) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (caseFailed) begin
			  $display("Failed Case 9");
			  gradeLocal = gradeLocal >> 2;
		 end
		 else $display("Passed Case 9");
		 grade = grade + gradeLocal;
         
         // Test Case 10: Reserving all seats without plug from the quiet area(CENG'ciler geliyo)
        
         #1;
		 caseFailed = 0;
		 // Set the inputs
		 selectedArea = 0'b01;
		 plugAvailability = 0; 
		 money = 27;
		 
		 #10;#10;#10;#10;#10;#10;#10;#10;#10;#10;#10;#10;#10;#10;
		 gradeLocal = 0; // Set local grade
		 
		 if (moneyLeft == 7) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatLeft == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (invalidPlugSeat == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (plugSeatUnavailable == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (notExactFund == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (insufficientFund == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatUnavailable == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatReady == 1) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (caseFailed) begin
			  $display("Failed Case 10");
			  gradeLocal = gradeLocal >> 2;
		 end
		 else $display("Passed Case 10");
		 grade = grade + gradeLocal;
        
         //All seats without plug in the quiet area are occupied.
        
        
         
		 /////////////////////////////////////
		 ///// TESTS FOR INDIVIDUAL AREA /////
		 /////////////////////////////////////
		 
		 // Test Case 11: ATTEMPT TO RESERVE W INSUFFICIENT MONEY
		 #1;
		 caseFailed = 0;
		 // Set the inputs
		 selectedArea = 0'b11;
		 money = 3;
		 
		 #10;
		 gradeLocal = 0; // Set local grade
		 
		 if (moneyLeft == 3) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatLeft == 20) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (invalidPlugSeat == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (plugSeatUnavailable == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (notExactFund == 1) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (insufficientFund == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatUnavailable == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatReady == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (caseFailed) begin
			  $display("Failed Case 11");
			  gradeLocal = gradeLocal >> 2;
		 end
		 else $display("Passed Case 11");
		 grade = grade + gradeLocal; 
		 
		 // Test Case 12: requesting a seat without a plug in the individual area
		 
		 #1;
		 caseFailed = 0;
		 // Set the inputs
		 selectedArea = 0'b11;
		 plugAvailability = 0;
		 money = 30;
		 
		 #10;
		 gradeLocal = 0; // Set local grade
		 
		 if (moneyLeft == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatLeft == 19) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (invalidPlugSeat == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (plugSeatUnavailable == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (notExactFund == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (insufficientFund == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatUnavailable == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatReady == 1) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (caseFailed) begin
			  $display("Failed Case 12");
			  gradeLocal = gradeLocal >> 2;
		 end
		 else $display("Passed Case 12");
		 grade = grade + gradeLocal; 
		 
		 // Test Case 13: Sufficient but not exact money in the individual area(learn math boy)
		 
		 #1;
		 caseFailed = 0;
		 // Set the inputs
		 selectedArea = 0'b11;
		 money = 31;
		 
		 #10;
		 gradeLocal = 0; // Set local grade
		 
		 if (moneyLeft == 31) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatLeft == 19) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (invalidPlugSeat == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (plugSeatUnavailable == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (notExactFund == 1) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (insufficientFund == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatUnavailable == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatReady == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (caseFailed) begin
			  $display("Failed Case 13");
			  gradeLocal = gradeLocal >> 2;
		 end
		 else $display("Passed Case 13");
		 grade = grade + gradeLocal; 
		 
		 // Test Case 14: Exact money, seat with a plug in the individual area
		 
		 #1;
		 caseFailed = 0;
		 // Set the inputs
		 selectedArea = 0'b11;
		 plugAvailability = 1;
		 money = 30;
		 
		 #10;
		 gradeLocal = 0; // Set local grade
		 
		 if (moneyLeft == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatLeft == 18) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (invalidPlugSeat == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (plugSeatUnavailable == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (notExactFund == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (insufficientFund == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatUnavailable == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatReady == 1) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (caseFailed) begin
			  $display("Failed Case 14");
			  gradeLocal = gradeLocal >> 2;
		 end
		 else $display("Passed Case 14");
		 grade = grade + gradeLocal; 
		 
		 // Test Case 15: Occupying all seats in the individual area
		 
		 #1;
		 caseFailed = 0;
		 // Set the inputs
		 selectedArea = 0'b11;
		 money = 30;
		 
		 #10;#10;#10;#10;#10;#10;#10;#10;#10;#10;#10;#10;#10;#10;#10;#10;#10;#10;
		 gradeLocal = 0; // Set local grade
		 
		 if (moneyLeft == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatLeft == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (invalidPlugSeat == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (plugSeatUnavailable == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (notExactFund == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (insufficientFund == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatUnavailable == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatReady == 1) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (caseFailed) begin
			  $display("Failed Case 15");
			  gradeLocal = gradeLocal >> 2;
		 end
		 else $display("Passed Case 15");
		 grade = grade + gradeLocal; 
		 
		 //Individual seats are all occupied at this point do not forget
		 
		 // Test Case 16: Trying to occupying non-existent seats in the individual area (??!)
		 
		 #1;
		 caseFailed = 0;
		 // Set the inputs
		 selectedArea = 0'b11;
		 money = 30;
		 
		 #10;
		 gradeLocal = 0; // Set local grade
		 
		 if (moneyLeft == 30) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatLeft == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (invalidPlugSeat == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (plugSeatUnavailable == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (notExactFund == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (insufficientFund == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatUnavailable == 1) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatReady == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (caseFailed) begin
			  $display("Failed Case 16");
			  gradeLocal = gradeLocal >> 2;
		 end
		 else $display("Passed Case 16");
		 grade = grade + gradeLocal; 
		 
		 // Test Case 17: Testing for warning sign priorities(Individual area)
		 
         #1;
		 caseFailed = 0;
		 // Set the inputs
		 selectedArea = 0'b11;
		 money = 3;
		 
		 #10;
		 gradeLocal = 0; // Set local grade
		 
		 if (moneyLeft == 3) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatLeft == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (invalidPlugSeat == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (plugSeatUnavailable == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (notExactFund == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (insufficientFund == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatUnavailable == 1) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatReady == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (caseFailed) begin
			  $display("Failed Case 17");
			  gradeLocal = gradeLocal >> 2;
		 end
		 else $display("Passed Case 17");
		 grade = grade + gradeLocal; 
		 
		 // Test Case 18: Testing for warning sign priorities(Quiet area)
		 
		 #1;
		 caseFailed = 0;
		 // Set the inputs
		 selectedArea = 0'b01;
		 plugAvailability = 0; 
		 money = 1;
		 
		 #10;
		 gradeLocal = 0; // Set local grade
		 
		 if (moneyLeft == 1) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatLeft == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (invalidPlugSeat == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (plugSeatUnavailable == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (notExactFund == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (insufficientFund == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatUnavailable == 1) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatReady == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (caseFailed) begin
			  $display("Failed Case 18");
			  gradeLocal = gradeLocal >> 2;
		 end
		 else $display("Passed Case 18");
		 grade = grade + gradeLocal;
		 
		 // Test Case 19: Testing for warning sign priorities(Loud area)
		 
		 #1;
		 caseFailed = 0;
		 // Set the inputs
		 selectedArea = 0'b00;
		 plugAvailability = 0; 
		 money = 3;
		 
		 #10;
		 gradeLocal = 0; // Set local grade
		 
		 if (moneyLeft == 3) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatLeft == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (invalidPlugSeat == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (plugSeatUnavailable == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (notExactFund == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (insufficientFund == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatUnavailable == 1) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatReady == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (caseFailed) begin
			  $display("Failed Case 19");
			  gradeLocal = gradeLocal >> 2;
		 end
		 else $display("Passed Case 19");
		 grade = grade + gradeLocal;
		 
		 // Test Case 20: Testing for warning sign priorities(Loud area)(All Warnings)
		 
		 #1;
		 caseFailed = 0;
		 // Set the inputs
		 selectedArea = 0'b00;
		 plugAvailability = 1; 
		 money = 7;
		 
		 #10;
		 gradeLocal = 0; // Set local grade
		 if (moneyLeft == 7) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatLeft == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (invalidPlugSeat == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (plugSeatUnavailable == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (notExactFund == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (insufficientFund == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatUnavailable == 1) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (seatReady == 0) gradeLocal = gradeLocal + 1; else caseFailed = 1;
		 if (caseFailed) begin
			  $display("Failed Case 20");
			  gradeLocal = gradeLocal >> 2;
		 end
		 else $display("Passed Case 20");
		 grade = grade + gradeLocal;
		 
	end

endmodule