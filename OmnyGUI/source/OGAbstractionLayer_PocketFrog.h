
// *****************************************************************************************************************************
// This is the OmnyGUI abstraction layer for PocketFrog.  It contains all the functions needed by OmnyGUI, written for
// PocketFrog.  Any details of the underlying graphics library should be irrelevant to OmnyGUI with this file in place.
// *****************************************************************************************************************************


namespace OmnyGUI {


	// This is our internal structure used to define a rectangular portion of a surface	
	struct OGRect {
		int left;
		int top;
		int right;
		int bottom;
	};


	using namespace Frog;


	// =======================================================================
  // Draws VGA text
  // =======================================================================
	void OGDrawVGAText(void* in_display, unsigned char* in_font, TCHAR* in_text, int in_align, int in_x, int in_y, int in_color) {

			Display* display = (Display*)in_display;
			unsigned char* pCharStart = NULL;
			int	currChar = 0;
			int	yLoc = 0;
			int	currRow = 0;
			int	bitTest = 0;
			// Abort if in_font is NULL
			if (in_font == NULL) { 
				return; 
			}
			// Get the length of the input in_text, abort if 0
			int strLen = _tcslen(in_text);
			if (strLen == 0) { 
				return; 
			}
			// Calculate X location based on in_alignment
			switch (in_align) {
			case DVT_NONE: {
				in_x = in_x; // Kind of silly, but I like explicit code
			break; }
			case DVT_LEFT: {
				in_x = 0;
			break; }
			case DVT_CENTER: {
				in_x = _tcslen(in_text);
				in_x = (display->GetWidth() - ((in_x << 3) + in_x - 1)) / 2;
			break; }
			case DVT_RIGHT: {
				in_x = _tcslen(in_text);
				in_x = (display->GetWidth() - (in_x << 3)) - (in_x - 1);
			break; }
			default: {
				// Handles any bogus values... We treat it like a left in_align
				in_x = 0;
			break; }
			}
			// Plot each character in the in_text
			for (int i = 0; i < strLen; i++) {
				// Get the next character code in the in_text and advance to the next one
				currChar = (unsigned char)(*in_text++);
				// Set our pointer to the start of THIS character
				pCharStart = in_font + (currChar << 4);
				// Loop through each row in the character
				for (int y = 0; y < 16; y++) {
					yLoc = in_y + y;
					// Grab the byte representing our current row
					currRow = *(pCharStart + y);
					// Go through each bit in the current row and plot those pixels that should be plotted
					bitTest = 0x01 << 7; if ((currRow & bitTest) != 0) { 
						display->SetPixel(in_x + 0, yLoc, in_color); 
					}
					bitTest = 0x01 << 6; if ((currRow & bitTest) != 0) { 
						display->SetPixel(in_x + 1, yLoc, in_color); 
					}
					bitTest = 0x01 << 5; if ((currRow & bitTest) != 0) { 
						display->SetPixel(in_x + 2, yLoc, in_color); 
					}
					bitTest = 0x01 << 4; if ((currRow & bitTest) != 0) { 
						display->SetPixel(in_x + 3, yLoc, in_color); 
					}
					bitTest = 0x01 << 3; if ((currRow & bitTest) != 0) { 
						display->SetPixel(in_x + 4, yLoc, in_color); 
					} 
					bitTest = 0x01 << 2; if ((currRow & bitTest) != 0) { 
						display->SetPixel(in_x + 5, yLoc, in_color); 
					}
					bitTest = 0x01 << 1; if ((currRow & bitTest) != 0) { 
						display->SetPixel(in_x + 6, yLoc, in_color); 
					}
					bitTest = 0x01 << 0; if ((currRow & bitTest) != 0) { 
						display->SetPixel(in_x + 7, yLoc, in_color); 
					}
				}
				// Increment X location to get ready for the next character
				in_x = in_x + 9;
			}

	} // End OGDrawVGAText()


	// =======================================================================
  // Blits a surface to another (expected to be the screens backbuffer)
  // =======================================================================
	void OGBlit(void* in_display, int in_left, int in_top, void* in_surface) {
		((Display*)in_display)->Blit(in_left, in_top, (Surface*)in_surface);
	}


  // =======================================================================
  // Blits a surface to another (expected to be the screens backbuffer)
	// This version accepts a source rectangle.
  // =======================================================================
	void OGBlit(void* in_display, int in_left, int in_top, void* in_surface, OGRect in_rect) {
		((Display*)in_display)->Blit(in_left, in_top, (Surface*)in_surface, &Rect(in_rect.left, in_rect.top, in_rect.right, in_rect.bottom));
	}


  // =======================================================================
  // Loads a resource image into a surface
  // =======================================================================
	void* OGLoadImage(void* in_display, int in_id, TCHAR* in_group) {
		return (void*)LoadImage((Display*)in_display, in_id, in_group);
	}


  // =======================================================================
  // Sets the transparent color of a surface
  // =======================================================================
	void OGSetTransparentColor(void* in_surface, int in_color) {
		((Surface*)in_surface)->SetColorMask(in_color);
	}


  // =======================================================================
  // Returns the width of a surface
  // =======================================================================
	int OGGetWidth(void* in_surface) {
		return ((Surface*)in_surface)->GetWidth();
	}


  // =======================================================================
  // Returns the height of a surface
  // =======================================================================
	int OGGetHeight(void* in_surface) {
		return ((Surface*)in_surface)->GetHeight();
	}


  // =======================================================================
  // Deletes an image that was previously loaded with OGLoadImage.  I'm not
	// absolutely sure this is necassery, but since the pointers to the
	// surfaces in all the widgets are void*'s, I wasn't comfortable deleting
	// a void*, so we'll do the proper cast here and then delete that.
  // =======================================================================
	void OGDeleteImage(void* in_surface) {
		delete (Surface*)in_surface;
	}


	// =======================================================================
  // Returns an int representing an RGB color.  I could see this being a
  // problem in the future, but I believe it will be fine for now.
	// =======================================================================
	int OGColor(int in_red, int in_green, int in_blue) {
		int RED_MASK    = 0x1F << 11;
		int GREEN_MASK  = 0x3F << 5;
		int BLUE_MASK   = 0x1F;
		return ((in_red << 8) & RED_MASK) | ((in_green << 3) & GREEN_MASK) | (in_blue >> 3);
	}


	// =======================================================================
  // Returns an OGRect with the values set to the input parameters.
	// =======================================================================
	OGRect OGSetRect(int in_left, int in_top, int in_right, int in_bottom) {
		OGRect ogrect;
		ogrect.left		= in_left;
		ogrect.top		= in_top;
		ogrect.right  = in_right;
		ogrect.bottom = in_bottom;
		return ogrect;
	}


	// =======================================================================
  // Draws a rectangle.
	// =======================================================================
	void OGDrawRect(void* in_display, int in_left, int in_top, int in_right, int in_bottom, int in_color) {
		((Display*)in_display)->DrawRect(in_left, in_top, in_right, in_bottom, in_color);		
	}


} // End OmnyGUI namespace