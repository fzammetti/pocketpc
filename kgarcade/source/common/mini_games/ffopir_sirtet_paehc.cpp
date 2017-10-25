
#include "../main.h"


namespace ns_FfopirSirtetPaehc {


// ****************************************************************************************************************
// Defines specific to this mini-game
// ****************************************************************************************************************
#define ROTATION_0   1
#define ROTATION_90  2
#define ROTATION_180 3
#define ROTATION_270 4


// ****************************************************************************************************************
// Function prototypes specific to this mini-game
// ****************************************************************************************************************
POINT newShape();
void  getShapePoints(int shape_number, int rotation);
int   clearRows();


// ****************************************************************************************************************
// Globals specific to this mini-game
// ****************************************************************************************************************
TCHAR	instructions[][32] = { TEXT("Ffopir Sirtet Paehc"),
														 TEXT(""),
														 TEXT("If Geometry wasn't your"),
														 TEXT("thing in school, your"),
														 TEXT("not going to like this!"),
														 TEXT("Actually, it doesn't"),
														 TEXT("matter in the least."),
														 TEXT("Decode the title and"),
														 TEXT("there's not really"),
														 TEXT("any more to say."),
                             //    ---------------------------
                             TEXT("The Goal"),
														 TEXT(""),
														 TEXT("Form complete lines"),
														 TEXT("across the screen"),
														 TEXT("to keep clearing away"),
														 TEXT("pieces.  Don't go"),
														 TEXT("past the top!"),
														 TEXT(""),
														 TEXT(""),
														 TEXT(""),
                             //    ---------------------------
                             TEXT("How To Play"),
														 TEXT(""),
														 TEXT("Move the falling piece"),
														 TEXT("left or right and press"),
														 TEXT("the ACTION button to"),
														 TEXT("rotate it.  Press down"),
														 TEXT("to drop it faster."),
														 TEXT(""),
														 TEXT(""),
														 TEXT(""),
                             //    ----------------------------
};

CGapiSurface*	block               = NULL;
CGapiSurface*	background          = NULL;
hssSound*			sfxMove             = NULL;
hssSound*			sfxRotating         = NULL;
hssSound*			sfxLandedClear      = NULL;
POINT					shape_points[6];
bool					quick_down          = false;
int						shape_rotation      = 0;
int						current_shape       = 0;
int						player_speed        = 0;
int						player_speed_delay  = 0;
int						lateral_move_delay  = 0;
int						matrix[22][13];
int						matrix_temp[22][13];


} // End of namespace


