
#include "../main.h"


namespace ns_SonOfEliminator {


// ****************************************************************************************************************
// Defines specific to this mini-game
// ****************************************************************************************************************
#define tBlank  0
#define tEmpty	1
#define tFilled	2
#define tRaised 3


// ****************************************************************************************************************
// Function prototypes specific to this mini-game
// ****************************************************************************************************************
void loadPatterns();
void loadCurrentStates();
void initPattern(int pNum);
bool checkMoreMoves();


// ****************************************************************************************************************
// Globals specific to this mini-game
// ****************************************************************************************************************
TCHAR	instructions[][32] = { TEXT("Son Of Eliminator"),
														 TEXT(""),
														 TEXT("Well, not so much a son"),
														 TEXT("as much a flat-out"),
														 TEXT("CLONE!  Just call it"),
														 TEXT("Bobba Fett and let's"),
														 TEXT("leave it at that."),
														 TEXT(""),
														 TEXT(""),
														 TEXT(""),
                             //    ---------------------------
                             TEXT("The Goal"),
														 TEXT(""),
														 TEXT("Clear as many marbles"),
														 TEXT("as you can, trying to"),
														 TEXT("leave just one.  When no"),
														 TEXT("valid moves remain, the"),
														 TEXT("marbles will reappear for"),
														 TEXT("you to try again.  You"),
														 TEXT("will lose points if more"),
														 TEXT("than one marble remains."),
                             //    ---------------------------
                             TEXT("How To Play"),
														 TEXT(""),
														 TEXT("Select a marble, press"),
														 TEXT("ACTION to raise it.  Then"),
														 TEXT("select an empty hole such"),
														 TEXT("that there is one marble"),
														 TEXT("between it and the raised"),
														 TEXT("marble in any direction."),
														 TEXT("Press ACTION to jump"),
														 TEXT("the marble and clear it."),
                             //    ----------------------------
};

CGapiSurface* tile_empty             = NULL;
CGapiSurface* tile_raised            = NULL;
CGapiSurface* tile_filled            = NULL;
CGapiSurface* tile_empty_current     = NULL;
CGapiSurface* tile_raised_current    = NULL;
CGapiSurface* tile_filled_current    = NULL;
hssSound*			sfxLose                = NULL;
hssSound*			sfxWin                 = NULL;
hssSound*     sfxRaised              = NULL;
hssSound*     sfxDown                = NULL;
hssSound*     sfxRemove              = NULL;
POINT         prev_current;
bool          piece_up               = false;
bool          cheat_possible         = true;
int           Patterns[23][14][14];
int           CurrentStates[14][14];
int           pieces_left            = 0;
int           pattern_index          = 0;
int           cheat_count            = 0;
int           marble_count           = 0;


} // End of namespace


// ****************************************************************************************************************
// ProcessNextFrame handler
// ****************************************************************************************************************
void CGame::pnfSonOfEliminator(CGapiSurface* backbuffer) {

	using namespace ns_SonOfEliminator;

	// Draw the board in it's current state, highlighting the current square
	int x, y;
	for (y = 0; y < 10; y++) {
		for (x = 0; x < 10; x++) {
			switch (CurrentStates[y + 1][x + 1]) {
				case tEmpty:	{
					if (player_pos.x - 1 == x && player_pos.y - 1 == y) {
						backbuffer->BltFast(xadj + (x * 20), yadj + (y * 20), tile_empty_current, NULL, GDBLTFAST_KEYSRC, NULL);
					} else {
						backbuffer->BltFast(xadj + (x * 20), yadj + (y * 20), tile_empty, NULL, GDBLTFAST_KEYSRC, NULL);
					}
				break; }
				case tFilled:	{
					if (player_pos.x - 1 == x && player_pos.y - 1 == y) {
						backbuffer->BltFast(xadj + (x * 20), yadj + (y * 20), tile_filled_current, NULL, GDBLTFAST_KEYSRC, NULL);
					} else {
						backbuffer->BltFast(xadj + (x * 20), yadj + (y * 20), tile_filled, NULL, GDBLTFAST_KEYSRC, NULL);
					}
				break; }
				case tRaised:	{
					if (player_pos.x - 1 == x && player_pos.y - 1 == y) {
						backbuffer->BltFast(xadj + (x * 20), yadj + (y * 20), tile_raised_current, NULL, GDBLTFAST_KEYSRC, NULL);
					} else {
						backbuffer->BltFast(xadj + (x * 20), yadj + (y * 20), tile_raised, NULL, GDBLTFAST_KEYSRC, NULL);
					}
				break; }
			}
		}
	}

}


