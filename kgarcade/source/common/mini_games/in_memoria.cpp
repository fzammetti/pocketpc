
#include "../main.h"


namespace ns_InMemoria {


// ****************************************************************************************************************
// Defines specific to this mini-game
// ****************************************************************************************************************
#define TILE_UNFLIPPED 0
#define TILE_FLIPPED   1
#define TILE_MATCHED   2


// ****************************************************************************************************************
// Function prototypes specific to this mini-game
// ****************************************************************************************************************
void setTileStatesUnflipped();
void randomizeTiles();


// ****************************************************************************************************************
// Globals specific to this mini-game
// ****************************************************************************************************************
TCHAR	instructions[][32] = { TEXT("In Memoria"),
														 TEXT(""),
														 TEXT("Some alien races view"),
														 TEXT("memory as the ultimate"),
														 TEXT("measure of intelligence."),
														 TEXT("Time to see if your a"),
														 TEXT("pangalactic super genius"),
														 TEXT("or an Aldevrian Marsh"),
														 TEXT("Rat's leftover dinner"),
														 TEXT("from three nights ago."),
                             //    ---------------------------
                             TEXT("The Goal"),
														 TEXT(""),
														 TEXT("Match as many tiles in"),
														 TEXT("before time runs out"),
														 TEXT("as you can."),
														 TEXT(""),
														 TEXT(""),
														 TEXT(""),
														 TEXT(""),
														 TEXT(""),
                             //    ---------------------------
                             TEXT("How To Play"),
														 TEXT(""),
														 TEXT("Move up, down, left or"),
														 TEXT("right and press ACTION"),
														 TEXT("to flip over a tile."),
														 TEXT("Flip another to see if"),
														 TEXT("they match."),
														 TEXT(""),
														 TEXT(""),
														 TEXT(""),
                             //    ----------------------------
};

CGapiSurface*	unflipped_tile_picture = NULL;  // Stores the picture that is used for unflipped tiles
CGapiSurface* explosion[8];
CGapiSurface*	tile_source_pictures[14];       // Stores all the possible pictures for underneath tiles
hssSound*			sfxFlip                = NULL;
hssSound*			sfxUnflip              = NULL;
hssSound*			sfxNoMatch             = NULL;
hssSound*     sfxExplosion           = NULL;
bool					unflipping             = false; // Flag to tell whether we're currently unflipping a pair of tiles
bool					explosion_running      = false; // Flag to tell us whether we are currently exploding matched tiles
int						tiles_flipped          = 0;     // Stores the number of tiles currently flipped
int						unflipping_counter     = 0;     // Used to delay before unflipping a pair of tiles
int						unflipped_tile_1_x     = 0;     // X index of the first unflipped tile
int						unflipped_tile_1_y     = 0;     // Y index of the first unflipped tile
int						unflipped_tile_2_x     = 0;     // X index of the second unflipped tile
int						unflipped_tile_2_y     = 0;     // Y index of the second unflipped tile
int						number_matched         = 0;     // Number of pairs matched so far
int						box_around_x           = 0;     // X index of the tile the select box is currently around
int						box_around_y           = 0;     // Y index of the tile the select box is currently around
int           explosion_frame        = 0;
int           explosion_frame_delay  = 0;
int						tile_states[7][7];				      // Stores the current state of each tke
int						tile_pictures[7][7];			      // Stores what picture is under each tile
int           op_dir                 = 0;
int           op                     = 240;


} // End of namespace


