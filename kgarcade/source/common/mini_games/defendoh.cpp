
#include "../main.h"


namespace ns_Defendoh {


// ****************************************************************************************************************
// Globals specific to this mini-game
// ****************************************************************************************************************
TCHAR	instructions[][32] = { TEXT("Defen'DOH!"),
														 TEXT(""),
														 TEXT("Top Gun in space!  Fly"),
														 TEXT("your fighter over the"),
														 TEXT("alien terrain and"),
														 TEXT("blow up the attacking,"),
														 TEXT("most probably drunk,"),
														 TEXT("UFO's coming at you."),
														 TEXT("Watch for a good place"),
														 TEXT("to eat too!"),
                             //    ---------------------------
                             TEXT("The Goal"),
														 TEXT(""),
														 TEXT("Destroy as many UFO's"),
														 TEXT("as you can.  Each time"),
														 TEXT("you get hit by a UFO"),
														 TEXT("or the ground, it costs"),
														 TEXT("you points, but you come"),
														 TEXT("right back to try again."),
														 TEXT(""),
														 TEXT(""),
                             //    ---------------------------
                             TEXT("How To Play"),
														 TEXT(""),
														 TEXT("Move up and down (it's a"),
														 TEXT("lousy fighter, it can't"),
														 TEXT("move any other way!)"),
														 TEXT("and press ACTION to fire"),
														 TEXT("at the oncoming UFO's."),
														 TEXT(""),
														 TEXT(""),
														 TEXT(""),
                             //    ----------------------------
};

CGapiSurface*	landscape             = NULL;
CGapiSurface*	ship[4];						           // Stores the picture of the ship
CGapiSurface*	alien[4];						           // Stores the picture of the alien ship
CGapiSurface* missile[6];
CGapiSurface* explosion[8];
hssSound*			sfxShip               = NULL;
hssSound*     sfxExplosion          = NULL;
hssSound*     sfxMissileFiring      = NULL;
POINT					alien_pos;					           // Position of alien
POINT					missile_pos;
POINT					alien_exploding_point;
POINT					ship_exploding_point;
RECT					landscape_rect;
bool					sfxShipPlaying        = false;
bool					ship_exploding        = false;
bool					alien_exploding       = false;
bool					missile_fired         = false;
int						alien_frame           = 0;
int						alien_frame_delay     = 0;
int						ship_frame            = 0;
int						ship_frame_delay      = 0;
int           explosion_frame       = 0;
int           explosion_frame_delay = 0;
int           missile_frame         = 0;
int           missile_frame_delay   = 0;
int						stars_x[52];				           // Starfield X coordinates
int						stars_y[52];				           // Starfield Y coordinates
int           sfxShiphssChannel        = 0;


} // End of namespace


