
#include "../main.h"


namespace ns_TroubleInVectropolis {


// ****************************************************************************************************************
// Defines specific to this mini-game
// ****************************************************************************************************************
#define smNorth			0
#define smEast			1
#define smSouth			2
#define smWest			3
#define smNorthEast 4
#define smSouthEast 5
#define smSouthWest 6
#define smNorthWest 7


// ****************************************************************************************************************
// Function prototypes specific to this mini-game
// ****************************************************************************************************************
void positionShip(int);


// ****************************************************************************************************************
// Globals specific to this mini-game
// ****************************************************************************************************************
TCHAR	instructions[][32] = { TEXT("Trouble In Vectropolis"),
														 TEXT(""),
														 TEXT("It's an alternate"),
														 TEXT("dimension, or something."),
														 TEXT("A dimension of sight"),
														 TEXT("and sound, but zero"),
														 TEXT("physical substance."),
														 TEXT("As if an artist drew"),
														 TEXT("an outline, but then lost"),
														 TEXT("his box of crayons!"),
                             //    ---------------------------
                             TEXT("The Goal"),
														 TEXT(""),
														 TEXT("Fly down the trench,"),
														 TEXT("destroying as many"),
														 TEXT("enemy fighters as"),
														 TEXT("possible.  Each one"),
														 TEXT("that gets past will"),
														 TEXT("cost you points."),
														 TEXT(""),
														 TEXT(""),
                             //    ---------------------------
                             TEXT("How To Play"),
														 TEXT(""),
														 TEXT("Move up, down, left or"),
														 TEXT("right to target, ACTION"),
														 TEXT("to fire.  Aim for the"),
														 TEXT("center of the enemy"),
														 TEXT("ships!  If your lasers"),
														 TEXT("overheat, they will not"),
														 TEXT("fire for a second.  Watch"),
														 TEXT("the meter along the top!"),
                             //    ----------------------------
};

CGapiSurface* ship[8];                         // Images for ships
CGapiSurface* crosshairs_red          = NULL;  // Image of crosshairs when lasers overheated
CGapiSurface* crosshairs_green        = NULL;  // Image of crosshairs when lasers OK
hssSound*			sfxShip                 = NULL;
hssSound*			sfxLaser                = NULL;
hssSound*     sfxExplosion            = NULL;
POINT					linesLeft[6][4];                 // First dimension is start point, second is end point
POINT					linesRight[6][3];                // First dimension is start point, second is end point
POINT					linesBottom[6][4];               // First dimension is start point, second is end point
POINT         ship_explosion_point[5];         // What location the explosion is at, if exploding
POINT         chairs;                          // Location of the crosshairs
RECT          ship_loc[5];                     // This is it's location
bool          laser_overheated        = false; // Flag: Is the laser overheated?
bool					sfxShipPlaying          = false;
bool          ship_explosion_cycle[5];         // True for explosion expansion, false for contraction
int						linesLeftDelay[6];		           // Delay counter
int						linesRightDelay[6];		           // Delay counter
int						linesBottomDelay[6];		         // Delay counter
int           ship_frame[5];                   // What animation frame it's on
int           ship_frame_delay[5];             // Delay between animation frame transition
int           ship_growth_delay[5];            // Delay between growth transitions
int           ship_growth_count[5];            // How much the ship has grown thus fatr
int           ship_movement[5];                // What direction the ship is moving in
int           ship_exploding[5];               // Flag; Is the ship exploding?
int           ship_explosion_step[5];          // What step of the explosion the ship is on, if exploding
int           laser_heat              = 0;              // Determines how hot the gun is (0-24)
int           cooldown_delay          = 0;     // Used to slow down the laser's cooldown cycle
int           laserhssChannel         = 0;
int           sfxShiphssChannel       = 0;


} // End of namespace