// ****************************************************************************************************************
// ProcessNextFrame handler
// ****************************************************************************************************************
void CGame::pnfInMemoria(CGapiSurface* backbuffer) {

	using namespace ns_InMemoria;

	int loc_x;
	int loc_y;

	// Draw the tiles in the correct current state
	for (int y = 0; y < 5; y++) {
		for (int x = 0; x < 5; x++) {
			// Calculate the proper X/Y coordinates for each tile
			loc_x = ((x * 36) + (x * 3)) + 4;
			loc_y = ((y * 36) + (y * 3)) + 4;
			// Draw the tile depending on it's state
			switch (tile_states[y][x]) {
				case TILE_FLIPPED:
					backbuffer->BltFast(xadj + loc_x, yadj + loc_y,
																tile_source_pictures[tile_pictures[y][x]],
																NULL, 0, NULL);
				break;
				case TILE_UNFLIPPED:
					backbuffer->BltFast(xadj + loc_x, yadj + loc_y,
																unflipped_tile_picture,
																NULL, 0, NULL);
				break;
			}
		}
	}

	// Draw the selection box around the correct tile
	loc_x = ((box_around_x * 36) + (box_around_x * 3)) + 3;
	loc_y = ((box_around_y * 36) + (box_around_y * 3)) + 3;
	RECT rect;
	SetRect(&rect, xadj + loc_x, yadj + loc_y, xadj + loc_x + 38, yadj + loc_y + 38);
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
			box_around_y--;
			if (box_around_y < 0) { box_around_y = 4; }
		} else {
			player_dir_delay++;
		}
	}
	if (player_dir_south) {
		if (player_dir_delay > 5) {
			player_dir_delay = 0;
			box_around_y++;
			if (box_around_y > 4) { box_around_y = 0; }
		} else {
			player_dir_delay++;
		}
	}
	if (player_dir_west) {
		if (player_dir_delay > 5) {
			player_dir_delay = 0;
			box_around_x--;
			if (box_around_x < 0) { box_around_x = 4; }
		} else {
			player_dir_delay++;
		}
	}
	if (player_dir_east) {
		if (player_dir_delay > 5) {
			player_dir_delay = 0;
			box_around_x++;
			if (box_around_x > 4) { box_around_x = 0; }
		} else {
			player_dir_delay++;
		}
	}


	// If we're currently unflipping a pair of tiles (i.e., they didn't match), we need to do that.
	// We'll just keep incrementing our counter until we hit te desired amount, then flip the tiles back over
	if (unflipping) {
		unflipping_counter++;
		if (unflipping_counter > 15) {
			sndObj.playSound(sfxNoMatch);
			unflipping				 = false;
			unflipping_counter = 0;
			tiles_flipped			 = 0;
			tile_states[unflipped_tile_1_y][unflipped_tile_1_x] = TILE_UNFLIPPED;
			tile_states[unflipped_tile_2_y][unflipped_tile_2_x] = TILE_UNFLIPPED;
		}
	}

	// If we're currently exploding a pair of matched tiles, we need to do that.
	if (explosion_running) {
		loc_x = ((unflipped_tile_1_x * 36) + (unflipped_tile_1_x * 3)) + 3;
		loc_y = ((unflipped_tile_1_y * 36) + (unflipped_tile_1_y * 3)) + 3;
		backbuffer->BltFast(xadj + loc_x, yadj + loc_y, explosion[explosion_frame], NULL, GDBLTFAST_KEYSRC, NULL);
		loc_x = ((unflipped_tile_2_x * 36) + (unflipped_tile_2_x * 3)) + 3;
		loc_y = ((unflipped_tile_2_y * 36) + (unflipped_tile_2_y * 3)) + 3;
		backbuffer->BltFast(xadj + loc_x, yadj + loc_y, explosion[explosion_frame], NULL, GDBLTFAST_KEYSRC, NULL);
		int ret_val;
		explosion_frame_delay++;
		if (explosion_frame_delay > 0) {
			explosion_frame_delay = 0;
			explosion_frame++;
			if (explosion_frame > 4) {
				explosion_frame = 0;
				ret_val = -1;
			} else {
				ret_val = explosion_frame;
			}
		}
		if (explosion_frame == 2) { ret_val = 99; }
		if (ret_val == -1) {
			explosion_running	= false;
			tiles_flipped			= 0;
			tile_states[unflipped_tile_1_y][unflipped_tile_1_x] = TILE_MATCHED;
			tile_states[unflipped_tile_2_y][unflipped_tile_2_x] = TILE_MATCHED;
    }
	}

}


