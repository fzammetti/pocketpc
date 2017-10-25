
#include "main.h"


namespace ns_TitleSequence {


// ****************************************************************************************************************
// Globals
// ****************************************************************************************************************
CGapiSurface* kangImg            = NULL;
CGapiSurface* letters[20];
hssSound*			sfxBackground      = NULL;
hssSound*			sfxCrash           = NULL;
hssSound*			sfxKrelmac         = NULL;
hssSound*			sfxGentoo          = NULL;
bool          background_started = false;
bool          gentoo_started     = false;
bool          krelmac_started    = false;
int           currentLetter      = 0;
int           currentFadeVal     = 0;
int           fadeVals[22]       = { 0, 0, 15, 30, 45, 60, 75, 90, 105, 120, 135, 150, 165, 180, 195, 210, 225, 240, 255, 255 };
int           bounceVals[34]     = { -30, 30, -28, 28, -26, 26, -24, 24, -22, 22, -20, 20, -18, 18, -16, 16, -14, 14, -12, 12, -10, 10, -8, 8, -6, 6, -4, 4, -2, 2, -1, 1 };
int           kangY              = -25;
int           bounce_index       = 0;
int           title_step         = 0;
int           end_delay          = 0;
int           gentoo_delay       = 42;
int           krelmac_delay      = 48;


} // End of namespace


// ****************************************************************************************************************
// ProcessNextFrame handler
// ****************************************************************************************************************
void CGame::pnfTitleSequence(CGapiSurface* backbuffer) {

	using namespace ns_TitleSequence;

  // Start background SFX if not started yet
  if (!background_started) {
    background_started = true;
    sndObj.playSound(sfxBackground);
  }

  // Letters fading in
  if (title_step == 0) {
    GDBLTFASTFX gdbltfastfx;
    gdbltfastfx.dwOpacity = fadeVals[currentFadeVal];
 	  backbuffer->BltFast(0, 140, letters[currentLetter], NULL, GDBLTFAST_KEYSRC | GDBLTFAST_OPACITY, &gdbltfastfx);
    currentFadeVal++;
    if (currentFadeVal > 19) {
      currentFadeVal = 0;
      currentLetter++;
      if (currentLetter > 17) {
        title_step = 1;
      }
    }
  }

  // Krelmac & Gentoo falling down
  if (title_step == 1) {
    backbuffer->FillRect(CRect(0, kangY, 240, kangY + 25), RGB(0, 0, 0), 0, NULL);
    backbuffer->BltFast(0, kangY, kangImg, NULL, GDBLTFAST_KEYSRC, NULL);
    kangY = kangY + 4;
    if (kangY > 110) {
      sndObj.playSound(sfxCrash);
      title_step = 2;
    }
  }

  // Krelmac & Gentoo bouncing
  if (title_step == 2) {
    backbuffer->FillRect(CRect(0, kangY, 240, kangY + 25), RGB(0, 0, 0), 0, NULL);
    kangY = kangY + bounceVals[bounce_index];
    backbuffer->BltFast(0, kangY, kangImg, NULL, GDBLTFAST_KEYSRC, NULL);
    bounce_index++;
    if (bounce_index > 31) {
      title_step = 3;
    }
  }

  // Pausing while Gentoo's sound goes
  if (title_step == 3) {
   if (!gentoo_started) {
    gentoo_started = true;
    sndObj.playSound(sfxGentoo);
    }
    gentoo_delay--;
    if (gentoo_delay < 0) {
      title_step = 4;
    }
  }

  // Pausing while Krelmac's sound goes
  if (title_step == 4) {
    if (!krelmac_started) {
      krelmac_started = true;
      sndObj.playSound(sfxKrelmac);
    }
    krelmac_delay--;
    if (krelmac_delay < 0) {
      title_step = 5;
    }
  }

  // Ending delay
  if (title_step == 5) {
    end_delay++;
    if (end_delay > 48) {
      doDestroy(csMainMenu);
    }
  }

}


// ****************************************************************************************************************
// KeyUp handler
// ****************************************************************************************************************
void CGame::kuTitleSequence() {

	using namespace ns_TitleSequence;

	doDestroy(csMainMenu);

}


