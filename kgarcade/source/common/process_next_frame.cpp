
#include "main.h"


HRESULT CGame::ProcessNextFrame(CGapiSurface* backbuffer, DWORD dwFlags) {

	if (doPopup) {
		pnfPopup(backbuffer);
	} else {

	  switch (current_screen) {

      // First-time initializations that require backbuffer
      case csFirstTimeInits: {
        bbCenterPoint = backbuffer->GetWidth() / 2;
        current_screen = csIntroClickgamer;
				// If the key variables are all NULL, we assume it means they were NOT read in from a config file.
				// Therefore, we need to do the default mappings and write out the KGA file
				if (kUp == NULL && kDown == NULL && kLeft == NULL && kRight == NULL && kAction == NULL && kCommand == NULL) {
					GDKEYLIST keylist;
					m_pInput->GetKeyList(&keylist);
					kUp			 = keylist.vkUp;
					kDown		 = keylist.vkDown;
					kLeft		 = keylist.vkLeft;
					kRight	 = keylist.vkRight;
					kAction  = keylist.vkA;
					kCommand = keylist.vkB;
					writeKGAFile(gameRestarted, false);
				}
      break; }

      // Exiting Program
		  case csExiting: {
				switch (shutdownStep) {
          case 1: {
						backbuffer->SetClipper(NULL);
						backbuffer->FillRect(CRect(0, 0, 240, 320), RGB(0, 0, 0), 0, NULL);
						if (ExitCounter < 120) {
							backbuffer->DrawLine(0 + ExitCounter, 160, 240 - ExitCounter, 160, RGB(255, 255, 255), NULL, NULL);
							ExitCounter = ExitCounter + 12;
						} else {
							if (ExitFadeCounter <= 0) {
								shutdownStep++;
								destroying_step = 0;
								destroyMainMenu(backbuffer);
							} else {
								backbuffer->FillRect(CRect(0, 0, 240, 320), RGB(0, 0, 0), 0, NULL);
								backbuffer->SetPixel(120, 160, RGB(ExitFadeCounter, ExitFadeCounter, ExitFadeCounter));
								ExitFadeCounter = ExitFadeCounter - 15;
							}
						}
					break; }
					case 2: {
						shutdownStep = 3;
					break; }
					case 3: {
						Shutdown();
					break; }
        }
		  break; }

		  // Intro: Clickgamer
		  case csIntroClickgamer: {
			  if			(loading)		  { loadIntroClickgamer(backbuffer); }
			  else if (destroying)  { destroyIntroClickgamer(backbuffer); }
			  else									{
															  backbuffer->SetClipper(NULL);
															  pnfIntroClickgamer(backbuffer);
			  }
		  break; }

		  // Intro: Omnytex
		  case csIntroOmnytex: {
			  if			(loading)		  { loadIntroOmnytex(backbuffer); }
			  else if (destroying)  { destroyIntroOmnytex(backbuffer); }
			  else									{
															  backbuffer->SetClipper(NULL);
															  pnfIntroOmnytex(backbuffer);
			  }
		  break; }

		  // Intro: Crackhead
		  case csIntroCrackhead: {
			  if			(loading)		  { loadIntroCrackhead(backbuffer); }
			  else if (destroying)  { destroyIntroCrackhead(backbuffer); }
			  else									{
															  backbuffer->SetClipper(NULL);
															  pnfIntroCrackhead(backbuffer);
			  }
		  break; }

		  // Title Sequence
		  case csTitleSequence: {
			  if			(loading)		  { loadTitleSequence(backbuffer); }
			  else if (destroying)  { destroyTitleSequence(backbuffer); }
			  else									{
															  backbuffer->SetClipper(NULL);
															  pnfTitleSequence(backbuffer);
			  }
		  break; }

		  // Main Menu
		  case csMainMenu: {
			  if			(loading)		  { loadMainMenu(backbuffer); }
			  else if (destroying)  { destroyMainMenu(backbuffer); }
			  else									{
															  backbuffer->SetClipper(NULL);
															  pnfMainMenu(backbuffer);
			  }
		  break; }

		  // Instructions
		  case csInstructions: {
			  backbuffer->SetClipper(NULL);
			  pnfInstructions(backbuffer);
		  break; }

		  // Options
		  case csOptions: {
			  backbuffer->SetClipper(NULL);
			  pnfOptions(backbuffer);
		  break; }

		  // Credits
		  case csCredits: {
			  backbuffer->SetClipper(NULL);
			  pnfCredits(backbuffer);
		  break; }

		  // High Scores
		  case csHighScores: {
			  backbuffer->SetClipper(NULL);
			  pnfHighScores(backbuffer);
		  break; }

		  // New Game Type
		  case csNewGameType: {
			  backbuffer->SetClipper(NULL);
			  pnfNewGameType(backbuffer);
		  break; }

		  // Walking around the ship
		  case csWalkingAroundTheShip: {
			  if			(loading)		  { loadWalkingAroundTheShip(backbuffer); }
			  else if (destroying)  { destroyWalkingAroundTheShip(backbuffer); }
			  else									{
															  backbuffer->SetClipper(NULL);
															  pnfWalkingAroundTheShip(backbuffer);
			  }
		  break; }

		  // Character Interaction
		  case csCharacterInteraction: {
			  backbuffer->SetClipper(NULL);
				pnfCharacterInteraction(backbuffer);
		  break; }

		  // Scene: Player Died
		  case csPlayerDied: {
			  if			(loading)		  { loadPlayerDied(backbuffer); }
			  else if (destroying)  { destroyPlayerDied(backbuffer); }
			  else									{
															  backbuffer->SetClipper(NULL);
															  pnfPlayerDied(backbuffer);
			  }
		  break; }

		  // Scene: A New Adventure Begins
		  case csNewAdventure: {
			  if			(loading)		  { loadNewAdventure(backbuffer); }
			  else if (destroying)  { destroyNewAdventure(backbuffer); }
			  else									{
															  backbuffer->SetClipper(NULL);
															  pnfNewAdventure(backbuffer);
			  }
		  break; }

		  // Scene: Player Won
		  case csWin: {
			  if			(loading)		  { loadWin(backbuffer); }
			  else if (destroying)  { destroyWin(backbuffer); }
			  else									{
															  backbuffer->SetClipper(NULL);
															  pnfWin(backbuffer);
				}
		  break; }

		  // Final Score
		  case csFinalScore: {
			  if			(loading)		  { loadFinalScore(backbuffer); }
			  else if (destroying)  { destroyFinalScore(backbuffer); }
			  else									{
															  backbuffer->SetClipper(NULL);
															  pnfFinalScore(backbuffer);
			  }
		  break; }

		  // Mini game: In Memoria
		  case csInMemoria: {
			  if			(loading)			{ loadInMemoria(backbuffer); }
			  else if (destroying)	{ destroyInMemoria(backbuffer); }
			  else {
				  switch (mini_game_state) {
					  case mgsInitialDraw: {
						  doInitialDraw(backbuffer);
					  break; }
					  case mgsInstructions: {
						  doInstructions(backbuffer); updateHands(backbuffer);
					  break; }
					  case mgsGetReady: {
						  doGetReady(backbuffer, TEXT("\"In Memoria\""), TEXT("250"));
					  break; }
					  case mgsGameOver: {
						  if (game_mode == gmMiniGameMelee) {
							  doGameOver(backbuffer, csNewGameType, 250);
						  } else {
							  doGameOver(backbuffer, csWalkingAroundTheShip, 250);
						  }
					  break; }
            case mgsEnding: { mini_game_state = mgsGameOver; break; }
					  case mgsGameRunning: {
              if (!force_game_over) {
						    if (clear_game_surface) { backbuffer->FillRect(CRect(20, 20, 220, 220), RGB(0, 0, 0), 0, NULL); }
                updateMiniGameFrameLights(backbuffer);
						    backbuffer->SetClipper(CRect(20, 20, 220, 220));
						    pnfInMemoria(backbuffer);
						    backbuffer->SetClipper(NULL);
              }
              updateHands(backbuffer);
						  if (updateStatusBar(backbuffer) || force_game_over) {
							  game_over_counter = 0;
							  mini_game_state = mgsEnding;
                processEvents = false;
						  }
					  break; }
				  }
			  }
		  break; }

		  // Mini game: Flight Of Doom
		  case csFlightOfDoom: {
			  if			(loading)			{ loadFlightOfDoom(backbuffer); }
			  else if (destroying)	{ destroyFlightOfDoom(backbuffer); }
			  else {
				  switch (mini_game_state) {
					  case mgsInitialDraw: {
						  doInitialDraw(backbuffer);
					  break; }
					  case mgsInstructions: {
						  doInstructions(backbuffer); updateHands(backbuffer);
					  break; }
					  case mgsGetReady: {
						  doGetReady(backbuffer, TEXT("\"Flight Of Doom\""), TEXT("2,000"));
					  break; }
					  case mgsGameOver: {
						  if (game_mode == gmMiniGameMelee) {
							  doGameOver(backbuffer, csNewGameType, 2000);
						  } else {
							  doGameOver(backbuffer, csWalkingAroundTheShip, 2000);
						  }
					  break; }
            case mgsEnding: { endFlightOfDoom(); mini_game_state = mgsGameOver; break; }
					  case mgsGameRunning: {
              if (!force_game_over) {
						    if (clear_game_surface) { backbuffer->FillRect(CRect(20, 20, 220, 220), RGB(0, 0, 0), 0, NULL); }
                updateMiniGameFrameLights(backbuffer);
						    backbuffer->SetClipper(CRect(20, 20, 220, 220));
						    pnfFlightOfDoom(backbuffer);
						    backbuffer->SetClipper(NULL);
              }
              updateHands(backbuffer);
						  if (updateStatusBar(backbuffer) || force_game_over) {
							  game_over_counter = 0;
							  mini_game_state = mgsEnding;
                processEvents = false;
						  }
					  break; }
				  }
			  }
		  break; }

		  // Mini game: Reluctant Hero
		  case csReluctantHero: {
			  if			(loading)			{ loadReluctantHero(backbuffer); }
			  else if (destroying)	{ destroyReluctantHero(backbuffer); }
			  else {
				  switch (mini_game_state) {
					  case mgsInitialDraw: {
						  doInitialDraw(backbuffer);
					  break; }
					  case mgsInstructions: {
						  doInstructions(backbuffer); updateHands(backbuffer);
					  break; }
					  case mgsGetReady: {
						  doGetReady(backbuffer, TEXT("\"Reluctant Hero\""), TEXT("600"));
					  break; }
					  case mgsGameOver: {
						  if (game_mode == gmMiniGameMelee) {
							  doGameOver(backbuffer, csNewGameType, 600);
						  } else {
							  doGameOver(backbuffer, csWalkingAroundTheShip, 600);
						  }
					  break; }
            case mgsEnding: { endReluctantHero(); mini_game_state = mgsGameOver; break; }
					  case mgsGameRunning: {
              if (!force_game_over) {
						    if (clear_game_surface) { backbuffer->FillRect(CRect(20, 20, 220, 220), RGB(0, 0, 0), 0, NULL); }
                updateMiniGameFrameLights(backbuffer);
						    backbuffer->SetClipper(CRect(20, 20, 220, 220));
						    pnfReluctantHero(backbuffer);
						    backbuffer->SetClipper(NULL);
              }
              updateHands(backbuffer);
						  if (updateStatusBar(backbuffer) || force_game_over) {
							  game_over_counter = 0;
							  mini_game_state = mgsEnding;
                processEvents = false;
						  }
					  break; }
				  }
			  }
		  break; }

		  // Mini game: Cosmic Squirrel
		  case csCosmicSquirrel: {
			  if			(loading)			{ loadCosmicSquirrel(backbuffer); }
			  else if (destroying)	{ destroyCosmicSquirrel(backbuffer); }
			  else {
				  switch (mini_game_state) {
					  case mgsInitialDraw: {
						  doInitialDraw(backbuffer);
					  break; }
					  case mgsInstructions: {
						  doInstructions(backbuffer); updateHands(backbuffer);
					  break; }
					  case mgsGetReady: {
						  doGetReady(backbuffer, TEXT("\"Cosmic Squirrel\""), TEXT("1,000"));
					  break; }
					  case mgsGameOver: {
						  if (game_mode == gmMiniGameMelee) {
							  doGameOver(backbuffer, csNewGameType, 1000);
						  } else {
							  doGameOver(backbuffer, csWalkingAroundTheShip, 1000);
						  }
					  break; }
            case mgsEnding: { endCosmicSquirrel(); mini_game_state = mgsGameOver; break; }
					  case mgsGameRunning: {
              if (!force_game_over) {
						    if (clear_game_surface) { backbuffer->FillRect(CRect(20, 20, 220, 220), RGB(0, 0, 0), 0, NULL); }
                updateMiniGameFrameLights(backbuffer);
						    backbuffer->SetClipper(CRect(20, 20, 220, 220));
						    pnfCosmicSquirrel(backbuffer);
						    backbuffer->SetClipper(NULL);
              }
              updateHands(backbuffer);
						  if (updateStatusBar(backbuffer) || force_game_over) {
							  game_over_counter = 0;
							  mini_game_state = mgsEnding;
                processEvents = false;
						  }
					  break; }
				  }
			  }
		  break; }

		  // Mini game: Refluxive
		  case csRefluxive: {
			  if			(loading)			{ loadRefluxive(backbuffer); }
			  else if (destroying)	{ destroyRefluxive(backbuffer); }
			  else {
				  switch (mini_game_state) {
					  case mgsInitialDraw: {
						  doInitialDraw(backbuffer);
					  break; }
					  case mgsInstructions: {
						  doInstructions(backbuffer); updateHands(backbuffer);
					  break; }
					  case mgsGetReady: {
						  doGetReady(backbuffer, TEXT("\"Refluxive\""), TEXT("350"));
					  break; }
					  case mgsGameOver: {
						  if (game_mode == gmMiniGameMelee) {
							  doGameOver(backbuffer, csNewGameType, 350);
						  } else {
							  doGameOver(backbuffer, csWalkingAroundTheShip, 350);
						  }
					  break; }
            case mgsEnding: { mini_game_state = mgsGameOver; break; }
					  case mgsGameRunning: {
              if (!force_game_over) {
						    if (clear_game_surface) { backbuffer->FillRect(CRect(20, 20, 220, 220), RGB(0, 0, 0), 0, NULL); }
                updateMiniGameFrameLights(backbuffer);
						    backbuffer->SetClipper(CRect(20, 20, 220, 220));
						    pnfRefluxive(backbuffer);
						    backbuffer->SetClipper(NULL);
              }
              updateHands(backbuffer);
						  if (updateStatusBar(backbuffer) || force_game_over) {
							  game_over_counter = 0;
							  mini_game_state = mgsEnding;
                processEvents = false;
						  }
					  break; }
				  }
			  }
		  break; }

		  // Mini game: Defendoh
		  case csDefendoh: {
			  if			(loading)			{ loadDefendoh(backbuffer); }
			  else if (destroying)	{ destroyDefendoh(backbuffer); }
			  else {
				  switch (mini_game_state) {
					  case mgsInitialDraw: {
						  doInitialDraw(backbuffer);
					  break; }
					  case mgsInstructions: {
						  doInstructions(backbuffer); updateHands(backbuffer);
					  break; }
					  case mgsGetReady: {
						  doGetReady(backbuffer, TEXT("\"Defen'DOH!\""), TEXT("250"));
					  break; }
					  case mgsGameOver: {
						  if (game_mode == gmMiniGameMelee) {
							  doGameOver(backbuffer, csNewGameType, 250);
						  } else {
							  doGameOver(backbuffer, csWalkingAroundTheShip, 250);
						  }
					  break; }
            case mgsEnding: { endDefendoh(); mini_game_state = mgsGameOver; break; }
					  case mgsGameRunning: {
              if (!force_game_over) {
						    if (clear_game_surface) { backbuffer->FillRect(CRect(20, 20, 220, 220), RGB(0, 0, 0), 0, NULL); }
                updateMiniGameFrameLights(backbuffer);
						    backbuffer->SetClipper(CRect(20, 20, 220, 220));
						    pnfDefendoh(backbuffer);
						    backbuffer->SetClipper(NULL);
              }
              updateHands(backbuffer);
						  if (updateStatusBar(backbuffer) || force_game_over) {
							  game_over_counter = 0;
							  mini_game_state = mgsEnding;
                processEvents = false;
						  }
					  break; }
				  }
			  }
		  break; }

		  // Mini game: A Day In The Strife
		  case csADayInTheStrife: {
			  if			(loading)			{ loadADayInTheStrife(backbuffer); }
			  else if (destroying)	{ destroyADayInTheStrife(backbuffer); }
			  else {
				  switch (mini_game_state) {
					  case mgsInitialDraw: {
						  doInitialDraw(backbuffer);
					  break; }
					  case mgsInstructions: {
						  doInstructions(backbuffer); updateHands(backbuffer);
					  break; }
					  case mgsGetReady: {
						  doGetReady(backbuffer, TEXT("\"A Day In The Strife\""), TEXT("1,000"));
					  break; }
					  case mgsGameOver: {
						  if (game_mode == gmMiniGameMelee) {
							  doGameOver(backbuffer, csNewGameType, 1000);
						  } else {
							  doGameOver(backbuffer, csWalkingAroundTheShip, 1000);
						  }
					  break; }
            case mgsEnding: { endADayInTheStrife(); mini_game_state = mgsGameOver; break; }
					  case mgsGameRunning: {
              if (!force_game_over) {
						    if (clear_game_surface) { backbuffer->FillRect(CRect(20, 20, 220, 220), RGB(0, 0, 0), 0, NULL); }
                updateMiniGameFrameLights(backbuffer);
						    backbuffer->SetClipper(CRect(20, 20, 220, 220));
						    pnfADayInTheStrife(backbuffer);
						    backbuffer->SetClipper(NULL);
              }
              updateHands(backbuffer);
						  if (updateStatusBar(backbuffer) || force_game_over) {
							  game_over_counter = 0;
							  mini_game_state = mgsEnding;
                processEvents = false;
						  }
					  break; }
				  }
			  }
		  break; }

		  // Mini game: Lepar Land
		  case csLeparLand: {
			  if			(loading)			{ loadLeparLand(backbuffer); }
			  else if (destroying)	{ destroyLeparLand(backbuffer); }
			  else {
				  switch (mini_game_state) {
					  case mgsInitialDraw: {
						  doInitialDraw(backbuffer);
					  break; }
					  case mgsInstructions: {
						  doInstructions(backbuffer); updateHands(backbuffer);
					  break; }
					  case mgsGetReady: {
						  doGetReady(backbuffer, TEXT("\"Lepar Land\""), TEXT("300"));
					  break; }
					  case mgsGameOver: {
						  if (game_mode == gmMiniGameMelee) {
							  doGameOver(backbuffer, csNewGameType, 300);
						  } else {
							  doGameOver(backbuffer, csWalkingAroundTheShip, 300);
						  }
					  break; }
            case mgsEnding: { endLeparLand(); mini_game_state = mgsGameOver; break; }
					  case mgsGameRunning: {
              if (!force_game_over) {
						    if (clear_game_surface) { backbuffer->FillRect(CRect(20, 20, 220, 220), RGB(0, 0, 0), 0, NULL); }
                updateMiniGameFrameLights(backbuffer);
						    backbuffer->SetClipper(CRect(20, 20, 220, 220));
						    pnfLeparLand(backbuffer);
						    backbuffer->SetClipper(NULL);
              }
              updateHands(backbuffer);
						  if (updateStatusBar(backbuffer) || force_game_over) {
							  game_over_counter = 0;
							  mini_game_state = mgsEnding;
                processEvents = false;
						  }
					  break; }
				  }
			  }
		  break; }

		  // Mini game: DeathTrap
		  case csDeathTrap: {
			  if			(loading)			{ loadDeathTrap(backbuffer); }
			  else if (destroying)	{ destroyDeathTrap(backbuffer); }
			  else {
				  switch (mini_game_state) {
					  case mgsInitialDraw: {
						  doInitialDraw(backbuffer);
					  break; }
					  case mgsInstructions: {
						  doInstructions(backbuffer); updateHands(backbuffer);
					  break; }
					  case mgsGetReady: {
						  doGetReady(backbuffer, TEXT("\"DeathTrap\""), TEXT("1,000"));
					  break; }
					  case mgsGameOver: {
						  if (game_mode == gmMiniGameMelee) {
							  doGameOver(backbuffer, csNewGameType, 1000);
						  } else {
							  doGameOver(backbuffer, csWalkingAroundTheShip, 1000);
						  }
					  break; }
            case mgsEnding: { mini_game_state = mgsGameOver; break; }
					  case mgsGameRunning: {
              if (!force_game_over) {
						    if (clear_game_surface) { backbuffer->FillRect(CRect(20, 20, 220, 220), RGB(0, 0, 0), 0, NULL); }
                updateMiniGameFrameLights(backbuffer);
						    backbuffer->SetClipper(CRect(20, 20, 220, 220));
						    pnfDeathTrap(backbuffer);
						    backbuffer->SetClipper(NULL);
              }
              updateHands(backbuffer);
						  if (updateStatusBar(backbuffer) || force_game_over) {
							  game_over_counter = 0;
							  mini_game_state = mgsEnding;
                processEvents = false;
						  }
					  break; }
				  }
			  }
		  break; }

		  // Mini game: CopyCat
		  case csCopyCat: {
			  if			(loading)			{ loadCopyCat(backbuffer); }
			  else if (destroying)	{ destroyCopyCat(backbuffer); }
			  else {
				  switch (mini_game_state) {
					  case mgsInitialDraw: {
						  doInitialDraw(backbuffer);
					  break; }
					  case mgsInstructions: {
						  doInstructions(backbuffer); updateHands(backbuffer);
					  break; }
					  case mgsGetReady: {
						  doGetReady(backbuffer, TEXT("\"CopyCat\""), TEXT("800"));
					  break; }
					  case mgsGameOver: {
						  if (game_mode == gmMiniGameMelee) {
							  doGameOver(backbuffer, csNewGameType, 800);
						  } else {
							  doGameOver(backbuffer, csWalkingAroundTheShip, 800);
						  }
					  break; }
            case mgsEnding: { mini_game_state = mgsGameOver; break; }
					  case mgsGameRunning: {
              if (!force_game_over) {
						    if (clear_game_surface) { backbuffer->FillRect(CRect(20, 20, 220, 220), RGB(0, 0, 0), 0, NULL); }
                updateMiniGameFrameLights(backbuffer);
						    backbuffer->SetClipper(CRect(20, 20, 220, 220));
						    pnfCopyCat(backbuffer);
						    backbuffer->SetClipper(NULL);
              }
              updateHands(backbuffer);
						  if (updateStatusBar(backbuffer) || force_game_over) {
							  game_over_counter = 0;
							  mini_game_state = mgsEnding;
                processEvents = false;
						  }
					  break; }
				  }
			  }
		  break; }

		  // Mini game: Virus
		  case csVirus: {
			  if			(loading)			{ loadVirus(backbuffer); }
			  else if (destroying)	{ destroyVirus(backbuffer); }
			  else {
				  switch (mini_game_state) {
					  case mgsInitialDraw: {
						  doInitialDraw(backbuffer);
					  break; }
					  case mgsInstructions: {
						  doInstructions(backbuffer); updateHands(backbuffer);
					  break; }
					  case mgsGetReady: {
						  doGetReady(backbuffer, TEXT("\"Virus\""), TEXT("2,000"));
					  break; }
					  case mgsGameOver: {
						  if (game_mode == gmMiniGameMelee) {
							  doGameOver(backbuffer, csNewGameType, 2000);
						  } else {
							  doGameOver(backbuffer, csWalkingAroundTheShip, 2000);
						  }
					  break; }
            case mgsEnding: { mini_game_state = mgsGameOver; break; }
					  case mgsGameRunning: {
              if (!force_game_over) {
						    if (clear_game_surface) { backbuffer->FillRect(CRect(20, 20, 220, 220), RGB(0, 0, 0), 0, NULL); }
                updateMiniGameFrameLights(backbuffer);
						    backbuffer->SetClipper(CRect(20, 20, 220, 220));
						    pnfVirus(backbuffer);
						    backbuffer->SetClipper(NULL);
              }
              updateHands(backbuffer);
						  if (updateStatusBar(backbuffer) || force_game_over) {
							  game_over_counter = 0;
							  mini_game_state = mgsEnding;
                processEvents = false;
						  }
					  break; }
				  }
			  }
		  break; }

		  // Mini game: Glutton
		  case csGlutton: {
			  if			(loading)			{ loadGlutton(backbuffer); }
			  else if (destroying)	{ destroyGlutton(backbuffer); }
			  else {
				  switch (mini_game_state) {
					  case mgsInitialDraw: {
						  doInitialDraw(backbuffer);
					  break; }
					  case mgsInstructions: {
						  doInstructions(backbuffer); updateHands(backbuffer);
					  break; }
					  case mgsGetReady: {
						  doGetReady(backbuffer, TEXT("\"Glutton\""), TEXT("500"));
					  break; }
					  case mgsGameOver: {
						  if (game_mode == gmMiniGameMelee) {
							  doGameOver(backbuffer, csNewGameType, 500);
						  } else {
							  doGameOver(backbuffer, csWalkingAroundTheShip, 500);
						  }
					  break; }
            case mgsEnding: { mini_game_state = mgsGameOver; break; }
					  case mgsGameRunning: {
              if (!force_game_over) {
						    if (clear_game_surface) { backbuffer->FillRect(CRect(20, 20, 220, 220), RGB(0, 0, 0), 0, NULL); }
                updateMiniGameFrameLights(backbuffer);
						    backbuffer->SetClipper(CRect(20, 20, 220, 220));
						    pnfGlutton(backbuffer);
						    backbuffer->SetClipper(NULL);
              }
              updateHands(backbuffer);
						  if (updateStatusBar(backbuffer) || force_game_over) {
							  game_over_counter = 0;
							  mini_game_state = mgsEnding;
                processEvents = false;
						  }
					  break; }
				  }
			  }
		  break; }

		  // Mini game: Conquerror
		  case csConquerror: {
			  if			(loading)			{ loadConquerror(backbuffer); }
			  else if (destroying)	{ destroyConquerror(backbuffer); }
			  else {
				  switch (mini_game_state) {
					  case mgsInitialDraw: {
						  doInitialDraw(backbuffer);
					  break; }
					  case mgsInstructions: {
						  doInstructions(backbuffer); updateHands(backbuffer);
					  break; }
					  case mgsGetReady: {
						  doGetReady(backbuffer, TEXT("\"Conquerror\""), TEXT("400"));
					  break; }
					  case mgsGameOver: {
						  if (game_mode == gmMiniGameMelee) {
							  doGameOver(backbuffer, csNewGameType, 400);
						  } else {
							  doGameOver(backbuffer, csWalkingAroundTheShip, 400);
						  }
					  break; }
            case mgsEnding: { mini_game_state = mgsGameOver; break; }
					  case mgsGameRunning: {
              if (!force_game_over) {
						    if (clear_game_surface) { backbuffer->FillRect(CRect(20, 20, 220, 220), RGB(0, 0, 0), 0, NULL); }
                updateMiniGameFrameLights(backbuffer);
						    backbuffer->SetClipper(CRect(20, 20, 220, 220));
						    pnfConquerror(backbuffer);
						    backbuffer->SetClipper(NULL);
              }
              updateHands(backbuffer);
						  if (updateStatusBar(backbuffer) || force_game_over) {
							  game_over_counter = 0;
							  mini_game_state = mgsEnding;
                processEvents = false;
						  }
					  break; }
				  }
			  }
		  break; }

		  // Mini game: Antigravitator
		  case csAntigravitator: {
			  if			(loading)			{ loadAntigravitator(backbuffer); }
			  else if (destroying)	{ destroyAntigravitator(backbuffer); }
			  else {
				  switch (mini_game_state) {
					  case mgsInitialDraw: {
						  doInitialDraw(backbuffer);
					  break; }
					  case mgsInstructions: {
						  doInstructions(backbuffer); updateHands(backbuffer);
					  break; }
					  case mgsGetReady: {
						  doGetReady(backbuffer, TEXT("\"Antigravitator\""), TEXT("600"));
					  break; }
					  case mgsGameOver: {
						  if (game_mode == gmMiniGameMelee) {
							  doGameOver(backbuffer, csNewGameType, 600);
						  } else {
							  doGameOver(backbuffer, csWalkingAroundTheShip, 600);
						  }
					  break; }
            case mgsEnding: { mini_game_state = mgsGameOver; break; }
					  case mgsGameRunning: {
              if (!force_game_over) {
						    if (clear_game_surface) { backbuffer->FillRect(CRect(20, 20, 220, 220), RGB(0, 0, 0), 0, NULL); }
                updateMiniGameFrameLights(backbuffer);
						    backbuffer->SetClipper(CRect(20, 20, 220, 220));
						    pnfAntigravitator(backbuffer);
						    backbuffer->SetClipper(NULL);
              }
              updateHands(backbuffer);
						  if (updateStatusBar(backbuffer) || force_game_over) {
							  game_over_counter = 0;
							  mini_game_state = mgsEnding;
                processEvents = false;
						  }
					  break; }
				  }
			  }
		  break; }

		  // Mini game: Far Out Fowl
		  case csFarOutFowl: {
			  if			(loading)			{ loadFarOutFowl(backbuffer); }
			  else if (destroying)	{ destroyFarOutFowl(backbuffer); }
			  else {
				  switch (mini_game_state) {
					  case mgsInitialDraw: {
						  doInitialDraw(backbuffer);
					  break; }
					  case mgsInstructions: {
						  doInstructions(backbuffer); updateHands(backbuffer);
					  break; }
					  case mgsGetReady: {
						  doGetReady(backbuffer, TEXT("\"Far Out Fowl\""), TEXT("500"));
					  break; }
					  case mgsGameOver: {
						  if (game_mode == gmMiniGameMelee) {
							  doGameOver(backbuffer, csNewGameType, 500);
						  } else {
							  doGameOver(backbuffer, csWalkingAroundTheShip, 500);
						  }
					  break; }
            case mgsEnding: { endFarOutFowl(); mini_game_state = mgsGameOver; break; }
					  case mgsGameRunning: {
              if (!force_game_over) {
						    if (clear_game_surface) { backbuffer->FillRect(CRect(20, 20, 220, 220), RGB(0, 0, 0), 0, NULL); }
                updateMiniGameFrameLights(backbuffer);
						    backbuffer->SetClipper(CRect(20, 20, 220, 220));
						    pnfFarOutFowl(backbuffer);
						    backbuffer->SetClipper(NULL);
              }
              updateHands(backbuffer);
						  if (updateStatusBar(backbuffer) || force_game_over) {
							  game_over_counter = 0;
							  mini_game_state = mgsEnding;
                processEvents = false;
						  }
					  break; }
				  }
			  }
		  break; }

		  // Mini game: The Escape
		  case csTheEscape: {
			  if			(loading)			{ loadTheEscape(backbuffer); }
			  else if (destroying)	{ destroyTheEscape(backbuffer); }
			  else {
				  switch (mini_game_state) {
					  case mgsInitialDraw: {
						  doInitialDraw(backbuffer);
					  break; }
					  case mgsInstructions: {
						  doInstructions(backbuffer); updateHands(backbuffer);
					  break; }
					  case mgsGetReady: {
						  doGetReady(backbuffer, TEXT("\"The Escape\""), TEXT("1,000"));
					  break; }
					  case mgsGameOver: {
						  if (game_mode == gmMiniGameMelee) {
							  doGameOver(backbuffer, csNewGameType, 1000);
						  } else {
							  doGameOver(backbuffer, csWalkingAroundTheShip, 1000);
						  }
					  break; }
            case mgsEnding: { mini_game_state = mgsGameOver; break; }
					  case mgsGameRunning: {
              if (!force_game_over) {
						    if (clear_game_surface) { backbuffer->FillRect(CRect(20, 20, 220, 220), RGB(0, 0, 0), 0, NULL); }
                updateMiniGameFrameLights(backbuffer);
						    backbuffer->SetClipper(CRect(20, 20, 220, 220));
						    pnfTheEscape(backbuffer);
						    backbuffer->SetClipper(NULL);
              }
              updateHands(backbuffer);
						  if (updateStatusBar(backbuffer) || force_game_over) {
							  game_over_counter = 0;
							  mini_game_state = mgsEnding;
                processEvents = false;
						  }
					  break; }
				  }
			  }
		  break; }

		  // Mini game: Alien Babble
		  case csAlienBabble: {
			  if			(loading)			{ loadAlienBabble(backbuffer); }
			  else if (destroying)	{ destroyAlienBabble(backbuffer); }
			  else {
				  switch (mini_game_state) {
					  case mgsInitialDraw: {
						  doInitialDraw(backbuffer);
					  break; }
					  case mgsInstructions: {
						  doInstructions(backbuffer); updateHands(backbuffer);
					  break; }
					  case mgsGetReady: {
						  doGetReady(backbuffer, TEXT("\"Alien Babble\""), TEXT("900"));
					  break; }
					  case mgsGameOver: {
						  if (game_mode == gmMiniGameMelee) {
							  doGameOver(backbuffer, csNewGameType, 900);
						  } else {
							  doGameOver(backbuffer, csWalkingAroundTheShip, 900);
						  }
					  break; }
            case mgsEnding: { endAlienBabble(); mini_game_state = mgsGameOver; break; }
					  case mgsGameRunning: {
              if (!force_game_over) {
						    if (clear_game_surface) { backbuffer->FillRect(CRect(20, 20, 220, 220), RGB(0, 0, 0), 0, NULL); }
                updateMiniGameFrameLights(backbuffer);
						    backbuffer->SetClipper(CRect(20, 20, 220, 220));
						    pnfAlienBabble(backbuffer);
						    backbuffer->SetClipper(NULL);
              }
              updateHands(backbuffer);
						  if (updateStatusBar(backbuffer) || force_game_over) {
							  game_over_counter = 0;
							  mini_game_state = mgsEnding;
                processEvents = false;
						  }
					  break; }
				  }
			  }
		  break; }

		  // Mini game: The Redeye Order
		  case csTheRedeyeOrder: {
			  if			(loading)			{ loadTheRedeyeOrder(backbuffer); }
			  else if (destroying)	{ destroyTheRedeyeOrder(backbuffer); }
			  else {
				  switch (mini_game_state) {
					  case mgsInitialDraw: {
						  doInitialDraw(backbuffer);
					  break; }
					  case mgsInstructions: {
						  doInstructions(backbuffer); updateHands(backbuffer);
					  break; }
					  case mgsGetReady: {
						  doGetReady(backbuffer, TEXT("\"The Redeye Order\""), TEXT("5,000"));
					  break; }
					  case mgsGameOver: {
						  if (game_mode == gmMiniGameMelee) {
							  doGameOver(backbuffer, csNewGameType, 5000);
						  } else {
							  doGameOver(backbuffer, csWalkingAroundTheShip, 5000);
						  }
					  break; }
            case mgsEnding: { mini_game_state = mgsGameOver; break; }
					  case mgsGameRunning: {
              if (!force_game_over) {
						    if (clear_game_surface) { backbuffer->FillRect(CRect(20, 20, 220, 220), RGB(0, 0, 0), 0, NULL); }
                updateMiniGameFrameLights(backbuffer);
						    backbuffer->SetClipper(CRect(20, 20, 220, 220));
						    pnfTheRedeyeOrder(backbuffer);
						    backbuffer->SetClipper(NULL);
              }
              updateHands(backbuffer);
						  if (updateStatusBar(backbuffer) || force_game_over) {
							  game_over_counter = 0;
							  mini_game_state = mgsEnding;
                processEvents = false;
						  }
					  break; }
				  }
			  }
		  break; }

		  // Mini game: Paehc Sirtet Ffopir
		  case csFfopirSirtetPaehc: {
			  if			(loading)			{ loadFfopirSirtetPaehc(backbuffer); }
			  else if (destroying)	{ destroyFfopirSirtetPaehc(backbuffer); }
			  else {
				  switch (mini_game_state) {
					  case mgsInitialDraw: {
						  doInitialDraw(backbuffer);
					  break; }
					  case mgsInstructions: {
						  doInstructions(backbuffer); updateHands(backbuffer);
					  break; }
					  case mgsGetReady: {
						  doGetReady(backbuffer, TEXT("\"Paehc Sirtet Ffopir\""), TEXT("200"));
					  break; }
					  case mgsGameOver: {
						  if (game_mode == gmMiniGameMelee) {
							  doGameOver(backbuffer, csNewGameType, 200);
						  } else {
							  doGameOver(backbuffer, csWalkingAroundTheShip, 200);
						  }
					  break; }
            case mgsEnding: { mini_game_state = mgsGameOver; break; }
					  case mgsGameRunning: {
              if (!force_game_over) {
						    if (clear_game_surface) { backbuffer->FillRect(CRect(20, 20, 220, 220), RGB(0, 0, 0), 0, NULL); }
                updateMiniGameFrameLights(backbuffer);
						    backbuffer->SetClipper(CRect(20, 20, 220, 220));
						    pnfFfopirSirtetPaehc(backbuffer);
						    backbuffer->SetClipper(NULL);
              }
              updateHands(backbuffer);
						  if (updateStatusBar(backbuffer) || force_game_over) {
							  game_over_counter = 0;
							  mini_game_state = mgsEnding;
                processEvents = false;
						  }
					  break; }
				  }
			  }
		  break; }

		  // Mini game: Engineer
		  case csEngineer: {
			  if			(loading)			{ loadEngineer(backbuffer); }
			  else if (destroying)	{ destroyEngineer(backbuffer); }
			  else {
				  switch (mini_game_state) {
					  case mgsInitialDraw: {
						  doInitialDraw(backbuffer);
					  break; }
					  case mgsInstructions: {
						  doInstructions(backbuffer); updateHands(backbuffer);
					  break; }
					  case mgsGetReady: {
						  doGetReady(backbuffer, TEXT("\"Engineer\""), TEXT("500"));
					  break; }
					  case mgsGameOver: {
						  if (game_mode == gmMiniGameMelee) {
							  doGameOver(backbuffer, csNewGameType, 500);
						  } else {
							  doGameOver(backbuffer, csWalkingAroundTheShip, 500);
						  }
					  break; }
            case mgsEnding: { mini_game_state = mgsGameOver; break; }
					  case mgsGameRunning: {
              if (!force_game_over) {
						    if (clear_game_surface) { backbuffer->FillRect(CRect(20, 20, 220, 220), RGB(0, 0, 0), 0, NULL); }
                updateMiniGameFrameLights(backbuffer);
						    backbuffer->SetClipper(CRect(20, 20, 220, 220));
						    pnfEngineer(backbuffer);
						    backbuffer->SetClipper(NULL);
              }
              updateHands(backbuffer);
						  if (updateStatusBar(backbuffer) || force_game_over) {
							  game_over_counter = 0;
							  mini_game_state = mgsEnding;
                processEvents = false;
						  }
					  break; }
				  }
			  }
		  break; }

		  // Mini game: The Bogaz Derby
		  case csTheBogazDerby: {
			  if			(loading)			{ loadTheBogazDerby(backbuffer); }
			  else if (destroying)	{ destroyTheBogazDerby(backbuffer); }
			  else {
				  switch (mini_game_state) {
					  case mgsInitialDraw: {
						  doInitialDraw(backbuffer);
					  break; }
					  case mgsInstructions: {
						  doInstructions(backbuffer); updateHands(backbuffer);
					  break; }
					  case mgsGetReady: {
						  doGetReady(backbuffer, TEXT("\"The Bogaz Derby\""), TEXT("200"));
					  break; }
					  case mgsGameOver: {
						  if (game_mode == gmMiniGameMelee) {
							  doGameOver(backbuffer, csNewGameType, 200);
						  } else {
							  doGameOver(backbuffer, csWalkingAroundTheShip, 200);
						  }
					  break; }
            case mgsEnding: { endTheBogazDerby(); mini_game_state = mgsGameOver; break; }
					  case mgsGameRunning: {
              if (!force_game_over) {
						    if (clear_game_surface) { backbuffer->FillRect(CRect(20, 20, 220, 220), RGB(0, 0, 0), 0, NULL); }
                updateMiniGameFrameLights(backbuffer);
						    backbuffer->SetClipper(CRect(20, 20, 220, 220));
						    pnfTheBogazDerby(backbuffer);
						    backbuffer->SetClipper(NULL);
              }
              updateHands(backbuffer);
						  if (updateStatusBar(backbuffer) || force_game_over) {
							  game_over_counter = 0;
							  mini_game_state = mgsEnding;
                processEvents = false;
						  }
					  break; }
				  }
			  }
		  break; }

		  // Mini game: Squish'em
		  case csSquishem: {
			  if			(loading)			{ loadSquishem(backbuffer); }
			  else if (destroying)	{ destroySquishem(backbuffer); }
			  else {
				  switch (mini_game_state) {
					  case mgsInitialDraw: {
						  doInitialDraw(backbuffer);
					  break; }
					  case mgsInstructions: {
						  doInstructions(backbuffer); updateHands(backbuffer);
					  break; }
					  case mgsGetReady: {
						  doGetReady(backbuffer, TEXT("\"Squish'em\""), TEXT("500"));
					  break; }
					  case mgsGameOver: {
						  if (game_mode == gmMiniGameMelee) {
							  doGameOver(backbuffer, csNewGameType, 500);
						  } else {
							  doGameOver(backbuffer, csWalkingAroundTheShip, 500);
						  }
					  break; }
            case mgsEnding: { mini_game_state = mgsGameOver; break; }
					  case mgsGameRunning: {
              if (!force_game_over) {
						    if (clear_game_surface) { backbuffer->FillRect(CRect(20, 20, 220, 220), RGB(0, 0, 0), 0, NULL); }
                updateMiniGameFrameLights(backbuffer);
						    backbuffer->SetClipper(CRect(20, 20, 220, 220));
						    pnfSquishem(backbuffer);
						    backbuffer->SetClipper(NULL);
              }
              updateHands(backbuffer);
						  if (updateStatusBar(backbuffer) || force_game_over) {
							  game_over_counter = 0;
							  mini_game_state = mgsEnding;
                processEvents = false;
						  }
					  break; }
				  }
			  }
		  break; }

		  // Mini game: Trouble In Vectropolis
		  case csTroubleInVectropolis: {
			  if			(loading)			{ loadTroubleInVectropolis(backbuffer); }
			  else if (destroying)	{ destroyTroubleInVectropolis(backbuffer); }
			  else {
				  switch (mini_game_state) {
					  case mgsInitialDraw: {
						  doInitialDraw(backbuffer);
					  break; }
					  case mgsInstructions: {
						  doInstructions(backbuffer); updateHands(backbuffer);
					  break; }
					  case mgsGetReady: {
						  doGetReady(backbuffer, TEXT("\"Trouble In Vectropolis\""), TEXT("350"));
					  break; }
					  case mgsGameOver: {
						  if (game_mode == gmMiniGameMelee) {
							  doGameOver(backbuffer, csNewGameType, 350);
						  } else {
							  doGameOver(backbuffer, csWalkingAroundTheShip, 350);
						  }
					  break; }
            case mgsEnding: { endTroubleInVectropolis(); mini_game_state = mgsGameOver; break; }
					  case mgsGameRunning: {
              if (!force_game_over) {
						    if (clear_game_surface) { backbuffer->FillRect(CRect(20, 20, 220, 220), RGB(0, 0, 0), 0, NULL); }
                updateMiniGameFrameLights(backbuffer);
						    backbuffer->SetClipper(CRect(20, 20, 220, 220));
						    pnfTroubleInVectropolis(backbuffer);
						    backbuffer->SetClipper(NULL);
              }
              updateHands(backbuffer);
						  if (updateStatusBar(backbuffer) || force_game_over) {
							  game_over_counter = 0;
							  mini_game_state = mgsEnding;
                processEvents = false;
						  }
					  break; }
				  }
			  }
		  break; }

		  // Mini game: Muncher Dude
		  case csMuncherDude: {
			  if			(loading)			{ loadMuncherDude(backbuffer); }
			  else if (destroying)	{ destroyMuncherDude(backbuffer); }
			  else {
				  switch (mini_game_state) {
					  case mgsInitialDraw: {
						  doInitialDraw(backbuffer);
					  break; }
					  case mgsInstructions: {
						  doInstructions(backbuffer); updateHands(backbuffer);
					  break; }
					  case mgsGetReady: {
						  doGetReady(backbuffer, TEXT("\"Muncher Dude\""), TEXT("750"));
					  break; }
					  case mgsGameOver: {
						  if (game_mode == gmMiniGameMelee) {
							  doGameOver(backbuffer, csNewGameType, 750);
						  } else {
							  doGameOver(backbuffer, csWalkingAroundTheShip, 750);
						  }
					  break; }
            case mgsEnding: { endMuncherDude(); mini_game_state = mgsGameOver; break; }
					  case mgsGameRunning: {
              if (!force_game_over) {
						    if (clear_game_surface) { backbuffer->FillRect(CRect(20, 20, 220, 220), RGB(0, 0, 0), 0, NULL); }
                updateMiniGameFrameLights(backbuffer);
						    backbuffer->SetClipper(CRect(20, 20, 220, 220));
						    pnfMuncherDude(backbuffer);
						    backbuffer->SetClipper(NULL);
              }
              updateHands(backbuffer);
						  if (updateStatusBar(backbuffer) || force_game_over) {
							  game_over_counter = 0;
							  mini_game_state = mgsEnding;
                processEvents = false;
						  }
					  break; }
				  }
			  }
		  break; }

		  // Mini game: Son Of Eliminator
		  case csSonOfEliminator: {
			  if			(loading)			{ loadSonOfEliminator(backbuffer); }
			  else if (destroying)	{ destroySonOfEliminator(backbuffer); }
			  else {
				  switch (mini_game_state) {
					  case mgsInitialDraw: {
						  doInitialDraw(backbuffer);
					  break; }
					  case mgsInstructions: {
						  doInstructions(backbuffer); updateHands(backbuffer);
					  break; }
					  case mgsGetReady: {
						  doGetReady(backbuffer, TEXT("\"Son Of Eliminator\""), TEXT("300"));
					  break; }
					  case mgsGameOver: {
						  if (game_mode == gmMiniGameMelee) {
							  doGameOver(backbuffer, csNewGameType, 300);
						  } else {
							  doGameOver(backbuffer, csWalkingAroundTheShip, 300);
						  }
					  break; }
            case mgsEnding: { mini_game_state = mgsGameOver; break; }
					  case mgsGameRunning: {
              if (!force_game_over) {
						    if (clear_game_surface) { backbuffer->FillRect(CRect(20, 20, 220, 220), RGB(0, 0, 0), 0, NULL); }
                updateMiniGameFrameLights(backbuffer);
						    backbuffer->SetClipper(CRect(20, 20, 220, 220));
						    pnfSonOfEliminator(backbuffer);
						    backbuffer->SetClipper(NULL);
              }
              updateHands(backbuffer);
						  if (updateStatusBar(backbuffer) || force_game_over) {
							  game_over_counter = 0;
							  mini_game_state = mgsEnding;
                processEvents = false;
						  }
					  break; }
				  }
			  }
		  break; }

    } // End SWITCH

  } // End IF

	if (show_fps) {
		// FPS
		FLOAT fps;
		m_pTimer->GetActualFrameRate(&fps);
		TCHAR szFPS[18];
		_stprintf(szFPS, TEXT("%.0f"), fps);
		backbuffer->FillRect(CRect(0, 0, 22, 16), RGB(0, 0, 0), 0, NULL);
		backbuffer->DrawText(0, -4, szFPS, &font1, GDDRAWTEXT_LEFT, NULL, NULL, NULL);
	}

	if (show_frame_time) {
		// Frame Time
		FLOAT ft;
		m_pTimer->GetActualFrameTime(&ft);
		TCHAR szFT[18];
		_stprintf(szFT, TEXT("%.0f"), ft);
		backbuffer->FillRect(CRect(218, 0, 240, 16), RGB(0, 0, 0), 0, NULL);
		backbuffer->DrawText(240, -4, szFT, &font1, GDDRAWTEXT_RIGHT, NULL, NULL, NULL);
	}

	return S_OK;

}