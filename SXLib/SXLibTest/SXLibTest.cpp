
#include "stdafx.h"
#include "SXLibTest.h"
#include <commctrl.h>
#include <aygshell.h>
#include <sipapi.h>
#include "../SXLib.h"

// Global Variables:
			 HINSTANCE			hInst;
			 HWND						hwndCB;
static SHACTIVATEINFO s_sai;
			 HWND						hWnd = NULL;

// Forward declarations of functions included in this code module:
ATOM							MyRegisterClass		(HINSTANCE, LPTSTR);
BOOL							InitInstance			(HINSTANCE, int);
LRESULT CALLBACK	WndProc						(HWND,			UINT, WPARAM, LPARAM);
LRESULT CALLBACK	TestDialog				(HWND,			UINT, WPARAM, LPARAM);
HWND							CreateRpCommandBar(HWND);

int WINAPI WinMain(	HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {
	MSG msg;
	if (!InitInstance (hInstance, nCmdShow)) {
		return FALSE;
	}
	DialogBox(hInst, (LPCTSTR)IDD_TEST_DIALOG, hWnd, (DLGPROC)TestDialog);
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}


ATOM MyRegisterClass(HINSTANCE hInstance, LPTSTR szWindowClass) {
	WNDCLASS	wc;
    wc.style				 = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc	 = (WNDPROC) WndProc;
    wc.cbClsExtra		 = 0;
    wc.cbWndExtra		 = 0;
    wc.hInstance		 = hInstance;
    wc.hIcon				 = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SXLIBTEST));
    wc.hCursor			 = 0;
    wc.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName	 = 0;
    wc.lpszClassName = szWindowClass;
	return RegisterClass(&wc);
}


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) {
	TCHAR	szTitle[25];
	TCHAR	szWindowClass[25];
	hInst = hInstance;
	LoadString(hInstance, IDC_SXLIBTEST, szWindowClass, 25);
	LoadString(hInstance, IDS_APP_TITLE, szTitle, 25);
	hWnd = FindWindow(szWindowClass, szTitle);	
	if (hWnd) {
		SetForegroundWindow ((HWND) (((DWORD)hWnd) | 0x01));    
		return 0;
	} 
	MyRegisterClass(hInstance, szWindowClass);
	RECT	rect;
	GetClientRect(hWnd, &rect);
	hWnd = CreateWindow(szWindowClass, szTitle, WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
	if (!hWnd) {	
		return FALSE;
	}
	{
		RECT rc;
		GetWindowRect(hWnd, &rc);
		rc.bottom -= MENU_HEIGHT;
		if (hwndCB) {
			MoveWindow(hWnd, rc.left, rc.top, rc.right, rc.bottom, FALSE);
		}
	}
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	return TRUE;
}


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


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	int wmId, wmEvent;
	switch (message) {
		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			switch (wmId) {	
				case IDOK:
					SendMessage(hWnd, WM_ACTIVATE, MAKEWPARAM(WA_INACTIVE, 0), (LPARAM)hWnd);
					SendMessage (hWnd, WM_CLOSE, 0, 0);
				break;
				default:
				   return DefWindowProc(hWnd, message, wParam, lParam);
				break;
			}
		break;
		case WM_CREATE:
			hwndCB = CreateRpCommandBar(hWnd);
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


LRESULT CALLBACK TestDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	static int idFX1 = NULL;
	static int idFX2 = NULL;
	static int idLoop1 = NULL;
	static int idLoop2 = NULL;
	static int idSilentLoop = NULL;
	SHINITDLGINFO shidi;
	switch (message) {
		case WM_INITDIALOG:
			shidi.dwMask = SHIDIM_FLAGS;
			shidi.dwFlags = SHIDIF_DONEBUTTON | SHIDIF_SIPDOWN | SHIDIF_SIZEDLGFULLSCREEN;
			shidi.hDlg = hDlg;
			SHInitDialog(&shidi);
			// initialize at 22050Hz with a .2 second buffer
			SX_Initialize(22050, 200);
			// load up sounds
			idFX1				 = SX_loadFX(IDR_FX_1,	 hInst);
			idFX2				 = SX_loadFX(IDR_FX_2,	 hInst);
			idLoop1			 = SX_loadMusic(IDR_LOOP_1, hInst);
			idLoop2			 = SX_loadMusic(IDR_LOOP_2, hInst);
			idSilentLoop = SX_loadMusic(IDR_SILENTLOOP, hInst);
			// set overall volume
			SX_setMusicVolume(100);
			SX_setFXVolume(200);
			SX_setCurrentMusic(idSilentLoop);
			SX_playStart();
			return TRUE;
		break; 
		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK) {
				SX_Exit();
				EndDialog(hDlg, LOWORD(wParam));
				SendMessage(hWnd, WM_ACTIVATE, MAKEWPARAM(WA_INACTIVE, 0), (LPARAM)hWnd);
				SendMessage (hWnd, WM_CLOSE, 0, 0);
				return TRUE;
			}
			int wmId    = LOWORD(wParam); 
			int wmEvent = HIWORD(wParam); 
      switch (wmId) {	
			  case IDC_PLAY_LOOP_1:
					SX_setCurrentMusic(idLoop1);
					SX_playStart();
				break;
			  case IDC_PLAY_LOOP_2:
					SX_setCurrentMusic(idLoop2);
					SX_playStart();
				break;
			  case IDC_PLAY_FX_1:
					SX_playFX(idFX1, 127);
				break;
			  case IDC_PLAY_FX_2:
					SX_playFX(idFX2, 127);
				break;
			  case IDC_PLAY_SILENT_MUSIC:
					SX_setCurrentMusic(idSilentLoop);
					SX_playStart();
				break;
			  case IDC_SILENCE_MUSIC:
					//SX_setSilentMusic();
				break;
				case IDC_STOP_ALL:
					SX_playStop();
				break;
			}
		break;
	}
  return FALSE;
}
