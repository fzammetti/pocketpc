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

//////////////////////////////////////////////////////////////////////////////
//
// Font and sound added by Thomas 'gersen' Maniero
//
// homepage:
//    http://www.digilander.libero.it/funnybits
// e-mail:
//    gersen.new@libero.it
//
//////////////////////////////////////////////////////////////////////////////

#include <math.h>

#include "blit.h"
#include "resource.h"

using namespace Frog;



//////////////////////////////////////////////////////////////////////////////
//
// _Module : This is needed to use ATL Windows
//
//////////////////////////////////////////////////////////////////////////////

CComModule _Module;



//////////////////////////////////////////////////////////////////////////////
//
// BlitSample
//
//////////////////////////////////////////////////////////////////////////////

BlitSample::BlitSample()
{
    m_config.szWindowName     = _T("Blit Sample");
    m_config.orientation      = ORIENTATION_WEST;
    m_config.splashScreenTime = 500;

    // use FROG_PC_X2 to double the game window in pc mode
    m_config.displayflags     = FROG_PC_NORMAL;
	//m_config.displayflags     = FROG_PC_X2;

    // you can use 11025 or 22050 standard frequency
	// set 0 if you want no sound
	m_config.soundfrequency = 22050;
    //m_config.soundfrequency = 0; // no sound

    // stereo or mono output
    m_config.soundstereo = true;
}



bool BlitSample::GameInit()
{
    uint32_t i;

    // Initialize random seed
    srand( PocketPC::GetTickCount() );
    
    DisplayDevice* display = GetDisplay();
    
    m_images[0] = LoadImage( display, IDB_BITMAP1 );
    m_images[1] = LoadImage( display, IDB_BITMAP2 );
    m_images[2] = LoadImage( display, IDB_BITMAP3 );
    m_images[3] = LoadImage( display, IDB_BITMAP4 );
    m_background = LoadImage( display, IDR_IMAGE1 );

    // load sfx wave
    m_sndfx[0].load(_Module.GetModuleInstance(), IDR_TRUMPET);
    m_sndfx[1].load(_Module.GetModuleInstance(), IDR_CHICKEN);
    m_sndfx[2].load(_Module.GetModuleInstance(), IDR_DRUM);
    m_sndfx[3].load(_Module.GetModuleInstance(), IDR_PHONE);

    // set loop to false
    for (i = 0; i < 4; i++)
        m_sndfx[i].setLoop(false);

    // load module
    m_mod.load(_Module.GetModuleInstance(), IDR_ARS);
    // set module volume
    m_mod.setVolume(42);
    // set looping mode
    m_mod.setLoop(true);

    // load font image
    m_font.load(display, IDR_FONT);
    // set font surface color mask
    m_font.getSurface()->SetColorMask(Color(255, 0, 255));

    
    for (i = 0; i < 4; ++i)
    {
        // Set color mask
        m_images[i]->SetColorMask( Color( 255, 0, 255) );
        
        // Set initial position
        m_position[i].Set( 0, 0, m_images[i]->GetWidth(), m_images[i]->GetHeight() );
        
        int x = rand() % (display->GetWidth() - m_images[i]->GetWidth());
        int y = rand() % (display->GetHeight() - m_images[i]->GetHeight());
        
        m_position[i].Move( x, y );
    }
    
    
    m_numbers = LoadImage( display, IDB_NUMBERS );
    m_FPSCounter = 0;

    m_dragImage = -1;   // Not dragging any image


    Sound *snd = GetSound();
    // play mod
    snd->playMod(&m_mod);
   
    return true;
}



void BlitSample::GameEnd()
{
    for (int i = 0; i < 4; ++i)
    {
        delete m_images[i];
    }
    
    delete m_background;
    delete m_numbers;
}



