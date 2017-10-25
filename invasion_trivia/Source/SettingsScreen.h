
#define ltNone  0
#define ltOne   1
#define ltTwo   2
#define ltThree 3

// ================================================================================================
// Globals
// ================================================================================================

int   txtLabel_Difficulty_X				  = 2;
int   txtLabel_Difficulty_Y				  = 70;
bool  DropDown_Difficulty_Dropped	  = false;
bool  DropDown_Difficulty_Tapped		= false;
bool  DropDown_Difficulty_UpArrow	  = false;
bool  DropDown_Difficulty_DownArrow = false;
int   DifficultyIndexer						  = 0;
int   txtLabel_Font_X							  = 2;
int   txtLabel_Font_Y							  = 120;
bool  DropDown_Font_Dropped				  = false;
bool  DropDown_Font_Tapped					= false;
bool  DropDown_Font_UpArrow				  = false;
bool  DropDown_Font_DownArrow			  = false;
int   fontIndexer									  = 0;
int   txtLabel_QAC_X								= 2;
int   txtLabel_QAC_Y								= 170;
bool  DropDown_QAC_Dropped					= false;
bool  DropDown_QAC_Tapped					  = false;
bool  DropDown_QAC_UpArrow					= false;
bool  DropDown_QAC_DownArrow				= false;
int   QACIndexer										= 0;
int   txtLabel_Volume_X						  = 2;
int   txtLabel_Volume_Y						  = 220;
bool  DropDown_Volume_Dropped			  = false;
bool  DropDown_Volume_Tapped				= false;
bool  DropDown_Volume_UpArrow			  = false;
bool  DropDown_Volume_DownArrow		  = false;
int   VolumeIndexer								  = 0;
int   DropDown_Line_Tapped					= ltNone;
TCHAR VolumeLevels[5][10];



// ================================================================================================
// Loader
// ================================================================================================
void loaderSettingsScreen(DisplayDevice* display) {
	wcscpy(VolumeLevels[0], L"No Sound");
	wcscpy(VolumeLevels[1], L"Low");
	wcscpy(VolumeLevels[2], L"Medium");
	wcscpy(VolumeLevels[3], L"High");
}


