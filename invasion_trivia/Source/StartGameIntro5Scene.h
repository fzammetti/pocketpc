
// ================================================================================================
// Globals
// ================================================================================================
Surface*			 StartGameIntro5SceneActors[18];
SoundFX 			 StartGameIntro5SceneAudioActors[8];
int						 StartGameIntro5SceneTextActors[3];
unsigned char* StartGameIntro5SceneScript = NULL;
SoundFX				 sfxK_PHYDIIMT;
SoundFX				 sfxG_NWKTDIIMB;
SoundFX				 sfxK_YDHABG;
SoundFX				 sfxG_TWTASCF;
SoundFX				 sfxK_IMBTH;
SoundFX				 sfxG_EEWW;


// ================================================================================================
// Loader
// ================================================================================================
void loaderStartGameIntro5Scene(DisplayDevice* display) {
	// Load audio actor sound fx for this scene
	sfxK_PHYDIIMT.load(_Module.GetModuleInstance(), IDR_SFX_K_PHYDIIMT);
	sfxG_NWKTDIIMB.load(_Module.GetModuleInstance(), IDR_SFX_G_NWKTDIIMB);
	sfxK_YDHABG.load(_Module.GetModuleInstance(), IDR_SFX_K_YDHABG);
	sfxG_TWTASCF.load(_Module.GetModuleInstance(), IDR_SFX_G_TWTASCF);
	sfxK_IMBTH.load(_Module.GetModuleInstance(), IDR_SFX_K_IMBTH);
	sfxG_EEWW.load(_Module.GetModuleInstance(), IDR_SFX_G_EEWW);
	// Get a pointer to the script for this scene
	StartGameIntro5SceneScript = (unsigned char*)OASIS_loadScriptResource(IDR_START_GAME_INTRO_5_SCENE_SCRIPT, hInst);
	// Place all actor images in array of actors (order MUST match the script editor!)
	// Last element MUST be NULL
	StartGameIntro5SceneActors[0]  = imgShipInterior;
	StartGameIntro5SceneActors[1]  = imgKrelmacBody;
	StartGameIntro5SceneActors[2]  = imgKrelmacHeadMouthClosed;
	StartGameIntro5SceneActors[3]  = imgKrelmacHeadMouthOpened;
	StartGameIntro5SceneActors[4]  = imgKrelmacHeadMouthOpenedWide;
	StartGameIntro5SceneActors[5]  = imgKrelmacEyebrows;
	StartGameIntro5SceneActors[6]  = imgGentooBody;
	StartGameIntro5SceneActors[7]  = imgGentooBodyWhackoff;
	StartGameIntro5SceneActors[8]  = imgGentooHeadMouthClosed;
	StartGameIntro5SceneActors[9]  = imgGentooHeadMouthOpened;
	StartGameIntro5SceneActors[10] = imgGentooHeadMouthOpenedWide;
	StartGameIntro5SceneActors[11] = imgGentooHeadLookingDown;
	StartGameIntro5SceneActors[12] = imgGentooHeadEmbarassed;
	StartGameIntro5SceneActors[13] = imgGentooHeadEmbarassedBlushing;
	StartGameIntro5SceneActors[14] = imgKGShip_Fullscreen;
	StartGameIntro5SceneActors[15] = NULL;
	// Place all audio actor sound fx in array of audio actors (order MUST match the script editor!)
	// No need to terminate array with NULL or -1
	StartGameIntro5SceneAudioActors[0] = sfxK_PHYDIIMT;
	StartGameIntro5SceneAudioActors[1] = sfxG_NWKTDIIMB;
	StartGameIntro5SceneAudioActors[2] = sfxK_YDHABG;
	StartGameIntro5SceneAudioActors[3] = sfxG_TWTASCF;
	StartGameIntro5SceneAudioActors[4] = sfxK_IMBTH;
	StartGameIntro5SceneAudioActors[5] = sfxG_EEWW;
	// Place all text actor resource ID's in array of text actors (order MUST match the script editor!)
	// Last element MUST be -1
	StartGameIntro5SceneTextActors[0] = -1;
}


// ================================================================================================
// Releaser
// ================================================================================================
void releaserStartGameIntro5Scene() {
}


// ================================================================================================
// Scene Starter
// ================================================================================================
void SceneStarter_StartGameIntro5Scene() {
	OASIS_StartScene(StartGameIntro5SceneScript, StartGameIntro5SceneActors, StartGameIntro5SceneAudioActors, StartGameIntro5SceneTextActors);
}


// ================================================================================================
// Scene Ender
// ================================================================================================
void SceneEnder_StartGameIntro5Scene() {
	OASIS_EndScene();
	game.currentScreen = csCharacterSelectScreen;
}


// ================================================================================================
// Event Handlers
// ================================================================================================
void stylusDownStartGameIntro5Scene(Point stylusPoint) {
}

void stylusMoveStartGameIntro5Scene(Point stylusPoint) {
}

void stylusUpStartGameIntro5Scene(Point stylusPoint) {
	SceneEnder_StartGameIntro5Scene();
}

void keyDownStartGameIntro5Scene(int key) {
}

void keyUpStartGameIntro5Scene(int key) {
}
