

#include <PocketFrog/PocketFrog.h>
#include "../resource.h"
#include "OmnyGUI.h"


#pragma comment(lib, "hss.lib")


using namespace Frog;


void MBT(TCHAR* txt) { MessageBox(NULL, txt, TEXT("MBT"), MB_OK); }


class CApp : public Game {

  public:

    unsigned char* fntVGA;
		Surface*       image1;
    OGManager      gui1;
    OGManager      gui2;
    uint32_t       lastTime;
    uint32_t       ticksPerFrame;

    CApp();

    virtual bool GameInit   ();
    virtual void GameLoop   ();
		virtual void GameEnd    ();
    virtual void StylusUp   (Point p);
		virtual void StylusDown (Point p);
    virtual void StylusMove (Point p);
    virtual void ButtonUp   (int b);

};
