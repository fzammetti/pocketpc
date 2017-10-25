
// ************************************************************************************************
// Header includes
// ************************************************************************************************
#include "stdafx.h"
#include "../resource.h"
#include <PocketFrog.h>
#include <stdlib.h>


// ************************************************************************************************
// PocketFrog needed stuff
// ************************************************************************************************
using namespace Frog;
CComModule _Module;


// ************************************************************************************************
// Structures
// ************************************************************************************************
// Structure that defines a point level
struct POINTLEVEL {
	TCHAR	valueText[12];
};

// Structure that defines a QAC file
struct QACFILE {
	TCHAR	fileName[MAX_PATH + 2];
};

// Structure that defines an entry in the high scores screen
struct HIGHSCOREENTRY {
  unsigned char pointLevelReached;
	TCHAR					playerName[13];
	int						characterUsed;
};


// ************************************************************************************************
// Defines
// ************************************************************************************************
#define csLoadingScreen			      0    // Screen
#define csIntroScreen				      1    // Screen
#define csMainMenuScreen          2    // Screen
#define csInstructionsScreen      3    // Screen
#define csHighScoresScreen        4    // Screen
#define csCreditsScreen           5    // Screen
#define csPointLevelsScreen       6    // Screen
#define csAnswerScreen            7    // Screen
#define csSettingsScreen          8    // Screen
#define	csCharacterSelectScreen		10	 // Screen
#define csCongratulationsScreen   11   // Screen
#define csExiting									12   // Screen (sort of)
#define csNone										20	 // Screen (sort of)
#define csTitleScene              100  // Scene
#define csStartGameIntro1Scene    102  // Scene
#define csStartGameIntro2Scene    103  // Scene
#define csStartGameIntro3Scene    104  // Scene
#define csStartGameIntro4Scene    105  // Scene
#define csStartGameIntro5Scene    106  // Scene
#define csCorrectAnswer1Scene     107  // Scene
#define csCorrectAnswer2Scene     108  // Scene
#define csCorrectAnswer3Scene     109  // Scene
#define csCorrectAnswer4Scene     110  // Scene
#define csCorrectAnswer5Scene     111  // Scene
#define csWorldDestruction1Scene  112  // Scene
#define csWorldDestruction2Scene  113  // Scene
#define csWorldDestruction3Scene  114  // Scene
#define csWorldDestruction4Scene  115  // Scene
#define csWorldDestruction5Scene  116  // Scene
#define csPlayerWins1Scene        117  // Scene
#define csPlayerWins2Scene        118  // Scene
#define csPlayerWins3Scene        119  // Scene
#define csPlayerWins4Scene        120  // Scene
#define csPlayerWins5Scene        121  // Scene
#define csBeamABrelnarScene				123  // Scene
#define csAskTheAndromedansScene	124	 // Scene
#define csMatterAntimatterScene		125  // Scene
#define csBookOfKnowledgeScene		126  // Scene
#define csParisDestructionScene   131  // Scene
#define csPisaDestructionScene    132  // Scene
#define csLondonDestructionScene  133  // Scene
#define csMoscowDestructionScene  134  // Scene
#define csRomeDestructionScene    135  // Scene
#define csStLouisDestructionScene 136  // Scene
#define csGizaDestructionScene    137  // Scene
#define csTokyoDestructionScene   138  // Scene
#define dlEasy										1000 // Difficulty level
#define dlNormal									1001 // Difficulty level
#define dlHard										1002 // Difficulty level
#define vlNoSound									0		 // Volume Level: No Sound
#define vlLow                     1		 // Volume Level: Low
#define vlMedium                  2		 // Volume Level: Medium
#define vlHigh                    3		 // Volume Level: High


// ************************************************************************************************
// Game class prototype
// ************************************************************************************************
class InvasionTrivia : public Game {

	public:

