
#include "main.h"


// ****************************************************************************************************************
// Constructor
// ****************************************************************************************************************
CGame::CGame(const GDAPPCONFIG& config) : CGapiApplication(config) {
}


// ****************************************************************************************************************
// Destructor
// ****************************************************************************************************************
CGame::~CGame() {
}



// ****************************************************************************************************************
// WinMain
// ****************************************************************************************************************
int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPTSTR pCmdLine, int nCmdShow) {

  // Check for available memory, abort if not enough
  DWORD totalFreeMemory = CGame::getStorageMemory() + CGame::getProgramMemory();
  TCHAR szOut[27] = TEXT("");
  if (totalFreeMemory < 8000) {
    MessageBox(NULL, TEXT("K&G Arcade requires 8MB of free memory to run.\n\nPlease free that much (Storage and Program memory combined), and restart the program."), TEXT("Not enough memory"), MB_OK);
    return 0;
  }

  GDAPPCONFIG config;
  ZeroMemory(&config, sizeof(GDAPPCONFIG));
	config.hInstance           = hInst;
	config.pAppTitle           = TEXT("KandG Arcade");
	config.dwWindowIcon        = ICO_ICON;
	config.dwTargetFPS         = 24;
	config.dwDisplayWidth      = 240;
	config.dwDisplayHeight     = 320;
	config.dwDisplayZoomWidth  = 240 * 2;
	config.dwDisplayZoomHeight = 320 * 2;
  CGame* myGame = new CGame(config);
	HRESULT hr = -1;
	if (myGame) {
		hr = myGame->Run();
		delete myGame;
	}
	return hr;

}


// ****************************************************************************************************************
// Game initialization
// ****************************************************************************************************************
HRESULT CGame::InitInstance() {

	// Initialize random number generator
	srand(GetTickCount());

	// Set the screen to start up on
	current_screen = csFirstTimeInits;

	// Scrolling menu and related screens background
	h_offset = 0;
	v_offset = 0;

	// Some misc setups
  doLoad();
  current_level							= 1;
	current_level_initialized = false;
  jumpBackToNewGameType			= false;
  fade_function							= 0;
  fade_value								= 255;
  total_points							= 0;
  points_this_level					= 0;
  health										= 12;
  processEvents							= true;
  volumeLevel								= vlMedium;
  fuzzIndex									= 0;
	doPopup										= false;
	common_init_counter				= 0;
	show_fps									= false;
	show_frame_time						=	false;
	kUp												= NULL;
	kDown											= NULL;
	kLeft											= NULL;
	kRight										= NULL;
	kAction										= NULL;
	kCommand									= NULL;
	gpTempBlended             = NULL;
  unlockCornerUL            = 0;
  unlockCornerUR            = 0;
	shutdownStep              = 0;

	// Get path to executable for later user
	GetModuleDirectory(GetModuleHandle(NULL), gameEXEPath, sizeof(gameEXEPath) / sizeof(TCHAR));

	// Initialize sound
	sndObj.open(11025, 8, false, 0, 8);

  // Mini-game names and descriptions and high scores and locked status
	for (int i = 0; i < 30; i++) { miniGameHighsTimed[i] = 0; miniGameHighsPUISS[i] = 0; }
	melee_selection[0] = csADayInTheStrife; game_unlocked[0] = true;
	_tcscpy(mini_game_info[0][0],  TEXT("A Day In The Strife"));
	_tcscpy(mini_game_info[0][1],  TEXT("Just a normal day of zapping"));
  _tcscpy(mini_game_info[0][2],  TEXT("the marauding alien invaders"));
	melee_selection[1] = csAlienBabble; game_unlocked[1] = false;
  _tcscpy(mini_game_info[1][0],  TEXT("Alien Babble"));
  _tcscpy(mini_game_info[1][1],  TEXT("Try to keep up with the aliens"));
  _tcscpy(mini_game_info[1][2],  TEXT("babbling away at you"));
	melee_selection[2] = csAntigravitator; game_unlocked[2] = false;
	_tcscpy(mini_game_info[2][0],  TEXT("Antigravitator"));
	_tcscpy(mini_game_info[2][1],  TEXT("Kill the escaping aliens"));
  _tcscpy(mini_game_info[2][2],  TEXT("before they reach their ship"));
	melee_selection[3] = csConquerror; game_unlocked[3] = false;
  _tcscpy(mini_game_info[3][0],  TEXT("Conquerror"));
  _tcscpy(mini_game_info[3][1],  TEXT("You go, you see, you"));
  _tcscpy(mini_game_info[3][2],  TEXT("destroy an entire city"));
	melee_selection[4] = csCopyCat; game_unlocked[4] = true;
	_tcscpy(mini_game_info[4][0],  TEXT("Copycat"));
	_tcscpy(mini_game_info[4][1],  TEXT("Some worlds call it Simon, but"));
  _tcscpy(mini_game_info[4][2],  TEXT("we didn't want to get sued"));
	melee_selection[5] = csCosmicSquirrel; game_unlocked[5] = true;
	_tcscpy(mini_game_info[5][0],  TEXT("Cosmic Squirrel"));
	_tcscpy(mini_game_info[5][1],  TEXT("In space, no one can hear a"));
  _tcscpy(mini_game_info[5][2],  TEXT("giant space squirrel buy it"));
	melee_selection[6] = csDeathTrap; game_unlocked[6] = false;
	_tcscpy(mini_game_info[6][0],  TEXT("DeathTrap"));
  _tcscpy(mini_game_info[6][1],  TEXT("Hop on the tiles to escape the"));
  _tcscpy(mini_game_info[6][2],  TEXT("chasm without getting cooked"));
	melee_selection[7] = csDefendoh; game_unlocked[7] = false;
	_tcscpy(mini_game_info[7][0],  TEXT("Defen'DOH!"));
	_tcscpy(mini_game_info[7][1],  TEXT("If Homer Simpson flew a space"));
  _tcscpy(mini_game_info[7][2],  TEXT("fighter, this is what you'd get"));
	melee_selection[8] = csEngineer; game_unlocked[8] = false;
	_tcscpy(mini_game_info[8][0],  TEXT("Engineer"));
	_tcscpy(mini_game_info[8][1],  TEXT("Route the energy particles"));
  _tcscpy(mini_game_info[8][2],  TEXT("to the right injector ports"));
	melee_selection[9] = csFarOutFowl; game_unlocked[9] = false;
	_tcscpy(mini_game_info[9][0], TEXT("Far Out Fowl"));
	_tcscpy(mini_game_info[9][1], TEXT("Picture a sadistic chicken from"));
  _tcscpy(mini_game_info[9][2], TEXT("space dropping eggs at you"));
	melee_selection[10] = csFlightOfDoom; game_unlocked[10] = true;
	_tcscpy(mini_game_info[10][0], TEXT("Flight Of Doom"));
	_tcscpy(mini_game_info[10][1], TEXT("The weather channel said this"));
  _tcscpy(mini_game_info[10][2], TEXT("was a bad day to fly in space"));
	melee_selection[11] = csGlutton; game_unlocked[11] = false;
	_tcscpy(mini_game_info[11][0], TEXT("Glutton"));
	_tcscpy(mini_game_info[11][1], TEXT("The sign said Don't Feed The"));
  _tcscpy(mini_game_info[11][2], TEXT("Garagnack, but did you listen?"));
  melee_selection[12] = csInMemoria; game_unlocked[12] = false;
	_tcscpy(mini_game_info[12][0],  TEXT("In Memoria"));
	_tcscpy(mini_game_info[12][1],  TEXT("If you can't remember your"));
  _tcscpy(mini_game_info[12][2],  TEXT("anniversary, your in trouble"));
	melee_selection[13] = csLeparLand; game_unlocked[13] = false;
	_tcscpy(mini_game_info[13][0], TEXT("Lepar Land"));
	_tcscpy(mini_game_info[13][1], TEXT("We put them all on one planet."));
  _tcscpy(mini_game_info[13][2], TEXT("Too bad you landed on it!"));
	melee_selection[14] = csMuncherDude; game_unlocked[14] = false;
	_tcscpy(mini_game_info[14][0], TEXT("Muncher Dude"));
	_tcscpy(mini_game_info[14][1], TEXT("Yet another hungry THING"));
  _tcscpy(mini_game_info[14][2], TEXT("stuck in a maze eating dots!"));
	melee_selection[15] = csFfopirSirtetPaehc; game_unlocked[15] = false;
	_tcscpy(mini_game_info[15][0], TEXT("Paehc Sirtet Ffopir"));
	_tcscpy(mini_game_info[15][1], TEXT("Read the name correcly and all"));
  _tcscpy(mini_game_info[15][2], TEXT("shall be revealed to you"));
	melee_selection[16] = csRefluxive; game_unlocked[16] = false;
	_tcscpy(mini_game_info[16][0], TEXT("Refluxive"));
	_tcscpy(mini_game_info[16][1], TEXT("Who knows what they are, but"));
  _tcscpy(mini_game_info[16][2], TEXT("they have to be kept moving"));
	melee_selection[17] = csReluctantHero; game_unlocked[17] = false;
	_tcscpy(mini_game_info[17][0], TEXT("Reluctant Hero"));
	_tcscpy(mini_game_info[17][1], TEXT("No one else would do it, so it's"));
  _tcscpy(mini_game_info[17][2], TEXT("up to you to rescue the people"));
	melee_selection[18] = csSonOfEliminator; game_unlocked[18] = false;
	_tcscpy(mini_game_info[18][0], TEXT("Son Of Eliminator"));
	_tcscpy(mini_game_info[18][1], TEXT("What, you didn't buy the"));
  _tcscpy(mini_game_info[18][2], TEXT("original Eliminator?!?  Bleh!"));
	melee_selection[19] = csSquishem; game_unlocked[19] = false;
	_tcscpy(mini_game_info[19][0], TEXT("Squish'em"));
	_tcscpy(mini_game_info[19][1], TEXT("Aliens to the left of me!"));
  _tcscpy(mini_game_info[19][2], TEXT("Aliens to the right of me!"));
  melee_selection[20] = csTheBogazDerby; game_unlocked[20] = false;
	_tcscpy(mini_game_info[20][0], TEXT("The Bogaz Derby"));
	_tcscpy(mini_game_info[20][1], TEXT("Enter the race, avoid a crash,"));
  _tcscpy(mini_game_info[20][2], TEXT("and above all else, have fun!"));
	melee_selection[21] = csTheEscape; game_unlocked[21] = false;
	_tcscpy(mini_game_info[21][0], TEXT("The Escape"));
	_tcscpy(mini_game_info[21][1], TEXT("It's not gonna be easy, but you"));
  _tcscpy(mini_game_info[21][2], TEXT("can't stay in a cave forever"));
	melee_selection[22] = csTheRedeyeOrder; game_unlocked[22] = true;
	_tcscpy(mini_game_info[22][0], TEXT("The Redeye Order"));
	_tcscpy(mini_game_info[22][1], TEXT("Use the Farce, and your basic"));
  _tcscpy(mini_game_info[22][2], TEXT("math skills, to order the tiles"));
	melee_selection[23] = csTroubleInVectropolis; game_unlocked[23] = false;
	_tcscpy(mini_game_info[23][0], TEXT("Trouble In Vectropolis"));
	_tcscpy(mini_game_info[23][1], TEXT("This seems somehow familiar..."));
  _tcscpy(mini_game_info[23][2], TEXT("Blue Six standing by?!?"));
  melee_selection[24] = csVirus; game_unlocked[24] = false;
	_tcscpy(mini_game_info[24][0], TEXT("Virus"));
	_tcscpy(mini_game_info[24][1], TEXT("It's up to you to remove the"));
  _tcscpy(mini_game_info[24][2], TEXT("virus from the ship's memory"));

  // Misc Sounds
	sfx_ins_arrow    = new hssSound(); loadSFX(TEXT("main : SFX_INS_ARROW"),       sfx_ins_arrow->load   (m_config.hInstance, SFX_INS_ARROW));       sfx_ins_arrow->loop   (false);
  sfxGameExitSound = new hssSound(); loadSFX(TEXT("main : SFX_GAME_EXIT_SOUND"), sfxGameExitSound->load(m_config.hInstance, SFX_GAME_EXIT_SOUND)); sfxGameExitSound->loop(false);
  sfxUnlockCode    = new hssSound(); loadSFX(TEXT("main : SFX_UNLOCKCODE"),      sfxUnlockCode->load   (m_config.hInstance, SFX_UNLOCKCODE));      sfxUnlockCode->loop   (false);
	sfxMisc1         = new hssSound(); loadSFX(TEXT("main : SFX_MISC_1"),          sfxMisc1->load        (m_config.hInstance, SFX_MISC_1));          sfxMisc1->loop        (false);
	sfxMisc2         = new hssSound(); loadSFX(TEXT("main : SFX_MISC_2"),          sfxMisc2->load        (m_config.hInstance, SFX_MISC_2));          sfxMisc2->loop        (false);
	sfxMisc3         = new hssSound(); loadSFX(TEXT("main : SFX_MISC_3"),          sfxMisc3->load        (m_config.hInstance, SFX_MISC_3));          sfxMisc3->loop        (false);
	sfxMisc4         = new hssSound(); loadSFX(TEXT("main : SFX_MISC_4"),          sfxMisc4->load        (m_config.hInstance, SFX_MISC_4));          sfxMisc4->loop        (false);
	sfxMisc5         = new hssSound(); loadSFX(TEXT("main : SFX_MISC_5"),          sfxMisc5->load        (m_config.hInstance, SFX_MISC_5));          sfxMisc5->loop        (false);

	// Read in KGA file.  It will be created if it doesn't exist in the app's directory
	readKGAFile();  

	return S_OK;

}


