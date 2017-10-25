
// ************************************************************************************************
// Defines
// ************************************************************************************************
#define PFE_ALIGN_NONE   0
#define PFE_ALIGN_LEFT   1
#define PFE_ALIGN_CENTER 2
#define PFE_ALIGN_RIGHT  3
#define PFE_CCDIR_LEFT   6
#define PFE_CCDIR_RIGHT  7
#define PFE_STACK_MAX	10000
#define PFE_STACK_PUSH(Y, XL, XR, DY) \
				if (sp < stack + PFE_STACK_MAX && Y + (DY) >= 0 && Y + (DY) <= 320) \
				{sp->y = Y; sp->xl = XL; sp->xr = XR; sp->dy = DY; sp++;}
#define PFE_STACK_POP(Y, XL, XR, DY) \
				{sp--; Y = sp->y+(DY = sp->dy); XL = sp->xl; XR = sp->xr;}


// ************************************************************************************************
// Structures
// ************************************************************************************************
struct PFE_DRAWTEXTCOLORCYCLECOLORSARRAYVALS {
	int red;
	int green;
	int blue;
};
struct PFE_Point {
	int x;
	int y;
} ;
struct PFE_FFSeg {short y, xl, xr, dy;};
struct PFE_FFSeg stack[PFE_STACK_MAX + 2], *sp = stack;


// ************************************************************************************************
// Globals
// ************************************************************************************************
int					 PFE_LastDrawText_X						 = 0;		  // Stores the calculated X location of the last drawText call
int					 PFE_LastDrawText_Length			 = 0;		  // Stores the calculated length (in pixels) of the last drawText call
unsigned int PFE_FPStartX[322];											// Used in the filled polygon function
unsigned int PFE_FPEndX[322];												// Used in the filled polygon function


// ************************************************************************************************
// Functions
// ************************************************************************************************

// Draws 8x16 VGA font text in a single solid color
void PFE_drawText(DisplayDevice* display, unsigned char* pFont, TCHAR* pOutStr, int Alignment, int locX, int locY, int colR, int colG, int colB) {
	// Get the length of the string
	int strLen = wcslen(pOutStr);
	// Record the length of this string in case the caller needs it
	PFE_LastDrawText_Length = strLen * 9;
	// Pointer to our character set data
	unsigned char* pCharStart;
	// Index to the current chatacter in the string
	int currChar;
	// Used during plotting
	int yLoc;
	int	currRow;
	int	bitTest;
	// Calculate X location based on alignment
	switch (Alignment) {
		case PFE_ALIGN_LEFT: {
			locX = 0;
		break; }
		case PFE_ALIGN_CENTER: {
			locX = wcslen(pOutStr);
			locX = (240 - ((locX << 3) + locX - 1)) / 2;
		break; }
		case PFE_ALIGN_RIGHT: {
			locX = wcslen(pOutStr);
			locX = (240 - (locX << 3)) - (locX - 1);
		break; }
	}
	// Record the X location of this text in case the caller needs it
	PFE_LastDrawText_X = locX;
	Pixel myPixel = Color(colR, colG, colB);
	// Plot each character in the string
	for (int i = 0; i < strLen; i++) {
		// Get the next character code in the string and advance to the next one
		currChar = (unsigned char)(*pOutStr++);
		// Set our pointer to the start of THIS character
		pCharStart = pFont + (currChar << 4);
		// Loop through each row in the character
		for (int y = 0; y < 16; y++) {
			yLoc = locY + y;
			// Grab the byte representing our current row
			currRow = *(pCharStart + y);
			// Go through each bit in the current row and plot those that should be plotted
			bitTest = 0x01 << 7; if ((currRow & bitTest) != 0) { display->SetPixel(locX + 0, yLoc, myPixel); }
			bitTest = 0x01 << 6; if ((currRow & bitTest) != 0) { display->SetPixel(locX + 1, yLoc, myPixel); }
			bitTest = 0x01 << 5; if ((currRow & bitTest) != 0) { display->SetPixel(locX + 2, yLoc, myPixel); }
			bitTest = 0x01 << 4; if ((currRow & bitTest) != 0) { display->SetPixel(locX + 3, yLoc, myPixel); }
			bitTest = 0x01 << 3; if ((currRow & bitTest) != 0) { display->SetPixel(locX + 4, yLoc, myPixel); } 
			bitTest = 0x01 << 2; if ((currRow & bitTest) != 0) { display->SetPixel(locX + 5, yLoc, myPixel); }
			bitTest = 0x01 << 1; if ((currRow & bitTest) != 0) { display->SetPixel(locX + 6, yLoc, myPixel); }
			bitTest = 0x01 << 0; if ((currRow & bitTest) != 0) { display->SetPixel(locX + 7, yLoc, myPixel); }
		}
		// Increment X location to get ready for the next character
		locX = locX + 9;
	}
}


