
#include "../main.h"


namespace ns_CosmicSquirrel {


// ****************************************************************************************************************
// Defines specific to this mini-game
// ****************************************************************************************************************
#define LEFT  1
#define RIGHT 2


// ****************************************************************************************************************
// Globals specific to this mini-game
// ****************************************************************************************************************
TCHAR	instructions[][32] = { TEXT("Cosmic Squirrel"),
														 TEXT(""),
														 TEXT("What are they feeding"),
														 TEXT("those things?!?  Here"),
														 TEXT("you play the part of a"),
														 TEXT("giant space-born squirrel,"),
														 TEXT("just trying to get"),
														 TEXT("across the interstellar"),
														 TEXT("freeway to get your"),
														 TEXT("planet-sized acorn."),
                             //    ---------------------------
                             TEXT("The Goal"),
														 TEXT(""),
														 TEXT("Get the acorn as many"),
														 TEXT("times as you can until"),
														 TEXT("time runs out.  Each"),
														 TEXT("time you get hit by"),
														 TEXT("something, you lose"),
														 TEXT("points."),
														 TEXT(""),
														 TEXT(""),
                             //    ---------------------------
                             TEXT("How To Play"),
														 TEXT(""),
														 TEXT("Move up, down, left or"),
														 TEXT("right to get the squirrel"),
														 TEXT("safely through the"),
														 TEXT("obstacles and to the"),
														 TEXT("giant acorn."),
														 TEXT(""),
														 TEXT(""),
														 TEXT(""),
                             //    ----------------------------
};

CGapiSurface*	acorn                   = NULL;	 // Our acorn image
CGapiSurface*	alien[4];											   // Our flying alien image
CGapiSurface*	ship[4];										     // Our flying ship image
CGapiSurface*	comet[4];
CGapiSurface*	squirrel[4];									   // Frames of animation of our squirrel
CGapiSurface* obstacles[10];								     // Stores the images of our eight obstacles
hssSound*			sfxChomp                = NULL;
hssSound*			sfxSplat                = NULL;
hssSound*     sfxWalking              = NULL;
POINT					acorn_pos;										   // Position of of acorn
POINT					obstacles_pos[10];						     // Stores the positions of our eight obstacles
bool					starfield_generated	    = false; // Only generate starfield coordinates once
bool					obstacles_positioned    = false; // Only position obstacles once
bool					just_died;										   // Set to true when player just died
bool          walkingPlaying          = false;
int						stars_x[52];								     // Starfield X coordinates
int						stars_y[52];								     // Starfield Y coordinates
int						alien_frame             = 0;
int						alien_frame_delay       = 0;
int						ship_frame              = 0;
int						ship_frame_delay        = 0;
int						comet_frame             = 0;
int						comet_frame_delay       = 0;
int						squirrel_frame          = 0;     // Index into squirrel image array
int						squirrel_frame_delay    = 0;
int						obstacles_dir[10];						     // Stores the direction of travel of our eight obstackes
int						obstacles_speed[10];			 	       // Stores the speed of our eight obstacles
int			      walkinghssChannel       = NULL;
long					asteroid_rotation_angle = 0;     // Used to rotate asteroid


} // End of namespace


