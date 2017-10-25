
// ================================================================================================
// Globals
// ================================================================================================
Surface*			 CorrectAnswer2SceneActors[17];
SoundFX 			 CorrectAnswer2SceneAudioActors[4];
int						 CorrectAnswer2SceneTextActors[3];
unsigned char* CorrectAnswer2SceneScript = NULL;
SoundFX				 sfxG_IDBIKTNO;
SoundFX				 sfxK_DWMLYSIWL;


// ================================================================================================
// Loader
// ================================================================================================
void loaderCorrectAnswer2Scene(DisplayDevice* display) {
	// Load audio actor sound fx for this scene
	sfxG_IDBIKTNO.load(_Module.GetModuleInstance(), IDR_SFX_G_IDBIKTNO);
	sfxK_DWMLYSIWL.load(_Module.GetModuleInstance(), IDR_SFX_K_DWMLYSIWL);
	// Get a pointer to the script for this scene
	CorrectAnswer2SceneScript = (unsigned char*)OASIS_loadScriptResource(IDR_CORRECT_ANSWER_2_SCENE_SCRIPT, hInst);
	// Place all actor images in array of actors (order MUST match the script editor!)
	// Last element MUST be NULL
	CorrectAnswer2SceneActors[0]  = imgShipInterior;
	CorrectAnswer2SceneActors[1]  = imgKrelmacBody;
	CorrectAnswer2SceneActors[2]  = imgKrelmacHeadMouthClosed;
	CorrectAnswer2SceneActors[3]  = imgKrelmacHeadMouthOpened;
	CorrectAnswer2SceneActors[4]  = imgKrelmacHeadMouthOpenedWide;
	CorrectAnswer2SceneActors[5]  = imgKrelmacEyebrows;
	CorrectAnswer2SceneActors[6]  = imgGentooBody;
	CorrectAnswer2SceneActors[7]  = imgGentooBodyWhackoff;
	CorrectAnswer2SceneActors[8]  = imgGentooHeadMouthClosed;
	CorrectAnswer2SceneActors[9]  = imgGentooHeadMouthOpened;
	CorrectAnswer2SceneActors[10] = imgGentooHeadMouthOpenedWide;
	CorrectAnswer2SceneActors[11] = imgGentooHeadLookingDown;
	CorrectAnswer2SceneActors[12] = imgGentooHeadEmbarassed;
	CorrectAnswer2SceneActors[13] = imgGentooHeadEmbarassedBlushing;
	CorrectAnswer2SceneActors[14] = NULL;
	// Place all audio actor sound fx in array of audio actors (order MUST match the script editor!)
	// No need to terminate array with NULL or -1
	CorrectAnswer2SceneAudioActors[0] = sfxG_IDBIKTNO;
	CorrectAnswer2SceneAudioActors[1] = sfxK_DWMLYSIWL;
	// Place all text actor resource ID's in array of text actors (order MUST match the script editor!)
	// Last element MUST be -1
	CorrectAnswer2SceneTextActors[0] = -1;
}


// ================================================================================================
// Releaser
// ================================================================================================
void releaserCorrectAnswer2Scene() {
}


// ================================================================================================
// Scene Starter
// ================================================================================================
void SceneStarter_CorrectAnswer2Scene() {
	OASIS_StartScene(CorrectAnswer2SceneScript, CorrectAnswer2SceneActors, CorrectAnswer2SceneAudioActors, CorrectAnswer2SceneTextActors);
}


// ================================================================================================
// Scene Ender
// ================================================================================================
void SceneEnder_CorrectAnswer2Scene() {
	OASIS_EndScene();
	game.currentScreen = csPointLevelsScreen;
}


// ================================================================================================
// Event Handlers
// ================================================================================================
void stylusDownCorrectAnswer2Scene(Point stylusPoint) {
}

void stylusMoveCorrectAnswer2Scene(Point stylusPoint) {
}

void stylusUpCorrectAnswer2Scene(Point stylusPoint) {
	SceneEnder_CorrectAnswer2Scene();
}

void keyDownCorrectAnswer2Scene(int key) {
}

void keyUpCorrectAnswer2Scene(int key) {
}
