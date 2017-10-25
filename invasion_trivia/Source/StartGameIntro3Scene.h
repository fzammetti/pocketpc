
// ================================================================================================
// Globals
// ================================================================================================
Surface*			 StartGameIntro3SceneActors[18];
SoundFX 			 StartGameIntro3SceneAudioActors[6];
int						 StartGameIntro3SceneTextActors[3];
unsigned char* StartGameIntro3SceneScript = NULL;
SoundFX				 sfxK_WNYCHRYPBST;
SoundFX				 sfxG_YYLITHUYWTSAMOTA;
SoundFX				 sfxK_GTGTP;


// ================================================================================================
// Loader
// ================================================================================================
void loaderStartGameIntro3Scene(DisplayDevice* display) {
	// Load audio actor sound fx for this scene
	sfxK_WNYCHRYPBST.load(_Module.GetModuleInstance(), IDR_SFX_K_WNYCHRYPBST);
	sfxG_YYLITHUYWTSAMOTA.load(_Module.GetModuleInstance(), IDR_SFX_G_YYLITHUYWTSAMOTA);
	sfxK_GTGTP.load(_Module.GetModuleInstance(), IDR_SFX_K_GTGTP);
	sfxG_S.load(_Module.GetModuleInstance(), IDR_SFX_G_S);
	// Get a pointer to the script for this scene
	StartGameIntro3SceneScript = (unsigned char*)OASIS_loadScriptResource(IDR_START_GAME_INTRO_3_SCENE_SCRIPT, hInst);
	// Place all actor images in array of actors (order MUST match the script editor!)
	// Last element MUST be NULL
	StartGameIntro3SceneActors[0]  = imgShipInterior;
	StartGameIntro3SceneActors[1]  = imgKrelmacBody;
	StartGameIntro3SceneActors[2]  = imgKrelmacHeadMouthClosed;
	StartGameIntro3SceneActors[3]  = imgKrelmacHeadMouthOpened;
	StartGameIntro3SceneActors[4]  = imgKrelmacHeadMouthOpenedWide;
	StartGameIntro3SceneActors[5]  = imgKrelmacEyebrows;
	StartGameIntro3SceneActors[6]  = imgGentooBody;
	StartGameIntro3SceneActors[7]  = imgGentooBodyWhackoff;
	StartGameIntro3SceneActors[8]  = imgGentooHeadMouthClosed;
	StartGameIntro3SceneActors[9]  = imgGentooHeadMouthOpened;
	StartGameIntro3SceneActors[10] = imgGentooHeadMouthOpenedWide;
	StartGameIntro3SceneActors[11] = imgGentooHeadLookingDown;
	StartGameIntro3SceneActors[12] = imgGentooHeadEmbarassed;
	StartGameIntro3SceneActors[13] = imgGentooHeadEmbarassedBlushing;
	StartGameIntro3SceneActors[14] = imgKGShip_Fullscreen;
	StartGameIntro3SceneActors[15] = NULL;
	// Place all audio actor sound fx in array of audio actors (order MUST match the script editor!)
	// No need to terminate array with NULL or -1
	StartGameIntro3SceneAudioActors[0] = sfxK_WNYCHRYPBST;
	StartGameIntro3SceneAudioActors[1] = sfxG_YYLITHUYWTSAMOTA;
	StartGameIntro3SceneAudioActors[2] = sfxK_GTGTP;
	StartGameIntro3SceneAudioActors[3] = sfxG_S;
	// Place all text actor resource ID's in array of text actors (order MUST match the script editor!)
	// Last element MUST be -1
	StartGameIntro3SceneTextActors[0] = -1;
}


// ================================================================================================
// Releaser
// ================================================================================================
void releaserStartGameIntro3Scene() {
}


// ================================================================================================
// Scene Starter
// ================================================================================================
void SceneStarter_StartGameIntro3Scene() {
	OASIS_StartScene(StartGameIntro3SceneScript, StartGameIntro3SceneActors, StartGameIntro3SceneAudioActors, StartGameIntro3SceneTextActors);
}


// ================================================================================================
// Scene Ender
// ================================================================================================
void SceneEnder_StartGameIntro3Scene() {
	OASIS_EndScene();
	game.currentScreen = csCharacterSelectScreen;
}


// ================================================================================================
// Event Handlers
// ================================================================================================
void stylusDownStartGameIntro3Scene(Point stylusPoint) {
}

void stylusMoveStartGameIntro3Scene(Point stylusPoint) {
}

void stylusUpStartGameIntro3Scene(Point stylusPoint) {
	SceneEnder_StartGameIntro3Scene();
}

void keyDownStartGameIntro3Scene(int key) {
}

void keyUpStartGameIntro3Scene(int key) {
}