		// Properties
		uint32_t	 FPSTicksPerFrame;		 // Used for frame rate limiting
		uint32_t	 FPSLastTime;					 // Used for frame rate limiting
		POINTLEVEL PointLevels[28];			 // Array of point level structures
		int				 difficultyLevel;			 // Difficulty level of the current game
		int				 volumeLevel;          // Volume level
		int				 currentPointLevel;		 // Point level player is currently at
		int				 numberPointLevels;		 // Number of point levels for this game
		int				 numberWrong;					 // Number of questions player has gotten wrong so far
		int				 maxWrongAllowed;			 // Number of questions allowed wrong before end of world
		int				 timeToAnswer;				 // Number of seconds player is allowed to take to answer a question
		Surface*	 FPSNumbers;					 // Numbers for FPS display
		int				 QuestionTimeLeft;		 // Time left for the current question
		int				 QuestionLastTick;		 // Time of last clock tick on answers screen
		DWORD			 previousTickCount;		 // Used to display FPS
		int				 countFPS;						 // Used to display FPS
		int				 lastFPS;							 // Used to display FPS
		int				 currentScreen;				 // What screen is currently being shown
		bool			 lllBeamABrelnar;			 // Is the Beam A Brelnar lifeline still left?
		bool			 lllAskTheAndromedans; // Is the Ask The Andromedans lifeline still left?
		bool			 lllMatterAntimatter;  // Is the Matter-Antimatter lifeline still left?
		bool			 lllBookOfKnowledge;   // Is the Book Of Knowledge lifeline still left?
		TCHAR			 gameEXEPath[130];		 // Path of the executable
		int				 usedQuestions[1002];  // Array containing the questions used in the current game
		int				 fontIndex;            // Index into the pFonts array of the current font
		int				 QACIndex;             // Index into the QACFiles array of the current QAC file in use
		int				 CharacterInUse;			 // What character head was selected for this game
		int				 ThemeMusicChannel;    // Records the channel the theme music is playing on
		bool			 destroyedGiza;
		bool			 destroyedLondon;
		bool			 destroyedMoscow;
		bool			 destroyedParis;
		bool			 destroyedPisa;
		bool			 destroyedRome;
		bool			 destroyedStLouis;
		bool			 destroyedTokyo;
		bool			 correctAnswer1Done;
		bool			 correctAnswer2Done;
		bool			 correctAnswer3Done;
		bool			 correctAnswer4Done;
		bool			 correctAnswer5Done;
		bool			 playerWins1Done;
		bool			 playerWins2Done;
		bool			 playerWins3Done;
		bool			 playerWins4Done;
		bool			 playerWins5Done;
		bool			 worldDestruction1Done;
		bool			 worldDestruction2Done;
		bool			 worldDestruction3Done;
		bool			 worldDestruction4Done;
		bool			 worldDestruction5Done;

		// Constructor
		InvasionTrivia();
		// Methods that mimick Frog calls so that global headers can use them
		void								 itStopSFX(int);
		void								 itSetVolume(int, int);
		void								 itSilenceAllSFX();
		int									 itPlaySFX(SoundFX*, bool);
		Sound*							 itGetSound();
		void								 itPlayThemeMusic();
		void								 itStopThemeMusic();
		// Other game methods
		static  DWORD WINAPI LoadingThreadFunc(LPVOID);
		virtual DWORD				 LoadingThreadMemberFunc();
		void								 SetVolumeLevel();
		bool								 GameInit();
		void								 GameEnd();
		void								 GameLoop();
		void								 StylusDown(Point);
		void								 StylusMove(Point);
		void								 StylusUp(Point);
		void								 ButtonDown(int);
		void								 ButtonUp(int);
		void								 SetUpGame(int);
		void								 FinishGameLoop(DisplayDevice*);
		DWORD								 GetModuleDirectory(HMODULE, LPTSTR, DWORD);
		void								 GetDirectoryContents(TCHAR*);
		bool								 readHSSFile();
		bool								 writeHSSFile();
		bool								 SeeIfPlayerGotHighScore();

};


// ************************************************************************************************
// Globals
// ************************************************************************************************
InvasionTrivia		 game;															  // Instance of our game class
HINSTANCE					 hInst											 = NULL;  // Handle to our application
int								 MaxFrameRate								 = 30;    // Desired frame rate to run game at
unsigned char*		 pFont											 = NULL;  // Pointer to in-use font
unsigned char*		 pFonts[22];												  // Array of all available fonts
TCHAR							 fontNames[22][14];									  // Array of all available font names
QACFILE						 QACFiles[102];											  // Array of QAC files
int								 QACFiles_Count							 = 0;		  // Count of QAC files found
HIGHSCOREENTRY		 HighScoreEasy;												// High score: Easy
HIGHSCOREENTRY		 HighScoreNormal;											// High score: Normal
HIGHSCOREENTRY		 HighScoreHard;												// High score: Hard
int								 gradientR									 = 225;		// Text color gradient red component (purplish)
int								 gradientG									 = 145;	  // Text color gradient green component (purplish)
int								 gradientB									 = 225;		// Text color gradient blue component (purplish)
DWORD							 StartingTickCount					 = 0;		  // Used to display number of ticks during startup
DWORD							 EndingTickCount						 = 0;			// Used to display number of ticks during startup
int								 ExitCounter								 = 0;			// Used to do the TV effect when the game is exited
int								 ExitFadeCounter						 = 255;		// Used to do the TV effect when the game is exited
bool							 ProcessEvents							 = false;


// ************************************************************************************************
// Utility debug functions
// ************************************************************************************************
LPVOID MB_FormatMsg(DWORD gle) {
	LPVOID lpMsgBuf;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
								NULL, gle, 0, (LPTSTR)&lpMsgBuf, 0, NULL);
	return lpMsgBuf;
}

