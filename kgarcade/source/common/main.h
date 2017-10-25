

//#define _TEST_ 1        // Turns this into a test build (includes extra menu options in spots)

// ****************************************************************************************************************
// Defines
// ****************************************************************************************************************
#define vlNoSound								0    // Volume Level: No Sound
#define vlLow                   1    // Volume Level: Low
#define vlMedium                2    // Volume Level: Medium
#define vlHigh                  3    // Volume Level: High
#define csFirstTimeInits        5    // First time inits that require backbuffer
#define csIntroClickgamer				13	 // Current scene:  Clickgamer intro
#define csIntroOmnytex					10	 // Current scene:  Omnytex intro
#define csIntroCrackhead				11	 // Current scene:  Crackhead intro
#define csTitleSequence 				12	 // Current scene:  Title sequence
#define csMainMenu							20	 // Current screen: Main menu
#define csWalkingAroundTheShip	30   // Current screen: Walking around the ship
#define csOptions         			42   // Current screen: Options screen
#define csCredits         			46   // Current screen: Credits screen
#define csNewGameType     			47   // Current screen: New Game Type
#define csInstructions     			48   // Current screen: Instructions
#define csHighScores      			49   // Current screen: High Scores
#define csExiting               50   // Exiting the program
#define csInMemoria							101  // Current screen: mini-game
#define csFlightOfDoom					102  // Current screen: mini-game
#define csReluctantHero					103  // Current screen: mini-game
#define csRefluxive							104  // Current screen: mini-game
#define csCosmicSquirrel				105  // Current screen: mini-game
#define csDefendoh							106  // Current screen: mini-game
#define csADayInTheStrife				107  // Current screen: mini-game
#define csLeparLand							108  // Current screen: mini-game
#define csDeathTrap							109  // Current screen: mini-game
#define csCopyCat								110  // Current screen: mini-game
#define csVirus									111  // Current screen: mini-game
#define csGlutton								112  // Current screen: mini-game
#define csConquerror						113  // Current screen: mini-game
#define csAntigravitator				114  // Current screen: mini-game
#define csFarOutFowl						115  // Current screen: mini-game
#define csTheEscape							116  // Current screen: mini-game
#define csAlienBabble						117  // Current screen: mini-game
#define csTheRedeyeOrder				118  // Current screen: mini-game
#define csFfopirSirtetPaehc			119  // Current screen: mini-game
#define csEngineer							120  // Current screen: mini-game
#define csTheBogazDerby					121  // Current screen: mini-game
#define csSquishem	    				122  // Current screen: mini-game
#define csTroubleInVectropolis	123  // Current screen: mini-game
#define csMuncherDude 		      124  // Current screen: mini-game
#define csSonOfEliminator	      125  // Current screen: mini-game
#define csFinalScore        		126  // Current screen: final score
#define csPlayerDied			  		150  // Cut Scene: player died
#define csNewAdventure		  		151  // Cut Scene: starting a new adventure
#define csWin			          		152  // Cut Scene: player won
#define csCharacterInteraction  160  // When doing a character interaction
#define mgsInitialDraw					1000 // Mini-game state
#define mgsGetReady							1001 // Mini-game state
#define mgsGameRunning					1002 // Mini-game state
#define mgsGameOver							1003 // Mini-game state
#define mgsInstructions					1004 // Mini-game state
#define mgsEnding			  				1005 // Mini-game state
#define gmMiniGameMelee         2005 // Game mode
#define gmAdventureGame         2006 // Game mode
#define gsmTimed                2010 // Mini-game sub-mode
#define gsmAlaCarte             2011 // Mini-game sub-mode
#define lhNothing               0    // Action the left hand was performing last frame
#define lhNorth                 1    // Action the left hand was performing last frame
#define lhSouth                 2    // Action the left hand was performing last frame
#define lhEast                  3    // Action the left hand was performing last frame
#define lhWest                  4    // Action the left hand was performing last frame
#define lhNorthEast             5    // Action the left hand was performing last frame
#define lhNorthWest             6    // Action the left hand was performing last frame
#define lhSouthEast             7    // Action the left hand was performing last frame
#define lhSouthWest             8    // Action the left hand was performing last frame
#define rhNothing               0    // Action the right hand was performing last frame
#define rhDown                  1    // Action the right hand was performing last frame
#define xadj                    20   // Horizontal adjustment for mini-games
#define yadj                    20   // Vertical adjustment for mini-games


// ****************************************************************************************************************
// Includes
// ****************************************************************************************************************
#include "GapiApplication.h"
#include "GapiDrawExtension.h"
#include "resource.h"
#include "HSS.h"


// ****************************************************************************************************************
// Required pragmas for proper linker execution
// ****************************************************************************************************************
#pragma comment(lib, "gd300.lib")
#pragma comment(lib, "hss.lib")


// ************************************************************************************************
// Structs
// ************************************************************************************************
struct OASIS_ACTOR {
	CGapiSurface* image; // Pointer to the image of this actor
};

struct OASIS_TEXTACTOR {
	int resourceID; // ID of the string in the String Table resource
};

struct OASIS_PLAYER {
  unsigned char		 actorID;	 // ID matching the ID in the OASIS_Actors array of this player
	bool             hidden;   // True if the player is not on the screen, false otherwise
	signed short int locX;		 // Horizontal location of player
	signed short int locY;     // Vertical location of player
};

