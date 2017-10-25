
// ================================================================================================
// Globals
// ================================================================================================
Surface*			 PisaDestructionSceneActors[17];
SoundFX 			 PisaDestructionSceneAudioActors[7];
int						 PisaDestructionSceneTextActors[3];
unsigned char* PisaDestructionSceneScript = NULL;
Surface*			 imgPisaLiveCity						= NULL;
Surface*       imgPisaDeadCity						= NULL;
SoundFX 			 sfxPisaWords;


// ================================================================================================
// Loader
// ================================================================================================
void loaderDestructionPisaScene(DisplayDevice* display) {
	// Load all images for this scene and set color masks
	imgPisaLiveCity = LoadImage(display, IDR_LIVECITY_PISA);
	imgPisaDeadCity = LoadImage(display, IDR_DEADCITY_PISA);
	// Load all wave files for this scene
	sfxPisaWords.load(_Module.GetModuleInstance(), IDR_SFX_DESTRUCTION_WORDS_PISA);
	// Place pointers to each image in our array of actors
	PisaDestructionSceneActors[0]	= imgPisaLiveCity;
	PisaDestructionSceneActors[1]	= imgUFO_001;
	PisaDestructionSceneActors[2]	= imgUFO_002;
	PisaDestructionSceneActors[3]	= imgUFO_003;
	PisaDestructionSceneActors[4]	= imgUFO_004;
	PisaDestructionSceneActors[5]	= imgExplosion_001;
	PisaDestructionSceneActors[6]	= imgExplosion_002;
	PisaDestructionSceneActors[7]	= imgExplosion_003;
	PisaDestructionSceneActors[8]	= imgExplosion_004;
	PisaDestructionSceneActors[9]	= imgExplosion_005;
	PisaDestructionSceneActors[10] = imgLASER_001;
	PisaDestructionSceneActors[11] = imgLASER_002;
	PisaDestructionSceneActors[12] = imgLASER_003;
	PisaDestructionSceneActors[13] = imgPisaDeadCity;
	PisaDestructionSceneActors[14] = NULL;
	// Get a pointer to the script for this scene
	PisaDestructionSceneScript = (unsigned char*)OASIS_loadScriptResource(IDR_DESTRUCTION_PISA_SCENE_SCRIPT, hInst);
	// Load the audio actors array with the SoundFX loaded above
	PisaDestructionSceneAudioActors[0] = sfxUFOHum;
	PisaDestructionSceneAudioActors[1] = sfxLASER;
	PisaDestructionSceneAudioActors[2] = sfxExplosion;
	PisaDestructionSceneAudioActors[3] = sfxPisaWords;
	PisaDestructionSceneAudioActors[4] = sfxBounceSound;
	// Do the text actors too
	PisaDestructionSceneTextActors[0] = -1;
}


// ================================================================================================
// Releaser
// ================================================================================================
void releaserDestructionPisaScene() {
	delete imgPisaLiveCity;
	delete imgPisaDeadCity;
}


// ================================================================================================
// Scene Starter
// ================================================================================================
void SceneStarter_DestructionPisaScene() {
	OASIS_StartScene(PisaDestructionSceneScript, PisaDestructionSceneActors, PisaDestructionSceneAudioActors, PisaDestructionSceneTextActors);
}


// ================================================================================================
// Scene Ender
// ================================================================================================
void SceneEnder_DestructionPisaScene() {
	OASIS_EndScene();
	game.currentScreen = csPointLevelsScreen;
}


// ================================================================================================
// Event Handlers
// ================================================================================================
void stylusDownDestructionPisaScene(Point stylusPoint) {
}

void stylusMoveDestructionPisaScene(Point stylusPoint) {
}

void stylusUpDestructionPisaScene(Point stylusPoint) {
	SceneEnder_DestructionPisaScene();
}

void keyDownDestructionPisaScene(int key) {
}

void keyUpDestructionPisaScene(int key) {
}
