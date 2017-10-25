
#include "main.h"


namespace ns_CharacterInteraction {


  // A structure to define a node of our interaction map
  struct INTERACTIONNODE {
	  TCHAR captiveResponse[4][32];   // What the captive says when this node is reached
	  TCHAR playerPhrases[7][4][32];  // Phrases the player can currently say
	  int   trustLevelAdjustments[7]; // The amount (+/- 1) that each response adjusts the captive's trust level when it is reached
    int		nextNode[7];		          // Stores index to the nodes of the reactions that each phrase elicits
  };

  // Storage of our history lines
  struct HISTORYLINE {
    TCHAR history_text[32]; // The text of the line
    bool  isCaptive;        // True if the line is the captive's, false if it's the player's
  };


  // Trust level defines for our captive
  // Note: Whenever we adjust the captive's trust level (when a player says a phrase), we check the value
  // after the adjustment.  If it's < tlDistrusting, the captive stops talking to us.  If it's 4, the player can only
  // then get the proper response to the "How do I get outta here?" question.
  #define tlDistrusting 0
  #define tlNuetral     1
  #define tlCautious    2
  #define tlWarmingUp   3
  #define tlTrusting    4


  // Method to initialize a character
  void initCharacterInteraction(int, HINSTANCE);

  // Variables we need
  CGapiSurface*		 ciTempBlended        = NULL;  // Our temp surface for the blending
  CGapiSurface*		 popup_border_big     = NULL;  // Our border
  CGapiSurface*		 happy_burst          = NULL;
  CGapiSurface*		 captive1[7];                  // Actual images for captive #1: Eeger
  CGapiSurface*		 captive2[7];                  // Actual images for captive #2: Frederick J. Smiley
  CGapiSurface*		 captive3[7];                  // Actual images for captive #3: Catrina
  CGapiSurface*		 captive4[7];                  // Actual images for captive #4: Brenda Bubey
  CGapiSurface*		 captive5[7];                  // Actual images for captive #5: Sully
	hssSound*        music                = NULL;  // The captive's music
  HISTORYLINE 		 history[7];                   // The history of the interaction
  INTERACTIONNODE  conversationMap[54];          // Stores all the nodes of our conversation
  TCHAR            hint_text[7][32];             // The text of the hint
	bool             musicPlaying         = false;
  bool						 first_time           = false; // Flag to tell if we've been through the PNF once yet
  bool						 currentNodeDisplayed = false; // Has the current node's character response been said yet?
  bool             exiting              = false; // Set to true when exiting the screen
  bool             initDone             = false; // Has the initialization of this level been done yet?
  bool             show_hint            = false; // Gets set to TRUE when it's time to show the hint
  int							 ci_loading_step      = 0;     // Used for loading
  int							 ci_destroying_step   = 0;     // Used for destroying
  int							 captive_trust_level  = 0;     // Current trust level of captive
  int							 ciButtonPressed      = 0;     // What button is pressed
  int              currentPlayerPhrase  = 0;     // What player phrase is currently being shown
  int              currentINode         = 0;		 // Index to the current interaction node we're on
  int              exiting_delay        = 0;     // Pause when exiting


} // End of namespace


