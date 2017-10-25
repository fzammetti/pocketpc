
// ================================================================================================
// Globals
// ================================================================================================
Surface*			 WorldDestruction2SceneActors[25];
SoundFX 			 WorldDestruction2SceneAudioActors[7];
int						 WorldDestruction2SceneTextActors[3];
unsigned char* WorldDestruction2SceneScript = NULL;
SoundFX 			 sfxG_IFAGDITF;
SoundFX 			 sfxK_HMTHITYGDMWL;
SoundFX 			 sfxG_BWATBLUK;
SoundFX 			 sfxK_GPGITCTHNIOTPOTDS;


// ================================================================================================
// Loader
// ================================================================================================
void loaderWorldDestruction2Scene(DisplayDevice* display) {
	// Load audio actor sound fx for this scene
	sfxG_IFAGDITF.load(_Module.GetModuleInstance(), IDR_SFX_G_IFAGDITF);
	sfxK_HMTHITYGDMWL.load(_Module.GetModuleInstance(), IDR_SFX_K_HMTHITYGDMWL);
	sfxG_BWATBLUK.load(_Module.GetModuleInstance(), IDR_SFX_G_BWATBLUK);
	sfxK_GPGITCTHNIOTPOTDS.load(_Module.GetModuleInstance(), IDR_SFX_K_GPGITCTHNIOTPOTDS);
	// Get a pointer to the script for this scene
	WorldDestruction2SceneScript = (unsigned char*)OASIS_loadScriptResource(IDR_WORLD_DESTRUCTION_2_SCENE_SCRIPT, hInst);
	// Place all actor images in array of actors (order MUST match the script editor!)
	// Last element MUST be NULL
	WorldDestruction2SceneActors[0]  = imgDestructionEarth;
	WorldDestruction2SceneActors[1]  = imgDestructionEarthDestroyed;
	WorldDestruction2SceneActors[2]  = imgDestructionUFOZoom01;
	WorldDestruction2SceneActors[3]  = imgDestructionUFOZoom02;
	WorldDestruction2SceneActors[4]  = imgDestructionUFOZoom03;
	WorldDestruction2SceneActors[5]  = imgDestructionUFOZoom04;
	WorldDestruction2SceneActors[6]  = imgDestructionUFOZoom05;
	WorldDestruction2SceneActors[7]  = imgDestructionUFOZoom06;
	WorldDestruction2SceneActors[8]  = imgDestructionUFOZoom07;
	WorldDestruction2SceneActors[9]  = imgDestructionUFOZoom08;
	WorldDestruction2SceneActors[10] = imgDestructionUFOZoom09;
	WorldDestruction2SceneActors[11] = imgDestructionUFOZoom10;
	WorldDestruction2SceneActors[12] = imgDestructionUFOZoom11;
	WorldDestruction2SceneActors[13] = imgDestructionUFOZoom12;
	WorldDestruction2SceneActors[14] = imgDestructionUFOZoom13;
	WorldDestruction2SceneActors[15] = imgDestructionUFOZoom14;
	WorldDestruction2SceneActors[16] = imgDestructionUFOZoom15;
	WorldDestruction2SceneActors[17] = imgExplosion_001;
	WorldDestruction2SceneActors[18] = imgExplosion_002;
	WorldDestruction2SceneActors[19] = imgExplosion_003;
	WorldDestruction2SceneActors[20] = imgExplosion_004;
	WorldDestruction2SceneActors[21] = imgExplosion_005;
	WorldDestruction2SceneActors[22] = NULL;
	// Place all audio actor sound fx in array of audio actors (order MUST match the script editor!)
	// No need to terminate array with NULL or -1
	WorldDestruction2SceneAudioActors[0] = sfxExplosion;
	WorldDestruction2SceneAudioActors[1] = sfxG_IFAGDITF;
	WorldDestruction2SceneAudioActors[2] = sfxK_HMTHITYGDMWL;
	WorldDestruction2SceneAudioActors[3] = sfxG_BWATBLUK;
	WorldDestruction2SceneAudioActors[4] = sfxK_GPGITCTHNIOTPOTDS;
	// Place all text actor resource ID's in array of text actors (order MUST match the script editor!)
	// Last element MUST be -1
	WorldDestruction2SceneTextActors[0] = -1;
}


// ================================================================================================
// Releaser
// ================================================================================================
void releaserWorldDestruction2Scene() {
}


// ================================================================================================
// Scene Starter
// ================================================================================================
void SceneStarter_WorldDestruction2Scene() {
	OASIS_StartScene(WorldDestruction2SceneScript, WorldDestruction2SceneActors, WorldDestruction2SceneAudioActors, WorldDestruction2SceneTextActors);
}


// ================================================================================================
// Scene Ender
// ================================================================================================
void SceneEnder_WorldDestruction2Scene() {
	OASIS_EndScene();
	if (game.SeeIfPlayerGotHighScore()) {
		game.currentPointLevel--; // Do this so that the correct point level is saved in high scores
		game.currentScreen = csCongratulationsScreen;
	} else {
		game.itPlayThemeMusic();
		game.currentScreen = csMainMenuScreen;
	}
}


// ================================================================================================
// Event Handlers
// ================================================================================================
void stylusDownWorldDestruction2Scene(Point stylusPoint) {
}

void stylusMoveWorldDestruction2Scene(Point stylusPoint) {
}

void stylusUpWorldDestruction2Scene(Point stylusPoint) {
	SceneEnder_WorldDestruction2Scene();
}

void keyDownWorldDestruction2Scene(int key) {
}

void keyUpWorldDestruction2Scene(int key) {
}
