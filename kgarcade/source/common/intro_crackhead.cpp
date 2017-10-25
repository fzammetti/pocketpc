
#include "main.h"


namespace ns_IntroCrackhead {


// ****************************************************************************************************************
// Globals
// ****************************************************************************************************************
CGapiSurface* logo_crackhead = NULL;
int           fadeVal				 = 0;
int						fadeDir				 = 1;
int           fadeDelay			 = 0;


} // End of namespace


// ****************************************************************************************************************
// ProcessNextFrame handler
// ****************************************************************************************************************
void CGame::pnfIntroCrackhead(CGapiSurface* backbuffer) {

	using namespace ns_IntroCrackhead;

	backbuffer->FillRect(CRect(0, 0, 240, 320), RGB(0, 0, 0), NULL, NULL);

  GDBLTFASTFX gdbltfastfx;
  gdbltfastfx.dwOpacity = fadeVal;
	backbuffer->BltFast((240 - logo_crackhead->GetWidth()) / 2, (320 - logo_crackhead->GetHeight()) / 2, logo_crackhead, NULL, GDBLTFAST_KEYSRC | GDBLTFAST_OPACITY, &gdbltfastfx);

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
			doDestroy(csTitleSequence);
		}
	}

}


// ****************************************************************************************************************
// KeyUp handler
// ****************************************************************************************************************
void CGame::kuIntroCrackhead() {

	using namespace ns_IntroCrackhead;

  doDestroy(csTitleSequence);

}


// ****************************************************************************************************************
// StylusUp handler
// ****************************************************************************************************************
void CGame::suIntroCrackhead() {

  using namespace ns_IntroCrackhead;

	kuIntroCrackhead();

}


// ****************************************************************************************************************
// Loader
// ****************************************************************************************************************
void CGame::loadIntroCrackhead(CGapiSurface* backbuffer) {

	using namespace ns_IntroCrackhead;

	processEvents = false;

	// Move on to the next step
	loading_step++;

	// Do the appropriate step
	switch(loading_step) {

		case 1: {
			logo_crackhead = new CGapiSurface(); createSurface(TEXT("intro_crackhead : GFX_LOGO_CRACKHEAD"), logo_crackhead->CreateSurface (0, m_config.hInstance, GFX_LOGO_CRACKHEAD, TEXT("GRAPHICS"))); logo_crackhead->SetColorKey(RGB(255, 128, 255));
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
void CGame::destroyIntroCrackhead(CGapiSurface* backbuffer) {

	using namespace ns_IntroCrackhead;

	processEvents = false;

	// Move on to the next step
	destroying_step++;

	// Do the appropriate step
	switch(destroying_step) {

		case 1: {
			delete logo_crackhead;
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
