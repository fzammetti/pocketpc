
#include "main.h"


namespace ns_NewGameType {


// ****************************************************************************************************************
// Globals
// ****************************************************************************************************************
bool onTop              = true;
bool prev_down          = false;
bool next_down          = false;
int  display_mode			  = 0;
int  current_screenshot = 0;
int  which_icon         = 0;
int  sub_mode           = 0;


} // End of namespace


// ****************************************************************************************************************
// ProcessNextFrame handler
// ****************************************************************************************************************
void CGame::pnfNewGameType(CGapiSurface* backbuffer) {

	using namespace ns_NewGameType;

	if (!themePlaying) {
		themePlaying = true;
		sndObj.playSound(sfxMusicTheme);
	}

  // Unlock all games if unlock cheat hasbeen done.  Must be done here to override KGA file read.
  if (unlockCornerUL == 3 && unlockCornerUR == 3) {
    for (int i = 0; i < 25; i++) { game_unlocked[i] = true; }
  }

  // Set up for fading
  GDBLTFASTFX gdbltfastfx;
  gdbltfastfx.dwOpacity = fade_value;

  // Scrolling background
	scrollingBackground(backbuffer);

	backbuffer->DrawText(bbCenterPoint, 0, TEXT("Start A New Game"), &font1_green, GDDRAWTEXT_CENTER, NULL, GDBLTFAST_OPACITY, &gdbltfastfx);

  // Icons
  GDBLTFASTFX gdbltfastfx1;
  if (fade_function == 0) { // When not fading, it's a 50% blend
    gdbltfastfx1.dwOpacity = 128;
  } else { // When fading in or out, use fade_value when < 128
    if (fade_value < 128) {
      gdbltfastfx1.dwOpacity = fade_value;
    } else {
      gdbltfastfx1.dwOpacity = 128;
    }
  }
  GDBLTFASTFX gdbltfastfx2;
  if (fade_function == 0) { // When not fading, it's a 100% blend
    gdbltfastfx2.dwOpacity = 255;
  } else { // When fading in or out just use fade_value
    gdbltfastfx2.dwOpacity = fade_value;
  }
  if (which_icon == 0) {
    backbuffer->BltFast(29,  24, icon_adventure_game, NULL, GDBLTFAST_KEYSRC | GDBLTFAST_OPACITY, &gdbltfastfx2);
	  backbuffer->BltFast(147, 24, icon_mini_game_melee,  NULL, GDBLTFAST_KEYSRC | GDBLTFAST_OPACITY, &gdbltfastfx1);
  } else {
	  backbuffer->BltFast(29,  24, icon_adventure_game, NULL, GDBLTFAST_KEYSRC | GDBLTFAST_OPACITY, &gdbltfastfx1);
    backbuffer->BltFast(147, 24, icon_mini_game_melee,  NULL, GDBLTFAST_KEYSRC | GDBLTFAST_OPACITY, &gdbltfastfx2);
  }

  // Display mode 1: Mini-game melee
  if (display_mode == 1) {
		backbuffer->BltFast(69,  112, screenshots[current_screenshot], NULL, GDBLTFAST_KEYSRC | GDBLTFAST_OPACITY, &gdbltfastfx);
		if (!game_unlocked[current_screenshot]) {
			backbuffer->BltFast(86,  124, gfxLock, NULL, GDBLTFAST_KEYSRC | GDBLTFAST_OPACITY, &gdbltfastfx);
		}
    if (prev_down) {
		  backbuffer->BltFast(20,  156, gfx_ins_prev_1, NULL, GDBLTFAST_KEYSRC | GDBLTFAST_OPACITY, &gdbltfastfx);
    } else {
      backbuffer->BltFast(20,  156, gfx_ins_prev_0, NULL, GDBLTFAST_KEYSRC | GDBLTFAST_OPACITY, &gdbltfastfx);
    }
    if (next_down) {
      backbuffer->BltFast(196, 156, gfx_ins_next_1, NULL, GDBLTFAST_KEYSRC | GDBLTFAST_OPACITY, &gdbltfastfx);
    } else {
      backbuffer->BltFast(196, 156, gfx_ins_next_0, NULL, GDBLTFAST_KEYSRC | GDBLTFAST_OPACITY, &gdbltfastfx);
    }
	  backbuffer->DrawText(bbCenterPoint, 216, mini_game_info[current_screenshot][0], &font1, GDDRAWTEXT_CENTER, NULL, GDBLTFAST_OPACITY, &gdbltfastfx);
    backbuffer->DrawText(bbCenterPoint, 244, mini_game_info[current_screenshot][1], &font1, GDDRAWTEXT_CENTER, NULL, GDBLTFAST_OPACITY, &gdbltfastfx);
    backbuffer->DrawText(bbCenterPoint, 262, mini_game_info[current_screenshot][2], &font1, GDDRAWTEXT_CENTER, NULL, GDBLTFAST_OPACITY, &gdbltfastfx);
  }

  // Display mode 2: Adventure game
  if (display_mode == 2) {
	 backbuffer->DrawText(bbCenterPoint, 110, TEXT("Adventure mode is the"), &font1, GDDRAWTEXT_CENTER, NULL, GDBLTFAST_OPACITY, &gdbltfastfx);
	 backbuffer->DrawText(bbCenterPoint, 128, TEXT("story-driven driven mode of"), &font1, GDDRAWTEXT_CENTER, NULL, GDBLTFAST_OPACITY, &gdbltfastfx);
	 backbuffer->DrawText(bbCenterPoint, 146, TEXT("K&G Arcade, but it is also"), &font1, GDDRAWTEXT_CENTER, NULL, GDBLTFAST_OPACITY, &gdbltfastfx);
	 backbuffer->DrawText(bbCenterPoint, 164, TEXT("the way you unlock mini-games"), &font1, GDDRAWTEXT_CENTER, NULL, GDBLTFAST_OPACITY, &gdbltfastfx);
	 backbuffer->DrawText(bbCenterPoint, 182, TEXT("to play in Mini-Game Melee."), &font1, GDDRAWTEXT_CENTER, NULL, GDBLTFAST_OPACITY, &gdbltfastfx);
   // Begin A New Adventure selector
   GDFILLRECTFX gdfillrectfx;
   if (fade_function == 0) { // When not fading, it's a 50% blend
     gdfillrectfx.dwOpacity = 128;
   } else { // When fading in or out, use fade_value when < 128
     if (fade_value < 128) {
       gdfillrectfx.dwOpacity = fade_value;
     } else {
       gdfillrectfx.dwOpacity = 128;
     }
   }
   backbuffer->FillRect(CRect(0, 236, 240, 257), RGB(240, 240, 240), GDFILLRECT_OPACITY, &gdfillrectfx);
   backbuffer->DrawText(bbCenterPoint, 236, TEXT("ACTION/Click to begin game"), &font1, GDDRAWTEXT_CENTER, NULL, GDBLTFAST_OPACITY, &gdbltfastfx);
  }

  // Display mode 3: Select mini-game sub-mode
  if (display_mode == 3) {
		backbuffer->DrawText(bbCenterPoint, 110, mini_game_info[current_screenshot][0], &font1, GDDRAWTEXT_CENTER, NULL, GDBLTFAST_OPACITY, &gdbltfastfx);
		backbuffer->DrawText(bbCenterPoint, 170, TEXT("What Mini-Game Mode?"), &font1, GDDRAWTEXT_CENTER, NULL, GDBLTFAST_OPACITY, &gdbltfastfx);
    if (prev_down) {
      backbuffer->BltFast(2,  200, gfx_ins_prev_1, NULL, GDBLTFAST_KEYSRC | GDBLTFAST_OPACITY, &gdbltfastfx);
    } else {
      backbuffer->BltFast(2,  200, gfx_ins_prev_0, NULL, GDBLTFAST_KEYSRC | GDBLTFAST_OPACITY, &gdbltfastfx);
    }
    if (next_down) {
		  backbuffer->BltFast(214, 200, gfx_ins_next_1, NULL, GDBLTFAST_KEYSRC | GDBLTFAST_OPACITY, &gdbltfastfx);
    } else {
      backbuffer->BltFast(214, 200, gfx_ins_next_0, NULL, GDBLTFAST_KEYSRC | GDBLTFAST_OPACITY, &gdbltfastfx);
    }
    if (sub_mode == 0) {
      backbuffer->DrawText(bbCenterPoint, 202,   TEXT("Timed 60-Second Game"), &font1, GDDRAWTEXT_CENTER, NULL, GDBLTFAST_OPACITY, &gdbltfastfx);
    } else {
	    backbuffer->DrawText(bbCenterPoint, 202, TEXT("Play Until I Say Stop"), &font1, GDDRAWTEXT_CENTER, NULL, GDBLTFAST_OPACITY, &gdbltfastfx);
    }
  }

  // Back
  backbuffer->DrawText(bbCenterPoint, 300,  TEXT("COMMAND/Click for Main Menu"), &font1_green, GDDRAWTEXT_CENTER, NULL, GDBLTFAST_OPACITY, &gdbltfastfx);

  // Fading
  screenFader();

}


