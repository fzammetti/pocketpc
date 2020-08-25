
// *****************************************************************************************************************************
// This is the class representing a checkbox widget
// *****************************************************************************************************************************
class OGCheckbox : public OGWidget {


  protected:


    void*					 pCheckboxChecked;           // Surface for checkbox when it is checked
    void*					 pCheckboxUnchecked;         // Surface for checkbox when it is not checked
    void*					 pCheckboxCheckedDisabled;	 // Surface for checkbox when it is checked and disabled
    void*					 pCheckboxUncheckedDisabled; // Surface for checkbox when it is unchecked and disabled
    TCHAR					 text[32];                   // The text displayed next to the checkbox
		int						 textLength;                 // Length of text next to checkbox
		int            checkboxWidth;              // The width of the checkbox image
    int						 textColor;                  // What color to draw the text
    int						 textColorDisabled;          // What color to draw the text when the checkbox is disabled
		unsigned char* font;							         // VGA font in use by widget
    bool           checked;                    // Flag; Is the checkbox checked (true) or not (false)?
    int            width;                      // The width of the checkbox image


    // =======================================================================
    // This is the method called each frame to display widget.
    // =======================================================================
    void doWidget(void* in_display) {
      // First, determine which image we'll need to draw and point to it
      void* s;
      if (enabled && checked) {
        s = pCheckboxChecked;
      } else if (enabled && !checked) {
        s = pCheckboxUnchecked;
      } else if (!enabled && checked) {
        s = pCheckboxCheckedDisabled;
      } else if (!enabled && !checked) {
        s = pCheckboxUncheckedDisabled;
      }
			OGBlit(in_display, left, top, s);
      // Draw the text IF a font has been selected
			if (font != NULL) {
				int c = 0;
				if (enabled) {
					c = textColor;
				} else {
					c = textColorDisabled;
				}
				OGDrawVGAText(in_display, font, text, DVT_NONE, left + width + 4, top,  c);
			}
    }

    
		// =======================================================================
		// stylusUp
		// =======================================================================
		void stylusDown(int in_x, int in_y) {
      checked = !checked;
      dispatchEvent(OG_EVENT_CHANGE);
		}


    // =======================================================================
		// Determine the right and bottom bounds of the widget (i.e., how far it 
		// extends to the right and down from the left/top location).  This is 
		// used for stylus event region checking.
		// =======================================================================
    void calculateBounds() {
      right  = left + OGGetWidth(pCheckboxChecked) + (textLength * 9) + 4; // Where the checkbox starts + the width of the checkbox image + the size of the text including spaces between characters + the 4 pixels between the checkbox and the text
			bottom = top + OGGetHeight(pCheckboxChecked);
    }


	public:


    // =======================================================================
    // Constructor.
    // =======================================================================
    OGCheckbox(void* in_display, TCHAR* in_id, int in_left, int in_top) {
			// Do initialization common to all widgets
			commonInit(in_id, in_left, in_top);
      // Load the images for the button
      pCheckboxChecked           = OGLoadImage(in_display, OG_IMG_CHECKBOX_CHECKED,	 TEXT("OMNYGUI"));
      pCheckboxUnchecked         = OGLoadImage(in_display, OG_IMG_CHECKBOX_UNCHECKED, TEXT("OMNYGUI"));
      pCheckboxCheckedDisabled   = OGLoadImage(in_display, OG_IMG_CHECKBOX_CHECKED_DISABLED,  TEXT("OMNYGUI"));
      pCheckboxUncheckedDisabled = OGLoadImage(in_display, OG_IMG_CHECKBOX_UNCHECKED_DISABLED,  TEXT("OMNYGUI"));
      // Set the transparent color of the widget
      OGSetTransparentColor(pCheckboxChecked, OGColor(255, 128, 255));
      OGSetTransparentColor(pCheckboxUnchecked, OGColor(255, 128, 255));
      OGSetTransparentColor(pCheckboxCheckedDisabled, OGColor(255, 128, 255));
      OGSetTransparentColor(pCheckboxUncheckedDisabled, OGColor(255, 128, 255));
      // Get the width of the checkbox image surface
      width = OGGetWidth(pCheckboxChecked);
      // Set default text to nothing and get the length
      _tcscpy(text, TEXT(""));
      textLength = _tcslen(text);
      // Default text color
      textColor = OGColor(0, 0, 0);
      // Default disabled text color
      textColorDisabled = OGColor(161, 161, 146);
      // Initial state: NOT checked
      checked = false;
			// No font by default
			font = NULL;
    }


    // =======================================================================
    // Destructor.
    // =======================================================================
    ~OGCheckbox() {
      OGDeleteImage(pCheckboxChecked);
      OGDeleteImage(pCheckboxUnchecked);
      OGDeleteImage(pCheckboxCheckedDisabled);
      OGDeleteImage(pCheckboxUncheckedDisabled);
    }


    // =======================================================================
    // Calculate right and bottom and set visible to true
    // =======================================================================
		void show() {
			calculateBounds();			
			visible = true;
		}


    // =======================================================================
    // Set text next to widget
    // =======================================================================
    void setText(TCHAR* in_text) {
      _tcscpy(text, in_text);
      textLength = _tcslen(text);
      calculateBounds();
    }


    // =======================================================================
    // Get text next to widget
    // =======================================================================
    TCHAR* getText() {
      return text;
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