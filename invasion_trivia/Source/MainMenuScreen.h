
// ================================================================================================
// Defines
// ================================================================================================
#define miNone         0
#define miStartGame    1
#define miSettings     2
#define miInstructions 3
#define miHighScores   4
#define miCredits      5
#define miExit         6
#define tdNone				 10
#define tdIn					 11
#define tdOut					 12
#define tsNone				 20
#define tsSettings     21
#define tsInstructions 22
#define tsHighScores   23
#define tsCredits      24


// ================================================================================================
// Globals
// ================================================================================================
int			 MenuTopStartingPosition = 90;   // Vertical position menu items begin at
int			 MenuSeparation          = 4;    // Space between the bottom of a menu item and the top of the next item
int			 menuTapped							 = miNone;
int			 shockFrameIndex         = 0;
Surface* imgStartGame_0          = NULL;
Surface* imgSettings_0           = NULL;
Surface* imgInstructions_0       = NULL;
Surface* imgHighScores_0         = NULL;
Surface* imgCredits_0            = NULL;
Surface* imgExit_0               = NULL;
Surface* imgStartGame_1          = NULL;
Surface* imgSettings_1           = NULL;
Surface* imgInstructions_1       = NULL;
Surface* imgHighScores_1         = NULL;
Surface* imgCredits_1            = NULL;
Surface* imgExit_1               = NULL;
Surface* imgShocks[8]            = { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL };
int			 imgStartGame_X          = NULL;
int			 imgSettings_X           = NULL;
int			 imgInstructions_X       = NULL;
int			 imgHighScores_X         = NULL;
int			 imgCredits_X            = NULL;
int			 imgExit_X               = NULL;
int			 imgStartGame_Y          = NULL;
int			 imgSettings_Y           = NULL;
int			 imgInstructions_Y       = NULL;
int			 imgHighScores_Y         = NULL;
int			 imgCredits_Y            = NULL;
int			 imgExit_Y               = NULL;
int			 imgStartGame_Width      = NULL;
int			 imgSettings_Width       = NULL;
int			 imgInstructions_Width   = NULL;
int			 imgHighScores_Width     = NULL;
int			 imgCredits_Width        = NULL;
int			 imgExit_Width           = NULL;
int			 imgStartGame_Height     = NULL;
int			 imgSettings_Height      = NULL;
int			 imgInstructions_Height  = NULL;
int			 imgHighScores_Height    = NULL;
int			 imgCredits_Height       = NULL;
int			 imgExit_Height          = NULL;
bool		 doTransition						 = false;
int			 transitionVal					 = 255;
int			 transitionScreen				 = tsNone;
int			 transitionDir					 = tdNone;
// Used on sub-screens of Main Menu
int			 ReturnToMenu_X					 = 57;
int			 ReturnToMenu_Y					 = 300;
int			 ReturnToMenu_Width			 = 126;
int			 ReturnToMenu_Height		 = 16;
bool		 ReturnToMenuTapped			 = false;
// Sound FX (not all are used on the menu, but they are gloabally available so here was a good place_
SoundFX  sfxStylusSound;
SoundFX	 sfxDropDownButtons;
SoundFX	 sfxDropDownDropped;

SoundFX  sfxPopupYes;
SoundFX  sfxPopupNo;
SoundFX  sfxIconSlide;
SoundFX  sfxReturnToMenu;
SoundFX  sfxGameExitSound;


