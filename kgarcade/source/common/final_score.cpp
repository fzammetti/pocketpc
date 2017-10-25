
#include "main.h"


namespace ns_FinalScore {


// ****************************************************************************************************************
// Globals
// ****************************************************************************************************************
CGapiSurface*	background   = NULL;
hssSound*     sfxMusic     = NULL;
bool          musicPlaying = false;
int           musicChannel = NULL;


} // End of namespace


// ****************************************************************************************************************
// ProcessNextFrame handler
// ****************************************************************************************************************
void CGame::pnfFinalScore(CGapiSurface* backbuffer) {

	using namespace ns_FinalScore;

	if (!musicPlaying) {
		musicPlaying = true;
		musicChannel = sndObj.playSound(sfxMusic);
	}

  backbuffer->BltFast(0, 0, background, NULL, NULL, NULL);

  // Text
  GDFILLRECTFX gdfillrectfx;
  gdfillrectfx.dwOpacity = 128;
  backbuffer->FillRect(CRect(30, 5, 210, 49), RGB(240, 240, 240), GDFILLRECT_OPACITY, &gdfillrectfx);
  backbuffer->DrawText(bbCenterPoint, 7, TEXT("Your final score was:"), &font1, GDDRAWTEXT_CENTER, NULL, NULL, NULL);
  TCHAR fScore[52] = TEXT("");
  _stprintf(fScore, TEXT("%d"), overall_score);
  backbuffer->DrawText(bbCenterPoint, 27, fScore, &font1, GDDRAWTEXT_CENTER, NULL, NULL, NULL);

  // Back
  backbuffer->DrawText(bbCenterPoint, 300, TEXT("COMMAND/Click for Main Menu"), &font1_green, GDDRAWTEXT_CENTER, NULL, NULL, NULL);

}


// ****************************************************************************************************************
// KeyDown handler
// ****************************************************************************************************************
void CGame::kuFinalScore(DWORD dwKey) {

	using namespace ns_FinalScore;

  // Back
  if (dwKey == kCommand) {
    hssChannel* c = sndObj.channel(musicChannel);
	  if (c->playing()) { c->stop(); }
    musicPlaying = false;
    musicChannel = NULL;
    writeKGAFile(false, false);
    doDestroy(csMainMenu);
  }

}


// ****************************************************************************************************************
// StylusUp handler
// ****************************************************************************************************************
void CGame::suFinalScore(POINT p) {

  using namespace ns_FinalScore;

	if (PtInRect(CRect(0, 300, 240, 320), p)) { kuFinalScore(kCommand); }

}


// ****************************************************************************************************************
// Loader
// ****************************************************************************************************************
  void CGame::loadFinalScore(CGapiSurface* backbuffer) {

	using namespace ns_FinalScore;

	processEvents = false;

	// Move on to the next step
	loading_step++;

	// Do the appropriate step
	switch(loading_step) {

    case 1: {
      background = new CGapiSurface(); createSurface(TEXT("final_score : GFX_FINAL_SCORE_BACKGROUND"), background->CreateSurface (0, m_config.hInstance, GFX_FINAL_SCORE_BACKGROUND, TEXT("GRAPHICS"))); background->SetColorKey(RGB(255, 128, 255));
			sfxMusic   = new hssSound();     loadSFX      (TEXT("final_score : SFX_MUSIC_WON"),              sfxMusic->load            (m_config.hInstance,    SFX_MUSIC_WON));                                sfxMusic->loop         (true);
      musicPlaying = false;
      musicChannel = NULL;
    break; }

		// End of loading
		default: {
			loading	= false;
			processEvents = true;
		break; }

	}

	// Show the Loading screen
	showLoadingScreen(backbuffer, true, true);

}


// ****************************************************************************************************************
// Destroyer
// ****************************************************************************************************************
void CGame::destroyFinalScore(CGapiSurface* backbuffer) {

	using namespace ns_FinalScore;

	processEvents = false;

	// Move on to the next step
	destroying_step++;

	// Do the appropriate step
	switch(destroying_step) {

		case 1: {
      delete background;
			delete sfxMusic;
		break; }

		default: {
      processEvents = false;
			// All done destroying, start loading the next screen
			current_screen = screen_after_destroy;
			doLoad();
		break; }

	}

	// Show the Loading screen
	showLoadingScreen(backbuffer, true, true);

}
