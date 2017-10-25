
#include "../main.h"


namespace ns_AlienBabble {


// ****************************************************************************************************************
// Defines specific to this mini-game
// ****************************************************************************************************************
#define STILL  1
#define TURNED 2
#define UP		 3
#define DOWN   4
#define LEFT   5
#define RIGHT  6
#define HIT    7


// ****************************************************************************************************************
// Function prototypes specific to this mini-game
// ****************************************************************************************************************
void newSymbol(int alien_number);
bool checkForHit(int dir);


// ****************************************************************************************************************
// Globals specific to this mini-game
// ****************************************************************************************************************
TCHAR	instructions[][32] = { TEXT("Alien Babble"),
														 TEXT(""),
														 TEXT("You find yourself in a"),
														 TEXT("First Contact situation!"),
														 TEXT("These aliens throw weird"),
														 TEXT("symbols in the air to"),
														 TEXT("communicate, and they"),
														 TEXT("expect you to mimic"),
														 TEXT("them to show that you"),
														 TEXT("understand them."),
                             //    ---------------------------
                             TEXT("The Goal"),
														 TEXT(""),
														 TEXT("Mimic as many alien"),
														 TEXT("symbols correctly as"),
														 TEXT("you can.  Missed"),
														 TEXT("symbols cost you points."),
														 TEXT(""),
														 TEXT(""),
														 TEXT(""),
														 TEXT(""),
                             //    ---------------------------
                             TEXT("How To Play"),
														 TEXT(""),
														 TEXT("Press ACTION to jump"),
														 TEXT("between translator"),
														 TEXT("boxes.  Move in the"),
														 TEXT("direction indicated by"),
														 TEXT("the symbol when it is"),
														 TEXT("within the appropriate"),
														 TEXT("translator box."),
														 TEXT(""),
                             //    ----------------------------
};

CGapiSurface*	box                   = NULL;
CGapiSurface*	alien_still           = NULL;
CGapiSurface*	alien_left            = NULL;
CGapiSurface*	arrow                 = NULL;
CGapiSurface*	target                = NULL;
CGapiSurface*	background            = NULL;
hssSound*     sfxBabbling           = NULL;
hssSound*     sfxHit                = NULL;
POINT					symbols_pos[12];
POINT					symbols_pos_temp[12];
bool          babblePlaying         = false;
int 					alien1_state          = 0;
int						alien1_state_delay    = 0;
int 					alien2_state          = 0;
int						alien2_state_delay    = 0;
int						target_position       = 0;
int						symbol_count          = 0;
int						symbols_dir[12];
int						symbols_dir_temp[12];
int           sfxBabblinghssChannel = 0;


} // End of namespace


