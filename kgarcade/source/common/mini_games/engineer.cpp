
#include "../main.h"


namespace ns_Engineer {


// ****************************************************************************************************************
// Defines specific to this mini-game
// ****************************************************************************************************************
#define dirUp    0
#define dirDown  1
#define dirLeft  2
#define dirRight 3
#define stDead   0
#define stAlive  1


// ****************************************************************************************************************
// Function prototypes specific to this mini-game
// ****************************************************************************************************************
int changeDir(int diverter, int currDir);


// ****************************************************************************************************************
// Globals specific to this mini-game
// ****************************************************************************************************************
TCHAR	instructions[][32] = { TEXT("Engineer"),
														 TEXT(""),
														 TEXT("Give the captain more"),
														 TEXT("power, wrench-monkey!"),
														 TEXT("Guide the particles"),
														 TEXT("spitting out of the"),
														 TEXT("generator into the"),
														 TEXT("appropriate injector"),
														 TEXT("ports, and don't let"),
														 TEXT("them feed back in!"),
                             //    ---------------------------
                             TEXT("The Goal"),
														 TEXT(""),
														 TEXT("Direct as many particles"),
														 TEXT("into the appropriate"),
														 TEXT("injector ports as you"),
														 TEXT("can.  If any get back"),
														 TEXT("into the generator, you"),
														 TEXT("lose points.  Hit the"),
														 TEXT("wrong injector ports,"),
														 TEXT("and you lose points."),
                             //    ---------------------------
                             TEXT("How To Play"),
														 TEXT(""),
														 TEXT("Move up, down left or"),
														 TEXT("right to cycle the"),
														 TEXT("corresponding diverter."),
														 TEXT("Form paths for particles"),
														 TEXT("to follow."),
														 TEXT(""),
														 TEXT(""),
														 TEXT(""),
                             //    ----------------------------
};

CGapiSurface*	background          = NULL; // Background image
CGapiSurface* diverters[8];			          // The six different diverter images
CGapiSurface* particleImgs[6][6];         // Images of the particles
CGapiSurface* nucleus[10];
hssSound*     sfxDiverter         = NULL;
hssSound*     sfxParticleEmerging = NULL;
hssSound*     sfxParticleGood     = NULL;
hssSound*     sfxParticleBad      = NULL;
hssSound*     sfxMissed           = NULL;
POINT         particlesA[5];              // The particles moving around coordinates
int						top_diverter        = 0;	  // Index into the diverters array for the top diverter
int						bottom_diverter     = 0;	  // Index into the diverters array for the bottom diverter
int						left_diverter       = 0;		// Index into the diverters array for the left diverter
int						right_diverter      = 0;		// Index into the diverters array for the right diverter
int           particlesB[5][8];           // The particles moving around: [x][0] = type (0-3), [x][1] = state (0/1),
                                          // [x][2] = frame change delay, [x][3] = direction,
                                          // [x][4] = particle alive (stAlive) or dead (stDead), [x][5] = time before particle emerges from generator
int           cheat_time          = 0;


} // End of namespace


