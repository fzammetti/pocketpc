
// ================================================================================================
// Globals
// ================================================================================================
bool isLoadingDone		= false; // Flag to tell us if the loading thread is done
bool firstTimeThrough	= false; // Flag to tell us if we're doing the first frame
int	 loadingBarAmount = 0;     // Number of boxes on screen, 0-15
int	 myColor          = 255;   // What high color values start out as, this will be reduced to 0 to do the final fade-out
int	 blockFadeVal     = 0;
int	 blockFadeDir			= 1;
/*
  16 boxes, 10x10 each, 2 pixels between, 4 between first and last and surrounding box, 4 top and bottom
	21, 0
	      =---------------------------------=
				|               4                 |
				|4#2#2#2#2#2#2#2#2#2#2#2#2#2#2#2#4|    # = 10x10
				|               4                 |
				=---------------------------------=
				                                   219, 18

*/


// ================================================================================================
// Loader
// ================================================================================================
void loaderLoadingScreen(DisplayDevice* display) {
}


// ================================================================================================
// Releaser
// ================================================================================================
void releaserLoadingScreen() {
}


// Called to display the text and draw the blue box during the first frame and fade-out
void doFirstFrame(DisplayDevice* display) {
	display->Clear(Color(0, 0, 0));
	// Just do the text stuff once
	firstTimeThrough = true;
	// Display text
	HDC hDC = display->GetBackBuffer()->GetDC(false);
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));
	lf.lfHeight = 32;
	lstrcpy(lf.lfFaceName, _T("Tahoma"));
	HFONT hfont;
	hfont = CreateFontIndirect(&lf);
	SelectObject(hDC,hfont);
	RECT rcString;
	rcString.top		= 10;
	rcString.left		= 0;
	rcString.right	= 240;
	rcString.bottom = 320;
	SetTextColor(hDC, RGB(myColor, myColor, myColor));
	SetBkMode(hDC, TRANSPARENT);
	DrawText(hDC, TEXT("Please Wait"), -1, &rcString, DT_CENTER | DT_WORDBREAK);
	rcString.top		= 270;
	DrawText(hDC, TEXT("While Loading"), -1, &rcString, DT_CENTER | DT_WORDBREAK);
	display->GetBackBuffer()->ReleaseDC(hDC);
	display->DrawRect(21,  142, 219, 159, Color(0, 0, myColor));
	display->SetPixel(219, 159, Color(0, 0, myColor));
}


// Called to draw the progress bar boxes during subsequent frames and the fade-out
void doSubsequentFrames(DisplayDevice* display, bool currentBar) {
	// Update progress bar, add a new box
	RECT barRect;
	barRect.left	 = 25 + (12 * loadingBarAmount); // 25 = box start X (21) + 4 pixel buffer. 12 = box width (10) + 2 pixel buffer
	barRect.top		 = 146;
	barRect.right	 = barRect.left  + 10; // 10 = box width
	barRect.bottom = barRect.top   + 10; // 10 = box height
	int colR = 0;
	int colG = myColor;
	int colB = 0;
	if (!isLoadingDone && currentBar == true) {
		colR = blockFadeVal;
		colG = 0;
		if (blockFadeDir == 1) {
			blockFadeVal = blockFadeVal + 25;
		} else {
			blockFadeVal = blockFadeVal - 25;
		}
		if (blockFadeVal > 255) {
			blockFadeVal = 255;
			blockFadeDir = 0;
		}
		if (blockFadeVal < 0) {
			blockFadeVal = 0;
			blockFadeDir = 1;
		}
	}
	display->FillRect(barRect, Color(colR, colG, colB));
}


// ================================================================================================
// Handler
// ================================================================================================
void handlerLoadingScreen(DisplayDevice* display) {
	if (!isLoadingDone) { // We want to do the loading screen until the loading thread is done and sets isLoadingDone to false
		if (!firstTimeThrough) { // We just want to do this the first frame, not every time
			doFirstFrame(display);
		} else { // We do this every frame, except the first, which is done above
			if (loadingBarAmount > 0) {
				loadingBarAmount--;
				doSubsequentFrames(display, false);
				loadingBarAmount++;
			}
			doSubsequentFrames(display, true);
		}
	} else { // Loading thread is done
		// Do the final fade-out
		myColor = myColor - 15;
		if (myColor > 0) { // If we haven't hit or gone below 0 yet
			// Redraw the text and blue box with the decreased color value
			doFirstFrame(display);
			// Then draw all 16 boxes, also with the decreased color value
			for (int i = 0; i < 16; i++) {
				loadingBarAmount = i;
				doSubsequentFrames(display, true);
			}
		} else { // We've finished the fade-out, let's move on
			display->Clear(Color(0, 0, 0));
			game.currentScreen = csIntroScreen;
		}
	}
}


// Called from the loading thread to update the progress bar.  We increment the number of blocks,
// set the update flag to true and loop until the update flag is again false.  This is accomplished
// in the above handler... If it's not the first time through, we check this flag every frame.  When
// it's true, we draw a new box corresponding to loadingBarAmount and reset the flag to false.  This
// gets us out of the infinite loop below and back into the loading thread.
void updateProgressBar(DisplayDevice* display) {
	loadingBarAmount++;
	handlerLoadingScreen(display);
	display->Update();
}