// ****************************************************************************************************************
// KeyDown handler
// ****************************************************************************************************************
void CGame::kdSonOfEliminator(DWORD dwKey) {

	using namespace ns_SonOfEliminator;

  if (dwKey == kUp)    { player_dir_north = true; }
  if (dwKey == kDown)  { player_dir_south = true; }
  if (dwKey == kLeft)  { player_dir_west  = true;	}
  if (dwKey == kRight) { player_dir_east  = true; }

}


// ****************************************************************************************************************
// KeyUp handler
// ****************************************************************************************************************
void CGame::kuSonOfEliminator(DWORD dwKey) {

	using namespace ns_SonOfEliminator;

	// Command button
	if (dwKey == kCommand) {
    miniGameCommandButtonHandler();
	}

  // ACTION
  if (dwKey == kAction) {

    // If they clicked on a filled hole, lower any previously raised marble and raise the new one
    if (CurrentStates[player_pos.y][player_pos.x] == tFilled) {
      if (prev_current.x != -1 && prev_current.y != -1) {
        CurrentStates[prev_current.y][prev_current.x] = tFilled;
      }
      sndObj.playSound(sfxRaised);
      CurrentStates[player_pos.y][player_pos.x] = tRaised;
      prev_current.y = player_pos.y; prev_current.x = player_pos.x;
      piece_up = true;
      cheat_count++;
      if (game_mode == gmAdventureGame && levelHintDone && cheat_possible && cheat_count == marble_count) {
        addToScore(500);
        force_game_over = true;
      }
      return;
    }

    // If they clicked on a raised marble, lower it
    if (CurrentStates[player_pos.y][player_pos.x] == tRaised) {
      if (prev_current.x != -1 && prev_current.y != -1) {
        CurrentStates[prev_current.y][prev_current.x] = tFilled;
      }
      sndObj.playSound(sfxDown);
      CurrentStates[player_pos.y][player_pos.x] = tFilled;
      prev_current.y = player_pos.y; prev_current.x = player_pos.x;
      piece_up = false;
      cheat_possible = false;
      return;
    }

    // If they clicked an empty tile AND a piece is currently up...
    if (CurrentStates[player_pos.y][player_pos.x] == tEmpty) {
      cheat_possible = false;
      if (piece_up) {
        // Go through each possible move.  Make sure its geometrically a valid move
        // and make sure there is a playable piece in between the source and destination
		    // If it passes both tests, update the status of the middle peg...
        int clicked_x = player_pos.x;
        int clicked_y = player_pos.y;
        int current_x = prev_current.x;
        int current_y = prev_current.y;
        int valid_move = 0;
		    int middle_y, middle_x;
		    if ((clicked_y == (current_y-2)) && (clicked_x == (current_x+0)) && (CurrentStates[current_y-1][current_x+0] == tFilled)) {
			    valid_move = 1; middle_y = current_y - 1; middle_x = current_x + 0;
		    } else if ((clicked_y == (current_y+2)) && (clicked_x == (current_x+0)) && (CurrentStates[current_y+1][current_x+0] == tFilled)) {
			    valid_move = 1; middle_y = current_y + 1; middle_x = current_x + 0;
		    } else if ((clicked_y == (current_y+0)) && (clicked_x == (current_x-2)) && (CurrentStates[current_y+0][current_x-1] == tFilled)) {
			    valid_move = 1; middle_y = current_y + 0; middle_x = current_x - 1;
		    } else if ((clicked_y == (current_y+0)) && (clicked_x == (current_x+2)) && (CurrentStates[current_y+0][current_x+1] == tFilled)) {
			    valid_move = 1; middle_y = current_y + 0; middle_x = current_x + 1;
		    } else if ((clicked_y == (current_y-2)) && (clicked_x == (current_x-2)) && (CurrentStates[current_y-1][current_x-1] == tFilled)) {
			    valid_move = 1; middle_y = current_y - 1; middle_x = current_x - 1;
		    } else if ((clicked_y == (current_y-2)) && (clicked_x == (current_x+2)) && (CurrentStates[current_y-1][current_x+1] == tFilled)) {
			    valid_move = 1; middle_y = current_y - 1; middle_x = current_x + 1;
		    } else if ((clicked_y == (current_y+2)) && (clicked_x == (current_x-2)) && (CurrentStates[current_y+1][current_x-1] == tFilled)) {
			    valid_move = 1; middle_y = current_y + 1; middle_x = current_x - 1;
		    } else if ((clicked_y == (current_y+2)) && (clicked_x == (current_x+2)) && (CurrentStates[current_y+1][current_x+1] == tFilled)) {
			    valid_move = 1; middle_y = current_y + 1; middle_x = current_x + 1;
		    }
		    if (valid_move == 1) {
          sndObj.playSound(sfxRemove);
          addToScore(10);
          // So we don't reset the piece we just cleared...
          prev_current.x = -1;
          prev_current.y = -1;
			    // Make sure we set our flag so we know no pieces are up now
			    piece_up = false;
			    // Change the target hole to filled
			    CurrentStates[clicked_y][clicked_x] = tFilled;
 			    // Change the current piece to empty
			    CurrentStates[current_y][current_x] = tEmpty;
			    // The piece in between, set to empty
			    CurrentStates[middle_y][middle_x] = tEmpty;
          // If there's no valid moves left...
          if (checkMoreMoves()) {
            if (pieces_left == 1) { // One piece left, they won
              sndObj.playSound(sfxWin);
              addToScore(250);
            } else { // More than one piece left, they lost
              sndObj.playSound(sfxLose);
              subtractFromScore(50);
            }
            initPattern(-1);
            player_pos.x = 8;
			      player_pos.y = 5;
          }
		    }
        return;
      }
    }

  }

  // Up
	if (dwKey == kUp && (CurrentStates[player_pos.y - 1][player_pos.x] != tBlank)) {
		if (player_pos.y > 1) { player_pos.y--; } player_dir_north = false;
	}

  // Down
	if (dwKey == kDown && (CurrentStates[player_pos.y + 1][player_pos.x] != tBlank)) {
		if (player_pos.y < 10) { player_pos.y++; } player_dir_south = false;
	}

  // Left
  if (dwKey == kLeft && (CurrentStates[player_pos.y][player_pos.x - 1] != tBlank)) {
		if (player_pos.x > 1) { player_pos.x--; } player_dir_west = false;
	}

  // Right
	if (dwKey == kRight && (CurrentStates[player_pos.y][player_pos.x + 1] != tBlank)) {
		if (player_pos.x < 10) { player_pos.x++; } player_dir_east = false;
	}

}


