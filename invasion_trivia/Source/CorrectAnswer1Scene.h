
// ================================================================================================
// Globals
// ================================================================================================
Surface*			 CorrectAnswer1SceneActors[17];
SoundFX 			 CorrectAnswer1SceneAudioActors[4];
int						 CorrectAnswer1SceneTextActors[3];
unsigned char* CorrectAnswer1SceneScript = NULL;
SoundFX				 sfxK_WWYAGOR;
SoundFX				 sfxG_ILHANIBWYI;


// ================================================================================================
// Loader
// ================================================================================================
void loaderCorrectAnswer1Scene(DisplayDevice* display) {
	// Load audio actor sound fx for this scene
	sfxK_WWYAGOR.load(_Module.GetModuleInstance(), IDR_SFX_K_WWYAGOR);
	sfxG_ILHANIBWYI.load(_Module.GetModuleInstance(), IDR_SFX_G_ILHANIBWYI);
	// Get a pointer to the script for this scene
	CorrectAnswer1SceneScript = (unsigned char*)OASIS_loadScriptResource(IDR_CORRECT_ANSWER_1_SCENE_SCRIPT, hInst);
	// Place all actor images in array of actors (order MUST match the script editor!)
	// Last element MUST be NULL
	CorrectAnswer1SceneActors[0]  = imgShipInterior;
	CorrectAnswer1SceneActors[1]  = imgKrelmacBody;
	CorrectAnswer1SceneActors[2]  = imgKrelmacHeadMouthClosed;
	CorrectAnswer1SceneActors[3]  = imgKrelmacHeadMouthOpened;
	CorrectAnswer1SceneActors[4]  = imgKrelmacHeadMouthOpenedWide;
	CorrectAnswer1SceneActors[5]  = imgKrelmacEyebrows;
	CorrectAnswer1SceneActors[6]  = imgGentooBody;
	CorrectAnswer1SceneActors[7]  = imgGentooBodyWhackoff;
	CorrectAnswer1SceneActors[8]  = imgGentooHeadMouthClosed;
	CorrectAnswer1SceneActors[9]  = imgGentooHeadMouthOpened;
	CorrectAnswer1SceneActors[10] = imgGentooHeadMouthOpenedWide;
	CorrectAnswer1SceneActors[11] = imgGentooHeadLookingDown;
	CorrectAnswer1SceneActors[12] = imgGentooHeadEmbarassed;
	CorrectAnswer1SceneActors[13] = imgGentooHeadEmbarassedBlushing;
	CorrectAnswer1SceneActors[14] = NULL;
	// Place all audio actor sound fx in array of audio actors (order MUST match the script editor!)
	// No need to terminate array with NULL or -1
	CorrectAnswer1SceneAudioActors[0] = sfxK_WWYAGOR;
	CorrectAnswer1SceneAudioActors[1] = sfxG_ILHANIBWYI;
	// Place all text actor resource ID's in array of text actors (order MUST match the script editor!)
	// Last element MUST be -1
	CorrectAnswer1SceneTextActors[0] = -1;
}


// ================================================================================================
// Releaser
// ================================================================================================
void releaserCorrectAnswer1Scene() {
}


// ================================================================================================
// Scene Starter
// ================================================================================================
void SceneStarter_CorrectAnswer1Scene() {
	OASIS_StartScene(CorrectAnswer1SceneScript, CorrectAnswer1SceneActors, CorrectAnswer1SceneAudioActors, CorrectAnswer1SceneTextActors);
}


// ================================================================================================
// Scene Ender
// ================================================================================================
void SceneEnder_CorrectAnswer1Scene() {
	OASIS_EndScene();
	game.currentScreen = csPointLevelsScreen;
}


// ================================================================================================
// Event Handlers
// ================================================================================================
void stylusDownCorrectAnswer1Scene(Point stylusPoint) {
}

void stylusMoveCorrectAnswer1Scene(Point stylusPoint) {
}

void stylusUpCorrectAnswer1Scene(Point stylusPoint) {
	SceneEnder_CorrectAnswer1Scene();
}

void keyDownCorrectAnswer1Scene(int key) {
}

void keyUpCorrectAnswer1Scene(int key) {
}
