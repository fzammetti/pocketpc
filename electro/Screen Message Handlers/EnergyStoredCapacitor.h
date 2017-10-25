
LRESULT CALLBACK EnergyStoredCapacitor(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {

	switch (message) {

		case WM_INITDIALOG: {
			SHINITDLGINFO shidi;
			shidi.dwMask	= SHIDIM_FLAGS;
 		  shidi.dwFlags = SHIDIF_SIZEDLGFULLSCREEN;
			shidi.hDlg		= hDlg;
			SHInitDialog(&shidi);
			// Limit edit controls to 8 characters
			SendMessage(GetDlgItem(hDlg, IDC_EDIT_C), EM_SETLIMITTEXT, (WPARAM)8, 0);
			SendMessage(GetDlgItem(hDlg, IDC_EDIT_E), EM_SETLIMITTEXT, (WPARAM)8, 0);
			SendMessage(GetDlgItem(hDlg, IDC_EDIT_W), EM_SETLIMITTEXT, (WPARAM)8, 0);
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
					SetDlgItemText(hDlg, IDC_EDIT_C, TEXT(""));
          SetDlgItemText(hDlg, IDC_EDIT_E, TEXT(""));
          SetDlgItemText(hDlg, IDC_EDIT_W, TEXT(""));
				break; }

        case IDC_CALCULATE: {  
					TCHAR  strInC[16]			= TEXT("");
					TCHAR  strInE[16]			= TEXT("");
					TCHAR  strInW[16]			= TEXT("");
					TCHAR  strResults[16] = TEXT("");
					double results				= 0;
					double known1					= 0;
					double known2					= 0;
					int		 whatOperation	= 0;
					LPTSTR sError;
          // Get our entered values
          GetDlgItemText(hDlg, IDC_EDIT_C, strInC, 15);
          GetDlgItemText(hDlg, IDC_EDIT_E, strInE, 15);
          GetDlgItemText(hDlg, IDC_EDIT_W, strInW, 15);
					// Check for illegal entries and abort if any found
					if (!validateInput(strInC)) { 
						MessageBox(hDlg, TEXT("There is a problem with the Capacitance you entered.\n\nPlease check to be sure you only used the characters 0-9 and no more than one decimal point."), TEXT("Input Error"), MB_OK); 
						SetFocus(GetDlgItem(hDlg, IDC_EDIT_C));
						break;
					}
					if (!validateInput(strInE)) { 
						MessageBox(hDlg, TEXT("There is a problem with the Voltage you entered.\n\nPlease check to be sure you only used the characters 0-9 and no more than one decimal point."), TEXT("Input Error"), MB_OK); 
						SetFocus(GetDlgItem(hDlg, IDC_EDIT_E));
						break;
					}
					if (!validateInput(strInW)) { 
						MessageBox(hDlg, TEXT("There is a problem with the Energy you entered.\n\nPlease check to be sure you only used the characters 0-9 and no more than one decimal point."), TEXT("Input Error"), MB_OK); 
						SetFocus(GetDlgItem(hDlg, IDC_EDIT_W));
						break;
					}
          // Assume an invalid entry to begin with
          whatOperation = 0;
          // Determine which operation to perform
          if (wcscmp(strInC, TEXT("")) != 0 && 
              wcscmp(strInE, TEXT("")) != 0 && 
              wcscmp(strInW, TEXT("")) == 0) {
                whatOperation = 1; 
          }
          if (wcscmp(strInC, TEXT("")) == 0 && 
              wcscmp(strInE, TEXT("")) != 0 && 
              wcscmp(strInW, TEXT("")) != 0) { 
                whatOperation = 2; 
          }
          if (wcscmp(strInC, TEXT("")) != 0 && 
              wcscmp(strInE, TEXT("")) == 0 && 
              wcscmp(strInW, TEXT("")) != 0) {
                whatOperation = 3; 
          }
          // Perform the proper operation and show the results, or pop error
          switch (whatOperation) {
            case 1: // Known: C+E, Calculate W
              // Get the two known values
              known1 = wcstod(strInC, &sError);
              known2 = wcstod(strInE, &sError);
              // Do the actual calculations
              results = ((known2 * known2) * known1) / 2;
              // Copy the results to strings formatted properly
              swprintf(strResults, TEXT("%.6f"), results);
              // Set the edit boxes to the answers
              SetDlgItemText(hDlg, IDC_EDIT_W, strResults);
              break;
            case 2: // Known: E+W, Calculate C
              // Get the two known values
              known1 = wcstod(strInE, &sError);
              known2 = wcstod(strInW, &sError);
              // Do the actual calculations
              results = (2 * known2) / (known1 * known1);
              // Copy the results to strings formatted properly
              swprintf(strResults, TEXT("%.6f"), results);
              // Set the edit boxes to the answers
              SetDlgItemText(hDlg, IDC_EDIT_C, strResults);
              break;
            case 3: // Known: C+W, Calculate E
              // Get the two known values
              known1 = wcstod(strInC, &sError);
              known2 = wcstod(strInW, &sError);
              // Do the actual calculations
              results = sqrt((2 * known2) / known1);
              // Copy the results to strings formatted properly
              swprintf(strResults, TEXT("%.6f"), results);
              // Set the edit boxes to the answers
              SetDlgItemText(hDlg, IDC_EDIT_E, strResults);
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