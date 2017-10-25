
#include "../main.h"


namespace ns_TheRedeyeOrder {


// ****************************************************************************************************************
// Function prototypes specific to this mini-game
// ****************************************************************************************************************
void resetBoard();


// ****************************************************************************************************************
// Globals specific to this mini-game
// ****************************************************************************************************************
TCHAR	instructions[][32] = { TEXT("The Redeye Order"),
														 TEXT(""),
														 TEXT("It's not rocket-science"),
														 TEXT("after all... Can you"),
														 TEXT("count?  GOOD!  Shouldn't"),
														 TEXT("be a problem then!"),
														 TEXT(""),
														 TEXT(""),
														 TEXT(""),
														 TEXT(""),
                             //    ---------------------------
                             TEXT("The Goal"),
														 TEXT(""),
														 TEXT("Slide the tiles into"),
														 TEXT("numerical order before"),
														 TEXT("time runs out."),
														 TEXT(""),
														 TEXT("What, you were"),
														 TEXT("expecting more?!?"),
														 TEXT(""),
														 TEXT(""),
                             //    ---------------------------
                             TEXT("How To Play"),
														 TEXT(""),
														 TEXT("Press on a tile next to"),
														 TEXT("the empty space, and the"),
														 TEXT("tile will swap itself"),
														 TEXT("with the empty space."),
														 TEXT("Keeping doing this until"),
														 TEXT("they are in order and"),
														 TEXT("the space is in the"),
														 TEXT("lower right-hand corner."),
                             //    ----------------------------
};

CGapiSurface* tiles[17];
hssSound*     sfxMove          = NULL;
hssSound*     sfxWin           = NULL;
int						tiles_index[18];
int           op_dir           = 0;
int           op               = 240;


} // End of namespace


// ****************************************************************************************************************
// ProcessNextFrame handler
// ****************************************************************************************************************
void CGame::pnfTheRedeyeOrder(CGapiSurface* backbuffer) {

	using namespace ns_TheRedeyeOrder;

	// Blit tiles
	int loc_x;
	int loc_y;
	int i = 0;
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			// Calculate the proper X/Y coordinates for each tile
			loc_x = ((x * 48) + (x * 2)) + 1;
			loc_y = ((y * 48) + (y * 2)) + 1;
			// Draw the tile depending on it's state
			if (tiles_index[i] != 15) { // 15 is a blank space
				backbuffer->BltFast(xadj + loc_x, yadj + loc_y, tiles[tiles_index[i]], NULL, GDBLTFAST_KEYSRC, NULL);
			}
			i++;
		}
	}

	// Draw the selection box around the correct tile
	loc_x = ((player_pos.x * 48) + (player_pos.x * 2)) + 0;
	loc_y = ((player_pos.y * 48) + (player_pos.y * 2)) + 0;
	RECT rect;
	SetRect(&rect, xadj + loc_x, yadj + loc_y, xadj + loc_x + 50, yadj + loc_y + 50);
  GDLINEFX gdlinefx;
  gdlinefx.dwOpacity = op;
  backbuffer->DrawRect(&rect, RGB(255, 255, 32), GDDRAWLINE_OPACITY, &gdlinefx);
  switch (op_dir) {
    case 0: {
      op = op + 10;
      if (op >= 250) { op_dir = 1; }
    break; }
    case 1: {
      op = op - 10;
      if (op <= 150) { op_dir = 0; }
    break; }
  }

	// Handle player movements
	if (player_dir_north) {
		if (player_dir_delay > 5) {
			player_dir_delay = 0;
			player_pos.y--;
			if (player_pos.y < 0) { player_pos.y = 3; }
		} else {
			player_dir_delay++;
		}
	}
	if (player_dir_south) {
		if (player_dir_delay > 5) {
			player_dir_delay = 0;
			player_pos.y++;
			if (player_pos.y > 3) { player_pos.y = 0; }
		} else {
			player_dir_delay++;
		}
	}
	if (player_dir_west) {
		if (player_dir_delay > 5) {
			player_dir_delay = 0;
			player_pos.x--;
			if (player_pos.x < 0) { player_pos.x = 3; }
		} else {
			player_dir_delay++;
		}
	}
	if (player_dir_east) {
		if (player_dir_delay > 5) {
			player_dir_delay = 0;
			player_pos.x++;
			if (player_pos.x > 3) { player_pos.x = 0; }
		} else {
			player_dir_delay++;
		}
	}

	// See if they won, end the game if so
	if (tiles_index[0]  == 0  && tiles_index[1]  == 1  && tiles_index[2]  == 2  && tiles_index[3]  == 3  &&
			tiles_index[4]  == 4  && tiles_index[5]  == 5  && tiles_index[6]  == 6  && tiles_index[7]  == 7  &&
			tiles_index[8]  == 8  && tiles_index[9]  == 9  && tiles_index[10] == 10 && tiles_index[11] == 11 &&
			tiles_index[12] == 12 && tiles_index[13] == 13 && tiles_index[14] == 14 && tiles_index[15] == 15) {
				sndObj.playSound(sfxWin);
				force_game_over = true;
				addToScore((5000 + (countdown_seconds * 50))); // More points for doing it quickly
	}
  // Cheat (only if in Adventure mode and only if level hint gotten):
  // 1, 2, 3, 4 tiles in corners going clockwise
  if (game_mode == gmAdventureGame && levelHintDone &&
      tiles_index[0] == 0 && tiles_index[3] == 1 && tiles_index[12] == 3 && tiles_index[15] == 2
     ) {
			 sndObj.playSound(sfxWin);
       force_game_over = true;
       addToScore(5000);
  }


}