struct OASIS_AUDIOACTOR {
	hssSound*	soundFX; // Pointer to the hssSound itself
	int				channel; // hssChannel number the audio actor is currently playing on as returned by playSound
};

struct KGAFILE {
  DWORD							 kUp;                          // Key code mapped to UP
  DWORD							 kDown;                        // Key code mapped to DOWN
  DWORD							 kLeft;                        // Key code mapped to LEFT
  DWORD							 kRight;                       // Key code mapped to RIGHT
  DWORD							 kAction;                      // Key code mapped to ACTION
  DWORD							 kCommand;                     // Key code mapped to COMMAND
	POINT							 playerPosition;               // Player position
	POINT							 ulTile;                       // Upper left-hand tile
  unsigned char			 volumeLevel;                  // Overall volume level
  unsigned char			 currentLevel;                 // Current level of the saved game
  unsigned char			 playerHealth;                 // Current health of the player for the saved game
  bool							 miniGameLockFlags[32];        // Flags to tell if each mini-game is unlocked and available in Melee Mode
  bool							 gameSavedFlag;                // Flag: Has a game been saved?
  bool							 miniGamesCompletedFlags[7];   // Flags to tell if each mini-game on the current level has been completed
	bool							 levelHintDone;                // Flag: Has the hint for the current level been given by the captive yet?
  int								 kgaFileVersion;               // Version number of KGA file, for forward-compatibility
  int								 tileOffsetH;                  // Horizontal tile offest
  int								 tileOffsetV;                  // Vertical tile offset
  unsigned long int  overall_score;                // The overall score of the current game
	unsigned long int  miniGameHighsTimed[32];			 // Saved high scores for the mini-games in Timed mode
	unsigned long int  miniGameHighsPUISS[32];			 // Saved high scores for the mini-games in Play Until I Say Stop mode
};


// ****************************************************************************************************************
// Game class definition
// ****************************************************************************************************************
class CGame : public CGapiApplication {

	public:

