

#include "main.h"


using namespace Frog;


CComModule _Module;


// Event handler for button1
class Button1EventHandler : public OGEventHandler {
	public:
    CApp* app;
    Button1EventHandler(CApp* in_app) {
      app = in_app;
    }
    void click() {
			((OGLabel*)app->gui1.getWidget(TEXT("label1")))->setText(TEXT("button1-click"));
    }
};


// Event handler for checkbox1
class Checkbox1EventHandler : public OGEventHandler {
	public:
    CApp* app;
    Checkbox1EventHandler(CApp* in_app) {
      app = in_app;
    }
    void change() {
      ((OGLabel*)app->gui1.getWidget(TEXT("label1")))->setText(TEXT("checkbox1-change"));
    }
};


// Event handler for radio1
class Radio1EventHandler : public OGEventHandler {
	public:
    CApp* app;
    Radio1EventHandler(CApp* in_app) {
      app = in_app;
    }
    void change() {
      ((OGLabel*)app->gui1.getWidget(TEXT("label1")))->setText(TEXT("radio1-change"));
    }
};


// Event handler for spinner1
class Spinner1EventHandler : public OGEventHandler {
	public:
    CApp* app;
    Spinner1EventHandler(CApp* in_app) {
      app = in_app;
    }
    void change() {
      ((OGLabel*)app->gui1.getWidget(TEXT("label1")))->setText(TEXT("spinner1-change"));
    }
};


// Event handler for image1
class Image1EventHandler : public OGEventHandler {
	public:
    CApp* app;
    Image1EventHandler(CApp* in_app) {
      app = in_app;
    }
    void click() {
      ((OGLabel*)app->gui1.getWidget(TEXT("label1")))->setText(TEXT("image1-click"));
    }
};


// Event handler for slider1
class Slider1EventHandler : public OGEventHandler {
	public:
    CApp* app;
    Slider1EventHandler(CApp* in_app) {
      app = in_app;
    }
    void change() {
      ((OGLabel*)app->gui1.getWidget(TEXT("label1")))->setText(TEXT("slider1-change"));
    }
};


// ***************************************************************************
// Constructor
// ***************************************************************************
CApp::CApp() {

  m_config.szWindowName = _TEXT("CApp");
  m_config.orientation  = ORIENTATION_NORMAL;

}


