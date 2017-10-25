
#include "main.h"


namespace ns_Instructions {


// ****************************************************************************************************************
// Globals
// ****************************************************************************************************************
bool		 PreviousTapped		 = false;
bool		 NextTapped				 = false;
int			 scrollCurrent		 = 0;
int			 scrollNew				 = 0;
int			 pageSwitchDir		 = 0;     // 1 - Previous, 2 = Next
int			 currentPage		   = 1;
int			 scrollIncrement	 = 8;
int			 textYLocation		 = 60;
int			 totalPages				 = 15;
                               //    ------------------------------
TCHAR		 screen1Text[][52] = { TEXT(" The Story... (1/15)"),
															 TEXT(""),
															 TEXT(" In K&G Arcade, you play the"),
															 TEXT(" part of Henry Miller,"),
															 TEXT(" mild-mannered farmer from"),
															 TEXT(" jolly-old 17th-century"),
															 TEXT(" England.  One night while"),
															 TEXT(" tending your field, you see"),
															 TEXT(" a strange light appear in"),
															 TEXT(" the sky above you.  It grows"),
															 TEXT(" ever larger as it nears..."),
															 //    ------------------------------
                               TEXT(" The Story... (2/15)"),
															 TEXT(""),
															 TEXT(" It is a strange flying"),
															 TEXT(" object that you cannot"),
															 TEXT(" identify.  It is round on"),
															 TEXT(" top with a spinning disc"),
															 TEXT(" beneath and yellow orbs"),
															 TEXT(" dancing around it's outer"),
															 TEXT(" surface.  What could it be?"),
															 TEXT(""),
															 TEXT(" Why, it's Krelmac & Gentoo!"),
															 //    ------------------------------
                               TEXT(" The Story... (3/15)"),
															 TEXT(""),
															 TEXT(" Turns out those two goofball"),
															 TEXT(" tormentors have decided to"),
															 TEXT(" go back in time to annoy the"),
															 TEXT(" human race at a time when"),
															 TEXT(" we were even more primitive"),
															 TEXT(" than they say we are in"),
															 TEXT(" their own time.  More to the"),
															 TEXT(" point, they decide to"),
															 TEXT(" run YOU through the ringer!"),
															 //    ------------------------------
                               TEXT(" The Story... (4/15)"),
															 TEXT(""),
															 TEXT(" So, they beam you aboard"),
															 TEXT(" their ship, give you a few"),
															 TEXT(" anal probes for good measure"),
															 TEXT(" and send you out to escape"),
															 TEXT(" from their ship.  You will"),
															 TEXT(" have to make your way"),
															 TEXT(" through all five levels of"),
															 TEXT(" the ship in order to escape"),
															 TEXT(" their semi-evil clutches."),
															 //    ------------------------------
                               TEXT(" Playing Adventure... (5/15)"),
															 TEXT(""),
															 TEXT(" Being sick, sadistic alien"),
															 TEXT(" torturers, it's not quite"),
															 TEXT(" as easy as it sounds..."),
															 TEXT(" Each level of the ship is a"),
															 TEXT(" complex maze, and within"),
															 TEXT(" each maze are gaming"),
															 TEXT(" consoles, five per level."),
															 TEXT(" You must find and play each"),
															 TEXT(" of the games."),
															 //    ------------------------------
                               TEXT(" Playing Adventure... (6/15)"),
															 TEXT(""),
															 TEXT(" More importantly, you must"),
															 TEXT(" achieve a given minimum"),
															 TEXT(" score on each game.  As you"),
															 TEXT(" do so, the indicators on the"),
															 TEXT(" display will light up.  When"),
															 TEXT(" all five are lit, you will"),
															 TEXT(" be able to access the"),
															 TEXT(" teleporter pad and move on"),
															 TEXT(" to the next level."),
															 //    ------------------------------
                               TEXT(" Playing Adventure... (7/15)"),
															 TEXT("                              "),
															 TEXT(" A word on game controls..."),
															 TEXT(" To activate a game console,"),
															 TEXT(" touch it and press the ACTION"),
															 TEXT(" button.  Likewise, to use an"),
															 TEXT(" activated teleporter pad,"),
															 TEXT(" touch it and press ACTION."),
                               TEXT(" You can pull up a menu at"),
															 TEXT(" any time by pressing the"),
															 TEXT(" COMMAND button.  Anyway..."),
															 //    ------------------------------
                               TEXT(" Playing Adventure... (8/15)"),
															 TEXT(""),
															 TEXT(" All the while, robots will"),
															 TEXT(" hunt you down.  These are"),
															 TEXT(" odd little robots though..."),
															 TEXT(" They were a failed science"),
															 TEXT(" fair project by Gentoo, and"),
															 TEXT(" they cannot move around the"),
															 TEXT(" ship normally,  They instead"),
															 TEXT(" utilize a rather unique mode"),
															 TEXT(" of transportation..."),
															 //    ------------------------------
                               TEXT(" Playing Adventure... (9/15)"),
															 TEXT(""),
															 TEXT(" The robots move by using a"),
															 TEXT(" Quantum Sub-Temporal Inter-"),
															 TEXT(" Spatial Displacement"),
															 TEXT(" Modulation Field Generator,"),
															 TEXT(" or QSTISDMFG for short.  Put"),
															 TEXT(" in terms a lame human could"),
															 TEXT(" understand, it means they"),
															 TEXT(" teleport in discrete units"),
															 TEXT(" from place to place."),
															 //    ------------------------------
                               TEXT(" Playing Adventure... (10/15)"),
															 TEXT(""),
															 TEXT(" This makes them less than"),
															 TEXT(" perfect killing machines,"),
															 TEXT(" a failing Gentoo greatly"),
															 TEXT(" regrets, but it DOES make"),
															 TEXT(" them highly unpredictable"),
															 TEXT(" and generally a nuisance."),
															 TEXT(" You can take a few hits from"),
															 TEXT(" them, but your heart rate"),
															 TEXT(" increases each hit."),
															 //    ------------------------------
                               TEXT(" Playing Adventure... (11/15)"),
															 TEXT(""),
															 TEXT(" The number on the heart"),
															 TEXT(" tells you how many more"),
															 TEXT(" hits you can take.  If it"),
															 TEXT(" says 0 and your heartrate"),
															 TEXT(" is going like mad, one more"),
															 TEXT(" kills!  Some of the games"),
															 TEXT(" are virtually impossible to"),
															 TEXT(" win at, by the way, but"),
															 TEXT(" there is always a way..."),
															 //    ------------------------------
                               TEXT(" Playing Adventure... (12/15)"),
															 TEXT(""),
															 TEXT(" Krelmac has been a bit"),
															 TEXT(" careless in the past when"),
															 TEXT(" tormenting other creatures."),
															 TEXT(" He has left some of them on"),
															 TEXT(" the levels of the ship with"),
															 TEXT(" you, one on each level, by"),
															 TEXT(" some bizarre coincidence of"),
															 TEXT(" wacky cosmic numerology."),
															 TEXT(" Seek them out!"),
															 //    ------------------------------
                               TEXT(" Playing Adventure... (13/15)"),
															 TEXT(""),
															 TEXT(" You will have to talk to"),
															 TEXT(" them, and gain their trust"),
															 TEXT(" by saying the right things"),
															 TEXT(" at the right time.  You will"),
															 TEXT(" know when they trust you"),
															 TEXT(" completely, and only then ask"),
															 TEXT(" them to 'Please tell me the"),
															 TEXT(" secret hint!' and they will"),
															 TEXT(" give some needed info."),
															 //    ------------------------------
                               TEXT(" Playing Melee... (14/15)"),
															 TEXT(""),
															 TEXT(" As you progress through the"),
															 TEXT(" mini-games in Adventure mode"),
															 TEXT(" the games that you achieve"),
															 TEXT(" the minimum score in will be"),
															 TEXT(" unlocked to play in Mini-"),
															 TEXT(" Game Melee mode.  This allows"),
															 TEXT(" you to play any game you"),
															 TEXT(" have unlocked in timed mode"),
															 TEXT(" or until you say stop."),
															 //    ------------------------------
                               TEXT(" In closing... (15/15)"),
															 TEXT(""),
															 TEXT(" That's really about all there"),
															 TEXT(" is to it.  Go fight your way"),
															 TEXT(" through Adventure mode,"),
															 TEXT(" unlock all the mini-games,"),
															 TEXT(" and then enjoy them any time"),
															 TEXT(" you want in Melee mode."),
															 TEXT(""),
															 TEXT(" See ya!                      "),
															 TEXT("")
                               //    ------------------------------
};


} // End of namespace


