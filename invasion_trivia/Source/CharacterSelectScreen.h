
// ================================================================================================
// Defines
// ================================================================================================
#define ctNone						 0
#define ctCharacterMale1	 1
#define ctCharacterMale2	 2
#define ctCharacterMale3	 3
#define ctCharacterFemale1 4
#define ctCharacterFemale2 5
#define ctCharacterFemale3 6


// ================================================================================================
// Globals
// ================================================================================================
Surface* CharacterMale1[6] = { NULL, NULL, NULL, NULL, NULL, NULL };
Surface* CharacterMale2[6] = { NULL, NULL, NULL, NULL, NULL, NULL };
Surface* CharacterMale3[6] = { NULL, NULL, NULL, NULL, NULL, NULL };
Surface* CharacterFemale1[6] = { NULL, NULL, NULL, NULL, NULL, NULL };
Surface* CharacterFemale2[6] = { NULL, NULL, NULL, NULL, NULL, NULL };
Surface* CharacterFemale3[6] = { NULL, NULL, NULL, NULL, NULL, NULL };
Surface* CharacterSelectScreenBackground = NULL;
Surface* CharacterSelectBox							 = NULL;
SoundFX  sfxCharacterSelect;
int			 CharacterMale1_X								 = 28;
int			 CharacterMale1_Y								 = 54;
int			 CharacterFemale1_X							 = 142;
int			 CharacterFemale1_Y							 = 54;
int			 CharacterMale2_X								 = 28;
int			 CharacterMale2_Y								 = 136;
int			 CharacterFemale2_X							 = 142;
int			 CharacterFemale2_Y							 = 136;
int			 CharacterMale3_X								 = 28;
int			 CharacterMale3_Y								 = 218;
int			 CharacterFemale3_X							 = 142;
int			 CharacterFemale3_Y							 = 218;
int			 characterTapped								 = ctNone;
int			 ctFadeVal											 = 255;
int			 ctFadeDir											 = 1; // 1 = Down, 2 = Up
int		   characterSelected               = ctNone;
SoundFX  sfxDropDownItemSelected;


// ================================================================================================
// Loader
// ================================================================================================
void loaderCharacterSelectScreen(DisplayDevice* display) {
	CharacterMale1[0]		= LoadImage(display, IDR_CHARACTER_MALE_1_A);
	CharacterMale1[1]		= LoadImage(display, IDR_CHARACTER_MALE_1_B);
	CharacterMale1[2]		= LoadImage(display, IDR_CHARACTER_MALE_1_C);
	CharacterMale1[3]		= LoadImage(display, IDR_CHARACTER_MALE_1_D);
	CharacterMale2[0]		= LoadImage(display, IDR_CHARACTER_MALE_2_A);
	CharacterMale2[1]		= LoadImage(display, IDR_CHARACTER_MALE_2_B);
	CharacterMale2[2]		= LoadImage(display, IDR_CHARACTER_MALE_2_C);
	CharacterMale2[3]		= LoadImage(display, IDR_CHARACTER_MALE_2_D);
	CharacterMale3[0]		= LoadImage(display, IDR_CHARACTER_MALE_3_A);
	CharacterMale3[1]		= LoadImage(display, IDR_CHARACTER_MALE_3_B);
	CharacterMale3[2]		= LoadImage(display, IDR_CHARACTER_MALE_3_C);
	CharacterMale3[3]		= LoadImage(display, IDR_CHARACTER_MALE_3_D);
	CharacterFemale1[0] = LoadImage(display, IDR_CHARACTER_FEMALE_1_A);
	CharacterFemale1[1] = LoadImage(display, IDR_CHARACTER_FEMALE_1_B);
	CharacterFemale1[2] = LoadImage(display, IDR_CHARACTER_FEMALE_1_C);
	CharacterFemale1[3] = LoadImage(display, IDR_CHARACTER_FEMALE_1_D);
	CharacterFemale2[0] = LoadImage(display, IDR_CHARACTER_FEMALE_2_A);
	CharacterFemale2[1] = LoadImage(display, IDR_CHARACTER_FEMALE_2_B);
	CharacterFemale2[2] = LoadImage(display, IDR_CHARACTER_FEMALE_2_C);
	CharacterFemale2[3] = LoadImage(display, IDR_CHARACTER_FEMALE_2_D);
	CharacterFemale3[0] = LoadImage(display, IDR_CHARACTER_FEMALE_3_A);
	CharacterFemale3[1] = LoadImage(display, IDR_CHARACTER_FEMALE_3_B);
	CharacterFemale3[2] = LoadImage(display, IDR_CHARACTER_FEMALE_3_C);
	CharacterFemale3[3] = LoadImage(display, IDR_CHARACTER_FEMALE_3_D);
	CharacterSelectScreenBackground = LoadImage(display, IDR_CHARACTER_SELECT_SCREEN_BACKGROUND);
	CharacterSelectBox = LoadImage(display, IDR_CHARACTER_SELECT_BOX);
	CharacterSelectBox->SetColorMask(Color(0, 0, 0));
	sfxCharacterSelect.load(_Module.GetModuleInstance(), IDR_SFX_CHARACTER_SELECT);
}