// ****************************************************************************************************************
// Loader
// ****************************************************************************************************************
void CGame::loadSonOfEliminator(CGapiSurface* backbuffer) {

	using namespace ns_SonOfEliminator;

	processEvents = false;

	// Move on to the next step
	loading_step++;

	// Do the appropriate step
	switch(loading_step) {

		case 1: {
			doCommonInit();
      pieces_left   = 0;
      pattern_index = 0;
      cheat_count   = 0;
      marble_count  = 0;
      tile_empty          = NULL;
      tile_raised         = NULL;
      tile_filled         = NULL;
      tile_empty_current  = NULL;
      tile_raised_current = NULL;
      tile_filled_current = NULL;
      sfxLose             = NULL;
      sfxWin              = NULL;
      sfxRaised           = NULL;
      sfxDown             = NULL;
      sfxRemove           = NULL;
		break; }

		case 2: {
			tile_empty          = new CGapiSurface(); createSurface(TEXT("son_of_eliminator : GFX_SON_OF_ELIMINATOR_EMPTY"),         tile_empty->CreateSurface         (0, m_config.hInstance, GFX_SON_OF_ELIMINATOR_EMPTY,         TEXT("GRAPHICS"))); tile_empty->SetColorKey         (RGB(255, 128, 255));
			tile_raised         = new CGapiSurface(); createSurface(TEXT("son_of_eliminator : GFX_SON_OF_ELIMINATOR_UP"),            tile_raised->CreateSurface        (0, m_config.hInstance, GFX_SON_OF_ELIMINATOR_UP,            TEXT("GRAPHICS"))); tile_raised->SetColorKey        (RGB(255, 128, 255));
			tile_filled         = new CGapiSurface(); createSurface(TEXT("son_of_eliminator : GFX_SON_OF_ELIMINATOR_DOWN"),          tile_filled->CreateSurface        (0, m_config.hInstance, GFX_SON_OF_ELIMINATOR_DOWN,          TEXT("GRAPHICS"))); tile_filled->SetColorKey        (RGB(255, 128, 255));
			tile_empty_current  = new CGapiSurface(); createSurface(TEXT("son_of_eliminator : GFX_SON_OF_ELIMINATOR_EMPTY_CURRENT"), tile_empty_current->CreateSurface (0, m_config.hInstance, GFX_SON_OF_ELIMINATOR_EMPTY_CURRENT, TEXT("GRAPHICS"))); tile_empty_current-> SetColorKey(RGB(255, 128, 255));
			tile_raised_current = new CGapiSurface(); createSurface(TEXT("son_of_eliminator : GFX_SON_OF_ELIMINATOR_UP_CURRENT"),    tile_raised_current->CreateSurface(0, m_config.hInstance, GFX_SON_OF_ELIMINATOR_UP_CURRENT,    TEXT("GRAPHICS"))); tile_raised_current->SetColorKey(RGB(255, 128, 255));
			tile_filled_current = new CGapiSurface(); createSurface(TEXT("son_of_eliminator : GFX_SON_OF_ELIMINATOR_DOWN_CURRENT"),  tile_filled_current->CreateSurface(0, m_config.hInstance, GFX_SON_OF_ELIMINATOR_DOWN_CURRENT,  TEXT("GRAPHICS"))); tile_filled_current->SetColorKey(RGB(255, 128, 255));
			sfxLose             = new hssSound();     loadSFX      (TEXT("son_of_eliminator : SFX_MISSED"),                          sfxLose->load                     (m_config.hInstance,    SFX_MISSED));                                            sfxLose->loop                   (false);
      sfxWin              = new hssSound();     loadSFX      (TEXT("son_of_eliminator : SFX_WIN_1"),                           sfxWin->load                      (m_config.hInstance,    SFX_WIN_1));                                             sfxWin->loop                    (false);
      sfxRaised           = new hssSound();     loadSFX      (TEXT("son_of_eliminator : SFX_SON_OF_ELIMINATOR_UP"),            sfxRaised->load                   (m_config.hInstance,    SFX_SON_OF_ELIMINATOR_UP));                              sfxRaised->loop                 (false);
      sfxDown             = new hssSound();     loadSFX      (TEXT("son_of_eliminator : SFX_SON_OF_ELIMINATOR_DOWN"),          sfxDown->load                     (m_config.hInstance,    SFX_SON_OF_ELIMINATOR_DOWN));                            sfxDown->loop                   (false);
      sfxRemove           = new hssSound();     loadSFX      (TEXT("son_of_eliminator : SFX_SON_OF_ELIMINATOR_REMOVE"),        sfxRemove->load                   (m_config.hInstance,    SFX_SON_OF_ELIMINATOR_REMOVE));                          sfxRemove->loop                 (false);
    break; }

		case 3: {
      for (int i = 0; i < 30; i++) { _tcscpy(mgInstructions[i], instructions[i]); } mgInstructionsPage = 0; mgiPrevTapped = false; mgiNextTapped = false;
			loadPatterns();
			initPattern(-1);
			player_pos.x = 8;
			player_pos.y = 5;
      piece_up = false;
      prev_current.x = -1;
      prev_current.y = -1;
      cheat_possible = true;
      cheat_count = 0;
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
void CGame::destroySonOfEliminator(CGapiSurface* backbuffer) {

	using namespace ns_SonOfEliminator;

	processEvents = false;

	// Move on to the next step
	destroying_step++;

	// Do the appropriate step
	switch(destroying_step) {

		case 1: {
			doCommonCleanup();
		break; }

		case 2: {
			delete tile_empty;
			delete tile_raised;
			delete tile_filled;
			delete tile_empty_current;
			delete tile_raised_current;
			delete tile_filled_current;
		break; }

    case 3: {
      delete sfxLose;
			delete sfxWin;
			delete sfxRaised;
			delete sfxDown;
			delete sfxRemove;
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
namespace ns_SonOfEliminator {

  // Initialze a pattern
	void initPattern(int pNum) {

    cheat_possible = true;
    cheat_count = 0;
    marble_count = 0;
    // If we are passed -1, we pick a pattern, otherwise we initialize what we were passed
    if (pNum == -1) {
      pickPattern:
		  pattern_index = rand() % 3;
		  if (pattern_index < 0 || pattern_index > 3) { goto pickPattern; }
    } else {
      pattern_index = pNum;
    }
		// Load the pattern into the CurrentStates array
		for (int y = 1; y < 11; y++) {
			for (int x = 1; x < 11; x++) {
				CurrentStates[y][x] = Patterns[pattern_index][y][x];
        if (Patterns[pattern_index][y][x] == 2) { marble_count++; }
			}
		}

	}


  // This routine checks to see if there are any moves remaining after the last move made
  bool checkMoreMoves() {

	  pieces_left = 0;
    int moves_left = 0;
    for (int y = 1; y < 11; y++) {
      for (int x = 1; x < 11; x++) {
        if (CurrentStates[y][x] == tFilled) {
          pieces_left++;
          if (
              (CurrentStates[y+1][x+0] == tFilled &&
               CurrentStates[y-1][x-0] == tEmpty) ||
              (CurrentStates[y-1][x+0] == tFilled &&
               CurrentStates[y+1][x-0] == tEmpty) ||
              (CurrentStates[y+0][x+1] == tFilled &&
               CurrentStates[y-0][x-1] == tEmpty) ||
              (CurrentStates[y+0][x-1] == tFilled &&
               CurrentStates[y-0][x+1] == tEmpty) ||
              (CurrentStates[y+1][x-1] == tFilled &&
               CurrentStates[y-1][x+1] == tEmpty) ||
              (CurrentStates[y-1][x+1] == tFilled &&
               CurrentStates[y+1][x-1] == tEmpty) ||
              (CurrentStates[y+1][x+1] == tFilled &&
               CurrentStates[y-1][x-1] == tEmpty) ||
              (CurrentStates[y-1][x-1] == tFilled &&
               CurrentStates[y+1][x+1] == tEmpty)
             ) {
            moves_left = 1;
          }
        }
      }
    }
    // BOARD CLEARED!!
    if (moves_left == 0) {
      return true;
    } else {
      return false;
    }

  }


  // Load the patterns data
	void loadPatterns() {

		// Big Cross
		Patterns[0][1][1]   = 0; Patterns[0][1][2]  = 0; Patterns[0][1][3]  = 0; Patterns[0][1][4]  = 2; Patterns[0][1][5]  = 2;
		Patterns[0][1][6]   = 2; Patterns[0][1][7]  = 2; Patterns[0][1][8]  = 0; Patterns[0][1][9]  = 0; Patterns[0][1][10]  = 0;
		Patterns[0][2][1]   = 0; Patterns[0][2][2]  = 0; Patterns[0][2][3]  = 0; Patterns[0][2][4]  = 2; Patterns[0][2][5]   = 2;
		Patterns[0][2][6]   = 2; Patterns[0][2][7]  = 2; Patterns[0][2][8]  = 0; Patterns[0][2][9]  = 0; Patterns[0][2][10]  = 0;
		Patterns[0][3][1]   = 0; Patterns[0][3][2]  = 0; Patterns[0][3][3]  = 0; Patterns[0][3][4]  = 2; Patterns[0][3][5]   = 2;
		Patterns[0][3][6]   = 2; Patterns[0][3][7]  = 2; Patterns[0][3][8]  = 0; Patterns[0][3][9]  = 0; Patterns[0][3][10]  = 0;
		Patterns[0][4][1]   = 2; Patterns[0][4][2]  = 2; Patterns[0][4][3]  = 2; Patterns[0][4][4]  = 2; Patterns[0][4][5]   = 2;
		Patterns[0][4][6]   = 2; Patterns[0][4][7]  = 2; Patterns[0][4][8]  = 2; Patterns[0][4][9]  = 2; Patterns[0][4][10]  = 2;
		Patterns[0][5][1]   = 2; Patterns[0][5][2]  = 2; Patterns[0][5][3]  = 2; Patterns[0][5][4]  = 2; Patterns[0][5][5]   = 2;
		Patterns[0][5][6]   = 1; Patterns[0][5][7]  = 2; Patterns[0][5][8]  = 2; Patterns[0][5][9]  = 2; Patterns[0][5][10]  = 2;
		Patterns[0][6][1]   = 2; Patterns[0][6][2]  = 2; Patterns[0][6][3]  = 2; Patterns[0][6][4]  = 2; Patterns[0][6][5]   = 2;
		Patterns[0][6][6]   = 2; Patterns[0][6][7]  = 2; Patterns[0][6][8]  = 2; Patterns[0][6][9]  = 2; Patterns[0][6][10]  = 2;
		Patterns[0][7][1]   = 2; Patterns[0][7][2]  = 2; Patterns[0][7][3]  = 2; Patterns[0][7][4]  = 2; Patterns[0][7][5]   = 2;
		Patterns[0][7][6]   = 2; Patterns[0][7][7]  = 2; Patterns[0][7][8]  = 2; Patterns[0][7][9]  = 2; Patterns[0][7][10]  = 2;
		Patterns[0][8][1]   = 0; Patterns[0][8][2]  = 0; Patterns[0][8][3]  = 0; Patterns[0][8][4]  = 2; Patterns[0][8][5]   = 2;
		Patterns[0][8][6]   = 2; Patterns[0][8][7]  = 2; Patterns[0][8][8]  = 0; Patterns[0][8][9]  = 0; Patterns[0][8][10]  = 0;
		Patterns[0][9][1]   = 0; Patterns[0][9][2]  = 0; Patterns[0][9][3]  = 0; Patterns[0][9][4]  = 2; Patterns[0][9][5]   = 2;
		Patterns[0][9][6]   = 2; Patterns[0][9][7]  = 2; Patterns[0][9][8]  = 0; Patterns[0][9][9]  = 0; Patterns[0][9][10]  = 0;
		Patterns[0][10][1]  = 0; Patterns[0][10][2] = 0; Patterns[0][10][3] = 0; Patterns[0][10][4] = 2; Patterns[0][10][5]  = 2;
		Patterns[0][10][6]  = 2; Patterns[0][10][7] = 2; Patterns[0][10][8] = 0; Patterns[0][10][9] = 0; Patterns[0][10][10] = 0;

		// Diamond
		Patterns[1][1][1]   = 0; Patterns[1][1][2]  = 0; Patterns[1][1][3]  = 0; Patterns[1][1][4]  = 0; Patterns[1][1][5]   = 0;
		Patterns[1][1][6]   = 0; Patterns[1][1][7]  = 0; Patterns[1][1][8]  = 0; Patterns[1][1][9]  = 0; Patterns[1][1][10]  = 0;
		Patterns[1][2][1]   = 0; Patterns[1][2][2]  = 0; Patterns[1][2][3]  = 0; Patterns[1][2][4]  = 0; Patterns[1][2][5]   = 2;
		Patterns[1][2][6]   = 2; Patterns[1][2][7]  = 0; Patterns[1][2][8]  = 0; Patterns[1][2][9]  = 0; Patterns[1][2][10]  = 0;
		Patterns[1][3][1]   = 0; Patterns[1][3][2]  = 0; Patterns[1][3][3]  = 0; Patterns[1][3][4]  = 2; Patterns[1][3][5]   = 2;
		Patterns[1][3][6]   = 2; Patterns[1][3][7]  = 2; Patterns[1][3][8]  = 0; Patterns[1][3][9]  = 0; Patterns[1][3][10]  = 0;
		Patterns[1][4][1]   = 0; Patterns[1][4][2]  = 0; Patterns[1][4][3]  = 2; Patterns[1][4][4]  = 2; Patterns[1][4][5]   = 2;
		Patterns[1][4][6]   = 2; Patterns[1][4][7]  = 2; Patterns[1][4][8]  = 2; Patterns[1][4][9]  = 0; Patterns[1][4][10]  = 0;
		Patterns[1][5][1]   = 0; Patterns[1][5][2]  = 2; Patterns[1][5][3]  = 2; Patterns[1][5][4]  = 2; Patterns[1][5][5]   = 2;
		Patterns[1][5][6]   = 1; Patterns[1][5][7]  = 2; Patterns[1][5][8]  = 2; Patterns[1][5][9]  = 2; Patterns[1][5][10]  = 0;
		Patterns[1][6][1]   = 0; Patterns[1][6][2]  = 2; Patterns[1][6][3]  = 2; Patterns[1][6][4]  = 2; Patterns[1][6][5]   = 2;
		Patterns[1][6][6]   = 2; Patterns[1][6][7]  = 2; Patterns[1][6][8]  = 2; Patterns[1][6][9]  = 2; Patterns[1][6][10]  = 0;
		Patterns[1][7][1]   = 0; Patterns[1][7][2]  = 0; Patterns[1][7][3]  = 2; Patterns[1][7][4]  = 2; Patterns[1][7][5]   = 2;
		Patterns[1][7][6]   = 2; Patterns[1][7][7]  = 2; Patterns[1][7][8]  = 2; Patterns[1][7][9]  = 0; Patterns[1][7][10]  = 0;
		Patterns[1][8][1]   = 0; Patterns[1][8][2]  = 0; Patterns[1][8][3]  = 0; Patterns[1][8][4]  = 2; Patterns[1][8][5]   = 2;
		Patterns[1][8][6]   = 2; Patterns[1][8][7]  = 2; Patterns[1][8][8]  = 0; Patterns[1][8][9]  = 0; Patterns[1][8][10]  = 0;
		Patterns[1][9][1]   = 0; Patterns[1][9][2]  = 0; Patterns[1][9][3]  = 0; Patterns[1][9][4]  = 0; Patterns[1][9][5]   = 2;
		Patterns[1][9][6]   = 2; Patterns[1][9][7]  = 0; Patterns[1][9][8]  = 0; Patterns[1][9][9]  = 0; Patterns[1][9][10]  = 0;
		Patterns[1][10][1]  = 0; Patterns[1][10][2] = 0; Patterns[1][10][3] = 0; Patterns[1][10][4] = 0; Patterns[1][10][5]  = 0;
		Patterns[1][10][6]  = 0; Patterns[1][10][7] = 0; Patterns[1][10][8] = 0; Patterns[1][10][9] = 0; Patterns[1][10][10] = 0;

		// Horseshoe
		Patterns[2][1][1]   = 2; Patterns[2][1][2]  = 2; Patterns[2][1][3]  = 2; Patterns[2][1][4]  = 0; Patterns[2][1][5]   = 0;
		Patterns[2][1][6]   = 0; Patterns[2][1][7]  = 0; Patterns[2][1][8]  = 2; Patterns[2][1][9]  = 2; Patterns[2][1][10]  = 2;
		Patterns[2][2][1]   = 2; Patterns[2][2][2]  = 2; Patterns[2][2][3]  = 2; Patterns[2][2][4]  = 0; Patterns[2][2][5]   = 0;
		Patterns[2][2][6]   = 0; Patterns[2][2][7]  = 0; Patterns[2][2][8]  = 2; Patterns[2][2][9]  = 2; Patterns[2][2][10]  = 2;
		Patterns[2][3][1]   = 2; Patterns[2][3][2]  = 2; Patterns[2][3][3]  = 2; Patterns[2][3][4]  = 0; Patterns[2][3][5]   = 0;
		Patterns[2][3][6]   = 0; Patterns[2][3][7]  = 0; Patterns[2][3][8]  = 2; Patterns[2][3][9]  = 2; Patterns[2][3][10]  = 2;
		Patterns[2][4][1]   = 2; Patterns[2][4][2]  = 2; Patterns[2][4][3]  = 2; Patterns[2][4][4]  = 0; Patterns[2][4][5]   = 0;
		Patterns[2][4][6]   = 0; Patterns[2][4][7]  = 0; Patterns[2][4][8]  = 2; Patterns[2][4][9]  = 2; Patterns[2][4][10]  = 2;
		Patterns[2][5][1]   = 2; Patterns[2][5][2]  = 2; Patterns[2][5][3]  = 2; Patterns[2][5][4]  = 0; Patterns[2][5][5]   = 0;
		Patterns[2][5][6]   = 0; Patterns[2][5][7]  = 0; Patterns[2][5][8]  = 2; Patterns[2][5][9]  = 2; Patterns[2][5][10]  = 2;
		Patterns[2][6][1]   = 2; Patterns[2][6][2]  = 2; Patterns[2][6][3]  = 2; Patterns[2][6][4]  = 0; Patterns[2][6][5]   = 0;
		Patterns[2][6][6]   = 0; Patterns[2][6][7]  = 0; Patterns[2][6][8]  = 2; Patterns[2][6][9]  = 2; Patterns[2][6][10]  = 2;
		Patterns[2][7][1]   = 2; Patterns[2][7][2]  = 2; Patterns[2][7][3]  = 2; Patterns[2][7][4]  = 0; Patterns[2][7][5]   = 0;
		Patterns[2][7][6]   = 0; Patterns[2][7][7]  = 0; Patterns[2][7][8]  = 2; Patterns[2][7][9]  = 2; Patterns[2][7][10]  = 2;
		Patterns[2][8][1]   = 2; Patterns[2][8][2]  = 2; Patterns[2][8][3]  = 2; Patterns[2][8][4]  = 2; Patterns[2][8][5]   = 2;
		Patterns[2][8][6]   = 2; Patterns[2][8][7]  = 2; Patterns[2][8][8]  = 2; Patterns[2][8][9]  = 2; Patterns[2][8][10]  = 2;
		Patterns[2][9][1]   = 1; Patterns[2][9][2]  = 2; Patterns[2][9][3]  = 2; Patterns[2][9][4]  = 2; Patterns[2][9][5]   = 2;
		Patterns[2][9][6]   = 2; Patterns[2][9][7]  = 2; Patterns[2][9][8]  = 2; Patterns[2][9][9]  = 2; Patterns[2][9][10]  = 1;
		Patterns[2][10][1]  = 1; Patterns[2][10][2] = 1; Patterns[2][10][3] = 2; Patterns[2][10][4] = 2; Patterns[2][10][5]  = 2;
		Patterns[2][10][6]  = 2; Patterns[2][10][7] = 2; Patterns[2][10][8] = 2; Patterns[2][10][9] = 1; Patterns[2][10][10] = 1;

		// Strange Invaders
		Patterns[3][1][1]   = 2; Patterns[3][1][2]  = 0; Patterns[3][1][3]  = 0; Patterns[3][1][4]  = 0; Patterns[3][1][5]   = 0;
		Patterns[3][1][6]   = 0; Patterns[3][1][7]  = 0; Patterns[3][1][8]  = 0; Patterns[3][1][9]  = 0; Patterns[3][1][10]  = 2;
		Patterns[3][2][1]   = 2; Patterns[3][2][2]  = 2; Patterns[3][2][3]  = 0; Patterns[3][2][4]  = 0; Patterns[3][2][5]   = 0;
		Patterns[3][2][6]   = 0; Patterns[3][2][7]  = 0; Patterns[3][2][8]  = 0; Patterns[3][2][9]  = 2; Patterns[3][2][10]  = 2;
		Patterns[3][3][1]   = 2; Patterns[3][3][2]  = 2; Patterns[3][3][3]  = 2; Patterns[3][3][4]  = 2; Patterns[3][3][5]   = 2;
		Patterns[3][3][6]   = 2; Patterns[3][3][7]  = 2; Patterns[3][3][8]  = 2; Patterns[3][3][9]  = 2; Patterns[3][3][10]  = 2;
		Patterns[3][4][1]   = 0; Patterns[3][4][2]  = 2; Patterns[3][4][3]  = 0; Patterns[3][4][4]  = 2; Patterns[3][4][5]   = 0;
		Patterns[3][4][6]   = 0; Patterns[3][4][7]  = 2; Patterns[3][4][8]  = 0; Patterns[3][4][9]  = 2; Patterns[3][4][10]  = 0;
		Patterns[3][5][1]   = 0; Patterns[3][5][2]  = 2; Patterns[3][5][3]  = 0; Patterns[3][5][4]  = 2; Patterns[3][5][5]   = 1;
		Patterns[3][5][6]   = 1; Patterns[3][5][7]  = 2; Patterns[3][5][8]  = 0; Patterns[3][5][9]  = 2; Patterns[3][5][10]  = 0;
		Patterns[3][6][1]   = 0; Patterns[3][6][2]  = 2; Patterns[3][6][3]  = 0; Patterns[3][6][4]  = 0; Patterns[3][6][5]   = 2;
		Patterns[3][6][6]   = 2; Patterns[3][6][7]  = 0; Patterns[3][6][8]  = 0; Patterns[3][6][9]  = 2; Patterns[3][6][10]  = 0;
		Patterns[3][7][1]   = 0; Patterns[3][7][2]  = 2; Patterns[3][7][3]  = 0; Patterns[3][7][4]  = 1; Patterns[3][7][5]   = 1;
		Patterns[3][7][6]   = 1; Patterns[3][7][7]  = 1; Patterns[3][7][8]  = 0; Patterns[3][7][9]  = 2; Patterns[3][7][10]  = 0;
		Patterns[3][8][1]   = 0; Patterns[3][8][2]  = 0; Patterns[3][8][3]  = 2; Patterns[3][8][4]  = 0; Patterns[3][8][5]   = 0;
		Patterns[3][8][6]   = 0; Patterns[3][8][7]  = 0; Patterns[3][8][8]  = 2; Patterns[3][8][9]  = 0; Patterns[3][8][10]  = 0;
		Patterns[3][9][1]   = 0; Patterns[3][9][2]  = 0; Patterns[3][9][3]  = 0; Patterns[3][9][4]  = 2; Patterns[3][9][5]   = 2;
		Patterns[3][9][6]   = 2; Patterns[3][9][7]  = 2; Patterns[3][9][8]  = 0; Patterns[3][9][9]  = 0; Patterns[3][9][10]  = 0;
		Patterns[3][10][1]  = 0; Patterns[3][10][2] = 0; Patterns[3][10][3] = 0; Patterns[3][10][4] = 0; Patterns[3][10][5]  = 0;
		Patterns[3][10][6]  = 0; Patterns[3][10][7] = 0; Patterns[3][10][8] = 0; Patterns[3][10][9] = 0; Patterns[3][10][10] = 0;

	}


} // End of namespace
