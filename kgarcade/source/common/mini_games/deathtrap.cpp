
#include "../main.h"


namespace ns_DeathTrap {


// ****************************************************************************************************************
// Defines specific to this mini-game
// ****************************************************************************************************************
#define NONE		0
#define NE			1
#define NW			2
#define ES			3
#define SW			4
#define NES			5
#define NSW			6
#define ESW			7
#define NEW			8
#define NESW		9
#define PSALIVE 10
#define PSDEAD  11
#define PSWON   12


// ****************************************************************************************************************
// Function prototypes specific to this mini-game
// ****************************************************************************************************************
bool isDeathTile();


// ****************************************************************************************************************
// Globals specific to this mini-game
// ****************************************************************************************************************
TCHAR	instructions[][32] = { TEXT("DeathTrap"),
														 TEXT(""),
														 TEXT("You find yourself in a"),
														 TEXT("room with tiles all over"),
														 TEXT("the floor.  Unfortunately"),
														 TEXT("for you, only a single"),
														 TEXT("path of safe tiles exists,"),
														 TEXT("all the rest are"),
														 TEXT("electrified and will toast"),
														 TEXT("you on contact.  Ouch!"),
                             //    ---------------------------
                             TEXT("The Goal"),
														 TEXT(""),
														 TEXT("You must find the safe"),
														 TEXT("route through the room"),
														 TEXT("to reach the escape"),
														 TEXT("hatch on the far side."),
														 TEXT("Accomplish this at least"),
														 TEXT("once before time runs"),
														 TEXT("out."),
														 TEXT(""),
                             //    ---------------------------
                             TEXT("How To Play"),
														 TEXT(""),
														 TEXT("Move up, down, left or"),
														 TEXT("right to hop from tile to"),
														 TEXT("tile."),
														 TEXT(""),
														 TEXT(""),
														 TEXT(""),
														 TEXT(""),
														 TEXT(""),
                             //    ----------------------------
};

CGapiSurface*	background        = NULL;
CGapiSurface*	player_standing   = NULL;
CGapiSurface*	player_jumping    = NULL;
CGapiSurface*	player_dieing[4];
hssSound*			sfxZap            = NULL;
hssSound*			sfxWin            = NULL;
hssSound*			sfxJump           = NULL;
POINT					player_prev_pos;
bool					regen_path        = true;
int						player_state      = 0;
int						vert_move_count   = 0;
int						player_tile_x     = 0;
int						player_tile_y     = 0;
int						correct_path      = -1;
int						dead_counter      = 0;
int						win_counter       = 0;
int           cheat_count       = 0;
int						move_matrix[11][11] = {
																	{ ES,   ESW,  ESW,  ESW,  NSW,  NONE, NONE, NONE, NONE },
																	{ NES,  NESW, NESW, NESW, NSW,  NONE, NONE, NONE, NONE },
																	{ NES,  NESW, NESW, NESW, NESW, SW,   NONE, NONE, NONE },
																	{ NES,  NESW, NESW, NESW, NESW, NSW,  NONE, NONE, NONE },
																	{ NES,  NESW, NESW, NESW, NESW, NESW, SW,   NONE, NONE },
																	{ NES,  NESW, NESW, NESW, NESW, NESW, NSW,  NONE, NONE },
																	{ NE,	  NESW, NESW, NESW, NESW, NESW, NSW,  NONE, NONE },
																	{ NONE, NES,  NESW, NESW, NESW, NESW, NESW, SW,   NONE },
																	{ NONE, NE,   NEW,  NEW,  NEW,  NEW,  NEW,  NW,   NONE }
																	};

// 1 is an OK tile, 0 is a death tile
int death_matrix[12][11][11] =
{{
{ 1, 1, 1, 1, 1, 0, 0, 0, 0 },
{ 1, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 1, 1, 1, 1, 1, 1, 0, 0, 0 },
{ 1, 1, 0, 0, 0, 1, 0, 0, 0 },
{ 1, 1, 0, 0, 0, 1, 0, 0, 0 },
{ 1, 1, 0, 1, 1, 1, 0, 0, 0 },
{ 0, 0, 0, 1, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 1, 0, 0, 0, 0, 0 },
{ 0, 1, 1, 1, 0, 0, 0, 0, 0 }
},{
{ 0, 0, 0, 0, 1, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 1, 0, 0, 0, 0 },
{ 1, 1, 1, 1, 1, 1, 0, 0, 0 },
{ 1, 0, 0, 0, 1, 1, 0, 0, 0 },
{ 1, 0, 0, 0, 1, 0, 0, 0, 0 },
{ 1, 1, 1, 0, 1, 0, 0, 0, 0 },
{ 0, 0, 1, 0, 1, 1, 0, 0, 0 },
{ 0, 1, 1, 0, 0, 0, 0, 0, 0 },
{ 0, 1, 1, 0, 0, 0, 0, 0, 0 }
},{
{ 1, 1, 1, 0, 1, 0, 0, 0, 0 },
{ 1, 0, 1, 1, 1, 0, 0, 0, 0 },
{ 1, 1, 1, 1, 1, 1, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 1, 0, 0, 0 },
{ 1, 1, 1, 1, 0, 1, 0, 0, 0 },
{ 1, 0, 0, 1, 0, 1, 0, 0, 0 },
{ 1, 1, 0, 1, 1, 1, 0, 0, 0 },
{ 0, 1, 0, 0, 1, 0, 0, 0, 0 },
{ 0, 1, 1, 0, 1, 1, 1, 0, 0 }
},{
{ 1, 1, 1, 1, 1, 0, 0, 0, 0 },
{ 1, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 1, 1, 1, 1, 1, 1, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 1, 0, 0, 0 },
{ 0, 0, 1, 1, 1, 1, 0, 0, 0 },
{ 0, 0, 1, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 1, 1, 1, 1, 1, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 1, 0, 0 },
{ 0, 1, 1, 1, 1, 1, 1, 0, 0 }
},{
{ 0, 0, 0, 0, 1, 0, 0, 0, 0 },
{ 0, 0, 0, 1, 1, 0, 0, 0, 0 },
{ 0, 1, 1, 1, 0, 0, 0, 0, 0 },
{ 0, 1, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 1, 1, 1, 1, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 1, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 1, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 1, 0, 0, 0, 0 },
{ 0, 1, 1, 1, 1, 0, 0, 0, 0 }
},{
{ 0, 0, 0, 0, 1, 0, 0, 0, 0 },
{ 1, 1, 1, 0, 1, 0, 0, 0, 0 },
{ 1, 0, 1, 0, 1, 0, 0, 0, 0 },
{ 1, 0, 1, 0, 1, 0, 0, 0, 0 },
{ 1, 0, 1, 1, 1, 0, 0, 0, 0 },
{ 1, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 1, 1, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 1, 0, 1, 1, 1, 0, 0, 0 },
{ 0, 1, 1, 1, 1, 1, 1, 0, 0 }
},{
{ 0, 0, 1, 1, 1, 0, 0, 0, 0 },
{ 0, 0, 1, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 1, 1, 1, 0, 0, 0, 0 },
{ 1, 1, 0, 1, 1, 0, 0, 0, 0 },
{ 0, 1, 0, 1, 0, 0, 0, 0, 0 },
{ 1, 1, 0, 1, 1, 1, 1, 0, 0 },
{ 1, 1, 0, 0, 0, 0, 1, 0, 0 },
{ 0, 1, 0, 0, 0, 0, 1, 1, 0 },
{ 0, 1, 1, 1, 1, 1, 1, 1, 0 }
},{
{ 1, 1, 1, 1, 1, 0, 0, 0, 0 },
{ 1, 0, 0, 1, 1, 0, 0, 0, 0 },
{ 1, 1, 1, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 1, 1, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 1, 1, 1, 0, 0, 0 },
{ 0, 1, 1, 0, 0, 1, 0, 0, 0 },
{ 0, 1, 1, 0, 0, 1, 0, 0, 0 },
{ 0, 1, 1, 0, 0, 1, 0, 0, 0 },
{ 0, 1, 1, 1, 1, 1, 0, 0, 0 }
},{
{ 1, 1, 1, 1, 1, 0, 0, 0, 0 },
{ 1, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 1, 0, 1, 1, 1, 0, 0, 0, 0 },
{ 1, 0, 1, 0, 1, 0, 0, 0, 0 },
{ 1, 0, 1, 0, 1, 1, 0, 0, 0 },
{ 1, 1, 1, 0, 1, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 1, 1, 1, 0, 0 },
{ 0, 0, 0, 0, 1, 0, 1, 0, 0 },
{ 0, 1, 1, 1, 1, 1, 1, 0, 0 }
},{
{ 0, 0, 0, 0, 1, 0, 0, 0, 0 },
{ 0, 0, 1, 1, 1, 0, 0, 0, 0 },
{ 0, 1, 1, 1, 1, 0, 0, 0, 0 },
{ 0, 1, 0, 1, 0, 0, 0, 0, 0 },
{ 1, 1, 0, 1, 0, 1, 0, 0, 0 },
{ 1, 0, 0, 1, 0, 1, 0, 0, 0 },
{ 1, 1, 0, 1, 0, 1, 0, 0, 0 },
{ 0, 1, 0, 1, 1, 1, 0, 0, 0 },
{ 0, 1, 1, 0, 0, 1, 1, 1, 0 }
}};

} // End of namespace