// ****************************************************************************************************************
// ProcessNextFrame handler
// ****************************************************************************************************************
void CGame::pnfCosmicSquirrel(CGapiSurface* backbuffer) {

	using namespace ns_CosmicSquirrel;

	GDBLTFX gdbltfx;

	// Starfield
	for (int i = 0; i < 50; i++) {
		backbuffer->SetPixel(xadj + stars_x[i], yadj + stars_y[i], RGB(255, 255, 255));
		backbuffer->SetPixel(xadj + stars_x[i] + 1, yadj + stars_y[i], RGB(255, 255, 255));
		backbuffer->SetPixel(xadj + stars_x[i], yadj + stars_y[i] + 1, RGB(255, 255, 255));
		backbuffer->SetPixel(xadj + stars_x[i] + 1, yadj + stars_y[i] + 1, RGB(255, 255, 255));
	}

	// Blit acorn
	backbuffer->BltFast(xadj + acorn_pos.x,	yadj + acorn_pos.y, acorn, NULL, GDBLTFAST_KEYSRC, NULL);

	// Blit obstacles and update positions
	for (i = 0; i < 8; i++) {
		if (i == 4 || i == 5) { // Handle asteroids differently so we can rotate them
			gdbltfx.nRotationAngle = asteroid_rotation_angle;
			backbuffer->Blt(CRect(xadj + obstacles_pos[i].x,			yadj + obstacles_pos[i].y,
															xadj + obstacles_pos[i].x + 32, yadj + obstacles_pos[i].y + 32),
															obstacles[i], NULL, GDBLT_KEYSRC  | GDBLT_ROTATIONANGLE, &gdbltfx);
			// Rotate 360 degrees in 1/100th of a degree increments
			asteroid_rotation_angle = asteroid_rotation_angle + 360;
			if (asteroid_rotation_angle > 36000) {
					asteroid_rotation_angle = 0;
			}
		} else { // Other obstacles
			backbuffer->BltFast(xadj + obstacles_pos[i].x, yadj + obstacles_pos[i].y, obstacles[i], NULL, GDBLTFAST_KEYSRC, NULL);
		}
		if (obstacles_dir[i] == LEFT) {
			obstacles_pos[i].x = obstacles_pos[i].x - obstacles_speed[i];
		}
		if (obstacles_dir[i] == RIGHT) {
			obstacles_pos[i].x = obstacles_pos[i].x + obstacles_speed[i];
		}
		if (i != 6 && i != 7) { // The comets have to be handled differently because of their size
			if (obstacles_pos[i].x < -40) {
				obstacles_pos[i].x = 240;
			}
		} else {
			if (obstacles_pos[i].x < -70) {
				obstacles_pos[i].x = 240;
			}
		}
		if (obstacles_pos[i].x > 240) {
			obstacles_pos[i].x = -40;
		}
	}

	// Update obstacle animations
	ship_frame_delay++;
	if (ship_frame_delay > 1) {
		ship_frame_delay = 0;
		ship_frame++;
		if (ship_frame > 1) { ship_frame = 0; }
		obstacles[2] = ship[ship_frame];
		obstacles[3] = ship[ship_frame];
	}
	alien_frame_delay++;
	if (alien_frame_delay > 3) {
		alien_frame_delay = 0;
		alien_frame++;
		if (alien_frame > 1) { alien_frame = 0; }
		obstacles[0] = alien[alien_frame];
		obstacles[1] = alien[alien_frame];
	}
	comet_frame_delay++;
	if (comet_frame_delay > 3) {
		comet_frame_delay = 0;
		comet_frame++;
		if (comet_frame > 1) { comet_frame = 0; }
		obstacles[6] = comet[comet_frame];
		obstacles[7] = comet[comet_frame];
	}

	// Blit squirrel
	RECT rect;
	SetRect(&rect, xadj + player_pos.x, yadj + player_pos.y, xadj + player_pos.x + 18, yadj + player_pos.y + 18);
	if (!player_dir_north && !player_dir_south && !player_dir_east && !player_dir_west) { // No movement
		gdbltfx.nRotationAngle = 0;
		backbuffer->Blt(&rect, squirrel[squirrel_frame], NULL, GDBLTFAST_KEYSRC | GDBLT_ROTATIONANGLE, &gdbltfx);
	}
	if (player_dir_north && !player_dir_south && !player_dir_east && !player_dir_west) { // North
		gdbltfx.nRotationAngle = 0;
		backbuffer->Blt(&rect, squirrel[squirrel_frame], NULL, GDBLTFAST_KEYSRC | GDBLT_ROTATIONANGLE, &gdbltfx);
	}
	if (!player_dir_north && player_dir_south && !player_dir_east && !player_dir_west) { // South
		gdbltfx.nRotationAngle = 18000;
		backbuffer->Blt(&rect, squirrel[squirrel_frame], NULL, GDBLTFAST_KEYSRC | GDBLT_ROTATIONANGLE, &gdbltfx);
	}
	if (!player_dir_north && !player_dir_south && player_dir_east && !player_dir_west) { // East
		gdbltfx.nRotationAngle = 9000;
		backbuffer->Blt(&rect, squirrel[squirrel_frame], NULL, GDBLTFAST_KEYSRC | GDBLT_ROTATIONANGLE, &gdbltfx);
	}
	if (!player_dir_north && !player_dir_south && !player_dir_east && player_dir_west) { // West
		gdbltfx.nRotationAngle = 27000;
		backbuffer->Blt(&rect, squirrel[squirrel_frame], NULL, GDBLTFAST_KEYSRC | GDBLT_ROTATIONANGLE, &gdbltfx);
	}
	if (player_dir_north && !player_dir_south && player_dir_east && !player_dir_west) { // NorthEast
		gdbltfx.nRotationAngle = 4500;
		backbuffer->Blt(&rect, squirrel[squirrel_frame], NULL, GDBLTFAST_KEYSRC | GDBLT_ROTATIONANGLE, &gdbltfx);
	}
	if (player_dir_north && !player_dir_south && !player_dir_east && player_dir_west) { // NorthWest
		gdbltfx.nRotationAngle = 31500;
		backbuffer->Blt(&rect, squirrel[squirrel_frame], NULL, GDBLTFAST_KEYSRC | GDBLT_ROTATIONANGLE, &gdbltfx);
	}
	if (!player_dir_north && player_dir_south && player_dir_east && !player_dir_west) { // SouthEast
		gdbltfx.nRotationAngle = 13500;
		backbuffer->Blt(&rect, squirrel[squirrel_frame], NULL, GDBLTFAST_KEYSRC | GDBLT_ROTATIONANGLE, &gdbltfx);
	}
	if (!player_dir_north && player_dir_south && !player_dir_east && player_dir_west) { // SouthWest
		gdbltfx.nRotationAngle = 22500;
		backbuffer->Blt(&rect, squirrel[squirrel_frame], NULL, GDBLTFAST_KEYSRC | GDBLT_ROTATIONANGLE, &gdbltfx);
	}

	// Handle player movements
	bool update_frame = false;
	if (player_dir_north) {
		player_pos.y = player_pos.y - 2;
		if (player_pos.y < 2) { player_pos.y = 2; }
		update_frame = true;
	}
	if (player_dir_south) {
		player_pos.y = player_pos.y + 2;
		if (player_pos.y > 180) { player_pos.y = 180; }
		update_frame = true;
	}
	if (player_dir_east) {
		player_pos.x = player_pos.x + 2;
		if (player_pos.x > 180) { player_pos.x = 180; }
		update_frame = true;
	}
	if (player_dir_west) {
		player_pos.x = player_pos.x - 2;
		if (player_pos.x < 2) { player_pos.x = 2; }
		update_frame = true;
	}
	if (update_frame) {
		squirrel_frame_delay++;
		if (squirrel_frame_delay > 1) {
			squirrel_frame_delay = 0;
			squirrel_frame++;
			if (squirrel_frame > 1) { squirrel_frame = 0; }
		}
	}

	// Check for collision with acorn
	POINT colPoint;
	CGapiSurface::Intersect(xadj + player_pos.x, yadj + player_pos.y,
													squirrel[squirrel_frame], NULL,
													xadj + acorn_pos.x, yadj + acorn_pos.y,
													acorn, NULL, &colPoint);
	if (colPoint.x != -1 || colPoint.y != -1) {
		if (walkingPlaying) {
			walkingPlaying = false;
			hssChannel* c = sndObj.channel(walkinghssChannel);
			if (c->playing()) { c->stop(); }
			walkinghssChannel = NULL;
		}
		sndObj.playSound(sfxChomp);
		addToScore(250);
		initializeCosmicSquirrel();
		player_dir_north = false;
		player_dir_south = false;
		player_dir_east  = false;
		player_dir_west  = false;
	}

	// Check for collissions with obstacles
	for (i = 0; i < 8; i++) {
		CGapiSurface::Intersect(xadj + player_pos.x, yadj + player_pos.y,
														squirrel[squirrel_frame], NULL,
														xadj + obstacles_pos[i].x, yadj + obstacles_pos[i].y,
														obstacles[i], NULL, &colPoint);
		if (colPoint.x != -1 || colPoint.y != -1) {
      if (walkingPlaying) {
		    hssChannel* wc = sndObj.channel(walkinghssChannel);
		    wc->stop();
        walkingPlaying = false;
      }
			sndObj.playSound(sfxSplat);
			subtractFromScore(100);
			just_died = true;
			initializeCosmicSquirrel();
			player_dir_north = false;
			player_dir_south = false;
			player_dir_east  = false;
			player_dir_west  = false;
		}
	}

	if (player_dir_north || player_dir_south || player_dir_east || player_dir_west) {
		// See if the channel the walking sound is playing on is actually playing.  If it's NOT, then play it and record the channel assigned
		hssChannel* wc = sndObj.channel(walkinghssChannel);
		if (!wc->playing()) {
			walkinghssChannel = sndObj.playSound(sfxWalking);
		}
    walkingPlaying = true;
	} else {
    if (walkingPlaying) {
		  // Player is NOT walking, so if the walking channel is playing, stop it
		  hssChannel* wc = sndObj.channel(walkinghssChannel);
		  wc->stop();
      walkingPlaying = false;
    }
	}

}


