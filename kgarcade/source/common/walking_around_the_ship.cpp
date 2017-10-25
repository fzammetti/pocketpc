
#include "main.h"


namespace ns_WalkingAroundTheShip {


struct ROBOT {
  POINT tile;				     // Tile the robot currently inhabits
	POINT next_tile;	     // Tile the robot will next move to
	int   anim_frame;      // Frame of animation the robot is currently doing
	int   state;           // State the robot is in: 1=Still, 2=Disappearing, 3=Appearing
	int   still_counter;   // Count of how many still animation cycles have occured
  int   appearing_delay; // Delay before robot appears
  int   explosion_frame;
  int   explosion_delay;
	bool  justPositioned;  // Gets set to true when a robot is just positioned (from randomlyPositionRobots() function ONLY) so that we can check for collission with player the next ProcessNextFrame to avoid immediate damage problem
};


// ****************************************************************************************************************
// Defines specific to this mini-game
// ****************************************************************************************************************
#define ROBOTS_COUNT        50 // Number of robots per level
#define MAX_ROBOT_MOVE      3  // Maximum number of tiles a robot can move in one telportation
#define PLAYERMOVEONSCREEN  3  // Number of pixels per frame moved by the player on the screne
#define PLAYERMOVESCROLLING 2  // Number of pixels per frame the screen scrolls when the player is at the edges (usually one less than PLAYERMOVEONSCREEN)
// Tile values that are used in collision detections
#define tileTeleporter  20
#define tileConsole_01  23
#define tileConsole_02  24
#define tileConsole_03  25
#define tileConsole_04  26
#define tileConsole_05  27
#define tileCaptive     30
#define tileHealth      32
// These defines are the ranges that are checked to determine collisions and such later
#define tileFloorMin    0
#define tileFloorMax    0
#define tileWallMin     3
#define tileWallMax     19
// Player orientations
#define pOrientN        20
#define pOrientS        21
#define pOrientE        22
#define pOrientW        23
// Robot states
#define rsStill         30
#define rsDisappearing  31
#define rsNewTile       32
#define rsAppearing     33
#define rsExploding     34


// ****************************************************************************************************************
// Function prototypes specific to this mini-game
// ****************************************************************************************************************
POINT moveNorth(POINT);
POINT moveSouth(POINT);
POINT moveEast(POINT);
POINT moveWest(POINT);
int startMiniGame(int, int);
void initializeLevel(int, GDAPPCONFIG);
void repositionRobot(int);
void randomlyPositionRobots();
void startNewLevel(int);


// ****************************************************************************************************************
// Globals
// ****************************************************************************************************************
CGapiSurface*  dissolve_surface                 = NULL;     // Used for level transition
CGapiSurface*  gfxConsoleFlipped                = NULL;
CGapiSurface*  current_player_image             = NULL;			// Points to the image of the player currently being displayed
CGapiSurface*  gdo                              = NULL;     // Game done ON indicator image (some odd problem when named gameDoneOn)
CGapiSurface*  gameDoneOff                      = NULL;     // Game done OFF indicator
CGapiSurface*  player_walking_n[5];							            // Images of the player walking north
CGapiSurface*  player_walking_s[5];							            // Images of the player walking south
CGapiSurface*  player_walking_e[5];							            // Images of the player walking east
CGapiSurface*  player_walking_w[5];							            // Images of the player walking west
CGapiSurface*  robot_still[9];									            // Robot still images
CGapiSurface*  captive_eeger[3];					    	            // Captive: Eeger images
CGapiSurface*  captive_frederick_j_smiley[4];		            // Captive: Frederick J. Smiley images
CGapiSurface*  captive_catrina[4];					                // Captive: Catrina images
CGapiSurface*  captive_brenda_bubey[4];					            // Captive: Brenda Bubey images
CGapiSurface*  captive_sully[4];					    	            // Captive: Sully images
CGapiSurface*  captive[4];                                  // Pointers to the actual captive images for the current level
CGapiSurface*  tiles[52];												            // Images of the various active tiles
CGapiSurface*  level_1_tiles[22];                           // Stores the actual images of the floor and wall tiles for level 1
CGapiSurface*  level_2_tiles[22];                           // Stores the actual images of the floor and wall tiles for level 2
CGapiSurface*  level_3_tiles[22];                           // Stores the actual images of the floor and wall tiles for level 3
CGapiSurface*  level_4_tiles[22];                           // Stores the actual images of the floor and wall tiles for level 4
CGapiSurface*  level_5_tiles[22];                           // Stores the actual images of the floor and wall tiles for level 5
CGapiSurface*  robot_new_tile_appearing[42];		            // Robot new tile appearing image
CGapiSurface*  robot_disappearing_appearing[42];            // Images for the robot disappearing sequence (and appearing when run backwards)
CGapiSurface*  robot_anim_seq_still[42];				            // Robot still animation sequence
CGapiSurface*  robot_anim_seq_disappearing[42];	            // Robot disappearing animation sequence (pointers to robot_disappearing_appearing array)
CGapiSurface*  robot_anim_seq_appearing[42];		            // Robot disappearing animation sequence (pointers to robot_disappearing_appearing array)
CGapiSurface*  heart[4];                                    // Animation frames for the heart
CGapiSurface*  explosion[8];
hssSound*			 sfxDeath                         = NULL;     // Not actually death, but when a robot hits
hssSound*			 sfxBeamMeUp                      = NULL;     // Teleporting sound
hssSound*      sfxWalking                       = NULL;
hssSound*      sfxExplosion                     = NULL;
hssSound*      sfxHeartbeat_1                   = NULL;
hssSound*      sfxHeartbeat_2                   = NULL;
hssSound*      sfxAaah                          = NULL;
POINT					 ul_tile;													            // Index into the map array of the upper left-hand tile while walking around the ship
POINT					 player_position;									            // Stores the location of the player.  Must be different than player_pos to work!
ROBOT          robots[ROBOTS_COUNT + 2];				            // Array of ROBOT structs
bool           got_health                       = false;    // Flag: have they gotten the health on this level yet?
bool					 moved_north                      = false;		// Flag: Last move was north
bool					 moved_east                       = false;		// Flag: Last move was east
bool					 moved_south                      = false;		// Flag: Last move was south
bool					 moved_west                       = false;		// Flag: Last move was west
bool					 fire_pressed                     = false;		// Has the fire button been pressed?
bool					 doingTeleportation               = false;    // Used for level transition
bool           walkingPlaying                   = false;
bool           consoleFlipped                   = false;
int            captiveFrameDelay                = 0;        // Used for animating captive tile
int            captiveFrameCounter              = 0;        // Used for animating captive tile
int						 player_frame                     = 0;				// Frame of animation for the player
int						 player_frame_delay               = 0;				// Frame delay of animation for the player
int						 horizontal_offset                = 0;				// Used for scrolling the tiles
int						 vertical_offset                  = 0;				// Used for scrolling the tiles
int						 tiles_across_screen              = 14;				// Number of tiles horizontally displayed on the screen
int						 tiles_down_screen                = 18;				// Number of tiles vertically displayed on the screen
int						 map_width                        = 52;				// Number of tiles wide the map is
int						 map_height                       = 52;				// Numberof tiles high the map is
int						 player_orientation               = pOrientN;	// Direction player is currently facing
int            health_counter                   = 0;        // Used for animating heart
int            health_frame                     = 0;        // Used for animating heart
int            health_delay                     = 0;        // Counts down after a robot hit
int						 dissolve_data_index              = 0;        // Used for level transition
int            dissolve_state                   = 0;        // Used for level transition
int            dissolve_big_fade                = 0;        // Used for level transition
int			       walkinghsshssChannel             = 0;
unsigned char* dissolve_dat                     = NULL;
unsigned char* level_map                        = NULL;			// Pointer to the map data for the current level
int            teleported_rcol                  = 0;
int            teleported_rcol_dir              = 0;
int            console_flip_delay               = 0;


} // End of namespace