// Used for debugging to display a number in a messagebox
void MB_Num(int num, TCHAR* szHeader) {
	TCHAR szOut[22];
	swprintf(szOut, L"%d", num);
	MessageBox(NULL, szOut,szHeader, MB_OK);
}

// Used for debugging to display a string
void MB_Txt(TCHAR* szIn, TCHAR* szHeader) {
	MessageBox(NULL, szIn, szHeader, MB_OK);
}


// ************************************************************************************************
// Includes of all other source
// ************************************************************************************************
#include "Starfield3D.h"
#include "ITTitleBounce.h"
#include "PFE_FunctionLibrary.h"
#include "PFE_GUIWidgets.h"
#include "OASIS.h"
#include "TitleScene.h"
#include "LoadingScreen.h"
#include "DestructionParisScene.h"
#include "DestructionGizaScene.h"
#include "DestructionLondonScene.h"
#include "DestructionMoscowScene.h"
#include "DestructionPisaScene.h"
#include "DestructionRomeScene.h"
#include "DestructionStLouisScene.h"
#include "DestructionTokyoScene.h"
#include "StartGameIntro1Scene.h"
#include "StartGameIntro2Scene.h"
#include "StartGameIntro3Scene.h"
#include "StartGameIntro4Scene.h"
#include "StartGameIntro5Scene.h"
#include "WorldDestruction1Scene.h"
#include "WorldDestruction2Scene.h"
#include "WorldDestruction3Scene.h"
#include "WorldDestruction4Scene.h"
#include "WorldDestruction5Scene.h"
#include "IntroScreen.h"
#include "CorrectAnswer1Scene.h"
#include "CorrectAnswer2Scene.h"
#include "CorrectAnswer3Scene.h"
#include "CorrectAnswer4Scene.h"
#include "CorrectAnswer5Scene.h"
#include "PlayerWins1Scene.h"
#include "PlayerWins2Scene.h"
#include "PlayerWins3Scene.h"
#include "PlayerWins4Scene.h"
#include "PlayerWins5Scene.h"
#include "CongratulationsScreen.h"
#include "ZumbugwaBeamABrelnarScene.h"
#include "ZumbugwaAskTheAndromedansScene.h"
#include "ZumbugwaMatterAntimatterScene.h"
#include "ZumbugwaBookOfKnowledgeScene.h"
#include "CharacterSelectScreen.h"
#include "MainMenuScreen.h"
#include "CreditsScreen.h"
#include "InstructionsScreen.h"
#include "AnswerScreen.h"
#include "SettingsScreen.h"
#include "HighScoresScreen.h"
#include "PointLevelsScreen.h"
#include "GameLoop.h"
#include "StylusHandlers.h"
#include "ButtonHandlers.h"


// ************************************************************************************************
// Game class method bodies
// ************************************************************************************************

