
// Prorotypes for utility functions after message handler
void		 setResColor(HWND, int, int, int);
void		 Calculate(HWND, int, int, int, int);
long int Exponent		(int, int);


LRESULT CALLBACK ResistorColorCode(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {

  static int band1 = 1;
  static int band2 = 1;
  static int band3 = 1;
  static int band4 = 11;

	switch (message) {

		case WM_INITDIALOG: {
			SHINITDLGINFO shidi;
			shidi.dwMask	= SHIDIM_FLAGS;
 		  shidi.dwFlags = SHIDIF_DONEBUTTON | SHIDIF_SIPDOWN | SHIDIF_SIZEDLGFULLSCREEN;
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
			// Fill our drop-downs
			SendMessage(GetDlgItem(hDlg, IDC_BANDCOLOR_1), CB_ADDSTRING, 0, (LPARAM)TEXT("Black"));
			SendMessage(GetDlgItem(hDlg, IDC_BANDCOLOR_1), CB_ADDSTRING, 0, (LPARAM)TEXT("Brown"));
			SendMessage(GetDlgItem(hDlg, IDC_BANDCOLOR_1), CB_ADDSTRING, 0, (LPARAM)TEXT("Red"));
			SendMessage(GetDlgItem(hDlg, IDC_BANDCOLOR_1), CB_ADDSTRING, 0, (LPARAM)TEXT("Orange"));
			SendMessage(GetDlgItem(hDlg, IDC_BANDCOLOR_1), CB_ADDSTRING, 0, (LPARAM)TEXT("Yellow"));
			SendMessage(GetDlgItem(hDlg, IDC_BANDCOLOR_1), CB_ADDSTRING, 0, (LPARAM)TEXT("Green"));
			SendMessage(GetDlgItem(hDlg, IDC_BANDCOLOR_1), CB_ADDSTRING, 0, (LPARAM)TEXT("Blue"));	
			SendMessage(GetDlgItem(hDlg, IDC_BANDCOLOR_1), CB_ADDSTRING, 0, (LPARAM)TEXT("Violet"));
			SendMessage(GetDlgItem(hDlg, IDC_BANDCOLOR_1), CB_ADDSTRING, 0, (LPARAM)TEXT("Gray"));
			SendMessage(GetDlgItem(hDlg, IDC_BANDCOLOR_1), CB_ADDSTRING, 0, (LPARAM)TEXT("White"));	
			SendMessage(GetDlgItem(hDlg, IDC_BANDCOLOR_2), CB_ADDSTRING, 0, (LPARAM)TEXT("Black"));
			SendMessage(GetDlgItem(hDlg, IDC_BANDCOLOR_2), CB_ADDSTRING, 0, (LPARAM)TEXT("Brown"));
			SendMessage(GetDlgItem(hDlg, IDC_BANDCOLOR_2), CB_ADDSTRING, 0, (LPARAM)TEXT("Red"));
			SendMessage(GetDlgItem(hDlg, IDC_BANDCOLOR_2), CB_ADDSTRING, 0, (LPARAM)TEXT("Orange"));
			SendMessage(GetDlgItem(hDlg, IDC_BANDCOLOR_2), CB_ADDSTRING, 0, (LPARAM)TEXT("Yellow"));
			SendMessage(GetDlgItem(hDlg, IDC_BANDCOLOR_2), CB_ADDSTRING, 0, (LPARAM)TEXT("Green"));
			SendMessage(GetDlgItem(hDlg, IDC_BANDCOLOR_2), CB_ADDSTRING, 0, (LPARAM)TEXT("Blue"));	
			SendMessage(GetDlgItem(hDlg, IDC_BANDCOLOR_2), CB_ADDSTRING, 0, (LPARAM)TEXT("Violet"));
			SendMessage(GetDlgItem(hDlg, IDC_BANDCOLOR_2), CB_ADDSTRING, 0, (LPARAM)TEXT("Gray"));
			SendMessage(GetDlgItem(hDlg, IDC_BANDCOLOR_2), CB_ADDSTRING, 0, (LPARAM)TEXT("White"));	
			SendMessage(GetDlgItem(hDlg, IDC_BANDCOLOR_3), CB_ADDSTRING, 0, (LPARAM)TEXT("Black"));
			SendMessage(GetDlgItem(hDlg, IDC_BANDCOLOR_3), CB_ADDSTRING, 0, (LPARAM)TEXT("Brown"));
			SendMessage(GetDlgItem(hDlg, IDC_BANDCOLOR_3), CB_ADDSTRING, 0, (LPARAM)TEXT("Red"));
			SendMessage(GetDlgItem(hDlg, IDC_BANDCOLOR_3), CB_ADDSTRING, 0, (LPARAM)TEXT("Orange"));
			SendMessage(GetDlgItem(hDlg, IDC_BANDCOLOR_3), CB_ADDSTRING, 0, (LPARAM)TEXT("Yellow"));
			SendMessage(GetDlgItem(hDlg, IDC_BANDCOLOR_3), CB_ADDSTRING, 0, (LPARAM)TEXT("Green"));
			SendMessage(GetDlgItem(hDlg, IDC_BANDCOLOR_3), CB_ADDSTRING, 0, (LPARAM)TEXT("Blue"));	
			SendMessage(GetDlgItem(hDlg, IDC_BANDCOLOR_3), CB_ADDSTRING, 0, (LPARAM)TEXT("Violet"));
			SendMessage(GetDlgItem(hDlg, IDC_BANDCOLOR_3), CB_ADDSTRING, 0, (LPARAM)TEXT("Gray"));
			SendMessage(GetDlgItem(hDlg, IDC_BANDCOLOR_3), CB_ADDSTRING, 0, (LPARAM)TEXT("White"));	
			SendMessage(GetDlgItem(hDlg, IDC_BANDCOLOR_3), CB_ADDSTRING, 0, (LPARAM)TEXT("Gold"));
			SendMessage(GetDlgItem(hDlg, IDC_BANDCOLOR_3), CB_ADDSTRING, 0, (LPARAM)TEXT("Silver"));	
			SendMessage(GetDlgItem(hDlg, IDC_BANDCOLOR_4), CB_ADDSTRING, 0, (LPARAM)TEXT("Gold"));
			SendMessage(GetDlgItem(hDlg, IDC_BANDCOLOR_4), CB_ADDSTRING, 0, (LPARAM)TEXT("Silver"));	
			SendMessage(GetDlgItem(hDlg, IDC_BANDCOLOR_4), CB_ADDSTRING, 0, (LPARAM)TEXT("None"));
			// Default selections
			SendMessage(GetDlgItem(hDlg, IDC_BANDCOLOR_1), CB_SETCURSEL, 0, 0);
			SendMessage(GetDlgItem(hDlg, IDC_BANDCOLOR_2), CB_SETCURSEL, 0, 0);
			SendMessage(GetDlgItem(hDlg, IDC_BANDCOLOR_3), CB_SETCURSEL, 0, 0);
			SendMessage(GetDlgItem(hDlg, IDC_BANDCOLOR_4), CB_SETCURSEL, 0, 0);
			Calculate(hDlg, band1, band2, band3, band4);
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
				if (LOWORD(wParam) == IDC_BANDCOLOR_1) { 
					int selIdx = SendMessage(GetDlgItem(hDlg, IDC_BANDCOLOR_1), CB_GETCURSEL, 0, 0);
					selIdx++;
					band1 = selIdx;
          setResColor(hDlg, IDC_BAND_1, IDC_BANDCOLOR_1, band1);
					Calculate(hDlg, band1, band2, band3, band4);
				}
				if (LOWORD(wParam) == IDC_BANDCOLOR_2) { 
					int selIdx = SendMessage(GetDlgItem(hDlg, IDC_BANDCOLOR_2), CB_GETCURSEL, 0, 0);
					selIdx++;
					band2 = selIdx;
          setResColor(hDlg, IDC_BAND_2, IDC_BANDCOLOR_2, band2);
					Calculate(hDlg, band1, band2, band3, band4);
				}
				if (LOWORD(wParam) == IDC_BANDCOLOR_3) { 
					int selIdx = SendMessage(GetDlgItem(hDlg, IDC_BANDCOLOR_3), CB_GETCURSEL, 0, 0);
					selIdx++;
					band3 = selIdx;
          setResColor(hDlg, IDC_BAND_3, IDC_BANDCOLOR_3, band3);
					Calculate(hDlg, band1, band2, band3, band4);
				}
				if (LOWORD(wParam) == IDC_BANDCOLOR_4) { 
					int selIdx = SendMessage(GetDlgItem(hDlg, IDC_BANDCOLOR_4), CB_GETCURSEL, 0, 0);
					selIdx = selIdx + 11;
					band4 = selIdx;
          setResColor(hDlg, IDC_BAND_4, IDC_BANDCOLOR_4, band4);
					Calculate(hDlg, band1, band2, band3, band4);
				}
			}

			int wmId    = LOWORD(wParam); 
			int wmEvent = HIWORD(wParam); 
 
      switch (wmId) {	

        case IDC_BAND_1: {
          band1++;
          if (band1 > 10) {
            band1 = 1;
          }
          setResColor(hDlg, IDC_BAND_1, IDC_BANDCOLOR_1, band1);
					Calculate(hDlg, band1, band2, band3, band4);
				break; }

        case IDC_BAND_2: {
          band2++;
          if (band2 > 10) {
            band2 = 1;
          }
          setResColor(hDlg, IDC_BAND_2, IDC_BANDCOLOR_2, band2);
					Calculate(hDlg, band1, band2, band3, band4);
				break; }

        case IDC_BAND_3: {
          band3++;
          if (band3 > 12) {
            band3 = 1;
          }
          setResColor(hDlg, IDC_BAND_3, IDC_BANDCOLOR_3, band3);
					Calculate(hDlg, band1, band2, band3, band4);
				break; }

        case IDC_BAND_4: {
          band4++;
          if (band4 > 13) {
            band4 = 11;
          }
          setResColor(hDlg, IDC_BAND_4, IDC_BANDCOLOR_4, band4);
					Calculate(hDlg, band1, band2, band3, band4);
				break; }

			}

		break; }

		default: {
			return DefWindowProc(hWnd, message, wParam, lParam);
    break; }

	}

  return FALSE;

}


