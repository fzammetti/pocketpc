
// Stylus Down Handler
void InvasionTrivia::StylusDown(Point stylus) {

	if (ProcessEvents) {

		switch (currentScreen) {

			// ***** Congratulations Screen *****
			case csCongratulationsScreen: {
				stylusDownCongratulationsScreen(stylus);
			break; }
			// ***** Intro Screen *****
			case csIntroScreen: {
				stylusDownIntroScreen(stylus);
			break; }
			// ***** Title Scene *****
			case csTitleScene: {
				stylusDownTitleScene(stylus);
			break; }
			// ***** Beam A Brelnar Scene *****
			case csBeamABrelnarScene: {
				stylusDownBeamABrelnarScene(stylus);
			break; }
			// ***** Ask The Abdromedans Scene *****
			case csAskTheAndromedansScene: {
				stylusDownAskTheAndromedansScene(stylus);
			break; }
			// ***** Matter-Antimatter Scene *****
			case csMatterAntimatterScene: {
				stylusDownMatterAntimatterScene(stylus);
			break; }
			// ***** Book Of Knowledge Scene *****
			case csBookOfKnowledgeScene: {
				stylusDownBookOfKnowledgeScene(stylus);
			break; }
			// ***** Main Menu Screen *****
			case csMainMenuScreen: {
				stylusDownMainMenuScreen(stylus);
			break; }
			// ***** Instructions Screen *****
			case csInstructionsScreen: {
				stylusDownInstructionsScreen(stylus);
			break; }
			// ***** High Scores Screen *****
			case csHighScoresScreen: {
				stylusDownHighScoresScreen(stylus);
			break; }
			// ***** Settings Screen *****
			case csSettingsScreen: {
				stylusDownSettingsScreen(stylus);
			break; }
			// ***** Character Select Screen *****
			case csCharacterSelectScreen: {
				stylusDownCharacterSelectScreen(stylus);
			break; }
				// ***** Point Levels Screen *****
			case csPointLevelsScreen: {
				stylusDownPointLevelsScreen(stylus);
			break; }
			// ***** Credits Screen *****
			case csCreditsScreen: {
				stylusDownCreditsScreen(stylus);
			break; }
			// ***** Answer Screen *****
			case csAnswerScreen: {
				stylusDownAnswerScreen(stylus);
			break; }
			// ***** St. Louis Destruction Scene *****
			case csStLouisDestructionScene: {
				stylusDownDestructionStLouisScene(stylus);
			break; }
			// ***** Tokyo Destruction Scene *****
			case csTokyoDestructionScene: {
				stylusDownDestructionTokyoScene(stylus);
			break; }
			// ***** Rome Destruction Scene *****
			case csRomeDestructionScene: {
				stylusDownDestructionRomeScene(stylus);
			break; }
			// ***** Pisa Destruction Scene *****
			case csPisaDestructionScene: {
				stylusDownDestructionPisaScene(stylus);
			break; }
			// ***** Paris Destruction Scene *****
			case csParisDestructionScene: {
				stylusDownDestructionParisScene(stylus);
			break; }
			// ***** Moscow Destruction Scene *****
			case csMoscowDestructionScene: {
				stylusDownDestructionMoscowScene(stylus);
			break; }
			// ***** London Destruction Scene *****
			case csLondonDestructionScene: {
				stylusDownDestructionLondonScene(stylus);
			break; }
			// ***** Giza Destruction Scene *****
			case csGizaDestructionScene: {
				stylusDownDestructionGizaScene(stylus);
			break; }
			// ***** World Destruction 1 Scene *****
			case csWorldDestruction1Scene: {
				stylusDownWorldDestruction1Scene(stylus);
			break; }
			// ***** World Destruction 2 Scene *****
			case csWorldDestruction2Scene: {
				stylusDownWorldDestruction2Scene(stylus);
			break; }
			// ***** World Destruction 3 Scene *****
			case csWorldDestruction3Scene: {
				stylusDownWorldDestruction3Scene(stylus);
			break; }
			// ***** World Destruction 4 Scene *****
			case csWorldDestruction4Scene: {
				stylusDownWorldDestruction4Scene(stylus);
			break; }
			// ***** World Destruction 5 Scene *****
			case csWorldDestruction5Scene: {
				stylusDownWorldDestruction5Scene(stylus);
			break; }
			// ***** Start Game Intro 1 Scene *****
			case csStartGameIntro1Scene: {
				stylusDownStartGameIntro1Scene(stylus);
			break; }
			// ***** Start Game Intro 2 Scene *****
			case csStartGameIntro2Scene: {
				stylusDownStartGameIntro2Scene(stylus);
			break; }
			// ***** Start Game Intro 3 Scene *****
			case csStartGameIntro3Scene: {
				stylusDownStartGameIntro3Scene(stylus);
			break; }
			// ***** Start Game Intro 4 Scene *****
			case csStartGameIntro4Scene: {
				stylusDownStartGameIntro4Scene(stylus);
			break; }
			// ***** Start Game Intro 5 Scene *****
			case csStartGameIntro5Scene: {
				stylusDownStartGameIntro5Scene(stylus);
			break; }
			// ***** Correct Answer 1 Scene *****
			case csCorrectAnswer1Scene: {
				stylusDownCorrectAnswer1Scene(stylus);
			break; }
			// ***** Correct Answer 2 Scene *****
			case csCorrectAnswer2Scene: {
				stylusDownCorrectAnswer2Scene(stylus);
			break; }
			// ***** Correct Answer 3 Scene *****
			case csCorrectAnswer3Scene: {
				stylusDownCorrectAnswer3Scene(stylus);
			break; }
			// ***** Correct Answer 4 Scene *****
			case csCorrectAnswer4Scene: {
				stylusDownCorrectAnswer4Scene(stylus);
			break; }
			// ***** Correct Answer 5 Scene *****
			case csCorrectAnswer5Scene: {
				stylusDownCorrectAnswer5Scene(stylus);
			break; }
			// ***** Player Wims 1 Scene *****
			case csPlayerWins1Scene: {
				stylusDownPlayerWins1Scene(stylus);
			break; }
			// ***** Player Wims 2 Scene *****
			case csPlayerWins2Scene: {
				stylusDownPlayerWins2Scene(stylus);
			break; }
			// ***** Player Wims 3 Scene *****
			case csPlayerWins3Scene: {
				stylusDownPlayerWins3Scene(stylus);
			break; }
			// ***** Player Wims 4 Scene *****
			case csPlayerWins4Scene: {
				stylusDownPlayerWins4Scene(stylus);
			break; }
			// ***** Player Wims 5 Scene *****
			case csPlayerWins5Scene: {
				stylusDownPlayerWins5Scene(stylus);
			break; }

		} // End Switch

	} // End IF


} // End StylusDownHandler


