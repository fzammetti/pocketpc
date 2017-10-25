
// ================================================================================================
// Globals
// ================================================================================================
Surface*			 AskTheAndromedansSceneActors[4];
SoundFX 			 AskTheAndromedansSceneAudioActors[3];
int						 AskTheAndromedansSceneTextActors[3];
unsigned char* AskTheAndromedansSceneScript = NULL;
Surface*			 imgAskTheAndromedans					= NULL;
SoundFX				 sfxAskTheAndromedans;


// ================================================================================================
// Loader
// ================================================================================================
void loaderAskTheAndromedansScene(DisplayDevice* display) {
	// Load audio actor sound fx for this scene
	sfxAskTheAndromedans.load(_Module.GetModuleInstance(), IDR_SFX_ASKTHEANDROMEDANS);
	// Load actor images for this scene and set required transparency masks
	imgAskTheAndromedans = LoadImage(display, IDR_ASKTHEANDROMEDANS);
	// Place pointers to each image in our array of actors
	AskTheAndromedansSceneActors[0]  = imgAskTheAndromedans;
	AskTheAndromedansSceneActors[1]	 = NULL;
	// Get a pointer to the script for this scene
	AskTheAndromedansSceneScript = (unsigned char*)OASIS_loadScriptResource(IDR_ASK_THE_ANDROMEDANS_SCENE_SCRIPT, hInst);
	// Place all audio actor sound fx in array of audio actors (order MUST match the script editor!)
	// No need to terminate array with NULL or -1
	AskTheAndromedansSceneAudioActors[0] = sfxAskTheAndromedans;
	// Do the text actors too
	AskTheAndromedansSceneTextActors[0] = -1;
}


// ================================================================================================
// Releaser
// ================================================================================================
void releaserAskTheAndromedansScene() {
	delete imgAskTheAndromedans;
}


// ================================================================================================
// Scene Starter
// ================================================================================================
void SceneStarter_AskTheAndromedansScene() {
	OASIS_StartScene(AskTheAndromedansSceneScript, AskTheAndromedansSceneActors, AskTheAndromedansSceneAudioActors, AskTheAndromedansSceneTextActors);
}


// ================================================================================================
// Scene Ender
// ================================================================================================
void SceneEnder_AskTheAndromedansScene() {
	OASIS_EndScene();
	game.currentScreen = csAnswerScreen;
}


// ================================================================================================
// Event Handlers
// ================================================================================================
void stylusDownAskTheAndromedansScene(Point stylusPoint) {
}

void stylusMoveAskTheAndromedansScene(Point stylusPoint) {
}

void stylusUpAskTheAndromedansScene(Point stylusPoint) {
	SceneEnder_AskTheAndromedansScene();
}

void keyDownAskTheAndromedansScene(int key) {
}

void keyUpAskTheAndromedansScene(int key) {
}
