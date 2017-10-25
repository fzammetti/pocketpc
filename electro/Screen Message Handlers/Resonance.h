
LRESULT CALLBACK Resonance(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {

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
			// Limit edit controls to 8 characters
			SendMessage(GetDlgItem(hDlg, IDC_EDIT_L), EM_SETLIMITTEXT, (WPARAM)8, 0);
			SendMessage(GetDlgItem(hDlg, IDC_EDIT_C), EM_SETLIMITTEXT, (WPARAM)8, 0);
			SendMessage(GetDlgItem(hDlg, IDC_EDIT_F), EM_SETLIMITTEXT, (WPARAM)8, 0);
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
					SetDlgItemText(hDlg, IDC_EDIT_L, TEXT(""));
					SetDlgItemText(hDlg, IDC_EDIT_C, TEXT(""));
					SetDlgItemText(hDlg, IDC_EDIT_F, TEXT(""));
				break; }

        case IDC_CALCULATE: {
					TCHAR  strInL[16]			= TEXT("");
					TCHAR  strInC[16]			= TEXT("");
					TCHAR  strInF[16]			= TEXT("");
					TCHAR  strResults[16] = TEXT("");
					double results				= 0;
					double known1					= 0;
					double known2					= 0;
					int		 whatOperation	= 0;
					LPTSTR sError;
          // Get our entered values
          GetDlgItemText(hDlg, IDC_EDIT_L, strInL, 15);
          GetDlgItemText(hDlg, IDC_EDIT_C, strInC, 15);
          GetDlgItemText(hDlg, IDC_EDIT_F, strInF, 15);
					// Check for illegal entries and abort if any found
					if (!validateInput(strInL)) { 
						MessageBox(hDlg, TEXT("There is a problem with the Inductance you entered.\n\nPlease check to be sure you only used the characters 0-9 and no more than one decimal point."), TEXT("Input Error"), MB_OK); 
						SetFocus(GetDlgItem(hDlg, IDC_EDIT_L));
						break;
					}
					if (!validateInput(strInC)) { 
						MessageBox(hDlg, TEXT("There is a problem with the Capacitance you entered.\n\nPlease check to be sure you only used the characters 0-9 and no more than one decimal point."), TEXT("Input Error"), MB_OK); 
						SetFocus(GetDlgItem(hDlg, IDC_EDIT_C));
						break;
					}
					if (!validateInput(strInF)) { 
						MessageBox(hDlg, TEXT("There is a problem with the Frequency you entered.\n\nPlease check to be sure you only used the characters 0-9 and no more than one decimal point."), TEXT("Input Error"), MB_OK); 
						SetFocus(GetDlgItem(hDlg, IDC_EDIT_F));
						break;
					}
          // Assume an invalid entry to begin with
          whatOperation = 0;
          // Determine which operation to perform
          if (wcscmp(strInL, TEXT("")) != 0 && 
              wcscmp(strInC, TEXT("")) != 0 && 
              wcscmp(strInF, TEXT("")) == 0) {
                whatOperation = 1; 
          }
          if (wcscmp(strInL, TEXT("")) == 0 && 
              wcscmp(strInC, TEXT("")) != 0 && 
              wcscmp(strInF, TEXT("")) != 0) { 
                whatOperation = 2; 
          }
          if (wcscmp(strInL, TEXT("")) != 0 && 
              wcscmp(strInC, TEXT("")) == 0 && 
              wcscmp(strInF, TEXT("")) != 0) {
                whatOperation = 3; 
          }
          // Perform the proper operation and show the results, or pop error
          switch (whatOperation) {
            case 1: // Known: L+C, Calculate F
              // Get the two known values
              known1 = wcstod(strInL, &sError);
              known2 = wcstod(strInC, &sError);
              // Do the actual calculations
              results = 1 / ((2 * Pi) * (sqrt(known1 * known2)));
              // Copy the results to strings formatted properly
              swprintf(strResults, TEXT("%.6f"), results);
              // Set the edit boxes to the answers
              SetDlgItemText(hDlg, IDC_EDIT_F, strResults);
              break;
            case 2: // Known: C+F, Calculate L
              // Get the two known values
              known1 = wcstod(strInC, &sError);
              known2 = wcstod(strInF, &sError);
              // Do the actual calculations
              results = 1 / (((4 * (Pi * Pi)) * (known2 * known2)) * known1);
              // Copy the results to strings formatted properly
              swprintf(strResults, TEXT("%.6f"), results);
              // Set the edit boxes to the answers
              SetDlgItemText(hDlg, IDC_EDIT_L, strResults);
              break;
            case 3: // Known: L+F, Calculate C
              // Get the two known values
              known1 = wcstod(strInL, &sError);
              known2 = wcstod(strInF, &sError);
              // Do the actual calculations
              results = 1 / (((4 * (Pi * Pi)) * (known2 * known2)) * known1);
              // Copy the results to strings formatted properly
              swprintf(strResults, TEXT("%.6f"), results);
              // Set the edit boxes to the answers
              SetDlgItemText(hDlg, IDC_EDIT_C, strResults);
              break;
            default:
              // Not a valid operation
              MessageBox(hDlg, TEXT("You must enter two and only two known values"), TEXT("Error"), MB_OK); 
            break;
					}
				break; }

			}

		break; }

		default: {
			return DefWindowProc(hWnd, message, wParam, lParam);
    break; }

	}

  return FALSE;

}