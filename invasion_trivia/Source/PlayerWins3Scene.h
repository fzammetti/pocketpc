
// ================================================================================================
// Globals
// ================================================================================================
Surface*			 PlayerWins3SceneActors[18];
SoundFX 			 PlayerWins3SceneAudioActors[9];
int						 PlayerWins3SceneTextActors[3];
unsigned char* PlayerWins3SceneScript = NULL;
SoundFX				 sfxK_YWYWIDKHBYW;
SoundFX				 sfxK_TSSITYSSS;
SoundFX				 sfxG_NKIKLTP;


// ================================================================================================
// Loader
// ================================================================================================
void loaderPlayerWins3Scene(DisplayDevice* display) {
	// Load audio actor sound fx for this scene
	sfxK_YWYWIDKHBYW.load(_Module.GetModuleInstance(), IDR_SFX_K_YWYWIDKHBYW);
	sfxK_TSSITYSSS.load(_Module.GetModuleInstance(), IDR_SFX_K_TSSITYSSS);
	sfxG_NKIKLTP.load(_Module.GetModuleInstance(), IDR_SFX_G_NKIKLTP);
	// Get a pointer to the script for this scene
	PlayerWins3SceneScript = (unsigned char*)OASIS_loadScriptResource(IDR_PLAYER_WINS_3_SCENE_SCRIPT, hInst);
	// Place all actor images in array of actors (order MUST match the script editor!)
	// Last element MUST be NULL
	PlayerWins3SceneActors[0]  = imgShipInterior;
	PlayerWins3SceneActors[1]  = imgKrelmacBody;
	PlayerWins3SceneActors[2]  = imgKrelmacHeadMouthClosed;
	PlayerWins3SceneActors[3]  = imgKrelmacHeadMouthOpened;
	PlayerWins3SceneActors[4]  = imgKrelmacHeadMouthOpenedWide;
	PlayerWins3SceneActors[5]  = imgKrelmacEyebrows;
	PlayerWins3SceneActors[6]  = imgGentooBody;
	PlayerWins3SceneActors[7]  = imgGentooBodyWhackoff;
	PlayerWins3SceneActors[8]  = imgGentooHeadMouthClosed;
	PlayerWins3SceneActors[9]  = imgGentooHeadMouthOpened;
	PlayerWins3SceneActors[10] = imgGentooHeadMouthOpenedWide;
	PlayerWins3SceneActors[11] = imgGentooHeadLookingDown;
	PlayerWins3SceneActors[12] = imgGentooHeadEmbarassed;
	PlayerWins3SceneActors[13] = imgGentooHeadEmbarassedBlushing;
	PlayerWins3SceneActors[14] = imgKGShip_Fullscreen;
	PlayerWins3SceneActors[15] = NULL;
	// Place all audio actor sound fx in array of audio actors (order MUST match the script editor!)
	// No need to terminate array with NULL or -1
	PlayerWins3SceneAudioActors[0] = sfxK_YWYWIDKHBYW;
	PlayerWins3SceneAudioActors[1] = sfxK_TSSITYSSS;
	PlayerWins3SceneAudioActors[2] = sfxK_G;
	PlayerWins3SceneAudioActors[3] = sfxG_S;
	PlayerWins3SceneAudioActors[4] = sfxK_IGITFUTLG;
	PlayerWins3SceneAudioActors[5] = sfxG_NKIKLTP;
	PlayerWins3SceneAudioActors[6] = sfxK_IKGIKIASDFUHIB;
	// Place all text actor resource ID's in array of text actors (order MUST match the script editor!)
	// Last element MUST be -1
	PlayerWins3SceneTextActors[0] = -1;
}


// ================================================================================================
// Releaser
// ================================================================================================
void releaserPlayerWins3Scene() {
}


// ================================================================================================
// Scene Starter
// ================================================================================================
void SceneStarter_PlayerWins3Scene() {
	OASIS_StartScene(PlayerWins3SceneScript, PlayerWins3SceneActors, PlayerWins3SceneAudioActors, PlayerWins3SceneTextActors);
}


// ================================================================================================
// Scene Ender
// ================================================================================================
void SceneEnder_PlayerWins3Scene() {
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
void stylusDownPlayerWins3Scene(Point stylusPoint) {
}

void stylusMovePlayerWins3Scene(Point stylusPoint) {
}

void stylusUpPlayerWins3Scene(Point stylusPoint) {
	SceneEnder_PlayerWins3Scene();
}

void keyDownPlayerWins3Scene(int key) {
}

void keyUpPlayerWins3Scene(int key) {
}
