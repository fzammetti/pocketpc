
#include "../main.h"


namespace ns_CopyCat {


// ****************************************************************************************************************
// Defines specific to this mini-game
// ****************************************************************************************************************
#define SEQUENCEPLAYING 1
#define PLAYERMOVING    2
#define SELECTION       3


// ****************************************************************************************************************
// Globals specific to this mini-game
// ****************************************************************************************************************
TCHAR	instructions[][32] = { TEXT("CopyCat"),
														 TEXT(""),
														 TEXT("Every sentient species"),
														 TEXT("in the universe has"),
														 TEXT("at least one thing in"),
														 TEXT("common: a game just like"),
														 TEXT("this one!  Mimic the"),
														 TEXT("ever-expanding pattern"),
														 TEXT("of lighted alien symbols"),
														 TEXT("until your brain melts."),
                             //    ---------------------------
                             TEXT("The Goal"),
														 TEXT(""),
														 TEXT("Mimic the sequence"),
														 TEXT("until you mess up, or"),
														 TEXT("time elapses, whichever"),
														 TEXT("comes first.  The"),
														 TEXT("farther you go, the"),
														 TEXT("more points you get."),
														 TEXT(""),
														 TEXT(""),
                             //    ---------------------------
                             TEXT("How To Play"),
														 TEXT(""),
														 TEXT("When it's your turn, move"),
														 TEXT("up, down, left or right"),
														 TEXT("to highlight a symbol,"),
														 TEXT("then press ACTION to"),
														 TEXT("activate it.  Keep"),
														 TEXT("doing this for the"),
														 TEXT("entire sequence."),
														 TEXT(""),
                             //    ----------------------------
};

CGapiSurface* symbols[6];
CGapiSurface* symbols_highlight[6];
hssSound*			sfxTones[6];
bool					selection_pause           = false;
bool					sequence_tone_play        = false;
bool					play_pause                = false;
int						pos_x                     = 0;
int						pos_y                     = 0;
int						sequence_place            = 0;
int						play_place                = 0;
int						play_delay                = 0;
int						game_state                = 0;
int						player_sequence_place     = 0;
int						selection_delay           = 0;
int						sequence_play_start_delay = 0;
int						sequence[102];
int						player_sequence[102];


} // End of namespace


