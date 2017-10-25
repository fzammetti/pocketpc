
LRESULT CALLBACK DCOhmsLaw(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {

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
			SendMessage(GetDlgItem(hDlg, IDC_EDIT_I), EM_SETLIMITTEXT, (WPARAM)8, 0);
			SendMessage(GetDlgItem(hDlg, IDC_EDIT_E), EM_SETLIMITTEXT, (WPARAM)8, 0);
			SendMessage(GetDlgItem(hDlg, IDC_EDIT_R), EM_SETLIMITTEXT, (WPARAM)8, 0);
			SendMessage(GetDlgItem(hDlg, IDC_EDIT_P), EM_SETLIMITTEXT, (WPARAM)8, 0);
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
					SetDlgItemText(hDlg, IDC_EDIT_I, TEXT(""));
          SetDlgItemText(hDlg, IDC_EDIT_E, TEXT(""));
          SetDlgItemText(hDlg, IDC_EDIT_R, TEXT(""));
          SetDlgItemText(hDlg, IDC_EDIT_P, TEXT(""));
				break; }

        case IDC_CALCULATE: {   
					TCHAR  strInI[16]			 = TEXT("");
					TCHAR  strInE[16]			 = TEXT("");
					TCHAR  strInR[16]			 = TEXT("");
					TCHAR  strInP[16]			 = TEXT("");
					TCHAR  strResults1[16] = TEXT("");
					TCHAR	 strResults2[16] = TEXT("");
					double results1				 = 0;
					double results2				 = 0;
					double known1					 = 0;
					double known2					 = 0;
					int		 whatOperation	 = 0;
					LPTSTR sError;
          // Get our entered values
          GetDlgItemText(hDlg, IDC_EDIT_I, strInI, 15);
          GetDlgItemText(hDlg, IDC_EDIT_E, strInE, 15);
          GetDlgItemText(hDlg, IDC_EDIT_R, strInR, 15);
          GetDlgItemText(hDlg, IDC_EDIT_P, strInP, 15);
					// Check for illegal entries and abort if any found
					if (!validateInput(strInI)) { 
						MessageBox(hDlg, TEXT("There is a problem with the Current you entered.\n\nPlease check to be sure you only used the characters 0-9 and no more than one decimal point."), TEXT("Input Error"), MB_OK); 
						SetFocus(GetDlgItem(hDlg, IDC_EDIT_I));
						break;
					}
					if (wcscmp(strInI, TEXT("0")) == 0) { 
						MessageBox(hDlg, TEXT("There is a problem with the Current you entered.\n\nYou cannot enter zero in this field."), TEXT("Input Error"), MB_OK); 
						SetFocus(GetDlgItem(hDlg, IDC_EDIT_I));
						break;
					}
					if (!validateInput(strInE)) { 
						MessageBox(hDlg, TEXT("There is a problem with the Voltage you entered.\n\nPlease check to be sure you only used the characters 0-9 and no more than one decimal point."), TEXT("Input Error"), MB_OK); 
						SetFocus(GetDlgItem(hDlg, IDC_EDIT_E));
						break;
					}
					if (wcscmp(strInE, TEXT("0")) == 0) { 
						MessageBox(hDlg, TEXT("There is a problem with the Voltage you entered.\n\nYou cannot enter zero in this field."), TEXT("Input Error"), MB_OK); 
						SetFocus(GetDlgItem(hDlg, IDC_EDIT_E));
						break;
					}
					if (!validateInput(strInR)) { 
						MessageBox(hDlg, TEXT("There is a problem with the Resistance you entered.\n\nPlease check to be sure you only used the characters 0-9 and no more than one decimal point."), TEXT("Input Error"), MB_OK); 
						SetFocus(GetDlgItem(hDlg, IDC_EDIT_R));
						break;
					}
					if (wcscmp(strInR, TEXT("0")) == 0) { 
						MessageBox(hDlg, TEXT("There is a problem with the Resistance you entered.\n\nYou cannot enter zero in this field."), TEXT("Input Error"), MB_OK); 
						SetFocus(GetDlgItem(hDlg, IDC_EDIT_R));
						break;
					}
					if (!validateInput(strInP)) { 
						MessageBox(hDlg, TEXT("There is a problem with the Power you entered.\n\nPlease check to be sure you only used the characters 0-9 and no more than one decimal point."), TEXT("Input Error"), MB_OK); 
						SetFocus(GetDlgItem(hDlg, IDC_EDIT_P));
						break;
					}
					if (wcscmp(strInP, TEXT("0")) == 0) { 
						MessageBox(hDlg, TEXT("There is a problem with the Power you entered.\n\nYou cannot enter zero in this field."), TEXT("Input Error"), MB_OK); 
						SetFocus(GetDlgItem(hDlg, IDC_EDIT_P));
						break;
					}
          whatOperation = 0;
          // Determine which operation to perform
          if (wcscmp(strInI, TEXT("")) != 0 && 
              wcscmp(strInE, TEXT("")) != 0 && 
              wcscmp(strInR, TEXT("")) == 0 &&
              wcscmp(strInP, TEXT("")) == 0) { 
                whatOperation = 1; 
          }
          if (wcscmp(strInI, TEXT("")) == 0 && 
              wcscmp(strInE, TEXT("")) != 0 && 
              wcscmp(strInR, TEXT("")) == 0 &&
              wcscmp(strInP, TEXT("")) != 0) { 
                whatOperation = 2; 
          }
          if (wcscmp(strInI, TEXT("")) == 0 && 
              wcscmp(strInE, TEXT("")) != 0 && 
              wcscmp(strInR, TEXT("")) != 0 &&
              wcscmp(strInP, TEXT("")) == 0) { 
                whatOperation = 3; 
          }
          if (wcscmp(strInI, TEXT("")) != 0 && 
              wcscmp(strInE, TEXT("")) == 0 && 
              wcscmp(strInR, TEXT("")) == 0 &&
              wcscmp(strInP, TEXT("")) != 0) { 
                whatOperation = 4; 
          }
          if (wcscmp(strInI, TEXT("")) != 0 && 
              wcscmp(strInE, TEXT("")) == 0 && 
              wcscmp(strInR, TEXT("")) != 0 &&
              wcscmp(strInP, TEXT("")) == 0) { 
                whatOperation = 5; 
          }
          if (wcscmp(strInI, TEXT("")) == 0 && 
              wcscmp(strInE, TEXT("")) == 0 && 
              wcscmp(strInR, TEXT("")) != 0 &&
              wcscmp(strInP, TEXT("")) != 0) { 
                whatOperation = 6; 
          }
          // Perform the proper operation and show the results, or pop error
          switch (whatOperation) {
            case 1: { // Known: E+I, Calculate P+R
              // Get the two known values
              known1 = wcstod(strInE, &sError);
              known2 = wcstod(strInI, &sError);
              // Do the actual calculations
              results1 = known1 * known2;
              results2 = known1 / known2;
              // Copy the results to strings formatted properly
              swprintf(strResults1, TEXT("%.6f"), results1);
              swprintf(strResults2, TEXT("%.6f"), results2);
              // Set the edit boxes to the answers
              SetDlgItemText(hDlg, IDC_EDIT_P, strResults1);
              SetDlgItemText(hDlg, IDC_EDIT_R, strResults2);
						break; }
            case 2: { // Known: E+P, Calculate I+R
              // Get the two known values
              known1 = wcstod(strInE, &sError);
              known2 = wcstod(strInP, &sError);
              // Do the actual calculations
              results1 = known2 / known1;
              results2 = (known1 * known1) / known2;
              // Copy the results to strings formatted properly
              swprintf(strResults1, TEXT("%.6f"), results1);
              swprintf(strResults2, TEXT("%.6f"), results2);
              // Set the edit boxes to the answers
              SetDlgItemText(hDlg, IDC_EDIT_I, strResults1);
              SetDlgItemText(hDlg, IDC_EDIT_R, strResults2);
						break; }
            case 3: { // Known: E+R, Calculate I+P
              // Get the two known values
              known1 = wcstod(strInE, &sError);
              known2 = wcstod(strInR, &sError);
              // Do the actual calculations
              results1 = known1 / known2;
              results2 = (known1 * known1) / known2;
              // Copy the results to strings formatted properly
              swprintf(strResults1, TEXT("%.6f"), results1);
              swprintf(strResults2, TEXT("%.6f"), results2);
              // Set the edit boxes to the answers
              SetDlgItemText(hDlg, IDC_EDIT_I, strResults1);
              SetDlgItemText(hDlg, IDC_EDIT_P, strResults2);
						break; }
            case 4: { // Known: I+P, Calculate E+R
              // Get the two known values
              known1 = wcstod(strInI, &sError);
              known2 = wcstod(strInP, &sError);
              // Do the actual calculations
              results1 = known2 / known1;
              results2 = known2 / (known1 * known1);
              // Copy the results to strings formatted properly
              swprintf(strResults1, TEXT("%.6f"), results1);
              swprintf(strResults2, TEXT("%.6f"), results2);
              // Set the edit boxes to the answers
              SetDlgItemText(hDlg, IDC_EDIT_E, strResults1);
              SetDlgItemText(hDlg, IDC_EDIT_R, strResults2);
						break; }
            case 5: { // Known: I+R, Calculate E+P
              // Get the two known values
              known1 = wcstod(strInI, &sError);
              known2 = wcstod(strInR, &sError);
              // Do the actual calculations
              results1 = known1 * known2;
              results2 = known2 * (known1 * known1);
              // Copy the results to strings formatted properly
              swprintf(strResults1, TEXT("%.6f"), results1);
              swprintf(strResults2, TEXT("%.6f"), results2);
              // Set the edit boxes to the answers
              SetDlgItemText(hDlg, IDC_EDIT_E, strResults1);
              SetDlgItemText(hDlg, IDC_EDIT_P, strResults2);
						break; }
            case 6: { // Known: P+R, Calculate E+I
              // Get the two known values
              known1 = wcstod(strInP, &sError);
              known2 = wcstod(strInR, &sError);
              // Do the actual calculations
              results1 = sqrt(known1 * known2);
              results2 = sqrt(known1 / known2);
              // Copy the results to strings formatted properly
              swprintf(strResults1, TEXT("%.6f"), results1);
              swprintf(strResults2, TEXT("%.6f"), results2);
              // Set the edit boxes to the answers
              SetDlgItemText(hDlg, IDC_EDIT_E, strResults1);
              SetDlgItemText(hDlg, IDC_EDIT_I, strResults2);
						break; }
            default: {
              // Not a valid operation
              MessageBox(hDlg, TEXT("You must enter two and only two known values"), TEXT("Error"), MB_OK); 
						break; }
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