void Calculate(HWND hDlg, int band1, int band2, int band3, int band4) {
	double multFact					= 0;
	double resVal						= 0;
	double resMin						= 0;
	double resMax						= 0;
	TCHAR strVal[16]				= TEXT("");
	TCHAR strOhms[16]				= TEXT("");
	TCHAR strTolerance[16]	= TEXT("");
	TCHAR whatTolerance[16] = TEXT("");
	TCHAR strMinAdd[16]			= TEXT("");
	TCHAR strMin[16]				= TEXT("");
	TCHAR strMaxAdd[16]			= TEXT("");
	TCHAR strMax[16]				= TEXT("");
	TCHAR strResults1[64]		= TEXT("");
	TCHAR strResults2[64]		= TEXT("");
  // Resistor value calculation 
  resVal = ((band1 - 1) * 10) + (band2 - 1);
  if (band3 == 1)  { resVal = resVal * 1; }
	if (band3 == 2)  { resVal = resVal * 10; }
	if (band3 == 3)  { resVal = resVal * 100; }
	if (band3 == 4)  { resVal = resVal * 1000; }
	if (band3 == 5)  { resVal = resVal * 10000; }
	if (band3 == 6)  { resVal = resVal * 100000; }
	if (band3 == 7)  { resVal = resVal * 1000000; }
	if (band3 == 8)  { resVal = resVal * 10000000; }
	if (band3 == 9)  { resVal = resVal * 100000000; }
	if (band3 == 10) { resVal = resVal * 1000000000; }
	if (band3 == 11) { resVal = resVal * .1; }
	if (band3 == 12) { resVal = resVal * .01; }
  // Pick right tolerance
  switch (band4) {
    case 13: {
			multFact = .2;
      wcscpy(whatTolerance, TEXT("20%)"));
		break; }
    case 11: {
      multFact = .05;
      wcscpy(whatTolerance, TEXT("5%)"));
		break; }
    case 12: {
      multFact = .1;
      wcscpy(whatTolerance, TEXT("10%)"));
		break; }
  }
  // Calculate minimum and maximum based on tolerance
  resMin = resVal - (resVal * multFact);
  resMax = resVal + (resVal * multFact);
  // Results String Parts
	// Format for pretty output
	if (resVal >= 1000000) {
		resVal /= 1000000;
		swprintf(strVal, TEXT("%.2f"), resVal);
		wcscpy(strOhms, TEXT(" M"));
	} else {
		if (resVal >= 1000) {
			resVal /= 1000;
			swprintf(strVal, TEXT("%.2f"), resVal);
			wcscpy(strOhms, TEXT(" K"));
		} else {
			swprintf(strVal, TEXT("%.2f"), resVal);
			wcscpy(strOhms, TEXT(" "));
		}
	}
	wcscat(strOhms, TEXT("Ohms (± "));
  wcscpy(strTolerance, whatTolerance);
  swprintf(strMin, TEXT("%.2f"), resMin);
  wcscpy(strMaxAdd, TEXT(" - "));
  swprintf(strMax, TEXT("%.2f"), resMax);
  // Clear Result Strings
  wcscpy(strResults1, TEXT(""));
  wcscpy(strResults2, TEXT(""));
  // Build Result Strings
  wcscat(strResults1, strVal);
  wcscat(strResults1, strOhms);
  wcscat(strResults1, strTolerance);
  wcscat(strResults2, strMin);
  wcscat(strResults2, strMaxAdd);
  wcscat(strResults2, strMax);
  // Display Result String2
  SetDlgItemText(hDlg, IDC_RESULTS1, strResults1);
  SetDlgItemText(hDlg, IDC_RESULTS2, strResults2);
}


