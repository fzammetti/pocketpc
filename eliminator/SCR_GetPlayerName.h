LRESULT CALLBACK GetPlayerName(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	
	SHINITDLGINFO shidi;

	switch (message) {

		case WM_INITDIALOG:
			// Create a Done button and size it.  
			shidi.dwMask = SHIDIM_FLAGS;
			shidi.dwFlags = SHIDIF_SIPDOWN | SHIDIF_SIZEDLGFULLSCREEN;
			shidi.hDlg = hDlg;
			SHInitDialog(&shidi);
			SHSipPreference(hDlg, SIP_UP);
     return TRUE; 
		break;

		case WM_COMMAND: 
			int wmId    = LOWORD(wParam); 
			int wmEvent = HIWORD(wParam); 
			if (wmId == IDC_SAVENAME) {
				GetDlgItemText(hDlg, IDC_INNAME, hof_player, 20);		
 				SHSipPreference(hDlg, SIP_DOWN);
      	EndDialog(hDlg, LOWORD(wParam));
      }
		break;

	}

  return FALSE;

}