// ****************************************************************************************************************
// ProcessNextFrame handler
// ****************************************************************************************************************
void CGame::pnfCharacterInteraction(CGapiSurface* backbuffer) {

	using namespace ns_CharacterInteraction;

  if (initDone) { // Initialization IS done

    if (first_time) { // It's the first time through

      // Do the first time inits
      ciTempBlended = new CGapiSurface();
	    createSurface(TEXT("character_interaction : 0x0037"), ciTempBlended->CreateSurface(NULL, 208, 288));
	    GDFILLRECTFX gdfillrectfx;
	    gdfillrectfx.dwOpacity = 128;
	    RECT rect;
	    SetRect(&rect, 15, 15, 223, 303);
      backbuffer->FillRect(&rect, RGB(0, 0, 200), GDFILLRECT_OPACITY, &gdfillrectfx);
      ciTempBlended->BltFast(0, 0, backbuffer, &rect, NULL, NULL);
      first_time = false;

    } else { // NOT the first time through

			if (music == NULL) {
				switch(current_level) {
					case 1: { music = new hssSound(); loadSFX(TEXT("character_interaction : SFX_MUSIC_EEGER"),   music->load(m_config.hInstance, SFX_MUSIC_EEGER));   music->loop(true); break; }
					case 2: { music = new hssSound(); loadSFX(TEXT("character_interaction : SFX_MUSIC_FRED"),    music->load(m_config.hInstance, SFX_MUSIC_FRED));    music->loop(true); break; }
					case 3: { music = new hssSound(); loadSFX(TEXT("character_interaction : SFX_MUSIC_CATRINA"), music->load(m_config.hInstance, SFX_MUSIC_CATRINA)); music->loop(true); break; }
					case 4: { music = new hssSound(); loadSFX(TEXT("character_interaction : SFX_MUSIC_BRENDA"),  music->load(m_config.hInstance, SFX_MUSIC_BRENDA));  music->loop(true); break; }
					case 5: { music = new hssSound(); loadSFX(TEXT("character_interaction : SFX_MUSIC_SULLY"),   music->load(m_config.hInstance, SFX_MUSIC_SULLY));   music->loop(true); break; }
				}
				sndObj.playSound(music);
			}

      if (show_hint) { // We're showing the hint and waiting for the player to exit

        // Blit Blended area
        backbuffer->BltFast(15, 15, ciTempBlended, NULL, NULL, NULL);
	      // Blit Border
	      backbuffer->BltFast(9, 9, popup_border_big, NULL, GDBLTFAST_KEYSRC, NULL);
        // Sunburst when happy
        backbuffer->BltFast(39, 23, happy_burst, NULL, GDBLTFAST_KEYSRC, NULL);
        // Captive
        switch (current_level) {
          case 1: { backbuffer->BltFast(39, 23, captive1[captive_trust_level], NULL, GDBLTFAST_KEYSRC, NULL); break; }
          case 2: { backbuffer->BltFast(39, 23, captive2[captive_trust_level], NULL, GDBLTFAST_KEYSRC, NULL); break; }
          case 3: { backbuffer->BltFast(39, 23, captive3[captive_trust_level], NULL, GDBLTFAST_KEYSRC, NULL); break; }
          case 4: { backbuffer->BltFast(39, 23, captive4[captive_trust_level], NULL, GDBLTFAST_KEYSRC, NULL); break; }
          case 5: { backbuffer->BltFast(39, 23, captive5[captive_trust_level], NULL, GDBLTFAST_KEYSRC, NULL); break; }
        }
        // Hint text
        int j = 168;
        for (int i = 0; i < 5; i++) {
	        backbuffer->DrawText(20, j, hint_text[i], &font1_green, GDDRAWTEXT_LEFT, NULL, NULL, NULL);
          j = j + 18;
        }
        // Notice to click Command to exit
		    backbuffer->DrawText(bbCenterPoint, 280, TEXT("COMMAND/Click To Exit"), &font1, GDDRAWTEXT_CENTER, NULL, NULL, NULL);

      } else {

		    // If the current node's character response hasn't been said yet, set up for that next frame
		    if (!currentNodeDisplayed) {
			    currentNodeDisplayed = true;
			    // Shift the history text up appropriately, depending on whether the response is one or two lines, and put the new text in
			    if (_tcscmp(conversationMap[currentINode].captiveResponse[1], TEXT("")) == 0) { // One line
				    history[0] = history[1];
				    history[1] = history[2];
				    history[2] = history[3];
				    history[3] = history[4];
				    _tcscpy(history[4].history_text, conversationMap[currentINode].captiveResponse[0]);
            history[4].isCaptive = true;
			    } else { // Two lines
				    history[0] = history[2];
				    history[1] = history[3];
				    history[2] = history[4];
				    _tcscpy(history[3].history_text, conversationMap[currentINode].captiveResponse[0]);
				    _tcscpy(history[4].history_text, conversationMap[currentINode].captiveResponse[1]);
            history[3].isCaptive = true;
            history[4].isCaptive = true;
			    }
		    }
        // Blit Blended area
        backbuffer->BltFast(15, 15, ciTempBlended, NULL, NULL, NULL);
	      // Blit Border
	      backbuffer->BltFast(9, 9, popup_border_big, NULL, GDBLTFAST_KEYSRC, NULL);
        // Sunburst when happy
        if (captive_trust_level == 4) {
          backbuffer->BltFast(39, 23, happy_burst, NULL, GDBLTFAST_KEYSRC, NULL);
        }
        // Captive
        switch (current_level) {
          case 1: { backbuffer->BltFast(39, 23, captive1[captive_trust_level], NULL, GDBLTFAST_KEYSRC, NULL); break; }
          case 2: { backbuffer->BltFast(39, 23, captive2[captive_trust_level], NULL, GDBLTFAST_KEYSRC, NULL); break; }
          case 3: { backbuffer->BltFast(39, 23, captive3[captive_trust_level], NULL, GDBLTFAST_KEYSRC, NULL); break; }
          case 4: { backbuffer->BltFast(39, 23, captive4[captive_trust_level], NULL, GDBLTFAST_KEYSRC, NULL); break; }
          case 5: { backbuffer->BltFast(39, 23, captive5[captive_trust_level], NULL, GDBLTFAST_KEYSRC, NULL); break; }
        }
		    // Blit History text
        int j = 168;
        for (int i = 0; i < 5; i++) {
          if (history[i].isCaptive) {
		        backbuffer->DrawText(20, j, history[i].history_text, &font1_green, GDDRAWTEXT_LEFT, NULL, NULL, NULL);
          } else {
            backbuffer->DrawText(20, j, history[i].history_text, &font1, GDDRAWTEXT_LEFT, NULL, NULL, NULL);
          }
          j = j + 18;
        }
		    // Blit Arrows
		    if (ciButtonPressed == 1) {
			    backbuffer->BltFast(15, 270, gfx_ins_prev_1, NULL, GDBLTFAST_KEYSRC, NULL);
		    } else {
			    backbuffer->BltFast(15, 270, gfx_ins_prev_0, NULL, GDBLTFAST_KEYSRC, NULL);
		    }
		    if (ciButtonPressed == 2) {
			    backbuffer->BltFast(198, 270, gfx_ins_next_1, NULL, GDBLTFAST_KEYSRC, NULL);
		    } else {
			    backbuffer->BltFast(198, 270, gfx_ins_next_0, NULL, GDBLTFAST_KEYSRC, NULL);
		    }
		    // Phrase text
		    backbuffer->DrawText(bbCenterPoint, 264, conversationMap[currentINode].playerPhrases[currentPlayerPhrase][0], &font1, GDDRAWTEXT_CENTER, NULL, NULL, NULL);
		    backbuffer->DrawText(bbCenterPoint, 280, conversationMap[currentINode].playerPhrases[currentPlayerPhrase][1], &font1, GDDRAWTEXT_CENTER, NULL, NULL, NULL);
        // If we're in the process of exiting, handle that
        if (exiting) {
          exiting_delay++;
          if (exiting_delay > 48) {
						sndObj.stopSounds();
						delete music;
						music = NULL;
            exiting              = false;
            initDone             = false;
            exiting_delay        = 0;
            first_time           = true;
            currentNodeDisplayed = false;
            current_screen       = csWalkingAroundTheShip;
          }
        }

      } // End if (show_hint)

    } // End if (first_time)

  } else { // Level initialization NOT yet done

    initCharacterInteraction(current_level, m_config.hInstance);

  }

}