// The actual loading thread function
DWORD InvasionTrivia::LoadingThreadMemberFunc() {
	DisplayDevice* display = GetDisplay();
	for (int i = 0; i < 1000; i++) {
		usedQuestions[i] = 0;
	}
	updateProgressBar(display);
	GetModuleDirectory(GetModuleHandle(NULL), gameEXEPath, sizeof(gameEXEPath) / sizeof(TCHAR));
	loaderIntroScreen(display);
	loaderTitleScene(display);
	updateProgressBar(display);
	loaderDestructionParisScene(display);
	loaderInstructionsScreen(display);
	loaderSettingsScreen(display);
	loaderHighScoresScreen(display);
	updateProgressBar(display);
	loaderDestructionLondonScene(display);
	loaderCreditsScreen(display);
	loaderWorldDestruction1Scene(display);
	updateProgressBar(display);
	loaderDestructionMoscowScene(display);
	loaderWorldDestruction2Scene(display);
	loaderStartGameIntro1Scene(display);
	loaderWorldDestruction4Scene(display);
	updateProgressBar(display);
	loaderDestructionGizaScene(display);
	loaderWorldDestruction5Scene(display);
	loaderBeamABrelnarScene(display);
	updateProgressBar(display);
	loaderDestructionPisaScene(display);
	loaderMainMenuScreen(display);
	loaderWorldDestruction3Scene(display);
	loaderStartGameIntro2Scene(display);
	updateProgressBar(display);
	loaderDestructionRomeScene(display);
	loaderStartGameIntro3Scene(display);
	loaderStartGameIntro4Scene(display);
	loaderAskTheAndromedansScene(display);
	updateProgressBar(display);
	loaderDestructionStLouisScene(display);
	loaderStartGameIntro5Scene(display);
	loaderCorrectAnswer1Scene(display);
	loaderMatterAntimatterScene(display);
	updateProgressBar(display);
	loaderDestructionTokyoScene(display);
	loaderCorrectAnswer2Scene(display);
	loaderCorrectAnswer3Scene(display);
	loaderBookOfKnowledgeScene(display);
	updateProgressBar(display);
	loaderCorrectAnswer4Scene(display);
	loaderCorrectAnswer5Scene(display);
	loaderITTitleBounce(display);
	updateProgressBar(display);
	loaderPlayerWins1Scene(display);
	loaderPlayerWins2Scene(display);
	loaderPlayerWins3Scene(display);
	updateProgressBar(display);
	loaderPlayerWins4Scene(display);
	PFE_GUIWidgetsInitialize(display);
	loaderAnswerScreen(display);
	loaderCongratulationsScreen(display);
	updateProgressBar(display);
	loaderPlayerWins5Scene(display);
	loaderPointLevelsScreen(display);
	loaderCharacterSelectScreen(display);
	initStarfield3D();
	GetDirectoryContents(game.gameEXEPath);
	difficultyLevel = dlNormal;
	volumeLevel = vlMedium;
	previousTickCount = PocketPC::GetTickCount();
	countFPS	 			  = 0;
	lastFPS						= 0;
	destroyedGiza = false;
	destroyedLondon = false;
	destroyedMoscow = false;
	destroyedParis = false;
	destroyedPisa = false;
	destroyedRome = false;
	destroyedStLouis = false;
	destroyedTokyo = false;
  correctAnswer1Done = false;
	correctAnswer2Done = false;
	correctAnswer3Done = false;
	correctAnswer4Done = false;
	correctAnswer5Done = false;
	playerWins1Done = false;
	playerWins2Done = false;
	playerWins3Done = false;
	playerWins4Done = false;
	playerWins5Done = false;
	worldDestruction1Done = false;
	worldDestruction2Done = false;
	worldDestruction3Done = false;
	worldDestruction4Done = false;
	worldDestruction5Done = false;
	updateProgressBar(display);
	HRSRC		hResInfo  = NULL;
	HGLOBAL	hResource = NULL;
	pFonts[0] = pFont;
	wcscpy(fontNames[0], L"Default");
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_FONT_20S), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[1] = (unsigned char*)LockResource(hResource);
	wcscpy(fontNames[1], L"20s");
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_FONT_ANTIQUE), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[2] = (unsigned char*)LockResource(hResource);
	wcscpy(fontNames[2], L"Antique");
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_FONT_ART), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[3] = (unsigned char*)LockResource(hResource);
	wcscpy(fontNames[3], L"Art");
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_FONT_BOLD), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[4] = (unsigned char*)LockResource(hResource);
	wcscpy(fontNames[4], L"Bold");
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_FONT_BOXROUND), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[5] = (unsigned char*)LockResource(hResource);
	wcscpy(fontNames[5], L"Boxround");
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_FONT_CP112), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[6] = (unsigned char*)LockResource(hResource);
	wcscpy(fontNames[6], L"CP112");
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_FONT_KANA), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[7] = (unsigned char*)LockResource(hResource);
	wcscpy(fontNames[7], L"Kana");
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_FONT_MERP), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[8] = (unsigned char*)LockResource(hResource);
	wcscpy(fontNames[8], L"Merp");
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_FONT_MODERN), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[9] = (unsigned char*)LockResource(hResource);
	wcscpy(fontNames[9], L"Modern");
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_FONT_POOTER), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[10] = (unsigned char*)LockResource(hResource);
	wcscpy(fontNames[10], L"Pooter");
	pFonts[11]	  = NULL;
	if (!readHSSFile()) { MB_Txt(L"BAD", L""); FatalError(L"Could not initialize game"); }
	isLoadingDone = true;
	return 0;
}


// Game initialization
bool InvasionTrivia::GameInit() {
	// Initialize random number generator
	srand(PocketPC::GetTickCount());
	// Set up frame limiting
	FPSTicksPerFrame = 1000 / MaxFrameRate; // FPS (denominator)
	FPSLastTime			 = PocketPC::GetTickCount();
	// Clear screen to white, initialize Loading screen and start the thread
	DisplayDevice* display = GetDisplay();
		display->Clear(Color(0, 0, 0));
	display->Update();
	// Load default font (must be done here in case we're displaying frame rate to avoid GPF in FinishGameLoop)
	HRSRC		hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_FONT_DEFAULT), TEXT("FONTS"));
	HGLOBAL	hResource = LoadResource(hInst, hResInfo);
	pFont = (unsigned char*)LockResource(hResource);
	fontIndex = 0;
	currentScreen	= csLoadingScreen;
	loaderLoadingScreen(display);
	isLoadingDone = false;
	HANDLE hThread = CreateThread(NULL, 0, LoadingThreadFunc, this, 0, NULL);
	SetThreadPriority(hThread, THREAD_PRIORITY_NORMAL);
	return true;
}