		// Properties
		bool               new_high_score;                   // Used in doGameOver() method to display the New High Score text when applicable
		int                current_mini_game;                // Tells what mini-game is being played in melee mode (index into melee_selection, game_unlocked and mini_game_info arrays)
		unsigned long int  miniGameHighsTimed[32];           // High scores of each mini-game in Timed mode
		unsigned long int  miniGameHighsPUISS[32];           // High scores of each mini-game in Play Until I Say Stop mode
		bool							 grgsg;                            // Used to make Get Ready...Get Set...Go grow
		int								 grgsg_count;                      // Used to make Get Ready...Get Set...Go grow
		int								 gr_x1;                            // Used to make Get Ready...Get Set...Go grow
		int								 gr_x2;                            // Used to make Get Ready...Get Set...Go grow
		int								 gs_x1;                            // Used to make Get Ready...Get Set...Go grow
		int								 gs_x2;                            // Used to make Get Ready...Get Set...Go grow
		int								 g_x1;                             // Used to make Get Ready...Get Set...Go grow
		int								 grgsg_y1;                         // Used to make Get Ready...Get Set...Go grow
		int								 g_x2;                             // Used to make Get Ready...Get Set...Go grow
		int								 grgsg_y2;                         // Used to make Get Ready...Get Set...Go grow
    bool               startingNewGame;                  // Flag to tell whether we're starting a new game or not
    bool               game_over_check_done;             // Flag to tell us whether we've done the final checks during game over or not
    unsigned long int  overall_score;                    // The overall score of the current game
		TCHAR              popupLine1[27];                   // First line of a popup's text
		TCHAR              popupLine2[27];                   // Second line of a popup's text
    bool               levelHintDone;                    // Flag: Has the hint for the current level been given by the captive yet?
    int                lightChangeCounter;               // Used to delay between mini-game frame light changes
		int                previous_level;                   // The level we are leaving, used for deletions
		hssSound*					 sfxMusicTheme;                    // Pointer to our theme music
		bool							 themePlaying;                     // Is the theme music currently playing?
		DWORD              kUp;                              // Internal key mapping value
		DWORD              kDown;                            // Internal key mapping value
		DWORD              kLeft;                            // Internal key mapping value
		DWORD              kRight;                           // Internal key mapping value
		DWORD              kAction;                          // Internal key mapping value
		DWORD              kCommand;                         // Internal key mapping value
		bool               show_fps;                         // Flag; Show FPS?
		bool               show_frame_time;                  // Flag: Show frame time?
		bool               gameRestarted;                    // Flag: Are we continuing a game?
		POINT              cl_player_position;               // Echoes player_position in Walking Around The Ship at class-level
		POINT              cl_ul_tile;                       // Echoes ul_tile in Walking Around The Ship at class-level
		int                cl_horizontal_offset;             // Horizontal offset of tiles in Walking Around The Ship at class-level
		int                cl_vertical_offset;               // Vertical offset of tiles in Walking Around The Ship at class-level
		TCHAR              gameEXEPath[154];                 // Path to the executable
		int                common_init_counter;              // Used during common mini-game loading
		int                common_cleanup_counter;           // Used during common mini-game cleanup
		bool               status_first_time;                // Flag: is this the first time through the updateStatus method?
    bool               jumpBackToNewGameType;            // Set to jump back to new game type after mini-game
		void					     (CGame::*popupCallback)(int);     // Callback that popup calls when done
		int							   game_submode;                     // Sub-mode of mini-game in melee mode
    TCHAR              mgInstructions[34][34];           // Instructions common
    int                mgInstructionsPage;               // What page of instructions a mini-game is currently showing
    bool               mgiPrevTapped;                    // Mini-game instructions arrows
    bool               mgiNextTapped;                    // Mini-game instructions arrows
    int                fuzzIndex;                        // Which fuzz image is being displayed
		int							   game_mode;										     // Mode of game... gmMiniGameMelee or gmAdventureGame
		int							   melee_selection[34];              // Current game values for selecting a mini-game in melee mode
		bool						   game_unlocked[34];                // Holds true if a particular mini-game is unlocked, false otherwise
    TCHAR              mini_game_info[34][7][132];       // NAmes & descriptions of mini-games on New Game Selection screen
    int                volumeLevel;                      // Volume level
		int							   whichGameBeingPlayed;             // Stores which mini-game on a level (0-4) is being played, used to set the flag if the player wins
		bool						   games_done[8];                    // Flag for each of the 5 games on a level, if they have been completed or not
    bool               processEvents;                    // Flag: when true, key events are processed, they're not when false
    int                ExitCounter;                      // Used during program exit for TV turn-off effect
    int                ExitFadeCounter;                  // Used during program exit for TV turn-off effect
    int                shutdownStep;                     // Used during program exit for TV turn-off effect
    int                bbCenterPoint;                    // Center point of backbuffer->  Used to center things.
    int                health;                           // The current health of the player: 0 = dead, 12 = full heatlh
    int                total_points;                     // Total points player has for the game
    int                points_this_level;                // Total points player has for the current level
    int                fade_function;                    // Used for fading between screens
    int                fade_value;                       // Used for fading between screens
    int                next_screen;                      // Used for fading between screens
		bool               loading;										       // Flag that tells us whether the current screen is loading or not
		int						     loading_step;								     // What step the current loader is on
		bool					     destroying;									     // Flag that tells us whether the current screen is being destroyed or not
		int						     destroying_step;						       // What step the current destroyer is on
		int						     screen_after_destroy;				     // Tells what screen will be shown after the current destroyer is done
		int						     current_screen;							     // The current screen that is showing
		int							   current_level;								     // The current level of the ship player is on
		bool						   current_level_initialized;        // Flag: Has the current level of the ship been initalized?
		int						     countdown_seconds;					       // Counts the number of seconds remaining in a game
		int						     countdown_ticks;						       // Used to determine when a second has passed
		int						     mini_game_state;						       // Tells us what the current mini-game is currently doing.  See defines above.
		int						     get_ready_counter;					       // Counts frames used to display get ready...set...go on mini-games
		int						     game_over_counter;					       // Counts frames used to display game over on mini-games
		unsigned long int  mini_game_score;						       // Players' score on the currently playing mini-game
		unsigned long int  mini_game_score_last;             // Score of the mini-game last frame
		bool					     player_dir_north;						     // Flag: is player moving north?
		bool					     player_dir_south;						     // Flag: is player moving south?
		bool					     player_dir_east;						       // Flag: is player moving east?
		bool					     player_dir_west;						       // Flag: is player moving west?
		bool						   player_button_down;               // Flag: is the button currently held down?
    int                player_left_hand_action;          // The action the left hand was performing last frame
    int                player_right_hand_action;         // The action the right hand was performing last frame
    int						     player_dir_delay;						     // Used to slow down repeat key events
		bool					     force_game_over;					         // Set to true to end a game before time runs out
		bool					     clear_game_surface;					     // Set to true to clear the game surface with every frame, false to not
		int							   h_offset;                         // Used for scrolling menu and related screens background
		int							   v_offset;                         // Used for scrolling menu and related screens background
		int                gpButtonPressed;                  // What button is pressed on a popup
    bool               gpBlendDone;                      // If the initial blend is done for a popup
    int                gpCurrentOption;                  // Currently showing option in popup
    CGapiSurface*		   gpTempBlended;                    // Temp surface for blend for popup
    TCHAR              gpOptions[14][24];                // Options for popup
    int                gpOptionsCount;                   // Number of options used in popup
		bool						   doPopup;                          // Flag: are we currently doing a popup?
    POINT					     player_pos;									     // Current position of the player
		CGapiBitmapFont    font1;      									     // The first bitmap font
    CGapiBitmapFont    font1_green;									     // The first bitmap font with a green gradient
    hssSpeaker  	     sndObj;									         // One and only instance of the sound system object
    hssSound*			     sfxUnlockCode;	  	  					   // Sound heard when the mini-game unlock code is used
    hssSound*			     sfxGameExitSound;							   // Sound heard when exiting the game
    hssSound*			     sfxMisc1;							           // Misc SFX 1
    hssSound*			     sfxMisc2;							           // Misc SFX 2
    hssSound*			     sfxMisc3;							           // Misc SFX 3
    hssSound*			     sfxMisc4;							           // Misc SFX 4
    hssSound*			     sfxMisc5;							           // Misc SFX 5
		hssSound*			     sfx_ins_arrow;                    // Arrow sound on instructions screen
		CGapiSurface*	     get_ready;									       // Get Ready (Common to all games)
    CGapiSurface*	     get_set;										       // Get Set (Common to all games)
    CGapiSurface*	     go;													     // Go (Common to all games)
    CGapiSurface*      fuzz[10];                         // Fuzz for mini-games (Common to all games)
    CGapiSurface*	     mini_game_frame;						       // Frame around mini-games
    CGapiSurface*	     mini_game_frame_l1;						   // Lights for the mini-game frame
    CGapiSurface*	     mini_game_frame_l2;						   // Lights for the mini-game frame
    CGapiSurface*	     mini_game_frame_l3;						   // Lights for the mini-game frame
    CGapiSurface*	     mini_game_frame_l4;						   // Lights for the mini-game frame
    CGapiSurface*	     mini_game_frame_l5;						   // Lights for the mini-game frame
    CGapiSurface*	     mini_game_frame_r1;						   // Lights for the mini-game frame
    CGapiSurface*	     mini_game_frame_r2;						   // Lights for the mini-game frame
    CGapiSurface*	     mini_game_frame_r3;						   // Lights for the mini-game frame
    CGapiSurface*	     mini_game_frame_r4;						   // Lights for the mini-game frame
    CGapiSurface*	     mini_game_frame_r5;						   // Lights for the mini-game frame
    CGapiSurface*	     status_bar;									     // Image of the 3-D status bar in mini-games (Common to all games)
	  CGapiSurface*	     left_hand_normal;                 // Image of joystick hand not moving (Common to all games)
	  CGapiSurface*	     left_hand_left;                   // Image of joystick hand going left (Common to all games)
	  CGapiSurface*	     left_hand_right;                  // Image of joystick hand going right (Common to all games)
	  CGapiSurface*	     left_hand_up;                     // Image of joystick hand going up (Common to all games)
	  CGapiSurface*	     left_hand_down;                   // Image of joystick hand going down (Common to all games)
	  CGapiSurface*	     left_hand_ul;                     // Image of joystick hand going up-left (Common to all games)
	  CGapiSurface*	     left_hand_ur;                     // Image of joystick hand going up-right (Common to all games)
	  CGapiSurface*	     left_hand_dl;                     // Image of joystick hand going down-left (Common to all games)
	  CGapiSurface*	     left_hand_dr;                     // Image of joystick hand going down-right (Common to all games)
	  CGapiSurface*	     right_hand_up;                    // Image of joystick hand going up (Common to all games)
	  CGapiSurface*	     right_hand_down;                  // Image of joystick hand going down (Common to all games)
	  CGapiSurface*	     console_left;                     // Left side of hands console (Common to all games)
	  CGapiSurface*	     console_middle;                   // Middle of hands consol between hands (Common to all games)
	  CGapiSurface*	     console_right;                    // Right side of hands console (Common to all games)
    CGapiSurface*      background_tile;                  // Used for scrolling menu and related screens background
		CGapiSurface*		   menu_top;                         // Main menu
		CGapiSurface*		   menu_bottom;                      // Main menu
		CGapiSurface*		   menu_new_game_0;                  // Main menu
		CGapiSurface*		   menu_new_game_1;                  // Main menu
		CGapiSurface*		   menu_continue_game_0;             // Main menu
		CGapiSurface*		   menu_continue_game_1;             // Main menu
		CGapiSurface*		   menu_instructions_0;              // Main menu
		CGapiSurface*		   menu_instructions_1;              // Main menu
		CGapiSurface*		   menu_high_scores_0;               // Main menu
		CGapiSurface*		   menu_high_scores_1;               // Main menu
		CGapiSurface*		   menu_options_0;                   // Main menu
		CGapiSurface*		   menu_options_1;                   // Main menu
		CGapiSurface*		   menu_credits_0;                   // Main menu
		CGapiSurface*		   menu_credits_1;                   // Main menu
		CGapiSurface*		   menu_quit_0;                      // Main menu
		CGapiSurface*		   menu_quit_1;                      // Main menu
		CGapiSurface*		   menu_title;                       // Main menu
    CGapiSurface*      screenshots[28];                  // Screenshots
    CGapiSurface*		   icon_mini_game_melee;             // Icon for New Game Selection screen
    CGapiSurface*		   icon_adventure_game;              // Icon for New Game Selection screen
    CGapiSurface*		   arrow_left_00;                    // Arrow for New Game Selection screen
    CGapiSurface*		   arrow_right_00;                   // Arrow for New Game Selection screen
		CGapiSurface*		   arrow_left_01;                    // Arrow for New Game Selection screen
    CGapiSurface*		   arrow_right_01;                   // Arrow for New Game Selection screen
		CGapiSurface*		   gfxLock;											     // Lock for locked mini-games
		CGapiSurface*		   gfx_ins_prev_0;								   // Arrow on instruction screen
		CGapiSurface*		   gfx_ins_prev_1;								   // Arrow on instruction screen
		CGapiSurface*		   gfx_ins_next_0;								   // Arrow on instruction screen
		CGapiSurface*		   gfx_ins_next_1;								   // Arrow on instruction screen
		CGapiSurface*		   popup_border;                     // Popup window
    CGapiSurface*		   divider_00;                       // Divider line
    int                unlockCornerUL;
    int                unlockCornerUR;

