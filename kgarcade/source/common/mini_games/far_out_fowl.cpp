
#include "../main.h"


namespace ns_FarOutFowl {


// ****************************************************************************************************************
// Function prototypes specific to this mini-game
// ****************************************************************************************************************
POINT newChickenPosition();


// ****************************************************************************************************************
// Globals specific to this mini-game
// ****************************************************************************************************************
TCHAR	instructions[][32] = { TEXT("Far Out Fowl"),
														 TEXT(""),
														 TEXT("Across the vastness of"),
														 TEXT("space, from the deepest,"),
														 TEXT("darkest reaches of the"),
														 TEXT("known universe comes a"),
														 TEXT("terror so ghastly, all"),
														 TEXT("who see it are chilled"),
														 TEXT("to their core.  It's the"),
														 TEXT("space chicken of DOOM!"),
                             //    ---------------------------
                             TEXT("The Goal"),
														 TEXT(""),
														 TEXT("Catch the eggs that the"),
														 TEXT("evil monster drops on"),
														 TEXT("you in your magnetic"),
														 TEXT("egg catcher thingy."),
														 TEXT("The fewer you drop,"),
														 TEXT("the better (DUH!)."),
														 TEXT("Any that splat on the"),
														 TEXT("deck costs you points."),
                             //    ---------------------------
                             TEXT("How To Play"),
														 TEXT(""),
														 TEXT("Move left or right to"),
														 TEXT("catch the eggs."),
														 TEXT(""),
														 TEXT(""),
														 TEXT(""),
														 TEXT(""),
														 TEXT(""),
														 TEXT(""),
                             //    ----------------------------
};

CGapiSurface* background          = NULL;
CGapiSurface*	catcher             = NULL;
CGapiSurface* egg                 = NULL;
CGapiSurface*	egg_splat           = NULL;
CGapiSurface*	chicken[4];
hssSound*			sfxSplat            = NULL;
hssSound*			sfxCatch            = NULL;
hssSound*			sfxChicken          = NULL;
POINT					chicken_pos;
POINT					chicken_new_pos;
POINT					eggs[102];
POINT					eggs_temp_array[52];
bool          chickenSoundPlaying = false;
int           chicken_frame       = 0;
int           chicken_frame_delay = 0;
int						chicken_egg_speed   = 0;
int						egg_count           = 0;
int						prev_score          = 0;
unsigned long int	score_flip_amount   = 0;
int           sfxChickenhssChannel   = 0;


} // End of namespace