// ****************************************************************************************************************
// ProcessNextFrame handler
// ****************************************************************************************************************
void CGame::pnfWalkingAroundTheShip(CGapiSurface* backbuffer) {

  using namespace ns_WalkingAroundTheShip;

	// Echo these values so we can easily get at them from class-level for saving
	cl_ul_tile.x				 = ul_tile.x;
	cl_ul_tile.y				 = ul_tile.y;
	cl_horizontal_offset = horizontal_offset;
	cl_vertical_offset	 = vertical_offset;
	cl_player_position.x = player_position.x;
	cl_player_position.y = player_position.y;

	if (doingTeleportation) { // We're dissolving for a level transition

		if (dissolve_state == 0) {
			COLORREF pixel_color;
			pixel_color = RGB(0, 0, 0);
			for (int i = 0; i < 35; i++) {
				unsigned char x = *(dissolve_dat + dissolve_data_index);
				dissolve_data_index++;
				unsigned char y = *(dissolve_dat + dissolve_data_index);
				dissolve_data_index++;
				dissolve_surface->SetPixel(x, y, pixel_color);
			}
			for (int y = 0; y < 8; y++) {
				for (int x = 0; x < 6; x++) {
					backbuffer->BltFast((x * 40), (y * 40), dissolve_surface, NULL, GDBLTFAST_KEYSRC, NULL);
				}
			}
			if (dissolve_data_index > 3200) {
				dissolve_state = 1;
				dissolve_big_fade = 31;
			}
		} else {
			if (dissolve_big_fade > -1) {
				int colr = 8 * dissolve_big_fade;
				backbuffer->FillRect(NULL, RGB(colr, colr, colr), NULL, NULL);
				dissolve_big_fade--;
			} else {
				ExitCounter = 0;
				ExitFadeCounter = 255;
				shutdownStep = 1;
				doDestroy(csExiting);
				return;
        if (current_level == 5) { // THEY WON!!
					// Echo these values so we can easily get at them from class-level for saving
					cl_ul_tile.x				 = ul_tile.x;
					cl_ul_tile.y				 = ul_tile.y;
					cl_horizontal_offset = horizontal_offset;
					cl_vertical_offset	 = vertical_offset;
					cl_player_position.x = player_position.x;
					cl_player_position.y = player_position.y;
          writeKGAFile(false, false);
					previous_level = 5;
          doDestroy(csWin);
        } else {
					doDestroy(csWalkingAroundTheShip);
          doingTeleportation				= false;
				  games_done[0]             = false;
				  player_dir_east		        = false;
				  player_dir_west		        = false;
				  player_dir_south	        = false;
				  player_dir_north	        = false;
				  moved_north				        = false;
				  moved_east				        = false;
				  moved_south				        = false;
				  moved_west				        = false;
				  player_frame			        = 0;
				  player_frame_delay        = 0;
				  fire_pressed              = false;
				  games_done[0]             = false;
				  games_done[1]             = false;
				  games_done[2]             = false;
				  games_done[3]             = false;
				  games_done[4]             = false;
				  processEvents             = true;
				  current_level_initialized = true;
				  current_level++;
				  initializeLevel(current_level, m_config);
				  startNewLevel(current_level);
          levelHintDone = false;
					// Echo these values so we can easily get at them from class-level for saving
					cl_ul_tile.x				 = ul_tile.x;
					cl_ul_tile.y				 = ul_tile.y;
					cl_horizontal_offset = horizontal_offset;
					cl_vertical_offset	 = vertical_offset;
					cl_player_position.x = player_position.x;
					cl_player_position.y = player_position.y;
				  writeKGAFile(true, false);
        }
			}
		}

	} else { // NOT dissolving, go as usual

		if (health <= 0) { doDestroy(csPlayerDied); } // Should avoid that rare super-fast heartbeat and subsequent crash

		POINT colPoint;

		// Blit tiles
		int locX = 0;
		int locY = -20;
		int tile = 1;
		for (int y = 0; y < tiles_down_screen; y++) {
			locX = -20;
			for (int x = 0; x < tiles_across_screen; x++) {
				tile = *(level_map + (((ul_tile.y + y) * map_width) + (ul_tile.x + x)));
        // First, always lay down a floor tile
				backbuffer->BltFast(locX + horizontal_offset, locY + vertical_offset, tiles[0], NULL, GDBLTFAST_KEYSRC, NULL);
        // If it's a teleporter and all games are finished, pulsate the teleporter
        if (tile == tileTeleporter && games_done[0] && games_done[1] && games_done[2] && games_done[3] && games_done[4]) {
          GDBLTFASTFX gdbltfastfx;
          gdbltfastfx.dwFXcolor1 = RGB(teleported_rcol, 32, 32);
          if (teleported_rcol_dir == 0) {
            teleported_rcol = teleported_rcol + 10;
            if (teleported_rcol > 245) { teleported_rcol_dir = 1; }
          } else {
            teleported_rcol = teleported_rcol - 10;
            if (teleported_rcol < 35) { teleported_rcol_dir = 0; }
          }
          backbuffer->BltFast(locX + horizontal_offset, locY + vertical_offset, tiles[tile], NULL, GDBLTFAST_KEYSRC | GDBLTFASTFX_COLORIZE, &gdbltfastfx);
        } else if (tile == tileConsole_01 || tile == tileConsole_02 || tile == tileConsole_03 || tile == tileConsole_04 || tile == tileConsole_05) {
					if (consoleFlipped) {
						backbuffer->BltFast(locX + horizontal_offset, locY + vertical_offset, gfxConsoleFlipped, NULL, GDBLTFAST_KEYSRC, NULL);
					} else {
						backbuffer->BltFast(locX + horizontal_offset, locY + vertical_offset, tiles[tile], NULL, GDBLTFAST_KEYSRC, NULL);
					}
				} else {
          // Now, if it's not actually a floor tile, lay down the correct image
          if (tile > tileFloorMax) {
            // If it's a health tile, only lay it down if player hasn't gotten it yet this level, if it's NOT a health tile, lay it down
            if (tile != tileHealth || (tile == tileHealth && !got_health)) {
				      backbuffer->BltFast(locX + horizontal_offset, locY + vertical_offset, tiles[tile], NULL, GDBLTFAST_KEYSRC, NULL);
            }
          }
        }
				locX = locX + 20;
			}
			locY = locY + 20;
		}

		// Flip consoles
		console_flip_delay++;
		if (console_flip_delay > 3) {
			console_flip_delay = 0;
			consoleFlipped = !consoleFlipped;
		}

		// Determine which player orientation to use and blit player
		switch (player_orientation) {
			case pOrientN: current_player_image = player_walking_n[player_frame]; break;
			case pOrientS: current_player_image = player_walking_s[player_frame]; break;
			case pOrientE: current_player_image = player_walking_e[player_frame]; break;
			case pOrientW: current_player_image = player_walking_w[player_frame]; break;
		}
		backbuffer->BltFast(player_position.x, player_position.y, current_player_image, NULL, GDBLTFAST_KEYSRC, NULL);
		if (health_delay > 0) { // Count down timer after a hit
			health_delay--;
		}

		// Blit robots, if applicable
    bool show_robot = false;
		for (int i = 0; i < ROBOTS_COUNT; i++) {
			if (robots[i].justPositioned) {
				robots[i].justPositioned = false;
					// Check for position with player.  If it occurs, reposition robot and set flag to do this check again next frame
					locX = (robots[i].tile.x - ul_tile.x) * 20;
					locY = (robots[i].tile.y - ul_tile.y) * 20;
					CGapiSurface::Intersect(locX + horizontal_offset, locY + vertical_offset, robot_anim_seq_still[robots[i].anim_frame], NULL, player_position.x, player_position.y, current_player_image, NULL, &colPoint);
					if (colPoint.x != -1 || colPoint.y != -1) {
						repositionRobot(i);
						robots[i].justPositioned = true;
					}
			} else {
				show_robot = false;
				if (robots[i].tile.x >= ul_tile.x && robots[i].tile.x <= ul_tile.x + tiles_across_screen &&
						robots[i].tile.y >= ul_tile.y && robots[i].tile.y <= ul_tile.y + tiles_down_screen) {
							show_robot = true;
							locX = (robots[i].tile.x - ul_tile.x) * 20;
							locY = (robots[i].tile.y - ul_tile.y) * 20;
				}
				switch (robots[i].state) {
					case rsStill: {
						if (show_robot) {
							backbuffer->BltFast(locX + horizontal_offset, locY + vertical_offset, robot_anim_seq_still[robots[i].anim_frame], NULL, GDBLTFAST_KEYSRC, NULL);
							// Check for colission with player, reduce health or kill as applicable
							CGapiSurface::Intersect(locX + horizontal_offset, locY + vertical_offset, robot_anim_seq_still[robots[i].anim_frame], NULL, player_position.x, player_position.y, current_player_image, NULL, &colPoint);
							if (colPoint.x != -1 || colPoint.y != -1) {
								if (health_delay <= 0) {
									robots[i].explosion_delay = 0;
									robots[i].explosion_frame = 0;
									robots[i].state = rsExploding;
									sndObj.playSound(sfxDeath);
									health_delay = 25;
									health = health - 3;
								}
							}
						}
						robots[i].anim_frame++;
						if (robot_anim_seq_still[robots[i].anim_frame] == NULL) {
							robots[i].anim_frame = 0;
							robots[i].still_counter++;
							if (robots[i].still_counter > 2) {
								robots[i].state = rsDisappearing;
								repositionRobot(i);
							}
						}
					break; }
					case rsDisappearing: {
  					if (show_robot) {
							backbuffer->BltFast(locX + horizontal_offset, locY + vertical_offset, robot_anim_seq_disappearing[robots[i].anim_frame], NULL, GDBLTFAST_KEYSRC, NULL);
						}
						robots[i].anim_frame++;
						if (robot_anim_seq_disappearing[robots[i].anim_frame] == NULL) {
							robots[i].anim_frame = 0;
							robots[i].tile.x = robots[i].next_tile.x;
							robots[i].tile.y = robots[i].next_tile.y;
							robots[i].appearing_delay = 0;
							robots[i].state = rsAppearing;
						}
					break; }
					case rsAppearing: {
						robots[i].appearing_delay++;
						if (robots[i].appearing_delay > 24) {
							if (show_robot) {
								backbuffer->BltFast(locX + horizontal_offset, locY + vertical_offset, robot_anim_seq_appearing[robots[i].anim_frame], NULL, GDBLTFAST_KEYSRC, NULL);
							}
							robots[i].anim_frame++;
							if (robot_anim_seq_appearing[robots[i].anim_frame] == NULL) {
								robots[i].anim_frame = 0;
								robots[i].state = rsStill;
							}
						}
					break; }
					case rsExploding: {
						backbuffer->BltFast(locX + horizontal_offset - 10, locY + vertical_offset - 10, explosion[robots[i].explosion_frame], NULL, GDBLTFAST_KEYSRC, NULL);
						int ret_val;
						robots[i].explosion_delay++;
						if (robots[i].explosion_delay > 0) {
							robots[i].explosion_delay = 0;
							robots[i].explosion_frame++;
							if (robots[i].explosion_frame > 4) {
								ret_val = -1;
							} else {
								ret_val = robots[i].explosion_frame;
							}
						}
						if (robots[i].explosion_frame == 2) { ret_val = 99; }
						if (ret_val == -1) {
							// Kill player if no more health
							if (health <= 0) {
								doDestroy(csPlayerDied);
							} else { // Otherwise, just reposition robot (health already reducde at time of collision)
								int x, y;
								newRobotPosExp:
									x = rand() % map_width;
									y = rand() % map_height;
									tile = *(level_map + (((y + 1) * map_width) + x + 1));
									if (tile < tileFloorMin || tile > tileFloorMin) {
										goto newRobotPosExp;
									}
									if (x < 3 || y < 3 || x > map_width - 3 || y > map_height - 3) {
										goto newRobotPosExp;
									}
									robots[i].tile.x		      = x;
									robots[i].tile.y		      = y;
									robots[i].anim_frame      = rand() % 12;
									robots[i].state			      = rsStill;
									robots[i].appearing_delay = 0;
									robots[i].still_counter   = rand() % 4;
							}
						}
					break; }
				} // End switch
			} // End if
		} // End for

		// Status
		switch (current_level) {
			case 1: { backbuffer->DrawText(238, 296, TEXT("Level 1"), &font1, GDDRAWTEXT_RIGHT, NULL, NULL, NULL); break; }
			case 2: { backbuffer->DrawText(238, 296, TEXT("Level 2"), &font1, GDDRAWTEXT_RIGHT, NULL, NULL, NULL); break; }
			case 3: { backbuffer->DrawText(238, 296, TEXT("Level 3"), &font1, GDDRAWTEXT_RIGHT, NULL, NULL, NULL); break; }
			case 4: { backbuffer->DrawText(238, 296, TEXT("Level 4"), &font1, GDDRAWTEXT_RIGHT, NULL, NULL, NULL); break; }
			case 5: { backbuffer->DrawText(238, 296, TEXT("Level 5"), &font1, GDDRAWTEXT_RIGHT, NULL, NULL, NULL); break; }
		}
		if (games_done[0]) {
			backbuffer->BltFast(42,  297, gdo, NULL, GDBLTFAST_KEYSRC, NULL);
		} else {
			backbuffer->BltFast(42,  297, gameDoneOff, NULL, GDBLTFAST_KEYSRC, NULL);
		}
		if (games_done[1]) {
			backbuffer->BltFast(72,  297, gdo, NULL, GDBLTFAST_KEYSRC, NULL);
		} else {
			backbuffer->BltFast(72,  297, gameDoneOff, NULL, GDBLTFAST_KEYSRC, NULL);
		}
		if (games_done[2]) {
			backbuffer->BltFast(102, 297, gdo, NULL, GDBLTFAST_KEYSRC, NULL);
		} else {
			backbuffer->BltFast(102, 297, gameDoneOff, NULL, GDBLTFAST_KEYSRC, NULL);
		}
		if (games_done[3]) {
			backbuffer->BltFast(132, 297, gdo, NULL, GDBLTFAST_KEYSRC, NULL);
		} else {
			backbuffer->BltFast(132, 297, gameDoneOff, NULL, GDBLTFAST_KEYSRC, NULL);
		}
		if (games_done[4]) {
			backbuffer->BltFast(162, 297, gdo, NULL, GDBLTFAST_KEYSRC, NULL);
		} else {
			backbuffer->BltFast(162, 297, gameDoneOff, NULL, GDBLTFAST_KEYSRC, NULL);
		}
		// The beating heart...
		health_counter--;
		if (health_counter <= 0) {
			if (health_frame == 0) {
				if (health < 6) {
					health_counter = health;
				} else {
					health_counter = 6;
				}
			} else {
				health_counter = health;
			}
			health_frame++;
			if (health_frame > 1) { health_frame = 0; }
      if (health_frame == 0) { sndObj.playSound(sfxHeartbeat_1); } else { sndObj.playSound(sfxHeartbeat_2); }
		}
		backbuffer->BltFast(0, 288, heart[health_frame], NULL, GDBLTFAST_KEYSRC, NULL);
		switch (health) {
		  case 12: { backbuffer->DrawText(16, 293, TEXT("3"), &font1_green, GDDRAWTEXT_CENTER, NULL, NULL, NULL); break; }
			case 9:  { backbuffer->DrawText(16, 293, TEXT("2"), &font1_green, GDDRAWTEXT_CENTER, NULL, NULL, NULL); break; }
			case 6:  { backbuffer->DrawText(16, 293, TEXT("1"), &font1,       GDDRAWTEXT_CENTER, NULL, NULL, NULL); break; }
			case 3:  { backbuffer->DrawText(16, 293, TEXT("0"), &font1,       GDDRAWTEXT_CENTER, NULL, NULL, NULL); break; }
		}

		// Move player
		moved_north = false; moved_east = false; moved_south = false;	moved_west = false;
		if (player_dir_north) {	player_position = moveNorth(player_position); }
		if (player_dir_east)  { player_position = moveEast(player_position);  }
		if (player_dir_south) {	player_position = moveSouth(player_position); }
		if (player_dir_west)  {	player_position = moveWest(player_position);  }
		// If the player is moving...
		if (player_dir_north || player_dir_south || player_dir_east || player_dir_west) {
			// If the walking sound is not currently playing, go ahead and play it
      if (!walkingPlaying) {
        walkingPlaying = true;
        walkinghsshssChannel = sndObj.playSound(sfxWalking);
      }
		} else {
			// Player is NOT walking, so if the walking channel is playing, stop it
      if (walkingPlaying) {
        walkingPlaying = false;
			  hssChannel* wc = sndObj.channel(walkinghsshssChannel);
			  wc->stop();
      }
		}

		// Handle player animation, if applicable
		if (player_dir_north || player_dir_south || player_dir_east || player_dir_west) {
			player_frame_delay++;
			if (player_frame_delay > 1) {
				player_frame_delay = 0;
				player_frame++;
				if (player_frame > 2) {
					player_frame = 0;
				}
			}
		}

		// Go through the tiles currently displayed and look for any none-floor tiles, check for player collision
		locX = 0;
		locY = -20;
		tile = 1;
		for (y = 0; y < tiles_down_screen; y++) {
			locX = -20;
			for (int x = 0; x < tiles_across_screen; x++) {
				tile = *(level_map + (((ul_tile.y + y) * map_width) + (ul_tile.x + x)));
				// If it's a wall, check for a collision
				if (tile >= tileWallMin && tile <= tileWallMax) {
					CGapiSurface::Intersect(locX + horizontal_offset, locY + vertical_offset, tiles[tile], NULL, player_position.x, player_position.y, current_player_image, NULL, &colPoint);
					if (colPoint.x != -1 || colPoint.y != -1) {
						if (moved_north) { player_position.y = player_position.y + 5; }
						if (moved_south) { player_position.y = player_position.y - 5; }
						if (moved_east)  { player_position.x = player_position.x - 5; }
						if (moved_west)  { player_position.x = player_position.x + 5; }
					}
				}
				// Deal with it if a health-up and they haven't gotten it yet this level (player does NOT have to hit the button for this)
				if (tile == tileHealth && !got_health) {
					CGapiSurface::Intersect(locX + horizontal_offset, locY + vertical_offset, tiles[tile], NULL, player_position.x, player_position.y, current_player_image, NULL, &colPoint);
					if (colPoint.x != -1 || colPoint.y != -1) {
            sndObj.playSound(sfxAaah);
						got_health = true;
            health = 12;
						writeKGAFile(true, false);
					}
				}
				// If fire is pressed...
				if (fire_pressed) {
					// Deal with it if if's a console
					if (tile == tileConsole_01 || tile == tileConsole_02 || tile == tileConsole_03 || tile == tileConsole_04 || tile == tileConsole_05) {
						CGapiSurface::Intersect(locX + horizontal_offset, locY + vertical_offset, tiles[tile], NULL, player_position.x, player_position.y, current_player_image, NULL, &colPoint);
						if (colPoint.x != -1 || colPoint.y != -1) {
              player_dir_north = false;
              player_dir_south = false;
              player_dir_east = false;
              player_dir_west = false;
              fire_pressed = false;
              if (walkingPlaying) {
                walkingPlaying = false;
			          hssChannel* wc = sndObj.channel(walkinghsshssChannel);
			          wc->stop();
              }
							game_submode = gsmTimed;
							whichGameBeingPlayed = tile - 23; // tile - the literal number here should be in the range 0-4
							processEvents = false;
							doDestroy(startMiniGame(current_level, tile));
						}
					}
					// Deal with it if if's a captive
					if (tile == tileCaptive) {
						CGapiSurface::Intersect(locX + horizontal_offset, locY + vertical_offset, tiles[tile], NULL, player_position.x, player_position.y, current_player_image, NULL, &colPoint);
						if (colPoint.x != -1 || colPoint.y != -1) {
              player_dir_north = false;
              player_dir_south = false;
              player_dir_east = false;
              player_dir_west = false;
              fire_pressed = false;
							player_button_down = false;
              if (walkingPlaying) {
                walkingPlaying = false;
			          hssChannel* wc = sndObj.channel(walkinghsshssChannel);
			          wc->stop();
              }
							fire_pressed = false;
							current_screen = csCharacterInteraction;
						}
					}
					// Deal with it if if's a teleporter
					if (tile == tileTeleporter) {
						CGapiSurface::Intersect(locX + horizontal_offset, locY + vertical_offset, tiles[tile], NULL, player_position.x, player_position.y, current_player_image, NULL, &colPoint);
						if (colPoint.x != -1 || colPoint.y != -1) {
							// Advance to next level if all mini-games on this level are complete
							if (games_done[0] && games_done[1] && games_done[2] && games_done[3] && games_done[4]) {
                player_dir_north = false;
                player_dir_south = false;
                player_dir_east = false;
                player_dir_west = false;
                fire_pressed = false;
                processEvents = false;
                if (walkingPlaying) {
                  walkingPlaying = false;
			            hssChannel* wc = sndObj.channel(walkinghsshssChannel);
			            wc->stop();
                }
                doingTeleportation = true;
								dissolve_data_index = 0;
								dissolve_state = 0;
                dissolve_surface->FillRect(NULL, RGB(255, 128, 255), NULL, NULL);
								sndObj.playSound(sfxBeamMeUp);
							}
						}
					}
				}
				locX = locX + 20;
			}
			locY = locY + 20;
		}

		// Update animated tiles
		captiveFrameDelay++;
		if (captiveFrameDelay > 2) {
			captiveFrameDelay = 0;
			captiveFrameCounter++;
			if (captiveFrameCounter > 1) {
				captiveFrameCounter = 0;
			}
			tiles[30] = captive[captiveFrameCounter];
		}

	} // End if (doingTeleportation)

}