// Called to end the game
void InvasionTrivia::GameEnd() {
	// Delete FPS numbers
	delete FPSNumbers;
	// Call all releasers to free up resources
	releaserIntroScreen();
	releaserTitleScene();
	releaserMainMenuScreen();
	releaserDestructionParisScene();
	releaserDestructionGizaScene();
	releaserDestructionLondonScene();
	releaserDestructionMoscowScene();
	releaserDestructionPisaScene();
	releaserDestructionRomeScene();
	releaserDestructionStLouisScene();
	releaserDestructionTokyoScene();
	releaserWorldDestruction1Scene();
	releaserWorldDestruction2Scene();
	releaserWorldDestruction3Scene();
	releaserWorldDestruction4Scene();
	releaserWorldDestruction5Scene();
	releaserBeamABrelnarScene();
	releaserAskTheAndromedansScene();
	releaserMatterAntimatterScene();
	releaserBookOfKnowledgeScene();
	releaserITTitleBounce();
	releaserAnswerScreen();
	releaserCongratulationsScreen();
	releaserCharacterSelectScreen();
	releaserStartGameIntro1Scene();
	releaserStartGameIntro2Scene();
	releaserStartGameIntro3Scene();
	releaserStartGameIntro4Scene();
	releaserStartGameIntro5Scene();
	releaserCorrectAnswer1Scene();
	releaserCorrectAnswer2Scene();
	releaserCorrectAnswer3Scene();
	releaserCorrectAnswer4Scene();
	releaserCorrectAnswer5Scene();
	releaserPlayerWins1Scene();
	releaserPlayerWins2Scene();
	releaserPlayerWins3Scene();
	releaserPlayerWins4Scene();
	releaserPlayerWins5Scene();
	releaserPointLevelsScreen();
	releaserCreditsScreen();
	releaserHighScoresScreen();
	releaserInstructionsScreen();
	releaserSettingsScreen();
	releaserLoadingScreen();
	PFE_GUIWidgetsShutdown();
}


// Constructor
InvasionTrivia::InvasionTrivia() {
	m_config.szWindowName     = _T("InvasionTrivia");
	m_config.orientation      = ORIENTATION_NORTH;
	m_config.splashScreenTime = 0;
	m_config.displayflags     = FROG_PC_NORMAL;
	m_config.soundfrequency		= 8000;
  PocketPC::GetModel();
}



// Called at the end of every iteration of GameLoop.  It does FPS limiting and also displays FPS
// if desired.  Anything else that has to happen every frame can go here, but remember it comes
// AFTER the frame is rendered!
void InvasionTrivia::FinishGameLoop(DisplayDevice* display) {
	// Slow down to desired FPS
	while (PocketPC::GetTickCount() - FPSLastTime < FPSTicksPerFrame) { } FPSLastTime = PocketPC::GetTickCount();
}


// Called to play a sound FX
int InvasionTrivia::itPlaySFX(SoundFX* sfx, bool loop) {
	sfx->setLoop(loop);
	return GetSound()->playSFX(sfx);
}


// Called to stop a sound FX on a particular channel (one FX per channel at a time)
void InvasionTrivia::itStopSFX(int channel) {
	GetSound()->stopSFX(channel);
}


// Called to set the volume of a channel
void InvasionTrivia::itSetVolume(int in_channel, int volume) {
	Channel *channel = GetSound()->getChannel(in_channel);
	channel->setVolume(volume);
}


// Called to get a pointed to the sound device
Sound* InvasionTrivia::itGetSound() {
	return GetSound();
}


// Called to play the theme music
void InvasionTrivia::itPlayThemeMusic() {
	Sound *snd = GetSound();
	ThemeMusicChannel = snd->playMod(&ThemeMusic);
}


// Called to stop playing of the theme music
void InvasionTrivia::itStopThemeMusic() {
	Sound *snd = GetSound();
	snd->stopMod(ThemeMusicChannel);
}


// Called to stop all sound FX playing on all channels
void InvasionTrivia::itSilenceAllSFX() {
	Sound* snd = GetSound();
	snd->stopSFX(0);
	snd->stopSFX(1);
	snd->stopSFX(2);
	snd->stopSFX(3);
	snd->stopSFX(4);
	snd->stopSFX(5);
	snd->stopSFX(6);
	snd->stopSFX(7);
}


// Called from GameInit to start the loading thread
DWORD WINAPI InvasionTrivia::LoadingThreadFunc(LPVOID param) {
	InvasionTrivia* pIT = (InvasionTrivia*)param;
	return pIT->LoadingThreadMemberFunc();
}


