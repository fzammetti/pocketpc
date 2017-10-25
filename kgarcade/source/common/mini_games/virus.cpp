
#include "../main.h"


namespace ns_Virus {


// ****************************************************************************************************************
// Function prototypes specific to this mini-game
// ****************************************************************************************************************
void matchFinder(int x, int y, int symbol_type, int new_symbol_type);
void copyGeneratedToTemp();
void copyTempToWorking();
void copyGeneratedToWorking();
void copyWorkingToTemp();
void copyTempToGenerated();


// ****************************************************************************************************************
// Globals specific to this mini-game
// ****************************************************************************************************************
TCHAR	instructions[][32] = { TEXT("Virus"),
														 TEXT(""),
														 TEXT("You are now playing the"),
														 TEXT("part of an antivirus"),
														 TEXT("program.  Really!  You"),
														 TEXT("must eradicate the virus"),
														 TEXT("from the system's"),
														 TEXT("memory banks before"),
														 TEXT("it's too late."),
														 TEXT(""),
                             //    ---------------------------
                             TEXT("The Goal"),
														 TEXT(""),
														 TEXT("There are four types of"),
														 TEXT("virus variants.  You can"),
														 TEXT("clear sections of them by"),
														 TEXT("pressing on groups.  Try"),
														 TEXT("to clear the entire memory"),
														 TEXT("surface at least once"),
														 TEXT("before time runs out."),
														 TEXT(""),
                             //    ---------------------------
                             TEXT("How To Play"),
														 TEXT(""),
														 TEXT("Select any virus bit"),
														 TEXT("twice to remove it and"),
														 TEXT("any like bits adjacent"),
														 TEXT("to them.  The bigger"),
														 TEXT("the virus colony you"),
														 TEXT("clear, the more"),
														 TEXT("points you get."),
														 TEXT(""),
                             //    ----------------------------
};

CGapiSurface*	symbols[8];
hssSound*			sfxSelect                       = NULL;
hssSound*			sfxUnselect                     = NULL;
hssSound*			sfxClear                        = NULL;
hssSound*			sfxLose                         = NULL;
hssSound*			sfxWin                          = NULL;
int						symbol_matrix_generated[13][13];
int						symbol_matrix_working[13][13];
int						symbol_matrix_temp[13][13];
int						box_around_x                    = 0;
int						box_around_y                    = 0;
int						player_dir_delay                = 0;
int						match_count                     = 0;
int           op_dir                          = 0;
int           op                              = 240;


} // End of namespace


// ****************************************************************************************************************
// ProcessNextFrame handler
// ****************************************************************************************************************
void CGame::pnfVirus(CGapiSurface* backbuffer) {

	using namespace ns_Virus;

	// Blit symbols
	int loc_x;
	int loc_y;
	for (int y = 0; y < 11; y++) {
		for (int x = 0; x < 11; x++) {
			if (symbol_matrix_working[y][x] >=0) {
				loc_x = ((x * 16) + (x * 2)) + 2;
				loc_y = ((y * 16) + (y * 2)) + 2;
				backbuffer->BltFast(xadj + loc_x,	yadj + loc_y, symbols[symbol_matrix_working[y][x]], NULL, GDBLTFAST_KEYSRC, NULL);
			}
		}
	}

	// Draw the selection box around the correct tile
	loc_x = ((box_around_x * 16) + (box_around_x * 2)) + 2;
	loc_y = ((box_around_y * 16) + (box_around_y * 2)) + 2;
	RECT rect;
  GDLINEFX gdlinefx;
  gdlinefx.dwOpacity = op;
	SetRect(&rect, xadj + loc_x, yadj + loc_y, xadj + loc_x + 18, yadj + loc_y + 18);
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
			box_around_y--;
			if (box_around_y < 0) { box_around_y = 10; }
		} else {
			player_dir_delay++;
		}
	}
	if (player_dir_south) {
		if (player_dir_delay > 5) {
			player_dir_delay = 0;
			box_around_y++;
			if (box_around_y > 10) { box_around_y = 0; }
		} else {
			player_dir_delay++;
		}
	}
	if (player_dir_west) {
		if (player_dir_delay > 5) {
			player_dir_delay = 0;
			box_around_x--;
			if (box_around_x < 0) { box_around_x = 10; }
		} else {
			player_dir_delay++;
		}
	}
	if (player_dir_east) {
		if (player_dir_delay > 5) {
			player_dir_delay = 0;
			box_around_x++;
			if (box_around_x > 10) { box_around_x = 0; }
		} else {
			player_dir_delay++;
		}
	}

}


