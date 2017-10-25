
// ================================================================================================
// Defines
// ================================================================================================
#define wthNothing					 0  // Used to determine what was tapped
#define wthAnswer1					 1  // Used to determine what was tapped
#define wthAnswer2					 2  // Used to determine what was tapped
#define wthAnswer3					 3  // Used to determine what was tapped
#define wthAnswer4					 4  // Used to determine what was tapped
#define wthBeamABrelnar			 5  // Used to determine what was tapped
#define wthAskTheAndromedans 6  // Used to determine what was tapped
#define wthMatterAntimatter	 7  // Used to determine what was tapped
#define wthBookOfKnowledge   8  // Used to determine what was tapped
#define itsHidden						 10 // Icon tray state: Hidden
#define itsShowing					 11 // Icon tray state: Showing
#define itsSlidingIn				 12 // Icon tray state: Sliding In
#define itsSlidingOut				 13 // Icon tray state: Sliding Out
#define vsStatic						 20 // What the viewscreen shows: Static
#define vsCharacter   			 21 // What the viewscreen shows: The character
#define vsKrelmacAndGentoo   22 // What the viewscreen shows: Krelmac & Gentoo
#define vsKrelmac            23 // What the viewscreen shows: Krelmac
#define vsGentoo						 24 // Whar the viewscreen shows: Gentoo

// ================================================================================================
// Globals
// ================================================================================================
// Locations of various screen elements
int			 QuestionLine1_Y							 = 4;
int			 QuestionLine2_Y							 = 22;
int			 QuestionLine3_Y							 = 40;
int			 Answer1_Y										 = 86;
int			 Answer2_Y										 = 126;
int			 Answer3_Y										 = 166;
int			 Answer4_Y										 = 206;
int			 BeamABrelnar_X								 = 14;
int			 BeamABrelnar_Y								 = 264;
int			 AskTheAndromedans_X					 = 64;
int			 AskTheAndromedans_Y					 = 264;
int			 MatterAntimatter_X						 = 116;
int			 MatterAntimatter_Y						 = 264;
int			 BookOfKnowledge_X						 = 168;
int			 BookOfKnowledge_Y						 = 264;
int			 Viewscreen_X									 = 76;
int			 Viewscreen_Y									 = 242;
int			 ViewscreenLastChangeTick			 = 0;
int			 ViewscreenCurrentlyShowing		 = vsStatic;
int			 IconTrayButton_X							 = 0;
int			 IconTrayButton_Y							 = 264;
// Widths and heights of images (these are automatically populated in the loader)
int			 BeamABrelnar_Width						 = 0;
int			 BeamABrelnar_Height					 = 0;
int			 AskTheAndromedans_Width			 = 0;
int			 AskTheAndromedans_Height			 = 0;
int			 MatterAntimatter_Width				 = 0;
int			 MatterAntimatter_Height			 = 0;
int			 BookOfKnowledge_Width				 = 0;
int			 BookOfKnowledge_Height				 = 0;
// Text colors
int			 QuestionColR									 = 255;
int			 QuestionColG									 = 255;
int			 QuestionColB									 = 0;
int			 AnswersColR									 = 255;
int			 AnswersColG									 = 255;
int			 AnswersColB									 = 0;
int			 InactiveAnswersColR					 = 80;
int			 InactiveAnswersColG					 = 80;
int			 InactiveAnswersColB					 = 80;
int			 TimerColR										 = 255;
int			 TimerColG										 = 255;
int			 TimerColB										 = 255;
int			 whichFacialExpression         = 0; // Which facial expresison to show in viewscreen when showing player's character
// Images
Surface* imgViewscreen								 = NULL;
Surface* imgAnswer_Box								 = NULL;
Surface* imgAnswer_BAB_ATA_Box				 = NULL;
Surface* imgBeamABrelnar_0						 = NULL;
Surface* imgAskTheAndromedans_0				 = NULL;
Surface* imgMatterAntimatter_0				 = NULL;
Surface* imgBeamABrelnar_1						 = NULL;
Surface* imgAskTheAndromedans_1				 = NULL;
Surface* imgMatterAntimatter_1				 = NULL;
Surface* imgBeamABrelnar_Disabled			 = NULL;
Surface* imgAskTheAndromedans_Disabled = NULL;
Surface* imgMatterAntimatter_Disabled  = NULL;
Surface* imgAnswerScreenBackground		 = NULL;
Surface* imgBookOfKnowledge_0				   = NULL;
Surface* imgBookOfKnowledge_1					 = NULL;
Surface* imgBookOfKnowledge_Disabled	 = NULL;
Surface* imgIconTraySlideIn_0					 = NULL;
Surface* imgIconTraySlideIn_1					 = NULL;
Surface* imgIconTraySlideOut_0				 = NULL;
Surface* imgIconTraySlideOut_1				 = NULL;
Surface* imgViewscreenKrelmac					 = NULL;
Surface* imgViewscreenGentoo					 = NULL;
Surface* imgViewscreenKrelmacAndGentoo = NULL;
// Others
int			 Answer1_X										 = 0;					// Automatic, stored from call to PFE_drawText
int			 Answer1_Length								 = 0;					// Automatic, stored from call to PFE_drawText
int			 Answer2_X										 = 0;					// Automatic, stored from call to PFE_drawText
int			 Answer2_Length								 = 0;					// Automatic, stored from call to PFE_drawText
int			 Answer3_X										 = 0;					// Automatic, stored from call to PFE_drawText
int			 Answer3_Length								 = 0;					// Automatic, stored from call to PFE_drawText
int			 Answer4_X										 = 0;					// Automatic, stored from call to PFE_drawText
int			 Answer4_Length								 = 0;					// Automatic, stored from call to PFE_drawText
int			 NumberOfQuestions						 = 0;					// Total number of questions (auto-determined)
int			 NumberOfCategories						 = 0;					// Total number of categories (auto-determined)
int			 QuestionsUsed                 = 0;					// Count of the number of questions used so far
int			 CurrentQuestion							 = 0;					// Number of the current question
int			 whatHighlighted							 = 0;					// The currently highlighted answer or lifeline
SoundFX  sfxTick;																		// Tick sound heard when seconds pass
SoundFX  sfxTock;																		// Tock sound heard when seconds pass
SoundFX  sfxDrumRoll;
SoundFX  sfxAnswerDone;
SoundFX  sfxG_BUHAHAHA;
SoundFX  sfxG_HNACD;
SoundFX  sfxG_T;
SoundFX  sfxK_BUHAHAHA;
SoundFX  sfxK_F;
SoundFX  sfxK_OJ;
SoundFX  sfxG_KCIFTECYHHCI;
SoundFX  sfxKANDG_LAUGHING;
bool		 TickOrTock										 = false;			// Determines which sound we play (false = Tick, true = Tock)
int			 questionNumLines							 = 1;					// Number of lines the question requires on the screen
TCHAR		 questionLine1[34]						 = L"";				// First line of the question
TCHAR		 questionLine2[34]					   = L"";				// Second line of the question
TCHAR		 questionLine3[34]						 = L"";				// Third line of the question
bool		 doMatterAntimatter						 = false;			// Set to true when showing two answers only
bool		 MA_ActiveAnswers[7];												// Array corresponding to the four answers set up when doing Matter-Antimatter
bool		 doBABOrATA										 = false;			// Set to true when showing one selected answer
int			 doBABOrATASelectedAnswer			 = 0;					// Answer selected by BeanABrelnar or AskTheAndromedans
int			 doBABOrATAFadeVal						 = 0;					// Used to do border fade of above selected answer
int			 doBABOrATAFadeDir						 = 2;					// 1 = Down, 2 = Up
int			 IconTrayState								 = itsHidden; // 0 = Hidden, 1 = Showing, 2 = Sliding In, 3 = Sliding Out
int			 IconTrayPosition							 = -216;			// Used to adjust icon X coordinates.  0 = Normal, - #'s is sliding
int			 IconTrayPositionMin					 = -216;			// Max value to adjust IconTrayPosition by
bool		 IconTrayButtonTapped					 = false;     // True if the icon tray button is being tapped
int			 ViewscreenBlend							 = 255;
int			 drumrollChannel							 = 0;
// Used to do the transition to correct answer scenes or world destrction scenes
bool		 alreadyCopied	= false;
Surface* copiedBuffer		= NULL;
bool		 doCATransition = false;
int			 CAFadeVal			= 0;
int			 CATargetScene	= 0;
bool		 KTaunt1				= false;
bool		 KTaunt2				= false;
bool		 KTaunt3				= false;
bool		 KTaunt4				= false;
bool		 KTaunt5				= false;
bool		 GTaunt1				= false;
bool		 GTaunt2				= false;
bool		 GTaunt3				= false;
bool		 GTaunt4				= false;
bool		 GTaunt5				= false;
bool		 KGTaunt1				= false;
bool		 KGTaunt2				= false;
bool		 KGTaunt3				= false;
bool		 KGTaunt4				= false;
bool		 KGTaunt5				= false;


// Structure that defines each a question and it's answers
struct QA {
	unsigned short int CategoryKey;
	TCHAR							 Question[82];
	TCHAR							 Answer1[32];
	TCHAR							 Answer2[32];
	TCHAR							 Answer3[32];
	TCHAR							 Answer4[32];
	unsigned short int CorrectAnswer;
};

