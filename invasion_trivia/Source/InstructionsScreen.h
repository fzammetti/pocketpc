
// ================================================================================================
// Globals
// ================================================================================================
int			 scrollCurrent		 = 0;
int			 scrollNew				 = 0;
int			 pageSwitchDir		 = 0; // 1 - Previous, 2 = Next
bool		 PreviousTapped		 = false;
bool		 NextTapped				 = false;
int			 currentPage		   = 1;
int			 scrollIncrement	 = 8;
int			 textYLocation		 = 73;
SoundFX  sfxArrows;
Surface* insNext_0				 = NULL;
Surface* insNext_1				 = NULL;
Surface* insPrev_0				 = NULL;
Surface* insPrev_1				 = NULL;
int			 totalPages				 = 24;
															 // -------------------------
TCHAR		 screen1Text[][30] = { L"Starting a game (1/24)",
															 L"",
															 L"Once you select Start Game",
															 L"from the main menu, you'll",
															 L"be introduced to your",
															 L"'hosts' for the game.",
															 L"You'll then be asked to",
															 L"choose a character to",
															 L"represent you during",
															 L"the game.",
															 L"                          ",
															 // -------------------------
															 L"Point levels screen (2/24)",
															 L"",
                               L"You'll then see the",
															 L"Ramalan point levels",
															 L"screen. Get to a million",
															 L"Ramalan points and answer",
															 L"that question right and",
															 L"you win! For each one you",
															 L"miss, a city is blown up",
															 L"THIS IS BAD.  Get too many",
															 L"wrong and Earth buys it.",
															 // -------------------------
															 L"Point levels screen (3/24)",
															 L"",
                               L"The point levels screen",
															 L"also shows the difficulty",
															 L"your playing at, how many",
															 L"wrong answers are still",
															 L"allowed and how much time",
															 L"you are allowed to answer",
															 L"It also shows the",
															 L"Zumbugwas you still have",
															 L"available to you.",
															 // -------------------------
                               L"Point levels screen (4/24)",
                               L"",
															 L"When you are ready, tap",
															 L"the Next Question button.",
															 L"You can quit the game from",
															 L"this screen at any time by",
															 L"tapping the Abandon Game",
															 L"button.  This is the only",
															 L"place you can leave the",
															 L"game from.  Note that your",
															 L"game is NOT saved!",
															 // -------------------------
                               L"Q & A's screen (5/24)",
                               L"",
															 L"Once you tap the Next",
															 L"Question button, you'll",
															 L"find yourself on the",
															 L"Question and Answers",
															 L"screen.  The time allowed",
															 L"to answer is seen counting",
															 L"down in the lower right-",
															 L"hand corner.",
															 L"",
															 // -------------------------
                               L"Q & A's screen (6/24)",
                               L"",
															 L"The TV monitor at the",
															 L"bottom shows you yourself",
															 L"as well as taunting from",
															 L"Krelmac and Gentoo.",
															 L"You'll just have to get",
															 L"used to this!",
															 L"",
															 L"",
															 L"",
															 // -------------------------
                               L"Q & A's screen (7/24)",
                               L"",
															 L"Tap an answer once to",
															 L"highlight it, tap it again",
															 L"when you are decided.",
															 L"The large button in the",
															 L"lower left-hand corner of",
															 L"the screen accesses your",
															 L"Zumbugwas. Tap it to see",
															 L"and use your available",
															 L"Zumbugwa icons.",
															 // -------------------------
                               L"Zumbugwas (8/24)",
                               L"",
															 L"On the Ramalan homeworld,",
															 L"Zumbugwas are small bugs",
															 L"that somehow manage to",
															 L"survive no matter what",
															 L"happens to them. Step on",
															 L"one, they survive. Blow",
															 L"one up, they manage to",
															 L"hang around. In short,",
															 L"they're lucky as hell!",
															 // -------------------------
                               L"Zumbugwas (9/24)",
                               L"",
															 L"In the spirit of that",
															 L"luck, Krelmac and Gentoo",
															 L"grant you four Zumbugwas",
															 L"to use. They are: Beam A",
															 L"Brelnar, Ask The",
															 L"Andromedans, Book Of",
															 L"Knowledge and Matter-",
															 L"Antimatter.",
															 L"",
															 // -------------------------
                               L"Zumbugwas (10/24)",
                               L"",
															 L"Tap a Zumbugwa icon once",
															 L"to highlight it, tap again",
															 L"to use it.  The Beam A",
															 L"Brelnar icon is the one",
															 L"with the weird little",
															 L"alien on it.  The Ask The",
															 L"Andromedans icon is the",
															 L"one with the meter on it.",
															 L"",
															 // -------------------------
                               L"Zumbugwas (11/24)",
                               L"",
															 L"The Matter-Antimatter icon",
															 L"is the one with the ",
															 L"dynamite and plunger on",
															 L"it.  The Book Of Knowledge",
															 L"icon is the one with,",
															 L"obviously enough, THE",
															 L"BOOKS ON IT!",
															 L"",
															 L"",
															 // -------------------------
                               L"Zumbugwas (12/24)",
                               L"",
															 L"Beam A Brelnar uses the",
															 L"Ramalan transporter system",
															 L"to retrieve a member of",
															 L"the Brelnar species.",
															 L"The Brelnar will tell you",
															 L"which of the answers they",
															 L"think is the right one.",
															 L"",
															 L"",
															 // -------------------------
                               L"Zumbugwas (13/24)",
                               L"",
															 L"The thing about Brelnars",
															 L"is that some are smarter",
															 L"than Einstein, but some",
															 L"are dumber than a",
															 L"Kentuckian in love with",
															 L"their cousin. You of",
															 L"course won't know which",
															 L"you got until it's too",
															 L"late, so pray first!",
															 // -------------------------
                               L"Zumbugwas (14/24)",
                               L"",
															 L"Ask The Andromedans polls",
															 L"the entire population of",
															 L"the Andromedan race and",
															 L"gives you the answer they",
															 L"think is right. Since",
															 L"it's based on the opinion",
															 L"of an entire species, the",
															 L"answer is more likely to",
															 L"be right, but not certain!",
															 // -------------------------
                               L"Zumbugwas (15/24)",
                               L"",
															 L"Book Of Knowledge is the",
															 L"ultimate cheat: it simply ",
															 L"skips the current",
															 L"question in your favor of",
															 L"course. Note that this",
															 L"Zumbugwa is taken away on",
															 L"the final question of the",
															 L"game. You didn't think it",
															 L"would be THAT easy, right?",
															 // -------------------------
                               L"Zumbugwas (16/24)",
                               L"",
															 L"Matter-Antimatter takes",
															 L"two of the questions and",
															 L"destroys them, just like",
															 L"when matter and antimatter",
															 L"come in contact with each",
															 L"other.  Strangely, one of",
															 L"the remaining question is",
															 L"always right and one is",
															 L"always wrong. Go figure!",
															 // -------------------------
                               L"Settings (17/24)",
                               L"",
															 L"Yep, that's about it.",
															 L"Note that there is no",
															 L"notion of easy or hard",
															 L"questions, some will be",
															 L"easy for you but hard for",
															 L"others. However, you can",
															 L"select from three",
															 L"difficulty levels on te",
															 L"Settings screen.",
															 // -------------------------
                               L"Settings (18/24)",
                               L"",
															 L"The Easy level gives you",
															 L"15 point levels to answer,",
															 L"you are allowed to get two",
															 L"wrong, you have 60 seconds",
															 L"per question and you get",
															 L"the Bean A Brelnar and",
															 L"Ask The Andromedans",
															 L"Zumbugwas only.",
															 L"",
															 // -------------------------
                               L"Settings (19/24)",
                               L"",
															 L"The Normal level gives you",
															 L"20 point levels to answer,",
															 L"you are allowed to get one",
															 L"wrong, you have 45 seconds",
															 L"per question and you get",
															 L"the Bean A Brelnar,",
															 L"Ask The Andromedans and",
															 L"Matter-Antimatter",
															 L"Zumbugwas only.",
															 // -------------------------
                               L"Settings (20/24)",
                               L"",
															 L"The Hard level gives you",
															 L"25 point levels to answer,",
															 L"you are allowed to get",
															 L"none wrong, you have 30",
															 L"seconds per question and",
															 L"you get all four",
															 L"Zumbugwas.",
															 L"",
															 L".           ",
															 // -------------------------
                               L"Settings (21/24)",
                               L"",
															 L"On the Settings screen you",
															 L"can also choose a font to",
															 L"use throughout the game,",
															 L"as well as load QAC packs.",
															 L"QAC packs are files which",
															 L"contain Categories,",
															 L"Questions and Answers.",
															 L"",
															 L".           ",
															 // -------------------------
                               L"Settings (22/24)",
                               L"",
															 L"QAC packs must be placed",
															 L"in the directory with the",
															 L"game executable, whereever",
															 L"that is. All files ending",
															 L"with .qac are shown in the",
															 L"drop-down. This list is",
															 L"populated when the game is",
															 L"started, so you must",
															 L"restart to add a QAC pack.",
															 // -------------------------
                               L"High Scores (23/24)",
                               L"",
															 L"The highest point level",
															 L"reached for each of the",
															 L"three difficulty levels is",
															 L"stored as a high score.",
															 L"You will be able to enter",
															 L"your name at the end of a",
															 L"successful game that",
															 L"qualifies as the high",
															 L"score for that difficulty.",
															 // -------------------------
                               L"Miscellaneous (24/24)",
                               L"",
															 L"You can abort any cut",
															 L"scene by simply tapping",
															 L"the screen, but why would",
															 L"you ever want to do that??",
															 L"Be sure to have a look at",
															 L"the Credits screen at",
															 L"some point (if you care",
															 L"about that sort of thing",
															 L"of course!)",
};
// ================================================================================================
// Loader
// ================================================================================================
void loaderInstructionsScreen(DisplayDevice* display) {
	insNext_0 = LoadImage(display, IDR_INS_NEXT_0);
	insNext_0->SetColorMask(Color(0, 0, 0));
	insNext_1 = LoadImage(display, IDR_INS_NEXT_1);
	insNext_1->SetColorMask(Color(0, 0, 0));
	insPrev_0 = LoadImage(display, IDR_INS_PREV_0);
	insPrev_0->SetColorMask(Color(0, 0, 0));
	insPrev_1 = LoadImage(display, IDR_INS_PREV_1);
	insPrev_1->SetColorMask(Color(0, 0, 0));
	sfxArrows.load(_Module.GetModuleInstance(), IDR_SFX_INSTRUCTIONS_ARROWS);
}


