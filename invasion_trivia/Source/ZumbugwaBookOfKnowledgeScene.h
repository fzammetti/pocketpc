
// ================================================================================================
// Globals
// ================================================================================================
Surface*			 BookOfKnowledgeSceneActors[9];
SoundFX 			 BookOfKnowledgeSceneAudioActors[3];
int						 BookOfKnowledgeSceneTextActors[3];
unsigned char* BookOfKnowledgeSceneScript = NULL;
Surface* imgBOKBackground									= NULL;
Surface* imgBOK1													= NULL;
Surface* imgBOK2													= NULL;
Surface* imgBOK3													= NULL;
Surface* imgBOK4													= NULL;
Surface* imgBOK5													= NULL;
SoundFX  sfxHarp;


// ================================================================================================
// Loader
// ================================================================================================
void loaderBookOfKnowledgeScene(DisplayDevice* display) {
	// Load audio actor sound fx for this scene
	sfxHarp.load(_Module.GetModuleInstance(), IDR_SFX_HARP);
	// Load actor images for this scene and set required transparency masks
	imgBOKBackground = LoadImage(display, IDR_BOK_BACKGROUND);
	imgBOK1 = LoadImage(display, IDR_BOK_1);
	imgBOK1->SetColorMask(Color(255, 255, 255));
	imgBOK2 = LoadImage(display, IDR_BOK_2);
	imgBOK2->SetColorMask(Color(255, 255, 255));
	imgBOK3 = LoadImage(display, IDR_BOK_3);
	imgBOK3->SetColorMask(Color(255, 255, 255));
	imgBOK4 = LoadImage(display, IDR_BOK_4);
	imgBOK4->SetColorMask(Color(255, 255, 255));
	imgBOK5 = LoadImage(display, IDR_BOK_5);
	imgBOK5->SetColorMask(Color(255, 255, 255));
	// Place pointers to each image in our array of actors
	BookOfKnowledgeSceneActors[0]  = imgBOKBackground;
	BookOfKnowledgeSceneActors[1]  = imgBOK1;
	BookOfKnowledgeSceneActors[2]  = imgBOK2;
	BookOfKnowledgeSceneActors[3]  = imgBOK3;
	BookOfKnowledgeSceneActors[4]  = imgBOK4;
	BookOfKnowledgeSceneActors[5]  = imgBOK5;
	BookOfKnowledgeSceneActors[6]	 = NULL;
	// Get a pointer to the script for this scene
	BookOfKnowledgeSceneScript = (unsigned char*)OASIS_loadScriptResource(IDR_BOOK_OF_KNOWLEDGE_SCENE_SCRIPT, hInst);
	// Place all audio actor sound fx in array of audio actors (order MUST match the script editor!)
	// No need to terminate array with NULL or -1
	BookOfKnowledgeSceneAudioActors[0] = sfxHarp;
	// Do the text actors too
	BookOfKnowledgeSceneTextActors[0] = -1;
}


// ================================================================================================
// Releaser
// ================================================================================================
void releaserBookOfKnowledgeScene() {
	delete imgBOKBackground;
	delete imgBOK1;
	delete imgBOK2;
	delete imgBOK3;
	delete imgBOK4;
	delete imgBOK5;
}


// ================================================================================================
// Scene Starter
// ================================================================================================
void SceneStarter_BookOfKnowledgeScene() {
	OASIS_StartScene(BookOfKnowledgeSceneScript, BookOfKnowledgeSceneActors, BookOfKnowledgeSceneAudioActors, BookOfKnowledgeSceneTextActors);
}


// ================================================================================================
// Scene Ender
// ================================================================================================
void SceneEnder_BookOfKnowledgeScene() {
	OASIS_EndScene();
	game.currentScreen = csPointLevelsScreen;
}


// ================================================================================================
// Event Handlers
// ================================================================================================
void stylusDownBookOfKnowledgeScene(Point stylusPoint) {
}

void stylusMoveBookOfKnowledgeScene(Point stylusPoint) {
}

void stylusUpBookOfKnowledgeScene(Point stylusPoint) {
	SceneEnder_BookOfKnowledgeScene();
}

void keyDownBookOfKnowledgeScene(int key) {
}

void keyUpBookOfKnowledgeScene(int key) {
}