// ================================================================================================
// Releaser
// ================================================================================================
void releaserCharacterSelectScreen() {
	delete CharacterMale1[0];
	delete CharacterMale1[1];
	delete CharacterMale1[2];
	delete CharacterMale1[3];
	delete CharacterMale2[0];
	delete CharacterMale2[1];
	delete CharacterMale2[2];
	delete CharacterMale2[3];
	delete CharacterMale3[0];
	delete CharacterMale3[1];
	delete CharacterMale3[2];
	delete CharacterMale3[3];
	delete CharacterFemale1[0];
	delete CharacterFemale1[1];
	delete CharacterFemale1[2];
	delete CharacterFemale1[3];
	delete CharacterFemale2[0];
	delete CharacterFemale2[1];
	delete CharacterFemale2[2];
	delete CharacterFemale2[3];
	delete CharacterFemale3[0];
	delete CharacterFemale3[1];
	delete CharacterFemale3[2];
	delete CharacterFemale3[3];
	delete CharacterSelectScreenBackground;
	delete CharacterSelectBox;
}


// ================================================================================================
// Handler
// ================================================================================================
void handlerCharacterSelectScreen(DisplayDevice* display) {
	if (!ProcessEvents) { ProcessEvents = true; }
	display->Blit(0, 0, CharacterSelectScreenBackground);
	PFE_drawText(display, pFont, L"Please select",    PFE_ALIGN_CENTER, 0, 6,  gradientR, gradientG, gradientB, true);
	PFE_drawText(display, pFont, L"your character:", PFE_ALIGN_CENTER, 0, 24, gradientR, gradientG, gradientB, true);
	display->SetBlending((char)ctFadeVal);
	switch (characterTapped) {
		case ctCharacterMale1: {
			display->Blit(CharacterMale1_X - 4, CharacterMale1_Y - 4, CharacterSelectBox);
		break; }
		case ctCharacterFemale1: {
			display->Blit(CharacterFemale1_X - 4, CharacterFemale1_Y - 4, CharacterSelectBox);
		break; }
		case ctCharacterMale2: {
			display->Blit(CharacterMale2_X - 4, CharacterMale2_Y - 4, CharacterSelectBox);
		break; }
		case ctCharacterFemale2: {
			display->Blit(CharacterFemale2_X - 4, CharacterFemale2_Y - 4, CharacterSelectBox);
		break; }
		case ctCharacterMale3: {
			display->Blit(CharacterMale3_X - 4, CharacterMale3_Y - 4, CharacterSelectBox);
		break; }
		case ctCharacterFemale3: {
			display->Blit(CharacterFemale3_X - 4, CharacterFemale3_Y - 4, CharacterSelectBox);
		break; }
	}
	display->SetBlending(255);
	if (characterTapped == ctCharacterMale1) {
		display->Blit(CharacterMale1_X, CharacterMale1_Y, CharacterMale1[3]);
	} else {
		display->Blit(CharacterMale1_X, CharacterMale1_Y, CharacterMale1[0]);
	}
	if (characterTapped == ctCharacterFemale1) {
		display->Blit(CharacterFemale1_X, CharacterFemale1_Y, CharacterFemale1[3]);
	} else {
		display->Blit(CharacterFemale1_X, CharacterFemale1_Y, CharacterFemale1[0]);
	}
	if (characterTapped == ctCharacterMale2) {
		display->Blit(CharacterMale2_X, CharacterMale2_Y, CharacterMale2[3]);
	} else {
		display->Blit(CharacterMale2_X, CharacterMale2_Y, CharacterMale2[0]);
	}
	if (characterTapped == ctCharacterFemale2) {
		display->Blit(CharacterFemale2_X, CharacterFemale2_Y, CharacterFemale2[3]);
	} else {
		display->Blit(CharacterFemale2_X, CharacterFemale2_Y, CharacterFemale2[0]);
	}
	if (characterTapped == ctCharacterMale3) {
		display->Blit(CharacterMale3_X, CharacterMale3_Y, CharacterMale3[3]);
	} else {
		display->Blit(CharacterMale3_X, CharacterMale3_Y, CharacterMale3[0]);
	}
	if (characterTapped == ctCharacterFemale3) {
		display->Blit(CharacterFemale3_X, CharacterFemale3_Y, CharacterFemale3[3]);
	} else {
		display->Blit(CharacterFemale3_X, CharacterFemale3_Y, CharacterFemale3[0]);
	}
	if (ctFadeDir == 1)  { ctFadeVal = ctFadeVal - 15; } else { ctFadeVal = ctFadeVal + 15; }
	if (ctFadeVal < 75)  { ctFadeVal = 75;  ctFadeDir = 2; }
	if (ctFadeVal > 255) { ctFadeVal = 255; ctFadeDir = 1; }
}


