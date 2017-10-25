LRESULT CALLBACK HOF(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	
	SHINITDLGINFO shidi;

	switch (message) {

		case WM_INITDIALOG: {
			// Create a Done button and size it.  
			shidi.dwMask = SHIDIM_FLAGS;
			shidi.dwFlags = SHIDIF_DONEBUTTON | SHIDIF_SIPDOWN | SHIDIF_SIZEDLGFULLSCREEN;
			shidi.hDlg = hDlg;
			SHInitDialog(&shidi);
			SHSipPreference(hDlg, SIP_DOWN);
			// Add columns to listview
			LV_COLUMN			lvColumn;       
			LV_ITEM				lvItem; 
			HWND hWndLV = GetDlgItem(hDlg, IDC_LISTVIEW);
			lvColumn.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
			lvColumn.fmt	= LVCFMT_LEFT;
			lvColumn.pszText = L"Pattern";
			lvColumn.cx			 = 55;
			ListView_InsertColumn(hWndLV, 0, &lvColumn);
			lvColumn.pszText = L"Name";
			lvColumn.cx			 = 45;
			ListView_InsertColumn(hWndLV, 1, &lvColumn);
			lvColumn.pszText = L"Pieces Left";
			lvColumn.cx			 = 75;
			ListView_InsertColumn(hWndLV, 2, &lvColumn);
			lvColumn.pszText = L"Time";
			lvColumn.cx			 = 40;
			ListView_InsertColumn(hWndLV, 3, &lvColumn);

			int index = 0;
			HANDLE HOFFileHandle = NULL;
			DWORD bytes_accessed = 0;
			HOFREC out_records[100];
			wcscpy(out_records[0].szPattern,    L"Pattern1            \0");
			wcscpy(out_records[0].szName,       L"Frank               \0");
			wcscpy(out_records[0].szPiecesLeft, L"10                  \0");
			wcscpy(out_records[0].szTime,       L"60                  \0");
			wcscpy(out_records[1].szPattern,    L"Pattern2            \0");
			wcscpy(out_records[1].szName,       L"Traci               \0");
			wcscpy(out_records[1].szPiecesLeft, L"20                  \0");
			wcscpy(out_records[1].szTime,       L"70                  \0");
			wcscpy(out_records[2].szPattern,    L"Pattern3            \0");
			wcscpy(out_records[2].szName,       L"Andrew              \0");
			wcscpy(out_records[2].szPiecesLeft, L"30                  \0");
			wcscpy(out_records[2].szTime,       L"80                  \0");
			HOFFileHandle = CreateFile(L"test.txt", GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
			for (index = 0; index < 3; index++) {	
				WriteFile(HOFFileHandle, out_records[index].szPattern,    21, &bytes_accessed, NULL);
				WriteFile(HOFFileHandle, out_records[index].szName,       21, &bytes_accessed, NULL);
				WriteFile(HOFFileHandle, out_records[index].szPiecesLeft, 21, &bytes_accessed, NULL);
				WriteFile(HOFFileHandle, out_records[index].szTime,       21, &bytes_accessed, NULL);
			}
			CloseHandle(HOFFileHandle);
			HOFFileHandle = CreateFile(L"test.txt", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
			for (index = 0; index < 3; index++) {	
				ReadFile(HOFFileHandle, out_records[index + 10].szPattern,    21, &bytes_accessed, NULL);
				ReadFile(HOFFileHandle, out_records[index + 10].szName,       21, &bytes_accessed, NULL);
				ReadFile(HOFFileHandle, out_records[index + 10].szPiecesLeft, 21, &bytes_accessed, NULL);
				ReadFile(HOFFileHandle, out_records[index + 10].szTime,       21, &bytes_accessed, NULL);
			}
			CloseHandle(HOFFileHandle);
			lvItem.mask = LVIF_TEXT | LVIF_PARAM | LVIF_STATE;
			lvItem.state = 0;      
			lvItem.stateMask = 0;
			for (index = 0; index < 3; index++) {
				lvItem.iItem			= index; // Index of new item
				lvItem.iSubItem		= 0; // Subitem number of first column (always 0)
				lvItem.pszText		= out_records[index + 10].szPattern;  // Text for first column
				lvItem.cchTextMax = 21; // Max size of first column
				lvItem.lParam			= NULL;
				ListView_InsertItem(hWndLV, &lvItem);
				ListView_SetItemText(hWndLV, index, 1, out_records[index + 10].szName);
				ListView_SetItemText(hWndLV, index, 2, out_records[index + 10].szPiecesLeft);
				ListView_SetItemText(hWndLV, index, 3, out_records[index + 10].szTime);
			}

			return TRUE; 
		break; }

		case WM_COMMAND: {
      
			if (LOWORD(wParam) == IDOK) {
 				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}

			int wmId    = LOWORD(wParam); 
			int wmEvent = HIWORD(wParam); 

		break; }

	}

  return FALSE;

}