// ****************************************************************************************************************
// KeyDown handler
// ****************************************************************************************************************
void CGame::kdTheRedeyeOrder(DWORD dwKey) {

	using namespace ns_TheRedeyeOrder;

	// Handle up movement events
	if (dwKey == kUp) {
		player_dir_north		 = true;
		player_dir_south		 = false;
		player_dir_east			 = false;
		player_dir_west			 = false;
		player_dir_delay		 = 10;
	}

	// Handle down movement events
	if (dwKey == kDown) {
		player_dir_north		 = false;
		player_dir_south		 = true;
		player_dir_east			 = false;
		player_dir_west			 = false;
		player_dir_delay		 = 10;
	}

	// Handle left movement events
	if (dwKey == kLeft) {
		player_dir_north		 = false;
		player_dir_south		 = false;
		player_dir_east			 = false;
		player_dir_west			 = true;
		player_dir_delay		 = 10;
	}

	// Handle right movement events
	if (dwKey == kRight) {
		player_dir_north		 = false;
		player_dir_south		 = false;
		player_dir_east			 = true;
		player_dir_west			 = false;
		player_dir_delay		 = 10;
	}

	// Handle keypresses
	if (dwKey == kAction) {
		player_button_down = true;
		int source_index = (player_pos.y * 4) + player_pos.x;
		int source_value = tiles_index[source_index];
		if (player_pos.y > 0) {
			int destination_index = ((player_pos.y - 1) * 4) + player_pos.x;
			int destination_value = tiles_index[destination_index];
			if (destination_value == 15) {
				tiles_index[destination_index] = source_value;
				tiles_index[source_index]			 = 15;
				sndObj.playSound(sfxMove);
				return;
			}
		}
		if (player_pos.y < 3) {
			int destination_index = ((player_pos.y + 1) * 4) + player_pos.x;
			int destination_value = tiles_index[destination_index];
			if (destination_value == 15) {
				tiles_index[destination_index] = source_value;
				tiles_index[source_index]			 = 15;
				sndObj.playSound(sfxMove);
				return;
			}
		}
		if (player_pos.x > 0) {
			int destination_index = (player_pos.y * 4) + (player_pos.x - 1);
			int destination_value = tiles_index[destination_index];
			if (destination_value == 15) {
				tiles_index[destination_index] = source_value;
				tiles_index[source_index]			 = 15;
				sndObj.playSound(sfxMove);
				return;
			}
		}
		if (player_pos.x < 3) {
			int destination_index = (player_pos.y * 4) + (player_pos.x + 1);
			int destination_value = tiles_index[destination_index];
			if (destination_value == 15) {
				tiles_index[destination_index] = source_value;
				tiles_index[source_index]			 = 15;
				sndObj.playSound(sfxMove);
				return;
			}
		}
	}

}


// ****************************************************************************************************************
// KeyUp handler
// ****************************************************************************************************************
void CGame::kuTheRedeyeOrder(DWORD dwKey) {

	using namespace ns_TheRedeyeOrder;

	// Command button
	if (dwKey == kCommand) {
    miniGameCommandButtonHandler();
	}

	// Handle up movement events
	if (dwKey == kUp) {
		player_dir_north = false;
	}

	// Handle down movement events
	if (dwKey == kDown) {
		player_dir_south = false;
	}

	// Handle left movement events
	if (dwKey == kLeft) {
		player_dir_west	 = false;
	}

	// Handle right movement events
	if (dwKey == kRight) {
		player_dir_east	 = false;
	}

	// Handle keypresses
	if (dwKey == kAction) {
		player_button_down = false;
	}

}


