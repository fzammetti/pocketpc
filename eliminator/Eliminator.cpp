// Eliminator.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Eliminator.h"
#include <commctrl.h>
#include <aygshell.h>
#include <sipapi.h>
HWND hWnd;

typedef struct tagHOFREC {
	TCHAR szPattern[21];
	TCHAR szName[21];
	TCHAR szPiecesLeft[21];
	TCHAR szTime[21];
}	HOFREC;

// Global Variables:
bool									showingClickGamer     = true;
unsigned long         showingClickGamerTime = 0;
static SHACTIVATEINFO s_sai;
HINSTANCE							hInst                 = NULL;
HWND									hwndCB                = NULL;
HWND									hwnd_Playfield        = NULL;    
int                   pattern_index         = 1;
int                   what_graphic          = IDB_MARBLE_RED;    // Current play piece
int                   what_graphic_up		    = IDB_MARBLE_RED_UP; // Current play piece_up
int										what_graphic_empty    = IDB_MARBLE_EMPTY;  // Current empty tile for current play piece
int                   current_y             = 0; // Y index of currently selected piece
int										current_x					    = 0; // X index of currently selected piece
int										current_up_tile				= 0;
bool                  piece_up              = false; // Flag: Is a piece currently up? 0=N,1=Y
int                   pieces_remaining      = 0; // Number of pieces remaining
bool									game_in_progress      = false; // Flag: Game in progress? 0=N,1=Y
int										selected_pattern      = 0; // Use on option screen when board pattern is changed
int										selected_pieces       = 0; // Use on option screen when play piece is changed
int										selected_pieces_up    = 0; // Use on option screen when play piece is changed
int										selected_pieces_empty = 0; // Use on option screen when play piece is changed
bool									sound_enabled         = true; // Flag: Is sound active?
TCHAR									strRemaining[5]       = L""; // Text version of number of remaining pieces
int										elapsed_minutes       = 0;
int										elapsed_seconds       = 0;

// These define the possible values for each tile
int										blank_tile				 = 0;
int										empty_tile				 = 1;
int										filled_tile				 = 2;
int										current_piece			 = 3;
int										what_sound         = 0;
bool									game_won					 = false;


// Forward declarations of functions included in this code module:
ATOM							MyRegisterClass		(HINSTANCE, LPTSTR);
BOOL							InitInstance			(HINSTANCE, int);
LRESULT CALLBACK	WndProc						(HWND, UINT, WPARAM, LPARAM);
HWND							CreateRpCommandBar(HWND);
void              PopulatePlayfield (HWND);


#include "Patterns.h"
#include "Tiles.h"
#include "CurrentStates.h"
#include "MainGameHandler.h"
#include "SCR_About.h"
#include "SCR_Options.h"
#include "SCR_HOF.h"
#include "SCR_HowToPlay.h"
#include "SCR_WonLost.h"


// WinMain
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {
	MSG msg;
	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) {
		return FALSE;
	}
	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}


// MyRegisterClass
ATOM MyRegisterClass(HINSTANCE hInstance, LPTSTR szWindowClass) {
	WNDCLASS	wc;
    wc.style					= CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc		= (WNDPROC) WndProc;
    wc.cbClsExtra			= 0;
    wc.cbWndExtra			= 0;
    wc.hInstance			= hInstance;
    wc.hIcon					= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APP_ICON));
    wc.hCursor			  = 0;
    wc.hbrBackground	= (HBRUSH) GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName		= 0;
    wc.lpszClassName	= szWindowClass;
	return RegisterClass(&wc);
}