// ****************************************************************************************************************
// ProcessNextFrame handler
// ****************************************************************************************************************
void CGame::pnfAlienBabble(CGapiSurface* backbuffer) {

	using namespace ns_AlienBabble;

	if (!babblePlaying) {
		babblePlaying = true;
		sfxBabblinghssChannel = sndObj.playSound(sfxBabbling);
	}

	// Background
	backbuffer->BltFast(xadj, yadj, background, NULL, NULL, NULL);

	// Blit box
	backbuffer->BltFast(xadj + 65,	yadj + 168, box, NULL, GDBLTFAST_KEYSRC, NULL);

	// Blit the aliens
	switch (alien1_state) {
		case STILL: {
			backbuffer->Blt(CRect(xadj + 15,  yadj + 162, xadj + 20 + 43, yadj + 162 + 38),
													 alien_still, NULL, GDBLT_KEYSRC  | GDBLT_MIRRORLEFTRIGHT, NULL);
		break; }
		case TURNED: {
			backbuffer->Blt(CRect(xadj + 20,  yadj + 162, xadj + 20 + 43, yadj + 162 + 38),
													 alien_left, NULL, GDBLT_KEYSRC  | GDBLT_MIRRORLEFTRIGHT, NULL);
		break; }
	}
	switch (alien2_state) {
		case STILL: {
			backbuffer->BltFast(xadj + 137, yadj + 162, alien_still, NULL, GDBLTFAST_KEYSRC, NULL);
		break; }
		case TURNED: {
			backbuffer->BltFast(xadj + 137, yadj + 162, alien_left, NULL, GDBLTFAST_KEYSRC, NULL);
		break; }
	}

	// Blit target
	if (target_position == 1) {
		backbuffer->BltFast(xadj + 23,	yadj + 20, target, NULL, GDBLTFAST_KEYSRC, NULL);
	} else {
		backbuffer->BltFast(xadj + 145, yadj + 20, target, NULL, GDBLTFAST_KEYSRC, NULL);
	}

	// Blit symbols
	RECT destRect;
	GDBLTFX gdbltfx;
	for (int i = 0; i < symbol_count; i++) {
		SetRect(&destRect, xadj + symbols_pos[i].x,      yadj + symbols_pos[i].y,
		 									 xadj + symbols_pos[i].x + 30, yadj + symbols_pos[i].y + 30);
		switch(symbols_dir[i]) {
			case UP: {
				gdbltfx.nRotationAngle = 0;
				backbuffer->Blt(&destRect, arrow, NULL, GDBLT_KEYSRC  | GDBLT_ROTATIONANGLE, &gdbltfx);
			break; }
			case RIGHT: {
				gdbltfx.nRotationAngle = 9000;
				backbuffer->Blt(&destRect, arrow, NULL, GDBLT_KEYSRC  | GDBLT_ROTATIONANGLE, &gdbltfx);
			break; }
			case DOWN: {
				gdbltfx.nRotationAngle = 18000;
				backbuffer->Blt(&destRect, arrow, NULL, GDBLT_KEYSRC  | GDBLT_ROTATIONANGLE, &gdbltfx);
			break; }
			case LEFT: {
				gdbltfx.nRotationAngle = 27000;
				backbuffer->Blt(&destRect, arrow, NULL, GDBLT_KEYSRC  | GDBLT_ROTATIONANGLE, &gdbltfx);
			break; }
		}
		symbols_pos[i].y = symbols_pos[i].y - 2;
	}

	// Tighten up the arrays: remove any elements off the screen
	for (i = 0; i < symbol_count; i++) {
		symbols_pos_temp[i].x = symbols_pos[i].x;
		symbols_pos_temp[i].y = symbols_pos[i].y;
		symbols_dir_temp[i]   = symbols_dir[i];
	}
	int new_symbol_count = 0;
	for (i = 0; i < symbol_count; i++) {
		if (symbols_pos_temp[i].y > -30) {
			symbols_pos[new_symbol_count].x = symbols_pos_temp[i].x;
			symbols_pos[new_symbol_count].y = symbols_pos_temp[i].y;
			symbols_dir[new_symbol_count]   = symbols_dir_temp[i];
			new_symbol_count++;
		} else {
			if (symbols_dir[i] != HIT) {
				subtractFromScore(25);
			}
		}
	}
	symbol_count = new_symbol_count;

	// Update state of alien 1
	alien1_state_delay++;
	if (alien1_state_delay > 25) {
		alien1_state_delay = 0;
		if (alien1_state == TURNED) {
			alien1_state = STILL;
			newSymbol(1);
		} else if (alien1_state == STILL) {
			alien1_state = TURNED;
		}
	}

	// Update state of alien 2
	alien2_state_delay++;
	if (alien2_state_delay > 25) {
		alien2_state_delay = 0;
		if (alien2_state == TURNED) {
			alien2_state = STILL;
			newSymbol(2);
		} else if (alien2_state == STILL) {
			alien2_state = TURNED;
		}
	}

}