// Structure that defines a category (not presently used)
struct CATEGORY {
	unsigned short int CategoryKey;
	TCHAR							 CategoryName[32];
};

// Array that holds all our QUESTIONS_ANSWERS structs
QA			 QuestionsAndAnswers[1003];

// We'll need a categories array later when we use them
CATEGORY Categories[27];

// Prototypes
void ChooseQuestion(void);
void loadQAs(TCHAR*);
void WrongOrTimedOut(void);


// ================================================================================================
// Loader
// ================================================================================================
void loaderAnswerScreen(DisplayDevice* display) {
	sfxTick.load(_Module.GetModuleInstance(), IDR_SFX_TICK);
	sfxTock.load(_Module.GetModuleInstance(), IDR_SFX_TOCK);
	sfxDrumRoll.load(_Module.GetModuleInstance(), IDR_SFX_DRUMROLL);
	sfxAnswerDone.load(_Module.GetModuleInstance(), IDR_SFX_ANSWER_DONE);
	sfxG_BUHAHAHA.load(_Module.GetModuleInstance(), IDR_SFX_G_BUHAHAHA);
	sfxG_HNACD.load(_Module.GetModuleInstance(), IDR_SFX_G_HNACD);
	sfxG_T.load(_Module.GetModuleInstance(), IDR_SFX_G_T);
	sfxK_BUHAHAHA.load(_Module.GetModuleInstance(), IDR_SFX_K_BUHAHAHA);
	sfxK_F.load(_Module.GetModuleInstance(), IDR_SFX_K_F);
	sfxK_OJ.load(_Module.GetModuleInstance(), IDR_SFX_K_OJ);
	sfxG_KCIFTECYHHCI.load(_Module.GetModuleInstance(), IDR_SFX_G_KCIFTECYHHCI);	
	sfxKANDG_LAUGHING.load(_Module.GetModuleInstance(), IDR_KANDG_LAUGHING);	
	loadQAs(L"");
	imgViewscreen = LoadImage(display, IDR_VIEWSCREEN);
	imgViewscreen->SetColorMask(Color(255, 255, 255));
	imgAnswer_Box = LoadImage(display, IDR_ANSWER_BOX);
	imgAnswer_Box->SetColorMask(Color(255, 255, 255));
	imgAnswer_BAB_ATA_Box = LoadImage(display, IDR_ANSWER_BAB_ATA_BOX);
	imgAnswer_BAB_ATA_Box->SetColorMask(Color(255, 0, 0));
	imgBeamABrelnar_0 = LoadImage(display, IDR_BEAM_A_BRELNAR_0);
	imgBeamABrelnar_0->SetColorMask(Color(0, 0, 0));
	imgBeamABrelnar_Disabled = LoadImage(display, IDR_BEAM_A_BRELNAR_DISABLED);
	imgBeamABrelnar_Disabled->SetColorMask(Color(0, 0, 0));
	imgBeamABrelnar_1 = LoadImage(display, IDR_BEAM_A_BRELNAR_1);
	imgBeamABrelnar_1->SetColorMask(Color(0, 0, 0));
	BeamABrelnar_Width = imgBeamABrelnar_0->GetWidth();
	BeamABrelnar_Height = imgBeamABrelnar_0->GetHeight();
	imgAskTheAndromedans_0 = LoadImage(display, IDR_ASK_THE_ANDROMEDANS_0);
	imgAskTheAndromedans_0->SetColorMask(Color(0, 0, 0));
	imgAskTheAndromedans_Disabled = LoadImage(display, IDR_ASK_THE_ANDROMEDANS_DISABLED);
	imgAskTheAndromedans_Disabled->SetColorMask(Color(0, 0, 0));
	imgAskTheAndromedans_1 = LoadImage(display, IDR_ASK_THE_ANDROMEDANS_1);
	imgAskTheAndromedans_1->SetColorMask(Color(0, 0, 0));
	AskTheAndromedans_Width = imgAskTheAndromedans_0->GetWidth();
	AskTheAndromedans_Height = imgAskTheAndromedans_0->GetHeight();
	imgMatterAntimatter_0 = LoadImage(display, IDR_MATTER_ANTIMATTER_0);
	imgMatterAntimatter_0->SetColorMask(Color(0, 0, 0));
	imgMatterAntimatter_Disabled = LoadImage(display, IDR_MATTER_ANTIMATTER_DISABLED);
	imgMatterAntimatter_Disabled->SetColorMask(Color(0, 0, 0));
	imgMatterAntimatter_1 = LoadImage(display, IDR_MATTER_ANTIMATTER_1);
	imgMatterAntimatter_1->SetColorMask(Color(0, 0, 0));
	MatterAntimatter_Width = imgMatterAntimatter_0->GetWidth();
	MatterAntimatter_Height = imgMatterAntimatter_0->GetHeight();
	imgBookOfKnowledge_0 = LoadImage(display, IDR_BOOK_OF_KNOWLEDGE_0);
	imgBookOfKnowledge_0->SetColorMask(Color(0, 0, 0));
	imgBookOfKnowledge_Disabled = LoadImage(display, IDR_BOOK_OF_KNOWLEDGE_DISABLED);
	imgBookOfKnowledge_Disabled->SetColorMask(Color(0, 0, 0));
	imgBookOfKnowledge_1 = LoadImage(display, IDR_BOOK_OF_KNOWLEDGE_1);
	imgBookOfKnowledge_1->SetColorMask(Color(0, 0, 0));
	BookOfKnowledge_Width = imgBookOfKnowledge_0->GetWidth();
	BookOfKnowledge_Height = imgBookOfKnowledge_0->GetHeight();
	imgAnswerScreenBackground = LoadImage(display, IDR_ANSWER_SCREEN_BACKGROUND);
	imgIconTraySlideIn_0 = LoadImage(display, IDR_ICON_TRAY_SLIDE_IN_0);
	imgIconTraySlideIn_1 =  LoadImage(display, IDR_ICON_TRAY_SLIDE_IN_1);
	imgIconTraySlideOut_0 = LoadImage(display, IDR_ICON_TRAY_SLIDE_OUT_0);
	imgIconTraySlideOut_1 = LoadImage(display, IDR_ICON_TRAY_SLIDE_OUT_1);
	imgViewscreenKrelmac = LoadImage(display, IDR_VIEWSCREEN_KRELMAC);
	imgViewscreenGentoo	= LoadImage(display, IDR_VIEWSCREEN_GENTOO);
	imgViewscreenKrelmacAndGentoo	= LoadImage(display, IDR_VIEWSCREEN_KRELMAC_AND_GENTOO);
}


// ================================================================================================
// Releaser
// ================================================================================================
void releaserAnswerScreen() {
	delete imgAnswer_Box;
	delete imgAnswer_BAB_ATA_Box;
	delete imgBeamABrelnar_0;
	delete imgBeamABrelnar_Disabled;
	delete imgBeamABrelnar_1;
	delete imgAskTheAndromedans_0;
	delete imgAskTheAndromedans_Disabled;
	delete imgAskTheAndromedans_1;
	delete imgMatterAntimatter_0;
	delete imgMatterAntimatter_Disabled;
	delete imgMatterAntimatter_1;
	delete imgBookOfKnowledge_0;
	delete imgBookOfKnowledge_Disabled;
	delete imgBookOfKnowledge_1;
	delete imgAnswerScreenBackground;
	delete imgViewscreen;
	delete imgIconTraySlideIn_0;
	delete imgIconTraySlideIn_1;
	delete imgIconTraySlideOut_0;
	delete imgIconTraySlideOut_1;
	delete imgViewscreenKrelmac;
	delete imgViewscreenGentoo;
	delete imgViewscreenKrelmacAndGentoo;
}