// ****************************************************************************************************************
// ProcessNextFrame handler
// ****************************************************************************************************************
void CGame::pnfFfopirSirtetPaehc(CGapiSurface* backbuffer) {

	using namespace ns_FfopirSirtetPaehc;

	// Background
	backbuffer->BltFast(xadj, yadj, background, NULL, NULL, NULL);

	// Blit matrix
	for (int y = 0; y < 20; y++) {
		for (int x = 0; x < 11; x++) {
			if (matrix[y][x] == 1) {
				backbuffer->BltFast(xadj + 45 + (x * 10), yadj + (y * 10), block, NULL, GDBLTFAST_KEYSRC, NULL);
			}
		}
	}

	// Blit current shape
	getShapePoints(current_shape, shape_rotation);
	backbuffer->BltFast(xadj + 45 + ((player_pos.x + shape_points[0].x) * 10), yadj + ((player_pos.y + shape_points[0].y) * 10), block, NULL, GDBLTFAST_KEYSRC, NULL);
	backbuffer->BltFast(xadj + 45 + ((player_pos.x + shape_points[1].x) * 10), yadj + ((player_pos.y + shape_points[1].y) * 10), block, NULL, GDBLTFAST_KEYSRC, NULL);
	backbuffer->BltFast(xadj + 45 + ((player_pos.x + shape_points[2].x) * 10), yadj + ((player_pos.y + shape_points[2].y) * 10), block, NULL, GDBLTFAST_KEYSRC, NULL);
	backbuffer->BltFast(xadj + 45 + ((player_pos.x + shape_points[3].x) * 10), yadj + ((player_pos.y + shape_points[3].y) * 10), block, NULL, GDBLTFAST_KEYSRC, NULL);

	// If shape hits bottom, work it into the matrix and start a new one
	if (player_pos.y + shape_points[0].y == 19 ||
			player_pos.y + shape_points[1].y == 19 ||
			player_pos.y + shape_points[2].y == 19 ||
			player_pos.y + shape_points[3].y == 19) {
				matrix[player_pos.y + shape_points[0].y][player_pos.x + shape_points[0].x] = 1;
				matrix[player_pos.y + shape_points[1].y][player_pos.x + shape_points[1].x] = 1;
				matrix[player_pos.y + shape_points[2].y][player_pos.x + shape_points[2].x] = 1;
				matrix[player_pos.y + shape_points[3].y][player_pos.x + shape_points[3].x] = 1;
				int num_cleared = clearRows();
				if (num_cleared != 0) { addToScore(25 * num_cleared); sndObj.playSound(sfxLandedClear); }
				player_pos = newShape();
	}

	// If shape hits top of another shape, work it into the matrix and start a new one
	if (matrix[player_pos.y + 1 + shape_points[0].y][player_pos.x + shape_points[0].x] == 1 ||
			matrix[player_pos.y + 1 + shape_points[1].y][player_pos.x + shape_points[1].x] == 1 ||
			matrix[player_pos.y + 1 + shape_points[2].y][player_pos.x + shape_points[2].x] == 1 ||
			matrix[player_pos.y + 1 + shape_points[3].y][player_pos.x + shape_points[3].x] == 1) {
        // If the position of the piece is <=0, it means we're above the top, so abort the game
        if (player_pos.y <= 0) {
          subtractFromScore(250);
          force_game_over = true;
          return;
        }
				matrix[player_pos.y + shape_points[0].y][player_pos.x + shape_points[0].x] = 1;
				matrix[player_pos.y + shape_points[1].y][player_pos.x + shape_points[1].x] = 1;
				matrix[player_pos.y + shape_points[2].y][player_pos.x + shape_points[2].x] = 1;
				matrix[player_pos.y + shape_points[3].y][player_pos.x + shape_points[3].x] = 1;
				int num_cleared = clearRows();
				if (num_cleared != 0) { addToScore(25 * num_cleared); sndObj.playSound(sfxLandedClear); }
				player_pos = newShape();
	}

	// Move current shape down
	player_speed_delay++;
	if (player_speed_delay > player_speed || quick_down == true) {
		player_speed_delay = 0;
		player_pos.y++;
    sndObj.playSound(sfxMove);
	}

	// Handle left movement events
	if (player_dir_west) {
		lateral_move_delay++;
		if (lateral_move_delay > 5) {
      sndObj.playSound(sfxMove);
			lateral_move_delay = 0;
			if (player_pos.x > 0) {
				// Make sure the target area is clear of blocks
				if (matrix[player_pos.y + shape_points[0].y][player_pos.x - 1 + shape_points[0].x] == 0 &&
						matrix[player_pos.y + shape_points[1].y][player_pos.x - 1 + shape_points[1].x] == 0 &&
						matrix[player_pos.y + shape_points[2].y][player_pos.x - 1 + shape_points[2].x] == 0 &&
						matrix[player_pos.y + shape_points[3].y][player_pos.x - 1 + shape_points[3].x] == 0) {
							player_pos.x--;
				}
			}
		}
	}

	// Handle right movement events
	if (player_dir_east) {
		lateral_move_delay++;
		if (lateral_move_delay > 5) {
      sndObj.playSound(sfxMove);
			lateral_move_delay = 0;
			if (player_pos.x + shape_points[0].x < 10 &&
					player_pos.x + shape_points[1].x < 10 &&
					player_pos.x + shape_points[2].x < 10 &&
					player_pos.x + shape_points[3].x < 10) {
						// Make sure the target area is clear of blocks
						if (matrix[player_pos.y + shape_points[0].y][player_pos.x + 1 + shape_points[0].x] == 0 &&
								matrix[player_pos.y + shape_points[1].y][player_pos.x + 1 + shape_points[1].x] == 0 &&
								matrix[player_pos.y + shape_points[2].y][player_pos.x + 1 + shape_points[2].x] == 0 &&
								matrix[player_pos.y + shape_points[3].y][player_pos.x + 1 + shape_points[3].x] == 0) {
									player_pos.x++;
						}
			}
		}
	}

}