// ****************************************************************************************************************
// CreateVidMemSurfaces
// Not used, but has to be defined to compile
// ****************************************************************************************************************
HRESULT CGame::CreateVidMemSurfaces(CGapiDisplay* pDisplay, HINSTANCE hInstance) {

    // Images
	popup_border   = new CGapiSurface(); createSurface(TEXT("main : GFX_POPUP_BORDER"), popup_border->CreateSurface  (0, m_config.hInstance, GFX_POPUP_BORDER, TEXT("GRAPHICS"))); popup_border->SetColorKey  (RGB(255, 128, 255));
	gfx_ins_prev_0 = new CGapiSurface(); createSurface(TEXT("main : GFX_INS_PREV_0"),   gfx_ins_prev_0->CreateSurface(0, m_config.hInstance, GFX_INS_PREV_0,   TEXT("GRAPHICS"))); gfx_ins_prev_0->SetColorKey(RGB(255, 128, 255));
	gfx_ins_prev_1 = new CGapiSurface(); createSurface(TEXT("main : GFX_INS_PREV_1"),   gfx_ins_prev_1->CreateSurface(0, m_config.hInstance, GFX_INS_PREV_1,   TEXT("GRAPHICS"))); gfx_ins_prev_1->SetColorKey(RGB(255, 128, 255));
	gfx_ins_next_0 = new CGapiSurface(); createSurface(TEXT("main : GFX_INS_NEXT_0"),   gfx_ins_next_0->CreateSurface(0, m_config.hInstance, GFX_INS_NEXT_0,   TEXT("GRAPHICS"))); gfx_ins_next_0->SetColorKey(RGB(255, 128, 255));
	gfx_ins_next_1 = new CGapiSurface(); createSurface(TEXT("main : GFX_INS_NEXT_1"),   gfx_ins_next_1->CreateSurface(0, m_config.hInstance, GFX_INS_NEXT_1,   TEXT("GRAPHICS"))); gfx_ins_next_1->SetColorKey(RGB(255, 128, 255));

  // Fonts
	createSurface(TEXT("main : FNT_FONT1"),       font1.CreateSurface      (NULL, hInstance, FNT_FONT1, TEXT("FONTS")));
	createFont   (TEXT("main : FNT_FONT1"),       font1.CreateFont         (NULL, RGB(255, 128, 255), NULL, NULL));
	createSurface(TEXT("main : FNT_FONT1_GREEN"), font1_green.CreateSurface(NULL, hInstance, FNT_FONT1_GREEN, TEXT("FONTS")));
	createFont   (TEXT("main : FNT_FONT1_GREEN"), font1_green.CreateFont   (NULL, RGB(255, 128, 255), NULL, NULL));

  return S_OK;

}


// ****************************************************************************************************************
// CreateSysMemSurfaces
// Create any surfaces that are not specific to any mini-game
// ****************************************************************************************************************
HRESULT CGame::CreateSysMemSurfaces(CGapiDisplay* display, HINSTANCE hInstance) {
	return S_OK;
}


// ****************************************************************************************************************
// Game exit
// ****************************************************************************************************************
HRESULT CGame::ExitInstance() {

	// Shut down sound
	sndObj.close();

	delete popup_border;
	delete gfx_ins_prev_0;
	delete gfx_ins_prev_1;
	delete gfx_ins_next_0;
	delete gfx_ins_next_1;
  delete sfx_ins_arrow;
  delete sfxGameExitSound;
	delete sfxUnlockCode;
  delete sfxMisc1;
  delete sfxMisc2;
  delete sfxMisc3;
  delete sfxMisc4;
  delete sfxMisc5;

	return S_OK;

}


// ****************************************************************************************************************
// Called when the window is minimized
// ****************************************************************************************************************
HRESULT CGame::OnMinimize() {

	sndObj.suspend();
	return S_OK;

}


// ****************************************************************************************************************
// Called when the window is restores
// ****************************************************************************************************************
HRESULT CGame::OnRestore() {

	sndObj.resume();
	return S_OK;

}


// ****************************************************************************************************************
// Called to set overall volume from options screen
// ****************************************************************************************************************
void CGame::setVolumeLevel() {

	int dwSoundVolumeLevel = 0;
	switch (volumeLevel) {
		case vlNoSound: {
			dwSoundVolumeLevel = 0;
		break; }
		case vlLow: {
			dwSoundVolumeLevel = 22;
		break; }
		case vlMedium: {
			dwSoundVolumeLevel = 42;
		break; }
		case vlHigh: {
			dwSoundVolumeLevel = 64;
		break; }
	}
  sndObj.volumeMusics(dwSoundVolumeLevel);
  sndObj.volumeSounds(dwSoundVolumeLevel);

}


// ****************************************************************************************************************
// Called to initialize a new game
// ****************************************************************************************************************
void CGame::setupForNewGame() {

    levelHintDone             = false;
		gameRestarted             = false;
		game_mode	                = gmAdventureGame;
		whichGameBeingPlayed      = 0;
		games_done[0]             = false;
    games_done[1]             = false;
    games_done[2]             = false;
    games_done[3]             = false;
    games_done[4]             = false;
    health                    = 12;
    total_points              = 0;
    points_this_level         = 0;
		current_level             = 1;
		current_level_initialized = false;
		player_dir_north          = false;
		player_dir_south          = false;
		player_dir_east           = false;
		player_dir_west           = false;
		player_button_down        = false;
    overall_score             = 0;

}


// ************************************************************************************************
// oasisInitialize
// ************************************************************************************************
void CGame::oasisInitialize() {

	OASIS_ScriptPointer				= NULL;
	OASIS_NumberOfPlayers			= 0;
	OASIS_NumberOfAudioActors = 0;
	int i;

	for (i = 0; i < 40; i++) {
		OASIS_Actors[i].image = NULL;
	}

	// Load the Audio Actors array with the data from the array passed in
	for (i = 0; i < 20; i++) {
		OASIS_AudioActors[i].soundFX = NULL;
		OASIS_AudioActors[i].channel = NULL;
	}

	// Load the Text Actors array with the data from the array passed in
	for (i = 0; i < 10; i++) {
		OASIS_TextActors[i].resourceID = NULL;
	}

}


// ************************************************************************************************
// oasisStartScene
// ************************************************************************************************
void CGame::oasisStartScene(int OASIS_ScriptResourceID) {

  // Find the script resource and load into memory
  HGLOBAL hResD		 = NULL;
  void    *pvRes	 = NULL;
	HRSRC   hResInfo = NULL;
  hResInfo						= FindResource(m_config.hInstance, MAKEINTRESOURCE(OASIS_ScriptResourceID), TEXT("SCRIPTS"));
  hResD								= LoadResource(m_config.hInstance, hResInfo);
	pvRes								= LockResource(hResD);
	OASIS_ScriptPointer = (unsigned char*)pvRes;

	// Count the number of audio actors
	OASIS_NumberOfPlayers			= 0;
	OASIS_NumberOfAudioActors = 0;
  while (OASIS_AudioActors[OASIS_NumberOfAudioActors].soundFX != NULL) {
		OASIS_NumberOfAudioActors++;
	}

}


// ************************************************************************************************
// oasisEndScene
// ************************************************************************************************
void CGame::oasisEndScene() {

	sndObj.stopSounds();
  oasisInitialize();

}