// ****************************************************************************************************************
// ProcessNextFrame handler
// ****************************************************************************************************************
void CGame::pnfTroubleInVectropolis(CGapiSurface* backbuffer) {

	using namespace ns_TroubleInVectropolis;

	if (!sfxShipPlaying) {
		sfxShipPlaying = true;
		sfxShiphssChannel = sndObj.playSound(sfxShip);
	}

	// First, draw the non-moving lines
	// Top diagonals
	backbuffer->DrawLine(xadj + 0,   yadj + 0,   xadj + 80,  yadj + 80,  RGB(255, 255, 255), NULL, NULL); // Left
	backbuffer->DrawLine(xadj + 120, yadj + 80,  xadj + 200, yadj + 0,   RGB(255, 255, 255), NULL, NULL); // Right
	// Bottom diagonals
	backbuffer->DrawLine(xadj + 0,   yadj + 200, xadj + 80,  yadj + 120, RGB(255, 255, 255), NULL, NULL); // Left
	backbuffer->DrawLine(xadj + 120, yadj + 120, xadj + 200, yadj + 200, RGB(255, 255, 255), NULL, NULL); // Right
	// Inner joiners (the U-shape)
	backbuffer->DrawLine(xadj + 80,  yadj + 80,  xadj + 80,  yadj + 120, RGB(255, 255, 255), NULL, NULL); // Left Top
	backbuffer->DrawLine(xadj + 120, yadj + 80,  xadj + 120, yadj + 120, RGB(255, 255, 255), NULL, NULL); // Left Bottom
	backbuffer->DrawLine(xadj + 80,  yadj + 120, xadj + 120, yadj + 120, RGB(255, 255, 255), NULL, NULL); // Bottom Left
	// Dimensional crossmembers
	backbuffer->DrawLine(xadj + 0,   yadj + 60,  xadj + 80,  yadj + 90,  RGB(255, 255, 255), NULL, NULL); // Left Top
	backbuffer->DrawLine(xadj + 0,   yadj + 140, xadj + 80,  yadj + 110, RGB(255, 255, 255), NULL, NULL); // Left Bottom
	backbuffer->DrawLine(xadj + 200, yadj + 60,  xadj + 120, yadj + 90,  RGB(255, 255, 255), NULL, NULL); // Right Top
	backbuffer->DrawLine(xadj + 200, yadj + 140, xadj + 120, yadj + 110, RGB(255, 255, 255), NULL, NULL); // Right Bottom
	backbuffer->DrawLine(xadj + 60,  yadj + 200, xadj + 90,  yadj + 120, RGB(255, 255, 255), NULL, NULL); // Bottom Left
	backbuffer->DrawLine(xadj + 140, yadj + 200, xadj + 110, yadj + 120, RGB(255, 255, 255), NULL, NULL); // Bottom Right

	// Now, draw the moving lines and move them, if it's time to
	// Now move our moving lines
	for (int i = 0; i < 4; i++) {
		// Draw the line
		backbuffer->DrawLine(xadj + linesLeft[i][0].x,   yadj + linesLeft[i][0].y,   xadj + linesLeft[i][1].x,   yadj + linesLeft[i][1].y,   RGB(255, 255, 255), NULL, NULL);
		backbuffer->DrawLine(xadj + linesRight[i][0].x,  yadj + linesRight[i][0].y,  xadj + linesRight[i][1].x,  yadj + linesRight[i][1].y,  RGB(255, 255, 255), NULL, NULL);
		backbuffer->DrawLine(xadj + linesBottom[i][0].x, yadj + linesBottom[i][0].y, xadj + linesBottom[i][1].x, yadj + linesBottom[i][1].y, RGB(255, 255, 255), NULL, NULL);
    // Lines on the left
    // If we're not at zero yet, continue the delay
		if (linesLeftDelay[i] > 0) {
			linesLeftDelay[i]--;
		} else {
			// Move the line's endpoints
			linesLeft[i][0].x = linesLeft[i][0].x - 2;
			linesLeft[i][0].y = linesLeft[i][0].y - 2;
			linesLeft[i][1].x = linesLeft[i][1].x - 2;
			linesLeft[i][1].y = linesLeft[i][1].y + 2;
			// Check if the line is at the edge
			if (linesLeft[i][0].x == 0 && linesLeft[i][0].y == 0) {
				// Reset delay and initial position
				linesLeftDelay[i] = 0;
				linesLeft[i][0].x	= 80; linesLeft[i][0].y	= 80;	linesLeft[i][1].x	= 80; linesLeft[i][1].y = 120;
			}
		}
    // Lines on the right
		// If we're not at zero yet, continue the delay
		if (linesRightDelay[i] > 0) {
			linesRightDelay[i]--;
		} else {
			// Move the line's endpoints
			linesRight[i][0].x = linesRight[i][0].x + 2;
			linesRight[i][0].y = linesRight[i][0].y - 2;
			linesRight[i][1].x = linesRight[i][1].x + 2;
			linesRight[i][1].y = linesRight[i][1].y + 2;
			// Check if the line is at the edge
			if (linesRight[i][0].x == 200 && linesRight[i][0].y == 0) {
				// Reset delay and initial position
				linesRightDelay[i] = 0;
				linesRight[i][0].x = 120; linesRight[i][0].y = 80; linesRight[i][1].x = 120; linesRight[i][1].y = 120;
			}
		}
    // Lines on the bottom
		// If we're not at zero yet, continue the delay
		if (linesBottomDelay[i] > 0) {
			linesBottomDelay[i]--;
		} else {
			// Move the line's endpoints
			linesBottom[i][0].x = linesBottom[i][0].x - 2;
			linesBottom[i][0].y = linesBottom[i][0].y + 2;
			linesBottom[i][1].x = linesBottom[i][1].x + 2;
			linesBottom[i][1].y = linesBottom[i][1].y + 2;
			// Check if the line is at the edge
			if (linesBottom[i][0].x == 0 && linesBottom[i][0].y == 200) {
				// Reset delay and initial position
				linesBottomDelay[i] = 0;
				linesBottom[i][0].x = 80; linesBottom[i][0].y = 120; linesBottom[i][1].x = 120; linesBottom[i][1].y = 120;
			}
		}
	} // End for

	// Draw the enemies
  for (i = 0; i < 3; i++) {
    if (ship_exploding[i]) {
      int r = rand() % 255; int g = rand() % 255; int b = rand() % 255;
      backbuffer->DrawLine(xadj + ship_explosion_point[i].x, yadj + ship_explosion_point[i].y, xadj + ship_explosion_point[i].x,                          yadj + ship_explosion_point[i].y - ship_explosion_step[i], RGB(r, g, b), NULL, NULL); // N
      backbuffer->DrawLine(xadj + ship_explosion_point[i].x, yadj + ship_explosion_point[i].y, xadj + ship_explosion_point[i].x,                          yadj + ship_explosion_point[i].y + ship_explosion_step[i], RGB(r, g, b), NULL, NULL); // S
      backbuffer->DrawLine(xadj + ship_explosion_point[i].x, yadj + ship_explosion_point[i].y, xadj + ship_explosion_point[i].x + ship_explosion_step[i], yadj + ship_explosion_point[i].y,                          RGB(r, g, b), NULL, NULL); // E
      backbuffer->DrawLine(xadj + ship_explosion_point[i].x, yadj + ship_explosion_point[i].y, xadj + ship_explosion_point[i].x - ship_explosion_step[i], yadj + ship_explosion_point[i].y,                          RGB(r, g, b), NULL, NULL); // W
      backbuffer->DrawLine(xadj + ship_explosion_point[i].x, yadj + ship_explosion_point[i].y, xadj + ship_explosion_point[i].x - ship_explosion_step[i], yadj + ship_explosion_point[i].y - ship_explosion_step[i], RGB(r, g, b), NULL, NULL); // NW
      backbuffer->DrawLine(xadj + ship_explosion_point[i].x, yadj + ship_explosion_point[i].y, xadj + ship_explosion_point[i].x + ship_explosion_step[i], yadj + ship_explosion_point[i].y - ship_explosion_step[i], RGB(r, g, b), NULL, NULL); // NE
      backbuffer->DrawLine(xadj + ship_explosion_point[i].x, yadj + ship_explosion_point[i].y, xadj + ship_explosion_point[i].x - ship_explosion_step[i], yadj + ship_explosion_point[i].y + ship_explosion_step[i], RGB(r, g, b), NULL, NULL); // SW
      backbuffer->DrawLine(xadj + ship_explosion_point[i].x, yadj + ship_explosion_point[i].y, xadj + ship_explosion_point[i].x + ship_explosion_step[i], yadj + ship_explosion_point[i].y + ship_explosion_step[i], RGB(r, g, b), NULL, NULL); // SE
      if (ship_explosion_cycle[i]) { // Expansion
        ship_explosion_step[i] = ship_explosion_step[i] + 3;
        if (ship_explosion_step[i] > 20) { ship_explosion_cycle[i] = false; }
      } else { // Contraction
        ship_explosion_step[i] = ship_explosion_step[i] - 3;
        if (ship_explosion_step[i] == 0) { positionShip(i); }
      }
    } else { // Ship NOT exploding
	    backbuffer->Blt(&ship_loc[i], ship[ship_frame[i]], NULL, GDBLTFAST_KEYSRC, NULL);
	    // Animate enemey
	    ship_frame_delay[i]++;
	    if (ship_frame_delay[i] > 2) {
		    ship_frame_delay[i] = 0;
		    ship_frame[i]++;
		    if (ship_frame[i] > 5) { ship_frame[i] = 0; }
	    }
	    // Move enemy
	    switch (ship_movement[i]) {
		    case smNorth:     { ship_loc[i].top--;  ship_loc[i].bottom--;                                         break; }
		    case smEast:      { ship_loc[i].left++; ship_loc[i].right++;                                          break; }
		    case smSouth:     { ship_loc[i].top++;  ship_loc[i].bottom++;                                         break; }
		    case smWest:      { ship_loc[i].left--; ship_loc[i].right--;                                          break; }
		    case smNorthEast: { ship_loc[i].left++; ship_loc[i].right++; ship_loc[i].top--; ship_loc[i].bottom--; break; }
		    case smSouthEast: { ship_loc[i].left++; ship_loc[i].right++; ship_loc[i].top++; ship_loc[i].bottom++; break; }
		    case smSouthWest: { ship_loc[i].left--; ship_loc[i].right--; ship_loc[i].top++; ship_loc[i].bottom++; break; }
		    case smNorthWest: { ship_loc[i].left--; ship_loc[i].right--; ship_loc[i].top--; ship_loc[i].bottom--; break; }
	    }
	    // Grow enemy
	    ship_growth_delay[i]++;
	    if (ship_growth_delay[i] > 1) {
		    ship_growth_delay[i] = 0;
		    ship_loc[i].left--;
		    ship_loc[i].top--;
		    ship_loc[i].right++;
		    ship_loc[i].bottom++;
	    }
	    ship_growth_count[i]++;
      if (ship_growth_count[i] > 100) { positionShip(i); subtractFromScore(40); } // This is when a ship gets passed the player
    }
  } // End for

  // Draw crosshairs and move them, if applicable
	if (laser_overheated) {
		backbuffer->BltFast(xadj + chairs.x, yadj + chairs.y, crosshairs_red, NULL, GDBLTFAST_KEYSRC, NULL);
	} else {
		backbuffer->BltFast(xadj + chairs.x, yadj + chairs.y, crosshairs_green, NULL, GDBLTFAST_KEYSRC, NULL);
	}
  if (player_dir_east)  { if (chairs.x < 170) { chairs.x = chairs.x + 4; } }
  if (player_dir_west)  { if (chairs.x > 10)  { chairs.x = chairs.x - 4; } }
  if (player_dir_north) { if (chairs.y > 10)  { chairs.y = chairs.y - 4; } }
  if (player_dir_south) { if (chairs.y < 170) { chairs.y = chairs.y + 4; } }

  // Draw lasers, if applicable, and check for collision with enemy, destroy if appropriate
  if (player_button_down && !laser_overheated) {
    int r = rand() % 255; int g = rand() % 255; int b = rand() % 255;
    backbuffer->DrawLine(xadj + 0,   yadj + 199, xadj + chairs.x + 10, yadj + chairs.y + 10,  RGB(r, g, b), NULL, NULL);
    backbuffer->DrawLine(xadj + 0,   yadj + 200, xadj + chairs.x + 10, yadj + chairs.y + 10,  RGB(r, g, b), NULL, NULL);
    backbuffer->DrawLine(xadj + 1,   yadj + 200, xadj + chairs.x + 10, yadj + chairs.y + 10,  RGB(r, g, b), NULL, NULL);
    backbuffer->DrawLine(xadj + 200, yadj + 199, xadj + chairs.x + 10, yadj + chairs.y + 10,  RGB(r, g, b), NULL, NULL);
    backbuffer->DrawLine(xadj + 200, yadj + 200, xadj + chairs.x + 10, yadj + chairs.y + 10,  RGB(r, g, b), NULL, NULL);
    backbuffer->DrawLine(xadj + 199, yadj + 200, xadj + chairs.x + 10, yadj + chairs.y + 10,  RGB(r, g, b), NULL, NULL);
    for (i = 0; i < 3; i++) {
      POINT p;
      p.x = chairs.x + 10; p.y = chairs.y + 10;
      if (!ship_exploding[i] && PtInRect(&ship_loc[i],  p)) { // Got it!
				sndObj.playSound(sfxExplosion);
        ship_exploding[i] = true;
        ship_explosion_cycle[i] = true;
        ship_explosion_step[i] = 0;
        ship_explosion_point[i].x = p.x; ship_explosion_point[i].y = p.y;
        addToScore(20);
      }
    }
  }

  // Draw outline of laser heat meter
  backbuffer->DrawRect(CRect(xadj + 63, yadj + 4, xadj + 137, yadj + 14), RGB(0, 0, 255), NULL, NULL);

  // Fill in the heat meter as appropriate
  if (laser_heat > 0) {
    int r;
    for (i = 0; i < laser_heat; i++) {
      r = 10 * i;
      backbuffer->FillRect(CRect(xadj + 64 + (3 * i), yadj + 5, xadj + 67 + (3 * i), yadj + 13), RGB(r, 100, 50), NULL, NULL);
    }
  }

  // Adjust laser heat
  if (player_button_down && !laser_overheated) {
    laser_heat = laser_heat + 2;
		if (laser_heat > 24) {
			sndObj.channel(laserhssChannel)->stop();
			laser_overheated = true;
			cooldown_delay = 0;
		}
  } else {
		cooldown_delay++;
		if (cooldown_delay > 3) {
			cooldown_delay = 0;
			if (laser_heat > 0) {
				laser_heat--;
			} else { // laser_heat is 0
				if (laser_overheated) { // If we were cooling down from an overheat, reset stuff
					laser_overheated = false;
					player_button_down = false;
				}
			}
		}
  }

}