// ================================================================================================
// Loader
// ================================================================================================
void loaderMainMenuScreen(DisplayDevice* display) {
	// Load electric shock images
	imgShocks[0] = LoadImage(display, IDR_MAIN_MENU_SHOCK_1);
	imgShocks[0]->SetColorMask(Color(255, 255, 255));
	imgShocks[1] = LoadImage(display, IDR_MAIN_MENU_SHOCK_2);
	imgShocks[1]->SetColorMask(Color(255, 255, 255));
	imgShocks[2] = LoadImage(display, IDR_MAIN_MENU_SHOCK_3);
	imgShocks[2]->SetColorMask(Color(255, 255, 255));
	imgShocks[3] = LoadImage(display, IDR_MAIN_MENU_SHOCK_4);
	imgShocks[3]->SetColorMask(Color(255, 255, 255));
	imgShocks[4] = LoadImage(display, IDR_MAIN_MENU_SHOCK_5);
	imgShocks[4]->SetColorMask(Color(255, 255, 255));
	imgShocks[5] = LoadImage(display, IDR_MAIN_MENU_SHOCK_6);
	imgShocks[5]->SetColorMask(Color(255, 255, 255));
	// Load all the menu items in the inactive state
	imgStartGame_0 = LoadImage(display, IDR_MAIN_MENU_START_GAME_0);
	imgStartGame_0->SetColorMask(Color(0, 0, 0));
	imgSettings_0 = LoadImage(display, IDR_MAIN_MENU_SETTINGS_0);
	imgSettings_0->SetColorMask(Color(0, 0, 0));
	imgInstructions_0 = LoadImage(display, IDR_MAIN_MENU_INSTRUCTIONS_0);
	imgInstructions_0->SetColorMask(Color(0, 0, 0));
	imgHighScores_0 = LoadImage(display, IDR_MAIN_MENU_HIGH_SCORES_0);
	imgHighScores_0->SetColorMask(Color(0, 0, 0));
	imgCredits_0 = LoadImage(display, IDR_MAIN_MENU_CREDITS_0);
	imgCredits_0->SetColorMask(Color(0, 0, 0));
	imgExit_0 = LoadImage(display, IDR_MAIN_MENU_EXIT_0);
	imgExit_0->SetColorMask(Color(0, 0, 0));
	// Load all the menu items in their active state
	imgStartGame_1 = LoadImage(display, IDR_MAIN_MENU_START_GAME_1);
	imgStartGame_1->SetColorMask(Color(0, 0, 0));
	imgSettings_1 = LoadImage(display, IDR_MAIN_MENU_SETTINGS_1);
	imgSettings_1->SetColorMask(Color(0, 0, 0));
	imgInstructions_1 = LoadImage(display, IDR_MAIN_MENU_INSTRUCTIONS_1);
	imgInstructions_1->SetColorMask(Color(0, 0, 0));
	imgHighScores_1 = LoadImage(display, IDR_MAIN_MENU_HIGH_SCORES_1);
	imgHighScores_1->SetColorMask(Color(0, 0, 0));
	imgCredits_1 = LoadImage(display, IDR_MAIN_MENU_CREDITS_1);
	imgCredits_1->SetColorMask(Color(0, 0, 0));
	imgExit_1 = LoadImage(display, IDR_MAIN_MENU_EXIT_1);
	imgExit_1->SetColorMask(Color(0, 0, 0));
	// Get the widths of all menu items
	imgStartGame_Width     = imgStartGame_0->GetWidth();
	imgSettings_Width      = imgSettings_0->GetWidth();
	imgInstructions_Width  = imgInstructions_0->GetWidth();
	imgHighScores_Width    = imgHighScores_0->GetWidth();
	imgCredits_Width       = imgCredits_0->GetWidth();
	imgExit_Width          = imgExit_0->GetWidth();
	// Get the heights of all meun items
	imgStartGame_Height    = imgStartGame_0->GetHeight();
	imgSettings_Height     = imgSettings_0->GetHeight();
	imgInstructions_Height = imgInstructions_0->GetHeight();
	imgHighScores_Height   = imgHighScores_0->GetHeight();
	imgCredits_Height      = imgCredits_0->GetHeight();
	imgExit_Height         = imgExit_0->GetHeight();
	// Calculate the X coordinate of all menu items
	imgStartGame_X         = (240 - imgStartGame_Width)    / 2;
	imgSettings_X          = (240 - imgSettings_Width)     / 2;
	imgInstructions_X      = (240 - imgInstructions_Width) / 2;
	imgHighScores_X        = (240 - imgHighScores_Width)   / 2;
	imgCredits_X           = (240 - imgCredits_Width)      / 2;
	imgExit_X              = (240 - imgExit_Width)         / 2;
	// Calculate the Y coordinate of all menu items
	int MTSP = MenuTopStartingPosition;
	imgStartGame_Y    = MTSP;
	MTSP              = MTSP + imgStartGame_Height + MenuSeparation;
	imgSettings_Y     = MTSP;
	MTSP              = MTSP + imgSettings_Height + MenuSeparation;
	imgInstructions_Y = MTSP;
	MTSP              = MTSP + imgInstructions_Height + MenuSeparation;
	imgHighScores_Y   = MTSP;
	MTSP              = MTSP + imgHighScores_Height + MenuSeparation;
	imgCredits_Y      = MTSP;
	MTSP              = MTSP + imgCredits_Height + MenuSeparation;
	imgExit_Y         = MTSP;
	// Load our Sound FX
	sfxStylusSound.load(_Module.GetModuleInstance(), IDR_SFX_STYLUSSOUND);
	sfxDropDownButtons.load(_Module.GetModuleInstance(), IDR_SFX_DROPDOWN_BUTTONS);
	sfxDropDownDropped.load(_Module.GetModuleInstance(), IDR_SFX_DROPDOWN_DROPPED);
	sfxDropDownItemSelected.load(_Module.GetModuleInstance(), IDR_SFX_DROPDOWN_ITEM_SELECTED);
	sfxReturnToMenu.load(_Module.GetModuleInstance(), IDR_SFX_RETURN_TO_MENU);
	sfxPopupYes.load(_Module.GetModuleInstance(), IDR_SFX_POPUP_YES);
	sfxPopupNo.load(_Module.GetModuleInstance(), IDR_SFX_POPUP_NO);
	sfxIconSlide.load(_Module.GetModuleInstance(), IDR_SFX_ICON_SLIDE);
	sfxGameExitSound.load(_Module.GetModuleInstance(), IDR_SFX_GAMEEXITSOUND);
}