// ***************************************************************************
// Init
// ***************************************************************************
bool CApp::GameInit() {

  // Randomize
  srand(PocketPC::GetTickCount());  

  // Add a button to the first GUI layout manager, set some properties on it, register an event handler for it and show it (not really... have to tell the manager to show all and activate)
  Display* display = GetDisplay();
  OGButton* pButton = (OGButton*)gui1.addWidget(display, OG_WIDGET_BUTTON, TEXT("button1"), 40, 10);
  pButton->setText(TEXT("My First Button!"));
  pButton->setFont(OG_FNT_VGA);
  pButton->setTextOffsetH(6);
  pButton->setTextOffsetV(2);
  Button1EventHandler* ehb1 = new Button1EventHandler(this);
  pButton->registerEventHandler(ehb1);
  pButton->show();

  // Add a checkbox to the first GUI layout manager, set some properties on it, register an event handler for it and show it (not really... have to tell the manager to show all and activate)
  OGCheckbox* pCheckbox = (OGCheckbox*)gui1.addWidget(display, OG_WIDGET_CHECKBOX, TEXT("checkbox1"), 10, 40);
  pCheckbox->setText(TEXT("My First Checkbox!"));
  pCheckbox->setFont(OG_FNT_VGA);
  Checkbox1EventHandler* ehc1 = new Checkbox1EventHandler(this);
  pCheckbox->registerEventHandler(ehc1);
  pCheckbox->show();

  // Add a radio button group to the first GUI layout manager, set some properties on it, register an event handler for it and show it (not really... have to tell the manager to show all and activate)
  OGRadio* pRadio = (OGRadio*)gui1.addWidget(display, OG_WIDGET_RADIO, TEXT("radio1"), 10, 70);
  pRadio->addOption(TEXT("1"));
  pRadio->addOption(TEXT("Opt2"));
  pRadio->addOption(TEXT("Option 3"));
  pRadio->setFont(OG_FNT_VGA);
  Radio1EventHandler* ehr1 = new Radio1EventHandler(this);
  pRadio->registerEventHandler(ehr1);
  pRadio->show();

  // Add a spinner to the first GUI layout manager, set some properties on it, register an event handler for it and show it (not really... have to tell the manager to show all and activate)
  OGSpinner* pSpinner = (OGSpinner*)gui1.addWidget(display, OG_WIDGET_SPINNER, TEXT("spinner1"), 10, 150);
  pSpinner->setMaxValue(50);
  pSpinner->setFont(OG_FNT_VGA);
  pSpinner->setTextOffsetV(2);
  pSpinner->setRepeatRate(3);
  Spinner1EventHandler* ehs1 = new Spinner1EventHandler(this);
  pSpinner->registerEventHandler(ehs1);
  pSpinner->show();

  // Add an image to the first GUI layout manager, set some properties on it, register an event handler for it and show it (not really... have to tell the manager to show all and activate)
  OGImage* pImage = (OGImage*)gui1.addWidget(display, OG_WIDGET_IMAGE, TEXT("image1"), 100, 180);
	image1 = LoadImage(display, IMAGE1, TEXT("IMAGES"));
  pImage->setImage(image1);
  pImage->showBorder();
  Image1EventHandler* ehi1 = new Image1EventHandler(this);
  pImage->registerEventHandler(ehi1);
  pImage->show();

  // Add a slider to the first GUI layout manager, set some properties on it, register an event handler for it and show it (not really... have to tell the manager to show all and activate)
  OGSlider* pSlider = (OGSlider*)gui1.addWidget(display, OG_WIDGET_SLIDER, TEXT("slider1"), 20, 250);
  Slider1EventHandler* ehsl1 = new Slider1EventHandler(this);
  pSlider->registerEventHandler(ehsl1);
  pSlider->show();

  // Add a label to the first GUI layout manager, set some properties on it, register an event handler for it and show it (not really... have to tell the manager to show all and activate)
  OGLabel* pLabel = (OGLabel*)gui1.addWidget(display, OG_WIDGET_LABEL, TEXT("label1"), 10, 290);
  pLabel->setFont(OG_FNT_VGA);
  pLabel->showBorder();
  pLabel->show();

  // Tell our layout manager to show all widgets, and then activate itself
  gui1.activate();

  // For FPS limiting
  ticksPerFrame = 1000 / 30; // 50 FPS
  lastTime      = PocketPC::GetTickCount();

  return true;

}


// ***************************************************************************
// Main Loop
// ***************************************************************************
void CApp::GameLoop() {

  Display* display = GetDisplay();
  display->GetBackBuffer();
  display->Clear(Color(236, 233, 216));
  gui1.doGUI(display);

  while(PocketPC::GetTickCount() - lastTime < ticksPerFrame);
  lastTime = PocketPC::GetTickCount();

  display->Update();

}


// ***************************************************************************
// Game End
// ***************************************************************************
void CApp::GameEnd() {

	delete image1;

}


// ***************************************************************************
// StylsDown
// ***************************************************************************
void CApp::StylusDown(Point p) {

	gui1.stylusDown(p.x, p.y);

}


// ***************************************************************************
// StylusUp
// ***************************************************************************
void CApp::StylusUp(Point p) {

	gui1.stylusUp(p.x, p.y);

}


// ***************************************************************************
// StylusMove
// ***************************************************************************
void CApp::StylusMove(Point p) {

  gui1.stylusMove(p.x, p.y);

}


// ***************************************************************************
// ButtonUp 
// ***************************************************************************
void CApp::ButtonUp(int b) {

  if (b == m_keys.vkA) {
    Shutdown();
  }

}


// ***************************************************************************
// WINMAIN
// ***************************************************************************
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPTSTR, int) {

  _Module.Init(0, hInstance);
  CApp game;
  game.Run();
  return 0;

}
