
#include "main.h"


namespace ns_MainMenu {


// ****************************************************************************************************************
// Globals
// ****************************************************************************************************************
int	x_top           = 0; int	y_top           = 0; int w_top           = 0; int h_top           = 0;
int	x_new_game      = 0; int	y_new_game      = 0; int w_new_game      = 0; int h_new_game      = 0;
int	x_high_scores   = 0; int	y_high_scores   = 0; int w_high_scores   = 0; int h_high_scores   = 0;
int	x_continue_game = 0; int	y_continue_game = 0; int w_continue_game = 0; int h_continue_game = 0;
int	x_instructions  = 0; int	y_instructions  = 0; int w_instructions  = 0; int h_instructions  = 0;
int	x_options       = 0; int	y_options       = 0; int w_options       = 0; int h_options       = 0;
int	x_credits       = 0; int	y_credits       = 0; int w_credits       = 0; int h_credits       = 0;
int	x_quit          = 0; int	y_quit          = 0; int w_quit          = 0; int h_quit          = 0;
int	x_bottom        = 0; int	y_bottom        = 0; int w_bottom        = 0; int h_bottom        = 0;
int	x_title         = 0;
int	active_item     = 1;
int title_y         = 1;
int menu_start_y    = 53;


} // End of namespace


// ****************************************************************************************************************
// ProcessNextFrame handler
// ****************************************************************************************************************
void CGame::pnfMainMenu(CGapiSurface* backbuffer) {

	using namespace ns_MainMenu;

	if (!themePlaying) {
		themePlaying = true;
		sndObj.playSound(sfxMusicTheme);
	}

  // Set up for fading
  GDBLTFASTFX gdbltfastfx;
  gdbltfastfx.dwOpacity = fade_value;

  // Background
	scrollingBackground(backbuffer);

	// Title
	backbuffer->BltFast(x_title, title_y, menu_title, NULL, GDBLTFAST_KEYSRC | GDBLTFAST_OPACITY, &gdbltfastfx);

	// Blit menu
	backbuffer->BltFast(x_top, y_top, menu_top, NULL, GDBLTFAST_KEYSRC | GDBLTFAST_OPACITY, &gdbltfastfx);
	if (active_item == 1) {
		backbuffer->BltFast(x_new_game, y_new_game, menu_new_game_1, NULL, GDBLTFAST_KEYSRC | GDBLTFAST_OPACITY, &gdbltfastfx);
	} else {
		backbuffer->BltFast(x_new_game, y_new_game, menu_new_game_0, NULL, GDBLTFAST_KEYSRC | GDBLTFAST_OPACITY, &gdbltfastfx);
	}
	if (active_item == 2) {
		backbuffer->BltFast(x_continue_game, y_continue_game, menu_continue_game_1, NULL, GDBLTFAST_KEYSRC | GDBLTFAST_OPACITY, &gdbltfastfx);
	} else {
		backbuffer->BltFast(x_continue_game, y_continue_game, menu_continue_game_0, NULL, GDBLTFAST_KEYSRC | GDBLTFAST_OPACITY, &gdbltfastfx);
	}
	if (active_item == 3) {
		backbuffer->BltFast(x_high_scores, y_high_scores, menu_high_scores_1, NULL, GDBLTFAST_KEYSRC | GDBLTFAST_OPACITY, &gdbltfastfx);
	} else {
		backbuffer->BltFast(x_high_scores, y_high_scores, menu_high_scores_0, NULL, GDBLTFAST_KEYSRC | GDBLTFAST_OPACITY, &gdbltfastfx);
	}
	if (active_item == 4) {
		backbuffer->BltFast(x_instructions, y_instructions, menu_instructions_1, NULL, GDBLTFAST_KEYSRC | GDBLTFAST_OPACITY, &gdbltfastfx);
	} else {
		backbuffer->BltFast(x_instructions, y_instructions, menu_instructions_0, NULL, GDBLTFAST_KEYSRC | GDBLTFAST_OPACITY, &gdbltfastfx);
	}
	if (active_item == 5) {
		backbuffer->BltFast(x_options, y_options, menu_options_1, NULL, GDBLTFAST_KEYSRC | GDBLTFAST_OPACITY, &gdbltfastfx);
	} else {
		backbuffer->BltFast(x_options, y_options, menu_options_0, NULL, GDBLTFAST_KEYSRC | GDBLTFAST_OPACITY, &gdbltfastfx);
	}
	if (active_item == 6) {
		backbuffer->BltFast(x_credits, y_credits, menu_credits_1, NULL, GDBLTFAST_KEYSRC | GDBLTFAST_OPACITY, &gdbltfastfx);
	} else {
		backbuffer->BltFast(x_credits, y_credits, menu_credits_0, NULL, GDBLTFAST_KEYSRC | GDBLTFAST_OPACITY, &gdbltfastfx);
	}
	if (active_item == 7) {
		backbuffer->BltFast(x_quit, y_quit, menu_quit_1, NULL, GDBLTFAST_KEYSRC | GDBLTFAST_OPACITY, &gdbltfastfx);
	} else {
		backbuffer->BltFast(x_quit, y_quit, menu_quit_0, NULL, GDBLTFAST_KEYSRC | GDBLTFAST_OPACITY, &gdbltfastfx);
	}
	backbuffer->BltFast(x_bottom, y_bottom, menu_bottom, NULL, GDBLTFAST_KEYSRC | GDBLTFAST_OPACITY, &gdbltfastfx);

  // Fading
  screenFader();

}