// ****************************************************************************************************************
// ProcessNextFrame handler
// ****************************************************************************************************************
void CGame::pnfInstructions(CGapiSurface* backbuffer) {

	using namespace ns_Instructions;

  // Set up for fading
  GDBLTFASTFX gdbltfastfx;
  gdbltfastfx.dwOpacity = fade_value;
  // Scrolling background
	scrollingBackground(backbuffer);
	// Title
	backbuffer->DrawText(bbCenterPoint, 10, TEXT("Instructions"), &font1_green, GDDRAWTEXT_CENTER, NULL, GDBLTFAST_OPACITY, &gdbltfastfx);
	// Lines
	backbuffer->BltFast(0, 40, divider_00, NULL, GDBLTFAST_OPACITY, &gdbltfastfx);
  backbuffer->BltFast(0, 290, divider_00, NULL, GDBLTFAST_OPACITY, &gdbltfastfx);
  // Back
  backbuffer->DrawText(bbCenterPoint, 300,  TEXT("COMMAND/Click for Main Menu"), &font1_green, GDDRAWTEXT_CENTER, NULL, GDBLTFAST_OPACITY, &gdbltfastfx);

	// Draw the text for the current scree
	int lineIncr = textYLocation;
	int arrayIndex = (currentPage - 1) * 11;
	for (int i = 0; i < 11; i++) {
		backbuffer->DrawText(scrollCurrent, lineIncr, screen1Text[i + arrayIndex], &font1, GDDRAWTEXT_LEFT, NULL, GDBLTFAST_OPACITY, &gdbltfastfx);
		lineIncr = lineIncr + 16;
	}
	// If we're changing the instructions page, do it now
	if (pageSwitchDir > 0) {
		switch (pageSwitchDir) {
			case 1: { // Previous
				arrayIndex = (currentPage - 2) * 11;
				lineIncr = textYLocation;
				for (int i = 0; i < 11; i++) {
					backbuffer->DrawText(scrollNew, lineIncr, screen1Text[i + arrayIndex], &font1, GDDRAWTEXT_LEFT, NULL, GDBLTFAST_OPACITY, &gdbltfastfx);
					lineIncr = lineIncr + 16;
				}
				scrollNew = scrollNew + scrollIncrement;
				scrollCurrent = scrollCurrent + scrollIncrement;
				if (scrollNew >= 0) {
					scrollNew = 0;
					scrollCurrent = 0;
					pageSwitchDir = 0;
					currentPage--;
				}
			break; }
			case 2: { // Next
				arrayIndex = currentPage * 11;
				lineIncr = textYLocation;
				for (int i = 0; i < 11; i++) {
					backbuffer->DrawText(scrollNew, lineIncr, screen1Text[i + arrayIndex], &font1, GDDRAWTEXT_LEFT, NULL, GDBLTFAST_OPACITY, &gdbltfastfx);
					lineIncr = lineIncr + 16;
				}
				scrollNew = scrollNew - scrollIncrement;
				scrollCurrent = scrollCurrent - scrollIncrement;
				if (scrollNew <= 0) {
					scrollNew = 0;
					scrollCurrent = 0;
					pageSwitchDir = 0;
					currentPage++;
				}
			break; }
		}
	}
	// Draw next/prev buttons
	if (PreviousTapped) {
		backbuffer->BltFast(5, 262, gfx_ins_prev_1, NULL, GDBLTFAST_KEYSRC | GDBLTFAST_OPACITY, &gdbltfastfx);
	} else {
		if (currentPage > 1) {
			backbuffer->BltFast(5, 262, gfx_ins_prev_0, NULL, GDBLTFAST_KEYSRC | GDBLTFAST_OPACITY, &gdbltfastfx);
		}
	}
	if (NextTapped)	{
		backbuffer->BltFast(211, 262, gfx_ins_next_1, NULL, GDBLTFAST_KEYSRC | GDBLTFAST_OPACITY, &gdbltfastfx);
	} else {
		if (currentPage < totalPages) {
			backbuffer->BltFast(211, 262, gfx_ins_next_0, NULL, GDBLTFAST_KEYSRC | GDBLTFAST_OPACITY, &gdbltfastfx);
		}
	}

  // Fading
  screenFader();

}