// ================================================================================================
// Releaser
// ================================================================================================
void releaserMainMenuScreen() {
	delete imgStartGame_0;
	delete imgSettings_0;
	delete imgInstructions_0;
	delete imgHighScores_0;
	delete imgCredits_0;
	delete imgExit_0;
	delete imgStartGame_1;
	delete imgSettings_1;
	delete imgInstructions_1;
	delete imgHighScores_1;
	delete imgCredits_1;
	delete imgExit_1;
	delete imgShocks[0];
	delete imgShocks[1];
	delete imgShocks[2];
	delete imgShocks[3];
	delete imgShocks[4];
	delete imgShocks[5];
}


// ================================================================================================
// Handler
// ================================================================================================
void handlerMainMenuScreen(DisplayDevice* display) {
	if (!ProcessEvents) { ProcessEvents = true; }
	display->Clear(Color(0, 0, 0));
	doStarfield3D(display);
	shockFrameIndex++;
	if (shockFrameIndex > 5) { shockFrameIndex = 0; }
	doITTitleBounce(display);
	display->SetBlending((char)transitionVal);
	// Start Game
	if (menuTapped == miStartGame) {
		display->Blit(0, imgStartGame_Y, imgShocks[shockFrameIndex]);
		display->Blit(imgStartGame_X, imgStartGame_Y, imgStartGame_1);
	} else {
		display->Blit(imgStartGame_X, imgStartGame_Y, imgStartGame_0);
	}
	// Instructions
	if (menuTapped == miSettings) {
		display->Blit(0, imgSettings_Y, imgShocks[shockFrameIndex]);
		display->Blit(imgSettings_X, imgSettings_Y, imgSettings_1);
	} else {
		display->Blit(imgSettings_X, imgSettings_Y, imgSettings_0);
	}
	// Instructions
	if (menuTapped == miInstructions) { 
		display->Blit(0, imgInstructions_Y, imgShocks[shockFrameIndex]);
		display->Blit(imgInstructions_X, imgInstructions_Y, imgInstructions_1);
	} else {
		display->Blit(imgInstructions_X, imgInstructions_Y, imgInstructions_0);
	}
	// High Scores
	if (menuTapped == miHighScores) { 	
		display->Blit(0, imgHighScores_Y, imgShocks[shockFrameIndex]);
		display->Blit(imgHighScores_X, imgHighScores_Y, imgHighScores_1);
	} else {
		display->Blit(imgHighScores_X, imgHighScores_Y, imgHighScores_0);
	}
	// Credits
	if (menuTapped == miCredits) {
		display->Blit(0, imgCredits_Y, imgShocks[shockFrameIndex]);
		display->Blit(imgCredits_X, imgCredits_Y, imgCredits_1);
	} else {
		display->Blit(imgCredits_X, imgCredits_Y, imgCredits_0);
	}
	// Exit
	if (menuTapped == miExit) { 	
		display->Blit(0, imgExit_Y, imgShocks[shockFrameIndex]);
		display->Blit(imgExit_X, imgExit_Y, imgExit_1);
	} else {
		display->Blit(imgExit_X, imgExit_Y, imgExit_0);
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
			// Fade out is done, go to the appropriate screen
			if (transitionVal < 0) {
				doTransition	= true;
				transitionVal = 0;
				transitionDir = tdIn;
				switch (transitionScreen) {
					case tsSettings: {
						ProcessEvents = false;
						game.currentScreen = csSettingsScreen;
					break; }
					case tsInstructions: {
						ProcessEvents = false;
						game.currentScreen = csInstructionsScreen;
					break; }
					case tsHighScores: {
						ProcessEvents = false;
						game.currentScreen = csHighScoresScreen;
					break; }
					case tsCredits: {
						ProcessEvents = false;
						game.currentScreen = csCreditsScreen;
					break; }
				}
			}
		}
	}
}


