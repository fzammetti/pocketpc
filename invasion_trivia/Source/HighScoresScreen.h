
#define numElements 40

// ================================================================================================
// Globals
// ================================================================================================
PFE_DRAWTEXTCOLORCYCLECOLORSARRAYVALS colorsArray1[numElements];
PFE_DRAWTEXTCOLORCYCLECOLORSARRAYVALS colorsArray2[numElements];
PFE_DRAWTEXTCOLORCYCLECOLORSARRAYVALS colorsArray3[numElements];
int StartOfText = 106;
Surface* imgHS_None = NULL;


// ================================================================================================
// Loader
// ================================================================================================
void loaderHighScoresScreen(DisplayDevice* display) {
	imgHS_None = LoadImage(display, IDR_HS_NONE);
	int colVal = 0;
	int i = 0;
	int j = 0;
	for (i = 0; i < numElements; i++) {
		if (i < 8) { 
			colVal = 255; 
		} else { 
			colVal = 255 - (6 * j);
			if (colVal < 0) { 
				colVal = 0; 
			}
			j++;
		}
		colorsArray1[i].red		= colVal;
		colorsArray1[i].green = 0;
		colorsArray1[i].blue	= 0;
		colorsArray2[i].red		= 0;
		colorsArray2[i].green = colVal;
		colorsArray2[i].blue	= 0;
		colorsArray3[i].red		= 0;
		colorsArray3[i].green = 0;
		colorsArray3[i].blue	= colVal;
	}
}


// ================================================================================================
// Releaser
// ================================================================================================
void releaserHighScoresScreen() {
	delete imgHS_None;
}


// ================================================================================================
// Handler
// ================================================================================================
void handlerHighScoresScreen(DisplayDevice* display) {
	if (!ProcessEvents) { ProcessEvents = true; }
	display->Clear(Color(0, 0, 0));
	doStarfield3D(display);
	doITTitleBounce(display);
	display->SetBlending((char)transitionVal);
	// Lines
	display->Blit(0, 60, imgCreditsLine);
	display->Blit(0, 290, imgCreditsLine);
	TCHAR szOut[22] = L"";

	// Hard
	switch (HighScoreHard.characterUsed) {
		case ctNone:						 { display->Blit(2, 65, imgHS_None);					break; }
		case ctCharacterMale1:	 { display->Blit(2, 65, CharacterMale1[0]);		break; }
		case ctCharacterMale2:	 { display->Blit(2, 65, CharacterMale2[0]);		break; }
		case ctCharacterMale3:	 { display->Blit(2, 65, CharacterMale3[0]);		break; }
		case ctCharacterFemale1: { display->Blit(2, 65, CharacterFemale1[0]); break; }
		case ctCharacterFemale2: { display->Blit(2, 65, CharacterFemale2[0]); break; }
		case ctCharacterFemale3: { display->Blit(2, 65, CharacterFemale3[0]); break; }
	}
	PFE_drawText(display, pFont, L"Difficulty: Hard", PFE_ALIGN_NONE, 75, 70, colorsArray1, numElements, PFE_CCDIR_LEFT);
	wcscpy(szOut, L"Player: ");
	wcscat(szOut, HighScoreHard.playerName);
	PFE_drawText(display, pFont, szOut, PFE_ALIGN_NONE, 75, 90, colorsArray2, numElements, PFE_CCDIR_RIGHT);
	game.SetUpGame(dlHard);
	wcscpy(szOut, L"Points: ");
	wcscat(szOut, game.PointLevels[HighScoreHard.pointLevelReached].valueText);
	PFE_drawText(display, pFont, szOut, PFE_ALIGN_NONE, 75, 110, colorsArray3, numElements, PFE_CCDIR_LEFT);

	// Normal
	switch (HighScoreNormal.characterUsed) {
		case ctNone:						 { display->Blit(2, 140, imgHS_None);					 break; }
		case ctCharacterMale1:	 { display->Blit(2, 140, CharacterMale1[0]);	 break; }
		case ctCharacterMale2:	 { display->Blit(2, 140, CharacterMale2[0]);	 break; }
		case ctCharacterMale3:	 { display->Blit(2, 140, CharacterMale3[0]);	 break; }
		case ctCharacterFemale1: { display->Blit(2, 140, CharacterFemale1[0]); break; }
		case ctCharacterFemale2: { display->Blit(2, 140, CharacterFemale2[0]); break; }
		case ctCharacterFemale3: { display->Blit(2, 140, CharacterFemale3[0]); break; }
	}
	PFE_drawText(display, pFont, L"Difficulty: Normal", PFE_ALIGN_NONE, 75, 145, colorsArray1, numElements, PFE_CCDIR_LEFT);
	wcscpy(szOut, L"Player: ");
	wcscat(szOut, HighScoreNormal.playerName);
	PFE_drawText(display, pFont, szOut, PFE_ALIGN_NONE, 75, 165, colorsArray2, numElements, PFE_CCDIR_RIGHT);
	game.SetUpGame(dlNormal);
	wcscpy(szOut, L"Points: ");
	wcscat(szOut, game.PointLevels[HighScoreNormal.pointLevelReached].valueText);
	PFE_drawText(display, pFont, szOut, PFE_ALIGN_NONE, 75, 185, colorsArray3, numElements, PFE_CCDIR_LEFT);

	// Easy
	switch (HighScoreEasy.characterUsed) {
		case ctNone:						 { display->Blit(2, 215, imgHS_None);					 break; }
		case ctCharacterMale1:	 { display->Blit(2, 215, CharacterMale1[0]);	 break; }
		case ctCharacterMale2:	 { display->Blit(2, 215, CharacterMale2[0]);	 break; }
		case ctCharacterMale3:	 { display->Blit(2, 215, CharacterMale3[0]);	 break; }
		case ctCharacterFemale1: { display->Blit(2, 215, CharacterFemale1[0]); break; }
		case ctCharacterFemale2: { display->Blit(2, 215, CharacterFemale2[0]); break; }
		case ctCharacterFemale3: { display->Blit(2, 215, CharacterFemale3[0]); break; }
	}
	PFE_drawText(display, pFont, L"Difficulty: Easy", PFE_ALIGN_NONE, 75, 220, colorsArray1, numElements, PFE_CCDIR_LEFT);
	wcscpy(szOut, L"Player: ");
	wcscat(szOut, HighScoreEasy.playerName);
	PFE_drawText(display, pFont, szOut, PFE_ALIGN_NONE, 75, 240, colorsArray2, numElements, PFE_CCDIR_RIGHT);
	game.SetUpGame(dlEasy);
	wcscpy(szOut, L"Points: ");
	wcscat(szOut, game.PointLevels[HighScoreEasy.pointLevelReached].valueText);
	PFE_drawText(display, pFont, szOut, PFE_ALIGN_NONE, 75, 260, colorsArray3, numElements, PFE_CCDIR_LEFT);

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
				ProcessEvents = false;
				game.currentScreen = csMainMenuScreen;
			}
		}
	}
}


// ================================================================================================
// Event Handlers
// ================================================================================================
void stylusDownHighScoresScreen(Point stylusPoint) {
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

void stylusMoveHighScoresScreen(Point stylusPoint) {
}

void stylusUpHighScoresScreen(Point stylusPoint) {
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

void keyDownHighScoresScreen(int key) {
}

void keyUpHighScoresScreen(int key) {
}