// ****************************************************************************************************************
// KeyDown handler
// ****************************************************************************************************************
void CGame::kdVirus(DWORD dwKey) {

	using namespace ns_Virus;

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
	}

}


// ****************************************************************************************************************
// KeyUp handler
// ****************************************************************************************************************
void CGame::kuVirus(DWORD dwKey) {

	using namespace ns_Virus;

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

		match_count = 0;
		int x, y;

		// If the symbol type they tapped on is less than three, then they tapped on an unselected item.
		// In that case, we'll have to see if they tapped on something with at least one other
		// adjacent symbol.  If so, select them all.  If not, unselect everything.
		if (symbol_matrix_working[box_around_y][box_around_x] < 3 && symbol_matrix_working[box_around_y][box_around_x] != -1) {

			// Copy the generated matrix over to our temp matrix
			copyGeneratedToTemp();

			// Call the match finding recursor (is that a word?!?).  Send it the X/Y the selection box
			// is currently around, the current sumbol type, and the target symbol type
			matchFinder(box_around_x, box_around_y, symbol_matrix_temp[box_around_y][box_around_x], symbol_matrix_temp[box_around_y][box_around_x] + 3);

			// If more than one match was found, copy the temp matrix into our working matrix, because
			// they are selecting a region
			if (match_count > 1) {

				copyTempToWorking();
				sndObj.playSound(sfxSelect);

			// If one match is found (0 matches can never occur), we want to essentially unselect
			// all symbols, so to do that we'll just copy over the generated matrix
			} else {

				copyGeneratedToWorking();
				sndObj.playSound(sfxUnselect);

			}

		// If the symbol type was greater 3 or higher, they tapped on a selected symbol.  In this case,
		// We need to destroy all the adjacent symbols.
		} else if (symbol_matrix_working[box_around_y][box_around_x] >= 3) {

			int  x1, y1, x_loc, y_loc;
			bool column_empty;

			// Copy the working matrix over to our temp matrix
			copyWorkingToTemp();

			// We need to call match_finder again, but this time we need it to set the values in the temp
			// matrix to -1 so we know to not draw those symbols again.
      matchFinder(box_around_x, box_around_y, symbol_matrix_temp[box_around_y][box_around_x], -1);
      if (match_count >= 2  && match_count <= 4)  { addToScore(match_count * 2);  }
      if (match_count >= 5  && match_count <= 7)  { addToScore(match_count * 3);  }
      if (match_count >= 8  && match_count <= 10) { addToScore(match_count * 4);  }
      if (match_count >= 11 && match_count <= 13) { addToScore(match_count * 5);  }
      if (match_count >= 14)                      { addToScore(match_count * 10); }

			// Now we have to shift everything down to fill in the gaps
			for (x = 0; x < 11; x++) {
				// y_loc is needed because when we scan the column for empty elements, we can't
				// use y because if we did, we wouldn't shift properly (i.e., the current element being
				// checked, y, would never be shifted into).  We need an asychronous index of the element
				// being checked so that when we shift, we don't increment it automatically.
				y_loc = 10;
				// Scan from the top of the current column to the bottom...
				for (y = 0; y < 11; y++) {
					// When we find an empty element...
					if (symbol_matrix_temp[y_loc][x] == -1) {
						// Loop from that point back to the top...
						for (y1 = y_loc; y1 > 0; y1--) {
							// Shifting everything down
							symbol_matrix_temp[y1][x] = symbol_matrix_temp[y1 - 1][x];
						}
						// And add an empty element at the top
						symbol_matrix_temp[0][x] = -1; // Empty-fill the top
					} else {
						// No empty element found, move on
						y_loc--;
					}
				}
			}

			// Now shift everything to the right of an empty column left
			x_loc = 0; // Needed for the same reason y_loc above is, but horizontally instead of vertically
			// Scen from left to right...
			for (x = 0; x < 11; x++) {
				column_empty = true;
				// Scan the current column.  If there are ANY non-empty elements, we'll be skipping this column...
				for (y = 0; y < 11; y++) {
					if (symbol_matrix_temp[y][x_loc] != -1) {
						column_empty = false;
					}
				}
				// If the column was empty...
				if (column_empty) {
					// Starting at this column, shift everything to the right of it left
					for (x1 = x_loc; x1 < 10; x1++) {
						for (y = 0; y < 11; y++) {
							symbol_matrix_temp[y][x1] = symbol_matrix_temp[y][x1 + 1];
							symbol_matrix_temp[y][10] = -1; // Empty-fill the right
						}
					}
				// Column was NOT empty, so move on
				} else {
					x_loc++;
				}
			}

			// Check to see if there are any valid moves left.  To do this, we scan through the temp
			// array, checking the four adjacent elements to each.  If we get any match_count at all, the
			// game continues, otherwise it ends.
			int num_matches = 0;
			for (y = 0; y < 11; y++) {
				for (x = 0; x < 11; x++) {
					int symbol_type = symbol_matrix_temp[y][x];
					if (symbol_type != -1) {
						if (x < 10) {
							if (symbol_matrix_temp[y][x + 1] == symbol_type) { num_matches++; }
						}
						if (x > 0) {
							if (symbol_matrix_temp[y][x - 1] == symbol_type) { num_matches++; }
						}
						if (y < 10) {
							if (symbol_matrix_temp[y + 1][x] == symbol_type) { num_matches++; }
						}
						if (y > 0) {
							if (symbol_matrix_temp[y - 1][x] == symbol_type) { num_matches++; }
						}
					}
				}
			}

			// If we got no match count, the game must end.  But, we need to see how many
			// symbols are left.  If none, they won.  If one or more, reset.
			if (num_matches == 0) {
				int num_symbols_left = 0;
				for (y = 0; y < 11; y++) {
					for (x = 0; x < 11; x++) {
						if (symbol_matrix_temp[y][x] != -1) { num_symbols_left++; }
					}
				}
				if (num_symbols_left == 0) {
					sndObj.playSound(sfxWin);
					addToScore(2000);
					initializeVirus();
					return;
				} else {
					sndObj.playSound(sfxLose);
					initializeVirus();
					return;
				}
			}

			// Now copy the resultant temp matrix into both the working and generated matrixes
			copyTempToWorking();
			copyTempToGenerated();

			sndObj.playSound(sfxClear);

		}

	} // End if (dwKey == kAction)

}