// ****************************************************************************************************************
// Initialize
// ****************************************************************************************************************
void CGame::initializeTheRedeyeOrder() {

	using namespace ns_TheRedeyeOrder;

	resetBoard();
  op_dir = 0;
  op     = 240;

}


// ****************************************************************************************************************
// Loader
// ****************************************************************************************************************
void CGame::loadTheRedeyeOrder(CGapiSurface* backbuffer) {

	using namespace ns_TheRedeyeOrder;

	processEvents = false;

	// Move on to the next step
	loading_step++;

	// Do the appropriate step
	switch(loading_step) {

		case 1: {
			doCommonInit();
      int i = 0;
      for (i = 0; i < 15; i++) { tiles[i] = NULL; }
      sfxMove = NULL;
      sfxWin  = NULL;
		break; }

		case 2: {
			tiles[0]  = new CGapiSurface(); createSurface(TEXT("the_redeye_order : GFX_THE_REDEYE_ORDER_1"),    tiles[0]->CreateSurface (0, m_config.hInstance, GFX_THE_REDEYE_ORDER_1,  TEXT("GRAPHICS"))); tiles[0]->SetColorKey (RGB(255, 128, 255));
			tiles[1]  = new CGapiSurface(); createSurface(TEXT("the_redeye_order : GFX_THE_REDEYE_ORDER_2"),    tiles[1]->CreateSurface (0, m_config.hInstance, GFX_THE_REDEYE_ORDER_2,  TEXT("GRAPHICS"))); tiles[1]->SetColorKey (RGB(255, 128, 255));
			tiles[2]  = new CGapiSurface(); createSurface(TEXT("the_redeye_order : GFX_THE_REDEYE_ORDER_3"),    tiles[2]->CreateSurface (0, m_config.hInstance, GFX_THE_REDEYE_ORDER_3,  TEXT("GRAPHICS"))); tiles[2]->SetColorKey (RGB(255, 128, 255));
			tiles[3]  = new CGapiSurface(); createSurface(TEXT("the_redeye_order : GFX_THE_REDEYE_ORDER_4"),    tiles[3]->CreateSurface (0, m_config.hInstance, GFX_THE_REDEYE_ORDER_4,  TEXT("GRAPHICS"))); tiles[3]->SetColorKey (RGB(255, 128, 255));
			tiles[4]  = new CGapiSurface(); createSurface(TEXT("the_redeye_order : GFX_THE_REDEYE_ORDER_5"),    tiles[4]->CreateSurface (0, m_config.hInstance, GFX_THE_REDEYE_ORDER_5,  TEXT("GRAPHICS"))); tiles[4]->SetColorKey (RGB(255, 128, 255));
			tiles[5]  = new CGapiSurface(); createSurface(TEXT("the_redeye_order : GFX_THE_REDEYE_ORDER_6"),    tiles[5]->CreateSurface (0, m_config.hInstance, GFX_THE_REDEYE_ORDER_6,  TEXT("GRAPHICS"))); tiles[5]->SetColorKey (RGB(255, 128, 255));
			tiles[6]  = new CGapiSurface(); createSurface(TEXT("the_redeye_order : GFX_THE_REDEYE_ORDER_7"),    tiles[6]->CreateSurface (0, m_config.hInstance, GFX_THE_REDEYE_ORDER_7,  TEXT("GRAPHICS"))); tiles[6]->SetColorKey (RGB(255, 128, 255));
			tiles[7]  = new CGapiSurface(); createSurface(TEXT("the_redeye_order : GFX_THE_REDEYE_ORDER_8"),    tiles[7]->CreateSurface (0, m_config.hInstance, GFX_THE_REDEYE_ORDER_8,  TEXT("GRAPHICS"))); tiles[7]->SetColorKey (RGB(255, 128, 255));
			tiles[8]  = new CGapiSurface(); createSurface(TEXT("the_redeye_order : GFX_THE_REDEYE_ORDER_9"),    tiles[8]->CreateSurface (0, m_config.hInstance, GFX_THE_REDEYE_ORDER_9,  TEXT("GRAPHICS"))); tiles[8]->SetColorKey (RGB(255, 128, 255));
			tiles[9]  = new CGapiSurface(); createSurface(TEXT("the_redeye_order : GFX_THE_REDEYE_ORDER_10"),   tiles[9]->CreateSurface (0, m_config.hInstance, GFX_THE_REDEYE_ORDER_10, TEXT("GRAPHICS"))); tiles[9]->SetColorKey (RGB(255, 128, 255));
			tiles[10] = new CGapiSurface(); createSurface(TEXT("the_redeye_order : GFX_THE_REDEYE_ORDER_11"),   tiles[10]->CreateSurface(0, m_config.hInstance, GFX_THE_REDEYE_ORDER_11, TEXT("GRAPHICS"))); tiles[10]->SetColorKey(RGB(255, 128, 255));
			tiles[11] = new CGapiSurface(); createSurface(TEXT("the_redeye_order : GFX_THE_REDEYE_ORDER_12"),   tiles[11]->CreateSurface(0, m_config.hInstance, GFX_THE_REDEYE_ORDER_12, TEXT("GRAPHICS"))); tiles[11]->SetColorKey(RGB(255, 128, 255));
			tiles[12] = new CGapiSurface(); createSurface(TEXT("the_redeye_order : GFX_THE_REDEYE_ORDER_13"),   tiles[12]->CreateSurface(0, m_config.hInstance, GFX_THE_REDEYE_ORDER_13, TEXT("GRAPHICS"))); tiles[12]->SetColorKey(RGB(255, 128, 255));
			tiles[13] = new CGapiSurface(); createSurface(TEXT("the_redeye_order : GFX_THE_REDEYE_ORDER_14"),   tiles[13]->CreateSurface(0, m_config.hInstance, GFX_THE_REDEYE_ORDER_14, TEXT("GRAPHICS"))); tiles[13]->SetColorKey(RGB(255, 128, 255));
			tiles[14] = new CGapiSurface(); createSurface(TEXT("the_redeye_order : GFX_THE_REDEYE_ORDER_15"),   tiles[14]->CreateSurface(0, m_config.hInstance, GFX_THE_REDEYE_ORDER_15, TEXT("GRAPHICS"))); tiles[14]->SetColorKey(RGB(255, 128, 255));
			sfxMove   = new hssSound();     loadSFX      (TEXT("the_redeye_order : SFX_THE_REDEYE_ORDER_MOVE"), sfxMove->load           (m_config.hInstance,   SFX_THE_REDEYE_ORDER_MOVE));                  sfxMove->loop         (false);
      sfxWin    = new hssSound();     loadSFX      (TEXT("the_redeye_order : SFX_THE_REDEYE_ORDER_WIN"),  sfxWin->load            (m_config.hInstance,   SFX_THE_REDEYE_ORDER_WIN));                   sfxWin->loop          (false);
    break; }

    case 3: {
			initializeTheRedeyeOrder();
      for (int i = 0; i < 30; i++) { _tcscpy(mgInstructions[i], instructions[i]); } mgInstructionsPage = 0; mgiPrevTapped = false; mgiNextTapped = false;
    break; }

		// End of loading
		default: {
			loading	= false;
			loading_step = 0;
			processEvents = true;
		break; }

	}

	// Show the Loading screen
	showLoadingScreen(backbuffer, true, true);

}


