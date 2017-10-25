
// ================================================================================================
// Globals
// ================================================================================================
Surface*			 PlayerWins5SceneActors[18];
SoundFX 			 PlayerWins5SceneAudioActors[9];
int						 PlayerWins5SceneTextActors[3];
unsigned char* PlayerWins5SceneScript = NULL;
SoundFX				 sfxK_YHDU;
SoundFX				 sfxG_IMK;
SoundFX				 sfxK_FWLBWBBSD;
SoundFX				 sfxG_TPWCABA;
SoundFX				 sfxK_UTHEYEIWLF;


// ================================================================================================
// Loader
// ================================================================================================
void loaderPlayerWins5Scene(DisplayDevice* display) {
	// Load audio actor sound fx for this scene
	sfxK_YHDU.load(_Module.GetModuleInstance(), IDR_SFX_K_YHDU);
	sfxG_IMK.load(_Module.GetModuleInstance(), IDR_SFX_G_IMK);
	sfxK_FWLBWBBSD.load(_Module.GetModuleInstance(), IDR_SFX_K_FWLBWBBSD);
	sfxG_TPWCABA.load(_Module.GetModuleInstance(), IDR_SFX_G_TPWCABA);
	sfxK_UTHEYEIWLF.load(_Module.GetModuleInstance(), IDR_SFX_K_UTHEYEIWLF);
	// Get a pointer to the script for this scene
	PlayerWins5SceneScript = (unsigned char*)OASIS_loadScriptResource(IDR_PLAYER_WINS_5_SCENE_SCRIPT, hInst);
	// Place all actor images in array of actors (order MUST match the script editor!)
	// Last element MUST be NULL
	PlayerWins5SceneActors[0]  = imgShipInterior;
	PlayerWins5SceneActors[1]  = imgKrelmacBody;
	PlayerWins5SceneActors[2]  = imgKrelmacHeadMouthClosed;
	PlayerWins5SceneActors[3]  = imgKrelmacHeadMouthOpened;
	PlayerWins5SceneActors[4]  = imgKrelmacHeadMouthOpenedWide;
	PlayerWins5SceneActors[5]  = imgKrelmacEyebrows;
	PlayerWins5SceneActors[6]  = imgGentooBody;
	PlayerWins5SceneActors[7]  = imgGentooBodyWhackoff;
	PlayerWins5SceneActors[8]  = imgGentooHeadMouthClosed;
	PlayerWins5SceneActors[9]  = imgGentooHeadMouthOpened;
	PlayerWins5SceneActors[10] = imgGentooHeadMouthOpenedWide;
	PlayerWins5SceneActors[11] = imgGentooHeadLookingDown;
	PlayerWins5SceneActors[12] = imgGentooHeadEmbarassed;
	PlayerWins5SceneActors[13] = imgGentooHeadEmbarassedBlushing;
	PlayerWins5SceneActors[14] = imgKGShip_Fullscreen;
	PlayerWins5SceneActors[15] = NULL;
	// Place all audio actor sound fx in array of audio actors (order MUST match the script editor!)
	// No need to terminate array with NULL or -1
	PlayerWins5SceneAudioActors[0] = sfxK_YHDU;
	PlayerWins5SceneAudioActors[1] = sfxG_IMK;
	PlayerWins5SceneAudioActors[2] = sfxK_G;
	PlayerWins5SceneAudioActors[3] = sfxG_S;
	PlayerWins5SceneAudioActors[4] = sfxK_FWLBWBBSD;
	PlayerWins5SceneAudioActors[5] = sfxG_TPWCABA;
	PlayerWins5SceneAudioActors[6] = sfxK_UTHEYEIWLF;
	// Place all text actor resource ID's in array of text actors (order MUST match the script editor!)
	// Last element MUST be -1
	PlayerWins5SceneTextActors[0] = -1;
}


// ================================================================================================
// Releaser
// ================================================================================================
void releaserPlayerWins5Scene() {
}


// ================================================================================================
// Scene Starter
// ================================================================================================
void SceneStarter_PlayerWins5Scene() {
	OASIS_StartScene(PlayerWins5SceneScript, PlayerWins5SceneActors, PlayerWins5SceneAudioActors, PlayerWins5SceneTextActors);
}


// ================================================================================================
// Scene Ender
// ================================================================================================
void SceneEnder_PlayerWins5Scene() {
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
void stylusDownPlayerWins5Scene(Point stylusPoint) {
}

void stylusMovePlayerWins5Scene(Point stylusPoint) {
}

void stylusUpPlayerWins5Scene(Point stylusPoint) {
	SceneEnder_PlayerWins5Scene();
}

void keyDownPlayerWins5Scene(int key) {
}

void keyUpPlayerWins5Scene(int key) {
}