// ****************************************************************************************************************
// KeyDown handler
// ****************************************************************************************************************
void CGame::kdMainMenu(DWORD dwKey) {

	using namespace ns_MainMenu;

	if (dwKey == kUp) {
    sndObj.playSound(sfxMisc3);
    active_item--;
    if (active_item < 1) { active_item = 7; }
	}

	if (dwKey == kDown) {
    sndObj.playSound(sfxMisc3);
    active_item++;
    if (active_item > 7) { active_item = 1; }
	}

}


// ****************************************************************************************************************
// KeyUp handler
// ****************************************************************************************************************
void CGame::kuMainMenu(DWORD dwKey) {

	using namespace ns_MainMenu;

  if (dwKey == kAction) {

    switch (active_item) {

      // New Game
      case 1: {
		    ngtReset();
        sndObj.playSound(sfxMisc1);
        fade_function = 1;
		    next_screen = csNewGameType;
      break; }

      // Continue Game
      case 2: {
        sndObj.playSound(sfxMisc1);
				readKGAFile();
        current_level_initialized = false;
				if (gameRestarted) {
          startingNewGame = false;
		      whichGameBeingPlayed      = 0;
		      current_level_initialized = false;
		      player_dir_north          = false;
		      player_dir_south          = false;
		      player_dir_east           = false;
		      player_dir_west           = false;
		      player_button_down        = false;
          game_mode	                = gmAdventureGame;
					doDestroy(csWalkingAroundTheShip);
				} else {
					// Do a popup...
					// Popup callback
					CGame::popupCallback = CGame::popupCallbackMainMenuContinueGame;
					// Popup options
					gpOptionsCount = 1;
					_tcscpy(gpOptions[0], TEXT("Ok"));
					// Start popup
					startPopup(TEXT("There is no saved"), TEXT("game to continue"));
				}
      break; }

      // High Scores
      case 3: {
        hisReset();
        sndObj.playSound(sfxMisc1);
        fade_function = 1;
		    next_screen = csHighScores;
      break; }

      // Instructions
      case 4: {
        insReset();
        sndObj.playSound(sfxMisc1);
        fade_function = 1;
		    next_screen = csInstructions;
      break; }

      // Options
      case 5: {
        optReset();
        sndObj.playSound(sfxMisc1);
				readKGAFile();
        fade_function = 1;
		    next_screen = csOptions;
      break; }

      // Credits
      case 6: {
        crdReset();
        sndObj.playSound(sfxMisc1);
        fade_function = 1;
		    next_screen = csCredits;
      break; }

      // Quit
      case 7: {
				sndObj.stopSounds();
        sndObj.playSound(sfxMisc1);
        ExitCounter = 0;
        ExitFadeCounter = 255;
        shutdownStep = 1;
        current_screen = csExiting;
        sndObj.playSound(sfxGameExitSound);
      break; }

    }

  }

}