// ****************************************************************************************************************
// KeyDown handler
// ****************************************************************************************************************
void CGame::kdAlienBabble(DWORD dwKey) {

	using namespace ns_AlienBabble;

	// Handle up movement events
	if (dwKey == kUp) {
		player_dir_north = true;
		if (checkForHit(UP)) { addToScore(25); sndObj.playSound(sfxHit); }
	}

	// Handle down movement events
	if (dwKey == kDown) {
		player_dir_south = true;
		if (checkForHit(DOWN)) { addToScore(25); sndObj.playSound(sfxHit); }
	}

	// Handle left movement events
	if (dwKey == kLeft) {
		player_dir_west = true;
		if (checkForHit(LEFT)) { addToScore(25); sndObj.playSound(sfxHit); }
	}

	// Handle right movement events
	if (dwKey == kRight) {
		player_dir_east = true;
		if (checkForHit(RIGHT)) { addToScore(25); sndObj.playSound(sfxHit); }
	}

	// Handle keypresses
	if (dwKey == kAction) {
		player_button_down = true;
		if (target_position == 1) {
			target_position = 2;
		} else {
			target_position = 1;
		}
	}

}


// ****************************************************************************************************************
// KeyUp handler
// ****************************************************************************************************************
void CGame::kuAlienBabble(DWORD dwKey) {

	using namespace ns_AlienBabble;

	// Command button
	if (dwKey == kCommand) {
    hssChannel* c = sndObj.channel(sfxBabblinghssChannel);
	  if (c->playing()) { c->stop(); }
    babblePlaying = false;
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
		player_dir_west = false;
	}

	// Handle right movement events
	if (dwKey == kRight) {
		player_dir_east = false;
	}

	// Handle keypresses
	if (dwKey == kAction) {
		player_button_down = false;
	}

}


// ****************************************************************************************************************
// Initialize
// ****************************************************************************************************************
void CGame::initializeAlienBabble() {

	using namespace ns_AlienBabble;

	alien1_state = STILL;
	alien1_state_delay = 0;
	alien2_state = STILL;
	alien2_state_delay = 0;
	symbol_count = 0;
	target_position = 1;

}


// ****************************************************************************************************************
// Ender
// ****************************************************************************************************************
void CGame::endAlienBabble() {

	using namespace ns_AlienBabble;

  hssChannel* c = sndObj.channel(sfxBabblinghssChannel);
	if (c->playing()) { c->stop(); }

}


