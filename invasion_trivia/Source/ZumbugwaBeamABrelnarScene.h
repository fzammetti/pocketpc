
// ================================================================================================
// Globals
// ================================================================================================
Surface*			 BeamABrelnarSceneActors[25];
SoundFX 			 BeamABrelnarSceneAudioActors[5];
int						 BeamABrelnarSceneTextActors[4];
unsigned char* BeamABrelnarSceneScript					= NULL;
Surface*			 imgBrelnarBackground							= NULL;
Surface*			 imgBrelnarBeamComingDown					= NULL;
Surface*			 imgBrelnarBeam1									= NULL;
Surface*			 imgBrelnarBeam2									= NULL;
Surface*			 imgBrelnarBeamUp1								= NULL;
Surface*			 imgBrelnarBeamUp2								= NULL;
Surface*			 imgBrelnarBored									= NULL;
Surface*			 imgBrelnarShockedLeft						= NULL;
Surface*			 imgBrelnarShockedRight						= NULL;
Surface*			 imgBrelnarWordsPitifulBrelnar		= NULL;
Surface*			 imgBrelnarWordsChooseAnAnswer		= NULL;
Surface*			 imgBrelnarWordsThankYouNowGetOut = NULL;
Surface*			 imgBrelnarWhatThe								= NULL;
Surface*			 imgBrelnarLaterJoe								= NULL;
Surface*			 imgBrelnarQuizzical							= NULL;
Surface*			 imgBrelnarBrightIdea							= NULL;
SoundFX				 sfxBrelnarCricket;
SoundFX				 sfxBrelnarBeamSound;


// ================================================================================================
// Loader
// ================================================================================================
void loaderBeamABrelnarScene(DisplayDevice* display) {
	// Load audio actor sound fx for this scene
	sfxBrelnarCricket.load(_Module.GetModuleInstance(), IDR_SFX_BRELNAR_CRICKET);
	sfxBrelnarBeamSound.load(_Module.GetModuleInstance(), IDR_SFX_BRELNAR_BEAM_SOUND);
	// Load actor images for this scene and set required transparency masks
	imgBrelnarBackground = LoadImage(display, IDR_BRELNAR_BACKGROUND);
	imgBrelnarBeamComingDown = LoadImage(display, IDR_BRELNAR_BEAM_COMING_DOWN);
	imgBrelnarBeamComingDown->SetColorMask(Color(255, 255, 255));
	imgBrelnarBeam1 = LoadImage(display, IDR_BRELNAR_BEAM_1);
	imgBrelnarBeam1->SetColorMask(Color(255, 255, 255));
	imgBrelnarBeam2 = LoadImage(display, IDR_BRELNAR_BEAM_2);
	imgBrelnarBeam2->SetColorMask(Color(255, 255, 255));
	imgBrelnarBored = LoadImage(display, IDR_BRELNAR_BORED);
	imgBrelnarBored->SetColorMask(Color(255, 255, 255));
	imgBrelnarBeamUp1 = LoadImage(display, IDR_BRELNAR_BEAM_UP_1);
	imgBrelnarBeamUp1->SetColorMask(Color(255, 255, 255));
	imgBrelnarBeamUp2 = LoadImage(display, IDR_BRELNAR_BEAM_UP_2);
	imgBrelnarBeamUp2->SetColorMask(Color(255, 255, 255));
	imgBrelnarShockedLeft = LoadImage(display, IDR_BRELNAR_SHOCKED_LEFT);
	imgBrelnarShockedLeft->SetColorMask(Color(255, 255, 255));
	imgBrelnarShockedRight = LoadImage(display, IDR_BRELNAR_SHOCKED_RIGHT);
	imgBrelnarShockedRight->SetColorMask(Color(255, 255, 255));
	imgBrelnarWordsPitifulBrelnar = LoadImage(display, IDR_BRELNAR_WORDS_PITIFULBRELNAR);
	imgBrelnarWordsChooseAnAnswer = LoadImage(display, IDR_BRELNAR_WORDS_CHOOSEANANSWER);
	imgBrelnarWordsThankYouNowGetOut = LoadImage(display, IDR_BRELNAR_WORDS_THANKYOUNOWGETOUT);
	imgBrelnarWhatThe = LoadImage(display, IDR_BRELNAR_WHAT_THE);
	imgBrelnarWhatThe->SetColorMask(Color(250, 250, 240));
	imgBrelnarLaterJoe = LoadImage(display, IDR_BRELNAR_LATER_JOE);
	imgBrelnarLaterJoe->SetColorMask(Color(250, 250, 240));
	imgBrelnarQuizzical = LoadImage(display, IDR_BRELNAR_QUIZZICAL);
	imgBrelnarQuizzical->SetColorMask(Color(255, 255, 255));
	imgBrelnarBrightIdea = LoadImage(display, IDR_BRELNAR_BRIGHT_IDEA);
	imgBrelnarBrightIdea->SetColorMask(Color(255, 255, 255));
	// Get a pointer to the script for this scene
	BeamABrelnarSceneScript = (unsigned char*)OASIS_loadScriptResource(IDR_BEAM_A_BRELNAR_SCENE_SCRIPT, hInst);
	// Place all actor images in array of actors (order MUST match the script editor!)
	// Last element MUST be NULL
	BeamABrelnarSceneActors[0]  = imgBrelnarBackground;
	BeamABrelnarSceneActors[1]  = imgBrelnarBeamComingDown;
	BeamABrelnarSceneActors[2]  = imgBrelnarBeam1;
	BeamABrelnarSceneActors[3]  = imgBrelnarBeam2;
	BeamABrelnarSceneActors[4]  = imgBrelnarBored;
	BeamABrelnarSceneActors[5]  = imgBrelnarBeamUp1;
	BeamABrelnarSceneActors[6]  = imgBrelnarBeamUp2;
	BeamABrelnarSceneActors[7]  = imgBrelnarShockedLeft;
	BeamABrelnarSceneActors[8]  = imgBrelnarShockedRight;
	BeamABrelnarSceneActors[9]  = imgShipInterior;
	BeamABrelnarSceneActors[10] = imgBrelnarWordsPitifulBrelnar;
	BeamABrelnarSceneActors[11] = imgBrelnarWordsChooseAnAnswer;
	BeamABrelnarSceneActors[12] = imgBrelnarWordsThankYouNowGetOut;
	BeamABrelnarSceneActors[13]	= imgExplosion_001;
	BeamABrelnarSceneActors[14]	= imgExplosion_002;
	BeamABrelnarSceneActors[15]	= imgExplosion_003;
	BeamABrelnarSceneActors[16]	= imgExplosion_004;
	BeamABrelnarSceneActors[17]	= imgExplosion_005;
	BeamABrelnarSceneActors[18] = imgBrelnarWhatThe;
	BeamABrelnarSceneActors[19] = imgBrelnarLaterJoe;
	BeamABrelnarSceneActors[20] = imgBrelnarQuizzical;
	BeamABrelnarSceneActors[21] = imgBrelnarBrightIdea;
	BeamABrelnarSceneActors[22] = NULL;
	// Place all audio actor sound fx in array of audio actors (order MUST match the script editor!)
	// No need to terminate array with NULL or -1
	BeamABrelnarSceneAudioActors[0] = sfxBrelnarCricket;
	BeamABrelnarSceneAudioActors[1] = sfxBrelnarBeamSound;
	BeamABrelnarSceneAudioActors[2] = sfxExplosion;
	// Place all text actor resource ID's in array of text actors (order MUST match the script editor!)
	// Last element MUST be -1
	BeamABrelnarSceneTextActors[0] = IDS_BRELNAR_MEANWHILE;
	BeamABrelnarSceneTextActors[1] = -1;
}