// ****************************************************************************************************************
// KeyDown handler
// ****************************************************************************************************************
void CGame::kdCosmicSquirrel(DWORD dwKey) {

	using namespace ns_CosmicSquirrel;

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

	// Handle left movement events
	if (dwKey == kLeft) {
		player_dir_west	 = true;
		player_dir_east	 = false;
	}

	// Handle right movement events
	if (dwKey == kRight) {
		player_dir_east	 = true;
		player_dir_west	 = false;
	}

}


// ****************************************************************************************************************
// KeyUp handler
// ****************************************************************************************************************
void CGame::kuCosmicSquirrel(DWORD dwKey) {

	using namespace ns_CosmicSquirrel;

	// Command button
	if (dwKey == kCommand) {
		hssChannel* wc = sndObj.channel(walkinghssChannel);
		wc->stop();
    walkingPlaying = false;
    miniGameCommandButtonHandler();
	}

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

}


// ****************************************************************************************************************
// Initialize
// ****************************************************************************************************************
void CGame::initializeCosmicSquirrel() {

	using namespace ns_CosmicSquirrel;

	// Generate initial starfield, if first time through
	if (!starfield_generated) {
		for (int i = 0; i < 50; i++) {
			stars_x[i] = (rand() % 199) + 1; // X coordinate (1-199)
			stars_y[i] = (rand() % 199) + 1; // Y coordinate (1-199)
		}
		starfield_generated = true;
	}

	// Player's initial position and animation frame
	player_pos.x				 = 91;
	player_pos.y				 = 180;
	squirrel_frame			 = 0;
	squirrel_frame_delay = 0;

	// Acorn's random position
	if (!just_died) { // Don't do this if we just died
		acorn_pos.x = (rand() % 180) + 1;
		acorn_pos.y = 2;
	}
	just_died = false;

  walkingPlaying = false;

	ship_frame = 0;
	ship_frame_delay = 0;
	alien_frame = 0;
	alien_frame_delay = 0;
	comet_frame = 0;
	comet_frame_delay = 0;

	// Obstacle positions and speeds, if first time through
	if (!obstacles_positioned) {
		asteroid_rotation_angle = 0;
		obstacles_pos[0].x			= 170;
		obstacles_pos[0].y			= 30;
		obstacles_dir[0]				= RIGHT;
		obstacles_speed[0]			= 5;
		obstacles_pos[1].x			= 80;
		obstacles_pos[1].y			= 30;
		obstacles_dir[1]				= RIGHT;
		obstacles_speed[1]	 		= 5;
		obstacles_pos[2].x			= 110;
		obstacles_pos[2].y			= 60;
		obstacles_dir[2]				= LEFT;
		obstacles_speed[2]			= 2;
		obstacles_pos[3].x			= 10;
		obstacles_pos[3].y			= 60;
		obstacles_dir[3]				= LEFT;
		obstacles_speed[3]			= 2;
		obstacles_pos[4].x			= 80;
		obstacles_pos[4].y			= 90;
		obstacles_dir[4]				= RIGHT;
		obstacles_speed[4]			= 4;
		obstacles_pos[5].x			= 140;
		obstacles_pos[5].y			= 90;
		obstacles_dir[5]				= RIGHT;
		obstacles_speed[5]			= 4;
		obstacles_pos[6].x			= 240;
		obstacles_pos[6].y			= 130;
		obstacles_dir[6]				= LEFT;
		obstacles_speed[6]			= 3;
		obstacles_pos[7].x			= 70;
		obstacles_pos[7].y			= 130;
		obstacles_dir[7]				= LEFT;
		obstacles_speed[7]			= 3;
		obstacles_positioned		= true;
	}

}


