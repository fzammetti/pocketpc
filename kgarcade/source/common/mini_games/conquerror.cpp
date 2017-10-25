
#include "../main.h"


namespace ns_Conquerror {


// ****************************************************************************************************************
// Globals specific to this mini-game
// ****************************************************************************************************************
TCHAR	instructions[][32] = { TEXT("Conquerror"),
														 TEXT(""),
														 TEXT("Take out your pent-up"),
														 TEXT("aggression on the"),
														 TEXT("innocent inhabitants"),
														 TEXT("of a large alien city"),
														 TEXT("on a world you've never"),
														 TEXT("seen before.  Go ahead,"),
														 TEXT("your human, destruction"),
														 TEXT("comes naturally to you!"),
                             //    ---------------------------
                             TEXT("The Goal"),
														 TEXT(""),
														 TEXT("Fire your missile at the"),
														 TEXT("city to destroy the four"),
														 TEXT("buildings.  They fire"),
														 TEXT("back of course, and"),
														 TEXT("each hit costs you"),
														 TEXT("points."),
														 TEXT(""),
														 TEXT(""),
                             //    ---------------------------
                             TEXT("How To Play"),
														 TEXT(""),
														 TEXT("Move left or right,"),
														 TEXT("and elevate your turret"),
														 TEXT("with up and down.  Press"),
														 TEXT("ACTION to fire.  Note the"),
														 TEXT("elevation number and if"),
														 TEXT("the shot goes behind or"),
														 TEXT("in front of your target"),
														 TEXT("to adjust the next time."),
                             //    ----------------------------
};

CGapiSurface*	background                 = NULL;
CGapiSurface*	gun_top                    = NULL;
CGapiSurface*	gun_bottom                 = NULL;
CGapiSurface*	building[6];
CGapiSurface*	building_destroyed[6];
CGapiSurface* missile[6];
CGapiSurface* explosion[8];
hssSound*     sfxExplosion               = NULL;
hssSound*     sfxMissileFiring           = NULL;
POINT					explosion_pos;
POINT					building_pos[6];
POINT					missile_pos;
POINT					city_missile_pos;
bool					city_missile_ascending     = false;
bool					missile_fired              = false;
bool					missile_ascending          = false;
bool					building_exploding         = false;
bool					city_missile_fired         = false;
bool					building_destroyed_flag[6];
int						building_hit_numbers[6];
int						barrel_delay               = 0;
int						elevation                  = 0;
int						player_hit_number          = 0;
int						fired_elevation            = 0;
int						building_hit               = 0;
int						city_missile_elevation     = 0;
int						player_hit_delay           = 0;
int           explosion_frame            = 0;
int           explosion_frame_delay      = 0;
int           missile_frame              = 0;
int           missile_frame_delay        = 0;
int           missile_building           = 0;
int           city_missile_building      = 0;


} // End of namespace