// ================================================================================================
// Event Handlers
// ================================================================================================
void stylusDownMainMenuScreen(Point stylusPoint) {
	if (!doTransition) {
		Rect menuBounds;
		// Start Game
		menuBounds.Set(imgStartGame_X, imgStartGame_Y, imgStartGame_X + imgStartGame_Width, imgStartGame_Y + imgStartGame_Height);
		if (menuBounds.Contains(stylusPoint)) { menuTapped = miStartGame; return; }
		// Settings
		menuBounds.Set(imgSettings_X, imgSettings_Y, imgSettings_X + imgSettings_Width, imgSettings_Y + imgSettings_Height);
		if (menuBounds.Contains(stylusPoint)) { menuTapped = miSettings; return; }
		// Instructions
		menuBounds.Set(imgInstructions_X, imgInstructions_Y, imgInstructions_X + imgInstructions_Width, imgInstructions_Y + imgInstructions_Height);
		if (menuBounds.Contains(stylusPoint)) { menuTapped = miInstructions; return; }
		// High Scores
		menuBounds.Set(imgHighScores_X, imgHighScores_Y, imgHighScores_X + imgHighScores_Width, imgHighScores_Y + imgHighScores_Height);
		if (menuBounds.Contains(stylusPoint)) { menuTapped = miHighScores; return; }
		// Credits
		menuBounds.Set(imgCredits_X, imgCredits_Y, imgCredits_X + imgCredits_Width, imgCredits_Y + imgCredits_Height);
		if (menuBounds.Contains(stylusPoint)) { menuTapped = miCredits; return; }
		// Exit
		menuBounds.Set(imgExit_X, imgExit_Y, imgExit_X + imgExit_Width, imgExit_Y + imgExit_Height);
		if (menuBounds.Contains(stylusPoint)) { menuTapped = miExit; return; }
		return;
	} // !doTransition
}

void stylusMoveMainMenuScreen(Point stylusPoint) {
}

