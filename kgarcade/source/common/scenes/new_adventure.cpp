
#include "../main.h"


namespace ns_NewAdventure {


// ****************************************************************************************************************
// Globals
// ****************************************************************************************************************
CGapiSurface*	ship_interior			 = NULL;
CGapiSurface*	krelmac_01				 = NULL;
CGapiSurface*	krelmac_02				 = NULL;
CGapiSurface*	krelmac_03				 = NULL;
CGapiSurface*	krelmac_06				 = NULL;
CGapiSurface*	krelmac_07				 = NULL;
CGapiSurface*	krelmac_09				 = NULL;
CGapiSurface*	krelmac_11				 = NULL;
CGapiSurface*	krelmac_10				 = NULL;
CGapiSurface*	krelmac_08				 = NULL;
CGapiSurface*	gentoo_01					 = NULL;
CGapiSurface*	gentoo_02					 = NULL;
CGapiSurface*	gentoo_03					 = NULL;
CGapiSurface*	gentoo_05					 = NULL;
CGapiSurface*	gentoo_06					 = NULL;
CGapiSurface*	henry_wandering_1  = NULL;
CGapiSurface*	henry_wandering_2  = NULL;
CGapiSurface*	henry_wandering_3  = NULL;
CGapiSurface*	henry_wandering_4  = NULL;
CGapiSurface*	henry_wandering_5  = NULL;
CGapiSurface*	henry_wandering_6  = NULL;
CGapiSurface*	henry_beamingup_1  = NULL;
CGapiSurface*	henry_beamingup_2  = NULL;
CGapiSurface*	henry_beamingup_3  = NULL;
CGapiSurface*	henry_beamingup_4  = NULL;
CGapiSurface*	henry_beamingup_5  = NULL;
CGapiSurface*	viewscreen_static1 = NULL;
CGapiSurface*	viewscreen_static2 = NULL;
CGapiSurface*	viewscreen_static3 = NULL;
CGapiSurface*	henry_captive_1		 = NULL;
CGapiSurface*	henry_captive_2		 = NULL;
CGapiSurface*	henry_captive_3		 = NULL;
CGapiSurface*	henry_captive_4		 = NULL;
hssSound*     bounce						 = NULL;
hssSound*     gentoo1						 = NULL;
hssSound*     krelmac1					 = NULL;
hssSound*     krelmac4					 = NULL;
hssSound*     gentoo5						 = NULL;
hssSound*     krelmac5					 = NULL;
hssSound*     gentoo6						 = NULL;
hssSound*     krelmac6					 = NULL;
hssSound*     gentoo20					 = NULL;
hssSound*     krelmac7					 = NULL;
hssSound*     gentoo7						 = NULL;
hssSound*     krelmac8					 = NULL;
hssSound*     gentoo8						 = NULL;
hssSound*     gentoo9						 = NULL;
hssSound*     beamup						 = NULL;

} // End of namespace


// ****************************************************************************************************************
// ProcessNextFrame handler
// ****************************************************************************************************************
void CGame::pnfNewAdventure(CGapiSurface* backbuffer) {

	using namespace ns_NewAdventure;

  if (oasisDoScene(backbuffer) == 1) {
		doDestroy(csWalkingAroundTheShip);
	}

}


// ****************************************************************************************************************
// KeyUp handler
// ****************************************************************************************************************
void CGame::kuNewAdventure() {

	using namespace ns_NewAdventure;

  doDestroy(csWalkingAroundTheShip);

}


// ****************************************************************************************************************
// StylusUp handler
// ****************************************************************************************************************
void CGame::suNewAdventure() {

  using namespace ns_NewAdventure;

	kuNewAdventure();

}


