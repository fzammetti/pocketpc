
#include "../main.h"


namespace ns_Squishem {


// ****************************************************************************************************************
// Defines specific to this mini-game
// ****************************************************************************************************************
#define asHidden    0
#define asPoppingUp 1
#define asDancing   3
#define asGoingDown 4
#define asSquished  5
#define fdNorth     10
#define fdEast      11
#define fdSouth     12
#define fdWest      13


// ****************************************************************************************************************
// Function prototypes specific to this mini-game
// ****************************************************************************************************************
void setupPath();
void determineGunDir(bool player_dir_north, bool player_dir_east, bool player_dir_south, bool player_dir_west);
void checkDirChange();


// ****************************************************************************************************************
// Globals specific to this mini-game
// ****************************************************************************************************************
TCHAR	instructions[][32] = { TEXT("Squish'em"),
														 TEXT(""),
														 TEXT("As you fly through space,"),
														 TEXT("subspace vortices"),
														 TEXT("appear, circling in front"),
														 TEXT("of your ship.  From them"),
														 TEXT("emerge nasty little alien"),
														 TEXT("dudes.  Fortunately, you"),
														 TEXT("are armed with your"),
														 TEXT("special squish'em ray!"),
                             //    ---------------------------
                             TEXT("The Goal"),
														 TEXT(""),
														 TEXT("Squish as many invading"),
														 TEXT("aliens as you can before"),
														 TEXT("time runs out.  Any you"),
														 TEXT("miss will cost you points."),
														 TEXT(""),
														 TEXT(""),
														 TEXT(""),
														 TEXT(""),
                             //    ---------------------------
                             TEXT("How To Play"),
														 TEXT(""),
														 TEXT("Press the ACTION button"),
														 TEXT("to switch between"),
														 TEXT("groups of subspace"),
														 TEXT("vertices, then press up,"),
														 TEXT("down, left or right to"),
														 TEXT("fire your ray in the"),
														 TEXT("corresponding direction,"),
														 TEXT("to squish an alien."),
                             //    ----------------------------
};

CGapiSurface* alienImages[8];               // The images of the aliens
CGapiSurface* rayV[4];                      // The squish'em ray (Vertical)
CGapiSurface* rayH[4];                      // The squish'em ray (Horizontal)
CGapiSurface* gun                   = NULL; // The gun
hssSound*     sfxAlienPopup         = NULL;
hssSound*     sfxLaser              = NULL;
hssSound*     sfxSquish             = NULL;
hssSound*     sfxSwitchGroups       = NULL;
POINT         circPnts[344];                // Array of points defining the path around the circle
int           circIndx1             = 0;    // Index into above array for first group
int           circIndx2             = 0;    // Index into above array for second group
int           gun_group             = 0;    // What group the gun is in
int           facing_dir            = 0;    // What direction the gun is facing
int           ray_frame             = 0;    // What frame the ray is on
int           ray_frame_delay       = 0;    // Delay for ray frame swapping
int           rotDir                = 0;    // Direction of rotation
int           rotDirChangeCount     = 0;    // Counter to tell when to change directions
int           laser_channel         = -1;
int           alienStates[10];               // What state each alien is in
int           alienDelays[10];               // Delay used throughout alien animation sequence
int           alienFrames[10];               // What frame each alien is on
int           alienDancingDelays[10];        // Delay between dancing frames
float         stars[204][9];                // 3-D starfield stars


} // End of namespace


