
// ================================================================================================
// Globals
// ================================================================================================
Surface*			 PlayerWins2SceneActors[18];
SoundFX 			 PlayerWins2SceneAudioActors[8];
int						 PlayerWins2SceneTextActors[3];
unsigned char* PlayerWins2SceneScript = NULL;
SoundFX				 sfxG_WNTCHWNWK;
SoundFX				 sfxK_ISHISS;
SoundFX				 sfxG_SSK;
SoundFX				 sfxK_IGITFUTLG;
SoundFX				 sfxG_BIDWGIWBSUK;


// ================================================================================================
// Loader
// ================================================================================================
void loaderPlayerWins2Scene(DisplayDevice* display) {
	// Load audio actor sound fx for this scene
	sfxG_WNTCHWNWK.load(_Module.GetModuleInstance(), IDR_SFX_G_WNTCHWNWK);
	sfxK_ISHISS.load(_Module.GetModuleInstance(), IDR_SFX_K_ISHISS);
	sfxG_SSK.load(_Module.GetModuleInstance(), IDR_SFX_G_SSK);
	sfxK_IGITFUTLG.load(_Module.GetModuleInstance(), IDR_SFX_K_IGITFUTLG);
	sfxG_BIDWGIWBSUK.load(_Module.GetModuleInstance(), IDR_SFX_G_BIDWGIWBSUK);
	// Get a pointer to the script for this scene
	PlayerWins2SceneScript = (unsigned char*)OASIS_loadScriptResource(IDR_PLAYER_WINS_2_SCENE_SCRIPT, hInst);
	// Place all actor images in array of actors (order MUST match the script editor!)
	// Last element MUST be NULL
	PlayerWins2SceneActors[0]  = imgShipInterior;
	PlayerWins2SceneActors[1]  = imgKrelmacBody;
	PlayerWins2SceneActors[2]  = imgKrelmacHeadMouthClosed;
	PlayerWins2SceneActors[3]  = imgKrelmacHeadMouthOpened;
	PlayerWins2SceneActors[4]  = imgKrelmacHeadMouthOpenedWide;
	PlayerWins2SceneActors[5]  = imgKrelmacEyebrows;
	PlayerWins2SceneActors[6]  = imgGentooBody;
	PlayerWins2SceneActors[7]  = imgGentooBodyWhackoff;
	PlayerWins2SceneActors[8]  = imgGentooHeadMouthClosed;
	PlayerWins2SceneActors[9]  = imgGentooHeadMouthOpened;
	PlayerWins2SceneActors[10] = imgGentooHeadMouthOpenedWide;
	PlayerWins2SceneActors[11] = imgGentooHeadLookingDown;
	PlayerWins2SceneActors[12] = imgGentooHeadEmbarassed;
	PlayerWins2SceneActors[13] = imgGentooHeadEmbarassedBlushing;
	PlayerWins2SceneActors[14] = imgKGShip_Fullscreen;
	PlayerWins2SceneActors[15] = NULL;
	// Place all audio actor sound fx in array of audio actors (order MUST match the script editor!)
	// No need to terminate array with NULL or -1
	PlayerWins2SceneAudioActors[0] = sfxG_WNTCHWNWK;
	PlayerWins2SceneAudioActors[1] = sfxK_ISHISS;
	PlayerWins2SceneAudioActors[2] = sfxG_SSK;
	PlayerWins2SceneAudioActors[3] = sfxK_IGITFUTLG;
	PlayerWins2SceneAudioActors[4] = sfxG_BIDWGIWBSUK;
	PlayerWins2SceneAudioActors[5] = sfxK_IKGIKIASDFUHIB;
	// Place all text actor resource ID's in array of text actors (order MUST match the script editor!)
	// Last element MUST be -1
	PlayerWins2SceneTextActors[0] = -1;
}


// ================================================================================================
// Releaser
// ================================================================================================
void releaserPlayerWins2Scene() {
}


// ================================================================================================
// Scene Starter
// ================================================================================================
void SceneStarter_PlayerWins2Scene() {
	OASIS_StartScene(PlayerWins2SceneScript, PlayerWins2SceneActors, PlayerWins2SceneAudioActors, PlayerWins2SceneTextActors);
}


// ================================================================================================
// Scene Ender
// ================================================================================================
void SceneEnder_PlayerWins2Scene() {
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
void stylusDownPlayerWins2Scene(Point stylusPoint) {
}

void stylusMovePlayerWins2Scene(Point stylusPoint) {
}

void stylusUpPlayerWins2Scene(Point stylusPoint) {
	SceneEnder_PlayerWins2Scene();
}

void keyDownPlayerWins2Scene(int key) {
}

void keyUpPlayerWins2Scene(int key) {
}
