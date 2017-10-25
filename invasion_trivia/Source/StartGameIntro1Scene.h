
// ================================================================================================
// Globals
// ================================================================================================
Surface*			 StartGameIntro1SceneActors[18];
SoundFX 			 StartGameIntro1SceneAudioActors[5];
int						 StartGameIntro1SceneTextActors[3];
unsigned char* StartGameIntro1SceneScript			 = NULL;
Surface*			 imgShipInterior								 = NULL;
Surface*			 imgKrelmacBody									 = NULL;
Surface*			 imgKrelmacHeadMouthClosed			 = NULL;
Surface*			 imgKrelmacHeadMouthOpened			 = NULL;
Surface*			 imgKrelmacHeadMouthOpenedWide	 = NULL;
Surface*			 imgKrelmacEyebrows							 = NULL;
Surface*			 imgGentooBody									 = NULL;
Surface*			 imgGentooBodyWhackoff					 = NULL;
Surface*			 imgGentooHeadMouthClosed				 = NULL;
Surface*			 imgGentooHeadMouthOpened				 = NULL;
Surface*			 imgGentooHeadMouthOpenedWide		 = NULL;
Surface*			 imgGentooHeadLookingDown				 = NULL;
Surface*			 imgGentooHeadEmbarassed				 = NULL;
Surface*			 imgGentooHeadEmbarassedBlushing = NULL;
Surface*			 imgKGShip_Fullscreen						 = NULL;
SoundFX				 sfxK_ATTGTSOTR;
SoundFX				 sfxG_IWUTECKTIGBF;
SoundFX				 sfxK_YILTSOBHFITN;


// ================================================================================================
// Loader
// ================================================================================================
void loaderStartGameIntro1Scene(DisplayDevice* display) {
	// Load audio actor sound fx for this scene
	sfxK_ATTGTSOTR.load(_Module.GetModuleInstance(), IDR_SFX_K_ATTGTSOTR);
	sfxG_IWUTECKTIGBF.load(_Module.GetModuleInstance(), IDR_SFX_G_IWUTECKTIGBF);
	sfxK_YILTSOBHFITN.load(_Module.GetModuleInstance(), IDR_SFX_K_YILTSOBHFITN);
	// Load actor images for this scene and set required transparency masks
	imgShipInterior = LoadImage(display, IDR_SHIP_INTERIOR);
	imgKrelmacBody = LoadImage(display, IDR_KRELMAC_BODY);
	imgKrelmacBody->SetColorMask(Color(255, 255, 255));
	imgKrelmacHeadMouthClosed = LoadImage(display, IDR_KRELMAC_HEAD_MOUTH_CLOSED);
	imgKrelmacHeadMouthClosed->SetColorMask(Color(255, 255, 255));
	imgKrelmacHeadMouthOpened = LoadImage(display, IDR_KRELMAC_HEAD_MOUTH_OPENED);
	imgKrelmacHeadMouthOpened->SetColorMask(Color(255, 255, 255));
	imgKrelmacHeadMouthOpenedWide = LoadImage(display, IDR_KRELMAC_HEAD_MOUTH_OPENED_WIDE);
	imgKrelmacHeadMouthOpenedWide->SetColorMask(Color(255, 255, 255));
	imgKrelmacEyebrows = LoadImage(display, IDR_KRELMAC_EYEBROWS);
	imgKrelmacEyebrows->SetColorMask(Color(255, 255, 255));
	imgGentooBody = LoadImage(display, IDR_GENTOO_BODY);
	imgGentooBody->SetColorMask(Color(255, 255, 255));
	imgGentooBodyWhackoff = LoadImage(display, IDR_GENTOO_BODY_WHACKOFF);
	imgGentooBodyWhackoff->SetColorMask(Color(255, 255, 255));
	imgGentooHeadMouthClosed = LoadImage(display, IDR_GENTOO_HEAD_MOUTH_CLOSED);
	imgGentooHeadMouthClosed->SetColorMask(Color(255, 255, 255));
	imgGentooHeadMouthOpened = LoadImage(display, IDR_GENTOO_HEAD_MOUTH_OPENED);
	imgGentooHeadMouthOpened->SetColorMask(Color(255, 255, 255));
	imgGentooHeadMouthOpenedWide = LoadImage(display, IDR_GENTOO_HEAD_MOUTH_OPENED_WIDE);
	imgGentooHeadMouthOpenedWide->SetColorMask(Color(255, 255, 255));
	imgGentooHeadLookingDown = LoadImage(display, IDR_GENTOO_HEAD_LOOKING_DOWN);
	imgGentooHeadLookingDown->SetColorMask(Color(255, 255, 255));
	imgGentooHeadEmbarassed = LoadImage(display, IDR_GENTOO_HEAD_EMBARASSED);
	imgGentooHeadEmbarassed->SetColorMask(Color(255, 255, 255));
	imgGentooHeadEmbarassedBlushing = LoadImage(display, IDR_GENTOO_HEAD_EMBARASSED_BLUSHING);
	imgGentooHeadEmbarassedBlushing->SetColorMask(Color(255, 255, 255));
	imgKGShip_Fullscreen = LoadImage(display, IDR_KGSHIP_FULLSCREEN);
	// Get a pointer to the script for this scene
	StartGameIntro1SceneScript = (unsigned char*)OASIS_loadScriptResource(IDR_START_GAME_INTRO_1_SCENE_SCRIPT, hInst);
	// Place all actor images in array of actors (order MUST match the script editor!)
	// Last element MUST be NULL
	StartGameIntro1SceneActors[0]  = imgShipInterior;
	StartGameIntro1SceneActors[1]  = imgKrelmacBody;
	StartGameIntro1SceneActors[2]  = imgKrelmacHeadMouthClosed;
	StartGameIntro1SceneActors[3]  = imgKrelmacHeadMouthOpened;
	StartGameIntro1SceneActors[4]  = imgKrelmacHeadMouthOpenedWide;
	StartGameIntro1SceneActors[5]  = imgKrelmacEyebrows;
	StartGameIntro1SceneActors[6]  = imgGentooBody;
	StartGameIntro1SceneActors[7]  = imgGentooBodyWhackoff;
	StartGameIntro1SceneActors[8]  = imgGentooHeadMouthClosed;
	StartGameIntro1SceneActors[9]  = imgGentooHeadMouthOpened;
	StartGameIntro1SceneActors[10] = imgGentooHeadMouthOpenedWide;
	StartGameIntro1SceneActors[11] = imgGentooHeadLookingDown;
	StartGameIntro1SceneActors[12] = imgGentooHeadEmbarassed;
	StartGameIntro1SceneActors[13] = imgGentooHeadEmbarassedBlushing;
	StartGameIntro1SceneActors[14] = imgKGShip_Fullscreen;
	StartGameIntro1SceneActors[15] = NULL;
	// Place all audio actor sound fx in array of audio actors (order MUST match the script editor!)
	// No need to terminate array with NULL or -1
	StartGameIntro1SceneAudioActors[0] = sfxK_ATTGTSOTR;
	StartGameIntro1SceneAudioActors[1] = sfxG_IWUTECKTIGBF;
	StartGameIntro1SceneAudioActors[2] = sfxK_YILTSOBHFITN;
	// Place all text actor resource ID's in array of text actors (order MUST match the script editor!)
	// Last element MUST be -1
	StartGameIntro1SceneTextActors[0] = -1;
}