// ****************************************************************************************************************
// ProcessNextFrame handler
// ****************************************************************************************************************
void CGame::pnfSquishem(CGapiSurface* backbuffer) {

	using namespace ns_Squishem;

	// Draw the stars in their new positions
	for (int j = 1; j < 195; j++) {
    backbuffer->SetPixel(xadj + (unsigned short int)stars[j][3], (unsigned short int)stars[j][4], RGB(255, 255, 255));
		backbuffer->SetPixel(xadj + (unsigned short int)stars[j][3] + 1, (unsigned short int)stars[j][4], RGB(255, 255, 255));
		backbuffer->SetPixel(xadj + (unsigned short int)stars[j][3], (unsigned short int)stars[j][4] + 1, RGB(255, 255, 255));
		backbuffer->SetPixel(xadj + (unsigned short int)stars[j][3] + 1, (unsigned short int)stars[j][4] + 1, RGB(255, 255, 255));
	}

  // First group
  backbuffer->BltFast(xadj + (circPnts[circIndx1].x - 12), yadj + (circPnts[circIndx1].y - 40), alienImages[alienFrames[0]], NULL, GDBLTFAST_KEYSRC, NULL); // Top
  backbuffer->BltFast(xadj + (circPnts[circIndx1].x - 12), yadj + (circPnts[circIndx1].y + 16), alienImages[alienFrames[1]], NULL, GDBLTFAST_KEYSRC, NULL); // Bottom
  backbuffer->BltFast(xadj + (circPnts[circIndx1].x - 40), yadj + (circPnts[circIndx1].y - 12), alienImages[alienFrames[2]], NULL, GDBLTFAST_KEYSRC, NULL); // Left
  backbuffer->BltFast(xadj + (circPnts[circIndx1].x + 16), yadj + (circPnts[circIndx1].y - 12), alienImages[alienFrames[3]], NULL, GDBLTFAST_KEYSRC, NULL); // Right

  // Second group
  backbuffer->BltFast(xadj + (circPnts[circIndx2].x - 12), yadj + (circPnts[circIndx2].y - 40), alienImages[alienFrames[4]], NULL, GDBLTFAST_KEYSRC, NULL); // Top
  backbuffer->BltFast(xadj + (circPnts[circIndx2].x - 12), yadj + (circPnts[circIndx2].y + 16), alienImages[alienFrames[5]], NULL, GDBLTFAST_KEYSRC, NULL); // Bottom
  backbuffer->BltFast(xadj + (circPnts[circIndx2].x - 40), yadj + (circPnts[circIndx2].y - 12), alienImages[alienFrames[6]], NULL, GDBLTFAST_KEYSRC, NULL); // Left
  backbuffer->BltFast(xadj + (circPnts[circIndx2].x + 16), yadj + (circPnts[circIndx2].y - 12), alienImages[alienFrames[7]], NULL, GDBLTFAST_KEYSRC, NULL); // Right

  // Blit Gun and ray (if applicable), and see if we need to alter an alien
  int pathIndx; if (gun_group == 1) { pathIndx = circIndx1; } else { pathIndx = circIndx2; }
  RECT rect; GDBLTFX gdbltfx;
	SetRect(&rect, xadj + (circPnts[pathIndx].x - 12), (circPnts[pathIndx].y - 2), xadj + (circPnts[pathIndx].x + 12), yadj + (circPnts[pathIndx].y + 22));
  if (facing_dir == fdNorth) { // Facing north
    gdbltfx.nRotationAngle = 27000; backbuffer->Blt(&rect, gun, NULL, GDBLT_KEYSRC | GDBLT_ROTATIONANGLE, &gdbltfx);
    if (player_dir_north) { // Firing in this direction
      backbuffer->BltFast(xadj + rect.left - 10, yadj + rect.top - 16, rayV[ray_frame], NULL, GDBLTFAST_KEYSRC, NULL);
      // If we're in group 1 AND there is an alien above us that is NOT hidden or squished, squish'em
      if (gun_group == 1 && alienStates[0] != asHidden && alienStates[0] != asSquished) {
        sndObj.playSound(sfxSquish);
        alienStates[0] = asSquished; alienFrames[0] = 5; alienDelays[0] = 24; addToScore(10); checkDirChange();
      }
      // If we're in group 2 AND there is an alien above us that is NOT hidden or squished, squish'em
      if (gun_group == 2 && alienStates[4] != asHidden && alienStates[4] != asSquished) {
        sndObj.playSound(sfxSquish);
        alienStates[4] = asSquished; alienFrames[4] = 5; alienDelays[4] = 24; addToScore(10); checkDirChange();
      }
    }
  }
  if (facing_dir == fdEast)  { // Facing east
    gdbltfx.nRotationAngle = 0; backbuffer->Blt(&rect, gun, NULL, GDBLT_KEYSRC | GDBLT_ROTATIONANGLE, &gdbltfx);
    if (player_dir_east) { // Firing in this direction
      backbuffer->BltFast(xadj + rect.left, yadj + rect.top, rayH[ray_frame], NULL, GDBLTFAST_KEYSRC, NULL);
      // If we're in group 1 AND there is an alien to the right of us that is NOT hidden or squished, squish'em
      if (gun_group == 1 && alienStates[3] != asHidden && alienStates[3] != asSquished) {
        sndObj.playSound(sfxSquish);
        alienStates[3] = asSquished; alienFrames[3] = 5; alienDelays[3] = 24; addToScore(10);  checkDirChange();
      }
      // If we're in group 2 AND there is an alien to the right of us that is NOT hidden or squished, squish'em
      if (gun_group == 2 && alienStates[7] != asHidden && alienStates[7] != asSquished) {
        sndObj.playSound(sfxSquish);
        alienStates[7] = asSquished; alienFrames[7] = 5; alienDelays[7] = 24; addToScore(10);  checkDirChange();
      }
    }
  }
  if (facing_dir == fdSouth) { // Facing south
    gdbltfx.nRotationAngle = 9000;  backbuffer->Blt(&rect, gun, NULL, GDBLT_KEYSRC | GDBLT_ROTATIONANGLE, &gdbltfx);
    if (player_dir_south) { // Firing in this direction
      backbuffer->BltFast(xadj + rect.left - 10, yadj + rect.top + 10, rayV[ray_frame], NULL, GDBLTFAST_KEYSRC, NULL);
      // If we're in group 1 AND there is an alien below us that is NOT hidden or squished, squish'em
      if (gun_group == 1 && alienStates[1] != asHidden && alienStates[1] != asSquished) {
        sndObj.playSound(sfxSquish);
        alienStates[1] = asSquished; alienFrames[1] = 5; alienDelays[1] = 24; addToScore(10);  checkDirChange();
      }
      // If we're in group 2 AND there is an alien below us that is NOT hidden or squished, squish'em
      if (gun_group == 2 && alienStates[5] != asHidden && alienStates[5] != asSquished) {
        sndObj.playSound(sfxSquish);
        alienStates[5] = asSquished; alienFrames[5] = 5; alienDelays[5] = 24; addToScore(10);  checkDirChange();
      }
    }
  }
  if (facing_dir == fdWest)  { // Facing west
    gdbltfx.nRotationAngle = 18000; backbuffer->Blt(&rect, gun, NULL, GDBLT_KEYSRC | GDBLT_ROTATIONANGLE, &gdbltfx);
    if (player_dir_west) { // Firing in this direction
      backbuffer->BltFast(xadj + rect.left - 26, yadj + rect.top, rayH[ray_frame], NULL, GDBLTFAST_KEYSRC, NULL);
      // If we're in group 1 AND there is an alien to the left of us that is NOT hidden or squished, squish'em
      if (gun_group == 1 && alienStates[2] != asHidden && alienStates[2] != asSquished) {
        sndObj.playSound(sfxSquish);
        alienStates[2] = asSquished; alienFrames[2] = 5; alienDelays[2] = 24; addToScore(10);  checkDirChange();
      }
      // If we're in group 2 AND there is an alien to the left of us that is NOT hidden or squished, squish'em
      if (gun_group == 2 && alienStates[6] != asHidden && alienStates[6] != asSquished) {
        sndObj.playSound(sfxSquish);
        alienStates[6] = asSquished; alienFrames[6] = 5; alienDelays[6] = 24; addToScore(10);  checkDirChange();
      }
    }
  }

  // Update ray animation
  ray_frame_delay++;
  if (ray_frame_delay > 1) {
    ray_frame_delay = 0;
    if (ray_frame == 0) { ray_frame = 1; } else { ray_frame = 0; }
  }

  // Move the groups along
	if (rotDir == 1) {
		circIndx1 = circIndx1 + 2; if (circIndx1 > 341) { circIndx1 = 1; }
		circIndx2 = circIndx2 + 2; if (circIndx2 > 341) { circIndx2 = 1; }
	} else {
		circIndx1 = circIndx1 - 2; if (circIndx1 < 1) { circIndx1 = 341; }
		circIndx2 = circIndx2 - 2; if (circIndx2 < 1) { circIndx2 = 341; }
	}

  // Update aliens
  for (int i = 0; i < 8; i++) {
    alienDelays[i]--;
    switch (alienStates[i]) {
      // If we're hidden...
      case asHidden: {
        // See if it's time to pop up
        if (alienDelays[i] < 0) {
          // If is time to pop up!
          sndObj.playSound(sfxAlienPopup);
          alienStates[i] = asPoppingUp;
          alienFrames[i]++;
          alienDelays[i] = 2;
        }
      break; }
        // If we're poppingu p...
      case asPoppingUp: {
        // See if it's time to change frames
        if (alienDelays[i] < 0) {
          // It is time to change frames!
          alienFrames[i]++;
          // If we're now really displaying the first dancing frame, change states
          if (alienFrames[i] > 2) {
            alienStates[i] = asDancing;
            alienDelays[i] = 48;
            alienDancingDelays[i] = 2;
          // No, we're now displaying the second popup frame, so reset the delay
          } else {
            alienDelays[i] = 2;
          }
        }
      break; }
      // If we're dancing...
      case asDancing: {
        // See if it's time to go down
        if (alienDelays[i] < 0) {
          alienStates[i] = asGoingDown;
        // No, it's NOT time to go down...
        } else {
          // Only swap if the delay between dancing frames is up
          alienDancingDelays[i]--;
          if (alienDancingDelays[i] < 0) {
            alienDancingDelays[i] = 2;
            // Swap frames
            if (alienFrames[i] == 3) {
              alienFrames[i] = 4;
            } else {
              alienFrames[i] = 3;
            }
          }
        }
      break; }
      // If we're going down...
      case asGoingDown: {
        // See if it's time to change frames
        if (alienDelays[i] < 0) {
          alienFrames[i]--;
          // If we're now reallyu displaying the hidding frame, change states
          if (alienFrames[i] < 1) {
            alienStates[i] = asHidden;
            alienDelays[i] = rand() % 120;
            subtractFromScore(5);
          // No, we're displaying the second going down frame, so reset the delay
          } else {
            alienDelays[i] = 2;
          }
        }
      break; }
      // If we're squished...
      case asSquished: {
        // See if we've been squished a while
        if (alienDelays[i] < 0) {
          // Yep, been squished a while, so reset for the next time
          alienFrames[i] = 0;
          alienStates[i] = asHidden;
          alienDelays[i] = rand() % 120;
        }
      break; }
    }
  }

	// Move the stars
	for (int k = 1; k < 195; k++) {
		stars[k][2] -= 3;
		if (stars[k][2] <= 0) {  // Re-initialize if star is too close
			stars[k][0] = (float)(rand() % 70 - 35);
			stars[k][1] = (float)(rand() % 70 - 35);
			stars[k][2] = (float)(rand() % 100 + 1);
		}
		stars[k][3] = (stars[k][0] / stars[k][2]) * 200 + (200 >> 1);
		stars[k][4] = (stars[k][1] / stars[k][2]) * 200 + (200 >> 1);
	}

}


