
// ================================================================================================
// Globals
// ================================================================================================
Surface*			 WorldDestruction3SceneActors[25];
SoundFX 			 WorldDestruction3SceneAudioActors[11];
int						 WorldDestruction3SceneTextActors[3];
unsigned char* WorldDestruction3SceneScript = NULL;
SoundFX				 sfxG_WGRFAWLSK;
SoundFX				 sfxK_GSITYEDPALTM;
SoundFX				 sfxG_WIDTPIMWK;
SoundFX				 sfxK_OISG;
SoundFX				 sfxG_WTYVMK;
SoundFX				 sfxK_YQWGNF;


// ================================================================================================
// Loader
// ================================================================================================
void loaderWorldDestruction3Scene(DisplayDevice* display) {
	// Load audio actor sound fx for this scene
	sfxG_WGRFAWLSK.load(_Module.GetModuleInstance(), IDR_SFX_G_WGRFAWLSK);
	sfxK_OISG.load(_Module.GetModuleInstance(), IDR_SFX_K_OISG);
	sfxG_WIDTPIMWK.load(_Module.GetModuleInstance(), IDR_SFX_G_WIDTPIMWK);
	sfxK_GSITYEDPALTM.load(_Module.GetModuleInstance(), IDR_SFX_K_GSITYEDPALTM);
	sfxK_YQWGNF.load(_Module.GetModuleInstance(), IDR_SFX_K_YQWGNF);
	sfxG_WTYVMK.load(_Module.GetModuleInstance(), IDR_SFX_G_WTYVMK);
	// Get a pointer to the script for this scene
	WorldDestruction3SceneScript = (unsigned char*)OASIS_loadScriptResource(IDR_WORLD_DESTRUCTION_3_SCENE_SCRIPT, hInst);
	// Place all actor images in array of actors (order MUST match the script editor!)
	// Last element MUST be NULL
	WorldDestruction3SceneActors[0]  = imgDestructionEarth;
	WorldDestruction3SceneActors[1]  = imgDestructionEarthDestroyed;
	WorldDestruction3SceneActors[2]  = imgDestructionUFOZoom01;
	WorldDestruction3SceneActors[3]  = imgDestructionUFOZoom02;
	WorldDestruction3SceneActors[4]  = imgDestructionUFOZoom03;
	WorldDestruction3SceneActors[5]  = imgDestructionUFOZoom04;
	WorldDestruction3SceneActors[6]  = imgDestructionUFOZoom05;
	WorldDestruction3SceneActors[7]  = imgDestructionUFOZoom06;
	WorldDestruction3SceneActors[8]  = imgDestructionUFOZoom07;
	WorldDestruction3SceneActors[9]  = imgDestructionUFOZoom08;
	WorldDestruction3SceneActors[10] = imgDestructionUFOZoom09;
	WorldDestruction3SceneActors[11] = imgDestructionUFOZoom10;
	WorldDestruction3SceneActors[12] = imgDestructionUFOZoom11;
	WorldDestruction3SceneActors[13] = imgDestructionUFOZoom12;
	WorldDestruction3SceneActors[14] = imgDestructionUFOZoom13;
	WorldDestruction3SceneActors[15] = imgDestructionUFOZoom14;
	WorldDestruction3SceneActors[16] = imgDestructionUFOZoom15;
	WorldDestruction3SceneActors[17] = imgExplosion_001;
	WorldDestruction3SceneActors[18] = imgExplosion_002;
	WorldDestruction3SceneActors[19] = imgExplosion_003;
	WorldDestruction3SceneActors[20] = imgExplosion_004;
	WorldDestruction3SceneActors[21] = imgExplosion_005;
	WorldDestruction3SceneActors[22] = NULL;
	// Place all audio actor sound fx in array of audio actors (order MUST match the script editor!)
	// No need to terminate array with NULL or -1
	WorldDestruction3SceneAudioActors[0] = sfxExplosion;
	WorldDestruction3SceneAudioActors[1] = sfxG_IWUTECKTIGBF;
	WorldDestruction3SceneAudioActors[2] = sfxK_YILTSOBHFITN;
	WorldDestruction3SceneAudioActors[3] = sfxG_WGRFAWLSK;
	WorldDestruction3SceneAudioActors[4] = sfxK_GSITYEDPALTM;
	WorldDestruction3SceneAudioActors[5] = sfxG_WIDTPIMWK;
	WorldDestruction3SceneAudioActors[6] = sfxK_OISG;
	WorldDestruction3SceneAudioActors[7] = sfxG_WTYVMK;
	WorldDestruction3SceneAudioActors[8] = sfxK_YQWGNF;
	// Place all text actor resource ID's in array of text actors (order MUST match the script editor!)
	// Last element MUST be -1
	WorldDestruction3SceneTextActors[0] = -1;
}


// ================================================================================================
// Releaser
// ================================================================================================
void releaserWorldDestruction3Scene() {
}


// ================================================================================================
// Scene Starter
// ================================================================================================
void SceneStarter_WorldDestruction3Scene() {
	OASIS_StartScene(WorldDestruction3SceneScript, WorldDestruction3SceneActors, WorldDestruction3SceneAudioActors, WorldDestruction3SceneTextActors);
}


// ================================================================================================
// Scene Ender
// ================================================================================================
void SceneEnder_WorldDestruction3Scene() {
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
void stylusDownWorldDestruction3Scene(Point stylusPoint) {
}

void stylusMoveWorldDestruction3Scene(Point stylusPoint) {
}

void stylusUpWorldDestruction3Scene(Point stylusPoint) {
	SceneEnder_WorldDestruction3Scene();
}

void keyDownWorldDestruction3Scene(int key) {
}

void keyUpWorldDestruction3Scene(int key) {
}
