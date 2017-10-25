
// Includes
#include "stdafx.h"
#include <windows.h>
#include <direct.h>
#include "resource.h"


// Global variables
HINSTANCE hInst						  = NULL;
TCHAR			szAppName[256]	  = TEXT("");
TCHAR			szAppVersion[32]	= TEXT("");
TCHAR			szTitle[256]			= TEXT("");
TCHAR			szFullTitle[256]  = TEXT("");
TCHAR			szWindowClass[32] = TEXT("");


// This function is called when the user clicks Cancel to verify they want to really quit the setup
BOOL verifyCancel(HWND hDlg) {
	// Create the text string for the message of this popup
	TCHAR szMessage[256] = TEXT("");
	strcat(szMessage, TEXT("Setup is not complete.  If you quit now,\n"));
	strcat(szMessage, szAppName);
	strcat(szMessage, TEXT(" v"));
	strcat(szMessage, szAppVersion);
	strcat(szMessage, TEXT(" will not be installed.\n\nYou may run Setup at a later time to complete the\ninstallation.\n\nDo you wish to quit installing "));
	strcat(szMessage, szAppName);
	strcat(szMessage, TEXT(" v"));
	strcat(szMessage, szAppVersion);
	strcat(szMessage, TEXT("?"));
	if (MessageBox(hDlg, szMessage, TEXT("Exit Setup"), MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2 | MB_APPLMODAL) == IDYES) { 
		return true;
	} else {
		return false;
	}
}


// Message handler function for the Welcome dialog
int CALLBACK scrWelcomeProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
		case WM_INITDIALOG: {
			// Create the text string for the text next to the install icon and set it
			TCHAR szWelcome1[128] = TEXT("");
			strcat(szWelcome1, TEXT("Welcome to the "));
			strcat(szWelcome1, szFullTitle);
			strcat(szWelcome1, TEXT(" setup program.  This program will install "));
			strcat(szWelcome1, szFullTitle);
			strcat(szWelcome1, TEXT(" on your mobile device."));
			SetDlgItemText(hDlg, IDC_WELCOME1, szWelcome1);
			// Create the text string for the titlebar text and set it
			TCHAR szTitlebarText[32] = TEXT("");
			strcat(szTitlebarText, szFullTitle);
			strcat(szTitlebarText, TEXT(" Setup"));
			SetWindowText(hDlg, szTitlebarText);
		break; }
		case WM_COMMAND: {
			int wmId    = LOWORD(wParam); 
			int wmEvent = HIWORD(wParam); 
			switch (wmId) {
				case IDC_CANCEL: {
					// CANCEL was clicked, make sure they want to exit
					if (verifyCancel(hDlg)) {
						EndDialog(hDlg, 1);
					}
				break; }
				case IDC_NEXT: {
					EndDialog(hDlg, 0);
				break; }
			}
		break; }
	}
	return 0;
}


