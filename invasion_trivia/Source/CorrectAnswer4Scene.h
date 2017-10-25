
// ================================================================================================
// Globals
// ================================================================================================
Surface*			 CorrectAnswer4SceneActors[17];
SoundFX 			 CorrectAnswer4SceneAudioActors[5];
int						 CorrectAnswer4SceneTextActors[3];
unsigned char* CorrectAnswer4SceneScript = NULL;
SoundFX				 sfxK_HCYPKTYMHGH;
SoundFX				 sfxG_YYGGRBG;
SoundFX				 sfxK_LSYDTA;


// ================================================================================================
// Loader
// ================================================================================================
void loaderCorrectAnswer4Scene(DisplayDevice* display) {
	// Load audio actor sound fx for this scene
	sfxK_HCYPKTYMHGH.load(_Module.GetModuleInstance(), IDR_SFX_K_HCYPKTYMHGH);
	sfxG_YYGGRBG.load(_Module.GetModuleInstance(), IDR_SFX_G_YYGGRBG);
	sfxK_LSYDTA.load(_Module.GetModuleInstance(), IDR_SFX_K_LSYDTA);
	// Get a pointer to the script for this scene
	CorrectAnswer4SceneScript = (unsigned char*)OASIS_loadScriptResource(IDR_CORRECT_ANSWER_4_SCENE_SCRIPT, hInst);
	// Place all actor images in array of actors (order MUST match the script editor!)
	// Last element MUST be NULL
	CorrectAnswer4SceneActors[0]  = imgShipInterior;
	CorrectAnswer4SceneActors[1]  = imgKrelmacBody;
	CorrectAnswer4SceneActors[2]  = imgKrelmacHeadMouthClosed;
	CorrectAnswer4SceneActors[3]  = imgKrelmacHeadMouthOpened;
	CorrectAnswer4SceneActors[4]  = imgKrelmacHeadMouthOpenedWide;
	CorrectAnswer4SceneActors[5]  = imgKrelmacEyebrows;
	CorrectAnswer4SceneActors[6]  = imgGentooBody;
	CorrectAnswer4SceneActors[7]  = imgGentooBodyWhackoff;
	CorrectAnswer4SceneActors[8]  = imgGentooHeadMouthClosed;
	CorrectAnswer4SceneActors[9]  = imgGentooHeadMouthOpened;
	CorrectAnswer4SceneActors[10] = imgGentooHeadMouthOpenedWide;
	CorrectAnswer4SceneActors[11] = imgGentooHeadLookingDown;
	CorrectAnswer4SceneActors[12] = imgGentooHeadEmbarassed;
	CorrectAnswer4SceneActors[13] = imgGentooHeadEmbarassedBlushing;
	CorrectAnswer4SceneActors[14] = NULL;
	// Place all audio actor sound fx in array of audio actors (order MUST match the script editor!)
	// No need to terminate array with NULL or -1
	CorrectAnswer4SceneAudioActors[0] = sfxK_HCYPKTYMHGH;
	CorrectAnswer4SceneAudioActors[1] = sfxG_YYGGRBG;
	CorrectAnswer4SceneAudioActors[2] = sfxK_LSYDTA;
	// Place all text actor resource ID's in array of text actors (order MUST match the script editor!)
	// Last element MUST be -1
	CorrectAnswer4SceneTextActors[0] = -1;
}


// ================================================================================================
// Releaser
// ================================================================================================
void releaserCorrectAnswer4Scene() {
}


// ================================================================================================
// Scene Starter
// ================================================================================================
void SceneStarter_CorrectAnswer4Scene() {
	OASIS_StartScene(CorrectAnswer4SceneScript, CorrectAnswer4SceneActors, CorrectAnswer4SceneAudioActors, CorrectAnswer4SceneTextActors);
}


// ================================================================================================
// Scene Ender
// ================================================================================================
void SceneEnder_CorrectAnswer4Scene() {
	OASIS_EndScene();
	game.currentScreen = csPointLevelsScreen;
}


// ================================================================================================
// Event Handlers
// ================================================================================================
void stylusDownCorrectAnswer4Scene(Point stylusPoint) {
}

void stylusMoveCorrectAnswer4Scene(Point stylusPoint) {
}

void stylusUpCorrectAnswer4Scene(Point stylusPoint) {
	SceneEnder_CorrectAnswer4Scene();
}

void keyDownCorrectAnswer4Scene(int key) {
}

void keyUpCorrectAnswer4Scene(int key) {
}