// ================================================================================================
// Handler
// ================================================================================================
void handlerAnswerScreen(DisplayDevice* display) {

	if (!ProcessEvents) { ProcessEvents = true; }

	// This section is done if we're doing a transition to a correct answer scene
	if (doCATransition) {
		if (alreadyCopied) { // We've already done the initial copy, so do our main loop
			display->SetBlending(255);
			display->Blit(0, 0, copiedBuffer);
			display->SetBlending((char)CAFadeVal);
			display->Blit(0, 0, imgKGShip_Fullscreen);
			display->SetBlending(255);
			if (CAFadeVal < 255) { 
				CAFadeVal = CAFadeVal + 16;
				if (CAFadeVal > 255) { CAFadeVal = 255; }
			} else { // We've completely transitioned, so start the scene
				alreadyCopied = false;
				CAFadeVal = 0;
				doCATransition = false;
				switch (CATargetScene) {
					case 1: {
						SceneStarter_CorrectAnswer1Scene();
						ProcessEvents = false;
						game.currentScreen	= csCorrectAnswer1Scene;
					break; }
					case 2: {
						SceneStarter_CorrectAnswer2Scene();
						ProcessEvents = false;
						game.currentScreen	= csCorrectAnswer2Scene;
					break; }
					case 3: {
						SceneStarter_CorrectAnswer3Scene();
						ProcessEvents = false;
						game.currentScreen	= csCorrectAnswer3Scene;
					break; }
					case 4: {
						SceneStarter_CorrectAnswer4Scene();
						ProcessEvents = false;
						game.currentScreen	= csCorrectAnswer4Scene;
					break; }
					case 5: {
						SceneStarter_CorrectAnswer5Scene();
						ProcessEvents = false;
						game.currentScreen	= csCorrectAnswer5Scene;
					break; }
				}
			}
		} else { // Start the transition
			copiedBuffer = display->GetBackBuffer();
			alreadyCopied = true;
			CAFadeVal = 0;
		}
		return;
	}

	// ----- Update tick count for current question
	if ((PocketPC::GetTickCount() - game.QuestionLastTick) >= 1000) {
		game.QuestionTimeLeft--;
		game.QuestionLastTick = PocketPC::GetTickCount();
		if (TickOrTock) {	game.itPlaySFX(&sfxTock, false); } else { game.itPlaySFX(&sfxTick, false); }
		TickOrTock = !TickOrTock;
	}
	if (game.QuestionTimeLeft == 0) {	WrongOrTimedOut(); return; }
	// ----- Update Bean A Brelnar Or Ask The Andromedans answer indicator color
	if (doBABOrATAFadeDir == 2) {
		doBABOrATAFadeVal = doBABOrATAFadeVal + 15;
	} else {
		doBABOrATAFadeVal = doBABOrATAFadeVal - 15;
	}
	if (doBABOrATAFadeVal > 250)  { doBABOrATAFadeVal = 250;  doBABOrATAFadeDir = 1; }
	if (doBABOrATAFadeVal < 50)   { doBABOrATAFadeVal = 50;   doBABOrATAFadeDir = 2; }
	// ----- Update icon tray and ViewscreenBlend
	switch (IconTrayState) {
		case itsSlidingIn: {
			IconTrayPosition = IconTrayPosition + 15;
			if (IconTrayPosition > 0) {
				IconTrayPosition = 0;
				IconTrayState = itsShowing;
				ViewscreenBlend = 0;
			}
			ViewscreenBlend = ViewscreenBlend - 15;
			if (ViewscreenBlend < 0) { ViewscreenBlend = 0; }
		break; }
		case itsSlidingOut: {
			IconTrayPosition = IconTrayPosition - 15;
			if (IconTrayPosition < IconTrayPositionMin) {
				IconTrayPosition = IconTrayPositionMin;
				IconTrayState = itsHidden;
				ViewscreenBlend = 255;
			}
			ViewscreenBlend = ViewscreenBlend + 20;
			if (ViewscreenBlend > 255) { ViewscreenBlend = 255; }
		break; }
	}
	// ******************************
	// * Background                 *
	// ******************************
	display->Blit(0, 0, imgAnswerScreenBackground);
	// ******************************
	// * Question                   *
	// ******************************
	switch (questionNumLines) {
		case 1: {
			PFE_drawText(display, pFont, questionLine1, PFE_ALIGN_CENTER, 0, QuestionLine2_Y, QuestionColR, QuestionColG, QuestionColB, false);
		break; }
		case 2: {
			PFE_drawText(display, pFont, questionLine1, PFE_ALIGN_CENTER, 0, QuestionLine1_Y + 9, QuestionColR, QuestionColG, QuestionColB, false);
			PFE_drawText(display, pFont, questionLine2, PFE_ALIGN_CENTER, 0, QuestionLine2_Y + 9, QuestionColR, QuestionColG, QuestionColB, false);
		break; }
		case 3: {
			PFE_drawText(display, pFont, questionLine1, PFE_ALIGN_CENTER, 0, QuestionLine1_Y, QuestionColR, QuestionColG, QuestionColB, false);
			PFE_drawText(display, pFont, questionLine2, PFE_ALIGN_CENTER, 0, QuestionLine2_Y, QuestionColR, QuestionColG, QuestionColB, false);
			PFE_drawText(display, pFont, questionLine3, PFE_ALIGN_CENTER, 0, QuestionLine3_Y, QuestionColR, QuestionColG, QuestionColB, false);
		break; }
	}
	// ******************************
	// * Answer 1                   *
	// ******************************
	if (whatHighlighted == wthAnswer1) { 
		display->SetBlending(80);
		display->Blit(2, Answer1_Y - 2, imgAnswer_Box);
		display->SetBlending(255);
		PFE_drawText(display, pFont, QuestionsAndAnswers[CurrentQuestion].Answer1, PFE_ALIGN_CENTER, 0, Answer1_Y);
	} else { 
		if ((doMatterAntimatter && MA_ActiveAnswers[1] == true) || !doMatterAntimatter) {
			PFE_drawText(display,				pFont, QuestionsAndAnswers[CurrentQuestion].Answer1, PFE_ALIGN_CENTER, 0, Answer1_Y, AnswersColR, AnswersColG, AnswersColB, false);
		} else {
			PFE_drawText(display,				pFont, QuestionsAndAnswers[CurrentQuestion].Answer1, PFE_ALIGN_CENTER, 0, Answer1_Y, InactiveAnswersColR, InactiveAnswersColG, InactiveAnswersColB, false);
		}
	}
	Answer1_X			 = PFE_LastDrawText_X			 - 5;
	Answer1_Length = PFE_LastDrawText_Length + 10;
	if (doBABOrATA && doBABOrATASelectedAnswer == 1) {
		display->SetBlending((char)doBABOrATAFadeVal);
		display->Blit(2, Answer1_Y - 2, imgAnswer_BAB_ATA_Box);
		display->SetBlending(255);
	}
	// ******************************
	// * Answer 2                   *
	// ******************************
	if (whatHighlighted == wthAnswer2) { 
		display->SetBlending(80);
		display->Blit(2, Answer2_Y - 2, imgAnswer_Box);
		display->SetBlending(255);
		PFE_drawText(display, pFont, QuestionsAndAnswers[CurrentQuestion].Answer2, PFE_ALIGN_CENTER, 0, Answer2_Y);
	} else { 
		if ((doMatterAntimatter && MA_ActiveAnswers[2] == true) || !doMatterAntimatter) {
			PFE_drawText(display,				pFont, QuestionsAndAnswers[CurrentQuestion].Answer2, PFE_ALIGN_CENTER, 0, Answer2_Y, AnswersColR, AnswersColG, AnswersColB, false);
		} else {
			PFE_drawText(display,				pFont, QuestionsAndAnswers[CurrentQuestion].Answer2, PFE_ALIGN_CENTER, 0, Answer2_Y, InactiveAnswersColR, InactiveAnswersColG, InactiveAnswersColB, false);
		}
	}
	Answer2_X			 = PFE_LastDrawText_X			 - 5;
	Answer2_Length = PFE_LastDrawText_Length + 10;
	if (doBABOrATA && doBABOrATASelectedAnswer == 2) {
		display->SetBlending((char)doBABOrATAFadeVal);
		display->Blit(2, Answer2_Y - 2, imgAnswer_BAB_ATA_Box);
		display->SetBlending(255);
	}
	// ******************************
	// * Answer 3                   *
	// ******************************
	if (whatHighlighted == wthAnswer3) { 
		display->SetBlending(80);
		display->Blit(2, Answer3_Y - 2, imgAnswer_Box);
		display->SetBlending(255);
		PFE_drawText(display, pFont, QuestionsAndAnswers[CurrentQuestion].Answer3, PFE_ALIGN_CENTER, 0, Answer3_Y);
	} else { 
		if ((doMatterAntimatter && MA_ActiveAnswers[3] == true) || !doMatterAntimatter) {
			PFE_drawText(display,				pFont, QuestionsAndAnswers[CurrentQuestion].Answer3, PFE_ALIGN_CENTER, 0, Answer3_Y, AnswersColR, AnswersColG, AnswersColB, false);
		} else {
			PFE_drawText(display,				pFont, QuestionsAndAnswers[CurrentQuestion].Answer3, PFE_ALIGN_CENTER, 0, Answer3_Y, InactiveAnswersColR, InactiveAnswersColG, InactiveAnswersColB, false);
		}
	}
	Answer3_X			 = PFE_LastDrawText_X			 - 5;
	Answer3_Length = PFE_LastDrawText_Length + 10;
	if (doBABOrATA && doBABOrATASelectedAnswer == 3) {
		display->SetBlending((char)doBABOrATAFadeVal);
		display->Blit(2, Answer3_Y - 2, imgAnswer_BAB_ATA_Box);
		display->SetBlending(255);
	}
	// ******************************
	// * Answer 4                   *
	// ******************************
	if (whatHighlighted == wthAnswer4) { 
		display->SetBlending(80);
		display->Blit(2, Answer4_Y - 2, imgAnswer_Box);
		display->SetBlending(255);
		PFE_drawText(display, pFont, QuestionsAndAnswers[CurrentQuestion].Answer4, PFE_ALIGN_CENTER, 0, Answer4_Y);
	} else { 
		if ((doMatterAntimatter && MA_ActiveAnswers[4] == true) || !doMatterAntimatter) {
			PFE_drawText(display,				pFont, QuestionsAndAnswers[CurrentQuestion].Answer4, PFE_ALIGN_CENTER, 0, Answer4_Y, AnswersColR, AnswersColG, AnswersColB, false);
		} else {
			PFE_drawText(display,				pFont, QuestionsAndAnswers[CurrentQuestion].Answer4, PFE_ALIGN_CENTER, 0, Answer4_Y, InactiveAnswersColR, InactiveAnswersColG, InactiveAnswersColB, false);
		}
	}
	Answer4_X			 = PFE_LastDrawText_X			 - 5;
	Answer4_Length = PFE_LastDrawText_Length + 10;
	if (doBABOrATA && doBABOrATASelectedAnswer == 4) {
		display->SetBlending((char)doBABOrATAFadeVal);
		display->Blit(2, Answer4_Y - 2, imgAnswer_BAB_ATA_Box);
		display->SetBlending(255);
	}
	// ******************************
	// * Viewscreen                 *
	// ******************************
	// Set blending in case we're fading because of an icon tray slide
	display->SetBlending((char)ViewscreenBlend);
		// Display whatever is appropriate in the viewscreen
	switch (ViewscreenCurrentlyShowing) {
		case vsCharacter: {
			switch (game.CharacterInUse) {
				case ctCharacterMale1:	 { 
					display->BlitStretch(Rect(Viewscreen_X + 11, Viewscreen_Y + 7, Viewscreen_X + 11 + 64, Viewscreen_Y + 7 + 46), CharacterMale1[whichFacialExpression]);
				break; }
				case ctCharacterFemale1: { 
					display->BlitStretch(Rect(Viewscreen_X + 11, Viewscreen_Y + 7, Viewscreen_X + 11 + 64, Viewscreen_Y + 7 + 46), CharacterFemale1[whichFacialExpression]);
				break; }
				case ctCharacterMale2:	 { 
					display->BlitStretch(Rect(Viewscreen_X + 11, Viewscreen_Y + 7, Viewscreen_X + 11 + 64, Viewscreen_Y + 7 + 46), CharacterMale2[whichFacialExpression]);
				break; }
				case ctCharacterFemale2: { 
					display->BlitStretch(Rect(Viewscreen_X + 11, Viewscreen_Y + 7, Viewscreen_X + 11 + 64, Viewscreen_Y + 7 + 46), CharacterFemale2[whichFacialExpression]);
				break; }
				case ctCharacterMale3:	 { 
					display->BlitStretch(Rect(Viewscreen_X + 11, Viewscreen_Y + 7, Viewscreen_X + 11 + 64, Viewscreen_Y + 7 + 46), CharacterMale3[whichFacialExpression]);
				break; }
				case ctCharacterFemale3: { 
					display->BlitStretch(Rect(Viewscreen_X + 11, Viewscreen_Y + 7, Viewscreen_X + 11 + 64, Viewscreen_Y + 7 + 46), CharacterFemale3[whichFacialExpression]);
				break; }
			}
		break; }
		case vsKrelmacAndGentoo: {
			display->Blit(Viewscreen_X + 11, Viewscreen_Y + 7, imgViewscreenKrelmacAndGentoo);
		break; }
		case vsKrelmac: {
			display->Blit(Viewscreen_X + 11, Viewscreen_Y + 7, imgViewscreenKrelmac);
		break; }
		case vsGentoo: {
			display->Blit(Viewscreen_X + 11, Viewscreen_Y + 7, imgViewscreenGentoo);
		break; }
		case vsStatic: default: {
			int staticPixel = 0;
			for (int y = Viewscreen_Y + 6; y < Viewscreen_Y + 53; y++) {
				for (int x = Viewscreen_X + 10; x < Viewscreen_X + 75; x++) {
					staticPixel = (rand() * (2 + 1)) / (RAND_MAX + 1);
					if (staticPixel == 1) {
						display->SetPixel(x, y, Color(255, 255, 255));
					} else {
						display->SetPixel(x, y, Color(0, 0, 0));
					}
				}
			}
		break; }
	}
	// Update the tick count to count down until the next viewscreen change; if we cross the
	// threshold, go ahead and randomly pick something new to display
	ViewscreenLastChangeTick++;
	if (ViewscreenLastChangeTick > 150) {
		ViewscreenLastChangeTick = 0;
		int newContent = (rand() * (5 + 1)) / (RAND_MAX + 1);
		switch (newContent) {
			case 1: { // Character
				ViewscreenCurrentlyShowing = vsCharacter;
				chooseFacialExpression:
				whichFacialExpression = (rand() * (4 + 1)) / (RAND_MAX + 1);
				if (whichFacialExpression < 0 || whichFacialExpression > 3) { goto chooseFacialExpression; }
			break; }
			case 2: { // Krelmac & Gentoo
				ViewscreenCurrentlyShowing = vsKrelmacAndGentoo;
				// Choose one of the five taunts to say and say it
				int whichKGTaunt = 0;
				// If they've all been used, reset them
				if (KGTaunt1 && KGTaunt2 && KGTaunt3 && KGTaunt4 && KGTaunt5) { KGTaunt1 = false; KGTaunt2 = false; KGTaunt3 = false; KGTaunt4 = false; KGTaunt5 = false; }
				// Choose one of the five
				chooseKGTaunt:
				whichKGTaunt = (rand() * (6 + 1)) / (RAND_MAX + 1);
				if (whichKGTaunt < 1 || whichKGTaunt > 5) { goto chooseKGTaunt; }
				// If the choosen was has already used, try again
				if (whichKGTaunt == 1 && KGTaunt1) { goto chooseKGTaunt; }
				if (whichKGTaunt == 2 && KGTaunt2) { goto chooseKGTaunt; }
				if (whichKGTaunt == 3 && KGTaunt3) { goto chooseKGTaunt; }
				if (whichKGTaunt == 4 && KGTaunt4) { goto chooseKGTaunt; }
				if (whichKGTaunt == 5 && KGTaunt5) { goto chooseKGTaunt; }
				// Everything is OK, so play it and set the flag so we don't play it again
				if (whichKGTaunt == 1) { KGTaunt1 = true; game.itPlaySFX(&sfxG_WTAEOSYWPH,	 false); }
				if (whichKGTaunt == 2) { KGTaunt2 = true; game.itPlaySFX(&sfxG_KCIFTECYHHCI, false); }
				if (whichKGTaunt == 3) { KGTaunt3 = true; game.itPlaySFX(&sfxK_PHYDIIMT,		 false); }
				if (whichKGTaunt == 4) { KGTaunt4 = true; game.itPlaySFX(&sfxK_WNYCHRYPBST,  false); }
				if (whichKGTaunt == 5) { KGTaunt5 = true; game.itPlaySFX(&sfxKANDG_LAUGHING, false); }
			break; }
			case 3: { // Krelmac
				ViewscreenCurrentlyShowing = vsKrelmac;
				// Choose one of the five taunts to say and say it
				int whichKrelmacTaunt = 0;
				// If they've all been used, reset them
				if (KTaunt1 && KTaunt2 && KTaunt3 && KTaunt4 && KTaunt5) { KTaunt1 = false; KTaunt2 = false; KTaunt3 = false; KTaunt4 = false; KTaunt5 = false; }
				// Choose one of the five
				chooseKrelmacTaunt:
				whichKrelmacTaunt = (rand() * (6 + 1)) / (RAND_MAX + 1);
				if (whichKrelmacTaunt < 1 || whichKrelmacTaunt > 5) { goto chooseKrelmacTaunt; }
				// If the choosen was has already used, try again
				if (whichKrelmacTaunt == 1 && KTaunt1) { goto chooseKrelmacTaunt; }
				if (whichKrelmacTaunt == 2 && KTaunt2) { goto chooseKrelmacTaunt; }
				if (whichKrelmacTaunt == 3 && KTaunt3) { goto chooseKrelmacTaunt; }
				if (whichKrelmacTaunt == 4 && KTaunt4) { goto chooseKrelmacTaunt; }
				if (whichKrelmacTaunt == 5 && KTaunt5) { goto chooseKrelmacTaunt; }
				// Everything is OK, so play it and set the flag so we don't play it again
				if (whichKrelmacTaunt == 1) { KTaunt1 = true; game.itPlaySFX(&sfxK_BUHAHAHA,  false); }
				if (whichKrelmacTaunt == 2) { KTaunt2 = true; game.itPlaySFX(&sfxK_F,					false); }
				if (whichKrelmacTaunt == 3) { KTaunt3 = true; game.itPlaySFX(&sfxK_OJ,				false); }
				if (whichKrelmacTaunt == 4) { KTaunt4 = true; game.itPlaySFX(&sfxK_ATTGTSOTR, false); }
				if (whichKrelmacTaunt == 5) { KTaunt5 = true; game.itPlaySFX(&sfxK_ISHISS,		false); }
			break; }
			case 4: { // Gentoo
				ViewscreenCurrentlyShowing = vsGentoo;
				// Choose one of the five taunts to say and say it
				int whichGentooTaunt = 0;
				// If they've all been used, reset them
				if (GTaunt1 && GTaunt2 && GTaunt3 && GTaunt4 && GTaunt5) { GTaunt1 = false; GTaunt2 = false; GTaunt3 = false; GTaunt4 = false; GTaunt5 = false; }
				// Choose one of the five
				chooseGentooTaunt:
				whichGentooTaunt = (rand() * (6 + 1)) / (RAND_MAX + 1);
				if (whichGentooTaunt < 1 || whichGentooTaunt > 5) { goto chooseGentooTaunt; }
				// If the choosen was has already used, try again
				if (whichGentooTaunt == 1 && GTaunt1) { goto chooseGentooTaunt; }
				if (whichGentooTaunt == 2 && GTaunt2) { goto chooseGentooTaunt; }
				if (whichGentooTaunt == 3 && GTaunt3) { goto chooseGentooTaunt; }
				if (whichGentooTaunt == 4 && GTaunt4) { goto chooseGentooTaunt; }
				if (whichGentooTaunt == 5 && GTaunt5) { goto chooseGentooTaunt; }
				// Everything is OK, so play it and set the flag so we don't play it again
				if (whichGentooTaunt == 1) { GTaunt1 = true; game.itPlaySFX(&sfxG_BUHAHAHA,			false); }
				if (whichGentooTaunt == 2) { GTaunt2 = true; game.itPlaySFX(&sfxG_HNACD, 				false); }
				if (whichGentooTaunt == 3) { GTaunt3 = true; game.itPlaySFX(&sfxG_T,						false); }
				if (whichGentooTaunt == 4) { GTaunt4 = true; game.itPlaySFX(&sfxG_IWUTECKTIGBF, false); }
				if (whichGentooTaunt == 5) { GTaunt5 = true; game.itPlaySFX(&sfxG_U,						false); }
			break; }
			default: { // Static
				ViewscreenCurrentlyShowing = vsStatic;
			break; }
		}
	}
	// Now overlay the viewscreen image itself and reset to default blending
	display->Blit(Viewscreen_X, Viewscreen_Y, imgViewscreen);
	display->SetBlending(255);
	// ******************************
	// * Icon tray slide button     *
	// ******************************
	if (IconTrayState == itsHidden || IconTrayState == itsSlidingIn) {
		if (IconTrayButtonTapped) {
			display->Blit(IconTrayButton_X, IconTrayButton_Y, imgIconTraySlideIn_1);
		} else {
			display->Blit(IconTrayButton_X, IconTrayButton_Y, imgIconTraySlideIn_0);
		}
	}
	if (IconTrayState == itsShowing || IconTrayState == itsSlidingOut) {
		if (IconTrayButtonTapped) {
			display->Blit(IconTrayButton_X, IconTrayButton_Y, imgIconTraySlideOut_1);
		} else {
			display->Blit(IconTrayButton_X, IconTrayButton_Y, imgIconTraySlideOut_0);
		}
	}
	// ******************************
	// * Icons: Beam A Brelnar      *
	// ******************************
	if (game.lllBeamABrelnar) {
		if (whatHighlighted == wthBeamABrelnar) { 
			display->Blit(BeamABrelnar_X + IconTrayPosition,	BeamABrelnar_Y,	imgBeamABrelnar_1);
		} else { 
			display->Blit(BeamABrelnar_X + IconTrayPosition,	BeamABrelnar_Y,	imgBeamABrelnar_0);
		}
		display->SetDefaultShader();
	} else {
		display->Blit(BeamABrelnar_X + IconTrayPosition,	BeamABrelnar_Y,	imgBeamABrelnar_Disabled);
	}
	// ******************************
	// * Icons: Ask The Andromedans *
	// ******************************
	if (game.lllAskTheAndromedans) {
		if (whatHighlighted == wthAskTheAndromedans) { 
			display->Blit(AskTheAndromedans_X + IconTrayPosition,	AskTheAndromedans_Y,	imgAskTheAndromedans_1);
		} else { 
			display->Blit(AskTheAndromedans_X + IconTrayPosition,	AskTheAndromedans_Y,	imgAskTheAndromedans_0);
		}
	} else {
		display->Blit(AskTheAndromedans_X + IconTrayPosition,	AskTheAndromedans_Y,	imgAskTheAndromedans_Disabled);
	}
	// ******************************
	// * Icons: Matter-Antimatter   *
	// ******************************
	if (game.lllMatterAntimatter) {
		if (whatHighlighted == wthMatterAntimatter) { 
			display->Blit(MatterAntimatter_X + IconTrayPosition,	MatterAntimatter_Y,	imgMatterAntimatter_1);
		} else { 
			display->Blit(MatterAntimatter_X + IconTrayPosition,	MatterAntimatter_Y,	imgMatterAntimatter_0);
		}
	} else {
		display->Blit(MatterAntimatter_X + IconTrayPosition,	MatterAntimatter_Y,	imgMatterAntimatter_Disabled);
	}
	// ******************************
	// * Icons: Book Of Knowledge   *
	// ******************************
	if (game.lllBookOfKnowledge) {
		if (whatHighlighted == wthBookOfKnowledge) { 
			display->Blit(BookOfKnowledge_X + IconTrayPosition,	BookOfKnowledge_Y,	imgBookOfKnowledge_1);
		} else { 
			display->Blit(BookOfKnowledge_X + IconTrayPosition,	BookOfKnowledge_Y,	imgBookOfKnowledge_0);
		}
	} else {
		display->Blit(BookOfKnowledge_X + IconTrayPosition,	BookOfKnowledge_Y,	imgBookOfKnowledge_Disabled);
	}
	// ******************************
	// * Time Left                  *
	// ******************************
	TCHAR szTimeLeft[5] = L"";
	swprintf(szTimeLeft, L"%d", game.QuestionTimeLeft);
	PFE_drawText(display, pFont, szTimeLeft, PFE_ALIGN_NONE, 222, 300, TimerColR, TimerColG, TimerColB, false);
}