// ****************************************************************************************************************
// KeyDown handler
// ****************************************************************************************************************
void CGame::kdInMemoria(DWORD dwKey) {

	using namespace ns_InMemoria;

	if (!unflipping && !explosion_running) {

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

}


// ****************************************************************************************************************
// KeyUp handler
// ****************************************************************************************************************
void CGame::kuInMemoria(DWORD dwKey) {

	using namespace ns_InMemoria;

	// Command button
	if (dwKey == kCommand) {
    miniGameCommandButtonHandler();
	}

	// Only process events if we're not unflipping tiles and not exploding tiles
	if (!unflipping && !explosion_running) {

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

			switch (tile_states[box_around_y][box_around_x]) {

				// Tile is currently flipped, so unflip it
				case TILE_FLIPPED:
					sndObj.playSound(sfxUnflip);
					tile_states[box_around_y][box_around_x] = TILE_UNFLIPPED;
					tiles_flipped--;
				break;

				// Tile is currently unflipped, so flip it
				case TILE_UNFLIPPED:

					sndObj.playSound(sfxFlip);
					tile_states[box_around_y][box_around_x] = TILE_FLIPPED;
					tiles_flipped++;

					// If it's the first tile that's unflipped, store it in the first set of vars
					if (tiles_flipped == 1) {
						unflipped_tile_1_x = box_around_x;
						unflipped_tile_1_y = box_around_y;
					}

					// If it's the second tile that's unflipped, store it in the second set of vats
					if (tiles_flipped == 2) {
						unflipped_tile_2_x = box_around_x;
						unflipped_tile_2_y = box_around_y;
					}

					// If two tiles are now flipped, check to see if they match.  If they don't, set our
					// unflipping flag so they will be unflipped after a brief delay
					if (tiles_flipped == 2) {

						// Match
						if (tile_pictures[unflipped_tile_1_y][unflipped_tile_1_x] ==
								tile_pictures[unflipped_tile_2_y][unflipped_tile_2_x]) {
									tile_states[unflipped_tile_1_y][unflipped_tile_1_x] = TILE_MATCHED;
									tile_states[unflipped_tile_2_y][unflipped_tile_2_x] = TILE_MATCHED;

									sndObj.playSound(sfxExplosion);

									number_matched++;
									addToScore(25);

									// If the game is over, restart it
									if (number_matched > 11) {
											initializeInMemoria();
											setTileStatesUnflipped();
											randomizeTiles();
									} else {
										// Otherwise, set our flag to blow up the tiles and reset movements
										explosion_running		 = true;
										player_dir_north		 = false;
										player_dir_south		 = false;
										player_dir_east			 = false;
										player_dir_west			 = false;
									}

						// No match
						} else {

							// Unflip our tiles and reset movements
							unflipping				   = true;
							unflipping_counter	 = 0;
							player_dir_north		 = false;
							player_dir_south		 = false;
							player_dir_east			 = false;
							player_dir_west			 = false;

						}

					}

				break;

			} // End of switch(tile_states[y][x])

		} // End of if(dwKey == kAction)

	} // End of if(!unflipping)

}


// ****************************************************************************************************************
// Initialize
// ****************************************************************************************************************
void CGame::initializeInMemoria() {

	using namespace ns_InMemoria;

	tiles_flipped				= 0;
	unflipping					= false;
	unflipping_counter	= 0;
	unflipped_tile_1_x	= 0;
	unflipped_tile_1_y	= 0;
	unflipped_tile_2_x	= 0;
	unflipped_tile_2_y	= 0;
	number_matched			= 0;
	box_around_x				= 0;
	box_around_y				= 0;
  op_dir              = 0;
  op                  = 240;

}