// ================================================================================================
// Handler
// ================================================================================================
void handlerSettingsScreen(DisplayDevice* display) {
	if (!ProcessEvents) { ProcessEvents = true; }
	display->Clear(Color(0, 0, 0));
	doStarfield3D(display);
	doITTitleBounce(display);
	display->SetBlending((char)transitionVal);
	int txtLabel_X = 0;
	int txtLabel_Y = 0;
	// Lines
	display->Blit(0, 60, imgCreditsLine);
	display->Blit(0, 290, imgCreditsLine);
	// Return To Main Menu
	if (ReturnToMenuTapped) {
		PFE_drawText(display, pFont, L"Return To Menu", PFE_ALIGN_NONE, ReturnToMenu_X, ReturnToMenu_Y, 255, 255, 0, false);
	} else {
		PFE_drawText(display, pFont, L"Return To Menu", PFE_ALIGN_NONE, ReturnToMenu_X, ReturnToMenu_Y, gradientR, gradientG, gradientB, true);
	}

	// ******************************
	// **** DIFFICULTY DROP_DOWN ****
	// ******************************
	txtLabel_X = txtLabel_Difficulty_X;
	txtLabel_Y = txtLabel_Difficulty_Y;
	// Label
	PFE_drawText(display, pFont, L"Difficulty:", PFE_ALIGN_NONE, txtLabel_X, txtLabel_Y, gradientR, gradientG, gradientB, true);
	// Drop-down box
	if (DropDown_Difficulty_Tapped) {
		display->Blit(txtLabel_X, txtLabel_Y + 18, PFE_DropDown_imgDropDown_1);
	} else {
		display->Blit(txtLabel_X, txtLabel_Y + 18, PFE_DropDown_imgDropDown_0);
	}
	// Current value
	switch (game.difficultyLevel) {
		case dlEasy: {
			PFE_drawText(display, pFont, L"Easy",   PFE_ALIGN_NONE, txtLabel_X + 6, txtLabel_Y + 22, 0, 0, 0, false);
		break; }
		case dlNormal: {
			PFE_drawText(display, pFont, L"Normal", PFE_ALIGN_NONE, txtLabel_X + 6, txtLabel_Y + 22, 0, 0, 0, false);
		break; }
		case dlHard: {
			PFE_drawText(display, pFont, L"Hard",   PFE_ALIGN_NONE, txtLabel_X + 6, txtLabel_Y + 22, 0, 0, 0, false);
		break; }
	}

	// ************************
	// **** FONT DROP DOWN ****
	// ************************
	txtLabel_X = txtLabel_Font_X;
	txtLabel_Y = txtLabel_Font_Y;
	// Label
	PFE_drawText(display, pFont, L"Font:", PFE_ALIGN_NONE, txtLabel_X, txtLabel_Y, gradientR, gradientG, gradientB, true);
	// Drop-down box
	if (DropDown_Font_Tapped) {
		display->Blit(txtLabel_X, txtLabel_Y + 18, PFE_DropDown_imgDropDown_1);
	} else {
		display->Blit(txtLabel_X, txtLabel_Y + 18, PFE_DropDown_imgDropDown_0);
	}
	// Current value
	PFE_drawText(display, pFont, fontNames[game.fontIndex], PFE_ALIGN_NONE, txtLabel_X + 6, txtLabel_Y + 22, 0, 0, 0, false);

	// ***********************
	// **** QAC DROP DOWN ****
	// ***********************
	txtLabel_X = txtLabel_QAC_X;
	txtLabel_Y = txtLabel_QAC_Y;
	// Label
	PFE_drawText(display, pFont, L"QAC Pack:", PFE_ALIGN_NONE, txtLabel_X, txtLabel_Y, gradientR, gradientG, gradientB, true);
	// Drop-down box
	if (DropDown_QAC_Tapped) {
		display->Blit(txtLabel_X, txtLabel_Y + 18, PFE_DropDown_imgDropDown_1);
	} else {
		display->Blit(txtLabel_X, txtLabel_Y + 18, PFE_DropDown_imgDropDown_0);
	}
	// Current value
	PFE_drawText(display, pFont, QACFiles[game.QACIndex].fileName, PFE_ALIGN_NONE, txtLabel_X + 6, txtLabel_Y + 22, 0, 0, 0, false);

	// **************************
	// **** VOLUME DROP DOWN ****
	// **************************
	txtLabel_X = txtLabel_Volume_X;
	txtLabel_Y = txtLabel_Volume_Y;
	// Label
	PFE_drawText(display, pFont, L"Volume:", PFE_ALIGN_NONE, txtLabel_X, txtLabel_Y, gradientR, gradientG, gradientB, true);
	// Drop-down box
	if (DropDown_QAC_Tapped) {
		display->Blit(txtLabel_X, txtLabel_Y + 18, PFE_DropDown_imgDropDown_1);
	} else {
		display->Blit(txtLabel_X, txtLabel_Y + 18, PFE_DropDown_imgDropDown_0);
	}
	// Current value
	switch (game.volumeLevel) {
		case vlNoSound: {
			PFE_drawText(display, pFont, L"No Sound", PFE_ALIGN_NONE, txtLabel_X + 6, txtLabel_Y + 22, 0, 0, 0, false);
		break; }
		case vlLow: {
			PFE_drawText(display, pFont, L"Low",			PFE_ALIGN_NONE, txtLabel_X + 6, txtLabel_Y + 22, 0, 0, 0, false);
		break; }
		case vlMedium: {
			PFE_drawText(display, pFont, L"Medium",   PFE_ALIGN_NONE, txtLabel_X + 6, txtLabel_Y + 22, 0, 0, 0, false);
		break; }
		case vlHigh: {
			PFE_drawText(display, pFont, L"High",			PFE_ALIGN_NONE, txtLabel_X + 6, txtLabel_Y + 22, 0, 0, 0, false);
		break; }
	}


	// ========================================================================================================

	// #####################################
	// ##### DIFFICULTY DROP DOWN DOWN #####
	// #####################################
	if (DropDown_Difficulty_Dropped) {
		txtLabel_X = txtLabel_Difficulty_X;
		txtLabel_Y = txtLabel_Difficulty_Y;
		// Draw the drop-down box, plain or hightlighted line version as appropriate
		switch (DropDown_Line_Tapped) {
			case ltNone: {
				display->Blit(txtLabel_X, txtLabel_Y + 40, PFE_DropDown_imgDropBox);
			break; }
			case ltOne: {
				display->Blit(txtLabel_X, txtLabel_Y + 40, PFE_DropDown_imgLineOne);
			break; }
			case ltTwo: {
				display->Blit(txtLabel_X, txtLabel_Y + 40, PFE_DropDown_imgLineTwo);
			break; }
			case ltThree: {
				display->Blit(txtLabel_X, txtLabel_Y + 40, PFE_DropDown_imgLineThree);
			break; }
		}
		// Values
		PFE_drawText(display, pFont, L"Easy",   PFE_ALIGN_NONE, txtLabel_X + 6, txtLabel_Y + 44, 0, 0, 0, false);
		PFE_drawText(display, pFont, L"Normal", PFE_ALIGN_NONE, txtLabel_X + 6, txtLabel_Y + 62, 0, 0, 0, false);
		PFE_drawText(display, pFont, L"Hard",   PFE_ALIGN_NONE, txtLabel_X + 6, txtLabel_Y + 80, 0, 0, 0, false);
	}

	// ###############################
	// ##### FONT DROP DOWN DOWN #####
	// ###############################
	if (DropDown_Font_Dropped) {
		txtLabel_X = txtLabel_Font_X;
		txtLabel_Y = txtLabel_Font_Y;
		// Draw the drop-down box, plain or hightlighted line version as appropriate
		switch (DropDown_Line_Tapped) {
			case ltNone: {
				display->Blit(txtLabel_X, txtLabel_Y + 40, PFE_DropDown_imgDropBox);
			break; }
			case ltOne: {
				display->Blit(txtLabel_X, txtLabel_Y + 40, PFE_DropDown_imgLineOne);
			break; }
			case ltTwo: {
				display->Blit(txtLabel_X, txtLabel_Y + 40, PFE_DropDown_imgLineTwo);
			break; }
			case ltThree: {
				display->Blit(txtLabel_X, txtLabel_Y + 40, PFE_DropDown_imgLineThree);
			break; }
		}
		// Arrows and divider
		if (DropDown_Font_UpArrow) {
			display->Blit(txtLabel_X + 134, txtLabel_Y + 40, PFE_DropDown_imgUpArrow_1);
		} else {
			display->Blit(txtLabel_X + 134, txtLabel_Y + 40, PFE_DropDown_imgUpArrow_0);
		}
		display->Blit(txtLabel_X + 134, txtLabel_Y + 56, PFE_DropDown_imgArrowDivider);
		if (DropDown_Font_DownArrow) {
			display->Blit(txtLabel_X + 134, txtLabel_Y + 82, PFE_DropDown_imgDownArrow_1);
		} else {
			display->Blit(txtLabel_X + 134, txtLabel_Y + 82, PFE_DropDown_imgDownArrow_0);
		}
		// Values
		if (pFonts[fontIndexer + 2] == NULL) { fontIndexer = fontIndexer - 2; }
		if (pFonts[fontIndexer + 1] == NULL) { fontIndexer = fontIndexer - 1; }
		PFE_drawText(display, pFont, fontNames[fontIndexer],     PFE_ALIGN_NONE, txtLabel_X + 6, txtLabel_Y + 44, 0, 0, 0, false);
		PFE_drawText(display, pFont, fontNames[fontIndexer + 1], PFE_ALIGN_NONE, txtLabel_X + 6, txtLabel_Y + 62, 0, 0, 0, false);
		PFE_drawText(display, pFont, fontNames[fontIndexer + 2], PFE_ALIGN_NONE, txtLabel_X + 6, txtLabel_Y + 80, 0, 0, 0, false);
	}

	// ##############################
	// ##### QAC DROP DOWN DOWN #####
	// ##############################
	if (DropDown_QAC_Dropped) {
		txtLabel_X = txtLabel_QAC_X;
		txtLabel_Y = txtLabel_QAC_Y;
		// Draw the drop-down box, plain or hightlighted line version as appropriate
		switch (DropDown_Line_Tapped) {
			case ltNone: {
				display->Blit(txtLabel_X, txtLabel_Y + 40, PFE_DropDown_imgDropBox);
			break; }
			case ltOne: {
				display->Blit(txtLabel_X, txtLabel_Y + 40, PFE_DropDown_imgLineOne);
			break; }
			case ltTwo: {
				display->Blit(txtLabel_X, txtLabel_Y + 40, PFE_DropDown_imgLineTwo);
			break; }
			case ltThree: {
				display->Blit(txtLabel_X, txtLabel_Y + 40, PFE_DropDown_imgLineThree);
			break; }
		}
		// Arrows and divider
		if (DropDown_QAC_UpArrow) {
			display->Blit(txtLabel_X + 134, txtLabel_Y + 40, PFE_DropDown_imgUpArrow_1);
		} else {
			display->Blit(txtLabel_X + 134, txtLabel_Y + 40, PFE_DropDown_imgUpArrow_0);
		}
		display->Blit(txtLabel_X + 134, txtLabel_Y + 56, PFE_DropDown_imgArrowDivider);
		if (DropDown_QAC_DownArrow) {
			display->Blit(txtLabel_X + 134, txtLabel_Y + 82, PFE_DropDown_imgDownArrow_1);
		} else {
			display->Blit(txtLabel_X + 134, txtLabel_Y + 82, PFE_DropDown_imgDownArrow_0);
		}
		// Values
		if (QACFiles_Count > 2) {
			if (wcscmp(QACFiles[QACIndexer + 2].fileName, L"") == 0) { QACIndexer = QACIndexer - 2; }
			if (wcscmp(QACFiles[QACIndexer + 1].fileName, L"") == 0) { QACIndexer = QACIndexer - 1; }
		}
		PFE_drawText(display, pFont, QACFiles[QACIndexer].fileName,			PFE_ALIGN_NONE, txtLabel_X + 6, txtLabel_Y + 44, 0, 0, 0, false);
		if (QACFiles_Count > 0) {
			PFE_drawText(display, pFont, QACFiles[QACIndexer + 1].fileName, PFE_ALIGN_NONE, txtLabel_X + 6, txtLabel_Y + 62, 0, 0, 0, false);
		}
		if (QACFiles_Count > 1) {
			PFE_drawText(display, pFont, QACFiles[QACIndexer + 2].fileName, PFE_ALIGN_NONE, txtLabel_X + 6, txtLabel_Y + 80, 0, 0, 0, false), false;
		}
	}

	// #################################
	// ##### VOLUME DROP DOWN DOWN #####
	// #################################
	if (DropDown_Volume_Dropped) {
		txtLabel_X = txtLabel_Volume_X;
		txtLabel_Y = txtLabel_Volume_Y;
		// Draw the drop-down box, plain or hightlighted line version as appropriate
		switch (DropDown_Line_Tapped) {
			case ltNone: {
				display->Blit(txtLabel_X, txtLabel_Y + 40, PFE_DropDown_imgDropBox);
			break; }
			case ltOne: {
				display->Blit(txtLabel_X, txtLabel_Y + 40, PFE_DropDown_imgLineOne);
			break; }
			case ltTwo: {
				display->Blit(txtLabel_X, txtLabel_Y + 40, PFE_DropDown_imgLineTwo);
			break; }
			case ltThree: {
				display->Blit(txtLabel_X, txtLabel_Y + 40, PFE_DropDown_imgLineThree);
			break; }
		}
		// Arrows and divider
		if (DropDown_Volume_UpArrow) {
			display->Blit(txtLabel_X + 134, txtLabel_Y + 40, PFE_DropDown_imgUpArrow_1);
		} else {
			display->Blit(txtLabel_X + 134, txtLabel_Y + 40, PFE_DropDown_imgUpArrow_0);
		}
		display->Blit(txtLabel_X + 134, txtLabel_Y + 56, PFE_DropDown_imgArrowDivider);
		if (DropDown_Volume_DownArrow) {
			display->Blit(txtLabel_X + 134, txtLabel_Y + 82, PFE_DropDown_imgDownArrow_1);
		} else {
			display->Blit(txtLabel_X + 134, txtLabel_Y + 82, PFE_DropDown_imgDownArrow_0);
		}
		// Values
		if (wcscmp(VolumeLevels[VolumeIndexer + 2], L"") == 0) { VolumeIndexer = VolumeIndexer - 2; }
		if (wcscmp(VolumeLevels[VolumeIndexer + 1], L"") == 0) { VolumeIndexer = VolumeIndexer - 1; }
		PFE_drawText(display, pFont, VolumeLevels[VolumeIndexer],			PFE_ALIGN_NONE, txtLabel_X + 6, txtLabel_Y + 44, 0, 0, 0, false);
		PFE_drawText(display, pFont, VolumeLevels[VolumeIndexer + 1], PFE_ALIGN_NONE, txtLabel_X + 6, txtLabel_Y + 62, 0, 0, 0, false);
		PFE_drawText(display, pFont, VolumeLevels[VolumeIndexer + 2], PFE_ALIGN_NONE, txtLabel_X + 6, txtLabel_Y + 80, 0, 0, 0, false), false;
	}

	display->SetBlending(255);
	// Fade
	if (doTransition) {
		if (transitionDir == tdIn) {
			transitionVal = transitionVal + 25;
			if (transitionVal > 255) {
				doTransition		 = false;
				transitionVal		 = 255;
				transitionDir		 = tdNone;
				transitionScreen = tsNone;
			}
		} else {
			transitionVal = transitionVal - 25;
			if (transitionVal < 0) {
				doTransition	= true;
				transitionVal = 0;
				transitionDir = tdIn;
				ProcessEvents = false;
				game.currentScreen = csMainMenuScreen;
			}
		}
	}

}


