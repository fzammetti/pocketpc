
LRESULT CALLBACK MorseCode(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {

	switch (message) {

		case WM_INITDIALOG: {
			SHINITDLGINFO shidi;
			shidi.dwMask	= SHIDIM_FLAGS;
 		  shidi.dwFlags = SHIDIF_DONEBUTTON | SHIDIF_SIZEDLGFULLSCREEN;
			shidi.hDlg		= hDlg;
			SHInitDialog(&shidi);
			// Set the font of our title
			LOGFONT logFont;
			logFont.lfHeight				 = 13;
			logFont.lfWidth					 = 0;
			logFont.lfEscapement		 = 0;
			logFont.lfOrientation		 = 0;
			logFont.lfWeight				 = FW_EXTRABOLD;
			logFont.lfItalic				 = false;
			logFont.lfUnderline			 = false;
			logFont.lfStrikeOut			 = false;
			logFont.lfCharSet				 = OEM_CHARSET;
			logFont.lfOutPrecision	 = OUT_DEFAULT_PRECIS;
			logFont.lfClipPrecision  = CLIP_DEFAULT_PRECIS;
			logFont.lfQuality				 = DEFAULT_QUALITY;
			logFont.lfPitchAndFamily = FF_ROMAN | DEFAULT_PITCH;
			wcscpy(logFont.lfFaceName, TEXT("Tahoma"));
			SendMessage(GetDlgItem(hDlg, IDC_DIALOG_TITLE), WM_SETFONT, (WPARAM)CreateFontIndirect(&logFont), true); 
			DeleteObject(CreateFontIndirect(&logFont));
			SendMessage(GetDlgItem(hDlg, IDC_EDIT_F), EM_SETLIMITTEXT, (WPARAM)250, 0);
			return true;
		break; }

		case WM_CTLCOLORSTATIC: {
			// Set the color of our title
			if ((HWND)lParam == GetDlgItem(hDlg, IDC_DIALOG_TITLE)) { 
				SetTextColor((HDC)wParam, RGB(255, 0, 0));
				return (DWORD)(HBRUSH)GetStockObject(WHITE_BRUSH);
			} else {
				return false;
			}
		break; }

		case WM_COMMAND: {
			if (LOWORD(wParam) == IDOK) {
				ShowWindow(hWndCurrentScreen, SW_HIDE);
				SHSipPreference(hWnd, SIP_DOWN);
				hWndCurrentScreen = NULL;
				return true;
			}

			if (HIWORD(wParam) == EN_SETFOCUS) {
				SHSipPreference(hWnd, SIP_UP);
			}

      int wmId    = LOWORD(wParam); 
			int wmEvent = HIWORD(wParam); 
 
      switch (wmId) {	

			  case IDC_CLEAR: {
					SetDlgItemText(hDlg, IDC_EDIT_TEXT, TEXT(""));
				break; }

        case IDC_ENCODE: {  
					// Grab tne entered text and it's length
					TCHAR  strInText[256]	= TEXT("");
          GetDlgItemText(hDlg, IDC_EDIT_TEXT, strInText, 250);
					int i = 0;
					int strLen = wcslen(strInText);
					// Make sure they only entered characters we can handle
					for (i = 0; i < strLen; i++) {
						if (strInText[i] != '0' && strInText[i] != '1'  && strInText[i] != '2' &&
                strInText[i] != '3' && strInText[i] != '4'  && strInText[i] != '5' &&
                strInText[i] != '6' && strInText[i] != '7'  && strInText[i] != '8' &&
                strInText[i] != '9' && strInText[i] != 'A'  && strInText[i] != 'B' &&
                strInText[i] != 'C' && strInText[i] != 'D'  && strInText[i] != 'E' &&
                strInText[i] != 'F' && strInText[i] != 'G'  && strInText[i] != 'H' &&
                strInText[i] != 'I' && strInText[i] != 'J'  && strInText[i] != 'K' &&
                strInText[i] != 'L' && strInText[i] != 'M'  && strInText[i] != 'N' &&
                strInText[i] != 'O' && strInText[i] != 'P'  && strInText[i] != 'Q' &&
                strInText[i] != 'R' && strInText[i] != 'S'  && strInText[i] != 'T' &&
                strInText[i] != 'U' && strInText[i] != 'V'  && strInText[i] != 'W' &&
                strInText[i] != 'X' && strInText[i] != 'Y'  && strInText[i] != 'Z' &&
								strInText[i] != '"' && strInText[i] != '\'' && strInText[i] != ':' &&
                strInText[i] != ',' && strInText[i] != '-'  && strInText[i] != '(' &&
                strInText[i] != ')' && strInText[i] != '.'  && strInText[i] != '?' &&
								strInText[i] != ' ') {
									MessageBox(hDlg, TEXT("Only the characters 0-9, A-Z, space and the following are allowed:\n\" ' : , - ( ) . ?"), TEXT("Entry Error"), MB_OK);
									break;
						}
					}	
					SendMessage(GetDlgItem(hDlg, IDC_TELEGRAPH), STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_TELEGRAPH)));
					for (i = 0; i < strLen; i++) {
						if (strInText[i] == '0')  { PlaySound((unsigned short *) IDR_MORSECODE_0,						 hInst, SND_RESOURCE | SND_SYNC); }
						if (strInText[i] == '1')  { PlaySound((unsigned short *) IDR_MORSECODE_1,						 hInst, SND_RESOURCE | SND_SYNC); }
						if (strInText[i] == '2')  { PlaySound((unsigned short *) IDR_MORSECODE_2,						 hInst, SND_RESOURCE | SND_SYNC); }
						if (strInText[i] == '3')  { PlaySound((unsigned short *) IDR_MORSECODE_3,						 hInst, SND_RESOURCE | SND_SYNC); }
						if (strInText[i] == '4')  { PlaySound((unsigned short *) IDR_MORSECODE_4,						 hInst, SND_RESOURCE | SND_SYNC); }
						if (strInText[i] == '5')  { PlaySound((unsigned short *) IDR_MORSECODE_5,						 hInst, SND_RESOURCE | SND_SYNC); }
						if (strInText[i] == '6')  { PlaySound((unsigned short *) IDR_MORSECODE_6,						 hInst, SND_RESOURCE | SND_SYNC); }
						if (strInText[i] == '7')  { PlaySound((unsigned short *) IDR_MORSECODE_7,						 hInst, SND_RESOURCE | SND_SYNC); }
						if (strInText[i] == '8')  { PlaySound((unsigned short *) IDR_MORSECODE_8,						 hInst, SND_RESOURCE | SND_SYNC); }
						if (strInText[i] == '9')  { PlaySound((unsigned short *) IDR_MORSECODE_9,						 hInst, SND_RESOURCE | SND_SYNC); }
						if (strInText[i] == 'A')  { PlaySound((unsigned short *) IDR_MORSECODE_A,						 hInst, SND_RESOURCE | SND_SYNC); }
						if (strInText[i] == 'B')  { PlaySound((unsigned short *) IDR_MORSECODE_B,						 hInst, SND_RESOURCE | SND_SYNC); }
						if (strInText[i] == 'C')  { PlaySound((unsigned short *) IDR_MORSECODE_C,						 hInst, SND_RESOURCE | SND_SYNC); }
						if (strInText[i] == 'D')  { PlaySound((unsigned short *) IDR_MORSECODE_D,						 hInst, SND_RESOURCE | SND_SYNC); }
						if (strInText[i] == 'E')  { PlaySound((unsigned short *) IDR_MORSECODE_E,						 hInst, SND_RESOURCE | SND_SYNC); }
						if (strInText[i] == 'F')  { PlaySound((unsigned short *) IDR_MORSECODE_F,						 hInst, SND_RESOURCE | SND_SYNC); }
						if (strInText[i] == 'G')  { PlaySound((unsigned short *) IDR_MORSECODE_G,						 hInst, SND_RESOURCE | SND_SYNC); }
						if (strInText[i] == 'H')  { PlaySound((unsigned short *) IDR_MORSECODE_H,						 hInst, SND_RESOURCE | SND_SYNC); }
						if (strInText[i] == 'I')  { PlaySound((unsigned short *) IDR_MORSECODE_I,						 hInst, SND_RESOURCE | SND_SYNC); }
						if (strInText[i] == 'J')  { PlaySound((unsigned short *) IDR_MORSECODE_J,						 hInst, SND_RESOURCE | SND_SYNC); }
						if (strInText[i] == 'K')  { PlaySound((unsigned short *) IDR_MORSECODE_K,						 hInst, SND_RESOURCE | SND_SYNC); }
						if (strInText[i] == 'L')  { PlaySound((unsigned short *) IDR_MORSECODE_L,						 hInst, SND_RESOURCE | SND_SYNC); }
						if (strInText[i] == 'M')  { PlaySound((unsigned short *) IDR_MORSECODE_M,						 hInst, SND_RESOURCE | SND_SYNC); }
						if (strInText[i] == 'N')  { PlaySound((unsigned short *) IDR_MORSECODE_N,						 hInst, SND_RESOURCE | SND_SYNC); }
						if (strInText[i] == 'O')  { PlaySound((unsigned short *) IDR_MORSECODE_O,						 hInst, SND_RESOURCE | SND_SYNC); }
						if (strInText[i] == 'P')  { PlaySound((unsigned short *) IDR_MORSECODE_P,						 hInst, SND_RESOURCE | SND_SYNC); }
						if (strInText[i] == 'Q')  { PlaySound((unsigned short *) IDR_MORSECODE_Q,						 hInst, SND_RESOURCE | SND_SYNC); }
						if (strInText[i] == 'R')  { PlaySound((unsigned short *) IDR_MORSECODE_R,						 hInst, SND_RESOURCE | SND_SYNC); }
						if (strInText[i] == 'S')  { PlaySound((unsigned short *) IDR_MORSECODE_S,						 hInst, SND_RESOURCE | SND_SYNC); }
						if (strInText[i] == 'T')  { PlaySound((unsigned short *) IDR_MORSECODE_T,						 hInst, SND_RESOURCE | SND_SYNC); }
						if (strInText[i] == 'U')  { PlaySound((unsigned short *) IDR_MORSECODE_U,						 hInst, SND_RESOURCE | SND_SYNC); }
						if (strInText[i] == 'V')  { PlaySound((unsigned short *) IDR_MORSECODE_V,						 hInst, SND_RESOURCE | SND_SYNC); }
						if (strInText[i] == 'W')  { PlaySound((unsigned short *) IDR_MORSECODE_W,						 hInst, SND_RESOURCE | SND_SYNC); }
						if (strInText[i] == 'X')  { PlaySound((unsigned short *) IDR_MORSECODE_X,						 hInst, SND_RESOURCE | SND_SYNC); }
						if (strInText[i] == 'Y')  { PlaySound((unsigned short *) IDR_MORSECODE_Y,						 hInst, SND_RESOURCE | SND_SYNC); }
						if (strInText[i] == 'Z')  { PlaySound((unsigned short *) IDR_MORSECODE_Z,						 hInst, SND_RESOURCE | SND_SYNC); }
						if (strInText[i] == '"')  { PlaySound((unsigned short *) IDR_MORSECODE_QUOTES,			 hInst, SND_RESOURCE | SND_SYNC); }
						if (strInText[i] == '\'') { PlaySound((unsigned short *) IDR_MORSECODE_APOSTROPHE,	 hInst, SND_RESOURCE | SND_SYNC); }
						if (strInText[i] == ':')  { PlaySound((unsigned short *) IDR_MORSECODE_COLON,				 hInst, SND_RESOURCE | SND_SYNC); }
						if (strInText[i] == ',')  { PlaySound((unsigned short *) IDR_MORSECODE_COMMA,				 hInst, SND_RESOURCE | SND_SYNC); }
						if (strInText[i] == '-')  { PlaySound((unsigned short *) IDR_MORSECODE_HYPHEN,			 hInst, SND_RESOURCE | SND_SYNC); }
						if (strInText[i] == '(')  { PlaySound((unsigned short *) IDR_MORSECODE_PARENTHESES,  hInst, SND_RESOURCE | SND_SYNC); }
						if (strInText[i] == ')')  { PlaySound((unsigned short *) IDR_MORSECODE_PARENTHESES,  hInst, SND_RESOURCE | SND_SYNC); }
						if (strInText[i] == '.')  { PlaySound((unsigned short *) IDR_MORSECODE_PERIOD,			 hInst, SND_RESOURCE | SND_SYNC); }
						if (strInText[i] == '?')  { PlaySound((unsigned short *) IDR_MORSECODE_QUESTIONMARK, hInst, SND_RESOURCE | SND_SYNC); }
						if (strInText[i] == ' ')  { PlaySound((unsigned short *) IDR_MORSECODE_SPACE,				 hInst, SND_RESOURCE | SND_SYNC); }
					}
					SendMessage(GetDlgItem(hDlg, IDC_TELEGRAPH), STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_NULLIMAGE)));
				break; }

			}

		break; }

		default: {
			return DefWindowProc(hWnd, message, wParam, lParam);
    break; }

	}

  return FALSE;

}