// ================================================================================================
// Event Handlers
// ================================================================================================
void stylusDownAnswerScreen(Point stylusPoint) {
	if (!doCATransition) {
		Rect testBounds;
		testBounds.Set(0, 264, 10, 312);
		if (testBounds.Contains(stylusPoint) && !IconTrayButtonTapped && (IconTrayState == itsHidden || IconTrayState == itsShowing)) {
			IconTrayButtonTapped = true;
		}
	}
}

void stylusMoveAnswerScreen(Point stylusPoint) {
}

void stylusUpAnswerScreen(Point stylusPoint) {
	if (!doCATransition) {
		game.itStopSFX(drumrollChannel);
		int  whatTapped	= wthNothing;
		Rect testBounds;
		// Handle icon tray slide button events
		testBounds.Set(0, 264, 10, 312);
		if (testBounds.Contains(stylusPoint) && IconTrayButtonTapped && (IconTrayState == itsHidden || IconTrayState == itsShowing)) {
			game.itPlaySFX(&sfxIconSlide, false);
			whatHighlighted = wthNothing;
			IconTrayButtonTapped = false;
			switch (IconTrayState) {
				case itsHidden: {
					IconTrayState = itsSlidingIn;
				break; }
				case itsShowing: {
					IconTrayState = itsSlidingOut;
				break; }
			}
			return;
		}
		IconTrayButtonTapped = false;
		// See which answer or lifeline they tapped:
		// Answer 1
		testBounds.Set(Answer1_X, Answer1_Y, Answer1_X + Answer1_Length, Answer1_Y + 16);
		if (testBounds.Contains(stylusPoint)) { 
			if ((doMatterAntimatter && MA_ActiveAnswers[1] == true) || !doMatterAntimatter) {
				whatTapped = wthAnswer1;
				game.itPlaySFX(&sfxAnswerDone, false);
			}
		}
		// Answer 2
		testBounds.Set(Answer2_X, Answer2_Y, Answer2_X + Answer2_Length, Answer2_Y + 16);
		if (testBounds.Contains(stylusPoint)) { 
			if ((doMatterAntimatter && MA_ActiveAnswers[2] == true) || !doMatterAntimatter) {
				whatTapped = wthAnswer2;
				game.itPlaySFX(&sfxAnswerDone, false);
			}
		}
		// Answer 3
		testBounds.Set(Answer3_X, Answer3_Y, Answer3_X + Answer3_Length, Answer3_Y + 16);
		if (testBounds.Contains(stylusPoint)) { 
			if ((doMatterAntimatter && MA_ActiveAnswers[3] == true) || !doMatterAntimatter) {
				whatTapped = wthAnswer3;
				game.itPlaySFX(&sfxAnswerDone, false);
			}
		}
		// Answer 4
		testBounds.Set(Answer4_X, Answer4_Y, Answer4_X + Answer4_Length, Answer4_Y + 16);
		if (testBounds.Contains(stylusPoint)) { 
			if ((doMatterAntimatter && MA_ActiveAnswers[4] == true) || !doMatterAntimatter) {
				whatTapped = wthAnswer4;
				game.itPlaySFX(&sfxAnswerDone, false);
			}
		}
		// Test lifelines, but ONLY if the tray is showing
		if (IconTrayState == itsShowing) {
			// Beam A Brelnar
			testBounds.Set(BeamABrelnar_X, BeamABrelnar_Y, BeamABrelnar_X + BeamABrelnar_Width, BeamABrelnar_Y + BeamABrelnar_Height);
			if (testBounds.Contains(stylusPoint) && game.lllBeamABrelnar) { whatTapped = wthBeamABrelnar; }
			// Ask The Andromedans
			testBounds.Set(AskTheAndromedans_X, AskTheAndromedans_Y, AskTheAndromedans_X + AskTheAndromedans_Width, AskTheAndromedans_Y + AskTheAndromedans_Height);
			if (testBounds.Contains(stylusPoint) && game.lllAskTheAndromedans) { whatTapped = wthAskTheAndromedans; }
			// Matter-Antimatter
			testBounds.Set(MatterAntimatter_X, MatterAntimatter_Y, MatterAntimatter_X + MatterAntimatter_Width, MatterAntimatter_Y + MatterAntimatter_Height);
			if (testBounds.Contains(stylusPoint) && game.lllMatterAntimatter) { whatTapped = wthMatterAntimatter; }
			// Book Of Knowledge
			testBounds.Set(BookOfKnowledge_X, BookOfKnowledge_Y, BookOfKnowledge_X + BookOfKnowledge_Width, BookOfKnowledge_Y + BookOfKnowledge_Height);
			if (testBounds.Contains(stylusPoint) && game.lllBookOfKnowledge) { whatTapped = wthBookOfKnowledge; }
		}
		// They didn't tap any answer or lifeline
		if (whatTapped == wthNothing) {
			whatTapped			= wthNothing;
			whatHighlighted = wthNothing;
			return;
		}
		// See if the answer they tapped is already highlighted or not.
		if (whatHighlighted != whatTapped) { 
			if (whatTapped != wthBeamABrelnar     && whatTapped != wthAskTheAndromedans &&
					whatTapped != wthMatterAntimatter && whatTapped != wthBookOfKnowledge) {
						drumrollChannel = game.itPlaySFX(&sfxDrumRoll, true);
			}
			// So highlight it
			whatHighlighted = whatTapped;
			return;
		} else { // It was the highlighted item, so process it
			// Lifelines:
			if (whatTapped == wthBeamABrelnar) {
				// Standard setup and of course disable the lifeline for next time
				whatTapped					 = wthNothing;
				whatHighlighted			 = wthNothing;
				game.lllBeamABrelnar = false;
				doBABOrATA = true;
				// Perform the lifeline function
				int AnswersArray[14]; // Our answers array
				// Fill six elements with the correct answer
				AnswersArray[1] = QuestionsAndAnswers[CurrentQuestion].CorrectAnswer;
				AnswersArray[2] = QuestionsAndAnswers[CurrentQuestion].CorrectAnswer;
				AnswersArray[3] = QuestionsAndAnswers[CurrentQuestion].CorrectAnswer;
				AnswersArray[4] = QuestionsAndAnswers[CurrentQuestion].CorrectAnswer;
				AnswersArray[5] = QuestionsAndAnswers[CurrentQuestion].CorrectAnswer;
				AnswersArray[6] = QuestionsAndAnswers[CurrentQuestion].CorrectAnswer;
				// Fill four elements with wrong answers
				for (int i = 7; i < 11; i++) {
					PickWrongAnswersBAB:
					AnswersArray[i] = (rand() * (4 + 1)) / (RAND_MAX + 1); // 4 = Total # of answers
					if (AnswersArray[i] == QuestionsAndAnswers[CurrentQuestion].CorrectAnswer ||
						  AnswersArray[i] < 1 || AnswersArray[i] > 4) { goto PickWrongAnswersBAB; }
				}
				// Pick one of the ten elements in the above array (60% chance of being right)
				PickFinalAnswerBAB:
				doBABOrATASelectedAnswer = (rand() * (10 + 1)) / (RAND_MAX + 1); // 10 = Total # of answers in array
				if (doBABOrATASelectedAnswer <= 0 || doBABOrATASelectedAnswer > 10) { goto PickFinalAnswerBAB; }
				doBABOrATASelectedAnswer = AnswersArray[doBABOrATASelectedAnswer];
				// Do the scene
				game.itSilenceAllSFX();
				SceneStarter_BeamABrelnarScene();
				ProcessEvents = false;
				game.currentScreen	= csBeamABrelnarScene;
				return;
			}
			if (whatTapped == wthAskTheAndromedans) {
				// Standard setup and of course disable the lifeline for next time
				whatTapped								= wthNothing;
				whatHighlighted						= wthNothing;
				game.lllAskTheAndromedans = false;
				doBABOrATA								= true;
				// Perform the lifeline function
				int AnswersArray[14]; // Our answers array
				// Fill six elements with the correct answer
				AnswersArray[1] = QuestionsAndAnswers[CurrentQuestion].CorrectAnswer;
				AnswersArray[2] = QuestionsAndAnswers[CurrentQuestion].CorrectAnswer;
				AnswersArray[3] = QuestionsAndAnswers[CurrentQuestion].CorrectAnswer;
				AnswersArray[4] = QuestionsAndAnswers[CurrentQuestion].CorrectAnswer;
				AnswersArray[5] = QuestionsAndAnswers[CurrentQuestion].CorrectAnswer;
				AnswersArray[6] = QuestionsAndAnswers[CurrentQuestion].CorrectAnswer;
				AnswersArray[7] = QuestionsAndAnswers[CurrentQuestion].CorrectAnswer;
				AnswersArray[8] = QuestionsAndAnswers[CurrentQuestion].CorrectAnswer;
				// Fill four elements with wrong answers
				for (int i = 9; i < 11; i++) {
					PickWrongAnswersATA:
					AnswersArray[i] = (rand() * (4 + 1)) / (RAND_MAX + 1); // 4 = Total # of answers
					if (AnswersArray[i] < 1 || AnswersArray[i] > 4 || 
						  AnswersArray[i] == QuestionsAndAnswers[CurrentQuestion].CorrectAnswer) { goto PickWrongAnswersATA; }
				}
				// Pick one of the ten elements in the above array (80% chance of being right)
				PickFinalAnswerATA:
				doBABOrATASelectedAnswer = (rand() * (10 + 1)) / (RAND_MAX + 1); // 10 = Total # of answers in array
				if (doBABOrATASelectedAnswer <= 0 || doBABOrATASelectedAnswer > 10) { goto PickFinalAnswerATA; }
				doBABOrATASelectedAnswer = AnswersArray[doBABOrATASelectedAnswer];
				// Do the scene
				game.itSilenceAllSFX();
				SceneStarter_AskTheAndromedansScene();
				ProcessEvents = false;
				game.currentScreen	= csAskTheAndromedansScene;
				return;
			}
			if (whatTapped == wthMatterAntimatter) {
				whatTapped			= wthNothing;
				whatHighlighted = wthNothing;
				doMatterAntimatter = true;
				game.lllMatterAntimatter = false;
				// Perform the lifeline function
				MA_ActiveAnswers[1] = false;
				MA_ActiveAnswers[2] = false;
				MA_ActiveAnswers[3] = false;
				MA_ActiveAnswers[4] = false;
				// Set the correct answer to active
				MA_ActiveAnswers[QuestionsAndAnswers[CurrentQuestion].CorrectAnswer] = true;
				// Choose an answer other than the correct one and activate it
				int choosenAnswer;
				pickActiveAnswer:
				choosenAnswer = (rand() * (4 + 1)) / (RAND_MAX + 1); // 4 = Total # of answers
				if (choosenAnswer <= 0 || choosenAnswer > 4 || 
					  choosenAnswer == QuestionsAndAnswers[CurrentQuestion].CorrectAnswer) { goto pickActiveAnswer; }
				MA_ActiveAnswers[choosenAnswer] = true;
				// Do the scene
				game.itSilenceAllSFX();
				SceneStarter_MatterAntimatterScene();
				ProcessEvents = false;
				game.currentScreen	= csMatterAntimatterScene;
				return;
			}
			if (whatTapped == wthBookOfKnowledge) {
				whatTapped			= wthNothing;
				whatHighlighted = wthNothing;
				game.lllBookOfKnowledge = false;
				game.itSilenceAllSFX();
				SceneStarter_BookOfKnowledgeScene();
				game.currentPointLevel++;
				ProcessEvents = false;
				game.currentScreen	= csBookOfKnowledgeScene;
				return;
			}
			// Answers:
			// Right
			if (whatTapped == QuestionsAndAnswers[CurrentQuestion].CorrectAnswer) {
				whatHighlighted = wthNothing;
				game.currentPointLevel++;
				// They won the game!  Get rid of the wise-asses
				if (game.currentPointLevel >= game.numberPointLevels) {
					ChoosePlayerWinsScene:
					int whatPlayerWinsScene = (rand() * (5 + 1)) / (RAND_MAX + 1); // 5 = Total # of scenes
					// If 0 comes up, choose again
					if (whatPlayerWinsScene <= 0 || whatPlayerWinsScene > 5) { goto ChoosePlayerWinsScene; }
					// Stop premature repeating of scenes
					if (game.playerWins1Done == true && game.playerWins2Done == true && 
						  game.playerWins3Done == true && game.playerWins4Done == true && 
							game.playerWins5Done == true) {
							  game.playerWins1Done = false;
								game.playerWins2Done = false;
								game.playerWins3Done = false;
								game.playerWins4Done = false;
								game.playerWins5Done = false;
					}
					if (whatPlayerWinsScene == 1 && game.playerWins1Done == true) { goto ChoosePlayerWinsScene; }
					if (whatPlayerWinsScene == 2 && game.playerWins2Done == true) { goto ChoosePlayerWinsScene; }
					if (whatPlayerWinsScene == 3 && game.playerWins3Done == true) { goto ChoosePlayerWinsScene; }
					if (whatPlayerWinsScene == 4 && game.playerWins4Done == true) { goto ChoosePlayerWinsScene; }
					if (whatPlayerWinsScene == 5 && game.playerWins5Done == true) { goto ChoosePlayerWinsScene; }
					game.itSilenceAllSFX();
					switch (whatPlayerWinsScene) {
						case 1: {
							game.playerWins1Done = true;
							SceneStarter_PlayerWins1Scene();
							ProcessEvents = false;
							game.currentScreen	= csPlayerWins1Scene;
						break; }
						case 2: {
							game.playerWins2Done = true;
							SceneStarter_PlayerWins2Scene();
							ProcessEvents = false;
							game.currentScreen	= csPlayerWins2Scene;
						break; }
						case 3: {
							game.playerWins3Done = true;
							SceneStarter_PlayerWins3Scene();
							ProcessEvents = false;
							game.currentScreen	= csPlayerWins3Scene;
						break; }
						case 4: {
							game.playerWins4Done = true;
							SceneStarter_PlayerWins4Scene();
							ProcessEvents = false;
							game.currentScreen	= csPlayerWins4Scene;
						break; }
						case 5: {
							game.playerWins5Done = true;
							SceneStarter_PlayerWins5Scene();
							ProcessEvents = false;
							game.currentScreen	= csPlayerWins5Scene;
						break; }
					}
				// Just another right answer, so show the wise-asses
				} else {
					// If we're about to go to the last point level, disable Book Of Knowledge
					if (game.currentPointLevel == game.numberPointLevels - 1) {
						game.lllBookOfKnowledge = false;
					}
					ChooseCorrectAnswerScene:
					int whatCorrectAnswerScene = (rand() * (5 + 1)) / (RAND_MAX + 1); // 5 = Total # of scenes
					// If 0 comes up, choose again
					if (whatCorrectAnswerScene <= 0 || whatCorrectAnswerScene > 5) { goto ChooseCorrectAnswerScene; }
					// Stop premature repeating of scenes
					if (game.correctAnswer1Done == true && game.correctAnswer2Done == true && 
						  game.correctAnswer3Done == true && game.correctAnswer4Done == true && 
							game.correctAnswer5Done == true) {
							  game.correctAnswer1Done = false;
								game.correctAnswer2Done = false;
								game.correctAnswer3Done = false;
								game.correctAnswer4Done = false;
								game.correctAnswer5Done = false;
					}
					if (whatCorrectAnswerScene == 1 && game.correctAnswer1Done == true) { goto ChooseCorrectAnswerScene; }
					if (whatCorrectAnswerScene == 2 && game.correctAnswer2Done == true) { goto ChooseCorrectAnswerScene; }
					if (whatCorrectAnswerScene == 3 && game.correctAnswer3Done == true) { goto ChooseCorrectAnswerScene; }
					if (whatCorrectAnswerScene == 4 && game.correctAnswer4Done == true) { goto ChooseCorrectAnswerScene; }
					if (whatCorrectAnswerScene == 5 && game.correctAnswer5Done == true) { goto ChooseCorrectAnswerScene; }
					game.itSilenceAllSFX();
					switch (whatCorrectAnswerScene) {
					case 1: {
							game.correctAnswer1Done = true;
							doCATransition = true;
							CATargetScene = 1;
						break; }
						case 2: {
							game.correctAnswer2Done = true;
							doCATransition = true;
							CATargetScene = 2;
						break; }
						case 3: {
							game.correctAnswer3Done = true;
							doCATransition = true;
							CATargetScene = 3;
						break; }
						case 4: {
							game.correctAnswer4Done = true;
							doCATransition = true;
							CATargetScene = 4;
						break; }
						case 5: {
							game.correctAnswer5Done = true;
							doCATransition = true;
							CATargetScene = 5;
						break; }
					}
				}
			// Wrong
			} else {
				WrongOrTimedOut();
			}
		} // End if (whatHighlighted != whatTapped)
	} // End if (!CATransition)
} // End StylusUp()

