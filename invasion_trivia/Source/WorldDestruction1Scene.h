
// ================================================================================================
// Globals
// ================================================================================================
Surface*			 WorldDestruction1SceneActors[25];
SoundFX 			 WorldDestruction1SceneAudioActors[12];
int            WorldDestruction1SceneTextActors[3];
unsigned char* WorldDestruction1SceneScript = NULL;
Surface*       imgDestructionEarth          = NULL;
Surface*       imgDestructionEarthDestroyed = NULL;
Surface*       imgDestructionUFOZoom01      = NULL;
Surface*       imgDestructionUFOZoom02      = NULL;
Surface*       imgDestructionUFOZoom03      = NULL;
Surface*       imgDestructionUFOZoom04      = NULL;
Surface*       imgDestructionUFOZoom05      = NULL;
Surface*       imgDestructionUFOZoom06      = NULL;
Surface*       imgDestructionUFOZoom07      = NULL;
Surface*       imgDestructionUFOZoom08      = NULL;
Surface*       imgDestructionUFOZoom09      = NULL;
Surface*       imgDestructionUFOZoom10      = NULL;
Surface*       imgDestructionUFOZoom11      = NULL;
Surface*       imgDestructionUFOZoom12      = NULL;
Surface*       imgDestructionUFOZoom13      = NULL;
Surface*       imgDestructionUFOZoom14      = NULL;
Surface*       imgDestructionUFOZoom15      = NULL;
SoundFX        sfxG_DTRTTWK;
SoundFX        sfxK_WGIGTDKOASA;
SoundFX        sfxG_WTK;
SoundFX        sfxK_IALTBD;
SoundFX        sfxG_YBYWSAWYAWTV;
SoundFX        sfxK_WWT;
SoundFX        sfxG_N;
SoundFX        sfxK_VW;
SoundFX        sfxK_FTPPALGOH;


