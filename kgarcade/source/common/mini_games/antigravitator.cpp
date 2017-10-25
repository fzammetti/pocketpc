
#include "../main.h"


namespace ns_Antigravitator {


// ****************************************************************************************************************
// Defines specific to this mini-game
// ****************************************************************************************************************
#define enemyAlive		 1
#define enemyExploding 2
#define enemyDead      3


// ****************************************************************************************************************
// Function prototypes specific to this mini-game
// ****************************************************************************************************************
void positionEnemy(int enemy_number);


// ****************************************************************************************************************
// Globals specific to this mini-game
// ****************************************************************************************************************
TCHAR	instructions[][32] = { TEXT("Antigravitator"),
														 TEXT(""),
														 TEXT("Now you get to play the"),
														 TEXT("bad guy!  You are the"),
														 TEXT("gunner at an alien"),
														 TEXT("prison, and the inmates"),
														 TEXT("are making a run for it"),
														 TEXT("with the help of their"),
														 TEXT("ship-having buddies."),
														 TEXT("Give 'em hell, chief!"),
                             //    ---------------------------
                             TEXT("The Goal"),
														 TEXT(""),
														 TEXT("Shoot as many escaping"),
														 TEXT("inmates as you can."),
														 TEXT("Each alien that makes it"),
														 TEXT("to the ship costs you"),
														 TEXT("points."),
														 TEXT(""),
														 TEXT(""),
														 TEXT(""),
                             //    ---------------------------
                             TEXT("How To Play"),
														 TEXT(""),
														 TEXT("Move up and down,"),
														 TEXT("press ACTION to fire.  Each"),
														 TEXT("time you fire, your gun"),
														 TEXT("will recharge for a"),
														 TEXT("second and you will be"),
														 TEXT("unable to move, so plan"),
														 TEXT("your shots if you can!"),
														 TEXT(""),
                             //    ----------------------------
};

CGapiSurface*	gun = NULL;
CGapiSurface*	laser = NULL;
CGapiSurface*	gravpit[4];
CGapiSurface*	enemy[4];
CGapiSurface* explosion[8];
CGapiSurface*	ship[8];
hssSound*     sfxExplosion                     = NULL;
hssSound*     sfxMissileFiring                 = NULL;
POINT					laser_pos;
POINT					enemies_pos[7];
bool					laser_fired                      = 0;
int						ship_frame                       = 0;
int						ship_frame_delay                 = 0;
int						enemy_frame                      = 0;
int						enemy_frame_delay                = 0;
int						gravpit_frame                    = 0;
int						gravpit_frame_delay              = 0;
int           explosion_frame                  = 0;
int           explosion_frame_delay            = 0;
int           missile_frame                    = 0;
int           missile_frame_delay              = 0;
int						enemies_speed[7];
int						enemies_explosion_frame[7];
int						enemies_explosion_frame_delay[7];
int						enemies_status[7];


} // End of namespace