// ****************************************************************************************************************
// KeyDown handler
// ****************************************************************************************************************
void CGame::kdNewGameType(DWORD dwKey) {

	using namespace ns_NewGameType;

  // Left
  if (dwKey == kLeft) {
    if (display_mode == 1 || display_mode == 3) { prev_down = true; }
  }

  // Left
  if (dwKey == kRight) {
    if (display_mode == 1 || display_mode == 3) { next_down = true; }
  }

}


// ****************************************************************************************************************
// KeyUp handler
// ****************************************************************************************************************
void CGame::kuNewGameType(DWORD dwKey) {

	using namespace ns_NewGameType;

  // Back
  if (dwKey == kCommand) {
		loading = false;
		destroying = false;
    sndObj.playSound(sfxMisc4);
		fade_function = 1;
		next_screen = csMainMenu;
  }

  // Left
  if (dwKey == kLeft) {
    if (onTop) { // We're selecting between Mini-Game Melee and Adventure Mode
			sndObj.playSound(sfxMisc3);
      if (which_icon == 1) {
        which_icon = 0;
      } else {
        which_icon = 1;
      }
    } else { // On bottom...
      prev_down = false;
      if (display_mode == 1) { // Mini-game selection
				sndObj.playSound(sfxMisc2);
        current_screenshot--;
        if (current_screenshot < 0) { current_screenshot = 24; }
      }
      if (display_mode == 3) { // Sub-mode selection
				sndObj.playSound(sfxMisc2);
        if (sub_mode == 0) { sub_mode = 1; } else { sub_mode = 0; }
      }
    }
  }

  // Right
  if (dwKey == kRight) {
    if (onTop) { // We're selecting between Mini-Game Melee and Adventure Mode
			sndObj.playSound(sfxMisc3);
      if (which_icon == 1) {
        which_icon = 0;
      } else {
        which_icon = 1;
      }
    } else { // On bottom...
      next_down = false;
      if (display_mode == 1) { // Mini-game selection
				sndObj.playSound(sfxMisc2);
        current_screenshot++;
        if (current_screenshot > 24) { current_screenshot = 0; }
      }
      if (display_mode == 3) { // Sub-mode selection
				sndObj.playSound(sfxMisc2);
        if (sub_mode == 0) { sub_mode = 1; } else { sub_mode = 0; }
      }
    }
  }

  // Action
  if (dwKey == kAction) {
    if (!onTop) {
      if (display_mode == 1 && game_unlocked[current_screenshot]) {
				sndObj.playSound(sfxMisc1);
        display_mode = 3;
        sub_mode = 0;
        return;
      }
      if (display_mode == 2) { // Begin adventure
				sndObj.playSound(sfxMisc1);
				if (gameRestarted) {
					// Do a popup...
					// Popup callback
					CGame::popupCallback = CGame::popupCallbackVerifyNewGame;
					// Popup options
					gpOptionsCount = 2;
					_tcscpy(gpOptions[0], TEXT("Yes"));
					_tcscpy(gpOptions[1], TEXT("No"));
					// Start popup
					startPopup(TEXT("Existing saved game"), TEXT("will be lost. Continue?"));
				} else {
					gameRestarted = false;
          startingNewGame = true;
					processEvents = false;
					jumpBackToNewGameType = false;
					current_screen  = csMainMenu; // We need to have the doDestroy of the main menu called, so we need to "fool" the program into thinking that's what screen we're coming from
					game_mode = -1; // To avoid going back to the screen we're on right away
					setupForNewGame();
					doDestroy(csNewAdventure);
				}
      }
      if (display_mode == 3) { // Begin mini-game
				sndObj.playSound(sfxMisc1);
				processEvents = false;
        display_mode = 1;
        if (sub_mode == 0) {
          jumpBackToNewGameType = false;
          current_screen  = csMainMenu; // We need to have the doDestroy of the main menu called, so we need to "fool" the program into thinking that's what screen we're coming from
          game_mode = -1; // To avoid going back to the screen we're on right away
          doDestroy(melee_selection[current_screenshot]);
					current_mini_game = current_screenshot;
          game_submode    = gsmTimed;
          game_mode				= gmMiniGameMelee;
        } else {
					processEvents = false;
          jumpBackToNewGameType = false;
          current_screen  = csMainMenu; // We need to have the doDestroy of the main menu called, so we need to "fool" the program into thinking that's what screen we're coming from
          game_mode = -1; // To avoid going back to the screen we're on right away
          doDestroy(melee_selection[current_screenshot]);
					current_mini_game = current_screenshot;
          game_submode    = gsmAlaCarte;
          game_mode				= gmMiniGameMelee;
        }
      }
    } else { // We're on top, do the same as clicking down
			sndObj.playSound(sfxMisc1);
      onTop = false;
      if (which_icon == 0) { display_mode = 2; } else { display_mode = 1; }
    }
  }

    // Up
  if (dwKey == kUp) {
    if (!onTop) { // Up only has meaning when we're on the bottom
			sndObj.playSound(sfxMisc3);
      onTop = true;
      display_mode = 0;
    }
  }

  // Down
  if (dwKey == kDown) {
    if (onTop) { // Down only has meaning when we're on the top
			sndObj.playSound(sfxMisc1);
      onTop = false;
      if (which_icon == 0) { display_mode = 2; } else { display_mode = 1; }
    }
  }

}