// ****************************************************************************************************************
// KeyDown handler
// ****************************************************************************************************************
void CGame::kdWalkingAroundTheShip(DWORD dwKey) {

	using namespace ns_WalkingAroundTheShip;

	if (dwKey == kAction) {
		fire_pressed = true;
	}

	if (dwKey == kRight) {
		player_frame_delay = 100; // Assure animation next frame
		player_orientation = pOrientE;
		player_dir_north = false;
		player_dir_east  = true;
		player_dir_south = false;
		player_dir_west  = false;
	}

	if (dwKey == kLeft) {
		player_frame_delay = 100; // Assure animation next frame
		player_orientation = pOrientW;
		player_dir_north = false;
		player_dir_east  = false;
		player_dir_south = false;
		player_dir_west  = true;
	}

	if (dwKey == kUp) {
		player_frame_delay = 100; // Assure animation next frame
		player_orientation = pOrientN;
		player_dir_north = true;
		player_dir_east  = false;
		player_dir_south = false;
		player_dir_west  = false;
	}

	if (dwKey == kDown) {
		player_frame_delay = 100; // Assure animation next frame
		player_orientation = pOrientS;
		player_dir_north = false;
		player_dir_east  = false;
		player_dir_south = true;
		player_dir_west	 = false;
	}

}


// ****************************************************************************************************************
// KeyUp handler
// ****************************************************************************************************************
void CGame::kuWalkingAroundTheShip(DWORD dwKey) {

	using namespace ns_WalkingAroundTheShip;

	// Command button
	if (dwKey == kCommand) {
		if (walkingPlaying) {
      walkingPlaying = false;
			hssChannel* wc = sndObj.channel(walkinghsshssChannel);
			wc->stop();
    }
    // Do a popup...
    // Popup callback
    CGame::popupCallback = CGame::popupCallbackWalkingAroundTheShip;
    // Popup options
    gpOptionsCount = 2;
    _tcscpy(gpOptions[0], TEXT("Continue Game"));
    _tcscpy(gpOptions[1], TEXT("Quit Game"));
    // Start popup
		startPopup(TEXT("What would you"), TEXT("like to do?"));
	}

	if (dwKey == kAction) {
		fire_pressed = false;
	}

	if (dwKey == kRight) {
		player_dir_east = false;
	}

	if (dwKey == kLeft) {
		player_dir_west = false;
	}

	if (dwKey == kUp) {
		player_dir_north = false;
	}

	if (dwKey == kDown) {
		player_dir_south = false;
	}

	// Command button
	if (dwKey == kCommand) {
    // Do a popup...
    // Popup callback
		CGame::popupCallback = CGame::popupCallbackWalkingAroundTheShip;
    // Popup options
    _tcscpy(gpOptions[0], TEXT("Continue Game"));
		_tcscpy(gpOptions[1], TEXT("Save Game"));
    _tcscpy(gpOptions[2], TEXT("Quit Game"));
		#ifdef _TEST_
    _tcscpy(gpOptions[3], TEXT("Complete All"));
    _tcscpy(gpOptions[4], TEXT("Next Level"));
    gpOptionsCount = 5;
		#else
    gpOptionsCount = 3;
		#endif
    // Start popup
		startPopup(TEXT("What would you"), TEXT("like to do?"));
	}

}


// ****************************************************************************************************************
// Popup Callback Handler
// ****************************************************************************************************************
void CGame::popupCallbackWalkingAroundTheShip(int option) {

  using namespace ns_WalkingAroundTheShip;

	if (option == 1) { // Save game
		// Echo these values so we can easily get at them from class-level for saving
		cl_ul_tile.x				 = ul_tile.x;
		cl_ul_tile.y				 = ul_tile.y;
		cl_horizontal_offset = horizontal_offset;
		cl_vertical_offset	 = vertical_offset;
		cl_player_position.x = player_position.x;
		cl_player_position.y = player_position.y;
		writeKGAFile(true, false);
	}

	if (option == 2) { // Quit game
	  doDestroy(csMainMenu);
	}

	#ifdef _TEST_
  if (option == 3) { // Complete All
    games_done[0] = true;
    games_done[1] = true;
    games_done[2] = true;
    games_done[3] = true;
    games_done[4] = true;
  }
  if (option == 4) { // Next Level
    doDestroy(csWalkingAroundTheShip);
    current_level++;
    games_done[0]             = false;
    player_dir_east		        = false;
    player_dir_west		        = false;
    player_dir_south	        = false;
    player_dir_north	        = false;
    moved_north				        = false;
    moved_east				        = false;
    moved_south				        = false;
    moved_west				        = false;
    player_frame			        = 0;
    player_frame_delay        = 0;
    fire_pressed              = false;
    games_done[0]             = false;
    games_done[1]             = false;
    games_done[2]             = false;
    games_done[3]             = false;
    games_done[4]             = false;
    processEvents             = true;
    current_level_initialized = true;
    initializeLevel(current_level, m_config);
    startNewLevel(current_level);
    levelHintDone = false;
  }
	#endif


}


