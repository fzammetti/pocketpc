
#include "../main.h"


namespace ns_ADayInTheStrife {


// ****************************************************************************************************************
// Defines specific to this mini-game
// ****************************************************************************************************************
#define SHIELD_OK						 0
#define SHIELD_MINOR_DAMAGE  1
#define SHIELD_MEDIUM_DAMAGE 2
#define SHIELD_SEVER_DAMAGE  3
#define SHIED_GONE           4
#define ALIEN_H_DIR_LEFT		 5
#define ALIEN_H_DIR_RIGHT		 6
#define ALIEN_ALIVE					 7
#define ALIEN_DEAD					 8
#define ALIEN_EXPLODING 		 9
#define ALIEN_RED						 10
#define ALIEN_YELLOW				 11
#define ALIEN_GREEN					 12


// ****************************************************************************************************************
// Globals specific to this mini-game
// ****************************************************************************************************************
TCHAR	instructions[][32] = { TEXT("A Day In The Strife"),
														 TEXT(""),
														 TEXT("Pesky hordes of aliens"),
														 TEXT("keep coming down on you "),
														 TEXT("in never-ending waves."),
														 TEXT("You must fire back and"),
														 TEXT("destroy them, hiding"),
														 TEXT("under your shields as"),
														 TEXT("long as possible.  Don't"),
														 TEXT("let them touch you!"),
                             //    ---------------------------
                             TEXT("The Goal"),
														 TEXT(""),
														 TEXT("Blow up as many bad"),
														 TEXT("guys as you can.  Each"),
                             TEXT("time you get hit will"),
														 TEXT("cost you points, but"),
														 TEXT("you will instantly "),
														 TEXT("come back for"),
														 TEXT("more punishment."),
														 TEXT(""),
                             //    ---------------------------
                             TEXT("How To Play"),
														 TEXT(""),
														 TEXT("Move left or right, hit"),
														 TEXT("the ACTION button to fire."),
														 TEXT(""),
														 TEXT(""),
														 TEXT(""),
														 TEXT(""),
														 TEXT(""),
														 TEXT(""),
                             //    ----------------------------
};

CGapiSurface*	background                = NULL;
CGapiSurface*	ship[4];									         // Stores the picture of the ship
CGapiSurface*	green_alien[4];						         // Stores the animation frames of the aliens
CGapiSurface*	yellow_alien[4];					         // Stores the animation frames of the aliens
CGapiSurface*	red_alien[4];							         // Stores the animation frames of the aliens
CGapiSurface* shield[6];								         // Various versions of the shield
CGapiSurface* missile[6];
CGapiSurface* explosion[8];
hssSound*			sfxTank                   = NULL;
hssSound*     sfxExplosion              = NULL;
hssSound*     sfxMissileFiring          = NULL;
POINT					shield_explosion_pos;
POINT					missile_pos;							         // Coordinates the missile is fired at (UL corner of ship)
POINT					ship_explosion_pos;
POINT					alien_pos[5][8];					         // positions of all our aliens
POINT					alien_explosion_pos[5][8];
POINT					alien_firing_pos[5][8];
POINT					shield_pos[5];						         // Positions of the three shields
bool					tank_sound_playing        = false;
bool					shield_exploding          = false;
bool					ship_exploding            = false; // True when ship is being blown up
bool					missile_fired             = false; // True if the missile has been fired
bool					alien_firing[5][8];
int						ship_frame                = 0;
int						ship_frame_delay          = 0;
int						alien_frame               = 0;     // Index to tell which alien frame to display
int						alien_frame_delay         = 0;     // Slows down the speed of our alien's frame changes
int						alien_move_h_dir          = 0;     // What horizontal direction the aliens are moving in
int						alien_explosion_frame     = 0;
int						aliens_alive              = 0;
int						aliens_firing             = 0;
int           explosion_frame           = 0;
int           explosion_frame_delay     = 0;
int           missile_frame             = 0;
int           missile_frame_delay       = 0;
int						alien_states[5][8];				         // The state each alien is in
int						alien_colors[5][8];
int						shield_states[5];					         // The states of the three shields
int           sfxTankhssChannel         = 0;


} // End of namespace