// ****************************************************************************************************************
// KeyDown handler
// ****************************************************************************************************************
void CGame::kdFfopirSirtetPaehc(DWORD dwKey) {

	using namespace ns_FfopirSirtetPaehc;

	// Handle left movement events
	if (dwKey == kLeft) {
		player_dir_west		 = true;
		lateral_move_delay = 5;
	}

	// Handle right movement events
	if (dwKey == kRight) {
		player_dir_east		 = true;
		lateral_move_delay = 5;
	}

	// Handle down movement events
	if (dwKey == kDown) {
		player_dir_south = true;
		quick_down			 = true;
	}

	// Handle keypresses
	if (dwKey == kAction) {
		player_button_down = true;
		switch (shape_rotation) {
			// See if the shape will be out of bounds or will collide with existing blocks if we rotate.  If not, do it.
			case ROTATION_0:	 {
				getShapePoints(current_shape, ROTATION_90);
				// Check right boundary
				if (player_pos.x + shape_points[0].x < 11 &&
						player_pos.x + shape_points[1].x < 11 &&
						player_pos.x + shape_points[2].x < 11 &&
						player_pos.x + shape_points[3].x < 11) {
							// Make sure the target area is clear of blocks
							if (matrix[player_pos.y + shape_points[0].y][player_pos.x + shape_points[0].x] == 0 &&
									matrix[player_pos.y + shape_points[1].y][player_pos.x + shape_points[1].x] == 0 &&
									matrix[player_pos.y + shape_points[2].y][player_pos.x + shape_points[2].x] == 0 &&
									matrix[player_pos.y + shape_points[3].y][player_pos.x + shape_points[3].x] == 0) {
										sndObj.playSound(sfxRotating);
										shape_rotation = ROTATION_90;
							}
				}
			break; }
			case ROTATION_90:  {
				getShapePoints(current_shape, ROTATION_180);
				// Check right boundary
				if (player_pos.x + shape_points[0].x < 11 &&
						player_pos.x + shape_points[1].x < 11 &&
						player_pos.x + shape_points[2].x < 11 &&
						player_pos.x + shape_points[3].x < 11) {
							// Make sure the target area is clear of blocks
							if (matrix[player_pos.y + shape_points[0].y][player_pos.x + shape_points[0].x] == 0 &&
									matrix[player_pos.y + shape_points[1].y][player_pos.x + shape_points[1].x] == 0 &&
									matrix[player_pos.y + shape_points[2].y][player_pos.x + shape_points[2].x] == 0 &&
									matrix[player_pos.y + shape_points[3].y][player_pos.x + shape_points[3].x] == 0) {
										sndObj.playSound(sfxRotating);
										shape_rotation = ROTATION_180;
							}
				}
			break; }
			case ROTATION_180: {
				getShapePoints(current_shape, ROTATION_270);
				// Check right boundary
				if (player_pos.x + shape_points[0].x < 11 &&
						player_pos.x + shape_points[1].x < 11 &&
						player_pos.x + shape_points[2].x < 11 &&
						player_pos.x + shape_points[3].x < 11) {
							// Make sure the target area is clear of blocks
							if (matrix[player_pos.y + shape_points[0].y][player_pos.x + shape_points[0].x] == 0 &&
									matrix[player_pos.y + shape_points[1].y][player_pos.x + shape_points[1].x] == 0 &&
									matrix[player_pos.y + shape_points[2].y][player_pos.x + shape_points[2].x] == 0 &&
									matrix[player_pos.y + shape_points[3].y][player_pos.x + shape_points[3].x] == 0) {
										sndObj.playSound(sfxRotating);
										shape_rotation = ROTATION_270;
							}
				}
			break; }
			case ROTATION_270: {
				getShapePoints(current_shape, ROTATION_0);
				// Check right boundary
				if (player_pos.x + shape_points[0].x < 11 &&
						player_pos.x + shape_points[1].x < 11 &&
						player_pos.x + shape_points[2].x < 11 &&
						player_pos.x + shape_points[3].x < 11) {
							// Make sure the target area is clear of blocks
							if (matrix[player_pos.y + shape_points[0].y][player_pos.x + shape_points[0].x] == 0 &&
									matrix[player_pos.y + shape_points[1].y][player_pos.x + shape_points[1].x] == 0 &&
									matrix[player_pos.y + shape_points[2].y][player_pos.x + shape_points[2].x] == 0 &&
									matrix[player_pos.y + shape_points[3].y][player_pos.x + shape_points[3].x] == 0) {
										sndObj.playSound(sfxRotating);
										shape_rotation = ROTATION_0;
							}
				}
			break; }
		}
	}

}


