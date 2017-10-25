
#include "main.h"


// ****************************************************************************************************************
// KeyDown handler
// ****************************************************************************************************************
HRESULT CGame::KeyDown(DWORD dwKey, GDKEYLIST& keylist) {

  if (mini_game_state == mgsInstructions) {
    kdMGInstructions(dwKey);
    return S_OK;
  }

  if (doPopup) {
    kdPopup(dwKey);
    return S_OK;
  }

  if (shutdownStep > 0) {
    shutdownStep++;
    return S_OK;
  }

  if (processEvents) {

	  switch (current_screen) {

		  // Main Menu
		  case csMainMenu: {
			  kdMainMenu(dwKey);
		  break; }

		  // Instructions
		  case csInstructions: {
			  kdInstructions(dwKey);
		  break; }

		  // Options
		  case csOptions: {
			  kdOptions(dwKey);
		  break; }

		  // New Game Type
		  case csNewGameType: {
			  kdNewGameType(dwKey);
		  break; }

		  // Walking around the ship
		  case csWalkingAroundTheShip: {
			  kdWalkingAroundTheShip(dwKey);
		  break; }

		  // Character Interaction
		  case csCharacterInteraction: {
			  kdCharacterInteraction(dwKey);
		  break; }

		  // Mini game: In Memoria
			case csInMemoria: {
			  kdInMemoria(dwKey);
		  break; }

		  // Mini game: Flight Of Doom
		  case csFlightOfDoom: {
			  kdFlightOfDoom(dwKey);
		  break; }

		  // Mini game: Reluctant Hero
			case csReluctantHero: {
			  kdReluctantHero(dwKey);
		  break; }

		  // Mini game: Refluxive
			case csRefluxive: {
			  kdRefluxive(dwKey);
		  break; }

		  // Mini game: Cosmic Squirrel
		  case csCosmicSquirrel: {
			  kdCosmicSquirrel(dwKey);
		  break; }

		  // Mini game: Defen'DOH!
			case csDefendoh: {
			  kdDefendoh(dwKey);
		  break; }

		  // Mini game: A Day In The Strife
		  case csADayInTheStrife: {
			  kdADayInTheStrife(dwKey);
		  break; }

		  // Mini game: Lepar Land
			case csLeparLand: {
			  kdLeparLand(dwKey);
		  break; }

		  // Mini game: CopyCat
		  case csCopyCat: {
			  kdCopyCat(dwKey);
		  break; }

		  // Mini game: Virus
			case csVirus: {
			  kdVirus(dwKey);
		  break; }

		  // Mini game: Glutton
			case csGlutton: {
			  kdGlutton(dwKey);
		  break; }

		  // Mini game: Conquerror
			case csConquerror: {
			  kdConquerror(dwKey);
		  break; }

		  // Mini game: Antigravitator
			case csAntigravitator: {
			  kdAntigravitator(dwKey);
		  break; }

		  // Mini game: Far Out Fowl
			case csFarOutFowl: {
			  kdFarOutFowl(dwKey);
		  break; }

		  // Mini game: The Escape
			case csTheEscape: {
			  kdTheEscape(dwKey);
		  break; }

		  // Mini game: Alien Babble
		  case csAlienBabble: {
			  kdAlienBabble(dwKey);
		  break; }

		  // Mini game: The Redeye Order
		  case csTheRedeyeOrder: {
			  kdTheRedeyeOrder(dwKey);
		  break; }

		  // Mini game: Ffopir Sirtet Paehc
		  case csFfopirSirtetPaehc: {
			  kdFfopirSirtetPaehc(dwKey);
		  break; }

		  // Mini game: Engineer
		  case csEngineer: {
			  kdEngineer(dwKey);
		  break; }

		  // Mini game: The Bogaz Derby
		  case csTheBogazDerby: {
			  kdTheBogazDerby(dwKey);
		  break; }

		  // Mini game: Squisk'em
		  case csSquishem: {
			  kdSquishem(dwKey);
		  break; }

		  // Mini game: Trouble In Vectropolis
		  case csTroubleInVectropolis: {
			  kdTroubleInVectropolis(dwKey);
		  break; }

		  // Mini game: Muncher Dude
		  case csMuncherDude: {
			  kdMuncherDude(dwKey);
		  break; }

		  // Mini game: Son Of Eliminator
		  case csSonOfEliminator: {
			  kdSonOfEliminator(dwKey);
		  break; }

	  }

  }

	return S_OK;

}


