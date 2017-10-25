
LRESULT CALLBACK ChipReference(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {

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
			// Add tabs
			HWND TabHandle = GetDlgItem (hDlg, IDC_TABS);
			// Define new tab
			TCITEM TabItem;
			TabItem.mask = TCIF_TEXT;
			TabItem.pszText = TEXT("Part Selection");
			// Insert new tab
			TabCtrl_InsertItem(TabHandle, 1, &TabItem);
			// Define new tab
			TabItem.pszText = TEXT("Pinout");
			// Insert new tab
			TabCtrl_InsertItem(TabHandle, 2, &TabItem);
			// Define new tab
			TabItem.pszText = TEXT("Function Table");
			// Insert new tab
			TabCtrl_InsertItem(TabHandle, 2, &TabItem);
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

		case WM_NOTIFY: {
      NMHDR FAR* tem = (NMHDR FAR*)lParam;   
      switch (tem->code) {

        case TCN_SELCHANGE: {
          // Hide the current child
					ShowWindow(hWndChipReferenceChild, SW_HIDE);
          // Figure out which tab is clicked
          int whatTab = TabCtrl_GetCurSel(tem->hwndFrom); 
          whatTab++;
          // Based on the above, chose which child to show
          switch (whatTab) {
            case 1: {
              // Part Selection tab
              hWndChipReferenceChild = hWndChipReferenceSelection;         
						break; }
            case 2: {
              // Pinout tab
              hWndChipReferenceChild = hWndChipReferencePinout;
						break; }
            case 3: {
              // Function Table tab
              hWndChipReferenceChild = hWndChipReferenceFunctionTable;
						break; }
          }
					ShowWindow(hWndChipReferenceChild, SW_SHOW);
					BringWindowToTop(hWndChipReferenceChild); 
          SHSipPreference(hDlg, SIP_DOWN);
				break; }
      }
		break; }

		case WM_COMMAND: {
			if (LOWORD(wParam) == IDOK) {
				ShowWindow(hWndCurrentScreen, SW_HIDE);
				SHSipPreference(hWnd, SIP_DOWN);
				hWndCurrentScreen = NULL;
				return true;
			}
		break; }

		default: {
			return DefWindowProc(hWnd, message, wParam, lParam);
    break; }

	}

  return FALSE;

}