// Message handler function for the EULA dialog
int CALLBACK scrEULAProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
		case WM_INITDIALOG: {
			// Create the text string for the text below the EULA text and set it
			TCHAR szEULA1[256] = TEXT("");
			strcat(szEULA1, TEXT("Do you accept all the terms of the preceeding License Agreement?  If you choose Decline, Setup will close.  To install "));
			strcat(szEULA1, szFullTitle);
			strcat(szEULA1, TEXT(", you must accept this agreement."));
			SetDlgItemText(hDlg, IDC_EULA1, szEULA1);
			// Set the actual EULA text
			TCHAR szEULA[14500]   = TEXT("");
			TCHAR szEULAP1[2050] = TEXT("");
			TCHAR szEULAP2[2050] = TEXT("");
			TCHAR szEULAP3[2050] = TEXT("");
			TCHAR szEULAP4[2050] = TEXT("");
			TCHAR szEULAP5[2050] = TEXT("");
			TCHAR szEULAP6[2050] = TEXT("");
			TCHAR szEULAP7[2050] = TEXT("");
			LoadString(hInst, IDS_EULA1, szEULAP1, 2048);
			LoadString(hInst, IDS_EULA2, szEULAP2, 2048);
			LoadString(hInst, IDS_EULA3, szEULAP3, 2048);
			LoadString(hInst, IDS_EULA4, szEULAP4, 2048);
			LoadString(hInst, IDS_EULA5, szEULAP5, 2048);
			LoadString(hInst, IDS_EULA6, szEULAP6, 2048);
			LoadString(hInst, IDS_EULA7, szEULAP7, 2048);
			strcat(szEULA, szEULAP1);
			strcat(szEULA, szEULAP2);
			strcat(szEULA, szEULAP3);
			strcat(szEULA, szEULAP4);
			strcat(szEULA, szEULAP5);
			strcat(szEULA, szEULAP6);
			strcat(szEULA, szEULAP7);
			SetDlgItemText(hDlg, IDC_EULA_TEXT, szEULA);
		break; }

		case WM_COMMAND: {
			int wmId    = LOWORD(wParam); 
			int wmEvent = HIWORD(wParam);
			switch (wmId) {
				case IDC_BACK: {
					EndDialog(hDlg, 2);
				break; }
				case IDC_DECLINE: {
					EndDialog(hDlg, 1);
				break; }
				case IDC_ACCEPT: {
					EndDialog(hDlg, 0);
				break; }
			}
		break; }
	}
	return 0;
}


// Message handler function for the main background window
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

	switch (message) {

		case WM_PAINT: {
			TCHAR szText[64] = TEXT("");
			strcpy(szText, szFullTitle);
			strcat(szText, TEXT(" Setup"));
			PAINTSTRUCT ps;
			RECT rt;
			HDC hDC	= NULL;
			hDC = BeginPaint(hWnd, &ps);
				rt.top    = 20;
				rt.left   = 20;
				rt.bottom = 1000;
				rt.right  = 1000;
				// Set the font
				LOGFONT lf;
				HGDIOBJ oldObject;
				lf.lfWeight					= FW_BOLD;
				lf.lfEscapement			= 0;
				lf.lfOrientation		= 0;
				lf.lfHeight					= 48;
				lf.lfWidth					= 0;
				lf.lfCharSet				= OEM_CHARSET;
				lf.lfClipPrecision	= CLIP_DEFAULT_PRECIS;
				lf.lfItalic					= TRUE;
				lf.lfUnderline			= FALSE;
				lf.lfStrikeOut			= FALSE;
				lf.lfQuality				= DEFAULT_QUALITY;
				lf.lfOutPrecision		= OUT_DEFAULT_PRECIS;
				lf.lfPitchAndFamily = FF_ROMAN | DEFAULT_PITCH;
				strcpy(lf.lfFaceName, TEXT("MS Serif"));
				oldObject = SelectObject(hDC, CreateFontIndirect(&lf));
				// Set the current text color and background
				SetTextColor(hDC, 0x00ffffff);
				SetBkColor  (hDC, 0x00000000);
				DrawText(hDC, szText, strlen(szText), &rt, DT_LEFT);
			EndPaint(hWnd, &ps);
		break; }

		default: {
			return DefWindowProc(hWnd, message, wParam, lParam);
    break; }

  }

  return 0;

}


// EXECUTION BEGINS HERE
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	int retVal;
	// Get our instance for later
	hInst = hInstance;
	// Load strings from string table for later
	LoadString(hInst, IDS_APP_NAME,    szAppName,    32);
	LoadString(hInst, IDS_APP_VERSION, szAppVersion, 16);

	// Create the main background window
	LoadString(hInstance, IDS_APP_CLASS, szWindowClass, 32);
	strcat(szTitle, szAppName);
	strcat(szTitle, TEXT(" v"));
	strcat(szTitle, szAppVersion);
	strcpy(szFullTitle, szTitle);
	HWND hWnd = FindWindow(szWindowClass, szTitle);	
	if (hWnd) {
		SetForegroundWindow((HWND)(((DWORD)hWnd) | 0x01));    
	} else {
		WNDCLASS wc;
			wc.style			    = CS_HREDRAW | CS_VREDRAW | CS_NOCLOSE;
			wc.lpfnWndProc		= (WNDPROC)WndProc;
			wc.cbClsExtra		  = 0;
			wc.cbWndExtra		  = 0;
			wc.hInstance		  = hInstance;
			wc.hIcon			    = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON));
			wc.hCursor			  = 0;
			wc.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
			wc.lpszMenuName		= 0;
			wc.lpszClassName	= szWindowClass;
		RegisterClass(&wc);
		hWnd = CreateWindow(szWindowClass, TEXT("Omnytex Technologies"), NULL, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
		if (!hWnd) { 
			return FALSE; 
		}
		ShowWindow(hWnd, SW_MAXIMIZE);
}

	// Show the welcome screen, exit program if 1 returned (CANCEL clicked)