// ****************************************************************************************************************
// ProcessNextFrame handler
// ****************************************************************************************************************
void CGame::pnfEngineer(CGapiSurface* backbuffer) {

	using namespace ns_Engineer;

	// Blit background
	backbuffer->BltFast(xadj, yadj, background, NULL, GDBLTFAST_KEYSRC, NULL);

	// Blit nucleus
	backbuffer->BltFast(xadj + 74, yadj + 73, nucleus[rand() % 8], NULL, GDBLTFAST_KEYSRC, NULL);

	// Blit diverters
	backbuffer->BltFast(xadj + 91,  yadj + 40,  diverters[top_diverter],    NULL, GDBLTFAST_KEYSRC, NULL);
	backbuffer->BltFast(xadj + 91,  yadj + 140, diverters[bottom_diverter], NULL, GDBLTFAST_KEYSRC, NULL);
	backbuffer->BltFast(xadj + 40,  yadj + 90,  diverters[left_diverter],   NULL, GDBLTFAST_KEYSRC, NULL);
	backbuffer->BltFast(xadj + 141, yadj + 90,  diverters[right_diverter],  NULL, GDBLTFAST_KEYSRC, NULL);

	// Blit particles and deal with them - this is the meat of it
	for (int i = 0; i < 3; i++) { // 3 particles max at any given time

		if (particlesB[i][4] == stAlive) {

			backbuffer->BltFast(xadj + particlesA[i].x, yadj + particlesA[i].y, particleImgs[particlesB[i][0]][particlesB[i][1]], NULL, GDBLTFAST_KEYSRC, NULL);

			// Frame change
			particlesB[i][2]++;
			if (particlesB[i][2] > 2) {
				particlesB[i][2] = 0;
				particlesB[i][1]++;
				if (particlesB[i][1] > 1) {
					particlesB[i][1] = 0;
				}
			}

			// Movemement
			switch (particlesB[i][3]) {
				case dirUp:    { particlesA[i].y--; break; }
				case dirDown:  { particlesA[i].y++; break; }
				case dirLeft:  { particlesA[i].x--; break; }
				case dirRight: { particlesA[i].x++; break; }
			}

			// See if they sent it back into the generator, subtract from score if so
			if (particlesA[i].x == 95 && particlesA[i].y == 94) {
				sndObj.playSound(sfxMissed);
				subtractFromScore(250);
				particlesB[i][4] = stDead; // Kill the particle
				particlesB[i][5] = rand() % 100; // Pick a time before it emerges as a new particle again
			}

			// Check for magic coordinates: corner pieces: just changes direction appropriately
			if (particlesA[i].x == 95  && particlesA[i].y == 12)                                  { particlesB[i][3] = dirRight; } // Top
			if (particlesA[i].x == 95  && particlesA[i].y == 177)                                 { particlesB[i][3] = dirLeft;  } // Bottom
			if (particlesA[i].x == 12  && particlesA[i].y == 94)                                  { particlesB[i][3] = dirUp;    } // Left
			if (particlesA[i].x == 177 && particlesA[i].y == 94)                                  { particlesB[i][3] = dirDown;  } // Right
			if (particlesA[i].x == 44  && particlesA[i].y == 44  && particlesB[i][3] == dirUp)    { particlesB[i][3] = dirRight; } // Upper Left Moving Up
			if (particlesA[i].x == 44  && particlesA[i].y == 44  && particlesB[i][3] == dirLeft)  { particlesB[i][3] = dirDown;  } // Upper Left Moving Left
			if (particlesA[i].x == 145 && particlesA[i].y == 44  && particlesB[i][3] == dirUp)    { particlesB[i][3] = dirLeft;  } // Upper Right Moving Up
			if (particlesA[i].x == 145 && particlesA[i].y == 44  && particlesB[i][3] == dirRight) { particlesB[i][3] = dirDown;  } // Upper Right Moving Right
			if (particlesA[i].x == 44  && particlesA[i].y == 144 && particlesB[i][3] == dirDown)  { particlesB[i][3] = dirRight; } // Lower Left Moving Down
			if (particlesA[i].x == 44  && particlesA[i].y == 144 && particlesB[i][3] == dirLeft)  { particlesB[i][3] = dirUp;    } // Lower Left Moving Left
			if (particlesA[i].x == 145 && particlesA[i].y == 144 && particlesB[i][3] == dirDown)  { particlesB[i][3] = dirLeft;  } // Lower Right Moving Down
			if (particlesA[i].x == 145 && particlesA[i].y == 144 && particlesB[i][3] == dirRight) { particlesB[i][3] = dirUp;    } // Lower Right Moving Right

			// Check for magic coordinates: divertors: change direction accordingly when we hit one
			if (particlesA[i].x == 95 && particlesA[i].y == 44) { // Top diverter
				particlesB[i][3] = changeDir(0, particlesB[i][3]);
				if (particlesB[i][3] == -1) { // Diverter state not valid when particle arrived, kill it
					particlesB[i][4] = stDead; // Kill the particle
					particlesB[i][5] = rand() % 100; // Pick a time before it emerges as a new particle again
				}
			}
			if (particlesA[i].x == 95 && particlesA[i].y == 144) { // Bottom diverter
				particlesB[i][3] = changeDir(1, particlesB[i][3]);
				if (particlesB[i][3] == -1) { // Diverter state not valid when particle arrived, kill it
					particlesB[i][4] = stDead; // Kill the particle
					particlesB[i][5] = rand() % 100; // Pick a time before it emerges as a new particle again
				}
			}
			if (particlesA[i].x == 44 && particlesA[i].y == 94) { // Left diverter
				particlesB[i][3] = changeDir(2, particlesB[i][3]);
				if (particlesB[i][3] == -1) { // Diverter state not valid when particle arrived, kill it
					particlesB[i][4] = stDead; // Kill the particle
					particlesB[i][5] = rand() % 100; // Pick a time before it emerges as a new particle again
				}
			}
			if (particlesA[i].x == 145 && particlesA[i].y == 94) { // Right diverter
				particlesB[i][3] = changeDir(3, particlesB[i][3]);
				if (particlesB[i][3] == -1) { // Diverter state not valid when particle arrived, kill it
					particlesB[i][4] = stDead; // Kill the particle
					particlesB[i][5] = rand() % 100; // Pick a time before it emerges as a new particle again
				}
			}

			// Check for magic coordinates: injector ports: if correct one, add to score, otherwise subtract
			if (particlesA[i].x == 12 && particlesA[i].y == 12)  { // Top Left
				if (particlesB[i][0] == 0) { addToScore(50); sndObj.playSound(sfxParticleGood); } else { subtractFromScore(100); sndObj.playSound(sfxParticleBad); }
				particlesB[i][4] = stDead; // Kill the particle
				particlesB[i][5] = rand() % 100; // Pick a time before it emerges as a new particle again
			}
			if (particlesA[i].x == 12 && particlesA[i].y == 177) { // Bottom Left
				if (particlesB[i][0] == 3) { addToScore(50); sndObj.playSound(sfxParticleGood); } else { subtractFromScore(100); sndObj.playSound(sfxParticleBad); }
				particlesB[i][4] = stDead; // Kill the particle
				particlesB[i][5] = rand() % 100; // Pick a time before it emerges as a new particle again
			}
			if (particlesA[i].x == 177 && particlesA[i].y == 12)  { // Top Right
				if (particlesB[i][0] == 1) { addToScore(50); sndObj.playSound(sfxParticleGood); } else { subtractFromScore(100); sndObj.playSound(sfxParticleBad); }
				particlesB[i][4] = stDead; // Kill the particle
				particlesB[i][5] = rand() % 100; // Pick a time before it emerges as a new particle again
			}
			if (particlesA[i].x == 177 && particlesA[i].y == 177) { // Bottom Right
				if (particlesB[i][0] == 2) { addToScore(50); sndObj.playSound(sfxParticleGood); } else { subtractFromScore(100); sndObj.playSound(sfxParticleBad); }
				particlesB[i][4] = stDead; // Kill the particle
				particlesB[i][5] = rand() % 100; // Pick a time before it emerges as a new particle again
			}

		} else { // Particle is currently dead

			particlesB[i][5]--;
			if (particlesB[i][5] < 0) { // Time to emerge from the generator
				sndObj.playSound(sfxParticleEmerging);
        cheat_time = 0;
				particlesA[i].x = 95;
				particlesA[i].y = 94;
				particlesB[i][4] = stAlive; // It lives!
				particlesB[i][5] = 0; // Time to emerge from the generator
				particlesB[i][2] = 0; // Frame change delay
				pickType:
				int type = rand() % 4;
				if (type != 0 && type != 1 && type != 2 && type != 3) { goto pickType; }
				particlesB[i][0] = type; // Type
				pickState:
				int state = rand() % 1;
				if (state != 0 && state != 1) { goto pickState; }
				particlesB[i][1] = state; // State
				pickDir:
				int dir = rand() % 4;
				if (dir != 0 && dir != 1 && dir != 2 && dir != 3) { goto pickDir; }
				particlesB[i][3] = dir; // Direction
			}

		}

	} // End for loop

  // Check for a cheat win: Three particles going around a closed loop for 10 seconds
  cheat_time++;
  if (game_mode == gmAdventureGame && levelHintDone &&
      top_diverter == 4 && bottom_diverter == 4 && left_diverter == 5 && right_diverter == 5 && cheat_time >= 250) {
        addToScore(500);
        force_game_over = true;
  }

}


