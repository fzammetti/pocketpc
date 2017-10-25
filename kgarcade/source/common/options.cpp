
#include "main.h"


namespace ns_Options {


// ****************************************************************************************************************
// Globals
// ****************************************************************************************************************
TCHAR volumeLevels[6][12] = { TEXT("No Sound"), TEXT("Low"), TEXT("Medium"), TEXT("High") };
bool  PreviousTapped      = false;
bool  NextTapped          = false;
bool  defaultBox          = false;
int   active_option       = 0;
int   key_map_step        = 0;


} // End of namespace


// ****************************************************************************************************************
// ProcessNextFrame handler
// ****************************************************************************************************************
void CGame::pnfOptions(CGapiSurface* backbuffer) {

	using namespace ns_Options;

  // Set up for fading
  GDBLTFASTFX gdbltfastfx;
  gdbltfastfx.dwOpacity = fade_value;
  // Scrolling background
	scrollingBackground(backbuffer);
	// Title
	backbuffer->DrawText(bbCenterPoint, 10, TEXT("Options"), &font1_green, GDDRAWTEXT_CENTER, NULL, GDBLTFAST_OPACITY, &gdbltfastfx);
	// Lines
	backbuffer->BltFast(0, 40, divider_00, NULL, GDBLTFAST_OPACITY, &gdbltfastfx);
  backbuffer->BltFast(0, 290, divider_00, NULL, GDBLTFAST_OPACITY, &gdbltfastfx);
  // Back
  backbuffer->DrawText(bbCenterPoint, 300,  TEXT("COMMAND/Click for Main Menu"), &font1_green, GDDRAWTEXT_CENTER, NULL, GDBLTFAST_OPACITY, &gdbltfastfx);

  int top;

  // *************************************
  // -----****>>>>> Volume <<<<<*****-----
  // *************************************
  top = 60;
  if (active_option == 1) {
    GDFILLRECTFX gdfillrectfx;
    if (fade_function == 0) { // When not fading, it's a 50% blend
      gdfillrectfx.dwOpacity = 128;
    } else { // When fading in or out, use fade_value when < 128
      if (fade_value < 128) {
        gdfillrectfx.dwOpacity = fade_value;
      } else {
        gdfillrectfx.dwOpacity = 128;
      }
    }
    // Blended box
    backbuffer->FillRect(CRect(0, top - 2, 240, top + 26), RGB(240, 240, 240), GDFILLRECT_OPACITY, &gdfillrectfx);
  }
  // Label
  backbuffer->DrawText(2, top + 1,  TEXT("Volume :"), &font1, GDDRAWTEXT_LEFT, NULL, GDBLTFAST_OPACITY, &gdbltfastfx);
  // Value
  backbuffer->DrawText(73, top + 1,  volumeLevels[volumeLevel], &font1_green, GDDRAWTEXT_LEFT, NULL, GDBLTFAST_OPACITY, &gdbltfastfx);
  // Arrows
  if (active_option == 1) {
    if (PreviousTapped) {
      backbuffer->BltFast(185, top, gfx_ins_prev_1, NULL, GDBLTFAST_KEYSRC | GDBLTFAST_OPACITY, &gdbltfastfx);
    } else {
      backbuffer->BltFast(185, top, gfx_ins_prev_0, NULL, GDBLTFAST_KEYSRC | GDBLTFAST_OPACITY, &gdbltfastfx);
    }
    if (NextTapped) {
      backbuffer->BltFast(214, top, gfx_ins_next_1, NULL, GDBLTFAST_KEYSRC | GDBLTFAST_OPACITY, &gdbltfastfx);
    } else {
      backbuffer->BltFast(214, top, gfx_ins_next_0, NULL, GDBLTFAST_KEYSRC | GDBLTFAST_OPACITY, &gdbltfastfx);
    }
  }

  // *****************************************
  // -----****>>>>> Frame Rate <<<<<*****-----
  // *****************************************
  top = 100;
  if (active_option == 2) {
    GDFILLRECTFX gdfillrectfx;
    if (fade_function == 0) { // When not fading, it's a 50% blend
      gdfillrectfx.dwOpacity = 128;
    } else { // When fading in or out, use fade_value when < 128
      if (fade_value < 128) {
        gdfillrectfx.dwOpacity = fade_value;
      } else {
        gdfillrectfx.dwOpacity = 128;
      }
    }
    // Blended box
    backbuffer->FillRect(CRect(0, top - 2, 240, top + 26), RGB(240, 240, 240), GDFILLRECT_OPACITY, &gdfillrectfx);
  }
  // Label
  backbuffer->DrawText(2, top + 1,  TEXT("Show Frame Rate :"), &font1, GDDRAWTEXT_LEFT, NULL, GDBLTFAST_OPACITY, &gdbltfastfx);
  // Arrows
  // Value
	TCHAR szYesNo1[5] = TEXT("");
	if (show_fps) { _tcscpy(szYesNo1, TEXT("Yes")); } else { _tcscpy(szYesNo1, TEXT("No")); }
  backbuffer->DrawText(155, top + 1, szYesNo1, &font1_green, GDDRAWTEXT_LEFT, NULL, GDBLTFAST_OPACITY, &gdbltfastfx);
  // Arrows
  if (active_option == 2) {
    if (PreviousTapped) {
      backbuffer->BltFast(185, top, gfx_ins_prev_1, NULL, GDBLTFAST_KEYSRC | GDBLTFAST_OPACITY, &gdbltfastfx);
    } else {
      backbuffer->BltFast(185, top, gfx_ins_prev_0, NULL, GDBLTFAST_KEYSRC | GDBLTFAST_OPACITY, &gdbltfastfx);
    }
    if (NextTapped) {
      backbuffer->BltFast(214, top, gfx_ins_next_1, NULL, GDBLTFAST_KEYSRC | GDBLTFAST_OPACITY, &gdbltfastfx);
    } else {
      backbuffer->BltFast(214, top, gfx_ins_next_0, NULL, GDBLTFAST_KEYSRC | GDBLTFAST_OPACITY, &gdbltfastfx);
    }
  }

  // *****************************************
  // -----****>>>>> Frame Time <<<<<*****-----
  // *****************************************
  top = 140;
  if (active_option == 3) {
    GDFILLRECTFX gdfillrectfx;
    if (fade_function == 0) { // When not fading, it's a 50% blend
      gdfillrectfx.dwOpacity = 128;
    } else { // When fading in or out, use fade_value when < 128
      if (fade_value < 128) {
        gdfillrectfx.dwOpacity = fade_value;
      } else {
        gdfillrectfx.dwOpacity = 128;
      }
    }
    // Blended box
    backbuffer->FillRect(CRect(0, top - 2, 240, top + 26), RGB(240, 240, 240), GDFILLRECT_OPACITY, &gdfillrectfx);
  }
  // Label
  backbuffer->DrawText(2, 140,  TEXT("Show Frame Time :"), &font1, GDDRAWTEXT_LEFT, NULL, GDBLTFAST_OPACITY, &gdbltfastfx);
  // Arrows
  // Value
	TCHAR szYesNo2[5] = TEXT("");
	if (show_frame_time) { _tcscpy(szYesNo2, TEXT("Yes")); } else { _tcscpy(szYesNo2, TEXT("No")); }
  backbuffer->DrawText(154, top + 1, szYesNo2, &font1_green, GDDRAWTEXT_LEFT, NULL, GDBLTFAST_OPACITY, &gdbltfastfx);
  // Arrows
  if (active_option == 3) {
    if (PreviousTapped) {
      backbuffer->BltFast(185, top, gfx_ins_prev_1, NULL, GDBLTFAST_KEYSRC | GDBLTFAST_OPACITY, &gdbltfastfx);
    } else {
      backbuffer->BltFast(185, top, gfx_ins_prev_0, NULL, GDBLTFAST_KEYSRC | GDBLTFAST_OPACITY, &gdbltfastfx);
    }
    if (NextTapped) {
      backbuffer->BltFast(214, top, gfx_ins_next_1, NULL, GDBLTFAST_KEYSRC | GDBLTFAST_OPACITY, &gdbltfastfx);
    } else {
      backbuffer->BltFast(214, top, gfx_ins_next_0, NULL, GDBLTFAST_KEYSRC | GDBLTFAST_OPACITY, &gdbltfastfx);
    }
  }

  // *******************************************
  // -----****>>>>> Key Mappings <<<<<*****-----
  // *******************************************
  top = 180;
  if (active_option == 4) {
    GDFILLRECTFX gdfillrectfx;
    if (fade_function == 0) { // When not fading, it's a 50% blend
      gdfillrectfx.dwOpacity = 128;
    } else { // When fading in or out, use fade_value when < 128
      if (fade_value < 128) {
        gdfillrectfx.dwOpacity = fade_value;
      } else {
        gdfillrectfx.dwOpacity = 128;
      }
    }
    // Blended box
    backbuffer->FillRect(CRect(0, top - 2, 240, top + 26), RGB(240, 240, 240), GDFILLRECT_OPACITY, &gdfillrectfx);
  }
  // Label
  backbuffer->DrawText(2, top + 1,  TEXT("Keys :"), &font1, GDDRAWTEXT_LEFT, NULL, GDBLTFAST_OPACITY, &gdbltfastfx);
  // Arrows
  // Value
	switch (key_map_step) {
    case 0: { if (active_option == 4) { backbuffer->DrawText(55, top + 1, TEXT("ACTION or Click to map..."), &font1_green, GDDRAWTEXT_LEFT, NULL, GDBLTFAST_OPACITY, &gdbltfastfx); } break; }
		case 1: { backbuffer->DrawText(55, top + 1, TEXT("Press UP"),      &font1_green, GDDRAWTEXT_LEFT, NULL, GDBLTFAST_OPACITY, &gdbltfastfx); break; }
		case 2: { backbuffer->DrawText(55, top + 1, TEXT("Press DOWN"),    &font1_green, GDDRAWTEXT_LEFT, NULL, GDBLTFAST_OPACITY, &gdbltfastfx); break; }
		case 3: { backbuffer->DrawText(55, top + 1, TEXT("Press LEFT"),    &font1_green, GDDRAWTEXT_LEFT, NULL, GDBLTFAST_OPACITY, &gdbltfastfx); break; }
		case 4: { backbuffer->DrawText(55, top + 1, TEXT("Press RIGHT"),   &font1_green, GDDRAWTEXT_LEFT, NULL, GDBLTFAST_OPACITY, &gdbltfastfx); break; }
		case 5: { backbuffer->DrawText(55, top + 1, TEXT("Press ACTION"),  &font1_green, GDDRAWTEXT_LEFT, NULL, GDBLTFAST_OPACITY, &gdbltfastfx); break; }
		case 6: { backbuffer->DrawText(55, top + 1, TEXT("Press COMMAND"), &font1_green, GDDRAWTEXT_LEFT, NULL, GDBLTFAST_OPACITY, &gdbltfastfx); break; }
	}

	GDLINEFX gdlinefx;
	GDFILLRECTFX gdfillrectfx;
	gdlinefx.dwOpacity = fade_value;
	gdfillrectfx.dwOpacity = fade_value;
	if (defaultBox) {
		backbuffer->FillRect(CRect(0, 223, 240, 263), RGB(255, 255, 255), GDFILLRECT_OPACITY, &gdfillrectfx);
	} else {
		backbuffer->DrawRect(CRect(0, 223, 240, 263), RGB(255, 255, 255), GDDRAWLINE_OPACITY, &gdlinefx);
	}
	backbuffer->DrawText(bbCenterPoint, 224, TEXT("Click in this box to restore"), &font1, GDDRAWTEXT_CENTER, NULL, GDBLTFAST_OPACITY, &gdbltfastfx);
	backbuffer->DrawText(bbCenterPoint, 240, TEXT("default key mappings"), &font1, GDDRAWTEXT_CENTER, NULL, GDBLTFAST_OPACITY, &gdbltfastfx);

  // Fading
  screenFader();

}


