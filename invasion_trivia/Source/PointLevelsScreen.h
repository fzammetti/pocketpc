
// ================================================================================================
// Globals
// ================================================================================================
Surface* imgAbandonGameButton_0					= NULL;
Surface* imgAbandonGameButton_1					= NULL;
Surface* imgNextQuestionButton_0				= NULL;
Surface* imgNextQuestionButton_1				= NULL;
Surface* imgPointLevelsScreenBackgeound = NULL;
int			 NextQuestionButton_X						= 0;
int			 NextQuestionButton_Y						= 0;
int			 NextQuestionButton_Width				= 0;
int			 NextQuestionButton_Height			= 0;
int			 AbandonGameButton_X						= 0;
int			 AbandonGameButton_Y						= 0;
int			 AbandonGameButton_Width				= 0;
int			 AbandonGameButton_Height				= 0;
int			 plBeamABrelnar_X								= 112;
int			 plBeamABrelnar_Y								= 139;
int			 plAskTheAndromedans_X					= 167;
int			 plAskTheAndromedans_Y					= 139;
int			 plMatterAntimatter_X						= 112;
int			 plMatterAntimatter_Y						= 191;
int			 plBookOfKnowledge_X						= 167;
int			 plBookOfKnowledge_Y						= 191;
int			 plVector												= 12;  // Separator between each point level text line
int			 plLeft													= 9;	 // Initial X starting position for point levels
int			 plTop													= 9;   // Initial Y starting position for point levels
int			 currentLevelPulseDir						= 1;   // 1 = Up, 2 = Down
int			 currentLevelPulseCol						= 60;
int			 buttonDown											= 0;
bool		 verifyAbandon									= false; // Set to true to do the verify abandon popup


// ================================================================================================
// Loader
// ================================================================================================
void loaderPointLevelsScreen(DisplayDevice* display) {
	imgPointLevelsScreenBackgeound = LoadImage(display, IDR_POINT_LEVELS_SCREEN_BACKGROUND);
	imgAbandonGameButton_0 = LoadImage(display, IDR_ABANDON_GAME_BUTTON_0);
	imgAbandonGameButton_0->SetColorMask(Color(0, 0, 0));
	imgAbandonGameButton_1 = LoadImage(display, IDR_ABANDON_GAME_BUTTON_1);
	imgAbandonGameButton_1->SetColorMask(Color(0, 0, 0));
	AbandonGameButton_Width = imgAbandonGameButton_0->GetWidth();
	AbandonGameButton_Height = imgAbandonGameButton_0->GetHeight();
	imgNextQuestionButton_0 = LoadImage(display, IDR_NEXT_QUESTION_BUTTON_0);
	imgNextQuestionButton_0->SetColorMask(Color(0, 0, 0));
	imgNextQuestionButton_1 = LoadImage(display, IDR_NEXT_QUESTION_BUTTON_1);
	imgNextQuestionButton_1->SetColorMask(Color(0, 0, 0));
	NextQuestionButton_Width  = imgNextQuestionButton_0->GetWidth();
	NextQuestionButton_Height = imgNextQuestionButton_0->GetHeight();
	NextQuestionButton_X			= 238 - NextQuestionButton_Width     - 9;
	NextQuestionButton_Y			= 260;
	AbandonGameButton_X				= 238 - AbandonGameButton_Width - 11;
	AbandonGameButton_Y				= 290;
}


// ================================================================================================
// Releaser
// ================================================================================================
void releaserPointLevelsScreen() {
	delete imgAbandonGameButton_0;
	delete imgNextQuestionButton_0;
	delete imgAbandonGameButton_1;
	delete imgNextQuestionButton_1;
	delete imgPointLevelsScreenBackgeound;
}