// ************************************************************************************************
// oasisDoScene
// ************************************************************************************************
unsigned short int CGame::oasisDoScene(CGapiSurface* in_Display) {

	// If the pointer currently points to the end of the script, exit now indicating this condition
	if (*OASIS_ScriptPointer == 0x40) { // ("@")
		return 1;
	}

	// Not at the end of the script, so we must be about to process a frame
	while (*OASIS_ScriptPointer != 0x21) { // Process until end of frame indicator is found ("!")
		unsigned char nextCmd = *OASIS_ScriptPointer;
		OASIS_ScriptPointer++;
		switch (nextCmd) {

			// Add Player To Scene
			case 0x41: { // A
				// Get the ID of the actor
				unsigned char actorID = *OASIS_ScriptPointer++;
				// Add the actor to the array of players
				OASIS_Players[OASIS_NumberOfPlayers].actorID = actorID;
				OASIS_Players[OASIS_NumberOfPlayers].hidden  = true;
				OASIS_Players[OASIS_NumberOfPlayers].locX		 = 500;
				OASIS_Players[OASIS_NumberOfPlayers].locY		 = 500;
				// Increase our player count
				OASIS_NumberOfPlayers++;
			break; }

			// Change Actor ID Of Player
			case 0x49: { // I
				// Get the ID of the Player
				unsigned char playerID = *OASIS_ScriptPointer++;
				// Get the ID of the Actor to replace this Player with
				unsigned char actorID  = *OASIS_ScriptPointer++;
				// Update the ID of the player
				OASIS_Players[playerID].actorID = actorID;
			break; }

			// Hide All Players
			case 0x45: { // E
				// Set hidden to true for all players
				for (int i = 0; i < OASIS_NumberOfPlayers; i++) {
					OASIS_Players[i].hidden	 = true;
				}
			break; }

			// Hide Player
			case 0x48: { // H
				// Get the ID of the Player
				unsigned char playerID = *OASIS_ScriptPointer++;
				// Toggle it's hidden state
				OASIS_Players[playerID].hidden = true;
			break; }

			// Unhide Player
			case 0x55: { // U
				// Get the ID of the Player
				unsigned char playerID = *OASIS_ScriptPointer++;
				// Toggle it's hidden state
				OASIS_Players[playerID].hidden = false;
			break; }

			// Put Player To Screen Location
			case 0x50: { // P
				// Get the ID of the player
				unsigned char playerID = *OASIS_ScriptPointer++;
				// Get the X coordinate to put the player at (2 bytes)
				unsigned short int negativeXIndicator = *OASIS_ScriptPointer++;
				unsigned short int locX = (unsigned short int)((*OASIS_ScriptPointer << 8) + *(OASIS_ScriptPointer + 1));
				OASIS_ScriptPointer = OASIS_ScriptPointer + 2;
				// Get the Y coordinate to put the player at (2 bytes)
				unsigned short int negativeYIndicator = *OASIS_ScriptPointer++;
				unsigned short int locY = (unsigned short int)((*OASIS_ScriptPointer << 8) + *(OASIS_ScriptPointer + 1));
				OASIS_ScriptPointer = OASIS_ScriptPointer + 2;
				// Update the player's coordinates
				if (negativeXIndicator == 1) {
					OASIS_Players[playerID].locX = (short)(locX * -1);
				} else {
					OASIS_Players[playerID].locX = locX;
				}
				if (negativeYIndicator == 1) {
					OASIS_Players[playerID].locY = (short)(locY * -1);
				} else {
					OASIS_Players[playerID].locY = locY;
				}
			break; }

			// Move Player On Screen
			case 0x4d: { // M
				// Get the ID of the player
				unsigned char playerID = *OASIS_ScriptPointer++;
				// Get the number of pixels to move (2 bytes)
				unsigned short int numPixels = (unsigned short int)((*OASIS_ScriptPointer << 8) + *(OASIS_ScriptPointer + 1));
				OASIS_ScriptPointer = OASIS_ScriptPointer + 2;
				// Get the direction to move
				unsigned char dirMove = *OASIS_ScriptPointer++;
				// Update the player's coordinates
				switch (dirMove) {
					case 0x55: { // Up
						OASIS_Players[playerID].locY = (short)(OASIS_Players[playerID].locY - numPixels);
					break; }
					case 0x44: { // Down
						OASIS_Players[playerID].locY = (short)(OASIS_Players[playerID].locY + numPixels);
					break; }
					case 0x4c: { // Left
						OASIS_Players[playerID].locX = (short)(OASIS_Players[playerID].locX - numPixels);
					break; }
					case 0x52: { // Right
						OASIS_Players[playerID].locX = (short)(OASIS_Players[playerID].locX + numPixels);
					break; }
				}
			break; }

			// Play Sound FX
			case 0x58: { // X
				// Get the ID of the Audio Actor
				unsigned char audioactorID = *OASIS_ScriptPointer++;
				// Get the loop flag
				unsigned char loopFlag = *OASIS_ScriptPointer++;
				// Play the Sound FX
				bool lf = false;
				if (loopFlag == 1) {
					OASIS_AudioActors[audioactorID].soundFX->loop(true);
				} else {
					OASIS_AudioActors[audioactorID].soundFX->loop(false);
				}
				OASIS_AudioActors[audioactorID].channel = sndObj.playSound(OASIS_AudioActors[audioactorID].soundFX);
			break; }

			// Stop Sound FX
			case 0x53: { // S
				// Get the ID of the Audio Actor
				unsigned char audioactorID = *OASIS_ScriptPointer++;
				// Stop the sound FX
				sndObj.channel(OASIS_AudioActors[audioactorID].channel)->stop();
				OASIS_AudioActors[audioactorID].channel = NULL;
			break; }

			// Change Sound FX Volume
			case 0x46: { // F
				// Get the ID of the Audio Actor
				unsigned char audioactorID = *OASIS_ScriptPointer++;
				// Get the volume
				unsigned char volume = *OASIS_ScriptPointer++;
				// Change volume of the specified audio actor
				OASIS_AudioActors[audioactorID].soundFX->volume(volume);
			break; }

			// Silence All Sound FX
			case 0x4c: { // S
				// Stop the sound FX
				sndObj.stopSounds();
			break; }

			// Restore Default Volume
			case 0x52: { // R
				// Set the default volume of all audio actors
				for (int i = 0; i < OASIS_NumberOfAudioActors; i++) {
					OASIS_AudioActors[i].soundFX->volume(32);
				}
			break; }

			// Clear screen
			case 0x43: { // C
				// Get the red color component
				unsigned char colR	= *OASIS_ScriptPointer++;
				// Get the green color component
				unsigned char colG = *OASIS_ScriptPointer++;
				// Get the blue color component
				unsigned char colB = *OASIS_ScriptPointer++;
				// Do the clear right now
				in_Display->FillRect(NULL, RGB(colR, colG, colB), 0, NULL);
			break; }

			// Show Text
			case 0x54: { // T
				// Get the ID of the Text Actor
				unsigned char textActorID = *OASIS_ScriptPointer++;
				// Get the Red color component
				unsigned char colR = *OASIS_ScriptPointer++;
				// Get the Green color component
				unsigned char colG = *OASIS_ScriptPointer++;
				// Get the Blue color component
				unsigned char colB = *OASIS_ScriptPointer++;
				// Get the Location Top (2 bytes)
				unsigned short int locX = (unsigned short int)((*OASIS_ScriptPointer << 8) + *(OASIS_ScriptPointer + 1));
				OASIS_ScriptPointer = OASIS_ScriptPointer + 2;
				// Get the Location Left (2 bytes)
				unsigned short int locY = (unsigned short int)((*OASIS_ScriptPointer << 8) + *(OASIS_ScriptPointer + 1));
				OASIS_ScriptPointer = OASIS_ScriptPointer + 2;
				// Get the Align Setting
				unsigned char alignSetting = *OASIS_ScriptPointer++;
				TCHAR szText[32] = TEXT("");
				LoadString(m_config.hInstance, OASIS_TextActors[textActorID].resourceID, szText, 32);
        in_Display->DrawText(bbCenterPoint, locY, szText, &font1, GDDRAWTEXT_CENTER, NULL, NULL, NULL);
			break; }

		}
	}
	// Scene just ended, point to the next byte (either the next frame or the end of the script)
	OASIS_ScriptPointer++;
	// Oh, and uh... DRAW THE PLAYERS!!
	for (int i = 0; i < OASIS_NumberOfPlayers; i++) {
		if (!OASIS_Players[i].hidden) {
			in_Display->BltFast(OASIS_Players[i].locX, OASIS_Players[i].locY, OASIS_Actors[OASIS_Players[i].actorID].image, NULL, GDBLTFAST_KEYSRC, NULL);
		}
	}
	// Exit normally
	return 0;
}


// ****************************************************************************************************************
// Show the loading screen
// ****************************************************************************************************************
void CGame::showLoadingScreen(CGapiSurface* backbuffer, bool displayStuff, bool clearScreen) {

	if (loading || destroying) {
		processEvents = false;
		if (clearScreen) {
			backbuffer->FillRect(NULL, RGB(0, 0, 0), 0, NULL);
		}
		if (displayStuff) {
			backbuffer->DrawText(bbCenterPoint, 150, TEXT("... One Moment Please ..."), &font1, GDDRAWTEXT_CENTER, NULL, NULL, NULL);
		}
	}

}


