
LRESULT CALLBACK Impedance(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {

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
			SendMessage(GetDlgItem(hDlg, IDC_SERIAL), BM_SETCHECK, (WPARAM)BST_CHECKED, 0); // Check Serial
			// Limit edit controls to 8 characters
			SendMessage(GetDlgItem(hDlg, IDC_EDIT_R), EM_SETLIMITTEXT, (WPARAM)8, 0);
			SendMessage(GetDlgItem(hDlg, IDC_EDIT_X), EM_SETLIMITTEXT, (WPARAM)8, 0);
			SendMessage(GetDlgItem(hDlg, IDC_EDIT_Z), EM_SETLIMITTEXT, (WPARAM)8, 0);
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
					SetDlgItemText(hDlg, IDC_EDIT_R, TEXT(""));
					SetDlgItemText(hDlg, IDC_EDIT_X, TEXT(""));
					SetDlgItemText(hDlg, IDC_EDIT_Z, TEXT(""));
				break; }

        case IDC_CALCULATE: {
					TCHAR  strInR[16]			= TEXT("");
					TCHAR  strInX[16]			= TEXT("");
					TCHAR  strInZ[16]			= TEXT("");
					TCHAR  strResults[16] = TEXT("");
					double results				= 0;
					double known1					= 0;
					double known2					= 0;
					int		 whatOperation	= 0;
					LPTSTR sError;
          // Get our entered values
          GetDlgItemText(hDlg, IDC_EDIT_R, strInR, 15);
          GetDlgItemText(hDlg, IDC_EDIT_X, strInX, 15);
          GetDlgItemText(hDlg, IDC_EDIT_Z, strInZ, 15);
					// Check for illegal entries and abort if any found
					if (!validateInput(strInR)) { 
						MessageBox(hDlg, TEXT("There is a problem with the Resistance you entered.\n\nPlease check to be sure you only used the characters 0-9 and no more than one decimal point."), TEXT("Input Error"), MB_OK); 
						SetFocus(GetDlgItem(hDlg, IDC_EDIT_R));
						break;
					}
					if (!validateInput(strInX)) { 
						MessageBox(hDlg, TEXT("There is a problem with the Reactance you entered.\n\nPlease check to be sure you only used the characters 0-9 and no more than one decimal point."), TEXT("Input Error"), MB_OK); 
						SetFocus(GetDlgItem(hDlg, IDC_EDIT_X));
						break;
					}
					if (!validateInput(strInZ)) { 
						MessageBox(hDlg, TEXT("There is a problem with the Impedance you entered.\n\nPlease check to be sure you only used the characters 0-9 and no more than one decimal point."), TEXT("Input Error"), MB_OK); 
						SetFocus(GetDlgItem(hDlg, IDC_EDIT_Z));
						break;
					}
					// Are we doing Serial or Parallel?
					int whatOp = 0;
					if (SendMessage(GetDlgItem(hDlg, IDC_SERIAL), BM_GETCHECK, 0, 0) == BST_CHECKED) {
						whatOp = 1;
					} else {
						whatOp = 2;
					}
          // Assume an invalid entry to begin with
          whatOperation = 0;
          // Determine which operation to perform
          if (wcscmp(strInR, TEXT("")) == 0 && 
              wcscmp(strInX, TEXT("")) != 0 && 
              wcscmp(strInZ, TEXT("")) != 0) {
                whatOperation = 1; 
          }
          if (wcscmp(strInR, TEXT("")) != 0 && 
              wcscmp(strInX, TEXT("")) == 0 && 
              wcscmp(strInZ, TEXT("")) != 0) { 
                whatOperation = 2; 
          }
          if (wcscmp(strInR, TEXT("")) != 0 && 
              wcscmp(strInX, TEXT("")) != 0 && 
              wcscmp(strInZ, TEXT("")) == 0) {
                whatOperation = 3; 
          }
          // Perform the proper operation and show the results, or pop error
          switch (whatOperation) {
            case 1: // Known: X+Z, Calculate R
              // Get the two known values
              known1 = wcstod(strInX, &sError);
              known2 = wcstod(strInZ, &sError);
              // Do the actual calculations
							if (whatOp == 1) { // Serial
								results = sqrt((known2 * known2) - (known1 * known1));
							} else { // Parallel
								results = (known2 / sqrt((-1 * (known2 * known2)) + (known1 * known1))) * known1;
							}
              // Copy the results to strings formatted properly
              swprintf(strResults, TEXT("%.6f"), results);
              // Set the edit boxes to the answers
              SetDlgItemText(hDlg, IDC_EDIT_R, strResults);
            break;
            case 2: // Known: R+Z, Calculate X
              // Get the two known values
              known1 = wcstod(strInR, &sError);
              known2 = wcstod(strInZ, &sError);
              // Do the actual calculations
							if (whatOp == 1) { // Serial
								results = sqrt((-1 * (known1 * known1)) + (known2 * known2));
							} else { // Parallel
								results = (known2 / sqrt((-1 * (known2 * known2)) + (known1 * known1))) * known1;
							}
              // Copy the results to strings formatted properly
              swprintf(strResults, TEXT("%.6f"), results);
              // Set the edit boxes to the answers
              SetDlgItemText(hDlg, IDC_EDIT_X, strResults);
            break;
            case 3: // Known: R+X, Calculate Z
              // Get the two known values
              known1 = wcstod(strInR, &sError);
              known2 = wcstod(strInX, &sError);
              // Do the actual calculations
							if (whatOp == 1) { // Serial
								results = sqrt((known1 * known1) + (known2 * known2));
							} else { // Parallel
								results = (known1 * known2) / sqrt((known1 * known1) + (known2 * known2));
							}
              // Copy the results to strings formatted properly
              swprintf(strResults, TEXT("%.6f"), results);
              // Set the edit boxes to the answers
              SetDlgItemText(hDlg, IDC_EDIT_Z, strResults);
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