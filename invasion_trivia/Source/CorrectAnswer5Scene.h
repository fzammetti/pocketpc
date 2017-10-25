
// ================================================================================================
// Globals
// ================================================================================================
Surface*			 CorrectAnswer5SceneActors[17];
SoundFX 			 CorrectAnswer5SceneAudioActors[5];
int						 CorrectAnswer5SceneTextActors[3];
unsigned char* CorrectAnswer5SceneScript = NULL;
SoundFX				 sfxG_KTHGIRTGIRK;
SoundFX				 sfxK_IKGIKIASDFUHIB;
SoundFX				 sfxG_YYSDHIBYY;


// ================================================================================================
// Loader
// ================================================================================================
void loaderCorrectAnswer5Scene(DisplayDevice* display) {
	// Load audio actor sound fx for this scene
	sfxG_KTHGIRTGIRK.load(_Module.GetModuleInstance(), IDR_SFX_G_KTHGIRTGIRK);
	sfxK_IKGIKIASDFUHIB.load(_Module.GetModuleInstance(), IDR_SFX_K_IKGIKIASDFUHIB);
	sfxG_YYSDHIBYY.load(_Module.GetModuleInstance(), IDR_SFX_G_YYSDHIBYY);
	// Get a pointer to the script for this scene
	CorrectAnswer5SceneScript = (unsigned char*)OASIS_loadScriptResource(IDR_CORRECT_ANSWER_5_SCENE_SCRIPT, hInst);
	// Place all actor images in array of actors (order MUST match the script editor!)
	// Last element MUST be NULL
	CorrectAnswer5SceneActors[0]  = imgShipInterior;
	CorrectAnswer5SceneActors[1]  = imgKrelmacBody;
	CorrectAnswer5SceneActors[2]  = imgKrelmacHeadMouthClosed;
	CorrectAnswer5SceneActors[3]  = imgKrelmacHeadMouthOpened;
	CorrectAnswer5SceneActors[4]  = imgKrelmacHeadMouthOpenedWide;
	CorrectAnswer5SceneActors[5]  = imgKrelmacEyebrows;
	CorrectAnswer5SceneActors[6]  = imgGentooBody;
	CorrectAnswer5SceneActors[7]  = imgGentooBodyWhackoff;
	CorrectAnswer5SceneActors[8]  = imgGentooHeadMouthClosed;
	CorrectAnswer5SceneActors[9]  = imgGentooHeadMouthOpened;
	CorrectAnswer5SceneActors[10] = imgGentooHeadMouthOpenedWide;
	CorrectAnswer5SceneActors[11] = imgGentooHeadLookingDown;
	CorrectAnswer5SceneActors[12] = imgGentooHeadEmbarassed;
	CorrectAnswer5SceneActors[13] = imgGentooHeadEmbarassedBlushing;
	CorrectAnswer5SceneActors[14] = NULL;
	// Place all audio actor sound fx in array of audio actors (order MUST match the script editor!)
	// No need to terminate array with NULL or -1
	CorrectAnswer5SceneAudioActors[0] = sfxG_KTHGIRTGIRK;
	CorrectAnswer5SceneAudioActors[1] = sfxK_IKGIKIASDFUHIB;
	CorrectAnswer5SceneAudioActors[2] = sfxG_YYSDHIBYY;
	// Place all text actor resource ID's in array of text actors (order MUST match the script editor!)
	// Last element MUST be -1
	CorrectAnswer5SceneTextActors[0] = -1;
}


// ================================================================================================
// Releaser
// ================================================================================================
void releaserCorrectAnswer5Scene() {
}


// ================================================================================================
// Scene Starter
// ================================================================================================
void SceneStarter_CorrectAnswer5Scene() {
	OASIS_StartScene(CorrectAnswer5SceneScript, CorrectAnswer5SceneActors, CorrectAnswer5SceneAudioActors, CorrectAnswer5SceneTextActors);
}


// ================================================================================================
// Scene Ender
// ================================================================================================
void SceneEnder_CorrectAnswer5Scene() {
	OASIS_EndScene();
	game.currentScreen = csPointLevelsScreen;
}


// ================================================================================================
// Event Handlers
// ================================================================================================
void stylusDownCorrectAnswer5Scene(Point stylusPoint) {
}

void stylusMoveCorrectAnswer5Scene(Point stylusPoint) {
}

void stylusUpCorrectAnswer5Scene(Point stylusPoint) {
	SceneEnder_CorrectAnswer5Scene();
}

void keyDownCorrectAnswer5Scene(int key) {
}

void keyUpCorrectAnswer5Scene(int key) {
}