		// Misellaneous methods
    static DWORD       getStorageMemory                  ();
    static DWORD       getProgramMemory                  ();
    void               startNewLevel                     (int current_level);
    void						   popupCallbackVerifyNewGame				 (int option);
		void               setupForNewGame                   ();
    void               loadSFX                           (TCHAR* location, int iResult);
    void               createFont                        (TCHAR* location, HRESULT hResult);
    void               createSurface                     (TCHAR* location, HRESULT hResult);
		bool							 readKGAFile                       ();
		bool							 writeKGAFile                      (bool hasGameStarted, bool initialCreation);
		DWORD							 GetModuleDirectory                (HMODULE hModule, LPTSTR szPath, DWORD dwLength);
    void               miniGameCommandButtonHandler      ();
    void						   popupCallbackMiniGame				     (int option);
    void						   kdMGInstructions						       (DWORD dwKey);
		void						   kuMGInstructions						       (DWORD dwKey);
		void						   sdMGInstructions						       (POINT p);
		void						   suMGInstructions						       (POINT p);
    void               kdPopup                           (DWORD dwKey);
    void               kuPopup                           (DWORD dwKey);
		void						   sdPopup        							     (POINT p);
		void						   suPopup		    							     (POINT p);
		void						   startPopup                        (TCHAR* line1, TCHAR* line2);
		void						   pnfPopup											     (CGapiSurface* backbuffer);
    void               setVolumeLevel                    ();
    void               screenFader                       ();
		void						   countdownStartClock					     ();
		void						   doCommonInit								       ();
    void               doCommonCleanup                   ();
		bool						   updateStatusBar							     (CGapiSurface* backbuffer);
		void						   updateMiniGameFrameLights				 (CGapiSurface* backbuffer);
    bool						   updateHands									     (CGapiSurface* backbuffer);
		void						   doGetReady									       (CGapiSurface* backbuffer, TCHAR* game_name, TCHAR* target_score);
		void						   doGameOver									       (CGapiSurface* backbuffer, int next_screen, unsigned long int target_score);
		void						   doInitialDraw								     (CGapiSurface* backbuffer);
		void						   addToScore								         (unsigned long int value);
		void						   subtractFromScore						     (unsigned long int value);
		void						   doLoad											       ();
		void						   doDestroy										     (int sad);
		void						   showLoadingScreen						     (CGapiSurface* backbuffer, bool showStuff, bool clearScreen);
		void						   doInstructions							       (CGapiSurface* backbuffer);
		void               scrollingBackground               (CGapiSurface* backbuffer);