// ****************************************************************************************************************
// KeyDown handler
// ****************************************************************************************************************
void CGame::kdEngineer(DWORD dwKey) {

	using namespace ns_Engineer;

	// Handle up movement events
	if (dwKey == kUp) {
		sndObj.playSound(sfxDiverter);
		player_dir_north = true;
		top_diverter++;
		if (top_diverter > 5) { top_diverter = 0; }
	}

	// Handle down movement events
	if (dwKey == kDown) {
		sndObj.playSound(sfxDiverter);
		player_dir_south = true;
		bottom_diverter++;
		if (bottom_diverter > 5) { bottom_diverter = 0; }
	}

	// Handle left movement events
	if (dwKey == kLeft) {
		sndObj.playSound(sfxDiverter);
		player_dir_west = true;
		left_diverter++;
		if (left_diverter > 5) { left_diverter = 0; }
	}

	// Handle right movement events
	if (dwKey == kRight) {
		sndObj.playSound(sfxDiverter);
		player_dir_east = true;
		right_diverter++;
		if (right_diverter > 5) { right_diverter = 0; }
	}

}


// ****************************************************************************************************************
// KeyUp handler
// ****************************************************************************************************************
void CGame::kuEngineer(DWORD dwKey) {

	using namespace ns_Engineer;

	// Command button
	if (dwKey == kCommand) {
    miniGameCommandButtonHandler();
	}

	// Handle up movement events
	if (dwKey == kUp) {
		player_dir_north = false;
	}

	// Handle down movement events
	if (dwKey == kDown) {
		player_dir_south = false;
	}

	// Handle left movement events
	if (dwKey == kLeft) {
		player_dir_west = false;
	}

	// Handle right movement events
	if (dwKey == kRight) {
		player_dir_east = false;
	}

}


