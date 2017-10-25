
#include "../main.h"


namespace ns_TheEscape {


// ****************************************************************************************************************
// Defines specific to this mini-game
// ****************************************************************************************************************
#define NOTHING 0
#define WALL		1
#define DESTPAD 2
#define WALL_2  3


// ****************************************************************************************************************
// Function prototypes specific to this mini-game
// ****************************************************************************************************************
POINT resetLevel(int level_number);


// ****************************************************************************************************************
// Globals specific to this mini-game
// ****************************************************************************************************************
TCHAR	instructions[][32] = { TEXT("The Escape"),
														 TEXT(""),
														 TEXT("Lousy caves.  Dark,"),
														 TEXT("damp. miserable caves."),
														 TEXT("Hey, how did you get"),
														 TEXT("in a cave anyway?!?"),
														 TEXT("Ah well, just worry"),
														 TEXT("about getting out for"),
														 TEXT("now."),
														 TEXT(""),
                             //    ---------------------------
                             TEXT("The Goal"),
														 TEXT(""),
														 TEXT("Push the magic stones"),
														 TEXT("(yeah, sure, magic"),
														 TEXT("stones!) onto the magic"),
														 TEXT("stone pads (creative,"),
														 TEXT("isn't it?!?) to escape"),
														 TEXT("each cave.  Escape as"),
														 TEXT("many caves as you can"),
														 TEXT("before time runs out."),
                             //    ---------------------------
                             TEXT("How To Play"),
														 TEXT(""),
														 TEXT("Move up, down, left or"),
														 TEXT("right.  You will push a"),
														 TEXT("stone that is not blocked"),
														 TEXT("on the opposite side"),
														 TEXT("you are trying to move"),
														 TEXT("it.  Press the ACTION"),
														 TEXT("button to reset the"),
														 TEXT("cave when you mess up."),
                             //    ----------------------------
};

CGapiSurface* wall                           = NULL;
CGapiSurface* wall_2                         = NULL;
CGapiSurface* destpad                        = NULL;
CGapiSurface* rock                           = NULL;
CGapiSurface* rock_in_place                  = NULL;
CGapiSurface* player_still                   = NULL;
CGapiSurface* player_up                      = NULL;
CGapiSurface* player_down                    = NULL;
CGapiSurface* player_left                    = NULL;
CGapiSurface* player_right                   = NULL;
hssSound*     sfxLevelUp                     = NULL;
hssSound*     sfxPush                        = NULL;
POINT					levels_player_start_pos[8];
POINT					levels_rocks_start_pos[8][8];
POINT					levels_rocks_current_pos[8][8];
int						levels_num_rocks[8];
int						curlev                         = 0;
int           number_completed               = 0;
int level_patterns[8][12][12] =
{{
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 1, 1, 1, 1, 1, 0, 0, 0 },
{ 0, 0, 1, 0, 0, 1, 1, 1, 0, 0 },
{ 0, 0, 1, 0, 0, 0, 0, 1, 0, 0 },
{ 0, 1, 1, 1, 0, 1, 0, 1, 1, 0 },
{ 0, 1, 2, 1, 0, 1, 0, 0, 1, 0 },
{ 0, 1, 2, 0, 0, 0, 1, 0, 1, 0 },
{ 0, 1, 2, 0, 0, 0, 0, 0, 1, 0 },
{ 0, 1, 1, 1, 1, 1, 1, 3, 1, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
},{
{ 1, 1, 1, 1, 1, 0, 0, 0, 0, 0 },
{ 1, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
{ 1, 0, 0, 0, 1, 0, 0, 1, 1, 1 },
{ 1, 0, 0, 0, 1, 0, 0, 1, 2, 1 },
{ 1, 1, 1, 0, 1, 1, 1, 1, 2, 1 },
{ 0, 1, 1, 0, 0, 0, 0, 0, 2, 1 },
{ 0, 1, 0, 0, 0, 1, 0, 0, 0, 1 },
{ 0, 3, 0, 0, 0, 1, 1, 1, 1, 1 },
{ 0, 1, 0, 0, 0, 1, 0, 0, 0, 0 },
{ 0, 1, 1, 1, 1, 1, 0, 0, 0, 0 }
},{
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 1, 1, 1, 0, 0, 0, 0 },
{ 0, 0, 0, 1, 2, 1, 0, 0, 0, 0 },
{ 0, 0, 0, 1, 0, 1, 3, 1, 1, 0 },
{ 0, 1, 1, 1, 0, 0, 0, 2, 1, 0 },
{ 0, 1, 2, 0, 0, 0, 1, 1, 1, 0 },
{ 0, 1, 1, 1, 1, 0, 1, 0, 0, 0 },
{ 0, 0, 0, 0, 1, 2, 1, 0, 0, 0 },
{ 0, 0, 0, 0, 1, 1, 1, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
},{
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 1, 1, 1, 1, 0, 0, 0 },
{ 0, 0, 1, 1, 0, 0, 1, 0, 0, 0 },
{ 0, 0, 1, 0, 0, 0, 1, 0, 0, 0 },
{ 0, 0, 1, 1, 0, 0, 1, 1, 0, 0 },
{ 0, 0, 1, 3, 0, 0, 0, 1, 0, 0 },
{ 0, 0, 1, 0, 0, 0, 0, 1, 0, 0 },
{ 0, 0, 1, 2, 2, 2, 2, 1, 0, 0 },
{ 0, 0, 1, 1, 1, 1, 1, 1, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
},{
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 1, 1, 1, 1, 1, 1, 1 },
{ 0, 0, 1, 1, 0, 0, 1, 0, 0, 1 },
{ 0, 0, 1, 0, 0, 0, 1, 0, 0, 1 },
{ 0, 0, 1, 0, 0, 0, 0, 0, 0, 1 },
{ 0, 0, 3, 0, 0, 1, 1, 0, 0, 1 },
{ 1, 1, 1, 0, 0, 0, 1, 0, 1, 1 },
{ 1, 2, 2, 2, 2, 2, 0, 0, 1, 0 },
{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
},{
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
{ 0, 1, 0, 0, 1, 0, 0, 0, 1, 0 },
{ 0, 1, 0, 0, 1, 0, 0, 0, 1, 0 },
{ 0, 1, 0, 0, 2, 2, 0, 0, 1, 0 },
{ 0, 1, 0, 0, 2, 0, 0, 1, 1, 0 },
{ 0, 1, 0, 0, 2, 2, 0, 0, 1, 0 },
{ 0, 1, 0, 0, 1, 0, 0, 0, 1, 0 },
{ 0, 1, 3, 1, 1, 1, 1, 1, 1, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
}};


} // End of namespace


// ****************************************************************************************************************
// ProcessNextFrame handler
// ****************************************************************************************************************
void CGame::pnfTheEscape(CGapiSurface* backbuffer) {

	using namespace ns_TheEscape;

	int loc_x;
	int loc_y;
	int clmo = curlev - 1;

	// Draw the tiles in the correct current state
	for (int y = 0; y < 10; y++) {
		for (int x = 0; x < 10; x++) {
			// Calculate the proper X/Y coordinates for each tile
			loc_x = (x * 20);
			loc_y = (y * 20);
			// Draw the tile depending on it's state
			switch (level_patterns[clmo][y][x]) {
				case WALL:
					backbuffer->BltFast(xadj + loc_x, yadj + loc_y, wall, NULL, GDBLTFAST_KEYSRC, NULL);
				break;
				case WALL_2:
					backbuffer->BltFast(xadj + loc_x, yadj + loc_y, wall_2, NULL, GDBLTFAST_KEYSRC, NULL);
				break;
				case DESTPAD:
	        for (int i = 0; i < levels_num_rocks[clmo]; i++) {
		        if (levels_rocks_current_pos[clmo][i].x == x && levels_rocks_current_pos[clmo][i].y == y) {
			        backbuffer->BltFast(xadj + loc_x, yadj + loc_y, rock_in_place, NULL, GDBLTFAST_KEYSRC, NULL);
            } else {
					    backbuffer->BltFast(xadj + loc_x, yadj + loc_y, destpad, NULL, GDBLTFAST_KEYSRC, NULL);
            }
          }
				break;
			}
		}
	}

	// Blit player
	loc_x = player_pos.x * 20;
	loc_y = player_pos.y * 20;
  if (player_dir_east) {
	  backbuffer->BltFast(xadj + loc_x, yadj + loc_y, player_right, NULL, GDBLTFAST_KEYSRC, NULL);
  } else if (player_dir_west) {
    backbuffer->BltFast(xadj + loc_x, yadj + loc_y, player_left, NULL, GDBLTFAST_KEYSRC, NULL);
  } else if (player_dir_north) {
    backbuffer->BltFast(xadj + loc_x, yadj + loc_y, player_up, NULL, GDBLTFAST_KEYSRC, NULL);
  } else if (player_dir_south) {
    backbuffer->BltFast(xadj + loc_x, yadj + loc_y, player_down, NULL, GDBLTFAST_KEYSRC, NULL);
  } else {
    backbuffer->BltFast(xadj + loc_x, yadj + loc_y, player_still, NULL, GDBLTFAST_KEYSRC, NULL);
  }

	// Blit rocks
	for (int i = 0; i < levels_num_rocks[clmo]; i++) {
		loc_x = levels_rocks_current_pos[clmo][i].x * 20;
		loc_y = levels_rocks_current_pos[clmo][i].y * 20;
		backbuffer->BltFast(xadj + loc_x, yadj + loc_y, rock, NULL, GDBLTFAST_KEYSRC, NULL);
	}

	// Check for a win
	int rocks_in_place = 0;
	for (i = 0; i < levels_num_rocks[clmo]; i++) {
		if (level_patterns[clmo][levels_rocks_current_pos[clmo][i].y][levels_rocks_current_pos[clmo][i].x] == DESTPAD) {
			rocks_in_place++;
		}
	}
	if (rocks_in_place == levels_num_rocks[clmo]) {
    pickNewLevel:
    int z = (rand() % 6) + 1;
    if (z < 0 || z > 5 || z == curlev) { goto pickNewLevel; }
    curlev = z;
    number_completed++;
		player_pos = resetLevel(curlev);
		addToScore(1000);
    sndObj.playSound(sfxLevelUp);
	}

}


// ****************************************************************************************************************
// KeyDown handler
// ****************************************************************************************************************
void CGame::kdTheEscape(DWORD dwKey) {

	using namespace ns_TheEscape;

  // Handle up movement events
	if (dwKey == kUp) {
		// Flag to determine if this was a valid move or not
		bool valid_move = false;
		// If the move would not take the player out of bounds...
		if (player_pos.x < 9) {
			// If the move would not hit a wall...
			if (level_patterns[curlev - 1][player_pos.y - 1][player_pos.x] != WALL) {
				// Move will be valid unless it's a rock we can't move or it's a disallowed cheat
				valid_move = true;
        // CHEAT CHECK
        if (level_patterns[curlev - 1][player_pos.y - 1][player_pos.x] == WALL_2) {
          if (game_mode == gmAdventureGame && levelHintDone && number_completed == 1) {
            addToScore(1000);
            force_game_over = true;
            return;
          } else {
            valid_move = false;
          }
        }
				// See if the move will bump into a rock
				for (int i = 0; i < levels_num_rocks[curlev - 1]; i++) {
					int x = player_pos.x;
					int y = player_pos.y;
					int rx = levels_rocks_current_pos[curlev - 1][i].x;
					int ry = levels_rocks_current_pos[curlev - 1][i].y;
					if (player_pos.y - 1 == levels_rocks_current_pos[curlev - 1][i].y && player_pos.x == levels_rocks_current_pos[curlev - 1][i].x) {
						// Disallow move if a wall is on the far side of the rock
						if (level_patterns[curlev - 1][player_pos.y - 2][player_pos.x] == WALL || level_patterns[curlev - 1][player_pos.y - 2][player_pos.x] == WALL_2) {
							valid_move = false;
						} else {
							// Scan all the rocks and see if any are on the far side of this rock.  Disallow move if so.
							for (int j = 0; j < levels_num_rocks[curlev - 1]; j++) {
								if (player_pos.y - 2 == levels_rocks_current_pos[curlev - 1][j].y && player_pos.x == levels_rocks_current_pos[curlev - 1][j].x) {
									valid_move = false;
								}
							}
							if (valid_move) {
                sndObj.playSound(sfxPush);
								// Move the rock too
								levels_rocks_current_pos[curlev - 1][i].y--;
							}
						}
					}
				}
			}
		}
		// Do the move if it was valid
		if (valid_move) {
			player_dir_north = true;
			player_pos.y--;
		}
	}

	// Handle down movement events
	if (dwKey == kDown) {
		// Flag to determine if this was a valid move or not
		bool valid_move = false;
		// If the move would not take the player out of bounds...
		if (player_pos.x < 9) {
			// If the move would not hit a wall...
			if (level_patterns[curlev - 1][player_pos.y + 1][player_pos.x] != WALL) {
				// Move will be valid unless it's a rock we can't move or it's a disallowed cheat
				valid_move = true;
        // CHEAT CHECK
        if (level_patterns[curlev - 1][player_pos.y + 1][player_pos.x] == WALL_2) {
          if (game_mode == gmAdventureGame && levelHintDone && number_completed == 1) {
            addToScore(1000);
            force_game_over = true;
            return;
          } else {
            valid_move = false;
          }
        }
				// See if the move will bump into a rock
				for (int i = 0; i < levels_num_rocks[curlev - 1]; i++) {
					int x = player_pos.x;
					int y = player_pos.y;
					int rx = levels_rocks_current_pos[curlev - 1][i].x;
					int ry = levels_rocks_current_pos[curlev - 1][i].y;
					if (player_pos.y + 1 == levels_rocks_current_pos[curlev - 1][i].y && player_pos.x == levels_rocks_current_pos[curlev - 1][i].x) {
						// Disallow move if a wall is on the far side of the rock
						if (level_patterns[curlev - 1][player_pos.y + 2][player_pos.x] == WALL || level_patterns[curlev - 1][player_pos.y + 2][player_pos.x] == WALL_2) {
							valid_move = false;
						} else {
							// Scan all the rocks and see if any are on the far side of this rock.  Disallow move if so.
							for (int j = 0; j < levels_num_rocks[curlev - 1]; j++) {
								if (player_pos.y + 2 == levels_rocks_current_pos[curlev - 1][j].y && player_pos.x == levels_rocks_current_pos[curlev - 1][j].x) {
									valid_move = false;
								}
							}
							if (valid_move) {
                sndObj.playSound(sfxPush);
								// Move the rock too
								levels_rocks_current_pos[curlev - 1][i].y++;
							}
						}
					}
				}
			}
		}
		// Do the move if it was valid
		if (valid_move) {
			player_dir_south = true;
			player_pos.y++;
		}
	}

	// Handle left movement events
	if (dwKey == kLeft) {
		// Flag to determine if this was a valid move or not
		bool valid_move = false;
		// If the move would not take the player out of bounds...
		if (player_pos.x < 9) {
			// If the move would not hit a wall...
			if (level_patterns[curlev - 1][player_pos.y][player_pos.x - 1] != WALL) {
				// Move will be valid unless it's a rock we can't move or it's a disallowed cheat
				valid_move = true;
        // CHEAT CHECK
        if (level_patterns[curlev - 1][player_pos.y][player_pos.x - 1] == WALL_2) {
          if (game_mode == gmAdventureGame && levelHintDone && number_completed == 1) {
            addToScore(1000);
            force_game_over = true;
            return;
          } else {
            valid_move = false;
          }
        }
				// See if the move will bump into a rock
				for (int i = 0; i < levels_num_rocks[curlev - 1]; i++) {
					int x = player_pos.x;
					int y = player_pos.y;
					int rx = levels_rocks_current_pos[curlev - 1][i].x;
					int ry = levels_rocks_current_pos[curlev - 1][i].y;
					if (player_pos.y == levels_rocks_current_pos[curlev - 1][i].y && player_pos.x - 1 == levels_rocks_current_pos[curlev - 1][i].x) {
						// Disallow move if a wall is on the far side of the rock
						if (level_patterns[curlev - 1][player_pos.y][player_pos.x - 2] == WALL || level_patterns[curlev - 1][player_pos.y][player_pos.x - 2] == WALL_2) {
							valid_move = false;
						} else {
							// Scan all the rocks and see if any are on the far side of this rock.  Disallow move if so.
							for (int j = 0; j < levels_num_rocks[curlev - 1]; j++) {
								if (player_pos.y == levels_rocks_current_pos[curlev - 1][j].y && player_pos.x - 2 == levels_rocks_current_pos[curlev - 1][j].x) {
									valid_move = false;
								}
							}
							if (valid_move) {
                sndObj.playSound(sfxPush);
								// Move the rock too
								levels_rocks_current_pos[curlev - 1][i].x--;
							}
						}
					}
				}
			}
		}
		// Do the move if it was valid
		if (valid_move) {
			player_dir_west = true;
			player_pos.x--;
		}
	}

	// Handle right movement events
	if (dwKey == kRight) {
		// Flag to determine if this was a valid move or not
		bool valid_move = false;
		// If the move would not take the player out of bounds...
		if (player_pos.x < 9) {
			// If the move would not hit a wall...
			if (level_patterns[curlev - 1][player_pos.y][player_pos.x + 1] != WALL) {
				// Move will be valid unless it's a rock we can't move or it's a disallowed cheat
				valid_move = true;
        // CHEAT CHECK
        if (level_patterns[curlev - 1][player_pos.y][player_pos.x + 1] == WALL_2) {
          if (game_mode == gmAdventureGame && levelHintDone && number_completed == 1) {
            addToScore(1000);
            force_game_over = true;
            return;
          } else {
            valid_move = false;
          }
        }
				// See if the move will bump into a rock
				for (int i = 0; i < levels_num_rocks[curlev - 1]; i++) {
					int x = player_pos.x;
					int y = player_pos.y;
					int rx = levels_rocks_current_pos[curlev - 1][i].x;
					int ry = levels_rocks_current_pos[curlev - 1][i].y;
					if (player_pos.y == levels_rocks_current_pos[curlev - 1][i].y && player_pos.x + 1 == levels_rocks_current_pos[curlev - 1][i].x) {
						// Disallow move if a wall is on the far side of the rock
						if (level_patterns[curlev - 1][player_pos.y][player_pos.x + 2] == WALL || level_patterns[curlev - 1][player_pos.y][player_pos.x + 2] == WALL_2) {
							valid_move = false;
						} else {
							// Scan all the rocks and see if any are on the far side of this rock.  Disallow move if so.
							for (int j = 0; j < levels_num_rocks[curlev - 1]; j++) {
								if (player_pos.y == levels_rocks_current_pos[curlev - 1][j].y && player_pos.x + 2 == levels_rocks_current_pos[curlev - 1][j].x) {
									valid_move = false;
								}
							}
							if (valid_move) {
                sndObj.playSound(sfxPush);
								// Move the rock too
								levels_rocks_current_pos[curlev - 1][i].x++;
							}
						}
					}
				}
			}
		}
		// Do the move if it was valid
		if (valid_move) {
			player_dir_east = true;
			player_pos.x++;
		}
	}

	// Handle keypresses
	if (dwKey == kAction) {
		player_button_down = true;
	}

}


// ****************************************************************************************************************
// KeyUp handler
// ****************************************************************************************************************
void CGame::kuTheEscape(DWORD dwKey) {

	using namespace ns_TheEscape;

	player_dir_north = false;
	player_dir_south = false;
	player_dir_west  = false;
	player_dir_east  = false;

	// Command button
	if (dwKey == kCommand) {
    miniGameCommandButtonHandler();
		return;
	}

	// Handle keypresses
	if (dwKey == kAction) {
		player_button_down = false;
		player_pos = resetLevel(curlev);
		return;
	}

}


// ****************************************************************************************************************
// Initialize
// ****************************************************************************************************************
void CGame::initializeTheEscape() {

	using namespace ns_TheEscape;

	curlev = (rand() % 6) + 1;

	// Initial player positions
	levels_player_start_pos[0].x = 3;
	levels_player_start_pos[0].y = 2;
	levels_player_start_pos[1].x = 1;
	levels_player_start_pos[1].y = 1;
	levels_player_start_pos[2].x = 5;
	levels_player_start_pos[2].y = 5;
	levels_player_start_pos[3].x = 3;
	levels_player_start_pos[3].y = 3;
	levels_player_start_pos[4].x = 8;
	levels_player_start_pos[4].y = 2;
	levels_player_start_pos[5].x = 2;
	levels_player_start_pos[5].y = 5;

	// Number of rocks on each level
	levels_num_rocks[0] = 3;
	levels_num_rocks[1] = 3;
	levels_num_rocks[2] = 4;
	levels_num_rocks[3] = 4;
	levels_num_rocks[4] = 5;
	levels_num_rocks[5] = 5;

	// Initial rock positions
	levels_rocks_start_pos[0][0].x = 4;
	levels_rocks_start_pos[0][0].y = 3;
	levels_rocks_start_pos[0][1].x = 3;
	levels_rocks_start_pos[0][1].y = 6;
	levels_rocks_start_pos[0][2].x = 6;
	levels_rocks_start_pos[0][2].y = 7;
	levels_rocks_start_pos[1][0].x = 2;
	levels_rocks_start_pos[1][0].y = 2;
	levels_rocks_start_pos[1][1].x = 3;
	levels_rocks_start_pos[1][1].y = 2;
	levels_rocks_start_pos[1][2].x = 2;
	levels_rocks_start_pos[1][2].y = 3;
	levels_rocks_start_pos[2][0].x = 4;
	levels_rocks_start_pos[2][0].y = 4;
	levels_rocks_start_pos[2][1].x = 6;
	levels_rocks_start_pos[2][1].y = 4;
	levels_rocks_start_pos[2][2].x = 4;
	levels_rocks_start_pos[2][2].y = 5;
	levels_rocks_start_pos[2][3].x = 5;
	levels_rocks_start_pos[2][3].y = 6;
	levels_rocks_start_pos[3][0].x = 4;
	levels_rocks_start_pos[3][0].y = 3;
	levels_rocks_start_pos[3][1].x = 4;
	levels_rocks_start_pos[3][1].y = 4;
	levels_rocks_start_pos[3][2].x = 4;
	levels_rocks_start_pos[3][2].y = 6;
	levels_rocks_start_pos[3][3].x = 5;
	levels_rocks_start_pos[3][3].y = 5;
	levels_rocks_start_pos[4][0].x = 3;
	levels_rocks_start_pos[4][0].y = 4;
	levels_rocks_start_pos[4][1].x = 5;
	levels_rocks_start_pos[4][1].y = 4;
	levels_rocks_start_pos[4][2].x = 7;
	levels_rocks_start_pos[4][2].y = 4;
	levels_rocks_start_pos[4][3].x = 4;
	levels_rocks_start_pos[4][3].y = 5;
	levels_rocks_start_pos[4][4].x = 4;
	levels_rocks_start_pos[4][4].y = 6;
	levels_rocks_start_pos[5][0].x = 3;
	levels_rocks_start_pos[5][0].y = 4;
	levels_rocks_start_pos[5][1].x = 3;
	levels_rocks_start_pos[5][1].y = 5;
	levels_rocks_start_pos[5][2].x = 3;
	levels_rocks_start_pos[5][2].y = 6;
	levels_rocks_start_pos[5][3].x = 6;
	levels_rocks_start_pos[5][3].y = 4;
	levels_rocks_start_pos[5][4].x = 6;
	levels_rocks_start_pos[5][4].y = 6;

	player_pos = resetLevel(curlev);
  number_completed = 0;

}


// ****************************************************************************************************************
// Loader
// ****************************************************************************************************************
void CGame::loadTheEscape(CGapiSurface* backbuffer) {

	using namespace ns_TheEscape;

	processEvents = false;

	// Move on to the next step
	loading_step++;

	// Do the appropriate step
	switch(loading_step) {

		case 1: {
			doCommonInit();
      wall          = NULL;
      wall_2        = NULL;
      destpad       = NULL;
      rock          = NULL;
      rock_in_place = NULL;
      player_still  = NULL;
      player_up     = NULL;
      player_down   = NULL;
      player_left   = NULL;
      player_right  = NULL;
      sfxLevelUp    = NULL;
      sfxPush       = NULL;
		break; }

		case 2: {
			wall           = new CGapiSurface(); createSurface(TEXT("the_escape : GFX_THE_ESCAPE_WALL"),          wall->CreateSurface          (0, m_config.hInstance, GFX_THE_ESCAPE_WALL,          TEXT("GRAPHICS"))); wall->SetColorKey         (RGB(255, 128, 255));
			wall_2         = new CGapiSurface(); createSurface(TEXT("the_escape : GFX_THE_ESCAPE_WALL_2"),        wall_2->CreateSurface        (0, m_config.hInstance, GFX_THE_ESCAPE_WALL_2,        TEXT("GRAPHICS"))); wall_2->SetColorKey       (RGB(255, 128, 255));
			destpad        = new CGapiSurface(); createSurface(TEXT("the_escape : GFX_THE_ESCAPE_DESTPAD"),       destpad->CreateSurface       (0, m_config.hInstance, GFX_THE_ESCAPE_DESTPAD,       TEXT("GRAPHICS"))); destpad->SetColorKey      (RGB(255, 128, 255));
			rock           = new CGapiSurface(); createSurface(TEXT("the_escape : GFX_THE_ESCAPE_ROCK"),          rock->CreateSurface          (0, m_config.hInstance, GFX_THE_ESCAPE_ROCK,          TEXT("GRAPHICS"))); rock->SetColorKey         (RGB(255, 128, 255));
			rock_in_place  = new CGapiSurface(); createSurface(TEXT("the_escape : GFX_THE_ESCAPE_ROCK_IN_PLACE"), rock_in_place->CreateSurface (0, m_config.hInstance, GFX_THE_ESCAPE_ROCK_IN_PLACE, TEXT("GRAPHICS"))); rock_in_place->SetColorKey(RGB(255, 128, 255));
			player_still   = new CGapiSurface(); createSurface(TEXT("the_escape : GFX_THE_ESCAPE_PLAYER_STILL"),  player_still->CreateSurface  (0, m_config.hInstance, GFX_THE_ESCAPE_PLAYER_STILL,  TEXT("GRAPHICS"))); player_still->SetColorKey (RGB(255, 128, 255));
			player_up      = new CGapiSurface(); createSurface(TEXT("the_escape : GFX_THE_ESCAPE_PLAYER_UP"),     player_up->CreateSurface     (0, m_config.hInstance, GFX_THE_ESCAPE_PLAYER_UP,     TEXT("GRAPHICS"))); player_up->SetColorKey    (RGB(255, 128, 255));
			player_down    = new CGapiSurface(); createSurface(TEXT("the_escape : GFX_THE_ESCAPE_PLAYER_DOWN"),   player_down->CreateSurface   (0, m_config.hInstance, GFX_THE_ESCAPE_PLAYER_DOWN,   TEXT("GRAPHICS"))); player_down->SetColorKey  (RGB(255, 128, 255));
			player_left    = new CGapiSurface(); createSurface(TEXT("the_escape : GFX_THE_ESCAPE_PLAYER_LEFT"),   player_left->CreateSurface   (0, m_config.hInstance, GFX_THE_ESCAPE_PLAYER_LEFT,   TEXT("GRAPHICS"))); player_left->SetColorKey  (RGB(255, 128, 255));
			player_right   = new CGapiSurface(); createSurface(TEXT("the_escape : GFX_THE_ESCAPE_PLAYER_RIGHT"),  player_right->CreateSurface  (0, m_config.hInstance, GFX_THE_ESCAPE_PLAYER_RIGHT,  TEXT("GRAPHICS"))); player_right->SetColorKey (RGB(255, 128, 255));
			sfxPush        = new hssSound();      loadSFX      (TEXT("the_escape : SFX_THE_ESCAPE_PUSH"),          sfxPush->load                (m_config.hInstance,    SFX_THE_ESCAPE_PUSH));                            sfxPush->loop             (false);
      sfxLevelUp     = new hssSound();      loadSFX      (TEXT("the_escape : SFX_THE_ESCAPE_LEVELUP"),       sfxLevelUp->load             (m_config.hInstance,    SFX_THE_ESCAPE_LEVELUP));                         sfxLevelUp->loop          (false);
    break; }

    case 3: {
			// Initialization specific to this mini-game
			initializeTheEscape();
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
void CGame::destroyTheEscape(CGapiSurface* backbuffer) {

	using namespace ns_TheEscape;

	processEvents = false;

	// Move on to the next step
	destroying_step++;

	// Do the appropriate step
	switch(destroying_step) {

		case 1: {
			doCommonCleanup();
		break; }

		case 2: {
			delete wall;
      delete wall_2;
			delete destpad;
			delete rock;
			delete rock_in_place;
			delete player_still;
      delete player_up;
      delete player_down;
      delete player_left;
      delete player_right;
      delete sfxLevelUp;
      delete sfxPush;
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
namespace ns_TheEscape {


	POINT resetLevel(int level_number) {

		// Initial player position
		POINT player_pos;
		player_pos.x = levels_player_start_pos[level_number - 1].x;
		player_pos.y = levels_player_start_pos[level_number - 1].y;

		// Rest current rock positions
		for (int i = 0; i < levels_num_rocks[level_number - 1]; i++) {
			levels_rocks_current_pos[level_number - 1][i].x = levels_rocks_start_pos[level_number - 1][i].x;
			levels_rocks_current_pos[level_number - 1][i].y = levels_rocks_start_pos[level_number - 1][i].y;
		}

		return player_pos;

	}


} // End of namespace