// Little function to determine the proper resource ID to load in a resistor 
// picture control as well as update the text in the band's display
void setResColor(HWND hDlg, int band, int label, int colNum) {
  int whatResPic		= 0;
  TCHAR whatCol[10] = TEXT("");
  if (colNum == 1) {
    whatResPic = IDB_RES_BAND_BLACK;
    swprintf(whatCol, TEXT("Black"));
  }
  if (colNum == 2) {
    whatResPic = IDB_RES_BAND_BROWN;
    swprintf(whatCol, TEXT("Brown"));
  }
  if (colNum == 3) {
    whatResPic = IDB_RES_BAND_RED;
    swprintf(whatCol, TEXT("Red"));
  }
  if (colNum == 4) {
    whatResPic = IDB_RES_BAND_ORANGE;
    swprintf(whatCol, TEXT("Orange"));
  }
  if (colNum == 5) {
    whatResPic = IDB_RES_BAND_YELLOW;
    swprintf(whatCol, TEXT("Yellow"));
  }
  if (colNum == 6) {
    whatResPic = IDB_RES_BAND_GREEN;
    swprintf(whatCol, TEXT("Green"));
  }
  if (colNum == 7) {
    whatResPic = IDB_RES_BAND_BLUE;
    swprintf(whatCol, TEXT("Blue"));
  }
  if (colNum == 8) {
    whatResPic = IDB_RES_BAND_VIOLET;
    swprintf(whatCol, TEXT("Violet"));
  }
  if (colNum == 9) {
    whatResPic = IDB_RES_BAND_GREY;
    swprintf(whatCol, TEXT("Grey"));
  }
  if (colNum == 10) {
    whatResPic = IDB_RES_BAND_WHITE;
    swprintf(whatCol, TEXT("White"));
  }
  if (colNum == 11) {
    whatResPic = IDB_RES_BAND_GOLD;
    swprintf(whatCol, TEXT("Gold"));
  }
  if (colNum == 12) {
    whatResPic = IDB_RES_BAND_SILVER;
    swprintf(whatCol, TEXT("Silver"));
  }
  if (colNum == 13) {
    whatResPic = IDB_RES_BAND_NONE;
    swprintf(whatCol, TEXT("None"));
  }
  SendMessage(GetDlgItem(hDlg, band), STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)LoadBitmap(hInst, MAKEINTRESOURCE(whatResPic)));
  SetDlgItemText(hDlg, label, whatCol);
}


// Recursive routine to calculate exponents
long int Exponent(int x, int n) {
  int multiplies = 0;
	long int result = 1;
  if (n == 1) {
		result = x;
  }	else if (n != 0) {
		result = Exponent(x, n%2) * Exponent(x * x, n / 2);
		multiplies = multiplies + 2;
	}
	return(result);
}
