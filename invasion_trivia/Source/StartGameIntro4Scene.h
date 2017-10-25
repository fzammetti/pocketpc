
// ================================================================================================
// Globals
// ================================================================================================
Surface*			 StartGameIntro4SceneActors[18];
SoundFX 			 StartGameIntro4SceneAudioActors[6];
int						 StartGameIntro4SceneTextActors[3];
unsigned char* StartGameIntro4SceneScript = NULL;
SoundFX				 sfxG_HKCIFTECYHHCIH;
SoundFX				 sfxK_YKTRGTHTGAQWF;
SoundFX				 sfxG_WWAWWFIWBS;
SoundFX				 sfxK_DWGTODLTBIWBL;


// ================================================================================================
// Loader
// ================================================================================================
void loaderStartGameIntro4Scene(DisplayDevice* display) {
	// Load audio actor sound fx for this scene
	sfxG_HKCIFTECYHHCIH.load(_Module.GetModuleInstance(), IDR_SFX_G_HKCIFTECYHHCIH);
	sfxK_YKTRGTHTGAQWF.load(_Module.GetModuleInstance(), IDR_SFX_K_YKTRGTHTGAQWF);
	sfxG_WWAWWFIWBS.load(_Module.GetModuleInstance(), IDR_SFX_G_WWAWWFIWBS);
	sfxK_DWGTODLTBIWBL.load(_Module.GetModuleInstance(), IDR_SFX_K_DWGTODLTBIWBL);
	// Get a pointer to the script for this scene
	StartGameIntro4SceneScript = (unsigned char*)OASIS_loadScriptResource(IDR_START_GAME_INTRO_4_SCENE_SCRIPT, hInst);
	// Place all actor images in array of actors (order MUST match the script editor!)
	// Last element MUST be NULL
	StartGameIntro4SceneActors[0]  = imgShipInterior;
	StartGameIntro4SceneActors[1]  = imgKrelmacBody;
	StartGameIntro4SceneActors[2]  = imgKrelmacHeadMouthClosed;
	StartGameIntro4SceneActors[3]  = imgKrelmacHeadMouthOpened;
	StartGameIntro4SceneActors[4]  = imgKrelmacHeadMouthOpenedWide;
	StartGameIntro4SceneActors[5]  = imgKrelmacEyebrows;
	StartGameIntro4SceneActors[6]  = imgGentooBody;
	StartGameIntro4SceneActors[7]  = imgGentooBodyWhackoff;
	StartGameIntro4SceneActors[8]  = imgGentooHeadMouthClosed;
	StartGameIntro4SceneActors[9]  = imgGentooHeadMouthOpened;
	StartGameIntro4SceneActors[10] = imgGentooHeadMouthOpenedWide;
	StartGameIntro4SceneActors[11] = imgGentooHeadLookingDown;
	StartGameIntro4SceneActors[12] = imgGentooHeadEmbarassed;
	StartGameIntro4SceneActors[13] = imgGentooHeadEmbarassedBlushing;
	StartGameIntro4SceneActors[14] = imgKGShip_Fullscreen;
	StartGameIntro4SceneActors[15] = NULL;
	// Place all audio actor sound fx in array of audio actors (order MUST match the script editor!)
	// No need to terminate array with NULL or -1
	StartGameIntro4SceneAudioActors[0] = sfxG_HKCIFTECYHHCIH;
	StartGameIntro4SceneAudioActors[1] = sfxK_YKTRGTHTGAQWF;
	StartGameIntro4SceneAudioActors[2] = sfxG_WWAWWFIWBS;
	StartGameIntro4SceneAudioActors[3] = sfxK_DWGTODLTBIWBL;
	// Place all text actor resource ID's in array of text actors (order MUST match the script editor!)
	// Last element MUST be -1
	StartGameIntro4SceneTextActors[0] = -1;
}


// ================================================================================================
// Releaser
// ================================================================================================
void releaserStartGameIntro4Scene() {
}


// ================================================================================================
// Scene Starter
// ================================================================================================
void SceneStarter_StartGameIntro4Scene() {
	OASIS_StartScene(StartGameIntro4SceneScript, StartGameIntro4SceneActors, StartGameIntro4SceneAudioActors, StartGameIntro4SceneTextActors);
}


// ================================================================================================
// Scene Ender
// ================================================================================================
void SceneEnder_StartGameIntro4Scene() {
	OASIS_EndScene();
	game.currentScreen = csCharacterSelectScreen;
}


// ================================================================================================
// Event Handlers
// ================================================================================================
void stylusDownStartGameIntro4Scene(Point stylusPoint) {
}

void stylusMoveStartGameIntro4Scene(Point stylusPoint) {
}

void stylusUpStartGameIntro4Scene(Point stylusPoint) {
	SceneEnder_StartGameIntro4Scene();
}

void keyDownStartGameIntro4Scene(int key) {
}

void keyUpStartGameIntro4Scene(int key) {
}
