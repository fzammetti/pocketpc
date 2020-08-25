
// *****************************************************************************************************************************
// This is the class representing a text label widget
// *****************************************************************************************************************************
class OGLabel : public OGWidget {


  protected:


    int						 textColor;					// What color to draw the text
    int						 textColorDisabled;	// What color to draw the text when the spinner is disabled
		unsigned char* font;							// VGA font in use by widget
    int            textLength;        // Number of characters displayed in textbox portion
		TCHAR          text[32];          // Text of this label  
		bool           border;            // Should the border be drawn?



    // =======================================================================
    // This is the method called each frame to display button.
    // =======================================================================
    void doWidget(void* in_display) {
			int c = 0;
			if (enabled) {
				c = textColor;
			} else {
				c = textColorDisabled;
			}
			int xAdjust = 0; // This will be set to non-zero if the border is to be drawn
			int yAdjust = 0; // This will be set to non-zero if the border is to be drawn
			if (border) {
				OGDrawRect(in_display, left, top, right, bottom, c);
				xAdjust = 4;
				yAdjust = 2;
			}
			if (font != NULL) {
				OGDrawVGAText(in_display, font, text, DVT_NONE, left + xAdjust, top + yAdjust,  c);
			}
    }

    
    // =======================================================================
		// Determine the right and bottom bounds of the widget (i.e., how far it 
		// extends to the right and down from the left/top location).  This is 
		// used for stylus event region checking.
		// =======================================================================
    void calculateBounds() {
			right  = 6 + ((textLength + 1) * 9); // 2 pixels total for border on either side and 2 for space between border on either side and text + Length of text
			bottom = top + 19;
    }


	public:


    // =======================================================================
    // Constructor.
    // =======================================================================
    OGLabel(void* in_display, TCHAR* in_id, int in_left, int in_top) {
			commonInit(in_id, in_left, in_top);
      // Default text color
      textColor = OGColor(0, 0, 0);
      // Default disabled text color
      textColorDisabled = OGColor(161, 161, 146);
			// No font by default
			font = NULL;
			// No border by default
			border = false;
			// Default no text
			_tcscpy(text, TEXT(""));
			textLength = 0;
    }


    // =======================================================================
    // Destructor.
    // =======================================================================
    ~OGLabel() {
    }


    // =======================================================================
    // Calculate right and bottom and set visible to true
    // =======================================================================
		void show() {
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
    // Border should be drawn around the label text.
    // =======================================================================
		void showBorder() {
			border = true;
		}


    // =======================================================================
    // Border should NOT be drawn around the label text.
    // =======================================================================
		void hideBorder() {
			border = false;
		}


};