// Draws 8x16 VGA font text in a single solid color with a single solid color background
void PFE_drawText(DisplayDevice* display, unsigned char* pFont, TCHAR* pOutStr, int Alignment, int locX, int locY, int colR, int colG, int colB, int colBR, int colBG, int colBB) {
	// Get the length of the string
	int strLen = wcslen(pOutStr);
	// Record the length of this string in case the caller needs it
	PFE_LastDrawText_Length = strLen * 9;
	// Pointer to our character set data
	unsigned char* pCharStart;
	// Index to the current chatacter in the string
	int currChar;
	// Used during plotting
	int yLoc;
	int	currRow;
	int	bitTest;
	// Calculate X location based on alignment
	switch (Alignment) {
		case PFE_ALIGN_LEFT: {
			locX = 0;
		break; }
		case PFE_ALIGN_CENTER: {
			locX = wcslen(pOutStr);
			locX = (240 - ((locX << 3) + locX - 1)) / 2;
		break; }
		case PFE_ALIGN_RIGHT: {
			locX = wcslen(pOutStr);
			locX = (240 - (locX << 3)) - (locX - 1);
		break; }
	}
	// Record the X location of this text in case the caller needs it
	PFE_LastDrawText_X = locX;
	Pixel myPixel  = Color(colR, colG, colB);
	Pixel myBPixel = Color(colBR, colBG, colBB);
	// Plot each character in the string
	for (int i = 0; i < strLen; i++) {
		// Get the next character code in the string and advance to the next one
		currChar = (unsigned char)(*pOutStr++);
		// Set our pointer to the start of THIS character
		pCharStart = pFont + (currChar << 4);
		// Loop through each row in the character
		for (int y = 0; y < 16; y++) {
			yLoc = locY + y;
			// Grab the byte representing our current row
			currRow = *(pCharStart + y);
			// Go through each bit in the current row and plot those that should be plotted
			bitTest = 0x01 << 7; if ((currRow & bitTest) != 0) { display->SetPixel(locX + 0, yLoc, myPixel); } else { display->SetPixel(locX + 0, yLoc, myBPixel); }
			bitTest = 0x01 << 6; if ((currRow & bitTest) != 0) { display->SetPixel(locX + 1, yLoc, myPixel); } else { display->SetPixel(locX + 1, yLoc, myBPixel); }
			bitTest = 0x01 << 5; if ((currRow & bitTest) != 0) { display->SetPixel(locX + 2, yLoc, myPixel); } else { display->SetPixel(locX + 2, yLoc, myBPixel); }
			bitTest = 0x01 << 4; if ((currRow & bitTest) != 0) { display->SetPixel(locX + 3, yLoc, myPixel); } else { display->SetPixel(locX + 3, yLoc, myBPixel); }
			bitTest = 0x01 << 3; if ((currRow & bitTest) != 0) { display->SetPixel(locX + 4, yLoc, myPixel); } else { display->SetPixel(locX + 4, yLoc, myBPixel); } 
			bitTest = 0x01 << 2; if ((currRow & bitTest) != 0) { display->SetPixel(locX + 5, yLoc, myPixel); } else { display->SetPixel(locX + 5, yLoc, myBPixel); }
			bitTest = 0x01 << 1; if ((currRow & bitTest) != 0) { display->SetPixel(locX + 6, yLoc, myPixel); } else { display->SetPixel(locX + 6, yLoc, myBPixel); }
			bitTest = 0x01 << 0; if ((currRow & bitTest) != 0) { display->SetPixel(locX + 7, yLoc, myPixel); } else { display->SetPixel(locX + 7, yLoc, myBPixel); }
			display->SetPixel(locX + 8, yLoc, myBPixel);
		}
		// Increment X location to get ready for the next character
		locX = locX + 9;
	}
}