// Stylus Move Handler
void InvasionTrivia::StylusMove(Point stylus) {

	if (ProcessEvents) {

		switch (currentScreen) {

			// ***** Congratulations Screen *****
			case csCongratulationsScreen: {
				stylusMoveCongratulationsScreen(stylus);
			break; }
			// ***** Intro Screen *****
			case csIntroScreen: {
				stylusMoveIntroScreen(stylus);
			break; }
			// ***** Title Scene *****
			case csTitleScene: {
				stylusMoveTitleScene(stylus);
			break; }
			// ***** Beam A Brelnar Scene *****
			case csBeamABrelnarScene: {
				stylusMoveBeamABrelnarScene(stylus);
			break; }
			// ***** Ask The Abdromedans Scene *****
			case csAskTheAndromedansScene: {
				stylusMoveAskTheAndromedansScene(stylus);
			break; }
			// ***** Matter-Antimatter Scene *****
			case csMatterAntimatterScene: {
				stylusMoveMatterAntimatterScene(stylus);
			break; }
			// ***** Book Of Knowledge Scene *****
			case csBookOfKnowledgeScene: {
				stylusMoveBookOfKnowledgeScene(stylus);
			break; }
			// ***** Main Menu Screen *****
			case csMainMenuScreen: {
				stylusMoveMainMenuScreen(stylus);
			break; }
			// ***** Instructions Screen *****
			case csInstructionsScreen: {
				stylusMoveInstructionsScreen(stylus);
			break; }
			// ***** High Scores Screen *****
			case csHighScoresScreen: {
				stylusMoveHighScoresScreen(stylus);
			break; }
			// ***** Settings Screen *****
			case csSettingsScreen: {
				stylusMoveSettingsScreen(stylus);
			break; }
			// ***** Character Select Screen *****
			case csCharacterSelectScreen: {
				stylusMoveCharacterSelectScreen(stylus);
			break; }
				// ***** Point Levels Screen *****
			case csPointLevelsScreen: {
				stylusMovePointLevelsScreen(stylus);
			break; }
			// ***** Credits Screen *****
			case csCreditsScreen: {
				stylusMoveCreditsScreen(stylus);
			break; }
			// ***** Answer Screen Screen *****
			case csAnswerScreen: {
				stylusMoveAnswerScreen(stylus);
			break; }
			// ***** St. Louis Destruction Scene *****
			case csStLouisDestructionScene: {
				stylusMoveDestructionStLouisScene(stylus);
			break; }
			// ***** Tokyo Destruction Scene *****
			case csTokyoDestructionScene: {
				stylusMoveDestructionTokyoScene(stylus);
			break; }
			// ***** Rome Destruction Scene *****
			case csRomeDestructionScene: {
				stylusMoveDestructionRomeScene(stylus);
			break; }
			// ***** Pisa Destruction Scene *****
			case csPisaDestructionScene: {
				stylusMoveDestructionPisaScene(stylus);
			break; }
			// ***** Paris Destruction Scene *****
			case csParisDestructionScene: {
				stylusMoveDestructionParisScene(stylus);
			break; }
			// ***** Moscow Destruction Scene *****
			case csMoscowDestructionScene: {
				stylusMoveDestructionMoscowScene(stylus);
			break; }
			// ***** London Destruction Scene *****
			case csLondonDestructionScene: {
				stylusMoveDestructionLondonScene(stylus);
			break; }
			// ***** Giza Destruction Scene *****
			case csGizaDestructionScene: {
				stylusMoveDestructionGizaScene(stylus);
			break; }
			// ***** World Destruction 1 Scene *****
			case csWorldDestruction1Scene: {
				stylusMoveWorldDestruction1Scene(stylus);
			break; }
			// ***** World Destruction 2 Scene *****
			case csWorldDestruction2Scene: {
				stylusMoveWorldDestruction2Scene(stylus);
			break; }
			// ***** World Destruction 3 Scene *****
			case csWorldDestruction3Scene: {
				stylusMoveWorldDestruction3Scene(stylus);
			break; }
			// ***** World Destruction 4 Scene *****
			case csWorldDestruction4Scene: {
				stylusMoveWorldDestruction4Scene(stylus);
			break; }
			// ***** World Destruction 5 Scene *****
			case csWorldDestruction5Scene: {
				stylusMoveWorldDestruction5Scene(stylus);
			break; }
			// ***** Start Game Intro 1 Scene *****
			case csStartGameIntro1Scene: {
				stylusMoveStartGameIntro1Scene(stylus);
			break; }
			// ***** Start Game Intro 2 Scene *****
			case csStartGameIntro2Scene: {
				stylusMoveStartGameIntro2Scene(stylus);
			break; }
			// ***** Start Game Intro 3 Scene *****
			case csStartGameIntro3Scene: {
				stylusMoveStartGameIntro3Scene(stylus);
			break; }
			// ***** Start Game Intro 4 Scene *****
			case csStartGameIntro4Scene: {
				stylusMoveStartGameIntro4Scene(stylus);
			break; }
			// ***** Start Game Intro 5 Scene *****
			case csStartGameIntro5Scene: {
				stylusMoveStartGameIntro5Scene(stylus);
			break; }
			// ***** Correct Answer 1 Scene *****
			case csCorrectAnswer1Scene: {
				stylusMoveCorrectAnswer1Scene(stylus);
			break; }
			// ***** Correct Answer 2 Scene *****
			case csCorrectAnswer2Scene: {
				stylusMoveCorrectAnswer2Scene(stylus);
			break; }
			// ***** Correct Answer 3 Scene *****
			case csCorrectAnswer3Scene: {
				stylusMoveCorrectAnswer3Scene(stylus);
			break; }
			// ***** Correct Answer 4 Scene *****
			case csCorrectAnswer4Scene: {
				stylusMoveCorrectAnswer4Scene(stylus);
			break; }
			// ***** Correct Answer 5 Scene *****
			case csCorrectAnswer5Scene: {
				stylusMoveCorrectAnswer5Scene(stylus);
			break; }
			// ***** Player Wims 1 Scene *****
			case csPlayerWins1Scene: {
				stylusMovePlayerWins1Scene(stylus);
			break; }
			// ***** Player Wims 2 Scene *****
			case csPlayerWins2Scene: {
				stylusMovePlayerWins2Scene(stylus);
			break; }
			// ***** Player Wims 3 Scene *****
			case csPlayerWins3Scene: {
				stylusMovePlayerWins3Scene(stylus);
			break; }
			// ***** Player Wims 4 Scene *****
			case csPlayerWins4Scene: {
				stylusMovePlayerWins4Scene(stylus);
			break; }
			// ***** Player Wims 5 Scene *****
			case csPlayerWins5Scene: {
				stylusMovePlayerWins5Scene(stylus);
			break; }

		} // End Switch

	} // End IF


} // End StylusMoveHandler