// ****************************************************************************************************************
// StylusDown handler
// ****************************************************************************************************************
void CGame::sdMainMenu(POINT p) {

  using namespace ns_MainMenu;

	if (PtInRect(CRect(x_new_game, y_new_game, x_new_game + w_new_game, y_new_game + h_new_game),  p)) {
		active_item = 1;
	}
	if (PtInRect(CRect(x_continue_game, y_continue_game, x_continue_game + w_continue_game, y_continue_game + h_continue_game),  p)) {
		active_item = 2;
	}
	if (PtInRect(CRect(x_high_scores, y_high_scores, x_high_scores + w_high_scores, y_high_scores + h_high_scores),  p)) {
		active_item = 3;
	}
	if (PtInRect(CRect(x_instructions, y_instructions, x_instructions + w_instructions, y_instructions + h_instructions),  p)) {
		active_item = 4;
	}
	if (PtInRect(CRect(x_options, y_options, x_options + w_options, y_options + h_options),  p)) {
		active_item = 5;
	}
	if (PtInRect(CRect(x_credits, y_credits, x_credits + w_credits, y_credits + h_credits),  p)) {
		active_item = 6;
	}
	if (PtInRect(CRect(x_quit, y_quit, x_quit + w_quit, y_quit + h_quit),  p)) {
		active_item = 7;
	}

}


// ****************************************************************************************************************
// StylusUp handler
// ****************************************************************************************************************
void CGame::suMainMenu(POINT p) {

  using namespace ns_MainMenu;

	if (PtInRect(CRect(x_new_game, y_new_game, x_new_game + w_new_game, y_new_game + h_new_game),  p)) {
		kuMainMenu(kAction);
	}
	if (PtInRect(CRect(x_continue_game, y_continue_game, x_continue_game + w_continue_game, y_continue_game + h_continue_game),  p)) {
		kuMainMenu(kAction);
	}
	if (PtInRect(CRect(x_high_scores, y_high_scores, x_high_scores + w_high_scores, y_high_scores + h_high_scores),  p)) {
		kuMainMenu(kAction);
	}
	if (PtInRect(CRect(x_instructions, y_instructions, x_instructions + w_instructions, y_instructions + h_instructions),  p)) {
		kuMainMenu(kAction);
	}
	if (PtInRect(CRect(x_options, y_options, x_options + w_options, y_options + h_options),  p)) {
		kuMainMenu(kAction);
	}
	if (PtInRect(CRect(x_credits, y_credits, x_credits + w_credits, y_credits + h_credits),  p)) {
		kuMainMenu(kAction);
	}
	if (PtInRect(CRect(x_quit, y_quit, x_quit + w_quit, y_quit + h_quit),  p)) {
		kuMainMenu(kAction);
	}

}


