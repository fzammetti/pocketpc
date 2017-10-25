
LRESULT CALLBACK RCICalcCapacitance(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {

	HWND hWndLB = GetDlgItem(hDlg, IDC_VALUES);

	switch (message) {

		case WM_INITDIALOG: {
			SHINITDLGINFO shidi;
			shidi.dwMask	= SHIDIM_FLAGS;
 		  shidi.dwFlags = SHIDIF_SIZEDLGFULLSCREEN;
			shidi.hDlg		= hDlg;
			SHInitDialog(&shidi);
			SendMessage(GetDlgItem(hDlg, IDC_SERIAL), BM_SETCHECK, (WPARAM)BST_CHECKED, 0); // Check Serial
			// Limit edit controls to 8 characters
			SendMessage(GetDlgItem(hDlg, IDC_NEW_VALUE), EM_SETLIMITTEXT, (WPARAM)8, 0);
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

			  case IDC_ADD: {
					// Get the new value entered, if any
					LPTSTR sError;
					TCHAR szNewValue[16] = TEXT("");
          GetDlgItemText(hDlg, IDC_NEW_VALUE, szNewValue, 15);
					// Check for an illegal entry and abort if one is found
					if (!validateInput(szNewValue)) { 
						MessageBox(hDlg, TEXT("There is a problem with the value you entered.\n\nPlease check to be sure you only used the characters 0-9 and no more than one decimal point."), TEXT("Input Error"), MB_OK); 
						SetFocus(GetDlgItem(hDlg, IDC_NEW_VALUE));
						break;
					}
          if (wcscmp(szNewValue, TEXT("")) != 0) {											// If something was entered... 
						if (wcstod(szNewValue, &sError) > 0) {											// And it's not zero...
							SendMessage(hWndLB, LB_ADDSTRING, 0, (LPARAM)szNewValue); // Add it...
							SetDlgItemText(hDlg, IDC_NEW_VALUE, TEXT(""));					  // And clear the edit box
						}
          }
					SetFocus(GetDlgItem(hDlg, IDC_NEW_VALUE));
				break; }

			  case IDC_REMOVE: {
					int selIdx = SendMessage(hWndLB, LB_GETCURSEL, 0, 0);			 // Get index of selected item
					if (selIdx != LB_ERR) {																		 // If an item was selected...
						SendMessage(hWndLB, LB_DELETESTRING, (WPARAM)selIdx, 0); // Delete it
					}
				break; }

			  case IDC_CLEAR: {
					SetDlgItemText(hDlg, IDC_NEW_VALUE, TEXT("")); // Clear new value edit box
					SetDlgItemText(hDlg, IDC_RESULTS, TEXT(""));   // Clear results
					SendMessage(hWndLB, LB_RESETCONTENT, 0, 0);		 // Clear listbox
				break; }

        case IDC_CALCULATE: {  
					// Pop an error if at least two values are not in the listbox
					int numVals = SendMessage(hWndLB, LB_GETCOUNT, 0, 0);
					if (numVals < 2) {
						MessageBox(hDlg, TEXT("At least two values must be entered to calculate a result."), TEXT("Error"), MB_OK);
						break;
					}
					// Are we doing Serial or Parallel?
					int whatOp = 0;
					if (SendMessage(GetDlgItem(hDlg, IDC_SERIAL), BM_GETCHECK, 0, 0) == BST_CHECKED) {
						whatOp = 1;
					} else {
						whatOp = 2;
					}
					// Get all our values into an array
					double myVals[256];
					LPTSTR sError;
					TCHAR	 szNextVal[16] = TEXT("");
					TCHAR	 szResults[16] = TEXT("");
					double results = 0;
					int		 i			 = 0;
					for (i = 0; i < numVals; i++) {
						myVals[i] = SendMessage(hWndLB, LB_GETTEXT, (WPARAM)i, (WPARAM)&szNextVal);
						myVals[i] = wcstod(szNextVal, &sError);
					}
					// Perform the actual calculations
					double tempResults = 0;
					if (whatOp == 1) { // Serial
						for (i = 0; i < numVals; i++) {
							tempResults = tempResults + (1 / myVals[i]); 
						}
						results = 1 / tempResults;
					} else {           // Parallel
						for (i = 0; i < numVals; i++) {
							results = results + myVals[i];
						}
					}
					// Display the result
          swprintf(szResults, TEXT("%.6f"), results);
					wcscat(szResults, TEXT(" Farads"));
          SetDlgItemText(hDlg, IDC_RESULTS, szResults);
			  break; }

			}

		break; }

		default: {
			return DefWindowProc(hWnd, message, wParam, lParam);
    break; }

	}

  return FALSE;

}