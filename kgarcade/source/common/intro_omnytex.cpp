
#include "main.h"


namespace ns_IntroOmnytex {


// ****************************************************************************************************************
// Globals
// ****************************************************************************************************************
CGapiSurface* logo_omnytex = NULL;
int           fadeVal			 = 0;
int						fadeDir			 = 1;
int           fadeDelay		 = 0;


} // End of namespace


// ****************************************************************************************************************
// ProcessNextFrame handler
// ****************************************************************************************************************
void CGame::pnfIntroOmnytex(CGapiSurface* backbuffer) {

	using namespace ns_IntroOmnytex;

	backbuffer->FillRect(CRect(0, 0, 240, 320), RGB(0, 0, 0), NULL, NULL);

  GDBLTFASTFX gdbltfastfx;
  gdbltfastfx.dwOpacity = fadeVal;
	backbuffer->BltFast((240 - logo_omnytex->GetWidth()) / 2, (320 - logo_omnytex->GetHeight()) / 2, logo_omnytex, NULL, GDBLTFAST_KEYSRC | GDBLTFAST_OPACITY, &gdbltfastfx);

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
			doDestroy(csIntroCrackhead);
		}
	}

}


// ****************************************************************************************************************
// KeyUp handler
// ****************************************************************************************************************
void CGame::kuIntroOmnytex() {

	using namespace ns_IntroOmnytex;

  doDestroy(csIntroCrackhead);

}


// ****************************************************************************************************************
// StylusUp handler
// ****************************************************************************************************************
void CGame::suIntroOmnytex() {

  using namespace ns_IntroOmnytex;

	kuIntroOmnytex();

}


// ****************************************************************************************************************
// Loader
// ****************************************************************************************************************
void CGame::loadIntroOmnytex(CGapiSurface* backbuffer) {

	using namespace ns_IntroOmnytex;

	processEvents = false;

	// Move on to the next step
	loading_step++;

	// Do the appropriate step
	switch(loading_step) {

		case 1: {
			logo_omnytex = new CGapiSurface(); createSurface(TEXT("intro_omnytex : GFX_LOGO_OMNYTEX"), logo_omnytex->CreateSurface (0, m_config.hInstance, GFX_LOGO_OMNYTEX, TEXT("GRAPHICS"))); logo_omnytex->SetColorKey(RGB(255, 128, 255));
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
void CGame::destroyIntroOmnytex(CGapiSurface* backbuffer) {

	using namespace ns_IntroOmnytex;

	processEvents = false;

	// Move on to the next step
	destroying_step++;

	// Do the appropriate step
	switch(destroying_step) {

		case 1: {
			delete logo_omnytex;
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
