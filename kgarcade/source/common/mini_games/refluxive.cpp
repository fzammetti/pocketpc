
#include "../main.h"


namespace ns_Refluxive {


// ****************************************************************************************************************
// Defines specific to this mini-game
// ****************************************************************************************************************
#define BOUNCY_DIR_NE 1
#define BOUNCY_DIR_NW 2
#define BOUNCY_DIR_SE 3
#define BOUNCY_DIR_SW 4


// ****************************************************************************************************************
// Globals specific to this mini-game
// ****************************************************************************************************************
TCHAR	instructions[][32] = { TEXT("Refluxive"),
														 TEXT(""),
														 TEXT("They came from beyond:"),
														 TEXT("small, rubber objects"),
														 TEXT("that destroy entire"),
														 TEXT("worlds on a whim.  You"),
														 TEXT("are the Earth's last"),
														 TEXT("line of defense against"),
														 TEXT("the evil bouncy thingys"),
														 TEXT("from space!"),
                             //    ---------------------------
                             TEXT("The Goal"),
														 TEXT(""),
														 TEXT("Keep bouncing the things"),
														 TEXT("as long as you can."),
														 TEXT("Each missed thingy"),
														 TEXT("costs you points."),
														 TEXT("Missing them all"),
														 TEXT("ends the game."),
														 TEXT(""),
														 TEXT(""),
                             //    ---------------------------
                             TEXT("How To Play"),
														 TEXT(""),
														 TEXT("Move left or right to"),
														 TEXT("position your bouncy"),
														 TEXT("thingy returner."),
														 TEXT("Try not to miss"),
														 TEXT("miss any of them,"),
														 TEXT("as if that needs to"),
														 TEXT("be said at all!"),
														 TEXT(""),
                             //    ----------------------------
};

CGapiSurface*	paddle                   = NULL; // Stores the picture of the paddle
CGapiSurface* bouncy                   = NULL;
CGapiSurface* background               = NULL;
hssSound*			sfxMissed                = NULL;
hssSound*			sfxBounce                = NULL;
POINT					bouncy_pos[5];
bool					bouncy_gone[5];
int						bouncy_rotation_angle[5];
int						bouncy_dir[5];


} // End of namespace


