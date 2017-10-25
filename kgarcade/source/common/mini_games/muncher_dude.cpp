
#include "../main.h"


namespace ns_MuncherDude {


// ****************************************************************************************************************
// Structures specific to this mini-game
// ****************************************************************************************************************
struct ALIEN {
  POINT position;	        // Position of the alien
  int   direction;        // Direction the alien is moving
	int   state;	          // The state of the alien
	int   frame;            // Frame of animation the alien is currently doing
	int   frameDelay;       // Delay between frame changes
  int   eatenDelay;       // Delay while eaten
  int   reappearingDelay; // Delay while reappearing
  int   reappearingFlash; // Used to flash the alien when reappearing
};


// ****************************************************************************************************************
// Defines specific to this mini-game
// ****************************************************************************************************************
#define dNorth       0
#define dSouth       1
#define dWest        2
#define dEast        3


// ****************************************************************************************************************
// Globals specific to this mini-game
// ****************************************************************************************************************
TCHAR	instructions[][32] = { TEXT("Muncher Dude"),
														 TEXT(""),
														 TEXT("Your hungry, your"),
														 TEXT("starving, your a"),
														 TEXT("a blob of some sort!"),
														 TEXT("And what does a"),
														 TEXT("blob of some sort"),
														 TEXT("eat?  Why, the typical"),
														 TEXT("plain white dot of"),
														 TEXT("course, what else?!?"),
                             //    ---------------------------
                             TEXT("The Goal"),
														 TEXT(""),
                             TEXT("Eat as many dots as you"),
														 TEXT("can while avoiding the"),
														 TEXT("brain-dead aliens.  They"),
														 TEXT("are slow and just kinda"),
														 TEXT("wander around, oblivious"),
														 TEXT("to your presence, but"),
														 TEXT("a single touch kills, so"),
														 TEXT("don't take them lightly!"),
                             //    ---------------------------
                             TEXT("How To Play"),
                             TEXT(""),
														 TEXT("Move up, down, left and"),
														 TEXT("right, avoiding the"),
														 TEXT("stupid aliens and eating"),
														 TEXT("up all the dots."),
														 TEXT(""),
														 TEXT(""),
														 TEXT(""),
														 TEXT(""),
                             //    ----------------------------
};

CGapiSurface* background           = NULL;
CGapiSurface* pellet               = NULL;
CGapiSurface* player[4];
CGapiSurface* imgAliens[4];                  // Images of our aliens
hssSound*     sfxBite              = NULL;
hssSound*     sfxAliens            = NULL;
ALIEN         aliens[5];
bool          facing_west          = false;
bool					alien_sound_playing  = false;
int           player_frame         = 0;
int           player_frame_delay   = 0;
int           pellet_array[12][12];         // 0 = Covered by wall, 1 = Still there, 2 = Eaten
int           sfxAlienshssChannel  = 0;


} // End of namespace