// ****************************************************************************************************************
// KeyDown handler
// ****************************************************************************************************************
void CGame::kdTroubleInVectropolis(DWORD dwKey) {

	using namespace ns_TroubleInVectropolis;

  if (dwKey == kAction && !laser_overheated) {
    player_button_down = true;
		laserhssChannel = sndObj.playSound(sfxLaser);
  }

  if (dwKey == kUp) {
    player_dir_north = true;
  }

  if (dwKey == kDown) {
    player_dir_south = true;
  }

  if (dwKey == kLeft) {
    player_dir_west = true;
  }

  if (dwKey == kRight) {
    player_dir_east = true;
  }

}


// ****************************************************************************************************************
// KeyUp handler
// ****************************************************************************************************************
void CGame::kuTroubleInVectropolis(DWORD dwKey) {

	using namespace ns_TroubleInVectropolis;

	// Command button
	if (dwKey == kCommand) {
    hssChannel* c = sndObj.channel(sfxShiphssChannel);
	  if (c->playing()) { c->stop(); }
    sfxShipPlaying = false;
    miniGameCommandButtonHandler();
	}

  if (dwKey == kAction && !laser_overheated) {
    player_button_down = false;
		cooldown_delay = 0;
		sndObj.channel(laserhssChannel)->stop();
  }

  if (dwKey == kUp) {
    player_dir_north = false;
  }

  if (dwKey == kDown) {
    player_dir_south = false;
  }

  if (dwKey == kLeft) {
    player_dir_west = false;
  }

  if (dwKey == kRight) {
    player_dir_east = false;
  }

}