// ****************************************************************************************************************
// ProcessNextFrame handler
// ****************************************************************************************************************
void CGame::pnfADayInTheStrife(CGapiSurface* backbuffer) {

	using namespace ns_ADayInTheStrife;

	if (!tank_sound_playing) {
		tank_sound_playing = true;
		sfxTankhssChannel = sndObj.playSound(sfxTank);
	}

	RECT  destRect;
	POINT colPoint;

	backbuffer->BltFast(xadj + 0,	yadj + 0, background, NULL, NULL, NULL);

	// Blit the shields in the correct states
	for (int i = 0; i < 3; i++) {
		if (shield_states[i] != SHIED_GONE) {
			backbuffer->BltFast(xadj + shield_pos[i].x,	yadj + shield_pos[i].y, shield[shield_states[i]], NULL, GDBLTFAST_KEYSRC, NULL);
		}
	}

	// Blit ship and take care of player movements (if not exploding)
	backbuffer->BltFast(xadj + player_pos.x, yadj + player_pos.y, ship[ship_frame], NULL, GDBLTFAST_KEYSRC, NULL);
	if (!ship_exploding) {
		// Moving right
		if (player_dir_east) {
			player_pos.x = player_pos.x + 3;
			// Stop at edge of screen
			if (player_pos.x > 167) { player_pos.x = 167; }
		}
		// Moving left
		if (player_dir_west) {
			player_pos.x = player_pos.x - 3;
			// Stop at edge of screen
			if (player_pos.x < 1) { player_pos.x = 1; }
		}
		if (player_dir_east || player_dir_west) {
			ship_frame_delay++;
			if (ship_frame_delay > 1) {
				ship_frame_delay = 0;
				ship_frame++;
				if (ship_frame > 1) {
					ship_frame = 0;
				}
			}
		}
	} else { // Ship is exploding, do that
		// Stretch explosion to 40 in all directions around point of collision
		SetRect(&destRect, ship_explosion_pos.x - 40, ship_explosion_pos.y - 40,
											 ship_explosion_pos.x + 40, ship_explosion_pos.y + 40);
		backbuffer->Blt(&destRect, explosion[explosion_frame], NULL, GDBLTFAST_KEYSRC, NULL);
		explosion_frame++;
		// When the explosion finishes, get on with the game
		if (explosion_frame > 4) {
			initializeADayInTheStrife();
		}
	}

	// Blit missile, , update animation frame and stop it if off the screen
	if (missile_fired) {
		backbuffer->BltFast(xadj + missile_pos.x,	yadj + missile_pos.y, missile[missile_frame], NULL, GDBLTFAST_KEYSRC, NULL);
		missile_pos.y = missile_pos.y - 4;
		if (missile_pos.y < -16) {
			missile_fired = false;
			missile_pos.y = 162;
		}
		// Check for collision with shields, destroy it a little if it hits
		for (int j = 0; j < 3; j++) {
			if (shield_states[j] != SHIED_GONE) { // Only check shields that are still there
				CGapiSurface::Intersect(xadj + shield_pos[j].x, yadj + shield_pos[j].y,
																shield[shield_states[j]], NULL,
																xadj + missile_pos.x, yadj + missile_pos.y,
																missile[missile_frame], NULL, &colPoint);
				if (colPoint.x != -1 || colPoint.y != -1) {
					sndObj.playSound(sfxExplosion);
					missile_fired				 = false;
					missile_pos.y				 = 162;
					shield_explosion_pos = colPoint;
					shield_exploding		 = true;
					shield_states[j]++;
					if (shield_states[j] > SHIED_GONE) {
						shield_states[j] = SHIED_GONE;
					}
				}
			}
		}
	}

	// If a shield is exploding, blit the explosion
	if (shield_exploding) {
		// Stretch explosion to 40 in all directions around point of collision
		SetRect(&destRect, shield_explosion_pos.x - 40, shield_explosion_pos.y - 40,
											 shield_explosion_pos.x + 40, shield_explosion_pos.y + 40);
		backbuffer->Blt(&destRect, explosion[explosion_frame], NULL, GDBLTFAST_KEYSRC, NULL);
		explosion_frame++;
		// When the explosion finishes, get on with the game
		if (explosion_frame > 4) {
			shield_exploding = false;
			explosion_frame	 = 0;
		}
	}

	// Blit and move the aliens
	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 6; x++) {
			if (alien_states[y][x] == ALIEN_ALIVE) {
        if (alien_pos[y][x].y > 180) { // Alien reached the bottom, reset
          initializeADayInTheStrife();
          return;
        }
				if (alien_colors[y][x] == ALIEN_YELLOW) {
					backbuffer->BltFast(xadj + alien_pos[y][x].x,	yadj + alien_pos[y][x].y, yellow_alien[alien_frame], NULL, GDBLTFAST_KEYSRC, NULL);
				}
				if (alien_colors[y][x] == ALIEN_GREEN) {
					backbuffer->BltFast(xadj + alien_pos[y][x].x,	yadj + alien_pos[y][x].y, green_alien[alien_frame], NULL, GDBLTFAST_KEYSRC, NULL);
				}
				if (alien_colors[y][x] == ALIEN_RED) {
					backbuffer->BltFast(xadj + alien_pos[y][x].x,	yadj + alien_pos[y][x].y, red_alien[alien_frame], NULL, GDBLTFAST_KEYSRC, NULL);
				}
				// Check for a collision with missile, it applicable
				if (missile_fired) {
					if (alien_colors[y][x] == ALIEN_YELLOW) {
						CGapiSurface::Intersect(xadj + alien_pos[y][x].x, yadj + alien_pos[y][x].y,
																		yellow_alien[alien_frame], NULL,
																		xadj + missile_pos.x, yadj + missile_pos.y,
																		missile[missile_frame], NULL, &colPoint);
					}
					if (alien_colors[y][x] == ALIEN_GREEN) {
						CGapiSurface::Intersect(xadj + alien_pos[y][x].x, yadj + alien_pos[y][x].y,
																		green_alien[alien_frame], NULL,
																		xadj + missile_pos.x, yadj + missile_pos.y,
																		missile[missile_frame], NULL, &colPoint);
					}
					if (alien_colors[y][x] == ALIEN_RED) {
						CGapiSurface::Intersect(xadj + alien_pos[y][x].x, yadj + alien_pos[y][x].y,
																		red_alien[alien_frame], NULL,
																		xadj + missile_pos.x, yadj + missile_pos.y,
																		missile[missile_frame], NULL, &colPoint);
					}
					if (colPoint.x != -1 || colPoint.y != -1) {
						sndObj.playSound(sfxExplosion);
						alien_explosion_pos[y][x] = colPoint;
						alien_states[y][x] = ALIEN_EXPLODING;
						addToScore(25);
						missile_fired	= false;
						missile_pos.y	= 162;
						// Check if all aliens dead.  If so, restart.
						bool all_dead = true;
						for (int y1 = 0; y1 < 3; y1++) {
							for (int x1 = 0; x1 < 6; x1++) {
								if (alien_states[y1][x1] == ALIEN_ALIVE) {
									all_dead = false;
								}
							}
						}
						if (all_dead) {
							initializeADayInTheStrife();
						}
					}
				}
			}
			// If alien is exploding, do that
			if (alien_states[y][x] == ALIEN_EXPLODING) {
				SetRect(&destRect, alien_explosion_pos[y][x].x - 40, alien_explosion_pos[y][x].y - 40,
													 alien_explosion_pos[y][x].x + 40, alien_explosion_pos[y][x].y + 40);
				backbuffer->Blt(&destRect, explosion[alien_explosion_frame], NULL, GDBLTFAST_KEYSRC, NULL);
				alien_explosion_frame++;
				// When the explosion finishes, get rid of the alien
				if (alien_explosion_frame > 4) {
					alien_states[y][x] = ALIEN_DEAD;
					alien_explosion_frame	= 0;
					aliens_alive--;
				}
			}
			// Move either left or right
			if (alien_frame_delay == 0) {
				int inc_val;
				if (aliens_alive >= 1 && aliens_alive < 5) {
					inc_val = 6;
				}
				if (aliens_alive >= 5 && aliens_alive < 10) {
					inc_val = 5;
				}
				if (aliens_alive >= 10 && aliens_alive < 15) {
					inc_val = 4;
				}
				if (aliens_alive >= 15 && aliens_alive < 20) {
					inc_val = 3;
				}
				if (aliens_alive >= 20 && aliens_alive < 25) {
					inc_val = 2;
				}
				if (aliens_alive >= 25 && aliens_alive <= 30) {
					inc_val = 1;
				}
				if (alien_move_h_dir == ALIEN_H_DIR_LEFT) {
					alien_pos[y][x].x = alien_pos[y][x].x - inc_val;
				} else {
					alien_pos[y][x].x = alien_pos[y][x].x + inc_val;
				}
				// If we reach a bounds on either side, change directions and move them down a bit
				if (alien_pos[0][0].x < 2) {
					alien_move_h_dir = ALIEN_H_DIR_RIGHT;
					alien_pos[y][x].y = alien_pos[y][x].y + 12;
				}
				if (alien_pos[0][0].x > 22) {
					alien_move_h_dir = ALIEN_H_DIR_LEFT;
					alien_pos[y][x].y = alien_pos[y][x].y + 12;
				}
				// Check for collision with shield.  If a hit, completely destroy shield
				for (int k = 0; k < 3; k++) {
					if (shield_states[k] != SHIED_GONE&& alien_states[y][x] != ALIEN_DEAD) { // Only check shields that are still there and aliens that are still there
						if (alien_colors[y][x] == ALIEN_YELLOW) {
							CGapiSurface::Intersect(xadj + alien_pos[y][x].x, yadj + alien_pos[y][x].y,
																			yellow_alien[alien_frame], NULL,
																			xadj + shield_pos[k].x, yadj + shield_pos[k].y,
																			shield[shield_states[k]], NULL, &colPoint);
						}
						if (alien_colors[y][x] == ALIEN_GREEN) {
							CGapiSurface::Intersect(xadj + alien_pos[y][x].x, yadj + alien_pos[y][x].y,
																			green_alien[alien_frame], NULL,
																			xadj + shield_pos[k].x, yadj + shield_pos[k].y,
																			shield[shield_states[k]], NULL, &colPoint);
						}
						if (alien_colors[y][x] == ALIEN_RED) {
							CGapiSurface::Intersect(xadj + alien_pos[y][x].x, yadj + alien_pos[y][x].y,
																			red_alien[alien_frame], NULL,
																			xadj + shield_pos[k].x, yadj + shield_pos[k].y,
																			shield[shield_states[k]], NULL, &colPoint);
						}
						if (colPoint.x != -1 || colPoint.y != -1) {
							sndObj.playSound(sfxExplosion);
							shield_states[k] = SHIED_GONE;
						}
					}
				}
				// Check for collision with ship
				if (!ship_exploding && alien_states[y][x] != ALIEN_DEAD) {
					if (alien_colors[y][x] == ALIEN_YELLOW) {
						CGapiSurface::Intersect(xadj + alien_pos[y][x].x, yadj + alien_pos[y][x].y,
																		yellow_alien[alien_frame], NULL,
																		xadj + player_pos.x, yadj + player_pos.y,
																		ship[ship_frame], NULL, &colPoint);
					}
					if (alien_colors[y][x] == ALIEN_GREEN) {
						CGapiSurface::Intersect(xadj + alien_pos[y][x].x, yadj + alien_pos[y][x].y,
																		green_alien[alien_frame], NULL,
																		xadj + player_pos.x, yadj + player_pos.y,
																		ship[ship_frame], NULL, &colPoint);
					}
					if (alien_colors[y][x] == ALIEN_RED) {
						CGapiSurface::Intersect(xadj + alien_pos[y][x].x, yadj + alien_pos[y][x].y,
																		red_alien[alien_frame], NULL,
																		xadj + player_pos.x, yadj + player_pos.y,
																		ship[ship_frame], NULL, &colPoint);
					}
					if (colPoint.x != -1 || colPoint.y != -1) {
						sndObj.playSound(sfxExplosion);
						ship_explosion_pos = colPoint;
						ship_exploding		 = true;
						player_dir_east		 = false;
						player_dir_west		 = false;
						explosion_frame		 = 0;
						subtractFromScore(50);
					}
				}
			}
		}
	}
	// Slow down the frame change
	alien_frame_delay = alien_frame_delay + 3;
	if (alien_frame_delay > aliens_alive / 2) {
		alien_frame_delay = 0;
		alien_frame++;
		if (alien_frame > 1) { alien_frame = 0; }
	}

	// For each alien, check if it's firing.  If so, blit it and check for collision with ship
	for (int y1 = 0; y1 < 3; y1++) {
		for (int x1 = 0; x1 < 6; x1++) {
			if (alien_states[y1][x1] != ALIEN_DEAD && alien_firing[y1][x1]) {
				backbuffer->Blt(CRect(xadj + alien_firing_pos[y1][x1].x, yadj + alien_firing_pos[y1][x1].y,
																xadj + alien_firing_pos[y1][x1].x + 6, yadj + alien_firing_pos[y1][x1].y + 12),
																missile[missile_frame], NULL, GDBLTFAST_KEYSRC | GDBLT_MIRRORUPDOWN , NULL);
				alien_firing_pos[y1][x1].y = alien_firing_pos[y1][x1].y + 3;
				if (alien_firing_pos[y1][x1].y > 216) {
					alien_firing[y1][x1] = false;
					aliens_firing--;
				}
				// Check for collision with shields, destroy it a little if it hits
				for (int j1 = 0; j1 < 3; j1++) {
					if (shield_states[j1] != SHIED_GONE) { // Only check shields that are still there
						CGapiSurface::Intersect(xadj + shield_pos[j1].x, yadj + shield_pos[j1].y,
																		shield[shield_states[j1]], NULL,
																		xadj + alien_firing_pos[y1][x1].x, yadj + alien_firing_pos[y1][x1].y,
																		missile[missile_frame], NULL, &colPoint);
						if (colPoint.x != -1 || colPoint.y != -1) {
							//sndObj.playSound(sfxExplosion);
							alien_firing[y1][x1] = false;
							aliens_firing--;
						}
					}
				}

				// Check for collision with ship
				if (!ship_exploding) {
					CGapiSurface::Intersect(xadj + alien_firing_pos[y1][x1].x, yadj + alien_firing_pos[y1][x1].y,
																	missile[missile_frame], NULL,
																	xadj + player_pos.x, yadj + player_pos.y,
																	ship[ship_frame], NULL, &colPoint);
					if (colPoint.x != -1 || colPoint.y != -1) {
						sndObj.playSound(sfxExplosion);
						ship_explosion_pos = colPoint;
						ship_exploding		 = true;
						player_dir_east		 = false;
						player_dir_west		 = false;
						explosion_frame		 = 0;
						subtractFromScore(50);
					}
				}

			}
		}
	}

	// Make sure there's always two aliens firing
	while (aliens_firing < 2) {
		aliens_firing++;
		int x = 0;
		int y = 0;
		pickAlien:
		y = rand() % 3;
		x = rand() % 5;
		if (y < 0 || y > 2) { goto pickAlien; }
		if (x < 0 || y > 4) { goto pickAlien; }
		if (alien_states[y][x] == ALIEN_DEAD) { goto pickAlien; }
		alien_firing[y][x] = true;
		alien_firing_pos[y][x].x = alien_pos[y][x].x + 12;
		alien_firing_pos[y][x].y = alien_pos[y][x].y + 20;
	}

	missile_frame_delay++;
	if (missile_frame_delay > 1) {
		missile_frame_delay = 0;
		missile_frame++;
		if (missile_frame > 1) {
			missile_frame = 0;
		}
	}

}


