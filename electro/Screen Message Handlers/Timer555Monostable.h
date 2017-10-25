
LRESULT CALLBACK Timer555Monostable(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {

	HWND hWndLB = GetDlgItem(hDlg, IDC_VALUES);

	switch (message) {

		case WM_INITDIALOG: {
			SHINITDLGINFO shidi;
			shidi.dwMask	= SHIDIM_FLAGS;
 		  shidi.dwFlags = SHIDIF_SIZEDLGFULLSCREEN;
			shidi.hDlg		= hDlg;
			SHInitDialog(&shidi);
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
					SetDlgItemText(hDlg, IDC_EDIT_RA, TEXT(""));
          SetDlgItemText(hDlg, IDC_EDIT_C,	TEXT(""));
          SetDlgItemText(hDlg, IDC_EDIT_T,	TEXT(""));
				break; }

        case IDC_CALCULATE: {   
					TCHAR  strInRa[16]		 = TEXT("");
					TCHAR  strInC[16]			 = TEXT("");
					TCHAR  strInT[16]			 = TEXT("");
					TCHAR  strResult[16]   = TEXT("");
					double results				 = 0;
					double known1					 = 0;
					double known2					 = 0;
					int		 whatOperation	 = 0;
					LPTSTR sError;
          // Get our entered values
          GetDlgItemText(hDlg, IDC_EDIT_RA, strInRa, 15);
          GetDlgItemText(hDlg, IDC_EDIT_C,	strInC,  15);
          GetDlgItemText(hDlg, IDC_EDIT_T,	strInT,  15);
					// Check for illegal entries and abort if any found
					if (!validateInput(strInRa)) { 
						MessageBox(hDlg, TEXT("There is a problem with the Ra value you entered.\n\nPlease check to be sure you only used the characters 0-9 and no more than one decimal point."), TEXT("Input Error"), MB_OK); 
						SetFocus(GetDlgItem(hDlg, IDC_EDIT_RA));
						break;
					}
					if (wcscmp(strInRa, TEXT("0")) == 0) { 
						MessageBox(hDlg, TEXT("There is a problem with the Ra value you entered.\n\nYou cannot enter zero in this field."), TEXT("Input Error"), MB_OK); 
						SetFocus(GetDlgItem(hDlg, IDC_EDIT_RA));
						break;
					}
          whatOperation = 0;
          // Determine which operation to perform
          if (wcscmp(strInRa, TEXT("")) != 0 && 
              wcscmp(strInC,  TEXT("")) != 0 && 
              wcscmp(strInT,  TEXT("")) == 0) { 
                whatOperation = 1; 
          }
          if (wcscmp(strInRa, TEXT("")) != 0 && 
              wcscmp(strInC,  TEXT("")) == 0 && 
              wcscmp(strInT,  TEXT("")) != 0) {
                whatOperation = 2; 
          }
          if (wcscmp(strInRa, TEXT("")) == 0 && 
              wcscmp(strInC,  TEXT("")) != 0 && 
              wcscmp(strInT,  TEXT("")) != 0) {
                whatOperation = 3; 
          }
          // Perform the proper operation and show the results, or pop error
          switch (whatOperation) {
            case 1: { // Known: Ra+C, Calculate T
              // Get the two known values
              known1 = wcstod(strInRa, &sError);
              known2 = wcstod(strInC,  &sError);
              // Do the actual calculations
              results = 1.1 * known1 * known2;
              // Copy the result to a string formatted properly
              swprintf(strResult, TEXT("%.6f"), results);
              // Set the edit box to the answer
              SetDlgItemText(hDlg, IDC_EDIT_T, strResult);
						break; }
            case 2: { // Known: Ra+T, Calculate C
              // Get the two known values
              known1 = wcstod(strInRa, &sError);
              known2 = wcstod(strInT,  &sError);
              // Do the actual calculations
              results = known2 / known1 * .90909090909090909091;
              // Copy the result to a string formatted properly
              swprintf(strResult, TEXT("%.6f"), results);
              // Set the edit box to the answer
              SetDlgItemText(hDlg, IDC_EDIT_C, strResult);
						break; }
            case 3: { // Known: C+T, Calculate Ra
              // Get the two known values
              known1 = wcstod(strInC, &sError);
              known2 = wcstod(strInT, &sError);
              // Do the actual calculations
              results = known2 / known1 * .90909090909090909091;
              // Copy the result to a string formatted properly
              swprintf(strResult, TEXT("%.6f"), results);
              // Set the edit box to the answer
              SetDlgItemText(hDlg, IDC_EDIT_RA, strResult);
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