// ****************************************************************************************************************
// Loader
// ****************************************************************************************************************
void CGame::loadWalkingAroundTheShip(CGapiSurface* backbuffer) {

	using namespace ns_WalkingAroundTheShip;

	processEvents = false;

	// Move on to the next step
	if (loading_step != 12) { // This number is the number of the case statement that calls on the loadCharacterInteraction() method
		loading_step++;
	}

	// Do the appropriate step
	switch(loading_step) {

		case 1: {
			int i = 0;
			for (i = 0; i < 2;  i++) { heart[i]												 = NULL; }
			for (i = 0; i < 3;  i++) { player_walking_n[i]						 = NULL; }
			for (i = 0; i < 3;  i++) { player_walking_s[i]						 = NULL; }
			for (i = 0; i < 3;  i++) { player_walking_e[i]						 = NULL; }
			for (i = 0; i < 3;  i++) { player_walking_w[i]						 = NULL; }
			for (i = 0; i < 7;  i++) { robot_still[i]									 = NULL; }
			for (i = 0; i < 2;  i++) { captive_eeger[i]								 = NULL; }
			for (i = 0; i < 2;  i++) { captive_frederick_j_smiley[i]	 = NULL; }
			for (i = 0; i < 2;  i++) { captive_catrina[i]							 = NULL; }
			for (i = 0; i < 2;  i++) { captive_brenda_bubey[i]				 = NULL; }
			for (i = 0; i < 2;  i++) { captive_sully[i]							   = NULL; }
			for (i = 0; i < 2;  i++) { captive[i]											 = NULL; }
			for (i = 0; i < 40; i++) { robot_new_tile_appearing[i]		 = NULL; }
			for (i = 0; i < 40; i++) { robot_disappearing_appearing[i] = NULL; }
			for (i = 0; i < 40; i++) { robot_anim_seq_still[i]				 = NULL; }
			for (i = 0; i < 40; i++) { robot_anim_seq_disappearing[i]	 = NULL; }
			for (i = 0; i < 40; i++) { robot_anim_seq_appearing[i]		 = NULL; }
			for (i = 0; i < 50; i++) { tiles[i]												 = NULL; }
			for (i = 0; i < 20; i++) { level_1_tiles[i]								 = NULL; }
			for (i = 0; i < 20; i++) { level_2_tiles[i]								 = NULL; }
			for (i = 0; i < 20; i++) { level_3_tiles[i]								 = NULL; }
			for (i = 0; i < 20; i++) { level_4_tiles[i]								 = NULL; }
			for (i = 0; i < 20; i++) { level_5_tiles[i]								 = NULL; }
			HRSRC hResInfo	= FindResource(m_config.hInstance, MAKEINTRESOURCE(IDR_DISSOLVE_DAT), TEXT("MISC"));
			HGLOBAL hResource	= LoadResource(m_config.hInstance, hResInfo);
			dissolve_dat = (unsigned char*)LockResource(hResource);
			explosion[0] = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_EXPLOSION_00"),  explosion[0]->CreateSurface(0, m_config.hInstance, GFX_EXPLOSION_00,  TEXT("GRAPHICS"))); explosion[0]->SetColorKey(RGB(255, 128, 255));
			explosion[1] = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_EXPLOSION_01"),  explosion[1]->CreateSurface(0, m_config.hInstance, GFX_EXPLOSION_01,  TEXT("GRAPHICS"))); explosion[1]->SetColorKey(RGB(255, 128, 255));
			explosion[2] = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_EXPLOSION_02"),  explosion[2]->CreateSurface(0, m_config.hInstance, GFX_EXPLOSION_02,  TEXT("GRAPHICS"))); explosion[2]->SetColorKey(RGB(255, 128, 255));
			explosion[3] = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_EXPLOSION_03"),  explosion[3]->CreateSurface(0, m_config.hInstance, GFX_EXPLOSION_03,  TEXT("GRAPHICS"))); explosion[3]->SetColorKey(RGB(255, 128, 255));
			explosion[4] = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_EXPLOSION_04"),  explosion[4]->CreateSurface(0, m_config.hInstance, GFX_EXPLOSION_04,  TEXT("GRAPHICS"))); explosion[4]->SetColorKey(RGB(255, 128, 255));
			heart[0]     = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_HEART_1"),       heart[0]->CreateSurface    (0, m_config.hInstance, GFX_HEART_1,       TEXT("GRAPHICS"))); heart[0]->SetColorKey    (RGB(255, 128, 255));
			heart[1]     = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_HEART_2"),       heart[1]->CreateSurface    (0, m_config.hInstance, GFX_HEART_2,       TEXT("GRAPHICS"))); heart[1]->SetColorKey    (RGB(255, 128, 255));
			gdo          = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_GAME_DONE_ON"),  gdo->CreateSurface         (0, m_config.hInstance, GFX_GAME_DONE_ON,  TEXT("GRAPHICS"))); gdo->SetColorKey         (RGB(255, 128, 255));
			gameDoneOff  = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_GAME_DONE_OFF"), gameDoneOff->CreateSurface (0, m_config.hInstance, GFX_GAME_DONE_OFF, TEXT("GRAPHICS"))); gameDoneOff->SetColorKey (RGB(255, 128, 255));
    break; }

		case 2: {
			switch (current_level) {
				case 1: {
 					level_1_tiles[0] = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_TILE_LEVEL_1_FLOOR_01"),   level_1_tiles[0]->CreateSurface (0, m_config.hInstance, GFX_TILE_LEVEL_1_FLOOR_01,   TEXT("GRAPHICS"))); level_1_tiles[0]->SetColorKey(RGB(255, 128, 255));
					level_1_tiles[1] = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_TILE_LEVEL_1_WALL_BLOCK"), level_1_tiles[1]->CreateSurface (0, m_config.hInstance, GFX_TILE_LEVEL_1_WALL_BLOCK, TEXT("GRAPHICS"))); level_1_tiles[1]->SetColorKey(RGB(255, 128, 255));
					level_1_tiles[2] = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_TILE_LEVEL_1_WALL_N"),     level_1_tiles[2]->CreateSurface (0, m_config.hInstance, GFX_TILE_LEVEL_1_WALL_N,     TEXT("GRAPHICS"))); level_1_tiles[2]->SetColorKey(RGB(255, 128, 255));
					level_1_tiles[3] = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_TILE_LEVEL_1_WALL_E"),     level_1_tiles[3]->CreateSurface (0, m_config.hInstance, GFX_TILE_LEVEL_1_WALL_E,     TEXT("GRAPHICS"))); level_1_tiles[3]->SetColorKey(RGB(255, 128, 255));
					level_1_tiles[4] = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_TILE_LEVEL_1_WALL_S"),     level_1_tiles[4]->CreateSurface (0, m_config.hInstance, GFX_TILE_LEVEL_1_WALL_S,     TEXT("GRAPHICS"))); level_1_tiles[4]->SetColorKey(RGB(255, 128, 255));
					level_1_tiles[5] = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_TILE_LEVEL_1_WALL_W"),     level_1_tiles[5]->CreateSurface (0, m_config.hInstance, GFX_TILE_LEVEL_1_WALL_W,     TEXT("GRAPHICS"))); level_1_tiles[5]->SetColorKey(RGB(255, 128, 255));
					level_1_tiles[6] = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_TILE_LEVEL_1_WALL_NW"),    level_1_tiles[6]->CreateSurface (0, m_config.hInstance, GFX_TILE_LEVEL_1_WALL_NW,    TEXT("GRAPHICS"))); level_1_tiles[6]->SetColorKey(RGB(255, 128, 255));
					level_1_tiles[7] = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_TILE_LEVEL_1_WALL_NE"),    level_1_tiles[7]->CreateSurface (0, m_config.hInstance, GFX_TILE_LEVEL_1_WALL_NE,    TEXT("GRAPHICS"))); level_1_tiles[7]->SetColorKey(RGB(255, 128, 255));
					level_1_tiles[8] = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_TILE_LEVEL_1_WALL_SW"),    level_1_tiles[8]->CreateSurface (0, m_config.hInstance, GFX_TILE_LEVEL_1_WALL_SW,    TEXT("GRAPHICS"))); level_1_tiles[8]->SetColorKey(RGB(255, 128, 255));
					level_1_tiles[9] = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_TILE_LEVEL_1_WALL_SE"),    level_1_tiles[9]->CreateSurface (0, m_config.hInstance, GFX_TILE_LEVEL_1_WALL_SE,    TEXT("GRAPHICS"))); level_1_tiles[9]->SetColorKey(RGB(255, 128, 255));
					captive_eeger[0] = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_CAPTIVE_EEGER_00"),        captive_eeger[0]->CreateSurface (0, m_config.hInstance, GFX_CAPTIVE_EEGER_00,        TEXT("GRAPHICS"))); captive_eeger[0]->SetColorKey(RGB(255, 128, 255));
					captive_eeger[1] = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_CAPTIVE_EEGER_01"),        captive_eeger[1]->CreateSurface (0, m_config.hInstance, GFX_CAPTIVE_EEGER_01,        TEXT("GRAPHICS"))); captive_eeger[1]->SetColorKey(RGB(255, 128, 255));
				break; }
				case 2: {
					level_2_tiles[0]              = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_TILE_LEVEL_2_FLOOR_01"),         level_2_tiles[0]->CreateSurface             (0, m_config.hInstance, GFX_TILE_LEVEL_2_FLOOR_01,         TEXT("GRAPHICS"))); level_2_tiles[0]->SetColorKey             (RGB(255, 128, 255));
					level_2_tiles[1]              = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_TILE_LEVEL_2_WALL_BLOCK"),       level_2_tiles[1]->CreateSurface             (0, m_config.hInstance, GFX_TILE_LEVEL_2_WALL_BLOCK,       TEXT("GRAPHICS"))); level_2_tiles[1]->SetColorKey             (RGB(255, 128, 255));
					level_2_tiles[2]              = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_TILE_LEVEL_2_WALL_N"),           level_2_tiles[2]->CreateSurface             (0, m_config.hInstance, GFX_TILE_LEVEL_2_WALL_N,           TEXT("GRAPHICS"))); level_2_tiles[2]->SetColorKey             (RGB(255, 128, 255));
					level_2_tiles[3]              = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_TILE_LEVEL_2_WALL_E"),           level_2_tiles[3]->CreateSurface             (0, m_config.hInstance, GFX_TILE_LEVEL_2_WALL_E,           TEXT("GRAPHICS"))); level_2_tiles[3]->SetColorKey             (RGB(255, 128, 255));
					level_2_tiles[4]              = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_TILE_LEVEL_2_WALL_S"),           level_2_tiles[4]->CreateSurface             (0, m_config.hInstance, GFX_TILE_LEVEL_2_WALL_S,           TEXT("GRAPHICS"))); level_2_tiles[4]->SetColorKey             (RGB(255, 128, 255));
					level_2_tiles[5]              = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_TILE_LEVEL_2_WALL_W"),           level_2_tiles[5]->CreateSurface             (0, m_config.hInstance, GFX_TILE_LEVEL_2_WALL_W,           TEXT("GRAPHICS"))); level_2_tiles[5]->SetColorKey             (RGB(255, 128, 255));
					level_2_tiles[6]              = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_TILE_LEVEL_2_WALL_NW"),          level_2_tiles[6]->CreateSurface             (0, m_config.hInstance, GFX_TILE_LEVEL_2_WALL_NW,          TEXT("GRAPHICS"))); level_2_tiles[6]->SetColorKey             (RGB(255, 128, 255));
					level_2_tiles[7]              = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_TILE_LEVEL_2_WALL_NE"),          level_2_tiles[7]->CreateSurface             (0, m_config.hInstance, GFX_TILE_LEVEL_2_WALL_NE,          TEXT("GRAPHICS"))); level_2_tiles[7]->SetColorKey             (RGB(255, 128, 255));
					level_2_tiles[8]              = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_TILE_LEVEL_2_WALL_SW"),          level_2_tiles[8]->CreateSurface             (0, m_config.hInstance, GFX_TILE_LEVEL_2_WALL_SW,          TEXT("GRAPHICS"))); level_2_tiles[8]->SetColorKey             (RGB(255, 128, 255));
					level_2_tiles[9]              = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_TILE_LEVEL_2_WALL_SE"),          level_2_tiles[9]->CreateSurface             (0, m_config.hInstance, GFX_TILE_LEVEL_2_WALL_SE,          TEXT("GRAPHICS"))); level_2_tiles[9]->SetColorKey             (RGB(255, 128, 255));
					captive_frederick_j_smiley[0] = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_CAPTIVE_FREDERICK_H_SMILEY_00"), captive_frederick_j_smiley[0]->CreateSurface(0, m_config.hInstance, GFX_CAPTIVE_FREDERICK_H_SMILEY_00, TEXT("GRAPHICS"))); captive_frederick_j_smiley[0]->SetColorKey(RGB(255, 128, 255));
					captive_frederick_j_smiley[1] = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_CAPTIVE_FREDERICK_H_SMILEY_01"), captive_frederick_j_smiley[1]->CreateSurface(0, m_config.hInstance, GFX_CAPTIVE_FREDERICK_H_SMILEY_01, TEXT("GRAPHICS"))); captive_frederick_j_smiley[1]->SetColorKey(RGB(255, 128, 255));
				break; }
				case 3: {
					level_3_tiles[0]   = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_TILE_LEVEL_3_FLOOR_01"),   level_3_tiles[0]->CreateSurface  (0, m_config.hInstance, GFX_TILE_LEVEL_3_FLOOR_01,   TEXT("GRAPHICS"))); level_3_tiles[0]->SetColorKey  (RGB(255, 128, 255));
					level_3_tiles[1]   = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_TILE_LEVEL_3_WALL_BLOCK"), level_3_tiles[1]->CreateSurface  (0, m_config.hInstance, GFX_TILE_LEVEL_3_WALL_BLOCK, TEXT("GRAPHICS"))); level_3_tiles[1]->SetColorKey  (RGB(255, 128, 255));
					level_3_tiles[2]   = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_TILE_LEVEL_3_WALL_N"),     level_3_tiles[2]->CreateSurface  (0, m_config.hInstance, GFX_TILE_LEVEL_3_WALL_N,     TEXT("GRAPHICS"))); level_3_tiles[2]->SetColorKey  (RGB(255, 128, 255));
					level_3_tiles[3]   = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_TILE_LEVEL_3_WALL_E"),     level_3_tiles[3]->CreateSurface  (0, m_config.hInstance, GFX_TILE_LEVEL_3_WALL_E,     TEXT("GRAPHICS"))); level_3_tiles[3]->SetColorKey  (RGB(255, 128, 255));
					level_3_tiles[4]   = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_TILE_LEVEL_3_WALL_S"),     level_3_tiles[4]->CreateSurface  (0, m_config.hInstance, GFX_TILE_LEVEL_3_WALL_S,     TEXT("GRAPHICS"))); level_3_tiles[4]->SetColorKey  (RGB(255, 128, 255));
					level_3_tiles[5]   = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_TILE_LEVEL_3_WALL_W"),     level_3_tiles[5]->CreateSurface  (0, m_config.hInstance, GFX_TILE_LEVEL_3_WALL_W,     TEXT("GRAPHICS"))); level_3_tiles[5]->SetColorKey  (RGB(255, 128, 255));
					level_3_tiles[6]   = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_TILE_LEVEL_3_WALL_NW"),    level_3_tiles[6]->CreateSurface  (0, m_config.hInstance, GFX_TILE_LEVEL_3_WALL_NW,    TEXT("GRAPHICS"))); level_3_tiles[6]->SetColorKey  (RGB(255, 128, 255));
					level_3_tiles[7]   = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_TILE_LEVEL_3_WALL_NE"),    level_3_tiles[7]->CreateSurface  (0, m_config.hInstance, GFX_TILE_LEVEL_3_WALL_NE,    TEXT("GRAPHICS"))); level_3_tiles[7]->SetColorKey  (RGB(255, 128, 255));
					level_3_tiles[8]   = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_TILE_LEVEL_3_WALL_SW"),    level_3_tiles[8]->CreateSurface  (0, m_config.hInstance, GFX_TILE_LEVEL_3_WALL_SW,    TEXT("GRAPHICS"))); level_3_tiles[8]->SetColorKey  (RGB(255, 128, 255));
					level_3_tiles[9]   = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_TILE_LEVEL_3_WALL_SE"),    level_3_tiles[9]->CreateSurface  (0, m_config.hInstance, GFX_TILE_LEVEL_3_WALL_SE,    TEXT("GRAPHICS"))); level_3_tiles[9]->SetColorKey  (RGB(255, 128, 255));
					level_3_tiles[10]  = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_TILE_LEVEL_3_WALL_ALONE"), level_3_tiles[10]->CreateSurface (0, m_config.hInstance, GFX_TILE_LEVEL_3_WALL_ALONE, TEXT("GRAPHICS"))); level_3_tiles[10]->SetColorKey (RGB(255, 128, 255));
					captive_catrina[0] = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_CAPTIVE_CATRINA_00"),      captive_catrina[0]->CreateSurface(0, m_config.hInstance, GFX_CAPTIVE_CATRINA_00,      TEXT("GRAPHICS"))); captive_catrina[0]->SetColorKey(RGB(255, 128, 255));
					captive_catrina[1] = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_CAPTIVE_CATRINA_01"),      captive_catrina[1]->CreateSurface(0, m_config.hInstance, GFX_CAPTIVE_CATRINA_01,      TEXT("GRAPHICS"))); captive_catrina[1]->SetColorKey(RGB(255, 128, 255));
				break; }
				case 4: {
					level_4_tiles[0]        = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_TILE_LEVEL_4_FLOOR_01"),   level_4_tiles[0]->CreateSurface       (0, m_config.hInstance, GFX_TILE_LEVEL_4_FLOOR_01,   TEXT("GRAPHICS"))); level_4_tiles[0]->SetColorKey       (RGB(255, 128, 255));
					level_4_tiles[1]        = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_TILE_LEVEL_4_WALL_BLOCK"), level_4_tiles[1]->CreateSurface       (0, m_config.hInstance, GFX_TILE_LEVEL_4_WALL_BLOCK, TEXT("GRAPHICS"))); level_4_tiles[1]->SetColorKey       (RGB(255, 128, 255));
					level_4_tiles[2]        = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_TILE_LEVEL_4_WALL_N"),     level_4_tiles[2]->CreateSurface       (0, m_config.hInstance, GFX_TILE_LEVEL_4_WALL_N,     TEXT("GRAPHICS"))); level_4_tiles[2]->SetColorKey       (RGB(255, 128, 255));
					level_4_tiles[3]        = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_TILE_LEVEL_4_WALL_E"),     level_4_tiles[3]->CreateSurface       (0, m_config.hInstance, GFX_TILE_LEVEL_4_WALL_E,     TEXT("GRAPHICS"))); level_4_tiles[3]->SetColorKey       (RGB(255, 128, 255));
					level_4_tiles[4]        = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_TILE_LEVEL_4_WALL_S"),     level_4_tiles[4]->CreateSurface       (0, m_config.hInstance, GFX_TILE_LEVEL_4_WALL_S,     TEXT("GRAPHICS"))); level_4_tiles[4]->SetColorKey       (RGB(255, 128, 255));
					level_4_tiles[5]        = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_TILE_LEVEL_4_WALL_W"),     level_4_tiles[5]->CreateSurface       (0, m_config.hInstance, GFX_TILE_LEVEL_4_WALL_W,     TEXT("GRAPHICS"))); level_4_tiles[5]->SetColorKey       (RGB(255, 128, 255));
					level_4_tiles[6]        = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_TILE_LEVEL_4_WALL_NW"),    level_4_tiles[6]->CreateSurface       (0, m_config.hInstance, GFX_TILE_LEVEL_4_WALL_NW,    TEXT("GRAPHICS"))); level_4_tiles[6]->SetColorKey       (RGB(255, 128, 255));
					level_4_tiles[7]        = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_TILE_LEVEL_4_WALL_NE"),    level_4_tiles[7]->CreateSurface       (0, m_config.hInstance, GFX_TILE_LEVEL_4_WALL_NE,    TEXT("GRAPHICS"))); level_4_tiles[7]->SetColorKey       (RGB(255, 128, 255));
					level_4_tiles[8]        = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_TILE_LEVEL_4_WALL_SW"),    level_4_tiles[8]->CreateSurface       (0, m_config.hInstance, GFX_TILE_LEVEL_4_WALL_SW,    TEXT("GRAPHICS"))); level_4_tiles[8]->SetColorKey       (RGB(255, 128, 255));
					level_4_tiles[9]        = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_TILE_LEVEL_4_WALL_SE"),    level_4_tiles[9]->CreateSurface       (0, m_config.hInstance, GFX_TILE_LEVEL_4_WALL_SE,    TEXT("GRAPHICS"))); level_4_tiles[9]->SetColorKey       (RGB(255, 128, 255));
					level_4_tiles[10]       = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_TILE_LEVEL_4_WALL_ALONE"), level_4_tiles[10]->CreateSurface      (0, m_config.hInstance, GFX_TILE_LEVEL_4_WALL_ALONE, TEXT("GRAPHICS"))); level_4_tiles[10]->SetColorKey      (RGB(255, 128, 255));
					captive_brenda_bubey[0] = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_CAPTIVE_BRENDA_BUBEY_00"), captive_brenda_bubey[0]->CreateSurface(0, m_config.hInstance, GFX_CAPTIVE_BRENDA_BUBEY_00, TEXT("GRAPHICS"))); captive_brenda_bubey[0]->SetColorKey(RGB(255, 128, 255));
					captive_brenda_bubey[1] = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_CAPTIVE_BRENDA_BUBEY_01"), captive_brenda_bubey[1]->CreateSurface(0, m_config.hInstance, GFX_CAPTIVE_BRENDA_BUBEY_01, TEXT("GRAPHICS"))); captive_brenda_bubey[1]->SetColorKey(RGB(255, 128, 255));
				break; }
				case 5: {
					level_5_tiles[0]  = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_TILE_LEVEL_5_FLOOR_01"),        level_5_tiles[0]->CreateSurface (0, m_config.hInstance, GFX_TILE_LEVEL_5_FLOOR_01,        TEXT("GRAPHICS"))); level_5_tiles[0]->SetColorKey (RGB(255, 128, 255));
					level_5_tiles[1]  = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_TILE_LEVEL_5_WALL_BLOCK"),      level_5_tiles[1]->CreateSurface (0, m_config.hInstance, GFX_TILE_LEVEL_5_WALL_BLOCK,      TEXT("GRAPHICS"))); level_5_tiles[1]->SetColorKey (RGB(255, 128, 255));
					level_5_tiles[2]  = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_TILE_LEVEL_5_WALL_N"),          level_5_tiles[2]->CreateSurface (0, m_config.hInstance, GFX_TILE_LEVEL_5_WALL_N,          TEXT("GRAPHICS"))); level_5_tiles[2]->SetColorKey (RGB(255, 128, 255));
					level_5_tiles[3]  = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_TILE_LEVEL_5_WALL_E"),          level_5_tiles[3]->CreateSurface (0, m_config.hInstance, GFX_TILE_LEVEL_5_WALL_E,          TEXT("GRAPHICS"))); level_5_tiles[3]->SetColorKey (RGB(255, 128, 255));
					level_5_tiles[4]  = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_TILE_LEVEL_5_WALL_S"),          level_5_tiles[4]->CreateSurface (0, m_config.hInstance, GFX_TILE_LEVEL_5_WALL_S,          TEXT("GRAPHICS"))); level_5_tiles[4]->SetColorKey (RGB(255, 128, 255));
					level_5_tiles[5]  = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_TILE_LEVEL_5_WALL_W"),          level_5_tiles[5]->CreateSurface (0, m_config.hInstance, GFX_TILE_LEVEL_5_WALL_W,          TEXT("GRAPHICS"))); level_5_tiles[5]->SetColorKey (RGB(255, 128, 255));
					level_5_tiles[6]  = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_TILE_LEVEL_5_WALL_NW"),         level_5_tiles[6]->CreateSurface (0, m_config.hInstance, GFX_TILE_LEVEL_5_WALL_NW,         TEXT("GRAPHICS"))); level_5_tiles[6]->SetColorKey (RGB(255, 128, 255));
					level_5_tiles[7]  = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_TILE_LEVEL_5_WALL_NE"),         level_5_tiles[7]->CreateSurface (0, m_config.hInstance, GFX_TILE_LEVEL_5_WALL_NE,         TEXT("GRAPHICS"))); level_5_tiles[7]->SetColorKey (RGB(255, 128, 255));
					level_5_tiles[8]  = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_TILE_LEVEL_5_WALL_SW"),         level_5_tiles[8]->CreateSurface (0, m_config.hInstance, GFX_TILE_LEVEL_5_WALL_SW,         TEXT("GRAPHICS"))); level_5_tiles[8]->SetColorKey (RGB(255, 128, 255));
					level_5_tiles[9]  = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_TILE_LEVEL_5_WALL_SE"),         level_5_tiles[9]->CreateSurface (0, m_config.hInstance, GFX_TILE_LEVEL_5_WALL_SE,         TEXT("GRAPHICS"))); level_5_tiles[9]->SetColorKey (RGB(255, 128, 255));
					level_5_tiles[10] = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_TILE_LEVEL_5_WALL_ALONE"),      level_5_tiles[10]->CreateSurface(0, m_config.hInstance, GFX_TILE_LEVEL_5_WALL_ALONE,      TEXT("GRAPHICS"))); level_5_tiles[10]->SetColorKey(RGB(255, 128, 255));
					level_5_tiles[11] = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_TILE_LEVEL_5_WALL_N_TJOINT"),   level_5_tiles[11]->CreateSurface(0, m_config.hInstance, GFX_TILE_LEVEL_5_WALL_N_TJOINT,   TEXT("GRAPHICS"))); level_5_tiles[11]->SetColorKey(RGB(255, 128, 255));
					level_5_tiles[12] = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_TILE_LEVEL_5_WALL_E_TJOINT"),   level_5_tiles[12]->CreateSurface(0, m_config.hInstance, GFX_TILE_LEVEL_5_WALL_E_TJOINT,   TEXT("GRAPHICS"))); level_5_tiles[12]->SetColorKey(RGB(255, 128, 255));
					level_5_tiles[13] = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_TILE_LEVEL_5_WALL_S_TJOINT"),   level_5_tiles[13]->CreateSurface(0, m_config.hInstance, GFX_TILE_LEVEL_5_WALL_S_TJOINT,   TEXT("GRAPHICS"))); level_5_tiles[13]->SetColorKey(RGB(255, 128, 255));
					level_5_tiles[14] = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_TILE_LEVEL_5_WALL_W_TJOINT"),   level_5_tiles[14]->CreateSurface(0, m_config.hInstance, GFX_TILE_LEVEL_5_WALL_W_TJOINT,   TEXT("GRAPHICS"))); level_5_tiles[14]->SetColorKey(RGB(255, 128, 255));
					level_5_tiles[15] = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_TILE_LEVEL_5_WALL_HORIZONTAL"), level_5_tiles[15]->CreateSurface(0, m_config.hInstance, GFX_TILE_LEVEL_5_WALL_HORIZONTAL, TEXT("GRAPHICS"))); level_5_tiles[15]->SetColorKey(RGB(255, 128, 255));
					level_5_tiles[16] = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_TILE_LEVEL_5_WALL_VERTICAL"),   level_5_tiles[16]->CreateSurface(0, m_config.hInstance, GFX_TILE_LEVEL_5_WALL_VERTICAL,   TEXT("GRAPHICS"))); level_5_tiles[16]->SetColorKey(RGB(255, 128, 255));
					captive_sully[0]  = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_CAPTIVE_SULLY_00"),             captive_sully[0]->CreateSurface (0, m_config.hInstance, GFX_CAPTIVE_SULLY_00,             TEXT("GRAPHICS"))); captive_sully[0]->SetColorKey (RGB(255, 128, 255));
					captive_sully[1]  = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_CAPTIVE_SULLY_01"),             captive_sully[1]->CreateSurface (0, m_config.hInstance, GFX_CAPTIVE_SULLY_01,             TEXT("GRAPHICS"))); captive_sully[1]->SetColorKey (RGB(255, 128, 255));
				break; }
			}
		break; }

    case 3: {
			tiles[20]					= new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_TILE_TELEPORTER_00"), tiles[20]->CreateSurface				(0, m_config.hInstance, GFX_TILE_TELEPORTER_00, TEXT("GRAPHICS"))); tiles[20]->SetColorKey				(RGB(255, 128, 255));
			tiles[32]					= new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_TILE_HEALTH"),        tiles[32]->CreateSurface				(0, m_config.hInstance, GFX_TILE_HEALTH,        TEXT("GRAPHICS"))); tiles[32]->SetColorKey				(RGB(255, 128, 255));
			tiles[23]					= new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_TILE_CONSOLE_00"),    tiles[23]->CreateSurface				(0, m_config.hInstance, GFX_TILE_CONSOLE_00,    TEXT("GRAPHICS"))); tiles[23]->SetColorKey				(RGB(255, 128, 255));
			tiles[24]					= new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_TILE_CONSOLE_00"),    tiles[24]->CreateSurface				(0, m_config.hInstance, GFX_TILE_CONSOLE_00,    TEXT("GRAPHICS"))); tiles[24]->SetColorKey				(RGB(255, 128, 255));
			tiles[25]					= new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_TILE_CONSOLE_00"),    tiles[25]->CreateSurface				(0, m_config.hInstance, GFX_TILE_CONSOLE_00,    TEXT("GRAPHICS"))); tiles[25]->SetColorKey				(RGB(255, 128, 255));
			tiles[26]					= new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_TILE_CONSOLE_00"),    tiles[26]->CreateSurface				(0, m_config.hInstance, GFX_TILE_CONSOLE_00,    TEXT("GRAPHICS"))); tiles[26]->SetColorKey				(RGB(255, 128, 255));
			tiles[27]					= new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_TILE_CONSOLE_00"),    tiles[27]->CreateSurface				(0, m_config.hInstance, GFX_TILE_CONSOLE_00,    TEXT("GRAPHICS"))); tiles[27]->SetColorKey				(RGB(255, 128, 255));
			gfxConsoleFlipped = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_TILE_CONSOLE_01"),    gfxConsoleFlipped->CreateSurface(0, m_config.hInstance, GFX_TILE_CONSOLE_01,    TEXT("GRAPHICS"))); gfxConsoleFlipped->SetColorKey(RGB(255, 128, 255));
		break; }

		case 4: {
      // Don't forget to point the tile array members to these initially as appropriate!
      tiles[30] = captive[0];
			// And the dissolve surface
			dissolve_surface = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : 0x0054"), dissolve_surface->CreateSurface(NULL, 40, 40)); dissolve_surface->SetColorKey(RGB(255, 128, 255));
		break; }

		case 5: {
			// Load player animations
			player_walking_n[0] = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_PLAYER_WALKING_N_00"), player_walking_n[0]->CreateSurface(0, m_config.hInstance, GFX_PLAYER_WALKING_N_00, TEXT("GRAPHICS"))); player_walking_n[0]->SetColorKey(RGB(255, 128, 255));
			player_walking_n[1] = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_PLAYER_WALKING_N_01"), player_walking_n[1]->CreateSurface(0, m_config.hInstance, GFX_PLAYER_WALKING_N_01, TEXT("GRAPHICS"))); player_walking_n[1]->SetColorKey(RGB(255, 128, 255));
			player_walking_n[2] = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_PLAYER_WALKING_N_02"), player_walking_n[2]->CreateSurface(0, m_config.hInstance, GFX_PLAYER_WALKING_N_02, TEXT("GRAPHICS"))); player_walking_n[2]->SetColorKey(RGB(255, 128, 255));
			player_walking_e[0] = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_PLAYER_WALKING_E_00"), player_walking_e[0]->CreateSurface(0, m_config.hInstance, GFX_PLAYER_WALKING_E_00, TEXT("GRAPHICS"))); player_walking_e[0]->SetColorKey(RGB(255, 128, 255));
			player_walking_e[1] = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_PLAYER_WALKING_E_01"), player_walking_e[1]->CreateSurface(0, m_config.hInstance, GFX_PLAYER_WALKING_E_01, TEXT("GRAPHICS"))); player_walking_e[1]->SetColorKey(RGB(255, 128, 255));
			player_walking_e[2] = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_PLAYER_WALKING_E_02"), player_walking_e[2]->CreateSurface(0, m_config.hInstance, GFX_PLAYER_WALKING_E_02, TEXT("GRAPHICS"))); player_walking_e[2]->SetColorKey(RGB(255, 128, 255));
			player_walking_s[0] = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_PLAYER_WALKING_S_00"), player_walking_s[0]->CreateSurface(0, m_config.hInstance, GFX_PLAYER_WALKING_S_00, TEXT("GRAPHICS"))); player_walking_s[0]->SetColorKey(RGB(255, 128, 255));
			player_walking_s[1] = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_PLAYER_WALKING_S_01"), player_walking_s[1]->CreateSurface(0, m_config.hInstance, GFX_PLAYER_WALKING_S_01, TEXT("GRAPHICS"))); player_walking_s[1]->SetColorKey(RGB(255, 128, 255));
			player_walking_s[2] = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_PLAYER_WALKING_S_02"), player_walking_s[2]->CreateSurface(0, m_config.hInstance, GFX_PLAYER_WALKING_S_02, TEXT("GRAPHICS"))); player_walking_s[2]->SetColorKey(RGB(255, 128, 255));
			player_walking_w[0] = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_PLAYER_WALKING_W_00"), player_walking_w[0]->CreateSurface(0, m_config.hInstance, GFX_PLAYER_WALKING_W_00, TEXT("GRAPHICS"))); player_walking_w[0]->SetColorKey(RGB(255, 128, 255));
			player_walking_w[1] = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_PLAYER_WALKING_W_01"), player_walking_w[1]->CreateSurface(0, m_config.hInstance, GFX_PLAYER_WALKING_W_01, TEXT("GRAPHICS"))); player_walking_w[1]->SetColorKey(RGB(255, 128, 255));
			player_walking_w[2] = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_PLAYER_WALKING_W_02"), player_walking_w[2]->CreateSurface(0, m_config.hInstance, GFX_PLAYER_WALKING_W_02, TEXT("GRAPHICS"))); player_walking_w[2]->SetColorKey(RGB(255, 128, 255));
		break; }

		case 6: {
			// Load robot still animations
			robot_still[0] = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_ROBOT_STILL_00"), robot_still[0]->CreateSurface(0, m_config.hInstance, GFX_ROBOT_STILL_00, TEXT("GRAPHICS"))); robot_still[0]->SetColorKey(RGB(255, 128, 255));
			robot_still[1] = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_ROBOT_STILL_01"), robot_still[1]->CreateSurface(0, m_config.hInstance, GFX_ROBOT_STILL_01, TEXT("GRAPHICS"))); robot_still[1]->SetColorKey(RGB(255, 128, 255));
			robot_still[2] = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_ROBOT_STILL_02"), robot_still[2]->CreateSurface(0, m_config.hInstance, GFX_ROBOT_STILL_02, TEXT("GRAPHICS"))); robot_still[2]->SetColorKey(RGB(255, 128, 255));
			robot_still[3] = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_ROBOT_STILL_03"), robot_still[3]->CreateSurface(0, m_config.hInstance, GFX_ROBOT_STILL_03, TEXT("GRAPHICS"))); robot_still[3]->SetColorKey(RGB(255, 128, 255));
			robot_still[4] = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_ROBOT_STILL_04"), robot_still[4]->CreateSurface(0, m_config.hInstance, GFX_ROBOT_STILL_04, TEXT("GRAPHICS"))); robot_still[4]->SetColorKey(RGB(255, 128, 255));
			robot_still[5] = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_ROBOT_STILL_05"), robot_still[5]->CreateSurface(0, m_config.hInstance, GFX_ROBOT_STILL_05, TEXT("GRAPHICS"))); robot_still[5]->SetColorKey(RGB(255, 128, 255));
			robot_still[6] = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_ROBOT_STILL_06"), robot_still[6]->CreateSurface(0, m_config.hInstance, GFX_ROBOT_STILL_06, TEXT("GRAPHICS"))); robot_still[6]->SetColorKey(RGB(255, 128, 255));
		break; }

		case 7: {
			// Load robot pre-appearing images
			robot_new_tile_appearing[0] = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_ROBOT_NEW_TILE_APPEARING_00"), robot_new_tile_appearing[0]->CreateSurface(0, m_config.hInstance, GFX_ROBOT_NEW_TILE_APPEARING_00, TEXT("GRAPHICS"))); robot_new_tile_appearing[0]->SetColorKey(RGB(255, 128, 255));
			robot_new_tile_appearing[1] = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_ROBOT_NEW_TILE_APPEARING_02"), robot_new_tile_appearing[1]->CreateSurface(0, m_config.hInstance, GFX_ROBOT_NEW_TILE_APPEARING_01, TEXT("GRAPHICS"))); robot_new_tile_appearing[1]->SetColorKey(RGB(255, 128, 255));
			robot_new_tile_appearing[2] = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_ROBOT_NEW_TILE_APPEARING_03"), robot_new_tile_appearing[2]->CreateSurface(0, m_config.hInstance, GFX_ROBOT_NEW_TILE_APPEARING_02, TEXT("GRAPHICS"))); robot_new_tile_appearing[2]->SetColorKey(RGB(255, 128, 255));
			robot_new_tile_appearing[3] = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_ROBOT_NEW_TILE_APPEARING_04"), robot_new_tile_appearing[3]->CreateSurface(0, m_config.hInstance, GFX_ROBOT_NEW_TILE_APPEARING_03, TEXT("GRAPHICS"))); robot_new_tile_appearing[3]->SetColorKey(RGB(255, 128, 255));
			robot_new_tile_appearing[4] = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_ROBOT_NEW_TILE_APPEARING_05"), robot_new_tile_appearing[4]->CreateSurface(0, m_config.hInstance, GFX_ROBOT_NEW_TILE_APPEARING_04, TEXT("GRAPHICS"))); robot_new_tile_appearing[4]->SetColorKey(RGB(255, 128, 255));
			robot_new_tile_appearing[5] = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_ROBOT_NEW_TILE_APPEARING_06"), robot_new_tile_appearing[5]->CreateSurface(0, m_config.hInstance, GFX_ROBOT_NEW_TILE_APPEARING_05, TEXT("GRAPHICS"))); robot_new_tile_appearing[5]->SetColorKey(RGB(255, 128, 255));
    break; }

    case 8: {
      // Load robot disappearing & appearing animations
      robot_disappearing_appearing[0]  = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_ROBOT_DISAPPEARING_APPEARING_00"), robot_disappearing_appearing[0]->CreateSurface (0, m_config.hInstance, GFX_ROBOT_DISAPPEARING_APPEARING_00, TEXT("GRAPHICS"))); robot_disappearing_appearing[0]->SetColorKey(RGB(255, 128, 255));
			robot_disappearing_appearing[1]  = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_ROBOT_DISAPPEARING_APPEARING_01"), robot_disappearing_appearing[1]->CreateSurface (0, m_config.hInstance, GFX_ROBOT_DISAPPEARING_APPEARING_01, TEXT("GRAPHICS"))); robot_disappearing_appearing[1]->SetColorKey(RGB(255, 128, 255));
			robot_disappearing_appearing[2]  = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_ROBOT_DISAPPEARING_APPEARING_02"), robot_disappearing_appearing[2]->CreateSurface (0, m_config.hInstance, GFX_ROBOT_DISAPPEARING_APPEARING_02, TEXT("GRAPHICS"))); robot_disappearing_appearing[2]->SetColorKey(RGB(255, 128, 255));
			robot_disappearing_appearing[3]  = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_ROBOT_DISAPPEARING_APPEARING_03"), robot_disappearing_appearing[3]->CreateSurface (0, m_config.hInstance, GFX_ROBOT_DISAPPEARING_APPEARING_03, TEXT("GRAPHICS"))); robot_disappearing_appearing[3]->SetColorKey(RGB(255, 128, 255));
			robot_disappearing_appearing[4]  = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_ROBOT_DISAPPEARING_APPEARING_04"), robot_disappearing_appearing[4]->CreateSurface (0, m_config.hInstance, GFX_ROBOT_DISAPPEARING_APPEARING_04, TEXT("GRAPHICS"))); robot_disappearing_appearing[4]->SetColorKey(RGB(255, 128, 255));
			robot_disappearing_appearing[5]  = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_ROBOT_DISAPPEARING_APPEARING_05"), robot_disappearing_appearing[5]->CreateSurface (0, m_config.hInstance, GFX_ROBOT_DISAPPEARING_APPEARING_05, TEXT("GRAPHICS"))); robot_disappearing_appearing[5]->SetColorKey(RGB(255, 128, 255));
			robot_disappearing_appearing[6]  = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_ROBOT_DISAPPEARING_APPEARING_06"), robot_disappearing_appearing[6]->CreateSurface (0, m_config.hInstance, GFX_ROBOT_DISAPPEARING_APPEARING_06, TEXT("GRAPHICS"))); robot_disappearing_appearing[6]->SetColorKey(RGB(255, 128, 255));
			robot_disappearing_appearing[7]  = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_ROBOT_DISAPPEARING_APPEARING_07"), robot_disappearing_appearing[7]->CreateSurface (0, m_config.hInstance, GFX_ROBOT_DISAPPEARING_APPEARING_07, TEXT("GRAPHICS"))); robot_disappearing_appearing[7]->SetColorKey(RGB(255, 128, 255));
			robot_disappearing_appearing[8]  = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_ROBOT_DISAPPEARING_APPEARING_08"), robot_disappearing_appearing[8]->CreateSurface (0, m_config.hInstance, GFX_ROBOT_DISAPPEARING_APPEARING_08, TEXT("GRAPHICS"))); robot_disappearing_appearing[8]->SetColorKey(RGB(255, 128, 255));
			robot_disappearing_appearing[9]  = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_ROBOT_DISAPPEARING_APPEARING_09"), robot_disappearing_appearing[9]->CreateSurface (0, m_config.hInstance, GFX_ROBOT_DISAPPEARING_APPEARING_09, TEXT("GRAPHICS"))); robot_disappearing_appearing[9]->SetColorKey(RGB(255, 128, 255));
			robot_disappearing_appearing[10] = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_ROBOT_DISAPPEARING_APPEARING_10"), robot_disappearing_appearing[10]->CreateSurface(0, m_config.hInstance, GFX_ROBOT_DISAPPEARING_APPEARING_10, TEXT("GRAPHICS"))); robot_disappearing_appearing[10]->SetColorKey(RGB(255, 128, 255));
			robot_disappearing_appearing[11] = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_ROBOT_DISAPPEARING_APPEARING_11"), robot_disappearing_appearing[11]->CreateSurface(0, m_config.hInstance, GFX_ROBOT_DISAPPEARING_APPEARING_11, TEXT("GRAPHICS"))); robot_disappearing_appearing[11]->SetColorKey(RGB(255, 128, 255));
			robot_disappearing_appearing[12] = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_ROBOT_DISAPPEARING_APPEARING_12"), robot_disappearing_appearing[12]->CreateSurface(0, m_config.hInstance, GFX_ROBOT_DISAPPEARING_APPEARING_12, TEXT("GRAPHICS"))); robot_disappearing_appearing[12]->SetColorKey(RGB(255, 128, 255));
			robot_disappearing_appearing[13] = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_ROBOT_DISAPPEARING_APPEARING_13"), robot_disappearing_appearing[13]->CreateSurface(0, m_config.hInstance, GFX_ROBOT_DISAPPEARING_APPEARING_13, TEXT("GRAPHICS"))); robot_disappearing_appearing[13]->SetColorKey(RGB(255, 128, 255));
			robot_disappearing_appearing[14] = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_ROBOT_DISAPPEARING_APPEARING_14"), robot_disappearing_appearing[14]->CreateSurface(0, m_config.hInstance, GFX_ROBOT_DISAPPEARING_APPEARING_14, TEXT("GRAPHICS"))); robot_disappearing_appearing[14]->SetColorKey(RGB(255, 128, 255));
			robot_disappearing_appearing[15] = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_ROBOT_DISAPPEARING_APPEARING_15"), robot_disappearing_appearing[15]->CreateSurface(0, m_config.hInstance, GFX_ROBOT_DISAPPEARING_APPEARING_15, TEXT("GRAPHICS"))); robot_disappearing_appearing[15]->SetColorKey(RGB(255, 128, 255));
			robot_disappearing_appearing[16] = new CGapiSurface(); createSurface(TEXT("walking_around_the_ship : GFX_ROBOT_DISAPPEARING_APPEARING_16"), robot_disappearing_appearing[16]->CreateSurface(0, m_config.hInstance, GFX_ROBOT_DISAPPEARING_APPEARING_16, TEXT("GRAPHICS"))); robot_disappearing_appearing[16]->SetColorKey(RGB(255, 128, 255));
    break; }

    case 9: {
      // Set up robot still animation sequence
			robot_anim_seq_still[0]  = robot_still[0];
			robot_anim_seq_still[1]  = robot_still[1];
			robot_anim_seq_still[2]  = robot_still[2];
			robot_anim_seq_still[3]  = robot_still[3];
			robot_anim_seq_still[4]  = robot_still[4];
			robot_anim_seq_still[5]  = robot_still[5];
			robot_anim_seq_still[6]  = robot_still[6];
			robot_anim_seq_still[7]  = robot_still[5];
			robot_anim_seq_still[8]  = robot_still[4];
			robot_anim_seq_still[9]  = robot_still[3];
			robot_anim_seq_still[10] = robot_still[2];
			robot_anim_seq_still[11] = robot_still[1];
			robot_anim_seq_still[12] = robot_still[0];
			robot_anim_seq_still[13] = NULL;
      // Set up robot disappearing animation sequence
      robot_anim_seq_disappearing[0]  = robot_disappearing_appearing[0];
			robot_anim_seq_disappearing[1]  = robot_disappearing_appearing[1];
			robot_anim_seq_disappearing[2]  = robot_disappearing_appearing[2];
			robot_anim_seq_disappearing[3]  = robot_disappearing_appearing[3];
			robot_anim_seq_disappearing[4]  = robot_disappearing_appearing[4];
			robot_anim_seq_disappearing[5]  = robot_disappearing_appearing[5];
			robot_anim_seq_disappearing[6]  = robot_disappearing_appearing[6];
			robot_anim_seq_disappearing[7]  = robot_disappearing_appearing[7];
			robot_anim_seq_disappearing[8]  = robot_disappearing_appearing[8];
			robot_anim_seq_disappearing[9]  = robot_disappearing_appearing[9];
			robot_anim_seq_disappearing[10] = robot_disappearing_appearing[10];
			robot_anim_seq_disappearing[11] = robot_disappearing_appearing[11];
			robot_anim_seq_disappearing[12] = robot_disappearing_appearing[12];
			robot_anim_seq_disappearing[13] = robot_disappearing_appearing[13];
			robot_anim_seq_disappearing[14] = robot_disappearing_appearing[14];
			robot_anim_seq_disappearing[15] = robot_disappearing_appearing[15];
			robot_anim_seq_disappearing[16] = robot_disappearing_appearing[16];
      robot_anim_seq_disappearing[17] = NULL;
      // Set up robot appearing animation sequence
			robot_anim_seq_appearing[0]  = robot_new_tile_appearing[0];
			robot_anim_seq_appearing[1]  = robot_new_tile_appearing[1];
			robot_anim_seq_appearing[2]  = robot_new_tile_appearing[2];
			robot_anim_seq_appearing[3]  = robot_new_tile_appearing[3];
			robot_anim_seq_appearing[4]  = robot_new_tile_appearing[4];
			robot_anim_seq_appearing[5]  = robot_new_tile_appearing[5];
			robot_anim_seq_appearing[6]  = robot_new_tile_appearing[4];
			robot_anim_seq_appearing[7]  = robot_new_tile_appearing[3];
			robot_anim_seq_appearing[8]  = robot_new_tile_appearing[2];
			robot_anim_seq_appearing[9]  = robot_new_tile_appearing[1];
			robot_anim_seq_appearing[10] = robot_new_tile_appearing[0];
			robot_anim_seq_appearing[11] = robot_new_tile_appearing[1];
			robot_anim_seq_appearing[12] = robot_new_tile_appearing[2];
			robot_anim_seq_appearing[13] = robot_new_tile_appearing[3];
			robot_anim_seq_appearing[14] = robot_new_tile_appearing[4];
      robot_anim_seq_appearing[15] = robot_new_tile_appearing[5];
			robot_anim_seq_appearing[16] = robot_disappearing_appearing[16];
			robot_anim_seq_appearing[17] = robot_disappearing_appearing[15];
			robot_anim_seq_appearing[18] = robot_disappearing_appearing[14];
			robot_anim_seq_appearing[19] = robot_disappearing_appearing[13];
			robot_anim_seq_appearing[20] = robot_disappearing_appearing[12];
			robot_anim_seq_appearing[21] = robot_disappearing_appearing[11];
			robot_anim_seq_appearing[22] = robot_disappearing_appearing[10];
			robot_anim_seq_appearing[23] = robot_disappearing_appearing[9];
			robot_anim_seq_appearing[24] = robot_disappearing_appearing[8];
      robot_anim_seq_appearing[25] = robot_disappearing_appearing[7];
      robot_anim_seq_appearing[26] = robot_disappearing_appearing[6];
      robot_anim_seq_appearing[27] = robot_disappearing_appearing[5];
      robot_anim_seq_appearing[28] = robot_disappearing_appearing[4];
      robot_anim_seq_appearing[29] = robot_disappearing_appearing[3];
      robot_anim_seq_appearing[30] = robot_disappearing_appearing[2];
      robot_anim_seq_appearing[31] = robot_disappearing_appearing[1];
      robot_anim_seq_appearing[32] = robot_disappearing_appearing[0];
      robot_anim_seq_appearing[33] = NULL;
		break; }

		case 10: {
			// Audio
			sfxAaah        = new hssSound(); loadSFX(TEXT("walking_around_the_ship : SFX_AAAH"),        sfxAaah->load       (m_config.hInstance, SFX_AAAH));        sfxAaah->loop       (false);
      sfxExplosion   = new hssSound(); loadSFX(TEXT("walking_around_the_ship : SFX_EXPLOSION"),   sfxExplosion->load  (m_config.hInstance, SFX_EXPLOSION));   sfxExplosion->loop  (false);
			sfxDeath       = new hssSound(); loadSFX(TEXT("walking_around_the_ship : SFX_DEATH"),       sfxDeath->load      (m_config.hInstance, SFX_DEATH));       sfxDeath->loop      (false);
			sfxBeamMeUp    = new hssSound(); loadSFX(TEXT("walking_around_the_ship : SFX_BEAMMEUP"),    sfxBeamMeUp->load   (m_config.hInstance, SFX_BEAMMEUP));    sfxBeamMeUp->loop   (false);
			sfxWalking     = new hssSound(); loadSFX(TEXT("walking_around_the_ship : SFX_WALKING"),     sfxWalking->load    (m_config.hInstance, SFX_WALKING));     sfxWalking->loop    (true);
      sfxHeartbeat_1 = new hssSound(); loadSFX(TEXT("walking_around_the_ship : SFX_HEARTBEAT_1"), sfxHeartbeat_1->load(m_config.hInstance, SFX_HEARTBEAT_1)); sfxHeartbeat_1->loop(false);
      sfxHeartbeat_2 = new hssSound(); loadSFX(TEXT("walking_around_the_ship : SFX_HEARTBEAT_2"), sfxHeartbeat_2->load(m_config.hInstance, SFX_HEARTBEAT_2)); sfxHeartbeat_2->loop(false);
      break; }

		case 11: {
			// General initialization
      walkingPlaying						= false;
			player_dir_east						= false;
			player_dir_west						= false;
			player_dir_south					= false;
			player_dir_north					= false;
			moved_north								= false;
			moved_east								= false;
			moved_south								= false;
			moved_west								= false;
			player_frame							= 0;
			player_frame_delay				= 0;
			fire_pressed							= false;
			doingTeleportation				= false;
      current_level_initialized = true;
      captiveFrameDelay         = 0;
      captiveFrameCounter       = 0;
      health_counter            = 0;
      health_frame              = 0;
      health_delay              = 0;
      initializeLevel(current_level, m_config);
       // Do this if we're restarting a saved game
			if (gameRestarted) {
				ul_tile.x					= cl_ul_tile.x;
				ul_tile.y					= cl_ul_tile.y;
				horizontal_offset = cl_horizontal_offset;
				vertical_offset		= cl_vertical_offset;
				player_position.x = cl_player_position.x;
				player_position.y = cl_player_position.y;
        gameRestarted = false;
			}
      // Do this if we're starting a new game, and do it only once!
      if (startingNewGame) {
        startingNewGame = false;
        startNewLevel(1);
      }
      randomlyPositionRobots();
			// Echo these values so we can easily get at them from class-level for saving
			cl_ul_tile.x				 = ul_tile.x;
			cl_ul_tile.y				 = ul_tile.y;
			cl_horizontal_offset = horizontal_offset;
			cl_vertical_offset	 = vertical_offset;
			cl_player_position.x = player_position.x;
			cl_player_position.y = player_position.y;
			writeKGAFile(true, false);
      processEvents = true;
		break; }

    case 12: {
      // Call the loaded for the character interaction screen
      // Note that this will continue to happen, meaning loading_step will remain 13, until
      // the loadCharacterInteraction() method increments it.  That method uses it's own
      // counter for loading.  This was a way to have one loader call on another over
      // and over, to keep the possibility of a smoothly animated waiting screen.
      loadCharacterInteraction(backbuffer);
    break; }

		// End of loading
		default: {
      previous_level = current_level;
			loading	= false;
			processEvents = true;
		break; }

	}

	// Show the Loading screen
	showLoadingScreen(backbuffer, true, true);

}