// ****************************************************************************************************************
// KeyDown handler
// ****************************************************************************************************************
void CGame::kdCharacterInteraction(DWORD dwKey) {

	using namespace ns_CharacterInteraction;

	if (currentNodeDisplayed && !exiting && !show_hint) {
    if (dwKey == kLeft)   { ciButtonPressed = 1;}
    if (dwKey == kRight)  { ciButtonPressed = 2; }
    if (dwKey == kAction) { player_button_down = true; }
	}

}


// ****************************************************************************************************************
// KeyUp handler
// ****************************************************************************************************************
void CGame::kuCharacterInteraction(DWORD dwKey) {

	using namespace ns_CharacterInteraction;

  // If we're showing the hint, just exit if they click Command
  if (show_hint && dwKey == kCommand) {
		sndObj.stopSounds();
		delete music;
		music = NULL;
    levelHintDone        = true;
    exiting              = false;
    initDone             = false;
    writeKGAFile(true, false);
    exiting_delay        = 0;
    first_time           = true;
    currentNodeDisplayed = false;
    current_screen       = csWalkingAroundTheShip;
  }

  // We're still doing the interaction...
	if (currentNodeDisplayed && !exiting && !show_hint) {

    // Deal with the left and right buttons
		ciButtonPressed = 0;
		if (dwKey == kLeft) {
			sndObj.playSound(sfx_ins_arrow);
			currentPlayerPhrase--;
			if (currentPlayerPhrase < 0) { currentPlayerPhrase = 4; }
		}
		if (dwKey == kRight) {
			sndObj.playSound(sfx_ins_arrow);
			currentPlayerPhrase++;
			if (currentPlayerPhrase > 4) { currentPlayerPhrase = 0; }
		}

    // They hit the Action button...
		if (dwKey == kAction && player_button_down) {

      // What we do depends on what phrase they selected
			switch (currentPlayerPhrase) {

				// Exit interaction
				case 0: {
						sndObj.stopSounds();
						delete music;
						music = NULL;
          initDone = false; // For next time
					current_screen = csWalkingAroundTheShip;
				break; }

        // Ask for the hint
				case 4: {
          if (captive_trust_level == tlTrusting) { // You'll only get the answer if the captive fully trusts you
            show_hint = true;
          } else { // If the character doesn't fully trust you, you blew it!
            currentINode         = 51;
            exiting_delay        = 0;
            currentNodeDisplayed = false;
            exiting              = true;
          }
				break; }

        // Any of the other phrases
				default: {
					currentNodeDisplayed = false;
					// Shift the history text up appropriately, depending on whether the phrase is one or two lines, and put the new text in
					if (_tcscmp(conversationMap[currentINode].playerPhrases[currentPlayerPhrase][0], TEXT("")) == 0) { // One line
				    history[0] = history[1];
				    history[1] = history[2];
				    history[2] = history[3];
				    history[3] = history[4];
						_tcscpy(history[4].history_text, conversationMap[currentINode].playerPhrases[currentPlayerPhrase][0]);
            history[4].isCaptive = false;
					} else { // Two lines
				    history[0] = history[2];
				    history[1] = history[3];
				    history[2] = history[4];
						_tcscpy(history[3].history_text, conversationMap[currentINode].playerPhrases[currentPlayerPhrase][0]);
						_tcscpy(history[4].history_text, conversationMap[currentINode].playerPhrases[currentPlayerPhrase][1]);
            history[3].isCaptive = false;
            history[4].isCaptive = false;
					}
					// Adjust trust level
					if (conversationMap[currentINode].trustLevelAdjustments[currentPlayerPhrase] == 1) { captive_trust_level--;	}
					if (conversationMap[currentINode].trustLevelAdjustments[currentPlayerPhrase] == 2) { captive_trust_level++;	}
          if (captive_trust_level > tlTrusting) { captive_trust_level = tlTrusting; } // To avoid bounds overflow
					// Next node
					currentINode = conversationMap[currentINode].nextNode[currentPlayerPhrase];
          // Start us off on the first phrase
          currentPlayerPhrase = 1;
          // See if the player blew it, and end if so
			    if (captive_trust_level < tlDistrusting) {
						writeKGAFile(true, false);
            captive_trust_level  = tlDistrusting; // We want to show the distrusting image, not -1, which is an array bounds violation!
            currentINode         = 51;
            exiting_delay        = 0;
            currentNodeDisplayed = false;
            exiting              = true;
          }
          break; }

			} // End switch


		} // End vkA if

	}

}