// Called to set overall system volume
void InvasionTrivia::SetVolumeLevel() {
	int dwSoundVolumeLevel = 0;
	switch (volumeLevel) {
		case vlNoSound: {
			dwSoundVolumeLevel = 0;
		break; }
		case vlLow: {
			dwSoundVolumeLevel = 22;
		break; }
		case vlMedium: {
			dwSoundVolumeLevel = 42;
		break; }
		case vlHigh: {
			dwSoundVolumeLevel = 64;
		break; }
	}
	Sound *snd = GetSound();
	snd->setVolume(dwSoundVolumeLevel);
}


// Set up the PointLevels array when a new game is started
void InvasionTrivia::SetUpGame(int diffLev) {
	// Start at the first point level wtih no mistakes
	currentPointLevel = 0;
	numberWrong				= 0;
	// Set up the things that are dependant on the current difficulty level setting
	switch (diffLev) {
		case dlEasy: {
			maxWrongAllowed			 = 2;
			numberPointLevels		 = 15;
			timeToAnswer				 = 60;
			lllBeamABrelnar			 = true;
			lllAskTheAndromedans = true;
			lllMatterAntimatter  = false;
			lllBookOfKnowledge	 = false;
			CharacterInUse       = ctNone;
			wcscpy(PointLevels[0].valueText,  L"1");
			wcscpy(PointLevels[1].valueText,  L"50");
			wcscpy(PointLevels[2].valueText,  L"75");
			wcscpy(PointLevels[3].valueText,  L"100");
			wcscpy(PointLevels[4].valueText,  L"500");
			wcscpy(PointLevels[5].valueText,  L"1000");
			wcscpy(PointLevels[6].valueText,  L"5000");
			wcscpy(PointLevels[7].valueText,  L"10000");
			wcscpy(PointLevels[8].valueText,  L"32000");
			wcscpy(PointLevels[9].valueText,  L"83456.12");
			wcscpy(PointLevels[10].valueText, L"100000");
			wcscpy(PointLevels[11].valueText, L"184174");
			wcscpy(PointLevels[12].valueText, L"500666");
			wcscpy(PointLevels[13].valueText, L"888888");
			wcscpy(PointLevels[14].valueText, L"1000000");
		break; }
		case dlNormal: {
			maxWrongAllowed			 = 1;
			numberPointLevels		 = 20;
			timeToAnswer				 = 45;
			lllBeamABrelnar			 = true;
			lllAskTheAndromedans = true;
			lllMatterAntimatter  = true;
			lllBookOfKnowledge	 = false;
			CharacterInUse       = ctNone;
			wcscpy(PointLevels[0].valueText,  L"1/2");
			wcscpy(PointLevels[1].valueText,  L"1");
			wcscpy(PointLevels[2].valueText,  L"3.14159");
			wcscpy(PointLevels[3].valueText,  L"50");
			wcscpy(PointLevels[4].valueText,  L"100");
			wcscpy(PointLevels[5].valueText,  L"250");
			wcscpy(PointLevels[6].valueText,  L"500");
			wcscpy(PointLevels[7].valueText,  L"750");
			wcscpy(PointLevels[8].valueText,  L"1000");
			wcscpy(PointLevels[9].valueText,  L"2500");
			wcscpy(PointLevels[10].valueText, L"5000");
			wcscpy(PointLevels[11].valueText, L"10000");
			wcscpy(PointLevels[12].valueText, L"16384");
			wcscpy(PointLevels[13].valueText, L"65535");
			wcscpy(PointLevels[14].valueText, L"83456.12");
			wcscpy(PointLevels[15].valueText, L"100000");
			wcscpy(PointLevels[16].valueText, L"250000");
			wcscpy(PointLevels[17].valueText, L"500666");
			wcscpy(PointLevels[18].valueText, L"750000");
			wcscpy(PointLevels[19].valueText, L"1000000");
		break; }
		case dlHard: {
			maxWrongAllowed			 = 0;
			numberPointLevels		 = 25;
			timeToAnswer				 = 30;
			lllBeamABrelnar			 = true;
			lllAskTheAndromedans = true;
			lllMatterAntimatter  = true;
			lllBookOfKnowledge	 = true;
			CharacterInUse       = ctNone;
			wcscpy(PointLevels[0].valueText,  L"1/2");
			wcscpy(PointLevels[1].valueText,  L"1");
			wcscpy(PointLevels[2].valueText,  L"3.14159");
			wcscpy(PointLevels[3].valueText,  L"50");
			wcscpy(PointLevels[4].valueText,  L"75");
			wcscpy(PointLevels[5].valueText,  L"100");
			wcscpy(PointLevels[6].valueText,  L"250");
			wcscpy(PointLevels[7].valueText,  L"500");
			wcscpy(PointLevels[8].valueText,  L"750");
			wcscpy(PointLevels[9].valueText,  L"1000");
			wcscpy(PointLevels[10].valueText, L"1001");
			wcscpy(PointLevels[11].valueText, L"2500");
			wcscpy(PointLevels[12].valueText, L"5000");
			wcscpy(PointLevels[13].valueText, L"10000");
			wcscpy(PointLevels[14].valueText, L"16384");
			wcscpy(PointLevels[15].valueText, L"32000");
			wcscpy(PointLevels[16].valueText, L"65535");
			wcscpy(PointLevels[17].valueText, L"83456.12");
			wcscpy(PointLevels[18].valueText, L"100000");
			wcscpy(PointLevels[19].valueText, L"184174");
			wcscpy(PointLevels[20].valueText, L"250000");
			wcscpy(PointLevels[21].valueText, L"500666");
			wcscpy(PointLevels[22].valueText, L"750000");
			wcscpy(PointLevels[23].valueText, L"888888");
			wcscpy(PointLevels[24].valueText, L"1000000");
		break; }
	}
}