// ****************************************************************************************************************
// ProcessNextFrame handler
// ****************************************************************************************************************
void CGame::pnfFarOutFowl(CGapiSurface* backbuffer) {

	using namespace ns_FarOutFowl;

	if (!chickenSoundPlaying) {
		chickenSoundPlaying = true;
		sfxChickenhssChannel = sndObj.playSound(sfxChicken);
	}

	// Background (so that everything would be in back of non-transparent elements)
	backbuffer->BltFast(xadj + 0, yadj + 0, background, NULL, GDBLTFAST_KEYSRC, NULL);

	// Blit chicken and take care of movements
	backbuffer->BltFast(xadj + chicken_pos.x, yadj + chicken_pos.y, chicken[chicken_frame], NULL, GDBLTFAST_KEYSRC, NULL);
	chicken_frame_delay++;
	if (chicken_frame_delay > 2) {
		chicken_frame_delay = 0;
		chicken_frame++;
		if (chicken_frame > 1) { chicken_frame = 0; }
	}
	if (chicken_pos.x < chicken_new_pos.x) {
		chicken_pos.x = chicken_pos.x + chicken_egg_speed;
		if (chicken_pos.x >= chicken_new_pos.x) {
			POINT egg_pos;
			egg_pos.x = chicken_new_pos.x + 22;
			egg_pos.y = 42;
			eggs[egg_count] = egg_pos;
			egg_count++;
			chicken_new_pos = newChickenPosition();
		}
	} else {
		chicken_pos.x = chicken_pos.x - chicken_egg_speed;
		if (chicken_pos.x <= chicken_new_pos.x) {
			POINT egg_pos;
			egg_pos.x = chicken_new_pos.x + 22;
			egg_pos.y = 42;
			eggs[egg_count] = egg_pos;
			egg_count++;
			chicken_new_pos = newChickenPosition();
		}
	}

	// Blit the eggs, check for colission with catcher, clear egg if caught
	for (int i = 0; i < egg_count; i++) {
		// Display splattered egg
		if (eggs[i].y > 400) {
			backbuffer->BltFast(xadj + eggs[i].x, yadj + 192, egg_splat, NULL, GDBLTFAST_KEYSRC, NULL);
			// Show it for one second (30 frames)
			eggs[i].y--;
			if (eggs[i].y < 470) {
				eggs[i].x = 0;
				eggs[i].y = 0;
      } else {
        if (eggs[i].y == 499) { // At one less than the high value we set when the egg splats, play the sound.  This will have the effect of only playing ocne per egg
          sndObj.playSound(sfxSplat);
        }
      }
		} else {
			// This egg is coming down
			backbuffer->BltFast(xadj + eggs[i].x, yadj + eggs[i].y, egg, NULL, GDBLTFAST_KEYSRC, NULL);
			// See if it collides with the catcher
			POINT colPoint;
			CGapiSurface::Intersect(xadj + player_pos.x, yadj + player_pos.y,
															catcher, NULL,
															xadj + eggs[i].x, yadj + eggs[i].y,
															egg, NULL, &colPoint);
			if (colPoint.x != -1 || colPoint.y != -1) {
				if (eggs[i].y < player_pos.y + 2) { // This makes it so you pretty much have to hit the top of the catcher, not much sides
					// Yep, it was caught
					addToScore(5);
					sndObj.playSound(sfxCatch);
					// Increase speed if it's time
					if (mini_game_score > (prev_score + score_flip_amount)) {
						chicken_egg_speed = chicken_egg_speed + 1;
						prev_score = mini_game_score;
						// Increment the speed flip counter so the speed increases slower as we go
						score_flip_amount = score_flip_amount + 50;
					}
					eggs[i].x = 0;
					eggs[i].y = 0;
				}
			}
		}
	}
	// Move the eggs if they are not splattered and not ready to be cleared
	for (i = 0; i < egg_count; i++) {
		if (!(eggs[i].x == 0 && eggs[i].y == 0) && (eggs[i].y < 400)) {
			eggs[i].y = eggs[i].y + chicken_egg_speed;
			// If the egg reaches the bottom, set the coordinates to 500 so we know we have to display
			// it splatered for a few frames before clearing it.
			if (eggs[i].y > 190) {
				subtractFromScore(5);
				prev_score = mini_game_score;
				eggs[i].y = 500;
			}
		}
	}
	// Clean up the array: copy into a new array any that don't have coordinates 0, 0, reduce the
	// egg_count accordingly, and copy the array back
	int j = 0;
	for (i = 0; i < egg_count; i++) {
		if (!(eggs[i].x == 0 && eggs[i].y == 0)) {
			eggs_temp_array[j] = eggs[i];
			j++;
		}
	}
	// Copy the temp array back over to the real array
	for (i = 0; i < j; i++) {
		eggs[i] = eggs_temp_array[i];
	}
	egg_count = j;

	// Blit paddle and take care of player movements
	backbuffer->BltFast(xadj + player_pos.x, yadj + player_pos.y, catcher, NULL, GDBLTFAST_KEYSRC, NULL);
	// Moving right
	if (player_dir_east) {
		player_pos.x = player_pos.x + 5;
		// Stop at edge of screen
		if (player_pos.x > 155) { player_pos.x = 155; }
	}
	// Moving left
	if (player_dir_west) {
		player_pos.x = player_pos.x - 5;
		// Stop at edge of screen
		if (player_pos.x < 1) { player_pos.x = 1; }
	}

}