// ****************************************************************************************************************
// Destroyer
// ****************************************************************************************************************
void CGame::destroyWalkingAroundTheShip(CGapiSurface* backbuffer) {

	using namespace ns_WalkingAroundTheShip;

	processEvents = false;

	// Move on to the next step
	destroying_step++;

	// Do the appropriate step
	switch(destroying_step) {

		case 1: {
      sndObj.stopSounds();
			switch (previous_level) {
				case 1: {
					delete level_1_tiles[0];
					delete level_1_tiles[1];
					delete level_1_tiles[2];
					delete level_1_tiles[3];
					delete level_1_tiles[4];
					delete level_1_tiles[5];
					delete level_1_tiles[6];
					delete level_1_tiles[7];
					delete level_1_tiles[8];
					delete level_1_tiles[9];
					delete captive_eeger[0];
					delete captive_eeger[1];
				break; }
				case 2: {
					delete level_2_tiles[0];
					delete level_2_tiles[1];
					delete level_2_tiles[2];
					delete level_2_tiles[3];
					delete level_2_tiles[4];
					delete level_2_tiles[5];
					delete level_2_tiles[6];
					delete level_2_tiles[7];
					delete level_2_tiles[8];
					delete level_2_tiles[9];
					delete captive_frederick_j_smiley[0];
					delete captive_frederick_j_smiley[1];
				break; }
				case 3: {
					delete level_3_tiles[0];
					delete level_3_tiles[1];
					delete level_3_tiles[2];
					delete level_3_tiles[3];
					delete level_3_tiles[4];
					delete level_3_tiles[5];
					delete level_3_tiles[6];
					delete level_3_tiles[7];
					delete level_3_tiles[8];
					delete level_3_tiles[9];
					delete level_3_tiles[10];
					delete captive_catrina[0];
					delete captive_catrina[1];
				break; }
				case 4: {
					delete level_4_tiles[0];
					delete level_4_tiles[1];
					delete level_4_tiles[2];
					delete level_4_tiles[3];
					delete level_4_tiles[4];
					delete level_4_tiles[5];
					delete level_4_tiles[6];
					delete level_4_tiles[7];
					delete level_4_tiles[8];
					delete level_4_tiles[9];
					delete level_4_tiles[10];
					delete captive_brenda_bubey[0];
					delete captive_brenda_bubey[1];
				break; }
				case 5: {
					delete level_5_tiles[0];
					delete level_5_tiles[1];
					delete level_5_tiles[2];
					delete level_5_tiles[3];
					delete level_5_tiles[4];
					delete level_5_tiles[5];
					delete level_5_tiles[6];
					delete level_5_tiles[7];
					delete level_5_tiles[8];
					delete level_5_tiles[9];
					delete level_5_tiles[10];
					delete level_5_tiles[11];
					delete level_5_tiles[12];
					delete level_5_tiles[13];
					delete level_5_tiles[14];
					delete level_5_tiles[15];
					delete level_5_tiles[16];
					delete captive_sully[0];
					delete captive_sully[1];
				break; }
			}
		break; }

		case 2: {
			delete player_walking_n[0];
			delete player_walking_n[1];
			delete player_walking_n[2];
			delete player_walking_s[0];
			delete player_walking_s[1];
			delete player_walking_s[2];
			delete player_walking_e[0];
			delete player_walking_e[1];
			delete player_walking_e[2];
			delete player_walking_w[0];
			delete player_walking_w[1];
			delete player_walking_w[2];
		break; }

		case 3: {
			delete robot_still[0];
			delete robot_still[1];
			delete robot_still[2];
			delete robot_still[3];
			delete robot_still[4];
			delete robot_still[5];
			delete robot_still[6];
			delete dissolve_surface;
			delete tiles[20]; // Teleported
			delete tiles[32]; // Health
		break; }

		case 8: {
			delete tiles[23]; // Console
			delete tiles[24]; // Console
			delete tiles[25]; // Console
			delete tiles[26]; // Console
			delete tiles[27]; // Console
      delete sfxExplosion;
      delete explosion[0];
      delete explosion[1];
      delete explosion[2];
      delete explosion[3];
      delete explosion[4];
		break; }

		case 4: {
			delete robot_new_tile_appearing[0];
      delete robot_new_tile_appearing[1];
      delete robot_new_tile_appearing[2];
      delete robot_new_tile_appearing[3];
      delete robot_new_tile_appearing[4];
      delete robot_new_tile_appearing[5];
			delete robot_disappearing_appearing[0];
			delete robot_disappearing_appearing[1];
			delete robot_disappearing_appearing[2];
			delete robot_disappearing_appearing[3];
			delete robot_disappearing_appearing[4];
			delete robot_disappearing_appearing[5];
			delete robot_disappearing_appearing[6];
			delete robot_disappearing_appearing[7];
			delete robot_disappearing_appearing[8];
			delete robot_disappearing_appearing[9];
			delete robot_disappearing_appearing[10];
			delete robot_disappearing_appearing[11];
			delete robot_disappearing_appearing[12];
			delete robot_disappearing_appearing[13];
			delete robot_disappearing_appearing[14];
			delete robot_disappearing_appearing[15];
      delete robot_disappearing_appearing[16];
		break; }

		case 5: {
			delete gfxConsoleFlipped;
			delete heart[0];
      delete heart[1];
      delete gdo;
      delete gameDoneOff;
      delete sfxAaah;
      delete sfxDeath;
			delete sfxBeamMeUp;
			delete sfxWalking;
      delete sfxHeartbeat_1;
      delete sfxHeartbeat_2;
		break; }

    case 6: {
      // Call the destroyer for the character interaction screen
      // Note that this will continue to happen, meaning destroying_step will remain 6, until
      // the destroyCharacterInteraction() method increments it.  That method uses it's own
      // counter for destroying.  This was a way to have one destroyer call on another over
      // and over, to keep the possibility of a smoothly animated waiting screen.
      destroyCharacterInteraction(backbuffer);
    break; }

		default: {
			// All done destroying, start loading the next screen
			current_screen = screen_after_destroy;
			doLoad();
		break; }

	}

	// Show the Loading screen
	showLoadingScreen(backbuffer, true, true);

}


