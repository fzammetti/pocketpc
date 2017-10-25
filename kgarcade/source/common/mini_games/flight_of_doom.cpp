
#include "../main.h"


namespace ns_FlightOfDoom {


// ****************************************************************************************************************
// Globals specific to this mini-game
// ****************************************************************************************************************
TCHAR	instructions[][32] = { TEXT("Flight Of Doom"),
														 TEXT(""),
														 TEXT("It seemed so simple:"),
														 TEXT("fly your spaceship to"),
														 TEXT("the galactic core to"),
														 TEXT("pick up milk.  You"),
														 TEXT("should have paid more"),
														 TEXT("attention to the asteroid"),
														 TEXT("weather reports."),
														 TEXT(""),
                             //    ---------------------------
                             TEXT("The Goal"),
														 TEXT(""),
														 TEXT("Keep blowing up"),
														 TEXT("asteroids without"),
														 TEXT("getting hit."),
														 TEXT(""),
														 TEXT(""),
														 TEXT(""),
														 TEXT(""),
														 TEXT(""),
                             //    ---------------------------
                             TEXT("How To Play"),
														 TEXT(""),
														 TEXT("Move your ship left or"),
														 TEXT("right and press ACTION"),
														 TEXT("to shoot."),
														 TEXT(""),
														 TEXT(""),
														 TEXT(""),
														 TEXT(""),
														 TEXT(""),
                             //    ----------------------------
};

CGapiSurface*	ship                    = NULL; // Stores the picture of the ship
CGapiSurface*	asteroid                = NULL; // Stores the picture of the asteroid
CGapiSurface* missile[6];
CGapiSurface* explosion[8];
hssSound*     sfxExplosion            = NULL;
hssSound*     sfxMissileFiring        = NULL;
hssSound*			sfxShip                 = NULL;
POINT					asteroid_pos;						         // X/Y coordinates of asteroid
POINT					ship_exploding_point;		         // Stores the point a collision occurred at
POINT					missile_pos;						         // Coordinates the missile is fired at (UL corner of ship)
POINT					asteroid_exploding_point;        // Stores the point a collision occurred at
bool					ship_exploding          = false; // True when ship is being blown up
bool					missile_fired           = false; // True if the missile has been fired
bool					asteroid_exploding      = false; // True if missile hit asteroid and asteroid is exploding
bool					sfxShipPlaying          = false;
int           explosion_frame         = 0;
int           explosion_frame_delay   = 0;
int           missile_frame           = 0;
int           missile_frame_delay     = 0;
int						stars_x[52];							       // Starfield X coordinates
int						stars_y[52];							       // Starfield Y coordinates
int						stars_v[52];							       // Starfield velocities
int           sfxShiphssChannel       = 0;
long					asteroid_rotation_angle = 0;     // Used to rotate asteroid


} // End of namespace