// ****************************************************************************************************************
// Do initialization common to all mini-games
// ****************************************************************************************************************
void CGame::doCommonInit() {

	common_init_counter++;

	switch (common_init_counter) {

		case 1: {
			// Common Get Ready... Get Set... Go! images
			get_ready = new CGapiSurface(); createSurface(TEXT("main : GFX_GET_READY"), get_ready->CreateSurface(0, m_config.hInstance, GFX_GET_READY, TEXT("GRAPHICS"))); get_ready->SetColorKey(RGB(255, 128, 255));
			get_set   = new CGapiSurface(); createSurface(TEXT("main : GFX_GET_SET"),   get_set->CreateSurface  (0, m_config.hInstance, GFX_GET_SET,   TEXT("GRAPHICS"))); get_set->SetColorKey  (RGB(255, 128, 255));
			go        = new CGapiSurface(); createSurface(TEXT("main : GFX_GO"),        go->CreateSurface       (0, m_config.hInstance, GFX_GO,        TEXT("GRAPHICS"))); go->SetColorKey       (RGB(255, 128, 255));
			grgsg = true;
			grgsg_count = 0;
			gr_x1 = 34;
			gr_x2 = 166;
			gs_x1 = 54;
			gs_x2 = 145;
			g_x1 = 82;
			grgsg_y1 = 30;
			g_x2 = 118;
			grgsg_y2 = 54;
			// Common mini-game frame images
			mini_game_frame    = new CGapiSurface(); createSurface(TEXT("main : GFX_MINI_GAME_FRAME"),    mini_game_frame->CreateSurface   (0, m_config.hInstance, GFX_MINI_GAME_FRAME,     TEXT("GRAPHICS"))); mini_game_frame->SetColorKey   (RGB(255, 128, 255));
			mini_game_frame_l1 = new CGapiSurface(); createSurface(TEXT("main : GFX_MINI_GAME_FRAME_L1"), mini_game_frame_l1->CreateSurface(0, m_config.hInstance, GFX_MINI_GAME_FRAME_L1,  TEXT("GRAPHICS"))); mini_game_frame_l1->SetColorKey(RGB(255, 128, 255));
      mini_game_frame_l2 = new CGapiSurface(); createSurface(TEXT("main : GFX_MINI_GAME_FRAME_L2"), mini_game_frame_l2->CreateSurface(0, m_config.hInstance, GFX_MINI_GAME_FRAME_L2,  TEXT("GRAPHICS"))); mini_game_frame_l2->SetColorKey(RGB(255, 128, 255));
      mini_game_frame_l3 = new CGapiSurface(); createSurface(TEXT("main : GFX_MINI_GAME_FRAME_L3"), mini_game_frame_l3->CreateSurface(0, m_config.hInstance, GFX_MINI_GAME_FRAME_L3,  TEXT("GRAPHICS"))); mini_game_frame_l3->SetColorKey(RGB(255, 128, 255));
      mini_game_frame_l4 = new CGapiSurface(); createSurface(TEXT("main : GFX_MINI_GAME_FRAME_L4"), mini_game_frame_l4->CreateSurface(0, m_config.hInstance, GFX_MINI_GAME_FRAME_L4,  TEXT("GRAPHICS"))); mini_game_frame_l4->SetColorKey(RGB(255, 128, 255));
      mini_game_frame_l5 = new CGapiSurface(); createSurface(TEXT("main : GFX_MINI_GAME_FRAME_L5"), mini_game_frame_l5->CreateSurface(0, m_config.hInstance, GFX_MINI_GAME_FRAME_L5,  TEXT("GRAPHICS"))); mini_game_frame_l5->SetColorKey(RGB(255, 128, 255));
      mini_game_frame_r1 = new CGapiSurface(); createSurface(TEXT("main : GFX_MINI_GAME_FRAME_R1"), mini_game_frame_r1->CreateSurface(0, m_config.hInstance, GFX_MINI_GAME_FRAME_R1,  TEXT("GRAPHICS"))); mini_game_frame_r1->SetColorKey(RGB(255, 128, 255));
      mini_game_frame_r2 = new CGapiSurface(); createSurface(TEXT("main : GFX_MINI_GAME_FRAME_R2"), mini_game_frame_r2->CreateSurface(0, m_config.hInstance, GFX_MINI_GAME_FRAME_R2,  TEXT("GRAPHICS"))); mini_game_frame_r2->SetColorKey(RGB(255, 128, 255));
      mini_game_frame_r3 = new CGapiSurface(); createSurface(TEXT("main : GFX_MINI_GAME_FRAME_R3"), mini_game_frame_r3->CreateSurface(0, m_config.hInstance, GFX_MINI_GAME_FRAME_R3,  TEXT("GRAPHICS"))); mini_game_frame_r3->SetColorKey(RGB(255, 128, 255));
      mini_game_frame_r4 = new CGapiSurface(); createSurface(TEXT("main : GFX_MINI_GAME_FRAME_R4"), mini_game_frame_r4->CreateSurface(0, m_config.hInstance, GFX_MINI_GAME_FRAME_R4,  TEXT("GRAPHICS"))); mini_game_frame_r4->SetColorKey(RGB(255, 128, 255));
      mini_game_frame_r5 = new CGapiSurface(); createSurface(TEXT("main : GFX_MINI_GAME_FRAME_R5"), mini_game_frame_r5->CreateSurface(0, m_config.hInstance, GFX_MINI_GAME_FRAME_R5,  TEXT("GRAPHICS"))); mini_game_frame_r5->SetColorKey(RGB(255, 128, 255));
			// Common status bar image
			status_bar = new CGapiSurface(); createSurface(TEXT("main : 0x0019"), status_bar->CreateSurface (0, m_config.hInstance, GFX_STATUS_BAR,  TEXT("GRAPHICS"))); status_bar->SetColorKey(RGB(255, 128, 255));
			// Common left hand images
			left_hand_normal = new CGapiSurface(); createSurface(TEXT("main : GFX_LEFT_HAND_NORMAL"), left_hand_normal->CreateSurface(0, m_config.hInstance, GFX_LEFT_HAND_NORMAL, TEXT("GRAPHICS"))); left_hand_normal->SetColorKey(RGB(255, 128, 255));
      left_hand_left	 = new CGapiSurface(); createSurface(TEXT("main : GFX_LEFT_HAND_LEFT"),   left_hand_left->CreateSurface  (0, m_config.hInstance, GFX_LEFT_HAND_LEFT,   TEXT("GRAPHICS"))); left_hand_left->SetColorKey  (RGB(255, 128, 255));
      left_hand_right  = new CGapiSurface(); createSurface(TEXT("main : GFX_LEFT_HAND_RIGHT"),  left_hand_right->CreateSurface (0, m_config.hInstance, GFX_LEFT_HAND_RIGHT,  TEXT("GRAPHICS"))); left_hand_right->SetColorKey (RGB(255, 128, 255));
      left_hand_up		 = new CGapiSurface(); createSurface(TEXT("main : GFX_LEFT_HAND_UP"),     left_hand_up->CreateSurface    (0, m_config.hInstance, GFX_LEFT_HAND_UP,     TEXT("GRAPHICS"))); left_hand_up->SetColorKey    (RGB(255, 128, 255));
      left_hand_down	 = new CGapiSurface(); createSurface(TEXT("main : GFX_LEFT_HAND_DOWN"),   left_hand_down->CreateSurface  (0, m_config.hInstance, GFX_LEFT_HAND_DOWN,   TEXT("GRAPHICS"))); left_hand_down->SetColorKey  (RGB(255, 128, 255));
      left_hand_dl     = new CGapiSurface(); createSurface(TEXT("main : GFX_LEFT_HAND_DL"),     left_hand_dl->CreateSurface    (0, m_config.hInstance, GFX_LEFT_HAND_DL,     TEXT("GRAPHICS"))); left_hand_dl->SetColorKey    (RGB(255, 128, 255));
      left_hand_dr     = new CGapiSurface(); createSurface(TEXT("main : GFX_LEFT_HAND_DR"),     left_hand_dr->CreateSurface    (0, m_config.hInstance, GFX_LEFT_HAND_DR,     TEXT("GRAPHICS"))); left_hand_dr->SetColorKey    (RGB(255, 128, 255));
      left_hand_ul     = new CGapiSurface(); createSurface(TEXT("main : GFX_LEFT_HAND_UL"),     left_hand_ul->CreateSurface    (0, m_config.hInstance, GFX_LEFT_HAND_UL,     TEXT("GRAPHICS"))); left_hand_ul->SetColorKey    (RGB(255, 128, 255));
      left_hand_ur     = new CGapiSurface(); createSurface(TEXT("main : GFX_LEFT_HAND_UR"),     left_hand_ur->CreateSurface    (0, m_config.hInstance, GFX_LEFT_HAND_UR,     TEXT("GRAPHICS"))); left_hand_ur->SetColorKey    (RGB(255, 128, 255));
			right_hand_up	   = new CGapiSurface(); createSurface(TEXT("main : GFX_RIGHT_HAND_UP"),    right_hand_up->CreateSurface   (0, m_config.hInstance, GFX_RIGHT_HAND_UP,    TEXT("GRAPHICS"))); right_hand_up->SetColorKey   (RGB(255, 128, 255));
      right_hand_down  = new CGapiSurface(); createSurface(TEXT("main : GFX_RIGHT_HAND_DOWN"),  right_hand_down->CreateSurface (0, m_config.hInstance, GFX_RIGHT_HAND_DOWN,  TEXT("GRAPHICS"))); right_hand_down->SetColorKey (RGB(255, 128, 255));
			// Common console images
			console_left	 = new CGapiSurface(); createSurface(TEXT("main : GFX_CONSOLE_LEFT"),   console_left->CreateSurface  (0, m_config.hInstance, GFX_CONSOLE_LEFT,   TEXT("GRAPHICS"))); console_left->SetColorKey  (RGB(255, 128, 255));
      console_middle = new CGapiSurface(); createSurface(TEXT("main : GFX_CONSOLE_MIDDLE"), console_middle->CreateSurface(0, m_config.hInstance, GFX_CONSOLE_MIDDLE, TEXT("GRAPHICS"))); console_middle->SetColorKey(RGB(255, 128, 255));
      console_right	 = new CGapiSurface(); createSurface(TEXT("main : GFX_CONSOLE_RIGHT"),  console_right->CreateSurface (0, m_config.hInstance, GFX_CONSOLE_RIGHT,  TEXT("GRAPHICS"))); console_right->SetColorKey (RGB(255, 128, 255));
			// Common fuzz surfaces
			for (int fc = 0; fc < 5; fc++) {
				fuzz[fc] = new CGapiSurface();
				createSurface(TEXT("main : 0x0017"), fuzz[fc]->CreateSurface(NULL, 200, 200));
				for (int fcy = 0; fcy < 200; fcy++) {
					for (int fcx = 0; fcx < 200; fcx++) {
						pickPixel1:
						int fcc = rand() % 2;
						if (fcc != 0 && fcc != 1) { goto pickPixel1; }
						if (fcc == 0) { fcc = 100; }
						if (fcc == 1) { fcc = 200; }
						fuzz[fc]->SetPixel(fcx, fcy, RGB(fcc, fcc, fcc));
					}
				}
			}
      // Common variable inits
      lightChangeCounter       = 0;
			common_cleanup_counter   = 0;
			destroying_step          = 0;
			jumpBackToNewGameType    = false;
			player_pos.x             = 0;
			player_pos.y             = 0;
			player_dir_north		     = false;
			player_dir_south		     = false;
			player_dir_east			     = false;
			player_dir_west			     = false;
			player_button_down		   = false;
			player_left_hand_action  = lhNothing;
			player_right_hand_action = rhNothing;
			game_over_counter		     = 0;
			get_ready_counter		     = 0;
			mini_game_state			     = mgsInitialDraw;
			mini_game_score			     = 0;
			mini_game_score_last     = 0;
			player_dir_delay		     = 0;
			force_game_over			     = false;
			clear_game_surface       = true;
			status_first_time				 = true;
      game_over_check_done     = false;
    break; }

		case 12: {
			common_init_counter = 0;
		break; }

	}

	// If it's 0, we're done, but if it's not, we're still loading
	if (common_init_counter != 0) {
		loading_step--; // So that we'll stay on the same step in the calling loader
	}

}


// ****************************************************************************************************************
// Do cleanup common to all mini-games
// ****************************************************************************************************************
void CGame::doCommonCleanup() {

	common_cleanup_counter++;

	switch (common_cleanup_counter) {

		case 1: {
      sndObj.stopSounds();
			delete get_ready;
			delete get_set;
			delete go;
			delete fuzz[0];
			delete fuzz[1];
			delete fuzz[2];
			delete fuzz[3];
			delete fuzz[4];
			delete mini_game_frame;
      delete mini_game_frame_l1;
      delete mini_game_frame_l2;
      delete mini_game_frame_l3;
      delete mini_game_frame_l4;
      delete mini_game_frame_l5;
      delete mini_game_frame_r1;
      delete mini_game_frame_r2;
      delete mini_game_frame_r3;
      delete mini_game_frame_r4;
      delete mini_game_frame_r5;
			delete status_bar;
			delete left_hand_normal;
			delete left_hand_left;
			delete left_hand_right;
			delete left_hand_up;
			delete left_hand_down;
			delete left_hand_ul;
			delete left_hand_ur;
			delete left_hand_dl;
			delete left_hand_dr;
			delete right_hand_up;
			delete right_hand_down;
			delete console_left;
			delete console_middle;
			delete console_right;
		break; }

		case 6: {
			common_cleanup_counter = 0;
		break; }

	}

	// If it's 0, we're done, but if it's not, we're still loading
	if (common_cleanup_counter != 0) {
		destroying_step--; // So that we'll stay on the same step in the calling destroyer
	}

}


