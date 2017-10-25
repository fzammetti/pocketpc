
	typedef struct tagCHIPREFERENCE {
			TCHAR szPartNumber[6];
			TCHAR szDescription[128];
			TCHAR szDetails[512];
			TCHAR szPin1[6]; 
			TCHAR szPin2[6]; 
			TCHAR szPin3[6]; 
			TCHAR szPin4[6]; 
			TCHAR szPin5[6]; 
			TCHAR szPin6[6]; 
			TCHAR szPin7[6]; 
			TCHAR szPin8[6]; 
			TCHAR szPin9[6]; 
			TCHAR szPin10[6]; 
			TCHAR szPin11[6]; 
			TCHAR szPin12[6]; 
			TCHAR szPin13[6]; 
			TCHAR szPin14[6]; 
			TCHAR szFTCol1Head[4];
			TCHAR szFTCol2Head[4];
			TCHAR szFTCol3Head[4];
			TCHAR szFTCol4Head[4];
			TCHAR szFTCol5Head[4];
			TCHAR szFTCol6Head[4];
			TCHAR szFTCol7Head[4];
			TCHAR szFTRow1_1[6];
			TCHAR szFTRow1_2[6];
			TCHAR szFTRow1_3[6];
			TCHAR szFTRow1_4[6];
			TCHAR szFTRow1_5[6];
			TCHAR szFTRow1_6[6];
			TCHAR szFTRow1_7[6];
			TCHAR szFTRow2_1[6];
			TCHAR szFTRow2_2[6];
			TCHAR szFTRow2_3[6];
			TCHAR szFTRow2_4[6];
			TCHAR szFTRow2_5[6];
			TCHAR szFTRow2_6[6];
			TCHAR szFTRow2_7[6];
			TCHAR szFTRow3_1[6];
			TCHAR szFTRow3_2[6];
			TCHAR szFTRow3_3[6];
			TCHAR szFTRow3_4[6];
			TCHAR szFTRow3_5[6];
			TCHAR szFTRow3_6[6];
			TCHAR szFTRow3_7[6];
			TCHAR szFTRow4_1[6];
			TCHAR szFTRow4_2[6];
			TCHAR szFTRow4_3[6];
			TCHAR szFTRow4_4[6];
			TCHAR szFTRow4_5[6];
			TCHAR szFTRow4_6[6];
			TCHAR szFTRow4_7[6];
			TCHAR szFTRow5_1[6];
			TCHAR szFTRow5_2[6];
			TCHAR szFTRow5_3[6];
			TCHAR szFTRow5_4[6];
			TCHAR szFTRow5_5[6];
			TCHAR szFTRow5_6[6];
			TCHAR szFTRow5_7[6];
			TCHAR szFTRow6_1[6];
			TCHAR szFTRow6_2[6];
			TCHAR szFTRow6_3[6];
			TCHAR szFTRow6_4[6];
			TCHAR szFTRow6_5[6];
			TCHAR szFTRow6_6[6];
			TCHAR szFTRow6_7[6];
			TCHAR szFTRow7_1[6];
			TCHAR szFTRow7_2[6];
			TCHAR szFTRow7_3[6];
			TCHAR szFTRow7_4[6];
			TCHAR szFTRow7_5[6];
			TCHAR szFTRow7_6[6];
			TCHAR szFTRow7_7[6];
			TCHAR szFTRow8_1[6];
			TCHAR szFTRow8_2[6];
			TCHAR szFTRow8_3[6];
			TCHAR szFTRow8_4[6];
			TCHAR szFTRow8_5[6];
			TCHAR szFTRow8_6[6];
			TCHAR szFTRow8_7[6];
	} CHIPREFERENCE;

	int numItemsChipReference = 25;

