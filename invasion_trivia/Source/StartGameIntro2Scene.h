
// ================================================================================================
// Globals
// ================================================================================================
Surface*			 StartGameIntro2SceneActors[18];
SoundFX 			 StartGameIntro2SceneAudioActors[7];
int						 StartGameIntro2SceneTextActors[3];
unsigned char* StartGameIntro2SceneScript = NULL;
SoundFX				 sfxG_WTAEOSYWPH;
SoundFX				 sfxK_GTWML;
SoundFX				 sfxG_BIWTSI;
SoundFX				 sfxK_G;
SoundFX				 sfxG_S;


// ================================================================================================
// Loader
// ================================================================================================
void loaderStartGameIntro2Scene(DisplayDevice* display) {
	// Load audio actor sound fx for this scene
	sfxG_WTAEOSYWPH.load(_Module.GetModuleInstance(), IDR_SFX_G_WTAEOSYWPH);
	sfxK_GTWML.load(_Module.GetModuleInstance(), IDR_SFX_K_GTWML);
	sfxG_BIWTSI.load(_Module.GetModuleInstance(), IDR_SFX_G_BIWTSI);
	sfxK_G.load(_Module.GetModuleInstance(), IDR_SFX_K_G);
	sfxG_S.load(_Module.GetModuleInstance(), IDR_SFX_G_S);
	// Get a pointer to the script for this scene
	StartGameIntro2SceneScript = (unsigned char*)OASIS_loadScriptResource(IDR_START_GAME_INTRO_2_SCENE_SCRIPT, hInst);
	// Place all actor images in array of actors (order MUST match the script editor!)
	// Last element MUST be NULL
	StartGameIntro2SceneActors[0]  = imgShipInterior;
	StartGameIntro2SceneActors[1]  = imgKrelmacBody;
	StartGameIntro2SceneActors[2]  = imgKrelmacHeadMouthClosed;
	StartGameIntro2SceneActors[3]  = imgKrelmacHeadMouthOpened;
	StartGameIntro2SceneActors[4]  = imgKrelmacHeadMouthOpenedWide;
	StartGameIntro2SceneActors[5]  = imgKrelmacEyebrows;
	StartGameIntro2SceneActors[6]  = imgGentooBody;
	StartGameIntro2SceneActors[7]  = imgGentooBodyWhackoff;
	StartGameIntro2SceneActors[8]  = imgGentooHeadMouthClosed;
	StartGameIntro2SceneActors[9]  = imgGentooHeadMouthOpened;
	StartGameIntro2SceneActors[10] = imgGentooHeadMouthOpenedWide;
	StartGameIntro2SceneActors[11] = imgGentooHeadLookingDown;
	StartGameIntro2SceneActors[12] = imgGentooHeadEmbarassed;
	StartGameIntro2SceneActors[13] = imgGentooHeadEmbarassedBlushing;
	StartGameIntro2SceneActors[14] = imgKGShip_Fullscreen;
	StartGameIntro2SceneActors[15] = NULL;
	// Place all audio actor sound fx in array of audio actors (order MUST match the script editor!)
	// No need to terminate array with NULL or -1
	StartGameIntro2SceneAudioActors[0] = sfxG_WTAEOSYWPH;
	StartGameIntro2SceneAudioActors[1] = sfxK_GTWML;
	StartGameIntro2SceneAudioActors[2] = sfxG_BIWTSI;
	StartGameIntro2SceneAudioActors[3] = sfxK_G;
	StartGameIntro2SceneAudioActors[4] = sfxG_S;
	// Place all text actor resource ID's in array of text actors (order MUST match the script editor!)
	// Last element MUST be -1
	StartGameIntro2SceneTextActors[0] = -1;
}


// ================================================================================================
// Releaser
// ================================================================================================
void releaserStartGameIntro2Scene() {
}


// ================================================================================================
// Scene Starter
// ================================================================================================
void SceneStarter_StartGameIntro2Scene() {
	OASIS_StartScene(StartGameIntro2SceneScript, StartGameIntro2SceneActors, StartGameIntro2SceneAudioActors, StartGameIntro2SceneTextActors);
}


// ================================================================================================
// Scene Ender
// ================================================================================================
void SceneEnder_StartGameIntro2Scene() {
	OASIS_EndScene();
	game.currentScreen = csCharacterSelectScreen;
}


// ================================================================================================
// Event Handlers
// ================================================================================================
void stylusDownStartGameIntro2Scene(Point stylusPoint) {
}

void stylusMoveStartGameIntro2Scene(Point stylusPoint) {
}

void stylusUpStartGameIntro2Scene(Point stylusPoint) {
	SceneEnder_StartGameIntro2Scene();
}

void keyDownStartGameIntro2Scene(int key) {
}

void keyUpStartGameIntro2Scene(int key) {
}
