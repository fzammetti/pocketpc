
LRESULT CALLBACK DWTransforms(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {

	static int FromTo = 1;
	
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
					SetDlgItemText(hDlg, IDC_EDIT_ZA, TEXT(""));
					SetDlgItemText(hDlg, IDC_EDIT_ZB, TEXT(""));
					SetDlgItemText(hDlg, IDC_EDIT_ZC, TEXT(""));
					SetDlgItemText(hDlg, IDC_EDIT_Z1, TEXT(""));
					SetDlgItemText(hDlg, IDC_EDIT_Z2, TEXT(""));
					SetDlgItemText(hDlg, IDC_EDIT_Z3, TEXT(""));					
				break; }

				case IDC_DW_SWAP: {
					if (FromTo == 1) { 
						FromTo = 2; 
						SetDlgItemText(hDlg, IDC_DW_SWAP, TEXT("<--"));
						SendMessage(GetDlgItem(hDlg, IDC_EDIT_ZA), EM_SETREADONLY, (WPARAM)true,  0);
						SendMessage(GetDlgItem(hDlg, IDC_EDIT_ZB), EM_SETREADONLY, (WPARAM)true,  0);
						SendMessage(GetDlgItem(hDlg, IDC_EDIT_ZC), EM_SETREADONLY, (WPARAM)true,  0);
						SendMessage(GetDlgItem(hDlg, IDC_EDIT_Z1), EM_SETREADONLY, (WPARAM)false, 0);
						SendMessage(GetDlgItem(hDlg, IDC_EDIT_Z2), EM_SETREADONLY, (WPARAM)false, 0);
						SendMessage(GetDlgItem(hDlg, IDC_EDIT_Z3), EM_SETREADONLY, (WPARAM)false, 0);
					} else { 
						FromTo = 1; 
						SetDlgItemText(hDlg, IDC_DW_SWAP, TEXT("-->"));
						SendMessage(GetDlgItem(hDlg, IDC_EDIT_ZA), EM_SETREADONLY, (WPARAM)false, 0);
						SendMessage(GetDlgItem(hDlg, IDC_EDIT_ZB), EM_SETREADONLY, (WPARAM)false, 0);
						SendMessage(GetDlgItem(hDlg, IDC_EDIT_ZC), EM_SETREADONLY, (WPARAM)false, 0);
						SendMessage(GetDlgItem(hDlg, IDC_EDIT_Z1), EM_SETREADONLY, (WPARAM)true,  0);
						SendMessage(GetDlgItem(hDlg, IDC_EDIT_Z2), EM_SETREADONLY, (WPARAM)true,  0);
						SendMessage(GetDlgItem(hDlg, IDC_EDIT_Z3), EM_SETREADONLY, (WPARAM)true,  0);
					}
					SetDlgItemText(hDlg, IDC_EDIT_ZA, TEXT(""));
					SetDlgItemText(hDlg, IDC_EDIT_ZB, TEXT(""));
					SetDlgItemText(hDlg, IDC_EDIT_ZC, TEXT(""));
					SetDlgItemText(hDlg, IDC_EDIT_Z1, TEXT(""));
					SetDlgItemText(hDlg, IDC_EDIT_Z2, TEXT(""));
					SetDlgItemText(hDlg, IDC_EDIT_Z3, TEXT(""));
				break; }

				case IDC_CALCULATE: {
					LPTSTR sError;
					TCHAR  strInZA[16]		= TEXT("");
					TCHAR  strInZB[16]		= TEXT("");
					TCHAR  strInZC[16]		= TEXT("");
					TCHAR  strInZ1[16]		= TEXT("");
					TCHAR  strInZ2[16]		= TEXT("");
					TCHAR  strInZ3[16]		= TEXT("");
					TCHAR  strResults[16] = TEXT("");
					double results1				= 0;
					double results2				= 0;
					double results3				= 0;
					double Za = 0, Zb = 0, Zc = 0, Z1 = 0, Z2 = 0, Z3 = 0;
          // Get our entered values
          GetDlgItemText(hDlg, IDC_EDIT_ZA, strInZA, 15);
          GetDlgItemText(hDlg, IDC_EDIT_ZB, strInZB, 15);
          GetDlgItemText(hDlg, IDC_EDIT_ZC, strInZC, 15);
          GetDlgItemText(hDlg, IDC_EDIT_Z1, strInZ1, 15);
          GetDlgItemText(hDlg, IDC_EDIT_Z2, strInZ2, 15);
          GetDlgItemText(hDlg, IDC_EDIT_Z3, strInZ3, 15);
					// Check for illegal entries and abort if any found
					if (FromTo == 1) {
						if (!validateInput(strInZA)) { 
							MessageBox(hDlg, TEXT("There is a problem with the Za value you entered.\n\nPlease check to be sure you only used the characters 0-9 and no more than one decimal point."), TEXT("Input Error"), MB_OK); 
							SetFocus(GetDlgItem(hDlg, IDC_EDIT_ZA));
							break;
						}
						if (!validateInput(strInZB)) { 
							MessageBox(hDlg, TEXT("There is a problem with the Zb value you entered.\n\nPlease check to be sure you only used the characters 0-9 and no more than one decimal point."), TEXT("Input Error"), MB_OK); 
							SetFocus(GetDlgItem(hDlg, IDC_EDIT_ZB));
							break;
						}
						if (!validateInput(strInZC)) { 
							MessageBox(hDlg, TEXT("There is a problem with the Zc value you entered.\n\nPlease check to be sure you only used the characters 0-9 and no more than one decimal point."), TEXT("Input Error"), MB_OK); 
							SetFocus(GetDlgItem(hDlg, IDC_EDIT_ZC));
							break;
						}
					} else {
						if (!validateInput(strInZ1)) { 
							MessageBox(hDlg, TEXT("There is a problem with the Z1 value you entered.\n\nPlease check to be sure you only used the characters 0-9 and no more than one decimal point."), TEXT("Input Error"), MB_OK); 
							SetFocus(GetDlgItem(hDlg, IDC_EDIT_Z1));
							break;
						}
						if (!validateInput(strInZ2)) { 
							MessageBox(hDlg, TEXT("There is a problem with the Z2 value you entered.\n\nPlease check to be sure you only used the characters 0-9 and no more than one decimal point."), TEXT("Input Error"), MB_OK); 
							SetFocus(GetDlgItem(hDlg, IDC_EDIT_Z2));
							break;
						}
						if (!validateInput(strInZ3)) { 
						MessageBox(hDlg, TEXT("There is a problem with the Z3 value you entered.\n\nPlease check to be sure you only used the characters 0-9 and no more than one decimal point."), TEXT("Input Error"), MB_OK); 
							SetFocus(GetDlgItem(hDlg, IDC_EDIT_Z3));
							break;
						}
					}
          // Make sure they entered all three values
					if (FromTo == 1) {
						if (wcscmp(strInZA, TEXT("")) == 0) { 
							MessageBox(hDlg, TEXT("You must enter all three values in order to calculate the transformation."), TEXT("Input Error"), MB_OK);
							SetFocus(GetDlgItem(hDlg, IDC_EDIT_ZA));
							break;
						}
						if (wcscmp(strInZB, TEXT("")) == 0) { 
							MessageBox(hDlg, TEXT("You must enter all three values in order to calculate the transformation."), TEXT("Input Error"), MB_OK);
							SetFocus(GetDlgItem(hDlg, IDC_EDIT_ZB));
							break;
						}
						if (wcscmp(strInZC, TEXT("")) == 0) { 
							MessageBox(hDlg, TEXT("You must enter all three values in order to calculate the transformation."), TEXT("Input Error"), MB_OK);
							SetFocus(GetDlgItem(hDlg, IDC_EDIT_ZC));
							break;
						}
					} else {
						if (wcscmp(strInZ1, TEXT("")) == 0) { 
							MessageBox(hDlg, TEXT("You must enter all three values in order to calculate the transformation."), TEXT("Input Error"), MB_OK);
							SetFocus(GetDlgItem(hDlg, IDC_EDIT_Z1));
							break;
						}
						if (wcscmp(strInZ2, TEXT("")) == 0) { 
							MessageBox(hDlg, TEXT("You must enter all three values in order to calculate the transformation."), TEXT("Input Error"), MB_OK);
							SetFocus(GetDlgItem(hDlg, IDC_EDIT_Z2));
							break;
						}
						if (wcscmp(strInZ3, TEXT("")) == 0) { 
							MessageBox(hDlg, TEXT("You must enter all three values in order to calculate the transformation."), TEXT("Input Error"), MB_OK);
							SetFocus(GetDlgItem(hDlg, IDC_EDIT_Z3));
							break;
						}
					}
					if (FromTo == 1) {
						Za = wcstod(strInZA, &sError);
            Zb = wcstod(strInZB, &sError);
            Zc = wcstod(strInZC, &sError);
						Z1 = (Za * Zc) / (Za + Zb + Zc); 
						Z2 = (Za * Zb) / (Za + Zb + Zc); 
						Z3 = (Zb * Zc) / (Za + Zb + Zc);
            swprintf(strResults, TEXT("%.6f"), Z1);
            SetDlgItemText(hDlg, IDC_EDIT_Z1, strResults);	
            swprintf(strResults, TEXT("%.6f"), Z2);
            SetDlgItemText(hDlg, IDC_EDIT_Z2, strResults);
            swprintf(strResults, TEXT("%.6f"), Z3);
            SetDlgItemText(hDlg, IDC_EDIT_Z3, strResults);						
					} else {
            Z1 = wcstod(strInZ1, &sError);
            Z2 = wcstod(strInZ2, &sError);
            Z3 = wcstod(strInZ3, &sError);
						Za = ((Z1 * Z2) + (Z2 * Z3) + (Z1 * Z3)) / Z3; 
						Zb = ((Z1 * Z2) + (Z2 * Z3) + (Z1 * Z3)) / Z1; 
						Zc = ((Z1 * Z2) + (Z2 * Z3) + (Z1 * Z3)) / Z2;
            swprintf(strResults, TEXT("%.6f"), Za);
            SetDlgItemText(hDlg, IDC_EDIT_ZA, strResults);	
            swprintf(strResults, TEXT("%.6f"), Zb);
            SetDlgItemText(hDlg, IDC_EDIT_ZB, strResults);
            swprintf(strResults, TEXT("%.6f"), Zc);
            SetDlgItemText(hDlg, IDC_EDIT_ZC, strResults);	
					}
					SHSipPreference(hWnd, SIP_DOWN);
				break; }

				default: {
					return DefWindowProc(hWnd, message, wParam, lParam);
				break; }

			}

		break; }

	}

  return FALSE;

}