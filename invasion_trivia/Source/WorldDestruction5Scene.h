
// ================================================================================================
// Globals
// ================================================================================================
Surface*			 WorldDestruction5SceneActors[25];
SoundFX 			 WorldDestruction5SceneAudioActors[10];
int						 WorldDestruction5SceneTextActors[3];
unsigned char* WorldDestruction5SceneScript = NULL;
SoundFX				 sfxK_IGMTPBMG;
SoundFX				 sfxG_YMTK;
SoundFX				 sfxK_AYCG;
SoundFX				 sfxG_SWIIAMAANATFEWAIAV;
SoundFX				 sfxK_RBIWJA;
SoundFX				 sfxG_YNSACFAK;
SoundFX				 sfxK_YCR;


// ================================================================================================
// Loader
// ================================================================================================
void loaderWorldDestruction5Scene(DisplayDevice* display) {
	// Load audio actor sound fx for this scene
	sfxK_IGMTPBMG.load(_Module.GetModuleInstance(), IDR_SFX_K_IGMTPBMG);
	sfxG_YMTK.load(_Module.GetModuleInstance(), IDR_SFX_G_YMTK);
	sfxK_AYCG.load(_Module.GetModuleInstance(), IDR_SFX_K_AYCG);
	sfxG_SWIIAMAANATFEWAIAV.load(_Module.GetModuleInstance(), IDR_SFX_G_SWIIAMAANATFEWAIAV);
	sfxK_RBIWJA.load(_Module.GetModuleInstance(), IDR_SFX_K_RBIWJA);
	sfxG_YNSACFAK.load(_Module.GetModuleInstance(), IDR_SFX_G_YNSACFAK);
	sfxK_YCR.load(_Module.GetModuleInstance(), IDR_SFX_K_YCR);
	// Get a pointer to the script for this scene
	WorldDestruction5SceneScript = (unsigned char*)OASIS_loadScriptResource(IDR_WORLD_DESTRUCTION_5_SCENE_SCRIPT, hInst);
	// Place all actor images in array of actors (order MUST match the script editor!)
	// Last element MUST be NULL
	WorldDestruction5SceneActors[0]  = imgDestructionEarth;
	WorldDestruction5SceneActors[1]  = imgDestructionEarthDestroyed;
	WorldDestruction5SceneActors[2]  = imgDestructionUFOZoom01;
	WorldDestruction5SceneActors[3]  = imgDestructionUFOZoom02;
	WorldDestruction5SceneActors[4]  = imgDestructionUFOZoom03;
	WorldDestruction5SceneActors[5]  = imgDestructionUFOZoom04;
	WorldDestruction5SceneActors[6]  = imgDestructionUFOZoom05;
	WorldDestruction5SceneActors[7]  = imgDestructionUFOZoom06;
	WorldDestruction5SceneActors[8]  = imgDestructionUFOZoom07;
	WorldDestruction5SceneActors[9]  = imgDestructionUFOZoom08;
	WorldDestruction5SceneActors[10] = imgDestructionUFOZoom09;
	WorldDestruction5SceneActors[11] = imgDestructionUFOZoom10;
	WorldDestruction5SceneActors[12] = imgDestructionUFOZoom11;
	WorldDestruction5SceneActors[13] = imgDestructionUFOZoom12;
	WorldDestruction5SceneActors[14] = imgDestructionUFOZoom13;
	WorldDestruction5SceneActors[15] = imgDestructionUFOZoom14;
	WorldDestruction5SceneActors[16] = imgDestructionUFOZoom15;
	WorldDestruction5SceneActors[17] = imgExplosion_001;
	WorldDestruction5SceneActors[18] = imgExplosion_002;
	WorldDestruction5SceneActors[19] = imgExplosion_003;
	WorldDestruction5SceneActors[20] = imgExplosion_004;
	WorldDestruction5SceneActors[21] = imgExplosion_005;
	WorldDestruction5SceneActors[22] = NULL;
	// Place all audio actor sound fx in array of audio actors (order MUST match the script editor!)
	// No need to terminate array with NULL or -1
	WorldDestruction5SceneAudioActors[0] = sfxExplosion;
	WorldDestruction5SceneAudioActors[1] = sfxK_IGMTPBMG;
	WorldDestruction5SceneAudioActors[2] = sfxG_YMTK;
	WorldDestruction5SceneAudioActors[3] = sfxK_AYCG;
	WorldDestruction5SceneAudioActors[4] = sfxG_SWIIAMAANATFEWAIAV;
	WorldDestruction5SceneAudioActors[5] = sfxK_RBIWJA;
	WorldDestruction5SceneAudioActors[6] = sfxG_YNSACFAK;
	WorldDestruction5SceneAudioActors[7] = sfxK_YCR;
	// Place all text actor resource ID's in array of text actors (order MUST match the script editor!)
	// Last element MUST be -1
	WorldDestruction5SceneTextActors[0] = -1;
}


// ================================================================================================
// Releaser
// ================================================================================================
void releaserWorldDestruction5Scene() {
}


// ================================================================================================
// Scene Starter
// ================================================================================================
void SceneStarter_WorldDestruction5Scene() {
	OASIS_StartScene(WorldDestruction5SceneScript, WorldDestruction5SceneActors, WorldDestruction5SceneAudioActors, WorldDestruction5SceneTextActors);
}


// ================================================================================================
// Scene Ender
// ================================================================================================
void SceneEnder_WorldDestruction5Scene() {
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
void stylusDownWorldDestruction5Scene(Point stylusPoint) {
}

void stylusMoveWorldDestruction5Scene(Point stylusPoint) {
}

void stylusUpWorldDestruction5Scene(Point stylusPoint) {
	SceneEnder_WorldDestruction5Scene();
}

void keyDownWorldDestruction5Scene(int key) {
}

void keyUpWorldDestruction5Scene(int key) {
}
