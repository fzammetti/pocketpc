
#include "../main.h"


namespace ns_ReluctantHero {


// ****************************************************************************************************************
// Globals specific to this mini-game
// ****************************************************************************************************************
TCHAR	instructions[][32] = { TEXT("Reluctant Hero"),
														 TEXT(""),
														 TEXT("Your not exactly John"),
														 TEXT("Wayne here, why not just"),
														 TEXT("leave them to die?"),
														 TEXT("Because, SOMEONE has"),
														 TEXT("to rescue the trapped"),
														 TEXT("colonists, and your the"),
														 TEXT("only one around.  Get"),
														 TEXT("to it!"),
                             //    ---------------------------
                             TEXT("The Goal"),
														 TEXT(""),
														 TEXT("Pick up as many of the"),
														 TEXT("colonists as you can."),
														 TEXT("Try not to crash into"),
														 TEXT("the walls, but if"),
														 TEXT("you do, you'll come"),
														 TEXT("right back."),
														 TEXT(""),
														 TEXT(""),
                             //    ---------------------------
                             TEXT("How To Play"),
														 TEXT(""),
														 TEXT("Fly up, down, left or"),
														 TEXT("right.  Touch colonists"),
														 TEXT("to save them, touch walls"),
														 TEXT("to blow up.  Uh, wait,"),
														 TEXT("that's a bad thing..."),
														 TEXT(""),
														 TEXT(""),
														 TEXT(""),
                             //    ----------------------------
};

CGapiSurface* background            = NULL;	 // Our background image
CGapiSurface*	player[4];					           // Stores animation frames for our player
CGapiSurface*	person[4];					           // Stores animation frames for our people
CGapiSurface* explosion[8];
hssSound*			sfxThankYou           = NULL;
hssSound*			sfxHover              = NULL;
hssSound*     sfxExplosion          = NULL;
POINT					exploding_point;		           // Stores the point a collision occurred at
POINT					people_pos[8];			           // Positions of each of the six people to rescue
bool					sfxHoverPlaying       = false;
bool					exploding             = false; // True when player is being blown up
bool					people[8];					           // Flag for each person to see if they were picked up yet (true) or not
int						person_frame          = 0;		 // Current animation frame of people
int						player_frame          = 0;		 // Current animation frame of player
int						player_frame_delay    = 0;
int						person_delay          = 0;		 // Slows down people's arm movements
int						gravity               = 0;		 // When this hits 15 and the player is not moving, move him down one pixel
int           explosion_frame       = 0;
int           explosion_frame_delay = 0;
int           sfxHoverhssChannel    = 0;


} // End of namespace


// ****************************************************************************************************************
// ProcessNextFrame handler
// ****************************************************************************************************************
void CGame::pnfReluctantHero(CGapiSurface* backbuffer) {

	using namespace ns_ReluctantHero;

	if (!sfxHoverPlaying) {
		sfxHoverPlaying = true;
		sfxHoverhssChannel = sndObj.playSound(sfxHover);
	}

	RECT destRect;

	// Blit the background
	backbuffer->BltFast(xadj + 0, yadj + 0, background, NULL, GDBLTFAST_KEYSRC, NULL);

	// Blit the people, if applicable
	for (int i = 0; i < 6; i++) {
		if (!people[i]) {
			backbuffer->BltFast(xadj + people_pos[i].x, yadj + people_pos[i].y,  person[person_frame], NULL, GDBLTFAST_KEYSRC, NULL);
		}
	}
	person_delay++;
	if (person_delay > 15) {
		person_delay = 0;
		person_frame++;
		if (person_frame > 1) { person_frame = 0; }
	}

	// Blit player
	if (player_dir_east) { // Mirror if facing east
		SetRect(&destRect, xadj + player_pos.x, yadj + player_pos.y, xadj + player_pos.x + 32, yadj + player_pos.y + 32);
		backbuffer->Blt(&destRect, player[player_frame], NULL, GDBLTFAST_KEYSRC | GDBLT_MIRRORLEFTRIGHT, NULL);
	} else { // Otherwise blit as-is
		backbuffer->BltFast(xadj + player_pos.x, yadj + player_pos.y, player[player_frame], NULL, GDBLTFAST_KEYSRC, NULL);
	}
	player_frame_delay++;
	if (player_frame_delay > 1 ) {
		player_frame++;
		if (player_frame > 1) {
			player_frame = 0;
		}
	}

	// Blit explosion, if applicable
	if (exploding) {
		// Stretch explosion to 40 in all directions around point of collision
		SetRect(&destRect, exploding_point.x - 40, exploding_point.y - 40,
											 exploding_point.x + 40, exploding_point.y + 40);
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
		// At the explosion's maximum size, hide the playe
		if (ret_val == 99) {
			player_pos.x = -200;
			player_pos.x = -200;
		}
		// When the explosion finishes, reposition the player and start again
		if (ret_val == -1) {
			exploding				= false;
			player_pos.x		= 160;
			player_pos.y		= 158;
		}
	}

	// Handle player movements, if not exploding
	if (!exploding) {
		if (player_dir_north) {
			player_pos.y--;
		}
		if (player_dir_south) {
			player_pos.y++;
		}
		if (player_dir_east) {
			player_pos.x++;
		}
		if (player_dir_west) {
			player_pos.x--;
		}
		// Gravity
		if (!player_dir_north && !player_dir_south) {
			gravity++;
			if (gravity > 5) {
				gravity = 0;
				player_pos.y++;
			}
		}
	}

	// Check for collision with the walls, if not exploding
	if (!exploding) {
		POINT colPoint;
		CGapiSurface::Intersect(xadj + 0, yadj + 0,
														background, NULL,
														xadj + player_pos.x, yadj + player_pos.y,
														player[player_frame], NULL, &colPoint);
		if (colPoint.x != -1 || colPoint.y != -1) {
			sndObj.playSound(sfxExplosion);
			exploding			 = true;
			exploding_point = colPoint;
			// Make sure all movements cease too
			player_dir_north		 = false;
			player_dir_south		 = false;
			player_dir_east			 = false;
			player_dir_west			 = false;
		}
	}

	// Check for collision with players, if not exploding
	if (!exploding) {
		for (i = 0; i < 6; i++) {
			// Only check people who haven't been picked up yet
			if (!people[i]) {
				POINT colPoint;
				CGapiSurface::Intersect(xadj + people_pos[i].x, yadj + people_pos[i].y,
																person[person_frame], NULL,
																xadj + player_pos.x, yadj + player_pos.y,
																player[player_frame], NULL, &colPoint);
				if (colPoint.x != -1 || colPoint.y != -1) {
					sndObj.playSound(sfxThankYou);
					people[i] = true;
					addToScore(100);
				}
			}
		}
	}

	// If all six people picked up, reset them and the player's position
	if (people[0] && people[1] && people[2] && people[3] && people[4] && people[5]) {
		people[0]		 = false;
		people[1]		 = false;
		people[2]		 = false;
		people[3]		 = false;
		people[4]		 = false;
		people[5]		 = false;
		player_pos.x = 160;
		player_pos.y = 158;
	}

}