// ****************************************************************************************************************
// doLoad
// Called from a destroy function to begin loading the next screen
// ****************************************************************************************************************
void CGame::doLoad() {

	loading							 = true;
	loading_step				 = 0;
	destroying					 = false;
	destroying_step			 = 0;
	screen_after_destroy = 0;

}


// ****************************************************************************************************************
// doDestroy
// Called to destroy a screen
// ****************************************************************************************************************
void CGame::doDestroy(int sad) {

	loading							 = false;
	loading_step				 = 0;
	destroying					 = true;
	destroying_step			 = 0;
	if (game_mode == gmMiniGameMelee) {
		screen_after_destroy = csNewGameType;
	} else {
		screen_after_destroy = sad;
	}

}


// ****************************************************************************************************************
// countdownStartClock
// Called to begin mini-game time countdown
// ****************************************************************************************************************
void CGame::countdownStartClock() {

	// This method is called when a mini-game begins to start the countdown to completion
	countdown_seconds = 60;
	countdown_ticks   = GetTickCount();

}


// ****************************************************************************************************************
// updateStatusBar
// Called to display updated time and score on the status bar
// ****************************************************************************************************************
bool CGame::updateStatusBar(CGapiSurface* backbuffer) {

	// This method is called with every frame drawn of a mini-game to display remaining time and current score.
	// It returns FALSE if time has not elapsed, TRUE if it has.
	bool timeChanged = false;
	if ((GetTickCount() - countdown_ticks) >= 1000) {
		if (!doPopup && game_submode == gsmTimed) {
			timeChanged = true;
			countdown_seconds--;
			countdown_ticks = GetTickCount();
			if (countdown_seconds == 0) {
				return true;
			}
		}
	}

	// Draw time and score status bar
	if (!doPopup) {
		if ((game_submode == gsmTimed && timeChanged) || (game_submode == gsmTimed && status_first_time)) {
			backbuffer->BltFast(0, 300, status_bar, CRect(0, 0, 120, 20), GDBLTFAST_KEYSRC, NULL);
			TCHAR tVal[18];
			_stprintf(tVal, TEXT("%d"), countdown_seconds);
			TCHAR tOutStr[18] = TEXT("Time: ");
			_tcscat(tOutStr, tVal);
			backbuffer->DrawText(2, 300, tOutStr, &font1, GDDRAWTEXT_LEFT, NULL, NULL, NULL);
		}
		if (mini_game_score != mini_game_score_last || status_first_time) {
			backbuffer->BltFast(120, 301, status_bar, CRect(120, 0, 240, 20), GDBLTFAST_KEYSRC, NULL);
			TCHAR sVal[18];
			_stprintf(sVal, TEXT("%d"), mini_game_score);
			TCHAR sOutStr[18] = TEXT("Score: ");
			_tcscat(sOutStr, sVal);
			backbuffer->DrawText(238, 301, sOutStr, &font1, GDDRAWTEXT_RIGHT, NULL, NULL, NULL);
		}
	}

	status_first_time = false;
	mini_game_score_last = mini_game_score;

	return false;

}


// ****************************************************************************************************************
// updateFrame
// Called to do the lights on the mini-game frame
// ****************************************************************************************************************
void CGame::updateMiniGameFrameLights(CGapiSurface* backbuffer) {

  // Every half a second we are going to light some lights and restore others
  lightChangeCounter++;
  if (lightChangeCounter > 12) {
    lightChangeCounter = 0;
    int l1 = rand() % 2;
    int l2 = rand() % 2;
    int l3 = rand() % 2;
    int l4 = rand() % 2;
    int l5 = rand() % 2;
    int r1 = rand() % 2;
    int r2 = rand() % 2;
    int r3 = rand() % 2;
    int r4 = rand() % 2;
    int r5 = rand() % 2;
	  // Draw mini-game area frame
	  backbuffer->BltFast(0, 0, mini_game_frame, NULL, GDBLTFAST_KEYSRC, NULL);
    if (l1 == 1) { backbuffer->BltFast(0,   22,  mini_game_frame_l1, NULL, NULL, NULL); }
    if (l2 == 1) { backbuffer->BltFast(0,   64,  mini_game_frame_l2, NULL, NULL, NULL); }
    if (l3 == 1) { backbuffer->BltFast(0,   107, mini_game_frame_l3, NULL, NULL, NULL); }
    if (l4 == 1) { backbuffer->BltFast(0,   150, mini_game_frame_l4, NULL, NULL, NULL); }
    if (l5 == 1) { backbuffer->BltFast(0,   193, mini_game_frame_l5, NULL, NULL, NULL); }
    if (r1 == 1) { backbuffer->BltFast(220, 20,  mini_game_frame_r1, NULL, NULL, NULL); }
    if (r2 == 1) { backbuffer->BltFast(220, 62,  mini_game_frame_r2, NULL, NULL, NULL); }
    if (r3 == 1) { backbuffer->BltFast(220, 107, mini_game_frame_r3, NULL, NULL, NULL); }
    if (r4 == 1) { backbuffer->BltFast(220, 150, mini_game_frame_r4, NULL, NULL, NULL); }
    if (r5 == 1) { backbuffer->BltFast(220, 193, mini_game_frame_r5, NULL, NULL, NULL); }
  }

}


// ****************************************************************************************************************
// updateHands
// Called to update the hands as appropriate
// ****************************************************************************************************************
bool CGame::updateHands(CGapiSurface* backbuffer) {

  // Draw left hand, IF it's something different than last frame
  if (player_left_hand_action != lhNorth && player_dir_north && !player_dir_east && !player_dir_south && !player_dir_west) { // North
		backbuffer->BltFast(29, 240, left_hand_up,	NULL, GDBLTFAST_KEYSRC, NULL);
    player_left_hand_action = lhNorth;
  } else if (player_left_hand_action != lhEast && !player_dir_north && player_dir_east && !player_dir_south && !player_dir_west) { // East
		backbuffer->BltFast(29, 240, left_hand_right, NULL, GDBLTFAST_KEYSRC, NULL);
    player_left_hand_action = lhEast;
  } else if (player_left_hand_action != lhSouth && !player_dir_north && !player_dir_east && player_dir_south && !player_dir_west) { // South
		backbuffer->BltFast(29, 240, left_hand_down, NULL, GDBLTFAST_KEYSRC, NULL);
    player_left_hand_action = lhSouth;
  }	else if (player_left_hand_action != lhWest && !player_dir_north && !player_dir_east && !player_dir_south && player_dir_west) { // West
		backbuffer->BltFast(29, 240, left_hand_left,	NULL, GDBLTFAST_KEYSRC, NULL);
    player_left_hand_action = lhWest;
  } else if (player_left_hand_action != lhNorthEast && player_dir_north && player_dir_east && !player_dir_south && !player_dir_west) { // NorthEast
		backbuffer->BltFast(29, 240, left_hand_ur, NULL, GDBLTFAST_KEYSRC, NULL);
    player_left_hand_action = lhNorthEast;
  } else if (player_left_hand_action != lhNorthWest && player_dir_north && !player_dir_east && !player_dir_south && player_dir_west) { // NorthWest
		backbuffer->BltFast(29, 240, left_hand_ul, NULL, GDBLTFAST_KEYSRC, NULL);
    player_left_hand_action = lhNorthWest;
  }	else if (player_left_hand_action != lhSouthEast && !player_dir_north && player_dir_east && player_dir_south && !player_dir_west) { // SouthEast
		backbuffer->BltFast(29, 240, left_hand_dr, NULL, GDBLTFAST_KEYSRC, NULL);
    player_left_hand_action = lhSouthEast;
  } else if (player_left_hand_action != lhSouthWest && !player_dir_north && !player_dir_east && player_dir_south && player_dir_west) { // SouthWest
		backbuffer->BltFast(29, 240, left_hand_dl, NULL, GDBLTFAST_KEYSRC, NULL);
    player_left_hand_action = lhSouthWest;
	} else if (player_left_hand_action != lhNothing && !player_dir_north && !player_dir_east && !player_dir_south && !player_dir_west) { // Nothing
		backbuffer->BltFast(29, 240, left_hand_normal, NULL, GDBLTFAST_KEYSRC, NULL);
    player_left_hand_action = lhNothing;
	}

  // Draw right hand, IF it's something other than last frame
	if (player_right_hand_action != rhDown && player_button_down) {
		backbuffer->BltFast(145, 240, right_hand_down, NULL, GDBLTFAST_KEYSRC, NULL);
    player_right_hand_action = rhDown;
  } else if (player_right_hand_action != rhNothing && !player_button_down) {
		backbuffer->BltFast(145, 240, right_hand_up,	NULL, GDBLTFAST_KEYSRC, NULL);
    player_right_hand_action = rhNothing;
	}

	return false;

}


