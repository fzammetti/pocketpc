
// ================================================================================================
// Globals
// ================================================================================================

// This is the actual data, line-by-line to scroll.  Each array element is a line.
TCHAR scrollerLines[][130] = { L"", 
															 L"Invasion: Trivia", 
															 L"Version 1.6",
															 L"", 
															 L"A game by", 
															 L"Frank W. Zammetti", 
															 L"and", 
															 L"Anthony Volpe", 
															 L"",
															 L"A joint production of",
															 L"Omnytex Technologies",
															 L"and",
															 L"Crackhead Creations",
															 L"",
															 L"Game concept and design:", 
															 L"Frank W. Zammetti", 
															 L"", 
															 L"Graphics:", 
															 L"99% Anthony Volpe", 
															 L"1% Frank W. Zammetti",
															 L"(If it sucks, chances are",
															 L"that Frank did it!)",
															 L"", 
															 L"Coding:", 
															 L"Frank W. Zammetti", 
															 L"",
															 L"Cut scene scripts:",
															 L"Frank W. Zammetti",
															 L"and",
															 L"Anthony Volpe",
															 L"",
															 L"Voiceovers for Gentoo:", 
															 L"Anthony Volpe", 
															 L"", 
															 L"Voiceovers for Krelmac:", 
															 L"Frank W. Zammetti", 
															 L"", 
															 L"Sound FX:", 
															 L"Frank W. Zammetti", 
															 L"", 
															 L"Title music:",
															 L"Fabian/Desire", 
															 L"", 
															 L"Anything else we forgot:", 
															 L"Frank W. Zammetti", 
															 L"and/or", 
															 L"Anthony Volpe", 
															 L"",
															 L"(And the point of all", 
															 L"that was what?!?)", 
															 L"",
															 L"We would like to",
															 L"specially thank the",
															 L"following people who",
															 L"beta-tested the game:",
															 L"Alex A.",
															 L"Brian Bohmueller",
															 L"Ian Ferguson",
															 L"Jeremy McCully",
															 L"Kyle Temkin",
															 L"Micael Samuelsson",
															 L"Michael Adcock",
															 L"MiniMe",
															 L"Refractor",
															 L"Rob",
															 L"Thomas Roessler",
															 L"Tyler R.",
															 L"",
															 L"Invasion: Trivia uses the", 
															 L"OASIS engine for it's",
															 L"cinematic cut scenes.", 
															 L"This is a proprietary", 
															 L"library written by",
															 L"Frank W. Zammetti of", 
															 L"Omnytex Technologies.", 
															 L"If you want it, give", 
															 L"me lots 'o cash!",	 
															 L"But since I know you", 
															 L"can do better on your own,",
															 L"I won't hold our breath!", 
															 L"",
															 L"Invasion: Trivia uses",
															 L"the awesome PocketFrog",
															 L"library, written by",
															 L"Thierry Tremblay, for",
															 L"it's graphics.  We",
															 L"used the extended library",
															 L"PocketFrogPlus, by",
															 L"Thomas Maniero for sound",
															 L"FX and MOD support.",
															 L"Thanks so much you guys!",
															 L"You're our heros!",
															 L"",
															 L"All voiceover recordings", 
															 L"were done on a Mac at",
															 L"Anthony's house and were", 
															 L"processed via GoldWave",
															 L"and SoundForge 6 on",
															 L"Frank's home PC.", 
															 L"Sorry BillG, Mac's are", 
															 L"kinda cool buddy!", 
															 L"",
															 L"Any resemblance to any", 
															 L"other game or game SHOW,",
															 L"whether still on the air", 
															 L"or not, is not in the",
															 L"least bit coincidence.", 
															 L"",
															 L"We feel originality is", 
															 L"VASTLY overrated and we",
															 L"therefore strive to avoid", 
															 L"it at all costs.", 
															 L"",
															 L"Invasion: Trivia...", 
															 L"Today's experiment:", 
															 L"FAILED!",
															 L"", 
															 L"", 
															 L"", 
															 L"", 
															 L"", 
															 L"", 
															 L"", 
															 L"", 
															 L"", 
															 L"", 
															 L"", 
															 L""
														};
// Note: The number of initialized L"" elements int scrollerLinesTemp should match the 
// value of scrolledLinesOnScreen variable below!
TCHAR scrollerLinesTemp[][130] = { L"", L"", L"", L"", L"", L"", L"", L"", L"", L"", L"", L""};
// The following variables are developer-adjustable
int	scrollerLinesCount		= 128; // Number of displayable elements in the scrollerLines array
int scrollerLinesOnScreen = 12;  // Number of lines to display on the screen
int	scrollerTopY					= 90;  // Top of the area the scroller covers
// The following variables are used internally and should NOT BE ALTERED!
int currentScrollerAmount = 0;   // Current amount a line is scrolled upwards
int	currentLineIndex			= 0;   // Current line currently being fed into scroller
int	fadeInAmount					= 0;   // Color fade-in index counter
int	fadeOutAmount					= 255; // Color fade-out index counter
Surface* imgCreditsLine;


// ================================================================================================
// Loader
// ================================================================================================
void loaderCreditsScreen(DisplayDevice* display) {
	imgCreditsLine = LoadImage(display, IDR_CREDITS_LINE);
}