// ****************************************************************************************************************
// KeyDown handler
// ****************************************************************************************************************
void CGame::kdADayInTheStrife(DWORD dwKey) {

	using namespace ns_ADayInTheStrife;

	if (!ship_exploding) {

		// Handle left movement events
		if (dwKey == kLeft) {
			player_dir_west	= true;
			player_dir_east	= false;
		}

		// Handle right movement events
		if (dwKey == kRight) {
			player_dir_east	= true;
			player_dir_west	= false;
		}

		// Handle keypresses
		if (dwKey == kAction) {
			player_button_down = true;
			sndObj.playSound(sfxMissileFiring);
			missile_fired = true;
			missile_pos.x = player_pos.x + 14;
			missile_pos.y	= 162;
		}

	}

}


// ****************************************************************************************************************
// KeyUp handler
// ****************************************************************************************************************
void CGame::kuADayInTheStrife(DWORD dwKey) {

	using namespace ns_ADayInTheStrife;

	// Command button
	if (dwKey == kCommand) {
    hssChannel* c = sndObj.channel(sfxTankhssChannel);
	  if (c->playing()) { c->stop(); }
    tank_sound_playing = false;
    miniGameCommandButtonHandler();
	}

	if (!ship_exploding) {

		// Handle left movement events
		if (dwKey == kLeft) {
			player_dir_west	= false;
		}

		// Handle right movement events
		if (dwKey == kRight) {
			player_dir_east	= false;
		}

		// Handle keypresses
		if (dwKey == kAction) {
			player_button_down = false;
		}

	}

}


