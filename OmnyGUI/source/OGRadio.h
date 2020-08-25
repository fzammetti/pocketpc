
// *****************************************************************************************************************************
// This is the class representing a radio button widget
// *****************************************************************************************************************************
class OGRadio : public OGWidget {


  protected:


    void*					 pRadioSelected;           // Surface for radio button when it is selected
    void*					 pRadioUnselected;         // Surface for radio button when it is not selected
    void*					 pRadioSelectedDisabled;   // Surface for radio button when it is selected and disabled
    void*				 	 pRadioUnselectedDisabled; // Surface for radio button when it is not selected and disabled
    int						 textColor;                // What color to draw the text
    int						 textColorDisabled;        // What color to draw the text when the checkbox is disabled
		unsigned char* font;							       // VGA font in use by widget
    int            which;                    // Which radio button of the group is selected
    TCHAR          options[20][50];          // All the options that are a part of this radio button group
    int            optionCount;              // Current number of options in the group
    int            width;                    // The width of the radio button image surface


    // =======================================================================
    // This is the method called each frame to display widget.
    // =======================================================================
    void doWidget(void* in_display) {
      void* s;
      int top1 = top;
      // Determine which image to draw
      for (int i = 0; i < optionCount; i++) {
        if (which == i && enabled) {
          s = pRadioSelected;
        } else if (which != i && enabled) {
          s = pRadioUnselected;
        } else if (which == i && !enabled) {
          s = pRadioSelectedDisabled;
        } else if (which != i && !enabled) {
          s = pRadioUnselectedDisabled;
        }
        // Draw the image
        OGBlit(in_display, left, top1, s);
			  if (font != NULL) {
				  int c = 0;
				  if (enabled) {
					  c = textColor;
				  } else {
					  c = textColorDisabled;
				  }
				  OGDrawVGAText(in_display, font, options[i], DVT_NONE, left + width + 4, top1,  c);
			  }
        top1 = top1 + 18;
      }
    }

    
		// =======================================================================
		// stylusDown
		// =======================================================================
		void stylusDown(int in_x, int in_y) {
      // If we're here, the stylus was placed within the bounds of this widget.
      // Now we need to determine exactly which of the options was clicked.
      int optionRight  = 0;
      int optionTop    = 0;
      int optionBottom = 0;
      int textLength   = 0;
      for (int i = 0; i < optionCount; i++) {
        textLength   = _tcslen(options[i]);
        optionRight  = left + width + (textLength *9) + 4; // Where the radio button starts + the width of the radio button image + the length of the text and spaces in between characters + the 4 pixels between the radio image and the text
        optionTop    = top + (i * 18);
        optionBottom = optionTop + 18;
        if (in_x >= left && in_x <= optionRight && in_y >= optionTop && in_y <= optionBottom) {
          if (which != i) {
            which = i;
            dispatchEvent(OG_EVENT_CHANGE);
          }
        }
      }
		}


		// =======================================================================
		// This method is called from show() as well as any methods that modifies
    // the list of options.  It is used to determine the current right and
    // bottom bounds of the widget.
		// =======================================================================
    void calculateBounds() {
      int longest      = 0;
      int longestIndex = 0;
      for (int i = 0; i < optionCount; i++) {
        int len = _tcslen(options[i]);
        if (len > longest) {
          longestIndex = i;
        }
      }
      right  = left + _tcslen(options[longestIndex]);
      bottom = top + (18 * optionCount);
    }


	public:


    // =======================================================================
    // Constructor.
    // =======================================================================
    OGRadio(void* in_display, TCHAR* in_id, int in_left, int in_top) {
			// Do initialization common to all widgets
			commonInit(in_id, in_left, in_top);
      // Load the images for the button
      pRadioSelected            = OGLoadImage(in_display, OG_IMG_RADIO_SELECTED,	          TEXT("OMNYGUI"));
      pRadioUnselected          = OGLoadImage(in_display, OG_IMG_RADIO_UNSELECTED,          TEXT("OMNYGUI"));
      pRadioSelectedDisabled    = OGLoadImage(in_display, OG_IMG_RADIO_SELECTED_DISABLED,   TEXT("OMNYGUI"));
      pRadioUnselectedDisabled  = OGLoadImage(in_display, OG_IMG_RADIO_UNSELECTED_DISABLED, TEXT("OMNYGUI"));
      // Get the width of the radio button image surface
      width = OGGetWidth(pRadioSelected);
      // Set the transparent color of the widget
      OGSetTransparentColor(pRadioSelected, OGColor(255, 128, 255));
      OGSetTransparentColor(pRadioUnselected, OGColor(255, 128, 255));
      OGSetTransparentColor(pRadioSelectedDisabled, OGColor(255, 128, 255));
      OGSetTransparentColor(pRadioUnselectedDisabled, OGColor(255, 128, 255));
      // Default text color
      textColor = OGColor(0, 0, 0);
      // Default disabled text color
      textColorDisabled = OGColor(161, 161, 146);
      // No option selected by default, and clear out the array to be sure
      clearOptions();
      which = -1;
    }


    // =======================================================================
    // Destructor.
    // =======================================================================
    ~OGRadio() {
      OGDeleteImage(pRadioSelected);
      OGDeleteImage(pRadioUnselected);
      OGDeleteImage(pRadioSelectedDisabled);
      OGDeleteImage(pRadioUnselectedDisabled);
    }


    // =======================================================================
    // Calculate right and bottom and set visible to true
    // =======================================================================
		void show() {
			// Determine the right and bottom bounds of the widget (i.e., how far it extends
			// to the right and down from the left/top location).  This is used for
			// stylus event region checking.
      calculateBounds();
			visible = true;
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

    
    // =======================================================================
    // Clears any options currently in this radio button group.
    // =======================================================================
    void clearOptions() {
      for (int i = 0; i < 20; i++) {
        _tcscpy(options[i], TEXT(""));
      }
      optionCount = 0;
      which       = -1;
      calculateBounds();
    }


    // =======================================================================
    // Adds a new option to this radio button group at the end.
    // =======================================================================
    void addOption(TCHAR* in_optionText) {
      if (optionCount < 20) {
        _tcscpy(options[optionCount], in_optionText);
        optionCount++;
      }
      calculateBounds();
    }


};