
// ================================================================================================
// Globals
// ================================================================================================
Surface*			 PlayerWins1SceneActors[18];
SoundFX 			 PlayerWins1SceneAudioActors[10];
int						 PlayerWins1SceneTextActors[3];
unsigned char* PlayerWins1SceneScript = NULL;
SoundFX				 sfxK_NII;
SoundFX				 sfxK_TNWYCDTAT;
SoundFX				 sfxG_YNWNWNWNW;
SoundFX				 sfxK_FWBOOWN;
SoundFX				 sfxG_UNTA;


// ================================================================================================
// Loader
// ================================================================================================
void loaderPlayerWins1Scene(DisplayDevice* display) {
	// Load audio actor sound fx for this scene
	sfxK_NII.load(_Module.GetModuleInstance(), IDR_SFX_K_NII);
	sfxK_TNWYCDTAT.load(_Module.GetModuleInstance(), IDR_SFX_K_TNWYCDTAT);
	sfxG_YNWNWNWNW.load(_Module.GetModuleInstance(), IDR_SFX_G_YNWNWNWNW);
	sfxK_FWBOOWN.load(_Module.GetModuleInstance(), IDR_SFX_K_FWBOOWN);
	sfxG_UNTA.load(_Module.GetModuleInstance(), IDR_SFX_G_UNTA);
	// Get a pointer to the script for this scene
	PlayerWins1SceneScript = (unsigned char*)OASIS_loadScriptResource(IDR_PLAYER_WINS_1_SCENE_SCRIPT, hInst);
	// Place all actor images in array of actors (order MUST match the script editor!)
	// Last element MUST be NULL
	PlayerWins1SceneActors[0]  = imgShipInterior;
	PlayerWins1SceneActors[1]  = imgKrelmacBody;
	PlayerWins1SceneActors[2]  = imgKrelmacHeadMouthClosed;
	PlayerWins1SceneActors[3]  = imgKrelmacHeadMouthOpened;
	PlayerWins1SceneActors[4]  = imgKrelmacHeadMouthOpenedWide;
	PlayerWins1SceneActors[5]  = imgKrelmacEyebrows;
	PlayerWins1SceneActors[6]  = imgGentooBody;
	PlayerWins1SceneActors[7]  = imgGentooBodyWhackoff;
	PlayerWins1SceneActors[8]  = imgGentooHeadMouthClosed;
	PlayerWins1SceneActors[9]  = imgGentooHeadMouthOpened;
	PlayerWins1SceneActors[10] = imgGentooHeadMouthOpenedWide;
	PlayerWins1SceneActors[11] = imgGentooHeadLookingDown;
	PlayerWins1SceneActors[12] = imgGentooHeadEmbarassed;
	PlayerWins1SceneActors[13] = imgGentooHeadEmbarassedBlushing;
	PlayerWins1SceneActors[14] = imgKGShip_Fullscreen;
	PlayerWins1SceneActors[15] = NULL;
	// Place all audio actor sound fx in array of audio actors (order MUST match the script editor!)
	// No need to terminate array with NULL or -1
	PlayerWins1SceneAudioActors[0] = sfxK_NII;
	PlayerWins1SceneAudioActors[1] = sfxG_ILHANIBWYI;
	PlayerWins1SceneAudioActors[2] = sfxK_TNWYCDTAT;
	PlayerWins1SceneAudioActors[3] = sfxG_YNWNWNWNW;
	PlayerWins1SceneAudioActors[4] = sfxK_GTGTP;
	PlayerWins1SceneAudioActors[5] = sfxG_S;
	PlayerWins1SceneAudioActors[6] = sfxK_FWBOOWN;
	PlayerWins1SceneAudioActors[7] = sfxG_UNTA;
	// Place all text actor resource ID's in array of text actors (order MUST match the script editor!)
	// Last element MUST be -1
	PlayerWins1SceneTextActors[0] = -1;
}


// ================================================================================================
// Releaser
// ================================================================================================
void releaserPlayerWins1Scene() {
}


// ================================================================================================
// Scene Starter
// ================================================================================================
void SceneStarter_PlayerWins1Scene() {
	OASIS_StartScene(PlayerWins1SceneScript, PlayerWins1SceneActors, PlayerWins1SceneAudioActors, PlayerWins1SceneTextActors);
}


// ================================================================================================
// Scene Ender
// ================================================================================================
void SceneEnder_PlayerWins1Scene() {
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
void stylusDownPlayerWins1Scene(Point stylusPoint) {
}

void stylusMovePlayerWins1Scene(Point stylusPoint) {
}

void stylusUpPlayerWins1Scene(Point stylusPoint) {
	SceneEnder_PlayerWins1Scene();
}

void keyDownPlayerWins1Scene(int key) {
}

void keyUpPlayerWins1Scene(int key) {
}