// ================================================================================================
// Loader
// ================================================================================================
void loaderWorldDestruction1Scene(DisplayDevice* display) {
	// Load audio actor sound fx for this scene
	sfxG_DTRTTWK.load(_Module.GetModuleInstance(), IDR_SFX_G_DTRTTWK);
	sfxK_WGIGTDKOASA.load(_Module.GetModuleInstance(), IDR_SFX_K_WGIGTDKOASA);
	sfxG_WTK.load(_Module.GetModuleInstance(), IDR_SFX_G_WTK);
	sfxK_IALTBD.load(_Module.GetModuleInstance(), IDR_SFX_K_IALTBD);
	sfxG_YBYWSAWYAWTV.load(_Module.GetModuleInstance(), IDR_SFX_G_YBYWSAWYAWTV);
	sfxK_WWT.load(_Module.GetModuleInstance(), IDR_SFX_K_WWT);
	sfxG_N.load(_Module.GetModuleInstance(), IDR_SFX_G_N);
	sfxK_VW.load(_Module.GetModuleInstance(), IDR_SFX_K_VW);
	sfxK_FTPPALGOH.load(_Module.GetModuleInstance(), IDR_SFX_K_FTPPALGOH);
	// Load actor images for this scene and set required transparency masks
	imgDestructionEarth = LoadImage(display, IDR_DESTRUCTION_EARTH);
	imgDestructionEarthDestroyed = LoadImage(display, IDR_DESTRUCTION_EARTH_DESTROYED);
	imgDestructionUFOZoom01 = LoadImage(display, IDR_DESTRUCTION_UFO_ZOOM_01);
	imgDestructionUFOZoom01->SetColorMask(Color(255, 255, 255));
	imgDestructionUFOZoom02 = LoadImage(display, IDR_DESTRUCTION_UFO_ZOOM_02);
	imgDestructionUFOZoom02->SetColorMask(Color(255, 255, 255));
	imgDestructionUFOZoom03 = LoadImage(display, IDR_DESTRUCTION_UFO_ZOOM_03);
	imgDestructionUFOZoom03->SetColorMask(Color(255, 255, 255));
	imgDestructionUFOZoom04 = LoadImage(display, IDR_DESTRUCTION_UFO_ZOOM_04);
	imgDestructionUFOZoom04->SetColorMask(Color(255, 255, 255));
	imgDestructionUFOZoom05 = LoadImage(display, IDR_DESTRUCTION_UFO_ZOOM_05);
	imgDestructionUFOZoom05->SetColorMask(Color(255, 255, 255));
	imgDestructionUFOZoom06 = LoadImage(display, IDR_DESTRUCTION_UFO_ZOOM_06);
	imgDestructionUFOZoom06->SetColorMask(Color(255, 255, 255));
	imgDestructionUFOZoom07 = LoadImage(display, IDR_DESTRUCTION_UFO_ZOOM_07);
	imgDestructionUFOZoom07->SetColorMask(Color(255, 255, 255));
	imgDestructionUFOZoom08 = LoadImage(display, IDR_DESTRUCTION_UFO_ZOOM_08);
	imgDestructionUFOZoom08->SetColorMask(Color(255, 255, 255));
	imgDestructionUFOZoom09 = LoadImage(display, IDR_DESTRUCTION_UFO_ZOOM_09);
	imgDestructionUFOZoom09->SetColorMask(Color(255, 255, 255));
	imgDestructionUFOZoom10 = LoadImage(display, IDR_DESTRUCTION_UFO_ZOOM_10);
	imgDestructionUFOZoom10->SetColorMask(Color(255, 255, 255));
	imgDestructionUFOZoom11 = LoadImage(display, IDR_DESTRUCTION_UFO_ZOOM_11);
	imgDestructionUFOZoom11->SetColorMask(Color(255, 255, 255));
	imgDestructionUFOZoom12 = LoadImage(display, IDR_DESTRUCTION_UFO_ZOOM_12);
	imgDestructionUFOZoom12->SetColorMask(Color(255, 255, 255));
	imgDestructionUFOZoom13 = LoadImage(display, IDR_DESTRUCTION_UFO_ZOOM_13);
	imgDestructionUFOZoom13->SetColorMask(Color(255, 255, 255));
	imgDestructionUFOZoom14 = LoadImage(display, IDR_DESTRUCTION_UFO_ZOOM_14);
	imgDestructionUFOZoom14->SetColorMask(Color(255, 255, 255));
	imgDestructionUFOZoom15 = LoadImage(display, IDR_DESTRUCTION_UFO_ZOOM_15);
	imgDestructionUFOZoom15->SetColorMask(Color(255, 255, 255));
	// Get a pointer to the script for this scene
	WorldDestruction1SceneScript = (unsigned char*)OASIS_loadScriptResource(IDR_WORLD_DESTRUCTION_1_SCENE_SCRIPT, hInst);
	// Place all actor images in array of actors (order MUST match the script editor!)
	// Last element MUST be NULL
	WorldDestruction1SceneActors[0]  = imgDestructionEarth;
	WorldDestruction1SceneActors[1]  = imgDestructionEarthDestroyed;
	WorldDestruction1SceneActors[2]  = imgDestructionUFOZoom01;
	WorldDestruction1SceneActors[3]  = imgDestructionUFOZoom02;
	WorldDestruction1SceneActors[4]  = imgDestructionUFOZoom03;
	WorldDestruction1SceneActors[5]  = imgDestructionUFOZoom04;
	WorldDestruction1SceneActors[6]  = imgDestructionUFOZoom05;
	WorldDestruction1SceneActors[7]  = imgDestructionUFOZoom06;
	WorldDestruction1SceneActors[8]  = imgDestructionUFOZoom07;
	WorldDestruction1SceneActors[9]  = imgDestructionUFOZoom08;
	WorldDestruction1SceneActors[10] = imgDestructionUFOZoom09;
	WorldDestruction1SceneActors[11] = imgDestructionUFOZoom10;
	WorldDestruction1SceneActors[12] = imgDestructionUFOZoom11;
	WorldDestruction1SceneActors[13] = imgDestructionUFOZoom12;
	WorldDestruction1SceneActors[14] = imgDestructionUFOZoom13;
	WorldDestruction1SceneActors[15] = imgDestructionUFOZoom14;
	WorldDestruction1SceneActors[16] = imgDestructionUFOZoom15;
	WorldDestruction1SceneActors[17] = imgExplosion_001;
	WorldDestruction1SceneActors[18] = imgExplosion_002;
	WorldDestruction1SceneActors[19] = imgExplosion_003;
	WorldDestruction1SceneActors[20] = imgExplosion_004;
	WorldDestruction1SceneActors[21] = imgExplosion_005;
	WorldDestruction1SceneActors[22] = NULL;
	// Place all audio actor sound fx in array of audio actors (order MUST match the script editor!)
	// No need to terminate array with NULL or -1
	WorldDestruction1SceneAudioActors[0] = sfxExplosion;
	WorldDestruction1SceneAudioActors[1] = sfxG_DTRTTWK;
	WorldDestruction1SceneAudioActors[2] = sfxK_WGIGTDKOASA;
	WorldDestruction1SceneAudioActors[3] = sfxG_WTK;
	WorldDestruction1SceneAudioActors[4] = sfxK_IALTBD;
	WorldDestruction1SceneAudioActors[5] = sfxG_YBYWSAWYAWTV;
	WorldDestruction1SceneAudioActors[6] = sfxK_WWT;
	WorldDestruction1SceneAudioActors[7] = sfxG_N;
	WorldDestruction1SceneAudioActors[8] = sfxK_VW;
	WorldDestruction1SceneAudioActors[9] = sfxK_FTPPALGOH;
	// Place all text actor resource ID's in array of text actors (order MUST match the script editor!)
	// Last element MUST be -1
	WorldDestruction1SceneTextActors[0] = -1;
}


// ================================================================================================
// Releaser
// ================================================================================================
void releaserWorldDestruction1Scene() {
	delete imgDestructionEarth;
	delete imgDestructionEarthDestroyed;
	delete imgDestructionUFOZoom01;
	delete imgDestructionUFOZoom02;
	delete imgDestructionUFOZoom03;
	delete imgDestructionUFOZoom04;
	delete imgDestructionUFOZoom05;
	delete imgDestructionUFOZoom06;
	delete imgDestructionUFOZoom07;
	delete imgDestructionUFOZoom08;
	delete imgDestructionUFOZoom09;
	delete imgDestructionUFOZoom10;
	delete imgDestructionUFOZoom11;
	delete imgDestructionUFOZoom12;
	delete imgDestructionUFOZoom13;
	delete imgDestructionUFOZoom14;
	delete imgDestructionUFOZoom15;
}


// ================================================================================================
// Scene Starter
// ================================================================================================
void SceneStarter_WorldDestruction1Scene() {
	OASIS_StartScene(WorldDestruction1SceneScript, WorldDestruction1SceneActors, WorldDestruction1SceneAudioActors, WorldDestruction1SceneTextActors);
}


// ================================================================================================
// Scene Ender
// ================================================================================================
void SceneEnder_WorldDestruction1Scene() {
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
void stylusDownWorldDestruction1Scene(Point stylusPoint) {
}

void stylusMoveWorldDestruction1Scene(Point stylusPoint) {
}

void stylusUpWorldDestruction1Scene(Point stylusPoint) {
	SceneEnder_WorldDestruction1Scene();
}

void keyDownWorldDestruction1Scene(int key) {
}

void keyUpWorldDestruction1Scene(int key) {
}