// ****************************************************************************************************************
// Initialize
// ****************************************************************************************************************
void CGame::initializeTroubleInVectropolis() {

	using namespace ns_TroubleInVectropolis;

	int i;
	// Initial position of the moving lines on the left
	for (i = 0; i < 4; i++) {
		linesLeft[i][0].x = 80; linesLeft[i][0].y = 80; linesLeft[i][1].x = 80; linesLeft[i][1].y = 120;
	}
		// Initial position of the moving lines on the right
	for (i = 0; i < 4; i++) {
		linesRight[i][0].x = 120; linesRight[i][0].y = 80;  linesRight[i][1].x = 120; linesRight[i][1].y = 120;
	}
	// Initial position of the moving lines on the bottom
	for (i = 0; i < 4; i++) {
		linesBottom[i][0].x = 80; linesBottom[i][0].y = 120; linesBottom[i][1].x = 120; linesBottom[i][1].y = 120;
	}
	// Set up delays so lines don't all come out at once
	linesLeftDelay[0]   = 0; linesLeftDelay[1]   = 10; linesLeftDelay[2]   = 20; linesLeftDelay[3]   = 30;
	linesRightDelay[0]  = 0; linesRightDelay[1]  = 10; linesRightDelay[2]  = 20; linesRightDelay[3]  = 30;
	linesBottomDelay[0] = 0; linesBottomDelay[1] = 10; linesBottomDelay[2] = 20; linesBottomDelay[3] = 30;

  laserhssChannel   = 0;
  sfxShiphssChannel = 0;

}