// ================================================================================================
// Releaser
// ================================================================================================
void releaserBeamABrelnarScene() {
	delete imgBrelnarBackground;
	delete imgBrelnarBeamComingDown;
	delete imgBrelnarBeam1;
	delete imgBrelnarBeam2;
	delete imgBrelnarBeamUp1;
	delete imgBrelnarBeamUp2;
	delete imgBrelnarBored;
	delete imgBrelnarShockedLeft;
	delete imgBrelnarShockedRight;
	delete imgBrelnarWordsPitifulBrelnar;
	delete imgBrelnarWordsChooseAnAnswer;
	delete imgBrelnarWordsThankYouNowGetOut;
	delete imgBrelnarWhatThe;
	delete imgBrelnarLaterJoe;
	delete imgBrelnarQuizzical;
	delete imgBrelnarBrightIdea;
}


// ================================================================================================
// Scene Starter
// ================================================================================================
void SceneStarter_BeamABrelnarScene() {
	OASIS_StartScene(BeamABrelnarSceneScript, BeamABrelnarSceneActors, BeamABrelnarSceneAudioActors, BeamABrelnarSceneTextActors);
}


// ================================================================================================
// Scene Ender
// ================================================================================================
void SceneEnder_BeamABrelnarScene() {
	OASIS_EndScene();
	game.currentScreen = csAnswerScreen;
}


// ================================================================================================
// Event Handlers
// ================================================================================================
void stylusDownBeamABrelnarScene(Point stylusPoint) {
}

void stylusMoveBeamABrelnarScene(Point stylusPoint) {
}

void stylusUpBeamABrelnarScene(Point stylusPoint) {
	SceneEnder_BeamABrelnarScene();
}

void keyDownBeamABrelnarScene(int key) {
}

void keyUpBeamABrelnarScene(int key) {
}
