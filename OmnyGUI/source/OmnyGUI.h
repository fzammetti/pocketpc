
// Notes
// 
// * All OmnyGUI resources are in the group OMNYGUI.
//
// * All widgets are constructed with (int type, TCHAR* id, int left, int top)
//
// * A widget MUST be completely set up before calling show()!  If it is not,
//   the behavior is underfined.


#ifndef OMNYGUI_H
#define OMNYGUI_H


#define OG_MAX_WIDGETS     50   // The maximum number of widgets a manager can handle.  It's arbitrary, but 50 should be MORE than enough for even the stupidest UI!
#define OG_WIDGET_BUTTON   1    // Code for a button widget
#define OG_WIDGET_CHECKBOX 2    // Code for a button widget
#define OG_WIDGET_RADIO    3    // Code for a radio button widget
#define OG_WIDGET_SPINNER  4    // Code for a spinner widget
#define OG_WIDGET_LABEL    5    // Code for a text label widget
#define OG_WIDGET_IMAGE    6    // Code for an image widget
#define OG_WIDGET_SLIDER   7    // Code for an slider widget
#define OG_EVENT_CLICK     100  // Code for a click event (corresponds to a StylusUp event)
#define OG_EVENT_CHANGE    101  // Code for a change event (like when a checkbox is clicked)


#include "OGAbstractionLayer_PocketFrog.h"


using namespace OmnyGUI;


#include "OGEventHandler.h"
#include "OGWidget.h"
#include "OGButton.h"
#include "OGCheckbox.h"
#include "OGRadio.h"
#include "OGSpinner.h"
#include "OGLabel.h"
#include "OGImage.h"
#include "OGSlider.h"


// *****************************************************************************************************************************
// This is the main OGManager class.  Clients should only ever make calls to
// this object (or except to widgets that it returns a reference to).
// Note that a client can instantiate as many of these as they want, so it
// should be possible to have multiple screens of a GUI created and just keep
// it hidden until needed.
// *****************************************************************************************************************************
class OGManager {


  private:


    int       widgetCount;
    bool      active;
    OGWidget* pWidgets[OG_MAX_WIDGETS];


  public:


    // =======================================================================
    // Constructor.
    // =======================================================================
    OGManager() {
			// Clear out our array of widgets for good measure
      widgetCount = 0;
      for (int i = 0; i < OG_MAX_WIDGETS; i++) {
        pWidgets[i] = NULL;
      }
      // Start out INACTIVE.  This means no widgets will be shown, no
      // events processed.
      active = false;
    }


    // =======================================================================
    // doGUI.  Called once per frame by client to draw the GUI.
    // =======================================================================
    void doGUI(void* in_display) {
      if (active) {
			  // Cycle through all widgets in widget array.  For any that are visible,
			  // ask them to draw themselves.
        for (int i = 0; i < widgetCount; i++) {
          if (pWidgets[i] != NULL && pWidgets[i]->isVisible()) {
            pWidgets[i]->doWidget(in_display);
          }
        }
      }
    }


    // =======================================================================
    // Adds a widget to the collection of widgets this manager is
    // managing.  Widget is assigned the supplied ID.
    // =======================================================================
    OGWidget* addWidget(void* in_display, int in_type, TCHAR* in_id, int in_left, int in_top) {
			OGWidget* widget = NULL;
			// Determine what kind of widget to create and do it
      if (widgetCount < OG_MAX_WIDGETS) {
        switch (in_type) {
          case OG_WIDGET_BUTTON: {
            OGButton* button = new OGButton(in_display, in_id, in_left, in_top);
						widget = button; // So that we can return the widget if caller needs it
            pWidgets[widgetCount] = button;
            widgetCount++;
          break; }
          case OG_WIDGET_CHECKBOX: {
            OGCheckbox* checkbox = new OGCheckbox(in_display, in_id, in_left, in_top);
						widget = checkbox; // So that we can return the widget if caller needs it
            pWidgets[widgetCount] = checkbox;
            widgetCount++;
          break; }
          case OG_WIDGET_RADIO: {
            OGRadio* radio = new OGRadio(in_display, in_id, in_left, in_top);
						widget = radio; // So that we can return the widget if caller needs it
            pWidgets[widgetCount] = radio;
            widgetCount++;
          break; }
          case OG_WIDGET_SPINNER: {
            OGSpinner* spinner = new OGSpinner(in_display, in_id, in_left, in_top);
						widget = spinner; // So that we can return the widget if caller needs it
            pWidgets[widgetCount] = spinner;
            widgetCount++;
          break; }
          case OG_WIDGET_LABEL: {
            OGLabel* label = new OGLabel(in_display, in_id, in_left, in_top);
						widget = label; // So that we can return the widget if caller needs it
            pWidgets[widgetCount] = label;
            widgetCount++;
          break; }
          case OG_WIDGET_IMAGE: {
            OGImage* image = new OGImage(in_display, in_id, in_left, in_top);
						widget = image; // So that we can return the widget if caller needs it
            pWidgets[widgetCount] = image;
            widgetCount++;
          break; }
          case OG_WIDGET_SLIDER: {
            OGSlider* slider = new OGSlider(in_display, in_id, in_left, in_top);
						widget = slider; // So that we can return the widget if caller needs it
            pWidgets[widgetCount] = slider;
            widgetCount++;
          break; }
        }
      }
			return widget;
    }