// ****************************************************************************************************************
// Initialize
// ****************************************************************************************************************
void CGame::initializeADayInTheStrife() {

	using namespace ns_ADayInTheStrife;

	// Start ship in the middle
	player_pos.x  = 84;
	player_pos.y  = 166;
	ship_frame	  = 0;

	// missile setup
	missile_fired = false;
	missile_pos.y = 162;

	// Start off with the ship not exploding
	ship_exploding = false;

	// Start shields off at full strength and positioned properly
	shield_states[0] = SHIELD_OK;
	shield_states[1] = SHIELD_OK;
	shield_states[2] = SHIELD_OK;
	shield_pos[0].x  = 25;
	shield_pos[0].y  = 120;
	shield_pos[1].x  = 85;
	shield_pos[1].y  = 120;
	shield_pos[2].x  = 145;
	shield_pos[2].y  = 120;
	shield_exploding = false;

	// Initial positions of our aliens
	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 6; x++) {
			alien_pos[y][x].x  = 12 + (x * 30);
			alien_pos[y][x].y  = 4  + (y * 30);
			alien_states[y][x] = ALIEN_ALIVE;
			alien_firing[y][x] = false;
			if (y == 0) {
				alien_colors[y][x] = ALIEN_YELLOW;
			}
			if (y == 1) {
				alien_colors[y][x] = ALIEN_GREEN;
			}
			if (y == 2) {
				alien_colors[y][x] = ALIEN_RED;
			}
		}
	}

	alien_frame					  = 0;
	alien_frame_delay		  = 0;
	alien_move_h_dir		  = ALIEN_H_DIR_LEFT;
	aliens_alive				  = 30;
	alien_explosion_frame = 0;
	aliens_firing				  = 0;
	ship_frame_delay			= 0;
	missile_frame				  = 0;
	missile_frame_delay   = 0;
	explosion_frame       = 0;
	explosion_frame_delay = 0;

}