// ================================================================================================
// Handler
// ================================================================================================
void handlerPointLevelsScreen(DisplayDevice* display) {
	if (!ProcessEvents) { ProcessEvents = true; }
	// Vars used throughout
	int i		 = 0;
	int colR = 0;
	int colG = 0;
	int colB = 0;
	int x1	 = 0;
	int y1	 = 0;
	int x2	 = 0;
	int y2	 = 0;
	// Background
	display->Blit(0, 0, imgPointLevelsScreenBackgeound);
	// Box around point levels
	colR = 0; colG = 0;	colB = 255;
	x1	 = 2;	y1	 = 2;	x2	 = 88;	y2	 = 317;
	for (i = 0; i < 5; i++) {
		display->DrawRect(x1, y1, x2, y2, Color(0, 0, colB));
		x1++;	y1++;	x2--;	y2--;	colB = colB - 50;
	}
	// Corner fixup
	x1 = 237; y1 = 317; colB = 255;
	for (i = 0; i < 5; i++) {
		display->SetPixel(x1, y1, Color(colR, colG, colB));
		x1--; y1--; colB = colB - 50;
	}
	// Box around buttons
	colR = 0; colG = 0; colB = 255;
	x1 = 89;	y1 = 252;	x2 = 237;	y2 = 317;
	for (i = 0; i < 5; i++) {
		display->DrawRect(x1, y1, x2, y2, Color(0, 0, colB));
		x1++;	y1++;	x2--;	y2--;	colB = colB - 50;
	}
	// Corner fixup
	x1 = 88; y1 = 317; colB = 255;
	for (i = 0; i < 5; i++) {
		display->SetPixel(x1, y1, Color(colR, colG, colB));
		x1--; y1--; colB = colB - 50;
	}
	// Box around stats
	colR = 0; colG = 0; colB = 255;
	x1 = 89;	y1 = 2;	x2 = 237;	y2 = 251;
	for (i = 0; i < 5; i++) {
		display->DrawRect(x1, y1, x2, y2, Color(0, 0, colB));
		x1++;	y1++;	x2--;	y2--;	colB = colB - 50;
	}
	// Corner fixup
	x1 = 237; y1 = 251; colB = 255;
	for (i = 0; i < 5; i++) {
		display->SetPixel(x1, y1, Color(colR, colG, colB));
		x1--; y1--; colB = colB - 50;
	}
	// Stats
	PFE_drawText(display, pFont, L"Difficulty:",    PFE_ALIGN_NONE, 97, 9,   255, 255, 0, false);
	switch (game.difficultyLevel) {
		case dlEasy:   { PFE_drawText(display, pFont, L"Easy",   PFE_ALIGN_NONE, 97, 25, 255, 255, 255, false); break; }
		case dlNormal: { PFE_drawText(display, pFont, L"Normal", PFE_ALIGN_NONE, 97, 25, 255, 255, 255, false); break; }
		case dlHard:   { PFE_drawText(display, pFont, L"Hard",   PFE_ALIGN_NONE, 97, 25, 255, 255, 255, false);	break; }
	}
	PFE_drawText(display, pFont, L"Wrong Allowed:", PFE_ALIGN_NONE, 97, 51, 255, 255, 0, false);
	TCHAR szOut[22] = L"";
	swprintf(szOut, L"%d", game.maxWrongAllowed);
	wcscat(szOut, L" (");
	TCHAR szOut1[5] = L"";
	swprintf(szOut1, L"%d", game.maxWrongAllowed - game.numberWrong);
	wcscat(szOut, szOut1);
	wcscat(szOut, L" more)");
	PFE_drawText(display, pFont, szOut,						 PFE_ALIGN_NONE, 97, 67, 255, 255, 255, false);
	PFE_drawText(display, pFont, L"Time/Question:", PFE_ALIGN_NONE, 97, 93, 255, 255, 0, false);
	_wcsset (szOut, '\0');
	swprintf(szOut, L"%d", game.timeToAnswer);
	wcscat(szOut, L" seconds");
	PFE_drawText(display, pFont, szOut,						 PFE_ALIGN_NONE, 97, 109, 255, 255, 255, false);
	int plTopCnt = plTop;
	// Do the pulsating color changes
	if (currentLevelPulseDir == 1) { 
		currentLevelPulseCol = currentLevelPulseCol + 20;
	} else {
		currentLevelPulseCol = currentLevelPulseCol - 20;
	}
	if (currentLevelPulseCol > 255) { currentLevelPulseCol = 255; currentLevelPulseDir = 2; }
	if (currentLevelPulseCol < 60)  { currentLevelPulseCol = 60;  currentLevelPulseDir = 1; }
	// Cycle through the PointsLevel array until we hit a NULL, display each, highlighting the current level
	for (i = 0; i < game.numberPointLevels; i++) {
		if (game.currentPointLevel == i) { 
			colR = 0; colG = currentLevelPulseCol; colB = 0;
		} else { 
			colR = 255; colG = 255; colB = 255;
		}
		PFE_drawText(display, pFont, game.PointLevels[i].valueText, PFE_ALIGN_NONE, plLeft, plTopCnt, colR, colG, colB, false);
		plTopCnt = plTopCnt + plVector;
	}
	// NextQuestion and Abandon game buttons
	if (buttonDown == 1) {
		display->Blit(NextQuestionButton_X, NextQuestionButton_Y,	imgNextQuestionButton_1);
	} else {
		display->Blit(NextQuestionButton_X, NextQuestionButton_Y,	imgNextQuestionButton_0);
	}
	if (buttonDown == 2) {
		display->Blit(AbandonGameButton_X, AbandonGameButton_Y, imgAbandonGameButton_1);
	} else {
		display->Blit(AbandonGameButton_X, AbandonGameButton_Y, imgAbandonGameButton_0);
	}
	// Beam A Brelnar
	if (game.lllBeamABrelnar) {
		display->Blit(plBeamABrelnar_X,	plBeamABrelnar_Y,	imgBeamABrelnar_0);
	} else {
		display->Blit(plBeamABrelnar_X,	plBeamABrelnar_Y,	imgBeamABrelnar_Disabled);
	}
	// Ask The Andromedans
	if (game.lllAskTheAndromedans) {
		display->Blit(plAskTheAndromedans_X,	plAskTheAndromedans_Y,	imgAskTheAndromedans_0);
	} else {
		display->Blit(plAskTheAndromedans_X,	plAskTheAndromedans_Y,	imgAskTheAndromedans_Disabled);
	}
	// Matter-Antimatter
	if (game.lllMatterAntimatter) {
		display->Blit(plMatterAntimatter_X,	plMatterAntimatter_Y,	imgMatterAntimatter_0);
	} else {
		display->Blit(plMatterAntimatter_X,	plMatterAntimatter_Y,	imgMatterAntimatter_Disabled);
	}
	// Book Of Knowledge
	if (game.lllBookOfKnowledge) {
		display->Blit(plBookOfKnowledge_X,	plBookOfKnowledge_Y,	imgBookOfKnowledge_0);
	} else {
		display->Blit(plBookOfKnowledge_X,	plBookOfKnowledge_Y,	imgBookOfKnowledge_Disabled);
	}
	// Verify Abandon popup
	if (verifyAbandon) {
		TCHAR szText1[22] = L"- Abandon Game -";
		TCHAR szText2[22] = L"Are you sure?";
		PFE_Popup(display, szText1, szText2, Color(0, 0, 255), Color(0, 0, 250), PFE_POPUP_YESNO);
	}
}