void keyDownAnswerScreen(int key) {
}

void keyUpAnswerScreen(int key) {
}


// ================================================================================================
// Functions used during loading, choosing a question and when a wrong answered is selected or time runs out
// ================================================================================================

// This is called when a wrong answer is selected or time runs out
void WrongOrTimedOut() {
	whatHighlighted = wthNothing;
	game.numberWrong++;
	// They blew it, so now blow up the world (check developer's flag to see if they even can lose the game)
	if (game.numberWrong > game.maxWrongAllowed) {
		ChooseWorldDestructionScene:
		int whatWorldDestructionScene = (rand() * (5 + 1)) / (RAND_MAX + 1); // 5 = Total # of scenes
		// If 0 comes up, choose again
		if (whatWorldDestructionScene <= 0 || whatWorldDestructionScene > 5) { goto ChooseWorldDestructionScene; }
					// Stop premature repeating of scenes
					if (game.worldDestruction1Done == true && game.worldDestruction2Done == true && 
						  game.worldDestruction3Done == true && game.worldDestruction4Done == true && 
							game.worldDestruction5Done == true) {
								game.worldDestruction1Done = false;
								game.worldDestruction2Done = false;
								game.worldDestruction3Done = false;
								game.worldDestruction4Done = false;
								game.worldDestruction5Done = false;
					}
					if (whatWorldDestructionScene == 1 && game.worldDestruction1Done == true) { goto ChooseWorldDestructionScene; }
					if (whatWorldDestructionScene == 2 && game.worldDestruction2Done == true) { goto ChooseWorldDestructionScene; }
					if (whatWorldDestructionScene == 3 && game.worldDestruction3Done == true) { goto ChooseWorldDestructionScene; }
					if (whatWorldDestructionScene == 4 && game.worldDestruction4Done == true) { goto ChooseWorldDestructionScene; }
					if (whatWorldDestructionScene == 5 && game.worldDestruction5Done == true) { goto ChooseWorldDestructionScene; }
		game.itSilenceAllSFX();
		switch (whatWorldDestructionScene) {
			case 1: {
				game.worldDestruction1Done = true;
				SceneStarter_WorldDestruction1Scene();
				ProcessEvents = false;
				game.currentScreen	= csWorldDestruction1Scene;
			break; }
			case 2: {
				game.worldDestruction2Done = true;
				SceneStarter_WorldDestruction2Scene();
				ProcessEvents = false;
				game.currentScreen	= csWorldDestruction2Scene;
			break; }
			case 3: {
				game.worldDestruction3Done = true;
				SceneStarter_WorldDestruction3Scene();
				ProcessEvents = false;
				game.currentScreen	= csWorldDestruction3Scene;
			break; }
			case 4: {
				game.worldDestruction4Done = true;
				SceneStarter_WorldDestruction4Scene();
				ProcessEvents = false;
				game.currentScreen	= csWorldDestruction4Scene;
			break; }
			case 5: {
				game.worldDestruction5Done = true;
				SceneStarter_WorldDestruction5Scene();
				ProcessEvents = false;
				game.currentScreen	= csWorldDestruction5Scene;
			break; }
		}		
	// Just another allowed wrong answer, so just blow up a city
	} else {
		// If all cities have been destroyed, reset them all
		if (game.destroyedGiza	 == true && game.destroyedLondon  == true &&
				game.destroyedMoscow == true &&
				game.destroyedParis  == true && game.destroyedPisa    == true &&
				game.destroyedRome   == true && game.destroyedStLouis == true &&
				game.destroyedTokyo  == true) {
					game.destroyedGiza		= false;
					game.destroyedLondon	= false;
					game.destroyedMoscow	= false;
					game.destroyedParis		= false;
					game.destroyedPisa		= false;
					game.destroyedRome		= false;
					game.destroyedStLouis = false;
					game.destroyedTokyo		= false;
		}
		ChooseCityDestructionScene:
		int whatCityDestructionScene = (rand() * (8 + 1)) / (RAND_MAX + 1); // 8 = Total # of scenes
		// If 0 comes up, choose again
		if (whatCityDestructionScene <= 0 || whatCityDestructionScene > 8) { goto ChooseCityDestructionScene; }

		// Do the appropriate city.  If it's already destroyed, choose again.
		game.itSilenceAllSFX();
		switch (whatCityDestructionScene) {
			case 1: {
				if (game.destroyedGiza == true) { goto ChooseCityDestructionScene; }
				game.destroyedGiza = true;
				SceneStarter_DestructionGizaScene();
				ProcessEvents = false;
				game.currentScreen	= csGizaDestructionScene;
			break; }
			case 2: {
				if (game.destroyedLondon == true) { goto ChooseCityDestructionScene; }
				game.destroyedLondon = true;
				SceneStarter_DestructionLondonScene();
				ProcessEvents = false;
				game.currentScreen	= csLondonDestructionScene;
			break; }
			case 3: {
				if (game.destroyedMoscow == true) { goto ChooseCityDestructionScene; }
				game.destroyedMoscow = true;
				SceneStarter_DestructionMoscowScene();
				ProcessEvents = false;
				game.currentScreen	= csMoscowDestructionScene;
			break; }
			case 4: {
				if (game.destroyedParis == true) { goto ChooseCityDestructionScene; }
				game.destroyedParis = true;
				SceneStarter_DestructionParisScene();
				ProcessEvents = false;
				game.currentScreen	= csParisDestructionScene;
			break; }
			case 5: {
				if (game.destroyedPisa == true) { goto ChooseCityDestructionScene; }
				game.destroyedPisa = true;
				SceneStarter_DestructionPisaScene();
				ProcessEvents = false;
				game.currentScreen	= csPisaDestructionScene;
			break; }
			case 6: {
				if (game.destroyedRome == true) { goto ChooseCityDestructionScene; }
				game.destroyedRome = true;
				SceneStarter_DestructionRomeScene();
				ProcessEvents = false;
				game.currentScreen	= csRomeDestructionScene;
			break; }
			case 7: {
				if (game.destroyedStLouis == true) { goto ChooseCityDestructionScene; }
				game.destroyedStLouis = true;
				SceneStarter_DestructionStLouisScene();
				ProcessEvents = false;
				game.currentScreen	= csStLouisDestructionScene;
			break; }
			case 8: {
				if (game.destroyedTokyo == true) { goto ChooseCityDestructionScene; }
				game.destroyedTokyo = true;
				SceneStarter_DestructionTokyoScene();
				ProcessEvents = false;
				game.currentScreen	= csTokyoDestructionScene;
			break; }
		}		
	}
}