// ****************************************************************************************************************
// ProcessNextFrame handler
// ****************************************************************************************************************
void CGame::pnfDeathTrap(CGapiSurface* backbuffer) {

	using namespace ns_DeathTrap;

	// Blit background
	backbuffer->BltFast(xadj + 0,	yadj + 0, background, NULL, GDBLTFAST_KEYSRC, NULL);

	switch (player_state) {

		case PSDEAD: { // Player is dieing
			if (dead_counter % 2 == 0) {
				backbuffer->BltFast(xadj + player_pos.x,	yadj + player_pos.y, player_dieing[0], NULL, GDBLTFAST_KEYSRC, NULL);
			} else {
				backbuffer->BltFast(xadj + player_pos.x,	yadj + player_pos.y, player_dieing[1], NULL, GDBLTFAST_KEYSRC, NULL);
			}
			dead_counter++;
			if (dead_counter == 15) {
				sndObj.playSound(sfxZap);
			}
			if (dead_counter > 30) {
				initializeDeathTrap();
			}
		break; }

		case PSWON: { // Player won
			GDBLTFX gdbltfx;
			gdbltfx.dwRotationScale = 100 - (win_counter * 2);
			gdbltfx.nRotationAngle  = 0;
			backbuffer->Blt(CRect(xadj + player_pos.x, yadj + player_pos.y, xadj + player_pos.x + 22, yadj + player_pos.y + 41), player_jumping, NULL, GDBLT_KEYSRC | GDBLT_ROTATIONSCALE | GDBLT_ROTATIONANGLE, &gdbltfx);
			win_counter = win_counter + 2;
			player_pos.y = player_pos.y - 1;
			vert_move_count++;
			if (vert_move_count > 1) {
				vert_move_count = 0;
				player_pos.x		= player_pos.x + 1;
			}
			if (win_counter > 50) {
				addToScore(1000);
				regen_path = true;
				initializeDeathTrap();
			}
		break; }

		case PSALIVE: { // Player is alive

			// Blit player
			if (player_dir_north || player_dir_east || player_dir_south || player_dir_west) {
				backbuffer->BltFast(xadj + player_pos.x,	yadj + player_pos.y, player_jumping, NULL, GDBLTFAST_KEYSRC, NULL);
			} else {
				backbuffer->BltFast(xadj + player_pos.x,	yadj + player_pos.y, player_standing, NULL, GDBLTFAST_KEYSRC, NULL);
			}

			// Handle player movement
			// Horizontal movemenet : x +- 25
			// Vertical movement:     x +- 10 && y +- 16

			// North
			if (player_dir_north) {
				// If movemement is done, finish up
				if (player_pos.y <= (player_prev_pos.y - 16)) {
          cheat_count = 0;
					vert_move_count  = 0;
					player_pos.x		 = player_prev_pos.x + 10;
					player_pos.y		 = player_prev_pos.y - 16;
					player_dir_north = false;
					if (isDeathTile()) {
						player_state = PSDEAD;
						sndObj.playSound(sfxZap);
					} else {
						sndObj.playSound(sfxJump);
					}
				} else { // Otherwise, move the player
					player_pos.y = player_pos.y - 3;
					vert_move_count++;
					if (vert_move_count > 1) {
						vert_move_count = 0;
						player_pos.x = player_pos.x + 3;
					}
				}
			}
			// East
			if (player_dir_east) {
				// If movemement is done, finish up
				if (player_pos.x >= (player_prev_pos.x + 26)) {
					player_pos.x		= player_prev_pos.x + 26;
					player_dir_east = false;
					if (isDeathTile()) {
						player_state = PSDEAD;
						sndObj.playSound(sfxZap);
					} else {
						sndObj.playSound(sfxJump);
					}

          if (player_prev_pos.x == 10 && player_prev_pos.y == 152) {
            cheat_count++;
          } else {
            cheat_count = 0;
          }
				} else { // Otherwise, move the player
					player_pos.x = player_pos.x + 3;
				}
			}
			// West
			if (player_dir_west) {
				// If movemement is done, finish up
				if (player_pos.x <= (player_prev_pos.x - 26)) {
					player_pos.x		= player_prev_pos.x - 26;
					player_dir_west = false;
					if (isDeathTile()) {
						player_state = PSDEAD;
						sndObj.playSound(sfxZap);
					} else {
						sndObj.playSound(sfxJump);
					}
          if (game_mode == gmAdventureGame && levelHintDone && player_prev_pos.x == 36 && player_prev_pos.y == 152) {
            cheat_count++;
            if (cheat_count >= 10) {
              addToScore(1000);
              force_game_over = true;
            }
          } else {
            cheat_count = 0;
          }
				} else { // Otherwise, move the player
					player_pos.x = player_pos.x - 3;
				}
			}
			// South
			if (player_dir_south) {
				// If movemement is done, finish up
				if (player_pos.y >= (player_prev_pos.y + 16)) {
          cheat_count = 0;
					vert_move_count  = 0;
					player_pos.x		 = player_prev_pos.x - 10;
					player_pos.y		 = player_prev_pos.y + 16;
					player_dir_south = false;
					if (isDeathTile()) {
						player_state = PSDEAD;
						sndObj.playSound(sfxZap);
					} else {
						sndObj.playSound(sfxJump);
					}
				} else { // Otherwise, move the player
					player_pos.y = player_pos.y + 3;
					vert_move_count++;
					if (vert_move_count > 1) {
						vert_move_count = 0;
						player_pos.x		= player_pos.x - 3;
					}
				}
			}

		break; }

	} // End of CASE

}