// ****************************************************************************************************************
// KeyDown handler
// ****************************************************************************************************************
void CGame::kdReluctantHero(DWORD dwKey) {

	using namespace ns_ReluctantHero;

	if (!exploding) {

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

}


// ****************************************************************************************************************
// KeyUp handler
// ****************************************************************************************************************
void CGame::kuReluctantHero(DWORD dwKey) {

	using namespace ns_ReluctantHero;

	// Command button
	if (dwKey == kCommand) {
    hssChannel* c = sndObj.channel(sfxHoverhssChannel);
	  if (c->playing()) { c->stop(); }
    sfxHoverPlaying = false;
    miniGameCommandButtonHandler();
	}

	if (!exploding) {

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

}


// ****************************************************************************************************************
// Initialize
// ****************************************************************************************************************
void CGame::initializeReluctantHero() {

	using namespace ns_ReluctantHero;

	// Start player in the bottom right-hand corner
	player_pos.x			 = 160;
	player_pos.y			 = 158;
	player_frame			 = 0;
	player_frame_delay = 0;
	gravity						 = 0;

	// Set people to not picked up
	people[0]		 = false;
	people[1]		 = false;
	people[2]		 = false;
	people[3]		 = false;
	people[4]		 = false;
	people[5]		 = false;
	person_delay = 0;
	person_frame = 0;

	// Positions of the people
	people_pos[0].x = 186; people_pos[0].y = 63;
	people_pos[1].x = 105; people_pos[1].y = 46;
	people_pos[2].x = 87;	 people_pos[2].y = 138;
	people_pos[3].x = 50;	 people_pos[3].y = 175;
	people_pos[4].x = 20;	 people_pos[4].y = 145;
	people_pos[5].x = 43;	 people_pos[5].y = 38;

	// Start off not exploding the player
	exploding = false;

	sfxHoverPlaying = false;

  sfxHoverPlaying    = false;
  sfxHoverhssChannel = 0;

}


// ****************************************************************************************************************
// Ender
// ****************************************************************************************************************
void CGame::endReluctantHero() {

	using namespace ns_ReluctantHero;

  hssChannel* c = sndObj.channel(sfxHoverhssChannel);
	if (c->playing()) { c->stop(); }

}


// ****************************************************************************************************************
// Loader
// ****************************************************************************************************************
void CGame::loadReluctantHero(CGapiSurface* backbuffer) {

	using namespace ns_ReluctantHero;

	processEvents = false;

	// Move on to the next step
	loading_step++;

	// Do the appropriate step
	switch(loading_step) {

		case 1: {
			doCommonInit();
      int i = 0;
      for (i = 0; i < 2; i++) { player[i]    = NULL; }
      for (i = 0; i < 2; i++) { person[i]    = NULL; }
      for (i = 0; i < 6; i++) { explosion[i] = NULL; }
      background   = NULL;
      sfxThankYou  = NULL;
      sfxHover     = NULL;
      sfxExplosion = NULL;
		break; }

		case 2: {
			explosion[0] = new CGapiSurface(); createSurface(TEXT("reluctant_hero : GFX_EXPLOSION_00"),              explosion[0]->CreateSurface(0, m_config.hInstance, GFX_EXPLOSION_00,              TEXT("GRAPHICS"))); explosion[0]->SetColorKey(RGB(255, 128, 255));
			explosion[1] = new CGapiSurface(); createSurface(TEXT("reluctant_hero : GFX_EXPLOSION_01"),              explosion[1]->CreateSurface(0, m_config.hInstance, GFX_EXPLOSION_01,              TEXT("GRAPHICS"))); explosion[1]->SetColorKey(RGB(255, 128, 255));
			explosion[2] = new CGapiSurface(); createSurface(TEXT("reluctant_hero : GFX_EXPLOSION_02"),              explosion[2]->CreateSurface(0, m_config.hInstance, GFX_EXPLOSION_02,              TEXT("GRAPHICS"))); explosion[2]->SetColorKey(RGB(255, 128, 255));
			explosion[3] = new CGapiSurface(); createSurface(TEXT("reluctant_hero : GFX_EXPLOSION_03"),              explosion[3]->CreateSurface(0, m_config.hInstance, GFX_EXPLOSION_03,              TEXT("GRAPHICS"))); explosion[3]->SetColorKey(RGB(255, 128, 255));
			explosion[4] = new CGapiSurface(); createSurface(TEXT("reluctant_hero : GFX_EXPLOSION_04"),              explosion[4]->CreateSurface(0, m_config.hInstance, GFX_EXPLOSION_04,              TEXT("GRAPHICS"))); explosion[4]->SetColorKey(RGB(255, 128, 255));
			background   = new CGapiSurface(); createSurface(TEXT("reluctant_hero : GFX_RELUCTANT_HERO_BACKGROUND"), background->CreateSurface  (0, m_config.hInstance, GFX_RELUCTANT_HERO_BACKGROUND, TEXT("GRAPHICS"))); background->SetColorKey  (RGB(255, 128, 255));
			player[0]    = new CGapiSurface(); createSurface(TEXT("reluctant_hero : GFX_RELUCTANT_HERO_PLAYER_00"),  player[0]->CreateSurface   (0, m_config.hInstance, GFX_RELUCTANT_HERO_PLAYER_00,  TEXT("GRAPHICS"))); player[0]->SetColorKey   (RGB(255, 128, 255));
			player[1]    = new CGapiSurface(); createSurface(TEXT("reluctant_hero : GFX_RELUCTANT_HERO_PLAYER_01"),  player[1]->CreateSurface   (0, m_config.hInstance, GFX_RELUCTANT_HERO_PLAYER_01,  TEXT("GRAPHICS"))); player[1]->SetColorKey   (RGB(255, 128, 255));
			person[0]    = new CGapiSurface(); createSurface(TEXT("reluctant_hero : GFX_RELUCTANT_HERO_PERSON_00"),  person[0]->CreateSurface   (0, m_config.hInstance, GFX_RELUCTANT_HERO_PERSON_00,  TEXT("GRAPHICS"))); person[0]->SetColorKey   (RGB(255, 128, 255));
			person[1]    = new CGapiSurface(); createSurface(TEXT("reluctant_hero : GFX_RELUCTANT_HERO_PERSON_01"),  person[1]->CreateSurface   (0, m_config.hInstance, GFX_RELUCTANT_HERO_PERSON_01,  TEXT("GRAPHICS"))); person[1]->SetColorKey   (RGB(255, 128, 255));
			sfxThankYou  = new hssSound();     loadSFX      (TEXT("reluctant_hero : SFX_THANK_YOU"),                 sfxThankYou->load          (m_config.hInstance,    SFX_THANK_YOU));                                   sfxThankYou->loop        (false);
      sfxHover     = new hssSound();     loadSFX      (TEXT("reluctant_hero : SFX_SHIP"),                      sfxHover->load             (m_config.hInstance,    SFX_SHIP));                                        sfxHover->loop           (true);
			sfxExplosion = new hssSound();     loadSFX      (TEXT("reluctant_hero : SFX_EXPLOSION"),                 sfxExplosion->load         (m_config.hInstance,    SFX_EXPLOSION));                                   sfxExplosion->loop       (false);
    break; }

    case 3: {
			initializeReluctantHero();
      for (int i = 0; i < 30; i++) { _tcscpy(mgInstructions[i], instructions[i]); } mgInstructionsPage = 0; mgiPrevTapped = false; mgiNextTapped = false;
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
void CGame::destroyReluctantHero(CGapiSurface* backbuffer) {

	using namespace ns_ReluctantHero;

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
			delete sfxThankYou;
			delete sfxHover;
			delete background;
			delete player[0];
			delete player[1];
		break; }

		case 3: {
			delete person[0];
			delete person[1];
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