// ****************************************************************************************************************
// KeyDown handler
// ****************************************************************************************************************
void CGame::kdSquishem(DWORD dwKey) {

	using namespace ns_Squishem;

	// Action button
	if (dwKey == kAction && !player_dir_north && !player_dir_south && !player_dir_east && !player_dir_west) {
    sndObj.playSound(sfxSwitchGroups);
    player_button_down = true;
    if (gun_group == 1) {
      gun_group = 2;
    } else {
      gun_group = 1;
    }
	}

  if (dwKey == kUp || dwKey == kDown || dwKey == kLeft || dwKey == kRight) {
    if (laser_channel == -1) {
	    laser_channel = sndObj.playSound(sfxLaser);
    }
  }

	// Handle up movement events
	if (dwKey == kUp) {
		player_dir_north	= true;
    determineGunDir(player_dir_north, player_dir_east, player_dir_south, player_dir_west);
	}

	// Handle down movement events
	if (dwKey == kDown) {
		player_dir_south	= true;
    determineGunDir(player_dir_north, player_dir_east, player_dir_south, player_dir_west);
	}

	// Handle left movement events
	if (dwKey == kLeft) {
		player_dir_west	= true;
    determineGunDir(player_dir_north, player_dir_east, player_dir_south, player_dir_west);
	}

	// Handle right movement events
	if (dwKey == kRight) {
		player_dir_east	= true;
    determineGunDir(player_dir_north, player_dir_east, player_dir_south, player_dir_west);
	}

}


// ****************************************************************************************************************
// KeyUp handler
// ****************************************************************************************************************
void CGame::kuSquishem(DWORD dwKey) {

	using namespace ns_Squishem;

	// Command button
	if (dwKey == kCommand) {
    miniGameCommandButtonHandler();
	}

	// Action button
	if (dwKey == kAction) {
    player_button_down = false;
	}

  if (dwKey == kUp || dwKey == kDown || dwKey == kLeft || dwKey == kRight) {
    if (laser_channel != -1) {
      hssChannel* lc = sndObj.channel(laser_channel);
		  lc->stop();
      laser_channel = -1;
    }
  }

	// Handle up movement events
	if (dwKey == kUp) {
		player_dir_north	= false;
	}

	// Handle down movement events
	if (dwKey == kDown) {
		player_dir_south	= false;
	}

	// Handle left movement events
	if (dwKey == kLeft) {
		player_dir_west	= false;
	}

	// Handle right movement events
	if (dwKey == kRight) {
		player_dir_east	= false;
	}

}


