
LRESULT CALLBACK ReactanceInductive(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {

	switch (message) {

		case WM_INITDIALOG: {
			SHINITDLGINFO shidi;
			shidi.dwMask	= SHIDIM_FLAGS;
 		  shidi.dwFlags = SHIDIF_SIZEDLGFULLSCREEN;
			shidi.hDlg		= hDlg;
			SHInitDialog(&shidi);
			// Limit edit controls to 8 characters
			SendMessage(GetDlgItem(hDlg, IDC_EDIT_F), EM_SETLIMITTEXT, (WPARAM)8, 0);
			SendMessage(GetDlgItem(hDlg, IDC_EDIT_L), EM_SETLIMITTEXT, (WPARAM)8, 0);
			SendMessage(GetDlgItem(hDlg, IDC_EDIT_X), EM_SETLIMITTEXT, (WPARAM)8, 0);
			return true;
		break; }

		case WM_COMMAND: {
			if (LOWORD(wParam) == IDOK) {
				ShowWindow(hWndCurrentScreen, SW_HIDE);
				SHSipPreference(hWnd, SIP_DOWN);
				return true;
			}

			if (HIWORD(wParam) == EN_SETFOCUS) {
				SHSipPreference(hWnd, SIP_UP);
			}

      int wmId    = LOWORD(wParam); 
			int wmEvent = HIWORD(wParam); 
 
      switch (wmId) {	

			  case IDC_CLEAR: {
					SetDlgItemText(hDlg, IDC_EDIT_F, TEXT(""));
          SetDlgItemText(hDlg, IDC_EDIT_L, TEXT(""));
          SetDlgItemText(hDlg, IDC_EDIT_X, TEXT(""));
				break; }

        case IDC_CALCULATE: {  
					TCHAR  strInF[16]			= TEXT("");
					TCHAR  strInL[16]			= TEXT("");
					TCHAR  strInX[16]			= TEXT("");
					TCHAR  strResults[16] = TEXT("");
					double results				= 0;
					double known1					= 0;
					double known2					= 0;
					int		 whatOperation	= 0;
					LPTSTR sError;
          // Get our entered values
          GetDlgItemText(hDlg, IDC_EDIT_F, strInF, 15);
          GetDlgItemText(hDlg, IDC_EDIT_L, strInL, 15);
          GetDlgItemText(hDlg, IDC_EDIT_X, strInX, 15);
					// Check for illegal entries and abort if any found
					if (!validateInput(strInF)) { 
						MessageBox(hDlg, TEXT("There is a problem with the Frequency you entered.\n\nPlease check to be sure you only used the characters 0-9 and no more than one decimal point."), TEXT("Input Error"), MB_OK); 
						SetFocus(GetDlgItem(hDlg, IDC_EDIT_F));
						break;
					}
					if (!validateInput(strInL)) { 
						MessageBox(hDlg, TEXT("There is a problem with the Inductance you entered.\n\nPlease check to be sure you only used the characters 0-9 and no more than one decimal point."), TEXT("Input Error"), MB_OK); 
						SetFocus(GetDlgItem(hDlg, IDC_EDIT_L));
						break;
					}
					if (!validateInput(strInX)) { 
						MessageBox(hDlg, TEXT("There is a problem with the Reactance you entered.\n\nPlease check to be sure you only used the characters 0-9 and no more than one decimal point."), TEXT("Input Error"), MB_OK); 
						SetFocus(GetDlgItem(hDlg, IDC_EDIT_X));
						break;
					}
          // Assume an invalid entry to begin with
          whatOperation = 0;
          // Determine which operation to perform
          if (wcscmp(strInF, TEXT("")) != 0 && 
              wcscmp(strInL, TEXT("")) != 0 && 
              wcscmp(strInX, TEXT("")) == 0) {
                whatOperation = 1; 
          }
          if (wcscmp(strInF, TEXT("")) == 0 && 
              wcscmp(strInL, TEXT("")) != 0 && 
              wcscmp(strInX, TEXT("")) != 0) { 
                whatOperation = 2; 
          }
          if (wcscmp(strInF, TEXT("")) != 0 && 
              wcscmp(strInL, TEXT("")) == 0 && 
              wcscmp(strInX, TEXT("")) != 0) {
                whatOperation = 3; 
          }
          // Perform the proper operation and show the results, or pop error
          switch (whatOperation) {
            case 1: // Known: F+L, Calculate X
              // Get the two known values
              known1 = wcstod(strInF, &sError);
              known2 = wcstod(strInL, &sError);
              // Do the actual calculations
              results = 2 * Pi * known1 * known2;
              // Copy the results to strings formatted properly
              swprintf(strResults, TEXT("%.6f"), results);
              // Set the edit boxes to the answers
              SetDlgItemText(hDlg, IDC_EDIT_X, strResults);
              break;
            case 2: // Known: L+X, Calculate F
              // Get the two known values
              known1 = wcstod(strInL, &sError);
              known2 = wcstod(strInX, &sError);
              // Do the actual calculations
              results = 1 / (2 * Pi * known1 * known2);
              // Copy the results to strings formatted properly
              swprintf(strResults, TEXT("%.6f"), results);
              // Set the edit boxes to the answers
              SetDlgItemText(hDlg, IDC_EDIT_F, strResults);
              break;
            case 3: // Known: F+X, Calculate L
              // Get the two known values
              known1 = wcstod(strInF, &sError);
              known2 = wcstod(strInX, &sError);
              // Do the actual calculations
              results = 1 / (2 * Pi * known1 * known2);
              // Copy the results to strings formatted properly
              swprintf(strResults, TEXT("%.6f"), results);
              // Set the edit boxes to the answers
              SetDlgItemText(hDlg, IDC_EDIT_L, strResults);
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