// ****************************************************************************************************************
// KeyDown handler
// ****************************************************************************************************************
void CGame::kdOptions(DWORD dwKey) {

	using namespace ns_Options;

  // Left
	if (dwKey == kLeft) {
    if (active_option < 4) {
      PreviousTapped = true;
    }
  }

	// Right
	if (dwKey == kRight) {
    if (active_option < 4) {
      NextTapped = true;
    }
  }

}


// ****************************************************************************************************************
// KeyUp handler
// ****************************************************************************************************************
void CGame::kuOptions(DWORD dwKey) {

	using namespace ns_Options;

	GDKEYLIST keylist;
	m_pInput->GetKeyList(&keylist);

	// If we're mapping buttons...
  if (key_map_step > 0) { // We're mapping keys AND All Done! is NOT showing...

		switch (key_map_step) {
			case 1:  { // UP
				if (dwKey == keylist.vkUp)		{ kUp		  = keylist.vkUp;		  key_map_step++; }
				if (dwKey == keylist.vkDown)	{ kUp		  = keylist.vkDown;	  key_map_step++; }
				if (dwKey == keylist.vkLeft)	{ kUp		  = keylist.vkLeft;	  key_map_step++; }
				if (dwKey == keylist.vkRight)	{ kUp		  = keylist.vkRight;  key_map_step++; }
				if (dwKey == keylist.vkA)			{ kUp		  = keylist.vkA;		  key_map_step++; }
				if (dwKey == keylist.vkB)			{ kUp		  = keylist.vkB;		  key_map_step++; }
				if (dwKey == keylist.vkC)			{ kUp		  = keylist.vkC;		  key_map_step++; }
				if (dwKey == keylist.vkStart) { kUp		  = keylist.vkStart;  key_map_step++; }
			break; }
			case 2:  { // DOWN
				if (dwKey == keylist.vkUp)		{ kDown    = keylist.vkUp;		key_map_step++; }
				if (dwKey == keylist.vkDown)	{ kDown    = keylist.vkDown;	key_map_step++; }
				if (dwKey == keylist.vkLeft)	{ kDown    = keylist.vkLeft;	key_map_step++; }
				if (dwKey == keylist.vkRight)	{ kDown    = keylist.vkRight;	key_map_step++; }
				if (dwKey == keylist.vkA)			{ kDown    = keylist.vkA;		  key_map_step++; }
				if (dwKey == keylist.vkB)			{ kDown    = keylist.vkB;		  key_map_step++; }
				if (dwKey == keylist.vkC)			{ kDown    = keylist.vkC;		  key_map_step++; }
				if (dwKey == keylist.vkStart) { kDown    = keylist.vkStart; key_map_step++; }
			break; }
			case 3:  { // LEFT
				if (dwKey == keylist.vkUp)		{ kLeft    = keylist.vkUp;		key_map_step++; }
				if (dwKey == keylist.vkDown)	{ kLeft    = keylist.vkDown;	key_map_step++; }
				if (dwKey == keylist.vkLeft)	{ kLeft    = keylist.vkLeft;	key_map_step++; }
				if (dwKey == keylist.vkRight)	{ kLeft    = keylist.vkRight;	key_map_step++; }
				if (dwKey == keylist.vkA)			{ kLeft    = keylist.vkA;		  key_map_step++; }
				if (dwKey == keylist.vkB)			{ kLeft    = keylist.vkB;		  key_map_step++; }
				if (dwKey == keylist.vkC)			{ kLeft    = keylist.vkC;		  key_map_step++; }
				if (dwKey == keylist.vkStart) { kLeft    = keylist.vkStart; key_map_step++; }
			break; }
			case 4:  { // RIGHTS
				if (dwKey == keylist.vkUp)		{ kRight   = keylist.vkUp;		key_map_step++; }
				if (dwKey == keylist.vkDown)	{ kRight   = keylist.vkDown;	key_map_step++; }
				if (dwKey == keylist.vkLeft)	{ kRight   = keylist.vkLeft;	key_map_step++; }
				if (dwKey == keylist.vkRight)	{ kRight   = keylist.vkRight; key_map_step++; }
				if (dwKey == keylist.vkA)			{ kRight   = keylist.vkA;		  key_map_step++; }
				if (dwKey == keylist.vkB)			{ kRight   = keylist.vkB;		  key_map_step++; }
				if (dwKey == keylist.vkC)			{ kRight   = keylist.vkC;		  key_map_step++; }
				if (dwKey == keylist.vkStart) { kRight   = keylist.vkStart; key_map_step++; }
			break; }
			case 5:  { // ACTION
				if (dwKey == keylist.vkUp)		{ kAction  = keylist.vkUp;		key_map_step++; }
				if (dwKey == keylist.vkDown)	{ kAction  = keylist.vkDown;	key_map_step++; }
				if (dwKey == keylist.vkLeft)	{ kAction  = keylist.vkLeft;	key_map_step++; }
				if (dwKey == keylist.vkRight)	{ kAction  = keylist.vkRight; key_map_step++; }
				if (dwKey == keylist.vkA)			{ kAction  = keylist.vkA;		  key_map_step++; }
				if (dwKey == keylist.vkB)			{ kAction  = keylist.vkB;		  key_map_step++; }
				if (dwKey == keylist.vkC)			{ kAction  = keylist.vkC;		  key_map_step++; }
				if (dwKey == keylist.vkStart) { kAction  = keylist.vkStart; key_map_step++; }
			break; }
			case 6: { // COMMAND
				if (dwKey == keylist.vkUp)		{ kCommand = keylist.vkUp;		key_map_step++; }
				if (dwKey == keylist.vkDown)	{ kCommand = keylist.vkDown;	key_map_step++; }
				if (dwKey == keylist.vkLeft)	{ kCommand = keylist.vkLeft;	key_map_step++; }
				if (dwKey == keylist.vkRight)	{ kCommand = keylist.vkLeft;	key_map_step++; }
				if (dwKey == keylist.vkA)			{ kCommand = keylist.vkA;		  key_map_step++; }
				if (dwKey == keylist.vkB)			{ kCommand = keylist.vkB;		  key_map_step++; }
				if (dwKey == keylist.vkC)			{ kCommand = keylist.vkC;		  key_map_step++; }
				if (dwKey == keylist.vkStart) { kCommand = keylist.vkStart; key_map_step++; }
				key_map_step = 0;
			break; }
		}

	} else { // We're NOT mapping buttons...

		// Up
		if (dwKey == kUp) {
			sndObj.playSound(sfxMisc3);
			active_option--;
			if (active_option < 1) { active_option = 4; }
      key_map_step = 0;
		}

		// Down
		if (dwKey == kDown) {
			sndObj.playSound(sfxMisc3);
			active_option++;
			if (active_option > 4) { active_option = 1; }
      key_map_step = 0;
		}

		// Left
		if (dwKey == kLeft) {
      PreviousTapped = false;
			sndObj.playSound(sfxMisc5);
      switch (active_option) {
        case 1: { // Volume
				  volumeLevel--;
				  if (volumeLevel < 0) { volumeLevel = 0; }
				  setVolumeLevel();
         break; }
        case 2: { // Frame Rate
          if (show_fps) { show_fps = false; } else { show_fps = true; }
        break; }
        case 3: { // Frame Time
          if (show_frame_time) { show_frame_time = false; } else { show_frame_time = true; }
        break; }
			}
		}

		// Right
		if (dwKey == kRight) {
      NextTapped = false;
			sndObj.playSound(sfxMisc5);
      switch (active_option) {
        case 1: { // Volume
				  volumeLevel++;
				  if (volumeLevel > 3) { volumeLevel = 3; }
				  setVolumeLevel();
         break; }
        case 2: { // Frame Rate
          if (show_fps) { show_fps = false; } else { show_fps = true; }
        break; }
        case 3: { // Frame Time
          if (show_frame_time) { show_frame_time = false; } else { show_frame_time = true; }
        break; }
			}
		}

	  // Action
	  if (dwKey == kAction) {
			if (active_option == 4 && key_map_step == 0) { // Map keys, unless All Done! is showing
				sndObj.playSound(sfxMisc3);
				key_map_step = 1;
			}
	  }

	  // Back
	  if (dwKey == kCommand) {
	    sndObj.playSound(sfxMisc4);
			writeKGAFile(gameRestarted, false);
	    fade_function = 1;
			next_screen = csMainMenu;
	  }

	}

}


