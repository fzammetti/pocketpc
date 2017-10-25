
#include "../main.h"


namespace ns_PlayerDied {


// ****************************************************************************************************************
// Globals
// ****************************************************************************************************************
CGapiSurface*	ship_interior = NULL;
CGapiSurface*	krelmac_01    = NULL;
CGapiSurface*	krelmac_02    = NULL;
CGapiSurface*	krelmac_03    = NULL;
CGapiSurface*	krelmac_04    = NULL;
CGapiSurface*	krelmac_05    = NULL;
CGapiSurface*	gentoo_01     = NULL;
CGapiSurface*	gentoo_02     = NULL;
CGapiSurface*	gentoo_03     = NULL;
CGapiSurface*	gentoo_04     = NULL;
CGapiSurface*	gentoo_05     = NULL;
CGapiSurface*	gentoo_07     = NULL;
CGapiSurface*	gentoo_08     = NULL;
CGapiSurface*	henry_dead_1  = NULL;
CGapiSurface*	henry_dead_2  = NULL;
CGapiSurface*	henry_dead_3  = NULL;
hssSound*      bounce        = NULL;
hssSound*      gentoo12      = NULL;
hssSound*      krelmac12     = NULL;
hssSound*      gentoo13      = NULL;
hssSound*      krelmac13     = NULL;

} // End of namespace


// ****************************************************************************************************************
// ProcessNextFrame handler
// ****************************************************************************************************************
void CGame::pnfPlayerDied(CGapiSurface* backbuffer) {

	using namespace ns_PlayerDied;

	if (oasisDoScene(backbuffer) == 1) {
		doDestroy(csMainMenu);
	}

}


// ****************************************************************************************************************
// KeyUp handler
// ****************************************************************************************************************
void CGame::kuPlayerDied() {

	using namespace ns_PlayerDied;

  doDestroy(csMainMenu);

}


// ****************************************************************************************************************
// StylusUp handler
// ****************************************************************************************************************
void CGame::suPlayerDied() {

  using namespace ns_PlayerDied;

	kuPlayerDied();

}


