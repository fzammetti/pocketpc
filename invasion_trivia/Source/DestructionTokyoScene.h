
// ================================================================================================
// Globals
// ================================================================================================
Surface*			 TokyoDestructionSceneActors[17];
SoundFX 			 TokyoDestructionSceneAudioActors[7];
int						 TokyoDestructionSceneTextActors[3];
unsigned char* TokyoDestructionSceneScript = NULL;
Surface*			 imgTokyoLiveCity						 = NULL;
Surface*       imgTokyoDeadCity						 = NULL;
SoundFX 			 sfxTokyoWords;


// ================================================================================================
// Loader
// ================================================================================================
void loaderDestructionTokyoScene(DisplayDevice* display) {
	// Load all images for this scene and set color masks
	imgTokyoLiveCity = LoadImage(display, IDR_LIVECITY_TOKYO);
	imgTokyoDeadCity = LoadImage(display, IDR_DEADCITY_TOKYO);
	// Load all wave files for this scene
	sfxTokyoWords.load(_Module.GetModuleInstance(), IDR_SFX_DESTRUCTION_WORDS_TOKYO);
	// Place pointers to each image in our array of actors
	TokyoDestructionSceneActors[0]	= imgTokyoLiveCity;
	TokyoDestructionSceneActors[1]	= imgUFO_001;
	TokyoDestructionSceneActors[2]	= imgUFO_002;
	TokyoDestructionSceneActors[3]	= imgUFO_003;
	TokyoDestructionSceneActors[4]	= imgUFO_004;
	TokyoDestructionSceneActors[5]	= imgExplosion_001;
	TokyoDestructionSceneActors[6]	= imgExplosion_002;
	TokyoDestructionSceneActors[7]	= imgExplosion_003;
	TokyoDestructionSceneActors[8]	= imgExplosion_004;
	TokyoDestructionSceneActors[9]	= imgExplosion_005;
	TokyoDestructionSceneActors[10] = imgLASER_001;
	TokyoDestructionSceneActors[11] = imgLASER_002;
	TokyoDestructionSceneActors[12] = imgLASER_003;
	TokyoDestructionSceneActors[13] = imgTokyoDeadCity;
	TokyoDestructionSceneActors[14] = NULL;
	// Get a pointer to the script for this scene
	TokyoDestructionSceneScript = (unsigned char*)OASIS_loadScriptResource(IDR_DESTRUCTION_TOKYO_SCENE_SCRIPT, hInst);
	// Load the audio actors array with the SoundFX loaded above
	TokyoDestructionSceneAudioActors[0] = sfxUFOHum;
	TokyoDestructionSceneAudioActors[1] = sfxLASER;
	TokyoDestructionSceneAudioActors[2] = sfxExplosion;
	TokyoDestructionSceneAudioActors[3] = sfxTokyoWords;
	TokyoDestructionSceneAudioActors[4] = sfxBounceSound;
	// Do the text actors too
	TokyoDestructionSceneTextActors[0] = -1;
}


// ================================================================================================
// Releaser
// ================================================================================================
void releaserDestructionTokyoScene() {
	delete imgTokyoLiveCity;
	delete imgTokyoDeadCity;
}


// ================================================================================================
// Scene Starter
// ================================================================================================
void SceneStarter_DestructionTokyoScene() {
	OASIS_StartScene(TokyoDestructionSceneScript, TokyoDestructionSceneActors, TokyoDestructionSceneAudioActors, TokyoDestructionSceneTextActors);
}


// ================================================================================================
// Scene Ender
// ================================================================================================
void SceneEnder_DestructionTokyoScene() {
	OASIS_EndScene();
	game.currentScreen = csPointLevelsScreen;
}


// ================================================================================================
// Event Handlers
// ================================================================================================
void stylusDownDestructionTokyoScene(Point stylusPoint) {
}

void stylusMoveDestructionTokyoScene(Point stylusPoint) {
}

void stylusUpDestructionTokyoScene(Point stylusPoint) {
	SceneEnder_DestructionTokyoScene();
}

void keyDownDestructionTokyoScene(int key) {
}

void keyUpDestructionTokyoScene(int key) {
}
