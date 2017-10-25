//////////////////////////////////////////////////////////////////////////////
//
//  Font extension for PocketFrog
//    Written by Thomas 'gersen' Maniero
//
//////////////////////////////////////////////////////////////////////////////


#include "font.h"

#include <stdio.h>
#include <stdarg.h> 



Font::Font() {

    m_surf = 0;

    m_betlet = 1;
    m_space = 4;
}


Font::~Font() {
}


Surface *Font::getSurface() {

    return m_surf;
}


uint32_t Font::findNextMark(uint32_t *pos, Surface *surf) {

    Surface::LockInfo buf;
    surf->Lock(buf);
    
	// initialize vars
	/*int dy = buf.pitch >> 1;
    int y = 0, w = 0;*/

    int w = 0;
    for (;;) {

        // fine dell'immagine, esco
        if ((*pos) > (uint32_t)(surf->GetWidth()-1))
            break;

        // se il colore è bianco aumento il contatore
        if (buf.pixels[(*pos)] >= /*Color(255, 255, 255)*/0xFFFF) {
            w++;
        }
        else {
            // se non era bianco e il contatore non è a 0 esco
            if (w != 0)
                break;
        }

        (*pos)++;
    }
    
    surf->Unlock();

    return w;
}


uint32_t Font::getWidth(const TCHAR *str) {

  
    uint32_t width = 0, let = 0;

    for (uint32_t i = 0; i < _tcsclen(str); i++) {
        if (str[i] == ' ') {
            width += m_space;
        }
        else {
            width += m_rect[str[i]].GetWidth();
            let++;
        }
    }

    if (let >= 2)
        width += m_betlet * (let-1);
        
    return width;
}


// tabella per le traduzioni delle lettere
const char trs[] = {
    '!', '"', '#', '$', '%', '&', 39, '(', ')', '*', '+', ',', '-', 
    '.', '/', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';',
    '<', '=', '>', '?', '@', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
    'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W',
    'X', 'Y', 'Z', '[', '\\', ']', '^', '_', 39, 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 
    'u', 'v', 'w', 'x', 'y', 'z', '{', '|', '}', '~', '_', 0
	// MSR: added missing characters, and terminated table with 0
};



bool Font::load(DisplayDevice* display, DWORD dwResID) {

    uint32_t h, w, i, pos;

    for (i = 0; i <= 255; i++)
        m_rect[i].Set(0, 0, 0, 0);

    // carico superficie contenente il font
    m_surf = LoadImage(display, dwResID);
    if (m_surf == 0)
        return false;

    h = m_surf->GetHeight();

    // trovo primo mark, i pixel per lo spazio
    pos = 0;
    w = findNextMark(&pos, m_surf);
    if (w != 0)
        m_space = w;
    else
        return false;

    
    i = 0;
    while (trs[i] != 0) {	// MSR: check for end of table
        // se non trovo un mark allora ho controllato tutta l'immagine, esco
        w = findNextMark(&pos, m_surf);
        if (w == 0)
            break;

        // setto rettangolo. se ho settato 255 rect allora ho finito
        m_rect[trs[i]].Set(pos-w, 1, pos, h);
        i++;
        if (i > 255)
            break;
    }


    return true;
}


void Font::draw(DisplayDevice* display, int32_t x, int32_t y, const TCHAR *str) {


    for (unsigned int i = 0; i < _tcsclen(str); i++) {
        if (str[i] == ' ') {
            x += m_space;
        }
        else {
            display->Blit(x, y, m_surf, &m_rect[str[i]]);
            x += m_rect[str[i]].GetWidth() + m_betlet;
        }
    }

}

void Font::drawf(DisplayDevice* display, int32_t x, int32_t y, const TCHAR *fmt, ...) {

    TCHAR str[1024];
    va_list ap;

    if (fmt == NULL)
        return;

    va_start(ap, fmt);             // parses the string for variables
        _vstprintf(str, fmt, ap);    // and converts symbols to actual numbers
    va_end(ap);                    // results are stored in str

    // draw str
    draw(display, x, y, str);
}

void Font::draw(DisplayDevice* display, int32_t x, int32_t y, uint32_t flags, const TCHAR *str) {

    switch (flags) {
      case FONT_CENTER:
        x -= getWidth(str)/2;
      break;

      case FONT_RIGHT:
        x -= getWidth(str);
      break;
    }

    draw(display, x, y, str);
}

void Font::drawf(DisplayDevice* display, int32_t x, int32_t y, uint32_t flags, const TCHAR *fmt, ...) {

    TCHAR str[1024];
    va_list ap;

    if (fmt == NULL)
        return;

    va_start(ap, fmt);             // parses the string for variables
        _vstprintf(str, fmt, ap);    // and converts symbols to actual numbers
    va_end(ap);                    // results are stored in str

    // draw str
    draw(display, x, y, flags, str);
}