// Gets the path of the executable
DWORD InvasionTrivia::GetModuleDirectory(HMODULE hModule, LPTSTR szPath, DWORD dwLength) {
	DWORD dwLen;
	LPTSTR p;
	if (0 == (dwLen = GetModuleFileName(hModule, szPath, dwLength))) {
		return(0);
	}
	p = szPath + dwLen;
	while (p != szPath) {
		if (TEXT('\\') == *--p) {
			*(++p) = 0;
			break;
		}
	}
	return(p - szPath);
}


// Fills the QACFiles directory with a list of all .QAC files in the EXE's directory
void InvasionTrivia::GetDirectoryContents(TCHAR* pszDirectory) {
	TCHAR myDir[MAX_PATH + 2] = L"";
	wcscpy(myDir, pszDirectory);
	wcscat(myDir, L"*.qac");
	for (int i = 0; i < 100; i++) {
		wcscpy(QACFiles[i].fileName, L"");
	}
	i = 0;
	wcscpy(QACFiles[0].fileName, L"Built-In");
	QACFiles_Count = 0;
	WIN32_FIND_DATA findData;
  HANDLE fileHandle;
	// Get the first file in the directory
	fileHandle = FindFirstFile(myDir, &findData);
	if (fileHandle != INVALID_HANDLE_VALUE) {
		wcsncpy(QACFiles[i + 1].fileName, findData.cFileName, wcslen(findData.cFileName) - 4);
		i++;
		// Loop on all remaining entries in the directory
		while (FindNextFile(fileHandle, &findData)) {
			wcsncpy(QACFiles[i + 1].fileName, findData.cFileName, wcslen(findData.cFileName) - 4);
			i++;
		}
	}
	// All done, everything worked.
	QACFiles_Count = i;
	FindClose(fileHandle);
}


// Reads in the High Scores & Settings file, creates a new one if not found in current directory
bool InvasionTrivia::readHSSFile() {
	TCHAR fileName[MAX_PATH] = L"";
	wcscat(fileName, game.gameEXEPath);
	wcscat(fileName, L"hss.hss");
	int j	= 0;
	// Set up default values in case of problems
	wcscpy(HighScoreEasy.playerName, L"None");
	HighScoreEasy.pointLevelReached = 0;
	HighScoreEasy.characterUsed = 0;
	wcscpy(HighScoreNormal.playerName, L"None");
	HighScoreNormal.pointLevelReached = 0;
	HighScoreNormal.characterUsed = 0;
	wcscpy(HighScoreHard.playerName, L"None");
	HighScoreHard.pointLevelReached = 0;
	HighScoreHard.characterUsed = 0;
	// Open the high scores file
	HANDLE hFile = CreateFile(fileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_HIDDEN, NULL);
	// It doesn't exist, so create and default-populate it
	if (hFile == INVALID_HANDLE_VALUE) {
		return writeHSSFile();
	// File was opened OK, read in the data (make sure it's valid first)
	} else {
		DWORD dwFileSize = GetFileSize(hFile, NULL);
		unsigned char* pHSS = (unsigned char*)malloc(dwFileSize);
		DWORD numBytesRead = 1;
		int bResult = ReadFile(hFile, pHSS, dwFileSize, &numBytesRead, NULL);
		CloseHandle(hFile);
		if (bResult == 0 || numBytesRead != dwFileSize) {
			return false;
		}
		// Parse the file.  First, get the header and make sure it's valid
		TCHAR headerID[8] = L"";
		headerID[0] = *pHSS++;
		headerID[1] = *pHSS++;
		headerID[2] = *pHSS++;
		headerID[3] = *pHSS++;
		headerID[4] = *pHSS++;
		headerID[5] = NULL;
		if (wcscmp(headerID, L"ITHSS")) {
			return false;
		}
		// Now get the major and minor version and make sure we can use it with the EXE version.
		int majorVersion = *pHSS++;
		int minorVersion = *pHSS++;
		if (majorVersion != 1) {
			return false;
		}
		if (minorVersion != 0) {
			return false;
		}
		// Font index
		fontIndex = *pHSS++;
		pFont = pFonts[fontIndex];
		// Volume level
		volumeLevel = *pHSS++;
		// Skip past expansion buffer area
		pHSS = pHSS + 9;
		// Easy entry
		HighScoreEasy.pointLevelReached = *pHSS++;
		for (j = 0; j < 10; j++) { HighScoreEasy.playerName[j] = *pHSS++;	}
		HighScoreEasy.characterUsed = *pHSS++;
		// Normal entry
		HighScoreNormal.pointLevelReached = *pHSS++;
		for (j = 0; j < 10; j++) { HighScoreNormal.playerName[j] = *pHSS++;	}
		HighScoreNormal.characterUsed = *pHSS++;
		// Hard entry
		HighScoreHard.pointLevelReached = *pHSS++;
		for (j = 0; j < 10; j++) { HighScoreHard.playerName[j] = *pHSS++;	}
		HighScoreHard.characterUsed = *pHSS++;
		return true;
	}
}


