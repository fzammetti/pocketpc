
// ================================================================================================
// Globals
// ================================================================================================
Surface*			 MatterAntimatterSceneActors[32];
SoundFX 			 MatterAntimatterSceneAudioActors[3];
int						 MatterAntimatterSceneTextActors[3];
unsigned char* MatterAntimatterSceneScript = NULL;
Surface*			 imgAtom_01									 = NULL;
Surface*			 imgAtom_02									 = NULL;
Surface*			 imgAtom_03									 = NULL;
Surface*			 imgAtom_04									 = NULL;
Surface*			 imgAtom_05									 = NULL;
Surface*			 imgAtom_06									 = NULL;
Surface*			 imgAtom_07									 = NULL;
Surface*			 imgAtom_08									 = NULL;
Surface*			 imgAtom_09									 = NULL;
Surface*			 imgAtom_10									 = NULL;
Surface*			 imgAtom_11									 = NULL;
Surface*			 imgAtom_12									 = NULL;
Surface*			 imgAntiAtom_01							 = NULL;
Surface*			 imgAntiAtom_02							 = NULL;
Surface*			 imgAntiAtom_03							 = NULL;
Surface*			 imgAntiAtom_04							 = NULL;
Surface*			 imgAntiAtom_05							 = NULL;
Surface*			 imgAntiAtom_06							 = NULL;
Surface*			 imgAntiAtom_07							 = NULL;
Surface*			 imgAntiAtom_08							 = NULL;
Surface*			 imgAntiAtom_09							 = NULL;
Surface*			 imgAntiAtom_10							 = NULL;
Surface*			 imgAntiAtom_11							 = NULL;
Surface*			 imgAntiAtom_12							 = NULL;


// ================================================================================================
// Loader
// ================================================================================================
void loaderMatterAntimatterScene(DisplayDevice* display) {
	// Load actor images for this scene and set required transparency masks
	imgAtom_01 = LoadImage(display, IDR_ATOM_01);
	imgAtom_01->SetColorMask(Color(255, 255, 255));
	imgAtom_02 = LoadImage(display, IDR_ATOM_02);
	imgAtom_02->SetColorMask(Color(255, 255, 255));
	imgAtom_03 = LoadImage(display, IDR_ATOM_03);
	imgAtom_03->SetColorMask(Color(255, 255, 255));
	imgAtom_04 = LoadImage(display, IDR_ATOM_04);
	imgAtom_04->SetColorMask(Color(255, 255, 255));
	imgAtom_05 = LoadImage(display, IDR_ATOM_05);
	imgAtom_05->SetColorMask(Color(255, 255, 255));
	imgAtom_06 = LoadImage(display, IDR_ATOM_06);
	imgAtom_06->SetColorMask(Color(255, 255, 255));
	imgAtom_07 = LoadImage(display, IDR_ATOM_07);
	imgAtom_07->SetColorMask(Color(255, 255, 255));
	imgAtom_08 = LoadImage(display, IDR_ATOM_08);
	imgAtom_08->SetColorMask(Color(255, 255, 255));
	imgAtom_09 = LoadImage(display, IDR_ATOM_09);
	imgAtom_09->SetColorMask(Color(255, 255, 255));
	imgAtom_10 = LoadImage(display, IDR_ATOM_10);
	imgAtom_10->SetColorMask(Color(255, 255, 255));
	imgAtom_11 = LoadImage(display, IDR_ATOM_11);
	imgAtom_11->SetColorMask(Color(255, 255, 255));
	imgAtom_12 = LoadImage(display, IDR_ATOM_12);
	imgAtom_12->SetColorMask(Color(255, 255, 255));
	imgAntiAtom_01 = LoadImage(display, IDR_ANTIATOM_01);
	imgAntiAtom_01->SetColorMask(Color(255, 255, 255));
	imgAntiAtom_02 = LoadImage(display, IDR_ANTIATOM_02);
	imgAntiAtom_02->SetColorMask(Color(255, 255, 255));
	imgAntiAtom_03 = LoadImage(display, IDR_ANTIATOM_03);
	imgAntiAtom_03->SetColorMask(Color(255, 255, 255));
	imgAntiAtom_04 = LoadImage(display, IDR_ANTIATOM_04);
	imgAntiAtom_04->SetColorMask(Color(255, 255, 255));
	imgAntiAtom_05 = LoadImage(display, IDR_ANTIATOM_05);
	imgAntiAtom_05->SetColorMask(Color(255, 255, 255));
	imgAntiAtom_06 = LoadImage(display, IDR_ANTIATOM_06);
	imgAntiAtom_06->SetColorMask(Color(255, 255, 255));
	imgAntiAtom_07 = LoadImage(display, IDR_ANTIATOM_07);
	imgAntiAtom_07->SetColorMask(Color(255, 255, 255));
	imgAntiAtom_08 = LoadImage(display, IDR_ANTIATOM_08);
	imgAntiAtom_08->SetColorMask(Color(255, 255, 255));
	imgAntiAtom_09 = LoadImage(display, IDR_ANTIATOM_09);
	imgAntiAtom_09->SetColorMask(Color(255, 255, 255));
	imgAntiAtom_10 = LoadImage(display, IDR_ANTIATOM_10);
	imgAntiAtom_10->SetColorMask(Color(255, 255, 255));
	imgAntiAtom_11 = LoadImage(display, IDR_ANTIATOM_11);
	imgAntiAtom_11->SetColorMask(Color(255, 255, 255));
	imgAntiAtom_12 = LoadImage(display, IDR_ANTIATOM_12);
	imgAntiAtom_12->SetColorMask(Color(255, 255, 255));
	// Place pointers to each image in our array of actors
	MatterAntimatterSceneActors[0]  = imgAtom_01;
	MatterAntimatterSceneActors[1]  = imgAtom_02;
	MatterAntimatterSceneActors[2]  = imgAtom_03;
	MatterAntimatterSceneActors[3]  = imgAtom_04;
	MatterAntimatterSceneActors[4]  = imgAtom_05;
	MatterAntimatterSceneActors[5]  = imgAtom_06;
	MatterAntimatterSceneActors[6]  = imgAtom_07;
	MatterAntimatterSceneActors[7]  = imgAtom_08;
	MatterAntimatterSceneActors[8]  = imgAtom_09;
	MatterAntimatterSceneActors[9]  = imgAtom_10;
	MatterAntimatterSceneActors[10] = imgAtom_11;
	MatterAntimatterSceneActors[11] = imgAtom_12;
	MatterAntimatterSceneActors[12] = imgAntiAtom_01;
	MatterAntimatterSceneActors[13] = imgAntiAtom_02;
	MatterAntimatterSceneActors[14] = imgAntiAtom_03;
	MatterAntimatterSceneActors[15] = imgAntiAtom_04;
	MatterAntimatterSceneActors[16] = imgAntiAtom_05;
	MatterAntimatterSceneActors[17] = imgAntiAtom_06;
	MatterAntimatterSceneActors[18] = imgAntiAtom_07;
	MatterAntimatterSceneActors[19] = imgAntiAtom_08;
	MatterAntimatterSceneActors[20] = imgAntiAtom_09;
	MatterAntimatterSceneActors[21] = imgAntiAtom_10;
	MatterAntimatterSceneActors[22] = imgAntiAtom_11;
	MatterAntimatterSceneActors[23] = imgAntiAtom_12;
	MatterAntimatterSceneActors[24] = imgExplosion_001;
	MatterAntimatterSceneActors[25] = imgExplosion_002;
	MatterAntimatterSceneActors[26] = imgExplosion_003;
	MatterAntimatterSceneActors[27] = imgExplosion_004;
	MatterAntimatterSceneActors[28] = imgExplosion_005;
	MatterAntimatterSceneActors[29] = NULL;
	// Get a pointer to the script for this scene
	MatterAntimatterSceneScript = (unsigned char*)OASIS_loadScriptResource(IDR_MATTER_ANTIMATTER_SCENE_SCRIPT, hInst);
	// Place all audio actor sound fx in array of audio actors (order MUST match the script editor!)
	// No need to terminate array with NULL or -1
	MatterAntimatterSceneAudioActors[0] = sfxExplosion;;
	// Do the text actors too
	MatterAntimatterSceneTextActors[0] = -1;
}