// ****************************************************************************************************************
// ProcessNextFrame handler
// ****************************************************************************************************************
void CGame::pnfCopyCat(CGapiSurface* backbuffer) {

	using namespace ns_CopyCat;

  // Fill background
  backbuffer->FillRect(CRect(xadj, yadj, xadj + 200, yadj + 200), RGB(128, 128, 128), NULL, NULL);

	// If not playing sequence, draw the square under the current symbol
	if (game_state == PLAYERMOVING) {
		backbuffer->DrawText(bbCenterPoint, yadj + 91, TEXT("Your Turn"), &font1, GDDRAWTEXT_CENTER, NULL, NULL, NULL);
		if (pos_x == 1 && pos_y == 1) {
			backbuffer->FillRect(CRect(xadj + 8,   yadj + 5,   xadj + 8   + 85, yadj + 5   + 85), RGB(255, 255, 255), NULL, NULL);
		}
		if (pos_x == 2 && pos_y == 1) {
			backbuffer->FillRect(CRect(xadj + 107, yadj + 5,   xadj + 107 + 85, yadj + 5   + 85), RGB(255, 255, 255), NULL, NULL);
		}
		if (pos_x == 1 && pos_y == 2) {
			backbuffer->FillRect(CRect(xadj + 8,   yadj + 112, xadj + 8   + 85, yadj + 112 + 85), RGB(255, 255, 255), NULL, NULL);
		}
		if (pos_x == 2 && pos_y == 2) {
			backbuffer->FillRect(CRect(xadj + 107, yadj + 112, xadj + 107 + 85, yadj + 112 + 85), RGB(255, 255, 255), NULL, NULL);
		}
	}

	// Blit the symbols in their normal state (always)
	backbuffer->BltFast(xadj + 8,   yadj + 5,   symbols[0], NULL, GDBLTFAST_KEYSRC, NULL);
	backbuffer->BltFast(xadj + 107, yadj + 5,   symbols[1], NULL, GDBLTFAST_KEYSRC, NULL);
	backbuffer->BltFast(xadj + 8,   yadj + 112, symbols[2], NULL, GDBLTFAST_KEYSRC, NULL);
	backbuffer->BltFast(xadj + 107, yadj + 112, symbols[3], NULL, GDBLTFAST_KEYSRC, NULL);

	// We're playing the sequence...
	if (game_state == SEQUENCEPLAYING) {
		backbuffer->DrawText(bbCenterPoint, yadj + 91, TEXT("Try To Remember"), &font1, GDDRAWTEXT_CENTER, NULL, NULL, NULL);
		sequence_play_start_delay++;
		if (sequence_play_start_delay > 10) {
			if (!sequence_tone_play) {
				sndObj.playSound(sfxTones[sequence[play_place] - 1]);
				sequence_tone_play = true;
			}
			// See if we're in the pause in between or not.
			// If not, go ahead and highlight the next symbol in sequence
			if (!play_pause) {
				switch (sequence[play_place]) {
					case 1: {
						backbuffer->BltFast(xadj + 8,   yadj + 5,   symbols_highlight[0], NULL, GDBLTFAST_KEYSRC, NULL);
					break; }
					case 2: {
						backbuffer->BltFast(xadj + 107, yadj + 5,   symbols_highlight[1], NULL, GDBLTFAST_KEYSRC, NULL);
					break; }
					case 3: {
						backbuffer->BltFast(xadj + 8,   yadj + 112, symbols_highlight[2], NULL, GDBLTFAST_KEYSRC, NULL);
					break; }
					case 4: {
						backbuffer->BltFast(xadj + 107, yadj + 112, symbols_highlight[3], NULL, GDBLTFAST_KEYSRC, NULL);
					break; }
				}
				// If the symbol has been highlighted long enough...
				play_delay++;
				if (play_delay > 10) {
					// Go to the next element in sequence and start the pause countdown
					play_place++;
					play_delay				 = 0;
					play_pause				 = true;
					sequence_tone_play = false;
					// If we move beyond the current element in sequence, stop the playing loop
					if (play_place > sequence_place) {
						sequence_play_start_delay = 0;
						game_state = PLAYERMOVING;
						play_place = 0;
						play_pause = false;
					}
				}
			// We must be pausing...
			} else {
				play_delay++;
				// See if it's time to continue playing
				if (play_delay > 1) {
					// It is, so reset the delay and get out of pause mode
					play_delay = 0;
					play_pause = false;
				}
			}
		}
	}

	// Highlight selection user last made
	if (game_state == SELECTION) {
		backbuffer->DrawText(bbCenterPoint, yadj + 91, TEXT("Your Turn"), &font1, GDDRAWTEXT_CENTER, NULL, NULL, NULL);
		if (!selection_pause) {
			switch (player_sequence[player_sequence_place - 1]) {
				case 1: {
					backbuffer->BltFast(xadj + 8,   yadj + 5,   symbols_highlight[0], NULL, GDBLTFAST_KEYSRC, NULL);
				break; }
				case 2: {
					backbuffer->BltFast(xadj + 107, yadj + 5,   symbols_highlight[1], NULL, GDBLTFAST_KEYSRC, NULL);
				break; }
				case 3: {
					backbuffer->BltFast(xadj + 8,   yadj + 112, symbols_highlight[2], NULL, GDBLTFAST_KEYSRC, NULL);
				break; }
				case 4: {
					backbuffer->BltFast(xadj + 107, yadj + 112, symbols_highlight[3], NULL, GDBLTFAST_KEYSRC, NULL);
				break; }
			}
			selection_delay++;
			if (selection_delay > 2) {
				selection_delay = 0;
				selection_pause = true;
			}
		} else {
			// Slight pause after highlighting
			selection_delay++;
			if (selection_delay > 2) {
				selection_delay = 0;
				selection_pause = false;
				// If their count is greater than the sequence place, add one to the sequence place and play the sequence,
				// and clear their entry array
				if (player_sequence_place > sequence_place) {
					sequence_place++;
					pos_x = 1;
					pos_y = 1;
					for (int i = 0; i < 100; i++) {
						player_sequence[i] = 0;
					}
					player_sequence_place = 0;
					game_state = SEQUENCEPLAYING;
				} else {
					game_state = PLAYERMOVING;
				}
			}
		}
	}

}