// ****************************************************************************************************************
// ProcessNextFrame handler
// ****************************************************************************************************************
void CGame::pnfConquerror(CGapiSurface* backbuffer) {

	using namespace ns_Conquerror;

  if (building_destroyed_flag[0] && building_destroyed_flag[1] && building_destroyed_flag[2] && building_destroyed_flag[3]) {
    building_destroyed_flag[0] = false;
    building_destroyed_flag[1] = false;
    building_destroyed_flag[2] = false;
    building_destroyed_flag[3] = false;
  }

	// Blit background
	backbuffer->BltFast(xadj, yadj, background, NULL, GDBLTFAST_KEYSRC, NULL);

  RECT rect;
  rect.left = xadj + missile_pos.x;
  rect.right = xadj + missile_pos.x + missile[0]->GetWidth();
  rect.top = yadj + missile_pos.y;
  rect.bottom = yadj + missile_pos.y + missile[0]->GetHeight();

  // If missile is fired and is coming down and it's elevation puts it behind the building being drawn, draw the missile first
  if (missile_fired && !missile_ascending && fired_elevation > building_hit_numbers[missile_building]) {
	  backbuffer->Blt(&rect, missile[missile_frame], NULL, GDBLTFAST_KEYSRC | GDBLT_MIRRORUPDOWN, NULL);
  }

  // If the city's missile is firing and is ascending and the player delay isn't going, blit the missile now so it's in back
	if (city_missile_fired && player_hit_delay == 0 && city_missile_ascending) {
			backbuffer->BltFast(xadj + city_missile_pos.x, yadj + city_missile_pos.y, missile[missile_frame], NULL, GDBLTFAST_KEYSRC, NULL);
  }

	// Blit buildings
	for (int i = 0; i < 4; i++) {
    // Blit the building in the correct state
		if (!building_destroyed_flag[i]) {
			backbuffer->BltFast(xadj + building_pos[i].x, yadj + building_pos[i].y, building[i], NULL, GDBLTFAST_KEYSRC, NULL);
		} else {
			backbuffer->BltFast(xadj + building_pos[i].x, yadj + building_pos[i].y, building_destroyed[i], NULL, GDBLTFAST_KEYSRC, NULL);
		}
	}

  // Player's missile is firing but it's elevation is too low or just right, so blit it now in front
  if (missile_fired && !missile_ascending && fired_elevation <= building_hit_numbers[missile_building]) {
    backbuffer->Blt(&rect, missile[missile_frame], NULL, GDBLTFAST_KEYSRC | GDBLT_MIRRORUPDOWN, NULL);
  }

  // Player's missile is firing and is ascending, blit it now so it's in front
  if ((missile_fired && missile_ascending)) {
  	backbuffer->BltFast(xadj + missile_pos.x, yadj + missile_pos.y, missile[missile_frame], NULL, GDBLTFAST_KEYSRC, NULL);
  }

  // If the city's missile is firing and is descending and the player delay isn't going, blit the missile now so it's in front
	if (city_missile_fired && player_hit_delay == 0 && !city_missile_ascending) {
	  backbuffer->Blt(CRect(xadj + city_missile_pos.x,		  yadj + city_missile_pos.y,
		 										  xadj + city_missile_pos.x + 6, yadj + city_missile_pos.y + 12),
													missile[missile_frame], NULL, GDBLTFAST_KEYSRC | GDBLT_MIRRORUPDOWN, NULL);
  }

	// Animate missile (applies to both player and city missile)
	if (missile_fired && !building_exploding) {
		missile_frame_delay++;
		if (missile_frame_delay > 1) {
			missile_frame_delay = 0;
			missile_frame++;
			if (missile_frame > 1) {
				missile_frame = 0;
			}
		}
  }

  // Move player's missile
	if (missile_fired && missile_ascending) {
	  missile_pos.y = missile_pos.y - 6;
		if (missile_pos.y < (((fired_elevation * 2) + 12) * -1)) {  missile_ascending = false; }
  }
  if (missile_fired && !missile_ascending) {
	  // Missile is coming down and a building is not exploding
	  missile_pos.y = missile_pos.y + 6;
		POINT colPoint;
		// Start explosion if collision with building
		if (!building_destroyed_flag[missile_building]) {
			CGapiSurface::Intersect(xadj + missile_pos.x, yadj + missile_pos.y,
				  										missile[missile_frame], NULL,
					  									xadj + building_pos[missile_building].x, yadj + building_pos[missile_building].y,
						  								building[missile_building], NULL, &colPoint);
		} else {
			CGapiSurface::Intersect(xadj + missile_pos.x, yadj + missile_pos.y,
															missile[missile_frame], NULL,
															xadj + building_pos[missile_building].x, yadj + building_pos[missile_building].y,
															building_destroyed[missile_building], NULL, &colPoint);
    }
    if (colPoint.x != -1 || colPoint.y != -1) {
			// If the elevation was correct, start the building exploding
			if (fired_elevation == building_hit_numbers[missile_building]) {
				building_hit			 = missile_building;
				building_exploding = true;
				explosion_pos			 = missile_pos;
				addToScore(100);
				sndObj.playSound(sfxExplosion);
			} else {
				// If we hit the horizon and the elevation was too low, do an explosion, but don't kill a building
				if (missile_pos.y > 108 && fired_elevation < building_hit_numbers[missile_building]) {
					building_hit			 = -1;
					building_exploding = true;
					explosion_pos = missile_pos;
					sndObj.playSound(sfxExplosion);
				}
				// If we hit the horizon and the elevation was too high, just stop missile firing, no explosion to show
				if (missile_pos.y > 108 && fired_elevation > building_hit_numbers[missile_building]) {
					missile_fired = false;
					sndObj.playSound(sfxExplosion);
				}
			}
		}
	}

	// If building exploding, do that
	if (building_exploding) {
		RECT destRect;
		SetRect(&destRect, xadj + explosion_pos.x - 40, yadj + explosion_pos.y - 40,
											 xadj + explosion_pos.x + 40, yadj + explosion_pos.y + 40);
		backbuffer->Blt(&destRect, explosion[explosion_frame], NULL, GDBLTFAST_KEYSRC, NULL);
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
		if (ret_val == 99 && building_hit != -1) { // Building exploding, not just a short shot
			building_destroyed_flag[building_hit] = true;
		}
		// Explosion cycle done
		if (ret_val == -1) {
			missile_ascending	 = false;
			missile_fired			 = false;
			building_exploding = false;
		}
	}

	// If city missile is firing and the player wasn't just hit, deal with it
	if (city_missile_fired && player_hit_delay == 0) {
		if (city_missile_ascending) {
			city_missile_pos.y = city_missile_pos.y - 6;
			if (city_missile_pos.y < -50) {
				city_missile_ascending = false;
			}
		} else {
      // Missile is descending
			// When missile reaches bottom of screen, see if the elevation was correct.  If it was, set up to do the temp
			// delay.  If it wan't, adjust if depending on how it compares to the magic number
			city_missile_pos.y = city_missile_pos.y + 6;
			if (city_missile_pos.y > 200) {
				sndObj.playSound(sfxExplosion);
				city_missile_fired = false;
				if (city_missile_elevation > player_hit_number) {
					city_missile_elevation--;
				} else if (city_missile_elevation < player_hit_number) {
					city_missile_elevation++;
				} else if (city_missile_elevation == player_hit_number) {
					city_missile_elevation = 0;
					player_hit_delay			 = 75;
					city_missile_fired		 = false;
					player_dir_north			 = false;
					player_dir_south			 = false;
					player_dir_east				 = false;
					player_dir_west				 = false;
				}
			}
		}
	// City missile NOT fired, go ahead and fire it
	} else {
		if (player_hit_delay == 0) {
			city_missile_fired		 = true;
			int x = 0;;
			pickX:
			x = (rand() % 191) + 1;
			if (x < 0 || x > 191) { goto pickX; }
			city_missile_pos.x		 = x;
			city_missile_pos.y		 = 100;
			city_missile_ascending = true;
			sndObj.playSound(sfxMissileFiring);
			// Missile was not previously fired (or player was hit), so choose a random elevation
			if (city_missile_elevation == 0) {
				int elev = 0;
				pickElev:
				elev = (rand() % 17) + 1;
				if (elev < 1 || elev > 17) { goto pickElev; }
				city_missile_elevation = elev;
				sndObj.playSound(sfxMissileFiring);
			}
		}
	}

	// Blit gun and elevation, and handle movement
	if (player_hit_delay == 0) {
		backbuffer->BltFast(xadj + player_pos.x, yadj + player_pos.y+2, gun_top,		 NULL, GDBLTFAST_KEYSRC, NULL);
		backbuffer->BltFast(xadj + player_pos.x, yadj + 175,					 gun_bottom, NULL, GDBLTFAST_KEYSRC, NULL);
	} else { // Draw the gun in red to denote the just hit delay
		GDBLTFASTFX gdbltfastfx;
		gdbltfastfx.dwFXcolor1 = RGB(255, 0, 0);
		backbuffer->BltFast(xadj + player_pos.x, yadj + player_pos.y+2, gun_top,		 NULL, GDBLTFAST_KEYSRC | GDBLTFASTFX_COLORIZE, &gdbltfastfx);
		backbuffer->BltFast(xadj + player_pos.x, yadj + 175,					 gun_bottom, NULL, GDBLTFAST_KEYSRC | GDBLTFASTFX_COLORIZE, &gdbltfastfx);
	}
	switch (elevation) {
		case 1:  backbuffer->DrawText(player_pos.x + 40, yadj + 175, TEXT("01"), &font1, GDDRAWTEXT_CENTER, NULL, NULL, NULL); break;
		case 2:  backbuffer->DrawText(player_pos.x + 40, yadj + 175, TEXT("02"), &font1, GDDRAWTEXT_CENTER, NULL, NULL, NULL); break;
		case 3:  backbuffer->DrawText(player_pos.x + 40, yadj + 175, TEXT("03"), &font1, GDDRAWTEXT_CENTER, NULL, NULL, NULL); break;
		case 4:  backbuffer->DrawText(player_pos.x + 40, yadj + 175, TEXT("04"), &font1, GDDRAWTEXT_CENTER, NULL, NULL, NULL); break;
		case 5:  backbuffer->DrawText(player_pos.x + 40, yadj + 175, TEXT("05"), &font1, GDDRAWTEXT_CENTER, NULL, NULL, NULL); break;
		case 6:  backbuffer->DrawText(player_pos.x + 40, yadj + 175, TEXT("06"), &font1, GDDRAWTEXT_CENTER, NULL, NULL, NULL); break;
		case 7:  backbuffer->DrawText(player_pos.x + 40, yadj + 175, TEXT("07"), &font1, GDDRAWTEXT_CENTER, NULL, NULL, NULL); break;
		case 8:  backbuffer->DrawText(player_pos.x + 40, yadj + 175, TEXT("08"), &font1, GDDRAWTEXT_CENTER, NULL, NULL, NULL); break;
		case 9:  backbuffer->DrawText(player_pos.x + 40, yadj + 175, TEXT("09"), &font1, GDDRAWTEXT_CENTER, NULL, NULL, NULL); break;
		case 10: backbuffer->DrawText(player_pos.x + 40, yadj + 175, TEXT("10"), &font1, GDDRAWTEXT_CENTER, NULL, NULL, NULL); break;
		case 11: backbuffer->DrawText(player_pos.x + 40, yadj + 175, TEXT("11"), &font1, GDDRAWTEXT_CENTER, NULL, NULL, NULL); break;
		case 12: backbuffer->DrawText(player_pos.x + 40, yadj + 175, TEXT("12"), &font1, GDDRAWTEXT_CENTER, NULL, NULL, NULL); break;
		case 13: backbuffer->DrawText(player_pos.x + 40, yadj + 175, TEXT("13"), &font1, GDDRAWTEXT_CENTER, NULL, NULL, NULL); break;
		case 14: backbuffer->DrawText(player_pos.x + 40, yadj + 175, TEXT("14"), &font1, GDDRAWTEXT_CENTER, NULL, NULL, NULL); break;
		case 15: backbuffer->DrawText(player_pos.x + 40, yadj + 175, TEXT("15"), &font1, GDDRAWTEXT_CENTER, NULL, NULL, NULL); break;
		case 16: backbuffer->DrawText(player_pos.x + 40, yadj + 175, TEXT("16"), &font1, GDDRAWTEXT_CENTER, NULL, NULL, NULL); break;
		case 17: backbuffer->DrawText(player_pos.x + 40, yadj + 175, TEXT("17"), &font1, GDDRAWTEXT_CENTER, NULL, NULL, NULL); break;
	}
	if (player_hit_delay == 0) {
		// Moving right
		if (player_dir_east) {
			player_pos.x = player_pos.x + 3;
			// Stop at edge of screen
			if (player_pos.x > 160) { player_pos.x = 160; }
		}
		// Moving left
		if (player_dir_west) {
			player_pos.x = player_pos.x - 3;
			// Stop at edge of screen
			if (player_pos.x < 0) { player_pos.x = 0; }
		}
		// Barrel moving up
		if (player_dir_north) {
			barrel_delay++;
			if (barrel_delay > 2) {
				barrel_delay = 0;
				player_pos.y--;
				elevation++;
				if (elevation > 17) { elevation = 17; }
				if (player_pos.y < 150) { player_pos.y = 150; }
			}
		}
		// Barrel moving down
		if (player_dir_south) {
			barrel_delay++;
			if (barrel_delay > 2) {
				barrel_delay = 0;
				player_pos.y++;
				elevation--;
				if (elevation < 1) { elevation = 1; }
				if (player_pos.y > 166) { player_pos.y = 166; }
			}
		}
	// If the player was hit, we're decreasing before they can do anything again
	} else {
		player_hit_delay--;
	}

}