		// Final Score
		void						   loadFinalScore 							     (CGapiSurface* backbuffer);
		void						   destroyFinalScore  						   (CGapiSurface* backbuffer);
		void						   pnfFinalScore  								   (CGapiSurface* backbuffer);
    void						   kuFinalScore  								     (DWORD dwKey);
		void						   suFinalScore		 							     (POINT p);

		// Clickgamer Intro
		void						   loadIntroClickgamer					     (CGapiSurface* backbuffer);
		void						   destroyIntroClickgamer 				   (CGapiSurface* backbuffer);
		void						   pnfIntroClickgamer							   (CGapiSurface* backbuffer);
    void						   kuIntroClickgamer						     ();
		void						   suIntroClickgamer						     ();

		// Omnytex Intro
		void						   loadIntroOmnytex							     (CGapiSurface* backbuffer);
		void						   destroyIntroOmnytex						   (CGapiSurface* backbuffer);
		void						   pnfIntroOmnytex								   (CGapiSurface* backbuffer);
    void						   kuIntroOmnytex								     ();
		void						   suIntroOmnytex  							     ();

		// Crackhead Intro
		void						   loadIntroCrackhead						     (CGapiSurface* backbuffer);
		void						   destroyIntroCrackhead					   (CGapiSurface* backbuffer);
		void						   pnfIntroCrackhead							   (CGapiSurface* backbuffer);
    void						   kuIntroCrackhead							     ();
		void						   suIntroCrackhead							     ();

		// Title sequence
		void						   loadTitleSequence							   (CGapiSurface* backbuffer);
		void						   destroyTitleSequence					     (CGapiSurface* backbuffer);
		void						   pnfTitleSequence							     (CGapiSurface* backbuffer);
    void						   kuTitleSequence								   ();
		void						   suTitleSequence							     ();

		// Main menu
		void						   loadMainMenu								       (CGapiSurface* backbuffer);
		void						   destroyMainMenu							     (CGapiSurface* backbuffer);
		void						   pnfMainMenu									     (CGapiSurface* backbuffer);
    void						   kdMainMenu      							     (DWORD dwKey);
    void						   kuMainMenu      							     (DWORD dwKey);
		void						   sdMainMenu      							     (POINT p);
		void						   suMainMenu      							     (POINT p);
		void						   popupCallbackMainMenuContinueGame (int option);

		// Options
		void						   pnfOptions									       (CGapiSurface* backbuffer);
    void						   kdOptions   	    						     (DWORD dwKey);
    void						   kuOptions       							     (DWORD dwKey);
		void						   sdOptions       							     (POINT p);
		void						   suOptions       							     (POINT p);
    void               optReset                          ();

