
// ================================================================================================
// Globals
// ================================================================================================
Surface*			 WorldDestruction4SceneActors[25];
SoundFX 			 WorldDestruction4SceneAudioActors[11];
int						 WorldDestruction4SceneTextActors[3];
unsigned char* WorldDestruction4SceneScript = NULL;
SoundFX				 sfxK_GIHTEWCOAS;
SoundFX				 sfxG_SWK;
SoundFX				 sfxK_TADTL;
SoundFX				 sfxG_IDGI;
SoundFX				 sfxK_AF;
SoundFX				 sfxG_U;
SoundFX				 sfxK_GYASAT;
SoundFX				 sfxG_YBIHTDB;


// ================================================================================================
// Loader
// ================================================================================================
void loaderWorldDestruction4Scene(DisplayDevice* display) {
	// Load audio actor sound fx for this scene
	sfxK_GIHTEWCOAS.load(_Module.GetModuleInstance(), IDR_SFX_K_GIHTEWCOAS);
	sfxG_SWK.load(_Module.GetModuleInstance(), IDR_SFX_G_SWK);
	sfxK_TADTL.load(_Module.GetModuleInstance(), IDR_SFX_K_TADTL);
	sfxG_IDGI.load(_Module.GetModuleInstance(), IDR_SFX_G_IDGI);
	sfxK_AF.load(_Module.GetModuleInstance(), IDR_SFX_K_AF);
	sfxG_U.load(_Module.GetModuleInstance(), IDR_SFX_G_U);
	sfxK_GYASAT.load(_Module.GetModuleInstance(), IDR_SFX_K_GYASAT);
	sfxG_YBIHTDB.load(_Module.GetModuleInstance(), IDR_SFX_G_YBIHTDB);
	// Get a pointer to the script for this scene
	WorldDestruction4SceneScript = (unsigned char*)OASIS_loadScriptResource(IDR_WORLD_DESTRUCTION_4_SCENE_SCRIPT, hInst);
	// Place all actor images in array of actors (order MUST match the script editor!)
	// Last element MUST be NULL
	WorldDestruction4SceneActors[0]  = imgDestructionEarth;
	WorldDestruction4SceneActors[1]  = imgDestructionEarthDestroyed;
	WorldDestruction4SceneActors[2]  = imgDestructionUFOZoom01;
	WorldDestruction4SceneActors[3]  = imgDestructionUFOZoom02;
	WorldDestruction4SceneActors[4]  = imgDestructionUFOZoom03;
	WorldDestruction4SceneActors[5]  = imgDestructionUFOZoom04;
	WorldDestruction4SceneActors[6]  = imgDestructionUFOZoom05;
	WorldDestruction4SceneActors[7]  = imgDestructionUFOZoom06;
	WorldDestruction4SceneActors[8]  = imgDestructionUFOZoom07;
	WorldDestruction4SceneActors[9]  = imgDestructionUFOZoom08;
	WorldDestruction4SceneActors[10] = imgDestructionUFOZoom09;
	WorldDestruction4SceneActors[11] = imgDestructionUFOZoom10;
	WorldDestruction4SceneActors[12] = imgDestructionUFOZoom11;
	WorldDestruction4SceneActors[13] = imgDestructionUFOZoom12;
	WorldDestruction4SceneActors[14] = imgDestructionUFOZoom13;
	WorldDestruction4SceneActors[15] = imgDestructionUFOZoom14;
	WorldDestruction4SceneActors[16] = imgDestructionUFOZoom15;
	WorldDestruction4SceneActors[17] = imgExplosion_001;
	WorldDestruction4SceneActors[18] = imgExplosion_002;
	WorldDestruction4SceneActors[19] = imgExplosion_003;
	WorldDestruction4SceneActors[20] = imgExplosion_004;
	WorldDestruction4SceneActors[21] = imgExplosion_005;
	WorldDestruction4SceneActors[22] = NULL;
	// Place all audio actor sound fx in array of audio actors (order MUST match the script editor!)
	// No need to terminate array with NULL or -1
	WorldDestruction4SceneAudioActors[0] = sfxExplosion;
	WorldDestruction4SceneAudioActors[1] = sfxK_GIHTEWCOAS;
	WorldDestruction4SceneAudioActors[2] = sfxG_SWK;
	WorldDestruction4SceneAudioActors[3] = sfxK_TADTL;
	WorldDestruction4SceneAudioActors[4] = sfxG_IDGI;
	WorldDestruction4SceneAudioActors[5] = sfxK_AF;
	WorldDestruction4SceneAudioActors[6] = sfxG_U;
	WorldDestruction4SceneAudioActors[7] = sfxK_GYASAT;
	WorldDestruction4SceneAudioActors[8] = sfxG_YBIHTDB;
	// Place all text actor resource ID's in array of text actors (order MUST match the script editor!)
	// Last element MUST be -1
	WorldDestruction4SceneTextActors[0] = -1;
}


// ================================================================================================
// Releaser
// ================================================================================================
void releaserWorldDestruction4Scene() {
}


// ================================================================================================
// Scene Starter
// ================================================================================================
void SceneStarter_WorldDestruction4Scene() {
	OASIS_StartScene(WorldDestruction4SceneScript, WorldDestruction4SceneActors, WorldDestruction4SceneAudioActors, WorldDestruction4SceneTextActors);
}


// ================================================================================================
// Scene Ender
// ================================================================================================
void SceneEnder_WorldDestruction4Scene() {
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
void stylusDownWorldDestruction4Scene(Point stylusPoint) {
}

void stylusMoveWorldDestruction4Scene(Point stylusPoint) {
}

void stylusUpWorldDestruction4Scene(Point stylusPoint) {
	SceneEnder_WorldDestruction4Scene();
}

void keyDownWorldDestruction4Scene(int key) {
}

void keyUpWorldDestruction4Scene(int key) {
}
