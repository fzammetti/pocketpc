
// Button Down Handler
void InvasionTrivia::ButtonDown(int key) {

	if (ProcessEvents) {

		switch (currentScreen) {

			// ***** Congratulations Screen *****
			case csCongratulationsScreen: {
				keyDownCongratulationsScreen(key);
			break; }
			// ***** Intro Screen *****
			case csIntroScreen: {
				keyDownIntroScreen(key);
			break; }
			// ***** Title Scene *****
			case csTitleScene: {
				keyDownTitleScene(key);
			break; }
			// ***** Beam A Brelnar Scene *****
			case csBeamABrelnarScene: {
				keyDownBeamABrelnarScene(key);
			break; }
			// ***** Ask The Abdromedans Scene *****
			case csAskTheAndromedansScene: {
				keyDownAskTheAndromedansScene(key);
			break; }
			// ***** Matter-Antimatter Scene *****
			case csMatterAntimatterScene: {
				keyDownMatterAntimatterScene(key);
			break; }
			// ***** Book Of Knowledge Scene *****
			case csBookOfKnowledgeScene: {
				keyDownBookOfKnowledgeScene(key);
			break; }
			// ***** Main Menu Screen *****
			case csMainMenuScreen: {
				keyDownMainMenuScreen(key);
			break; }
			// ***** Instructions Screen *****
			case csInstructionsScreen: {
				keyDownInstructionsScreen(key);
			break; }
			// ***** High Scores Screen *****
			case csHighScoresScreen: {
				keyDownHighScoresScreen(key);
			break; }
			// ***** Settings Screen *****
			case csSettingsScreen: {
				keyDownSettingsScreen(key);
			break; }
			// ***** Character Select Screen *****
			case csCharacterSelectScreen: {
				keyDownCharacterSelectScreen(key);
			break; }
				// ***** Point Levels Screen *****
			case csPointLevelsScreen: {
				keyDownPointLevelsScreen(key);
			break; }
			// ***** Credits Screen *****
			case csCreditsScreen: {
				keyDownCreditsScreen(key);
			break; }
			// ***** Answer Screen *****
			case csAnswerScreen: {
				keyDownAnswerScreen(key);
			break; }
			// ***** St. Louis Destruction Scene *****
			case csStLouisDestructionScene: {
				keyDownDestructionStLouisScene(key);
			break; }
			// ***** Tokyo Destruction Scene *****
			case csTokyoDestructionScene: {
				keyDownDestructionTokyoScene(key);
			break; }
			// ***** Rome Destruction Scene *****
			case csRomeDestructionScene: {
				keyDownDestructionRomeScene(key);
			break; }
			// ***** Pisa Destruction Scene *****
			case csPisaDestructionScene: {
				keyDownDestructionPisaScene(key);
			break; }
			// ***** Paris Destruction Scene *****
			case csParisDestructionScene: {
				keyDownDestructionParisScene(key);
			break; }
			// ***** Moscow Destruction Scene *****
			case csMoscowDestructionScene: {
				keyDownDestructionMoscowScene(key);
			break; }
			// ***** London Destruction Scene *****
			case csLondonDestructionScene: {
				keyDownDestructionLondonScene(key);
			break; }
			// ***** Giza Destruction Scene *****
			case csGizaDestructionScene: {
				keyDownDestructionGizaScene(key);
			break; }
			// ***** World Destruction 1 Scene *****
			case csWorldDestruction1Scene: {
				keyDownWorldDestruction1Scene(key);
			break; }
			// ***** World Destruction 2 Scene *****
			case csWorldDestruction2Scene: {
				keyDownWorldDestruction2Scene(key);
			break; }
			// ***** World Destruction 3 Scene *****
			case csWorldDestruction3Scene: {
				keyDownWorldDestruction3Scene(key);
			break; }
			// ***** World Destruction 4 Scene *****
			case csWorldDestruction4Scene: {
				keyDownWorldDestruction4Scene(key);
			break; }
			// ***** World Destruction 5 Scene *****
			case csWorldDestruction5Scene: {
				keyDownWorldDestruction5Scene(key);
			break; }
			// ***** Start Game Intro 1 Scene *****
			case csStartGameIntro1Scene: {
				keyDownStartGameIntro1Scene(key);
			break; }
			// ***** Start Game Intro 2 Scene *****
			case csStartGameIntro2Scene: {
				keyDownStartGameIntro2Scene(key);
			break; }
			// ***** Start Game Intro 3 Scene *****
			case csStartGameIntro3Scene: {
				keyDownStartGameIntro3Scene(key);
			break; }
			// ***** Start Game Intro 4 Scene *****
			case csStartGameIntro4Scene: {
				keyDownStartGameIntro4Scene(key);
			break; }
			// ***** Start Game Intro 5 Scene *****
			case csStartGameIntro5Scene: {
				keyDownStartGameIntro5Scene(key);
			break; }
			// ***** Correct Answer 1 Scene *****
			case csCorrectAnswer1Scene: {
				keyDownCorrectAnswer1Scene(key);
			break; }
			// ***** Correct Answer 2 Scene *****
			case csCorrectAnswer2Scene: {
				keyDownCorrectAnswer2Scene(key);
			break; }
			// ***** Correct Answer 3 Scene *****
			case csCorrectAnswer3Scene: {
				keyDownCorrectAnswer3Scene(key);
			break; }
			// ***** Correct Answer 4 Scene *****
			case csCorrectAnswer4Scene: {
				keyDownCorrectAnswer4Scene(key);
			break; }
			// ***** Correct Answer 5 Scene *****
			case csCorrectAnswer5Scene: {
				keyDownCorrectAnswer5Scene(key);
			break; }
			// ***** Player Wims 1 Scene *****
			case csPlayerWins1Scene: {
				keyDownPlayerWins1Scene(key);
			break; }
			// ***** Player Wims 2 Scene *****
			case csPlayerWins2Scene: {
				keyDownPlayerWins2Scene(key);
			break; }
			// ***** Player Wims 3 Scene *****
			case csPlayerWins3Scene: {
				keyDownPlayerWins3Scene(key);
			break; }
			// ***** Player Wims 4 Scene *****
			case csPlayerWins4Scene: {
				keyDownPlayerWins4Scene(key);
			break; }
			// ***** Player Wims 5 Scene *****
			case csPlayerWins5Scene: {
				keyDownPlayerWins5Scene(key);
			break; }

		} // End Switch
	
	} // End IF

} // End ButtonDownHandler


