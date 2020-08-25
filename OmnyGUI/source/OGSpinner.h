
// *****************************************************************************************************************************
// This is the class representing a spinner widget
// *****************************************************************************************************************************
class OGSpinner : public OGWidget {


  protected:


    void*					 pSpinnerTextbox;          // Surface for spinner's textbox portion when it is not disabled
    void*					 pSpinnerButtons;					 // Surface for spinner's buttons portion when it is not disabled
		void*					 pSpinnerTopButtonDown;    // Surface for spinner's buttons portion when it is not disabled and the top button is pressed
		void*					 pSpinnerBottomButtonDown; // Surface for spinner's buttons portion when it is not disabled and the bottom button is pressed
		void*					 pSpinnerTextboxDisabled;  // Surface for spinner's textbox portion when it is disabled
		void*					 pSpinnerButtonsDisabled;  // Surface for spinner's buttons portion when it is disabled
    int						 minValue;								 // Minimum number spinner will accept
		int						 maxValue;								 // Maximum number spinner will accept
    OGRect				 repeatableSection;				 // Rect defining the repeating section of the textbox portion
    OGRect				 nonRepeatableSection;		 // Rect defining the non-repeating section of the textbox portion
    int						 textColor;								 // What color to draw the text
    int						 textColorDisabled;				 // What color to draw the text when the spinner is disabled
		unsigned char* font;										 // VGA font in use by widget
    bool           topDown;									 // Flag; Is the top button down (true) or not (false)?
		bool           bottomDown;							 // Flag; Is the bottom button down (true) or not (false)?
		int            value;                    // Current value of the spinner
    int            textLength;               // Number of characters displayed in textbox portion
    int						 textOffsetH;              // How far to the right from the start of the textbox portion should text begin
    int						 textOffsetV;              // How far down from the start of the textbox portion should text begin
    int            repeatRateCounter;        // How many frames to delay between changing the value when a button is being held down
    int            repeatRate;               // How quickly the value should change when a button is being held down
    int            buttonsLeft;              // X coordinates the buttons were drawn at


    // =======================================================================
    // This is the method called each frame to display button.
    // =======================================================================
    void doWidget(void* in_display) {
      // First, determine which image we'll need to draw and point to it
      void* pTextboxSurface;
      void* pButtonsSurface;
      if (!enabled) {
        pTextboxSurface = pSpinnerTextboxDisabled;
        pButtonsSurface = pSpinnerButtonsDisabled;
      } else {
        pTextboxSurface = pSpinnerTextbox;
        if (topDown) {
          pButtonsSurface = pSpinnerTopButtonDown;
        } else if (bottomDown) {
          pButtonsSurface = pSpinnerBottomButtonDown;
        } else {
          pButtonsSurface = pSpinnerButtons;
        }
      }
      int left1 = left;
      // Draw the non-repeating section of the textbox
      OGBlit(in_display, left1, top, pTextboxSurface, nonRepeatableSection);
      left1 = left1 + (OGGetWidth(pTextboxSurface) - 1);
      // Draw the  section behind the text.  We draw 9 of the repeatable
      // middle sections for each character.
      for (int i = 0; i < textLength; i++) {
        for (int j = 0; j < 9; j++) {
          OGBlit(in_display, left1, top, pTextboxSurface, repeatableSection);
          left1++;
        }
      }
      // Draw the buttons
      buttonsLeft = left1;
      OGBlit(in_display, left1, top, pButtonsSurface);
      // Draw the text in the textbox portion IF a font has been selected
			if (font != NULL) {
				int c = 0;
				if (enabled) {
					c = textColor;
				} else {
					c = textColorDisabled;
				}
        TCHAR txt[10] = TEXT("");
        _stprintf(txt, TEXT("%d"), value);
				OGDrawVGAText(in_display, font, txt, DVT_NONE, left + textOffsetH, top + textOffsetV,  c);
			}
      // If a button is being held down, adjust the value accordingly, dealing with the delay too
      if (topDown || bottomDown) {
        repeatRateCounter++;
        if (repeatRateCounter > repeatRate) {
          repeatRateCounter = 0;
          if (topDown && value < maxValue) {
            value++;
          }
          if (bottomDown && value > minValue) {
            value--;
          }
          dispatchEvent(OG_EVENT_CHANGE);
        }
      }
    }

    
		// =======================================================================
		// stylsDown
		// =======================================================================
		void stylusDown(int in_x, int in_y) {
      if (in_x >= buttonsLeft && in_x <= right) {
        repeatRateCounter = 1000; // We want an immediate value change
        if (in_y >= top && in_y <= top + (int)(OGGetWidth(pSpinnerButtons) / 2)) {
          topDown = true;
        }
        if (in_y >= top + (int)(OGGetHeight(pSpinnerButtons)) / 2 && in_y <= bottom) {
          bottomDown = true;
        }
      }
		}