		// Instructions
		void						   pnfInstructions							     (CGapiSurface* backbuffer);
    void						   kdInstructions   							   (DWORD dwKey);
    void						   kuInstructions   							   (DWORD dwKey);
		void						   sdInstructions  							     (POINT p);
		void						   suInstructions  							     (POINT p);
    void               insReset                          ();

		// Credits
		void						   pnfCredits									       (CGapiSurface* backbuffer);
    void						   kuCredits       							     (DWORD dwKey);
		void						   suCredits      							     (POINT p);
		void               crdReset                          ();

		// High Scores
		void						   pnfHighScores							       (CGapiSurface* backbuffer);
    void						   kuHighScores    							     (DWORD dwKey);
		void						   suHighScores    							     (POINT p);
		void               hisReset                          ();

		// New Game Type
		void						   pnfNewGameType								     (CGapiSurface* backbuffer);
    void						   kdNewGameType    							   (DWORD dwKey);
    void						   kuNewGameType    							   (DWORD dwKey);
		void						   sdNewGameType  							     (POINT p);
		void						   suNewGameType  							     (POINT p);
    void               ngtReset                          ();

		// Walking around the ship
		void						   loadWalkingAroundTheShip			     (CGapiSurface* backbuffer);
		void						   destroyWalkingAroundTheShip		   (CGapiSurface* backbuffer);
		void						   pnfWalkingAroundTheShip				   (CGapiSurface* backbuffer);
		void						   kdWalkingAroundTheShip				     (DWORD dwKey);
		void						   kuWalkingAroundTheShip				     (DWORD dwKey);
    void						   popupCallbackWalkingAroundTheShip (int option);

    // Character Interaction
    void               loadCharacterInteraction          (CGapiSurface* backbuffer);
    void               destroyCharacterInteraction       (CGapiSurface* backbuffer);
    void               pnfCharacterInteraction           (CGapiSurface* backbuffer);
    void               kdCharacterInteraction            (DWORD dwKey);
    void               kuCharacterInteraction            (DWORD dwKey);
		void               sdCharacterInteraction            (POINT p);
		void               suCharacterInteraction            (POINT p);

		// Scene: PlayerDied
		void						   loadPlayerDied  							     (CGapiSurface* backbuffer);
		void						   destroyPlayerDied   					     (CGapiSurface* backbuffer);
		void						   pnfPlayerDied   							     (CGapiSurface* backbuffer);
    void						   kuPlayerDied  								     ();
		void						   suPlayerDied    							     ();

		// Scene: Starting A New Adventure
		void						   loadNewAdventure							     (CGapiSurface* backbuffer);
		void						   destroyNewAdventure 					     (CGapiSurface* backbuffer);
		void						   pnfNewAdventure  						     (CGapiSurface* backbuffer);
    void						   kuNewAdventure								     ();
		void						   suNewAdventure  							     ();

		// Scene: Win
		void						   loadWin  							           (CGapiSurface* backbufferC);
		void						   destroyWin   					           (CGapiSurface* backbuffer);
		void						   pnfWin   							           (CGapiSurface* backbuffer);
    void						   kuWin  								           ();
		void						   suWin		      							     ();