// ================================================================================================
// Event Handlers
// ================================================================================================
void stylusDownCharacterSelectScreen(Point stylusPoint) {
	Rect menuBounds;
	// Male 1
	menuBounds.Set(CharacterMale1_X, CharacterMale1_Y, CharacterMale1_X + 70, CharacterMale1_Y + 70);
	if (menuBounds.Contains(stylusPoint)) { 
		ctFadeVal = 255;
		ctFadeDir = 1;
		characterTapped = ctCharacterMale1;
		return;
	}
	// Female 1
	menuBounds.Set(CharacterFemale1_X, CharacterFemale1_Y, CharacterFemale1_X + 70, CharacterFemale1_Y + 70);
	if (menuBounds.Contains(stylusPoint)) {
		ctFadeVal = 255;
		ctFadeDir = 1;
		characterTapped = ctCharacterFemale1;
		return;
	}
	// Male 2
	menuBounds.Set(CharacterMale2_X, CharacterMale2_Y, CharacterMale2_X + 70, CharacterMale2_Y + 70);
	if (menuBounds.Contains(stylusPoint)) {
		ctFadeVal = 255;
		ctFadeDir = 1;
		characterTapped = ctCharacterMale2;
		return;
	}
	// Female 2
	menuBounds.Set(CharacterFemale2_X, CharacterFemale2_Y, CharacterFemale2_X + 70, CharacterFemale2_Y + 70);
	if (menuBounds.Contains(stylusPoint)) {
		ctFadeVal = 255;
		ctFadeDir = 1;
		characterTapped = ctCharacterFemale2;
		return;
	}
	// Male 3
	menuBounds.Set(CharacterMale3_X, CharacterMale3_Y, CharacterMale3_X + 70, CharacterMale3_Y + 70);
	if (menuBounds.Contains(stylusPoint)) {
		ctFadeVal = 255;
		ctFadeDir = 1;
		characterTapped = ctCharacterMale3;
		return;
	}
	// Female 3
	menuBounds.Set(CharacterFemale3_X, CharacterFemale3_Y, CharacterFemale3_X + 70, CharacterFemale3_Y + 70);
	if (menuBounds.Contains(stylusPoint)) {
		ctFadeVal = 255;
		ctFadeDir = 1;
		characterTapped = ctCharacterFemale3;
		return;
	}
}

void stylusMoveCharacterSelectScreen(Point stylusPoint) {
}

