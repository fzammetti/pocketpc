
// *****************************************************************************************************************************
// This is the class representing a slidder widget
// *****************************************************************************************************************************
class OGSlider : public OGWidget {


  protected:


    void*	 pSliderKnob;
    void*	 pSliderKnobGrabbed;
		void*	 pSliderLine;
    void*	 pSliderKnobDisabled;
		void*	 pSliderLineDisabled;
    int		 minValue;
		int		 maxValue;
    OGRect repeatableSection;
    OGRect nonRepeatableSection;
		int    value;
		int    length;
		int    knobLeft;
		int    knobTop;
		bool   knobGrabbed;
		int    stylusLastX;


    // =======================================================================
    // This is the method called each frame to display button.
    // =======================================================================
    void doWidget(void* in_display) {
      void* pLineSurface;
      void* pKnobSurface;
      if (enabled) {
        pLineSurface = pSliderLine;
				if (knobGrabbed) {
					pKnobSurface = pSliderKnobGrabbed;
				} else {
					pKnobSurface = pSliderKnob;
				}
      } else {
        pLineSurface = pSliderLineDisabled;
        pKnobSurface = pSliderKnobDisabled;
      }
			// Draw line...first the end, then extended out to the length
			OGBlit(in_display, left, top, pLineSurface, nonRepeatableSection);
			for (int i = OGGetWidth(pSliderLine) - 1; i < length; i++) {
				OGBlit(in_display, left + i, top, pLineSurface, repeatableSection);
			}
			// Draw knob
			OGBlit(in_display, knobLeft, knobTop, pKnobSurface);
    }

    
		// =======================================================================
		// stylsDown
		// =======================================================================
		void stylusDown(int in_x, int in_y) {
			knobGrabbed = true;
			stylusLastX = in_x;
		}


		// =======================================================================
		// stylusUp
		// =======================================================================
		void stylusUp(int in_x, int in_y) {
			knobGrabbed = false;
		}


		// =======================================================================
		// stylusMove
		// =======================================================================
		void stylusMove(int in_x, int in_y) {
			if (knobGrabbed) {
				if (in_x > stylusLastX) {
					knobLeft++;
					stylusLastX = in_x;
					calculateBounds();
				} else if (in_x < stylusLastX) {
					knobLeft--;
					stylusLastX = in_x;
					calculateBounds();
				}
			}
		}


    // =======================================================================
		// Determine the right and bottom bounds of the widget (i.e., how far it 
		// extends to the right and down from the left/top location).  This is 
		// used for stylus event region checking.
		// =======================================================================
    void calculateBounds() {
			// We need to calculate the height of the knob MINUS the height of the
			// line so that we can determine where to place it in relation to the
			// line such that it is vertically centered on the line.
			right	 = knobLeft + OGGetWidth(pSliderKnob);
			bottom = top + OGGetHeight(pSliderLine) + ((OGGetHeight(pSliderKnob) - OGGetHeight(pSliderLine)) / 2);
    }


	public:


    // =======================================================================
    // Constructor.
    // =======================================================================
    OGSlider(void* in_display, TCHAR* in_id, int in_left, int in_top) {
			// Do initialization common to all widgets
			commonInit(in_id, in_left, in_top);
      // Load the images for the widget
			pSliderKnob				  = OGLoadImage(in_display, OG_IMG_SLIDER_KNOB,					 TEXT("OMNYGUI"));
			pSliderKnobGrabbed  = OGLoadImage(in_display, OG_IMG_SLIDER_KNOB_GRABBED,  TEXT("OMNYGUI"));
			pSliderLine				  = OGLoadImage(in_display, OG_IMG_SLIDER_LINE,				   TEXT("OMNYGUI"));
			pSliderKnobDisabled = OGLoadImage(in_display, OG_IMG_SLIDER_KNOB_DISABLED, TEXT("OMNYGUI"));
			pSliderLineDisabled	= OGLoadImage(in_display, OG_IMG_SLIDER_LINE_DISABLED, TEXT("OMNYGUI"));
      // Set the transparent color of the button
			OGSetTransparentColor(pSliderKnob,				 OGColor(255, 128, 255));
			OGSetTransparentColor(pSliderKnobGrabbed,  OGColor(255, 128, 255));
			OGSetTransparentColor(pSliderLine,			 	 OGColor(255, 128, 255));
			OGSetTransparentColor(pSliderKnobDisabled, OGColor(255, 128, 255));
			OGSetTransparentColor(pSliderLineDisabled, OGColor(255, 128, 255));
      // Calculate a rect for the non-repeating section of our spinner's textbox portion.
      // We assume all but last column of the textbox portion is non-repeatable.
			nonRepeatableSection = OGSetRect(0, 0, OGGetWidth(pSliderLine) - 1, OGGetHeight(pSliderLine));
      // Calculate a rect for the repeating section of our spinner's textbox portion.
      // We assume the last column of the textbox portion is repeatable, and will use 
      // it to fill in behind our text.
			repeatableSection = OGSetRect(OGGetWidth(pSliderLine) - 1, 0, OGGetWidth(pSliderLine), OGGetHeight(pSliderLine));
			// Initial default values
			minValue		= 0;
			maxValue		= 100;
			value				= 50;
			length			= 200;
			// Center knob horizontally and verticallly to begin with
			knobLeft		= left + ((length / 2) - OGGetWidth(pSliderKnob) / 2);
			knobTop     = top - ((OGGetHeight(pSliderKnob) - OGGetHeight(pSliderLine)) / 2); 
			knobGrabbed = false;
    }


    // =======================================================================
    // Destructor.
    // =======================================================================
    ~OGSlider() {
			OGDeleteImage(pSliderKnob);
			OGDeleteImage(pSliderKnobGrabbed);
			OGDeleteImage(pSliderLine);
			OGDeleteImage(pSliderKnobDisabled);
			OGDeleteImage(pSliderLineDisabled);
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
    // Set maximum value slider will accept
    // =======================================================================
    void setMaxValue(int in_maxValue) {
			maxValue = in_maxValue;
			// Handle the situation where the maximum is changed and the current
			// value is higher than the new maximum.
			if (value > maxValue) {
				value = maxValue;
			}
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
    }


    // =======================================================================
    // Get the current value of the spinner
    // =======================================================================
    int getValue() {
			return value;
    }


    // =======================================================================
    // Set the length of the line
    // =======================================================================
    void setLength(int in_length) {
			length = in_length;
			calculateBounds();
    }


    // =======================================================================
    // Get the length of the line
    // =======================================================================
    int getLength() {
			return length;
    }


		// =======================================================================
    // Checks if a point is within the bounds of the slider's knob.  Note this 
		// is an overriden version because the one in the base OGWidget class
		// checks against the bounds of the ENTIRE widget.  In this case though we
		// only want ot react to events within the bounds of the knob.
    // =======================================================================
    bool isPointInBounds(int in_px, int in_py) {
      if (in_px >= knobLeft && in_px <= right) {
				return true;
			} else {
				return false;
			}
    }

};