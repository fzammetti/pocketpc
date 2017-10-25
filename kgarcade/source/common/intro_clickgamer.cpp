
#include "main.h"


namespace ns_IntroClickgamer {


// ****************************************************************************************************************
// Globals
// ****************************************************************************************************************
CGapiSurface* logo_clickgamer = NULL;
int           fadeVal			 = 0;
int						fadeDir			 = 1;
int           fadeDelay		 = 0;


} // End of namespace


// ****************************************************************************************************************
// ProcessNextFrame handler
// ****************************************************************************************************************
void CGame::pnfIntroClickgamer(CGapiSurface* backbuffer) {

	using namespace ns_IntroClickgamer;

	backbuffer->FillRect(CRect(0, 0, 240, 320), RGB(0, 0, 0), NULL, NULL);

  GDBLTFASTFX gdbltfastfx;
  gdbltfastfx.dwOpacity = fadeVal;
	backbuffer->BltFast(0, 0, logo_clickgamer, NULL, GDBLTFAST_KEYSRC | GDBLTFAST_OPACITY, &gdbltfastfx);

	// Fade in
	if (fadeDir == 1) {
		fadeVal = fadeVal + 10;
		if (fadeVal == 250) {
			fadeVal = 255;
			fadeDir = 2;
		}
	}

	// Pause
	if (fadeDir == 2) {
		fadeDelay++;
		if (fadeDelay == 48) {
			fadeVal = 250;
			fadeDir = 3;
		}
	}

	// Fade out
	if (fadeDir == 3) {
		fadeVal = fadeVal - 10;
		if (fadeVal == 0) {
			doDestroy(csIntroOmnytex);
		}
	}

}


// ****************************************************************************************************************
// KeyUp handler
// ****************************************************************************************************************
void CGame::kuIntroClickgamer() {

}


// ****************************************************************************************************************
// StylusUp handler
// ****************************************************************************************************************
void CGame::suIntroClickgamer() {

}


// ****************************************************************************************************************
// Loader
// ****************************************************************************************************************
void CGame::loadIntroClickgamer(CGapiSurface* backbuffer) {

	using namespace ns_IntroClickgamer;

	processEvents = false;

	// Move on to the next step
	loading_step++;

	// Do the appropriate step
	switch(loading_step) {

		case 1: {
			logo_clickgamer = new CGapiSurface(); createSurface(TEXT("intro_clickgamer : GFX_LOGO_CLICKGAMER"), logo_clickgamer->CreateSurface (0, m_config.hInstance, GFX_LOGO_CLICKGAMER, TEXT("GRAPHICS"))); logo_clickgamer->SetColorKey(RGB(255, 128, 255));
		break; }

		// End of loading
		default: {
			loading	= false;
			processEvents = true;
		break; }

	}

	// Show the Loading screen
	showLoadingScreen(backbuffer, false, true);

}


// ****************************************************************************************************************
// Destroyer
// ****************************************************************************************************************
void CGame::destroyIntroClickgamer(CGapiSurface* backbuffer) {

	using namespace ns_IntroClickgamer;

	processEvents = false;

	// Move on to the next step
	destroying_step++;

	// Do the appropriate step
	switch(destroying_step) {

		case 1: {
			delete logo_clickgamer;
		break; }

		default: {
			// All done destroying, start loading the next screen
			current_screen = screen_after_destroy;
			doLoad();
		break; }

	}

	// Show the Loading screen
	showLoadingScreen(backbuffer, false, true);

}