// ****************************************************************************************************************
// Loader
// ****************************************************************************************************************
void CGame::loadInMemoria(CGapiSurface* backbuffer) {

	using namespace ns_InMemoria;

	processEvents = false;

	// Move on to the next step
	loading_step++;

	// Do the appropriate step
	switch(loading_step) {

		case 1: {
			doCommonInit();
      int i = 0;
      for (i = 0; i < 6; i++)  { explosion[i]           = NULL; }
      for (i = 0; i < 12; i++) {tile_source_pictures[i] = NULL; }
      unflipped_tile_picture = NULL;
      sfxFlip                = NULL;
      sfxUnflip              = NULL;
      sfxNoMatch             = NULL;
      sfxExplosion           = NULL;
		break; }

		case 2: {
			explosion[0]             = new CGapiSurface(); createSurface(TEXT("in_memoria : GFX_EXPLOSION_00"),                      explosion[0]->CreateSurface            (0, m_config.hInstance, GFX_EXPLOSION_00,                       TEXT("GRAPHICS"))); explosion[0]->SetColorKey            (RGB(255, 128, 255));
			explosion[1]             = new CGapiSurface(); createSurface(TEXT("in_memoria : GFX_EXPLOSION_01"),                      explosion[1]->CreateSurface            (0, m_config.hInstance, GFX_EXPLOSION_01,                       TEXT("GRAPHICS"))); explosion[1]->SetColorKey            (RGB(255, 128, 255));
			explosion[2]             = new CGapiSurface(); createSurface(TEXT("in_memoria : GFX_EXPLOSION_02"),                      explosion[2]->CreateSurface            (0, m_config.hInstance, GFX_EXPLOSION_02,                       TEXT("GRAPHICS"))); explosion[2]->SetColorKey            (RGB(255, 128, 255));
			explosion[3]             = new CGapiSurface(); createSurface(TEXT("in_memoria : GFX_EXPLOSION_03"),                      explosion[3]->CreateSurface            (0, m_config.hInstance, GFX_EXPLOSION_03,                       TEXT("GRAPHICS"))); explosion[3]->SetColorKey            (RGB(255, 128, 255));
			explosion[4]             = new CGapiSurface(); createSurface(TEXT("in_memoria : GFX_EXPLOSION_04"),                      explosion[4]->CreateSurface            (0, m_config.hInstance, GFX_EXPLOSION_04,                       TEXT("GRAPHICS"))); explosion[4]->SetColorKey            (RGB(255, 128, 255));
			unflipped_tile_picture   = new CGapiSurface(); createSurface(TEXT("in_memoria : GFX_IN_MEMORIA_UNFLIPPED_TILE_PICTURE"), unflipped_tile_picture->CreateSurface  (0, m_config.hInstance, GFX_IN_MEMORIA_UNFLIPPED_TILE_PICTURE,  TEXT("GRAPHICS"))); explosion[4]->SetColorKey            (RGB(255, 128, 255));
      tile_source_pictures[0]  = new CGapiSurface(); createSurface(TEXT("in_memoria : GFX_IN_MEMORIA_TILE_PICTURE_00"),        tile_source_pictures[0]->CreateSurface (0, m_config.hInstance, GFX_IN_MEMORIA_TILE_PICTURE_00,         TEXT("GRAPHICS"))); tile_source_pictures[0]->SetColorKey (RGB(255, 128, 255));
      tile_source_pictures[1]  = new CGapiSurface(); createSurface(TEXT("in_memoria : GFX_IN_MEMORIA_TILE_PICTURE_01"),        tile_source_pictures[1]->CreateSurface (0, m_config.hInstance, GFX_IN_MEMORIA_TILE_PICTURE_01,         TEXT("GRAPHICS"))); tile_source_pictures[1]->SetColorKey (RGB(255, 128, 255));
      tile_source_pictures[2]  = new CGapiSurface(); createSurface(TEXT("in_memoria : GFX_IN_MEMORIA_TILE_PICTURE_02"),        tile_source_pictures[2]->CreateSurface (0, m_config.hInstance, GFX_IN_MEMORIA_TILE_PICTURE_02,         TEXT("GRAPHICS"))); tile_source_pictures[2]->SetColorKey (RGB(255, 128, 255));
      tile_source_pictures[3]  = new CGapiSurface(); createSurface(TEXT("in_memoria : GFX_IN_MEMORIA_TILE_PICTURE_03"),        tile_source_pictures[3]->CreateSurface (0, m_config.hInstance, GFX_IN_MEMORIA_TILE_PICTURE_03,         TEXT("GRAPHICS"))); tile_source_pictures[3]->SetColorKey (RGB(255, 128, 255));
      tile_source_pictures[4]  = new CGapiSurface(); createSurface(TEXT("in_memoria : GFX_IN_MEMORIA_TILE_PICTURE_04"),        tile_source_pictures[4]->CreateSurface (0, m_config.hInstance, GFX_IN_MEMORIA_TILE_PICTURE_04,         TEXT("GRAPHICS"))); tile_source_pictures[4]->SetColorKey (RGB(255, 128, 255));
      tile_source_pictures[5]  = new CGapiSurface(); createSurface(TEXT("in_memoria : GFX_IN_MEMORIA_TILE_PICTURE_05"),        tile_source_pictures[5]->CreateSurface (0, m_config.hInstance, GFX_IN_MEMORIA_TILE_PICTURE_05,         TEXT("GRAPHICS"))); tile_source_pictures[5]->SetColorKey (RGB(255, 128, 255));
      tile_source_pictures[6]  = new CGapiSurface(); createSurface(TEXT("in_memoria : GFX_IN_MEMORIA_TILE_PICTURE_06"),        tile_source_pictures[6]->CreateSurface (0, m_config.hInstance, GFX_IN_MEMORIA_TILE_PICTURE_06,         TEXT("GRAPHICS"))); tile_source_pictures[6]->SetColorKey (RGB(255, 128, 255));
      tile_source_pictures[7]  = new CGapiSurface(); createSurface(TEXT("in_memoria : GFX_IN_MEMORIA_TILE_PICTURE_07"),        tile_source_pictures[7]->CreateSurface (0, m_config.hInstance, GFX_IN_MEMORIA_TILE_PICTURE_07,         TEXT("GRAPHICS"))); tile_source_pictures[7]->SetColorKey (RGB(255, 128, 255));
      tile_source_pictures[8]  = new CGapiSurface(); createSurface(TEXT("in_memoria : GFX_IN_MEMORIA_TILE_PICTURE_08"),        tile_source_pictures[8]->CreateSurface (0, m_config.hInstance, GFX_IN_MEMORIA_TILE_PICTURE_08,         TEXT("GRAPHICS"))); tile_source_pictures[8]->SetColorKey (RGB(255, 128, 255));
      tile_source_pictures[9]  = new CGapiSurface(); createSurface(TEXT("in_memoria : GFX_IN_MEMORIA_TILE_PICTURE_09"),        tile_source_pictures[9]->CreateSurface (0, m_config.hInstance, GFX_IN_MEMORIA_TILE_PICTURE_09,         TEXT("GRAPHICS"))); tile_source_pictures[9]->SetColorKey (RGB(255, 128, 255));
      tile_source_pictures[10] = new CGapiSurface(); createSurface(TEXT("in_memoria : GFX_IN_MEMORIA_TILE_PICTURE_10"),        tile_source_pictures[10]->CreateSurface(0, m_config.hInstance, GFX_IN_MEMORIA_TILE_PICTURE_10,         TEXT("GRAPHICS"))); tile_source_pictures[10]->SetColorKey(RGB(255, 128, 255));
      tile_source_pictures[11] = new CGapiSurface(); createSurface(TEXT("in_memoria : GFX_IN_MEMORIA_TILE_PICTURE_11"),        tile_source_pictures[11]->CreateSurface(0, m_config.hInstance, GFX_IN_MEMORIA_TILE_PICTURE_11,         TEXT("GRAPHICS"))); tile_source_pictures[11]->SetColorKey(RGB(255, 128, 255));
      sfxFlip                  = new hssSound();     loadSFX      (TEXT("in_memoria : SFX_MISC_3"),                            sfxFlip->load                          (m_config.hInstance,    SFX_MISC_3));                                               sfxFlip->loop                        (false);
			sfxUnflip                = new hssSound();     loadSFX      (TEXT("in_memoria : SFX_UNFLIP"),                            sfxUnflip->load                        (m_config.hInstance,    SFX_UNFLIP));                                               sfxUnflip->loop                      (false);
			sfxNoMatch               = new hssSound();     loadSFX      (TEXT("in_memoria : SFX_NO_MATCH"),                          sfxNoMatch->load                       (m_config.hInstance,    SFX_NO_MATCH));                                             sfxNoMatch->loop                     (false);
			sfxExplosion             = new hssSound();     loadSFX      (TEXT("in_memoria : SFX_EXPLOSION"),                         sfxExplosion->load                     (m_config.hInstance,    SFX_EXPLOSION));                                            sfxExplosion->loop                   (false);
    break; }

    case 3 : {
			initializeInMemoria();
      for (int i = 0; i < 30; i++) { _tcscpy(mgInstructions[i], instructions[i]); } mgInstructionsPage = 0; mgiPrevTapped = false; mgiNextTapped = false;
      setTileStatesUnflipped();
			randomizeTiles();
			explosion_frame       = 0;
			explosion_frame_delay = 0;
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
void CGame::destroyInMemoria(CGapiSurface* backbuffer) {

	using namespace ns_InMemoria;

	processEvents = false;

	// Move on to the next step
	destroying_step++;

	// Do the appropriate step
	switch(destroying_step) {

		case 1: {
			doCommonCleanup();
		break; }

		case 2: {
			delete explosion[0];
			delete explosion[1];
			delete explosion[2];
			delete explosion[3];
			delete explosion[4];
			delete sfxExplosion;
			delete sfxFlip;
			delete sfxUnflip;
			delete sfxNoMatch;
			delete unflipped_tile_picture;
		break; }

		case 3: {
			delete tile_source_pictures[0];
			delete tile_source_pictures[1];
			delete tile_source_pictures[2];
			delete tile_source_pictures[3];
		break; }

		case 4: {
			delete tile_source_pictures[4];
			delete tile_source_pictures[5];
			delete tile_source_pictures[6];
			delete tile_source_pictures[7];
		break; }

		case 5: {
			delete tile_source_pictures[8];
			delete tile_source_pictures[9];
			delete tile_source_pictures[10];
			delete tile_source_pictures[11];
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
namespace ns_InMemoria {


	// Set all our tile states to unflipped
	void setTileStatesUnflipped() {

		// Set the state of all tiles to unflipped
		for (int y = 0; y < 5; y++) {
			for (int x = 0; x < 5; x++) {
				tile_states[y][x] = TILE_UNFLIPPED;
			}
		}

	}


	// Randomly choose which pictures will be under the tiles
	void randomizeTiles() {

		int i;
		int x;
		int y;
		int x1;
		int y1;
		int x2;
		int y2;

		// Set all tiles to -1, which means no image assigned
		for (y = 0; y < 5; y++) {
			for (x = 0; x < 5; x++) {
				tile_pictures[y][x] = -1;
			}
		}

		// For each source tile, randomly choose two tiles and assign them the next image,
		for (i = 0; i < 11; i++) {
			chooseIndexes:
			x1 = rand() % 5;
			y1 = rand() % 5;
			x2 = rand() % 5;
			y2 = rand() % 5;
			if (tile_pictures[y1][x1] == -1 && tile_pictures[y2][x2] == -1) {
				tile_pictures[y1][x1] = i;
				tile_pictures[y2][x2] = i;
			} else {
				goto chooseIndexes;
			}
		}

		// We'll have one tile left with nothing in it, so find it and set it to the last image (it's never matched)
		for (y = 0; y < 5; y++) {
			for (x = 0; x < 5; x++) {
				if (tile_pictures[y][x] == -1) {
					tile_pictures[y][x] = 11;
				}
			}
		}

	}


} // End of namespace