void stylusUpMainMenuScreen(Point stylusPoint) {
	if (!doTransition) {
		Rect menuBounds;
		// Start Game
		menuBounds.Set(imgStartGame_X,    imgStartGame_Y,    imgStartGame_X    + imgStartGame_Width,    imgStartGame_Y    + imgStartGame_Height);
		if (menuBounds.Contains(stylusPoint) && menuTapped == miStartGame) { 
			game.itPlaySFX(&sfxStylusSound, false);
			game.itStopThemeMusic();
			menuTapped = miNone; 
			game.SetUpGame(game.difficultyLevel);
			ChooseStartGameIntroScene:
			int whatStartGameIntroScene = (rand() * (5 + 1)) / (RAND_MAX + 1); // 5 = Total # of scenes
			// If 0 comes up, choose again
			if (whatStartGameIntroScene <= 0 || whatStartGameIntroScene > 5) { goto ChooseStartGameIntroScene; }
			switch (whatStartGameIntroScene) {
				case 1: {
					SceneStarter_StartGameIntro1Scene();
					game.currentScreen	= csStartGameIntro1Scene;
				break; }
				case 2: {
					SceneStarter_StartGameIntro2Scene();
					game.currentScreen	= csStartGameIntro2Scene;
				break; }
				case 3: {
					SceneStarter_StartGameIntro3Scene();
					game.currentScreen	= csStartGameIntro3Scene;
				break; }
				case 4: {
					SceneStarter_StartGameIntro4Scene();
					game.currentScreen	= csStartGameIntro4Scene;
				break; }
				case 5: {
					SceneStarter_StartGameIntro5Scene();
					game.currentScreen	= csStartGameIntro5Scene;
				break; }
			}
			return;
		}
		// Settings
		menuBounds.Set(imgSettings_X,     imgSettings_Y,     imgSettings_X     + imgSettings_Width,     imgSettings_Y     + imgSettings_Height);
		if (menuBounds.Contains(stylusPoint) && menuTapped == miSettings) { 
			game.itPlaySFX(&sfxStylusSound, false);
			menuTapped = miNone;
			doTransition		 = true;
			transitionVal		 = 255;
			transitionScreen = tsSettings;
			transitionDir		 = tdOut;
			return;
		}
		// Instructions
		menuBounds.Set(imgInstructions_X, imgInstructions_Y, imgInstructions_X + imgInstructions_Width, imgInstructions_Y + imgInstructions_Height);
		if (menuBounds.Contains(stylusPoint) && menuTapped == miInstructions) { 
			game.itPlaySFX(&sfxStylusSound, false);
			menuTapped = miNone;
			doTransition		 = true;
			transitionVal		 = 255;
			transitionScreen = tsInstructions;
			transitionDir		 = tdOut;
			return;
		}
		// High Scores
		menuBounds.Set(imgHighScores_X,   imgHighScores_Y,   imgHighScores_X   + imgHighScores_Width,   imgHighScores_Y   + imgHighScores_Height);
		if (menuBounds.Contains(stylusPoint) && menuTapped == miHighScores) { 
			game.itPlaySFX(&sfxStylusSound, false);
			menuTapped = miNone;
			doTransition		 = true;
			transitionVal		 = 255;
			transitionScreen = tsHighScores;
			transitionDir		 = tdOut;
			return;
		}
		// Credits
		menuBounds.Set(imgCredits_X,      imgCredits_Y,      imgCredits_X      + imgCredits_Width,      imgCredits_Y      + imgCredits_Height);
		if (menuBounds.Contains(stylusPoint) && menuTapped == miCredits) { 
			game.itPlaySFX(&sfxStylusSound, false);
			menuTapped = miNone;
			doTransition		 = true;
			transitionVal		 = 255;
			transitionScreen = tsCredits;
			transitionDir		 = tdOut;
			return;
		}
		// Exit
		menuBounds.Set(imgExit_X,         imgExit_Y,         imgExit_X         + imgExit_Width,         imgExit_Y         + imgExit_Height);
		if (menuBounds.Contains(stylusPoint) && menuTapped == miExit) { 
			game.itStopThemeMusic();
			game.itPlaySFX(&sfxGameExitSound, false);
			menuTapped = miNone;
			game.currentScreen = csExiting;
			return;
		}
		menuTapped = miNone;
	} // !doTransition
}

void keyDownMainMenuScreen(int key) {
}

void keyUpMainMenuScreen(int key) {
}