// ****************************************************************************************************************
// StylusDown handler
// ****************************************************************************************************************
void CGame::sdOptions(POINT p) {

  using namespace ns_Options;

	if (key_map_step == 0) {

		if (PtInRect(CRect(0, 223, 240, 263),  p)) { // Restore default key mappings
			defaultBox = true;
			return;
		}

		// Check previous/next buttons, depending on current option
		switch (active_option) {
			// Volume
			case 1: {
				if (PtInRect(CRect(185, 60, 209, 84),  p)) { // Previous
					kdOptions(kLeft);
				}
				if (PtInRect(CRect(214, 60, 238, 84),  p)) { // Previous
					kdOptions(kRight);
				}
			break; }
			// Frame rate
			case 2: {
				if (PtInRect(CRect(185, 100, 209, 124),  p)) { // Previous
					kdOptions(kLeft);
				}
				if (PtInRect(CRect(214, 100, 238, 124),  p)) { // Previous
					kdOptions(kRight);
				}
			break; }
			// Frame time
			case 3: {
				if (PtInRect(CRect(185, 140, 209, 164),  p)) { // Previous
					kdOptions(kLeft);
				}
				if (PtInRect(CRect(214, 140, 238, 164),  p)) { // Previous
					kdOptions(kRight);
				}
			break; }
		}
		
	}

}