// Called to randomly choose a question
void ChooseQuestion() {
	// Reset zumbugwa indicators
	doMatterAntimatter = false;
	doBABOrATA         = false;
	int i	= 0;
	// Generate a random number between 1 and the total number of questions
	ChooseCurrentQuestion:
	CurrentQuestion = (rand() * (NumberOfQuestions + 1)) / (RAND_MAX + 1);
	// If 0 comes up, choose again
	if (CurrentQuestion <= 0 || CurrentQuestion > NumberOfQuestions) { goto ChooseCurrentQuestion; }
	// See if we've used this question already and pick another if so, if not record it for next time
	for (i = 0; i < QuestionsUsed; i++) { if (game.usedQuestions[i] == CurrentQuestion) { goto ChooseCurrentQuestion;	} }
	game.usedQuestions[QuestionsUsed] = CurrentQuestion;
	// If we've used more than half the total questions, reset the array and the counter.  We
	// really should only do this when the number of questions used equals the total number of
	// questions, but if we wait that long than the above check loop will start to take an
	// unacceptably long time, so half seems like a reasonable compromise.
	QuestionsUsed++;
	if (QuestionsUsed > NumberOfQuestions / 2) { 
		QuestionsUsed = 0;
		for (i = 0; i < 1000; i++) { game.usedQuestions[i] = 0; }
	}
	// Start with nothing highlighted
	whatHighlighted = 0;
	// Determine how many rows it needs on the screen and populates some vars
	int szLen = wcslen(QuestionsAndAnswers[CurrentQuestion].Question);
	_wcsset(questionLine1, '\0');
	_wcsset(questionLine2, '\0');
	_wcsset(questionLine3, '\0');
	int j = 0;
	questionNumLines = 1;
	for (i = 0; i < szLen; i++) {
		if (QuestionsAndAnswers[CurrentQuestion].Question[i] != '~') {
			if (questionNumLines == 1) {
				questionLine1[j] = QuestionsAndAnswers[CurrentQuestion].Question[i];
				j++;
			}
			if (questionNumLines == 2) {
				questionLine2[j] = QuestionsAndAnswers[CurrentQuestion].Question[i];
				j++;
			}
			if (questionNumLines == 3) {
				questionLine3[j] = QuestionsAndAnswers[CurrentQuestion].Question[i];
				j++;
			}
		} else { // EOL character
			questionNumLines++;
			j = 0;
		}
	}
}


