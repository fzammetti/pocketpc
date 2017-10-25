
// ================================================================================================
// Globals
// ================================================================================================
Surface*			 TitleSceneActors[4];
SoundFX 			 TitleSceneAudioActors[3];
int						 TitleSceneTextActors[3];
unsigned char* TitleSceneScript					= NULL;
Surface*			 imgTitleSceneBackground  = NULL;
Module				 ThemeMusic;


// ================================================================================================
// Loader
// ================================================================================================
void loaderTitleScene(DisplayDevice* display) {
	// Load all images for this scene and set color masks
	imgTitleSceneBackground = LoadImage(display, IDR_TITLE_SCENE_BACKGROUND);
	// Place pointers to each image in our array of actors
	TitleSceneActors[0] = imgTitleSceneBackground;
	TitleSceneActors[1] = NULL;
	// Get a pointer to the script for this scene
	TitleSceneScript = (unsigned char*)OASIS_loadScriptResource(IDR_TITLE_SCENE_SCRIPT, hInst);
	// Do the text actors too
	TitleSceneTextActors[0] = -1;
	ThemeMusic.load(_Module.GetModuleInstance(), IDR_THEME_MUSIC);
	ThemeMusic.setVolume(24);
	ThemeMusic.setLoop(true);
}


// ================================================================================================
// Releaser
// ================================================================================================
void releaserTitleScene() {
	delete imgTitleSceneBackground;
}


// ================================================================================================
// Scene Starter
// ================================================================================================
void SceneStarter_TitleScene() {
	OASIS_StartScene(TitleSceneScript, TitleSceneActors, TitleSceneAudioActors, TitleSceneTextActors);
	game.itPlayThemeMusic();
}


// ================================================================================================
// Scene Ender
// ================================================================================================
void SceneEnder_TitleScene() {
	OASIS_EndScene();
	game.currentScreen = csMainMenuScreen;
}


// ================================================================================================
// Event Handlers
// ================================================================================================
void stylusDownTitleScene(Point stylusPoint) {
}

void stylusMoveTitleScene(Point stylusPoint) {
}

void stylusUpTitleScene(Point stylusPoint) {
	SceneEnder_TitleScene();
}

void keyDownTitleScene(int key) {
}

void keyUpTitleScene(int key) {
}