// Stylus Up Handler
void InvasionTrivia::StylusUp(Point stylus) {

	if (ProcessEvents) {

		switch (currentScreen) {

			// ***** Congratulations Screen *****
			case csCongratulationsScreen: {
				stylusUpCongratulationsScreen(stylus);
			break; }
			// ***** Intro Screen *****
			case csIntroScreen: {
				stylusUpIntroScreen(stylus);
			break; }
			// ***** Title Scene *****
			case csTitleScene: {
				stylusUpTitleScene(stylus);
			break; }
			// ***** Beam A Brelnar Scene *****
			case csBeamABrelnarScene: {
				stylusUpBeamABrelnarScene(stylus);
			break; }
			// ***** Ask The Abdromedans Scene *****
			case csAskTheAndromedansScene: {
				stylusUpAskTheAndromedansScene(stylus);
			break; }
			// ***** Matter-Antimatter Scene *****
			case csMatterAntimatterScene: {
				stylusUpMatterAntimatterScene(stylus);
			break; }
			// ***** Book Of Knowledge Scene *****
			case csBookOfKnowledgeScene: {
				stylusUpBookOfKnowledgeScene(stylus);
			break; }
			// ***** Main Menu Screen *****
			case csMainMenuScreen: {
				stylusUpMainMenuScreen(stylus);
			break; }
			// ***** Instructions Screen *****
			case csInstructionsScreen: {
				stylusUpInstructionsScreen(stylus);
			break; }
			// ***** High Scores Screen *****
			case csHighScoresScreen: {
				stylusUpHighScoresScreen(stylus);
			break; }
			// ***** Settings Screen *****
			case csSettingsScreen: {
				stylusUpSettingsScreen(stylus);
			break; }
			// ***** Character Select Screen *****
			case csCharacterSelectScreen: {
				stylusUpCharacterSelectScreen(stylus);
			break; }
				// ***** Point Levels Screen *****
			case csPointLevelsScreen: {
				stylusUpPointLevelsScreen(stylus);
			break; }
			// ***** Credits Screen *****
			case csCreditsScreen: {
				stylusUpCreditsScreen(stylus);
			break; }
			// ***** Answer Screen *****
			case csAnswerScreen: {
				stylusUpAnswerScreen(stylus);
			break; }
			// ***** St. Louis Destruction Scene *****
			case csStLouisDestructionScene: {
				stylusUpDestructionStLouisScene(stylus);
			break; }
			// ***** Tokyo Destruction Scene *****
			case csTokyoDestructionScene: {
				stylusUpDestructionTokyoScene(stylus);
			break; }
			// ***** Rome Destruction Scene *****
			case csRomeDestructionScene: {
				stylusUpDestructionRomeScene(stylus);
			break; }
			// ***** Pisa Destruction Scene *****
			case csPisaDestructionScene: {
				stylusUpDestructionPisaScene(stylus);
			break; }
			// ***** Paris Destruction Scene *****
			case csParisDestructionScene: {
				stylusUpDestructionParisScene(stylus);
			break; }
			// ***** Moscow Destruction Scene *****
			case csMoscowDestructionScene: {
				stylusUpDestructionMoscowScene(stylus);
			break; }
			// ***** London Destruction Scene *****
			case csLondonDestructionScene: {
				stylusUpDestructionLondonScene(stylus);
			break; }
			// ***** Giza Destruction Scene *****
			case csGizaDestructionScene: {
				stylusUpDestructionGizaScene(stylus);
			break; }
			// ***** World Destruction 1 Scene *****
			case csWorldDestruction1Scene: {
				stylusUpWorldDestruction1Scene(stylus);
			break; }
			// ***** World Destruction 2 Scene *****
			case csWorldDestruction2Scene: {
				stylusUpWorldDestruction2Scene(stylus);
			break; }
			// ***** World Destruction 3 Scene *****
			case csWorldDestruction3Scene: {
				stylusUpWorldDestruction3Scene(stylus);
			break; }
			// ***** World Destruction 4 Scene *****
			case csWorldDestruction4Scene: {
				stylusUpWorldDestruction4Scene(stylus);
			break; }
			// ***** World Destruction 5 Scene *****
			case csWorldDestruction5Scene: {
				stylusUpWorldDestruction5Scene(stylus);
			break; }
			// ***** Start Game Intro 1 Scene *****
			case csStartGameIntro1Scene: {
				stylusUpStartGameIntro1Scene(stylus);
			break; }
			// ***** Start Game Intro 2 Scene *****
			case csStartGameIntro2Scene: {
				stylusUpStartGameIntro2Scene(stylus);
			break; }
			// ***** Start Game Intro 3 Scene *****
			case csStartGameIntro3Scene: {
				stylusUpStartGameIntro3Scene(stylus);
			break; }
			// ***** Start Game Intro 4 Scene *****
			case csStartGameIntro4Scene: {
				stylusUpStartGameIntro4Scene(stylus);
			break; }
			// ***** Start Game Intro 5 Scene *****
			case csStartGameIntro5Scene: {
				stylusUpStartGameIntro5Scene(stylus);
			break; }
			// ***** Correct Answer 1 Scene *****
			case csCorrectAnswer1Scene: {
				stylusUpCorrectAnswer1Scene(stylus);
			break; }
			// ***** Correct Answer 2 Scene *****
			case csCorrectAnswer2Scene: {
				stylusUpCorrectAnswer2Scene(stylus);
			break; }
			// ***** Correct Answer 3 Scene *****
			case csCorrectAnswer3Scene: {
				stylusUpCorrectAnswer3Scene(stylus);
			break; }
			// ***** Correct Answer 4 Scene *****
			case csCorrectAnswer4Scene: {
				stylusUpCorrectAnswer4Scene(stylus);
			break; }
			// ***** Correct Answer 5 Scene *****
			case csCorrectAnswer5Scene: {
				stylusUpCorrectAnswer5Scene(stylus);
			break; }
			// ***** Player Wims 1 Scene *****
			case csPlayerWins1Scene: {
				stylusUpPlayerWins1Scene(stylus);
			break; }
			// ***** Player Wims 2 Scene *****
			case csPlayerWins2Scene: {
				stylusUpPlayerWins2Scene(stylus);
			break; }
			// ***** Player Wims 3 Scene *****
			case csPlayerWins3Scene: {
				stylusUpPlayerWins3Scene(stylus);
			break; }
			// ***** Player Wims 4 Scene *****
			case csPlayerWins4Scene: {
				stylusUpPlayerWins4Scene(stylus);
			break; }
			// ***** Player Wims 5 Scene *****
			case csPlayerWins5Scene: {
				stylusUpPlayerWins5Scene(stylus);
			break; }

		} // End Switch

	} // End IF

} // End StylusUpHandler