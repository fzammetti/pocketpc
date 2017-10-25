
// ================================================================================================
// Globals
// ================================================================================================
Surface*			 LondonDestructionSceneActors[17];
SoundFX 			 LondonDestructionSceneAudioActors[7];
int						 LondonDestructionSceneTextActors[3];
unsigned char* LondonDestructionSceneScript = NULL;
Surface*			 imgLondonLiveCity						= NULL;
Surface*       imgLondonDeadCity						= NULL;
SoundFX 			 sfxLondonWords;


// ================================================================================================
// Loader
// ================================================================================================
void loaderDestructionLondonScene(DisplayDevice* display) {
	// Load all images for this scene and set color masks
	imgLondonLiveCity = LoadImage(display, IDR_LIVECITY_LONDON);
	imgLondonDeadCity = LoadImage(display, IDR_DEADCITY_LONDON);
	// Load all wave files for this scene
	sfxLondonWords.load(_Module.GetModuleInstance(), IDR_SFX_DESTRUCTION_WORDS_LONDON);
	// Place pointers to each image in our array of actors
	LondonDestructionSceneActors[0]	= imgLondonLiveCity;
	LondonDestructionSceneActors[1]	= imgUFO_001;
	LondonDestructionSceneActors[2]	= imgUFO_002;
	LondonDestructionSceneActors[3]	= imgUFO_003;
	LondonDestructionSceneActors[4]	= imgUFO_004;
	LondonDestructionSceneActors[5]	= imgExplosion_001;
	LondonDestructionSceneActors[6]	= imgExplosion_002;
	LondonDestructionSceneActors[7]	= imgExplosion_003;
	LondonDestructionSceneActors[8]	= imgExplosion_004;
	LondonDestructionSceneActors[9]	= imgExplosion_005;
	LondonDestructionSceneActors[10] = imgLASER_001;
	LondonDestructionSceneActors[11] = imgLASER_002;
	LondonDestructionSceneActors[12] = imgLASER_003;
	LondonDestructionSceneActors[13] = imgLondonDeadCity;
	LondonDestructionSceneActors[14] = NULL;
	// Get a pointer to the script for this scene
	LondonDestructionSceneScript = (unsigned char*)OASIS_loadScriptResource(IDR_DESTRUCTION_LONDON_SCENE_SCRIPT, hInst);
	// Load the audio actors array with the SoundFX loaded above
	LondonDestructionSceneAudioActors[0] = sfxUFOHum;
	LondonDestructionSceneAudioActors[1] = sfxLASER;
	LondonDestructionSceneAudioActors[2] = sfxExplosion;
	LondonDestructionSceneAudioActors[3] = sfxLondonWords;
	LondonDestructionSceneAudioActors[4] = sfxBounceSound;
	// Do the text actors too
	LondonDestructionSceneTextActors[0] = -1;
}


// ================================================================================================
// Releaser
// ================================================================================================
void releaserDestructionLondonScene() {
	delete imgLondonLiveCity;
	delete imgLondonDeadCity;
}


// ================================================================================================
// Scene Starter
// ================================================================================================
void SceneStarter_DestructionLondonScene() {
	OASIS_StartScene(LondonDestructionSceneScript, LondonDestructionSceneActors, LondonDestructionSceneAudioActors, LondonDestructionSceneTextActors);
}


// ================================================================================================
// Scene Ender
// ================================================================================================
void SceneEnder_DestructionLondonScene() {
	OASIS_EndScene();
	game.currentScreen = csPointLevelsScreen;
}


// ================================================================================================
// Event Handlers
// ================================================================================================
void stylusDownDestructionLondonScene(Point stylusPoint) {
}

void stylusMoveDestructionLondonScene(Point stylusPoint) {
}

void stylusUpDestructionLondonScene(Point stylusPoint) {
	SceneEnder_DestructionLondonScene();
}

void keyDownDestructionLondonScene(int key) {
}

void keyUpDestructionLondonScene(int key) {
}