// ****************************************************************************************************************
// doGetReady
// Called to do the Get Ready... Get Set... Go sequence to start a mini-game
// ****************************************************************************************************************
void CGame::doGetReady(CGapiSurface* backbuffer, TCHAR* game_name, TCHAR* target_score) {

  processEvents      = false;
	player_dir_west	   = false;
	player_dir_east	   = false;
  player_button_down = false;
  updateHands(backbuffer);

	// Flashing lights
	updateMiniGameFrameLights(backbuffer);

  // Fuzz
  backbuffer->BltFast(xadj, yadj, fuzz[fuzzIndex], NULL, NULL, NULL);
  fuzzIndex++; if (fuzzIndex > 4) { fuzzIndex = 0; }

	// Game name
  backbuffer->DrawText(bbCenterPoint, yadj + 90, game_name, &font1, GDDRAWTEXT_CENTER, NULL, NULL, NULL);
	
	// If in Adventure Mode, show Target Score
	if (game_mode == gmAdventureGame) {
		TCHAR szOut[26] = TEXT("Target Score: ");
		_tcscat(szOut, target_score);
		backbuffer->DrawText(bbCenterPoint, yadj + 140, szOut, &font1, GDDRAWTEXT_CENTER, NULL, NULL, NULL);
	}

	// If in Melee Mode, show the high score for either Timed Mode or PUISS Mode
	if (game_mode == gmMiniGameMelee) {
		TCHAR szHS[20] = TEXT("");
		if (game_submode == gsmTimed) {	
			_stprintf(szHS, TEXT("%d"), miniGameHighsTimed[current_mini_game]);
		} else {
			_stprintf(szHS, TEXT("%d"), miniGameHighsPUISS[current_mini_game]);
		}
		TCHAR szOut[25] = TEXT("High Score: ");
		_tcscat(szOut, szHS);
		backbuffer->DrawText(bbCenterPoint, yadj + 140, szOut, &font1, GDDRAWTEXT_CENTER, NULL, NULL, NULL);
	}

	// Draw the appropriate text
	if (get_ready_counter > 0 && get_ready_counter < 24) {
		backbuffer->Blt(CRect(xadj + gr_x1, yadj + grgsg_y1, xadj + gr_x2, yadj + grgsg_y2), get_ready, NULL, GDBLT_KEYSRC, NULL);
	}
	if (get_ready_counter > 24 && get_ready_counter < 48) {
		backbuffer->Blt(CRect(xadj + gs_x1, yadj + grgsg_y1, xadj + gs_x2, yadj + grgsg_y2), get_set, NULL, GDBLT_KEYSRC, NULL);
	}
	if (get_ready_counter > 48 && get_ready_counter < 72) {
		backbuffer->Blt(CRect(xadj + g_x1, yadj + grgsg_y1, xadj + g_x2, yadj + grgsg_y2), go, NULL, GDBLT_KEYSRC, NULL);
	}

	if (grgsg) {
		gr_x1 = gr_x1 - 2; gr_x2 = gr_x2 + 2,
		gs_x1 = gs_x1 - 2; gs_x2 = gs_x2 + 2,
		g_x1 = g_x1 - 2; grgsg_y1 = grgsg_y1 - 2; g_x2 = g_x2 + 2, grgsg_y2 = grgsg_y2 + 2;
	} else {
		gr_x1 = gr_x1 + 2; gr_x2 = gr_x2 - 2,
		gs_x1 = gs_x1 + 2; gs_x2 = gs_x2 - 2,
		g_x1 = g_x1 + 2; grgsg_y1 = grgsg_y1 + 2; g_x2 = g_x2 - 2, grgsg_y2 = grgsg_y2 - 2;
	}
	grgsg_count++;
	if (grgsg_count > 4) { 
		grgsg = !grgsg; 
		grgsg_count = 0;
	}

	if (get_ready_counter > 72) {
    processEvents = true;
		// Change state to start game
		mini_game_state = mgsGameRunning;
		countdownStartClock(); // Start the countdown clock
	}

	get_ready_counter++;

}


// ****************************************************************************************************************
// doGameOver
// Called to display the Game Over when a mini-game finishes.
// ****************************************************************************************************************
void CGame::doGameOver(CGapiSurface* backbuffer, int next_screen, unsigned long int target_score) {

  processEvents = false;

  if (game_over_counter < 40) {

    // Final checks, only done once
    if (!game_over_check_done) {
			new_high_score = false; // By default, assume NOT melee mode and high score was NOT beat
      game_over_check_done = true;
			// If playing adventure mode and the score was >= the target score, unlock the mini-game
      if (game_mode == gmAdventureGame && mini_game_score >= target_score) {
		  overall_score = overall_score + mini_game_score;
			  games_done[whichGameBeingPlayed] = true;
				for (int i = 0; i < 25; i++) {
				  if (melee_selection[i] == current_screen) { game_unlocked[i] = true; }
				}
			}
			// If in melee mode and the score was >= the current high score (depending on submode), record it
			if (game_mode == gmMiniGameMelee) {
				if (game_submode == gsmTimed && mini_game_score > miniGameHighsTimed[current_mini_game]) {
					miniGameHighsTimed[current_mini_game] = mini_game_score;
					new_high_score = true;
				}
				if (game_submode == gsmAlaCarte && mini_game_score > miniGameHighsPUISS[current_mini_game]) {
					miniGameHighsPUISS[current_mini_game] = mini_game_score;
					new_high_score = true;
				}
			}
			// Write out the KGA file regardless of what we did above
			writeKGAFile(gameRestarted, false);
    }
	  // Flashing lights
	  updateMiniGameFrameLights(backbuffer);
    // Fuzz
    backbuffer->BltFast(xadj, yadj, fuzz[fuzzIndex], NULL, NULL, NULL);
    fuzzIndex++; if (fuzzIndex > 4) { fuzzIndex = 0; }
    // Draw the appropriate text
    backbuffer->DrawText(bbCenterPoint,  yadj + 40, TEXT("Game Over"), &font1, GDDRAWTEXT_CENTER, NULL, NULL, NULL);
		// If in Adventure Mode, display mission status
		if (game_mode == gmAdventureGame) {
			if (mini_game_score >= target_score) {
				backbuffer->DrawText(bbCenterPoint, yadj + 100, TEXT("Mission accomplished!"), &font1, GDDRAWTEXT_CENTER, NULL, NULL, NULL);
			} else {
				backbuffer->DrawText(bbCenterPoint, yadj + 100, TEXT("Mission failed!"), &font1, GDDRAWTEXT_CENTER, NULL, NULL, NULL);
			}
		} else { // Must be in Melee mode, so display the appropriate high score message
			if (new_high_score) {
				backbuffer->DrawText(bbCenterPoint, yadj + 100, TEXT("A NEW HIGH SCORE!"), &font1, GDDRAWTEXT_CENTER, NULL, NULL, NULL);
			} else {
				backbuffer->DrawText(bbCenterPoint, yadj + 100, TEXT("High Score Still Stands"), &font1, GDDRAWTEXT_CENTER, NULL, NULL, NULL);
			}
		}
    // Continue
	  game_over_counter++;
	  // Draw status bar and score
	  backbuffer->BltFast(0, 300, status_bar, NULL, GDBLTFAST_KEYSRC, NULL);
	  TCHAR sVal[18];
	  _stprintf(sVal, TEXT("%d"), mini_game_score);
	  TCHAR sOutStr[18] = TEXT("Score: ");
	  _tcscat(sOutStr, sVal);
    backbuffer->DrawText(bbCenterPoint, 301, sOutStr, &font1, GDDRAWTEXT_CENTER, NULL, NULL, NULL);

	} else {
		// Exit game, go to the next screen
		doDestroy(next_screen);
		return;
	}

}


// ****************************************************************************************************************
// doInitialDraw
// Does the initial static drawings on a mini-game screen
// ****************************************************************************************************************
void CGame::doInitialDraw(CGapiSurface* backbuffer) {

	// Clear screen
	backbuffer->FillRect(NULL, RGB(0, 0, 0), 0, NULL);

	// Draw mini-game area frame
	backbuffer->BltFast(0, 0, mini_game_frame, NULL, GDBLTFAST_KEYSRC, NULL);

	// Draw console parts and initial hands
	backbuffer->BltFast(0,   240, console_left,		 NULL, GDBLTFAST_KEYSRC, NULL);
	backbuffer->BltFast(29,  240, left_hand_normal, NULL, GDBLTFAST_KEYSRC, NULL);
	backbuffer->BltFast(108, 240, console_middle,	 NULL, GDBLTFAST_KEYSRC, NULL);
	backbuffer->BltFast(145, 240, right_hand_up,		 NULL, GDBLTFAST_KEYSRC, NULL);
	backbuffer->BltFast(215, 240, console_right,		 NULL, GDBLTFAST_KEYSRC, NULL);

	// Draw status bar and game title
	backbuffer->BltFast(0, 300, status_bar, NULL, GDBLTFAST_KEYSRC, NULL);

	// Change state
	mini_game_state = mgsInstructions;

}


// ****************************************************************************************************************
// addToScore
// Adds to the current mini-game score
// ****************************************************************************************************************
void CGame::addToScore(unsigned long int value) {

	mini_game_score = mini_game_score + value;

}


// ****************************************************************************************************************
// subtractFromScore
// Subtracts from the current mini-game score
// ****************************************************************************************************************
void CGame::subtractFromScore(unsigned long int value) {

	if (mini_game_score <= value) { mini_game_score = 0; return; }
	mini_game_score = mini_game_score - value;
	if (mini_game_score <= 0) {
    MessageBox(NULL, TEXT(""), TEXT(""), MB_OK);
		mini_game_score = 0;
	}

}


// ****************************************************************************************************************
// doInstructions
// ?
// ****************************************************************************************************************
void CGame::doInstructions(CGapiSurface* backbuffer) {

	// Flashing lights
	updateMiniGameFrameLights(backbuffer);

  // Fuzz
  backbuffer->BltFast(xadj, yadj, fuzz[fuzzIndex], NULL, NULL, NULL);
  fuzzIndex++; if (fuzzIndex > 4) { fuzzIndex = 0; }

  int iAdd = mgInstructionsPage * 10; // 10 lines per page of instructions
  int y = 22;
  bool firstLineDone = false;
  for (int i = iAdd; i < iAdd + 10; i++) {
    if (firstLineDone) {
      backbuffer->DrawText(22, y, mgInstructions[i], &font1, GDDRAWTEXT_LEFT, NULL, NULL, NULL);
    } else {
      firstLineDone = true;
      backbuffer->DrawText(bbCenterPoint, y, mgInstructions[i], &font1, GDDRAWTEXT_CENTER, NULL, NULL, NULL);
    }
    y = y + 16;
  }
	if (mgiPrevTapped)	{
		backbuffer->BltFast(20, 194, gfx_ins_prev_1, NULL, GDBLTFAST_KEYSRC, NULL);
	} else {
		backbuffer->BltFast(20, 194, gfx_ins_prev_0, NULL, GDBLTFAST_KEYSRC, NULL);
	}
  backbuffer->DrawText(bbCenterPoint, 196, TEXT("ACTION/Click begins"), &font1, GDDRAWTEXT_CENTER, NULL, NULL, NULL);
	if (mgiNextTapped)	{
		backbuffer->BltFast(196, 194, gfx_ins_next_1, NULL, GDBLTFAST_KEYSRC, NULL);
	} else {
		backbuffer->BltFast(196, 194, gfx_ins_next_0, NULL, GDBLTFAST_KEYSRC, NULL);
	}

}


// ****************************************************************************************************************
// KeyDown handler for mini-game instructions
// ****************************************************************************************************************
void CGame::kdMGInstructions(DWORD dwKey) {

	// Handle left movement events
	if (dwKey == kLeft) {
    mgiPrevTapped = true;
		player_dir_west	= true;
	}

	// Handle right movement events
	if (dwKey == kRight) {
    mgiNextTapped = true;
		player_dir_east	= true;
	}

	// Handle keypress
	if (dwKey == kAction) {
    player_button_down = true;
  }

}


