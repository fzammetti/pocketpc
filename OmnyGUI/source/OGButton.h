
// *****************************************************************************************************************************
// This is the class representing a button widget
// Note that all the images for the button must be the same width and height,
// and the width must be an even number!
// *****************************************************************************************************************************
class OGButton : public OGWidget {


  protected:


    void*					 pButtonUp;         // Surface for button when it is not being pressed
    void*					 pButtonDown;       // Surface for button when it is being pressed
    void*					 pButtonDisabled;   // Surface for button when it is disabled
    TCHAR					 text[32];          // The text displayed on button
    int						 textLength;        // Length of text displayed on button
    int						 buttonRightStart;  // Where the right half of the image begins
    OGRect				 leftHalf;          // Rect defining the left half of the button
    OGRect				 rightHalf;         // Rect defining the right half of the button
    OGRect				 repeatableSection; // Rect defining the middle repeating section of the button
    int						 textOffsetH;       // How far to the right from the start of the button should text begin
    int						 textOffsetV;       // How far down from the start of the button should text begin
    int						 textColor;         // What color to draw the text
    int						 textColorDisabled; // What color to draw the text when the button is disabled
		unsigned char* font;							// VGA font in use by widget
    bool           down;              // Flag; Is the button down (true) or not (false)?
    int            width;             // Width of the button surface
    int            height;            // Height of the button surface


    // =======================================================================
    // This is the method called each frame to display button.
    // =======================================================================
    void doWidget(void* in_display) {
      // First, determine which image we'll need to draw and point to it
      void* s;
      if (!enabled) {
        s = pButtonDisabled;
      } else {
        if (down) {
          s = pButtonDown;
        } else {
          s = pButtonUp;
        }
      }
      int left1 = left;
      // Draw the left half of the button
      OGBlit(in_display, left1, top, s, leftHalf);
      left1 = left1 + buttonRightStart;
      // Draw the  section behind the text.  We draw 4 of the repeatable
      // middle sections for each character, then add one more column after
      // that to account for the space between characters.
      for (int i = 0; i < textLength; i++) {
        for (int j = 0; j < 4; j++) {
					OGBlit(in_display, left1, top, s, repeatableSection);
          left1 = left1 + 2;
        }
				OGBlit(in_display, left1 - 1, top, s, repeatableSection);
        left1++;
      }
			left1--; // Correct for the one too many additions above
      // Draw the right half of the button
			OGBlit(in_display, left1, top, s, rightHalf);
      // Draw the text IF a font has been selected
			if (font != NULL) {
				int c = 0;
				if (enabled) {
					c = textColor;
				} else {
					c = textColorDisabled;
				}
				OGDrawVGAText(in_display, font, text, DVT_NONE, left + textOffsetH, top + textOffsetV,  c);
			}
    }

    
		// =======================================================================
		// stylsDown
		// =======================================================================
		void stylusDown(int in_x, int in_y) {
      down = true;
		}


		// =======================================================================
		// stylusUp
		// =======================================================================
		void stylusUp(int in_x, int in_y) {
      down = false;
      dispatchEvent(OG_EVENT_CLICK);
		}


    // =======================================================================
		// Determine the right and bottom bounds of the widget (i.e., how far it 
		// extends to the right and down from the left/top location).  This is 
		// used for stylus event region checking.
		// =======================================================================
    void calculateBounds() {
			right  = left + width + (textLength * 9); // Where the button starts + the width of the base button image + the length of the text and the spaces between each character
			bottom = top + height;
    }


	public:


