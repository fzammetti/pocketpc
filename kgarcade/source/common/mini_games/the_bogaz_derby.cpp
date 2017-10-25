
#include "../main.h"


namespace ns_TheBogazDerby {


// ****************************************************************************************************************
// Globals specific to this mini-game
// ****************************************************************************************************************
TCHAR	instructions[][32] = { TEXT("The Bogaz Derby"),
														 TEXT(""),
														 TEXT("It might not seem like"),
														 TEXT("it, but racing exotic"),
														 TEXT("hovercars can be very"),
														 TEXT("relaxing."),
														 TEXT(""),
														 TEXT(""),
														 TEXT(""),
														 TEXT(""),
                             //    ---------------------------
                             TEXT("The Goal"),
														 TEXT(""),
														 TEXT("Just keep going until"),
														 TEXT("time runs out,"),
														 TEXT("avoiding the other"),
														 TEXT("hovercars.  If you hit"),
														 TEXT("a hovercar, you lose"),
														 TEXT("points and the"),
														 TEXT("game ends."),
														 TEXT(""),
                             //    ---------------------------
                             TEXT("How To Play"),
														 TEXT(""),
														 TEXT("Move left and right to"),
														 TEXT("avoid other hovercars,"),
														 TEXT("press the ACTION button"),
														 TEXT("to accelerate, release"),
														 TEXT("it to slow down."),
														 TEXT(""),
														 TEXT(""),
														 TEXT(""),
                             //    ----------------------------
};

CGapiSurface* player[4];
CGapiSurface* enemy[4];
CGapiSurface* roadside           = NULL;
CGapiSurface* road               = NULL;
hssSound*     sfxHonk            = NULL;
hssSound*     sfxCrash           = NULL;
hssSound*     sfxCar             = NULL;
POINT         enemy_car;
bool          accelerate         = false;
bool          sfxHonkPlaying     = false;
bool          sfxCarPlaying      = false;
int           sfxCarhssChannel   = 0;
int           v_offset           = 0;
int           speed              = 0;
int           player_frame       = 0;
int           player_frame_delay = 0;
int           enemy_frame        = 0;
int           enemy_frame_delay  = 0;
int           speed_change_delay = 0;


} // End of namespace


