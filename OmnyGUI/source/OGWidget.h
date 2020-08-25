
// *****************************************************************************************************************************
// This is the superclass of all widgets.
// *****************************************************************************************************************************
class OGWidget {


	protected:


    TCHAR           id[100];	    // ID assigned to widget by client
    int             left;			    // X location of widget
    int             top;			    // Y location of widget
		int             right;		    // X location widget extends to (this is the entire event area)
		int             bottom;		    // Y location widget extends to (this is the entire event area)
		bool	          enabled;	    // Flag; is widget enabled (true) or not (false)?
		bool            visible;      // Flag: is widget visible (true) or not (false)?
    OGEventHandler* eventHandler; // Event handler object registered to widget


	  // =======================================================================
    // Initilization common to all widgets.  Called from subclass constructor.
    // =======================================================================
		void commonInit(TCHAR* in_id, int in_left, int in_top) {
      // Set widget ID
			_tcscpy(id, in_id);
			// Enable by default
      enabled = true;
			// Set left and top
			left = in_left;
			top  = in_top;
			// Start out not visible
			visible = false;
      // Start with NO event handler
      eventHandler = NULL;
		}


    // =======================================================================
    // Dispatch event.  This is called when an event occurs in any widget
    // extending this base class.  It is passed the type of event that
    // occurred, and we call the corresponding method in the registered event
    // handler object, if one has been registered.
    // =======================================================================
    void dispatchEvent(int in_eventType) {
      if (eventHandler != NULL) {
        switch (in_eventType) {
          case OG_EVENT_CLICK: {
            eventHandler->click();
          break; }
          case OG_EVENT_CHANGE: {
            eventHandler->change();
          break; }
        }
      }
    }


    // =======================================================================
    // This method MUST be called from the show() method as well as any place
    // that might change the right and bottom bounds of a widget (like if the
    // text is changed in a button for instance).
		// This is used for stylus event region checking.
    // =======================================================================
    virtual void calculateBounds() = 0;


  public:


    friend class OGManager; // So manager has access to things not exposed in public interface


    // =======================================================================
    // Destructor.
    // =======================================================================
    ~OGWidget() {
      delete eventHandler;
    }


    // =======================================================================
    // Registers and event handler object for this widget that will be called
    // when various events occur.
    // =======================================================================
    void registerEventHandler(OGEventHandler* in_eventHandler) {
      eventHandler = in_eventHandler;
    }


		// =======================================================================
    // Called to make widget visible.  Subclass MUST implement and MUST
		// set right and top and MUST have as its last statement:
		// visible = true;
    // =======================================================================
		virtual void show() = 0;
		

		// =======================================================================
    // Called to make widget visible.  Subclass MUST implement and MUST
		// have as its last statement:
		// visible = true;
    // =======================================================================		
		void hide() {
			visible = false;
		}


		// =======================================================================
    // Returns true if widget is visible, false otherwise
    // =======================================================================	
		bool isVisible() {
			return visible;
		}


    // =======================================================================
    // Get the ID assigned to widget.
    // =======================================================================
    TCHAR* getID() {
      return id;
    }


		// =======================================================================
    // Get left bounds of widget
    // =======================================================================
    int getLeft() {
      return left;
    }


		// =======================================================================
    // Get top bounds of widget
    // =======================================================================
    int getTop() {
      return top;
    }

		// =======================================================================
    // Get right bounds of widget
    // =======================================================================
    int getRight() {
      return right;
    }


		// =======================================================================
    // Get bottom bounds of widget
    // =======================================================================
    int getBottom() {
      return bottom;
    }


		// =======================================================================
    // Enable widget
    // =======================================================================
    void enable() {
      enabled = true;
    }


    // =======================================================================
    // Disable widget
    // =======================================================================
    void disable() {
      enabled = false;
    }


		// =======================================================================
    // Checks if widget is enabled.  Returns true if so, false if not.
    // =======================================================================
    bool isEnabled() {
      return enabled;
    }


		// =======================================================================
    // Checks if a point is within the bounds of the widget.
    // =======================================================================
    bool isPointInBounds(int in_px, int in_py) {
      if (in_px >= left && in_px <= right && in_py >= top && in_py <= bottom) {
				return true;
			} else {
				return false;
			}
    }


		// =======================================================================
    // This is the method called each frame to display widget.  A subclass
    // MUST implement this, otherwise there's not much point!
    // =======================================================================
    virtual void doWidget(void* in_display) = 0;


		// =======================================================================
		// stylsDown
		// =======================================================================
    virtual void stylusDown(int in_x, int in_y) { }


		// =======================================================================
		// stylusUp
		// =======================================================================
    virtual void stylusUp(int in_x, int in_y) { }


		// =======================================================================
		// stylusMove
		// =======================================================================
    virtual void stylusMove(int in_x, int in_y) { }


};