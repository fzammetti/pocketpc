
#include "../main.h"


namespace ns_Win {


// ****************************************************************************************************************
// Globals
// ****************************************************************************************************************
CGapiSurface*	ship_interior		= NULL;
CGapiSurface*	krelmac_01			= NULL;
CGapiSurface*	krelmac_04			= NULL;
CGapiSurface*	krelmac_05			= NULL;
CGapiSurface*	krelmac_06			= NULL;
CGapiSurface*	krelmac_07			= NULL;
CGapiSurface*	krelmac_09			= NULL;
CGapiSurface*	krelmac_10			= NULL;
CGapiSurface*	krelmac_11			= NULL;
CGapiSurface*	gentoo_04				= NULL;
CGapiSurface*	gentoo_06				= NULL;
CGapiSurface*	gentoo_07				= NULL;
CGapiSurface*	gentoo_08				= NULL;
CGapiSurface*	gentoo_09				= NULL;
CGapiSurface*	henry_jumping_1 = NULL;
CGapiSurface*	henry_jumping_2 = NULL;
hssSound*     bounce					= NULL;
hssSound*     gentoo15				= NULL;
hssSound*     krelmac15				= NULL;
hssSound*     gentoo17				= NULL;
hssSound*     krelmac16				= NULL;


} // End of namespace


// ****************************************************************************************************************
// ProcessNextFrame handler
// ****************************************************************************************************************
void CGame::pnfWin(CGapiSurface* backbuffer) {

	using namespace ns_Win;

	if (oasisDoScene(backbuffer) == 1) {
		doDestroy(csFinalScore);
	}

}


// ****************************************************************************************************************
// KeyUp handler
// ****************************************************************************************************************
void CGame::kuWin() {

	using namespace ns_Win;

  doDestroy(csFinalScore);

}


// ****************************************************************************************************************
// StylusUp handler
// ****************************************************************************************************************
void CGame::suWin() {

  using namespace ns_Win;

	kuWin();

}