		// Mini-games
    void						   endFlightOfDoom		      		     ();
		void						   initializeFlightOfDoom			       ();
		void						   loadFlightOfDoom						       (CGapiSurface* backbuffer);
		void						   destroyFlightOfDoom					     (CGapiSurface* backbuffer);
		void						   pnfFlightOfDoom							     (CGapiSurface* backbuffer);
		void						   kdFlightOfDoom							       (DWORD dwKey);
		void						   kuFlightOfDoom							       (DWORD dwKey);
		void						   endCosmicSquirrel		             ();
    void						   initializeCosmicSquirrel		       ();
		void						   loadCosmicSquirrel					       (CGapiSurface* backbuffer);
		void						   destroyCosmicSquirrel				     (CGapiSurface* backbuffer);
		void						   pnfCosmicSquirrel						     (CGapiSurface* backbuffer);
		void						   kdCosmicSquirrel						       (DWORD dwKey);
		void						   kuCosmicSquirrel						       (DWORD dwKey);
		void						   endADayInTheStrife	        	     ();
    void						   initializeADayInTheStrife		     ();
		void						   loadADayInTheStrife     		       (CGapiSurface* backbuffer);
		void						   destroyADayInTheStrife			       (CGapiSurface* backbuffer);
		void						   pnfADayInTheStrife					       (CGapiSurface* backbuffer);
		void						   kdADayInTheStrife						     (DWORD dwKey);
		void						   kuADayInTheStrife						     (DWORD dwKey);
    void						   initializeCopyCat						     ();
		void						   loadCopyCat     						       (CGapiSurface* backbuffer);
		void						   destroyCopyCat							       (CGapiSurface* backbuffer);
		void						   pnfCopyCat									       (CGapiSurface* backbuffer);
		void						   kdCopyCat										     (DWORD dwKey);
		void						   kuCopyCat										     (DWORD dwKey);
    void						   initializeTheRedeyeOrder			     ();
		void						   loadTheRedeyeOrder						     (CGapiSurface* backbuffer);
		void						   destroyTheRedeyeOrder					   (CGapiSurface* backbuffer);
		void						   pnfTheRedeyeOrder							   (CGapiSurface* backbuffer);
		void						   kdTheRedeyeOrder							     (DWORD dwKey);
		void						   kuTheRedeyeOrder							     (DWORD dwKey);
		void						   initializeInMemoria					     ();
		void						   loadInMemoria								     (CGapiSurface* backbuffer);
		void						   destroyInMemoria						       (CGapiSurface* backbuffer);
		void						   pnfInMemoria								       (CGapiSurface* backbuffer);
		void						   kdInMemoria									     (DWORD dwKey);
		void						   kuInMemoria									     (DWORD dwKey);
		void						   endReluctantHero			             ();
    void						   initializeReluctantHero			     ();
		void						   loadReluctantHero						     (CGapiSurface* backbuffer);
		void						   destroyReluctantHero				       (CGapiSurface* backbuffer);
		void						   pnfReluctantHero						       (CGapiSurface* backbuffer);
		void						   kdReluctantHero							     (DWORD dwKey);
		void						   kuReluctantHero							     (DWORD dwKey);
    void						   initializeRefluxive					     ();
		void						   loadRefluxive     					       (CGapiSurface* backbuffer);
		void						   destroyRefluxive						       (CGapiSurface* backbuffer);
		void						   pnfRefluxive								       (CGapiSurface* backbuffer);
		void						   kdRefluxive									     (DWORD dwKey);
		void						   kuRefluxive									     (DWORD dwKey);
		void						   endDefendoh		      			       ();
    void						   initializeDefendoh					       ();
		void						   loadDefendoh     						     (CGapiSurface* backbuffer);
		void						   destroyDefendoh							     (CGapiSurface* backbuffer);
		void						   pnfDefendoh									     (CGapiSurface* backbuffer);
		void						   kdDefendoh									       (DWORD dwKey);
		void						   kuDefendoh									       (DWORD dwKey);
		void						   endLeparLand			        		     ();
    void						   initializeLeparLand					     ();
		void						   loadLeparLand     					       (CGapiSurface* backbuffer);
		void						   destroyLeparLand						       (CGapiSurface* backbuffer);
		void						   pnfLeparLand								       (CGapiSurface* backbuffer);
		void						   kdLeparLand									     (DWORD dwKey);
		void						   kuLeparLand									     (DWORD dwKey);
    void						   initializeDeathTrap					     ();
		void						   loadDeathTrap     					       (CGapiSurface* backbuffer);
		void						   destroyDeathTrap						       (CGapiSurface* backbuffer);
		void						   pnfDeathTrap								       (CGapiSurface* backbuffer);
		void						   kuDeathTrap									     (DWORD dwKey);
    void						   initializeVirus							     ();
		void						   loadVirus     							       (CGapiSurface* backbuffer);
		void						   destroyVirus								       (CGapiSurface* backbuffer);
		void						   pnfVirus										       (CGapiSurface* backbuffer);
		void						   kdVirus											     (DWORD dwKey);
		void						   kuVirus											     (DWORD dwKey);
    void						   initializeGlutton						     ();
		void						   loadGlutton     						       (CGapiSurface* backbuffer);
		void						   destroyGlutton							       (CGapiSurface* backbuffer);
		void						   pnfGlutton									       (CGapiSurface* backbuffer);
		void						   kdGlutton										     (DWORD dwKey);
		void						   kuGlutton										     (DWORD dwKey);
    void						   initializeConquerror				       ();
		void						   loadConquerror     					     (CGapiSurface* backbuffer);
		void						   destroyConquerror						     (CGapiSurface* backbuffer);
		void						   pnfConquerror								     (CGapiSurface* backbuffer);
		void						   kdConquerror								       (DWORD dwKey);
		void						   kuConquerror								       (DWORD dwKey);
    void						   initializeAntigravitator		       ();
		void						   loadAntigravitator 					     (CGapiSurface* backbuffer);
		void						   destroyAntigravitator				     (CGapiSurface* backbuffer);
		void						   pnfAntigravitator						     (CGapiSurface* backbuffer);
		void						   kdAntigravitator						       (DWORD dwKey);
		void						   kuAntigravitator						       (DWORD dwKey);
		void						   endFarOutFowl		      		       ();
    void						   initializeFarOutFowl				       ();
		void						   loadFarOutFowl 							     (CGapiSurface* backbuffer);
		void						   destroyFarOutFowl						     (CGapiSurface* backbuffer);
		void						   pnfFarOutFowl								     (CGapiSurface* backbuffer);
		void						   kdFarOutFowl								       (DWORD dwKey);
		void						   kuFarOutFowl								       (DWORD dwKey);
    void						   initializeTheEscape					     ();
		void						   loadTheEscape 							       (CGapiSurface* backbuffer);
		void						   destroyTheEscape						       (CGapiSurface* backbuffer);
		void						   pnfTheEscape								       (CGapiSurface* backbuffer);
		void						   kdTheEscape									     (DWORD dwKey);
		void						   kuTheEscape									     (DWORD dwKey);
		void						   endAlienBabble       				     ();
    void						   initializeAlienBabble				     ();
		void						   loadAlienBabble 						       (CGapiSurface* backbuffer);
		void						   destroyAlienBabble					       (CGapiSurface* backbuffer);
		void						   pnfAlienBabble							       (CGapiSurface* backbuffer);
		void						   kdAlienBabble									   (DWORD dwKey);
		void						   kuAlienBabble									   (DWORD dwKey);
    void						   initializeFfopirSirtetPaehc		   ();
		void						   loadFfopirSirtetPaehc				     (CGapiSurface* backbuffer);
		void						   destroyFfopirSirtetPaehc			     (CGapiSurface* backbuffer);
		void						   pnfFfopirSirtetPaehc					     (CGapiSurface* backbuffer);
		void						   kdFfopirSirtetPaehc						   (DWORD dwKey);
		void						   kuFfopirSirtetPaehc						   (DWORD dwKey);
    void						   initializeEngineer						     ();
		void						   loadEngineer									     (CGapiSurface* backbuffer);
		void						   destroyEngineer								   (CGapiSurface* backbuffer);
		void						   pnfEngineer										   (CGapiSurface* backbuffer);
		void						   kdEngineer										     (DWORD dwKey);
		void						   kuEngineer										     (DWORD dwKey);
		void						   endTheBogazDerby        			     ();
    void						   initializeTheBogazDerby 			     ();
		void						   loadTheBogazDerby							   (CGapiSurface* backbuffer);
		void						   destroyTheBogazDerby					     (CGapiSurface* backbuffer);
		void						   pnfTheBogazDerby							     (CGapiSurface* backbuffer);
		void						   kdTheBogazDerby								   (DWORD dwKey);
		void						   kuTheBogazDerby								   (DWORD dwKey);
    void						   initializeSquishem 			         ();
		void						   loadSquishem							         (CGapiSurface* backbuffer);
		void						   destroySquishem					         (CGapiSurface* backbuffer);
		void						   pnfSquishem							         (CGapiSurface* backbuffer);
		void						   kdSquishem								         (DWORD dwKey);
		void						   kuSquishem								         (DWORD dwKey);
		void						   endTroubleInVectropolis       	   ();
    void						   initializeTroubleInVectropolis	   ();
		void						   loadTroubleInVectropolis 			   (CGapiSurface* backbuffer);
		void						   destroyTroubleInVectropolis		   (CGapiSurface* backbuffer);
		void						   pnfTroubleInVectropolis				   (CGapiSurface* backbuffer);
		void						   kdTroubleInVectropolis					   (DWORD dwKey);
		void						   kuTroubleInVectropolis					   (DWORD dwKey);
    void						   endMuncherDude	                   ();
    void						   initializeMuncherDude	           ();
		void						   loadMuncherDude 			             (CGapiSurface* backbuffer);
		void						   destroyMuncherDude		             (CGapiSurface* backbuffer);
		void						   pnfMuncherDude				             (CGapiSurface* backbuffer);
		void						   kdMuncherDude					           (DWORD dwKey);
		void						   kuMuncherDude				             (DWORD dwKey);
		void						   loadSonOfEliminator 			         (CGapiSurface* backbuffer);
		void						   destroySonOfEliminator		         (CGapiSurface* backbuffer);
		void						   pnfSonOfEliminator				         (CGapiSurface* backbuffer);
		void						   kdSonOfEliminator					       (DWORD dwKey);
		void						   kuSonOfEliminator				         (DWORD dwKey);