// ****************************************************************************************************************
// Initialize
// ****************************************************************************************************************
void CGame::initializeVirus() {

	using namespace ns_Virus;

	// Start selection box in upper left-hand corner
	box_around_x = 0;
	box_around_y = 0;

	// Randomly fill spaces
	for (int y = 0; y < 11; y++) {
		for (int x = 0; x < 11; x++) {
			symbol_matrix_generated[y][x] = rand() % 3;
			symbol_matrix_working[y][x]		= symbol_matrix_generated[y][x];
		}
	}

  op_dir           = 0;
  op               = 240;
  player_dir_delay = 0;
  match_count      = 0;

}


// ****************************************************************************************************************
// Loader
// ****************************************************************************************************************
void CGame::loadVirus(CGapiSurface* backbuffer) {

	using namespace ns_Virus;

	processEvents = false;

	// Move on to the next step
	loading_step++;

	// Do the appropriate step
	switch(loading_step) {

		case 1: {
			doCommonInit();
      int i = 0;
      for (i = 0; i < 6; i++) { symbols[i] = NULL; }
      sfxSelect   = NULL;
      sfxUnselect = NULL;
      sfxClear    = NULL;
      sfxLose     = NULL;
      sfxWin      = NULL;
		break; }

		case 2: {
			symbols[0]  = new CGapiSurface(); createSurface(TEXT("virus : GFX_VIRUS_SYMBOL_0"),          symbols[0]->CreateSurface(0, m_config.hInstance, GFX_VIRUS_SYMBOL_0,          TEXT("GRAPHICS"))); symbols[0]->SetColorKey(RGB(255, 128, 255));
			symbols[1]  = new CGapiSurface(); createSurface(TEXT("virus : GFX_VIRUS_SYMBOL_1"),          symbols[1]->CreateSurface(0, m_config.hInstance, GFX_VIRUS_SYMBOL_1,          TEXT("GRAPHICS"))); symbols[1]->SetColorKey(RGB(255, 128, 255));
			symbols[2]  = new CGapiSurface(); createSurface(TEXT("virus : GFX_VIRUS_SYMBOL_2"),          symbols[2]->CreateSurface(0, m_config.hInstance, GFX_VIRUS_SYMBOL_2,          TEXT("GRAPHICS"))); symbols[2]->SetColorKey(RGB(255, 128, 255));
			symbols[3]  = new CGapiSurface(); createSurface(TEXT("virus : GFX_VIRUS_SYMBOL_SELECTED_0"), symbols[3]->CreateSurface(0, m_config.hInstance, GFX_VIRUS_SYMBOL_SELECTED_0, TEXT("GRAPHICS"))); symbols[3]->SetColorKey(RGB(255, 128, 255));
			symbols[4]  = new CGapiSurface(); createSurface(TEXT("virus : GFX_VIRUS_SYMBOL_SELECTED_1"), symbols[4]->CreateSurface(0, m_config.hInstance, GFX_VIRUS_SYMBOL_SELECTED_1, TEXT("GRAPHICS"))); symbols[4]->SetColorKey(RGB(255, 128, 255));
			symbols[5]  = new CGapiSurface(); createSurface(TEXT("virus : GFX_VIRUS_SYMBOL_SELECTED_2"), symbols[5]->CreateSurface(0, m_config.hInstance, GFX_VIRUS_SYMBOL_SELECTED_2, TEXT("GRAPHICS"))); symbols[5]->SetColorKey(RGB(255, 128, 255));
			sfxSelect   = new hssSound();     loadSFX      (TEXT("virus : SFX_MISC_3"),                  sfxSelect->load          (m_config.hInstance,    SFX_MISC_3));                                    sfxSelect->loop        (false);
      sfxUnselect = new hssSound();     loadSFX      (TEXT("virus : SFX_UNFLIP"),                  sfxUnselect->load        (m_config.hInstance,    SFX_UNFLIP));                                    sfxUnselect->loop      (false);
      sfxClear    = new hssSound();     loadSFX      (TEXT("virus : SFX_NO_MATCH"),                sfxClear->load           (m_config.hInstance,    SFX_NO_MATCH));                                  sfxClear->loop         (false);
      sfxLose     = new hssSound();     loadSFX      (TEXT("virus : SFX_MISSED"),                  sfxLose->load            (m_config.hInstance,    SFX_MISSED));                                    sfxLose->loop          (false);
      sfxWin      = new hssSound();     loadSFX      (TEXT("virus : SFX_WIN_1"),                   sfxWin->load             (m_config.hInstance,    SFX_WIN_1));                                     sfxWin->loop           (false);
		break; }

    case 3: {
			initializeVirus();
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
void CGame::destroyVirus(CGapiSurface* backbuffer) {

	using namespace ns_Virus;

	processEvents = false;

	// Move on to the next step
	destroying_step++;

	// Do the appropriate step
	switch(destroying_step) {

		case 1: {
			doCommonCleanup();
		break; }

		case 2: {
			delete sfxSelect;
			delete sfxUnselect;
			delete sfxClear;
			delete sfxLose;
			delete sfxWin;
			delete symbols[0];
			delete symbols[1];
			delete symbols[2];
			delete symbols[3];
			delete symbols[4];
			delete symbols[5];
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
namespace ns_Virus {


	// Does a flood-fill to find all adjacent matching symbols to a starting point
	void matchFinder(int x, int y, int symbol_type, int new_symbol_type) {
		if (symbol_matrix_temp[y][x] == symbol_type) {
			match_count++;
			symbol_matrix_temp[y][x] = new_symbol_type;
			if (x < 10) {
				matchFinder(x + 1, y, symbol_type, new_symbol_type);
			}
			if (x > 0) {
				matchFinder(x - 1, y, symbol_type, new_symbol_type);
			}
			if (y < 10) {
				matchFinder(x, y + 1, symbol_type, new_symbol_type);
			}
			if (y > 0) {
				matchFinder(x, y - 1, symbol_type, new_symbol_type);
			}
		}
	}


	// Copies the generated symbol matrix to the temp matrix
	void copyGeneratedToTemp() {
		using namespace ns_Virus;
		for (int y = 0; y < 11; y++) {
			for (int x = 0; x < 11; x++) {
				symbol_matrix_temp[y][x] = symbol_matrix_generated[y][x];
			}
		}
	}


	// Copies the temp symbol matrix to the working matrix
	void copyTempToWorking() {
		using namespace ns_Virus;
		for (int y = 0; y < 11; y++) {
			for (int x = 0; x < 11; x++) {
				symbol_matrix_working[y][x] = symbol_matrix_temp[y][x];
			}
		}
	}


	// Copies the generated symbol matrix to the working matrix
	void copyGeneratedToWorking() {
		using namespace ns_Virus;
		for (int y = 0; y < 11; y++) {
			for (int x = 0; x < 11; x++) {
				symbol_matrix_working[y][x] = symbol_matrix_generated[y][x];
			}
		}
	}


	// Copies the working symbol matrix to the temp matrix
	void copyWorkingToTemp() {
		using namespace ns_Virus;
		for (int y = 0; y < 11; y++) {
			for (int x = 0; x < 11; x++) {
				symbol_matrix_working[y][x] = symbol_matrix_generated[y][x];
			}
		}
	}


	// Copies the temp symbol matrix to the generated matrix
	void copyTempToGenerated() {
		using namespace ns_Virus;
		for (int y = 0; y < 11; y++) {
			for (int x = 0; x < 11; x++) {
				symbol_matrix_generated[y][x] = symbol_matrix_temp[y][x];
			}
		}
	}


} // End of namespace