// ****************************************************************************************************************
// ProcessNextFrame handler
// ****************************************************************************************************************
void CGame::pnfAntigravitator(CGapiSurface* backbuffer) {

	using namespace ns_Antigravitator;

	// Blit laser, if applicable, and handle movement
	if (laser_fired) {
		backbuffer->BltFast(xadj + laser_pos.x, yadj + laser_pos.y - 1, laser, NULL, GDBLTFAST_KEYSRC, NULL);
		laser_pos.x = laser_pos.x + 18;
		if (laser_pos.x > 200) {
			laser_fired = false;
		}
	}

	// Blit enemies and deal with them
	for (int i = 0; i < 5; i++) {
		// Blit any enemy that is alive or exploding
		if (enemies_status[i] == enemyAlive || enemies_status[i] == enemyExploding) {
			backbuffer->BltFast(xadj + enemies_pos[i].x,  yadj + enemies_pos[i].y, enemy[enemy_frame], NULL, GDBLTFAST_KEYSRC, NULL);
			// Check for collision with laser, explode if hit
			POINT colPoint;
			CGapiSurface::Intersect(xadj + laser_pos.x, yadj + laser_pos.y,
															laser, NULL,
															xadj + enemies_pos[i].x, yadj + enemies_pos[i].y,
															enemy[enemy_frame], NULL, &colPoint);
			if (colPoint.x != -1 || colPoint.y != -1) {
				enemies_status[i] = enemyExploding;
				sndObj.playSound(sfxExplosion);
				addToScore(10);
			}
		}
		// Update position if alive
		if (enemies_status[i] == enemyAlive) {
			enemies_pos[i].y = enemies_pos[i].y - enemies_speed[i];
			if (enemies_pos[i].y < 10) {
				positionEnemy(i);
				subtractFromScore(50);
			}
		}
		// If exploding or dead, blit explosion
		if (enemies_status[i] == enemyExploding || enemies_status[i] == enemyDead) {
			backbuffer->BltFast(xadj + (enemies_pos[i].x - 14),  yadj + (enemies_pos[i].y - 10), explosion[enemies_explosion_frame[i]], NULL, GDBLTFAST_KEYSRC, NULL);
			enemies_explosion_frame_delay[i]++;
			if (enemies_explosion_frame_delay[i] > 1) {
				enemies_explosion_frame[i]++;
				if (enemies_explosion_frame[i] == 2) {
					enemies_status[i] = enemyDead;
				}
				if (enemies_explosion_frame[i] > 4) {
					enemies_explosion_frame[i] = 0;
					positionEnemy(i);
					enemies_status[i] = enemyAlive;
				}
			}
		}
	}
	// Update enemy frame
	enemy_frame_delay++;
	if (enemy_frame_delay > 10) {
		enemy_frame_delay = 0;
		enemy_frame++;
		if (enemy_frame > 1) {
			enemy_frame = 0;
		}
	}

	// Blit ship
	backbuffer->BltFast(xadj, yadj, ship[ship_frame], NULL, GDBLTFAST_KEYSRC, NULL);
	ship_frame_delay++;
	if (ship_frame_delay > 2) {
		ship_frame_delay = 0;
		ship_frame++;
		if (ship_frame > 5) { ship_frame = 0; }
	}

	// Blit gravpits
	backbuffer->BltFast(xadj + 18,  yadj + 182, gravpit[gravpit_frame], NULL, GDBLTFAST_KEYSRC, NULL);
	backbuffer->BltFast(xadj + 79,  yadj + 182, gravpit[gravpit_frame], NULL, GDBLTFAST_KEYSRC, NULL);
	backbuffer->BltFast(xadj + 140, yadj + 182, gravpit[gravpit_frame], NULL, GDBLTFAST_KEYSRC, NULL);
	gravpit_frame_delay++;
	if (gravpit_frame_delay > 2) {
		gravpit_frame_delay = 0;
		gravpit_frame++;
		if (gravpit_frame > 1) {
			gravpit_frame = 0;
		}
	}

	// Blit player and handle movements, if applicable
	backbuffer->BltFast(xadj + player_pos.x, yadj + player_pos.y, gun, NULL, GDBLTFAST_KEYSRC, NULL);
	if (!laser_fired) {
		if (player_dir_north) {
			player_pos.y = player_pos.y - 3;
			if (player_pos.y < 41) { player_pos.y = 42; }
		}
		if (player_dir_south) {
			player_pos.y = player_pos.y + 3;
			if (player_pos.y > 160) { player_pos.y = 160; }
		}
	}

}


// ****************************************************************************************************************
// KeyDown handler
// ****************************************************************************************************************
void CGame::kdAntigravitator(DWORD dwKey) {

	using namespace ns_Antigravitator;

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
		if (!laser_fired) {
			sndObj.playSound(sfxMissileFiring);
			laser_fired			 = true;
			laser_pos.x			 = player_pos.x - 200;
			laser_pos.y			 = player_pos.y + 11;
		}
	}

}