// ****************************************************************************************************************
// Initialize
// ****************************************************************************************************************
void CGame::initializeSquishem() {

	using namespace ns_Squishem;

  // Setup the path array elements
  setupPath();

  // Setup the starting positions for each group within our path
  circIndx1 = 1;
  circIndx2 = 171;

  gun_group = 1;
  facing_dir = fdEast;
  ray_frame = 0;
  ray_frame_delay = 0;
	rotDir = 1;
	rotDirChangeCount = 0;

  // Initialize our aliens
  alienStates[0] = asHidden;
  alienStates[1] = asHidden;
  alienStates[2] = asHidden;
  alienStates[3] = asHidden;
  alienStates[4] = asHidden;
  alienStates[5] = asHidden;
  alienDelays[0] = rand() % 120;
  alienDelays[1] = rand() % 120;
  alienDelays[2] = rand() % 120;
  alienDelays[3] = rand() % 120;
  alienDelays[4] = rand() % 120;
  alienDelays[5] = rand() % 120;
  alienFrames[0] = 0;
  alienFrames[1] = 0;
  alienFrames[2] = 0;
  alienFrames[3] = 0;
  alienFrames[4] = 0;
  alienFrames[5] = 0;
  alienDancingDelays[0] = 0;
  alienDancingDelays[1] = 0;
  alienDancingDelays[2] = 0;
  alienDancingDelays[3] = 0;
  alienDancingDelays[4] = 0;
  alienDancingDelays[5] = 0;

  // Initialize stars for 3-D starfield
  for (int i = 1; i < 195; i++) {
	  stars[i][0] = (float)(rand() % 70 - 35);
	  stars[i][1] = (float)(rand() % 70 - 35);
	  stars[i][2] = (float)(rand() % 100 + 1);
  }

  laser_channel = -1;

}