// ****************************************************************************************************************
// KeyDown handler
// ****************************************************************************************************************
void CGame::kdCopyCat(DWORD dwKey) {

	using namespace ns_CopyCat;

	if (game_state != SEQUENCEPLAYING) {

		if (dwKey == kUp) {
			pos_y--;
			if (pos_y < 1) {
				pos_y = 2;
			}
		}

		if (dwKey == kDown) {
			pos_y++;
			if (pos_y > 2) {
				pos_y = 1;
			}
		}

		if (dwKey == kLeft) {
			pos_x--;
			if (pos_x < 1) {
				pos_x = 2;
			}
		}

		if (dwKey == kRight) {
			pos_x++;
			if (pos_x > 2) {
				pos_x = 1;
			}
		}

		// Handle keypresses
		if (dwKey == kAction) {
			player_button_down = true;
			// Determine which square they selected
			int what_symbol;
			if (pos_x == 1 && pos_y == 1) { what_symbol = 1; }
			if (pos_x == 2 && pos_y == 1) { what_symbol = 2; }
			if (pos_x == 1 && pos_y == 2) { what_symbol = 3; }
			if (pos_x == 2 && pos_y == 2) { what_symbol = 4; }
			sndObj.playSound(sfxTones[what_symbol - 1]);
			// Add it to the array of their entries in the correct place
			player_sequence[player_sequence_place] = what_symbol;
			player_sequence_place++;
			// Compare their entry array so far with the sequence array, force game over when they miss
			for (int i = 0; i < player_sequence_place; i++) {
				if (sequence[i] != player_sequence[i]) {
					force_game_over = true;
					return;
				}
			}
			addToScore(25);
			game_state			= SELECTION;
			selection_delay	= 0;
		}

	}

}


// ****************************************************************************************************************
// KeyUp handler
// ****************************************************************************************************************
void CGame::kuCopyCat(DWORD dwKey) {

	using namespace ns_CopyCat;

	// Command button
	if (dwKey == kCommand) {
    miniGameCommandButtonHandler();
	}

	// Handle keypresses
	if (dwKey == kAction) {
		player_button_down = false;
	}

}


// ****************************************************************************************************************
// Initialize
// ****************************************************************************************************************
void CGame::initializeCopyCat() {

	using namespace ns_CopyCat;

	// Determine our sequence out to 100 moves
	for (int i = 0; i < 100; i++) {
		int nextSeq = 0;
		pickNextSeq:
		nextSeq = (rand() % 4) + 1;
		if (nextSeq < 1 || nextSeq > 4) { goto pickNextSeq; }
		sequence[i] = nextSeq;
	}
	sequence_place	= 0;
	selection_delay = 0;
	selection_pause = false;

	// Start off playing the sequence at the first element
	game_state = SEQUENCEPLAYING;
	play_delay = 0;
	play_place = 0;
	play_pause = false;

	// Start us in the upper left-hand corner
	pos_x											= 1;
	pos_y											= 1;
	player_sequence_place			= 0;
	sequence_play_start_delay = 0;
	sequence_tone_play				= false;

}