// ****************************************************************************************************************
// StylusDown handler
// ****************************************************************************************************************
void CGame::sdNewGameType(POINT p) {

  using namespace ns_NewGameType;

	if (display_mode == 1 && PtInRect(CRect(20, 156, 44, 180),  p)) { // Previous while in melee mode
		kdNewGameType(kLeft);
		return;
	}

	if (display_mode == 1 && PtInRect(CRect(196, 156, 220, 180),  p)) { // Next while in melee mode
		kdNewGameType(kRight);
		return;
	}

	if (display_mode == 3 && PtInRect(CRect(2, 200, 26, 224),  p)) { // Previous while in sub-mode select
		kdNewGameType(kLeft);
		return;
	}

	if (display_mode == 3 && PtInRect(CRect(214, 200, 228, 224),  p)) { // Next while in sub-mode select
		kdNewGameType(kRight);
		return;
	}

}


// ****************************************************************************************************************
// StylusUp handler
// ****************************************************************************************************************
void CGame::suNewGameType(POINT p) {

  using namespace ns_NewGameType;

	// Menu
	if (!prev_down && !next_down && PtInRect(CRect(0, 300, 240, 320), p)) { 
		kuNewGameType(kCommand); 
		return;
	}

	if (!prev_down && !next_down && PtInRect(CRect(29, 24, 94, 90),  p)) { // Adventure mode
		onTop = true;
		which_icon = 1;
		kuNewGameType(kLeft);
		kuNewGameType(kDown);
		return;
	}

	if (!prev_down && !next_down && PtInRect(CRect(147, 24, 213, 90),  p)) { // Melee mode
		onTop = true;
		which_icon = 0;
		kuNewGameType(kLeft);
		kuNewGameType(kDown);
		return;
	}

	if (!prev_down && !next_down && PtInRect(CRect(0, 236, 240, 257), p)) { // Start new game
		kuNewGameType(kAction);
		return;
	}

	if (prev_down && display_mode == 1 && PtInRect(CRect(20, 156, 44, 180),  p)) { // Previous while in melee mode
		kuNewGameType(kLeft);
		return;
	}

	if (next_down && display_mode == 1 && PtInRect(CRect(196, 156, 220, 180),  p)) { // Next while in melee mode
		kuNewGameType(kRight);
		return;
	}

	if (prev_down && display_mode == 3 && PtInRect(CRect(2, 200, 26, 224),  p)) { // Previous while in sub-mode select
		kuNewGameType(kLeft);
		return;
	}

	if (next_down && display_mode == 3 && PtInRect(CRect(214, 200, 228, 224),  p)) { // Next while in sub-mode select
		kuNewGameType(kRight);
		return;
	}

	if (!prev_down && !next_down && display_mode == 3 && PtInRect(CRect(30, 200, 210, 220), p)) { // Select sub-mode
		kuNewGameType(kAction);
		return;
	}

	if (!prev_down && !next_down && display_mode == 1 && PtInRect(CRect(69, 112, 171, 214),  p)) { // Select mini-game while in melee mode
		kuNewGameType(kAction);
		return;
	}

	prev_down = false;
	next_down = false;

}


// ****************************************************************************************************************
// Utility functions
// ****************************************************************************************************************
void CGame::ngtReset() {

	using namespace ns_NewGameType;
  display_mode			 = 0;
  current_screenshot = 0;
  which_icon         = 0;
  onTop              = true;
  sub_mode           = 0;
  prev_down          = false;
  next_down          = false;

}


// ****************************************************************************************************************
// Popup Callback Handler for when New Game clicked and there is a saved game
// ****************************************************************************************************************
void CGame::popupCallbackVerifyNewGame(int option) {

  using namespace ns_NewGameType;

	if (option == 0) { // Go ahead and start a new game, overwriting existing game
		gameRestarted = false;
    startingNewGame = true;
		processEvents = false;
		jumpBackToNewGameType = false;
		current_screen  = csMainMenu; // We need to have the doDestroy of the main menu called, so we need to "fool" the program into thinking that's what screen we're coming from
		game_mode = -1; // To avoid going back to the screen we're on right away
		setupForNewGame();
		doDestroy(csNewAdventure);
	} // Otherwise we'll just abort

}