// ****************************************************************************************************************
// StylusDown handler for popups
// ****************************************************************************************************************
void CGame::sdCharacterInteraction(POINT p) {

	using namespace ns_CharacterInteraction;

	if (PtInRect(CRect(15, 270, 39, 294),  p)) { // Previous
		kdCharacterInteraction(kLeft);
		return;
	}

	if (PtInRect(CRect(198, 270, 222, 294),  p)) { // Next
		kdCharacterInteraction(kRight);
		return;
	}

	if (PtInRect(CRect(43, 264, 194, 300),  p)) { // Select
		kdCharacterInteraction(kAction);
		return;
	}

}


// ****************************************************************************************************************
// StylusUp handler for popups
// ****************************************************************************************************************
void CGame::suCharacterInteraction(POINT p) {

	using namespace ns_CharacterInteraction;

	if (ciButtonPressed == 1 && PtInRect(CRect(15, 270, 39, 294),  p)) { // Previous
		kuCharacterInteraction(kLeft);
		return;
	}

	if (ciButtonPressed == 2 && PtInRect(CRect(198, 270, 222, 294),  p)) { // Next
		kuCharacterInteraction(kRight);
		return;
	}

	if (player_button_down && PtInRect(CRect(43, 264, 194, 300),  p)) { // Select
		kuCharacterInteraction(kAction);
		return;
	}

	if (show_hint && PtInRect(CRect(15, 280, 222, 300), p)) { // Exit showing hint
		kuCharacterInteraction(kCommand);
		return;
	}

  ciButtonPressed = 0;
  player_button_down = false;

}


