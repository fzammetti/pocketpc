
#include "../main.h"

namespace ns_Glutton {


// ****************************************************************************************************************
// Function prototypes specific to this mini-game
// ****************************************************************************************************************
POINT placeFood();


// ****************************************************************************************************************
// Globals specific to this mini-game
// ****************************************************************************************************************
TCHAR	instructions[][32] = { TEXT("Glutton"),
														 TEXT(""),
														 TEXT("On the planet Trigamop"),
														 TEXT("there is a small creature"),
														 TEXT("called a Garagnack"),
														 TEXT("that does nothing all"),
														 TEXT("day but sliver around"),
														 TEXT("the group eating small"),
														 TEXT("energy pellets getting"),
														 TEXT("ever larger.  Gross!"),
                             //    ---------------------------
                             TEXT("The Goal"),
														 TEXT(""),
														 TEXT("East as many energy"),
														 TEXT("pellets as you can"),
														 TEXT("without eating yourself."),
														 TEXT(""),
														 TEXT(""),
														 TEXT(""),
														 TEXT(""),
														 TEXT(""),
                             //    ---------------------------
                             TEXT("How To Play"),
														 TEXT(""),
														 TEXT("Move up, down, left or"),
														 TEXT("right.  Avoid eating"),
														 TEXT("yourself or going out"),
														 TEXT("of bounds, which ends"),
														 TEXT("the game."),
														 TEXT(""),
														 TEXT(""),
														 TEXT(""),
                             //    ----------------------------
};

CGapiSurface*	head          = NULL;
CGapiSurface*	body          = NULL;
CGapiSurface*	food          = NULL;
CGapiSurface*	background    = NULL;
hssSound*			sfxChomp      = NULL;
hssSound*			sfxSplat      = NULL;
hssSound*			sfxMove       = NULL;
POINT					food_pos;
POINT					segments[102];
int						segment_count = 0;
int						move_delay    = 0;


} // End of namespace


// ****************************************************************************************************************
// ProcessNextFrame handler
// ****************************************************************************************************************
void CGame::pnfGlutton(CGapiSurface* backbuffer) {

	using namespace ns_Glutton;

	// Blit background
	for (int y = 0; y < 5; y++) {
		for (int x = 0; x < 5; x++) {
			backbuffer->BltFast(xadj + (x * 40), yadj + (y * 40), background, NULL, GDBLTFAST_KEYSRC, NULL);
		}
	}


	// Blit snake
  RECT rect;
  GDBLTFX gdbltfx;
	SetRect(&rect, xadj + (segments[0].x * 10),  yadj + (segments[0].y * 10), (xadj + (segments[0].x * 10)) + 10,  (yadj + (segments[0].y * 10) + 10));
  if (player_dir_north) { gdbltfx.nRotationAngle = 0;     }
  if (player_dir_south) { gdbltfx.nRotationAngle = 18000; }
  if (player_dir_east)  { gdbltfx.nRotationAngle = 9000;  }
  if (player_dir_west)  { gdbltfx.nRotationAngle = 27000; }
	backbuffer->Blt(&rect, head, NULL, GDBLTFAST_KEYSRC | GDBLT_ROTATIONANGLE, &gdbltfx);
	for (int i = 1; i < segment_count; i++) {
		backbuffer->BltFast(xadj + (segments[i].x * 10), yadj + (segments[i].y * 10), body, NULL, GDBLTFAST_KEYSRC, NULL);
	}

	// Blit food
	backbuffer->BltFast(xadj + (food_pos.x * 10), yadj + (food_pos.y * 10), food, NULL, GDBLTFAST_KEYSRC, NULL);

	// Move snake
	move_delay++;
	if (move_delay > 2) {
		sndObj.playSound(sfxMove);
		move_delay = 0;
		POINT new_head = segments[0];
		for (i = segment_count - 1; i > 0; i--) {
			segments[i] = segments[i - 1];
		}
		if (player_dir_north || (!player_dir_north && !player_dir_south && !player_dir_east && ! player_dir_west)) {
			new_head.y--;
			segments[0] = new_head;
		}
		if (player_dir_south) {
			new_head.y++;
			segments[0] = new_head;
		}
		if (player_dir_west) {
			new_head.x--;
			segments[0] = new_head;
		}
		if (player_dir_east) {
			new_head.x++;
			segments[0] = new_head;
		}
	}

	// Check for out of bounds, end game if hit
	if (segments[0].x < 0 || segments[0].x > 19 || segments[0].y < 0 || segments[0].y > 19) {
		subtractFromScore(2000);
		sndObj.playSound(sfxSplat);
		force_game_over = true;
	}

	// Check for collision with body, end game if hit
	for (i = 1; i < segment_count; i++) {
		if (segments[0].x == segments[i].x && segments[0].y == segments[i].y) {
			subtractFromScore(2000);
			sndObj.playSound(sfxSplat);
			force_game_over = true;
		}
	}

	// Check for food.  Grow snake if it hits and replace it.
	if (segments[0].x == food_pos.x && segments[0].y == food_pos.y) {
		sndObj.playSound(sfxChomp);
		addToScore(25);
		POINT tail		 = segments[segment_count - 1];
		POINT pre_tail = segments[segment_count - 2];
		POINT new_tail;
		if (tail.x == pre_tail.x && tail.y > pre_tail.y) { // Adding segment on bottom
			new_tail.x = tail.x;
			new_tail.y = tail.y++;
		}
		if (tail.x == pre_tail.x && tail.y < pre_tail.y) { // Adding segment on top
			new_tail.x = tail.x;
			new_tail.y = tail.y--;
		}
		if (tail.x < pre_tail.x && tail.y == pre_tail.y) { // Adding segment on left
			new_tail.x = tail.x--;
			new_tail.y = tail.y;
		}
		if (tail.x > pre_tail.x && tail.y == pre_tail.y) { // Adding segment on right
			new_tail.x = tail.x++;
			new_tail.y = tail.y;
		}
		segments[segment_count] = new_tail;
		segment_count++;
		food_pos = placeFood();
	}

}


