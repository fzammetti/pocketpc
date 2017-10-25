
// ================================================================================================
// Globals
// ================================================================================================
Surface*			 GizaDestructionSceneActors[17];
SoundFX 			 GizaDestructionSceneAudioActors[7];
int						 GizaDestructionSceneTextActors[3];
unsigned char* GizaDestructionSceneScript = NULL;
Surface*			 imgGizaLiveCity						= NULL;
Surface*       imgGizaDeadCity						= NULL;
SoundFX 			 sfxGizaWords;


// ================================================================================================
// Loader
// ================================================================================================
void loaderDestructionGizaScene(DisplayDevice* display) {
	// Load all images for this scene and set color masks
	imgGizaLiveCity = LoadImage(display, IDR_LIVECITY_GIZA);
	imgGizaDeadCity = LoadImage(display, IDR_DEADCITY_GIZA);
	// Load all wave files for this scene
	sfxGizaWords.load(_Module.GetModuleInstance(), IDR_SFX_DESTRUCTION_WORDS_GIZA);
	// Place pointers to each image in our array of actors
	GizaDestructionSceneActors[0]	= imgGizaLiveCity;
	GizaDestructionSceneActors[1]	= imgUFO_001;
	GizaDestructionSceneActors[2]	= imgUFO_002;
	GizaDestructionSceneActors[3]	= imgUFO_003;
	GizaDestructionSceneActors[4]	= imgUFO_004;
	GizaDestructionSceneActors[5]	= imgExplosion_001;
	GizaDestructionSceneActors[6]	= imgExplosion_002;
	GizaDestructionSceneActors[7]	= imgExplosion_003;
	GizaDestructionSceneActors[8]	= imgExplosion_004;
	GizaDestructionSceneActors[9]	= imgExplosion_005;
	GizaDestructionSceneActors[10] = imgLASER_001;
	GizaDestructionSceneActors[11] = imgLASER_002;
	GizaDestructionSceneActors[12] = imgLASER_003;
	GizaDestructionSceneActors[13] = imgGizaDeadCity;
	GizaDestructionSceneActors[14] = NULL;
	// Get a pointer to the script for this scene
	GizaDestructionSceneScript = (unsigned char*)OASIS_loadScriptResource(IDR_DESTRUCTION_GIZA_SCENE_SCRIPT, hInst);
	// Load the audio actors array with the SoundFX loaded above
	GizaDestructionSceneAudioActors[0] = sfxUFOHum;
	GizaDestructionSceneAudioActors[1] = sfxLASER;
	GizaDestructionSceneAudioActors[2] = sfxExplosion;
	GizaDestructionSceneAudioActors[3] = sfxGizaWords;
	GizaDestructionSceneAudioActors[4] = sfxBounceSound;
	// Do the text actors too
	GizaDestructionSceneTextActors[0] = -1;
}


// ================================================================================================
// Releaser
// ================================================================================================
void releaserDestructionGizaScene() {
	delete imgGizaLiveCity;
	delete imgGizaDeadCity;
}


// ================================================================================================
// Scene Starter
// ================================================================================================
void SceneStarter_DestructionGizaScene() {
	OASIS_StartScene(GizaDestructionSceneScript, GizaDestructionSceneActors, GizaDestructionSceneAudioActors, GizaDestructionSceneTextActors);
}


// ================================================================================================
// Scene Ender
// ================================================================================================
void SceneEnder_DestructionGizaScene() {
	OASIS_EndScene();
	game.currentScreen = csPointLevelsScreen;
}


// ================================================================================================
// Event Handlers
// ================================================================================================
void stylusDownDestructionGizaScene(Point stylusPoint) {
}

void stylusMoveDestructionGizaScene(Point stylusPoint) {
}

void stylusUpDestructionGizaScene(Point stylusPoint) {
	SceneEnder_DestructionGizaScene();
}

void keyDownDestructionGizaScene(int key) {
}

void keyUpDestructionGizaScene(int key) {
}