// ****************************************************************************************************************
// ProcessNextFrame handler
// ****************************************************************************************************************
void CGame::pnfMuncherDude(CGapiSurface* backbuffer) {

	using namespace ns_MuncherDude;

	if (!alien_sound_playing) {
		alien_sound_playing = true;
		sfxAlienshssChannel = sndObj.playSound(sfxAliens);
	}

  // Blit background
  backbuffer->BltFast(xadj, yadj, background, NULL, GDBLTFAST_KEYSRC, NULL);

  // Blit grid of pellets
  POINT colPoint;
  int xVal, yVal;
  for (int y = 0; y < 10; y++) {
    yVal = yadj + (y * 20);
    for (int x = 0; x < 10; x++) {
      xVal = xadj + (x * 20);
      // See if the pellet would be hidden by a wall
      CGapiSurface::Intersect(xVal, yVal,	pellet, NULL, xadj, yadj, background, NULL, &colPoint);
      if (colPoint.x == -1 && colPoint.y == -1) {
        // Nope, we can draw it, but only if it's still there
        if (pellet_array[y][x] == 1) {
          backbuffer->BltFast(xadj + (x * 20), yVal, pellet, NULL, GDBLTFAST_KEYSRC, NULL);
        }
      } else {
        // Pellet is covered by a wall, set the value so we know later
        pellet_array[y][x] = 0;
      }
    }
  }

  // Blit player and animate it
  if (facing_west) {
    backbuffer->Blt(CRect(xadj + player_pos.x, yadj + player_pos.y, xadj + player_pos.x + 20, yadj + player_pos.y + 20), player[player_frame], NULL, GDBLTFAST_KEYSRC | GDBLT_MIRRORLEFTRIGHT, NULL);
  } else {
    backbuffer->Blt(CRect(xadj + player_pos.x, yadj + player_pos.y, xadj + player_pos.x + 20,yadj +  player_pos.y + 20), player[player_frame], NULL, GDBLTFAST_KEYSRC, NULL);
  }

  if (player_dir_north || player_dir_south || player_dir_east || player_dir_west) {
    player_frame_delay++;
    if (player_frame_delay > 2) {
      player_frame_delay = 0;
      player_frame++;
      if (player_frame > 1) { player_frame = 0; }
    }
  }

  // Blit aliens and animate them, also check for colission with player and end game if one occurs
  for (int i = 0; i < 3; i++) {
		if (aliens[i].direction == dEast) {
			backbuffer->Blt(CRect(xadj + aliens[i].position.x, yadj + aliens[i].position.y, xadj + aliens[i].position.x + 20, yadj + aliens[i].position.y + 20), imgAliens[aliens[i].frame], NULL, GDBLTFAST_KEYSRC, NULL);
		} else {
			backbuffer->Blt(CRect(xadj + aliens[i].position.x, yadj + aliens[i].position.y, xadj + aliens[i].position.x + 20, yadj + aliens[i].position.y + 20), imgAliens[aliens[i].frame], NULL, GDBLTFAST_KEYSRC | GDBLT_MIRRORLEFTRIGHT, NULL);
		}
    // Animate alien
    aliens[i].frameDelay++;
    if (aliens[i].frameDelay > 2) {
      aliens[i].frameDelay = 0;
      aliens[i].frame++;
      if (aliens[i].frame > 1) { aliens[i].frame = 0; }
    }
    // Move alien
    bool changeDir = false;
    switch (aliens[i].direction) {
      case dEast: {
       // A move MIGHT be valid, see if we'll hit a wall.  If not, go ahead and move.
        changeDir = false;
        aliens[i].position.x++;
        if (aliens[i].position.x > 180) { aliens[i].position.x = 180; changeDir = true; }
        CGapiSurface::Intersect(xadj + aliens[i].position.x, yadj + aliens[i].position.y,	imgAliens[aliens[i].frame], NULL, xadj, yadj,	background, NULL, &colPoint);
        if (colPoint.x != -1 || colPoint.y != -1) { aliens[i].position.x--; changeDir = true; }
        if (changeDir) {
          acd1:
          aliens[i].direction = rand() % 4;
          if (aliens[i].direction < 0 || aliens[i].direction > 3) { goto acd1; }
        }
      break; }
      case dWest: {
        // A move MIGHT be valid, see if we'll hit a wall.  If not, go ahead and move.
        changeDir = false;
        aliens[i].position.x--;
        if (aliens[i].position.x < 0) { aliens[i].position.x = 0; changeDir = true; }
        CGapiSurface::Intersect(xadj + aliens[i].position.x, yadj + aliens[i].position.y,	imgAliens[aliens[i].frame], NULL, xadj, yadj,	background, NULL, &colPoint);
        if (colPoint.x != -1 || colPoint.y != -1) {aliens[i].position.x++; changeDir = true; }
        if (changeDir) {
          acd2:
          aliens[i].direction = rand() % 4;
          if (aliens[i].direction < 0 || aliens[i].direction > 3) { goto acd2; }
        }
      break; }
      case dSouth: {
        // A move MIGHT be valid, see if we'll hit a wall.  If not, go ahead and move.
        changeDir = false;
        aliens[i].position.y++;
        if (aliens[i].position.y > 180) { aliens[i].position.y = 180; changeDir = true; }
        CGapiSurface::Intersect(xadj + aliens[i].position.x, yadj + aliens[i].position.y,	imgAliens[aliens[i].frame], NULL, xadj, yadj,	background, NULL, &colPoint);
        if (colPoint.x != -1 || colPoint.y != -1) { aliens[i].position.y--; changeDir = true; }
        if (changeDir) {
          acd3:
          aliens[i].direction = rand() % 4;
          if (aliens[i].direction < 0 || aliens[i].direction > 3) { goto acd3; }
        }
      break; }
      case dNorth: {
        // A move MIGHT be valid, see if we'll hit a wall.  If not, go ahead and move.
        changeDir = false;
        aliens[i].position.y--;
        if (aliens[i].position.y < 0) { aliens[i].position.y = 0; changeDir = true; }
        CGapiSurface::Intersect(xadj + aliens[i].position.x, yadj + aliens[i].position.y,	imgAliens[aliens[i].frame], NULL, xadj, yadj,	background, NULL, &colPoint);
        if (colPoint.x != -1 || colPoint.y != -1) { aliens[i].position.y++; changeDir = true; }
        if (changeDir) {
          acd4:
          aliens[i].direction = rand() % 4;
          if (aliens[i].direction < 0 || aliens[i].direction > 3) { goto acd4; }
        }
      break; }
    }
    CGapiSurface::Intersect(xadj + player_pos.x, yadj + player_pos.y,	player[player_frame], NULL, xadj + aliens[i].position.x, yadj + aliens[i].position.y,	imgAliens[aliens[i].frame], NULL, &colPoint);
    if (colPoint.x != -1 || colPoint.y != -1) { force_game_over = true; }
  }

  // Move player
  if (player_dir_east && player_pos.x < 180) {
    CGapiSurface::Intersect(xadj + player_pos.x + 2, yadj + player_pos.y,	player[player_frame], NULL, xadj, yadj,	background, NULL, &colPoint);
    if (colPoint.x == -1 && colPoint.y == -1) { player_pos.x = player_pos.x + 2; }
  }
  if (player_dir_west && player_pos.x > 0) {
    CGapiSurface::Intersect(xadj + player_pos.x - 2, yadj + player_pos.y,	player[player_frame], NULL, xadj, yadj,	background, NULL, &colPoint);
    if (colPoint.x == -1 && colPoint.y == -1) { player_pos.x = player_pos.x - 2; }
  }
  if (player_dir_south && player_pos.y < 180) {
    CGapiSurface::Intersect(xadj + player_pos.x, yadj + player_pos.y + 2,	player[player_frame], NULL, xadj, yadj,	background, NULL, &colPoint);
    if (colPoint.x == -1 && colPoint.y == -1) { player_pos.y = player_pos.y + 2; }
  }
  if (player_dir_north && player_pos.y > 0) {
    CGapiSurface::Intersect(xadj + player_pos.x, yadj + player_pos.y - 2,	player[player_frame], NULL, xadj, yadj,	background, NULL, &colPoint);
    if (colPoint.x == -1 && colPoint.y == -1) { player_pos.y = player_pos.y - 2; }
  }

  // Check for colission with pellet, eat it if is happens
  bool still_pellets_left = false;
  for (y = 0; y < 10; y++) {
    yVal = yadj + (y * 20);
    for (int x = 0; x < 10; x++) {
      if (pellet_array[y][x] == 1) { // Only check pellets that are still there
        still_pellets_left = true;
        CGapiSurface::Intersect(xadj + player_pos.x, yadj + player_pos.y,	player[player_frame], NULL, xadj + (x * 20), yVal, pellet, NULL, &colPoint);
        if (colPoint.x != -1 || colPoint.y != -1) { sndObj.playSound(sfxBite); pellet_array[y][x] = false; addToScore(10); }
      }
    }
  }
  // Reset if all the pellets are gone
  if (!still_pellets_left) { initializeMuncherDude(); }

}