// ****************************************************************************************************************
// KeyDown handler
// ****************************************************************************************************************
void CGame::kdConquerror(DWORD dwKey) {

	using namespace ns_Conquerror;

	// Handle left movement events
	if (dwKey == kLeft && player_hit_delay == 0) {
		// We'll only do this if the player wasn't just hit
		player_dir_west	= true;
		player_dir_east	= false;
	}

	// Handle right movement events
	if (dwKey == kRight && player_hit_delay == 0) {
		// We'll only do this if the player wasn't just hit
		player_dir_east	= true;
		player_dir_west	= false;
	}

	// Handle up movement events
	if (dwKey == kUp && player_hit_delay == 0) {
		// We'll only do this if the player wasn't just hit
		player_dir_north = true;
		barrel_delay		 = 99;
	}

	// Handle down movement events
	if (dwKey == kDown && player_hit_delay == 0) {
		// We'll only do this if the player wasn't just hit
		player_dir_south = true;
		barrel_delay		 = 99;
	}

	// Handle keypresses
	if (dwKey == kAction && !missile_fired && player_hit_delay == 0) {
		player_button_down = true;
		// We'll only fire if a missile isn't already flying, and if the player wasn't just hit
		building_hit					= -1;
		missile_fired					= true;
		missile_ascending			= true;
		building_exploding		= false;
		fired_elevation				= elevation;
		missile_pos.x					= player_pos.x + 17;
		missile_pos.y					= player_pos.y;
    // Determine which building the missile is fired at
    int x = missile_pos.x;
    if (x >= 0   && x <= 39)  { missile_building = 0; }
    if (x >= 40  && x <= 109) { missile_building = 1; }
    if (x >= 110 && x <= 139) { missile_building = 2; }
    if (x >= 140 && x <= 200) { missile_building = 3; }
    sndObj.playSound(sfxMissileFiring);
	}

}