// ****************************************************************************************************************
// Loader
// ****************************************************************************************************************
void CGame::loadPlayerDied(CGapiSurface* backbuffer) {

	using namespace ns_PlayerDied;

	processEvents = false;

	// Move on to the next step
	loading_step++;

	// Do the appropriate step
	switch(loading_step) {

		case 1: {
      ship_interior = new CGapiSurface(); createSurface(TEXT("player_died : GFX_SHIP_INTERIOR"),		ship_interior->CreateSurface(0, m_config.hInstance, GFX_SHIP_INTERIOR, TEXT("GRAPHICS"))); ship_interior->SetColorKey(RGB(255, 128, 255));
	    krelmac_01	  = new CGapiSurface(); createSurface(TEXT("player_died : GFX_KRELMAC_01"),				krelmac_01->CreateSurface		(0, m_config.hInstance, GFX_KRELMAC_01,		 TEXT("GRAPHICS"))); krelmac_01->SetColorKey	 (RGB(255, 128, 255));
	    krelmac_02	  = new CGapiSurface(); createSurface(TEXT("player_died : GFX_KRELMAC_02"),				krelmac_02->CreateSurface		(0, m_config.hInstance, GFX_KRELMAC_02,		 TEXT("GRAPHICS"))); krelmac_02->SetColorKey	 (RGB(255, 128, 255));
	    krelmac_03	  = new CGapiSurface(); createSurface(TEXT("player_died : GFX_KRELMAC_03"),				krelmac_03->CreateSurface		(0, m_config.hInstance, GFX_KRELMAC_03,		 TEXT("GRAPHICS"))); krelmac_03->SetColorKey	 (RGB(255, 128, 255));
	    krelmac_04	  = new CGapiSurface(); createSurface(TEXT("player_died : GFX_KRELMAC_04"),				krelmac_04->CreateSurface		(0, m_config.hInstance, GFX_KRELMAC_04,		 TEXT("GRAPHICS"))); krelmac_04->SetColorKey	 (RGB(255, 128, 255));
	    krelmac_05	  = new CGapiSurface(); createSurface(TEXT("player_died : GFX_KRELMAC_05"),				krelmac_05->CreateSurface		(0, m_config.hInstance, GFX_KRELMAC_05,		 TEXT("GRAPHICS"))); krelmac_05->SetColorKey	 (RGB(255, 128, 255));
	    gentoo_01		  = new CGapiSurface(); createSurface(TEXT("player_died : GFX_GENTOO_01"),				gentoo_01->CreateSurface		(0, m_config.hInstance, GFX_GENTOO_01,		 TEXT("GRAPHICS"))); gentoo_01->SetColorKey	   (RGB(255, 128, 255));
	    gentoo_02		  = new CGapiSurface(); createSurface(TEXT("player_died : GFX_GENTOO_02"),				gentoo_02->CreateSurface		(0, m_config.hInstance, GFX_GENTOO_02,		 TEXT("GRAPHICS"))); gentoo_02->SetColorKey		 (RGB(255, 128, 255));
	    gentoo_03		  = new CGapiSurface(); createSurface(TEXT("player_died : GFX_GENTOO_03"),				gentoo_03->CreateSurface		(0, m_config.hInstance, GFX_GENTOO_03,		 TEXT("GRAPHICS"))); gentoo_03->SetColorKey		 (RGB(255, 128, 255));
	    gentoo_04		  = new CGapiSurface(); createSurface(TEXT("player_died : GFX_GENTOO_04"),				gentoo_04->CreateSurface		(0, m_config.hInstance, GFX_GENTOO_04,		 TEXT("GRAPHICS"))); gentoo_04->SetColorKey		 (RGB(255, 128, 255));
	    gentoo_05		  = new CGapiSurface(); createSurface(TEXT("player_died : GFX_GENTOO_05"),				gentoo_05->CreateSurface		(0, m_config.hInstance, GFX_GENTOO_05,		 TEXT("GRAPHICS"))); gentoo_05->SetColorKey		 (RGB(255, 128, 255));
	    gentoo_07		  = new CGapiSurface(); createSurface(TEXT("player_died : GFX_GENTOO_07"),				gentoo_07->CreateSurface		(0, m_config.hInstance, GFX_GENTOO_07,		 TEXT("GRAPHICS"))); gentoo_07->SetColorKey		 (RGB(255, 128, 255));
	    gentoo_08		  = new CGapiSurface(); createSurface(TEXT("player_died : GFX_GENTOO_08"),				gentoo_08->CreateSurface		(0, m_config.hInstance, GFX_GENTOO_08,		 TEXT("GRAPHICS"))); gentoo_08->SetColorKey		 (RGB(255, 128, 255));
      henry_dead_1  = new CGapiSurface(); createSurface(TEXT("player_died : GFX_HENRY_DEAD_1"),			henry_dead_1->CreateSurface (0, m_config.hInstance, GFX_HENRY_DEAD_1,  TEXT("GRAPHICS"))); henry_dead_1->SetColorKey (RGB(255, 128, 255));
	    henry_dead_2  = new CGapiSurface(); createSurface(TEXT("player_died : GFX_HENRY_DEAD_2"),			henry_dead_2->CreateSurface (0, m_config.hInstance, GFX_HENRY_DEAD_2,  TEXT("GRAPHICS"))); henry_dead_1->SetColorKey (RGB(255, 128, 255));
	    henry_dead_3  = new CGapiSurface(); createSurface(TEXT("player_died : GFX_HENRY_DEAD_3"),			henry_dead_3->CreateSurface (0, m_config.hInstance, GFX_HENRY_DEAD_3,  TEXT("GRAPHICS"))); henry_dead_3->SetColorKey (RGB(255, 128, 255));
      bounce			  = new hssSound();			loadSFX			 (TEXT("player_died : SFX_BOUNCE_2"),				  bounce->load								(m_config.hInstance,		SFX_BOUNCE_2));												 bounce->loop							 (false);
      gentoo12		  = new hssSound();			loadSFX			 (TEXT("player_died : SFX_VOICE_GENTOO_12"),  gentoo12->load							(m_config.hInstance,		SFX_VOICE_GENTOO_12));								 gentoo12->loop						 (false);
			krelmac12		  = new hssSound();			loadSFX			 (TEXT("player_died : SFX_VOICE_KRELMAC_12"), krelmac12->load							(m_config.hInstance,		SFX_VOICE_KRELMAC_12));								 krelmac12->loop					 (false);
			gentoo13		  = new hssSound();			loadSFX			 (TEXT("player_died : SFX_VOICE_GENTOO_13"),  gentoo13->load							(m_config.hInstance,		SFX_VOICE_GENTOO_13));								 gentoo13->loop						 (false);
			krelmac13		  = new hssSound();			loadSFX			 (TEXT("player_died : SFX_VOICE_KRELMAC_13"), krelmac13->load							(m_config.hInstance,		SFX_VOICE_KRELMAC_13));								 krelmac13->loop					 (false);
		break; }

    case 2: {
      // Initialize OASIS
      oasisInitialize();
      // Load visual actors array
	    OASIS_Actors[0].image  = ship_interior;
      OASIS_Actors[1].image  = krelmac_01;
      OASIS_Actors[2].image  = krelmac_02;
      OASIS_Actors[3].image  = krelmac_03;
      OASIS_Actors[4].image  = krelmac_04;
      OASIS_Actors[5].image  = krelmac_05;
      OASIS_Actors[6].image  = NULL;
      OASIS_Actors[7].image  = gentoo_01;
      OASIS_Actors[8].image  = gentoo_02;
      OASIS_Actors[9].image  = gentoo_03;
      OASIS_Actors[10].image = gentoo_04;
      OASIS_Actors[11].image = gentoo_05;
      OASIS_Actors[12].image = NULL;
      OASIS_Actors[13].image = henry_dead_1;
      OASIS_Actors[14].image = henry_dead_2;
      OASIS_Actors[15].image = henry_dead_3;
      OASIS_Actors[16].image = gentoo_07;
      OASIS_Actors[17].image = gentoo_08;
	    // Load audio actors array
	    OASIS_AudioActors[0].soundFX = bounce;
	    OASIS_AudioActors[1].soundFX = gentoo12;
	    OASIS_AudioActors[2].soundFX = krelmac12;
      OASIS_AudioActors[3].soundFX = gentoo13;
	    OASIS_AudioActors[4].soundFX = krelmac13;
      // Start the scene
      oasisStartScene(OSS_PLAYER_DIED);
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
void CGame::destroyPlayerDied(CGapiSurface* backbuffer) {

	using namespace ns_PlayerDied;

	processEvents = false;

	// Move on to the next step
	destroying_step++;

	// Do the appropriate step
	switch(destroying_step) {

		case 1: {
      oasisEndScene();
      delete ship_interior;
	    delete krelmac_01;
	    delete krelmac_02;
	    delete krelmac_03;
      delete krelmac_04;
      delete krelmac_05;
	    delete gentoo_01;
	    delete gentoo_02;
	    delete gentoo_03;
	    delete gentoo_04;
	    delete gentoo_05;
      delete gentoo_07;
      delete gentoo_08;
      delete bounce;
			delete gentoo12;
			delete krelmac12;
			delete gentoo13;
			delete krelmac13;
			delete henry_dead_1;
			delete henry_dead_2;
			delete henry_dead_3;
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


// ****************************************************************************************************************
// Utility functions
// ****************************************************************************************************************
namespace ns_PlayerDied {

} // End of namespace