// ****************************************************************************************************************
// KeyDown handler
// ****************************************************************************************************************
void CGame::kdMuncherDude(DWORD dwKey) {

	using namespace ns_MuncherDude;

  if (dwKey == kUp) {
    player_dir_north = true;
  }
  if (dwKey == kDown) {
    player_dir_south = true;
  }
  if (dwKey == kLeft) {
    player_dir_west = true;
    facing_west = true;
  }
  if (dwKey == kRight) {
    player_dir_east = true;
    facing_west = false;
  }

}


// ****************************************************************************************************************
// KeyUp handler
// ****************************************************************************************************************
void CGame::kuMuncherDude(DWORD dwKey) {

	using namespace ns_MuncherDude;

	// Command button
	if (dwKey == kCommand) {
    hssChannel* c = sndObj.channel(sfxAlienshssChannel);
	  if (c->playing()) { c->stop(); }
    alien_sound_playing = false;
    miniGameCommandButtonHandler();
	}

  if (dwKey == kUp) {
    player_dir_north = false;
  }
  if (dwKey == kDown) {
    player_dir_south = false;
  }
  if (dwKey == kLeft) {
    player_dir_west = false;
  }
  if (dwKey == kRight) {
    player_dir_east = false;
  }

}


// ****************************************************************************************************************
// Initialize
// ****************************************************************************************************************
void CGame::initializeMuncherDude() {

	using namespace ns_MuncherDude;

  for (int y = 0; y < 10; y++) {
    for (int x = 0; x < 10; x++) {
      pellet_array[y][x] = 1;
    }
  }

  aliens[0].position.x       = 120;
  aliens[0].position.y       = 20;
  aliens[0].direction        = dWest;
  aliens[0].eatenDelay       = 0;
  aliens[0].frame            = 0;
  aliens[0].frameDelay       = 0;
  aliens[0].reappearingDelay = 0;
  aliens[0].reappearingFlash = 0;

  aliens[1].position.x       = 180;
  aliens[1].position.y       = 180;
  aliens[1].direction        = dNorth;
  aliens[1].eatenDelay       = 0;
  aliens[1].frame            = 0;
  aliens[1].frameDelay       = 0;
  aliens[1].reappearingDelay = 0;
  aliens[1].reappearingFlash = 0;

  aliens[2].position.x       = 0;
  aliens[2].position.y       = 180;
  aliens[2].direction        = dEast;
  aliens[2].eatenDelay       = 0;
  aliens[2].frame            = 0;
  aliens[2].frameDelay       = 0;
  aliens[2].reappearingDelay = 0;
  aliens[2].reappearingFlash = 0;

  alien_sound_playing = false;

  sfxAlienshssChannel = 0;

}