// Draws 8x16 VGA font text with a color gradient from top to bottom
void PFE_drawText(DisplayDevice* display, unsigned char* pFont, TCHAR* pOutStr, int Alignment, int locX, int locY, int colR, int colG, int colB, bool colorGradient) {
	// Save the colors as passed in
	int colRIn = colR;
	int colGIn = colG;
	int colBIn = colB;
	// Determine the proper increment value for each line in the gradient
	int RIncVal = (255 - colR) / 16;
	int GIncVal = (255 - colG) / 16;
	int BIncVal = (255 - colB) / 16;
	// Get the length of the string
	int strLen = wcslen(pOutStr);
	// Record the length of this string in case the caller needs it
	PFE_LastDrawText_Length = strLen * 9;
	// Pointer to our character set data
	unsigned char* pCharStart;
	// Index to the current chatacter in the string
	int currChar;
	// Used during plotting
	int yLoc;
	int	currRow;
	int	bitTest;
	// Calculate X location based on alignment
	switch (Alignment) {
		case PFE_ALIGN_LEFT: {
			locX = 0;
		break; }
		case PFE_ALIGN_CENTER: {
			locX = wcslen(pOutStr);
			locX = (240 - ((locX << 3) + locX - 1)) / 2;
		break; }
		case PFE_ALIGN_RIGHT: {
			locX = wcslen(pOutStr);
			locX = (240 - (locX << 3)) - (locX - 1);
		break; }
	}
	// Record the X location of this text in case the caller needs it
	PFE_LastDrawText_X = locX;
	Pixel myPixel;
	// Plot each character in the string
	for (int i = 0; i < strLen; i++) {
		// Get the next character code in the string and advance to the next one
		currChar = (unsigned char)(*pOutStr++);
		// Set our pointer to the start of THIS character
		pCharStart = pFont + (currChar << 4);
		// Reset the colors for this character to the starting colors
		colR = colRIn;
		colG = colGIn;
		colB = colBIn;
		// Loop through each row in the character
		for (int y = 0; y < 16; y++) {
			// Set the color for the row and increment the gradient colors
			myPixel = Color(colR, colG, colB);
			if (colorGradient) {
				colR = colR + RIncVal;
				colG = colG + GIncVal;
				colB = colB + BIncVal;
			}
			yLoc = locY + y;
			// Grab the byte representing our current row
			currRow = *(pCharStart + y);
			// Go through each bit in the current row and plot those that should be plotted
			bitTest = 0x01 << 7; if ((currRow & bitTest) != 0) { display->SetPixel(locX + 0, yLoc, myPixel); }
			bitTest = 0x01 << 6; if ((currRow & bitTest) != 0) { display->SetPixel(locX + 1, yLoc, myPixel); }
			bitTest = 0x01 << 5; if ((currRow & bitTest) != 0) { display->SetPixel(locX + 2, yLoc, myPixel); }
			bitTest = 0x01 << 4; if ((currRow & bitTest) != 0) { display->SetPixel(locX + 3, yLoc, myPixel); }
			bitTest = 0x01 << 3; if ((currRow & bitTest) != 0) { display->SetPixel(locX + 4, yLoc, myPixel); } 
			bitTest = 0x01 << 2; if ((currRow & bitTest) != 0) { display->SetPixel(locX + 5, yLoc, myPixel); }
			bitTest = 0x01 << 1; if ((currRow & bitTest) != 0) { display->SetPixel(locX + 6, yLoc, myPixel); }
			bitTest = 0x01 << 0; if ((currRow & bitTest) != 0) { display->SetPixel(locX + 7, yLoc, myPixel); }
		}
		// Increment X location to get ready for the next character
		locX = locX + 9;
	}
}