// ****************************************************************************************************************
// Ender
// ****************************************************************************************************************
void CGame::endCosmicSquirrel() {

	using namespace ns_CosmicSquirrel;

  hssChannel* c = sndObj.channel(walkinghssChannel);
	if (c->playing()) { c->stop(); }

}


// ****************************************************************************************************************
// Loader
// ****************************************************************************************************************
void CGame::loadCosmicSquirrel(CGapiSurface* backbuffer) {

	using namespace ns_CosmicSquirrel;

	processEvents = false;

	// Move on to the next step
	loading_step++;

	// Do the appropriate step
	switch(loading_step) {

		case 1: {
			doCommonInit();
      int i = 0;
      for (i = 0; i < 2; i++) { alien[i]     = NULL; }											 
      for (i = 0; i < 2; i++) { ship[i]      = NULL; }								   
      for (i = 0; i < 2; i++) { comet[i]     = NULL; }
      for (i = 0; i < 2; i++) { squirrel[i]  = NULL; }							 
      for (i = 0; i < 8; i++) { obstacles[i] = NULL; }								   
      acorn      = NULL;
      sfxChomp   = NULL;
      sfxSplat   = NULL;
      sfxWalking = NULL;
		break; }

		case 2: {
			acorn        = new CGapiSurface(); createSurface(TEXT("cosmic_squirrel : GFX_COSMIC_SQUIRREL_ACORN"),       acorn->CreateSurface       (0, m_config.hInstance, GFX_COSMIC_SQUIRREL_ACORN,       TEXT("GRAPHICS"))); acorn->SetColorKey       (RGB(255, 128, 255));
			alien[0]     = new CGapiSurface(); createSurface(TEXT("cosmic_squirrel : GFX_COSMIC_SQUIRREL_ALIEN_00"),    alien[0]->CreateSurface    (0, m_config.hInstance, GFX_COSMIC_SQUIRREL_ALIEN_00,    TEXT("GRAPHICS"))); alien[0]->SetColorKey    (RGB(255, 128, 255));
			alien[1]     = new CGapiSurface(); createSurface(TEXT("cosmic_squirrel : GFX_COSMIC_SQUIRREL_ALIEN_01"),    alien[1]->CreateSurface    (0, m_config.hInstance, GFX_COSMIC_SQUIRREL_ALIEN_01,    TEXT("GRAPHICS"))); alien[1]->SetColorKey    (RGB(255, 128, 255));
			ship[0]      = new CGapiSurface(); createSurface(TEXT("cosmic_squirrel : GFX_DEFENDOH_SHIP_00"),            ship[0]->CreateSurface     (0, m_config.hInstance, GFX_DEFENDOH_SHIP_00,            TEXT("GRAPHICS"))); ship[0]->SetColorKey     (RGB(255, 128, 255));
			ship[1]      = new CGapiSurface(); createSurface(TEXT("cosmic_squirrel : GFX_DEFENDOH_SHIP_01"),            ship[1]->CreateSurface     (0, m_config.hInstance, GFX_DEFENDOH_SHIP_01,            TEXT("GRAPHICS"))); ship[1]->SetColorKey     (RGB(255, 128, 255));
			comet[0]     = new CGapiSurface(); createSurface(TEXT("cosmic_squirrel : GFX_COSMIC_SQUIRREL_COMET_00"),    comet[0]->CreateSurface    (0, m_config.hInstance, GFX_COSMIC_SQUIRREL_COMET_00,    TEXT("GRAPHICS"))); comet[0]->SetColorKey    (RGB(255, 128, 255));
			comet[1]     = new CGapiSurface(); createSurface(TEXT("cosmic_squirrel : GFX_COSMIC_SQUIRREL_COMET_01"),    comet[1]->CreateSurface    (0, m_config.hInstance, GFX_COSMIC_SQUIRREL_COMET_01,    TEXT("GRAPHICS"))); comet[1]->SetColorKey    (RGB(255, 128, 255));
			squirrel[0]  = new CGapiSurface(); createSurface(TEXT("cosmic_squirrel : GFX_COSMIC_SQUIRREL_SQUIRREL_00"), squirrel[0]->CreateSurface (0, m_config.hInstance, GFX_COSMIC_SQUIRREL_SQUIRREL_00, TEXT("GRAPHICS"))); squirrel[0]->SetColorKey (RGB(255, 128, 255));
			squirrel[1]  = new CGapiSurface(); createSurface(TEXT("cosmic_squirrel : GFX_COSMIC_SQUIRREL_SQUIRREL_01"), squirrel[1]->CreateSurface (0, m_config.hInstance, GFX_COSMIC_SQUIRREL_SQUIRREL_01, TEXT("GRAPHICS"))); squirrel[1]-> SetColorKey(RGB(255, 128, 255));
			obstacles[4] = new CGapiSurface(); createSurface(TEXT("cosmic_squirrel : GFX_FLIGHT_OF_DOOM_ASTEROID"),     obstacles[4]->CreateSurface(0, m_config.hInstance, GFX_FLIGHT_OF_DOOM_ASTEROID,     TEXT("GRAPHICS"))); obstacles[4]->SetColorKey(RGB(255, 128, 255));
			obstacles[5] = new CGapiSurface(); createSurface(TEXT("cosmic_squirrel : GFX_FLIGHT_OF_DOOM_ASTEROID"),     obstacles[5]->CreateSurface(0, m_config.hInstance, GFX_FLIGHT_OF_DOOM_ASTEROID,     TEXT("GRAPHICS"))); obstacles[5]->SetColorKey(RGB(255, 128, 255));
			sfxChomp     = new hssSound();     loadSFX      (TEXT("cosmic_squirrel : SFX_CHOMP"),                       sfxChomp->load             (m_config.hInstance,    SFX_CHOMP));                                         sfxChomp->loop           (false);
			sfxSplat     = new hssSound();     loadSFX      (TEXT("cosmic_squirrel : SFX_SPLAT"),                       sfxSplat->load             (m_config.hInstance,    SFX_SPLAT));                                         sfxSplat->loop           (false);
			sfxWalking   = new hssSound();     loadSFX      (TEXT("cosmic_squirrel : SFX_COSMIC_SQUIRREL_WALKING"),     sfxWalking->load           (m_config.hInstance,    SFX_COSMIC_SQUIRREL_WALKING));                       sfxWalking->loop         (true);
      break; }

    case 3: {
			initializeCosmicSquirrel();
      for (int i = 0; i < 30; i++) { _tcscpy(mgInstructions[i], instructions[i]); } mgInstructionsPage = 0; mgiPrevTapped = false; mgiNextTapped = false;
			obstacles[0] = alien[0];
			obstacles[1] = alien[0];
			obstacles[2] = ship[0];
			obstacles[3] = ship[0];
			obstacles[6] = comet[0];
			obstacles[7] = comet[0];
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
void CGame::destroyCosmicSquirrel(CGapiSurface* backbuffer) {

	using namespace ns_CosmicSquirrel;

	processEvents = false;

	// Move on to the next step
	destroying_step++;

	// Do the appropriate step
	switch(destroying_step) {

		case 1: {
			doCommonCleanup();
		break; }

		case 2: {
			obstacles_positioned = false; // So the obstacles will be randomly positioned on the next invocation
			starfield_generated  = false; // So the starfield will be generated on the next onvocation
			delete acorn;
			delete alien[0];
			delete alien[1];
			delete ship[0];
			delete ship[1];
			delete squirrel[0];
			delete squirrel[1];
			delete comet[0];
			delete comet[1];
			delete obstacles[4];
			delete obstacles[5];
			delete sfxChomp;
			delete sfxSplat;
      delete sfxWalking;
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

