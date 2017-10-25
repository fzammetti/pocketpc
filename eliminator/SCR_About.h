LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {

	SHINITDLGINFO shidi;
  TCHAR szVerTemp[255] = L"";

	switch (message) {

		case WM_INITDIALOG:
			shidi.dwMask = SHIDIM_FLAGS;
 		  shidi.dwFlags = SHIDIF_DONEBUTTON | SHIDIF_SIPDOWN | SHIDIF_SIZEDLGFULLSCREEN;
			shidi.hDlg = hDlg;
			SHInitDialog(&shidi);
  		SHSipPreference(hDlg, SIP_DOWN);
			LoadString(hInst, IDS_VERSION, szVerTemp, 255);
			SetDlgItemText(hDlg, IDC_VERSION, szVerTemp);	
			return TRUE;
		break; 

		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK) {
				EndDialog(hDlg, LOWORD(wParam));
				SHSipPreference(hDlg, SIP_DOWN);
				return TRUE;
			}
		break;

	}

  return FALSE;

}