// ================================================================================================
// Releaser
// ================================================================================================
void releaserSettingsScreen() {
}


// ================================================================================================
// Event Handlers
// ================================================================================================
void stylusDownSettingsScreen(Point stylusPoint) {
	if (!doTransition) {
		Rect itemBounds;
		// Only do this block if no drop-down is down
		if (!DropDown_Difficulty_Dropped && !DropDown_Font_Dropped && !DropDown_QAC_Dropped && !DropDown_Volume_Dropped) {
			// Difficulty Drop-down button
			itemBounds.Set(txtLabel_Difficulty_X, txtLabel_Difficulty_Y + 18, txtLabel_Difficulty_X + 150, txtLabel_Difficulty_Y + 40);
			if (itemBounds.Contains(stylusPoint)) { 
				DropDown_Difficulty_Tapped = true;
				return;
			}
			// Font Drop-down button
			itemBounds.Set(txtLabel_Font_X, txtLabel_Font_Y + 18, txtLabel_Font_X + 150, txtLabel_Font_Y + 40);
			if (itemBounds.Contains(stylusPoint)) { 
				DropDown_Font_Tapped = true;
				return;
			}
			// QAC Drop-down button
			itemBounds.Set(txtLabel_QAC_X, txtLabel_QAC_Y + 18, txtLabel_QAC_X + 150, txtLabel_QAC_Y + 40);
			if (itemBounds.Contains(stylusPoint)) {
				DropDown_QAC_Tapped = true;
				return;
			}
			// Volum level Drop-down button
			itemBounds.Set(txtLabel_Volume_X, txtLabel_Volume_Y + 18, txtLabel_Volume_X + 150, txtLabel_Volume_Y + 40);
			if (itemBounds.Contains(stylusPoint)) {
				DropDown_Volume_Tapped = true;
				return;
			}
			// Return To Main Menu
			itemBounds.Set(ReturnToMenu_X, ReturnToMenu_Y, ReturnToMenu_X + ReturnToMenu_Width, ReturnToMenu_Y + ReturnToMenu_Height);
			if (itemBounds.Contains(stylusPoint)) { 
				ReturnToMenuTapped = true;
				return;
			}
		}
		// Only do this block if Difficulty drop-down is dropped down
		if (DropDown_Difficulty_Dropped) {
			// First item
			itemBounds.Set(txtLabel_Difficulty_X + 2, txtLabel_Difficulty_Y + 44, txtLabel_Difficulty_X + 130, txtLabel_Difficulty_Y + 60);
			if (itemBounds.Contains(stylusPoint)) { 
				DropDown_Line_Tapped = ltOne;
				return;
			}
			// Second item
			itemBounds.Set(txtLabel_Difficulty_X + 2, txtLabel_Difficulty_Y + 62, txtLabel_Difficulty_X + 130, txtLabel_Difficulty_Y + 78);
			if (itemBounds.Contains(stylusPoint)) { 
				DropDown_Line_Tapped = ltTwo;
				return;
			}
			// Third item
			itemBounds.Set(txtLabel_Difficulty_X + 2, txtLabel_Difficulty_Y + 80, txtLabel_Difficulty_X + 130, txtLabel_Difficulty_Y + 96);
			if (itemBounds.Contains(stylusPoint)) { 
				DropDown_Line_Tapped = ltThree;
				return;
			}
		}
		// Only do this block if Font drop-down is dropped down
		if (DropDown_Font_Dropped) {
			// Font Drop-down up arrow
			itemBounds.Set(txtLabel_Font_X + 134, txtLabel_Font_Y + 40, txtLabel_Font_X + 150, txtLabel_Font_Y + 56);
			if (itemBounds.Contains(stylusPoint)) { 
				DropDown_Font_UpArrow		= true;
				return;
			}
			// Font Drop-down down arrow
			itemBounds.Set(txtLabel_Font_X + 134, txtLabel_Font_Y + 82, txtLabel_Font_X + 150, txtLabel_Font_Y + 98);
			if (itemBounds.Contains(stylusPoint)) { 
				DropDown_Font_DownArrow = true;
				return;
			}
			// First item
			itemBounds.Set(txtLabel_Font_X + 2, txtLabel_Font_Y + 44, txtLabel_Font_X + 130, txtLabel_Font_Y + 60);
			if (itemBounds.Contains(stylusPoint)) { 
				DropDown_Line_Tapped = ltOne;
				return;
			}
			// Second item
			itemBounds.Set(txtLabel_Font_X + 2, txtLabel_Font_Y + 62, txtLabel_Font_X + 130, txtLabel_Font_Y + 78);
			if (itemBounds.Contains(stylusPoint)) { 
				DropDown_Line_Tapped = ltTwo;
				return;
			}
			// Third item
			itemBounds.Set(txtLabel_Font_X + 2, txtLabel_Font_Y + 80, txtLabel_Font_X + 130, txtLabel_Font_Y + 96);
			if (itemBounds.Contains(stylusPoint)) { 
				DropDown_Line_Tapped = ltThree;
				return;
			}
		}
		// Only do this block if QAC drop-down is dropped down
		if (DropDown_QAC_Dropped) {
			// QAC Drop-down up arrow
			itemBounds.Set(txtLabel_QAC_X + 134, txtLabel_QAC_Y + 40, txtLabel_QAC_X + 150, txtLabel_QAC_Y + 56);
			if (itemBounds.Contains(stylusPoint)) { 
				DropDown_QAC_UpArrow = true;
				return;
			}
			// QAC Drop-down down arrow
			itemBounds.Set(txtLabel_QAC_X + 134, txtLabel_QAC_Y + 82, txtLabel_QAC_X + 150, txtLabel_QAC_Y + 98);
			if (itemBounds.Contains(stylusPoint)) { 
				DropDown_QAC_DownArrow = true;
				return;
			}
			// First item
			itemBounds.Set(txtLabel_QAC_X + 2, txtLabel_QAC_Y + 44, txtLabel_QAC_X + 130, txtLabel_QAC_Y + 60);
			if (itemBounds.Contains(stylusPoint)) { 
				DropDown_Line_Tapped = ltOne;
				return;
			}
			// Second item
			if (QACFiles_Count > 0) {
				itemBounds.Set(txtLabel_QAC_X + 2, txtLabel_QAC_Y + 62, txtLabel_QAC_X + 130, txtLabel_QAC_Y + 78);
				if (itemBounds.Contains(stylusPoint)) { 
					DropDown_Line_Tapped = ltTwo;
					return;
				}
			}
			// Third item
			if (QACFiles_Count > 1) {
				itemBounds.Set(txtLabel_QAC_X + 2, txtLabel_QAC_Y + 80, txtLabel_QAC_X + 130, txtLabel_QAC_Y + 96);
				if (itemBounds.Contains(stylusPoint)) { 
					DropDown_Line_Tapped = ltThree;
					return;
				}
			}
		}
		// Only do this block if Volume level drop-down is dropped down
		if (DropDown_Volume_Dropped) {
			// Volume Drop-down up arrow
			itemBounds.Set(txtLabel_Volume_X + 134, txtLabel_Volume_Y + 40, txtLabel_Volume_X + 150, txtLabel_Volume_Y + 56);
			if (itemBounds.Contains(stylusPoint)) { 
				DropDown_Volume_UpArrow = true;
				return;
			}
			// Volume Drop-down down arrow
			itemBounds.Set(txtLabel_Volume_X + 134, txtLabel_Volume_Y + 82, txtLabel_Volume_X + 150, txtLabel_Volume_Y + 98);
			if (itemBounds.Contains(stylusPoint)) { 
				DropDown_Volume_DownArrow = true;
				return;
			}
			// First item
			itemBounds.Set(txtLabel_Volume_X + 2, txtLabel_Volume_Y + 44, txtLabel_Volume_X + 130, txtLabel_Volume_Y + 60);
			if (itemBounds.Contains(stylusPoint)) { 
				DropDown_Line_Tapped = ltOne;
				return;
			}
			// Second item
			itemBounds.Set(txtLabel_Volume_X + 2, txtLabel_Volume_Y + 62, txtLabel_Volume_X + 130, txtLabel_Volume_Y + 78);
			if (itemBounds.Contains(stylusPoint)) { 
				DropDown_Line_Tapped = ltTwo;
				return;
			}
			// Third item
			itemBounds.Set(txtLabel_Volume_X + 2, txtLabel_Volume_Y + 80, txtLabel_Volume_X + 130, txtLabel_Volume_Y + 96);
			if (itemBounds.Contains(stylusPoint)) { 
				DropDown_Line_Tapped = ltThree;
				return;
			}
		}
	}
}

