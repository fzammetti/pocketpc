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

#ifndef POCKETFROG_RASTERIZER_H
#define POCKETFROG_RASTERIZER_H

#include "defs.h"



namespace Frog {

class Surface;

namespace Internal
{
    struct I2DRasterizer;
    class AlphaRaster2D;
    class GenericRaster2D;
}



//////////////////////////////////////////////////////////////////////////////
//
// PixelShader - Use to create your own raster operations
//
///////////////////////////////////////////////////////////////////////////////

struct PixelShader
{
    // Override this method to do your custom raster operations.
    // src is the source color color specified to the primitive)
    // dest is the content of the graphic buffer (dest color)
    virtual Pixel operator()( Pixel src, Pixel dest ) const = 0;
};



//////////////////////////////////////////////////////////////////////////////
//
// Rasterizer
//
//////////////////////////////////////////////////////////////////////////////

class Rasterizer : noncopyable
{
public:
    
    // Primitives
    void Blit( int destX, int destY, const Surface* source, const Rect* srcRect = 0 );
    void Clear( Pixel color );
    void DrawCircle( int x, int y, int radius, Pixel color );
    void DrawHLine( int x, int y, int length, Pixel color );
    void DrawLine( int x1, int y1, int x2, int y2, Pixel color );
    void DrawRect( int x1, int y1, int x2, int y2, Pixel color );
    void DrawVLine( int x, int y, int length, Pixel color );
    void FillRect( const Rect& rect, Pixel color );
    void SetPixel( int x, int y, Pixel color );

    // Blit with rotation
    void BlitRotated( int destX, int destY, float angle, const Surface* source );

    // Blit with stretching
    void BlitStretch( const Rect& dest, const Surface* source, const Rect* srcRect = 0 );

    // Return the pixel at the specified location
    Pixel GetPixel( int x, int y );

    // Return the current clipping rectangle
    const Rect& GetClipping() const { return m_clipper; }

    // Set the blending alpha value (0 - transparent, 255 - opaque)
    void SetBlending( uint8_t alpha );

    // Set the clipping region
    void SetClipping( const Rect& rect );

    // Restore the default shader
    void SetDefaultShader();

    // Set a custom raster operation
    void SetPixelShader( PixelShader* shader );

    // Change the rendering target, returning the old target
    Surface* SetRenderTarget( Surface* target );

   

    
private:

    // Compute the outcode for a point (used for Cohen-Sutherland line clipping)
    int GetOutCode( const Point& p ) const;

    // Transform points and rectangles based on orientation
    void Transform( Point& p ) const;
    void Transform( Rect& r ) const;


    // Data
    Orientation                             m_orientation;   // Orientation of target
    Surface*                                m_surface;       // Target
    Rect                                    m_clipper;       // Clipping rectangle
    Internal::I2DRasterizer*                m_raster;        // Current rasterizer
    scoped_ptr<Internal::AlphaRaster2D>     m_alphaRaster;   // Alpha blending rasterizer
    scoped_ptr<Internal::GenericRaster2D>   m_genericRaster; // Generic blending rasterizer


    // You can't create a Rasterizer directly, use DisplayDevice::CreateRasterizer()
    friend class DisplayDevice;
    void Init( Surface* target, Orientation orientation );
    Rasterizer();
};
    


} // end of namespace Frog



#endif
