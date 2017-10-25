
// Sort comparison function
int CALLBACK DialectricConstantsCompareProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort) {
	DIALECTRICCONSTANTS *pVal1  = (DIALECTRICCONSTANTS *)lParam1;
	DIALECTRICCONSTANTS *pVal2  = (DIALECTRICCONSTANTS *)lParam2;
	LPTSTR							szVal1  = TEXT("");
	LPTSTR							szVal2  = TEXT("");
	long								lVal1   = 0;
	long								lVal2   = 0;
	int									iResult = 0;
	LPTSTR							sError;
	if (pVal1 && pVal2)	{
		switch (lParamSort) {
			case 0:
				szVal1 = pVal1->szMaterial;
				szVal2 = pVal2->szMaterial;
				if (sortDir) {
					iResult = lstrcmpi(szVal1, szVal2);
				} else {
					iResult = lstrcmpi(szVal2, szVal1);
				}
			break;
			case 1:
				lVal1 = (long)wcstod(pVal1->szDCLower, &sError);
				lVal2 = (long)wcstod(pVal2->szDCLower, &sError);
				if (sortDir) {
					iResult = lVal1 - lVal2;
				} else {
					iResult = lVal2 - lVal1;
				}
			break;
			case 2:
				lVal1 = (long)wcstod(pVal1->szDCUpper, &sError);
				lVal2 = (long)wcstod(pVal2->szDCUpper, &sError);
				if (sortDir) {
					iResult = lVal1 - lVal2;
				} else {
					iResult = lVal2 - lVal1;
				}
			break;
		}
	}
	return(iResult);
}


// Message handler
LRESULT CALLBACK DialectricConstants(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {

	static bool DialectricConstants_lastSortDir = true;
	static int  DialectricConstants_lastSortCol = 0;

	switch (message) {

		case WM_INITDIALOG: {
			LV_COLUMN			lvColumn;        
			LV_ITEM				lvItem;
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
      // Fill our listview
      HWND hWndLV = GetDlgItem(hDlg, IDC_LISTVIEW);
      ListView_DeleteAllItems(hWndLV); // Delete everything from it
      // Add our columns
      lvColumn.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
      lvColumn.fmt	= LVCFMT_LEFT;
      for (int index = 0; index < 3; index++) {
        lvColumn.pszText = DialectricConstantsColsTable[index].szText;
        lvColumn.cx			 = DialectricConstantsColsTable[index].intSize;
        ListView_InsertColumn(hWndLV, index, &lvColumn);
      }
      // Add our data
      lvItem.mask = LVIF_TEXT | LVIF_PARAM | LVIF_STATE;
	    lvItem.state = 0;      
	    lvItem.stateMask = 0;
      for (index = 0; index < numItemsDialectricConstants; index++) {
		    lvItem.iItem			= index; // Index of new item
		    lvItem.iSubItem		= 0; // Subitem number of first column (always 0)
		    lvItem.pszText		= DialectricConstantsTable[index].szMaterial;  // Text for first column
		    lvItem.cchTextMax = 32; // Max size of first column
		    lvItem.lParam			= (LPARAM)&DialectricConstantsTable[index];
				if (ListView_InsertItem(hWndLV, &lvItem) == -1) { // Insert the item
			    return NULL;
				}
        // Add each column after the first
			  ListView_SetItemText(hWndLV, index, 1, DialectricConstantsTable[index].szDCLower);
			  ListView_SetItemText(hWndLV, index, 2, DialectricConstantsTable[index].szDCUpper);
      }
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
		break; }

		case WM_NOTIFY: {
			NMHDR FAR* tem = (NMHDR FAR*)lParam;   
			switch (tem->code) {
				case LVN_COLUMNCLICK: {
					NM_LISTVIEW *pNm = (NM_LISTVIEW *)lParam;
					if (DialectricConstants_lastSortCol == pNm->iSubItem) {
						sortDir = !DialectricConstants_lastSortDir;
					} else {
						sortDir = true;
					}
					DialectricConstants_lastSortCol = pNm->iSubItem;
					DialectricConstants_lastSortDir = sortDir;
					ListView_SortItems(pNm->hdr.hwndFrom,	DialectricConstantsCompareProc, (LPARAM)(pNm->iSubItem));
				break; }
			}
		break; }

		default: {
			return DefWindowProc(hWnd, message, wParam, lParam);
    break; }

	}

  return FALSE;

}