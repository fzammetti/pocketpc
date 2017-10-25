
// ================================================================================================
// Globals
// ================================================================================================
Surface*			 PlayerWins4SceneActors[18];
SoundFX 			 PlayerWins4SceneAudioActors[6];
int						 PlayerWins4SceneTextActors[3];
unsigned char* PlayerWins4SceneScript = NULL;
SoundFX				 sfxG_TCTMHNHCHW;
SoundFX				 sfxK_WSTGAFCATGO;
SoundFX				 sfxG_TSKSWTICSWT;
SoundFX				 sfxK_IIDGRATTWWNT;


// ================================================================================================
// Loader
// ================================================================================================
void loaderPlayerWins4Scene(DisplayDevice* display) {
	// Load audio actor sound fx for this scene
	sfxG_TCTMHNHCHW.load(_Module.GetModuleInstance(), IDR_SFX_G_TCTMHNHCHW);
	sfxK_WSTGAFCATGO.load(_Module.GetModuleInstance(), IDR_SFX_K_WSTGAFCATGO);
	sfxG_TSKSWTICSWT.load(_Module.GetModuleInstance(), IDR_SFX_G_TSKSWTICSWT);
	sfxK_IIDGRATTWWNT.load(_Module.GetModuleInstance(), IDR_SFX_K_IIDGRATTWWNT);
	// Get a pointer to the script for this scene
	PlayerWins4SceneScript = (unsigned char*)OASIS_loadScriptResource(IDR_PLAYER_WINS_4_SCENE_SCRIPT, hInst);
	// Place all actor images in array of actors (order MUST match the script editor!)
	// Last element MUST be NULL
	PlayerWins4SceneActors[0]  = imgShipInterior;
	PlayerWins4SceneActors[1]  = imgKrelmacBody;
	PlayerWins4SceneActors[2]  = imgKrelmacHeadMouthClosed;
	PlayerWins4SceneActors[3]  = imgKrelmacHeadMouthOpened;
	PlayerWins4SceneActors[4]  = imgKrelmacHeadMouthOpenedWide;
	PlayerWins4SceneActors[5]  = imgKrelmacEyebrows;
	PlayerWins4SceneActors[6]  = imgGentooBody;
	PlayerWins4SceneActors[7]  = imgGentooBodyWhackoff;
	PlayerWins4SceneActors[8]  = imgGentooHeadMouthClosed;
	PlayerWins4SceneActors[9]  = imgGentooHeadMouthOpened;
	PlayerWins4SceneActors[10] = imgGentooHeadMouthOpenedWide;
	PlayerWins4SceneActors[11] = imgGentooHeadLookingDown;
	PlayerWins4SceneActors[12] = imgGentooHeadEmbarassed;
	PlayerWins4SceneActors[13] = imgGentooHeadEmbarassedBlushing;
	PlayerWins4SceneActors[14] = imgKGShip_Fullscreen;
	PlayerWins4SceneActors[15] = NULL;
	// Place all audio actor sound fx in array of audio actors (order MUST match the script editor!)
	// No need to terminate array with NULL or -1
	PlayerWins4SceneAudioActors[0] = sfxG_TCTMHNHCHW;
	PlayerWins4SceneAudioActors[1] = sfxK_WSTGAFCATGO;
	PlayerWins4SceneAudioActors[2] = sfxG_TSKSWTICSWT;
	PlayerWins4SceneAudioActors[3] = sfxK_IIDGRATTWWNT;
	// Place all text actor resource ID's in array of text actors (order MUST match the script editor!)
	// Last element MUST be -1
	PlayerWins4SceneTextActors[0] = -1;
}


// ================================================================================================
// Releaser
// ================================================================================================
void releaserPlayerWins4Scene() {
}


// ================================================================================================
// Scene Starter
// ================================================================================================
void SceneStarter_PlayerWins4Scene() {
	OASIS_StartScene(PlayerWins4SceneScript, PlayerWins4SceneActors, PlayerWins4SceneAudioActors, PlayerWins4SceneTextActors);
}


// ================================================================================================
// Scene Ender
// ================================================================================================
void SceneEnder_PlayerWins4Scene() {
	OASIS_EndScene();
	if (game.SeeIfPlayerGotHighScore()) {
		game.currentPointLevel--; // Do this so that the correct point level is saved in high scores
		game.currentScreen = csCongratulationsScreen;
	} else {
		game.currentScreen = csMainMenuScreen;
	}
}


// ================================================================================================
// Event Handlers
// ================================================================================================
void stylusDownPlayerWins4Scene(Point stylusPoint) {
}

void stylusMovePlayerWins4Scene(Point stylusPoint) {
}

void stylusUpPlayerWins4Scene(Point stylusPoint) {
	SceneEnder_PlayerWins4Scene();
}

void keyDownPlayerWins4Scene(int key) {
}

void keyUpPlayerWins4Scene(int key) {
}