doWelcome:
	retVal = DialogBox(hInst, MAKEINTRESOURCE(IDD_WELCOME), hWnd, (DLGPROC)scrWelcomeProc);
	if (retVal == 1) {
		return -1;
	}

	// Show the EULA, exit program if FALSE returned (DECLINE clicked)
	retVal = DialogBox(hInst, MAKEINTRESOURCE(IDD_EULA),    hWnd, (DLGPROC)scrEULAProc);
	if (retVal == 1) {
		return -1;
	} else if (retVal == 2) {
		goto doWelcome;
	}

	// Info message about installing over previous versions
	MessageBox(NULL, TEXT("If you have a previous version of this software installed on your device, you will twice see a message asking you\nif you want to proceed with the re-install/upgrade, once on your PC and once on your device.\n\nClick YES both times and the previous installation will be overwritten."), TEXT("IMPORTANT!!"), MB_OK | MB_SETFOREGROUND | MB_ICONEXCLAMATION); 

	// Install the application
	
	// Make sure ActiveSync is installed
	LRESULT retValL;
	HKEY hKey;
	retValL = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\App Paths\\CEAPPMGR.EXE", 0, KEY_QUERY_VALUE, &hKey);
	if (retValL != ERROR_SUCCESS) {
		MessageBox(NULL, "Microsoft ActiveSync not found on this computer. Setup cannot continue and will now exit.", "Setup", MB_OK);
		return -1;
	}

	// Get the full path to CEAppMgr.exe
	TCHAR szCEAppMgr[512];
	DWORD bs;
	bs = sizeof(szCEAppMgr);
	retValL = RegQueryValueEx(hKey, "", 0, NULL, (BYTE *)szCEAppMgr, &bs);
	if (retValL != ERROR_SUCCESS) {
		MessageBox(NULL, "Unable to locate CeAppMgr.exe. Setup cannot continue and will now exit.", "Setup", MB_OK);
	}
	RegCloseKey(hKey);

	// Execute CEAppMgr.exe with the INI file as a parameter
	TCHAR szCmdLine[512]		= TEXT("");
	TCHAR szCurrentDir[512] = TEXT("");
	_getcwd(szCurrentDir, 512); // Get current working directory
	_strupr(szCurrentDir); // Make sure it's all upper-case
	int CurDirStrLen = strlen(szCurrentDir); // Get the length of the current directory string, INCLUDING the terminator
	// If the character right before the terminator is NOT a backslash, add it
	if (szCurrentDir[CurDirStrLen - 1] != '\\') {
		strcat(szCurrentDir, TEXT("\\"));
	}
	// Now construct our command line string, starting with the full path to CEAppMgr, enclosed in quotes
	strcat(szCmdLine, TEXT("\""));
	strcat(szCmdLine, szCEAppMgr);
	strcat(szCmdLine, TEXT("\""));
	// Now a space to separate the CEAppMgr part from the INI file part
	strcat(szCmdLine, TEXT(" "));
	// Now the INI file part, enclosed in quotes, starting with the current working directory
	strcat(szCmdLine, TEXT("\""));
	strcat(szCmdLine, szCurrentDir);
	strcat(szCmdLine, TEXT("setup.ini"));
	strcat(szCmdLine, TEXT("\""));
	// And execute it...
	WinExec(szCmdLine, SW_SHOW);
	// Exit successfully
	return 0; 
}