// ****************************************************************************************************************
// Destroyer
// ****************************************************************************************************************
void CGame::destroyTheRedeyeOrder(CGapiSurface* backbuffer) {

	using namespace ns_TheRedeyeOrder;

	processEvents = false;

	// Move on to the next step
	destroying_step++;

	// Do the appropriate step
	switch(destroying_step) {

		case 1: {
			doCommonCleanup();
		break; }

		case 2: {
			delete tiles[0];
			delete tiles[1];
			delete tiles[2];
			delete tiles[3];
			delete tiles[4];
			delete tiles[5];
			delete tiles[6];
			delete tiles[7];
			delete tiles[8];
			delete tiles[9];
			delete tiles[10];
			delete tiles[11];
			delete tiles[12];
			delete tiles[13];
			delete tiles[14];
			delete sfxMove;
			delete sfxWin;
		break; }

		default: {
			// All done destroying, start loading the next screen
      if (screen_after_destroy == csNewGameType) { // If we just finished playing mini-game melee mode, we need to do some special tricks to get back there... first, re-load the menu stuff, then set our special flag so that loader knows to go to the new game type screen instead
        screen_after_destroy = csMainMenu;
        jumpBackToNewGameType = true;
      }
      current_screen = screen_after_destroy;
			doLoad();
		break; }

	}

	// Show the Loading screen
	showLoadingScreen(backbuffer, true, true);

}


// ****************************************************************************************************************
// Utility functions
// ****************************************************************************************************************
namespace ns_TheRedeyeOrder {


	void resetBoard() {

		int i, j;
		for (i = 0; i < 16; i++) { tiles_index[i] = -1; }
		for (i = 0; i < 16; i++) {
			pick_again:
			j = rand() % 16;
			if (tiles_index[j] != -1) { goto pick_again; }
			tiles_index[j] = i;
		}

	}


} // End of namespace