// ****************************************************************************************************************
// ProcessNextFrame handler
// ****************************************************************************************************************
void CGame::pnfFlightOfDoom(CGapiSurface* backbuffer) {

	using namespace ns_FlightOfDoom;

	if (!sfxShipPlaying) {
		sfxShipPlaying = true;
		sfxShiphssChannel = sndObj.playSound(sfxShip);
	}

	POINT colPoint;
	int	  ret_val;

	// Starfield
	for (int i = 0; i < 50; i++) {
		// Plot the next star
		backbuffer->SetPixel(xadj + stars_x[i], yadj + stars_y[i], RGB(255, 255, 255));
		backbuffer->SetPixel(xadj + stars_x[i] + 1, yadj + stars_y[i], RGB(255, 255, 255));
		backbuffer->SetPixel(xadj + stars_x[i], yadj + stars_y[i] + 1, RGB(255, 255, 255));
		backbuffer->SetPixel(xadj + stars_x[i] + 1, yadj + stars_y[i] + 1, RGB(255, 255, 255));
		// ... Move the star down the screen
		stars_y[i] = stars_y[i] + stars_v[i];
		// Regenerate stars that move off the bottom
		if (stars_y[i] > 200) {
			stars_x[i] = (rand() % 199) + 1;	// X coordinate (1-199)
			stars_y[i] = -1;									// Y coordinate (off top of screen)
			stars_v[i] = (rand() % 5)	  + 2;	// Velocity (2-5)
		}
	}

	// Blit missile, , update animation frame and stop it if off the screen
	if (missile_fired) {
		backbuffer->BltFast(xadj + missile_pos.x,			yadj + missile_pos.y, missile[missile_frame], NULL, GDBLTFAST_KEYSRC, NULL);
		backbuffer->BltFast(xadj + missile_pos.x + 24, yadj + missile_pos.y, missile[missile_frame], NULL, GDBLTFAST_KEYSRC, NULL);
		missile_pos.y = missile_pos.y - 4;
		if (missile_pos.y < -16) {
			missile_fired = false;
			missile_pos.y = 162;
		}
		missile_frame_delay++;
		if (missile_frame_delay > 1) {
			missile_frame_delay = 0;
			missile_frame++;
			if (missile_frame > 1) {
				missile_frame = 0;
			}
		}
		// Check for collision with asteroid, begin explosion if it hits
		if (missile_fired) {
			// Check the left missile
			CGapiSurface::Intersect(xadj + asteroid_pos.x, yadj + asteroid_pos.y,
															asteroid, NULL,
															xadj + missile_pos.x, yadj + missile_pos.y,
															missile[missile_frame], NULL, &colPoint);
			if (colPoint.x != -1 || colPoint.y != -1) {
				sndObj.playSound(sfxExplosion);
				asteroid_exploding_point = colPoint;
				asteroid_exploding			 = true;
				missile_fired						 = false;
				missile_pos.y						 = 162;
			}
			// Check the right missile
			CGapiSurface::Intersect(xadj + asteroid_pos.x, yadj + asteroid_pos.y,
															asteroid, NULL,
															xadj + missile_pos.x + 24, yadj + missile_pos.y,
															missile[missile_frame], NULL, &colPoint);
			if (colPoint.x != -1 || colPoint.y != -1) {
				sndObj.playSound(sfxExplosion);
				asteroid_exploding_point = colPoint;
				asteroid_exploding			 = true;
				missile_fired						 = false;
				missile_pos.y						 = 162;
			}
		}
	}

	// Blit ship and take care of player movements (if not exploding)
	backbuffer->BltFast(xadj + player_pos.x, yadj + player_pos.y, ship, NULL, GDBLTFAST_KEYSRC, NULL);
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
	}

	// Blit asteroid and move it (if not exploding) - 32 is height & width
	RECT destRect;
	SetRect(&destRect, xadj + asteroid_pos.x,			 yadj + asteroid_pos.y,
										 xadj + asteroid_pos.x + 32, yadj + asteroid_pos.y + 32);
	GDBLTFX gdbltfx;
	gdbltfx.nRotationAngle = asteroid_rotation_angle;
	backbuffer->Blt(&destRect, asteroid, NULL, GDBLT_KEYSRC  | GDBLT_ROTATIONANGLE, &gdbltfx);
	if (!ship_exploding && !asteroid_exploding) {
		// Rotate 360 degrees in 1/100th of a degree increments
		asteroid_rotation_angle = asteroid_rotation_angle + 360;
		if (asteroid_rotation_angle > 36000) {
			asteroid_rotation_angle = 0;
		}
		// Move the asteroid down the screen
		asteroid_pos.y = asteroid_pos.y + 6;
		// If we're off the screen, start it at the top at a random horizontal position
		if (asteroid_pos.y > 234) {
			asteroid_pos.x = (rand() % 168) + 1; // X coordinate (1-168)
			asteroid_pos.y = -34;
		}
	}
	// If asteroid is exploding, do that
	if (asteroid_exploding) {
		// Stretch explosion to 40 in all directions around point of collision
		SetRect(&destRect, asteroid_exploding_point.x - 40, asteroid_exploding_point.y - 40,
											 asteroid_exploding_point.x + 40, asteroid_exploding_point.y + 40);
		backbuffer->Blt(&destRect, explosion[explosion_frame], NULL, GDBLTFAST_KEYSRC, NULL);
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
		// At the explosion's maximum size, hide the asteroid
		if (ret_val == 99) {
			asteroid_pos.x = -200;
		}
		// When the explosion finishes, get on with the game
		if (ret_val == -1) {
			addToScore(50);
			explosion_frame		 = 0;
			asteroid_exploding = false;
			// Initial asteroid position
			asteroid_pos.x = (rand() % 168) + 1; // X coordinate (1-168)
			asteroid_pos.y = -34;
			// Reset missile
			asteroid_exploding = false;
			missile_fired			 = false;
			missile_pos.y			 = 162;
		}
	}

	// If the ship is exploding, do that, otherwise check for a collision
	if (ship_exploding) {
		// Stretch explosion to 40 in all directions around point of collision
		SetRect(&destRect, ship_exploding_point.x - 40, ship_exploding_point.y - 40,
											 ship_exploding_point.x + 40, ship_exploding_point.y + 40);
		backbuffer->Blt(&destRect, explosion[explosion_frame], NULL, GDBLTFAST_KEYSRC, NULL);
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
		// At the explosion's maximum size, hide the ship and asteroid
		if (ret_val == 99) {
			asteroid_pos.x = -200;
			player_pos.x	 = -200;
		}
		// When the explosion finishes, reposition the ship and asteroid and let us get on with the game
		if (ret_val == -1) {
			subtractFromScore(250);
			ship_exploding = false;
			// Start ship in the middle
			player_pos.x = 84;
			// Initial asteroid position
			asteroid_pos.x = (rand() % 168) + 1; // X coordinate (1-168)
			asteroid_pos.y = -34;
			// Reset missile
			missile_fired = false;
			missile_pos.y = 162;
		}
	} else {
		// See if there is a collision
		CGapiSurface::Intersect(xadj + asteroid_pos.x, yadj + asteroid_pos.y,
														asteroid, NULL,
														xadj + player_pos.x, yadj + 166,
														ship, NULL, &colPoint);
		if (colPoint.x != -1 || colPoint.y != -1) {
			sndObj.playSound(sfxExplosion);
			ship_exploding			 = true;
			ship_exploding_point = colPoint;
			// Make sure all movements cease too
			player_dir_north		 = false;
			player_dir_south		 = false;
			player_dir_east			 = false;
			player_dir_west			 = false;
		}
	}

}