// ================================================================================================
// Releaser
// ================================================================================================
void releaserInstructionsScreen() {
	delete insNext_0;
	delete insNext_1;
	delete insPrev_0;
	delete insPrev_1;
}


// ================================================================================================
// Handler
// ================================================================================================
void handlerInstructionsScreen(DisplayDevice* display) {
	if (!ProcessEvents) { ProcessEvents = true; }
	display->Clear(Color(0, 0, 0));
	doStarfield3D(display);
	doITTitleBounce(display);
	display->SetBlending((char)transitionVal);
	// Draw the text for the current scree
	int lineIncr = textYLocation;
	int arrayIndex = (currentPage - 1) * 11;
	for (int i = 0; i < 11; i++) {
		PFE_drawText(display, pFont, screen1Text[i + arrayIndex], PFE_ALIGN_NONE, scrollCurrent, lineIncr, gradientR, gradientG, gradientB, true);
		lineIncr = lineIncr + 16;
	}
	// If we're changing the instructions page, do it now
	if (pageSwitchDir > 0) {
		switch (pageSwitchDir) {
			case 1: { // Previous
				arrayIndex = (currentPage - 2) * 11;
				lineIncr = textYLocation;
				for (int i = 0; i < 11; i++) {
					PFE_drawText(display, pFont, screen1Text[i + arrayIndex], PFE_ALIGN_NONE, scrollNew, lineIncr, gradientR, gradientG, gradientB, true);
					lineIncr = lineIncr + 16;
				}
				scrollNew = scrollNew + scrollIncrement;
				scrollCurrent = scrollCurrent + scrollIncrement;
				if (scrollNew >= 0) {
					scrollNew = 0;
					scrollCurrent = 0;
					pageSwitchDir = 0;
					currentPage--;
				}
			break; }
			case 2: { // Next
				arrayIndex = currentPage * 11;
				lineIncr = textYLocation;
				for (int i = 0; i < 11; i++) {
					PFE_drawText(display, pFont, screen1Text[i + arrayIndex], PFE_ALIGN_NONE, scrollNew, lineIncr, gradientR, gradientG, gradientB, true);
					lineIncr = lineIncr + 16;
				}
				scrollNew = scrollNew - scrollIncrement;
				scrollCurrent = scrollCurrent - scrollIncrement;
				if (scrollNew <= 0) {
					scrollNew = 0;
					scrollCurrent = 0;
					pageSwitchDir = 0;
					currentPage++;
				}
			break; }
		}
	}
	// Draw next/prev buttons
	if (PreviousTapped) {	
		display->Blit(15, 262, insPrev_1); 
	} else { 
		if (currentPage > 1) {
			display->Blit(15, 262, insPrev_0); 
		}
	}
	if (NextTapped)	{	
		display->Blit(201, 262, insNext_1); 
	} else { 
		if (currentPage < totalPages) {
			display->Blit(201, 262, insNext_0); 
		}
	}
	// Lines
	display->Blit(0, 60, imgCreditsLine);
	display->Blit(0, 290, imgCreditsLine);
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
				scrollCurrent		 = 0;
				scrollNew				 = 0;
				pageSwitchDir		 = 0;
				PreviousTapped	 = false;
				NextTapped			 = false;
				currentPage		   = 1;
				scrollIncrement	 = 8;
				ProcessEvents = false;
				game.currentScreen = csMainMenuScreen;
			}
		}
	}
}