// ****************************************************************************************************************
// KeyUp handler for mini-game instructions
// ****************************************************************************************************************
void CGame::kuMGInstructions(DWORD dwKey) {

	player_dir_west	   = false;
	player_dir_east	   = false;
  player_button_down = false;

	// Handle left movement events
	if (dwKey == kLeft) {
    sndObj.playSound(sfx_ins_arrow);
    mgiPrevTapped = false;
    mgInstructionsPage--;
    if (mgInstructionsPage < 0) { mgInstructionsPage = 2; }
	}

	// Handle right movement events
	if (dwKey == kRight) {
    sndObj.playSound(sfx_ins_arrow);
    mgiNextTapped = false;
    mgInstructionsPage++;
    if (mgInstructionsPage > 2) { mgInstructionsPage = 0; }
	}

	// Handle keypress
	if (dwKey == kAction) {
    sndObj.playSound(sfxMisc2);
    mini_game_state = mgsGetReady;
	}

}


// ****************************************************************************************************************
// StylusDown handler for mini-game instructions screen
// ****************************************************************************************************************
void CGame::sdMGInstructions(POINT p) {

	if (PtInRect(CRect(20, 194, 44, 218),  p)) { // Previous
		kdMGInstructions(kLeft);
		return;
	}

	if (PtInRect(CRect(196, 194, 220, 218),  p)) { // Next
		kdMGInstructions(kRight);
		return;
	}

	if (PtInRect(CRect(48, 196, 192, 216),  p)) { // Select
		kdMGInstructions(kAction);
		return;
	}

}


// ****************************************************************************************************************
// StylusUp handler for mini-game instructions screen
// ****************************************************************************************************************
void CGame::suMGInstructions(POINT p) {

	if (mgiPrevTapped && PtInRect(CRect(20, 194, 44, 218),  p)) { // Previous
		kuMGInstructions(kLeft);
		return;
	}

	if (mgiNextTapped && PtInRect(CRect(196, 194, 220, 218),  p)) { // Next
		kuMGInstructions(kRight);
		return;
	}

	if (player_button_down && PtInRect(CRect(48, 196, 192, 216),  p)) { // Select
		kuMGInstructions(kAction);
		return;
	}

	player_dir_east = false;
	player_dir_west = false;
	mgiPrevTapped = false;
	mgiNextTapped = false;
	player_button_down = false;

}


// ****************************************************************************************************************
// Scrolling background for menu and related screens
// ****************************************************************************************************************
void CGame::scrollingBackground(CGapiSurface* backbuffer) {

	int y1;

	for (int y = -1; y < 6; y++) {
		y1 = (y * 60) + v_offset;
		for (int x = 0; x < 5; x++) {
      backbuffer->BltFast((x * 60) - h_offset, y1, background_tile, NULL, NULL, NULL);
		}
	}

	h_offset++;
	v_offset++;
	if (h_offset > 60) { h_offset = 0; v_offset = 0; }

}


// ****************************************************************************************************************
// Function for fading between screens
// ****************************************************************************************************************
void CGame::screenFader() {

  switch (fade_function) {
    case 1: { // Out
			processEvents = false;
      fade_value = fade_value - 20;
      if (fade_value <= 0) { current_screen = next_screen; fade_function = 2; fade_value = 0; }
    break; }
    case 2: { // In
			processEvents = false;
      fade_value = fade_value + 20;
      if (fade_value >= 255) { fade_function = 0; fade_value = 255; processEvents = true; }
    break; }
	}

}


// ****************************************************************************************************************
// Initializes a popup
// ****************************************************************************************************************
void CGame::startPopup(TCHAR* line1, TCHAR* line2) {
	_tcscpy(popupLine1, line1);
	_tcscpy(popupLine2, line2);
  sndObj.playSound(sfxMisc1);
  gpBlendDone = false;
	gpButtonPressed = 0;
	player_dir_east = false;
	player_dir_west = false;
	player_dir_north = false;
	player_dir_south = false;
	player_button_down = false;
	doPopup = true;
  gpCurrentOption = 0;
  gpTempBlended = new CGapiSurface();
	createSurface(TEXT("main : 0x0034"), gpTempBlended->CreateSurface(NULL, 170, 88));
}


// ****************************************************************************************************************
// Handles KeyDown popup events
// ****************************************************************************************************************
void CGame::kdPopup(DWORD dwKey) {
  if (dwKey == kLeft) {
    gpButtonPressed = 1;
    player_dir_west	= true;
  }
  if (dwKey == kRight) {
    gpButtonPressed = 2;
    player_dir_east	= true;
  }
  if (dwKey == kAction) {
    player_button_down = true;
  }
}


// ****************************************************************************************************************
// Handles KeyUp popup events
// ****************************************************************************************************************
void CGame::kuPopup(DWORD dwKey) {

  if (dwKey == kLeft && gpButtonPressed == 1) {
		gpButtonPressed = 0;
		player_dir_west = false;
    sndObj.playSound(sfx_ins_arrow);
    gpCurrentOption--;
    if (gpCurrentOption < 0) { gpCurrentOption = gpOptionsCount - 1; }
  }
  if (dwKey == kRight && gpButtonPressed == 2) {
		gpButtonPressed = 0;
		player_dir_east = false;
    sndObj.playSound(sfx_ins_arrow);
    gpCurrentOption++;
    if (gpCurrentOption > gpOptionsCount - 1) { gpCurrentOption = 0; }
  }
  if (dwKey == kAction && player_button_down)	{
		doPopup = false;
		player_dir_east = false;
		player_dir_west = false;
		player_dir_north = false;
		player_dir_south = false;
		player_button_down = false;
    sndObj.playSound(sfxMisc4);
    delete gpTempBlended;
		(*this.*popupCallback)(gpCurrentOption);
  }

}


// ****************************************************************************************************************
// StylusDown handler for popups
// ****************************************************************************************************************
void CGame::sdPopup(POINT p) {

	if (PtInRect(CRect(35, 117, 59, 141),  p)) { // Previous
		kdPopup(kLeft);
		return;
	}

	if (PtInRect(CRect(178, 117, 202, 141),  p)) { // Next
		kdPopup(kRight);
		return;
	}

	if (PtInRect(CRect(63, 119, 174, 139),  p)) { // Select
		kdPopup(kAction);
		return;
	}

}


// ****************************************************************************************************************
// StylusUp handler for popups
// ****************************************************************************************************************
void CGame::suPopup(POINT p) {

	if (gpButtonPressed == 1 && PtInRect(CRect(35, 117, 59, 141),  p)) { // Previous
		kuPopup(kLeft);
		return;
	}

	if (gpButtonPressed == 2 && PtInRect(CRect(178, 117, 202, 141),  p)) { // Next
		kuPopup(kRight);
		return;
	}

	if (player_button_down && PtInRect(CRect(63, 119, 174, 139),  p)) { // Select
		kuPopup(kAction);
		return;
	}

	player_dir_east = false;
	player_dir_west = false;
	player_button_down = false;
	gpButtonPressed = 0;

}


// ****************************************************************************************************************
// Handles Popup ProcessNextFrame events
// ****************************************************************************************************************
void CGame::pnfPopup(CGapiSurface* backbuffer) {

  if (gpBlendDone) {
    backbuffer->BltFast(34, 65, gpTempBlended, NULL, NULL, NULL);
  } else {
	  // Blended region
	  GDFILLRECTFX gdfillrectfx;
	  gdfillrectfx.dwOpacity = 128;
	  RECT rect;
	  SetRect(&rect, 34, 65, 204, 153);
    backbuffer->FillRect(&rect, RGB(0, 0, 250), GDFILLRECT_OPACITY, &gdfillrectfx);
    gpBlendDone = true;
    gpTempBlended->BltFast(0, 0, backbuffer, &rect, NULL, NULL);
  }
	// Border
	backbuffer->BltFast(28, 59, popup_border, NULL, GDBLTFAST_KEYSRC, NULL);
	// Text
	backbuffer->DrawText(bbCenterPoint, 72, popupLine1, &font1, GDDRAWTEXT_CENTER, NULL, NULL, NULL);
	backbuffer->DrawText(bbCenterPoint, 92, popupLine2, &font1, GDDRAWTEXT_CENTER, NULL, NULL, NULL);
	// Arrows
	if (gpButtonPressed == 1) {
		backbuffer->BltFast(35, 117, gfx_ins_prev_1, NULL, GDBLTFAST_KEYSRC, NULL);
	} else {
		backbuffer->BltFast(35, 117, gfx_ins_prev_0, NULL, GDBLTFAST_KEYSRC, NULL);
	}
	if (gpButtonPressed == 2) {
		backbuffer->BltFast(178, 117, gfx_ins_next_1, NULL, GDBLTFAST_KEYSRC, NULL);
	} else {
		backbuffer->BltFast(178, 117, gfx_ins_next_0, NULL, GDBLTFAST_KEYSRC, NULL);
	}
  // Option text
  backbuffer->DrawText(bbCenterPoint, 119, gpOptions[gpCurrentOption], &font1, GDDRAWTEXT_CENTER, NULL, NULL, NULL);
	if (current_screen != csWalkingAroundTheShip && current_screen != csMainMenu && current_screen != csNewGameType) {
		updateHands(backbuffer);
	}

}


// ****************************************************************************************************************
// Called when the command button is clicked during a mini-game
// ****************************************************************************************************************
void CGame::miniGameCommandButtonHandler() {

  player_button_down = false;
  // Do a popup...
  // Popup callback
  CGame::popupCallback = CGame::popupCallbackMiniGame;
  // Popup options
  gpOptionsCount = 2;
  _tcscpy(gpOptions[0], TEXT("Continue Game"));
  _tcscpy(gpOptions[1], TEXT("Quit Game"));
  // Start popup
  startPopup(TEXT("What would you"), TEXT("like to do?"));

}


// ****************************************************************************************************************
// Called when a popup is dismissed during a mini-game
// ****************************************************************************************************************
void CGame::popupCallbackMiniGame(int option) {

  switch (option) {
    case 1:  { // Quit
		  force_game_over = true;
    break; }
	}

}