// ****************************************************************************************************************
// KeyDown handler
// ****************************************************************************************************************
void CGame::kdFlightOfDoom(DWORD dwKey) {

	using namespace ns_FlightOfDoom;

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
			if (!missile_fired) {
				sndObj.playSound(sfxMissileFiring);
				missile_fired = true;
				missile_pos.x = player_pos.x + 1;
			}
		}

	}

}



// ****************************************************************************************************************
// KeyUp handler
// ****************************************************************************************************************
void CGame::kuFlightOfDoom(DWORD dwKey) {

	using namespace ns_FlightOfDoom;

	// Command button
	if (dwKey == kCommand) {
    hssChannel* c = sndObj.channel(sfxShiphssChannel);
	  if (c->playing()) { c->stop(); }
    sfxShipPlaying = false;
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
void CGame::initializeFlightOfDoom() {

	using namespace ns_FlightOfDoom;

	// Generate initial starfield
	for (int i = 0; i < 50; i++) {
		stars_x[i] = (rand() % 199) + 1;	// X coordinate (1-199)
		stars_y[i] = (rand() % 199) + 1;	// Y coordinate (1-199)
		stars_v[i] = (rand() % 4)	 + 1;	// Velocity (1-4)
	}

	// Start ship in the middle
	player_pos.x = 84;
	player_pos.y = 166;

	// Initial asteroid position and rotation angle
	asteroid_pos.x					= (rand() % 168) + 1; // X coordinate (1-168)
	asteroid_pos.y				 	= -34;
	asteroid_rotation_angle = 0;
	asteroid_exploding			= false;

	// missile setup
	missile_fired = false;
	missile_pos.y = 162;

	// Start off with the ship not exploding
	ship_exploding = false;

	sfxShipPlaying = false;

}


// ****************************************************************************************************************
// Ender
// ****************************************************************************************************************
void CGame::endFlightOfDoom() {

	using namespace ns_FlightOfDoom;

  hssChannel* c = sndObj.channel(sfxShiphssChannel);
	if (c->playing()) { c->stop(); }

}


// ****************************************************************************************************************
// Loader
// ****************************************************************************************************************
void CGame::loadFlightOfDoom(CGapiSurface* backbuffer) {

	using namespace ns_FlightOfDoom;

	processEvents = false;

	// Move on to the next step
	loading_step++;

	// Do the appropriate step
	switch(loading_step) {

		case 1: {
			doCommonInit();
      int i = 0;
      for (i = 0; i < 4; i++) { missile[i]   = NULL; }
      for (i = 0; i < 6; i++) { explosion[i] = NULL; }
      ship             = NULL;
      asteroid         = NULL;
      sfxExplosion     = NULL;
      sfxMissileFiring = NULL;
      sfxShip          = NULL;
		break; }

		case 2: {
			explosion[0]     = new CGapiSurface(); createSurface(TEXT("flight_of_doom : GFX_EXPLOSION_00"),            explosion[0]->CreateSurface(0, m_config.hInstance, GFX_EXPLOSION_00,            TEXT("GRAPHICS"))); explosion[0]->SetColorKey(RGB(255, 128, 255));
			explosion[1]     = new CGapiSurface(); createSurface(TEXT("flight_of_doom : GFX_EXPLOSION_01"),            explosion[1]->CreateSurface(0, m_config.hInstance, GFX_EXPLOSION_01,            TEXT("GRAPHICS"))); explosion[1]->SetColorKey(RGB(255, 128, 255));
			explosion[2]     = new CGapiSurface(); createSurface(TEXT("flight_of_doom : GFX_EXPLOSION_02"),            explosion[2]->CreateSurface(0, m_config.hInstance, GFX_EXPLOSION_02,            TEXT("GRAPHICS"))); explosion[2]->SetColorKey(RGB(255, 128, 255));
			explosion[3]     = new CGapiSurface(); createSurface(TEXT("flight_of_doom : GFX_EXPLOSION_03"),            explosion[3]->CreateSurface(0, m_config.hInstance, GFX_EXPLOSION_03,            TEXT("GRAPHICS"))); explosion[3]->SetColorKey(RGB(255, 128, 255));
			explosion[4]     = new CGapiSurface(); createSurface(TEXT("flight_of_doom : GFX_EXPLOSION_04"),            explosion[4]->CreateSurface(0, m_config.hInstance, GFX_EXPLOSION_04,            TEXT("GRAPHICS"))); explosion[4]->SetColorKey(RGB(255, 128, 255));
			missile[0]       = new CGapiSurface(); createSurface(TEXT("flight_of_doom : GFX_MISSILE_00"),              missile[0]->CreateSurface  (0, m_config.hInstance, GFX_MISSILE_00,              TEXT("GRAPHICS"))); missile[0]->SetColorKey  (RGB(255, 128, 255));
			missile[1]       = new CGapiSurface(); createSurface(TEXT("flight_of_doom : GFX_MISSILE_01"),              missile[1]->CreateSurface  (0, m_config.hInstance, GFX_MISSILE_01,              TEXT("GRAPHICS"))); missile[1]->SetColorKey  (RGB(255, 128, 255));
 		  ship             = new CGapiSurface(); createSurface(TEXT("flight_of_doom : GFX_FLIGHT_OF_DOOM_SHIP"),     ship->CreateSurface        (0, m_config.hInstance, GFX_FLIGHT_OF_DOOM_SHIP,     TEXT("GRAPHICS"))); ship->SetColorKey        (RGB(255, 128, 255));
			asteroid         = new CGapiSurface(); createSurface(TEXT("flight_of_doom : GFX_FLIGHT_OF_DOOM_ASTEROID"), asteroid->CreateSurface    (0, m_config.hInstance, GFX_FLIGHT_OF_DOOM_ASTEROID, TEXT("GRAPHICS"))); asteroid->SetColorKey    (RGB(255, 128, 255));
			sfxShip          = new hssSound();     loadSFX      (TEXT("flight_of_doom : SFX_SHIP"),                    sfxShip->load              (m_config.hInstance,    SFX_SHIP));                                      sfxShip->loop            (true);
			sfxExplosion     = new hssSound();     loadSFX      (TEXT("flight_of_doom : SFX_EXPLOSION"),               sfxExplosion->load         (m_config.hInstance,    SFX_EXPLOSION));                                 sfxExplosion->loop       (false);
			sfxMissileFiring = new hssSound();     loadSFX      (TEXT("flight_of_doom : SFX_MISSILE_FIRING"),          sfxMissileFiring->load     (m_config.hInstance,    SFX_MISSILE_FIRING));                            sfxMissileFiring->loop   (false);
    break; }

    case 3: {
			initializeFlightOfDoom();
      for (int i = 0; i < 30; i++) { _tcscpy(mgInstructions[i], instructions[i]); } mgInstructionsPage = 0; mgiPrevTapped = false; mgiNextTapped = false;
			missile_frame				  = 0;
			missile_frame_delay   = 0;
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

	showLoadingScreen(backbuffer, true, true);

}


// ****************************************************************************************************************
// Destroyer
// ****************************************************************************************************************
void CGame::destroyFlightOfDoom(CGapiSurface* backbuffer) {

	using namespace ns_FlightOfDoom;

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
			delete sfxShip;
			delete ship;
			delete asteroid;
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