// ****************************************************************************************************************
// KeyUp handler
// ****************************************************************************************************************
void CGame::kuDeathTrap(DWORD dwKey) {

	using namespace ns_DeathTrap;

	// Command button
	if (dwKey == kCommand) {
    miniGameCommandButtonHandler();
	}

	if (!player_dir_north && !player_dir_east && !player_dir_south && !player_dir_west && player_state == PSALIVE) {

		// Handle up movement events
		if (dwKey == kUp) {
			if (move_matrix[player_tile_y][player_tile_x] == NE  ||
					move_matrix[player_tile_y][player_tile_x] == NW  ||
					move_matrix[player_tile_y][player_tile_x] == NES ||
					move_matrix[player_tile_y][player_tile_x] == NSW ||
					move_matrix[player_tile_y][player_tile_x] == NEW ||
					move_matrix[player_tile_y][player_tile_x] == NESW) {
            cheat_count = 0;
						if (player_tile_y == 0 && player_tile_x == 4) {
							player_state = PSWON;
							sndObj.playSound(sfxWin);
							vert_move_count = 0;
						} else {
							player_tile_y--;
							player_prev_pos = player_pos;
							player_dir_north = true;
							player_dir_east  = false;
							player_dir_south = false;
							player_dir_west	 = false;
						}
			}
		}

		// Handle right movement events
		if (dwKey == kRight) {
			if (move_matrix[player_tile_y][player_tile_x] == NE  ||
					move_matrix[player_tile_y][player_tile_x] == ES  ||
					move_matrix[player_tile_y][player_tile_x] == NES ||
					move_matrix[player_tile_y][player_tile_x] == ESW ||
					move_matrix[player_tile_y][player_tile_x] == NEW ||
					move_matrix[player_tile_y][player_tile_x] == NESW) {
						player_tile_x++;
						player_prev_pos = player_pos;
						player_dir_north = false;
						player_dir_east  = true;
						player_dir_south = false;
						player_dir_west	 = false;
			}
		}

		// Handle down movement events
		if (dwKey == kDown) {
			if (move_matrix[player_tile_y][player_tile_x] == ES  ||
					move_matrix[player_tile_y][player_tile_x] == SW  ||
					move_matrix[player_tile_y][player_tile_x] == NES ||
					move_matrix[player_tile_y][player_tile_x] == NSW ||
					move_matrix[player_tile_y][player_tile_x] == ESW ||
					move_matrix[player_tile_y][player_tile_x] == NESW) {
            cheat_count = 0;
						player_tile_y++;
						player_prev_pos = player_pos;
						player_dir_north = false;
						player_dir_east  = false;
						player_dir_south = true;
						player_dir_west	 = false;
			}
		}

		// Handle left movement events
		if (dwKey == kLeft) {
			if (move_matrix[player_tile_y][player_tile_x] == NW  ||
					move_matrix[player_tile_y][player_tile_x] == SW  ||
					move_matrix[player_tile_y][player_tile_x] == NSW ||
					move_matrix[player_tile_y][player_tile_x] == ESW ||
					move_matrix[player_tile_y][player_tile_x] == NEW ||
					move_matrix[player_tile_y][player_tile_x] == NESW) {
						player_tile_x--;
						player_prev_pos = player_pos;
						player_dir_north = false;
						player_dir_east  = false;
						player_dir_south = false;
						player_dir_west	 = true;
			}
		}

	}

}