// ****************************************************************************************************************
// Loader
// ****************************************************************************************************************
void CGame::loadNewAdventure(CGapiSurface* backbuffer) {

	using namespace ns_NewAdventure;

	processEvents = false;

	// Move on to the next step
	loading_step++;

	// Do the appropriate step
	switch(loading_step) {

    case 1: {
      ship_interior			 = new CGapiSurface(); createSurface(TEXT("new_adventure : GFX_SHIP_INTERIOR"),				ship_interior->CreateSurface		 (0, m_config.hInstance, GFX_SHIP_INTERIOR,				TEXT("GRAPHICS"))); ship_interior->SetColorKey		 (RGB(255, 128, 255));
	    krelmac_01				 = new CGapiSurface(); createSurface(TEXT("new_adventure : GFX_KRELMAC_01"),					krelmac_01->CreateSurface				 (0, m_config.hInstance, GFX_KRELMAC_01,					TEXT("GRAPHICS"))); krelmac_01->SetColorKey				 (RGB(255, 128, 255));
	    krelmac_02				 = new CGapiSurface(); createSurface(TEXT("new_adventure : GFX_KRELMAC_02"),					krelmac_02->CreateSurface				 (0, m_config.hInstance, GFX_KRELMAC_02,					TEXT("GRAPHICS"))); krelmac_02->SetColorKey				 (RGB(255, 128, 255));
	    krelmac_03				 = new CGapiSurface(); createSurface(TEXT("new_adventure : GFX_KRELMAC_03"),					krelmac_03->CreateSurface				 (0, m_config.hInstance, GFX_KRELMAC_03,					TEXT("GRAPHICS"))); krelmac_03->SetColorKey				 (RGB(255, 128, 255));
	    krelmac_06				 = new CGapiSurface(); createSurface(TEXT("new_adventure : GFX_KRELMAC_06"),					krelmac_06->CreateSurface				 (0, m_config.hInstance, GFX_KRELMAC_06,					TEXT("GRAPHICS"))); krelmac_06->SetColorKey				 (RGB(255, 128, 255));
	    krelmac_07				 = new CGapiSurface(); createSurface(TEXT("new_adventure : GFX_KRELMAC_07"),					krelmac_07->CreateSurface				 (0, m_config.hInstance, GFX_KRELMAC_07,					TEXT("GRAPHICS"))); krelmac_07->SetColorKey				 (RGB(255, 128, 255));
	    krelmac_09				 = new CGapiSurface(); createSurface(TEXT("new_adventure : GFX_KRELMAC_09"),					krelmac_09->CreateSurface				 (0, m_config.hInstance, GFX_KRELMAC_09,					TEXT("GRAPHICS"))); krelmac_09->SetColorKey				 (RGB(255, 128, 255));
	    krelmac_11		     = new CGapiSurface(); createSurface(TEXT("new_adventure : GFX_KRELMAC_11"),					krelmac_11->CreateSurface				 (0, m_config.hInstance, GFX_KRELMAC_11,					TEXT("GRAPHICS"))); krelmac_11->SetColorKey				 (RGB(255, 128, 255));
	    krelmac_10		     = new CGapiSurface(); createSurface(TEXT("new_adventure : GFX_KRELMAC_10"),					krelmac_10->CreateSurface				 (0, m_config.hInstance, GFX_KRELMAC_10,					TEXT("GRAPHICS"))); krelmac_10->SetColorKey				 (RGB(255, 128, 255));
	    krelmac_08			   = new CGapiSurface(); createSurface(TEXT("new_adventure : GFX_KRELMAC_08"),					krelmac_08->CreateSurface				 (0, m_config.hInstance, GFX_KRELMAC_08,					TEXT("GRAPHICS"))); krelmac_08->SetColorKey				 (RGB(255, 128, 255));
      gentoo_01					 = new CGapiSurface(); createSurface(TEXT("new_adventure : GFX_GENTOO_01"),						gentoo_01->CreateSurface				 (0, m_config.hInstance, GFX_GENTOO_01,						TEXT("GRAPHICS"))); gentoo_01->SetColorKey				 (RGB(255, 128, 255));
	    gentoo_02					 = new CGapiSurface(); createSurface(TEXT("new_adventure : GFX_GENTOO_02"),						gentoo_02->CreateSurface				 (0, m_config.hInstance, GFX_GENTOO_02,						TEXT("GRAPHICS"))); gentoo_02->SetColorKey				 (RGB(255, 128, 255));
	    gentoo_03					 = new CGapiSurface(); createSurface(TEXT("new_adventure : GFX_GENTOO_03"),						gentoo_03->CreateSurface				 (0, m_config.hInstance, GFX_GENTOO_03,						TEXT("GRAPHICS"))); gentoo_03->SetColorKey				 (RGB(255, 128, 255));
	    gentoo_05					 = new CGapiSurface(); createSurface(TEXT("new_adventure : GFX_GENTOO_05"),						gentoo_05->CreateSurface				 (0, m_config.hInstance, GFX_GENTOO_05,						TEXT("GRAPHICS"))); gentoo_05->SetColorKey				 (RGB(255, 128, 255));
	    gentoo_06					 = new CGapiSurface(); createSurface(TEXT("new_adventure : GFX_GENTOO_06"),						gentoo_06->CreateSurface				 (0, m_config.hInstance, GFX_GENTOO_06,						TEXT("GRAPHICS"))); gentoo_06->SetColorKey				 (RGB(255, 128, 255));
	    henry_wandering_1	 = new CGapiSurface(); createSurface(TEXT("new_adventure : GFX_HENRY_WANDERING_1"),		henry_wandering_1->CreateSurface (0, m_config.hInstance, GFX_HENRY_WANDERING_1,		TEXT("GRAPHICS"))); henry_wandering_1->SetColorKey (RGB(255, 128, 255));
			henry_wandering_2	 = new CGapiSurface(); createSurface(TEXT("new_adventure : GFX_HENRY_WANDERING_2"),		henry_wandering_2->CreateSurface (0, m_config.hInstance, GFX_HENRY_WANDERING_2,		TEXT("GRAPHICS"))); henry_wandering_2->SetColorKey (RGB(255, 128, 255));
			henry_wandering_3	 = new CGapiSurface(); createSurface(TEXT("new_adventure : GFX_HENRY_WANDERING_3"),		henry_wandering_3->CreateSurface (0, m_config.hInstance, GFX_HENRY_WANDERING_3,		TEXT("GRAPHICS"))); henry_wandering_3->SetColorKey (RGB(255, 128, 255));
			henry_wandering_4	 = new CGapiSurface(); createSurface(TEXT("new_adventure : GFX_HENRY_WANDERING_4"),		henry_wandering_4->CreateSurface (0, m_config.hInstance, GFX_HENRY_WANDERING_4,		TEXT("GRAPHICS"))); henry_wandering_4->SetColorKey (RGB(255, 128, 255));
			henry_wandering_5	 = new CGapiSurface(); createSurface(TEXT("new_adventure : GFX_HENRY_WANDERING_5"),		henry_wandering_5->CreateSurface (0, m_config.hInstance, GFX_HENRY_WANDERING_5,		TEXT("GRAPHICS"))); henry_wandering_5->SetColorKey (RGB(255, 128, 255));
			henry_wandering_6	 = new CGapiSurface(); createSurface(TEXT("new_adventure : GFX_HENRY_WANDERING_6"),		henry_wandering_6->CreateSurface (0, m_config.hInstance, GFX_HENRY_WANDERING_6,		TEXT("GRAPHICS"))); henry_wandering_6->SetColorKey (RGB(255, 128, 255));
	    henry_beamingup_1	 = new CGapiSurface(); createSurface(TEXT("new_adventure : GFX_HENRY_BEAMINGUP_1"),		henry_beamingup_1->CreateSurface (0, m_config.hInstance, GFX_HENRY_BEAMINGUP_1,		TEXT("GRAPHICS"))); henry_beamingup_1->SetColorKey (RGB(255, 128, 255));
			henry_beamingup_2	 = new CGapiSurface(); createSurface(TEXT("new_adventure : GFX_HENRY_BEAMINGUP_2"),		henry_beamingup_2->CreateSurface (0, m_config.hInstance, GFX_HENRY_BEAMINGUP_2,		TEXT("GRAPHICS"))); henry_beamingup_2->SetColorKey (RGB(255, 128, 255));
			henry_beamingup_3	 = new CGapiSurface(); createSurface(TEXT("new_adventure : GFX_HENRY_BEAMINGUP_3"),		henry_beamingup_3->CreateSurface (0, m_config.hInstance, GFX_HENRY_BEAMINGUP_3,		TEXT("GRAPHICS"))); henry_beamingup_3->SetColorKey (RGB(255, 128, 255));
			henry_beamingup_4	 = new CGapiSurface(); createSurface(TEXT("new_adventure : GFX_HENRY_BEAMINGUP_4"),		henry_beamingup_4->CreateSurface (0, m_config.hInstance, GFX_HENRY_BEAMINGUP_4,		TEXT("GRAPHICS"))); henry_beamingup_4->SetColorKey (RGB(255, 128, 255));
			henry_beamingup_5	 = new CGapiSurface(); createSurface(TEXT("new_adventure : GFX_HENRY_BEAMINGUP_5"),		henry_beamingup_5->CreateSurface (0, m_config.hInstance, GFX_HENRY_BEAMINGUP_5,		TEXT("GRAPHICS"))); henry_beamingup_5->SetColorKey (RGB(255, 128, 255));
	    viewscreen_static1 = new CGapiSurface(); createSurface(TEXT("new_adventure : GFX_VIEWSCREEN_STATIC_1"),	viewscreen_static1->CreateSurface(0, m_config.hInstance, GFX_VIEWSCREEN_STATIC_1,	TEXT("GRAPHICS"))); viewscreen_static1->SetColorKey(RGB(255, 128, 255));
			viewscreen_static2 = new CGapiSurface(); createSurface(TEXT("new_adventure : GFX_VIEWSCREEN_STATIC_2"),	viewscreen_static2->CreateSurface(0, m_config.hInstance, GFX_VIEWSCREEN_STATIC_2,	TEXT("GRAPHICS"))); viewscreen_static2->SetColorKey(RGB(255, 128, 255));
			viewscreen_static3 = new CGapiSurface(); createSurface(TEXT("new_adventure : GFX_VIEWSCREEN_STATIC_3"),	viewscreen_static3->CreateSurface(0, m_config.hInstance, GFX_VIEWSCREEN_STATIC_3,	TEXT("GRAPHICS"))); viewscreen_static3->SetColorKey(RGB(255, 128, 255));
			henry_captive_1		 = new CGapiSurface(); createSurface(TEXT("new_adventure : GFX_HENRY_CAPTIVE_1"),			henry_captive_1->CreateSurface	 (0, m_config.hInstance, GFX_HENRY_CAPTIVE_1,			TEXT("GRAPHICS"))); henry_captive_1->SetColorKey 	 (RGB(255, 128, 255));
			henry_captive_2		 = new CGapiSurface(); createSurface(TEXT("new_adventure : GFX_HENRY_CAPTIVE_2"),			henry_captive_2->CreateSurface	 (0, m_config.hInstance, GFX_HENRY_CAPTIVE_2,			TEXT("GRAPHICS"))); henry_captive_2->SetColorKey	 (RGB(255, 128, 255));
			henry_captive_3		 = new CGapiSurface(); createSurface(TEXT("new_adventure : GFX_HENRY_CAPTIVE_3"),			henry_captive_3->CreateSurface	 (0, m_config.hInstance, GFX_HENRY_CAPTIVE_3,			TEXT("GRAPHICS"))); henry_captive_3->SetColorKey	 (RGB(255, 128, 255));
			henry_captive_4		 = new CGapiSurface(); createSurface(TEXT("new_adventure : GFX_HENRY_CAPTIVE_4"),			henry_captive_4->CreateSurface	 (0, m_config.hInstance, GFX_HENRY_CAPTIVE_4,			TEXT("GRAPHICS"))); henry_captive_4->SetColorKey	 (RGB(255, 128, 255));
			bounce						 = new hssSound();			loadSFX			  (TEXT("new_adventure : SFX_BOUNCE_2"),						bounce->load										 (m_config.hInstance,		 SFX_BOUNCE_2));															bounce->loop									 (false);
      gentoo1						 = new hssSound();			loadSFX			  (TEXT("new_adventure : SFX_VOICE_GENTOO_01"),			gentoo1->load										 (m_config.hInstance,		 SFX_VOICE_GENTOO_01));												gentoo1->loop									 (false);
      krelmac1					 = new hssSound();			loadSFX			  (TEXT("new_adventure : SFX_VOICE_KRELMAC_01"),		krelmac1->load									 (m_config.hInstance,		 SFX_VOICE_KRELMAC_01));											krelmac1->loop								 (false);
      krelmac4					 = new hssSound();			loadSFX		    (TEXT("new_adventure : SFX_VOICE_KRELMAC_04"),		krelmac4->load									 (m_config.hInstance,		 SFX_VOICE_KRELMAC_04));											krelmac4->loop								 (false);
      gentoo5						 = new hssSound();			loadSFX			  (TEXT("new_adventure : SFX_VOICE_GENTOO_05"),			gentoo5->load										 (m_config.hInstance,		 SFX_VOICE_GENTOO_05));												gentoo5->loop									 (false);
			krelmac5					 = new hssSound();			loadSFX			  (TEXT("new_adventure : SFX_VOICE_KRELMAC_05"),		krelmac5->load									 (m_config.hInstance,		 SFX_VOICE_KRELMAC_05));											krelmac5->loop								 (false);
      gentoo6						 = new hssSound();			loadSFX			  (TEXT("new_adventure : SFX_VOICE_GENTOO_06"),			gentoo6->load										 (m_config.hInstance,		 SFX_VOICE_GENTOO_06));												gentoo6->loop									 (false);
      krelmac6					 = new hssSound();			loadSFX			  (TEXT("new_adventure : SFX_VOICE_KRELMAC_06"),		krelmac6->load									 (m_config.hInstance,		 SFX_VOICE_KRELMAC_06));											krelmac6->loop								 (false);
      gentoo20					 = new hssSound();			loadSFX			  (TEXT("new_adventure : SFX_VOICE_GENTOO_20"),			gentoo20->load									 (m_config.hInstance,		 SFX_VOICE_GENTOO_20));												gentoo20->loop								 (false);
      krelmac7					 = new hssSound();			loadSFX			  (TEXT("new_adventure : SFX_VOICE_KRELMAC_07"),		krelmac7->load									 (m_config.hInstance,		 SFX_VOICE_KRELMAC_07));											krelmac7->loop								 (false);
      gentoo7						 = new hssSound();			loadSFX			  (TEXT("new_adventure : SFX_VOICE_GENTOO_07"),			gentoo7->load										 (m_config.hInstance,		 SFX_VOICE_GENTOO_07));												gentoo7->loop									 (false);
      krelmac8					 = new hssSound();			loadSFX			  (TEXT("new_adventure : SFX_VOICE_KRELMAC_08"),		krelmac8->load									 (m_config.hInstance,		 SFX_VOICE_KRELMAC_08));											krelmac8->loop								 (false);
      gentoo8						 = new hssSound();			loadSFX			  (TEXT("new_adventure : SFX_VOICE_GENTOO_08"),			gentoo8->load										 (m_config.hInstance,		 SFX_VOICE_GENTOO_08));												gentoo8->loop									 (false);
      gentoo9						 = new hssSound();			loadSFX			  (TEXT("new_adventure : SFX_VOICE_GENTOO_09"),			gentoo9->load										 (m_config.hInstance,		 SFX_VOICE_GENTOO_09));												gentoo9->loop									 (false);
			beamup						 = new hssSound();			loadSFX			  (TEXT("new_adventure : SFX_BEAMMEUP"),						beamup->load										 (m_config.hInstance,		 SFX_BEAMMEUP));								      				beamup->loop									 (false);
		break; }

    case 2: {
      // Initialize OASIS
      oasisInitialize();
      // Load visual actors array
	    OASIS_Actors[0].image  = ship_interior;
      OASIS_Actors[1].image  = krelmac_01;
      OASIS_Actors[2].image  = krelmac_02;
      OASIS_Actors[3].image  = krelmac_03;
      OASIS_Actors[4].image  = krelmac_06;
      OASIS_Actors[5].image  = krelmac_07;
      OASIS_Actors[6].image  = krelmac_09;
      OASIS_Actors[7].image  = gentoo_01;
      OASIS_Actors[8].image  = gentoo_02;
      OASIS_Actors[9].image  = gentoo_03;
      OASIS_Actors[10].image = krelmac_11;
      OASIS_Actors[11].image = gentoo_05;
      OASIS_Actors[12].image = gentoo_06;
			OASIS_Actors[13].image = henry_wandering_1;
			OASIS_Actors[14].image = henry_wandering_2;
			OASIS_Actors[15].image = henry_wandering_3;
			OASIS_Actors[16].image = henry_wandering_4;
			OASIS_Actors[17].image = henry_wandering_5;
			OASIS_Actors[18].image = henry_wandering_6;
			OASIS_Actors[19].image = henry_beamingup_1;
			OASIS_Actors[20].image = henry_beamingup_2;
			OASIS_Actors[21].image = henry_beamingup_3;
			OASIS_Actors[22].image = henry_beamingup_4;
			OASIS_Actors[23].image = henry_beamingup_5;
			OASIS_Actors[24].image = viewscreen_static1;
			OASIS_Actors[25].image = viewscreen_static2;
			OASIS_Actors[26].image = viewscreen_static3;
			OASIS_Actors[27].image = henry_captive_1;
			OASIS_Actors[28].image = henry_captive_2;
			OASIS_Actors[29].image = henry_captive_3;
			OASIS_Actors[30].image = henry_captive_4;
      OASIS_Actors[31].image = krelmac_10;
      OASIS_Actors[32].image = krelmac_08;
	    // Load audio actors array
	    OASIS_AudioActors[0].soundFX  = bounce;
	    OASIS_AudioActors[1].soundFX  = gentoo1;
	    OASIS_AudioActors[2].soundFX  = krelmac1;
      OASIS_AudioActors[3].soundFX  = krelmac4;
	    OASIS_AudioActors[4].soundFX  = gentoo5;
	    OASIS_AudioActors[5].soundFX  = krelmac5;
      OASIS_AudioActors[6].soundFX  = gentoo6;
      OASIS_AudioActors[7].soundFX  = krelmac6;
      OASIS_AudioActors[8].soundFX  = gentoo20;
      OASIS_AudioActors[9].soundFX  = krelmac7;
      OASIS_AudioActors[10].soundFX = gentoo7;
      OASIS_AudioActors[11].soundFX = krelmac8;
      OASIS_AudioActors[12].soundFX = gentoo8;
      OASIS_AudioActors[13].soundFX = gentoo9;
			OASIS_AudioActors[14].soundFX = beamup;
      // Start the scene
      oasisStartScene(OSS_THE_ADVENTURE_BEGINS);
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
void CGame::destroyNewAdventure(CGapiSurface* backbuffer) {

	using namespace ns_NewAdventure;

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
      delete krelmac_06;
      delete krelmac_07;
      delete krelmac_09;
      delete krelmac_11;
      delete krelmac_10;
      delete krelmac_08;
	    delete gentoo_01;
	    delete gentoo_02;
	    delete gentoo_03;
	    delete gentoo_05;
      delete gentoo_06;
      delete bounce;
      delete gentoo1;
      delete krelmac1;
      delete krelmac4;
      delete gentoo5;
			delete krelmac5;
      delete gentoo6;
      delete krelmac6;
      delete gentoo20;
      delete krelmac7;
      delete gentoo7;
      delete krelmac8;
      delete gentoo8;
      delete gentoo9;
			delete henry_captive_1;
			delete henry_captive_2;
			delete henry_captive_3;
			delete henry_captive_4;
      delete henry_wandering_1;
      delete henry_wandering_2;
      delete henry_wandering_3;
      delete henry_wandering_4;
      delete henry_wandering_5;
      delete henry_wandering_6;
      delete henry_beamingup_1;
      delete henry_beamingup_2;
      delete henry_beamingup_3;
      delete henry_beamingup_4;
      delete henry_beamingup_5;
      delete viewscreen_static1;
      delete viewscreen_static2;
      delete viewscreen_static3;
			delete beamup;
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
namespace ns_NewAdventure {

} // End of namespace