// InitInstance
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) {
	TCHAR	szTitle[255];			// The title bar text
	TCHAR	szWindowClass[255];		// The window class name
	hInst = hInstance;		// Store instance handle in our global variable
	// Initialize global strings
	LoadString(hInstance, IDS_APP_CLASS, szWindowClass, 255);
	LoadString(hInstance, IDS_APP_TITLE, szTitle, 255);
	//If it is already running, then focus on the window
	hWnd = FindWindow(szWindowClass, szTitle);	
	if (hWnd) {
		SetForegroundWindow ((HWND) (((DWORD)hWnd) | 0x01));    
		return 0;
	} 
	MyRegisterClass(hInstance, szWindowClass);
	RECT	rect;
	GetClientRect(hWnd, &rect);
	hWnd = CreateWindow(szWindowClass, szTitle, WS_VISIBLE,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
	if (!hWnd) {	
		return FALSE;
	}
	//When the main window is created using CW_USEDEFAULT the height of the menubar (if one
	// is created is not taken into account). So we resize the window after creating it
	// if a menubar is present
	{
		RECT rc;
		GetWindowRect(hWnd, &rc);
		rc.bottom -= MENU_HEIGHT;
		if (hwndCB)
			MoveWindow(hWnd, rc.left, rc.top, rc.right, rc.bottom, FALSE);
	}
	// Load the tile resource codes now
	loadTiles();
	// Load the playfield pattern array now
  loadPatterns();
  // And load the current states of our tiles
	loadCurrentStates();
	// Load our playfield dialog
	hwnd_Playfield = CreateDialog(hInst, MAKEINTRESOURCE(IDD_PLAYFIELD), hWnd, (DLGPROC)MainGameHandler); 
	// Start our elapsed time counter
	SetTimer(hwnd_Playfield, 1, 1000, NULL);
	SHSipPreference(hWnd, SIP_DOWN);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	return TRUE;
}


// WndProc
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

	HDC hdc, hDCMem;
	HBITMAP hBitmap, hOldBitmap;
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	RECT rt;
	TCHAR szVerTemp[255] = L"", szVersion[255] = L"";

	switch (message) {

		case WM_LBUTTONDOWN:
			if (showingClickGamer) {
				showingClickGamer = false;
				InvalidateRect(hWnd, NULL, true);
				UpdateWindow(hWnd);
				hwndCB = CreateRpCommandBar(hWnd);
			}
		break;
	
		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 

			// Parse the menu selections:
			switch (wmId) {	

				case IDM_NEW:
					if (game_in_progress == true) {
						if (MessageBox(hWnd, L"The current game will be abandoned.  Are you sure you want to do this?", L"Confirm...", MB_YESNO | MB_ICONQUESTION) == IDNO) { 
							break; 
						}
					}
					piece_up = false;
					game_in_progress = true;
	        // Populate the playfield with the current pattern
	        PopulatePlayfield(hWnd);
          // Reset our current states
	        loadCurrentStates();
          // And show it
				  SHSipPreference(hWnd, SIP_DOWN);
					_stprintf(strRemaining, TEXT("%d"), pieces_remaining);
					SetDlgItemText(hwnd_Playfield, IDC_REMAINING, strRemaining);
					elapsed_minutes = 0;
					elapsed_seconds = 0;
					SetDlgItemText(hwnd_Playfield, IDC_ELAPSED, L"");
					ShowWindow(hwnd_Playfield, SW_SHOWNORMAL);
				break;

				case IDM_OPTIONS:
					DialogBox(hInst, (LPCTSTR)IDD_OPTIONS, hWnd, (DLGPROC)Options);
				break;

				case IDM_HOWTOPLAY:
					DialogBox(hInst, (LPCTSTR)IDD_INSTRUCTIONS, hWnd, (DLGPROC)HowToPlay);
				break;

				case IDM_ABOUT:
					DialogBox(hInst, (LPCTSTR)IDD_ABOUT, hWnd, (DLGPROC)About);
				break;

				case IDM_EXIT:
					SHSipPreference(hWnd, SIP_DOWN);
					SendMessage(hWnd, WM_ACTIVATE, MAKEWPARAM(WA_INACTIVE, 0), (LPARAM)hWnd);
					SendMessage(hWnd, WM_CLOSE, 0, 0);
				break;

				case IDOK:
					SendMessage(hWnd, WM_ACTIVATE, MAKEWPARAM(WA_INACTIVE, 0), (LPARAM)hWnd);
					SendMessage (hWnd, WM_CLOSE, 0, 0);
				break;

				default:
				   return DefWindowProc(hWnd, message, wParam, lParam);
				break;
			}
			break;

		case WM_PAINT:

			hdc = BeginPaint(hWnd, &ps);

			if (showingClickGamer) {

				// Create a memory device context compatible with the device. 
				hDCMem = CreateCompatibleDC(hdc);
				// Load bitmap into bitmap structure (ELIMINATOR LOGO)
				hBitmap = LoadBitmap(hInst,MAKEINTRESOURCE(IDB_CLICKGAMER));;
				// Select the new bitmap object into the memory device context. 
				hOldBitmap = (struct HBITMAP__*)SelectObject(hDCMem, hBitmap);
				BitBlt(hdc, 0, 0, 240, 320, hDCMem, 0,0, SRCCOPY);
				// Select the old bitmap back into the device context.
				SelectObject(hDCMem, hOldBitmap);

			} else {

				GetClientRect(hWnd, &rt);
				_tcscat(szVersion, L"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
				LoadString(hInst, IDS_VERSION, szVerTemp, 255);
				_tcscat(szVersion, szVerTemp);
				DrawText(hdc, szVersion, _tcslen(szVersion), &rt, DT_WORDBREAK | DT_CENTER);
				// Create a memory device context compatible with the device. 
				hDCMem = CreateCompatibleDC(hdc);

				// Load bitmap into bitmap structure (ELIMINATOR LOGO)
				hBitmap = LoadBitmap(hInst,MAKEINTRESOURCE(IDB_ELIMINATOR));;
				// Select the new bitmap object into the memory device context. 
				hOldBitmap = (struct HBITMAP__*)SelectObject(hDCMem, hBitmap);
				BitBlt(hdc, 3, 19, 240, 45, hDCMem, 0,0, SRCCOPY);
				// Select the old bitmap back into the device context.
				SelectObject(hDCMem, hOldBitmap);

				// Load bitmap into bitmap structure (BY FRANK W. ZAMMETTI)
				hBitmap = LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BYFWZ));;
				// Select the new bitmap object into the memory device context. 
				hOldBitmap = (struct HBITMAP__*)SelectObject(hDCMem, hBitmap);
				BitBlt(hdc, 30, 70, 180, 26, hDCMem, 0,0, SRCCOPY);
				// Select the old bitmap back into the device context.
				SelectObject(hDCMem, hOldBitmap);

				// Load bitmap into bitmap structure (HAPPY MAN)
				hBitmap = LoadBitmap(hInst,MAKEINTRESOURCE(IDB_HAPPYMAN));;
				// Select the new bitmap object into the memory device context. 
				hOldBitmap = (struct HBITMAP__*)SelectObject(hDCMem, hBitmap);
				BitBlt(hdc, 10, 115, 73, 100, hDCMem, 0,0, SRCCOPY);
				// Select the old bitmap back into the device context.
				SelectObject(hDCMem, hOldBitmap);

				// Load bitmap into bitmap structure (BROUGHT TO YOU BY BLOCK)
				hBitmap = LoadBitmap(hInst,MAKEINTRESOURCE(IDB_BROUGHTTOYOUBY));;
				// Select the new bitmap object into the memory device context. 
				hOldBitmap = (struct HBITMAP__*)SelectObject(hDCMem, hBitmap);
				BitBlt(hdc, 90, 125, 129, 71, hDCMem, 0,0, SRCCOPY);
				// Select the old bitmap back into the device context.
				SelectObject(hDCMem, hOldBitmap);

			}

			// Delete the bitmap object and free all resources associated with it. 
			DeleteObject(hBitmap);
			// Delete the memory device context and the display device context.
			DeleteDC(hDCMem);
			ReleaseDC(hWnd, hdc);
			EndPaint(hWnd, &ps);
      SHSipPreference(hWnd, SIP_DOWN);

		break;

		case WM_DESTROY:
			CommandBar_Destroy(hwndCB);
			PostQuitMessage(0);
		break;

		case WM_SETTINGCHANGE:
			SHHandleWMSettingChange(hWnd, wParam, lParam, &s_sai);
    break;

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		break;
   }
   return 0;
}