// ================================================================================================
// Handler
// ================================================================================================
void handlerCreditsScreen(DisplayDevice* display) {
	if (!ProcessEvents) { ProcessEvents = true; }
	display->Clear(Color(0, 0, 0));
	doStarfield3D(display);
	doITTitleBounce(display);
	display->SetBlending((char)transitionVal);
	PFE_drawText(display, pFont, scrollerLinesTemp[0],  PFE_ALIGN_CENTER, 0, scrollerTopY - currentScrollerAmount, 0, fadeOutAmount, 0, false);
	for (int i=1, j=16; i < scrollerLinesOnScreen - 1; i++, j=j+16) {
		PFE_drawText(display, pFont, scrollerLinesTemp[i], PFE_ALIGN_CENTER, 0, (scrollerTopY + j)  - currentScrollerAmount, 0,	255, 0, false);
	}
	PFE_drawText(display, pFont, scrollerLinesTemp[scrollerLinesOnScreen - 1], PFE_ALIGN_CENTER, 0, scrollerTopY + (16 * (scrollerLinesOnScreen - 1)) - currentScrollerAmount, 0,	fadeInAmount, 0, false);
	// Lines
	display->Blit(0, 60, imgCreditsLine);
	display->Blit(0, 290, imgCreditsLine);
	// Update fade in and out amounts
	fadeInAmount =  fadeInAmount  + 16;
	fadeOutAmount = fadeOutAmount - 16;
	// Scroll all lines up one pixel
	currentScrollerAmount++;
	// If we've scrolled all lines up 16 pixels, it's time to cycle some text
	if (currentScrollerAmount > 15) {
		currentScrollerAmount = 0;
		// Reset our fade amounts
		fadeInAmount  = 0;
		fadeOutAmount = 255;
		// Cycle all text in the temp area upwards one full line
		for (int i = 0; i < scrollerLinesOnScreen; i++) {
			wcscpy(scrollerLinesTemp[i], scrollerLinesTemp[i + 1]);
		}
		// Get the next line of text to pop on to the bottom, or start at the beginning again if it's time
		currentLineIndex++;
		if (currentLineIndex == scrollerLinesCount) { 
			currentLineIndex = 0; 
		}
		// Pop the next string on to the bottom of our scroller area
		wcscpy(scrollerLinesTemp[scrollerLinesOnScreen - 1], scrollerLines[currentLineIndex]);
	}
	// Return To Main Menu
	if (ReturnToMenuTapped) {
		PFE_drawText(display, pFont, L"Return To Menu", PFE_ALIGN_NONE, ReturnToMenu_X, ReturnToMenu_Y, 255, 255, 0, false);
	} else {
		PFE_drawText(display, pFont, L"Return To Menu", PFE_ALIGN_NONE, ReturnToMenu_X, ReturnToMenu_Y, gradientR, gradientG, gradientB, true);
	}
	display->SetBlending(255);
	// Fade
	if (doTransition) {
		if (transitionDir == tdIn) {
			transitionVal = transitionVal + 25;
			if (transitionVal > 255) {
				doTransition		 = false;
				transitionVal		 = 255;
				transitionDir		 = tdNone;
				transitionScreen = tsNone;
			}
		} else {
			transitionVal = transitionVal - 25;
			if (transitionVal < 0) {
				doTransition	= true;
				transitionVal = 0;
				transitionDir = tdIn;
				for (int i = 0; i < 12; i++) {
					wcscpy(scrollerLinesTemp[i], L"");
				}	
				currentScrollerAmount = 0;
				currentLineIndex			= 0;
				fadeInAmount					= 0;
				fadeOutAmount					= 255;
				ProcessEvents = false;
				game.currentScreen = csMainMenuScreen;
			}
		}
	}
}


// ================================================================================================
// Releaser
// ================================================================================================
void releaserCreditsScreen() {
	delete imgCreditsLine;
}


// ================================================================================================
// Event Handlers
// ================================================================================================
void stylusDownCreditsScreen(Point stylusPoint) {
	if (!doTransition) {
		Rect itemBounds;
		// Return To Main Menu
		itemBounds.Set(ReturnToMenu_X, ReturnToMenu_Y, ReturnToMenu_X + ReturnToMenu_Width, ReturnToMenu_Y + ReturnToMenu_Height);
		if (itemBounds.Contains(stylusPoint)) { 
			ReturnToMenuTapped = true;
			return;
		}
	}
}

void stylusMoveCreditsScreen(Point stylusPoint) {
}

void stylusUpCreditsScreen(Point stylusPoint) {
	if (!doTransition) {
		Rect itemBounds;
		// Return To Main Menu
		itemBounds.Set(ReturnToMenu_X, ReturnToMenu_Y, ReturnToMenu_X + ReturnToMenu_Width, ReturnToMenu_Y + ReturnToMenu_Height);
		if (itemBounds.Contains(stylusPoint) && ReturnToMenuTapped) { 
			game.itPlaySFX(&sfxReturnToMenu, false);
			ReturnToMenuTapped = false;
			doTransition			 = true;
			transitionVal			 = 255;
			transitionScreen	 = tsNone;
			transitionDir			 = tdOut;
			return;
		}
		ReturnToMenuTapped = false;
	}
}

void keyDownCreditsScreen(int key) {
}

void keyUpCreditsScreen(int key) {
}