void stylusMoveSettingsScreen(Point stylusPoint) {
}

void stylusUpSettingsScreen(Point stylusPoint) {
	if (!doTransition) {
		// Some resets we need to do on any lift event
		DropDown_Font_UpArrow			 = false;
		DropDown_Font_DownArrow		 = false;
		DropDown_QAC_UpArrow			 = false;
		DropDown_QAC_DownArrow		 = false;
		DropDown_Volume_UpArrow		 = false;
		DropDown_Volume_DownArrow	 = false;
		DropDown_Difficulty_Tapped = false;
		DropDown_Font_Tapped			 = false;
		DropDown_QAC_Tapped				 = false;
		DropDown_Volume_Tapped		 = false;
		Rect itemBounds;
		// Only do this block if no drop-down is down
		if (!DropDown_Difficulty_Dropped && !DropDown_Font_Dropped && !DropDown_QAC_Dropped && !DropDown_Volume_Dropped) {
			// Difficulty Drop-down button
			itemBounds.Set(txtLabel_Difficulty_X, txtLabel_Difficulty_Y + 18, txtLabel_Difficulty_X + 150, txtLabel_Difficulty_Y + 40);
			if (itemBounds.Contains(stylusPoint)) { 
				game.itPlaySFX(&sfxDropDownDropped, false);
				DropDown_Difficulty_Dropped = !DropDown_Difficulty_Dropped;
				return;
			}
			// Font Drop-down button
			itemBounds.Set(txtLabel_Font_X, txtLabel_Font_Y + 18, txtLabel_Font_X + 150, txtLabel_Font_Y + 40);
			if (itemBounds.Contains(stylusPoint)) { 
				game.itPlaySFX(&sfxDropDownDropped, false);
				DropDown_Font_Dropped = !DropDown_Font_Dropped;
				fontIndexer = game.fontIndex;
				return;
			}
			// QAC Drop-down button
			itemBounds.Set(txtLabel_QAC_X, txtLabel_QAC_Y + 18, txtLabel_QAC_X + 150, txtLabel_QAC_Y + 40);
			if (itemBounds.Contains(stylusPoint)) {
				game.itPlaySFX(&sfxDropDownDropped, false);
				DropDown_QAC_Dropped = !DropDown_QAC_Dropped;
				return;
			}
			// Volume Drop-down button
			itemBounds.Set(txtLabel_Volume_X, txtLabel_Volume_Y + 18, txtLabel_Volume_X + 150, txtLabel_Volume_Y + 40);
			if (itemBounds.Contains(stylusPoint)) { 
				game.itPlaySFX(&sfxDropDownDropped, false);
				DropDown_Volume_Dropped = !DropDown_Volume_Dropped;
				if (game.volumeLevel == vlHigh) { VolumeIndexer = 1; } else { VolumeIndexer = 0; }
				return;
			}
			// Return To Main Menu
			itemBounds.Set(ReturnToMenu_X, ReturnToMenu_Y, ReturnToMenu_X + ReturnToMenu_Width, ReturnToMenu_Y + ReturnToMenu_Height);
			if (itemBounds.Contains(stylusPoint) && ReturnToMenuTapped) { 
				game.itPlaySFX(&sfxReturnToMenu, false);
				ReturnToMenuTapped = false;
				doTransition			 = true;
				transitionVal			 = 255;
				transitionScreen	 = tsNone;
				transitionDir			 = tdOut;
				return;
			}
		}
		// Only do this block if the Difficulty drop-down is down
		if (DropDown_Difficulty_Dropped) {
			// Item 1
			itemBounds.Set(txtLabel_Difficulty_X + 2, txtLabel_Difficulty_Y + 44, txtLabel_Difficulty_X + 130, txtLabel_Difficulty_Y + 60);
			if (itemBounds.Contains(stylusPoint) && DropDown_Line_Tapped == ltOne) { 
				game.itPlaySFX(&sfxDropDownItemSelected, false);
				game.difficultyLevel = dlEasy;
				goto ResetStuff;
			}
			// Item 2
			itemBounds.Set(txtLabel_Difficulty_X + 2, txtLabel_Difficulty_Y + 62, txtLabel_Difficulty_X + 130, txtLabel_Difficulty_Y + 78);
			if (itemBounds.Contains(stylusPoint) && DropDown_Line_Tapped == ltTwo) { 
				game.itPlaySFX(&sfxDropDownItemSelected, false);
				game.difficultyLevel = dlNormal;
				goto ResetStuff;
			}
			// Item 3
			itemBounds.Set(txtLabel_Difficulty_X + 2, txtLabel_Difficulty_Y + 80, txtLabel_Difficulty_X + 130, txtLabel_Difficulty_Y + 96);
			if (itemBounds.Contains(stylusPoint) && DropDown_Line_Tapped == ltThree) { 
				game.itPlaySFX(&sfxDropDownItemSelected, false);
				game.difficultyLevel = dlHard;
				goto ResetStuff;
			}
		}
		// Only do this block if the Font drop-down is down
		if (DropDown_Font_Dropped) {
			// Up arrow
			itemBounds.Set(txtLabel_Font_X + 134, txtLabel_Font_Y + 40, txtLabel_Font_X + 150, txtLabel_Font_Y + 56);
			if (itemBounds.Contains(stylusPoint)) { 
				game.itPlaySFX(&sfxDropDownButtons, false);
				if (fontIndexer > 0) { 
					fontIndexer--;
				}
				return;
			}
			// Down arrow
			itemBounds.Set(txtLabel_Font_X + 134, txtLabel_Font_Y + 82, txtLabel_Font_X + 150, txtLabel_Font_Y + 98);
			if (itemBounds.Contains(stylusPoint)) { 
				game.itPlaySFX(&sfxDropDownButtons, false);
				if (pFonts[fontIndexer + 3] != NULL) {
					fontIndexer++;
				}
				return;
			}
			// Item 1
			itemBounds.Set(txtLabel_Font_X + 2, txtLabel_Font_Y + 44, txtLabel_Font_X + 130, txtLabel_Font_Y + 60);
			if (itemBounds.Contains(stylusPoint) && DropDown_Line_Tapped == ltOne) { 
				game.itPlaySFX(&sfxDropDownItemSelected, false);
				game.fontIndex = fontIndexer;
				game.writeHSSFile();
				pFont = pFonts[game.fontIndex];
				goto ResetStuff;
			}
			// Item 2
			itemBounds.Set(txtLabel_Font_X + 2, txtLabel_Font_Y + 62, txtLabel_Font_X + 130, txtLabel_Font_Y + 78);
			if (itemBounds.Contains(stylusPoint) && DropDown_Line_Tapped == ltTwo) { 
				game.itPlaySFX(&sfxDropDownItemSelected, false);
				game.fontIndex = fontIndexer + 1;
				game.writeHSSFile();
				pFont = pFonts[game.fontIndex];
				goto ResetStuff;
			}
			// Iten 3
			itemBounds.Set(txtLabel_Font_X + 2, txtLabel_Font_Y + 80, txtLabel_Font_X + 130, txtLabel_Font_Y + 96);
			if (itemBounds.Contains(stylusPoint) && DropDown_Line_Tapped == ltThree) { 
				game.itPlaySFX(&sfxDropDownItemSelected, false);
				game.fontIndex = fontIndexer + 2;
				game.writeHSSFile();
				pFont = pFonts[game.fontIndex];
				goto ResetStuff;
			}
		}
		// Only do this block if the QAC drop-down is down
		if (DropDown_QAC_Dropped) {
			// Up arrow
			itemBounds.Set(txtLabel_QAC_X + 134, txtLabel_QAC_Y + 40, txtLabel_QAC_X + 150, txtLabel_QAC_Y + 56);
			if (itemBounds.Contains(stylusPoint)) { 
				game.itPlaySFX(&sfxDropDownButtons, false);
				if (QACIndexer > 0) { 
					QACIndexer--;
				}
				return;
			}
			// Down arrow
			itemBounds.Set(txtLabel_QAC_X + 134, txtLabel_QAC_Y + 82, txtLabel_QAC_X + 150, txtLabel_QAC_Y + 98);
			if (itemBounds.Contains(stylusPoint)) { 
				game.itPlaySFX(&sfxDropDownButtons, false);
				if (wcscmp(QACFiles[QACIndexer + 3].fileName, L"") != 0) {
					QACIndexer++;
				}
				return;
			}
			// Item 1
			itemBounds.Set(txtLabel_QAC_X + 2, txtLabel_QAC_Y + 44, txtLabel_QAC_X + 130, txtLabel_QAC_Y + 60);
			if (itemBounds.Contains(stylusPoint) && DropDown_Line_Tapped == ltOne) { 
				game.itPlaySFX(&sfxDropDownItemSelected, false);
				game.QACIndex = QACIndexer;
				if (wcscmp(QACFiles[game.QACIndex].fileName, L"Built-In") == 0) {
					loadQAs(L"");
				} else {
					TCHAR fullPath[MAX_PATH] = L"";
					wcscat(fullPath, game.gameEXEPath);
					wcscat(fullPath, QACFiles[game.QACIndex].fileName);
					wcscat(fullPath, L".qac");
					loadQAs(fullPath);
				}
				goto ResetStuff;
			}
			// Item 2
			itemBounds.Set(txtLabel_QAC_X + 2, txtLabel_QAC_Y + 62, txtLabel_QAC_X + 130, txtLabel_QAC_Y + 78);
			if (itemBounds.Contains(stylusPoint) && DropDown_Line_Tapped == ltTwo) { 
				game.itPlaySFX(&sfxDropDownItemSelected, false);
				if (QACFiles_Count > 0) {
					game.QACIndex = QACIndexer + 1;
					if (wcscmp(QACFiles[game.QACIndex].fileName, L"Built-In") == 0) {
						loadQAs(L"");
					} else {
						TCHAR fullPath[MAX_PATH] = L"";
						wcscat(fullPath, game.gameEXEPath);
						wcscat(fullPath, QACFiles[game.QACIndex].fileName);
						wcscat(fullPath, L".qac");
						loadQAs(fullPath);
					}
				}
				goto ResetStuff;
			}
			// Iten 3
			itemBounds.Set(txtLabel_QAC_X + 2, txtLabel_QAC_Y + 80, txtLabel_QAC_X + 130, txtLabel_QAC_Y + 96);
			if (itemBounds.Contains(stylusPoint) && DropDown_Line_Tapped == ltThree) { 
				if (QACFiles_Count > 1) {
					game.itPlaySFX(&sfxDropDownItemSelected, false);
					game.QACIndex = QACIndexer + 2;
					if (wcscmp(QACFiles[game.QACIndex].fileName, L"Built-In") == 0) {
						loadQAs(L"");
					} else {
						TCHAR fullPath[MAX_PATH] = L"";
						wcscat(fullPath, game.gameEXEPath);
						wcscat(fullPath, QACFiles[game.QACIndex].fileName);
						wcscat(fullPath, L".qac");
						loadQAs(fullPath);
					}
				}
				goto ResetStuff;
			}
		}
		// Only do this block if the Volume drop-down is down
		if (DropDown_Volume_Dropped) {
			// Up arrow
			itemBounds.Set(txtLabel_Volume_X + 134, txtLabel_Volume_Y + 40, txtLabel_Volume_X + 150, txtLabel_Volume_Y + 56);
			if (itemBounds.Contains(stylusPoint)) { 
				game.itPlaySFX(&sfxDropDownButtons, false);
				if (VolumeIndexer > 0) { 
					VolumeIndexer--;
				}
				return;
			}
			// Down arrow
			itemBounds.Set(txtLabel_Volume_X + 134, txtLabel_Volume_Y + 82, txtLabel_Volume_X + 150, txtLabel_Volume_Y + 98);
			if (itemBounds.Contains(stylusPoint)) { 
				game.itPlaySFX(&sfxDropDownButtons, false);
				if (wcscmp(VolumeLevels[VolumeIndexer + 3], L"") != 0) {
					VolumeIndexer++;
				}
				return;
			}
			// Item 1
			itemBounds.Set(txtLabel_Volume_X + 2, txtLabel_Volume_Y + 44, txtLabel_Volume_X + 130, txtLabel_Volume_Y + 60);
			if (itemBounds.Contains(stylusPoint) && DropDown_Line_Tapped == ltOne) { 
				game.itPlaySFX(&sfxDropDownItemSelected, false);
				if (VolumeIndexer == 0) { 
					game.volumeLevel = vlNoSound;
				} else {
					game.volumeLevel = vlLow;
				}
				game.SetVolumeLevel();
				game.writeHSSFile();
				VolumeIndexer = 0;
				goto ResetStuff;
			}
			// Item 2
			itemBounds.Set(txtLabel_Volume_X + 2, txtLabel_Volume_Y + 62, txtLabel_Volume_X + 130, txtLabel_Volume_Y + 78);
			if (itemBounds.Contains(stylusPoint) && DropDown_Line_Tapped == ltTwo) { 
				game.itPlaySFX(&sfxDropDownItemSelected, false);
				if (VolumeIndexer == 0) { 
					game.volumeLevel = vlLow;
				} else {
					game.volumeLevel = vlMedium;
				}
				game.SetVolumeLevel();
				game.writeHSSFile();
				VolumeIndexer = 0;
				goto ResetStuff;
			}
			// Iten 3
			itemBounds.Set(txtLabel_Volume_X + 2, txtLabel_Volume_Y + 80, txtLabel_Volume_X + 130, txtLabel_Volume_Y + 96);
			if (itemBounds.Contains(stylusPoint) && DropDown_Line_Tapped == ltThree) { 
				game.itPlaySFX(&sfxDropDownItemSelected, false);
				if (VolumeIndexer == 0) { 
					game.volumeLevel = vlMedium;
				} else {
					game.volumeLevel = vlHigh;
				}
				game.SetVolumeLevel();
				game.writeHSSFile();
				VolumeIndexer = 0;
				goto ResetStuff;
			}
		}
		// More reset stuff (only done if none of the above conditions are met, and must be done after all the above, NOT before!)
		ResetStuff:
		ReturnToMenuTapped					= false;
		DropDown_Line_Tapped			  = ltNone;
		DropDown_Difficulty_Dropped = false;
		DropDown_Font_Dropped				= false;
		DropDown_QAC_Dropped				= false;
		DropDown_Volume_Dropped			= false;
	} // !doTransition
}

void keyDownSettingsScreen(int key) {
}

void keyUpSettingsScreen(int key) {
}