// ****************************************************************************************************************
// Reads in the High Scores & Settings file, creates a new one if not found in current directory
// ****************************************************************************************************************
bool CGame::readKGAFile() {

  TCHAR fileName[152] = TEXT("");
	_tcscat(fileName, gameEXEPath);
	_tcscat(fileName, TEXT("kga.kga"));

  FILE*   file;
  KGAFILE kgaFile;
  if ((file = _tfopen(fileName, TEXT("r"))) == NULL) {
    writeKGAFile(false, true);
    file = _tfopen(fileName, TEXT("r"));
  }
  fread(&kgaFile, 1, sizeof(KGAFILE), file);
  fclose(file);

  int i;

  volumeLevel = kgaFile.volumeLevel;
  setVolumeLevel();
  kUp = kgaFile.kUp;
  kDown = kgaFile.kDown;
  kLeft = kgaFile.kLeft;
  kRight = kgaFile.kRight;
  kAction = kgaFile.kAction;
  kCommand = kgaFile.kCommand;
  for (i = 0; i < 30; i++) { game_unlocked[i]	     = kgaFile.miniGameLockFlags[i];  }
  for (i = 0; i < 30; i++) { miniGameHighsTimed[i] = kgaFile.miniGameHighsTimed[i]; }
  for (i = 0; i < 30; i++) { miniGameHighsPUISS[i] = kgaFile.miniGameHighsPUISS[i]; }
  // Games from first level are always unlocked regardless
  game_unlocked[0]  = true; kgaFile.miniGameLockFlags[0]  = true;
  game_unlocked[4]  = true; kgaFile.miniGameLockFlags[4]  = true;
  game_unlocked[5]  = true; kgaFile.miniGameLockFlags[5]  = true;
  game_unlocked[10] = true; kgaFile.miniGameLockFlags[10] = true;
  game_unlocked[22] = true; kgaFile.miniGameLockFlags[22] = true;
  gameRestarted = kgaFile.gameSavedFlag;
  current_level = kgaFile.currentLevel;
  health = kgaFile.playerHealth;
	for (i = 0; i < 5; i++) { games_done[i] = kgaFile.miniGamesCompletedFlags[i]; }
  cl_ul_tile = kgaFile.ulTile;
  cl_horizontal_offset = kgaFile.tileOffsetH;
  cl_vertical_offset = kgaFile.tileOffsetV;
  cl_player_position = kgaFile.playerPosition;
  levelHintDone = kgaFile.levelHintDone;
  overall_score = kgaFile.overall_score;

  // Deal with conversion issues now
  if (kgaFile.kgaFileVersion == 1) {
	  // When converting from v1 to v2, the only thing to worry about is the high scores, which were added in
	  // v2 (K&G Arcade v1.1).  To handle that, all we need to do is set each element of the two high score
	  // arrays to 0 in the class-level arrays, then write out the KGA file.  Everything else should be
	  // converted over automagically (the only changes to the file structure was the addition of the two
	  // high score arrays and the data type change of the overall_score element).
	  for (i = 0; i < 30; i++) { miniGameHighsTimed[i] = 0; }
	  for (i = 0; i < 30; i++) { miniGameHighsPUISS[i] = 0; }
	  writeKGAFile(gameRestarted, false);
  }

  return true;

}


// ****************************************************************************************************************
// Writes out the High Scores & Settings file, creates a new one if not found in current directory
// ****************************************************************************************************************
bool CGame::writeKGAFile(bool hasGameStarted, bool initialCreation) {

  TCHAR fileName[152] = TEXT("");
	_tcscat(fileName, gameEXEPath);
	_tcscat(fileName, TEXT("kga.kga"));

  KGAFILE kgaFile;
  kgaFile.kgaFileVersion = 2;
  kgaFile.volumeLevel = volumeLevel;
  kgaFile.kUp = kUp;
  kgaFile.kDown = kDown;
  kgaFile.kLeft = kLeft;
  kgaFile.kRight = kRight;
  kgaFile.kAction = kAction;
  kgaFile.kCommand = kCommand;
	int i;
  for (i = 0; i < 30; i++) { kgaFile.miniGameLockFlags[i]  = game_unlocked[i];      }
	for (i = 0; i < 30; i++) { kgaFile.miniGameHighsTimed[i] = miniGameHighsTimed[i]; }
	for (i = 0; i < 30; i++) { kgaFile.miniGameHighsPUISS[i] = miniGameHighsPUISS[i]; }
  if (initialCreation) {
    game_unlocked[0]  = true; kgaFile.miniGameLockFlags[0]  = true;
    game_unlocked[4]  = true; kgaFile.miniGameLockFlags[4]  = true;
    game_unlocked[5]  = true; kgaFile.miniGameLockFlags[5]  = true;
    game_unlocked[10] = true; kgaFile.miniGameLockFlags[10] = true;
    game_unlocked[22] = true; kgaFile.miniGameLockFlags[22] = true;
		for (i = 0; i < 30; i++) { kgaFile.miniGameHighsTimed[i] = 0; }
		for (i = 0; i < 30; i++) { kgaFile.miniGameHighsPUISS[i] = 0; }
  }
  kgaFile.gameSavedFlag = hasGameStarted;
	if (hasGameStarted) {
    kgaFile.currentLevel = current_level;
		kgaFile.playerHealth = health;
		for (i = 0; i < 5; i++) { kgaFile.miniGamesCompletedFlags[i] = games_done[i]; }
		kgaFile.ulTile = cl_ul_tile;
		kgaFile.tileOffsetH = cl_horizontal_offset;
		kgaFile.tileOffsetV = cl_vertical_offset;
		kgaFile.playerPosition = cl_player_position;
		kgaFile.levelHintDone = levelHintDone;
		kgaFile.overall_score = overall_score;
	} else {
		kgaFile.currentLevel = 0;
		kgaFile.playerHealth = 0;
		for (i = 0; i < 5; i++) { kgaFile.miniGamesCompletedFlags[i] = false; }
		POINT p;
		p.x = 0; p.y = 0;
		kgaFile.ulTile = p;
		kgaFile.tileOffsetH = 0;
		kgaFile.tileOffsetV = 0;
		kgaFile.playerPosition = p;
		kgaFile.levelHintDone = false;
		kgaFile.overall_score = 0;
	}

  FILE* file = _tfopen(fileName, TEXT("w"));
  fwrite(&kgaFile, 1, sizeof(KGAFILE), file);
  fclose(file);

  return true;

}


// ****************************************************************************************************************
// Gets the path of the executable
// ****************************************************************************************************************
DWORD CGame::GetModuleDirectory(HMODULE hModule, LPTSTR szPath, DWORD dwLength) {

	DWORD dwLen;
	LPTSTR p;
	if (0 == (dwLen = GetModuleFileName(hModule, szPath, dwLength))) {
		return(0);
	}
	p = szPath + dwLen;
	while (p != szPath) {
		if (TEXT('\\') == *--p) {
			*(++p) = 0;
			break;
		}
	}
	return(p - szPath);

}


// ****************************************************************************************************************
// This method is called any time a surface is created so that errors can be centrally handled
// ****************************************************************************************************************
void CGame::createSurface(TCHAR* location, HRESULT hResult) {
  if (hResult == GD_OK) { return; }
  TCHAR szOut[502] = TEXT("");
  _tcscat(szOut, location);
  _tcscat(szOut, TEXT("\n\nAn unrecoverable error has occurred.  This program will now terminate."));
  switch (hResult) {
    case GDERR_OUTOFMEMORY : {
      _tcscat(szOut, TEXT("It appears that there is not enough free memory to run this program.  Please free up 8MB of total memory (or better yet, 8MB of just Program memory) and run the program again."));
      MessageBox(NULL, szOut, TEXT("CS - Stop Code A"), MB_OK);
    break; }
    case GDERR_BITMAPNOTFOUND: {
      MessageBox(NULL, szOut, TEXT("CS - Stop Code B"), MB_OK);
    break; }
    case GDERR_INCOMPATIBLEPRIMARY: {
      MessageBox(NULL, szOut, TEXT("CS - Stop Code C"), MB_OK);
    break; }
    case GDERR_INVALIDBITMAP: {
      MessageBox(NULL, szOut, TEXT("CS - Stop Code D"), MB_OK);
    break; }
    case GDERR_INVALIDPARAMS: {
      MessageBox(NULL, szOut, TEXT("CS - Stop Code E"), MB_OK);
    break; }
    case GDERR_INVALIDSURFACETYPE: {
      MessageBox(NULL, szOut, TEXT("CS - Stop Code F"), MB_OK);
    break; }
    case GDERR_LOCKEDSURFACES: {
      MessageBox(NULL, szOut, TEXT("CS - Stop Code G"), MB_OK);
    break; }
    case GDERR_SURFACELOST : {
      MessageBox(NULL, szOut, TEXT("CS - Stop Code H"), MB_OK);
    break; }
		default: {
			MessageBox(NULL, szOut, TEXT("CS - UNKNOWN STOP CODE"), MB_OK);
		break; }
  }
  Shutdown();
}


// ****************************************************************************************************************
// This method is called any time a font is created so that errors can be centrally handled
// ****************************************************************************************************************
void CGame::createFont(TCHAR* location, HRESULT hResult) {
  if (hResult == GD_OK) { return; }
  TCHAR szOut[502] = TEXT("");
  _tcscat(szOut, location);
  _tcscat(szOut, TEXT("\n\nAn unrecoverable error has occurred.  This program will now terminate."));
  switch (hResult) {
    case GDERR_OUTOFMEMORY : {
      _tcscat(szOut, TEXT("It appears that there is not enough free memory to run this program.  Please free up 8MB of total memory (or better yet, 8MB of just Program memory) and run the program again."));
      MessageBox(NULL, szOut, TEXT("CF - Stop Code A"), MB_OK);
    break; }
    case GDERR_INVALIDBITMAP: {
      MessageBox(NULL, szOut, TEXT("CF - Stop Code B"), MB_OK);
    break; }
    case GDERR_SURFACELOST : {
      MessageBox(NULL, szOut, TEXT("CF - Stop Code C"), MB_OK);
    break; }
		default: {
			MessageBox(NULL, szOut, TEXT("CF - UNKNOWN STOP CODE"), MB_OK);
		break; }
  }
  Shutdown();
}



// ****************************************************************************************************************
// This method is called any time a hssSound is loaded
// ****************************************************************************************************************
void CGame::loadSFX(TCHAR* location, int iResult) {
  if (iResult == HSS_OK) {
    return;
  } else {
    TCHAR szOut[502] = TEXT("");
    _tcscat(szOut, location);
    _tcscat(szOut, TEXT("\n\nAn unrecoverable error has occurred.  This program will now terminate."));
    _tcscat(szOut, TEXT("It appears that there is not enough free memory to run this program.  Please free up 8MB of total memory (or better yet, 8MB of just Program memory) and run the program again."));
    MessageBox(NULL, szOut, TEXT("LX - Stop Code A"), MB_OK);
    Shutdown();
  }
}


// ****************************************************************************************************************
// Method to get free storage memory
// ****************************************************************************************************************
DWORD CGame::getStorageMemory() {
  unsigned __int64 i64FreeBytesToCaller, i64TotalBytes, i64FreeBytes; 
  GetDiskFreeSpaceEx(NULL,(PULARGE_INTEGER)&i64FreeBytesToCaller, (PULARGE_INTEGER)&i64TotalBytes, (PULARGE_INTEGER)&i64FreeBytes); 
  DWORD StorageFreeSp = (DWORD)i64FreeBytes / 1024; 
  return StorageFreeSp;
}


// ****************************************************************************************************************
// Method to get free program memory
// ****************************************************************************************************************
DWORD CGame::getProgramMemory() {
  MEMORYSTATUS Mem; 
  GlobalMemoryStatus(&Mem); 
  DWORD PhyFree = Mem.dwAvailPhys / 1024;
  return PhyFree;
}