void stylusUpCharacterSelectScreen(Point stylusPoint) {
	Rect menuBounds;
	// Male 1
	menuBounds.Set(CharacterMale1_X, CharacterMale1_Y, CharacterMale1_X + 70, CharacterMale1_Y + 70);
	if (menuBounds.Contains(stylusPoint) && characterTapped == ctCharacterMale1) { 
		if (characterSelected == characterTapped) {
			game.itPlaySFX(&sfxCharacterSelect, false);
			characterTapped = ctNone;
			game.CharacterInUse = ctCharacterMale1;
			ProcessEvents = false;
			game.currentScreen = csPointLevelsScreen;
		} else {
			game.itPlaySFX(&sfxDropDownItemSelected, false);
			characterSelected = characterTapped;
		}
		return;
	}
	// Female 1
	menuBounds.Set(CharacterFemale1_X, CharacterFemale1_Y, CharacterFemale1_X + 70, CharacterFemale1_Y + 70);
	if (menuBounds.Contains(stylusPoint) && characterTapped == ctCharacterFemale1) {
		if (characterSelected == characterTapped) {
			game.itPlaySFX(&sfxCharacterSelect, false);
			characterTapped = ctNone;
			game.CharacterInUse = ctCharacterFemale1;
			ProcessEvents = false;
			game.currentScreen = csPointLevelsScreen;
		} else {
			game.itPlaySFX(&sfxDropDownItemSelected, false);
			characterSelected = characterTapped;
		}
		return;
	}
	// Male 2
	menuBounds.Set(CharacterMale2_X, CharacterMale2_Y, CharacterMale2_X + 70, CharacterMale2_Y + 70);
	if (menuBounds.Contains(stylusPoint) && characterTapped == ctCharacterMale2) {
		if (characterSelected == characterTapped) {
			game.itPlaySFX(&sfxCharacterSelect, false);
			characterTapped = ctNone;
			game.CharacterInUse = ctCharacterMale2;
			ProcessEvents = false;
			game.currentScreen = csPointLevelsScreen;
		} else {
			game.itPlaySFX(&sfxDropDownItemSelected, false);
			characterSelected = characterTapped;
		}
		return;
	}
	// Female 2
	menuBounds.Set(CharacterFemale2_X, CharacterFemale2_Y, CharacterFemale2_X + 70, CharacterFemale2_Y + 70);
	if (menuBounds.Contains(stylusPoint) && characterTapped == ctCharacterFemale2) {
		if (characterSelected == characterTapped) {
			game.itPlaySFX(&sfxCharacterSelect, false);
			characterTapped = ctNone;
			game.CharacterInUse = ctCharacterFemale2;
			ProcessEvents = false;
			game.currentScreen = csPointLevelsScreen;
		} else {
			game.itPlaySFX(&sfxDropDownItemSelected, false);
			characterSelected = characterTapped;
		}
		return;
	}
	// Male 3
	menuBounds.Set(CharacterMale3_X, CharacterMale3_Y, CharacterMale3_X + 70, CharacterMale3_Y + 70);
	if (menuBounds.Contains(stylusPoint) && characterTapped == ctCharacterMale3) {
		if (characterSelected == characterTapped) {	
		  game.itPlaySFX(&sfxCharacterSelect, false);
			characterTapped = ctNone;
			game.CharacterInUse = ctCharacterMale3;
			ProcessEvents = false;
			game.currentScreen = csPointLevelsScreen;
		} else {
			game.itPlaySFX(&sfxDropDownItemSelected, false);
			characterSelected = characterTapped;
		}
		return;
	}
	// Female 3
	menuBounds.Set(CharacterFemale3_X, CharacterFemale3_Y, CharacterFemale3_X + 70, CharacterFemale3_Y + 70);
	if (menuBounds.Contains(stylusPoint) && characterTapped == ctCharacterFemale3) {
		if (characterSelected == characterTapped) {
		  game.itPlaySFX(&sfxCharacterSelect, false);
			characterTapped = ctNone;
			game.CharacterInUse = ctCharacterFemale3;
			ProcessEvents = false;
			game.currentScreen = csPointLevelsScreen;
		} else {
			game.itPlaySFX(&sfxDropDownItemSelected, false);
			characterSelected = characterTapped;
		}
		return;
	}
	characterTapped = ctNone;
}

void keyDownCharacterSelectScreen(int key) {
}

void keyUpCharacterSelectScreen(int key) {
}