    // =======================================================================
    // Removes a widget from the collection of widgets this manager is
    // managing.  Widget is assigned the supplied ID.
    // =======================================================================
    void removeWidget(TCHAR* in_id) {
      int i;
			// Find the widget in the widget collection, and destroy it
      for (i = 0; i < widgetCount; i++) {
        if (_tcscmp(pWidgets[i]->getID(), in_id) == 0) {
          delete pWidgets[i];
          pWidgets[i] = NULL;
        }
      }
      // We're now going to "tighten up" the pWidgets array, which means remove
      // any null items (which should only be the widget we just removed).  To
      // do this we're going to create a temporary array, copy any non-null
      // widgets to it, then copy that entire array back.  Yes, this should
      // be an actual data structure, a linked list probably, but for now
      // this will do.  The Algorithms And Data Structures Police(tm) can
      // shoot me, I'll do it right later!
      OGWidget* pWidgetsTemp[OG_MAX_WIDGETS];
      // Start by making sure the temp array is clear
      for (i = 0; i < OG_MAX_WIDGETS; i++) {
        pWidgetsTemp[i] = NULL;
      }
      // Now copy over the non-null widgets
      int j = 0;
      for (i = 0; i < widgetCount; i++) {
        if (pWidgets[i] != NULL) {
          pWidgetsTemp[j] = pWidgets[i];
          j++;
        }
      }
      // Subtract one for the widget we're removing
      widgetCount--;
      // Clear out the widget array
      for (i = 0; i < OG_MAX_WIDGETS; i++) {
        pWidgets[i] = NULL;
      }
      // Finally, copy the temp array over to the real array
      for (i = 0; i < widgetCount; i++) {
        pWidgets[i] = pWidgetsTemp[i];
      }
    }


    // =======================================================================
    // Returns a pointer to a widget object based on a supplied ID.
    // =======================================================================
    OGWidget* getWidget(TCHAR* in_id) {
      OGWidget* pWidget = NULL;
      for (int i = 0; i < widgetCount; i++) {
        if (_tcscmp(pWidgets[i]->getID(), in_id) == 0) {
          pWidget = pWidgets[i];
        }
      }
      return pWidget;
    }


    // =======================================================================
    // Clears all widgets from the GUI.  All widgets are deleted.
    // =======================================================================
    void clearGUI() {
      for (int i = 0; i < widgetCount; i++) {
        delete pWidgets[i];
      }
      widgetCount = 0;
    }


		// =======================================================================
		// stylusDown
		// Cycle through all widgets and for any that are enabled, see if the
		// point falls within it and if it does, delegate to the widget.  Npte
		// that overlapping widgets will probably cause havoc, so for now it
		// is not "officially" allowed!
		// =======================================================================
		void stylusDown(int in_x, int in_y) {
      if (active) {
			  for (int i = 0; i < widgetCount; i++) {
				  if (pWidgets[i]->isEnabled() && pWidgets[i]->isPointInBounds(in_x, in_y)) {
					  pWidgets[i]->stylusDown(in_x, in_y);
				  }
			  }
      }
		}


		// =======================================================================
		// stylusUp
		// Cycle through all widgets and for any that are enabled, see if the
		// point falls within it and if it does, delegate to the widget.  Npte
		// that overlapping widgets will probably cause havoc, so for now it
		// is not "officially" allowed!
		// =======================================================================
		void stylusUp(int in_x, int in_y) {
      if (active) {
			  for (int i = 0; i < widgetCount; i++) {
				  if (pWidgets[i]->isEnabled() && pWidgets[i]->isPointInBounds(in_x, in_y)) {
					  pWidgets[i]->stylusUp(in_x, in_y);
				  }
			  }
      }
		}


		// =======================================================================
		// stylusMove
		// Cycle through all widgets and for any that are enabled, see if the
		// point falls within it and if it does, delegate to the widget.  Npte
		// that overlapping widgets will probably cause havoc, so for now it
		// is not "officially" allowed!
		// =======================================================================
		void stylusMove(int in_x, int in_y) {
      if (active) {
			  for (int i = 0; i < widgetCount; i++) {
				  if (pWidgets[i]->isEnabled() && pWidgets[i]->isPointInBounds(in_x, in_y)) {
					  pWidgets[i]->stylusMove(in_x, in_y);
				  }
			  }
      }
		}


    // =======================================================================
    // Hides all widgets managed by this manager
    // =======================================================================
    void hideAll() {
      for (int i = 0; i < widgetCount; i++) {
        pWidgets[i]->hide();
      }
    }


    // =======================================================================
    // Shows all widgets managed by this manager
    // =======================================================================
    void showAll() {
      for (int i = 0; i < widgetCount; i++) {
        pWidgets[i]->show();
      }
    }


    // =======================================================================
    // Activates this manager.  Events WILL be processed.
    // =======================================================================
    void activate() {
      active = true;
    }


    // =======================================================================
    // Deactivates this manager.  Events WILL NOT be processed.
    // =======================================================================
    void deactivate() {
      active = false;
    }


    // =======================================================================
    // Returns whether this manager is active (true) or not (false)
    // =======================================================================
    bool isActive() {
      return active;
    }


};


#endif
