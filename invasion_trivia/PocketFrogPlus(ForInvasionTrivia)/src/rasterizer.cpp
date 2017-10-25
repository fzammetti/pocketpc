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

#include "rasterizer.h"
#include "display.h"
#include "surface.h"
#include "internal/raster2d.h"
#include "internal/graphicbuffer.h"
#include <algorithm>
#include <cassert>

#if defined(FROG_PC)
#include <cmath>
#else
inline float cosf( float angle )  { return (float)cos( angle ); }
inline float sinf( float angle )  { return (float)sin( angle ); }
inline float sqrtf( float angle ) { return (float)sqrt( angle ); }
#endif

namespace Frog {


    
//////////////////////////////////////////////////////////////////////////////
//
// Globals
//
//////////////////////////////////////////////////////////////////////////////

namespace Internal
{
    Raster2D g_defaultRaster;
}



//////////////////////////////////////////////////////////////////////////////
//
// Helpers
//
//////////////////////////////////////////////////////////////////////////////

namespace
{
    inline void TransformHelper( Point& p, Orientation orientation, const Surface* surface )
    {
       switch (orientation)
       {
       case ORIENTATION_SOUTH:
          p.x = surface->GetWidth() - p.x - 1;
          p.y = surface->GetHeight() - p.y - 1;
          break;

       case ORIENTATION_WEST:
          std::swap( p.x, p.y );
          p.x = surface->GetHeight() - p.x - 1;
          break;

       case ORIENTATION_EAST:
          std::swap( p.x, p.y );
          p.y = surface->GetWidth() - p.y - 1;
          break;
       }
    }



