
#include "main.h"


namespace ns_Credits {


// ****************************************************************************************************************
// Globals
// ****************************************************************************************************************
// This is the actual data, line-by-line to scroll.  Each array element is a line.
TCHAR scrollerLines[][140] = { TEXT(""),
															 TEXT("K&G Arcade"),
															 TEXT("Version 1.6"),
															 TEXT(""),
															 TEXT("A game by"),
															 TEXT("Frank W. Zammetti"),
															 TEXT("and"),
															 TEXT("Anthony Volpe"),
															 TEXT(""),
															 TEXT("A joint production of"),
															 TEXT("Omnytex Technologies"),
															 TEXT("and"),
															 TEXT("Crackhead Creations"),
															 TEXT(""),
															 TEXT("Game concept and design:"),
															 TEXT("Frank W. Zammetti"),
															 TEXT(""),
															 TEXT("Graphics:"),
															 TEXT("99% Anthony Volpe"),
															 TEXT("1% Frank W. Zammetti"),
															 TEXT("(If it sucks, you can assume"),
															 TEXT("that Frank did it!)"),
															 TEXT(""),
															 TEXT("Coding:"),
															 TEXT("Frank W. Zammetti"),
															 TEXT(""),
															 TEXT("Cut scene scripts:"),
															 TEXT("Frank W. Zammetti"),
															 TEXT("and"),
															 TEXT("Anthony Volpe"),
															 TEXT(""),
															 TEXT("Voice of Gentoo:"),
															 TEXT("Anthony Volpe"),
															 TEXT(""),
															 TEXT("Voice of Krelmac:"),
															 TEXT("Frank W. Zammetti"),
															 TEXT(""),
															 TEXT("Sound FX:"),
															 TEXT("Frank W. Zammetti"),
															 TEXT(""),
															 TEXT("Music composed by:"),
															 TEXT("Frank W. Zammetti"),
															 TEXT(""),
															 TEXT("Anything else we forgot:"),
															 TEXT("Frank W. Zammetti"),
															 TEXT("and/or"),
															 TEXT("Anthony Volpe"),
															 TEXT(""),
															 TEXT("(And the point of all that,"),
															 TEXT("aside from good old-fashioned"),
                               TEXT("ego stroking, was what?!?)"),
															 TEXT(""),
															 TEXT("K&G Arcade uses the"),
															 TEXT("GapiDraw toolkit for it's"),
															 TEXT("graphics and the Hekkus"),
                               TEXT("Sound System for it's audio."),
                               TEXT("For information on"),
                               TEXT("GapiDraw, visit"),
                               TEXT("http://www.gapidraw.com"),
                               TEXT("and for Hekkus, go to"),
                               TEXT("http://www.shlzero.com"),
                               TEXT("Thanks very much to"),
                               TEXT("Johan Sanneblad and"),
                               TEXT("Thomas Maniero (aka Gerson)"),
                               TEXT("for their great work in"),
                               TEXT("creating GapiDraw and"),
                               TEXT("Hekkus, respectively!"),
															 TEXT(""),
                               TEXT("K&G Arcade uses the"),
															 TEXT("OASIS engine for it's"),
															 TEXT("cinematic cut scenes."),
															 TEXT("This is a proprietary"),
															 TEXT("library written by"),
															 TEXT("Frank W. Zammetti of"),
															 TEXT("Omnytex Technologies."),
															 TEXT("If you want it, give"),
															 TEXT("me lots 'o cash!"),
															 TEXT("But since I know you"),
															 TEXT("can do better on your own,"),
															 TEXT("I won't hold my breath!"),
															 TEXT(""),
															 TEXT("All voiceover recordings"),
															 TEXT("were done on a Mac at"),
															 TEXT("Anthony's house and were"),
															 TEXT("processed via GoldWave"),
															 TEXT("and SoundForge on"),
															 TEXT("Frank's Dell PC."),
															 TEXT("Sorry BillG, Mac's are"),
															 TEXT("kinda cool buddy!"),
															 TEXT(""),
                               TEXT("Special thanks to those who"),
                               TEXT("were beta testers for us:"),
                               TEXT("10inchAssassin, blankg, com,"),
                               TEXT("felixdd, hockeydude and Helios,"),
                               TEXT("all of PocketMatrix.com fame!"),                                                           
                               TEXT(""),
                               TEXT("Visit the K&G Arcade web site:"),
                               TEXT("http://www.kgarcade.com"),
                               TEXT(""),
							                 TEXT("K&G Arcade"),
															 TEXT("(C)opyright 2004"),
															 TEXT("Omnytex Technologies"),
															 TEXT("All rights reserved."),
															 TEXT(""),
                               TEXT("Krelmac and Gentoo are"),
                               TEXT("trademarks of"),
                               TEXT("Frank W. Zammetti"), 
                               TEXT("and Anthony Volpe"),
                               TEXT("Brenda Bubey, Sully,"), 
                               TEXT("Eeeger, Catrina and"),
                               TEXT("Frederick J. Smiley"),
                               TEXT("are trademarks of "),
                               TEXT("Anthony Volpe."),
                               TEXT("All rights reserved."),
                               TEXT(""),
															 TEXT("K&G Arcade..."),
															 TEXT("Today's experiment:"),
															 TEXT("FAILED!"),
															 TEXT(""),
															 TEXT(""),
															 TEXT(""),
															 TEXT(""),
															 TEXT(""),
															 TEXT(""),
															 TEXT(""),
															 TEXT(""),
															 TEXT(""),
                               TEXT(""),
                               TEXT(""),
                               TEXT(""),
                               TEXT(""),
                               TEXT(""),
                               TEXT(""),
															 TEXT("")
														};
// Note: The number of initialized TEXT("") elements int scrollerLinesTemp should match the
// value of scrolledLinesOnScreen variable below!
TCHAR scrollerLinesTemp[][50] = { TEXT(""), TEXT(""), TEXT(""), TEXT(""), TEXT(""), TEXT(""), TEXT(""), TEXT(""), TEXT(""), TEXT(""), TEXT(""), TEXT(""), TEXT(""), TEXT(""), TEXT(""), TEXT(""), TEXT(""), TEXT("") };
// The following variables are developer-adjustable
int	scrollerLinesCount		    = 134; // Number of displayable elements in the scrollerLines array
int scrollerLinesOnScreen     = 18;  // Number of lines to display on the screen (must natch # of elements in scrollerLinesTemp)
int	scrollerTopY					    = 10;  // Top of the area the scroller covers
// The following variables are used internally and should NOT BE ALTERED!
int currentScrollerAmount     = 0;   // Current amount a line is scrolled upwards
int	currentLineIndex			    = 0;   // Current line currently being fed into scroller


} // End of namespace