void BlitSample::GameLoop()
{
    DisplayDevice* display = GetDisplay();

    display->Blit( 0, 0, m_background );
    
#if defined(FROG_HPC)
    display->Blit( 320, 0, m_background );
#endif

    m_font.draw(display, display->GetWidth()/2, 202, FONT_CENTER, TEXT("Sound Engine ver. 0.94 + Simple Font"));
    m_font.draw(display, display->GetWidth()/2, 215, FONT_CENTER, TEXT("For PocketFrog ver. 0.6.0"));
    m_font.draw(display, display->GetWidth()/2, 228, FONT_CENTER, TEXT("by Thomas 'gersen' Maniero"));

    Sound *sound = GetSound();
    m_font.drawf(display, 1, 1, FONT_LEFT, TEXT("Playing Mod Channel %u/%u"), sound->playingChannelMod(), sound->numChannelMod());
    m_font.drawf(display, 1, 14, FONT_LEFT, TEXT("Playing SFX Channel %u/%u"), sound->playingChannelSFX(), sound->numChannelSFX());
    m_font.drawf(display, 1, 27, FONT_LEFT, TEXT("Master Volume %u"), sound->getVolume());

    for (int i = 0; i < 4; ++i)
    {
        Rect& pos = m_position[i];
        
        // Display image
        display->Blit( pos.left, pos.top, m_images[i] );
        
        if (i != m_dragImage)
        {
            // Move image (horizontal)
            switch (rand() % 3)
            {
            case 0: break;  // Don't move
            case 1: if (pos.left > 0) pos.Translate( -1, 0 ); break;
            case 2: if (pos.right < display->GetWidth()) pos.Translate( 1, 0 ); break;
            }
            
            // Move image (vertical)
            switch (rand() % 3)
            {
            case 0: break;  // Don't move
            case 1: if (pos.top > 0) pos.Translate( 0, -1 ); break;
            case 2: if (pos.bottom < display->GetHeight()) pos.Translate( 0, 1 ); break;
            }
        }
    }

    
    // Update FPS
    m_FPSTicks[ m_FPSCounter & 15 ] = PocketPC::GetTickCount();
    if (m_FPSCounter > 15)
    {
        uint32_t totalTime = m_FPSTicks[ m_FPSCounter & 15 ] - m_FPSTicks[ (m_FPSCounter+1) & 15 ];
        if (totalTime == 0) totalTime = 1;
        uint32_t fps  = 16000 / totalTime;

        m_font.drawf(display, display->GetWidth()-1, 1, FONT_RIGHT, TEXT("fps: %u"), fps);
    }
    ++m_FPSCounter;
   

    
    // Update screen
    display->Update();
}


void BlitSample::ButtonDown( int button )
{

    const InputDevice::KeyList &kl = GetInput()->GetKeyList();


    Sound *sound = GetSound();

    if ((button == kl.vkUp) || (button == kl.vkRight))  {
        if (sound->getVolume() <= 64-8)
            sound->setVolume(sound->getVolume() + 8);
        else
            sound->setVolume(64);
    }

    if ((button == kl.vkDown) || (button == kl.vkLeft)) {
        if (sound->getVolume() >= 8)
            sound->setVolume(sound->getVolume() - 8);
        else
            sound->setVolume(0);
    }

    if ((button == kl.vkA) ||(button == kl.vkB) || (button == kl.vkC) ||
       (button == kl.vkStart)) 
       Shutdown();
}



void BlitSample::StylusDown( Point stylus )
{
    // Check if the point is on one of the images
    for (int i = 3; i >= 0; --i)
    {
        if (m_position[i].Contains( stylus ))
        {
            m_dragImage  = i;
            m_dragOffset = stylus - Point( m_position[i].left, m_position[i].top );

            Sound *snd = GetSound();
            // play sfx
            snd->playSFX(&m_sndfx[i]);

            break;
        }
    }
}



void BlitSample::StylusUp( Point stylus )
{
    m_dragImage = -1;
}



void BlitSample::StylusMove( Point stylus )
{
    if (m_dragImage == -1)
        return;
    
    Point newPosition ( stylus - m_dragOffset );
    
    const Surface* image = m_images[m_dragImage];
    Rect limit( 0, 0, GetDisplay()->GetWidth() - image->GetWidth(), GetDisplay()->GetHeight() - image->GetHeight() );
    
    if (newPosition.x < limit.left) newPosition.x = limit.left;
    else if (newPosition.x > limit.right) newPosition.x = limit.right;
    
    if (newPosition.y < limit.top) newPosition.y = limit.top;
    else if (newPosition.y > limit.bottom) newPosition.y = limit.bottom;
    
    m_dragOffset = stylus - newPosition;
    
    m_position[m_dragImage].Move( newPosition.x, newPosition.y );
}




//////////////////////////////////////////////////////////////////////////////
//
// WinMain - Entry point
//
//////////////////////////////////////////////////////////////////////////////

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE, LPTSTR, int )
{
    _Module.Init( 0, hInstance );
    
    BlitSample game;
    
    game.Run();
    
    return 0;
}