// ****************************************************************************************************************
// KeyUp handler
// ****************************************************************************************************************
HRESULT CGame::KeyUp(DWORD dwKey, GDKEYLIST& keylist) {

  if (mini_game_state == mgsInstructions) {
    kuMGInstructions(dwKey);
    return GD_OK;
  }

  if (doPopup) {
    kuPopup(dwKey);
    return S_OK;
  }

  if (processEvents) {

	  switch (current_screen) {

		  // Scene: Player Died
		  case csPlayerDied: {
			  kuPlayerDied();
		  break; }

		  // Scene: A New Adventure Begins
      case csNewAdventure: {
			  kuNewAdventure();
		  break; }

		  // Scene: Win
		  case csWin: {
			  kuWin();
		  break; }

		  // Final Score
		  case csFinalScore: {
			  kuFinalScore(dwKey);
		  break; }

		  // Intro: Clickgamer
		  case csIntroClickgamer: {
			  kuIntroClickgamer();
		  break; }

		  // Intro: Omnytex
		  case csIntroOmnytex: {
			  kuIntroOmnytex();
		  break; }

		  // Intro: Crackhead
		  case csIntroCrackhead: {
			  kuIntroCrackhead();
		  break; }

		  // Title
		  case csTitleSequence: {
			  kuTitleSequence();
		  break; }

		  // Main Menu
		  case csMainMenu: {
			  kuMainMenu(dwKey);
		  break; }

		  // Credits
		  case csCredits: {
			  kuCredits(dwKey);
		  break; }

		  // Instructions
		  case csInstructions: {
			  kuInstructions(dwKey);
		  break; }

		  // High Scores
		  case csHighScores: {
			  kuHighScores(dwKey);
		  break; }

		  // Options
		  case csOptions: {
			  kuOptions(dwKey);
		  break; }

		  // New Game Type
		  case csNewGameType: {
			  kuNewGameType(dwKey);
		  break; }

		  // Walking around the ship
		  case csWalkingAroundTheShip: {
			  kuWalkingAroundTheShip(dwKey);
		  break; }

		  // Character Interaction
		  case csCharacterInteraction: {
			  kuCharacterInteraction(dwKey);
		  break; }

		  // Mini game: In Memoria
		  case csInMemoria: {
			  kuInMemoria(dwKey);
		  break; }

		  // Mini game: Flight Of Doom
		  case csFlightOfDoom: {
			  kuFlightOfDoom(dwKey);
		  break; }

		  // Mini game: Reluctant Hero
		  case csReluctantHero: {
			  kuReluctantHero(dwKey);
		  break; }

		  // Mini game: Refluxive
			case csRefluxive: {
			  kuRefluxive(dwKey);
		  break; }

		  // Mini game: Cosmic Squirrel
		  case csCosmicSquirrel: {
			  kuCosmicSquirrel(dwKey);
		  break; }

		  // Mini game: Defen'DOH!
		  case csDefendoh: {
			  kuDefendoh(dwKey);
		  break; }

		  // Mini game: A Day In The Strife
		  case csADayInTheStrife: {
			  kuADayInTheStrife(dwKey);
		  break; }

		  // Mini game: Lepar Land
		  case csLeparLand: {
			  kuLeparLand(dwKey);
		  break; }

		  // Mini game: DeathTrap
		  case csDeathTrap: {
			  kuDeathTrap(dwKey);
		  break; }

		  // Mini game: CopyCat
		  case csCopyCat: {
			  kuCopyCat(dwKey);
		  break; }

		  // Mini game: Virus
		  case csVirus: {
			  kuVirus(dwKey);
		  break; }

		  // Mini game: Glutton
		  case csGlutton: {
			  kuGlutton(dwKey);
		  break; }

		  // Mini game: Conquerror
		  case csConquerror: {
			  kuConquerror(dwKey);
		  break; }

		  // Mini game: Antigravitator
		  case csAntigravitator: {
			  kuAntigravitator(dwKey);
		  break; }

		  // Mini game: Far Out Fowl
		  case csFarOutFowl: {
			  kuFarOutFowl(dwKey);
		  break; }

		  // Mini game: The Escape
		  case csTheEscape: {
			  kuTheEscape(dwKey);
		  break; }

		  // Mini game: Alien Babble
		  case csAlienBabble: {
			  kuAlienBabble(dwKey);
		  break; }

		  // Mini game: The Redeye Order
		  case csTheRedeyeOrder: {
			  kuTheRedeyeOrder(dwKey);
		  break; }

		  // Mini game: Ffopir Sirtet Paehc
		  case csFfopirSirtetPaehc: {
			  kuFfopirSirtetPaehc(dwKey);
		  break; }

		  // Mini game: Engineer
		  case csEngineer: {
			  kuEngineer(dwKey);
		  break; }

		  // Mini game: The Bogaz Derby
			case csTheBogazDerby: {
			  kuTheBogazDerby(dwKey);
		  break; }

		  // Mini game: Squisk'em
			case csSquishem: {
			  kuSquishem(dwKey);
		  break; }

		  // Mini game: Trouble In Vectropolis
			case csTroubleInVectropolis: {
			  kuTroubleInVectropolis(dwKey);
		  break; }

		  // Mini game: Muncher Dude
			case csMuncherDude: {
			  kuMuncherDude(dwKey);
		  break; }

		  // Mini game: Son Of Eliminator
			case csSonOfEliminator: {
			  kuSonOfEliminator(dwKey);
		  break; }

	  }

  }

	return S_OK;

}