// ****************************************************************************************************************
// ProcessNextFrame handler
// ****************************************************************************************************************
void CGame::pnfTheBogazDerby(CGapiSurface* backbuffer) {

	using namespace ns_TheBogazDerby;

	if (!sfxCarPlaying && speed > 0) {
		sfxCarPlaying = true;
		sfxCarhssChannel = sndObj.playSound(sfxCar);
	}
  if (sfxCarPlaying && speed == 0) {
    hssChannel* c = sndObj.channel(sfxCarhssChannel);
	  if (c->playing()) { c->stop(); }
    sfxCarPlaying = false;
  }

  // Deal with collisions
  POINT colPoint;
  CGapiSurface::Intersect(xadj + player_pos.x, yadj + player_pos.y,	player[player_frame], NULL,
																xadj + enemy_car.x, yadj + enemy_car.y, enemy[enemy_frame],
                                NULL, &colPoint);
	if (colPoint.x != -1 || colPoint.y != -1) {
    sndObj.playSound(sfxCrash);
    subtractFromScore(50);
    force_game_over = true;
    return;
  }

	// Blit roadside and road and move it all, if applicable
	int y_loc = -50;
	for (int i = 0; i < 5; i++) {
		backbuffer->BltFast(xadj + 0,   yadj + y_loc + v_offset, roadside, NULL, NULL, NULL);
		backbuffer->BltFast(xadj + 25,  yadj + y_loc + v_offset, road,		  NULL, NULL, NULL);
		backbuffer->BltFast(xadj + 75,  yadj + y_loc + v_offset, road,		  NULL, NULL, NULL);
		backbuffer->BltFast(xadj + 125, yadj + y_loc + v_offset, road,		  NULL, NULL, NULL);
		backbuffer->BltFast(xadj + 175, yadj + y_loc + v_offset, roadside, NULL, NULL, NULL);
		y_loc = y_loc + 50;
	}
	v_offset = v_offset + speed;;
	if (v_offset > 50) { v_offset = 0; }

	// Blit player and deal with movement and animation
	backbuffer->BltFast(xadj + player_pos.x, yadj + player_pos.y, player[player_frame], NULL, GDBLTFAST_KEYSRC, NULL);
	if (accelerate || speed > 0) {
		player_frame_delay++;
		if (player_frame_delay > 1) {
			player_frame_delay = 0;
			player_frame++;
			if (player_frame > 1) { player_frame = 0; }
		}
	}
	if (player_dir_west && speed > 0) {
		player_pos.x = player_pos.x - (speed - 1);
		if (player_pos.x < 26) { player_pos.x = 26; }
	}
	if (player_dir_east && speed > 0) {
		player_pos.x = player_pos.x + (speed - 1);
		if (player_pos.x > 124) { player_pos.x = 124; }
	}

  // Blit enemy car
  backbuffer->BltFast(xadj + enemy_car.x, yadj + enemy_car.y, enemy[enemy_frame], NULL, GDBLTFAST_KEYSRC, NULL);
	enemy_frame_delay++;
	if (enemy_frame_delay > 1) {
		enemy_frame_delay = 0;
		enemy_frame++;
		if (enemy_frame > 1) { enemy_frame = 0; }
	}

	// Handle player speed change
	if (accelerate) {
		speed_change_delay++;
		if (speed_change_delay > 5 ) {
			speed_change_delay = 0;
			speed++;
			if (speed > 6) { speed = 6; }
		}
	} else {
		speed_change_delay++;
		if (speed_change_delay > 5 ) {
			speed_change_delay = 0;
			speed--;
			if (speed < 0) { speed = 0; }
		}
	}

  // Now deal with the enemy cars movement
  enemy_car.y = enemy_car.y -  2;    // Upward movement of enemy
  enemy_car.y = enemy_car.y + speed; // Downward movement of enemy
  if (enemy_car.y > 100 && !sfxHonkPlaying) { sfxHonkPlaying = true; sndObj.playSound(sfxHonk); }
  // When the player passes the enemey, reposition it
  if (enemy_car.y > 202) {
    sfxHonkPlaying = false;
    enemy_car.x = (rand() % 98) + 26;
    enemy_car.y = -80;
    addToScore(10);
  }

}


// ****************************************************************************************************************
// KeyDown handler
// ****************************************************************************************************************
void CGame::kdTheBogazDerby(DWORD dwKey) {

	using namespace ns_TheBogazDerby;

	// Action button
	if (dwKey == kAction) {
    player_button_down = true;
		accelerate = true;
		speed_change_delay = 0;
	}

	// Handle left movement events
	if (dwKey == kLeft) {
		player_dir_west	= true;
	}

	// Handle right movement events
	if (dwKey == kRight) {
		player_dir_east	= true;
	}

}