// ****************************************************************************************************************
// KeyUp handler
// ****************************************************************************************************************
void CGame::kuAntigravitator(DWORD dwKey) {

	using namespace ns_Antigravitator;

	// Command button
	if (dwKey == kCommand) {
    miniGameCommandButtonHandler();
	}

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


// ****************************************************************************************************************
// Initialize
// ****************************************************************************************************************
void CGame::initializeAntigravitator() {

	using namespace ns_Antigravitator;

	// Track animation frame for gravpits and the delay of that animation
	gravpit_frame										 = 0;
	gravpit_frame_delay							 = 0;

	// Start the player in the proper position
	player_pos.x										 = 0;
	player_pos.y										 = 42;

	// Make sure we start out not firing
	laser_fired											 = false;

	// Set up frame variables for enemy animation
	enemy_frame											 = 0;
	enemy_frame_delay								 = 0;

	// Each enemy can be exploding independantly, so we have to have an array element
	// for each to track the explosion animation frame and the delay of it
	enemies_explosion_frame[0]			 = 0;
	enemies_explosion_frame[1]			 = 0;
	enemies_explosion_frame[2]			 = 0;
	enemies_explosion_frame[3]			 = 0;
	enemies_explosion_frame[4]			 = 0;
	enemies_explosion_frame_delay[0] = 0;
	enemies_explosion_frame_delay[1] = 0;
	enemies_explosion_frame_delay[2] = 0;
	enemies_explosion_frame_delay[3] = 0;
	enemies_explosion_frame_delay[4] = 0;

	// Randomly position all the possible enemies
	positionEnemy(0);
	positionEnemy(1);
	positionEnemy(2);
	positionEnemy(3);
	positionEnemy(4);

	ship_frame_delay = 0;
	ship_frame			 = 0;

}


// ****************************************************************************************************************
// Loader
// ****************************************************************************************************************
void CGame::loadAntigravitator(CGapiSurface* backbuffer) {

	using namespace ns_Antigravitator;

	processEvents = false;

	// Move on to the next step
	loading_step++;

	// Do the appropriate step
	switch(loading_step) {

		case 1: {
			doCommonInit();
      int i = 0;
      for (i = 0; i < 2; i++) { gravpit[i]   = NULL; }
      for (i = 0; i < 2; i++) { enemy[i]     = NULL; }
      for (i = 0; i < 6; i++) { explosion[i] = NULL; }
      for (i = 0; i < 6; i++) { ship[i]      = NULL; }
      gun              = NULL;
      laser            = NULL;
      sfxExplosion     = NULL;
      sfxMissileFiring = NULL;
		break; }

		case 2: {
			explosion[0]     = new CGapiSurface(); createSurface(TEXT("antigravitator : GFX_EXPLOSION_00"),              explosion[0]->CreateSurface(0, m_config.hInstance, GFX_EXPLOSION_00,              TEXT("GRAPHICS"))); explosion[0]->SetColorKey(RGB(255, 128, 255));
			explosion[1]     = new CGapiSurface(); createSurface(TEXT("antigravitator : GFX_EXPLOSION_01"),              explosion[1]->CreateSurface(0, m_config.hInstance, GFX_EXPLOSION_01,              TEXT("GRAPHICS"))); explosion[1]->SetColorKey(RGB(255, 128, 255));
			explosion[2]     = new CGapiSurface(); createSurface(TEXT("antigravitator : GFX_EXPLOSION_02"),              explosion[2]->CreateSurface(0, m_config.hInstance, GFX_EXPLOSION_02,              TEXT("GRAPHICS"))); explosion[2]->SetColorKey(RGB(255, 128, 255));
			explosion[3]     = new CGapiSurface(); createSurface(TEXT("antigravitator : GFX_EXPLOSION_03"),              explosion[3]->CreateSurface(0, m_config.hInstance, GFX_EXPLOSION_03,              TEXT("GRAPHICS"))); explosion[3]->SetColorKey(RGB(255, 128, 255));
			explosion[4]     = new CGapiSurface(); createSurface(TEXT("antigravitator : GFX_EXPLOSION_04"),              explosion[4]->CreateSurface(0, m_config.hInstance, GFX_EXPLOSION_04,              TEXT("GRAPHICS"))); explosion[4]->SetColorKey(RGB(255, 128, 255));
			ship[0]          = new CGapiSurface(); createSurface(TEXT("antigravitator : GFX_ANTIGRAVITATOR_SHIP_00"),    ship[0]->CreateSurface     (0, m_config.hInstance, GFX_ANTIGRAVITATOR_SHIP_00,    TEXT("GRAPHICS"))); ship[0]->SetColorKey     (RGB(255, 128, 255));
			ship[1]          = new CGapiSurface(); createSurface(TEXT("antigravitator : GFX_ANTIGRAVITATOR_SHIP_01"),    ship[1]->CreateSurface     (0, m_config.hInstance, GFX_ANTIGRAVITATOR_SHIP_01,    TEXT("GRAPHICS"))); ship[1]->SetColorKey     (RGB(255, 128, 255));
			ship[2]          = new CGapiSurface(); createSurface(TEXT("antigravitator : GFX_ANTIGRAVITATOR_SHIP_02"),    ship[2]->CreateSurface     (0, m_config.hInstance, GFX_ANTIGRAVITATOR_SHIP_02,    TEXT("GRAPHICS"))); ship[2]->SetColorKey     (RGB(255, 128, 255));
			ship[3]          = new CGapiSurface(); createSurface(TEXT("antigravitator : GFX_ANTIGRAVITATOR_SHIP_03"),    ship[3]->CreateSurface     (0, m_config.hInstance, GFX_ANTIGRAVITATOR_SHIP_03,    TEXT("GRAPHICS"))); ship[3]->SetColorKey     (RGB(255, 128, 255));
			ship[4]          = new CGapiSurface(); createSurface(TEXT("antigravitator : GFX_ANTIGRAVITATOR_SHIP_04"),    ship[4]->CreateSurface     (0, m_config.hInstance, GFX_ANTIGRAVITATOR_SHIP_04,    TEXT("GRAPHICS"))); ship[4]->SetColorKey     (RGB(255, 128, 255));
			ship[5]          = new CGapiSurface(); createSurface(TEXT("antigravitator : GFX_ANTIGRAVITATOR_SHIP_05"),    ship[5]->CreateSurface     (0, m_config.hInstance, GFX_ANTIGRAVITATOR_SHIP_05,    TEXT("GRAPHICS"))); ship[5]->SetColorKey     (RGB(255, 128, 255));
			gun              = new CGapiSurface(); createSurface(TEXT("antigravitator : GFX_ANTIGRAVITATOR_GUN"),        gun->CreateSurface         (0, m_config.hInstance, GFX_ANTIGRAVITATOR_GUN,        TEXT("GRAPHICS"))); gun->SetColorKey         (RGB(255, 128, 255));
			laser            = new CGapiSurface(); createSurface(TEXT("antigravitator : GFX_ANTIGRAVITATOR_LASER"),      laser->CreateSurface       (0, m_config.hInstance, GFX_ANTIGRAVITATOR_LASER,      TEXT("GRAPHICS"))); laser->SetColorKey       (RGB(255, 128, 255));
			gravpit[0]       = new CGapiSurface(); createSurface(TEXT("antigravitator : GFX_ANTIGRAVITATOR_GRAVPIT_00"), gravpit[0]->CreateSurface  (0, m_config.hInstance, GFX_ANTIGRAVITATOR_GRAVPIT_00, TEXT("GRAPHICS"))); gravpit[0]->SetColorKey  (RGB(255, 128, 255));
			gravpit[1]       = new CGapiSurface(); createSurface(TEXT("antigravitator : GFX_ANTIGRAVITATOR_GRAVPIT_01"), gravpit[1]->CreateSurface  (0, m_config.hInstance, GFX_ANTIGRAVITATOR_GRAVPIT_01, TEXT("GRAPHICS"))); gravpit[1]->SetColorKey  (RGB(255, 128, 255));
			enemy[0]         = new CGapiSurface(); createSurface(TEXT("antigravitator : GFX_RELUCTANT_HERO_PERSON_00"),  enemy[0]->CreateSurface    (0, m_config.hInstance, GFX_RELUCTANT_HERO_PERSON_00,  TEXT("GRAPHICS"))); enemy[0]->SetColorKey    (RGB(255, 128, 255));
			enemy[1]         = new CGapiSurface(); createSurface(TEXT("antigravitator : GFX_RELUCTANT_HERO_PERSON_01"),  enemy[1]->CreateSurface    (0, m_config.hInstance, GFX_RELUCTANT_HERO_PERSON_01,  TEXT("GRAPHICS"))); enemy[1]->SetColorKey    (RGB(255, 128, 255));
			sfxExplosion     = new hssSound();     loadSFX      (TEXT("antigravitator : SFX_EXPLOSION"),                 sfxExplosion->load         (m_config.hInstance,    SFX_EXPLOSION));                                   sfxExplosion->loop       (false);
			sfxMissileFiring = new hssSound();     loadSFX      (TEXT("antigravitator : SFX_MISSILE_FIRING"),            sfxMissileFiring->load     (m_config.hInstance,    SFX_MISSILE_FIRING));                              sfxMissileFiring->loop   (false);
    break; }

		case 3: {
			initializeAntigravitator();
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
void CGame::destroyAntigravitator(CGapiSurface* backbuffer) {

	using namespace ns_Antigravitator;

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
			delete sfxMissileFiring;
			delete ship[0];
			delete ship[1];
			delete ship[2];
			delete ship[3];
			delete ship[4];
			delete ship[5];
			delete gun;
			delete laser;
			delete gravpit[0];
			delete gravpit[1];
			delete enemy[0];
			delete enemy[1];
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
namespace ns_Antigravitator {


	void positionEnemy(int enemy_number) {
		enemies_status[enemy_number] = enemyAlive;
		int gravpit = 0;
		pGravPit:
		gravpit = (rand() % 3)	+ 1;
		if (gravpit < 1 || gravpit > 3) { goto pGravPit; }
		// Set X position, add an offset to center it on the gravpit
		if (gravpit == 1) { enemies_pos[enemy_number].x = 18  + 17; }
		if (gravpit == 2) { enemies_pos[enemy_number].x = 79  + 17; }
		if (gravpit == 3) { enemies_pos[enemy_number].x = 140 + 17; }
		enemies_pos[enemy_number].y = (rand() % 100)	+ 200; // 200-300
		// Randomize speed
		enemies_speed[enemy_number] = (rand() % 3) + 1;
	}


} // End of namespace