// ****************************************************************************************************************
// KeyUp handler
// ****************************************************************************************************************
void CGame::kuConquerror(DWORD dwKey) {

	using namespace ns_Conquerror;

	// Command button
	if (dwKey == kCommand) {
    miniGameCommandButtonHandler();
	}

	// Handle left movement events
	if (dwKey == kLeft) {
		player_dir_west	= false;
	}

	// Handle right movement events
	if (dwKey == kRight) {
		player_dir_east	= false;
	}

	// Handle up movement events
	if (dwKey == kUp) {
		player_dir_north = false;
		barrel_delay		 = 0;
	}

	// Handle down movement events
	if (dwKey == kDown) {
		player_dir_south = false;
		barrel_delay		 = 0;
	}

	// Handle keypresses
	if (dwKey == kAction) {
		player_button_down = false;
	}

}


// ****************************************************************************************************************
// Initialize
// ****************************************************************************************************************
void CGame::initializeConquerror() {

	using namespace ns_Conquerror;

	// Start gun barrel in right place
	player_pos.x = 75;
	player_pos.y = 150;

	// Set delay for moving barrel up or down
	barrel_delay = 0;

	// Set initial barrel elevation
	elevation = 17;

	// Determine the magic number to hit the gun barrel
	player_hit_number = (rand() % 17) + 1;

	// Determine the magic numbers to hit each building
	building_hit_numbers[0] = (rand() % 17) + 1;
	building_hit_numbers[1] = (rand() % 17) + 1;
	building_hit_numbers[2] = (rand() % 17) + 1;
	building_hit_numbers[3] = (rand() % 17) + 1;

	// Start all buildings not destroyed
	building_destroyed_flag[0] = false;
	building_destroyed_flag[1] = false;
	building_destroyed_flag[2] = false;
	building_destroyed_flag[3] = false;

	// Building positions
	building_pos[0].x = 0;   building_pos[0].y = 40;
	building_pos[1].x = 40;  building_pos[1].y = 80;
	building_pos[2].x = 110; building_pos[2].y = 20;
	building_pos[3].x = 140; building_pos[3].y = 70;

	city_missile_fired		 = false;
	city_missile_elevation = 0;
	player_hit_delay			 = 0;
  missile_building       = 0;
  city_missile_building  = 0;

}