		// =======================================================================
		// stylsUp
		// =======================================================================
		void stylusUp(int in_x, int in_y) {
			topDown           = false;
      bottomDown        = false;
		}


    // =======================================================================
		// Determine the right and bottom bounds of the widget (i.e., how far it 
		// extends to the right and down from the left/top location).  This is 
		// used for stylus event region checking.
		// =======================================================================
    void calculateBounds() {
      right = OGGetWidth(pSpinnerTextbox) + (textLength * 9) + 1 + OGGetWidth(pSpinnerButtons);
      bottom = top + OGGetHeight(pSpinnerTextbox);
    }


	public:


    // =======================================================================
    // Constructor.
    // =======================================================================
    OGSpinner(void* in_display, TCHAR* in_id, int in_left, int in_top) {
			// Do initialization common to all widgets
			commonInit(in_id, in_left, in_top);
      // Load the images for the widget
			pSpinnerTextbox					 = OGLoadImage(in_display, OG_IMG_SPINNER_TEXTBOX,					  TEXT("OMNYGUI"));
			pSpinnerButtons					 = OGLoadImage(in_display, OG_IMG_SPINNER_BUTTONS,					  TEXT("OMNYGUI"));
			pSpinnerTopButtonDown    = OGLoadImage(in_display, OG_IMG_SPINNER_TOP_BUTTON_DOWN,		TEXT("OMNYGUI"));
			pSpinnerBottomButtonDown = OGLoadImage(in_display, OG_IMG_SPINNER_BOTTOM_BUTTON_DOWN,	TEXT("OMNYGUI"));
			pSpinnerTextboxDisabled  = OGLoadImage(in_display, OG_IMG_SPINNER_TEXTBOX_DISABLED,		TEXT("OMNYGUI"));
			pSpinnerButtonsDisabled  = OGLoadImage(in_display, OG_IMG_SPINNER_BUTTONS_DISABLED,		TEXT("OMNYGUI"));
      // Set the transparent color of the button
			OGSetTransparentColor(pSpinnerTextbox, OGColor(255, 128, 255));
			OGSetTransparentColor(pSpinnerButtons, OGColor(255, 128, 255));
			OGSetTransparentColor(pSpinnerTopButtonDown, OGColor(255, 128, 255));
			OGSetTransparentColor(pSpinnerBottomButtonDown, OGColor(255, 128, 255));
			OGSetTransparentColor(pSpinnerTextboxDisabled, OGColor(255, 128, 255));
			OGSetTransparentColor(pSpinnerButtonsDisabled, OGColor(255, 128, 255));
      // Calculate a rect for the non-repeating section of our spinner's textbox portion.
      // We assume all but last column of the textbox portion is non-repeatable.
			nonRepeatableSection = OGSetRect(0, 0, OGGetWidth(pSpinnerTextbox) - 1, OGGetHeight(pSpinnerTextbox));
      // Calculate a rect for the repeating section of our spinner's textbox portion.
      // We assume the last column of the textbox portion is repeatable, and will use 
      // it to fill in behind our text.
			repeatableSection = OGSetRect(OGGetWidth(pSpinnerTextbox) - 1, 0, OGGetWidth(pSpinnerTextbox), OGGetHeight(pSpinnerTextbox));
      // Default text color
      textColor = OGColor(0, 0, 0);
      // Default disabled text color
      textColorDisabled = OGColor(161, 161, 146);
      // Initial state: NO buttons down down
      topDown		 = false;
			bottomDown = false;
			// Initial value and min/max values
			value		 = 0;
			minValue = 0;
			maxValue = 1000;
			// No font by default
			font = NULL;
      // Initial text offsets (at least 2 for horizontal to account for repeating section and a space between a border and the text)
      textOffsetH = 2;
      textOffsetV = 0;
    }