// Writes out the High Scores & Settings file, creates a new one if not found in current directory
bool InvasionTrivia::writeHSSFile() {
	TCHAR fileName[MAX_PATH + 2] = L"";
	wcscat(fileName, game.gameEXEPath);
	wcscat(fileName, L"hss.hss");
	int i	= 0;
	int j	= 0;
	// Create the HSS file
	HANDLE hFile = CreateFile(fileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_HIDDEN, NULL);
	DWORD bytesWritten = 0;
	int outBufferSize = 53;
	unsigned char* outBuffer = (unsigned char*)malloc(outBufferSize);
	int indexer = 0;
	// Header
	*(outBuffer + indexer++) = 'I';
	*(outBuffer + indexer++) = 'T';
	*(outBuffer + indexer++) = 'H';
	*(outBuffer + indexer++) = 'S';
	*(outBuffer + indexer++) = 'S';
	// Major version
	*(outBuffer + indexer++) = 1;
	// Minor version
	*(outBuffer + indexer++) = 0;
	// Font index
	*(outBuffer + indexer++) = (unsigned char)fontIndex;
	// Volume level
	*(outBuffer + indexer++) = (unsigned char)volumeLevel;
	// Expansion padding
	for (i = 0; i < 9; i++) {
		*(outBuffer + indexer++) = 32;
	}
	// Easy entry
	*(outBuffer + indexer++) = HighScoreEasy.pointLevelReached;
	for (j = 0; j < 10; j++) { *(outBuffer + indexer++) = (unsigned char)HighScoreEasy.playerName[j];	}
	*(outBuffer + indexer++) = (unsigned char)HighScoreEasy.characterUsed;
	// Normal entry
	*(outBuffer + indexer++) = HighScoreNormal.pointLevelReached;
	for (j = 0; j < 10; j++) { *(outBuffer + indexer++) = (unsigned char)HighScoreNormal.playerName[j]; }
	*(outBuffer + indexer++) = (unsigned char)HighScoreNormal.characterUsed;
	// Hard entry
	*(outBuffer + indexer++) = HighScoreHard.pointLevelReached;
	for (j = 0; j < 10; j++) { *(outBuffer + indexer++) = (unsigned char)HighScoreHard.playerName[j]; }
	*(outBuffer + indexer++) = (unsigned char)HighScoreHard.characterUsed;
	// Write out the buffer
	if (WriteFile(hFile, outBuffer, outBufferSize, &bytesWritten, NULL) == 0) {
		return false;
	}
	CloseHandle(hFile);
	return true;
}


// See if player got high score for the just completed game (called from SceneEnder of Player Wins
// scenes).  If they did, return true, otherwise return false;
bool InvasionTrivia::SeeIfPlayerGotHighScore() {
	if (difficultyLevel == dlEasy) {
		if (currentPointLevel > HighScoreEasy.pointLevelReached) { return true; }
	}
	if (difficultyLevel == dlNormal) {
		if (currentPointLevel > HighScoreNormal.pointLevelReached) { return true; }
	}
	if (difficultyLevel == dlHard) {
		if (currentPointLevel > HighScoreHard.pointLevelReached) { return true; }
	}
	return false;
}


// ************************************************************************************************
// WinMain
// ************************************************************************************************
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPTSTR, int) {
	hInst = hInstance;
	_Module.Init(0, hInstance);
  game.Run();
  return 0;
}
