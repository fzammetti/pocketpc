
LRESULT CALLBACK Timer555Astable(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {

//	HWND hWndLB = GetDlgItem(hDlg, IDC_VALUES);
	static int FromTo = 1;

	switch (message) {

		case WM_INITDIALOG: {
			SHINITDLGINFO shidi;
			shidi.dwMask	= SHIDIM_FLAGS;
 		  shidi.dwFlags = SHIDIF_SIZEDLGFULLSCREEN;
			shidi.hDlg		= hDlg;
			SHInitDialog(&shidi);
			SendMessage(GetDlgItem(hDlg, IDC_EDIT_TH), EM_SETREADONLY, (WPARAM)true,  0);
			SendMessage(GetDlgItem(hDlg, IDC_EDIT_TL), EM_SETREADONLY, (WPARAM)true,  0);
			SendMessage(GetDlgItem(hDlg, IDC_EDIT_F),  EM_SETREADONLY, (WPARAM)true,  0);
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
					SetDlgItemText(hDlg, IDC_EDIT_R1, TEXT(""));
					SetDlgItemText(hDlg, IDC_EDIT_R2, TEXT(""));
					SetDlgItemText(hDlg, IDC_EDIT_C,  TEXT(""));
					SetDlgItemText(hDlg, IDC_EDIT_TH, TEXT(""));
					SetDlgItemText(hDlg, IDC_EDIT_TL, TEXT(""));
					SetDlgItemText(hDlg, IDC_EDIT_F,  TEXT(""));
				break; }

				case IDC_TF_SWAP: {
					if (FromTo == 1) { 
						FromTo = 2; 
						SetDlgItemText(hDlg, IDC_TF_SWAP, TEXT("<--"));
						SendMessage(GetDlgItem(hDlg, IDC_EDIT_R1), EM_SETREADONLY, (WPARAM)true,  0);
						SendMessage(GetDlgItem(hDlg, IDC_EDIT_R2), EM_SETREADONLY, (WPARAM)true,  0);
						SendMessage(GetDlgItem(hDlg, IDC_EDIT_C),  EM_SETREADONLY, (WPARAM)true,  0);
						SendMessage(GetDlgItem(hDlg, IDC_EDIT_TH), EM_SETREADONLY, (WPARAM)false, 0);
						SendMessage(GetDlgItem(hDlg, IDC_EDIT_TL), EM_SETREADONLY, (WPARAM)false, 0);
						SendMessage(GetDlgItem(hDlg, IDC_EDIT_F),  EM_SETREADONLY, (WPARAM)false, 0);
					} else { 
						FromTo = 1; 
						SetDlgItemText(hDlg, IDC_TF_SWAP, TEXT("-->"));
						SendMessage(GetDlgItem(hDlg, IDC_EDIT_R1), EM_SETREADONLY, (WPARAM)false, 0);
						SendMessage(GetDlgItem(hDlg, IDC_EDIT_R2), EM_SETREADONLY, (WPARAM)false, 0);
						SendMessage(GetDlgItem(hDlg, IDC_EDIT_C),  EM_SETREADONLY, (WPARAM)false, 0);
						SendMessage(GetDlgItem(hDlg, IDC_EDIT_TH), EM_SETREADONLY, (WPARAM)true,  0);
						SendMessage(GetDlgItem(hDlg, IDC_EDIT_TL), EM_SETREADONLY, (WPARAM)true,  0);
						SendMessage(GetDlgItem(hDlg, IDC_EDIT_F),  EM_SETREADONLY, (WPARAM)true,  0);
					}
					SetDlgItemText(hDlg, IDC_EDIT_R1, TEXT(""));
					SetDlgItemText(hDlg, IDC_EDIT_R2, TEXT(""));
					SetDlgItemText(hDlg, IDC_EDIT_C,  TEXT(""));
					SetDlgItemText(hDlg, IDC_EDIT_TH, TEXT(""));
					SetDlgItemText(hDlg, IDC_EDIT_TL, TEXT(""));
					SetDlgItemText(hDlg, IDC_EDIT_F,  TEXT(""));
				break; }

				case IDC_CALCULATE: {
					TCHAR  strInR1[16]		= TEXT("");
					TCHAR  strInR2[16]		= TEXT("");
					TCHAR  strInC[16]			= TEXT("");
					TCHAR  strInTh[16]		= TEXT("");
					TCHAR  strInTl[16]		= TEXT("");
					TCHAR  strInF[16]			= TEXT("");
					TCHAR  strResult1[16] = TEXT("");
					TCHAR  strResult2[16] = TEXT("");
					TCHAR  strResult3[16] = TEXT("");
					TCHAR  strFrom[16]    = TEXT("");
					TCHAR  strTo[16]			= TEXT("");
					double result1				= 0;
					double result2				= 0;
					double result3				= 0;
					double known1					= 0;
					double known2					= 0;
					double known3					= 0;
					LPTSTR sError;
          // Get our entered values
          GetDlgItemText(hDlg, IDC_EDIT_R1, strInR1, 15);
          GetDlgItemText(hDlg, IDC_EDIT_R2, strInR2, 15);
          GetDlgItemText(hDlg, IDC_EDIT_C,  strInC,  15);
          GetDlgItemText(hDlg, IDC_EDIT_TH, strInTh, 15);
          GetDlgItemText(hDlg, IDC_EDIT_TL, strInTl, 15);
          GetDlgItemText(hDlg, IDC_EDIT_F,  strInF,  15);
					// Check for illegal entries and abort if any found
					if (!validateInput(strInR1)) { 
						MessageBox(hDlg, TEXT("There is a problem with the R1 value you entered.\n\nPlease check to be sure you only used the characters 0-9 and no more than one decimal point."), TEXT("Input Error"), MB_OK); 
						SetFocus(GetDlgItem(hDlg, IDC_EDIT_R1));
						break;
					}
					if (wcscmp(strInR1, TEXT("0")) == 0) { 
						MessageBox(hDlg, TEXT("There is a problem with the R1 value you entered.\n\nYou cannot enter zero in this field."), TEXT("Input Error"), MB_OK); 
						SetFocus(GetDlgItem(hDlg, IDC_EDIT_R2));
						break;
					}
					if (!validateInput(strInR2)) { 
						MessageBox(hDlg, TEXT("There is a problem with the R2 value you entered.\n\nPlease check to be sure you only used the characters 0-9 and no more than one decimal point."), TEXT("Input Error"), MB_OK); 
						SetFocus(GetDlgItem(hDlg, IDC_EDIT_R2));
						break;
					}
					if (wcscmp(strInR2, TEXT("0")) == 0) { 
						MessageBox(hDlg, TEXT("There is a problem with the R2 value you entered.\n\nYou cannot enter zero in this field."), TEXT("Input Error"), MB_OK); 
						SetFocus(GetDlgItem(hDlg, IDC_EDIT_R2));
						break;
					}
					if (!validateInput(strInC)) { 
						MessageBox(hDlg, TEXT("There is a problem with the C value you entered.\n\nPlease check to be sure you only used the characters 0-9 and no more than one decimal point."), TEXT("Input Error"), MB_OK); 
						SetFocus(GetDlgItem(hDlg, IDC_EDIT_C));
						break;
					}
					if (wcscmp(strInC, TEXT("0")) == 0) { 
						MessageBox(hDlg, TEXT("There is a problem with the C value you entered.\n\nYou cannot enter zero in this field."), TEXT("Input Error"), MB_OK); 
						SetFocus(GetDlgItem(hDlg, IDC_EDIT_C));
						break;
					}
					if (!validateInput(strInTh)) { 
						MessageBox(hDlg, TEXT("There is a problem with the Th value you entered.\n\nPlease check to be sure you only used the characters 0-9 and no more than one decimal point."), TEXT("Input Error"), MB_OK); 
						SetFocus(GetDlgItem(hDlg, IDC_EDIT_TH));
						break;
					}
					if (wcscmp(strInTh, TEXT("0")) == 0) { 
						MessageBox(hDlg, TEXT("There is a problem with the Th value you entered.\n\nYou cannot enter zero in this field."), TEXT("Input Error"), MB_OK); 
						SetFocus(GetDlgItem(hDlg, IDC_EDIT_TH));
						break;
					}
					if (!validateInput(strInTl)) { 
						MessageBox(hDlg, TEXT("There is a problem with the Tl value you entered.\n\nPlease check to be sure you only used the characters 0-9 and no more than one decimal point."), TEXT("Input Error"), MB_OK); 
						SetFocus(GetDlgItem(hDlg, IDC_EDIT_TL));
						break;
					}
					if (wcscmp(strInTl, TEXT("0")) == 0) { 
						MessageBox(hDlg, TEXT("There is a problem with the Tl value you entered.\n\nYou cannot enter zero in this field."), TEXT("Input Error"), MB_OK); 
						SetFocus(GetDlgItem(hDlg, IDC_EDIT_TL));
						break;
					}
					if (!validateInput(strInF)) { 
						MessageBox(hDlg, TEXT("There is a problem with the F value you entered.\n\nPlease check to be sure you only used the characters 0-9 and no more than one decimal point."), TEXT("Input Error"), MB_OK); 
						SetFocus(GetDlgItem(hDlg, IDC_EDIT_F));
						break;
					}
					if (wcscmp(strInF, TEXT("0")) == 0) { 
						MessageBox(hDlg, TEXT("There is a problem with the F value you entered.\n\nYou cannot enter zero in this field."), TEXT("Input Error"), MB_OK); 
						SetFocus(GetDlgItem(hDlg, IDC_EDIT_F));
						break;
					}
          // Perform the proper operation and show the results, or pop error
          switch (FromTo) {
            case 1: // Known: R1+R2+C, Calculate Th, Tl, F
              // Get the two known values
              known1 = wcstod(strInR1, &sError);
              known2 = wcstod(strInR2, &sError);
              known3 = wcstod(strInC,  &sError);
              // Do the actual calculations
							result1 = .693 * known3 * (known1 + known2);
							result2 = .693 * known3 * known2;
							result3 = 1 / (result1 + result2);
              // Copy the results to strings formatted properly
              swprintf(strResult1, TEXT("%.6f"), result1);
              swprintf(strResult2, TEXT("%.6f"), result2);
              swprintf(strResult3, TEXT("%.6f"), result3);
              // Set the edit boxes to the answers
              SetDlgItemText(hDlg, IDC_EDIT_TH, strResult1);
              SetDlgItemText(hDlg, IDC_EDIT_TL, strResult2);
              SetDlgItemText(hDlg, IDC_EDIT_F,  strResult3);
							SHSipPreference(hWnd, SIP_DOWN);
            break;
            case 2: // Known: Th+Tl+F, Calculate R1, R2, C
              // Get the two known values
              known1 = wcstod(strInTh, &sError);
              known2 = wcstod(strInTl, &sError);
              known3 = wcstod(strInF,  &sError);
              // Do the actual calculations
							result1 = 0;
							result2 = 0;
							result3 = 0;
              // Copy the results to strings formatted properly
              swprintf(strResult1, TEXT("%.6f"), result1);
              swprintf(strResult2, TEXT("%.6f"), result2);
              swprintf(strResult3, TEXT("%.6f"), result3);
              // Set the edit boxes to the answers
              SetDlgItemText(hDlg, IDC_EDIT_R1, strResult1);
              SetDlgItemText(hDlg, IDC_EDIT_R2, strResult2);
              SetDlgItemText(hDlg, IDC_EDIT_C,  strResult3);
							SHSipPreference(hWnd, SIP_DOWN);
            break;
            default:
              // Not a valid operation
              MessageBox(hDlg, TEXT("You must enter all three known values"), TEXT("Error"), MB_OK); 
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