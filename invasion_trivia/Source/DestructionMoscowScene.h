
// ================================================================================================
// Globals
// ================================================================================================
Surface*			 MoscowDestructionSceneActors[17];
SoundFX 			 MoscowDestructionSceneAudioActors[7];
int						 MoscowDestructionSceneTextActors[3];
unsigned char* MoscowDestructionSceneScript = NULL;
Surface*			 imgMoscowLiveCity						= NULL;
Surface*       imgMoscowDeadCity						= NULL;
SoundFX 			 sfxMoscowWords;


// ================================================================================================
// Loader
// ================================================================================================
void loaderDestructionMoscowScene(DisplayDevice* display) {
	// Load all images for this scene and set color masks
	imgMoscowLiveCity = LoadImage(display, IDR_LIVECITY_MOSCOW);
	imgMoscowDeadCity = LoadImage(display, IDR_DEADCITY_MOSCOW);
	// Load all wave files for this scene
	sfxMoscowWords.load(_Module.GetModuleInstance(), IDR_SFX_DESTRUCTION_WORDS_MOSCOW);
	// Place pointers to each image in our array of actors
	MoscowDestructionSceneActors[0]	= imgMoscowLiveCity;
	MoscowDestructionSceneActors[1]	= imgUFO_001;
	MoscowDestructionSceneActors[2]	= imgUFO_002;
	MoscowDestructionSceneActors[3]	= imgUFO_003;
	MoscowDestructionSceneActors[4]	= imgUFO_004;
	MoscowDestructionSceneActors[5]	= imgExplosion_001;
	MoscowDestructionSceneActors[6]	= imgExplosion_002;
	MoscowDestructionSceneActors[7]	= imgExplosion_003;
	MoscowDestructionSceneActors[8]	= imgExplosion_004;
	MoscowDestructionSceneActors[9]	= imgExplosion_005;
	MoscowDestructionSceneActors[10] = imgLASER_001;
	MoscowDestructionSceneActors[11] = imgLASER_002;
	MoscowDestructionSceneActors[12] = imgLASER_003;
	MoscowDestructionSceneActors[13] = imgMoscowDeadCity;
	MoscowDestructionSceneActors[14] = NULL;
	// Get a pointer to the script for this scene
	MoscowDestructionSceneScript = (unsigned char*)OASIS_loadScriptResource(IDR_DESTRUCTION_MOSCOW_SCENE_SCRIPT, hInst);
	// Load the audio actors array with the SoundFX loaded above
	MoscowDestructionSceneAudioActors[0] = sfxUFOHum;
	MoscowDestructionSceneAudioActors[1] = sfxLASER;
	MoscowDestructionSceneAudioActors[2] = sfxExplosion;
	MoscowDestructionSceneAudioActors[3] = sfxMoscowWords;
	MoscowDestructionSceneAudioActors[4] = sfxBounceSound;
	// Do the text actors too
	MoscowDestructionSceneTextActors[0] = -1;
}


// ================================================================================================
// Releaser
// ================================================================================================
void releaserDestructionMoscowScene() {
	delete imgMoscowLiveCity;
	delete imgMoscowDeadCity;
}


// ================================================================================================
// Scene Starter
// ================================================================================================
void SceneStarter_DestructionMoscowScene() {
	OASIS_StartScene(MoscowDestructionSceneScript, MoscowDestructionSceneActors, MoscowDestructionSceneAudioActors, MoscowDestructionSceneTextActors);
}


// ================================================================================================
// Scene Ender
// ================================================================================================
void SceneEnder_DestructionMoscowScene() {
	OASIS_EndScene();
	game.currentScreen = csPointLevelsScreen;
}


// ================================================================================================
// Event Handlers
// ================================================================================================
void stylusDownDestructionMoscowScene(Point stylusPoint) {
}

void stylusMoveDestructionMoscowScene(Point stylusPoint) {
}

void stylusUpDestructionMoscowScene(Point stylusPoint) {
	SceneEnder_DestructionMoscowScene();
}

void keyDownDestructionMoscowScene(int key) {
}

void keyUpDestructionMoscowScene(int key) {
}