// ****************************************************************************************************************
// KeyDown handler
// ****************************************************************************************************************
void CGame::kdGlutton(DWORD dwKey) {

	using namespace ns_Glutton;

	// Handle up movement events
	if (dwKey == kUp && !player_dir_south) {
		player_dir_north = true;
		player_dir_south = false;
		player_dir_east  = false;
		player_dir_west  = false;
	}

	// Handle down movement events
	if (dwKey == kDown && !player_dir_north) {
		player_dir_north = false;
		player_dir_south = true;
		player_dir_east  = false;
		player_dir_west  = false;
	}

	// Handle left movement events
	if (dwKey == kLeft && !player_dir_east) {
		player_dir_north = false;
		player_dir_south = false;
		player_dir_east  = false;
		player_dir_west  = true;
	}

	// Handle right movement events
	if (dwKey == kRight && !player_dir_west) {
		player_dir_north = false;
		player_dir_south = false;
		player_dir_east  = true;
		player_dir_west  = false;
	}

}


// ****************************************************************************************************************
// KeyUp handler
// ****************************************************************************************************************
void CGame::kuGlutton(DWORD dwKey) {

	using namespace ns_Glutton;

	// Command button
	if (dwKey == kCommand) {
    miniGameCommandButtonHandler();
	}

}


// ****************************************************************************************************************
// Initialize
// ****************************************************************************************************************
void CGame::initializeGlutton() {

	using namespace ns_Glutton;

	segment_count		 = 2;
	move_delay			 = 0;
	segments[0].x		 = 9;
	segments[0].y		 = 9;
	segments[1].x		 = 9;
	segments[1].y		 = 10;
	food_pos = placeFood();

}


// ****************************************************************************************************************
// Loader
// ****************************************************************************************************************
void CGame::loadGlutton(CGapiSurface* backbuffer) {

	using namespace ns_Glutton;

	processEvents = false;

	// Move on to the next step
	loading_step++;

	// Do the appropriate step
	switch(loading_step) {

		case 1: {
			doCommonInit();
      head       = NULL;
      body       = NULL;
      food       = NULL;
      background = NULL;
      sfxChomp   = NULL;
      sfxSplat   = NULL;
      sfxMove    = NULL;
		break; }

		case 2: {
			head       = new CGapiSurface(); createSurface(TEXT("glutton : 0x0000"), head->CreateSurface      (0, m_config.hInstance, GFX_GLUTTON_HEAD,       TEXT("GRAPHICS"))); head->SetColorKey      (RGB(255, 128, 255));
			body       = new CGapiSurface(); createSurface(TEXT("glutton : 0x0001"), body->CreateSurface      (0, m_config.hInstance, GFX_GLUTTON_BODY,       TEXT("GRAPHICS"))); body->SetColorKey      (RGB(255, 128, 255));
			food       = new CGapiSurface(); createSurface(TEXT("glutton : 0x0002"), food->CreateSurface      (0, m_config.hInstance, GFX_GLUTTON_FOOD,       TEXT("GRAPHICS"))); food->SetColorKey      (RGB(255, 128, 255));
			background = new CGapiSurface(); createSurface(TEXT("glutton : 0x0003"), background->CreateSurface(0, m_config.hInstance, GFX_GLUTTON_BACKGROUND, TEXT("GRAPHICS"))); background->SetColorKey(RGB(255, 128, 255));
			sfxChomp   = new hssSound();     loadSFX      (TEXT("glutton : 0x0100"), sfxChomp->load           (m_config.hInstance,    SFX_CHOMP));                                sfxChomp->loop         (false);
			sfxSplat   = new hssSound();     loadSFX      (TEXT("glutton : 0x0101"), sfxSplat->load           (m_config.hInstance,    SFX_SPLAT));                                sfxSplat->loop         (false);
			sfxMove    = new hssSound();     loadSFX      (TEXT("glutton : 0x0102"), sfxMove->load            (m_config.hInstance,    SFX_MOVE));                                 sfxMove->loop          (false);
		break; }

    case 3: {
			initializeGlutton();
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
void CGame::destroyGlutton(CGapiSurface* backbuffer) {

	using namespace ns_Glutton;

	processEvents = false;

	// Move on to the next step
	destroying_step++;

	// Do the appropriate step
	switch(destroying_step) {

		case 1: {
			doCommonCleanup();
		break; }

		case 2: {
			delete sfxSplat;
			delete sfxChomp;
			delete sfxMove;
			delete background;
			delete head;
			delete body;
			delete food;
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
namespace ns_Glutton {


	POINT placeFood() {

		int i;
		POINT p;
		pickPoint:
		p.x = rand() % 19;
		p.y = rand() % 19;
		// Make sure food is not placed on the snake
		for (i = 0; i < segment_count; i++) {
			if (p.x == segments[i].x && p.y == segments[i].y) { goto pickPoint;	}
		}
		return p;

	}


} // End of namespace
