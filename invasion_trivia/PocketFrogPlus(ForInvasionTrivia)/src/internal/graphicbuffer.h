//////////////////////////////////////////////////////////////////////////////
//
// PocketFrog - The Game Library for Pocket PC Devices
// Copyright 2002  Thierry Tremblay
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee,
// provided that the above copyright notice appear in all copies and
// that both that copyright notice and this permission notice appear
// in supporting documentation.  Thierry Tremblay makes no representations
// about the suitability of this software for any purpose.
// It is provided "as is" without express or implied warranty.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef POCKETFROG_INTERNAL_GRAPHICBUFFER_H
#define POCKETFROG_INTERNAL_GRAPHICBUFFER_H

#include "../defs.h"

namespace Frog {
namespace Internal {



//////////////////////////////////////////////////////////////////////////////
//
// GraphicBuffer
//
//////////////////////////////////////////////////////////////////////////////

class GraphicBuffer : noncopyable
{
public:

    // Destructor
    virtual ~GraphicBuffer() = 0 {}

    // Info
    int            GetWidth() const                 { return m_width; }
    int            GetHeight() const                { return m_height; }
    int            GetPitch() const                 { return m_pitch; }

    // Direct Access
    Pixel*         GetPixels()                      { return m_pixels; }
    const Pixel*   GetPixels() const                { return m_pixels; }
    Pixel*         GetPixels( int x, int y )        { return (Pixel*)((char*)(m_pixels + x) + y * m_pitch); }
    const Pixel*   GetPixels( int x, int y ) const  { return (Pixel*)((char*)(m_pixels + x) + y * m_pitch); }


protected:
    
    // Construct the graphic buffer
    GraphicBuffer( Pixel* pPixels, int width, int height, int pitch )
        : m_pixels(pPixels), m_width(width), m_height(height), m_pitch(pitch) {}
    
    // Data
    Pixel*      m_pixels;           // Start of pixel memory
    int         m_width, m_height;  // Surface dimensions
    int         m_pitch;            // Pitch of the surface
};



//////////////////////////////////////////////////////////////////////////////
//
// MemoryGraphicBuffer
//
//////////////////////////////////////////////////////////////////////////////

class MemoryGraphicBuffer : public GraphicBuffer
{
public:

    MemoryGraphicBuffer( int width, int height );
    ~MemoryGraphicBuffer();
};



//////////////////////////////////////////////////////////////////////////////
//
// GAPIBuffer
//
//////////////////////////////////////////////////////////////////////////////

class GAPIBuffer : public GraphicBuffer
{
public:

    GAPIBuffer( int width, int height, int pitch );

    // Set the video pointer
    void SetVideo( Pixel* pixels ) { m_pixels = pixels; }
};



//////////////////////////////////////////////////////////////////////////////
//
// GDIBuffer
//
//////////////////////////////////////////////////////////////////////////////

class GDIBuffer : public GraphicBuffer
{
public:

    // Create a GDI buffer with the specified dimensions
    GDIBuffer( int width, int height );

    // Destructor
    ~GDIBuffer();

    // GDI support
    HDC  GetDC();
    void ReleaseDC( HDC hdc );


private:

    // Data
    HBITMAP  m_hBitmap;
};




//////////////////////////////////////////////////////////////////////////////
//
// Blits with rotation
//
//////////////////////////////////////////////////////////////////////////////

void Blit( const GraphicBuffer& source, GraphicBuffer& destination );
void BlitRotateCCW( const GraphicBuffer& source, GraphicBuffer& destination );
void BlitRotateCW( const GraphicBuffer& source, GraphicBuffer& destination );
void BlitUpsideDown( const GraphicBuffer& source, GraphicBuffer& destination );




} // end of namespace Internal
} // end of namespace Frog



#endif
