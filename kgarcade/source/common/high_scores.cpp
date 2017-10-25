
#include "main.h"


namespace ns_HighScores {


// ****************************************************************************************************************
// Globals
// ****************************************************************************************************************
int current_screenshot = 0;
int current_action = 0; // 0 = sliding in, 1 = paused, 2 = sliding out, 3 = initial delay
int pause_delay = 0;
POINT screenshot_pos;


} // End of namespace


// ****************************************************************************************************************
// ProcessNextFrame handler
// ****************************************************************************************************************
void CGame::pnfHighScores(CGapiSurface* backbuffer) {

	using namespace ns_HighScores;

	int y = 54;

  // Set up for fading
  GDBLTFASTFX gdbltfastfx;
  gdbltfastfx.dwOpacity = fade_value;
  // Scrolling background
	scrollingBackground(backbuffer);
	// Title
	backbuffer->DrawText(bbCenterPoint, 10, TEXT("High Scores"), &font1_green, GDDRAWTEXT_CENTER, NULL, GDBLTFAST_OPACITY, &gdbltfastfx);
	// Lines
	backbuffer->BltFast(0, 40, divider_00, NULL, GDBLTFAST_OPACITY, &gdbltfastfx);
  backbuffer->BltFast(0, 290, divider_00, NULL, GDBLTFAST_OPACITY, &gdbltfastfx);
  // Back
  backbuffer->DrawText(bbCenterPoint, 300,  TEXT("COMMAND/Click for Main Menu"), &font1_green, GDDRAWTEXT_CENTER, NULL, GDBLTFAST_OPACITY, &gdbltfastfx);

	switch (current_action) {
		case 0: { // Slide in
			backbuffer->BltFast(screenshot_pos.x, y, screenshots[current_screenshot], NULL, GDBLTFAST_KEYSRC | GDBLTFAST_OPACITY, &gdbltfastfx);
			screenshot_pos.x = screenshot_pos.x - 15;
			if (screenshot_pos.x == 69) { 
				current_action = 1; 
				pause_delay = 0; 
			}
		break; }
		case 1: { // Pause
			backbuffer->BltFast(screenshot_pos.x, y, screenshots[current_screenshot], NULL, GDBLTFAST_KEYSRC | GDBLTFAST_OPACITY, &gdbltfastfx);
			backbuffer->DrawText(bbCenterPoint, y + 106, mini_game_info[current_screenshot][0], &font1, GDDRAWTEXT_CENTER, NULL, GDBLTFAST_OPACITY, &gdbltfastfx);
			TCHAR szHS1[20] = TEXT("");
			TCHAR szHS2[20] = TEXT("");
			_stprintf(szHS1, TEXT("%d"), miniGameHighsTimed[current_screenshot]);
			_stprintf(szHS2, TEXT("%d"), miniGameHighsPUISS[current_screenshot]);
			backbuffer->DrawText(bbCenterPoint, y + 144, TEXT("Timed Mode:"), &font1, GDDRAWTEXT_CENTER, NULL, GDBLTFAST_OPACITY, &gdbltfastfx);
			backbuffer->DrawText(bbCenterPoint, y + 144 + 18, szHS1, &font1, GDDRAWTEXT_CENTER, NULL, GDBLTFAST_OPACITY, &gdbltfastfx);
			backbuffer->DrawText(bbCenterPoint, y + 144 + 46, TEXT("Play Until I Say Stop Mode:"), &font1, GDDRAWTEXT_CENTER, NULL, GDBLTFAST_OPACITY, &gdbltfastfx);
			backbuffer->DrawText(bbCenterPoint, y + 144 + 64, szHS2, &font1, GDDRAWTEXT_CENTER, NULL, GDBLTFAST_OPACITY, &gdbltfastfx);
			pause_delay++;
			if (pause_delay > 75) {
				current_action = 2;
			}
		break; }
		case 2: { // Slide Out
			backbuffer->BltFast(screenshot_pos.x, y, screenshots[current_screenshot], NULL, GDBLTFAST_KEYSRC | GDBLTFAST_OPACITY, &gdbltfastfx);
			screenshot_pos.x = screenshot_pos.x - 15;
			if (screenshot_pos.x == -111) { 
				current_action = 0; 
				screenshot_pos.x = 264;
				current_screenshot++;
				if (current_screenshot > 24) { 
					current_screenshot = 0; 
				}
			}
		break; }
		case 3: { // Initial Delay
			pause_delay++;
			if (pause_delay > 20) {
				current_action = 0;
			}
		break; }
	}

  // Fading
  screenFader();

}


// ****************************************************************************************************************
// KeyUp handler
// ****************************************************************************************************************
void CGame::kuHighScores(DWORD dwKey) {

	using namespace ns_HighScores;

  // Back
  if (dwKey == kCommand) {
    sndObj.playSound(sfxMisc4);
    fade_function = 1;
		next_screen = csMainMenu;
  }

}


// ****************************************************************************************************************
// StylusUp handler
// ****************************************************************************************************************
void CGame::suHighScores(POINT p) {

  using namespace ns_HighScores;

	// Exit
	if (PtInRect(CRect(0, 300, 240, 320), p)) { 
		kuHighScores(kCommand); 
		return; 
	}

}


// ****************************************************************************************************************
// Utility functions
// ****************************************************************************************************************

void CGame::hisReset() {

  using namespace ns_HighScores;
	pause_delay = 0;
	current_screenshot = 0;
	current_action = 3;
	screenshot_pos.x = 264; 

}