// ****************************************************************************************************************
// Loader
// ****************************************************************************************************************
void CGame::loadConquerror(CGapiSurface* backbuffer) {

	using namespace ns_Conquerror;

	processEvents = false;

	// Move on to the next step
	loading_step++;

	// Do the appropriate step
	switch(loading_step) {

		case 1: {
			doCommonInit();
      int i = 0;
      for (i = 0; i < 4; i++) { building[i]           = NULL; }
      for (i = 0; i < 4; i++) { building_destroyed[i] = NULL; }
      for (i = 0; i < 4; i++) { missile[i]            = NULL; }
      for (i = 0; i < 6; i++) { explosion[i]          = NULL; }
      background       = NULL;
      gun_top          = NULL;
      gun_bottom       = NULL;
      sfxExplosion     = NULL;
      sfxMissileFiring = NULL;
		break; }

		case 2: {
			explosion[0]          = new CGapiSurface(); createSurface(TEXT("conquerror : GFX_EXPLOSION_00"),                    explosion[0]->CreateSurface          (0, m_config.hInstance, GFX_EXPLOSION_00,                    TEXT("GRAPHICS"))); explosion[0]->SetColorKey         (RGB(255, 128, 255));
			explosion[1]          = new CGapiSurface(); createSurface(TEXT("conquerror : GFX_EXPLOSION_01"),                    explosion[1]->CreateSurface          (0, m_config.hInstance, GFX_EXPLOSION_01,                    TEXT("GRAPHICS"))); explosion[1]->SetColorKey         (RGB(255, 128, 255));
			explosion[2]          = new CGapiSurface(); createSurface(TEXT("conquerror : GFX_EXPLOSION_02"),                    explosion[2]->CreateSurface          (0, m_config.hInstance, GFX_EXPLOSION_02,                    TEXT("GRAPHICS"))); explosion[2]->SetColorKey         (RGB(255, 128, 255));
			explosion[3]          = new CGapiSurface(); createSurface(TEXT("conquerror : GFX_EXPLOSION_03"),                    explosion[3]->CreateSurface          (0, m_config.hInstance, GFX_EXPLOSION_03,                    TEXT("GRAPHICS"))); explosion[3]->SetColorKey         (RGB(255, 128, 255));
			explosion[4]          = new CGapiSurface(); createSurface(TEXT("conquerror : GFX_EXPLOSION_04"),                    explosion[4]->CreateSurface          (0, m_config.hInstance, GFX_EXPLOSION_04,                    TEXT("GRAPHICS"))); explosion[4]->SetColorKey         (RGB(255, 128, 255));
			missile[0]            = new CGapiSurface(); createSurface(TEXT("conquerror : GFX_MISSILE_00"),                      missile[0]->CreateSurface            (0, m_config.hInstance, GFX_MISSILE_00,                      TEXT("GRAPHICS"))); missile[0]->SetColorKey           (RGB(255, 128, 255));
			missile[1]            = new CGapiSurface(); createSurface(TEXT("conquerror : GFX_MISSILE_01"),                      missile[1]->CreateSurface            (0, m_config.hInstance, GFX_MISSILE_01,                      TEXT("GRAPHICS"))); missile[1]->SetColorKey           (RGB(255, 128, 255));
			background            = new CGapiSurface(); createSurface(TEXT("conquerror : GFX_CONQUERROR_BACKGROUND"),           background->CreateSurface            (0, m_config.hInstance, GFX_CONQUERROR_BACKGROUND,           TEXT("GRAPHICS"))); background->SetColorKey           (RGB(255, 128, 255));
			building[0]           = new CGapiSurface(); createSurface(TEXT("conquerror : GFX_CONQUERROR_BUILDING_1"),           building[0]->CreateSurface           (0, m_config.hInstance, GFX_CONQUERROR_BUILDING_1,           TEXT("GRAPHICS"))); building[0]->SetColorKey          (RGB(255, 128, 255));
			building_destroyed[0] = new CGapiSurface(); createSurface(TEXT("conquerror : GFX_CONQUERROR_BUILDING_1_DESTROYED"), building_destroyed[0]->CreateSurface (0, m_config.hInstance, GFX_CONQUERROR_BUILDING_1_DESTROYED, TEXT("GRAPHICS"))); building_destroyed[0]->SetColorKey(RGB(255, 128, 255));
			building[1]           = new CGapiSurface(); createSurface(TEXT("conquerror : GFX_CONQUERROR_BUILDING_2"),           building[1]->CreateSurface           (0, m_config.hInstance, GFX_CONQUERROR_BUILDING_2,           TEXT("GRAPHICS"))); building[1]->SetColorKey          (RGB(255, 128, 255));
			building_destroyed[1] = new CGapiSurface(); createSurface(TEXT("conquerror : GFX_CONQUERROR_BUILDING_2_DESTROYED"), building_destroyed[1]->CreateSurface (0, m_config.hInstance, GFX_CONQUERROR_BUILDING_2_DESTROYED, TEXT("GRAPHICS"))); building_destroyed[1]->SetColorKey(RGB(255, 128, 255));
			gun_top               = new CGapiSurface(); createSurface(TEXT("conquerror : GFX_CONQUERROR_GUN_TOP"),              gun_top->CreateSurface               (0, m_config.hInstance, GFX_CONQUERROR_GUN_TOP,              TEXT("GRAPHICS"))); gun_top->SetColorKey              (RGB(255, 128, 255));
			gun_bottom            = new CGapiSurface(); createSurface(TEXT("conquerror : GFX_CONQUERROR_GUN_BOTTOM"),           gun_bottom->CreateSurface            (0, m_config.hInstance, GFX_CONQUERROR_GUN_BOTTOM,           TEXT("GRAPHICS"))); gun_bottom->SetColorKey           (RGB(255, 128, 255));
			building[2]           = new CGapiSurface(); createSurface(TEXT("conquerror : GFX_CONQUERROR_BUILDING_3"),           building[2]->CreateSurface           (0, m_config.hInstance, GFX_CONQUERROR_BUILDING_3,           TEXT("GRAPHICS"))); building[2]->SetColorKey          (RGB(255, 128, 255));
			building_destroyed[2] = new CGapiSurface(); createSurface(TEXT("conquerror : GFX_CONQUERROR_BUILDING_3_DESTROYED"), building_destroyed[2]->CreateSurface (0, m_config.hInstance, GFX_CONQUERROR_BUILDING_3_DESTROYED, TEXT("GRAPHICS"))); building_destroyed[2]->SetColorKey(RGB(255, 128, 255));
			building[3]           = new CGapiSurface(); createSurface(TEXT("conquerror : GFX_CONQUERROR_BUILDING_4"),           building[3]->CreateSurface           (0, m_config.hInstance, GFX_CONQUERROR_BUILDING_4,           TEXT("GRAPHICS"))); building[3]->SetColorKey          (RGB(255, 128, 255));
			building_destroyed[3] = new CGapiSurface(); createSurface(TEXT("conquerror : GFX_CONQUERROR_BUILDING_4_DESTROYED"), building_destroyed[3]->CreateSurface (0, m_config.hInstance, GFX_CONQUERROR_BUILDING_4_DESTROYED, TEXT("GRAPHICS"))); building_destroyed[3]->SetColorKey(RGB(255, 128, 255));
			sfxExplosion          = new hssSound();     loadSFX      (TEXT("conquerror : SFX_EXPLOSION"),                       sfxExplosion->load                   (m_config.hInstance,    SFX_EXPLOSION));	                                        sfxExplosion->loop                (false);
			sfxMissileFiring      = new hssSound();     loadSFX      (TEXT("conquerror : SFX_MISSILE_FIRING"),                  sfxMissileFiring->load               (m_config.hInstance,    SFX_MISSILE_FIRING));                                    sfxMissileFiring->loop            (false);
		break; }

		case 3: {
			initializeConquerror();
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
void CGame::destroyConquerror(CGapiSurface* backbuffer) {

	using namespace ns_Conquerror;

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
			delete background;
			delete building[0];
			delete building_destroyed[0];
			delete building[1];
			delete building_destroyed[1];
			delete gun_top;
			delete gun_bottom;
			delete building[2];
			delete building_destroyed[2];
			delete building[3];
			delete building_destroyed[3];
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