// ****************************************************************************************************************
// ProcessNextFrame handler
// ****************************************************************************************************************
void CGame::pnfRefluxive(CGapiSurface* backbuffer) {

	using namespace ns_Refluxive;

	// Background
	backbuffer->BltFast(xadj + 0, yadj + 0, background, NULL, NULL, NULL);

	// Blit paddle and take care of player movements (if not exploding)
	backbuffer->BltFast(xadj + player_pos.x, yadj + player_pos.y, paddle, NULL, GDBLTFAST_KEYSRC, NULL);
	// Moving right
	if (player_dir_east) {
		player_pos.x = player_pos.x + 4;
		// Stop at edge of screen
		if (player_pos.x > 174) { player_pos.x = 174; }
	}
	// Moving left
	if (player_dir_west) {
		player_pos.x = player_pos.x - 4;
		// Stop at edge of screen
		if (player_pos.x < 1) { player_pos.x = 1; }
	}

	// Blit bouncies and take care of movements
	for (int i = 0; i < 3; i++) {
		if (bouncy_dir[i] == BOUNCY_DIR_NE) {
			bouncy_pos[i].x = bouncy_pos[i].x + 3;
			bouncy_pos[i].y = bouncy_pos[i].y - 3;
		}
		if (bouncy_dir[i] == BOUNCY_DIR_NW) {
			bouncy_pos[i].x = bouncy_pos[i].x - 3;
			bouncy_pos[i].y = bouncy_pos[i].y - 3;
		}
		if (bouncy_dir[i] == BOUNCY_DIR_SE) {
			bouncy_pos[i].x = bouncy_pos[i].x + 3;
			bouncy_pos[i].y = bouncy_pos[i].y + 3;
		}
		if (bouncy_dir[i] == BOUNCY_DIR_SW) {
			bouncy_pos[i].x = bouncy_pos[i].x - 3;
			bouncy_pos[i].y = bouncy_pos[i].y + 3;
		}
		RECT destRect;
		SetRect(&destRect, xadj + bouncy_pos[i].x,
											 yadj + bouncy_pos[i].y,
											 xadj + bouncy_pos[i].x + 18,
											 yadj + bouncy_pos[i].y + 18);
		GDBLTFX gdbltfx;
		gdbltfx.nRotationAngle = bouncy_rotation_angle[i];
		backbuffer->Blt(&destRect, bouncy, NULL, GDBLT_KEYSRC  | GDBLT_ROTATIONANGLE, &gdbltfx);
		// Update bouncy rotation
		bouncy_rotation_angle[i] = bouncy_rotation_angle[i] + 750;
		if (bouncy_rotation_angle[i] > 36000) {
			bouncy_rotation_angle[i] = 0;
		}
		// Check for collision with paddle
		POINT colPoint;
		CGapiSurface::Intersect(xadj + player_pos.x, yadj + player_pos.y,
														paddle, NULL,
														xadj + bouncy_pos[i].x, yadj + bouncy_pos[i].y,
														bouncy, NULL, &colPoint);
		// Bounce off the frame edges (horizontal)
		if (bouncy_pos[i].x < 1) {
			if (bouncy_dir[i] == BOUNCY_DIR_NW) {
				bouncy_dir[i] = BOUNCY_DIR_NE;
			}
			if (bouncy_dir[i] == BOUNCY_DIR_SW) {
				bouncy_dir[i] = BOUNCY_DIR_SE;
			}
		}
		if (bouncy_pos[i].x > 182) {
			if (bouncy_dir[i] == BOUNCY_DIR_NE) {
				bouncy_dir[i] = BOUNCY_DIR_NW;
			}
			if (bouncy_dir[i] == BOUNCY_DIR_SE) {
				bouncy_dir[i] = BOUNCY_DIR_SW;
			}
		}
		// Bounce off the frame edges (vertical)
		if (bouncy_pos[i].y < 1) {
			if (bouncy_dir[i] == BOUNCY_DIR_NE) {
				bouncy_dir[i] = BOUNCY_DIR_SE;
			}
			if (bouncy_dir[i] == BOUNCY_DIR_NW) {
				bouncy_dir[i] = BOUNCY_DIR_SW;
			}
		}
		// See if it goes off the bottom of the screen, flag it if so
		if (bouncy_pos[i].y > 200 && bouncy_gone[i] == false) {
			sndObj.playSound(sfxMissed);
			bouncy_gone[i] = true;
			subtractFromScore(50);
		}
		// Check for collision with top of paddle, bounce if so
		if ((colPoint.x != -1 || colPoint.y != -1) && bouncy_pos[i].y < 180) {
			sndObj.playSound(sfxBounce);
			if (bouncy_dir[i] == BOUNCY_DIR_SE &&
					bouncy_pos[i].x + 9 < player_pos.x + 12) {
						bouncy_dir[i] = BOUNCY_DIR_NW;
						addToScore(10);
			}
			if (bouncy_dir[i] == BOUNCY_DIR_SE &&
					bouncy_pos[i].x + 9 > player_pos.x + 12) {
						bouncy_dir[i] = BOUNCY_DIR_NE;
						addToScore(10);
			}
			if (bouncy_dir[i] == BOUNCY_DIR_SW &&
					bouncy_pos[i].x + 9 < player_pos.x + 12) {
						bouncy_dir[i] = BOUNCY_DIR_NW;
						addToScore(10);
			}
			if (bouncy_dir[i] == BOUNCY_DIR_SW &&
					bouncy_pos[i].x + 9 > player_pos.x + 12) {
						bouncy_dir[i] = BOUNCY_DIR_NE;
						addToScore(10);
			}
		}
	}

	// Check to see if all bouncies are gone.  If so, end game.
	if (bouncy_gone[0] && bouncy_gone[1] && bouncy_gone[2]) {
		force_game_over = true;
	}

}


