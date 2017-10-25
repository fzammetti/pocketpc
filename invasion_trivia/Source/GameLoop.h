
bool doShutdown = false;

void InvasionTrivia::GameLoop() {

	if (!doShutdown) {

		DisplayDevice* display = GetDisplay();

		switch (currentScreen) {

			// ********** Main Menu Screen **********
			case csMainMenuScreen: {
					handlerMainMenuScreen(display);
			break; }
			// ********** Loading Screen **********
			case csLoadingScreen: {
					handlerLoadingScreen(display);
			break; }
			// ********** Congratulations Screen **********
			case csCongratulationsScreen: {
					handlerCongratulationsScreen(display);
			break; }
			// ********** Intro Screen **********
			case csIntroScreen: {
					handlerIntroScreen(display);
			break; }
			// ********** Instructions Screen **********
			case csInstructionsScreen: {
					handlerInstructionsScreen(display);
			break; }
			// ********** Settings Screen **********
			case csSettingsScreen: {
					handlerSettingsScreen(display);
			break; }
			// ********** High Scores Screen **********
			case csHighScoresScreen: {
					handlerHighScoresScreen(display);
			break; }
			// ********** Character Select Screen **********
			case csCharacterSelectScreen: {
					handlerCharacterSelectScreen(display);
			break; }
				// ********** Point Levels Screen **********
			case csPointLevelsScreen: {
					handlerPointLevelsScreen(display);
			break; }
			// ********** Credits Screen **********
			case csCreditsScreen: {
					handlerCreditsScreen(display);
			break; }
			// ********** Answer Screen Screen **********
			case csAnswerScreen: {
					handlerAnswerScreen(display);
			break; }
			// ********** Title Scene **********
			case csTitleScene: {
				if (OASIS_DoScene(display) == 1) { SceneEnder_TitleScene();	}
			break; }
			// ********** Beam A Brelnar Scene **********
			case csBeamABrelnarScene: {
				if (OASIS_DoScene(display) == 1) { SceneEnder_BeamABrelnarScene();	}
			break; }
			// ********** Ask The Andromedans Scene **********
			case csAskTheAndromedansScene: {
				if (OASIS_DoScene(display) == 1) { SceneEnder_AskTheAndromedansScene(); }
			break; }
			// ********** Matter-Antimatter Scene **********
			case csMatterAntimatterScene: {
				if (OASIS_DoScene(display) == 1) { SceneEnder_MatterAntimatterScene(); }
			break; }
			// ********** Book Of Knowledge Scene **********
			case csBookOfKnowledgeScene: {
				if (OASIS_DoScene(display) == 1) { SceneEnder_BookOfKnowledgeScene(); }
			break; }
				// ********** St. Louis Destruction Scene **********
			case csStLouisDestructionScene: {
				if (OASIS_DoScene(display) == 1) { SceneEnder_DestructionStLouisScene();	}
			break; }
				// ********** Tokyo Destruction Scene **********
			case csTokyoDestructionScene: {
				if (OASIS_DoScene(display) == 1) { SceneEnder_DestructionTokyoScene();	}
			break; }
				// ********** Rome Destruction Scene **********
			case csRomeDestructionScene: {
				if (OASIS_DoScene(display) == 1) { SceneEnder_DestructionRomeScene();	}
			break; }
				// ********** Pisa Destruction Scene **********
			case csPisaDestructionScene: {
				if (OASIS_DoScene(display) == 1) { SceneEnder_DestructionPisaScene();	}
			break; }
				// ********** Paris Destruction Scene **********
			case csParisDestructionScene: {
				if (OASIS_DoScene(display) == 1) { SceneEnder_DestructionParisScene();	}
			break; }
				// ********** Moscow Destruction Scene **********
			case csMoscowDestructionScene: {
				if (OASIS_DoScene(display) == 1) { SceneEnder_DestructionMoscowScene();	}
			break; }
				// ********** London Destruction Scene **********
			case csLondonDestructionScene: {
				if (OASIS_DoScene(display) == 1) { SceneEnder_DestructionLondonScene();	}
			break; }
				// ********** Giza Destruction Scene **********
			case csGizaDestructionScene: {
				if (OASIS_DoScene(display) == 1) { SceneEnder_DestructionGizaScene();	}
			break; }
			// ********** World Destruction 1 Scene **********
			case csWorldDestruction1Scene: {
				if (OASIS_DoScene(display) == 1) { SceneEnder_WorldDestruction1Scene(); }
			break; }
			// ********** World Destruction 2 Scene **********
			case csWorldDestruction2Scene: {
				if (OASIS_DoScene(display) == 1) { SceneEnder_WorldDestruction2Scene(); }
			break; }
			// ********** World Destruction 3 Scene **********
			case csWorldDestruction3Scene: {
				if (OASIS_DoScene(display) == 1) { SceneEnder_WorldDestruction3Scene(); }
			break; }
			// ********** World Destruction 4 Scene **********
			case csWorldDestruction4Scene: {
				if (OASIS_DoScene(display) == 1) { SceneEnder_WorldDestruction4Scene(); }
			break; }
			// ********** World Destruction 5 Scene **********
			case csWorldDestruction5Scene: {
				if (OASIS_DoScene(display) == 1) { SceneEnder_WorldDestruction5Scene(); }
			break; }
			// ********** Start Game Intro 1 Scene **********
			case csStartGameIntro1Scene: {
				if (OASIS_DoScene(display) == 1) { SceneEnder_StartGameIntro1Scene(); }
			break; }
			// ********** Start Game Intro 2 Scene **********
			case csStartGameIntro2Scene: {
				if (OASIS_DoScene(display) == 1) { SceneEnder_StartGameIntro2Scene(); }
			break; }
			// ********** Start Game Intro 3 Scene **********
			case csStartGameIntro3Scene: {
				if (OASIS_DoScene(display) == 1) { SceneEnder_StartGameIntro3Scene(); }
			break; }
			// ********** Start Game Intro 4 Scene **********
			case csStartGameIntro4Scene: {
				if (OASIS_DoScene(display) == 1) { SceneEnder_StartGameIntro4Scene(); }
			break; }
			// ********** Start Game Intro 5 Scene **********
			case csStartGameIntro5Scene: {
				if (OASIS_DoScene(display) == 1) { SceneEnder_StartGameIntro5Scene(); }
			break; }
			// ********** Correct Answer 1 Scene **********
			case csCorrectAnswer1Scene: {
				if (OASIS_DoScene(display) == 1) { SceneEnder_CorrectAnswer1Scene(); }
			break; }
			// ********** Correct Answer 2 Scene **********
			case csCorrectAnswer2Scene: {
				if (OASIS_DoScene(display) == 1) { SceneEnder_CorrectAnswer2Scene(); }
			break; }
			// ********** Correct Answer 3 Scene **********
			case csCorrectAnswer3Scene: {
				if (OASIS_DoScene(display) == 1) { SceneEnder_CorrectAnswer3Scene(); }
			break; }
			// ********** Correct Answer 4 Scene **********
			case csCorrectAnswer4Scene: {
				if (OASIS_DoScene(display) == 1) { SceneEnder_CorrectAnswer4Scene(); }
			break; }
			// ********** Correct Answer 5 Scene **********
			case csCorrectAnswer5Scene: {
				if (OASIS_DoScene(display) == 1) { SceneEnder_CorrectAnswer5Scene(); }
			break; }
			// ********** Player Wins 1 Scene **********
			case csPlayerWins1Scene: {
				if (OASIS_DoScene(display) == 1) { SceneEnder_PlayerWins1Scene(); }
			break; }
			// ********** Player Wins 2 Scene **********
			case csPlayerWins2Scene: {
				if (OASIS_DoScene(display) == 1) { SceneEnder_PlayerWins2Scene(); }
			break; }
			// ********** Player Wins 3 Scene **********
			case csPlayerWins3Scene: {
				if (OASIS_DoScene(display) == 1) { SceneEnder_PlayerWins3Scene(); }
			break; }
			// ********** Player Wins 4 Scene **********
			case csPlayerWins4Scene: {
				if (OASIS_DoScene(display) == 1) { SceneEnder_PlayerWins4Scene(); }
			break; }
			// ********** Player Wins 5 Scene **********
			case csPlayerWins5Scene: {
				if (OASIS_DoScene(display) == 1) { SceneEnder_PlayerWins5Scene(); }
			break; }
			// ********** Exiting **********
			case csExiting: {
				display->Clear(Color(0, 0, 0));
				if (ExitCounter < 120) {
					display->DrawLine(0 + ExitCounter, 160, 240 - ExitCounter, 160, Color(255, 255, 255));
					ExitCounter = ExitCounter + 12;
				} else {
					if (ExitFadeCounter <= 0) {
						doShutdown = true;
						game.currentScreen = csNone;
					} else {
						display->SetBlending(255);
						display->Clear(Color(0, 0, 0));
						display->SetBlending((char)ExitFadeCounter);
						display->SetPixel(120, 160, Color(255, 255, 255));
						ExitFadeCounter = ExitFadeCounter - 15;
					}
				}
			break; }
		} // End of SWITCH

		game.FinishGameLoop(display);
		display->Update();

	} else { // This only executes when we're doing a shutdown
		Shutdown();
	}


} // End of GameLoopHandler