// ****************************************************************************************************************
// StylusUp handler
// ****************************************************************************************************************
void CGame::suTitleSequence() {

  using namespace ns_TitleSequence;

	kuTitleSequence();

}


// ****************************************************************************************************************
// Loader
// ****************************************************************************************************************
void CGame::loadTitleSequence(CGapiSurface* backbuffer) {

	using namespace ns_TitleSequence;

	processEvents = false;

	// Move on to the next step
	loading_step++;

	// Do the appropriate step
	switch(loading_step) {

		case 1: {
      letters[0]    = new CGapiSurface(); createSurface(TEXT("title : GFX_TITLE_01"),         letters[0]->CreateSurface (0, m_config.hInstance, GFX_TITLE_01,   TEXT("GRAPHICS"))); letters[0]->SetColorKey (RGB(0, 0, 0));
      letters[1]    = new CGapiSurface(); createSurface(TEXT("title : GFX_TITLE_02"),         letters[1]->CreateSurface (0, m_config.hInstance, GFX_TITLE_02,   TEXT("GRAPHICS"))); letters[1]->SetColorKey (RGB(0, 0, 0));
      letters[2]    = new CGapiSurface(); createSurface(TEXT("title : GFX_TITLE_03"),         letters[2]->CreateSurface (0, m_config.hInstance, GFX_TITLE_03,   TEXT("GRAPHICS"))); letters[2]->SetColorKey (RGB(0, 0, 0));
      letters[3]    = new CGapiSurface(); createSurface(TEXT("title : GFX_TITLE_04"),         letters[3]->CreateSurface (0, m_config.hInstance, GFX_TITLE_04,   TEXT("GRAPHICS"))); letters[3]->SetColorKey (RGB(0, 0, 0));
      letters[4]    = new CGapiSurface(); createSurface(TEXT("title : GFX_TITLE_05"),         letters[4]->CreateSurface (0, m_config.hInstance, GFX_TITLE_05,   TEXT("GRAPHICS"))); letters[4]->SetColorKey (RGB(0, 0, 0));
      letters[5]    = new CGapiSurface(); createSurface(TEXT("title : GFX_TITLE_06"),         letters[5]->CreateSurface (0, m_config.hInstance, GFX_TITLE_06,   TEXT("GRAPHICS"))); letters[5]->SetColorKey (RGB(0, 0, 0));
      letters[6]    = new CGapiSurface(); createSurface(TEXT("title : GFX_TITLE_07"),         letters[6]->CreateSurface (0, m_config.hInstance, GFX_TITLE_07,   TEXT("GRAPHICS"))); letters[6]->SetColorKey (RGB(0, 0, 0));
      letters[7]    = new CGapiSurface(); createSurface(TEXT("title : GFX_TITLE_08"),         letters[7]->CreateSurface (0, m_config.hInstance, GFX_TITLE_08,   TEXT("GRAPHICS"))); letters[7]->SetColorKey (RGB(0, 0, 0));
      letters[8]    = new CGapiSurface(); createSurface(TEXT("title : GFX_TITLE_09"),         letters[8]->CreateSurface (0, m_config.hInstance, GFX_TITLE_09,   TEXT("GRAPHICS"))); letters[8]->SetColorKey (RGB(0, 0, 0));
      letters[9]    = new CGapiSurface(); createSurface(TEXT("title : GFX_TITLE_10"),         letters[9]->CreateSurface (0, m_config.hInstance, GFX_TITLE_10,   TEXT("GRAPHICS"))); letters[9]->SetColorKey (RGB(0, 0, 0));
      letters[10]   = new CGapiSurface(); createSurface(TEXT("title : GFX_TITLE_11"),         letters[10]->CreateSurface(0, m_config.hInstance, GFX_TITLE_11,   TEXT("GRAPHICS"))); letters[10]->SetColorKey(RGB(0, 0, 0));
      letters[11]   = new CGapiSurface(); createSurface(TEXT("title : GFX_TITLE_12"),         letters[11]->CreateSurface(0, m_config.hInstance, GFX_TITLE_12,   TEXT("GRAPHICS"))); letters[11]->SetColorKey(RGB(0, 0, 0));
      letters[12]   = new CGapiSurface(); createSurface(TEXT("title : GFX_TITLE_13"),         letters[12]->CreateSurface(0, m_config.hInstance, GFX_TITLE_13,   TEXT("GRAPHICS"))); letters[12]->SetColorKey(RGB(0, 0, 0));
      letters[13]   = new CGapiSurface(); createSurface(TEXT("title : GFX_TITLE_14"),         letters[13]->CreateSurface(0, m_config.hInstance, GFX_TITLE_14,   TEXT("GRAPHICS"))); letters[13]->SetColorKey(RGB(0, 0, 0));
      letters[14]   = new CGapiSurface(); createSurface(TEXT("title : GFX_TITLE_15"),         letters[14]->CreateSurface(0, m_config.hInstance, GFX_TITLE_15,   TEXT("GRAPHICS"))); letters[14]->SetColorKey(RGB(0, 0, 0));
      letters[15]   = new CGapiSurface(); createSurface(TEXT("title : GFX_TITLE_16"),         letters[15]->CreateSurface(0, m_config.hInstance, GFX_TITLE_16,   TEXT("GRAPHICS"))); letters[15]->SetColorKey(RGB(0, 0, 0));
      letters[16]   = new CGapiSurface(); createSurface(TEXT("title : GFX_TITLE_17"),         letters[16]->CreateSurface(0, m_config.hInstance, GFX_TITLE_17,   TEXT("GRAPHICS"))); letters[16]->SetColorKey(RGB(0, 0, 0));
      letters[17]   = new CGapiSurface(); createSurface(TEXT("title : GFX_TITLE_18"),         letters[17]->CreateSurface(0, m_config.hInstance, GFX_TITLE_18,   TEXT("GRAPHICS"))); letters[17]->SetColorKey(RGB(0, 0, 0));
      kangImg       = new CGapiSurface(); createSurface(TEXT("title : GFX_TITLE_KANG"),       kangImg->CreateSurface    (0, m_config.hInstance, GFX_TITLE_KANG, TEXT("GRAPHICS"))); kangImg->SetColorKey    (RGB(0, 0, 0));
      sfxBackground = new hssSound();      loadSFX      (TEXT("title : SFX_TITLE_BACKGROUND"), sfxBackground->load       (m_config.hInstance,    SFX_TITLE_BACKGROUND));             sfxBackground->loop     (false);
      sfxCrash      = new hssSound();      loadSFX      (TEXT("title : SFX_TITLE_CRASH"),      sfxCrash->load            (m_config.hInstance,    SFX_TITLE_CRASH));                  sfxCrash->loop          (false);
      sfxKrelmac    = new hssSound();      loadSFX      (TEXT("title : SFX_TITLE_KRELMAC"),    sfxKrelmac->load          (m_config.hInstance,    SFX_TITLE_KRELMAC));                sfxKrelmac->loop        (false);
      sfxGentoo     = new hssSound();      loadSFX      (TEXT("title : SFX_TITLE_GENTOO"),     sfxGentoo->load           (m_config.hInstance,    SFX_TITLE_GENTOO));                 sfxGentoo->loop         (false);
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
void CGame::destroyTitleSequence(CGapiSurface* backbuffer) {

	using namespace ns_TitleSequence;

	processEvents = false;

	// Move on to the next step
	destroying_step++;

	// Do the appropriate step
	switch(destroying_step) {

		case 1: {
      sndObj.stopSounds();
      delete sfxBackground;
      delete sfxCrash;
      delete sfxKrelmac;
      delete sfxGentoo;
      delete letters[0];
      delete letters[1];
      delete letters[2];
      delete letters[3];
      delete letters[4];
      delete letters[5];
      delete letters[6];
      delete letters[7];
      delete letters[8];
      delete letters[9];
      delete letters[10];
      delete letters[11];
      delete letters[12];
      delete letters[13];
      delete letters[14];
      delete letters[15];
      delete letters[16];
      delete letters[17];
      delete kangImg;
		break; }

		default: {
			// All done destroying, start loading the next screen
			current_screen = screen_after_destroy;
			doLoad();
		break; }

	}

	// Show the Loading screen
	showLoadingScreen(backbuffer, true, true);

}