// ****************************************************************************************************************
// KeyDown handler
// ****************************************************************************************************************
void CGame::kdRefluxive(DWORD dwKey) {

	using namespace ns_Refluxive;

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

}


// ****************************************************************************************************************
// KeyUp handler
// ****************************************************************************************************************
void CGame::kuRefluxive(DWORD dwKey) {

	using namespace ns_Refluxive;

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

}


// ****************************************************************************************************************
// Initialize
// ****************************************************************************************************************
void CGame::initializeRefluxive() {

	using namespace ns_Refluxive;

	// Start ship in the middle
	player_pos.x = 88;
	player_pos.y = 188;

	// Bouncy initial positions
	bouncy_pos[0].x = (rand() % 180) + 1;
	bouncy_pos[0].y = 10;
	bouncy_pos[1].x = (rand() % 180) + 1;
	bouncy_pos[1].y = 70;
	bouncy_pos[2].x = (rand() % 180) + 1;
	bouncy_pos[2].y = 140;

	// Bouncy initial rotation angles
	bouncy_rotation_angle[0] = 0;
	bouncy_rotation_angle[1] = 9000;
	bouncy_rotation_angle[2] = 18000;

	// Bouncy initial directions
	bouncy_dir[0] = BOUNCY_DIR_SE;
	bouncy_dir[1] = BOUNCY_DIR_SW;
	bouncy_dir[2] = BOUNCY_DIR_NE;

	// Make sure they aren't gone off the bottom of the screen yet
	bouncy_gone[0] = false;
	bouncy_gone[1] = false;
	bouncy_gone[2] = false;

}


// ****************************************************************************************************************
// Loader
// ****************************************************************************************************************
void CGame::loadRefluxive(CGapiSurface* backbuffer) {

	using namespace ns_Refluxive;

	processEvents = false;

	// Move on to the next step
	loading_step++;

	// Do the appropriate step
	switch(loading_step) {

		case 1: {
			doCommonInit();
      paddle     = NULL;
      bouncy     = NULL;
      background = NULL;
      sfxMissed  = NULL;
      sfxBounce  = NULL;
		break; }

		case 2: {
			paddle     = new CGapiSurface(); createSurface(TEXT("refluxive : GFX_REFLUXIVE_PADDLE"),     paddle->CreateSurface    (0, m_config.hInstance, GFX_REFLUXIVE_PADDLE,     TEXT("GRAPHICS"))); paddle->SetColorKey    (RGB(255, 128, 255));
			bouncy     = new CGapiSurface(); createSurface(TEXT("refluxive : GFX_REFLUXIVE_BOUNCY"),     bouncy->CreateSurface    (0, m_config.hInstance, GFX_REFLUXIVE_BOUNCY,     TEXT("GRAPHICS"))); bouncy->SetColorKey    (RGB(255, 128, 255));
			background = new CGapiSurface(); createSurface(TEXT("refluxive : GFX_REFLUXIVE_BACKGROUND"), background->CreateSurface(0, m_config.hInstance, GFX_REFLUXIVE_BACKGROUND, TEXT("GRAPHICS"))); background->SetColorKey(RGB(255, 128, 255));
      sfxMissed  = new hssSound();     loadSFX      (TEXT("refluxive : SFX_MISSED"),               sfxMissed->load          (m_config.hInstance,    SFX_MISSED));                                 sfxMissed->loop        (false);
      sfxBounce  = new hssSound();     loadSFX      (TEXT("rekluxive : SFX_BOUNCE"),               sfxBounce->load          (m_config.hInstance,    SFX_BOUNCE));                                 sfxBounce->loop        (false);
		break; }

    case 3: {
			initializeRefluxive();
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
void CGame::destroyRefluxive(CGapiSurface* backbuffer) {

	using namespace ns_Refluxive;

	processEvents = false;

	// Move on to the next step
	destroying_step++;

	// Do the appropriate step
	switch(destroying_step) {

		case 1: {
			doCommonCleanup();
		break; }

		case 2: {
			delete sfxMissed;
			delete sfxBounce;
			delete paddle;
			delete bouncy;
			delete background;
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