// ****************************************************************************************************************
// Loader
// ****************************************************************************************************************
void CGame::loadWin(CGapiSurface* backbuffer) {

	using namespace ns_Win;

	processEvents = false;

	// Move on to the next step
	loading_step++;

	// Do the appropriate step
	switch(loading_step) {

    case 1: {
      #ifndef _TRIAL_
      ship_interior		= new CGapiSurface(); createSurface(TEXT("win : GFX_SHIP_INTERIOR"),					 ship_interior->CreateSurface	 (0, m_config.hInstance, GFX_SHIP_INTERIOR,   TEXT("GRAPHICS"))); ship_interior->SetColorKey	 (RGB(255, 128, 255));
	    krelmac_01			= new CGapiSurface(); createSurface(TEXT("win : GFX_KRELMAC_01"),							 krelmac_01->CreateSurface		 (0, m_config.hInstance, GFX_KRELMAC_01,		  TEXT("GRAPHICS"))); krelmac_01->SetColorKey		 (RGB(255, 128, 255));
	    krelmac_04			= new CGapiSurface(); createSurface(TEXT("win : GFX_KRELMAC_04"),							 krelmac_04->CreateSurface		 (0, m_config.hInstance, GFX_KRELMAC_04,		  TEXT("GRAPHICS"))); krelmac_04->SetColorKey		 (RGB(255, 128, 255));
	    krelmac_05			= new CGapiSurface(); createSurface(TEXT("win : GFX_KRELMAC_05"),							 krelmac_05->CreateSurface		 (0, m_config.hInstance, GFX_KRELMAC_05,		  TEXT("GRAPHICS"))); krelmac_05->SetColorKey		 (RGB(255, 128, 255));
	    krelmac_06			= new CGapiSurface(); createSurface(TEXT("win : GFX_KRELMAC_06"),							 krelmac_06->CreateSurface		 (0, m_config.hInstance, GFX_KRELMAC_06,		  TEXT("GRAPHICS"))); krelmac_06->SetColorKey		 (RGB(255, 128, 255));
	    krelmac_07			= new CGapiSurface(); createSurface(TEXT("win : GFX_KRELMAC_07"),						   krelmac_07->CreateSurface		 (0, m_config.hInstance, GFX_KRELMAC_07,		  TEXT("GRAPHICS"))); krelmac_07->SetColorKey		 (RGB(255, 128, 255));
	    krelmac_09			= new CGapiSurface(); createSurface(TEXT("win : GFX_KRELMAC_09"),							 krelmac_09->CreateSurface		 (0, m_config.hInstance, GFX_KRELMAC_09,		  TEXT("GRAPHICS"))); krelmac_09->SetColorKey		 (RGB(255, 128, 255));
	    krelmac_10			= new CGapiSurface(); createSurface(TEXT("win : GFX_KRELMAC_10"),							 krelmac_10->CreateSurface		 (0, m_config.hInstance, GFX_KRELMAC_10,		  TEXT("GRAPHICS"))); krelmac_10->SetColorKey		 (RGB(255, 128, 255));
	    krelmac_11			= new CGapiSurface(); createSurface(TEXT("win : GFX_KRELMAC_11"),							 krelmac_11->CreateSurface		 (0, m_config.hInstance, GFX_KRELMAC_11,		  TEXT("GRAPHICS"))); krelmac_11->SetColorKey		 (RGB(255, 128, 255));
      gentoo_04				= new CGapiSurface(); createSurface(TEXT("win : GFX_GENTOO_04"),							 gentoo_04->CreateSurface			 (0, m_config.hInstance, GFX_GENTOO_04,		    TEXT("GRAPHICS"))); gentoo_04->SetColorKey			 (RGB(255, 128, 255));
	    gentoo_06				= new CGapiSurface(); createSurface(TEXT("win : GFX_GENTOO_06"),							 gentoo_06->CreateSurface			 (0, m_config.hInstance, GFX_GENTOO_06,		    TEXT("GRAPHICS"))); gentoo_06->SetColorKey			 (RGB(255, 128, 255));
	    gentoo_07				= new CGapiSurface(); createSurface(TEXT("win : GFX_GENTOO_07"),							 gentoo_07->CreateSurface			 (0, m_config.hInstance, GFX_GENTOO_07,		    TEXT("GRAPHICS"))); gentoo_07->SetColorKey			 (RGB(255, 128, 255));
	    gentoo_08				= new CGapiSurface(); createSurface(TEXT("win : GFX_GENTOO_08"),							 gentoo_08->CreateSurface			 (0, m_config.hInstance, GFX_GENTOO_08,		    TEXT("GRAPHICS"))); gentoo_08->SetColorKey		   (RGB(255, 128, 255));
	    gentoo_09				= new CGapiSurface(); createSurface(TEXT("win : GFX_GENTOO_09"),							 gentoo_09->CreateSurface			 (0, m_config.hInstance, GFX_GENTOO_09,		    TEXT("GRAPHICS"))); gentoo_09->SetColorKey			 (RGB(255, 128, 255));
      henry_jumping_1 = new CGapiSurface(); createSurface(TEXT("player_died : GFX_HENRY_JUMPING_1"), henry_jumping_1->CreateSurface(0, m_config.hInstance, GFX_HENRY_JUMPING_1, TEXT("GRAPHICS"))); henry_jumping_1->SetColorKey(RGB(255, 128, 255));
	    henry_jumping_2 = new CGapiSurface(); createSurface(TEXT("player_died : GFX_HENRY_JUMPING_2"), henry_jumping_2->CreateSurface(0, m_config.hInstance, GFX_HENRY_JUMPING_2, TEXT("GRAPHICS"))); henry_jumping_1->SetColorKey(RGB(255, 128, 255));
      bounce					= new hssSound();			loadSFX			 (TEXT("win : SFX_BOUNCE_2"),								 bounce->load									 (m_config.hInstance,		 SFX_BOUNCE_2));												  bounce->loop								 (false);
      gentoo15				= new hssSound();			loadSFX			 (TEXT("win : SFX_VOICE_GENTOO_15"),				 gentoo15->load								 (m_config.hInstance,		 SFX_VOICE_GENTOO_15));								    gentoo15->loop							 (false);
			krelmac15				= new hssSound();			loadSFX			 (TEXT("win : SFX_VOICE_KRELMAC_15"),				 krelmac15->load							 (m_config.hInstance,		 SFX_VOICE_KRELMAC_15));								  krelmac15->loop						 (false);
			gentoo17				= new hssSound();			loadSFX			 (TEXT("win : SFX_VOICE_GENTOO_17"),			   gentoo17->load								 (m_config.hInstance,		 SFX_VOICE_GENTOO_17));								    gentoo17->loop							 (false);
			krelmac16				= new hssSound();			loadSFX			 (TEXT("win : SFX_VOICE_KRELMAC_16"),				 krelmac16->load							 (m_config.hInstance,		 SFX_VOICE_KRELMAC_16));								  krelmac16->loop						 (false);
      #endif
    break; }

    case 2: {
      // Initialize OASIS
      oasisInitialize();
      // Load visual actors array
	    OASIS_Actors[0].image  = ship_interior;
      OASIS_Actors[1].image  = krelmac_01;
      OASIS_Actors[2].image  = NULL;
      OASIS_Actors[3].image  = NULL;
      OASIS_Actors[4].image  = krelmac_04;
      OASIS_Actors[5].image  = krelmac_05;
      OASIS_Actors[6].image  = krelmac_06;
      OASIS_Actors[7].image  = henry_jumping_1;
      OASIS_Actors[8].image  = henry_jumping_2;
      OASIS_Actors[9].image  = NULL;
      OASIS_Actors[10].image = gentoo_04;
      OASIS_Actors[11].image = NULL;
      OASIS_Actors[12].image = gentoo_06;
      OASIS_Actors[13].image = krelmac_07;
      OASIS_Actors[14].image = NULL;
      OASIS_Actors[15].image = krelmac_09;
      OASIS_Actors[16].image = gentoo_07;
      OASIS_Actors[17].image = gentoo_08;
      OASIS_Actors[18].image = gentoo_09;
      OASIS_Actors[19].image = krelmac_10;
      OASIS_Actors[20].image = krelmac_11;
	    // Load audio actors array
	    OASIS_AudioActors[0].soundFX = bounce;
	    OASIS_AudioActors[1].soundFX = gentoo15;
	    OASIS_AudioActors[2].soundFX = krelmac15;
	    OASIS_AudioActors[3].soundFX = gentoo17;
	    OASIS_AudioActors[4].soundFX = krelmac16;
      // Start the scene
      oasisStartScene(OSS_WIN);
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
void CGame::destroyWin(CGapiSurface* backbuffer) {

	using namespace ns_Win;

	processEvents = false;

	// Move on to the next step
	destroying_step++;

	// Do the appropriate step
	switch(destroying_step) {

		case 1: {
      oasisEndScene();
      #ifndef _TRIAL_
      delete ship_interior;
      delete krelmac_01;
      delete krelmac_04;
      delete krelmac_05;
      delete krelmac_06;
      delete krelmac_07;
      delete krelmac_09;
      delete krelmac_10;
      delete krelmac_11;
      delete gentoo_04;
      delete gentoo_06;
      delete gentoo_07;
      delete gentoo_08;
      delete gentoo_09;
      delete bounce;
      delete gentoo15;
			delete krelmac15;
			delete gentoo17;
			delete krelmac16;
			delete henry_jumping_1;
			delete henry_jumping_2;
      #endif
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