// ****************************************************************************************************************
// Loader
// ****************************************************************************************************************
void CGame::loadMainMenu(CGapiSurface* backbuffer) {

  using namespace ns_MainMenu;

	processEvents = false;

	// Move on to the next step
	loading_step++;

	// Do the appropriate step
	switch(loading_step) {

    case 1: {
	    // Images for the main menu and "surround" screens
      gfxLock              = new CGapiSurface(); createSurface(TEXT("main_menu : GFX_LOCK"),                      gfxLock->CreateSurface             (0, m_config.hInstance, GFX_LOCK,                      TEXT("GRAPHICS"))); gfxLock->SetColorKey             (RGB(255, 128, 255));
	    background_tile      = new CGapiSurface(); createSurface(TEXT("main_menu : GFX_MAIN_MENU_BACKGROUND_TILE"), background_tile->CreateSurface     (0, m_config.hInstance, GFX_MAIN_MENU_BACKGROUND_TILE, TEXT("GRAPHICS"))); background_tile->SetColorKey     (RGB(255, 128, 255));
      divider_00           = new CGapiSurface(); createSurface(TEXT("main_menu : GFX_DIVIDER_00"),                divider_00->CreateSurface          (0, m_config.hInstance, GFX_DIVIDER_00,                TEXT("GRAPHICS"))); divider_00->SetColorKey          (RGB(255, 128, 255));
      menu_top             = new CGapiSurface(); createSurface(TEXT("main_menu : GFX_MENU_TOP"),                  menu_top->CreateSurface            (0, m_config.hInstance, GFX_MENU_TOP,                  TEXT("GRAPHICS"))); menu_top->SetColorKey            (RGB(255, 128, 255));
	    menu_bottom          = new CGapiSurface(); createSurface(TEXT("main_menu : GFX_MENU_BOTTOM"),               menu_bottom->CreateSurface         (0, m_config.hInstance, GFX_MENU_BOTTOM,               TEXT("GRAPHICS"))); menu_bottom->SetColorKey         (RGB(255, 128, 255));
	    menu_new_game_0      = new CGapiSurface(); createSurface(TEXT("main_menu : GFX_MENU_NEW_GAME_0"),           menu_new_game_0->CreateSurface     (0, m_config.hInstance, GFX_MENU_NEW_GAME_0,           TEXT("GRAPHICS"))); menu_new_game_0->SetColorKey     (RGB(255, 128, 255));
	    menu_new_game_1      = new CGapiSurface(); createSurface(TEXT("main_menu : GFX_MENU_NEW_GAME_1"),           menu_new_game_1->CreateSurface     (0, m_config.hInstance, GFX_MENU_NEW_GAME_1,           TEXT("GRAPHICS"))); menu_new_game_1->SetColorKey     (RGB(255, 128, 255));
	    menu_continue_game_0 = new CGapiSurface(); createSurface(TEXT("main_menu : GFX_MENU_CONTINUE_GAME_0"),      menu_continue_game_0->CreateSurface(0, m_config.hInstance, GFX_MENU_CONTINUE_GAME_0,      TEXT("GRAPHICS"))); menu_continue_game_0->SetColorKey(RGB(255, 128, 255));
	    menu_continue_game_1 = new CGapiSurface(); createSurface(TEXT("main_menu : GFX_MENU_CONTINUE_GAME_1"),      menu_continue_game_1->CreateSurface(0, m_config.hInstance, GFX_MENU_CONTINUE_GAME_1,      TEXT("GRAPHICS"))); menu_continue_game_1->SetColorKey(RGB(255, 128, 255));
	    menu_instructions_0  = new CGapiSurface(); createSurface(TEXT("main_menu : GFX_MENU_INSTRUCTIONS_0"),       menu_instructions_0->CreateSurface (0, m_config.hInstance, GFX_MENU_INSTRUCTIONS_0,       TEXT("GRAPHICS"))); menu_instructions_0->SetColorKey (RGB(255, 128, 255));
	    menu_instructions_1  = new CGapiSurface(); createSurface(TEXT("main_menu : GFX_MENU_INSTRUCTIONS_1"),       menu_instructions_1->CreateSurface (0, m_config.hInstance, GFX_MENU_INSTRUCTIONS_1,       TEXT("GRAPHICS"))); menu_instructions_1->SetColorKey (RGB(255, 128, 255));
	    menu_options_0       = new CGapiSurface(); createSurface(TEXT("main_menu : GFX_MENU_OPTIONS_0"),            menu_options_0->CreateSurface      (0, m_config.hInstance, GFX_MENU_OPTIONS_0,            TEXT("GRAPHICS"))); menu_options_0->SetColorKey      (RGB(255, 128, 255));
	    menu_options_1       = new CGapiSurface(); createSurface(TEXT("main_menu : GFX_MENU_OPTIONS_1"),            menu_options_1->CreateSurface      (0, m_config.hInstance, GFX_MENU_OPTIONS_1,            TEXT("GRAPHICS"))); menu_options_1->SetColorKey      (RGB(255, 128, 255));
	    menu_credits_0       = new CGapiSurface(); createSurface(TEXT("main_menu : GFX_MENU_CREDITS_0"),            menu_credits_0->CreateSurface      (0, m_config.hInstance, GFX_MENU_CREDITS_0,            TEXT("GRAPHICS"))); menu_credits_0->SetColorKey      (RGB(255, 128, 255));
	    menu_credits_1       = new CGapiSurface(); createSurface(TEXT("main_menu : GFX_MENU_CREDITS_1"),            menu_credits_1->CreateSurface      (0, m_config.hInstance, GFX_MENU_CREDITS_1,            TEXT("GRAPHICS"))); menu_credits_1->SetColorKey      (RGB(255, 128, 255));
	    menu_high_scores_0   = new CGapiSurface(); createSurface(TEXT("main_menu : GFX_MENU_HIGH_SCORES_0"),        menu_high_scores_0->CreateSurface  (0, m_config.hInstance, GFX_MENU_HIGH_SCORES_0,        TEXT("GRAPHICS"))); menu_high_scores_0->SetColorKey  (RGB(255, 128, 255));
	    menu_high_scores_1   = new CGapiSurface(); createSurface(TEXT("main_menu : GFX_MENU_HIGH_SCORES_1"),        menu_high_scores_1->CreateSurface  (0, m_config.hInstance, GFX_MENU_HIGH_SCORES_1,        TEXT("GRAPHICS"))); menu_high_scores_1->SetColorKey  (RGB(255, 128, 255));
			menu_quit_0          = new CGapiSurface(); createSurface(TEXT("main_menu : GFX_MENU_QUIT_0"),               menu_quit_0->CreateSurface         (0, m_config.hInstance, GFX_MENU_QUIT_0,               TEXT("GRAPHICS"))); menu_quit_0->SetColorKey         (RGB(255, 128, 255));
	    menu_quit_1          = new CGapiSurface(); createSurface(TEXT("main_menu : GFX_MENU_QUIT_1"),               menu_quit_1->CreateSurface         (0, m_config.hInstance, GFX_MENU_QUIT_1,               TEXT("GRAPHICS"))); menu_quit_1->SetColorKey         (RGB(255, 128, 255));
	    menu_title           = new CGapiSurface(); createSurface(TEXT("main_menu : GFX_MAIN_MENU_TITLE"),           menu_title->CreateSurface          (0, m_config.hInstance, GFX_MAIN_MENU_TITLE,           TEXT("GRAPHICS"))); menu_title->SetColorKey          (RGB(255, 128, 255));
      screenshots[0]       = new CGapiSurface(); createSurface(TEXT("main_menu : GFX_SS_A_DAY_IN_THE_STRIFE"),    screenshots[0]->CreateSurface      (0, m_config.hInstance, GFX_SS_A_DAY_IN_THE_STRIFE,    TEXT("GRAPHICS"))); screenshots[0]->SetColorKey      (RGB(255, 128, 255));
      screenshots[1]       = new CGapiSurface(); createSurface(TEXT("main_menu : GFX_SS_ALIEN_BABBLE"),           screenshots[1]->CreateSurface      (0, m_config.hInstance, GFX_SS_ALIEN_BABBLE,           TEXT("GRAPHICS"))); screenshots[1]->SetColorKey      (RGB(255, 128, 255));
      screenshots[2]       = new CGapiSurface(); createSurface(TEXT("main_menu : GFX_SS_ANTIGRAVITATOR"),         screenshots[2]->CreateSurface      (0, m_config.hInstance, GFX_SS_ANTIGRAVITATOR,         TEXT("GRAPHICS"))); screenshots[2]->SetColorKey      (RGB(255, 128, 255));
      screenshots[3]       = new CGapiSurface(); createSurface(TEXT("main_menu : GFX_SS_CONQUERROR"),             screenshots[3]->CreateSurface      (0, m_config.hInstance, GFX_SS_CONQUERROR,             TEXT("GRAPHICS"))); screenshots[3]->SetColorKey      (RGB(255, 128, 255));
      screenshots[4]       = new CGapiSurface(); createSurface(TEXT("main_menu : GFX_SS_COPYCAT"),                screenshots[4]->CreateSurface      (0, m_config.hInstance, GFX_SS_COPYCAT,                TEXT("GRAPHICS"))); screenshots[4]->SetColorKey      (RGB(255, 128, 255));
      screenshots[5]       = new CGapiSurface(); createSurface(TEXT("main_menu : GFX_SS_COSMIC_SQUIRREL"),        screenshots[5]->CreateSurface      (0, m_config.hInstance, GFX_SS_COSMIC_SQUIRREL,        TEXT("GRAPHICS"))); screenshots[5]->SetColorKey      (RGB(255, 128, 255));
      screenshots[6]       = new CGapiSurface(); createSurface(TEXT("main_menu : GFX_SS_DEATHTRAP"),              screenshots[6]->CreateSurface      (0, m_config.hInstance, GFX_SS_DEATHTRAP,              TEXT("GRAPHICS"))); screenshots[6]->SetColorKey      (RGB(255, 128, 255));
      screenshots[7]       = new CGapiSurface(); createSurface(TEXT("main_menu : GFX_SS_DEFENDOH"),               screenshots[7]->CreateSurface      (0, m_config.hInstance, GFX_SS_DEFENDOH,               TEXT("GRAPHICS"))); screenshots[7]->SetColorKey      (RGB(255, 128, 255));
      screenshots[8]       = new CGapiSurface(); createSurface(TEXT("main_menu : GFX_SS_ENGINEER"),               screenshots[8]->CreateSurface      (0, m_config.hInstance, GFX_SS_ENGINEER,               TEXT("GRAPHICS"))); screenshots[8]->SetColorKey      (RGB(255, 128, 255));
      screenshots[9]       = new CGapiSurface(); createSurface(TEXT("main_menu : GFX_SS_FAR_OUT_FOWL"),           screenshots[9]->CreateSurface      (0, m_config.hInstance, GFX_SS_FAR_OUT_FOWL,           TEXT("GRAPHICS"))); screenshots[9]->SetColorKey      (RGB(255, 128, 255));
      screenshots[10]      = new CGapiSurface(); createSurface(TEXT("main_menu : GFX_SS_FLIGHT_OF_DOOM"),         screenshots[10]->CreateSurface     (0, m_config.hInstance, GFX_SS_FLIGHT_OF_DOOM,         TEXT("GRAPHICS"))); screenshots[10]->SetColorKey     (RGB(255, 128, 255));
      screenshots[11]      = new CGapiSurface(); createSurface(TEXT("main_menu : GFX_SS_GLUTTON"),                screenshots[11]->CreateSurface     (0, m_config.hInstance, GFX_SS_GLUTTON,                TEXT("GRAPHICS"))); screenshots[11]->SetColorKey     (RGB(255, 128, 255));
      screenshots[12]      = new CGapiSurface(); createSurface(TEXT("main_menu : GFX_SS_IN_MEMORIA"),             screenshots[12]->CreateSurface     (0, m_config.hInstance, GFX_SS_IN_MEMORIA,             TEXT("GRAPHICS"))); screenshots[12]->SetColorKey     (RGB(255, 128, 255));
      screenshots[13]      = new CGapiSurface(); createSurface(TEXT("main_menu : GFX_SS_LEPAR_LAND"),             screenshots[13]->CreateSurface     (0, m_config.hInstance, GFX_SS_LEPAR_LAND,             TEXT("GRAPHICS"))); screenshots[13]->SetColorKey     (RGB(255, 128, 255));
      screenshots[14]      = new CGapiSurface(); createSurface(TEXT("main_menu : GFX_SS_MUNCHER_DUDE"),           screenshots[14]->CreateSurface     (0, m_config.hInstance, GFX_SS_MUNCHER_DUDE,           TEXT("GRAPHICS"))); screenshots[14]->SetColorKey     (RGB(255, 128, 255));
      screenshots[15]      = new CGapiSurface(); createSurface(TEXT("main_menu : GFX_SS_FFOPIR_SIRTET_PAEHC"),    screenshots[15]->CreateSurface     (0, m_config.hInstance, GFX_SS_FFOPIR_SIRTET_PAEHC,    TEXT("GRAPHICS"))); screenshots[15]->SetColorKey     (RGB(255, 128, 255));
      screenshots[16]      = new CGapiSurface(); createSurface(TEXT("main_menu : GFX_SS_REFLUXIVE"),              screenshots[16]->CreateSurface     (0, m_config.hInstance, GFX_SS_REFLUXIVE,              TEXT("GRAPHICS"))); screenshots[16]->SetColorKey     (RGB(255, 128, 255));
      screenshots[17]      = new CGapiSurface(); createSurface(TEXT("main_menu : GFX_SS_RELUCTANT_HERO"),         screenshots[17]->CreateSurface     (0, m_config.hInstance, GFX_SS_RELUCTANT_HERO,         TEXT("GRAPHICS"))); screenshots[17]->SetColorKey     (RGB(255, 128, 255));
      screenshots[18]      = new CGapiSurface(); createSurface(TEXT("main_menu : GFX_SS_SON_OF_ELIMINATOR"),      screenshots[18]->CreateSurface     (0, m_config.hInstance, GFX_SS_SON_OF_ELIMINATOR,      TEXT("GRAPHICS"))); screenshots[18]->SetColorKey     (RGB(255, 128, 255));
      screenshots[19]      = new CGapiSurface(); createSurface(TEXT("main_menu : GFX_SS_SQUISHEM"),               screenshots[19]->CreateSurface     (0, m_config.hInstance, GFX_SS_SQUISHEM,               TEXT("GRAPHICS"))); screenshots[19]->SetColorKey     (RGB(255, 128, 255));
      screenshots[20]      = new CGapiSurface(); createSurface(TEXT("main_menu : GFX_SS_THE_BOGAZ_DERBY"),        screenshots[20]->CreateSurface     (0, m_config.hInstance, GFX_SS_THE_BOGAZ_DERBY,        TEXT("GRAPHICS"))); screenshots[20]->SetColorKey     (RGB(255, 128, 255));
      screenshots[21]      = new CGapiSurface(); createSurface(TEXT("main_menu : GFX_SS_THE_ESCAPE"),             screenshots[21]->CreateSurface     (0, m_config.hInstance, GFX_SS_THE_ESCAPE,             TEXT("GRAPHICS"))); screenshots[21]->SetColorKey     (RGB(255, 128, 255));
      screenshots[22]      = new CGapiSurface(); createSurface(TEXT("main_menu : GFX_SS_THE_REDEYE_ORDER"),       screenshots[22]->CreateSurface     (0, m_config.hInstance, GFX_SS_THE_REDEYE_ORDER,       TEXT("GRAPHICS"))); screenshots[22]->SetColorKey     (RGB(255, 128, 255));
      screenshots[23]      = new CGapiSurface(); createSurface(TEXT("main_menu : GFX_SS_TROUBLE_IN_LINE_WORLD"),  screenshots[23]->CreateSurface     (0, m_config.hInstance, GFX_SS_TROUBLE_IN_LINE_WORLD,  TEXT("GRAPHICS"))); screenshots[23]->SetColorKey     (RGB(255, 128, 255));
      screenshots[24]      = new CGapiSurface(); createSurface(TEXT("main_menu : GFX_SS_VIRUS"),                  screenshots[24]->CreateSurface     (0, m_config.hInstance, GFX_SS_VIRUS,                  TEXT("GRAPHICS"))); screenshots[24]->SetColorKey     (RGB(255, 128, 255));
      icon_mini_game_melee = new CGapiSurface(); createSurface(TEXT("main_menu : GFX_ICON_MINI_GAME_MELEE"),      icon_mini_game_melee->CreateSurface(0, m_config.hInstance, GFX_ICON_MINI_GAME_MELEE,      TEXT("GRAPHICS"))); icon_mini_game_melee->SetColorKey(RGB(255, 128, 255));
      icon_adventure_game  = new CGapiSurface(); createSurface(TEXT("main_menu : GFX_ICON_ADVENTURE_GAME"),       icon_adventure_game->CreateSurface (0, m_config.hInstance, GFX_ICON_ADVENTURE_GAME,       TEXT("GRAPHICS"))); icon_adventure_game->SetColorKey (RGB(255, 128, 255));
			sfxMusicTheme        = new hssSound();      loadSFX      (TEXT("main_menu : SFX_MUSIC_THEME"),               sfxMusicTheme->load               (m_config.hInstance,    SFX_MUSIC_THEME));                                 sfxMusicTheme->loop              (true);
			themePlaying    = false;
      active_item     = 1;
			w_top					  = menu_top->GetWidth();
			w_new_game		  = menu_new_game_0->GetWidth();
			w_high_scores   = menu_high_scores_0->GetWidth();
			w_continue_game = menu_continue_game_0->GetWidth();
			w_instructions  = menu_instructions_0->GetWidth();
			w_options			  = menu_options_0->GetWidth();
			w_credits			  = menu_credits_0->GetWidth();
			w_quit				  = menu_quit_0->GetWidth();
			w_bottom			  = menu_bottom->GetWidth();
			h_top					  = menu_top->GetHeight();
			h_new_game		  = menu_new_game_0->GetHeight();
			h_high_scores   = menu_high_scores_0->GetHeight();
			h_continue_game = menu_continue_game_0->GetHeight();
			h_instructions  = menu_instructions_0->GetHeight();
			h_options			  = menu_options_0->GetHeight();
			h_credits			  = menu_credits_0->GetHeight();
			h_quit				  = menu_quit_0->GetHeight();
			x_title					= (240 - menu_title->GetWidth()) / 2;
			x_top						= (240 - w_top) / 2;
			x_new_game			= (240 - w_new_game) / 2;
			x_high_scores		= (240 - w_high_scores) / 2;
			x_continue_game = (240 - w_continue_game) / 2;
			x_instructions	= (240 - w_instructions) / 2;
			x_options				= (240 - w_options) / 2;
			x_credits				= (240 - w_credits) / 2;
			x_quit					= (240 - w_quit) / 2;
			x_bottom				= (240 - w_bottom) / 2;
			int y           = menu_start_y;
			y_top           = y;
			y               = y + h_top;
			y_new_game      = y;
			y               = y + h_new_game;
			y_continue_game = y;
			y               = y + h_continue_game;
			y_high_scores   = y;
			y               = y + h_high_scores;
			y_instructions  = y;
			y               = y + h_instructions;
			y_options       = y;
			y               = y + h_options;
			y_credits       = y;
			y               = y + h_credits;
			y_quit          = y;
			y               = y + h_quit;
			y_bottom        = y;
			readKGAFile(); // So that if we just saved a game and exited, it will be re-read as started
		break; }

		// End of loading
		default: {
			loading	= false;
      if (jumpBackToNewGameType) { current_screen = csNewGameType; }
			processEvents = true;
		break; }

	}

	// Show the Loading screen
	showLoadingScreen(backbuffer, true, true);

}