    // Constructor
		CGame																				         (const GDAPPCONFIG& config);

		// Destructor
		virtual					   ~CGame											       ();

		// GapiDraw methods
		virtual HRESULT    InitInstance								       ();
		virtual HRESULT    ExitInstance								       ();
		virtual HRESULT    OnMinimize									       ();
		virtual HRESULT    OnRestore										     ();
	  virtual HRESULT    CreateSysMemSurfaces              (CGapiDisplay* display, HINSTANCE hInstance);
	  virtual HRESULT    CreateVidMemSurfaces              (CGapiDisplay* pDisplay, HINSTANCE hInstance);
	  virtual HRESULT    ProcessNextFrame                  (CGapiSurface* backbuffer, DWORD dwFlags);
		virtual HRESULT    KeyDown											     (DWORD dwKey, GDKEYLIST& keylist);
		virtual HRESULT    KeyUp												     (DWORD dwKey, GDKEYLIST& keylist);
    virtual HRESULT    StylusDown                        (POINT p);
		virtual HRESULT    StylusUp                          (POINT p);

		// OASIS properties
		OASIS_ACTOR			   OASIS_Actors[44];					       // Array of actors available for use in the scene
		OASIS_AUDIOACTOR   OASIS_AudioActors[24];		         // Array of audio actors available for use in the scene
		OASIS_TEXTACTOR    OASIS_TextActors[14];			       // Array of text actors available for use in the scene
		OASIS_PLAYER		   OASIS_Players[14];				         // Array of players currently used in the scene
		unsigned char*	   OASIS_ScriptPointer;				       // Pointer to the current position in the script
		unsigned char		   OASIS_NumberOfPlayers;			       // Number of players currently involved in scene
		unsigned char		   OASIS_NumberOfAudioActors;	       // Total number of audio actors loaded for this scene

		// OASIS methods
		void							 oasisInitialize                   ();
		void							 oasisStartScene                   (int OASIS_ScriptResourceID);
		unsigned short int oasisDoScene                      (CGapiSurface* in_Display);
		void							 oasisEndScene                     ();

};