    inline void TransformHelper( Rect& r, Orientation orientation, const Surface* surface )
    {
        switch (orientation)
        {
        case ORIENTATION_SOUTH:
            {
                Rect t = r;
                r.left   = surface->GetWidth()  - t.right;
                r.right  = surface->GetWidth()  - t.left;
                r.top    = surface->GetHeight() - t.bottom;
                r.bottom = surface->GetHeight() - t.top;
            }
            break;
            
        case ORIENTATION_WEST:
            {
                Rect t = r;
                r.left   = surface->GetHeight() - t.bottom;
                r.right  = surface->GetHeight() - t.top;
                r.top    = t.left;
                r.bottom = t.right;
            }
            break;
            
        case ORIENTATION_EAST:
            {
                Rect t = r;
                r.left   = t.top;
                r.right  = t.bottom;
                r.top    = surface->GetWidth() - t.right;
                r.bottom = surface->GetWidth() - t.left;
            }
            break;
        }
    }
}



//////////////////////////////////////////////////////////////////////////////
//
// Rasterizer
//
//////////////////////////////////////////////////////////////////////////////

Rasterizer::Rasterizer()
:   m_surface( 0 ),
    m_orientation( ORIENTATION_UNKNOWN ),
    m_raster( &Internal::g_defaultRaster )
{
}



void Rasterizer::Init( Surface* target, Orientation orientation )
{
    m_orientation = orientation;

    SetRenderTarget( target );
}



int Rasterizer::GetOutCode( const Point& p ) const
{
    int code;
    
    if (p.x < m_clipper.left) code = 1;
    else if (p.x >= m_clipper.right) code = 2;
    else code = 0;
    
    if (p.y < m_clipper.top) code |= 4;
    else if (p.y >= m_clipper.bottom) code |= 8;
    
    return code;
}



void Rasterizer::SetBlending( uint8_t alpha )
{
    // The last two bits of alpha are not significant
    if ( (alpha | 0x03) == 0xFF )
    {
        // Completely opaque
        SetDefaultShader();
    }
    else
    {
        if (!m_alphaRaster.get())
            m_alphaRaster.reset( new Internal::AlphaRaster2D( alpha ) );
        else
            m_alphaRaster->SetAlpha( alpha );

        m_raster = m_alphaRaster.get();
    }
}


void Rasterizer::SetClipping( const Rect& rect )
{
    m_clipper.Set( 0, 0, m_surface->GetWidth(), m_surface->GetHeight() );
    m_clipper.Intersect( rect );
}



void Rasterizer::SetDefaultShader()
{
    m_raster = &Internal::g_defaultRaster;
}



void Rasterizer::SetPixelShader( PixelShader* shader )
{
    if (!m_genericRaster.get())
        m_genericRaster.reset( new Internal::GenericRaster2D( shader ) );
    else
        m_genericRaster->SetPixelShader( shader );

    m_raster = m_genericRaster.get();
}



Surface* Rasterizer::SetRenderTarget( Surface* target )
{
    Surface* oldTarget = m_surface;
    
    m_surface = target;
    m_clipper.Set( 0, 0, m_surface->GetWidth(), m_surface->GetHeight() );
    
    return oldTarget;
}



void Rasterizer::Transform( Point& p ) const
{
    TransformHelper( p, m_orientation, m_surface );
}



void Rasterizer::Transform( Rect& r ) const
{
    TransformHelper( r, m_orientation, m_surface );
}



//////////////////////////////////////////////////////////////////////////////
// Graphic primitives
//////////////////////////////////////////////////////////////////////////////

void Rasterizer::Blit( int destX, int destY, const Surface* source, const Rect* srcRect_ )
{
    assert( source != 0 );

    // Prepare blit source and destination rectangles
    Rect srcRect;
    if (srcRect_)
        srcRect = *srcRect_;
    else
        srcRect.Set( 0, 0, source->GetWidth(), source->GetHeight() );

    Rect destRect( destX, destY, destX + srcRect.GetWidth(), destY + srcRect.GetHeight() );

    // Clipping
    if (!m_clipper.IsEmpty())
    {
        destRect.Intersect( m_clipper );
        
        // Trivial reject
        if (destRect.IsEmpty())
            return;
        
        // Adjust left and top sides of source rectangle
        int xoffset = destRect.left - destX;
        int yoffset = destRect.top - destY;
        
        srcRect.left += xoffset;
        srcRect.top += yoffset;
        
        // Adjust width and height of source rectangle
        srcRect.right = srcRect.left + destRect.GetWidth();
        srcRect.bottom = srcRect.top + destRect.GetHeight();
    }


    // Coordinates transform
    TransformHelper( srcRect, m_orientation, source );
    Transform( destRect );

    
    // Drawing
    int colorMask = source->GetColorMask();

    if (colorMask < 0)
        m_raster->Blit( *m_surface->m_buffer, destRect, *source->m_buffer, srcRect );
    else
        m_raster->BlitMask( *m_surface->m_buffer, destRect, *source->m_buffer, srcRect, colorMask );
}



//todo: add source rectangle (should be easy)
void Rasterizer::BlitRotated( int destX, int destY, float angle, const Surface* source )
{
    assert( source != 0 );

    // Calculate destination rectangle
    //todo: find better fit
    float tw = 0.5f * source->GetWidth();
    float th = 0.5f * source->GetHeight();
    int diag = sqrtf(tw*tw+th*th) + 1.0f;
    Rect destRect( destX-diag, destY-diag, destX+diag, destY+diag );

    // Clipping
    if (!m_clipper.IsEmpty())
    {
        destRect.Intersect( m_clipper );
        if (destRect.IsEmpty())
            return;
    }


    Point dest( destX, destY );
    Transform( dest );


    unsigned c = cosf( -angle ) * 1024.0f;
    unsigned s = sinf( -angle ) * 1024.0f;
    unsigned w = source->GetWidth() << 9;
    unsigned h = source->GetHeight() << 9;

    if (m_orientation == ORIENTATION_EAST || m_orientation == ORIENTATION_WEST)
    {
        std::swap( w, h );
    }

    // Use fixed point (22.10)
    unsigned T[3][2];

    T[0][0] = c;
    T[0][1] = -s;
    T[1][0] = s;
    T[1][1] = c;
    T[2][0] = -c * dest.x - s * dest.y + w;
    T[2][1] =  s * dest.x - c * dest.y + h;

    // Optimization: compensate for fixed point arithmetic in rasterization loops
    T[2][0] <<= 6;
    T[2][1] <<= 6;


    // Transform destination rectangl`e
    Transform( destRect );

    // Drawing
    int colorMask = source->GetColorMask();

    if (colorMask < 0)
        m_raster->BlitTransform( *m_surface->m_buffer, destRect, T, *source->m_buffer );
    else
        m_raster->BlitTransformMask( *m_surface->m_buffer, destRect, T, *source->m_buffer, colorMask );
}



void Rasterizer::BlitStretch( const Rect& dest, const Surface* source, const Rect* srcRect_ )
{
    assert( source != 0 );

    // Prepare blit source and destination rectangles
    Rect srcRect;
    if (srcRect_)
        srcRect = *srcRect_;
    else
        srcRect.Set( 0, 0, source->GetWidth(), source->GetHeight() );

    Rect destRect( dest );


    // Coordinates transform
    TransformHelper( srcRect, m_orientation, source );
    Transform( destRect );

    // We will use a 3x2 matrix to map the "texture" to the destination

    // Compute ratios (22.10)
    unsigned rx = unsigned(srcRect.GetWidth() << 10) / unsigned(destRect.GetWidth());
    unsigned ry = unsigned(srcRect.GetHeight() << 10) / unsigned(destRect.GetHeight());

    // Use fixed point (22.10)
    unsigned T[3][2];

    T[0][0] = rx;
    T[0][1] = 0;
    T[1][0] = 0;
    T[1][1] = ry;
    T[2][0] = -destRect.left * rx + (srcRect.left << 10);
    T[2][1] = -destRect.top * ry + (srcRect.top << 10);

    // Optimization: compensate for fixed point arithmetic in rasterization loops
    T[2][0] <<= 6;
    T[2][1] <<= 6;


    // Clipping
    if (!m_clipper.IsEmpty())
    {
        Rect clipper( m_clipper );
        Transform( clipper );
        destRect.Intersect( clipper );
        
        // Trivial reject
        if (destRect.IsEmpty())
            return;
    }

    // Drawing
    int colorMask = source->GetColorMask();

    if (colorMask < 0)
        m_raster->BlitTransform( *m_surface->m_buffer, destRect, T, *source->m_buffer );
    else
        m_raster->BlitTransformMask( *m_surface->m_buffer, destRect, T, *source->m_buffer, colorMask );
}



void Rasterizer::Clear( Pixel color )
{
    m_raster->Clear( *m_surface->m_buffer, color );
}



void Rasterizer::DrawCircle( int x, int y, int radius, Pixel color )
{
    if (!m_clipper.IsEmpty())
    {
        // Trivial rejection
        if (x + radius < m_clipper.left ||
            y + radius < m_clipper.top ||
            x - radius >= m_clipper.right ||
            y - radius >= m_clipper.bottom)
        {
            return;
        }

        // Is clipping really needed?
        if (x - radius < m_clipper.left || x + radius >= m_clipper.right ||
            y - radius < m_clipper.top || y + radius >= m_clipper.bottom)
        {
            // Coordinates transform
            Point p( x, y );
            Rect clipper( m_clipper );
        
            Transform( p );
            Transform( clipper );
        
            // Drawing
            m_raster->Circle( *m_surface->m_buffer, p, radius, color, clipper );
            return;
        }
    }

    
    // Coordinates transform
    Point p( x, y );
    Transform( p );
    
    // Drawing
    m_raster->Circle( *m_surface->m_buffer, p, radius, color );
}



void Rasterizer::DrawHLine( int x, int y, int length, Pixel color )
{
    assert( length >= 0 );
    
    if (!m_clipper.IsEmpty())
    {
        // Trivial rejection
        if (y < m_clipper.top || y >= m_clipper.bottom)
            return;
        
        // Clipping
        if (x < m_clipper.left)
        {
            length += x - m_clipper.left;
            x = m_clipper.left;
        }
        
        if (x + length > m_clipper.right)
            length = m_clipper.right - x;
        
        if (length <= 0) return;
    }
    
    // Coordinates transform
    Point p1( x, y );
    Point p2( x + length - 1, y );
    
    Transform( p1 );
    Transform( p2 );
    
    // Drawing
    switch (m_orientation)
    {
    case ORIENTATION_NORTH:
    case ORIENTATION_SOUTH:
        if (p1.x < p2.x)
            m_raster->HLine( *m_surface->m_buffer, p1, length, color );
        else
            m_raster->HLine( *m_surface->m_buffer, p2, length, color );
        break;
        
    case ORIENTATION_WEST:
    case ORIENTATION_EAST:
        if (p1.y < p2.y)
            m_raster->VLine( *m_surface->m_buffer, p1, length, color );
        else
            m_raster->VLine( *m_surface->m_buffer, p2, length, color );
        break;
    }
}



void Rasterizer::DrawLine( int x1, int y1, int x2, int y2, Pixel color )
{
    // Optimize using HLine / VLine when possible
    if (x1 == x2)
    {
        if (y2 < y1) std::swap( y1, y2 );
        DrawVLine( x1, y1, y2 - y1, color );
    }
    else if (y1 == y2)
    {
        if (x2 < x1) std::swap( x1, x2 );
        DrawHLine( x1, y1, x2 - x1, color );
    }
    else
    {   
        Point p1( x1, y1 );
        Point p2( x2, y2 );  
        
        if (!m_clipper.IsEmpty())
        {
            // Clip using Cohen-Sutherland
            int xmin = m_clipper.left;
            int ymin = m_clipper.top;
            int xmax = m_clipper.right - 1;
            int ymax = m_clipper.bottom - 1;
            
            int code1 = GetOutCode( p1 );
            int code2 = GetOutCode( p2 );
            
            while (code1 || code2)
            {
                // Trivial rejection
                if (code1 & code2)
                    return;
                
                int code = (code1) ? code1 : code2;
                
                int x, y;
                
                if (code & 1)
                {
                    // Left edge
                    y = p1.y + (p2.y - p1.y) * (xmin - p1.x) / (p2.x - p1.x);
                    x = xmin;
                }
                else if (code & 2)
                {
                    // Right edge
                    y = p1.y + (p2.y - p1.y) * (xmax - p1.x) / (p2.x - p1.x);
                    x = xmax;
                }
                else if (code & 4)
                {
                    // Top edge
                    x = p1.x + (p2.x - p1.x) * (ymax - p1.y) / (p2.y - p1.y);
                    y = ymax;
                }
                else if (code & 8)
                {
                    // Bottom edge
                    x = p1.x + (p2.x - p1.x) * (ymin - p1.y) / (p2.y - p1.y);
                    y = ymax;
                }
                
                if (code == code1)
                {
                    p1.Set( x, y );
                    code1 = GetOutCode( p1 );
                }
                else
                {
                    p2.Set( x, y );
                    code2 = GetOutCode( p2 );
                }
            }
        }
        
        // Coordinates transform
        Transform( p1 );
        Transform( p2 );
        
        // Drawing
        m_raster->Line( *m_surface->m_buffer, p1, p2, color );
    }
}



void Rasterizer::DrawRect( int x1, int y1, int x2, int y2, Pixel color )
{
    DrawHLine( x1, y1, x2-x1, color );
    DrawVLine( x1, y1, y2-y1, color );
    DrawVLine( x2, y1, y2-y1, color );
    DrawHLine( x1, y2, x2-x1, color );
}



void Rasterizer::DrawVLine( int x, int y, int length, Pixel color )
{
    assert( length >= 0 );
    
    if (!m_clipper.IsEmpty())
    {
        // Trivial rejection
        if (x < m_clipper.left || x >= m_clipper.right)
            return;
        
        // Clipping
        if (y < m_clipper.top)
        {
            length += y - m_clipper.top;
            y = m_clipper.top;
        }
        
        if (y + length > m_clipper.bottom)
            length = m_clipper.bottom - y;
        
        if (length <= 0) return;
    }
    
    // Coordinates transform
    Point p1( x, y );
    Point p2( x, y + length - 1 );
    
    Transform( p1 );
    Transform( p2 );
    
    // Drawing
    switch (m_orientation)
    {
    case ORIENTATION_WEST:
    case ORIENTATION_EAST:
        if (p1.x < p2.x)
            m_raster->HLine( *m_surface->m_buffer, p1, length, color );
        else
            m_raster->HLine( *m_surface->m_buffer, p2, length, color );
        break;
        
    case ORIENTATION_NORTH:
    case ORIENTATION_SOUTH:
        if (p1.y < p2.y)
            m_raster->VLine( *m_surface->m_buffer, p1, length, color );
        else
            m_raster->VLine( *m_surface->m_buffer, p2, length, color );
        break;
    }
}



void Rasterizer::FillRect( const Rect& rect, Pixel color )
{
    Rect r( rect );
    
    // Clipping
    if (!m_clipper.IsEmpty())
    {
        r.Intersect( m_clipper );
    }
    
    // Coordinates transform
    Transform( r );
    
    // Drawing
    m_raster->FillRect( *m_surface->m_buffer, r, color );
}



Pixel Rasterizer::GetPixel( int x, int y )
{
    assert( x >= 0 && x < m_surface->GetWidth() );
    assert( y >= 0 && y < m_surface->GetHeight() );

    // Coordinates transform
    Point p( x, y );
    Transform( p );

    // Return the pixel
    return *m_surface->m_buffer->GetPixels( p.x, p.y );
}



void Rasterizer::SetPixel( int x, int y, Pixel color )
{
    // Trivial rejection
    if (x < 0 || y < 0 || x >= m_surface->GetWidth() || y >= m_surface->GetHeight())
        return;
    
    // Coordinates transform
    Point p( x, y );
    Transform( p );
    
    // Drawing
    m_raster->SetPixel( *m_surface->m_buffer, p, color );
}



} // end of namespace Frog