// ================================================================================================
// Releaser
// ================================================================================================
void releaserMatterAntimatterScene() {
	delete imgAtom_01;
	delete imgAtom_02;
	delete imgAtom_03;
	delete imgAtom_04;
	delete imgAtom_05;
	delete imgAtom_06;
	delete imgAtom_07;
	delete imgAtom_08;
	delete imgAtom_09;
	delete imgAtom_10;
	delete imgAtom_11;
	delete imgAtom_12;
	delete imgAntiAtom_01;
	delete imgAntiAtom_02;
	delete imgAntiAtom_03;
	delete imgAntiAtom_04;
	delete imgAntiAtom_05;
	delete imgAntiAtom_06;
	delete imgAntiAtom_07;
	delete imgAntiAtom_08;
	delete imgAntiAtom_09;
	delete imgAntiAtom_10;
	delete imgAntiAtom_11;
	delete imgAntiAtom_12;
}


// ================================================================================================
// Scene Starter
// ================================================================================================
void SceneStarter_MatterAntimatterScene() {
	OASIS_StartScene(MatterAntimatterSceneScript, MatterAntimatterSceneActors, MatterAntimatterSceneAudioActors, MatterAntimatterSceneTextActors);
}


// ================================================================================================
// Scene Ender
// ================================================================================================
void SceneEnder_MatterAntimatterScene() {
	OASIS_EndScene();
	game.currentScreen = csAnswerScreen;
}


// ================================================================================================
// Event Handlers
// ================================================================================================
void stylusDownMatterAntimatterScene(Point stylusPoint) {
}

void stylusMoveMatterAntimatterScene(Point stylusPoint) {
}

void stylusUpMatterAntimatterScene(Point stylusPoint) {
	SceneEnder_MatterAntimatterScene();
}

void keyDownMatterAntimatterScene(int key) {
}

void keyUpMatterAntimatterScene(int key) {
}