// ****************************************************************************************************************
// ProcessNextFrame handler
// ****************************************************************************************************************
void CGame::pnfCredits(CGapiSurface* backbuffer) {

	using namespace ns_Credits;

  // Set up for fading
  GDBLTFASTFX gdbltfastfx;
  gdbltfastfx.dwOpacity = fade_value;
  // Scrolling background
	scrollingBackground(backbuffer);
	// Title
	backbuffer->DrawText(bbCenterPoint, 10, TEXT("Credits"), &font1_green, GDDRAWTEXT_CENTER, NULL, GDBLTFAST_OPACITY, &gdbltfastfx);
	// Lines
	backbuffer->BltFast(0, 40, divider_00, NULL, GDBLTFAST_OPACITY, &gdbltfastfx);
  backbuffer->BltFast(0, 290, divider_00, NULL, GDBLTFAST_OPACITY, &gdbltfastfx);
  // Back
  backbuffer->DrawText(bbCenterPoint, 300,  TEXT("COMMAND/Click for Main Menu"), &font1_green, GDDRAWTEXT_CENTER, NULL, GDBLTFAST_OPACITY, &gdbltfastfx);

  // Reset clipper
  backbuffer->SetClipper(CRect(0, 50, 240, 280));

  // Draw text
	int i, j;
  backbuffer->DrawText(bbCenterPoint, scrollerTopY - currentScrollerAmount, scrollerLinesTemp[0], &font1, GDDRAWTEXT_CENTER, NULL, GDBLTFAST_OPACITY, &gdbltfastfx);
	for (i = 1, j = 16; i < scrollerLinesOnScreen - 1; i++, j=j+16) {
		backbuffer->DrawText(bbCenterPoint, (scrollerTopY + j)  - currentScrollerAmount, scrollerLinesTemp[i], &font1, GDDRAWTEXT_CENTER, NULL, GDBLTFAST_OPACITY, &gdbltfastfx);
	}
	backbuffer->DrawText(bbCenterPoint, scrollerTopY + (16 * (scrollerLinesOnScreen - 1)) - currentScrollerAmount, scrollerLinesTemp[scrollerLinesOnScreen - 1], &font1, GDDRAWTEXT_CENTER, NULL, GDBLTFAST_OPACITY, &gdbltfastfx);

	// Scroll all lines up one pixel
	currentScrollerAmount++;
	// If we've scrolled all lines up 16 pixels, it's time to cycle some text
	if (currentScrollerAmount > 15) {
		currentScrollerAmount = 0;
		// Cycle all text in the temp area upwards one full line
		for (int i = 0; i < scrollerLinesOnScreen; i++) {
			_tcscpy(scrollerLinesTemp[i], scrollerLinesTemp[i + 1]);
		}
		// Get the next line of text to pop on to the bottom, or start at the beginning again if it's time
		currentLineIndex++;
		if (currentLineIndex == scrollerLinesCount) {
			currentLineIndex = 0;
		}
		// Pop the next string on to the bottom of our scroller area
		_tcscpy(scrollerLinesTemp[scrollerLinesOnScreen - 1], scrollerLines[currentLineIndex]);
	}

	backbuffer->SetClipper(NULL);

  // Fading
  screenFader();

}


// ****************************************************************************************************************
// KeyUp handler
// ****************************************************************************************************************
void CGame::kuCredits(DWORD dwKey) {

	using namespace ns_Credits;

  // Back
  if (dwKey == kCommand) {
    sndObj.playSound(sfxMisc4);
    fade_function = 1;
		next_screen = csMainMenu;
  }

}


// ****************************************************************************************************************
// StylusUp handler
// ****************************************************************************************************************
void CGame::suCredits(POINT p) {

  using namespace ns_Credits;

	// Exit
	if (PtInRect(CRect(0, 300, 240, 320), p)) { 
		kuCredits(kCommand); 
		return; 
	}

}


// ****************************************************************************************************************
// Utility functions
// ****************************************************************************************************************

void CGame::crdReset() {
  using namespace ns_Credits;
  currentScrollerAmount = 0;
  currentLineIndex = 0;
  for (int i = 0; i < 18; i++) {
    _tcscpy(scrollerLinesTemp[i], TEXT(""));
  }
}