// ****************************************************************************************************************
// KeyUp handler
// ****************************************************************************************************************
void CGame::kuFfopirSirtetPaehc(DWORD dwKey) {

	using namespace ns_FfopirSirtetPaehc;

	// Command button
	if (dwKey == kCommand) {
    miniGameCommandButtonHandler();
	}

	// Handle left movement events
	if (dwKey == kLeft) {
		player_dir_west = false;
	}

	// Handle right movement events
	if (dwKey == kRight) {
		player_dir_east = false;
	}

	// Handle down movement events
	if (dwKey == kDown) {
		player_dir_south = false;
		quick_down			 = false;
	}

	// Handle keypresses
	if (dwKey == kAction) {
		player_button_down = false;
	}

}


// ****************************************************************************************************************
// Initialize
// ****************************************************************************************************************
void CGame::initializeFfopirSirtetPaehc() {

	using namespace ns_FfopirSirtetPaehc;

	player_pos				 = newShape();
	player_speed_delay = 0;
	player_speed			 = 10;
	quick_down				 = false;

	for (int y = 0; y < 20; y++) {
		for (int x = 0; x < 11; x++) {
			matrix[y][x] = 0;
		}
	}

}


// ****************************************************************************************************************
// Loader
// ****************************************************************************************************************
void CGame::loadFfopirSirtetPaehc(CGapiSurface* backbuffer) {

	using namespace ns_FfopirSirtetPaehc;

	processEvents = false;

	// Move on to the next step
	loading_step++;

	// Do the appropriate step
	switch(loading_step) {

		case 1: {
			doCommonInit();
      block          = NULL;
      background     = NULL;
      sfxMove        = NULL;
      sfxRotating    = NULL;
      sfxLandedClear = NULL;
		break; }

		case 2: {
			block          = new CGapiSurface();  createSurface(TEXT("ffopir_sirtet_paehc : GFX_FFOPIR_SIRTET_PAEHC_BLOCK"),          block->CreateSurface     (0, m_config.hInstance, GFX_FFOPIR_SIRTET_PAEHC_BLOCK,      TEXT("GRAPHICS"))); block->SetColorKey     (RGB(255, 128, 255));
			background     = new CGapiSurface();  createSurface(TEXT("ffopir_sirtet_paehc : GFX_FFOPIR_SIRTET_PAEHC_BACKGROUND"),     background->CreateSurface(0, m_config.hInstance, GFX_FFOPIR_SIRTET_PAEHC_BACKGROUND, TEXT("GRAPHICS"))); background->SetColorKey(RGB(255, 128, 255));
      sfxMove        = new hssSound();      loadSFX      (TEXT("ffopir_sirtet_paehc : SFX_MOVE"),                               sfxMove->load            (m_config.hInstance,    SFX_MOVE));                                             sfxMove->loop          (false);
      sfxRotating    = new hssSound();      loadSFX      (TEXT("ffopir_sirtet_paehc : SFX_FFOPIR_SIRTET_PAEHC_ROTATING"),       sfxRotating->load        (m_config.hInstance,    SFX_FFOPIR_SIRTET_PAEHC_ROTATING));                     sfxRotating->loop      (false);
      sfxLandedClear = new hssSound();      loadSFX      (TEXT("ffopir_sirtet_paehc : SFX_FFOPIR_SIRTET_PAEHC_LANDED_CLEARED"), sfxLandedClear->load     (m_config.hInstance,    SFX_FFOPIR_SIRTET_PAEHC_LANDED_CLEARED));               sfxLandedClear->loop   (false);
		break; }

    case 3: {
			initializeFfopirSirtetPaehc();
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
void CGame::destroyFfopirSirtetPaehc(CGapiSurface* backbuffer) {

	using namespace ns_FfopirSirtetPaehc;

	processEvents = false;

	// Move on to the next step
	destroying_step++;

	// Do the appropriate step
	switch(destroying_step) {

		case 1: {
			doCommonCleanup();
		break; }

		case 2: {
			delete block;
			delete background;
      delete sfxMove;
			delete sfxRotating;
			delete sfxLandedClear;
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
namespace ns_FfopirSirtetPaehc {

	POINT newShape() {

		POINT pp;
		current_shape = (rand() % 7) + 1; // 1-7
		switch (current_shape) {
			case 1: {	pp.x = 5;	break; }
			case 2: {	pp.x = 5;	break; }
			case 3: {	pp.x = 5;	break; }
			case 4: {	pp.x = 5;	break; }
			case 5: {	pp.x = 5;	break; }
			case 6: {	pp.x = 5;	break; }
			case 7: {	pp.x = 5;	break; }
		}
		pp.y							 = 0;
		shape_rotation		 = ROTATION_0;
		player_speed_delay = 0;
		quick_down				 = false;
		return pp;

	}


	int clearRows() {

		int num_cleared = 0;
		bool clear_row;

		for (int y = 0; y < 20; y++) {
			clear_row = true;
			// Scan the next row.  If any blank spaces found, don't clear it
			for (int x = 0; x < 11; x++) {
				if (matrix[y][x] == 0) { clear_row = false; }
			}
			// No blanks found, go ahead and set the row to be cleared
			if (clear_row) {
				num_cleared++;
				matrix[y][0] = 2;
			}
		}

		// At this point, all rows to be cleared have values of 2 in the matrix.  So, we go through the matrix again, and
		// for each row to be cleared, we copy it over to the temp matrix, then back again when we're done
		for (y = 0; y < 20; y++) {
			for (int x = 0; x < 11; x++) {
				matrix_temp[y][x] = 0;
			}
		}
		int dest = 19;
		for (y = 19; y > 1; y--) {
			if (matrix[y][0] != 2) {
				for (int x = 0; x < 11; x++) {
					matrix_temp[dest][x] = matrix[y][x];
				}
				dest--;
			}
		}
		for (y = 0; y < 20; y++) {
			for (int x = 0; x < 11; x++) {
				matrix[y][x] = matrix_temp[y][x];
			}
		}

		// Return true if any rows cleared, false otherwisw
		return num_cleared;

	}


	void getShapePoints(int shape_number, int rotation) {

		switch (shape_number) {

			// *
			// *
			// *
			// *
			case 1: {
				switch (rotation) {
					case ROTATION_0: case ROTATION_180:
						shape_points[0].x = 0; shape_points[0].y = 0;
						shape_points[1].x = 0; shape_points[1].y = 1;
						shape_points[2].x = 0; shape_points[2].y = 2;
						shape_points[3].x = 0; shape_points[3].y = 3;
					break;
					case ROTATION_90: case ROTATION_270:
						shape_points[0].x = 0; shape_points[0].y = 0;
						shape_points[1].x = 1; shape_points[1].y = 0;
						shape_points[2].x = 2; shape_points[2].y = 0;
						shape_points[3].x = 3; shape_points[3].y = 0;
					break;
				}
			break; }

			// *
			// **
			//  *
			case 2: {
				switch (rotation) {
					case ROTATION_0: case ROTATION_180:
						shape_points[0].x = 0; shape_points[0].y = 0;
						shape_points[1].x = 0; shape_points[1].y = 1;
						shape_points[2].x = 1; shape_points[2].y = 1;
						shape_points[3].x = 1; shape_points[3].y = 2;
					break;
					case ROTATION_90: case ROTATION_270:
						shape_points[0].x = 1; shape_points[0].y = 0;
						shape_points[1].x = 2; shape_points[1].y = 0;
						shape_points[2].x = 0; shape_points[2].y = 1;
						shape_points[3].x = 1; shape_points[3].y = 1;
					break;
				}
			break; }

			// **
			// **
			case 3: {
				switch (rotation) {
					case ROTATION_0: case ROTATION_180: case ROTATION_90: case ROTATION_270:
						shape_points[0].x = 0; shape_points[0].y = 0;
						shape_points[1].x = 1; shape_points[1].y = 0;
						shape_points[2].x = 0; shape_points[2].y = 1;
						shape_points[3].x = 1; shape_points[3].y = 1;
					break;
				}
			break; }

			//  *
			// **
			// *
			case 4: {
				switch (rotation) {
					case ROTATION_0: case ROTATION_180:
						shape_points[0].x = 1; shape_points[0].y = 0;
						shape_points[1].x = 0; shape_points[1].y = 1;
						shape_points[2].x = 1; shape_points[2].y = 1;
						shape_points[3].x = 0; shape_points[3].y = 2;
					break;
					case ROTATION_90: case ROTATION_270:
						shape_points[0].x = 0; shape_points[0].y = 0;
						shape_points[1].x = 1; shape_points[1].y = 0;
						shape_points[2].x = 1; shape_points[2].y = 1;
						shape_points[3].x = 2; shape_points[3].y = 1;
					break;
				}
			break; }

			//  *
			// ***
			case 5: {
				switch (rotation) {
					case ROTATION_0:
						shape_points[0].x = 1; shape_points[0].y = 0;
						shape_points[1].x = 0; shape_points[1].y = 1;
						shape_points[2].x = 1; shape_points[2].y = 1;
						shape_points[3].x = 2; shape_points[3].y = 1;
					break;
					case ROTATION_90:
						shape_points[0].x = 0; shape_points[0].y = 0;
						shape_points[1].x = 0; shape_points[1].y = 1;
						shape_points[2].x = 1; shape_points[2].y = 1;
						shape_points[3].x = 0; shape_points[3].y = 2;
					break;
					case ROTATION_180:
						shape_points[0].x = 0; shape_points[0].y = 0;
						shape_points[1].x = 1; shape_points[1].y = 0;
						shape_points[2].x = 2; shape_points[2].y = 0;
						shape_points[3].x = 1; shape_points[3].y = 1;
					break;
					case ROTATION_270:
						shape_points[0].x = 1; shape_points[0].y = 0;
						shape_points[1].x = 0; shape_points[1].y = 1;
						shape_points[2].x = 1; shape_points[2].y = 1;
						shape_points[3].x = 1; shape_points[3].y = 2;
					break;
				}
			break; }

			// *
			// *
			// **
			case 6: {
				switch (rotation) {
					case ROTATION_0:
						shape_points[0].x = 0; shape_points[0].y = 0;
						shape_points[1].x = 0; shape_points[1].y = 1;
						shape_points[2].x = 0; shape_points[2].y = 2;
						shape_points[3].x = 1; shape_points[3].y = 2;
					break;
					case ROTATION_90:
						shape_points[0].x = 0; shape_points[0].y = 0;
						shape_points[1].x = 1; shape_points[1].y = 0;
						shape_points[2].x = 2; shape_points[2].y = 0;
						shape_points[3].x = 0; shape_points[3].y = 1;
					break;
					case ROTATION_180:
						shape_points[0].x = 0; shape_points[0].y = 0;
						shape_points[1].x = 1; shape_points[1].y = 0;
						shape_points[2].x = 1; shape_points[2].y = 1;
						shape_points[3].x = 1; shape_points[3].y = 2;
					break;
					case ROTATION_270:
						shape_points[0].x = 2; shape_points[0].y = 0;
						shape_points[1].x = 0; shape_points[1].y = 1;
						shape_points[2].x = 1; shape_points[2].y = 1;
						shape_points[3].x = 2; shape_points[3].y = 1;
					break;
				}
			break; }

			//  *
			//  *
			// **
			case 7: {
				switch (rotation) {
					case ROTATION_0:
						shape_points[0].x = 1; shape_points[0].y = 0;
						shape_points[1].x = 1; shape_points[1].y = 1;
						shape_points[2].x = 0; shape_points[2].y = 2;
						shape_points[3].x = 1; shape_points[3].y = 2;
					break;
					case ROTATION_90:
						shape_points[0].x = 0; shape_points[0].y = 0;
						shape_points[1].x = 0; shape_points[1].y = 1;
						shape_points[2].x = 1; shape_points[2].y = 1;
						shape_points[3].x = 2; shape_points[3].y = 1;
					break;
					case ROTATION_180:
						shape_points[0].x = 0; shape_points[0].y = 0;
						shape_points[1].x = 1; shape_points[1].y = 0;
						shape_points[2].x = 0; shape_points[2].y = 1;
						shape_points[3].x = 0; shape_points[3].y = 2;
					break;
					case ROTATION_270:
						shape_points[0].x = 0; shape_points[0].y = 0;
						shape_points[1].x = 1; shape_points[1].y = 0;
						shape_points[2].x = 2; shape_points[2].y = 0;
						shape_points[3].x = 2; shape_points[3].y = 1;
					break;
				}
			break; }

		}

	}


} // End of namespace