// Button Up Handler
void InvasionTrivia::ButtonUp(int key) {

	if (ProcessEvents) {

		switch (currentScreen) {

			// ***** Congratulations Screen *****
			case csCongratulationsScreen: {
				keyUpCongratulationsScreen(key);
			break; }
			// ***** Intro Screen *****
			case csIntroScreen: {
				keyUpIntroScreen(key);
			break; }
			// ***** Title Scene *****
			case csTitleScene: {
				keyUpTitleScene(key);
			break; }
			// ***** Beam A Brelnar Scene *****
			case csBeamABrelnarScene: {
				keyUpBeamABrelnarScene(key);
			break; }
			// ***** Ask The Abdromedans Scene *****
			case csAskTheAndromedansScene: {
				keyUpAskTheAndromedansScene(key);
			break; }
			// ***** Matter-Antimatter Scene *****
			case csMatterAntimatterScene: {
				keyUpMatterAntimatterScene(key);
			break; }
			// ***** Book Of Knowledge Scene *****
			case csBookOfKnowledgeScene: {
				keyUpBookOfKnowledgeScene(key);
			break; }
			// ***** Main Menu Screen *****
			case csMainMenuScreen: {
				keyUpMainMenuScreen(key);
			break; }
			// ***** Instructions Screen *****
			case csInstructionsScreen: {
				keyUpInstructionsScreen(key);
			break; }
			// ***** High Scores Screen *****
			case csHighScoresScreen: {
				keyUpHighScoresScreen(key);
			break; }
			// ***** Settings Screen *****
			case csSettingsScreen: {
				keyUpSettingsScreen(key);
			break; }
			// ***** Character Select Screen *****
			case csCharacterSelectScreen: {
				keyUpCharacterSelectScreen(key);
			break; }
				// ***** Point Levels Screen *****
			case csPointLevelsScreen: {
				keyUpPointLevelsScreen(key);
			break; }
			// ***** Credits Screen *****
			case csCreditsScreen: {
				keyUpCreditsScreen(key);
			break; }
			// ***** Answer Screen *****
			case csAnswerScreen: {
				keyUpAnswerScreen(key);
			break; }
			// ***** St. Louis Destruction Scene *****
			case csStLouisDestructionScene: {
				keyUpDestructionStLouisScene(key);
			break; }
			// ***** Tokyo Destruction Scene *****
			case csTokyoDestructionScene: {
				keyUpDestructionTokyoScene(key);
			break; }
			// ***** Rome Destruction Scene *****
			case csRomeDestructionScene: {
				keyUpDestructionRomeScene(key);
			break; }
			// ***** Pisa Destruction Scene *****
			case csPisaDestructionScene: {
				keyUpDestructionPisaScene(key);
			break; }
			// ***** Paris Destruction Scene *****
			case csParisDestructionScene: {
				keyUpDestructionParisScene(key);
			break; }
			// ***** Moscow Destruction Scene *****
			case csMoscowDestructionScene: {
				keyUpDestructionMoscowScene(key);
			break; }
			// ***** London Destruction Scene *****
			case csLondonDestructionScene: {
				keyUpDestructionLondonScene(key);
			break; }
			// ***** Giza Destruction Scene *****
			case csGizaDestructionScene: {
				keyUpDestructionGizaScene(key);
			break; }
			// ***** World Destruction 1 Scene *****
			case csWorldDestruction1Scene: {
				keyUpWorldDestruction1Scene(key);
			break; }
			// ***** World Destruction 2 Scene *****
			case csWorldDestruction2Scene: {
				keyUpWorldDestruction2Scene(key);
			break; }
			// ***** World Destruction 3 Scene *****
			case csWorldDestruction3Scene: {
				keyUpWorldDestruction3Scene(key);
			break; }
			// ***** World Destruction 4 Scene *****
			case csWorldDestruction4Scene: {
				keyUpWorldDestruction4Scene(key);
			break; }
			// ***** World Destruction 5 Scene *****
			case csWorldDestruction5Scene: {
				keyUpWorldDestruction5Scene(key);
			break; }
			// ***** Start Game Intro 1 Scene *****
			case csStartGameIntro1Scene: {
				keyUpStartGameIntro1Scene(key);
			break; }
			// ***** Start Game Intro 2 Scene *****
			case csStartGameIntro2Scene: {
				keyUpStartGameIntro2Scene(key);
			break; }
			// ***** Start Game Intro 3 Scene *****
			case csStartGameIntro3Scene: {
				keyUpStartGameIntro3Scene(key);
			break; }
			// ***** Start Game Intro 4 Scene *****
			case csStartGameIntro4Scene: {
				keyUpStartGameIntro4Scene(key);
			break; }
			// ***** Start Game Intro 5 Scene *****
			case csStartGameIntro5Scene: {
				keyUpStartGameIntro5Scene(key);
			break; }
			// ***** Correct Answer 1 Scene *****
			case csCorrectAnswer1Scene: {
				keyUpCorrectAnswer1Scene(key);
			break; }
			// ***** Correct Answer 2 Scene *****
			case csCorrectAnswer2Scene: {
				keyUpCorrectAnswer2Scene(key);
			break; }
			// ***** Correct Answer 3 Scene *****
			case csCorrectAnswer3Scene: {
				keyUpCorrectAnswer3Scene(key);
			break; }
			// ***** Correct Answer 4 Scene *****
			case csCorrectAnswer4Scene: {
				keyUpCorrectAnswer4Scene(key);
			break; }
			// ***** Correct Answer 5 Scene *****
			case csCorrectAnswer5Scene: {
				keyUpCorrectAnswer5Scene(key);
			break; }
			// ***** Player Wims 1 Scene *****
			case csPlayerWins1Scene: {
				keyUpPlayerWins1Scene(key);
			break; }
			// ***** Player Wims 2 Scene *****
			case csPlayerWins2Scene: {
				keyUpPlayerWins2Scene(key);
			break; }
			// ***** Player Wims 3 Scene *****
			case csPlayerWins3Scene: {
				keyUpPlayerWins3Scene(key);
			break; }
			// ***** Player Wims 4 Scene *****
			case csPlayerWins4Scene: {
				keyUpPlayerWins4Scene(key);
			break; }
			// ***** Player Wims 5 Scene *****
			case csPlayerWins5Scene: {
				keyUpPlayerWins5Scene(key);
			break; }

		} // End Switch

	} // End IF

} // End ButtonUpHandler
