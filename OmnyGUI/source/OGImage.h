
// *****************************************************************************************************************************
// This is the class representing an image widget
// *****************************************************************************************************************************
class OGImage : public OGWidget {


  protected:


    void*	pImage;	// The image to display
    bool  border; // Flag; Draw border around image (true) or not (false)?
    int   width;  // Width of the image
    int   height; // Height of the image


    // =======================================================================
    // This is the method called each frame to display button.
    // =======================================================================
    void doWidget(void* in_display) {
			if (pImage != NULL) {
				OGBlit(in_display, left, top, pImage);
				if (border) {
					OGDrawRect(in_display, left - 1, top - 1, width + 2, height + 2, OGColor(0, 0, 0));
				}
			}
    }

    
		// =======================================================================
		// stylsDown
		// =======================================================================
		void stylusDown(int in_x, int in_y) {
      dispatchEvent(OG_EVENT_CLICK);
		}


    // =======================================================================
		// Determine the right and bottom bounds of the widget (i.e., how far it 
		// extends to the right and down from the left/top location).  This is 
		// used for stylus event region checking.
		// =======================================================================
    void calculateBounds() {
			right  = left + OGGetWidth(pImage);
			bottom = top  + OGGetHeight(pImage);
    }


	public:


    // =======================================================================
    // Constructor.
    // =======================================================================
    OGImage(void* in_display, TCHAR* in_id, int in_left, int in_top) {
			// Do initialization common to all widgets
			commonInit(in_id, in_left, in_top);
			// No border by default
			border = false;
			// No image by default
			pImage = NULL;
    }


    // =======================================================================
    // Calculate right and bottom and set visible to true
    // =======================================================================
		void show() {
      calculateBounds();
			visible = true;
		}


    // =======================================================================
    // Set image to display
    // =======================================================================
    void setImage(void* in_image) {
			pImage = in_image;
      calculateBounds();
    }


    // =======================================================================
    // Get image
    // =======================================================================
    void* getImage() {
      return pImage;
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