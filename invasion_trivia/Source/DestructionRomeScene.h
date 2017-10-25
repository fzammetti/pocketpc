
// ================================================================================================
// Globals
// ================================================================================================
Surface*			 RomeDestructionSceneActors[17];
SoundFX 			 RomeDestructionSceneAudioActors[7];
int						 RomeDestructionSceneTextActors[3];
unsigned char* RomeDestructionSceneScript = NULL;
Surface*			 imgRomeLiveCity						= NULL;
Surface*       imgRomeDeadCity						= NULL;
SoundFX 			 sfxRomeWords;


// ================================================================================================
// Loader
// ================================================================================================
void loaderDestructionRomeScene(DisplayDevice* display) {
	// Load all images for this scene and set color masks
	imgRomeLiveCity = LoadImage(display, IDR_LIVECITY_ROME);
	imgRomeDeadCity = LoadImage(display, IDR_DEADCITY_ROME);
	// Load all wave files for this scene
	sfxRomeWords.load(_Module.GetModuleInstance(), IDR_SFX_DESTRUCTION_WORDS_ROME);
	// Place pointers to each image in our array of actors
	RomeDestructionSceneActors[0]	= imgRomeLiveCity;
	RomeDestructionSceneActors[1]	= imgUFO_001;
	RomeDestructionSceneActors[2]	= imgUFO_002;
	RomeDestructionSceneActors[3]	= imgUFO_003;
	RomeDestructionSceneActors[4]	= imgUFO_004;
	RomeDestructionSceneActors[5]	= imgExplosion_001;
	RomeDestructionSceneActors[6]	= imgExplosion_002;
	RomeDestructionSceneActors[7]	= imgExplosion_003;
	RomeDestructionSceneActors[8]	= imgExplosion_004;
	RomeDestructionSceneActors[9]	= imgExplosion_005;
	RomeDestructionSceneActors[10] = imgLASER_001;
	RomeDestructionSceneActors[11] = imgLASER_002;
	RomeDestructionSceneActors[12] = imgLASER_003;
	RomeDestructionSceneActors[13] = imgRomeDeadCity;
	RomeDestructionSceneActors[14] = NULL;
	// Get a pointer to the script for this scene
	RomeDestructionSceneScript = (unsigned char*)OASIS_loadScriptResource(IDR_DESTRUCTION_ROME_SCENE_SCRIPT, hInst);
	// Load the audio actors array with the SoundFX loaded above
	RomeDestructionSceneAudioActors[0] = sfxUFOHum;
	RomeDestructionSceneAudioActors[1] = sfxLASER;
	RomeDestructionSceneAudioActors[2] = sfxExplosion;
	RomeDestructionSceneAudioActors[3] = sfxRomeWords;
	RomeDestructionSceneAudioActors[4] = sfxBounceSound;
	// Do the text actors too
	RomeDestructionSceneTextActors[0] = -1;
}


// ================================================================================================
// Releaser
// ================================================================================================
void releaserDestructionRomeScene() {
	delete imgRomeLiveCity;
	delete imgRomeDeadCity;
}


// ================================================================================================
// Scene Starter
// ================================================================================================
void SceneStarter_DestructionRomeScene() {
	OASIS_StartScene(RomeDestructionSceneScript, RomeDestructionSceneActors, RomeDestructionSceneAudioActors, RomeDestructionSceneTextActors);
}


// ================================================================================================
// Scene Ender
// ================================================================================================
void SceneEnder_DestructionRomeScene() {
	OASIS_EndScene();
	game.currentScreen = csPointLevelsScreen;
}


// ================================================================================================
// Event Handlers
// ================================================================================================
void stylusDownDestructionRomeScene(Point stylusPoint) {
}

void stylusMoveDestructionRomeScene(Point stylusPoint) {
}

void stylusUpDestructionRomeScene(Point stylusPoint) {
	SceneEnder_DestructionRomeScene();
}

void keyDownDestructionRomeScene(int key) {
}

void keyUpDestructionRomeScene(int key) {
}