// ****************************************************************************************************************
// KeyDown handler
// ****************************************************************************************************************
void CGame::kdFarOutFowl(DWORD dwKey) {

	using namespace ns_FarOutFowl;

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
void CGame::kuFarOutFowl(DWORD dwKey) {

	using namespace ns_FarOutFowl;

	// Command button
	if (dwKey == kCommand) {
    hssChannel* c = sndObj.channel(sfxChickenhssChannel);
	  if (c->playing()) { c->stop(); }
    chickenSoundPlaying = false;
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
void CGame::initializeFarOutFowl() {

	using namespace ns_FarOutFowl;

	// Start catcher in the middle
	player_pos.x = 88;
	player_pos.y = 184;

	// Start chicken off in middle
	chicken_pos.x = 80;
	chicken_pos.y = 2;
	chicken_frame = 0;
	chicken_frame_delay = 0;

	// Determine the chicken's next position
	chicken_new_pos		= newChickenPosition();
	chicken_egg_speed = 3;

	prev_score				= 0;
	score_flip_amount = 25;

}


// ****************************************************************************************************************
// Ender
// ****************************************************************************************************************
void CGame::endFarOutFowl() {

	using namespace ns_FarOutFowl;

  hssChannel* c = sndObj.channel(sfxChickenhssChannel);
	if (c->playing()) { c->stop(); }

}


// ****************************************************************************************************************
// Loader
// ****************************************************************************************************************
void CGame::loadFarOutFowl(CGapiSurface* backbuffer) {

	using namespace ns_FarOutFowl;

	processEvents = false;

	// Move on to the next step
	loading_step++;

	// Do the appropriate step
	switch(loading_step) {

		case 1: {
			doCommonInit();
      int i = 0;
      for (i = 0; i < 2; i++) { chicken[i] = NULL; }
      background = NULL;
      catcher    = NULL;
      egg        = NULL;
      egg_splat  = NULL;
      sfxSplat   = NULL;
      sfxCatch   = NULL;
      sfxChicken = NULL;

		break; }

		case 2: {
			background = new CGapiSurface(); createSurface(TEXT("far_out_fowl : GFX_FAR_OUT_FOWL_BACKGROUND"), background->CreateSurface(0, m_config.hInstance, GFX_FAR_OUT_FOWL_BACKGROUND, TEXT("GRAPHICS"))); background->SetColorKey(RGB(255, 128, 255));
			catcher    = new CGapiSurface(); createSurface(TEXT("far_out_fowl : GFX_FAR_OUT_FOWL_CATCHER"),    catcher->CreateSurface   (0, m_config.hInstance, GFX_FAR_OUT_FOWL_CATCHER,    TEXT("GRAPHICS"))); catcher->SetColorKey   (RGB(255, 128, 255));
			chicken[0] = new CGapiSurface(); createSurface(TEXT("far_out_fowl : GFX_FAR_OUT_FOWL_CHICKEN_00"), chicken[0]->CreateSurface(0, m_config.hInstance, GFX_FAR_OUT_FOWL_CHICKEN_00, TEXT("GRAPHICS"))); chicken[0]->SetColorKey(RGB(255, 128, 255));
			chicken[1] = new CGapiSurface(); createSurface(TEXT("far_out_fowl : GFX_FAR_OUT_FOWL_CHICKEN_01"), chicken[1]->CreateSurface(0, m_config.hInstance, GFX_FAR_OUT_FOWL_CHICKEN_01, TEXT("GRAPHICS"))); chicken[1]->SetColorKey(RGB(255, 128, 255));
			egg        = new CGapiSurface(); createSurface(TEXT("far_out_fowl : GFX_FAR_OUT_FOWL_EGG"),        egg->CreateSurface       (0, m_config.hInstance, GFX_FAR_OUT_FOWL_EGG,        TEXT("GRAPHICS"))); egg->SetColorKey       (RGB(255, 128, 255));
			egg_splat  = new CGapiSurface(); createSurface(TEXT("far_out_fowl : GFX_FAR_OUT_FOWL_EGG_SPLAT"),  egg_splat->CreateSurface (0, m_config.hInstance, GFX_FAR_OUT_FOWL_EGG_SPLAT,  TEXT("GRAPHICS"))); egg_splat->SetColorKey (RGB(255, 128, 255));
			sfxSplat   = new hssSound();     loadSFX      (TEXT("far_out_fowl : SFX_SPLAT"),                   sfxSplat->load           (m_config.hInstance,    SFX_SPLAT));                                     sfxSplat->loop         (false);
			sfxCatch   = new hssSound();     loadSFX      (TEXT("far_out_fowl : SFX_FAR_OUT_FOWL_CATCH"),      sfxCatch->load           (m_config.hInstance,    SFX_FAR_OUT_FOWL_CATCH));                        sfxCatch->loop         (false);
			sfxChicken = new hssSound();     loadSFX      (TEXT("far_out_fowl : SFX_FAR_OUT_FOWL_CHICKEN"),    sfxChicken->load         (m_config.hInstance,    SFX_FAR_OUT_FOWL_CHICKEN));                      sfxChicken->loop       (true);
		break; }

    case 3: {
			initializeFarOutFowl();
      for (int i = 0; i < 30; i++) { _tcscpy(mgInstructions[i], instructions[i]); } mgInstructionsPage = 0; mgiPrevTapped = false; mgiNextTapped = false;
      chickenSoundPlaying = false;
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
void CGame::destroyFarOutFowl(CGapiSurface* backbuffer) {

	using namespace ns_FarOutFowl;

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
			delete catcher;
			delete chicken[0];
			delete chicken[1];
			delete egg;
			delete egg_splat;
      delete sfxSplat;
			delete sfxCatch;
			delete sfxChicken;
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
namespace ns_FarOutFowl {


	POINT newChickenPosition() {

		POINT ncp;
		ncp.x = (rand() % 151) + 1;
		ncp.y = chicken_pos.y;
		return ncp;

	}


} // End of namespace