// ****************************************************************************************************************
// Loader
// ****************************************************************************************************************
void CGame::loadSquishem(CGapiSurface* backbuffer) {

	using namespace ns_Squishem;

	processEvents = false;

	// Move on to the next step
	loading_step++;

	// Do the appropriate step
	switch(loading_step) {

		case 1: {
			doCommonInit();
      int i = 0;
      for (i = 0; i < 6; i++) { alienImages[i] = NULL; }
      for (i = 0; i < 2; i++) { rayV[2] = NULL; }
      for (i = 0; i < 2; i++) { rayH[2] = NULL; }
      gun             = NULL;
      sfxAlienPopup   = NULL;
      sfxLaser        = NULL;
      sfxSquish       = NULL;
      sfxSwitchGroups = NULL;
		break; }

    case 2: {
			alienImages[0]  = new CGapiSurface(); createSurface(TEXT("squishem : GFX_SQUISHEM_ALIEN_00"),      alienImages[0]->CreateSurface(0, m_config.hInstance, GFX_SQUISHEM_ALIEN_00,  TEXT("GRAPHICS"))); alienImages[0]->SetColorKey(RGB(255, 128, 255));
			alienImages[1]  = new CGapiSurface(); createSurface(TEXT("squishem : GFX_SQUISHEM_ALIEN_01"),      alienImages[1]->CreateSurface(0, m_config.hInstance, GFX_SQUISHEM_ALIEN_01,  TEXT("GRAPHICS"))); alienImages[1]->SetColorKey(RGB(255, 128, 255));
			alienImages[2]  = new CGapiSurface(); createSurface(TEXT("squishem : GFX_SQUISHEM_ALIEN_02"),      alienImages[2]->CreateSurface(0, m_config.hInstance, GFX_SQUISHEM_ALIEN_02,  TEXT("GRAPHICS"))); alienImages[2]->SetColorKey(RGB(255, 128, 255));
			alienImages[3]  = new CGapiSurface(); createSurface(TEXT("squishem : GFX_SQUISHEM_ALIEN_03"),      alienImages[3]->CreateSurface(0, m_config.hInstance, GFX_SQUISHEM_ALIEN_03,  TEXT("GRAPHICS"))); alienImages[3]->SetColorKey(RGB(255, 128, 255));
			alienImages[4]  = new CGapiSurface(); createSurface(TEXT("squishem : GFX_SQUISHEM_ALIEN_04"),      alienImages[4]->CreateSurface(0, m_config.hInstance, GFX_SQUISHEM_ALIEN_04,  TEXT("GRAPHICS"))); alienImages[4]->SetColorKey(RGB(255, 128, 255));
			alienImages[5]  = new CGapiSurface(); createSurface(TEXT("squishem : GFX_SQUISHEM_ALIEN_05"),      alienImages[5]->CreateSurface(0, m_config.hInstance, GFX_SQUISHEM_ALIEN_05,  TEXT("GRAPHICS"))); alienImages[5]->SetColorKey(RGB(255, 128, 255));
			gun             = new CGapiSurface(); createSurface(TEXT("squishem : GFX_ANTIGRAVITATOR_GUN"),     gun->CreateSurface           (0, m_config.hInstance, GFX_ANTIGRAVITATOR_GUN, TEXT("GRAPHICS"))); gun->SetColorKey           (RGB(255, 128, 255));
			rayH[0]         = new CGapiSurface(); createSurface(TEXT("squishem : GFX_SQUISHEM_RAYH_00"),       rayH[0]->CreateSurface       (0, m_config.hInstance, GFX_SQUISHEM_RAYH_00,   TEXT("GRAPHICS"))); rayH[0]->SetColorKey       (RGB(255, 128, 255));
			rayH[1]         = new CGapiSurface(); createSurface(TEXT("squishem : GFX_SQUISHEM_RAYH_01"),       rayH[1]->CreateSurface       (0, m_config.hInstance, GFX_SQUISHEM_RAYH_01,   TEXT("GRAPHICS"))); rayH[1]->SetColorKey       (RGB(255, 128, 255));
			rayV[0]         = new CGapiSurface(); createSurface(TEXT("squishem : GFX_SQUISHEM_RAYV_00"),       rayV[0]->CreateSurface       (0, m_config.hInstance, GFX_SQUISHEM_RAYV_00,   TEXT("GRAPHICS"))); rayV[0]->SetColorKey       (RGB(255, 128, 255));
			rayV[1]         = new CGapiSurface(); createSurface(TEXT("squishem : GFX_SQUISHEM_RAYV_01"),       rayV[1]->CreateSurface       (0, m_config.hInstance, GFX_SQUISHEM_RAYV_01,   TEXT("GRAPHICS"))); rayV[1]->SetColorKey       (RGB(255, 128, 255));
			sfxAlienPopup   = new hssSound();      loadSFX      (TEXT("squishem : SFX_SQUISHEM_ALIEN_POPUP"),   sfxAlienPopup->load          (m_config.hInstance,    SFX_SQUISHEM_ALIEN_POPUP));                 sfxAlienPopup->loop        (false);
			sfxSquish       = new hssSound();      loadSFX      (TEXT("squishem : SFX_SQUISHEM_SQUISH"),        sfxSquish->load              (m_config.hInstance,    SFX_SQUISHEM_SQUISH));                      sfxSquish->loop            (false);
			sfxLaser        = new hssSound();      loadSFX      (TEXT("squishem : SFX_SQUISHEM_LASER"),         sfxLaser->load               (m_config.hInstance,    SFX_SQUISHEM_LASER));                       sfxLaser->loop             (true);
			sfxSwitchGroups = new hssSound();      loadSFX      (TEXT("squishem : SFX_SQUISHEM_SWITCH_GROUPS"), sfxSwitchGroups->load        (m_config.hInstance,    SFX_SQUISHEM_SWITCH_GROUPS));               sfxSwitchGroups->loop      (false);
      break; }

		case 3: {
			initializeSquishem();
      for (int i = 0; i < 30; i++) { _tcscpy(mgInstructions[i], instructions[i]); } mgInstructionsPage = 0; mgiPrevTapped = false; mgiNextTapped = false;
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
void CGame::destroySquishem(CGapiSurface* backbuffer) {

	using namespace ns_Squishem;

	processEvents = false;

	// Move on to the next step
	destroying_step++;

	// Do the appropriate step
	switch(destroying_step) {

		case 1: {
			doCommonCleanup();
		break; }

    case 2: {
      delete alienImages[0];
      delete alienImages[1];
      delete alienImages[2];
      delete alienImages[3];
      delete alienImages[4];
      delete alienImages[5];
      delete gun;
      delete rayH[0];
      delete rayH[1];
      delete rayV[0];
      delete rayV[1];
      delete sfxAlienPopup;
      delete sfxLaser;
      delete sfxSquish;
      delete sfxSwitchGroups;
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
namespace ns_Squishem {

  void determineGunDir(bool player_dir_north, bool player_dir_east, bool player_dir_south, bool player_dir_west) {

	  if (player_dir_north && !player_dir_south && !player_dir_east && !player_dir_west) { // North
      facing_dir = fdNorth;
	  }
	  if (!player_dir_north && player_dir_south && !player_dir_east && !player_dir_west) { // South
      facing_dir = fdSouth;
	  }
	  if (!player_dir_north && !player_dir_south && player_dir_east && !player_dir_west) { // East
      facing_dir = fdEast;
	  }
	  if (!player_dir_north && !player_dir_south && !player_dir_east && player_dir_west) { // West
      facing_dir = fdWest;
	  }

  }


	void checkDirChange() {

		rotDirChangeCount++;
		if (rotDirChangeCount > 10) {
			rotDirChangeCount = 0;
			if (rotDir == 1) {
				rotDir = 2;
			} else {
				rotDir = 1;
			}
		}

	}


  void setupPath() {

    circPnts[1].x = 100; circPnts[1].y = 44; // Top Midpoint
    circPnts[2].x = 101; circPnts[2].y = 44;
    circPnts[3].x = 102; circPnts[3].y = 44;
    circPnts[4].x = 103; circPnts[4].y = 44;
    circPnts[5].x = 104; circPnts[5].y = 44;
    circPnts[6].x = 105; circPnts[6].y = 44;
    circPnts[7].x = 106; circPnts[7].y = 44;
    circPnts[8].x = 107; circPnts[8].y = 44;
    circPnts[9].x = 108; circPnts[9].y = 44;
    circPnts[10].x = 109; circPnts[10].y = 44;
    circPnts[11].x = 110; circPnts[11].y = 44;
    circPnts[12].x = 111; circPnts[12].y = 44;
    circPnts[13].x = 112; circPnts[13].y = 44;
    circPnts[14].x = 113; circPnts[14].y = 44;
    circPnts[15].x = 114; circPnts[15].y = 44;
    circPnts[16].x = 115; circPnts[16].y = 44;
    circPnts[17].x = 116; circPnts[17].y = 44;
    circPnts[18].x = 117; circPnts[18].y = 45;
    circPnts[19].x = 118; circPnts[19].y = 45;
    circPnts[20].x = 119; circPnts[20].y = 45;
    circPnts[21].x = 120; circPnts[21].y = 45;
    circPnts[22].x = 121; circPnts[22].y = 45;
    circPnts[23].x = 122; circPnts[23].y = 45;
    circPnts[24].x = 123; circPnts[24].y = 46;
    circPnts[25].x = 124; circPnts[25].y = 46;
    circPnts[26].x = 125; circPnts[26].y = 46;
    circPnts[27].x = 126; circPnts[27].y = 47;
    circPnts[28].x = 127; circPnts[28].y = 47;
    circPnts[29].x = 128; circPnts[29].y = 48;
    circPnts[30].x = 129; circPnts[30].y = 48;
    circPnts[31].x = 130; circPnts[31].y = 49;
    circPnts[32].x = 131; circPnts[32].y = 49;
    circPnts[33].x = 132; circPnts[33].y = 49;
    circPnts[34].x = 133; circPnts[34].y = 50;
    circPnts[35].x = 134; circPnts[35].y = 51;
    circPnts[36].x = 135; circPnts[36].y = 51;
    circPnts[37].x = 136; circPnts[37].y = 52;
    circPnts[38].x = 137; circPnts[38].y = 53;
    circPnts[39].x = 138; circPnts[39].y = 53;
    circPnts[40].x = 139; circPnts[40].y = 54;
    circPnts[41].x = 140; circPnts[41].y = 55;
    circPnts[42].x = 141; circPnts[42].y = 56;
    circPnts[43].x = 142; circPnts[43].y = 57;
    circPnts[44].x = 143; circPnts[44].y = 58;
    circPnts[45].x = 144; circPnts[45].y = 59;
    circPnts[46].x = 145; circPnts[46].y = 60;
    circPnts[47].x = 146; circPnts[47].y = 61;
    circPnts[48].x = 146; circPnts[48].y = 62;
    circPnts[49].x = 146; circPnts[49].y = 63;
    circPnts[50].x = 147; circPnts[50].y = 64;
    circPnts[51].x = 148; circPnts[51].y = 65;
    circPnts[52].x = 149; circPnts[52].y = 66;
    circPnts[53].x = 150; circPnts[53].y = 67;
    circPnts[54].x = 150; circPnts[54].y = 67;
    circPnts[55].x = 150; circPnts[55].y = 68;
    circPnts[56].x = 150; circPnts[56].y = 69;
    circPnts[57].x = 151; circPnts[57].y = 70;
    circPnts[58].x = 151; circPnts[58].y = 71;
    circPnts[59].x = 152; circPnts[59].y = 72;
    circPnts[60].x = 152; circPnts[60].y = 73;
    circPnts[61].x = 153; circPnts[61].y = 74;
    circPnts[62].x = 153; circPnts[62].y = 75;
    circPnts[63].x = 153; circPnts[63].y = 76;
    circPnts[64].x = 154; circPnts[64].y = 77;
    circPnts[65].x = 154; circPnts[65].y = 78;
    circPnts[66].x = 154; circPnts[66].y = 79;
    circPnts[67].x = 154; circPnts[67].y = 80;
    circPnts[68].x = 155; circPnts[68].y = 81;
    circPnts[69].x = 155; circPnts[69].y = 82;
    circPnts[70].x = 155; circPnts[70].y = 83;
    circPnts[71].x = 155; circPnts[71].y = 84;
    circPnts[72].x = 155; circPnts[72].y = 85;
    circPnts[73].x = 155; circPnts[73].y = 86;
    circPnts[74].x = 155; circPnts[74].y = 87;
    circPnts[75].x = 155; circPnts[75].y = 88;
    circPnts[76].x = 155; circPnts[76].y = 89;
    circPnts[77].x = 155; circPnts[77].y = 90;
    circPnts[78].x = 155; circPnts[78].y = 91;
    circPnts[79].x = 155; circPnts[79].y = 92;
    circPnts[80].x = 155; circPnts[80].y = 93;
    circPnts[81].x = 155; circPnts[81].y = 94;
    circPnts[82].x = 155; circPnts[82].y = 95;
    circPnts[83].x = 155; circPnts[83].y = 96;
    circPnts[84].x = 155; circPnts[84].y = 97;
    circPnts[85].x = 155; circPnts[85].y = 98;
    circPnts[86].x = 155; circPnts[86].y = 99;
    circPnts[87].x = 155; circPnts[87].y = 100;
    circPnts[88].x = 155; circPnts[88].y = 101;
    circPnts[89].x = 155; circPnts[89].y = 102;
    circPnts[90].x = 155; circPnts[90].y = 103;
    circPnts[91].x = 155; circPnts[91].y = 104;
    circPnts[92].x = 155; circPnts[92].y = 105;
    circPnts[93].x = 155; circPnts[93].y = 106;
    circPnts[94].x = 155; circPnts[94].y = 107;
    circPnts[95].x = 155; circPnts[95].y = 108;
    circPnts[96].x = 155; circPnts[96].y = 109;
    circPnts[97].x = 155; circPnts[97].y = 110;
    circPnts[98].x = 155; circPnts[98].y = 111;
    circPnts[99].x = 155; circPnts[99].y = 112;
    circPnts[100].x = 155; circPnts[100].y = 113;
    circPnts[101].x = 155; circPnts[101].y = 114;
    circPnts[102].x = 155; circPnts[102].y = 115;
    circPnts[103].x = 155; circPnts[103].y = 116;
    circPnts[104].x = 155; circPnts[104].y = 117;
    circPnts[105].x = 155; circPnts[105].y = 118;
    circPnts[106].x = 154; circPnts[106].y = 119;
    circPnts[107].x = 154; circPnts[107].y = 120;
    circPnts[108].x = 154; circPnts[108].y = 121;
    circPnts[109].x = 154; circPnts[109].y = 122;
    circPnts[110].x = 153; circPnts[110].y = 123;
    circPnts[111].x = 153; circPnts[111].y = 124;
    circPnts[112].x = 153; circPnts[112].y = 125;
    circPnts[113].x = 152; circPnts[113].y = 126;
    circPnts[114].x = 152; circPnts[114].y = 127;
    circPnts[115].x = 151; circPnts[115].y = 128;
    circPnts[116].x = 151; circPnts[116].y = 129;
    circPnts[117].x = 150; circPnts[117].y = 130;
    circPnts[118].x = 150; circPnts[118].y = 131;
    circPnts[119].x = 150; circPnts[119].y = 132;
    circPnts[120].x = 149; circPnts[120].y = 133;
    circPnts[121].x = 148; circPnts[121].y = 134;
    circPnts[122].x = 147; circPnts[122].y = 135;
    circPnts[123].x = 146; circPnts[123].y = 136;
    circPnts[124].x = 146; circPnts[124].y = 137;
    circPnts[125].x = 146; circPnts[125].y = 138;
    circPnts[126].x = 145; circPnts[126].y = 139;
    circPnts[127].x = 144; circPnts[127].y = 140;
    circPnts[128].x = 143; circPnts[128].y = 141;
    circPnts[129].x = 142; circPnts[129].y = 142;
    circPnts[130].x = 141; circPnts[130].y = 143;
    circPnts[131].x = 140; circPnts[131].y = 144;
    circPnts[132].x = 139; circPnts[132].y = 145;
    circPnts[133].x = 138; circPnts[133].y = 146;
    circPnts[134].x = 137; circPnts[134].y = 146;
    circPnts[135].x = 136; circPnts[135].y = 147;
    circPnts[136].x = 135; circPnts[136].y = 148;
    circPnts[137].x = 134; circPnts[137].y = 148;
    circPnts[138].x = 133; circPnts[138].y = 149;
    circPnts[139].x = 132; circPnts[139].y = 150;
    circPnts[140].x = 131; circPnts[140].y = 150;
    circPnts[141].x = 130; circPnts[141].y = 150;
    circPnts[142].x = 129; circPnts[142].y = 151;
    circPnts[143].x = 128; circPnts[143].y = 151;
    circPnts[144].x = 127; circPnts[144].y = 152;
    circPnts[145].x = 126; circPnts[145].y = 152;
    circPnts[146].x = 125; circPnts[146].y = 153;
    circPnts[147].x = 124; circPnts[147].y = 153;
    circPnts[148].x = 123; circPnts[148].y = 153;
    circPnts[149].x = 122; circPnts[149].y = 154;
    circPnts[150].x = 121; circPnts[150].y = 154;
    circPnts[151].x = 120; circPnts[151].y = 154;
    circPnts[152].x = 119; circPnts[152].y = 154;
    circPnts[153].x = 118; circPnts[153].y = 154;
    circPnts[154].x = 117; circPnts[154].y = 154;
    circPnts[155].x = 116; circPnts[155].y = 155;
    circPnts[156].x = 115; circPnts[156].y = 155;
    circPnts[157].x = 114; circPnts[157].y = 155;
    circPnts[158].x = 113; circPnts[158].y = 155;
    circPnts[159].x = 112; circPnts[159].y = 155;
    circPnts[160].x = 111; circPnts[160].y = 155;
    circPnts[161].x = 110; circPnts[161].y = 155;
    circPnts[162].x = 109; circPnts[162].y = 155;
    circPnts[163].x = 108; circPnts[163].y = 155;
    circPnts[164].x = 107; circPnts[164].y = 155;
    circPnts[165].x = 106; circPnts[165].y = 155;
    circPnts[166].x = 105; circPnts[166].y = 155;
    circPnts[167].x = 104; circPnts[167].y = 155;
    circPnts[168].x = 103; circPnts[168].y = 155;
    circPnts[169].x = 102; circPnts[169].y = 155;
    circPnts[170].x = 101; circPnts[170].y = 155;
    circPnts[171].x = 100; circPnts[171].y = 155; // Bottom Midpoint
    circPnts[172].x = 99; circPnts[172].y = 155;
    circPnts[173].x = 98; circPnts[173].y = 155;
    circPnts[174].x = 97; circPnts[174].y = 155;
    circPnts[175].x = 96; circPnts[175].y = 155;
    circPnts[176].x = 95; circPnts[176].y = 155;
    circPnts[177].x = 94; circPnts[177].y = 155;
    circPnts[178].x = 93; circPnts[178].y = 155;
    circPnts[179].x = 92; circPnts[179].y = 155;
    circPnts[180].x = 91; circPnts[180].y = 155;
    circPnts[181].x = 90; circPnts[181].y = 155;
    circPnts[182].x = 89; circPnts[182].y = 155;
    circPnts[183].x = 88; circPnts[183].y = 155;
    circPnts[184].x = 87; circPnts[184].y = 155;
    circPnts[185].x = 86; circPnts[185].y = 155;
    circPnts[186].x = 85; circPnts[186].y = 155;
    circPnts[187].x = 84; circPnts[187].y = 155;
    circPnts[188].x = 83; circPnts[188].y = 155;
    circPnts[189].x = 82; circPnts[189].y = 154;
    circPnts[190].x = 81; circPnts[190].y = 154;
    circPnts[191].x = 80; circPnts[191].y = 154;
    circPnts[192].x = 79; circPnts[192].y = 154;
    circPnts[193].x = 78; circPnts[193].y = 154;
    circPnts[194].x = 77; circPnts[194].y = 154;
    circPnts[195].x = 76; circPnts[195].y = 153;
    circPnts[196].x = 75; circPnts[196].y = 153;
    circPnts[197].x = 74; circPnts[197].y = 153;
    circPnts[198].x = 73; circPnts[198].y = 152;
    circPnts[199].x = 72; circPnts[199].y = 152;
    circPnts[200].x = 71; circPnts[200].y = 151;
    circPnts[201].x = 70; circPnts[201].y = 151;
    circPnts[202].x = 69; circPnts[202].y = 150;
    circPnts[203].x = 68; circPnts[203].y = 150;
    circPnts[204].x = 67; circPnts[204].y = 150;
    circPnts[205].x = 66; circPnts[205].y = 149;
    circPnts[206].x = 65; circPnts[206].y = 148;
    circPnts[207].x = 64; circPnts[207].y = 148;
    circPnts[208].x = 63; circPnts[208].y = 147;
    circPnts[209].x = 62; circPnts[209].y = 146;
    circPnts[210].x = 61; circPnts[210].y = 146;
    circPnts[211].x = 60; circPnts[211].y = 145;
    circPnts[212].x = 59; circPnts[212].y = 144;
    circPnts[213].x = 58; circPnts[213].y = 143;
    circPnts[214].x = 57; circPnts[214].y = 142;
    circPnts[215].x = 56; circPnts[215].y = 141;
    circPnts[216].x = 55; circPnts[216].y = 140;
    circPnts[217].x = 54; circPnts[217].y = 139;
    circPnts[218].x = 53; circPnts[218].y = 138;
    circPnts[219].x = 53; circPnts[219].y = 137;
    circPnts[220].x = 53; circPnts[220].y = 136;
    circPnts[221].x = 52; circPnts[221].y = 135;
    circPnts[222].x = 51; circPnts[222].y = 134;
    circPnts[223].x = 50; circPnts[223].y = 133;
    circPnts[224].x = 49; circPnts[224].y = 132;
    circPnts[225].x = 49; circPnts[225].y = 131;
    circPnts[226].x = 49; circPnts[226].y = 130;
    circPnts[227].x = 48; circPnts[227].y = 129;
    circPnts[228].x = 48; circPnts[228].y = 128;
    circPnts[229].x = 47; circPnts[229].y = 127;
    circPnts[230].x = 47; circPnts[230].y = 126;
    circPnts[231].x = 46; circPnts[231].y = 125;
    circPnts[232].x = 46; circPnts[232].y = 124;
    circPnts[233].x = 46; circPnts[233].y = 123;
    circPnts[234].x = 45; circPnts[234].y = 122;
    circPnts[235].x = 45; circPnts[235].y = 121;
    circPnts[236].x = 45; circPnts[236].y = 120;
    circPnts[237].x = 45; circPnts[237].y = 119;
    circPnts[238].x = 44; circPnts[238].y = 118;
    circPnts[239].x = 44; circPnts[239].y = 117;
    circPnts[240].x = 44; circPnts[240].y = 116;
    circPnts[241].x = 44; circPnts[241].y = 115;
    circPnts[242].x = 44; circPnts[242].y = 114;
    circPnts[243].x = 44; circPnts[243].y = 113;
    circPnts[244].x = 44; circPnts[244].y = 112;
    circPnts[245].x = 44; circPnts[245].y = 111;
    circPnts[246].x = 44; circPnts[246].y = 110;
    circPnts[247].x = 44; circPnts[247].y = 109;
    circPnts[248].x = 44; circPnts[248].y = 108;
    circPnts[249].x = 44; circPnts[249].y = 107;
    circPnts[250].x = 44; circPnts[250].y = 106;
    circPnts[251].x = 44; circPnts[251].y = 105;
    circPnts[252].x = 44; circPnts[252].y = 104;
    circPnts[253].x = 44; circPnts[253].y = 103;
    circPnts[254].x = 44; circPnts[254].y = 102;
    circPnts[255].x = 44; circPnts[255].y = 101;
    circPnts[256].x = 44; circPnts[256].y = 100;
    circPnts[257].x = 44; circPnts[257].y = 99;
    circPnts[258].x = 44; circPnts[258].y = 98;
    circPnts[259].x = 44; circPnts[259].y = 97;
    circPnts[260].x = 44; circPnts[260].y = 96;
    circPnts[261].x = 44; circPnts[261].y = 95;
    circPnts[262].x = 44; circPnts[262].y = 94;
    circPnts[263].x = 44; circPnts[263].y = 93;
    circPnts[264].x = 44; circPnts[264].y = 92;
    circPnts[265].x = 44; circPnts[265].y = 91;
    circPnts[266].x = 44; circPnts[266].y = 90;
    circPnts[267].x = 44; circPnts[267].y = 89;
    circPnts[268].x = 44; circPnts[268].y = 88;
    circPnts[269].x = 44; circPnts[269].y = 87;
    circPnts[270].x = 44; circPnts[270].y = 86;
    circPnts[271].x = 44; circPnts[271].y = 85;
    circPnts[272].x = 44; circPnts[272].y = 84;
    circPnts[273].x = 44; circPnts[273].y = 83;
    circPnts[274].x = 44; circPnts[274].y = 82;
    circPnts[275].x = 44; circPnts[275].y = 81;
    circPnts[276].x = 45; circPnts[276].y = 80;
    circPnts[277].x = 45; circPnts[277].y = 79;
    circPnts[278].x = 45; circPnts[278].y = 78;
    circPnts[279].x = 45; circPnts[279].y = 77;
    circPnts[280].x = 46; circPnts[280].y = 76;
    circPnts[281].x = 46; circPnts[281].y = 75;
    circPnts[282].x = 46; circPnts[282].y = 74;
    circPnts[283].x = 47; circPnts[283].y = 73;
    circPnts[284].x = 47; circPnts[284].y = 72;
    circPnts[285].x = 48; circPnts[285].y = 71;
    circPnts[286].x = 48; circPnts[286].y = 70;
    circPnts[287].x = 49; circPnts[287].y = 69;
    circPnts[288].x = 49; circPnts[288].y = 68;
    circPnts[289].x = 49; circPnts[289].y = 67;
    circPnts[290].x = 50; circPnts[290].y = 66;
    circPnts[291].x = 51; circPnts[291].y = 65;
    circPnts[292].x = 52; circPnts[292].y = 64;
    circPnts[293].x = 53; circPnts[293].y = 63;
    circPnts[294].x = 53; circPnts[294].y = 62;
    circPnts[295].x = 53; circPnts[295].y = 61;
    circPnts[296].x = 54; circPnts[296].y = 60;
    circPnts[297].x = 55; circPnts[297].y = 59;
    circPnts[298].x = 56; circPnts[298].y = 58;
    circPnts[299].x = 57; circPnts[299].y = 57;
    circPnts[300].x = 58; circPnts[300].y = 56;
    circPnts[301].x = 59; circPnts[301].y = 55;
    circPnts[302].x = 60; circPnts[302].y = 54;
    circPnts[303].x = 61; circPnts[303].y = 53;
    circPnts[304].x = 62; circPnts[304].y = 53;
    circPnts[305].x = 63; circPnts[305].y = 52;
    circPnts[306].x = 64; circPnts[306].y = 51;
    circPnts[307].x = 65; circPnts[307].y = 51;
    circPnts[308].x = 66; circPnts[308].y = 50;
    circPnts[309].x = 67; circPnts[309].y = 49;
    circPnts[310].x = 68; circPnts[310].y = 49;
    circPnts[311].x = 69; circPnts[311].y = 49;
    circPnts[312].x = 70; circPnts[312].y = 48;
    circPnts[313].x = 71; circPnts[313].y = 48;
    circPnts[314].x = 72; circPnts[314].y = 47;
    circPnts[315].x = 73; circPnts[315].y = 47;
    circPnts[316].x = 74; circPnts[316].y = 46;
    circPnts[317].x = 75; circPnts[317].y = 46;
    circPnts[318].x = 76; circPnts[318].y = 46;
    circPnts[319].x = 77; circPnts[319].y = 45;
    circPnts[320].x = 78; circPnts[320].y = 45;
    circPnts[321].x = 79; circPnts[321].y = 45;
    circPnts[322].x = 80; circPnts[322].y = 45;
    circPnts[323].x = 81; circPnts[323].y = 45;
    circPnts[324].x = 82; circPnts[324].y = 45;
    circPnts[325].x = 83; circPnts[325].y = 44;
    circPnts[326].x = 84; circPnts[326].y = 44;
    circPnts[327].x = 85; circPnts[327].y = 44;
    circPnts[328].x = 86; circPnts[328].y = 44;
    circPnts[329].x = 87; circPnts[329].y = 44;
    circPnts[330].x = 88; circPnts[330].y = 44;
    circPnts[331].x = 89; circPnts[331].y = 44;
    circPnts[332].x = 90; circPnts[332].y = 44;
    circPnts[333].x = 91; circPnts[333].y = 44;
    circPnts[334].x = 92; circPnts[334].y = 44;
    circPnts[335].x = 93; circPnts[335].y = 44;
    circPnts[336].x = 94; circPnts[336].y = 44;
    circPnts[337].x = 95; circPnts[337].y = 44;
    circPnts[338].x = 96; circPnts[338].y = 44;
    circPnts[339].x = 97; circPnts[339].y = 44;
    circPnts[340].x = 98; circPnts[340].y = 44;
    circPnts[341].x = 99; circPnts[341].y = 44;

  }

} // End of namespace