// ****************************************************************************************************************
// Initialize
// ****************************************************************************************************************
void CGame::initializeDeathTrap() {

	using namespace ns_DeathTrap;

	// Initialize player
	player_pos.x		= 10;
	player_pos.y		= 152;
	vert_move_count = 0;
	player_state		= PSALIVE;
	player_tile_x	  = 1;
	player_tile_y	  = 8;

	// Choose correct path
	if (regen_path) {
		pickCP:
		correct_path = rand() % 9;
		if (correct_path < 0 || correct_path > 8) { goto pickCP; }
		regen_path = false;
	}

	// Counters used to do dieing and winner
	dead_counter  = 0;
	win_counter	 = 0;

}


// ****************************************************************************************************************
// Loader
// ****************************************************************************************************************
void CGame::loadDeathTrap(CGapiSurface* backbuffer) {

	using namespace ns_DeathTrap;

	processEvents = false;

	// Move on to the next step
	loading_step++;

	// Do the appropriate step
	switch(loading_step) {

		case 1: {
			doCommonInit();
      int i = 0;
      for (i = 0; i < 2; i++) { player_dieing[i] = NULL; }
      background      = NULL;
      player_standing = NULL;
      player_jumping  = NULL;
      sfxZap          = NULL;
      sfxWin          = NULL;
      sfxJump         = NULL;
		break; }

		case 2: {
			background       = new CGapiSurface(); createSurface(TEXT("deathtrap : GFX_DEATHTRAP_BACKGROUND"),       background->CreateSurface      (0, m_config.hInstance, GFX_DEATHTRAP_BACKGROUND,       TEXT("GRAPHICS"))); background->SetColorKey      (RGB(255, 128, 255));
			player_standing  = new CGapiSurface(); createSurface(TEXT("deathtrap : GFX_DEATHTRAP_PLAYER_STANDING"),  player_standing->CreateSurface (0, m_config.hInstance, GFX_DEATHTRAP_PLAYER_STANDING,  TEXT("GRAPHICS"))); player_standing->SetColorKey (RGB(255, 128, 255));
			player_jumping   = new CGapiSurface(); createSurface(TEXT("deathtrap : GFX_DEATHTRAP_PLAYER_JUMPING"),   player_jumping->CreateSurface  (0, m_config.hInstance, GFX_DEATHTRAP_PLAYER_JUMPING,   TEXT("GRAPHICS"))); player_jumping->SetColorKey  (RGB(255, 128, 255));
			player_dieing[0] = new CGapiSurface(); createSurface(TEXT("deathtrap : GFX_DEATHTRAP_PLAYER_DIEING_00"), player_dieing[0]->CreateSurface(0, m_config.hInstance, GFX_DEATHTRAP_PLAYER_DIEING_00, TEXT("GRAPHICS"))); player_dieing[0]->SetColorKey(RGB(255, 128, 255));
			player_dieing[1] = new CGapiSurface(); createSurface(TEXT("deathtrap : GFX_DEATHTRAP_PLAYER_DIEING_01"), player_dieing[1]->CreateSurface(0, m_config.hInstance, GFX_DEATHTRAP_PLAYER_DIEING_01, TEXT("GRAPHICS"))); player_dieing[1]->SetColorKey(RGB(255, 128, 255));
			sfxZap           = new hssSound();     loadSFX      (TEXT("deathtrap : SFX_ZAP"),                        sfxZap->load                   (m_config.hInstance,    SFX_ZAP));                                          sfxZap->loop                 (false);
			sfxWin           = new hssSound();     loadSFX      (TEXT("deathtrap : SFX_WIN_2"),                      sfxWin->load                   (m_config.hInstance,    SFX_WIN_2));                                        sfxWin->loop                 (false);
			sfxJump          = new hssSound();     loadSFX      (TEXT("deathtrap : SFX_JUMP"),                       sfxJump->load                  (m_config.hInstance,    SFX_JUMP));                                         sfxJump->loop                (false);
		break; }

		case 3: {
			initializeDeathTrap();
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
void CGame::destroyDeathTrap(CGapiSurface* backbuffer) {

	using namespace ns_DeathTrap;

	processEvents = false;

	// Move on to the next step
	destroying_step++;

	// Do the appropriate step
	switch(destroying_step) {

		case 1: {
			doCommonCleanup();
		break; }

		case 2: {
			delete sfxZap;
			delete sfxWin;
			delete sfxJump;
			delete background;
			delete player_standing;
			delete player_jumping;
			delete player_dieing[0];
			delete player_dieing[1];
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
namespace ns_DeathTrap {


bool isDeathTile() {
	// This function checks the current tile to see if it's a death tile
	// Returns true if it is a death tile, false otherwise
	if (death_matrix[correct_path][player_tile_y][player_tile_x] == 0) {
		return true;
	} else {
		return false;
	}
}


} // End of namespace