// ****************************************************************************************************************
// Ender
// ****************************************************************************************************************
void CGame::endTroubleInVectropolis() {

	using namespace ns_TroubleInVectropolis;

  hssChannel* c = sndObj.channel(sfxShiphssChannel);
	if (c->playing()) { c->stop(); }
  c = sndObj.channel(laserhssChannel);
	if (c->playing()) { c->stop(); }

}


// ****************************************************************************************************************
// Loader
// ****************************************************************************************************************
void CGame::loadTroubleInVectropolis(CGapiSurface* backbuffer) {

	using namespace ns_TroubleInVectropolis;

	processEvents = false;

	// Move on to the next step
	loading_step++;

	// Do the appropriate step
	switch(loading_step) {

		case 1: {
			doCommonInit();
      int i = 0;
      for (i = 0; i < 6; i++) { ship[i] = NULL; }
      crosshairs_red   = NULL;
      crosshairs_green = NULL;
      sfxShip          = NULL;
      sfxLaser         = NULL;
      sfxExplosion     = NULL;
		break; }

		case 2: {
			ship[0]          = new CGapiSurface(); createSurface(TEXT("trouble_in_vectropolis : GFX_TROUBLE_IN_LINE_WORLD_SHIP_00"),          ship[0]->CreateSurface         (0, m_config.hInstance, GFX_TROUBLE_IN_LINE_WORLD_SHIP_00,          TEXT("GRAPHICS"))); ship[0]->SetColorKey         (RGB(255, 128, 255));
			ship[1]          = new CGapiSurface(); createSurface(TEXT("trouble_in_vectropolis : GFX_TROUBLE_IN_LINE_WORLD_SHIP_01"),          ship[1]->CreateSurface         (0, m_config.hInstance, GFX_TROUBLE_IN_LINE_WORLD_SHIP_01,          TEXT("GRAPHICS"))); ship[1]->SetColorKey         (RGB(255, 128, 255));
			ship[2]          = new CGapiSurface(); createSurface(TEXT("trouble_in_vectropolis : GFX_TROUBLE_IN_LINE_WORLD_SHIP_02"),          ship[2]->CreateSurface         (0, m_config.hInstance, GFX_TROUBLE_IN_LINE_WORLD_SHIP_02,          TEXT("GRAPHICS"))); ship[2]->SetColorKey         (RGB(255, 128, 255));
			ship[3]          = new CGapiSurface(); createSurface(TEXT("trouble_in_vectropolis : GFX_TROUBLE_IN_LINE_WORLD_SHIP_03"),          ship[3]->CreateSurface         (0, m_config.hInstance, GFX_TROUBLE_IN_LINE_WORLD_SHIP_03,          TEXT("GRAPHICS"))); ship[3]->SetColorKey         (RGB(255, 128, 255));
			ship[4]          = new CGapiSurface(); createSurface(TEXT("trouble_in_vectropolis : GFX_TROUBLE_IN_LINE_WORLD_SHIP_04"),          ship[4]->CreateSurface         (0, m_config.hInstance, GFX_TROUBLE_IN_LINE_WORLD_SHIP_04,          TEXT("GRAPHICS"))); ship[4]->SetColorKey         (RGB(255, 128, 255));
			ship[5]          = new CGapiSurface(); createSurface(TEXT("trouble_in_vectropolis : GFX_TROUBLE_IN_LINE_WORLD_SHIP_05"),          ship[5]->CreateSurface         (0, m_config.hInstance, GFX_TROUBLE_IN_LINE_WORLD_SHIP_05,          TEXT("GRAPHICS"))); ship[5]->SetColorKey         (RGB(255, 128, 255));
			crosshairs_red   = new CGapiSurface(); createSurface(TEXT("trouble_in_vectropolis : GFX_TROUBLE_IN_LINE_WORLD_CROSSHAIRS_RED"),   crosshairs_red->CreateSurface  (0, m_config.hInstance, GFX_TROUBLE_IN_LINE_WORLD_CROSSHAIRS_RED,   TEXT("GRAPHICS"))); crosshairs_red->SetColorKey  (RGB(255, 128, 255));
			crosshairs_green = new CGapiSurface(); createSurface(TEXT("trouble_in_vectropolis : GFX_TROUBLE_IN_LINE_WORLD_CROSSHAIRS_GREEN"), crosshairs_green->CreateSurface(0, m_config.hInstance, GFX_TROUBLE_IN_LINE_WORLD_CROSSHAIRS_GREEN, TEXT("GRAPHICS"))); crosshairs_green->SetColorKey(RGB(255, 128, 255));
			sfxShip          = new hssSound();     loadSFX      (TEXT("trouble_in_vectropolis : SFX_SHIP"),                                   sfxShip->load                  (m_config.hInstance,    SFX_SHIP));                                                     sfxShip->loop                (true);
			sfxLaser         = new hssSound();     loadSFX      (TEXT("trouble_in_vectropolis : SFX_LASER"),                                  sfxLaser->load                 (m_config.hInstance,    SFX_LASER));                                                    sfxLaser->loop               (true);
			sfxExplosion     = new hssSound();     loadSFX      (TEXT("trouble_in_vectropolis : SFX_EXPLOSION"),                              sfxExplosion->load             (m_config.hInstance,    SFX_EXPLOSION));                                                sfxExplosion->loop           (false);
		break; }

    case 3: {
			initializeTroubleInVectropolis();
      for (int i = 0; i < 30; i++) { _tcscpy(mgInstructions[i], instructions[i]); } mgInstructionsPage = 0; mgiPrevTapped = false; mgiNextTapped = false;
      chairs.x = 80;
      chairs.y = 80;
      laser_heat = 0;
			cooldown_delay = 0;
			laser_overheated = false;
			sfxShipPlaying = false;
      positionShip(0);
      positionShip(1);
      positionShip(2);
    break; }

		// End of loading
		default: {
			loading	= false;
			loading_step = 0;
			processEvents = true;
		break; }

	}

	// Show the Loading screen
	showLoadingScreen(backbuffer, true, true);

}