    // =======================================================================
    // Destructor.
    // =======================================================================
    ~OGSpinner() {
			OGDeleteImage(pSpinnerTextbox);
			OGDeleteImage(pSpinnerButtons);
			OGDeleteImage(pSpinnerTopButtonDown);
			OGDeleteImage(pSpinnerBottomButtonDown);
			OGDeleteImage(pSpinnerTextboxDisabled);
			OGDeleteImage(pSpinnerButtonsDisabled);
	}


    // =======================================================================
    // Set repeat rate.
    // =======================================================================
    void setRepeatRate(int in_repeatRate) {
      repeatRate = in_repeatRate;
    }


    // =======================================================================
    // Get repeat rate.
    // =======================================================================
    int getRepeatRate() {
      return repeatRate;
    }


    // =======================================================================
    // Set horizontal text offset.  This can be used to correctly position
    // the text inside the textbox portion.
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
    // Calculate right and bottom and set visible to true
    // =======================================================================
		void show() {
      calculateBounds();
			visible = true;
		}


    // =======================================================================
    // Set minimum value spinner will accept
    // =======================================================================
    void setMinValue(int in_minValue) {
			minValue = in_minValue;
			// Handle the situation where the minimum is changed and the current
			// value is lower than the new minimum.
			if (value < minValue) {
				value = minValue;
			}
    }


    // =======================================================================
    // Get minimum value spinner will accept
    // =======================================================================
    int getMinValue() {
			return minValue;
    }


    // =======================================================================
    // Set maximum value spinner will accept
    // =======================================================================
    void setMaxValue(int in_maxValue) {
			maxValue = in_maxValue;
			// Handle the situation where the maximum is changed and the current
			// value is higher than the new maximum.
			if (value > maxValue) {
				value = maxValue;
			}
      // We also need to determine how many digits are in the maximum value
      // and that will become our textLength
      if (maxValue >= 0          && maxValue <= 9)          { textLength = 1;  }
      if (maxValue >= 10         && maxValue <= 99)         { textLength = 2;  }
      if (maxValue >= 100        && maxValue <= 999)        { textLength = 3;  }
      if (maxValue >= 1000       && maxValue <= 9999)       { textLength = 4;  }
      if (maxValue >= 10000      && maxValue <= 99999)      { textLength = 5;  }
      if (maxValue >= 100000     && maxValue <= 999999)     { textLength = 6;  }
      if (maxValue >= 1000000    && maxValue <= 9999999)    { textLength = 7;  }
      if (maxValue >= 10000000   && maxValue <= 99999999)   { textLength = 8;  }
      if (maxValue >= 100000000  && maxValue <= 999999999)  { textLength = 9;  }
      if (maxValue >= 1000000000 && maxValue <= 9999999999) { textLength = 10; }
      calculateBounds();
    }


    // =======================================================================
    // Get maximum value spinner will accept
    // =======================================================================
    int getMaxValue() {
			return maxValue;
    }


    // =======================================================================
    // Set value of spinner
    // =======================================================================
    void setValue(int in_value) {
			if (in_value > maxValue) {
				value = maxValue;
			} else if (in_value < minValue) {
				value = minValue;
			} else {
				value = in_value;
			}
      calculateBounds();
    }


    // =======================================================================
    // Get the current value of the spinner
    // =======================================================================
    int getValue() {
			return value;
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