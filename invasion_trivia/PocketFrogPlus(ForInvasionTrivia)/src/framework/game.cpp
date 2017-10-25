/////////////////////////////////////////////////////////////////////////////
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

#include <algorithm>
#include "game.h"

namespace Frog
{



//////////////////////////////////////////////////////////////////////////////
//
// Game
//
//////////////////////////////////////////////////////////////////////////////

Game::Game()
{
    m_config.szWindowName = _T( "PocketFrog" );
    m_config.orientation  = ORIENTATION_NORTH;
	m_config.displayflags = 0;

#if defined(NDEBUG)
    m_config.splashScreenTime = 1000;  // 1 second on retail builds
#else
    m_config.splashScreenTime = 0;     // Disabled on debug builds
#endif
}



Game::~Game()
{
}



DisplayDevice* Game::GetDisplay()
{
    DisplayDevice* display = m_display.get();
    
    if (display)
        display->BeginScene();

    return display;
}



InputDevice* Game::GetInput()
{
    return m_input.get();
}


Sound *Game::GetSound() {

    return m_sound;
}


void Game::FatalError( LPCTSTR msg )
{
	m_display.reset();
	m_input.reset();

    if (m_hWnd) DestroyWindow();

    ::MessageBox( 0, msg, _T("Fatal Error"), MB_OK);
    
	exit(-1);
}



bool Game::Init()
{
#if defined(FROG_HPC)
    // Handheld PC: force orientation to NORTH
    m_config.orientation = ORIENTATION_NORTH;
#endif

    m_bSuspended = false;

	//GetWndClassInfo().m_wc.style &= ~CS_DBLCLKS;
	GetWndClassInfo().m_wc.style = CS_HREDRAW | CS_VREDRAW;
	GetWndClassInfo().m_wc.hbrBackground = 0;

    // Create the window
#if defined(_WIN32_WCE)
    Rect r( 0, 0, ::GetSystemMetrics( SM_CXSCREEN ), ::GetSystemMetrics( SM_CYSCREEN ) );
    DWORD style = WS_VISIBLE;
#else
    Rect r( CW_USEDEFAULT, CW_USEDEFAULT, 0, 0 );
    DWORD style = WS_SYSMENU;
#endif

#if defined(FROG_HPC)
    DWORD exStyle = WS_EX_TOPMOST;
#else
    DWORD exStyle = 0;
#endif

    if (!Create( 0, r, m_config.szWindowName, style, exStyle ))
	{
		FatalError( _T("Window creation failed") );
        return false;
	}

#if defined(FROG_PC)
    // Make sure the window is of the proper size
    /*#if defined(FROG_PC_X2)
        int width = 240*2, height = 320*2;
    #else
        int width = 240, height = 320;
    #endif*/
	int width, height;
	if (m_config.displayflags & FROG_PC_X2) {
		width = 240*2; height = 320*2;
	}
	else {
		width = 240; height = 320;
	}
    
    if (m_config.orientation == ORIENTATION_WEST || m_config.orientation == ORIENTATION_EAST)
        std::swap( width, height );
    
    ResizeClient( width, height );
#endif

    // Init display
    m_display.reset( PocketPC::CreateDisplay( m_hWnd, m_config.orientation, m_config.displayflags ) );
    if (!m_display.get())
        return false;


#if defined(FROG_PC)
    ShowWindow( SW_SHOWNORMAL );
#endif


    // Init input
    m_input.reset( PocketPC::CreateInput( m_hWnd, m_config.orientation ));
    if (!m_input.get())
        return false;

    // In case ORIENTATION_UNKNOWN was selected
    m_config.orientation = m_display->GetOrientation();

    m_sound = PocketPC::CreateSound(m_hWnd);
	// if m_config.soundfrequency == 0 don't open... no sound!
	if (m_config.soundfrequency != 0) {
        if (m_sound->open(m_config.soundfrequency, m_config.soundstereo) == false)
		    return false;
	}
    
    return true;
}



bool Game::Run()
{
    // Initialization
    if (!Init())
	{
		FatalError( _T("Game::Init() failed") );
        return false;
	}

    // Splash screen
    if (m_config.splashScreenTime)
    {
        uint32_t timeEnd = PocketPC::GetTickCount() + m_config.splashScreenTime;
        
        m_display->SetDithering( DisplayDevice::DITHER_NICE );
        SplashScreen();
        m_display->SetDithering( DisplayDevice::DITHER_FAST );
        
        while (PocketPC::GetTickCount() < timeEnd)
            Sleep(1);
    }


    // Game will start...
    if (!GameInit())
    {
        m_sound->close();
        m_input.reset();
        m_display.reset();
        DestroyWindow();
        return false;
    }

    
    // Main loop
    for(;;)
    {
        MSG msg;

        if (::PeekMessage( &msg, 0, 0, 0, PM_REMOVE ))
        {
            if (msg.message == WM_QUIT)
                break;
            
            ::TranslateMessage( &msg );
            ::DispatchMessage( &msg );
        }
        else
        {
            if (!m_bSuspended)
                GameLoop();
        }
    }

    return true;
}



void Game::ShowTaskbar( bool bShow )
{
#if defined(FROG_PPC)

    if (bShow)
        ::SHFullScreen( m_hWnd, SHFS_SHOWTASKBAR | SHFS_SHOWSIPBUTTON | SHFS_SHOWSTARTICON );
    else
        ::SHFullScreen( m_hWnd, SHFS_HIDETASKBAR | SHFS_HIDESIPBUTTON | SHFS_HIDESTARTICON );

#elif defined(FROG_HPC)

    // Nothing to do...

#endif
}



void Game::Shutdown()
{
    GameEnd();

    m_sound->close();
    m_input.reset();
    m_display.reset();

    DestroyWindow();
}



//////////////////////////////////////////////////////////////////////////////
//
// Default implementation of callbacks
//
//////////////////////////////////////////////////////////////////////////////

bool Game::GameInit()
{
    return true;
}



void Game::GameEnd()
{
}



void Game::GameLoop()
{
}



void Game::ButtonDown( int button )
{
    Shutdown();
}



void Game::ButtonUp( int button )
{
}



void Game::StylusDown( Point p )
{
	Shutdown();
}



void Game::StylusMove( Point p )
{
}



void Game::StylusUp( Point p )
{
}



//////////////////////////////////////////////////////////////////////////////
//
// Message Handlers
//
//////////////////////////////////////////////////////////////////////////////

LRESULT Game::OnClose( UINT msg, WPARAM wparam, LPARAM lparam, BOOL& bHandled )
{
    Shutdown();
    return 0;
}



LRESULT Game::OnCreate( UINT msg, WPARAM wparam, LPARAM lparam, BOOL& bHandled )
{

    return 0;
}



LRESULT Game::OnDestroy( UINT msg, WPARAM wparam, LPARAM lparam, BOOL& bHandled )
{
    PostQuitMessage(0);
    return 0;
}



LRESULT Game::OnKeyDown( UINT msg, WPARAM wparam, LPARAM lparam, BOOL& bHandled )
{
    if (!(lparam & 0x40000000)) // Prevent auto-repeat
    {
        int button = wparam;
        m_input->DeviceToLogical( button );
        ButtonDown( button );
    }
    
#if defined(FROG_PC)
    if (wparam == VK_ESCAPE)
        PostMessage( WM_CLOSE, 0, 0 );
#endif

    return 0;
}



LRESULT Game::OnKeyUp( UINT msg, WPARAM wparam, LPARAM lparam, BOOL& bHandled )
{
    int button = wparam;
    m_input->DeviceToLogical( button );
    ButtonUp( button );

    return 0;
}



LRESULT Game::OnMouseEvent( UINT msg, WPARAM wparam, LPARAM lparam, BOOL& bHandled )
{

#if defined(FROG_PC)
    /*#if defined(FROG_PC_X2)
        Point P( LOWORD(lparam)/2, HIWORD(lparam)/2 );
    #else
        Point P( LOWORD(lparam), HIWORD(lparam) );
    #endif*/

    Point P;
	if (m_config.displayflags & FROG_PC_X2) {
        P.Set( LOWORD(lparam)/2, HIWORD(lparam)/2 );
	}
	else {
        P.Set( LOWORD(lparam), HIWORD(lparam) );
	}

#else
    Point P( LOWORD(lparam), HIWORD(lparam) );
    m_input->DeviceToLogical( P );
#endif

    switch(msg)
    {
    case WM_LBUTTONDOWN: StylusDown( P ); break;
    case WM_MOUSEMOVE:   StylusMove( P ); break;
    case WM_LBUTTONUP:   StylusUp( P );   break;
    }
    
    return 0;
}



LRESULT Game::OnActivate( UINT msg, WPARAM wparam, LPARAM lparam, BOOL& bHandled )
{
    if (LOWORD(wparam) == WA_INACTIVE)
    {
        if (!m_bSuspended)
        {
            PocketPC::Suspend();
            m_sound->suspend();
            m_bSuspended = true;
        }
    }
    else
    {
        if (m_bSuspended)
        {
            PocketPC::Resume();
            m_sound->resume();
            m_bSuspended = false;
        }
    }
    

    ShowTaskbar( LOWORD(wparam) == WA_INACTIVE );

    return 0;
}



LRESULT Game::OnSetFocus( UINT msg, WPARAM wparam, LPARAM lparam, BOOL& bHandled )
{
    return OnActivate( WM_ACTIVATE, WA_ACTIVE, 0, bHandled );
}



LRESULT Game::OnKillFocus( UINT msg, WPARAM wparam, LPARAM lparam, BOOL& bHandled )
{
    return OnActivate( WM_ACTIVATE, WA_INACTIVE, 0, bHandled );
}



LRESULT Game::OnPaint( UINT msg, WPARAM wparam, LPARAM lparam, BOOL& bHandled )
{
    PAINTSTRUCT ps;
    
    BeginPaint( &ps );
    EndPaint( &ps );

	return 0;
}



} // end of namespace Frog