// ****************************************************************************************************************
// Initialize
// ****************************************************************************************************************
void CGame::initializeEngineer() {

	using namespace ns_Engineer;

	top_diverter		 = 0;
	bottom_diverter  = 0;
	left_diverter		 = 0;
	right_diverter	 = 0;

  particlesB[0][4] = stDead; particlesB[0][5] = 0;
  particlesB[1][4] = stDead; particlesB[1][5] = 60;
  particlesB[2][4] = stDead; particlesB[2][5] = 120;

}


// ****************************************************************************************************************
// Loader
// ****************************************************************************************************************
void CGame::loadEngineer(CGapiSurface* backbuffer) {

	using namespace ns_Engineer;

	processEvents = false;

	// Move on to the next step
	loading_step++;

	// Do the appropriate step
	switch(loading_step) {

		case 1: {
			doCommonInit();
      int i = 0;
      for (i = 0; i < 6; i++) { diverters[i] = NULL; }
      for (i = 0; i < 8; i++) { nucleus[i]   = NULL; }
      for (i = 0; i < 4; i++) { particleImgs[i][0] = NULL; particleImgs[i][1] = NULL; particleImgs[i][2] = NULL; particleImgs[i][3] = NULL;}
      background          = NULL;
      sfxDiverter         = NULL;
      sfxParticleEmerging = NULL;
      sfxParticleGood     = NULL;
      sfxParticleBad      = NULL;
      sfxMissed           = NULL;
		break; }

		case 2: {
			background          = new CGapiSurface(); createSurface(TEXT("engineer : GFX_ENGINEER_BACKGROUND"),          background->CreateSurface        (0, m_config.hInstance, GFX_ENGINEER_BACKGROUND,          TEXT("GRAPHICS"))); background->SetColorKey        (RGB(255, 128, 255));
			diverters[0]        = new CGapiSurface(); createSurface(TEXT("engineer : GFX_ENGINEER_DIVERTER_UP_LEFT"),    diverters[0]->CreateSurface      (0, m_config.hInstance, GFX_ENGINEER_DIVERTER_UP_LEFT,    TEXT("GRAPHICS"))); diverters[0]->SetColorKey      (RGB(255, 128, 255));
			diverters[1]        = new CGapiSurface(); createSurface(TEXT("engineer : GFX_ENGINEER_DIVERTER_UP_RIGHT"),   diverters[1]->CreateSurface      (0, m_config.hInstance, GFX_ENGINEER_DIVERTER_UP_RIGHT,   TEXT("GRAPHICS"))); diverters[1]->SetColorKey      (RGB(255, 128, 255));
			diverters[2]        = new CGapiSurface(); createSurface(TEXT("engineer : GFX_ENGINEER_DIVERTER_DOWN_RIGHT"), diverters[2]->CreateSurface      (0, m_config.hInstance, GFX_ENGINEER_DIVERTER_DOWN_RIGHT, TEXT("GRAPHICS"))); diverters[2]->SetColorKey      (RGB(255, 128, 255));
			diverters[3]        = new CGapiSurface(); createSurface(TEXT("engineer : GFX_ENGINEER_DIVERTER_DOWN_LEFT"),  diverters[3]->CreateSurface      (0, m_config.hInstance, GFX_ENGINEER_DIVERTER_DOWN_LEFT,  TEXT("GRAPHICS"))); diverters[3]->SetColorKey      (RGB(255, 128, 255));
			diverters[4]        = new CGapiSurface(); createSurface(TEXT("engineer : GFX_ENGINEER_DIVERTER_HORIZONTAL"), diverters[4]->CreateSurface      (0, m_config.hInstance, GFX_ENGINEER_DIVERTER_HORIZONTAL, TEXT("GRAPHICS"))); diverters[4]->SetColorKey      (RGB(255, 128, 255));
			diverters[5]        = new CGapiSurface(); createSurface(TEXT("engineer : GFX_ENGINEER_DIVERTER_VERTICAL"),   diverters[5]->CreateSurface      (0, m_config.hInstance, GFX_ENGINEER_DIVERTER_VERTICAL,   TEXT("GRAPHICS"))); diverters[5]->SetColorKey      (RGB(255, 128, 255));
			particleImgs[0][0]  = new CGapiSurface(); createSurface(TEXT("engineer : GFX_ENGINEER_PARTICLE1_00"),        particleImgs[0][0]->CreateSurface(0, m_config.hInstance, GFX_ENGINEER_PARTICLE1_00,        TEXT("GRAPHICS"))); particleImgs[0][0]->SetColorKey(RGB(255, 128, 255));
			particleImgs[0][1]  = new CGapiSurface(); createSurface(TEXT("engineer : GFX_ENGINEER_PARTICLE1_01"),        particleImgs[0][1]->CreateSurface(0, m_config.hInstance, GFX_ENGINEER_PARTICLE1_01,        TEXT("GRAPHICS"))); particleImgs[0][1]->SetColorKey(RGB(255, 128, 255));
			particleImgs[1][0]  = new CGapiSurface(); createSurface(TEXT("engineer : GFX_ENGINEER_PARTICLE2_00"),        particleImgs[1][0]->CreateSurface(0, m_config.hInstance, GFX_ENGINEER_PARTICLE2_00,        TEXT("GRAPHICS"))); particleImgs[1][0]->SetColorKey(RGB(255, 128, 255));
			particleImgs[1][1]  = new CGapiSurface(); createSurface(TEXT("engineer : GFX_ENGINEER_PARTICLE2_01"),        particleImgs[1][1]->CreateSurface(0, m_config.hInstance, GFX_ENGINEER_PARTICLE2_01,        TEXT("GRAPHICS"))); particleImgs[1][1]->SetColorKey(RGB(255, 128, 255));
			particleImgs[2][0]  = new CGapiSurface(); createSurface(TEXT("engineer : GFX_ENGINEER_PARTICLE3_00"),        particleImgs[2][0]->CreateSurface(0, m_config.hInstance, GFX_ENGINEER_PARTICLE3_00,        TEXT("GRAPHICS"))); particleImgs[2][0]->SetColorKey(RGB(255, 128, 255));
			particleImgs[2][1]  = new CGapiSurface(); createSurface(TEXT("engineer : GFX_ENGINEER_PARTICLE3_01"),        particleImgs[2][1]->CreateSurface(0, m_config.hInstance, GFX_ENGINEER_PARTICLE3_01,        TEXT("GRAPHICS"))); particleImgs[2][1]->SetColorKey(RGB(255, 128, 255));
			particleImgs[3][0]  = new CGapiSurface(); createSurface(TEXT("engineer : GFX_ENGINEER_PARTICLE4_00"),        particleImgs[3][0]->CreateSurface(0, m_config.hInstance, GFX_ENGINEER_PARTICLE4_00,        TEXT("GRAPHICS"))); particleImgs[3][0]->SetColorKey(RGB(255, 128, 255));
			particleImgs[3][1]  = new CGapiSurface(); createSurface(TEXT("engineer : GFX_ENGINEER_PARTICLE4_01"),        particleImgs[3][1]->CreateSurface(0, m_config.hInstance, GFX_ENGINEER_PARTICLE4_01,        TEXT("GRAPHICS"))); particleImgs[3][1]->SetColorKey(RGB(255, 128, 255));
			nucleus[0]          = new CGapiSurface(); createSurface(TEXT("engineer : GFX_ENGINEER_NUCLEUS_1"),           nucleus[0]->CreateSurface        (0, m_config.hInstance, GFX_ENGINEER_NUCLEUS_1,           TEXT("GRAPHICS"))); nucleus[0]->SetColorKey        (RGB(255, 128, 255));
			nucleus[1]          = new CGapiSurface(); createSurface(TEXT("engineer : GFX_ENGINEER_NUCLEUS_2"),           nucleus[1]->CreateSurface        (0, m_config.hInstance, GFX_ENGINEER_NUCLEUS_2,           TEXT("GRAPHICS"))); nucleus[1]->SetColorKey        (RGB(255, 128, 255));
			nucleus[2]          = new CGapiSurface(); createSurface(TEXT("engineer : GFX_ENGINEER_NUCLEUS_3"),           nucleus[2]->CreateSurface        (0, m_config.hInstance, GFX_ENGINEER_NUCLEUS_3,           TEXT("GRAPHICS"))); nucleus[2]->SetColorKey        (RGB(255, 128, 255));
			nucleus[3]          = new CGapiSurface(); createSurface(TEXT("engineer : GFX_ENGINEER_NUCLEUS_4"),           nucleus[3]->CreateSurface        (0, m_config.hInstance, GFX_ENGINEER_NUCLEUS_4,           TEXT("GRAPHICS"))); nucleus[3]->SetColorKey        (RGB(255, 128, 255));
			nucleus[4]          = new CGapiSurface(); createSurface(TEXT("engineer : GFX_ENGINEER_NUCLEUS_5"),           nucleus[4]->CreateSurface        (0, m_config.hInstance, GFX_ENGINEER_NUCLEUS_5,           TEXT("GRAPHICS"))); nucleus[4]->SetColorKey        (RGB(255, 128, 255));
			nucleus[5]          = new CGapiSurface(); createSurface(TEXT("engineer : GFX_ENGINEER_NUCLEUS_6"),           nucleus[5]->CreateSurface        (0, m_config.hInstance, GFX_ENGINEER_NUCLEUS_6,           TEXT("GRAPHICS"))); nucleus[5]->SetColorKey        (RGB(255, 128, 255));
			nucleus[6]          = new CGapiSurface(); createSurface(TEXT("engineer : GFX_ENGINEER_NUCLEUS_7"),           nucleus[6]->CreateSurface        (0, m_config.hInstance, GFX_ENGINEER_NUCLEUS_7,           TEXT("GRAPHICS"))); nucleus[6]->SetColorKey        (RGB(255, 128, 255));
			nucleus[7]          = new CGapiSurface(); createSurface(TEXT("engineer : GFX_ENGINEER_NUCLEUS_8"),           nucleus[7]->CreateSurface        (0, m_config.hInstance, GFX_ENGINEER_NUCLEUS_8,           TEXT("GRAPHICS"))); nucleus[7]->SetColorKey        (RGB(255, 128, 255));
			sfxDiverter         = new hssSound();     loadSFX      (TEXT("engineer : SFX_ENGINEER_DIVERTER"),            sfxDiverter->load                (m_config.hInstance,    SFX_ENGINEER_DIVERTER));                              sfxDiverter->loop              (false);
			sfxParticleEmerging = new hssSound();     loadSFX      (TEXT("engineer : SFX_ENGINEER_PARTICLE_EMERGING"),   sfxParticleEmerging->load        (m_config.hInstance,    SFX_ENGINEER_PARTICLE_EMERGING));                     sfxParticleEmerging->          loop(false);
			sfxParticleGood     = new hssSound();     loadSFX      (TEXT("engineer : SFX_ENGINEER_PARTICLE_GOOD"),       sfxParticleGood->load            (m_config.hInstance,    SFX_ENGINEER_PARTICLE_GOOD));                         sfxParticleGood->              loop(false);
			sfxParticleBad      = new hssSound();     loadSFX      (TEXT("engineer : SFX_ENGINEER_PARTICLE_BAD"),        sfxParticleBad->load             (m_config.hInstance,    SFX_ENGINEER_PARTICLE_BAD));                          sfxParticleBad->               loop(false);
			sfxMissed           = new hssSound();     loadSFX      (TEXT("engineer : SFX_MISSED"),                       sfxMissed->load                  (m_config.hInstance,    SFX_MISSED));                                         sfxMissed->                    loop(false);
		break; }

    case 3: {
			initializeEngineer();
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
void CGame::destroyEngineer(CGapiSurface* backbuffer) {

	using namespace ns_Engineer;

	processEvents = false;

	// Move on to the next step
	destroying_step++;

	// Do the appropriate step
	switch(destroying_step) {

		case 1: {
			doCommonCleanup();
		break; }

		case 2: {
			delete background;
			delete diverters[0];
			delete diverters[1];
			delete diverters[2];
			delete diverters[3];
			delete diverters[4];
			delete diverters[5];
      delete particleImgs[0][0];
      delete particleImgs[1][0];
      delete particleImgs[2][0];
      delete particleImgs[3][0];
      delete particleImgs[0][1];
      delete particleImgs[1][1];
      delete particleImgs[2][1];
      delete particleImgs[3][1];
			delete nucleus[0];
			delete nucleus[1];
			delete nucleus[2];
			delete nucleus[3];
			delete nucleus[4];
			delete nucleus[5];
			delete nucleus[6];
			delete nucleus[7];
			delete sfxDiverter;
			delete sfxParticleEmerging;
			delete sfxParticleGood;
			delete sfxParticleBad;
			delete sfxMissed;
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
namespace ns_Engineer {

  int changeDir(int diverter, int currDir) {

    int retVal = 0;
    int diverter_state = 0;

    // Get the current state of the appropriate diverter
    switch (diverter) {
      case 0: { diverter_state = top_diverter;    break; }
      case 1: { diverter_state = bottom_diverter; break; }
      case 2: { diverter_state = left_diverter;   break; }
      case 3: { diverter_state = right_diverter;  break; }
    }

    // Depending on which direction the particle is moving and the state of the diverter, change the direction appropriately
    switch (currDir) {

      case dirUp: {
        switch (diverter_state) {
          case 0: { retVal = -1;       break; }
          case 1: { retVal = -1;       break; }
          case 2: { retVal = dirRight; break; }
          case 3: { retVal = dirLeft;  break; }
          case 4: { retVal = -1;       break; }
          case 5: { retVal = dirUp;    break; }
        }
      break; }

      case dirDown: {
        switch (diverter_state) {
          case 0: { retVal = dirLeft;  break; }
          case 1: { retVal = dirRight; break; }
          case 2: { retVal = -1;       break; }
          case 3: { retVal = -1;       break; }
          case 4: { retVal = -1;       break; }
          case 5: { retVal = dirDown;  break; }
        }
      break; }

      case dirLeft: {
        switch (diverter_state) {
          case 0: { retVal = -1;       break; }
          case 1: { retVal = dirUp;    break; }
          case 2: { retVal = dirDown;  break; }
          case 3: { retVal = -1;       break; }
          case 4: { retVal = dirLeft;  break; }
          case 5: { retVal = -1;       break; }
        }
      break; }

      case dirRight: {
        switch (diverter_state) {
          case 0: { retVal = dirUp;    break; }
          case 1: { retVal = -1;       break; }
          case 2: { retVal = -1;       break; }
          case 3: { retVal = dirDown;  break; }
          case 4: { retVal = dirRight; break; }
          case 5: { retVal = -1;       break; }
        }
      break; }

    }

    return retVal;

  }


} // End of namespace