// This function reads in the questions and answers from memory
void loadQAs(TCHAR* fileName) {
	unsigned char			 counter					= 0;
	unsigned short int CategoryKey			= 0;
	unsigned short int CorrectAnswer		= 0;
	unsigned char*		 pQAS							= NULL;
	TCHAR              CategoryName[32] = L"";
	TCHAR							 Question[82]			= L"";
	TCHAR							 Answer1[32]			= L"";
	TCHAR							 Answer2[32]			= L"";
	TCHAR							 Answer3[32]			= L"";
	TCHAR							 Answer4[32]			= L"";
	// Loading QAs from a resource
	if (wcscmp(fileName, L"") == 0) {
		HGLOBAL hResD		 = NULL;
		HRSRC   hResInfo = NULL;
		hResInfo = FindResource(hInst, MAKEINTRESOURCE(IDR_QAC), L"QAC");
		hResD = LoadResource(hInst, hResInfo);
		pQAS = (unsigned char*)hResD;
	// Loading QAs from a file
	} else {
		// Read in the QA file
		HANDLE hFile = CreateFile(fileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hFile == INVALID_HANDLE_VALUE) { 	return; }
		DWORD dwFileSize = GetFileSize(hFile, NULL);
		pQAS = (unsigned char*)malloc(dwFileSize);
		DWORD numBytesRead = 1;
		int bResult = ReadFile(hFile, pQAS, dwFileSize, &numBytesRead, NULL);
		if (bResult == 0 || numBytesRead != dwFileSize) { return; }
		CloseHandle(hFile);
	}
	// Parse the file.  First, get the header and make sure it's valid
	TCHAR headerID[8] = L"";
	headerID[0] = *pQAS++;
	headerID[1] = *pQAS++;
	headerID[2] = *pQAS++;
	headerID[3] = *pQAS++;
	headerID[4] = *pQAS++;
	headerID[5] = NULL;
	if (wcscmp(headerID, L"ITQAC")) { return; }
	// Now get the major and minor version and make sure we can use it with the EXE version.
	int majorVersion = *pQAS++;
	int minorVersion = *pQAS++;
	if (majorVersion != 1) { return; }
	if (minorVersion != 0) { return; }
	// Skip past expansion buffer area
	pQAS = pQAS + 10;
	// Now read in the category information (not used for now, but we still have to read it
	NumberOfCategories = 0;
 	while (*pQAS != 0xff) {
		NumberOfCategories++;
		// Category key
		CategoryKey = *pQAS++;
		// Category name
		wcscpy(CategoryName, L"");
		counter = 0;
	 	while (*pQAS != 0xfe) {
			CategoryName[counter] = *pQAS++;
			counter++;
		}
		CategoryName[counter] = NULL;
		pQAS++;
		// Load up the structure of the current question number with the data
		Categories[NumberOfCategories].CategoryKey  = CategoryKey;
		wcscpy(Categories[NumberOfCategories].CategoryName, CategoryName);
	}
	pQAS++;
	// Go through them and populate our array
	NumberOfQuestions = 0;
	while (*pQAS != 0xff) { // Until the end of QA data
		NumberOfQuestions++;
		wcscpy(Question, L"");
		wcscpy(Answer1,  L"");
		wcscpy(Answer2,  L"");
		wcscpy(Answer3,  L"");
		wcscpy(Answer4,  L"");
		// Get the category key
		CategoryKey = *pQAS;
		pQAS++;
		// Get the question
		counter = 0;
		while (*pQAS != 0xfe) {
			Question[counter] = *pQAS;
			pQAS++;
			counter++;
		}
		Question[counter] = NULL;
		pQAS++;
		// Get answer #1
		counter = 0;
		while (*pQAS != 0xfe) {
			Answer1[counter] = *pQAS;
			pQAS++;
			counter++;
		}
		Answer1[counter] = NULL;
		pQAS++;
		// Get answer #2
		counter = 0;
		while (*pQAS != 0xfe) {
			Answer2[counter] = *pQAS;
			pQAS++;
			counter++;
		}
		Answer2[counter] = NULL;
		pQAS++;
		// Get answer #3
		counter = 0;
		while (*pQAS != 0xfe) {
			Answer3[counter] = *pQAS;
			pQAS++;
			counter++;
		}
		Answer3[counter] = NULL;
		pQAS++;
		// Get answer #4
		counter = 0;
		while (*pQAS != 0xfe) {
			Answer4[counter] = *pQAS;
			pQAS++;
			counter++;
		}
		Answer4[counter] = NULL;
		pQAS++;
		// Get the correct answer
		CorrectAnswer = *pQAS;
		pQAS++;
		// Load up the structure of the current question number with the data
		QuestionsAndAnswers[NumberOfQuestions].CategoryKey	 = CategoryKey;
		wcscpy(QuestionsAndAnswers[NumberOfQuestions].Question, Question);
		wcscpy(QuestionsAndAnswers[NumberOfQuestions].Answer1, Answer1);
		wcscpy(QuestionsAndAnswers[NumberOfQuestions].Answer2, Answer2);
		wcscpy(QuestionsAndAnswers[NumberOfQuestions].Answer3, Answer3);
		wcscpy(QuestionsAndAnswers[NumberOfQuestions].Answer4, Answer4);
		QuestionsAndAnswers[NumberOfQuestions].CorrectAnswer = CorrectAnswer;
	}
}