// ****************************************************************************************************************
// Loader
// ****************************************************************************************************************
void CGame::loadCharacterInteraction(CGapiSurface* backbuffer) {

	using namespace ns_CharacterInteraction;

	processEvents = false;

  ci_loading_step++;
  bool loadingDone = false;

  switch(ci_loading_step) {

		case 1: {
			music = NULL;
			first_time = true;
	    popup_border_big = new CGapiSurface(); createSurface(TEXT("character_interaction : GFX_POPUP_BORDER_BIG"), popup_border_big->CreateSurface(0, m_config.hInstance, GFX_POPUP_BORDER_BIG, TEXT("GRAPHICS"))); popup_border_big->SetColorKey(RGB(255, 128, 255));
		  happy_burst      = new CGapiSurface(); createSurface(TEXT("character_interaction : GFX_HAPPY_BURST"),      happy_burst->CreateSurface     (0, m_config.hInstance, GFX_HAPPY_BURST,      TEXT("GRAPHICS"))); happy_burst->SetColorKey     (RGB(255, 128, 255));
    break; }

    case 2: {
			switch (current_level) {
				case 1: {
					captive1[0] = new CGapiSurface(); createSurface(TEXT("character_interaction : GFX_CAPTIVE_1_EXPRESSION_1"), captive1[0]->CreateSurface (0, m_config.hInstance, GFX_CAPTIVE_1_EXPRESSION_1, TEXT("GRAPHICS"))); captive1[0]->SetColorKey(RGB(255, 128, 255));
					captive1[1] = new CGapiSurface(); createSurface(TEXT("character_interaction : GFX_CAPTIVE_1_EXPRESSION_2"), captive1[1]->CreateSurface (0, m_config.hInstance, GFX_CAPTIVE_1_EXPRESSION_2, TEXT("GRAPHICS"))); captive1[1]->SetColorKey(RGB(255, 128, 255));
					captive1[2] = new CGapiSurface(); createSurface(TEXT("character_interaction : GFX_CAPTIVE_1_EXPRESSION_3"), captive1[2]->CreateSurface (0, m_config.hInstance, GFX_CAPTIVE_1_EXPRESSION_3, TEXT("GRAPHICS"))); captive1[2]->SetColorKey(RGB(255, 128, 255));
					captive1[3] = new CGapiSurface(); createSurface(TEXT("character_interaction : GFX_CAPTIVE_1_EXPRESSION_4"), captive1[3]->CreateSurface (0, m_config.hInstance, GFX_CAPTIVE_1_EXPRESSION_4, TEXT("GRAPHICS"))); captive1[3]->SetColorKey(RGB(255, 128, 255));
					captive1[4] = new CGapiSurface(); createSurface(TEXT("character_interaction : GFX_CAPTIVE_1_EXPRESSION_5"), captive1[4]->CreateSurface (0, m_config.hInstance, GFX_CAPTIVE_1_EXPRESSION_5, TEXT("GRAPHICS"))); captive1[4]->SetColorKey(RGB(255, 128, 255));
				break; }
				case 2: {
					captive2[0] = new CGapiSurface(); createSurface(TEXT("character_interaction : GFX_CAPTIVE_2_EXPRESSION_1"), captive2[0]->CreateSurface (0, m_config.hInstance, GFX_CAPTIVE_2_EXPRESSION_1, TEXT("GRAPHICS"))); captive2[0]->SetColorKey(RGB(255, 128, 255));
					captive2[1] = new CGapiSurface(); createSurface(TEXT("character_interaction : GFX_CAPTIVE_2_EXPRESSION_2"), captive2[1]->CreateSurface (0, m_config.hInstance, GFX_CAPTIVE_2_EXPRESSION_2, TEXT("GRAPHICS"))); captive2[1]->SetColorKey(RGB(255, 128, 255));
					captive2[2] = new CGapiSurface(); createSurface(TEXT("character_interaction : GFX_CAPTIVE_2_EXPRESSION_3"), captive2[2]->CreateSurface (0, m_config.hInstance, GFX_CAPTIVE_2_EXPRESSION_3, TEXT("GRAPHICS"))); captive2[2]->SetColorKey(RGB(255, 128, 255));
					captive2[3] = new CGapiSurface(); createSurface(TEXT("character_interaction : GFX_CAPTIVE_2_EXPRESSION_4"), captive2[3]->CreateSurface (0, m_config.hInstance, GFX_CAPTIVE_2_EXPRESSION_4, TEXT("GRAPHICS"))); captive2[3]->SetColorKey(RGB(255, 128, 255));
					captive2[4] = new CGapiSurface(); createSurface(TEXT("character_interaction : GFX_CAPTIVE_2_EXPRESSION_5"), captive2[4]->CreateSurface (0, m_config.hInstance, GFX_CAPTIVE_2_EXPRESSION_5, TEXT("GRAPHICS"))); captive2[4]->SetColorKey(RGB(255, 128, 255));
				break; }
				case 3: {
					captive3[0] = new CGapiSurface(); createSurface(TEXT("character_interaction : GFX_CAPTIVE_3_EXPRESSION_1"), captive3[0]->CreateSurface (0, m_config.hInstance, GFX_CAPTIVE_3_EXPRESSION_1, TEXT("GRAPHICS"))); captive3[0]->SetColorKey(RGB(255, 128, 255));
					captive3[1] = new CGapiSurface(); createSurface(TEXT("character_interaction : GFX_CAPTIVE_3_EXPRESSION_2"), captive3[1]->CreateSurface (0, m_config.hInstance, GFX_CAPTIVE_3_EXPRESSION_2, TEXT("GRAPHICS"))); captive3[1]->SetColorKey(RGB(255, 128, 255));
					captive3[2] = new CGapiSurface(); createSurface(TEXT("character_interaction : GFX_CAPTIVE_3_EXPRESSION_3"), captive3[2]->CreateSurface (0, m_config.hInstance, GFX_CAPTIVE_3_EXPRESSION_3, TEXT("GRAPHICS"))); captive3[2]->SetColorKey(RGB(255, 128, 255));
					captive3[3] = new CGapiSurface(); createSurface(TEXT("character_interaction : GFX_CAPTIVE_3_EXPRESSION_4"), captive3[3]->CreateSurface (0, m_config.hInstance, GFX_CAPTIVE_3_EXPRESSION_4, TEXT("GRAPHICS"))); captive3[3]->SetColorKey(RGB(255, 128, 255));
					captive3[4] = new CGapiSurface(); createSurface(TEXT("character_interaction : GFX_CAPTIVE_3_EXPRESSION_5"), captive3[4]->CreateSurface (0, m_config.hInstance, GFX_CAPTIVE_3_EXPRESSION_5, TEXT("GRAPHICS"))); captive3[4]->SetColorKey(RGB(255, 128, 255));
				break; }
				case 4: {
					captive4[0] = new CGapiSurface(); createSurface(TEXT("character_interaction : GFX_CAPTIVE_4_EXPRESSION_1"), captive4[0]->CreateSurface (0, m_config.hInstance, GFX_CAPTIVE_4_EXPRESSION_1, TEXT("GRAPHICS"))); captive4[0]->SetColorKey(RGB(255, 128, 255));
					captive4[1] = new CGapiSurface(); createSurface(TEXT("character_interaction : GFX_CAPTIVE_4_EXPRESSION_2"), captive4[1]->CreateSurface (0, m_config.hInstance, GFX_CAPTIVE_4_EXPRESSION_2, TEXT("GRAPHICS"))); captive4[1]->SetColorKey(RGB(255, 128, 255));
					captive4[2] = new CGapiSurface(); createSurface(TEXT("character_interaction : GFX_CAPTIVE_4_EXPRESSION_3"), captive4[2]->CreateSurface (0, m_config.hInstance, GFX_CAPTIVE_4_EXPRESSION_3, TEXT("GRAPHICS"))); captive4[2]->SetColorKey(RGB(255, 128, 255));
					captive4[3] = new CGapiSurface(); createSurface(TEXT("character_interaction : GFX_CAPTIVE_4_EXPRESSION_4"), captive4[3]->CreateSurface (0, m_config.hInstance, GFX_CAPTIVE_4_EXPRESSION_4, TEXT("GRAPHICS"))); captive4[3]->SetColorKey(RGB(255, 128, 255));
					captive4[4] = new CGapiSurface(); createSurface(TEXT("character_interaction : GFX_CAPTIVE_4_EXPRESSION_5"), captive4[4]->CreateSurface (0, m_config.hInstance, GFX_CAPTIVE_4_EXPRESSION_5, TEXT("GRAPHICS"))); captive4[4]->SetColorKey(RGB(255, 128, 255));
				break; }
				case 5: {
					captive5[0] = new CGapiSurface(); createSurface(TEXT("character_interaction : GFX_CAPTIVE_5_EXPRESSION_1"), captive5[0]->CreateSurface (0, m_config.hInstance, GFX_CAPTIVE_5_EXPRESSION_1, TEXT("GRAPHICS"))); captive5[0]->SetColorKey(RGB(255, 128, 255));
					captive5[1] = new CGapiSurface(); createSurface(TEXT("character_interaction : GFX_CAPTIVE_5_EXPRESSION_2"), captive5[1]->CreateSurface (0, m_config.hInstance, GFX_CAPTIVE_5_EXPRESSION_2, TEXT("GRAPHICS"))); captive5[1]->SetColorKey(RGB(255, 128, 255));
					captive5[2] = new CGapiSurface(); createSurface(TEXT("character_interaction : GFX_CAPTIVE_5_EXPRESSION_3"), captive5[2]->CreateSurface (0, m_config.hInstance, GFX_CAPTIVE_5_EXPRESSION_3, TEXT("GRAPHICS"))); captive5[2]->SetColorKey(RGB(255, 128, 255));
					captive5[3] = new CGapiSurface(); createSurface(TEXT("character_interaction : GFX_CAPTIVE_5_EXPRESSION_4"), captive5[3]->CreateSurface (0, m_config.hInstance, GFX_CAPTIVE_5_EXPRESSION_4, TEXT("GRAPHICS"))); captive5[3]->SetColorKey(RGB(255, 128, 255));
					captive5[4] = new CGapiSurface(); createSurface(TEXT("character_interaction : GFX_CAPTIVE_5_EXPRESSION_5"), captive5[4]->CreateSurface (0, m_config.hInstance, GFX_CAPTIVE_5_EXPRESSION_5, TEXT("GRAPHICS"))); captive5[4]->SetColorKey(RGB(255, 128, 255));
				break; }
			}
    break; }

    default: {
      player_button_down = false;
      loadingDone = true;
			processEvents = true;
    break; }

	}

  if (loadingDone) { // When the last step is complete, we're done
    loading_step++; // This effectively gets us out of here by continuing the loadWalkingAroundTheShip() method
    ci_loading_step = 0; // For the next time, if needed
  }

}