// Part Number
// Short Description
// Detailed Description
// Pinout Data For Pins 1-7
// Pinout Data For Pins 8-14
// Function Table Columns 1-7 Headers (1-5 Are Inputs, 6 & 7 Are Outpus)
// Function Data Data For Row 1, Columns 1-7
// Function Data Data For Row 2, Columns 1-7
// Function Data Data For Row 3, Columns 1-7
// Function Data Data For Row 4, Columns 1-7
// Function Data Data For Row 5, Columns 1-7
// Function Data Data For Row 6, Columns 1-7
// Function Data Data For Row 7, Columns 1-7
// Function Data Data For Row 8, Columns 1-7

  CHIPREFERENCE ChipReferenceTable[] = {
    {TEXT("7400"), 
			TEXT("Quadruple 2-input positive-NAND gates"),															
			TEXT("These devices contain four independent 2-input NAND gates.  They perform the Boolean functions Y=!(A&&B) or Y=!A||!B in positive logic."), 
			TEXT("1A"), TEXT("1B"), TEXT("1Y"), TEXT("2A"), TEXT("2B"), TEXT("2Y"), TEXT("Gnd"), 
			TEXT("3Y"), TEXT("3A"), TEXT("3B"), TEXT("4Y"), TEXT("4A"), TEXT("4B"), TEXT("Vcc"), 
			TEXT("A"), TEXT("B"), TEXT(" "), TEXT(" "), TEXT(" "), TEXT("Y"), TEXT(" "), 
			TEXT("H"), TEXT("H"), TEXT(" "), TEXT(" "), TEXT(" "), TEXT("L"), TEXT(" "), 
			TEXT("L"), TEXT("X"), TEXT(" "), TEXT(" "), TEXT(" "), TEXT("H"), TEXT(" "), 
			TEXT("X"), TEXT("L"), TEXT(" "), TEXT(" "), TEXT(" "), TEXT("H"), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" ")},
    {TEXT("7401"), 
			TEXT("Quadruple 2-input positive-NAND gates with open-collector outputs"), 
			TEXT("These devices contain four independent 2-input NAND gates with open-collector outputs.    They perform the Boolean functions Y=!(A&&B) or Y=!A||!B in positive logic.  The open-collector outputs require pull-up resistors to perform correctly.  They may be connected to other open-collector outputs to implement active-low wired-OR or active-high wired-AND functions.  Open-collector devices are often used to generate higher Voh levels."), 
			TEXT("1Y"), TEXT("1A"), TEXT("1B"), TEXT("2Y"), TEXT("2A"), TEXT("2B"), TEXT("Gnd"), 
			TEXT("3A"), TEXT("3B"), TEXT("3Y"), TEXT("4A"), TEXT("4B"), TEXT("4Y"), TEXT("Vcc"), 
			TEXT("A"), TEXT("B"), TEXT(" "), TEXT(" "), TEXT(" "), TEXT("Y"), TEXT(" "), 
			TEXT("H"), TEXT("H"), TEXT(" "), TEXT(" "), TEXT(" "), TEXT("L"), TEXT(" "), 
			TEXT("L"), TEXT("X"), TEXT(" "), TEXT(" "), TEXT(" "), TEXT("H"), TEXT(" "), 
			TEXT("X"), TEXT("L"), TEXT(" "), TEXT(" "), TEXT(" "), TEXT("H"), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" ")},
    {TEXT("7402"), 
			TEXT("Quadruple 2-input positive-NOR gates"),
			TEXT("These devices contain four independent 2-input NOR gates.  They perform the Boolean functions Y=!(A||B) or Y=!A&&!B in positive logic."), 
			TEXT("1Y"), TEXT("1A"), TEXT("1B"), TEXT("2Y"), TEXT("2A"), TEXT("2B"), TEXT("Gnd"), 
			TEXT("3A"), TEXT("3B"), TEXT("3Y"), TEXT("4A"), TEXT("4B"), TEXT("4Y"), TEXT("Vcc,"),
			TEXT("A"), TEXT("B"), TEXT(" "), TEXT(" "), TEXT(" "), TEXT("Y"), TEXT(" "), 
			TEXT("H"), TEXT("X"), TEXT(" "), TEXT(" "), TEXT(" "), TEXT("L"), TEXT(" "), 
			TEXT("X"), TEXT("H"), TEXT(" "), TEXT(" "), TEXT(" "), TEXT("L"), TEXT(" "), 
			TEXT("L"), TEXT("L"), TEXT(" "), TEXT(" "), TEXT(" "), TEXT("H"), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" ")},			
    {TEXT("7403"), 
			TEXT("Quadruple 2-input positive-NOR gates with open-collector outputs"),  
			TEXT("These devices contain four independent 2-input NAND gates with open-collector outputs.  They perform the Boolean functions Y=!(A&&B) or Y=!A||!B in positive logic.  The open-collector outputs require pull-up resistors to perform correctly.  They may be connected to other open-collector outputs to implement active-low wired-OR or active-high wired-AND functions.  Open-collector devices are often used to generate higher Voh levels."), 
			TEXT("1A"), TEXT("1B"), TEXT("1Y"), TEXT("2A"), TEXT("2B"), TEXT("2Y"), TEXT("Gnd"), 
			TEXT("3Y"), TEXT("3A"), TEXT("3B"), TEXT("4Y"), TEXT("4A"), TEXT("4B"), TEXT("Vcc"),
			TEXT("A"), TEXT("B"), TEXT(" "), TEXT(" "), TEXT(" "), TEXT("Y"), TEXT(" "), 
			TEXT("H"), TEXT("H"), TEXT(" "), TEXT(" "), TEXT(" "), TEXT("L"), TEXT(" "), 
			TEXT("L"), TEXT("X"), TEXT(" "), TEXT(" "), TEXT(" "), TEXT("H"), TEXT(" "), 
			TEXT("X"), TEXT("L"), TEXT(" "), TEXT(" "), TEXT(" "), TEXT("H"), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" ")},
    {TEXT("7404"), 
			TEXT("Hex inverters"),
			TEXT("These devices contain six independent inverters.  They perform the Boolean function Y=!A."), 
			TEXT("1A"), TEXT("1Y"), TEXT("2A"), TEXT("2Y"), TEXT("3A"), TEXT("3Y"), TEXT("Gnd"), 
			TEXT("4Y"), TEXT("4A"), TEXT("5Y"), TEXT("5A"), TEXT("6Y"), TEXT("6A"), TEXT("Vcc"),
			TEXT("A"), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT("Y"), TEXT(" "), 
			TEXT("H"), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT("L"), TEXT(" "), 
			TEXT("L"), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT("H"), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" ")},
    {TEXT("7405"), 
			TEXT("Hex inverters with open-collector outputs"),
			TEXT("These devices contain six independent inverters with open-collector outputs.  They perform the Boolean function Y=!A.  The open-collector outputs require pull-up resistors to perform correctly.  They may be connected to other open-collector outputs to implement active-low wired-OR or active-high wired-AND functions.  Open-collector devices are often used to generate higher Voh levels."), 
			TEXT("1A"), TEXT("1Y"), TEXT("2A"), TEXT("2Y"), TEXT("3A"), TEXT("3Y"), TEXT("Gnd"), 
			TEXT("4Y"), TEXT("4A"), TEXT("5Y"), TEXT("5A"), TEXT("6Y"), TEXT("6A"), TEXT("Vcc"),
			TEXT("A"), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT("Y"), TEXT(" "), 
			TEXT("H"), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT("L"), TEXT(" "), 
			TEXT("L"), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT("H"), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" ")},
    {TEXT("7408"), 
			TEXT("Quadruple 2-input positive-AND gates"),
			TEXT("These devices contain four independent 2-input AND gates.  They perform the Boolean functions Y=A&&B or Y=!(!A||!B) in positive logic."), 
			TEXT("1A"), TEXT("1B"), TEXT("1Y"), TEXT("2A"), TEXT("2B"), TEXT("2Y"), TEXT("Gnd"), 
			TEXT("3Y"), TEXT("3A"), TEXT("3B"), TEXT("4Y"), TEXT("4A"), TEXT("4B"), TEXT("Vcc"),
			TEXT("A"), TEXT("B"), TEXT(" "), TEXT(" "), TEXT(" "), TEXT("Y"), TEXT(" "), 
			TEXT("H"), TEXT("H"), TEXT(" "), TEXT(" "), TEXT(" "), TEXT("H"), TEXT(" "), 
			TEXT("L"), TEXT("X"), TEXT(" "), TEXT(" "), TEXT(" "), TEXT("L"), TEXT(" "), 
			TEXT("X"), TEXT("L"), TEXT(" "), TEXT(" "), TEXT(" "), TEXT("L"), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" ")},
    {TEXT("7409"), 
			TEXT("Quadruple 2-input positive-AND gates with open-collector outputs"),
			TEXT("These devices contain four independent 2-input AND gates with open-collector outputs.  They perform the Boolean functions Y=A&&B or Y=!(!A||!B) in positive logic.  The open-collector outputs require pull-up resistors to perform correctly.  They may be connected to other open-collector outputs to implement active-low wired-OR or active-high wired-AND functions.  Open-collector devices are often used to generate higher Voh levels."), 
			TEXT("1A"), TEXT("1B"), TEXT("1Y"), TEXT("2A"), TEXT("2B"), TEXT("2Y"), TEXT("Gnd"), 
			TEXT("3Y"), TEXT("3A"), TEXT("3B"), TEXT("4Y"), TEXT("4A"), TEXT("4B"), TEXT("Vcc"),
			TEXT("A"), TEXT("B"), TEXT(" "), TEXT(" "), TEXT(" "), TEXT("Y"), TEXT(" "), 
			TEXT("H"), TEXT("H"), TEXT(" "), TEXT(" "), TEXT(" "), TEXT("H"), TEXT(" "), 
			TEXT("L"), TEXT("X"), TEXT(" "), TEXT(" "), TEXT(" "), TEXT("L"), TEXT(" "), 
			TEXT("X"), TEXT("L"), TEXT(" "), TEXT(" "), TEXT(" "), TEXT("L"), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" ")},
    {TEXT("7410"), 
			TEXT("Triple 3-input positive-NAND gates"),
			TEXT("These devices contain three independent 3-input NAND gates.  They perform the Boolean functions Y=!(A&&B&&C) or Y=!A||!B||!C in positive logic."), 
			TEXT("1A"), TEXT("1B"), TEXT("2A"), TEXT("2B"), TEXT("2C"), TEXT("2Y"), TEXT("Gnd"), 
			TEXT("3Y"), TEXT("3A"), TEXT("3B"), TEXT("3C"), TEXT("1Y"), TEXT("1C"), TEXT("Vcc"),
			TEXT("A"), TEXT("B"), TEXT("C"), TEXT(" "), TEXT(" "), TEXT("Y"), TEXT(" "), 
			TEXT("H"), TEXT("H"), TEXT("H"), TEXT(" "), TEXT(" "), TEXT("L"), TEXT(" "), 
			TEXT("L"), TEXT("X"), TEXT("X"), TEXT(" "), TEXT(" "), TEXT("H"), TEXT(" "), 
			TEXT("X"), TEXT("L"), TEXT("X"), TEXT(" "), TEXT(" "), TEXT("H"), TEXT(" "), 
			TEXT("X"), TEXT("X"), TEXT("L"), TEXT(" "), TEXT(" "), TEXT("H"), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" ")},
    {TEXT("7411"), 
			TEXT("Triple 3-input positive-AND gates"),
			TEXT("These devices contain three independent 3-input AND gates.  They perform the Boolean functions Y=A&&B&&C or Y=!(!A||!B||!C) in positive logic."), 
			TEXT("1A"), TEXT("1B"), TEXT("2A"), TEXT("2B"), TEXT("2C"), TEXT("2Y"), TEXT("Gnd"), 
			TEXT("3Y"), TEXT("3A"), TEXT("3B"), TEXT("3C"), TEXT("1Y"), TEXT("1C"), TEXT("Vcc"),
			TEXT("A"), TEXT("B"), TEXT("C"), TEXT(" "), TEXT(" "), TEXT("Y"), TEXT(" "), 
			TEXT("H"), TEXT("H"), TEXT("H"), TEXT(" "), TEXT(" "), TEXT("H"), TEXT(" "), 
			TEXT("L"), TEXT("X"), TEXT("X"), TEXT(" "), TEXT(" "), TEXT("L"), TEXT(" "), 
			TEXT("X"), TEXT("L"), TEXT("X"), TEXT(" "), TEXT(" "), TEXT("L"), TEXT(" "), 
			TEXT("X"), TEXT("X"), TEXT("L"), TEXT(" "), TEXT(" "), TEXT("L"), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" ")},
    {TEXT("7412"), 
			TEXT("Triple 3-input positive-NAND gates with open-collector outputs"),
			TEXT("These devices contain three independent 3-input NAND gates with open-collector outputs.  They perform the Boolean functions Y=!(A&&B&&C) or Y=!A||!B||!C in positive logic.  The open-collector outputs require pull-up resistors to perform correctly.  They may be connected to other open-collector outputs to implement active-low wired-OR or active-high wired-AND functions.  Open-collector devices are often used to generate higher Voh levels."), 
			TEXT("1A"), TEXT("1B"), TEXT("2A"), TEXT("2B"), TEXT("2C"), TEXT("2Y"), TEXT("Gnd"), 
			TEXT("3Y"), TEXT("3A"), TEXT("3B"), TEXT("3C"), TEXT("1Y"), TEXT("1C"), TEXT("Vcc"),
			TEXT("A"), TEXT("B"), TEXT("C"), TEXT(" "), TEXT(" "), TEXT("Y"), TEXT(" "), 
			TEXT("H"), TEXT("H"), TEXT("H"), TEXT(" "), TEXT(" "), TEXT("L"), TEXT(" "), 
			TEXT("L"), TEXT("X"), TEXT("X"), TEXT(" "), TEXT(" "), TEXT("H"), TEXT(" "), 
			TEXT("X"), TEXT("L"), TEXT("X"), TEXT(" "), TEXT(" "), TEXT("H"), TEXT(" "), 
			TEXT("X"), TEXT("X"), TEXT("L"), TEXT(" "), TEXT(" "), TEXT("H"), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" ")},
    {TEXT("7415"), 
			TEXT("Triple 3-input positive-AND gates with open-collector outputs"),
			TEXT("These devices contain three independent 3-input AND gates with open-collector outputs.  They perform the Boolean functions Y=A&&B&&C or Y=!(!A||!B||!C) in positive logic.  The open-collector outputs require pull-up resistors to perform correctly.  They may be connected to other open-collector outputs to implement active-low wired-OR or active-high wired-AND functions.  Open-collector devices are often used to generate higher Voh levels."), 
			TEXT("1A"), TEXT("1B"), TEXT("2A"), TEXT("2B"), TEXT("2C"), TEXT("2Y"), TEXT("Gnd"), 
			TEXT("3Y"), TEXT("3A"), TEXT("3B"), TEXT("3C"), TEXT("1Y"), TEXT("1C"), TEXT("Vcc"),
			TEXT("A"), TEXT("B"), TEXT("C"), TEXT(" "), TEXT(" "), TEXT("Y"), TEXT(" "), 
			TEXT("H"), TEXT("H"), TEXT("H"), TEXT(" "), TEXT(" "), TEXT("H"), TEXT(" "), 
			TEXT("L"), TEXT("X"), TEXT("X"), TEXT(" "), TEXT(" "), TEXT("L"), TEXT(" "), 
			TEXT("X"), TEXT("L"), TEXT("X"), TEXT(" "), TEXT(" "), TEXT("L"), TEXT(" "), 
			TEXT("X"), TEXT("X"), TEXT("L"), TEXT(" "), TEXT(" "), TEXT("L"), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" ")},
    {TEXT("7420"), 
			TEXT("Dual 4-input positive-NAND gates"),
			TEXT("These devices contain two independent 4-input NAND gates.  They perform the Boolean functions Y=!(A&&B&&C&&D) or Y=!A||!B||!C||!D in positive logic."), 
			TEXT("1A"), TEXT("1B"), TEXT("NC"), TEXT("1C"), TEXT("1D"), TEXT("1Y"), TEXT("Gnd"), 
			TEXT("2Y"), TEXT("2A"), TEXT("2B"), TEXT("NC"), TEXT("2C"), TEXT("2D"), TEXT("Vcc"),
			TEXT("A"), TEXT("B"), TEXT("C"), TEXT("D"), TEXT(" "), TEXT("Y"), TEXT(" "), 
			TEXT("H"), TEXT("H"), TEXT("H"), TEXT("H"), TEXT(" "), TEXT("L"), TEXT(" "), 
			TEXT("L"), TEXT("X"), TEXT("X"), TEXT("X"), TEXT(" "), TEXT("H"), TEXT(" "), 
			TEXT("X"), TEXT("L"), TEXT("X"), TEXT("X"), TEXT(" "), TEXT("H"), TEXT(" "), 
			TEXT("X"), TEXT("X"), TEXT("L"), TEXT("X"), TEXT(" "), TEXT("H"), TEXT(" "), 
			TEXT("X"), TEXT("X"), TEXT("X"), TEXT("L"), TEXT(" "), TEXT("H"), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" ")},
    {TEXT("7421"), 
			TEXT("Dual 4-input positive-AND gates"),
			TEXT("These devices contain two independent 4-input AND gates.  They perform the Boolean functions Y=A&&B&&C&&D or Y=!(!A||!B||!C||!D) in positive logic."), 
			TEXT("1A"), TEXT("1B"), TEXT("NC"), TEXT("1C"), TEXT("1D"), TEXT("1Y"), TEXT("Gnd"), 
			TEXT("2Y"), TEXT("2A"), TEXT("2B"), TEXT("NC"), TEXT("2C"), TEXT("2D"), TEXT("Vcc"),
			TEXT("A"), TEXT("B"), TEXT("C"), TEXT("D"), TEXT(" "), TEXT("Y"), TEXT(" "), 
			TEXT("H"), TEXT("H"), TEXT("H"), TEXT("H"), TEXT(" "), TEXT("H"), TEXT(" "), 
			TEXT("L"), TEXT("X"), TEXT("X"), TEXT("X"), TEXT(" "), TEXT("L"), TEXT(" "), 
			TEXT("X"), TEXT("L"), TEXT("X"), TEXT("X"), TEXT(" "), TEXT("L"), TEXT(" "), 
			TEXT("X"), TEXT("X"), TEXT("L"), TEXT("X"), TEXT(" "), TEXT("L"), TEXT(" "), 
			TEXT("X"), TEXT("X"), TEXT("X"), TEXT("L"), TEXT(" "), TEXT("L"), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" ")},
    {TEXT("7422"), 
			TEXT("Dual 4-input positive-NAND gates with open-collector outputs"),
			TEXT("These devices contain two independent 4-input NAND gates.  They perform the Boolean functions Y=!(A&&B&&C&&D) or Y=!A||!B||!C||!D in positive logic.  The open-collector outputs require pull-up resistors to perform correctly.  They may be connected to other open-collector outputs to implement active-low wired-OR or active-high wired-AND functions.  Open-collector devices are often used to generate higher Voh levels."), 
			TEXT("1A"), TEXT("1B"), TEXT("NC"), TEXT("1C"), TEXT("1D"), TEXT("1Y"), TEXT("Gnd"), 
			TEXT("2Y"), TEXT("2A"), TEXT("2B"), TEXT("NC"), TEXT("2C"), TEXT("2D"), TEXT("Vcc"),
			TEXT("A"), TEXT("B"), TEXT("C"), TEXT("D"), TEXT(" "), TEXT("Y"), TEXT(" "), 
			TEXT("H"), TEXT("H"), TEXT("H"), TEXT("H"), TEXT(" "), TEXT("L"), TEXT(" "), 
			TEXT("L"), TEXT("X"), TEXT("X"), TEXT("X"), TEXT(" "), TEXT("H"), TEXT(" "), 
			TEXT("X"), TEXT("L"), TEXT("X"), TEXT("X"), TEXT(" "), TEXT("H"), TEXT(" "), 
			TEXT("X"), TEXT("X"), TEXT("L"), TEXT("X"), TEXT(" "), TEXT("H"), TEXT(" "), 
			TEXT("X"), TEXT("X"), TEXT("X"), TEXT("L"), TEXT(" "), TEXT("H"), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" ")},
    {TEXT("7427"), 
			TEXT("Triple 3-input positive-NOR gates"),
			TEXT("These devices contain three independent 3-input NOR gates.  They perform the Boolean functions Y=!(A||B||C) or Y=!A&&!B&&!C in positive logic."), 
			TEXT("1A"), TEXT("1B"), TEXT("2A"), TEXT("2B"), TEXT("2C"), TEXT("2Y"), TEXT("Gnd"), 
			TEXT("3Y"), TEXT("3A"), TEXT("3B"), TEXT("3C"), TEXT("1Y"), TEXT("1C"), TEXT("Vcc"),
			TEXT("A"), TEXT("B"), TEXT("C"), TEXT(" "), TEXT(" "), TEXT("Y"), TEXT(" "), 
			TEXT("H"), TEXT("X"), TEXT("X"), TEXT(" "), TEXT(" "), TEXT("L"), TEXT(" "), 
			TEXT("X"), TEXT("H"), TEXT("X"), TEXT(" "), TEXT(" "), TEXT("L"), TEXT(" "), 
			TEXT("X"), TEXT("X"), TEXT("H"), TEXT(" "), TEXT(" "), TEXT("L"), TEXT(" "), 
			TEXT("L"), TEXT("L"), TEXT("L"), TEXT(" "), TEXT(" "), TEXT("H"), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" ")},
    {TEXT("7428"), 
			TEXT("Quadruple 2-input positive-NOR buffers"),
			TEXT("These devices contain four independent 2-input NOR buffer gates.  They perform the Boolean functions Y=!(A||B) or Y=!A&&!B in positive logic."), 
			TEXT("1Y"), TEXT("1A"), TEXT("1B"), TEXT("2Y"), TEXT("2A"), TEXT("2B"), TEXT("Gnd"), 
			TEXT("3A"), TEXT("3B"), TEXT("3Y"), TEXT("4A"), TEXT("4B"), TEXT("4Y"), TEXT("Vcc"),
			TEXT("A"), TEXT("B"), TEXT(" "), TEXT(" "), TEXT(" "), TEXT("Y"), TEXT(" "), 
			TEXT("H"), TEXT("X"), TEXT(" "), TEXT(" "), TEXT(" "), TEXT("L"), TEXT(" "), 
			TEXT("X"), TEXT("H"), TEXT(" "), TEXT(" "), TEXT(" "), TEXT("L"), TEXT(" "), 
			TEXT("L"), TEXT("L"), TEXT(" "), TEXT(" "), TEXT(" "), TEXT("H"), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" ")},
    {TEXT("7432"), 
			TEXT("Quadruple 2-input positive-OR gates"),
			TEXT("These devices contain four independent 2-input OR gates.  They perform the Boolean functions Y=A||B or Y=!(!A&&!B) in positive logic."), 
			TEXT("1A"), TEXT("1B"), TEXT("1Y"), TEXT("2A"), TEXT("2B"), TEXT("2Y"), TEXT("Gnd"), 
			TEXT("3Y"), TEXT("3A"), TEXT("3B"), TEXT("4Y"), TEXT("4A"), TEXT("4B"), TEXT("Vcc"),
			TEXT("A"), TEXT("B"), TEXT(" "), TEXT(" "), TEXT(" "), TEXT("Y"), TEXT(" "), 
			TEXT("H"), TEXT("X"), TEXT(" "), TEXT(" "), TEXT(" "), TEXT("H"), TEXT(" "), 
			TEXT("X"), TEXT("H"), TEXT(" "), TEXT(" "), TEXT(" "), TEXT("H"), TEXT(" "), 
			TEXT("L"), TEXT("L"), TEXT(" "), TEXT(" "), TEXT(" "), TEXT("L"), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" ")},
    {TEXT("7433"), 
			TEXT("Quadruple 2-input positive-NOR buffers with open-collector outputs"),
			TEXT("These devices contain four independent 2-input NOR buffer gates.  They perform the Boolean functions Y=!(A||B) or Y=!A&&!B in positive logic.  The open-collector outputs require pull-up resistors to perform correctly.  They may be connected to other open-collector outputs to implement active-low wired-OR or active-high wired-AND functions.  Open-collector devices are often used to generate higher Voh levels."), 
			TEXT("1Y"), TEXT("1A"), TEXT("1B"), TEXT("2Y"), TEXT("2A"), TEXT("2B"), TEXT("Gnd"), 
			TEXT("3A"), TEXT("3B"), TEXT("3Y"), TEXT("4A"), TEXT("4B"), TEXT("4Y"), TEXT("Vcc"),
			TEXT("A"), TEXT("B"), TEXT(" "), TEXT(" "), TEXT(" "), TEXT("Y"), TEXT(" "), 
			TEXT("H"), TEXT("X"), TEXT(" "), TEXT(" "), TEXT(" "), TEXT("L"), TEXT(" "), 
			TEXT("X"), TEXT("H"), TEXT(" "), TEXT(" "), TEXT(" "), TEXT("L"), TEXT(" "), 
			TEXT("L"), TEXT("L"), TEXT(" "), TEXT(" "), TEXT(" "), TEXT("H"), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" ")},
    {TEXT("7434"), 
			TEXT("Hex noninverters"),
			TEXT("These devices contain six independent noninverters.  They perform the Boolean function Y=A."), 
			TEXT("1A"), TEXT("1Y"), TEXT("2A"), TEXT("2Y"), TEXT("3A"), TEXT("3Y"), TEXT("Gnd"), 
			TEXT("4Y"), TEXT("4A"), TEXT("5Y"), TEXT("5A"), TEXT("6Y"), TEXT("6A"), TEXT("Vcc"),
			TEXT("A"), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT("Y"), TEXT(" "), 
			TEXT("H"), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT("H"), TEXT(" "), 
			TEXT("L"), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT("L"), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" ")},
    {TEXT("7435"), 
			TEXT("Hex noninverters with open-collector outputs"),
			TEXT("These devices contain six independent noninverters.  They perform the Boolean function Y=A.  The open-collector outputs require pull-up resistors to perform correctly.  They may be connected to other open-collector outputs to implement active-low wired-OR or active-high wired-AND functions.  Open-collector devices are often used to generate higher Voh levels."), 
			TEXT("1A"), TEXT("1Y"), TEXT("2A"), TEXT("2Y"), TEXT("3A"), TEXT("3Y"), TEXT("Gnd"), 
			TEXT("4Y"), TEXT("4A"), TEXT("5Y"), TEXT("5A"), TEXT("6Y"), TEXT("6A"), TEXT("Vcc"),
			TEXT("A"), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT("Y"), TEXT(" "), 
			TEXT("H"), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT("H"), TEXT(" "), 
			TEXT("L"), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT("L"), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" ")},
    {TEXT("7437"), 
			TEXT("Quadruple 2-input positive-NAND buffers"),
			TEXT("These devices contain four independent 2-input NAND buffer gates.  They perform the Boolean functions Y=!(A&&B) or Y=!A||!B."), 
			TEXT("1A"), TEXT("1B"), TEXT("1Y"), TEXT("2A"), TEXT("2B"), TEXT("2Y"), TEXT("Gnd"), 
			TEXT("3Y"), TEXT("3A"), TEXT("3B"), TEXT("4Y"), TEXT("4A"), TEXT("4B"), TEXT("Vcc"),
			TEXT("A"), TEXT("B"), TEXT(" "), TEXT(" "), TEXT(" "), TEXT("Y"), TEXT(" "), 
			TEXT("H"), TEXT("H"), TEXT(" "), TEXT(" "), TEXT(" "), TEXT("L"), TEXT(" "), 
			TEXT("L"), TEXT("X"), TEXT(" "), TEXT(" "), TEXT(" "), TEXT("H"), TEXT(" "), 
			TEXT("X"), TEXT("L"), TEXT(" "), TEXT(" "), TEXT(" "), TEXT("H"), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" ")},
    {TEXT("7438"), 
			TEXT("Quadruple 2-input positive-NAND buffers with open-collector outputs"),
			TEXT("These devices contain four independent 2-input NAND buffer gates.  They perform the Boolean functions Y=!(A&&B) or Y=!A||!B.  The open-collector outputs require pull-up resistors to perform correctly.  They may be connected to other open-collector outputs to implement active-low wired-OR or active-high wired-AND functions.  Open-collector devices are often used to generate higher Voh levels."), 
			TEXT("1A"), TEXT("1B"), TEXT("1Y"), TEXT("2A"), TEXT("2B"), TEXT("2Y"), TEXT("Gnd"), 
			TEXT("3Y"), TEXT("3A"), TEXT("3B"), TEXT("4Y"), TEXT("4A"), TEXT("4B"), TEXT("Vcc"),
			TEXT("A"), TEXT("B"), TEXT(" "), TEXT(" "), TEXT(" "), TEXT("Y"), TEXT(" "), 
			TEXT("H"), TEXT("H"), TEXT(" "), TEXT(" "), TEXT(" "), TEXT("L"), TEXT(" "), 
			TEXT("L"), TEXT("X"), TEXT(" "), TEXT(" "), TEXT(" "), TEXT("H"), TEXT(" "), 
			TEXT("X"), TEXT("L"), TEXT(" "), TEXT(" "), TEXT(" "), TEXT("H"), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" ")},
    {TEXT("7440"), 
			TEXT("Dual 4-input positive-NAND buffers"),
			TEXT("These devices contain two independent 4-input NAND buffer gates.  They perform the Boolean functions Y=!(A&&B&&C&&D) or Y=!A||!B||!C||!D."), 
			TEXT("1A"), TEXT("1B"), TEXT("NC"), TEXT("1C"), TEXT("1D"), TEXT("1Y"), TEXT("Gnd"), 
			TEXT("2Y"), TEXT("2A"), TEXT("2B"), TEXT("NC"), TEXT("2C"), TEXT("2D"), TEXT("Vcc"),
			TEXT("A"), TEXT("B"), TEXT("C"), TEXT("D"), TEXT(" "), TEXT("Y"), TEXT(" "), 
			TEXT("H"), TEXT("H"), TEXT("H"), TEXT("H"), TEXT(" "), TEXT("L"), TEXT(" "), 
			TEXT("L"), TEXT("X"), TEXT("X"), TEXT("X"), TEXT(" "), TEXT("H"), TEXT(" "), 
			TEXT("X"), TEXT("L"), TEXT("X"), TEXT("X"), TEXT(" "), TEXT("H"), TEXT(" "), 
			TEXT("X"), TEXT("X"), TEXT("L"), TEXT("X"), TEXT(" "), TEXT("H"), TEXT(" "), 
			TEXT("X"), TEXT("X"), TEXT("X"), TEXT("L"), TEXT(" "), TEXT("H"), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" ")},
    {TEXT("7486"), 
			TEXT("Quadruple 2-input exclusive-OR gates"),
			TEXT("These devices contain four independent 2-input exclusive-OR gates.  They perform the Boolean functions Y=A^B or Y=!A&&B||A&&!B."), 
			TEXT("1A"), TEXT("1B"), TEXT("1Y"), TEXT("2A"), TEXT("2B"), TEXT("2Y"), TEXT("Gnd"), 
			TEXT("3Y"), TEXT("3A"), TEXT("3B"), TEXT("4Y"), TEXT("4A"), TEXT("4B"), TEXT("Vcc"),
			TEXT("A"), TEXT("B"), TEXT(" "), TEXT(" "), TEXT(" "), TEXT("Y"), TEXT(" "), 
			TEXT("L"), TEXT("L"), TEXT(" "), TEXT(" "), TEXT(" "), TEXT("L"), TEXT(" "), 
			TEXT("L"), TEXT("H"), TEXT(" "), TEXT(" "), TEXT(" "), TEXT("H"), TEXT(" "), 
			TEXT("H"), TEXT("L"), TEXT(" "), TEXT(" "), TEXT(" "), TEXT("H"), TEXT(" "), 
			TEXT("H"), TEXT("H"), TEXT(" "), TEXT(" "), TEXT(" "), TEXT("L"), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), 
			TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" "), TEXT(" ")}
  };