// ****************************************************************************************************************
// Ender
// ****************************************************************************************************************
void CGame::endMuncherDude() {

	using namespace ns_MuncherDude;

  hssChannel* c = sndObj.channel(sfxAlienshssChannel);
	if (c->playing()) { c->stop(); }

}


// ****************************************************************************************************************
// Loader
// ****************************************************************************************************************
void CGame::loadMuncherDude(CGapiSurface* backbuffer) {

	using namespace ns_MuncherDude;

	processEvents = false;

	// Move on to the next step
	loading_step++;

	// Do the appropriate step
	switch(loading_step) {

		case 1: {
			doCommonInit();
      int i = 0;
      for (i = 0; i < 2; i++) { player[i]    = NULL; }
      for (i = 0; i < 2; i++) { imgAliens[i] = NULL; }
      pellet    = NULL;
      sfxBite   = NULL;
      sfxAliens = NULL;
		break; }

		case 2: {
			background   = new CGapiSurface(); createSurface(TEXT("muncher_dude : GFX_MUNCHER_DUDE_BACKGROUND"), background->CreateSurface  (0, m_config.hInstance, GFX_MUNCHER_DUDE_BACKGROUND, TEXT("GRAPHICS"))); background->SetColorKey  (RGB(255, 128, 255));
			pellet       = new CGapiSurface(); createSurface(TEXT("muncher_dude : GFX_MUNCHER_DUDE_PELLET"),     pellet->CreateSurface      (0, m_config.hInstance, GFX_MUNCHER_DUDE_PELLET,     TEXT("GRAPHICS"))); pellet->SetColorKey      (RGB(255, 128, 255));
			player[0]    = new CGapiSurface(); createSurface(TEXT("muncher_dude : GFX_MUNCHER_DUDE_PLAYER_00"),  player[0]->CreateSurface   (0, m_config.hInstance, GFX_MUNCHER_DUDE_PLAYER_00,  TEXT("GRAPHICS"))); player[0]->SetColorKey   (RGB(255, 128, 255));
			player[1]    = new CGapiSurface(); createSurface(TEXT("muncher_dude : GFX_MUNCHER_DUDE_PLAYER_01"),  player[1]->CreateSurface   (0, m_config.hInstance, GFX_MUNCHER_DUDE_PLAYER_01,  TEXT("GRAPHICS"))); player[1]->SetColorKey   (RGB(255, 128, 255));
			imgAliens[0] = new CGapiSurface(); createSurface(TEXT("muncher_dude : GFX_MUNCHER_DUDE_ALIEN_00"),   imgAliens[0]->CreateSurface(0, m_config.hInstance, GFX_MUNCHER_DUDE_ALIEN_00,   TEXT("GRAPHICS"))); imgAliens[0]->SetColorKey(RGB(255, 128, 255));
			imgAliens[1] = new CGapiSurface(); createSurface(TEXT("muncher_dude : GFX_MUNCHER_DUDE_ALIEN_01"),   imgAliens[1]->CreateSurface(0, m_config.hInstance, GFX_MUNCHER_DUDE_ALIEN_01,   TEXT("GRAPHICS"))); imgAliens[1]->SetColorKey(RGB(255, 128, 255));
			sfxBite      = new hssSound();     loadSFX      (TEXT("muncher_dude : SFX_MUNCHER_DUDE_BITE"),       sfxBite->load              (m_config.hInstance,    SFX_MUNCHER_DUDE_BITE));                         sfxBite->loop            (false);
			sfxAliens    = new hssSound();     loadSFX      (TEXT("muncher_dude : SFX_MUNCHER_DUDE_ALIENS"),     sfxAliens->load            (m_config.hInstance,    SFX_MUNCHER_DUDE_ALIENS));                       sfxAliens->loop          (true);
    break; }

    case 3: {
			initializeMuncherDude();
      for (int i = 0; i < 30; i++) { _tcscpy(mgInstructions[i], instructions[i]); } mgInstructionsPage = 0; mgiPrevTapped = false; mgiNextTapped = false;
      player_pos.x = 0;
      player_pos.y = 0;
      player_frame = 0;
      player_frame_delay = 0;
      facing_west = false;
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
void CGame::destroyMuncherDude(CGapiSurface* backbuffer) {

	using namespace ns_MuncherDude;

	processEvents = false;

	// Move on to the next step
	destroying_step++;

	// Do the appropriate step
	switch(destroying_step) {

		case 1: {
			doCommonCleanup();
		break; }

		case 2: {
			delete background;
      delete pellet;
      delete player[0];
      delete player[1];
      delete imgAliens[0];
      delete imgAliens[1];
      delete sfxBite;
      delete sfxAliens;
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