// ****************************************************************************************************************
// Utility functions
// ****************************************************************************************************************

// Called to start a new level (called just once to start a new level)
void CGame::startNewLevel(int current_level) {
  using namespace ns_WalkingAroundTheShip;
  // Start the map in the right place, and initially position our player
  got_health    = false;
  levelHintDone = false;
	games_done[0] = false;
	games_done[1] = false;
	games_done[2] = false;
	games_done[3] = false;
	games_done[4] = false;
	switch (current_level) {
		case 1: {
			ul_tile.x					= 0;
			ul_tile.y				  = 0;
			horizontal_offset = 0;
			vertical_offset	  = 0;
			player_position.x	= 160;
			player_position.y	= 160;
		break; }
		case 2: {
			ul_tile.x					= 38;
			ul_tile.y				  = 34;
			horizontal_offset = 0;
			vertical_offset	  = 0;
			player_position.x	= 160;
			player_position.y	= 160;
		break; }
		case 3: {
			ul_tile.x					= 37;
			ul_tile.y				  = 34;
			horizontal_offset = 0;
			vertical_offset	  = 0;
			player_position.x	= 160;
			player_position.y	= 240;
		break; }
		case 4: {
			ul_tile.x					= 28;
			ul_tile.y				  = 8;
			horizontal_offset = 0;
			vertical_offset	  = 0;
			player_position.x	= 60;
			player_position.y	= 80;
		break; }
		case 5: {
			ul_tile.x					= 0;
			ul_tile.y				  = 0;
			horizontal_offset = 0;
			vertical_offset	  = 0;
			player_position.x	= 80;
			player_position.y	= 80;
		break; }
	}
}


