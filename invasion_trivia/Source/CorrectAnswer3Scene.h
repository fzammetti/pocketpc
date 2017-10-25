
// ================================================================================================
// Globals
// ================================================================================================
Surface*			 CorrectAnswer3SceneActors[17];
SoundFX 			 CorrectAnswer3SceneAudioActors[5];
int						 CorrectAnswer3SceneTextActors[3];
unsigned char* CorrectAnswer3SceneScript = NULL;
SoundFX				 sfxK_ITTMTOFSG;
SoundFX				 sfxG_YSHLMPITQAQT;
SoundFX				 sfxK_NMTTMTNOFS;

// ================================================================================================
// Loader
// ================================================================================================
void loaderCorrectAnswer3Scene(DisplayDevice* display) {
	// Load audio actor sound fx for this scene
	sfxK_ITTMTOFSG.load(_Module.GetModuleInstance(), IDR_SFX_K_ITTMTOFSG);
	sfxG_YSHLMPITQAQT.load(_Module.GetModuleInstance(), IDR_SFX_G_YSHLMPITQAQT);
	sfxK_NMTTMTNOFS.load(_Module.GetModuleInstance(), IDR_SFX_K_NMTTMTNOFS);
	// Get a pointer to the script for this scene
	CorrectAnswer3SceneScript = (unsigned char*)OASIS_loadScriptResource(IDR_CORRECT_ANSWER_3_SCENE_SCRIPT, hInst);
	// Place all actor images in array of actors (order MUST match the script editor!)
	// Last element MUST be NULL
	CorrectAnswer3SceneActors[0]  = imgShipInterior;
	CorrectAnswer3SceneActors[1]  = imgKrelmacBody;
	CorrectAnswer3SceneActors[2]  = imgKrelmacHeadMouthClosed;
	CorrectAnswer3SceneActors[3]  = imgKrelmacHeadMouthOpened;
	CorrectAnswer3SceneActors[4]  = imgKrelmacHeadMouthOpenedWide;
	CorrectAnswer3SceneActors[5]  = imgKrelmacEyebrows;
	CorrectAnswer3SceneActors[6]  = imgGentooBody;
	CorrectAnswer3SceneActors[7]  = imgGentooBodyWhackoff;
	CorrectAnswer3SceneActors[8]  = imgGentooHeadMouthClosed;
	CorrectAnswer3SceneActors[9]  = imgGentooHeadMouthOpened;
	CorrectAnswer3SceneActors[10] = imgGentooHeadMouthOpenedWide;
	CorrectAnswer3SceneActors[11] = imgGentooHeadLookingDown;
	CorrectAnswer3SceneActors[12] = imgGentooHeadEmbarassed;
	CorrectAnswer3SceneActors[13] = imgGentooHeadEmbarassedBlushing;
	CorrectAnswer3SceneActors[14] = NULL;
	// Place all audio actor sound fx in array of audio actors (order MUST match the script editor!)
	// No need to terminate array with NULL or -1
	CorrectAnswer3SceneAudioActors[0] = sfxK_ITTMTOFSG;
	CorrectAnswer3SceneAudioActors[1] = sfxG_YSHLMPITQAQT;
	CorrectAnswer3SceneAudioActors[2] = sfxK_NMTTMTNOFS;
	// Place all text actor resource ID's in array of text actors (order MUST match the script editor!)
	// Last element MUST be -1
	CorrectAnswer3SceneTextActors[0] = -1;
}


// ================================================================================================
// Releaser
// ================================================================================================
void releaserCorrectAnswer3Scene() {
}


// ================================================================================================
// Scene Starter
// ================================================================================================
void SceneStarter_CorrectAnswer3Scene() {
	OASIS_StartScene(CorrectAnswer3SceneScript, CorrectAnswer3SceneActors, CorrectAnswer3SceneAudioActors, CorrectAnswer3SceneTextActors);
}


// ================================================================================================
// Scene Ender
// ================================================================================================
void SceneEnder_CorrectAnswer3Scene() {
	OASIS_EndScene();
	game.currentScreen = csPointLevelsScreen;
}


// ================================================================================================
// Event Handlers
// ================================================================================================
void stylusDownCorrectAnswer3Scene(Point stylusPoint) {
}

void stylusMoveCorrectAnswer3Scene(Point stylusPoint) {
}

void stylusUpCorrectAnswer3Scene(Point stylusPoint) {
	SceneEnder_CorrectAnswer3Scene();
}

void keyDownCorrectAnswer3Scene(int key) {
}

void keyUpCorrectAnswer3Scene(int key) {
}