// ****************************************************************************************************************
// Destroyer
// ****************************************************************************************************************
void CGame::destroyTroubleInVectropolis(CGapiSurface* backbuffer) {

	using namespace ns_TroubleInVectropolis;

	processEvents = false;

	// Move on to the next step
	destroying_step++;

	// Do the appropriate step
	switch(destroying_step) {

		case 1: {
			doCommonCleanup();
		break; }

		case 2: {
			delete sfxExplosion;
			delete sfxShip;
			delete sfxLaser;
			delete ship[0];
			delete ship[1];
			delete ship[2];
			delete ship[3];
			delete ship[4];
			delete ship[5];
      delete crosshairs_red;
			delete crosshairs_green;
		break; }

		default: {
			// All done destroying, start loading the next screen
      if (screen_after_destroy == csNewGameType) { // If we just finished playing mini-game melee mode, we need to do some special tricks to get back there... first, re-load the menu stuff, then set our special flag so that loader knows to go to the new game type screen instead
        screen_after_destroy = csMainMenu;
        jumpBackToNewGameType = true;
      }
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
namespace ns_TroubleInVectropolis {


	void positionShip(int index) {
		ship_loc[index].left = xadj + (rand() % 40) + 80;
		ship_loc[index].top = yadj + (rand() % 40) + 80;
		ship_loc[index].right = ship_loc[index].left;
		ship_loc[index].bottom = ship_loc[index].top;
		ship_frame[index] = rand() % 5;
		ship_frame_delay[index] = 0;
		ship_growth_delay[index] = 0;
		ship_growth_count[index] = 0;
		ship_movement[index] = rand() % 8;
    ship_exploding[index] = false;
	}


} // End of namespace
