
// ================================================================================================
// Globals
// ================================================================================================
Surface*			 ParisDestructionSceneActors[17];
SoundFX 			 ParisDestructionSceneAudioActors[7];
int						 ParisDestructionSceneTextActors[3];
unsigned char* ParisDestructionSceneScript = NULL;
Surface*			 imgParisLiveCity						 = NULL;
Surface*       imgParisDeadCity						 = NULL;
Surface*			 imgUFO_001									 = NULL;
Surface*			 imgUFO_002									 = NULL;
Surface*			 imgUFO_003									 = NULL;
Surface*			 imgUFO_004									 = NULL;
Surface*			 imgExplosion_001						 = NULL;
Surface*			 imgExplosion_002						 = NULL;
Surface*			 imgExplosion_003						 = NULL;
Surface*			 imgExplosion_004						 = NULL;
Surface*			 imgExplosion_005						 = NULL;
Surface*			 imgLASER_001								 = NULL;
Surface*			 imgLASER_002								 = NULL;
Surface*			 imgLASER_003								 = NULL;
SoundFX 			 sfxUFOHum;
SoundFX 			 sfxLASER;
SoundFX 			 sfxExplosion;
SoundFX 			 sfxParisWords;
SoundFX				 sfxBounceSound;


// ================================================================================================
// Loader
// ================================================================================================
void loaderDestructionParisScene(DisplayDevice* display) {
	// Load all images for this scene and set color masks
	imgParisLiveCity = LoadImage(display, IDR_LIVECITY_PARIS);
	imgParisDeadCity = LoadImage(display, IDR_DEADCITY_PARIS);
	imgUFO_001 = LoadImage(display, IDR_UFO_001);
	imgUFO_001->SetColorMask(Color(255, 255, 255));
	imgUFO_002 = LoadImage(display, IDR_UFO_002);
	imgUFO_002->SetColorMask(Color(255, 255, 255));
	imgUFO_003 = LoadImage(display, IDR_UFO_003);
	imgUFO_003->SetColorMask(Color(255, 255, 255));
	imgUFO_004 = LoadImage(display, IDR_UFO_004);
	imgUFO_004->SetColorMask(Color(255, 255, 255));
	imgExplosion_001 = LoadImage(display, IDR_EXPLOSION_001);
	imgExplosion_001->SetColorMask(Color(255, 255, 255));
	imgExplosion_002 = LoadImage(display, IDR_EXPLOSION_002);
	imgExplosion_002->SetColorMask(Color(255, 255, 255));
	imgExplosion_003 = LoadImage(display, IDR_EXPLOSION_003);
	imgExplosion_003->SetColorMask(Color(255, 255, 255));
	imgExplosion_004 = LoadImage(display, IDR_EXPLOSION_004);
	imgExplosion_004->SetColorMask(Color(255, 255, 255));
	imgExplosion_005 = LoadImage(display, IDR_EXPLOSION_005);
	imgExplosion_005->SetColorMask(Color(255, 255, 255));
	imgLASER_001 = LoadImage(display, IDR_LASER_001);
	imgLASER_001->SetColorMask(Color(255, 255, 255));
	imgLASER_002 = LoadImage(display, IDR_LASER_002);
	imgLASER_002->SetColorMask(Color(255, 255, 255));
	imgLASER_003 = LoadImage(display, IDR_LASER_003);
	imgLASER_003->SetColorMask(Color(255, 255, 255));
	// Load all wave files for this scene
	sfxUFOHum.load(_Module.GetModuleInstance(), IDR_SFX_UFO_HUM);
	sfxLASER.load(_Module.GetModuleInstance(), IDR_SFX_LASER);
	sfxExplosion.load(_Module.GetModuleInstance(), IDR_SFX_EXPLOSION);
	sfxParisWords.load(_Module.GetModuleInstance(), IDR_SFX_DESTRUCTION_WORDS_PARIS);
	sfxBounceSound.load(_Module.GetModuleInstance(), IDR_SFX_BOUNCE_SOUND);
	// Place pointers to each image in our array of actors
	ParisDestructionSceneActors[0]	= imgParisLiveCity;
	ParisDestructionSceneActors[1]	= imgUFO_001;
	ParisDestructionSceneActors[2]	= imgUFO_002;
	ParisDestructionSceneActors[3]	= imgUFO_003;
	ParisDestructionSceneActors[4]	= imgUFO_004;
	ParisDestructionSceneActors[5]	= imgExplosion_001;
	ParisDestructionSceneActors[6]	= imgExplosion_002;
	ParisDestructionSceneActors[7]	= imgExplosion_003;
	ParisDestructionSceneActors[8]	= imgExplosion_004;
	ParisDestructionSceneActors[9]	= imgExplosion_005;
	ParisDestructionSceneActors[10] = imgLASER_001;
	ParisDestructionSceneActors[11] = imgLASER_002;
	ParisDestructionSceneActors[12] = imgLASER_003;
	ParisDestructionSceneActors[13] = imgParisDeadCity;
	ParisDestructionSceneActors[14] = NULL;
	// Get a pointer to the script for this scene
	ParisDestructionSceneScript = (unsigned char*)OASIS_loadScriptResource(IDR_DESTRUCTION_PARIS_SCENE_SCRIPT, hInst);
	// Load the audio actors array with the SoundFX loaded above
	ParisDestructionSceneAudioActors[0] = sfxUFOHum;
	ParisDestructionSceneAudioActors[1] = sfxLASER;
	ParisDestructionSceneAudioActors[2] = sfxExplosion;
	ParisDestructionSceneAudioActors[3] = sfxParisWords;
	ParisDestructionSceneAudioActors[4] = sfxBounceSound;
	// Do the text actors too
	ParisDestructionSceneTextActors[0] = -1;
}


// ================================================================================================
// Releaser
// ================================================================================================
void releaserDestructionParisScene() {
	delete imgParisLiveCity;
	delete imgParisDeadCity;
	delete imgUFO_001;
	delete imgUFO_002;
	delete imgUFO_003;
	delete imgUFO_004;
	delete imgExplosion_001;
	delete imgExplosion_002;
	delete imgExplosion_003;
	delete imgExplosion_004;
	delete imgExplosion_005;
	delete imgLASER_001;
	delete imgLASER_002;
	delete imgLASER_003;
}


// ================================================================================================
// Scene Starter
// ================================================================================================
void SceneStarter_DestructionParisScene() {
	OASIS_StartScene(ParisDestructionSceneScript, ParisDestructionSceneActors, ParisDestructionSceneAudioActors, ParisDestructionSceneTextActors);
}


// ================================================================================================
// Scene Ender
// ================================================================================================
void SceneEnder_DestructionParisScene() {
	OASIS_EndScene();
	game.currentScreen = csPointLevelsScreen;
}


// ================================================================================================
// Event Handlers
// ================================================================================================
void stylusDownDestructionParisScene(Point stylusPoint) {
}

void stylusMoveDestructionParisScene(Point stylusPoint) {
}

void stylusUpDestructionParisScene(Point stylusPoint) {
	SceneEnder_DestructionParisScene();
}

void keyDownDestructionParisScene(int key) {
}

void keyUpDestructionParisScene(int key) {
}