// ================================================================================================
// Event Handlers
// ================================================================================================
void stylusDownPointLevelsScreen(Point stylusPoint) {
	if (verifyAbandon) {
		PFE_popupStylusDown(stylusPoint);
	} else {
		Rect buttonBounds;
		// NextQuestion Button
		buttonBounds.Set(NextQuestionButton_X, NextQuestionButton_Y, NextQuestionButton_X + NextQuestionButton_Width, NextQuestionButton_Y + NextQuestionButton_Height);
		if (buttonBounds.Contains(stylusPoint)) {
			buttonDown = 1;
		}
		// Abandon Game Button
		buttonBounds.Set(AbandonGameButton_X, AbandonGameButton_Y, AbandonGameButton_X + AbandonGameButton_Width, AbandonGameButton_Y + AbandonGameButton_Height);
		if (buttonBounds.Contains(stylusPoint)) {
			buttonDown = 2;
		}
	}
}

void stylusMovePointLevelsScreen(Point stylusPoint) {
}

void stylusUpPointLevelsScreen(Point stylusPoint) {
	if (verifyAbandon) {
		int whatPFEPressed = PFE_popupStylusUp(stylusPoint);
		switch (whatPFEPressed) {
			case 1: { // Yes
				game.itPlaySFX(&sfxPopupYes, false);
				game.itPlayThemeMusic();
				buttonDown = 0;
				verifyAbandon = false;
				ProcessEvents = false;
				game.currentScreen = csMainMenuScreen;
				return;
			break; }
			case 2: { // No
				game.itPlaySFX(&sfxPopupNo, false);
				buttonDown = 0;
				verifyAbandon = false;
				return;
			break; }
		}
	} else {
		Rect buttonBounds;
		// NextQuestion Button
		buttonBounds.Set(NextQuestionButton_X, NextQuestionButton_Y, NextQuestionButton_X + NextQuestionButton_Width, NextQuestionButton_Y + NextQuestionButton_Height);
		if (buttonBounds.Contains(stylusPoint) && buttonDown == 1) {
			game.itPlaySFX(&sfxStylusSound, false);
			buttonDown = 0;
			ChooseQuestion();
			IconTrayState = itsHidden;
			IconTrayPosition = -216;
			IconTrayButtonTapped = false;
			ViewscreenBlend = 255;
			ViewscreenLastChangeTick = 0;
		  ViewscreenCurrentlyShowing = vsStatic;
			game.QuestionTimeLeft = game.timeToAnswer;
			game.QuestionLastTick = PocketPC::GetTickCount();
			// Clear the screen to black
			ProcessEvents = false;
			game.currentScreen = csAnswerScreen;
			return;
		}
		// Abandon Game Button
		buttonBounds.Set(AbandonGameButton_X, AbandonGameButton_Y, AbandonGameButton_X + AbandonGameButton_Width, AbandonGameButton_Y + AbandonGameButton_Height);
		if (buttonBounds.Contains(stylusPoint) && buttonDown == 2) {
			game.itPlaySFX(&sfxStylusSound, false);
			buttonDown = 0;
			// Clear the screen to black
			verifyAbandon = true;
			return;
		}
	}
	// NONE
	buttonDown = 0;
}

void keyDownPointLevelsScreen(int key) {
}

void keyUpPointLevelsScreen(int key) {
}