// ****************************************************************************************************************
// KeyUp handler
// ****************************************************************************************************************
void CGame::kuTheBogazDerby(DWORD dwKey) {

	using namespace ns_TheBogazDerby;

	// Command button
	if (dwKey == kCommand) {
		accelerate = false;
    hssChannel* c = sndObj.channel(sfxCarhssChannel);
	  if (c->playing()) { c->stop(); }
    sfxCarPlaying = false;
    miniGameCommandButtonHandler();
	}

	// Action button
	if (dwKey == kAction) {
    player_button_down = false;
		accelerate = false;
		speed_change_delay = 0;
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
void CGame::initializeTheBogazDerby() {

	using namespace ns_TheBogazDerby;

	v_offset					 = 0;
	speed							 = 0;
	player_frame			 = 0;
	player_frame_delay = 0;
	enemy_frame				 = 0;
	enemy_frame_delay  = 0;
	player_pos.x			 = 75;
	player_pos.y			 = 122;
	accelerate				 = false;
	speed_change_delay = 0;
  enemy_car.x        = (rand() % 98) + 26;
  enemy_car.y        = -80;
  sfxHonkPlaying     = false;
  sfxCarPlaying      = false;

}


// ****************************************************************************************************************
// Ender
// ****************************************************************************************************************
void CGame::endTheBogazDerby() {

	using namespace ns_TheBogazDerby;

  hssChannel* c = sndObj.channel(sfxCarhssChannel);
	if (c->playing()) { c->stop(); }

}


// ****************************************************************************************************************
// Loader
// ****************************************************************************************************************
void CGame::loadTheBogazDerby(CGapiSurface* backbuffer) {

	using namespace ns_TheBogazDerby;

	processEvents = false;

	// Move on to the next step
	loading_step++;

	// Do the appropriate step
	switch(loading_step) {

		case 1: {
			doCommonInit();
      int i = 0;
      for (i = 0; i < 2; i++) { player[i] = NULL; }
      for (i = 0; i < 2; i++) { enemy[i]  = NULL; }
      roadside = NULL;
      road     = NULL;
      sfxHonk  = NULL;
      sfxCrash = NULL;
      sfxCar   = NULL;
		break; }

		case 2: {
			roadside  = new CGapiSurface(); createSurface(TEXT("the_bogaz_derby : GFX_THE_BOGAZ_DERBY_SIDE"),      roadside->CreateSurface (0, m_config.hInstance,  GFX_THE_BOGAZ_DERBY_SIDE,      TEXT("GRAPHICS"))); roadside->SetColorKey (RGB(255, 128, 255));
      road      = new CGapiSurface(); createSurface(TEXT("the_bogaz_derby : GFX_THE_BOGAZ_DERBY_STREET"),    road->CreateSurface     (0, m_config.hInstance,  GFX_THE_BOGAZ_DERBY_STREET,    TEXT("GRAPHICS"))); road->SetColorKey     (RGB(255, 128, 255));
      player[0] = new CGapiSurface(); createSurface(TEXT("the_bogaz_derby : GFX_THE_BOGAZ_DERBY_PLAYER_00"), player[0]->CreateSurface(0, m_config.hInstance,  GFX_THE_BOGAZ_DERBY_PLAYER_00, TEXT("GRAPHICS"))); player[0]->SetColorKey(RGB(255, 128, 255));
			player[1] = new CGapiSurface(); createSurface(TEXT("the_bogaz_derby : GFX_THE_BOGAZ_DERBY_PLAYER_01"), player[1]->CreateSurface(0, m_config.hInstance,  GFX_THE_BOGAZ_DERBY_PLAYER_01, TEXT("GRAPHICS"))); player[1]->SetColorKey(RGB(255, 128, 255));
			enemy[0]  = new CGapiSurface(); createSurface(TEXT("the_bogaz_derby : GFX_THE_BOGAZ_DERBY_ENEMY_00"),  enemy[0]->CreateSurface (0, m_config.hInstance,  GFX_THE_BOGAZ_DERBY_ENEMY_00,  TEXT("GRAPHICS"))); enemy[0]->SetColorKey (RGB(255, 128, 255));
			enemy[1]  = new CGapiSurface(); createSurface(TEXT("the_bogaz_derby : GFX_THE_BOGAZ_DERBY_ENEMY_01"),  enemy[1]->CreateSurface (0, m_config.hInstance,  GFX_THE_BOGAZ_DERBY_ENEMY_01,  TEXT("GRAPHICS"))); enemy[1]->SetColorKey (RGB(255, 128, 255));
      sfxHonk   = new hssSound();      loadSFX      (TEXT("the_bogaz_derby : SFX_BOGAZ_HONK"),                sfxHonk->load           (m_config.hInstance,     SFX_BOGAZ_HONK));                                  sfxHonk->loop         (false);
      sfxCrash  = new hssSound();      loadSFX      (TEXT("the_bogaz_derby : SFX_BOGAZ_CRASH"),               sfxCrash->load          (m_config.hInstance,     SFX_BOGAZ_CRASH));                                 sfxCrash->loop        (false);
      sfxCar    = new hssSound();      loadSFX      (TEXT("the_bogaz_derby : SFX_BOGAZ_CAR"),                 sfxCar->load            (m_config.hInstance,     SFX_BOGAZ_CAR));                                   sfxCar->loop          (true);
    break; }

		case 3: {
			initializeTheBogazDerby();
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
void CGame::destroyTheBogazDerby(CGapiSurface* backbuffer) {

	using namespace ns_TheBogazDerby;

	processEvents = false;

	// Move on to the next step
	destroying_step++;

	// Do the appropriate step
	switch(destroying_step) {

		case 1: {
			doCommonCleanup();
		break; }

		case 2: {
			delete road;
			delete roadside;
			delete player[0];
			delete player[1];
			delete enemy[0];
			delete enemy[1];
      delete sfxHonk;
      delete sfxCrash;
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