// Draws 8x16 VGA font text with each pixel a random color
void PFE_drawText(DisplayDevice* display, unsigned char* pFont, TCHAR* pOutStr, int Alignment, int locX, int locY) {
	// Get the length of the string
	int	strLen = wcslen(pOutStr);
	// Record the length of this string in case the caller needs it
	PFE_LastDrawText_Length = strLen * 9;
	// Pointer to our character set data
	unsigned char* pCharStart;
	// Index to the current chatacter in the string
	int	currChar;
	// Used during plotting
	int yLoc;
	int	currRow;
	int	bitTest;
	// Calculate X location based on alignment
	switch (Alignment) {
		case PFE_ALIGN_LEFT: {
			locX = 0;
		break; }
		case PFE_ALIGN_CENTER: {
			locX = wcslen(pOutStr);
			locX = (240 - ((locX << 3) + locX - 1)) / 2;
		break; }
		case PFE_ALIGN_RIGHT: {
			locX = wcslen(pOutStr);
			locX = (240 - (locX << 3)) - (locX - 1);
		break; }
	}
	// Record the X location of this text in case the caller needs it
	PFE_LastDrawText_X = locX;
	Pixel myPixel;
	// Plot each character in the string
	for (int i = 0; i < strLen; i++) {
		// Get the next character code in the string and advance to the next one
		currChar = (unsigned char)(*pOutStr++);
		// Set our pointer to the start of THIS character
		pCharStart = pFont + (currChar << 4);
		// Loop through each row in the character
		for (int y = 0; y < 16; y++) {
			yLoc = locY + y;
			// Grab the byte representing our current row
			currRow = *(pCharStart + y);
			// Go through each bit in the current row and plot those that should be plotted
			bitTest = 0x01 << 7; if ((currRow & bitTest) != 0) { 
				myPixel = Color((rand() * (255 + 1)) / (RAND_MAX + 1), (rand() * (255 + 1)) / (RAND_MAX + 1), (rand() * (255 + 1)) / (RAND_MAX + 1));
				display->SetPixel(locX + 0, yLoc, myPixel); 
			}
			bitTest = 0x01 << 6; if ((currRow & bitTest) != 0) { 
				myPixel = Color((rand() * (255 + 1)) / (RAND_MAX + 1), (rand() * (255 + 1)) / (RAND_MAX + 1), (rand() * (255 + 1)) / (RAND_MAX + 1));
				display->SetPixel(locX + 1, yLoc, myPixel); 
			}
			bitTest = 0x01 << 5; if ((currRow & bitTest) != 0) { 
				myPixel = Color((rand() * (255 + 1)) / (RAND_MAX + 1), (rand() * (255 + 1)) / (RAND_MAX + 1), (rand() * (255 + 1)) / (RAND_MAX + 1));
				display->SetPixel(locX + 2, yLoc, myPixel); 
			}
			bitTest = 0x01 << 4; if ((currRow & bitTest) != 0) { 
				myPixel = Color((rand() * (255 + 1)) / (RAND_MAX + 1), (rand() * (255 + 1)) / (RAND_MAX + 1), (rand() * (255 + 1)) / (RAND_MAX + 1));
				display->SetPixel(locX + 3, yLoc, myPixel); 
			}
			bitTest = 0x01 << 3; if ((currRow & bitTest) != 0) { 
				myPixel = Color((rand() * (255 + 1)) / (RAND_MAX + 1), (rand() * (255 + 1)) / (RAND_MAX + 1), (rand() * (255 + 1)) / (RAND_MAX + 1));
				display->SetPixel(locX + 4, yLoc, myPixel); 
			} 
			bitTest = 0x01 << 2; if ((currRow & bitTest) != 0) { 
				myPixel = Color((rand() * (255 + 1)) / (RAND_MAX + 1), (rand() * (255 + 1)) / (RAND_MAX + 1), (rand() * (255 + 1)) / (RAND_MAX + 1));
				display->SetPixel(locX + 5, yLoc, myPixel); 
			}
			bitTest = 0x01 << 1; if ((currRow & bitTest) != 0) { 
				myPixel = Color((rand() * (255 + 1)) / (RAND_MAX + 1), (rand() * (255 + 1)) / (RAND_MAX + 1), (rand() * (255 + 1)) / (RAND_MAX + 1));
				display->SetPixel(locX + 6, yLoc, myPixel); 
			}
			bitTest = 0x01 << 0; if ((currRow & bitTest) != 0) { 
				myPixel = Color((rand() * (255 + 1)) / (RAND_MAX + 1), (rand() * (255 + 1)) / (RAND_MAX + 1), (rand() * (255 + 1)) / (RAND_MAX + 1));
				display->SetPixel(locX + 7, yLoc, myPixel); 
			}
		}
		// Increment X location to get ready for the next character
		locX = locX + 9;
	}
}