// ****************************************************************************************************************
// Destroyer
// ****************************************************************************************************************
void CGame::destroyCharacterInteraction(CGapiSurface* backbuffer) {

	using namespace ns_CharacterInteraction;

	processEvents = false;

  ci_destroying_step++;
  bool destroyingDone = false;

  switch(ci_destroying_step) {

		case 1: {
			if (!first_time) { delete ciTempBlended; }
      delete popup_border_big;
			switch (previous_level) {
				case 1: {
          delete happy_burst;
					delete captive1[0];
					delete captive1[1];
					delete captive1[2];
					delete captive1[3];
					delete captive1[4];
				break; }
				case 2: {
					delete captive2[0];
					delete captive2[1];
					delete captive2[2];
					delete captive2[3];
					delete captive2[4];
				break; }
				case 3: {
					delete captive3[0];
					delete captive3[1];
					delete captive3[2];
					delete captive3[3];
					delete captive3[4];
				break; }
				case 4: {
					delete captive4[0];
					delete captive4[1];
					delete captive4[2];
					delete captive4[3];
					delete captive4[4];
				break; }
				case 5: {
					delete captive5[0];
					delete captive5[1];
					delete captive5[2];
					delete captive5[3];
					delete captive5[4];
				break; }
			}
      destroyingDone = true;
    break; }

	}

  if (destroyingDone) { // When the last step is complete, we're done
    destroying_step++; // This effectively gets us out of here by continuing the destroyWalkingAroundTheShip() method
    ci_destroying_step = 0; // For the next time, if needed
  }

}