namespace ns_WalkingAroundTheShip {


	// Called to initialize the current level (called continually every time screen switched to csWalkingAroundTheShip)
	void initializeLevel(int current_level, GDAPPCONFIG m_config) {
    teleported_rcol     = 0;
    teleported_rcol_dir = 0;
		// Determine which level we're setting up and set up the appropriate one
		switch (current_level) {
			case 1: {
				HRSRC		hResInfo = FindResource(m_config.hInstance, MAKEINTRESOURCE(IDR_MAP_LEVEL_1), TEXT("MAPS"));
				HGLOBAL	hResD		 = LoadResource(m_config.hInstance, hResInfo);
				void*	  pvRes		 = LockResource(hResD);
				level_map				 = (unsigned char*)pvRes;
				tiles[0]         = level_1_tiles[0];
				tiles[3]         = level_1_tiles[1];
				tiles[4]         = level_1_tiles[2];
				tiles[5]         = level_1_tiles[3];
				tiles[6]         = level_1_tiles[4];
				tiles[7]         = level_1_tiles[5];
				tiles[8]         = level_1_tiles[6];
				tiles[9]         = level_1_tiles[7];
				tiles[10]        = level_1_tiles[8];
				tiles[11]        = level_1_tiles[9];
				captive[0]       = captive_eeger[0];
				captive[1]       = captive_eeger[1];
			break; }
			case 2: {
				HRSRC		hResInfo = FindResource(m_config.hInstance, MAKEINTRESOURCE(IDR_MAP_LEVEL_2), TEXT("MAPS"));
				HGLOBAL	hResD		 = LoadResource(m_config.hInstance, hResInfo);
				void*	  pvRes		 = LockResource(hResD);
				level_map				 = (unsigned char*)pvRes;
				tiles[0]         = level_2_tiles[0];
				tiles[3]         = level_2_tiles[1];
				tiles[4]         = level_2_tiles[2];
				tiles[5]         = level_2_tiles[3];
				tiles[6]         = level_2_tiles[4];
				tiles[7]         = level_2_tiles[5];
				tiles[8]         = level_2_tiles[6];
				tiles[9]         = level_2_tiles[7];
				tiles[10]        = level_2_tiles[8];
				tiles[11]        = level_2_tiles[9];
				captive[0]       = captive_frederick_j_smiley[0];
				captive[1]       = captive_frederick_j_smiley[1];
			break; }
			case 3: {
				HRSRC		hResInfo = FindResource(m_config.hInstance, MAKEINTRESOURCE(IDR_MAP_LEVEL_3), TEXT("MAPS"));
				HGLOBAL	hResD		 = LoadResource(m_config.hInstance, hResInfo);
				void*	  pvRes		 = LockResource(hResD);
				level_map				 = (unsigned char*)pvRes;
				tiles[0]         = level_3_tiles[0];
				tiles[3]         = level_3_tiles[1];
				tiles[4]         = level_3_tiles[2];
				tiles[5]         = level_3_tiles[3];
				tiles[6]         = level_3_tiles[4];
				tiles[7]         = level_3_tiles[5];
				tiles[8]         = level_3_tiles[6];
				tiles[9]         = level_3_tiles[7];
				tiles[10]        = level_3_tiles[8];
				tiles[11]        = level_3_tiles[9];
        tiles[12]        = level_3_tiles[10];
				captive[0]       = captive_catrina[0];
				captive[1]       = captive_catrina[1];
			break; }
			case 4: {
				HRSRC		hResInfo = FindResource(m_config.hInstance, MAKEINTRESOURCE(IDR_MAP_LEVEL_4), TEXT("MAPS"));
				HGLOBAL	hResD		 = LoadResource(m_config.hInstance, hResInfo);
				void*	  pvRes		 = LockResource(hResD);
				level_map				 = (unsigned char*)pvRes;
				tiles[0]         = level_4_tiles[0];
				tiles[3]         = level_4_tiles[1];
				tiles[4]         = level_4_tiles[2];
				tiles[5]         = level_4_tiles[3];
				tiles[6]         = level_4_tiles[4];
				tiles[7]         = level_4_tiles[5];
				tiles[8]         = level_4_tiles[6];
				tiles[9]         = level_4_tiles[7];
				tiles[10]        = level_4_tiles[8];
				tiles[11]        = level_4_tiles[9];
        tiles[12]        = level_4_tiles[10];
				captive[0]       = captive_brenda_bubey[0];
				captive[1]       = captive_brenda_bubey[1];
			break; }
			case 5: {
				HRSRC		hResInfo = FindResource(m_config.hInstance, MAKEINTRESOURCE(IDR_MAP_LEVEL_5), TEXT("MAPS"));
				HGLOBAL	hResD		 = LoadResource(m_config.hInstance, hResInfo);
				void*	  pvRes		 = LockResource(hResD);
				level_map				 = (unsigned char*)pvRes;
				tiles[0]         = level_5_tiles[0];
				tiles[3]         = level_5_tiles[1];
				tiles[4]         = level_5_tiles[2];
				tiles[5]         = level_5_tiles[3];
				tiles[6]         = level_5_tiles[4];
				tiles[7]         = level_5_tiles[5];
				tiles[8]         = level_5_tiles[6];
				tiles[9]         = level_5_tiles[7];
				tiles[10]        = level_5_tiles[8];
				tiles[11]        = level_5_tiles[9];
        tiles[12]        = level_5_tiles[10];
        tiles[13]        = level_5_tiles[11];
        tiles[14]        = level_5_tiles[12];
        tiles[15]        = level_5_tiles[13];
        tiles[16]        = level_5_tiles[14];
        tiles[17]        = level_5_tiles[15];
        tiles[18]        = level_5_tiles[16];
				captive[0]       = captive_sully[0];
				captive[1]       = captive_sully[1];
			break; }
		}
	}