// ****************************************************************************************************************
// StylusUp handler
// ****************************************************************************************************************
void CGame::suOptions(POINT p) {

  using namespace ns_Options;

	if (key_map_step == 0) {

		// Restore default key mappings
		if (defaultBox && !PreviousTapped && !NextTapped && PtInRect(CRect(2, 181, 40, 201),  p)) {
			GDKEYLIST keylist;
			m_pInput->GetKeyList(&keylist);
			kUp			 = keylist.vkUp;
			kDown		 = keylist.vkDown;
			kLeft		 = keylist.vkLeft;
			kRight	 = keylist.vkRight;
			kAction  = keylist.vkA;
			kCommand = keylist.vkB;
			return;
		}	

		// Begin mapping
		if (active_option == 4 && !defaultBox && !PreviousTapped && !NextTapped && PtInRect(CRect(54, 181, 240, 201), p)) { 
			kuOptions(kAction); 
			return;
		}

		if (!defaultBox && !PreviousTapped && !NextTapped && PtInRect(CRect(0, 300, 240, 320), p)) { 
			kuOptions(kCommand); 
			return;
		} // Exit

		if (!defaultBox && !PreviousTapped && !NextTapped && PtInRect(CRect(2, 61, 65, 81),  p)) { // Activate volume
			sndObj.playSound(sfxMisc3);
			active_option = 1;
			return;
		}	

		if (!defaultBox && !PreviousTapped && !NextTapped && PtInRect(CRect(2, 101, 145, 121),  p)) { // Activate frame rate
			sndObj.playSound(sfxMisc3);
			active_option = 2;
			return;
		}	

		if (!defaultBox && !PreviousTapped && !NextTapped && PtInRect(CRect(2, 141, 145, 161),  p)) { // Activate frame time
			sndObj.playSound(sfxMisc3);
			active_option = 3;
			return;
		}	

		if (!defaultBox && !PreviousTapped && !NextTapped && PtInRect(CRect(2, 181, 45, 201),  p)) { // Activate key mapping
			sndObj.playSound(sfxMisc3);
			active_option = 4;
			return;
		}

		// Check previous/next buttons, depending on current option
		if (!defaultBox && (PreviousTapped || NextTapped)) {
			switch (active_option) {
				case 1: { // Volume
					if (PreviousTapped && PtInRect(CRect(185, 60, 209, 84),  p)) { // Previous
						kuOptions(kLeft);
						return;
					}
					if (NextTapped && PtInRect(CRect(214, 60, 238, 84),  p)) { // Previous
						kuOptions(kRight);
						return;
					}
				break; }
				case 2: { // Frame rate
					if (PreviousTapped && PtInRect(CRect(185, 100, 209, 124),  p)) { // Previous
						kuOptions(kLeft);
						return;
					}
					if (NextTapped && PtInRect(CRect(214, 100, 238, 124),  p)) { // Previous
						kuOptions(kRight);
						return;
					}
				break; }
				case 3: { // Frame time
					if (PreviousTapped && PtInRect(CRect(185, 140, 209, 164),  p)) { // Previous
						kuOptions(kLeft);
						return;
					}
					if (NextTapped && PtInRect(CRect(214, 140, 238, 164),  p)) { // Previous
						kuOptions(kRight);
						return;
					}
				break; }
			}
		}

	}

	PreviousTapped = false;
	NextTapped = false;
	defaultBox = false;

}


// ****************************************************************************************************************
// Utility functions
// ****************************************************************************************************************

void CGame::optReset() {
  using namespace ns_Options;
  active_option = 1;
	key_map_step = 0;
  PreviousTapped = false;
  NextTapped = false;
}