// ****************************************************************************************************************
// Utility functions
// ****************************************************************************************************************
namespace ns_CharacterInteraction {


	void initCharacterInteraction(int level, HINSTANCE hInstance) {

		using namespace ns_CharacterInteraction;

		// General inits
 		ci_destroying_step   = 0;
		first_time					 = true;
		ciButtonPressed			 = 0;
		currentPlayerPhrase  = 1;
		currentINode				 = 1;
    exiting              = false;
    captive_trust_level  = tlDistrusting;
    first_time           = true;
		currentPlayerPhrase  = 0;
		currentNodeDisplayed = false;
    exiting              = false;
    exiting_delay        = 0;
    show_hint            = false;

		// Clear out history
    for (int i = 0; i < 5; i++) { _tcscpy(history[i].history_text, TEXT("")); history[i].isCaptive = true; }

    // Do setups based on what level we're on
    HRSRC hResInfo;
    switch (level) {
			// Captive for level 1: Eeger
			case 1: {
        hResInfo = FindResource(hInstance, MAKEINTRESOURCE(IDR_CI_EEGER), TEXT("CHARACTER_INTERACTS")); // Interaction data
        // Hint text
        _tcscpy(hint_text[0], TEXT("In The Redeye Order, just"));
        _tcscpy(hint_text[1], TEXT("put the 1, 2, 3 and 4"));
        _tcscpy(hint_text[2], TEXT("tiles in the corners going"));
        _tcscpy(hint_text[3], TEXT("clockwise, and you'll win!"));
        _tcscpy(hint_text[4], TEXT("You got that?"));
      break; }
			// Captive for level 2: Frederick J. Smiley
			case 2: {
        hResInfo = FindResource(hInstance, MAKEINTRESOURCE(IDR_CI_FREDERICK_J_SMILEY), TEXT("CHARACTER_INTERACTS")); // Interaction data
        // Hint text
        _tcscpy(hint_text[0], TEXT("In DeathTrap, just hop"));
        _tcscpy(hint_text[1], TEXT("back and forth between"));
        _tcscpy(hint_text[2], TEXT("the starting tile and"));
        _tcscpy(hint_text[3], TEXT("the one on the right ten"));
        _tcscpy(hint_text[4], TEXT("times. Easy! Good luck!"));
      break; }
			// Captive for level 3: Catrina
			case 3: {
        hResInfo = FindResource(hInstance, MAKEINTRESOURCE(IDR_CI_CATRINA), TEXT("CHARACTER_INTERACTS")); // Interaction data
        // Hint text
        _tcscpy(hint_text[0], TEXT("In Engineer, get three"));
        _tcscpy(hint_text[1], TEXT("particles moving around"));
        _tcscpy(hint_text[2], TEXT("a closed loop for 10"));
        _tcscpy(hint_text[3], TEXT("seconds and you've got"));
        _tcscpy(hint_text[4], TEXT("it beat!"));
      break; }
			// Captive for level 4: Brenda Bubey
			case 4: {
        hResInfo = FindResource(hInstance, MAKEINTRESOURCE(IDR_CI_BRENDA_BUBEY), TEXT("CHARACTER_INTERACTS")); // Interaction data
        // Hint text
        _tcscpy(hint_text[0], TEXT("In The Escape, clear the"));
        _tcscpy(hint_text[1], TEXT("first level, then on the"));
        _tcscpy(hint_text[2], TEXT("second, just push on the"));
        _tcscpy(hint_text[3], TEXT("wall where it is"));
        _tcscpy(hint_text[4], TEXT("different and you win!"));
      break; }
			// Captive for level 5: Sully
			case 5: {
        hResInfo = FindResource(hInstance, MAKEINTRESOURCE(IDR_CI_SULLY), TEXT("CHARACTER_INTERACTS")); // Interaction data
        // Hint text
        _tcscpy(hint_text[0], TEXT("In Son Of Eliminator,"));
        _tcscpy(hint_text[1], TEXT("raise each exactly once"));
        _tcscpy(hint_text[2], TEXT("without lowering it or"));
        _tcscpy(hint_text[3], TEXT("doing anything"));
        _tcscpy(hint_text[4], TEXT("else, and you win!"));
      break; }
		}

    // Load and parse interaction data
		HGLOBAL	       hResD	     = LoadResource(hInstance, hResInfo);
		void*	         pvRes	     = LockResource(hResD);
    unsigned char* dataPointer = (unsigned char*)pvRes;
    int node = 0;
    while (*dataPointer != 255) {

      node++;

      // ********** Parse the character response
      int whichLine = 0;
      int i = 0;
      while (*dataPointer != '`') { // The ` character is the end of the response
        if (*dataPointer == '~') { // Next line
          conversationMap[node].captiveResponse[whichLine][i] = '\0'; // Terminate the line properly
          whichLine = 1;
          i = 0;
        } else {
          conversationMap[node].captiveResponse[whichLine][i] = *dataPointer;
          i++;
        }
        dataPointer++;
      } // End character response while loop
      conversationMap[node].captiveResponse[whichLine][i] = '\0'; // Terminate the line properly
      dataPointer++;

      // ********** Parse the player phrases, trust adjustments and next nodes
		  _tcscpy(conversationMap[node].playerPhrases[0][0], TEXT("See you later"));    // These are
		  _tcscpy(conversationMap[node].playerPhrases[0][1], TEXT("you weirdo!"));      // the two
      conversationMap[node].trustLevelAdjustments[0] = 0;                           // special
      conversationMap[node].nextNode[0] = 0;
		  _tcscpy(conversationMap[node].playerPhrases[4][0], TEXT("Please tell me"));   // hard-coded
		  _tcscpy(conversationMap[node].playerPhrases[4][1], TEXT("the secret hint!")); // phrases
      conversationMap[node].trustLevelAdjustments[4] = 0;
      conversationMap[node].nextNode[4] = 0;
      for (int j = 1; j < 4; j++) {
        int whichLine = 0;
        int i = 0;
        while (*dataPointer != '`') { // The ` character is the end of the response
          if (*dataPointer == '~') { // Next line
            conversationMap[node].playerPhrases[j][whichLine][i] = '\0'; // Terminate the line properly
            whichLine = 1;
            i = 0;
          } else {
            conversationMap[node].playerPhrases[j][whichLine][i] = *dataPointer;
            i++;
          }
          dataPointer++;
        } // End player phrase while loop
        conversationMap[node].playerPhrases[j][whichLine][i] = '\0'; // Terminate the line properly
        dataPointer++;
        conversationMap[node].trustLevelAdjustments[j] = *dataPointer; // Get the trust level adjustment
        dataPointer++;
        conversationMap[node].nextNode[j] = *dataPointer; // Get the next node
        dataPointer++;
      } // End three-iteration player phrase for loop

    } // End main data while loop

    // Our special node for when you blow it
    _tcscpy(conversationMap[51].captiveResponse[0], TEXT("Argh!  I don't trust"));
    _tcscpy(conversationMap[51].captiveResponse[1], TEXT("you!  Get away!"));
    conversationMap[51].trustLevelAdjustments[0] = 0;
    _tcscpy(conversationMap[51].playerPhrases[0][0], TEXT(""));
    _tcscpy(conversationMap[51].playerPhrases[0][1], TEXT(""));
    _tcscpy(conversationMap[51].playerPhrases[1][0], TEXT(""));
    _tcscpy(conversationMap[51].playerPhrases[1][1], TEXT(""));
    _tcscpy(conversationMap[51].playerPhrases[2][0], TEXT(""));
    _tcscpy(conversationMap[51].playerPhrases[2][1], TEXT(""));
    _tcscpy(conversationMap[51].playerPhrases[3][0], TEXT(""));
    _tcscpy(conversationMap[51].playerPhrases[3][1], TEXT(""));
    _tcscpy(conversationMap[51].playerPhrases[4][0], TEXT(""));
    _tcscpy(conversationMap[51].playerPhrases[4][1], TEXT(""));
    conversationMap[51].nextNode[0] = 0;
    conversationMap[51].nextNode[1] = 0;
    conversationMap[51].nextNode[2] = 0;
    conversationMap[51].nextNode[3] = 0;
    conversationMap[51].nextNode[4] = 0;

    // We're done
    initDone = true;

  } // End of initCharacterInteraction() method


} // End of namespace