// ****************************************************************************************************************
// Loader
// ****************************************************************************************************************
void CGame::loadCopyCat(CGapiSurface* backbuffer) {

	using namespace ns_CopyCat;

	processEvents = false;

	// Move on to the next step
	loading_step++;

	// Do the appropriate step
	switch(loading_step) {

		case 1: {
			doCommonInit();
      int i = 0;
      for (i = 0; i < 4; i++) { symbols[i]           = NULL; }
      for (i = 0; i < 4; i++) { symbols_highlight[i] = NULL; }
      for (i = 0; i < 4; i++) { sfxTones[i]          = NULL; }
		break; }

		case 2: {
			symbols[0]           = new CGapiSurface(); createSurface(TEXT("copycat : GFX_COPYCAT_SYMBOL_00"),           symbols[0]->CreateSurface          (0, m_config.hInstance, GFX_COPYCAT_SYMBOL_00,           TEXT("GRAPHICS"))); symbols[0]->SetColorKey          (RGB(255, 128, 255));
			symbols[1]           = new CGapiSurface(); createSurface(TEXT("copycat : GFX_COPYCAT_SYMBOL_01"),           symbols[1]->CreateSurface          (0, m_config.hInstance, GFX_COPYCAT_SYMBOL_01,           TEXT("GRAPHICS"))); symbols[1]->SetColorKey          (RGB(255, 128, 255));
			symbols[2]           = new CGapiSurface(); createSurface(TEXT("copycat : GFX_COPYCAT_SYMBOL_02"),           symbols[2]->CreateSurface          (0, m_config.hInstance, GFX_COPYCAT_SYMBOL_02,           TEXT("GRAPHICS"))); symbols[2]->SetColorKey          (RGB(255, 128, 255));
			symbols[3]           = new CGapiSurface(); createSurface(TEXT("copycat : GFX_COPYCAT_SYMBOL_03"),           symbols[3]->CreateSurface          (0, m_config.hInstance, GFX_COPYCAT_SYMBOL_03,           TEXT("GRAPHICS"))); symbols[3]->SetColorKey          (RGB(255, 128, 255));
			symbols_highlight[0] = new CGapiSurface(); createSurface(TEXT("copycat : GFX_COPYCAT_SYMBOL_HIGHLIGHT_00"), symbols_highlight[0]->CreateSurface(0, m_config.hInstance, GFX_COPYCAT_SYMBOL_HIGHLIGHT_00, TEXT("GRAPHICS"))); symbols_highlight[0]->SetColorKey(RGB(255, 128, 255));
			symbols_highlight[1] = new CGapiSurface(); createSurface(TEXT("copycat : GFX_COPYCAT_SYMBOL_HIGHLIGHT_01"), symbols_highlight[1]->CreateSurface(0, m_config.hInstance, GFX_COPYCAT_SYMBOL_HIGHLIGHT_01, TEXT("GRAPHICS"))); symbols_highlight[1]->SetColorKey(RGB(255, 128, 255));
			symbols_highlight[2] = new CGapiSurface(); createSurface(TEXT("copycat : GFX_COPYCAT_SYMBOL_HIGHLIGHT_02"), symbols_highlight[2]->CreateSurface(0, m_config.hInstance, GFX_COPYCAT_SYMBOL_HIGHLIGHT_02, TEXT("GRAPHICS"))); symbols_highlight[2]->SetColorKey(RGB(255, 128, 255));
			symbols_highlight[3] = new CGapiSurface(); createSurface(TEXT("copycat : GFX_COPYCAT_SYMBOL_HIGHLIGHT_03"), symbols_highlight[3]->CreateSurface(0, m_config.hInstance, GFX_COPYCAT_SYMBOL_HIGHLIGHT_03, TEXT("GRAPHICS"))); symbols_highlight[3]->SetColorKey(RGB(255, 128, 255));
			sfxTones[0]          = new hssSound();     loadSFX      (TEXT("copycat : SFX_TONE_A"),                      sfxTones[0]->load                  (m_config.hInstance,    SFX_TONE_A));                                        sfxTones[0]->loop                (false);
			sfxTones[1]          = new hssSound();	   loadSFX      (TEXT("copycat : SFX_TONE_B"),                      sfxTones[1]->load                  (m_config.hInstance,    SFX_TONE_B));                                        sfxTones[1]->loop                (false);
			sfxTones[2]          = new hssSound();     loadSFX      (TEXT("copycat : SFX_TONE_C"),                      sfxTones[2]->load                  (m_config.hInstance,    SFX_TONE_C));                                        sfxTones[2]->loop                (false);
			sfxTones[3]          = new hssSound();     loadSFX      (TEXT("copycat : SFX_TONE_D"),                      sfxTones[3]->load                  (m_config.hInstance,    SFX_TONE_D));                                        sfxTones[3]->loop                (false);
		break; }

    case 3: {
			initializeCopyCat();
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
void CGame::destroyCopyCat(CGapiSurface* backbuffer) {

	using namespace ns_CopyCat;

	processEvents = false;

	// Move on to the next step
	destroying_step++;

	// Do the appropriate step
	switch(destroying_step) {

		case 1: {
			doCommonCleanup();
		break; }

		case 2: {
			delete sfxTones[0];
			delete sfxTones[1];
			delete sfxTones[2];
			delete sfxTones[3];
			delete symbols[0];
			delete symbols[1];
			delete symbols[2];
			delete symbols[3];
			delete symbols_highlight[0];
			delete symbols_highlight[1];
			delete symbols_highlight[2];
			delete symbols_highlight[3];
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

