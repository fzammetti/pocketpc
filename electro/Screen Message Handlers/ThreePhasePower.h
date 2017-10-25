
LRESULT CALLBACK ThreePhasePower(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {

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
			// Fill our drop-downs
			SendMessage(GetDlgItem(hDlg, IDC_DD_FROM), CB_ADDSTRING, 0, (LPARAM)TEXT("Delta"));
			SendMessage(GetDlgItem(hDlg, IDC_DD_FROM), CB_ADDSTRING, 0, (LPARAM)TEXT("Wye"));
			SendMessage(GetDlgItem(hDlg, IDC_DD_TO),   CB_ADDSTRING, 0, (LPARAM)TEXT("Delta"));
			SendMessage(GetDlgItem(hDlg, IDC_DD_TO),   CB_ADDSTRING, 0, (LPARAM)TEXT("Wye"));
			// Default selections
			SendMessage(GetDlgItem(hDlg, IDC_DD_FROM), CB_SETCURSEL, 0, 0);
			SendMessage(GetDlgItem(hDlg, IDC_DD_TO),   CB_SETCURSEL, 0, 0);
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

			if (HIWORD(wParam) == CBN_SELCHANGE) {
				TCHAR  strFrom[16]    = TEXT("");
				TCHAR  strTo[16]			= TEXT("");
				int		 imgFrom				= 0;
				int		 imgTo					= 0;
				SendMessage(GetDlgItem(hDlg, IDC_DD_FROM), CB_GETLBTEXT, SendMessage(GetDlgItem(hDlg, IDC_DD_FROM), CB_GETCURSEL, 0, 0), (LPARAM)strFrom);
				SendMessage(GetDlgItem(hDlg, IDC_DD_TO),   CB_GETLBTEXT, SendMessage(GetDlgItem(hDlg, IDC_DD_TO),   CB_GETCURSEL, 0, 0), (LPARAM)strTo);
				if (wcscmp(strFrom, TEXT("Delta")) == 0 && wcscmp(strTo, TEXT("Wye"))   == 0 ) { 
					imgFrom = IDB_DELTA;
					imgTo		= IDB_WYE;
				}
				if (wcscmp(strFrom, TEXT("Delta")) == 0 && wcscmp(strTo, TEXT("Delta")) == 0 ) {
					imgFrom = IDB_DELTA;
					imgTo		= IDB_DELTA;
				}
				if (wcscmp(strFrom, TEXT("Wye"))   == 0 && wcscmp(strTo, TEXT("Delta")) == 0 ) {
					imgFrom = IDB_WYE;
					imgTo		= IDB_DELTA;
				}
				if (wcscmp(strFrom, TEXT("Wye"))   == 0 && wcscmp(strTo, TEXT("Wye"))   == 0 ) {
					imgFrom = IDB_WYE;
					imgTo		= IDB_WYE;
				}
				SendMessage(GetDlgItem(hDlg, IDC_PIC_FROM), STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)LoadBitmap(hInst, MAKEINTRESOURCE(imgFrom)));
				SendMessage(GetDlgItem(hDlg, IDC_PIC_TO),   STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)LoadBitmap(hInst, MAKEINTRESOURCE(imgTo)));
			}

			if (HIWORD(wParam) == EN_SETFOCUS) {
				SHSipPreference(hWnd, SIP_UP);
			}

      int wmId    = LOWORD(wParam); 
			int wmEvent = HIWORD(wParam); 

      switch (wmId) {	

				case IDC_CLEAR: {
					SetDlgItemText(hDlg, IDC_EDIT_EP, TEXT(""));
					SetDlgItemText(hDlg, IDC_EDIT_ES, TEXT(""));
					SetDlgItemText(hDlg, IDC_EDIT_N,  TEXT(""));
				break; }

       case IDC_CALCULATE: {
					TCHAR  strInEP[16]		= TEXT("");
					TCHAR  strInES[16]		= TEXT("");
					TCHAR  strInN[16]			= TEXT("");
					TCHAR  strResults[16] = TEXT("");
					TCHAR  strFrom[16]    = TEXT("");
					TCHAR  strTo[16]			= TEXT("");
					double results				= 0;
					double known1					= 0;
					double known2					= 0;
					int		 whatOperation	= 0;
					// Figure out what we're going from and to
					SendMessage(GetDlgItem(hDlg, IDC_DD_FROM), CB_GETLBTEXT, SendMessage(GetDlgItem(hDlg, IDC_DD_FROM), CB_GETCURSEL, 0, 0), (LPARAM)strFrom);
					SendMessage(GetDlgItem(hDlg, IDC_DD_TO),   CB_GETLBTEXT, SendMessage(GetDlgItem(hDlg, IDC_DD_TO),   CB_GETCURSEL, 0, 0), (LPARAM)strTo);
					int whatOp = 0;
					if (wcscmp(strFrom, TEXT("Delta")) == 0 && wcscmp(strTo, TEXT("Wye"))   == 0 ) { whatOp = 1; }
					if (wcscmp(strFrom, TEXT("Delta")) == 0 && wcscmp(strTo, TEXT("Delta")) == 0 ) { whatOp = 2; }
					if (wcscmp(strFrom, TEXT("Wye"))   == 0 && wcscmp(strTo, TEXT("Delta")) == 0 ) { whatOp = 3; }
					if (wcscmp(strFrom, TEXT("Wye"))   == 0 && wcscmp(strTo, TEXT("Wye"))   == 0 ) { whatOp = 4; }
					LPTSTR sError;
          // Get our entered values
          GetDlgItemText(hDlg, IDC_EDIT_EP, strInEP, 15);
          GetDlgItemText(hDlg, IDC_EDIT_ES, strInES, 15);
          GetDlgItemText(hDlg, IDC_EDIT_N,  strInN,  15);
					// Check for illegal entries and abort if any found
					if (!validateInput(strInEP)) { 
						MessageBox(hDlg, TEXT("There is a problem with the Primary Voltage you entered.\n\nPlease check to be sure you only used the characters 0-9 and no more than one decimal point."), TEXT("Input Error"), MB_OK); 
						SetFocus(GetDlgItem(hDlg, IDC_EDIT_EP));
						break;
					}
					if (!validateInput(strInES)) { 
						MessageBox(hDlg, TEXT("There is a problem with the Secondary Voltage you entered.\n\nPlease check to be sure you only used the characters 0-9 and no more than one decimal point."), TEXT("Input Error"), MB_OK); 
						SetFocus(GetDlgItem(hDlg, IDC_EDIT_ES));
						break;
					}
					if (!validateInput(strInN)) { 
						MessageBox(hDlg, TEXT("There is a problem with the Turns Ratio you entered.\n\nPlease check to be sure you only used the characters 0-9 and no more than one decimal point."), TEXT("Input Error"), MB_OK); 
						SetFocus(GetDlgItem(hDlg, IDC_EDIT_N));
						break;
					}
          // Assume an invalid entry to begin with
          whatOperation = 0;
          // Determine which operation to perform
          if (wcscmp(strInEP, TEXT("")) != 0 && 
              wcscmp(strInES, TEXT("")) != 0 && 
              wcscmp(strInN,  TEXT("")) == 0) {
                whatOperation = 1; 
          }
          if (wcscmp(strInEP, TEXT("")) == 0 && 
              wcscmp(strInES, TEXT("")) != 0 && 
              wcscmp(strInN,  TEXT("")) != 0) { 
                whatOperation = 2; 
          }
          if (wcscmp(strInEP, TEXT("")) != 0 && 
              wcscmp(strInES, TEXT("")) == 0 && 
              wcscmp(strInN,  TEXT("")) != 0) {
                whatOperation = 3; 
          }
          // Perform the proper operation and show the results, or pop error
          switch (whatOperation) {
            case 1: // Known: EP+ES, Calculate N
              // Get the two known values
              known1 = wcstod(strInEP, &sError);
              known2 = wcstod(strInES, &sError);
              // Do the actual calculations
							if (whatOp == 1) { // Delta-Wye
								results = (1/3) * (known2 / known1) * sqrt(3);
							} else if (whatOp == 2) { // Delta-Delta
								results = known2 / known1;
							} else if (whatOp == 3) { // Wye-Delta
								results = (known2 / known1) * sqrt(3);
							} else { // Wye-Wye
								results = known2 / known1;
							}
              // Copy the results to strings formatted properly
              swprintf(strResults, TEXT("%.6f"), results);
              // Set the edit boxes to the answers
              SetDlgItemText(hDlg, IDC_EDIT_N, strResults);
							SHSipPreference(hWnd, SIP_DOWN);
            break;
            case 2: // Known: ES+N, Calculate EP
              // Get the two known values
              known1 = wcstod(strInES, &sError);
              known2 = wcstod(strInN,  &sError);
              // Do the actual calculations
							if (whatOp == 1) { // Delta-Wye
								results = (1/3) * (known1 / known2) * sqrt(3);
							} else if (whatOp == 2) { // Delta-Delta
								results = known1 / known2;
							} else if (whatOp == 3) { // Wye-Delta
								results = (known1 / known2) * sqrt(3);
							} else { // Wye-Wye
								results = known1 / known2;
							}
              // Copy the results to strings formatted properly
              swprintf(strResults, TEXT("%.6f"), results);
              // Set the edit boxes to the answers
              SetDlgItemText(hDlg, IDC_EDIT_EP, strResults);
							SHSipPreference(hWnd, SIP_DOWN);
            break;
            case 3: // Known: EP+N, Calculate ES
              // Get the two known values
              known1 = wcstod(strInEP, &sError);
              known2 = wcstod(strInN,  &sError);
              // Do the actual calculations
							if (whatOp == 1) { // Delta-Wye
								results = known1 * known2 * sqrt(3);
							} else if (whatOp == 2) { // Delta-Delta
								results = known1 * known2;
							} else if (whatOp == 3) { // Wye-Delta
								results = (known1 * known2) / sqrt(3);
							} else { // Wye-Wye
								results = known1 * known2;
							}
              // Copy the results to strings formatted properly
              swprintf(strResults, TEXT("%.6f"), results);
              // Set the edit boxes to the answers
              SetDlgItemText(hDlg, IDC_EDIT_ES, strResults);
							SHSipPreference(hWnd, SIP_DOWN);
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