// ****************************************************************************************************************
// StylusDown Handler
// ****************************************************************************************************************
HRESULT CGame::StylusDown(POINT p) {

  if (mini_game_state == mgsInstructions) {
    sdMGInstructions(p);
    return S_OK;
  }

  if (doPopup) {
    sdPopup(p);
    return S_OK;
  }

  if (shutdownStep > 0) {
    shutdownStep++;
  }

	if (processEvents) {

		switch (current_screen) {

		  // Character Interaction
		  case csCharacterInteraction: {
			  sdCharacterInteraction(p);
		  break; }

			// Options
			case csOptions: {
				sdOptions(p);
			break; }

			// Instructions
			case csInstructions: {
				sdInstructions(p);
			break; }

			// Main Menu
			case csMainMenu: {
				sdMainMenu(p);
			break; }

			// New Game Type
			case csNewGameType: {
				bool wasACorner = false;
				if (!(unlockCornerUL == 3 && unlockCornerUR == 3)) {
					if (PtInRect(CRect(0,   0,   20,  20),  p)) { unlockCornerUL++; wasACorner = true; if (unlockCornerUL > 3) { unlockCornerUL = 3; }  }
					if (PtInRect(CRect(220, 0,   240, 20),  p)) { unlockCornerUR++; wasACorner = true; if (unlockCornerUR > 3) { unlockCornerUR = 3; }  }
					if (wasACorner) {
						if (unlockCornerUL == 3 && unlockCornerUR == 3) {
							sndObj.playSound(sfxUnlockCode);
							for (int i = 0; i < 25; i++) { game_unlocked[i] = true; }
						}
					}
				}
				if (!wasACorner) {
					sdNewGameType(p);
				}

			break; }

		}

	}

  return S_OK;

}


// ****************************************************************************************************************
// StylusUp Handler
// ****************************************************************************************************************
HRESULT CGame::StylusUp(POINT p) {

  if (mini_game_state == mgsInstructions) {
    suMGInstructions(p);
    return S_OK;
  }

  if (doPopup) {
    suPopup(p);
    return S_OK;
  }

	if (processEvents) {

		switch (current_screen) {

		  // Character Interaction
		  case csCharacterInteraction: {
			  suCharacterInteraction(p);
		  break; }

			// New game type
			case csNewGameType: {
				suNewGameType(p);
			break; }

			// Credits
			case csCredits: {
				suCredits(p);
			break; }

			// High Scores
			case csHighScores: {
				suHighScores(p);
			break; }

			// Options
			case csOptions: {
				suOptions(p);
			break; }

			// Instructions
			case csInstructions: {
				suInstructions(p);
			break; }

			// Main Menu
			case csMainMenu: {
				suMainMenu(p);
			break; }

			// Intro: Clickgamer
			case csIntroClickgamer: {
				suIntroClickgamer();
			break; }

			// Intro: Omnytex
			case csIntroOmnytex: {
				suIntroOmnytex();
			break; }

			// Intro: Crackhead
			case csIntroCrackhead: {
				suIntroCrackhead();
			break; }

			// Title Sequence
			case csTitleSequence: {
				suTitleSequence();
			break; }

		  // Scene: A New Adventure Begins
      case csNewAdventure: {
			  suNewAdventure();
		  break; }

		  // Scene: Win
		  case csWin: {
			  suWin();
		  break; }

		  // Scene: Player died
		  case csPlayerDied: {
			  suPlayerDied();
		  break; }

		  // Final Score
		  case csFinalScore: {
			  suFinalScore(p);
		  break; }

		}

	}

  return S_OK;

}