// ****************************************************************************************************************
// Destroyer
// ****************************************************************************************************************
void CGame::destroyMainMenu(CGapiSurface* backbuffer) {

	using namespace ns_MainMenu;

	processEvents = false;

	// Move on to the next step
	destroying_step++;

	// Do the appropriate step
	switch(destroying_step) {

	  case 1: {
			sndObj.stopSounds();
			themePlaying = false;
	    delete background_tile;
      delete divider_00;
      delete gfxLock;
      delete menu_top;
	    delete menu_bottom;
	    delete menu_new_game_0;
	    delete menu_new_game_1;
			delete menu_high_scores_0;
	    delete menu_high_scores_1;
	    delete menu_continue_game_0;
	    delete menu_continue_game_1;
	    delete menu_instructions_0;
	    delete menu_instructions_1;
	    delete menu_options_0;
	    delete menu_options_1;
	    delete menu_credits_0;
	    delete menu_credits_1;
	    delete menu_quit_0;
	    delete menu_quit_1;
	    delete menu_title;
      delete screenshots[0];
      delete screenshots[1];
      delete screenshots[2];
      delete screenshots[3];
      delete screenshots[4];
      delete screenshots[5];
      delete screenshots[6];
      delete screenshots[7];
      delete screenshots[8];
      delete screenshots[9];
      delete screenshots[10];
      delete screenshots[11];
      delete screenshots[12];
      delete screenshots[13];
      delete screenshots[14];
      delete screenshots[15];
      delete screenshots[16];
      delete screenshots[17];
      delete screenshots[18];
      delete screenshots[19];
      delete screenshots[20];
      delete screenshots[21];
      delete screenshots[22];
      delete screenshots[23];
      delete screenshots[24];
      delete icon_mini_game_melee;
      delete icon_adventure_game;
			delete sfxMusicTheme;
		break; }

		default: {
			// All done destroying, start loading the next screen
			current_screen = screen_after_destroy;
			doLoad();
		break; }

	}

	// Show the Loading screen
	if (shutdownStep == 0) { // If we're shutting down, we just called this method directly and executing this would probably cause an error, so let's not!
		showLoadingScreen(backbuffer, true, true);
	}

}


// ****************************************************************************************************************
// Popup Callback Handler for when Continue Game clicked and there is no saved game
// ****************************************************************************************************************
void CGame::popupCallbackMainMenuContinueGame(int option) {

  using namespace ns_MainMenu;

	// Do nothing, the popup just ends

}