// Draws 8x16 VGA font text with a C64 color cycle effect
void PFE_drawText(DisplayDevice* display, unsigned char* pFont, TCHAR* pOutStr, int Alignment, int locX, int locY, PFE_DRAWTEXTCOLORCYCLECOLORSARRAYVALS colorsArray[], int numElements, int cycleDirection) {
	// Get the length of the string
	int	strLen = wcslen(pOutStr);
	// Record the length of this string in case the caller needs it
	PFE_LastDrawText_Length = strLen * 9;
	// Pointer to our character set data
	unsigned char* pCharStart;
	// Index to the current chatacter in the string
	int	currChar;
	// Used during plotting
	int yLoc;
	int	currRow;
	int	bitTest;
	// Calculate X location based on alignment
	switch (Alignment) {
		case PFE_ALIGN_LEFT: {
			locX = 0;
		break; }
		case PFE_ALIGN_CENTER: {
			locX = wcslen(pOutStr);
			locX = (240 - ((locX << 3) + locX - 1)) / 2;
		break; }
		case PFE_ALIGN_RIGHT: {
			locX = wcslen(pOutStr);
			locX = (240 - (locX << 3)) - (locX - 1);
		break; }
	}
	PFE_LastDrawText_X = locX;
	// Record the X location of this text in case the caller needs it
	Pixel myPixel;
	// Plot each character in the string
	for (int i = 0; i < strLen; i++) {
		// Get the next character code in the string and advance to the next one
		myPixel = Color(colorsArray[i].red, colorsArray[i].green, colorsArray[i].blue);
		currChar = (unsigned char)(*pOutStr++);
		// Set our pointer to the start of THIS character
		pCharStart = pFont + (currChar << 4);
		// Loop through each row in the character
		for (int y = 0; y < 16; y++) {
			yLoc = locY + y;
			// Grab the byte representing our current row
			currRow = *(pCharStart + y);
			// Go through each bit in the current row and plot those that should be plotted
			bitTest = 0x01 << 7; if ((currRow & bitTest) != 0) { display->SetPixel(locX + 0, yLoc, myPixel); }
			bitTest = 0x01 << 6; if ((currRow & bitTest) != 0) { display->SetPixel(locX + 1, yLoc, myPixel); }
			bitTest = 0x01 << 5; if ((currRow & bitTest) != 0) { display->SetPixel(locX + 2, yLoc, myPixel); }
			bitTest = 0x01 << 4; if ((currRow & bitTest) != 0) { display->SetPixel(locX + 3, yLoc, myPixel); }
			bitTest = 0x01 << 3; if ((currRow & bitTest) != 0) { display->SetPixel(locX + 4, yLoc, myPixel); } 
			bitTest = 0x01 << 2; if ((currRow & bitTest) != 0) { display->SetPixel(locX + 5, yLoc, myPixel); }
			bitTest = 0x01 << 1; if ((currRow & bitTest) != 0) { display->SetPixel(locX + 6, yLoc, myPixel); }
			bitTest = 0x01 << 0; if ((currRow & bitTest) != 0) { display->SetPixel(locX + 7, yLoc, myPixel); }
		}
		// Increment X location to get ready for the next character
		locX = locX + 9;
	}
	// Cycle the colorsArray in the specified direction
	switch (cycleDirection) {
		case PFE_CCDIR_LEFT: { // Left
			int colRTemp = colorsArray[0].red;
			int colGTemp = colorsArray[0].green;
			int colBTemp = colorsArray[0].blue;
			for (i = 0; i < numElements - 1; i++) {
				colorsArray[i].red = colorsArray[i + 1].red;
				colorsArray[i].green = colorsArray[i + 1].green;
				colorsArray[i].blue = colorsArray[i + 1].blue;
			}
			colorsArray[numElements - 1].red = colRTemp;
			colorsArray[numElements - 1].green = colGTemp;
			colorsArray[numElements - 1].blue = colBTemp;
		break; }
		case PFE_CCDIR_RIGHT: { // Right
			int colRTemp = colorsArray[numElements - 1].red;
			int colGTemp = colorsArray[numElements - 1].green;
			int colBTemp = colorsArray[numElements - 1].blue;
			for (i = numElements - 1; i > 0; i--) {
				colorsArray[i].red = colorsArray[i - 1].red;
				colorsArray[i].green = colorsArray[i - 1].green;
				colorsArray[i].blue = colorsArray[i - 1].blue;
			}
			colorsArray[0].red = colRTemp;
			colorsArray[0].green = colGTemp;
			colorsArray[0].blue = colBTemp;
		break; }
	}
}