// ****************************************************************************************************************
// KeyDown handler
// ****************************************************************************************************************
void CGame::kdInstructions(DWORD dwKey) {

	using namespace ns_Instructions;

  // Left
  if (dwKey == kLeft && pageSwitchDir == 0) {
    if (currentPage > 1) {
      PreviousTapped = true;
    }
  }

  // Right
  if (dwKey == kRight && pageSwitchDir == 0) {
    if (currentPage < totalPages) {
      NextTapped = true;
    }
  }

}


// ****************************************************************************************************************
// KeyUp handler
// ****************************************************************************************************************
void CGame::kuInstructions(DWORD dwKey) {

	using namespace ns_Instructions;

  // Left
  if (dwKey == kLeft && pageSwitchDir == 0) {
    if (currentPage > 1) {
      sndObj.playSound(sfx_ins_arrow);
	    NextTapped = false;
	    PreviousTapped = false;
	    pageSwitchDir = 1;
	    scrollCurrent = 0;
	    scrollNew = -240;
    }
  }

  // Right
  if (dwKey == kRight && pageSwitchDir == 0) {
    if (currentPage < totalPages) {
      sndObj.playSound(sfx_ins_arrow);
		  NextTapped = false;
		  PreviousTapped = false;
		  pageSwitchDir = 2;
		  scrollCurrent = 0;
		  scrollNew = 240;
    }
  }

  // Back
  if (dwKey == kCommand && pageSwitchDir == 0) {
    sndObj.playSound(sfxMisc4);
    fade_function = 1;
		next_screen = csMainMenu;
  }

}


