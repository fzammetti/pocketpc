
// ================================================================================================
// Globals
// ================================================================================================
Surface*			 StLouisDestructionSceneActors[17];
SoundFX 			 StLouisDestructionSceneAudioActors[7];
int						 StLouisDestructionSceneTextActors[3];
unsigned char* StLouisDestructionSceneScript = NULL;
Surface*			 imgStLouisLiveCity						 = NULL;
Surface*       imgStLouisDeadCity						 = NULL;
SoundFX 			 sfxStLouisWords;


// ================================================================================================
// Loader
// ================================================================================================
void loaderDestructionStLouisScene(DisplayDevice* display) {
	// Load all images for this scene and set color masks
	imgStLouisLiveCity = LoadImage(display, IDR_LIVECITY_ST_LOUIS);
	imgStLouisDeadCity = LoadImage(display, IDR_DEADCITY_ST_LOUIS);
	// Load all wave files for this scene
	sfxStLouisWords.load(_Module.GetModuleInstance(), IDR_SFX_DESTRUCTION_WORDS_ST_LOUIS);
	// Place pointers to each image in our array of actors
	StLouisDestructionSceneActors[0]	= imgStLouisLiveCity;
	StLouisDestructionSceneActors[1]	= imgUFO_001;
	StLouisDestructionSceneActors[2]	= imgUFO_002;
	StLouisDestructionSceneActors[3]	= imgUFO_003;
	StLouisDestructionSceneActors[4]	= imgUFO_004;
	StLouisDestructionSceneActors[5]	= imgExplosion_001;
	StLouisDestructionSceneActors[6]	= imgExplosion_002;
	StLouisDestructionSceneActors[7]	= imgExplosion_003;
	StLouisDestructionSceneActors[8]	= imgExplosion_004;
	StLouisDestructionSceneActors[9]	= imgExplosion_005;
	StLouisDestructionSceneActors[10] = imgLASER_001;
	StLouisDestructionSceneActors[11] = imgLASER_002;
	StLouisDestructionSceneActors[12] = imgLASER_003;
	StLouisDestructionSceneActors[13] = imgStLouisDeadCity;
	StLouisDestructionSceneActors[14] = NULL;
	// Get a pointer to the script for this scene
	StLouisDestructionSceneScript = (unsigned char*)OASIS_loadScriptResource(IDR_DESTRUCTION_ST_LOUIS_SCENE_SCRIPT, hInst);
	// Load the audio actors array with the SoundFX loaded above
	StLouisDestructionSceneAudioActors[0] = sfxUFOHum;
	StLouisDestructionSceneAudioActors[1] = sfxLASER;
	StLouisDestructionSceneAudioActors[2] = sfxExplosion;
	StLouisDestructionSceneAudioActors[3] = sfxStLouisWords;
	StLouisDestructionSceneAudioActors[4] = sfxBounceSound;
	// Do the text actors too
	StLouisDestructionSceneTextActors[0] = -1;
}


// ================================================================================================
// Releaser
// ================================================================================================
void releaserDestructionStLouisScene() {
	delete imgStLouisLiveCity;
	delete imgStLouisDeadCity;
}


// ================================================================================================
// Scene Starter
// ================================================================================================
void SceneStarter_DestructionStLouisScene() {
	OASIS_StartScene(StLouisDestructionSceneScript, StLouisDestructionSceneActors, StLouisDestructionSceneAudioActors, StLouisDestructionSceneTextActors);
}


// ================================================================================================
// Scene Ender
// ================================================================================================
void SceneEnder_DestructionStLouisScene() {
	OASIS_EndScene();
	game.currentScreen = csPointLevelsScreen;
}


// ================================================================================================
// Event Handlers
// ================================================================================================
void stylusDownDestructionStLouisScene(Point stylusPoint) {
}

void stylusMoveDestructionStLouisScene(Point stylusPoint) {
}

void stylusUpDestructionStLouisScene(Point stylusPoint) {
	SceneEnder_DestructionStLouisScene();
}

void keyDownDestructionStLouisScene(int key) {
}

void keyUpDestructionStLouisScene(int key) {
}