	void randomlyPositionRobots() {
		// Now randomly position our 10 robots
		int i, x, y, tile;
		for (i = 0; i < ROBOTS_COUNT; i++) {
			newRobotPos:
				x = rand() % map_width;
				y = rand() % map_height;
				tile = *(level_map + (((y + 1) * map_width) + x + 1));
        // Out of bounds
				if (tile < tileFloorMin || tile > tileFloorMin) {
					goto newRobotPos;
				}
        // Not a floor tile
				if (x < 3 || y < 3 || x > map_width - 3 || y > map_height - 3) {
					goto newRobotPos;
				}
        // No robots on top of each other
        for (int j = 0; j < ROBOTS_COUNT; j++) {
          if (i != j && x == robots[j].tile.x && y == robots[j].tile.y) {
            goto newRobotPos;
          }
        }
				robots[i].justPositioned  = true;
        robots[i].tile.x		      = x;
				robots[i].tile.y		      = y;
				robots[i].anim_frame      = rand() % 12;
				robots[i].state			      = rsStill;
        robots[i].appearing_delay = 0;
        robots[i].still_counter   = rand() % 4;
		}
	}


	void repositionRobot(int i) {
		int d, x, y, z, tile;
		reposRobot:
			x = robots[i].tile.x;
			y = robots[i].tile.y;
      z = (rand() % MAX_ROBOT_MOVE) + 1; // Number of tiles to move robot
			d = rand() % 4;
			switch (d) {
				case 0: {
					x = robots[i].tile.x + z;
				break; }
				case 1: {
					x = robots[i].tile.x - z;
				break; }
				case 2: {
					y = robots[i].tile.y + z;
				break; }
				case 3: {
					y = robots[i].tile.y - z;
				break; }
				default: {
					goto reposRobot;
				break; }
			}
      // Out of bounds
			if (x < 2 || y < 2 || x > map_width - 2 || y > map_height - 2) {
			  goto reposRobot;
			}
      // Not a floor tile
			tile = *(level_map + (((y + 1) * map_width) + x + 1));
			if (tile < tileFloorMin || tile > tileFloorMin) {
				goto reposRobot;
			}
      // No robots on top of each other
      for (int j = 0; j < ROBOTS_COUNT; j++) {
        if (i != j && x == robots[j].tile.x && y == robots[j].tile.y) {
          goto reposRobot;
        }
      }
			robots[i].next_tile.x		= x;
			robots[i].next_tile.y		= y;
			robots[i].anim_frame		= 0;
			robots[i].still_counter	= 0;
      robots[i].explosion_delay = 0;
      robots[i].explosion_frame = 0;
  }


	int startMiniGame(int current_level, int tile) {
		int retVal = 0;
		// Determine which level we're on
		switch (current_level) {
			case 1: {
				// Determine which mini-game to start
				switch (tile) {
					case tileConsole_01: { retVal = csADayInTheStrife;			break; }
					case tileConsole_02: { retVal = csCopyCat;							break; }
					case tileConsole_03: { retVal = csCosmicSquirrel;				break; }
					case tileConsole_04: { retVal = csFlightOfDoom;					break; }
					case tileConsole_05: { retVal = csTheRedeyeOrder;				break; } // Special
				}
			break; }
			case 2: {
				// Determine which mini-game to start
				switch (tile) {
					case tileConsole_01: { retVal = csAlienBabble;					break; }
					case tileConsole_02: { retVal = csFarOutFowl;						break; }
				 	case tileConsole_03: { retVal = csDefendoh;	  					break; }
					case tileConsole_04: { retVal = csRefluxive;						break; }
					case tileConsole_05: { retVal = csDeathTrap;	    			break; } // Special
				}
			break; }
			case 3: {
				// Determine which mini-game to start
				switch (tile) {
					case tileConsole_01: { retVal = csAntigravitator;				break; }
					case tileConsole_02: { retVal = csInMemoria;						break; }
					case tileConsole_03: { retVal = csReluctantHero;				break; }
					case tileConsole_04: { retVal = csConquerror;						break; }
					case tileConsole_05: { retVal = csEngineer;							break; } // Special
        }
			break; }
			case 4: {
				// Determine which mini-game to start
				switch (tile) {
					case tileConsole_01: { retVal = csVirus;	  						break; }
					case tileConsole_02: { retVal = csFfopirSirtetPaehc;		break; }
					case tileConsole_03: { retVal = csGlutton;							break; }
					case tileConsole_04: { retVal = csLeparLand;						break; }
          case tileConsole_05: { retVal = csTheEscape;						break; } // Special
				}
			break; }
			case 5: {
				// Determine which mini-game to start
				switch (tile) {
					case tileConsole_01: { retVal = csTheBogazDerby;				break; }
					case tileConsole_02: { retVal = csSquishem;							break; }
					case tileConsole_03: { retVal = csTroubleInVectropolis; break; }
          case tileConsole_04: { retVal = csMuncherDude;			    break; }
					case tileConsole_05: { retVal = csSonOfEliminator;	    break; } // Special
				}
			break; }
		}
		return retVal;
	}


	POINT moveNorth(POINT player_position) {
		if (player_position.y > 40 || (ul_tile.y == 0 && vertical_offset == 0)) {
			moved_north = true;
			player_position.y = player_position.y - PLAYERMOVEONSCREEN;
		} else {
			if (ul_tile.y >= 0) {
				moved_north = true;
				vertical_offset = vertical_offset + PLAYERMOVESCROLLING;
				if (vertical_offset > 19) {
					vertical_offset = 0;
					ul_tile.y--;
				}
			}
		}
		return player_position;
	}


	POINT moveEast(POINT player_position) {
		if (player_position.x < 180 || (ul_tile.x == map_width - tiles_across_screen && horizontal_offset == 0)) {
			moved_east = true;
			player_position.x = player_position.x + PLAYERMOVEONSCREEN;
		} else {
			if (ul_tile.x <= map_width - tiles_across_screen) {
				moved_east = true;
				horizontal_offset = horizontal_offset - PLAYERMOVESCROLLING;
				if (horizontal_offset < -19) {
					horizontal_offset = 0;
					ul_tile.x++;
				}
			}
		}
		return player_position;
	}


	POINT moveSouth(POINT player_position) {
		if (player_position.y < 260 || (ul_tile.y == map_height - tiles_down_screen && vertical_offset == 0)) {
			moved_south = true;
			player_position.y = player_position.y + PLAYERMOVEONSCREEN;
		} else {
			if (ul_tile.y <= map_height - tiles_down_screen) {
				moved_south = true;
				vertical_offset = vertical_offset - PLAYERMOVESCROLLING;
				if (vertical_offset < -19) {
					vertical_offset = 0;
					ul_tile.y++;
				}
			}
		}
		return player_position;
	}


	POINT moveWest(POINT player_position) {
		if (player_position.x > 40 || (ul_tile.x == 0 && horizontal_offset == 0)) {
			moved_west = true;
			player_position.x = player_position.x - PLAYERMOVEONSCREEN;
		} else {
			if (ul_tile.x >= 0) {
				moved_west = true;
				horizontal_offset = horizontal_offset + PLAYERMOVESCROLLING;
				if (horizontal_offset > 19) {
					horizontal_offset = 0;
					ul_tile.x--;
				}
			}
		}
		return player_position;
	}


} // End of namespace