// ================================================================================================
// Releaser
// ================================================================================================
void releaserStartGameIntro1Scene() {
	delete imgShipInterior;
	delete imgKrelmacBody;
	delete imgKrelmacHeadMouthClosed;
	delete imgKrelmacHeadMouthOpened;
	delete imgKrelmacHeadMouthOpenedWide;
	delete imgKrelmacEyebrows;
	delete imgGentooBody;
	delete imgGentooBodyWhackoff;
	delete imgGentooHeadMouthClosed;
	delete imgGentooHeadMouthOpened;
	delete imgGentooHeadMouthOpenedWide;
	delete imgGentooHeadLookingDown;
	delete imgGentooHeadEmbarassed;
	delete imgGentooHeadEmbarassedBlushing;
	delete imgKGShip_Fullscreen;
}


// ================================================================================================
// Scene Starter
// ================================================================================================
void SceneStarter_StartGameIntro1Scene() {
	OASIS_StartScene(StartGameIntro1SceneScript, StartGameIntro1SceneActors, StartGameIntro1SceneAudioActors, StartGameIntro1SceneTextActors);
}


// ================================================================================================
// Scene Ender
// ================================================================================================
void SceneEnder_StartGameIntro1Scene() {
	OASIS_EndScene();
	game.currentScreen = csCharacterSelectScreen;
}


// ================================================================================================
// Event Handlers
// ================================================================================================
void stylusDownStartGameIntro1Scene(Point stylusPoint) {
}

void stylusMoveStartGameIntro1Scene(Point stylusPoint) {
}

void stylusUpStartGameIntro1Scene(Point stylusPoint) {
	SceneEnder_StartGameIntro1Scene();
}

void keyDownStartGameIntro1Scene(int key) {
}

void keyUpStartGameIntro1Scene(int key) {
}