// ****************************************************************************************************************
// ProcessNextFrame handler
// ****************************************************************************************************************
void CGame::pnfDefendoh(CGapiSurface* backbuffer) {

	using namespace ns_Defendoh;

	if (!sfxShipPlaying) {
		sfxShipPlaying = true;
		sfxShiphssChannel = sndObj.playSound(sfxShip);
	}

	RECT  destRect;
	POINT colPoint;
	int		ret_val;

	// Starfield
	for (int i = 0; i < 50; i++) {
		// Plot the next star
		backbuffer->SetPixel(xadj + stars_x[i], yadj + stars_y[i], RGB(255, 255, 255));
		backbuffer->SetPixel(xadj + stars_x[i] + 1, yadj + stars_y[i], RGB(255, 255, 255));
		backbuffer->SetPixel(xadj + stars_x[i], yadj + stars_y[i] + 1, RGB(255, 255, 255));
		backbuffer->SetPixel(xadj + stars_x[i] + 1, yadj + stars_y[i] + 1, RGB(255, 255, 255));
	}

	// Blit landscape and update source rect
	backbuffer->BltFast(xadj + 0,	yadj + 100, landscape, &landscape_rect, GDBLTFAST_KEYSRC, NULL);
	landscape_rect.left = landscape_rect.left - 3;
	landscape_rect.right = landscape_rect.right - 3;
	if (landscape_rect.left < 0) {
		landscape_rect.left	= 900;
		landscape_rect.right = 1100;
	}

	// Blit missile, , update animation frame and stop it if off the screen
	if (missile_fired) {
		SetRect(&destRect, xadj + missile_pos.x,			yadj + missile_pos.y,
											 xadj + missile_pos.x + 12, yadj + missile_pos.y + 12);
		GDBLTFX gdbltfx;
		gdbltfx.nRotationAngle = 27000;
		backbuffer->Blt(&destRect, missile[missile_frame], NULL, GDBLT_KEYSRC  | GDBLT_ROTATIONANGLE, &gdbltfx);
		missile_pos.x = missile_pos.x - 4;
		if (missile_pos.x < -16) {
			missile_fired = false;
			missile_pos.x = 154;
		}
		missile_frame_delay++;
		if (missile_frame_delay > 1) {
			missile_frame_delay = 0;
			missile_frame++;
			if (missile_frame > 1) {
				missile_frame = 0;
			}
		}
		// Check for collision with alien, begin explosion if it hits
		if (missile_fired) {
			CGapiSurface::Intersect(xadj + alien_pos.x, yadj + alien_pos.y,
															alien[alien_frame], NULL,
															xadj + missile_pos.x, yadj + missile_pos.y,
															missile[missile_frame], NULL, &colPoint);
			if (colPoint.x != -1 || colPoint.y != -1) {
				sndObj.playSound(sfxExplosion);
				alien_exploding_point = colPoint;
				alien_exploding			  = true;
				missile_fired				  = false;
				missile_pos.x					= 154;
			}
		}
	}

	// Blit ship and take care of player movements (if not exploding)
	backbuffer->BltFast(xadj + player_pos.x, yadj + player_pos.y, ship[ship_frame], NULL, GDBLTFAST_KEYSRC, NULL);
	if (!ship_exploding) {
		ship_frame_delay++;
		if (ship_frame_delay > 1) {
			ship_frame_delay = 0;
			ship_frame++;
			if (ship_frame > 1) { ship_frame = 0; }
		}
		// Moving up
		if (player_dir_north) {
			player_pos.y = player_pos.y - 3;
			// Stop at edge of screen
			if (player_pos.y < 1) { player_pos.y = 1; }
		}
		// Moving down
		if (player_dir_south) {
			player_pos.y = player_pos.y + 3;
		}
	}

	// Blit alien and move it (if not exploding)
	backbuffer->BltFast(xadj + alien_pos.x, yadj + alien_pos.y, alien[alien_frame], NULL, GDBLTFAST_KEYSRC, NULL);
	if (!ship_exploding && !alien_exploding) {
		alien_frame_delay++;
		if (alien_frame_delay > 3) {
			alien_frame_delay = 0;
			alien_frame++;
			if (alien_frame > 1) { alien_frame = 0; }
		}
		// Move the alien across the screen
		alien_pos.x = alien_pos.x + 2;
		if (((rand() % 2) + 1) == 1) {
			alien_pos.y = alien_pos.y - 4;
		} else {
			alien_pos.y = alien_pos.y + 4;
		}
		if (alien_pos.y < 1)		{ alien_pos.y = 1;		}
		if (alien_pos.y > 100) { alien_pos.y = 100; }
		// If we're off the screen, start it at the left at a random vertical position
		if (alien_pos.x > 234) {
			alien_pos.x = -34;
			alien_pos.y = (rand() % 100) + 1; // Y coordinate (1-100)
		}
	}
	// If alien is exploding, do that
	if (alien_exploding) {
		// Stretch explosion to 40 in all directions around point of collision
		SetRect(&destRect, alien_exploding_point.x - 40, alien_exploding_point.y - 40,
											 alien_exploding_point.x + 40, alien_exploding_point.y + 40);
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
		// At the explosion's maximum size, hide the alien
		if (ret_val == 99) {
			alien_pos.x = -200;
		}
		// When the explosion finishes, get on with the game
		if (ret_val == -1) {
			addToScore(25);
			alien_exploding = false;
			// Initial alien position
			alien_pos.x = -34;
			alien_pos.y = (rand() % 100) + 1; // Y coordinate (1-100)
			// Reset missile
			alien_exploding = false;
			missile_fired	  = false;
			missile_pos.x	  = 154;
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
		// At the explosion's maximum size, hide the ship and alien
		if (ret_val == 99) {
			alien_pos.x  = -200;
			player_pos.x = -200;
		}
		// When the explosion finishes, reposition the ship and alien and let us get on with the game
		if (ret_val == -1) {
			subtractFromScore(75);
			explosion_frame	= 0;
			ship_exploding	= false;
			// Start ship at initial coordinates
			player_pos.x = 165;
			player_pos.y = 36;
			// Initial alien position
			alien_pos.x = -34;
			alien_pos.y = (rand() % 100) + 1; // Y coordinate (1-100)
			// Reset missile
			missile_fired = false;
			missile_pos.x = 154;
		}
	} else {
		// See if there is a collision with the alien
		CGapiSurface::Intersect(xadj + alien_pos.x, yadj + alien_pos.y,
														alien[alien_frame], NULL,
														xadj + 165, yadj + player_pos.y,
														ship[ship_frame], NULL, &colPoint);
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
		// See if there is a collission with the landscape
		CGapiSurface::Intersect(xadj + 0, yadj + 100,
														landscape, &landscape_rect,
														xadj + 165, yadj + player_pos.y,
														ship[ship_frame], NULL, &colPoint);
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
void CGame::kdDefendoh(DWORD dwKey) {

	using namespace ns_Defendoh;

	if (!ship_exploding) {

		// Handle up movement events
		if (dwKey == kUp) {
			player_dir_north = true;
			player_dir_south = false;
		}

		// Handle down movement events
		if (dwKey == kDown) {
			player_dir_south = true;
			player_dir_north = false;
		}

		// Handle keypresses
		if (dwKey == kAction) {
			player_button_down = true;
			if (!missile_fired) {
				sndObj.playSound(sfxMissileFiring);
				missile_fired = true;
				missile_pos.y = player_pos.y + 8;
			}
		}

	}

}


// ****************************************************************************************************************
// KeyUp handler
// ****************************************************************************************************************
void CGame::kuDefendoh(DWORD dwKey) {

	using namespace ns_Defendoh;

	// Command button
	if (dwKey == kCommand) {
    hssChannel* c = sndObj.channel(sfxShiphssChannel);
	  if (c->playing()) { c->stop(); }
    sfxShipPlaying = false;
    miniGameCommandButtonHandler();
	}

	if (!ship_exploding) {

		// Handle up movement events
		if (dwKey == kUp) {
			player_dir_north = false;
		}

		// Handle south movement events
		if (dwKey == kDown) {
			player_dir_south = false;
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
void CGame::initializeDefendoh() {

	using namespace ns_Defendoh;

	// Generate initial starfield
	for (int i = 0; i < 50; i++) {
		stars_x[i] = (rand() % 199) + 1;	// X coordinate (1-199)
		stars_y[i] = (rand() % 199) + 1;	// Y coordinate (1-199)
	}

	// Initial landscape source rect
	SetRect(&landscape_rect, 900, 0, 1100, 100);

	// Start ship in the middle
	player_pos.x = 165;
	player_pos.y = 36;

	// missile setup
	missile_fired = false;
	missile_pos.x = 154;

	// Start off with the ship and alien not exploding
	ship_exploding  = false;
	alien_exploding = false;

	// Initial alien position and rotation angle
	alien_pos.x	= -34;
	alien_pos.y	= (rand() % 100) + 1; // Y coordinate (1-100)

	sfxShipPlaying = false;

	alien_frame = 0;
	alien_frame_delay = 0;
	ship_frame = 0;
	ship_frame_delay = 0;

}


// ****************************************************************************************************************
// Ender
// ****************************************************************************************************************
void CGame::endDefendoh() {

	using namespace ns_Defendoh;

  hssChannel* c = sndObj.channel(sfxShiphssChannel);
	if (c->playing()) { c->stop(); }

}


// ****************************************************************************************************************
// Loader
// ****************************************************************************************************************
void CGame::loadDefendoh(CGapiSurface* backbuffer) {

	using namespace ns_Defendoh;

	processEvents = false;

	// Move on to the next step
	loading_step++;

	// Do the appropriate step
	switch(loading_step) {

		case 1: {
			doCommonInit();
      int i = 0;
      for (i = 0; i < 2; i++) { ship[i]      = NULL; }
      for (i = 0; i < 2; i++) { alien[i]     = NULL; }
      for (i = 0; i < 4; i++) { missile[i]   = NULL; }
      for (i = 0; i < 6; i++) { explosion[i] = NULL; }
      landscape        = NULL;
      sfxShip          = NULL;
      sfxExplosion     = NULL;
      sfxMissileFiring = NULL;
		break; }

		case 2: {
			explosion[0]     = new CGapiSurface(); createSurface(TEXT("defendoh : GFX_EXPLOSION_00"),       explosion[0]->CreateSurface(0, m_config.hInstance, GFX_EXPLOSION_00,       TEXT("GRAPHICS"))); explosion[0]->SetColorKey(RGB(255, 128, 255));
			explosion[1]     = new CGapiSurface(); createSurface(TEXT("defendoh : GFX_EXPLOSION_01"),       explosion[1]->CreateSurface(0, m_config.hInstance, GFX_EXPLOSION_01,       TEXT("GRAPHICS"))); explosion[1]->SetColorKey(RGB(255, 128, 255));
			explosion[2]     = new CGapiSurface(); createSurface(TEXT("defendoh : GFX_EXPLOSION_02"),       explosion[2]->CreateSurface(0, m_config.hInstance, GFX_EXPLOSION_02,       TEXT("GRAPHICS"))); explosion[2]->SetColorKey(RGB(255, 128, 255));
			explosion[3]     = new CGapiSurface(); createSurface(TEXT("defendoh : GFX_EXPLOSION_03"),       explosion[3]->CreateSurface(0, m_config.hInstance, GFX_EXPLOSION_03,       TEXT("GRAPHICS"))); explosion[3]->SetColorKey(RGB(255, 128, 255));
			explosion[4]     = new CGapiSurface(); createSurface(TEXT("defendoh : GFX_EXPLOSION_04"),       explosion[4]->CreateSurface(0, m_config.hInstance, GFX_EXPLOSION_04,       TEXT("GRAPHICS"))); explosion[4]->SetColorKey(RGB(255, 128, 255));
			missile[0]       = new CGapiSurface(); createSurface(TEXT("defendoh : GFX_MISSILE_00"),         missile[0]->CreateSurface  (0, m_config.hInstance, GFX_MISSILE_00,         TEXT("GRAPHICS"))); missile[0]->SetColorKey  (RGB(255, 128, 255));
			missile[1]       = new CGapiSurface(); createSurface(TEXT("defendoh : GFX_MISSILE_01"),         missile[1]->CreateSurface  (0, m_config.hInstance, GFX_MISSILE_01,         TEXT("GRAPHICS"))); missile[1]->SetColorKey  (RGB(255, 128, 255));
			landscape        = new CGapiSurface(); createSurface(TEXT("defendoh : GFX_DEFENDOH_LANDSCAPE"), landscape->CreateSurface   (0, m_config.hInstance, GFX_DEFENDOH_LANDSCAPE, TEXT("GRAPHICS"))); landscape->SetColorKey   (RGB(255, 128, 255));
			ship[0]          = new CGapiSurface(); createSurface(TEXT("defendoh : GFX_DEFENDOH_SHIP_00"),   ship[0]->CreateSurface     (0, m_config.hInstance, GFX_DEFENDOH_SHIP_00,   TEXT("GRAPHICS"))); ship[0]->SetColorKey     (RGB(255, 128, 255));
			ship[1]          = new CGapiSurface(); createSurface(TEXT("defendoh : GFX_DEFENDOH_SHIP_01"),   ship[1]->CreateSurface     (0, m_config.hInstance, GFX_DEFENDOH_SHIP_01,   TEXT("GRAPHICS"))); ship[1]->SetColorKey     (RGB(255, 128, 255));
			alien[0]         = new CGapiSurface(); createSurface(TEXT("defendoh : GFX_DEFENDOH_ALIEN_00"),  alien[0]->CreateSurface    (0, m_config.hInstance, GFX_DEFENDOH_ALIEN_00,  TEXT("GRAPHICS"))); alien[0]->SetColorKey    (RGB(255, 128, 255));
			alien[1]         = new CGapiSurface(); createSurface(TEXT("defendoh : GFX_DEFENDOH_ALIEN_01"),  alien[1]->CreateSurface    (0, m_config.hInstance, GFX_DEFENDOH_ALIEN_01,  TEXT("GRAPHICS"))); alien[1]->SetColorKey    (RGB(255, 128, 255));
			sfxShip          = new hssSound();     loadSFX      (TEXT("defendoh : SFX_SHIP"),               sfxShip->load              (m_config.hInstance,    SFX_SHIP));                                 sfxShip->loop            (true);
			sfxExplosion     = new hssSound();     loadSFX      (TEXT("defendoh : SFX_EXPLOSION"),          sfxExplosion->load         (m_config.hInstance,    SFX_EXPLOSION));                            sfxExplosion->loop       (false);
			sfxMissileFiring = new hssSound();     loadSFX      (TEXT("defendoh : SFX_MISSILE_FIRING"),     sfxMissileFiring->load     (m_config.hInstance,    SFX_MISSILE_FIRING));                       sfxMissileFiring->loop   (false);
    break; }

    case 3: {
			initializeDefendoh();
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

	// Show the Loading screen
	showLoadingScreen(backbuffer, true, true);

}


// ****************************************************************************************************************
// Destroyer
// ****************************************************************************************************************
void CGame::destroyDefendoh(CGapiSurface* backbuffer) {

	using namespace ns_Defendoh;

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
			delete landscape;
			delete ship[0];
			delete ship[1];
			delete alien[0];
			delete alien[1];
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