    // =======================================================================
    // Constructor.
    // =======================================================================
    OGButton(void* in_display, TCHAR* in_id, int in_left, int in_top) {
			// Do initialization common to all widgets
			commonInit(in_id, in_left, in_top);
      // Load the images for the widget
      pButtonUp       = OGLoadImage(in_display, OG_IMG_BUTTON_UP,			  TEXT("OMNYGUI"));
      pButtonDown     = OGLoadImage(in_display, OG_IMG_BUTTON_DOWN,		  TEXT("OMNYGUI"));
      pButtonDisabled = OGLoadImage(in_display, OG_IMG_BUTTON_DISABLED, TEXT("OMNYGUI"));
      // Set the transparent color of the button
      OGSetTransparentColor(pButtonUp, OGColor(255, 128, 255));
      OGSetTransparentColor(pButtonDown, OGColor(255, 128, 255));
      OGSetTransparentColor(pButtonDisabled, OGColor(255, 128, 255));
      // Get the width and height of the widget
      width  = OGGetWidth(pButtonUp);
      height = OGGetHeight(pButtonUp);
      // Determine where the middle of the button is
      buttonRightStart = width / 2;
      // Set default text to nothing and get the length
      _tcscpy(text, TEXT(""));
      textLength = _tcslen(text);
      // Calculate rects for the left and right half of the button
			leftHalf = OGSetRect(0, 0, buttonRightStart - 1, height);
      rightHalf = OGSetRect(buttonRightStart + 1, 0, width, height);
      // Calculate a rect for the middle section of our button, one for each state.  
      // We assume the middle two columns of the button is repeatable, and will use 
      // it to fill in behind our letters.
      repeatableSection = OGSetRect(buttonRightStart - 1, 0, buttonRightStart + 1, height);
      // Set the default text offsets (always at least 2 horizontally to account for the repeating middle section)
      textOffsetH = 2;
      textOffsetV = 0;
      // Default text color
      textColor = OGColor(0, 0, 0);
      // Default disabled text color
      textColorDisabled = OGColor(161, 161, 146);
      // Initial state: NOT down
      down = false;
			// No font by default
			font = NULL;
    }


    // =======================================================================
    // Destructor.
    // =======================================================================
    ~OGButton() {
      OGDeleteImage(pButtonUp);
      OGDeleteImage(pButtonDown);
      OGDeleteImage(pButtonDisabled);
    }


    // =======================================================================
    // Calculate right and bottom and set visible to true
    // =======================================================================
		void show() {
      calculateBounds();
			visible = true;
		}


    // =======================================================================
    // Set text on widget.
    // =======================================================================
    void setText(TCHAR* in_text) {
      _tcscpy(text, in_text);
      textLength = _tcslen(text);
      calculateBounds();
    }


    // =======================================================================
    // Get text on widget.
    // =======================================================================
    TCHAR* getText() {
      return text;
    }


    // =======================================================================
    // Set horizontal text offset.  This can be used if the button image is 
    // bigger than the text itself can be, like if the image has sections on 
    // both sides and you want the text to always be within those sections, 
    // you can set an offset to move the text over by from the actual starting
    // position it would normally be at, which is the left side of the image.
    // =======================================================================
    void setTextOffsetH(int in_offsetH) {
      textOffsetH = in_offsetH;
    }


    // =======================================================================
    // Returns the current horizontal text offset value.
    // =======================================================================
    int getTextOffsetH() {
      return textOffsetH;
    }


    // =======================================================================
    // Set vertical text offset.
    // =======================================================================
    void setTextOffsetV(int in_offsetV) {
      textOffsetV = in_offsetV;
    }


    // =======================================================================
    // Returns the current vertical text offset value.
    // =======================================================================
    int getTextOffsetV() {
      return textOffsetV;
    }


		// =======================================================================
    // Set the font widget will use.
    // =======================================================================
    void setFont(int in_fontResourceID) {
			HRSRC   hResInfo	= NULL;
			HGLOBAL hResource = NULL;
			hResInfo					= FindResource(_Module.GetModuleInstance(), MAKEINTRESOURCE(in_fontResourceID), TEXT("OMNYGUI"));
			hResource					= LoadResource(_Module.GetModuleInstance(), hResInfo);
			font						  = (unsigned char*)LockResource(hResource);
    }


    // =======================================================================
    // Get the font widget is using.
    // =======================================================================
    unsigned char* getFont() {
      return font;
    }


};