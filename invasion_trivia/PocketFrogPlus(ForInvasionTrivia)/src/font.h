//////////////////////////////////////////////////////////////////////////////
//
//  Font extension for PocketFrog
//    Written by Thomas 'gersen' Maniero
//
//////////////////////////////////////////////////////////////////////////////


#ifndef FONT_H
#define FONT_H


#include "display.h"
#include "surface.h"
#include "rasterizer.h"
#include "image.h"


#include <windows.h>
#include <tchar.h>


#define FONT_LEFT 1
#define FONT_RIGHT 2
#define FONT_CENTER 3


using namespace Frog;



class Font {

private:
    Surface *m_surf;
    Rect m_rect[256];
    uint32_t m_space, m_betlet;

private:
    uint32_t findNextMark(uint32_t *pos, Surface *surf);

public:
    Font();
    ~Font();

    
    Surface *getSurface();

    uint32_t getWidth(const TCHAR *str);

    bool load(DisplayDevice* display, DWORD dwResID);

    void draw(DisplayDevice* display, int32_t x, int32_t y, const TCHAR *str);

    void drawf(DisplayDevice* display, int32_t x, int32_t y, const TCHAR *fmt, ...);

    void draw(DisplayDevice* display, int32_t x, int32_t y, uint32_t flags, const TCHAR *str);

    void drawf(DisplayDevice* display, int32_t x, int32_t y, uint32_t flags, const TCHAR *fmt, ...);
};



#endif