// CreateRpCommandBar
HWND CreateRpCommandBar(HWND hwnd) {
	SHMENUBARINFO mbi;
	memset(&mbi, 0, sizeof(SHMENUBARINFO));
	mbi.cbSize     = sizeof(SHMENUBARINFO);
	mbi.hwndParent = hwnd;
	mbi.nToolBarId = IDM_MENU;
	mbi.hInstRes   = hInst;
	mbi.nBmpId     = 0;
	mbi.cBmpImages = 0;
	if (!SHCreateMenuBar(&mbi)) {
		return NULL;
	}
	return mbi.hwndMB;
}


// Populates the playfield with the current pattern
void PopulatePlayfield(HWND myhwnd) {
	pieces_remaining = 0;
  // myhwnd is only for debugging purposes, it serves no real purpose
	int x, y, show_graphic;
	for (y = 1; y < 11; y++) {
		for (x = 1; x < 11; x++) {
			switch (Patterns[pattern_index][y][x]) {
				case 0:		
					show_graphic = IDB_BLANK_TILE;
				break;
				case 1:	
					show_graphic = IDB_MARBLE_EMPTY;	
				break;
				case 2:		
          pieces_remaining++;
					show_graphic = what_graphic;
				break;
			}
			SendMessage(GetDlgItem(hwnd_Playfield, Tiles[y][x]), STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)LoadBitmap(hInst, MAKEINTRESOURCE(show_graphic)));
		}
	}
}