// ****************************************************************************************************************
// Ender
// ****************************************************************************************************************
void CGame::endADayInTheStrife() {

	using namespace ns_ADayInTheStrife;

  hssChannel* c = sndObj.channel(sfxTankhssChannel);
	if (c->playing()) { c->stop(); }

}


// ****************************************************************************************************************
// Loader
// ****************************************************************************************************************
void CGame::loadADayInTheStrife(CGapiSurface* backbuffer) {

	using namespace ns_ADayInTheStrife;

	processEvents = false;

	// Move on to the next step
	loading_step++;

	// Do the appropriate step
	switch(loading_step) {

		case 1: {
			doCommonInit();
      background = NULL;
      int i = 0;
      for (i = 0; i < 2; i++) { ship[i]         = NULL; }
      for (i = 0; i < 2; i++) { green_alien[i]  = NULL; }
      for (i = 0; i < 2; i++) { yellow_alien[i] = NULL; }
      for (i = 0; i < 2; i++) { red_alien[i]    = NULL; }
      for (i = 0; i < 4; i++) { shield[i]       = NULL; }
      for (i = 0; i < 4; i++) { missile[i]      = NULL; }
      for (i = 0; i < 6; i++) { explosion[i]    = NULL; }
      sfxTank          = NULL;
      sfxExplosion     = NULL;
      sfxMissileFiring = NULL;
    break; }

		case 2: {
			explosion[0]     = new CGapiSurface(); createSurface(TEXT("a_day_in_the_strife : GFX_EXPLOSION_00"),                        explosion[0]->CreateSurface   (0, m_config.hInstance, GFX_EXPLOSION_00,                        TEXT("GRAPHICS"))); explosion[0]->SetColorKey   (RGB(255, 128, 255));
			explosion[1]     = new CGapiSurface(); createSurface(TEXT("a_day_in_the_strife : GFX_EXPLOSION_01"),                        explosion[1]->CreateSurface   (0, m_config.hInstance, GFX_EXPLOSION_01,                        TEXT("GRAPHICS"))); explosion[1]->SetColorKey   (RGB(255, 128, 255));
			explosion[2]     = new CGapiSurface(); createSurface(TEXT("a_day_in_the_strife : GFX_EXPLOSION_02"),                        explosion[2]->CreateSurface   (0, m_config.hInstance, GFX_EXPLOSION_02,                        TEXT("GRAPHICS"))); explosion[2]->SetColorKey   (RGB(255, 128, 255));
			explosion[3]     = new CGapiSurface(); createSurface(TEXT("a_day_in_the_strife : GFX_EXPLOSION_03"),                        explosion[3]->CreateSurface   (0, m_config.hInstance, GFX_EXPLOSION_03,                        TEXT("GRAPHICS"))); explosion[3]->SetColorKey   (RGB(255, 128, 255));
			explosion[4]     = new CGapiSurface(); createSurface(TEXT("a_day_in_the_strife : GFX_EXPLOSION_04"),                        explosion[4]->CreateSurface   (0, m_config.hInstance, GFX_EXPLOSION_04,                        TEXT("GRAPHICS"))); explosion[4]->SetColorKey   (RGB(255, 128, 255));
			missile[0]       = new CGapiSurface(); createSurface(TEXT("a_day_in_the_strife : GFX_MISSILE_00"),                          missile[0]->CreateSurface     (0, m_config.hInstance, GFX_MISSILE_00,                          TEXT("GRAPHICS"))); missile[0]->SetColorKey     (RGB(255, 128, 255));
			missile[1]       = new CGapiSurface(); createSurface(TEXT("a_day_in_the_strife : GFX_MISSILE_01"),                          missile[1]->CreateSurface     (0, m_config.hInstance, GFX_MISSILE_01,                          TEXT("GRAPHICS"))); missile[1]->SetColorKey     (RGB(255, 128, 255));
			ship[0]          = new CGapiSurface(); createSurface(TEXT("a_day_in_the_strife : GFX_A_DAY_IN_THE_STRIFE_SHIP_00"),         ship[0]->CreateSurface        (0, m_config.hInstance, GFX_A_DAY_IN_THE_STRIFE_SHIP_00,         TEXT("GRAPHICS"))); ship[0]->SetColorKey        (RGB(255, 128, 255));
			ship[1]          = new CGapiSurface(); createSurface(TEXT("a_day_in_the_strife : GFX_A_DAY_IN_THE_STRIFE_SHIP_01"),         ship[1]->CreateSurface        (0, m_config.hInstance, GFX_A_DAY_IN_THE_STRIFE_SHIP_01,         TEXT("GRAPHICS"))); ship[1]->SetColorKey        (RGB(255, 128, 255));
			background       = new CGapiSurface(); createSurface(TEXT("a_day_in_the_strife : GFX_A_DAY_IN_THE_STRIFE_BACKGROUND"),      background->CreateSurface     (0, m_config.hInstance, GFX_A_DAY_IN_THE_STRIFE_BACKGROUND,      TEXT("GRAPHICS"))); background->SetColorKey     (RGB(255, 128, 255));
      shield[0]        = new CGapiSurface(); createSurface(TEXT("a_day_in_the_strife : GFX_A_DAY_IN_THE_STRIFE_SHIELD_00"),       shield[0]->CreateSurface      (0, m_config.hInstance, GFX_A_DAY_IN_THE_STRIFE_SHIELD_00,       TEXT("GRAPHICS"))); shield[0]->SetColorKey      (RGB(255, 128, 255));
			shield[1]        = new CGapiSurface(); createSurface(TEXT("a_day_in_the_strife : GFX_A_DAY_IN_THE_STRIFE_SHIELD_01"),       shield[1]->CreateSurface      (0, m_config.hInstance, GFX_A_DAY_IN_THE_STRIFE_SHIELD_01,       TEXT("GRAPHICS"))); shield[1]->SetColorKey      (RGB(255, 128, 255));
			shield[2]        = new CGapiSurface(); createSurface(TEXT("a_day_in_the_strife : GFX_A_DAY_IN_THE_STRIFE_SHIELD_02"),       shield[2]->CreateSurface      (0, m_config.hInstance, GFX_A_DAY_IN_THE_STRIFE_SHIELD_02,       TEXT("GRAPHICS"))); shield[2]->SetColorKey      (RGB(255, 128, 255));
			shield[3]        = new CGapiSurface(); createSurface(TEXT("a_day_in_the_strife : GFX_A_DAY_IN_THE_STRIFE_SHIELD_03"),       shield[3]->CreateSurface      (0, m_config.hInstance, GFX_A_DAY_IN_THE_STRIFE_SHIELD_03,       TEXT("GRAPHICS"))); shield[3]->SetColorKey      (RGB(255, 128, 255));
			green_alien[0]   = new CGapiSurface(); createSurface(TEXT("a_day_in_the_strife : GFX_A_DAY_IN_THE_STRIFE_GREEN_ALIEN_00"),  green_alien[0]->CreateSurface (0, m_config.hInstance, GFX_A_DAY_IN_THE_STRIFE_GREEN_ALIEN_00,  TEXT("GRAPHICS"))); green_alien[0]->SetColorKey (RGB(255, 128, 255));
			green_alien[1]   = new CGapiSurface(); createSurface(TEXT("a_day_in_the_strife : GFX_A_DAY_IN_THE_STRIFE_GREEN_ALIEN_01"),  green_alien[1]->CreateSurface (0, m_config.hInstance, GFX_A_DAY_IN_THE_STRIFE_GREEN_ALIEN_01,  TEXT("GRAPHICS"))); green_alien[1]->SetColorKey (RGB(255, 128, 255));
			yellow_alien[0]  = new CGapiSurface(); createSurface(TEXT("a_day_in_the_strife : GFX_A_DAY_IN_THE_STRIFE_YELLOW_ALIEN_00"), yellow_alien[0]->CreateSurface(0, m_config.hInstance, GFX_A_DAY_IN_THE_STRIFE_YELLOW_ALIEN_00, TEXT("GRAPHICS"))); yellow_alien[0]->SetColorKey(RGB(255, 128, 255));
			yellow_alien[1]  = new CGapiSurface(); createSurface(TEXT("a_day_in_the_strife : GFX_A_DAY_IN_THE_STRIFE_YELLOW_ALIEN_01"), yellow_alien[1]->CreateSurface(0, m_config.hInstance, GFX_A_DAY_IN_THE_STRIFE_YELLOW_ALIEN_01, TEXT("GRAPHICS"))); yellow_alien[1]->SetColorKey(RGB(255, 128, 255));
			red_alien[0]     = new CGapiSurface(); createSurface(TEXT("a_day_in_the_strife : GFX_A_DAY_IN_THE_STRIFE_RED_ALIEN_00"),    red_alien[0]->CreateSurface   (0, m_config.hInstance, GFX_A_DAY_IN_THE_STRIFE_RED_ALIEN_00,    TEXT("GRAPHICS"))); red_alien[0]->SetColorKey   (RGB(255, 128, 255));
			red_alien[1]     = new CGapiSurface(); createSurface(TEXT("a_day_in_the_strife : GFX_A_DAY_IN_THE_STRIFE_RED_ALIEN_01"),    red_alien[1]->CreateSurface   (0, m_config.hInstance, GFX_A_DAY_IN_THE_STRIFE_RED_ALIEN_01,    TEXT("GRAPHICS"))); red_alien[1]->SetColorKey   (RGB(255, 128, 255));
			sfxTank          = new hssSound();     loadSFX      (TEXT("a_day_in_the_strife : SFX_TANK"),                                sfxTank->load                 (m_config.hInstance,    SFX_TANK));                                                  sfxTank->loop               (true);
			sfxExplosion     = new hssSound();     loadSFX      (TEXT("a_day_in_the_strife : SFX_EXPLOSION"),                           sfxExplosion->load            (m_config.hInstance,    SFX_EXPLOSION));                                             sfxExplosion->loop          (false);
			sfxMissileFiring = new hssSound();     loadSFX      (TEXT("a_day_in_the_strife : SFX_MISSILE_FIRING"),                      sfxMissileFiring->load        (m_config.hInstance,    SFX_MISSILE_FIRING));                                        sfxMissileFiring->loop      (false);
		break; }

    case 3: {
      initializeADayInTheStrife();
      for (int i = 0; i < 30; i++) { _tcscpy(mgInstructions[i], instructions[i]); } mgInstructionsPage = 0; mgiPrevTapped = false; mgiNextTapped = false;
      tank_sound_playing = false;
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
void CGame::destroyADayInTheStrife(CGapiSurface* backbuffer) {

	using namespace ns_ADayInTheStrife;

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
			delete missile[0];
			delete missile[1];
			delete sfxExplosion;
			delete sfxMissileFiring;
			delete sfxTank;
			delete ship[0];
			delete ship[1];
			delete background;
			delete shield[0];
			delete shield[1];
			delete shield[2];
			delete shield[3];
			delete red_alien[0];
			delete red_alien[1];
			delete yellow_alien[0];
			delete yellow_alien[1];
			delete green_alien[0];
			delete green_alien[1];
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