// ================================================================================================
// Event Handlers
// ================================================================================================
void stylusDownInstructionsScreen(Point stylusPoint) {
	if (!doTransition) {
		Rect itemBounds;
		// Return To Main Menu
		itemBounds.Set(ReturnToMenu_X, ReturnToMenu_Y, ReturnToMenu_X + ReturnToMenu_Width, ReturnToMenu_Y + ReturnToMenu_Height);
		if (itemBounds.Contains(stylusPoint)) { 
			ReturnToMenuTapped = true;
			return;
		}
		// Previous
		itemBounds.Set(15, 262, 15 + 24, 286);
		if (itemBounds.Contains(stylusPoint) && pageSwitchDir == 0 && currentPage > 1) { 
			PreviousTapped = true;
			return;
		}
		// Next
		itemBounds.Set(201, 262, 201 + 24, 286);
		if (itemBounds.Contains(stylusPoint) && pageSwitchDir == 0 && currentPage < totalPages) { 
			NextTapped = true;
			return;
		}
	}
}

void stylusMoveInstructionsScreen(Point stylusPoint) {
}

void stylusUpInstructionsScreen(Point stylusPoint) {
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
		// Previous
		itemBounds.Set(15, 262, 15 + 24, 286);
		if (itemBounds.Contains(stylusPoint) && PreviousTapped) {
			game.itPlaySFX(&sfxArrows, false);
			NextTapped = false;
			PreviousTapped = false;
			pageSwitchDir = 1;
			scrollCurrent = 0;
			scrollNew = -240;
			return;
		}
		// Next
		itemBounds.Set(201, 262, 201 + 15, 286);
		if (itemBounds.Contains(stylusPoint) && NextTapped) { 
			game.itPlaySFX(&sfxArrows, false);
			NextTapped = false;
			PreviousTapped = false;
			pageSwitchDir = 2;
			scrollCurrent = 0;
			scrollNew = 240;
			return;
		}
		NextTapped = false;
		PreviousTapped = false;
		ReturnToMenuTapped = false;
	}
}

void keyDownInstructionsScreen(int key) {
}

void keyUpInstructionsScreen(int key) {
}