// ****************************************************************************************************************
// Loader
// ****************************************************************************************************************
void CGame::loadAlienBabble(CGapiSurface* backbuffer) {

	using namespace ns_AlienBabble;

	processEvents = false;

	// Move on to the next step
	loading_step++;

	// Do the appropriate step
	switch(loading_step) {

		case 1: {
			doCommonInit();
      box         = NULL;
      alien_still = NULL;
      alien_left  = NULL;
      arrow       = NULL;
      target      = NULL;
      background  = NULL;
      sfxBabbling = NULL;
      sfxHit      = NULL;
		break; }

		case 2: {
			box         = new CGapiSurface(); createSurface(TEXT("alien_babble : GFX_ALIEN_BABBLE_BOX"),         box->CreateSurface        (0, m_config.hInstance, GFX_ALIEN_BABBLE_BOX, TEXT("GRAPHICS")));         box->SetColorKey        (RGB(255, 128, 255));
			alien_still = new CGapiSurface(); createSurface(TEXT("alien_babble : GFX_ALIEN_BABBLE_ALIEN_STILL"), alien_still->CreateSurface(0, m_config.hInstance, GFX_ALIEN_BABBLE_ALIEN_STILL, TEXT("GRAPHICS"))); alien_still->SetColorKey(RGB(255, 128, 255));
			alien_left  = new CGapiSurface(); createSurface(TEXT("alien_babble : GFX_ALIEN_BABBLE_ALIEN_LEFT"),  alien_left->CreateSurface (0, m_config.hInstance, GFX_ALIEN_BABBLE_ALIEN_LEFT, TEXT("GRAPHICS")));  alien_left->SetColorKey (RGB(255, 128, 255));
			arrow       = new CGapiSurface(); createSurface(TEXT("alien_babble : GFX_ALIEN_BABBLE_ARROW"),       arrow->CreateSurface      (0, m_config.hInstance, GFX_ALIEN_BABBLE_ARROW, TEXT("GRAPHICS")));       arrow->SetColorKey      (RGB(255, 128, 255));
			target      = new CGapiSurface(); createSurface(TEXT("alien_babble : GFX_ALIEN_BABBLE_TARGET"),      target->CreateSurface     (0, m_config.hInstance, GFX_ALIEN_BABBLE_TARGET, TEXT("GRAPHICS")));      target->SetColorKey     (RGB(255, 128, 255));
			background  = new CGapiSurface(); createSurface(TEXT("alien_babble : GFX_ALIEN_BABBLE_BACKGROUND"),  background->CreateSurface (0, m_config.hInstance, GFX_ALIEN_BABBLE_BACKGROUND, TEXT("GRAPHICS")));  background->SetColorKey (RGB(255, 128, 255));
			sfxBabbling = new hssSound();     loadSFX      (TEXT("alien_babble : SFX_ALIEN_BABBLE_BABBLING"),    sfxBabbling->load         (m_config.hInstance,    SFX_ALIEN_BABBLE_BABBLING));                      sfxBabbling->loop       (true);
			sfxHit      = new hssSound();     loadSFX      (TEXT("alien_babble : SFX_ALIEN_BABBLE_HIT"),         sfxHit->load              (m_config.hInstance,    SFX_ALIEN_BABBLE_HIT));                           sfxHit->loop            (false);
      babblePlaying = false;
		break; }

		case 3: {
			initializeAlienBabble();
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
void CGame::destroyAlienBabble(CGapiSurface* backbuffer) {

	using namespace ns_AlienBabble;

	processEvents = false;

	// Move on to the next step
	destroying_step++;

	// Do the appropriate step
	switch(destroying_step) {

		case 1: {
			doCommonCleanup();
		break; }

		case 2: {
			delete box;
      delete background;
			delete alien_still;
			delete alien_left;
			delete arrow;
			delete target;
			delete sfxBabbling;
			delete sfxHit;
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
namespace ns_AlienBabble {


	void newSymbol(int alien_number) {

		int rand_num = 0;
		pRandNum:
		rand_num = (rand() % 100) + 1;
		if (rand_num < 1 || rand_num > 100) { goto pRandNum; }
		// Only add a new symbol sometimes
		if (rand_num > 25) {
			int symbol_dir = 0;
			pickAgain:
			symbol_dir = (rand() % 4) + 1;
			if (symbol_dir != 1 && symbol_dir != 2 && symbol_dir != 3 && symbol_dir != 4) { goto pickAgain; }
			if (symbol_dir == 1) { symbols_dir[symbol_count] = UP;	  }
			if (symbol_dir == 2) { symbols_dir[symbol_count] = RIGHT; }
			if (symbol_dir == 3) { symbols_dir[symbol_count] = DOWN;  }
			if (symbol_dir == 4) { symbols_dir[symbol_count] = LEFT;  }
			symbols_pos[symbol_count].y = 134;
			if (alien_number == 1) {
				symbols_pos[symbol_count].x = 24;
			} else {
				symbols_pos[symbol_count].x = 146;
			}
			symbol_count++;
		}

	}


	bool checkForHit(int dir) {

		bool ret_val = false;
		int x;
		if (target_position == 1) { x = 24; } else { x = 146;	}
		for (int i = 0; i < symbol_count; i++) {
			if (symbols_dir[i] == dir && symbols_pos[i].x == x && symbols_pos[i].y > 9 && symbols_pos[i].y < 39) {
				symbols_pos[i].y = -50;
				symbols_dir[i]	 = HIT;
				ret_val = true;
			}
		}
		return ret_val;

	}


} // End of namespace