// ****************************************************************************************************************
// StylusDown handler
// ****************************************************************************************************************
void CGame::sdInstructions(POINT p) {

  using namespace ns_Instructions;

	// Previous
	if (PtInRect(CRect(5, 262, 29, 287),  p)) {
		kdInstructions(kLeft);
		return;
	}
	
	// Next
	if (PtInRect(CRect(211, 262, 264, 287),  p)) {
		kdInstructions(kRight);
		return;
	}

}


// ****************************************************************************************************************
// StylusUp handler
// ****************************************************************************************************************
void CGame::suInstructions(POINT p) {

  using namespace ns_Instructions;

	// Exit
	if (!PreviousTapped && !NextTapped && PtInRect(CRect(0, 300, 240, 320), p)) { 
		kuInstructions(kCommand); 
		return; 
	}

	// Previous
	if (PreviousTapped && PtInRect(CRect(5, 262, 29, 287),  p)) {
		kuInstructions(kLeft);
		return;
	}
	
	// Next
	if (NextTapped && PtInRect(CRect(211, 262, 264, 287),  p)) {
		kuInstructions(kRight);
		return;
	}

	NextTapped = false;
	PreviousTapped = false;

}


// ****************************************************************************************************************
// Utility functions
// ****************************************************************************************************************

void CGame::insReset() {
  using namespace ns_Instructions;
  scrollCurrent = 0;
  scrollNew = 0;
  pageSwitchDir = 0;
  PreviousTapped = false;
  NextTapped = false;
  currentPage = 1;
  scrollIncrement = 8;
}