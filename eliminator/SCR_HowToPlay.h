LRESULT CALLBACK HowToPlay(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {

	SHINITDLGINFO shidi;
	static int what_page = 1;
	TCHAR strPage1[255] = L"Page 1 of 3... Playing Eliminator is rather simple:  The game is played on a board containing a number of holes.  Each hole can be empty or hold one marble.  A legal move consists of one marble jumping over another.";
	TCHAR strPage2[255] = L"Page 2 of 3... You can only jump a marble into an empty hole.  The jumped marble is removed from the board.  You can jump horizontally, vertically or diagonally.  You can only jump one marble at a time.";
	TCHAR strPage3[255] = L"Page 3 of 3... That means that whatever marble you move can only move a total of two tiles away in any direction at a time.  The object of the game is to eliminate all but one marble from the board in the fastest time possible.";

	switch (message) {

		case WM_INITDIALOG:
			shidi.dwMask = SHIDIM_FLAGS;
 		  shidi.dwFlags = SHIDIF_DONEBUTTON | SHIDIF_SIPDOWN | SHIDIF_SIZEDLGFULLSCREEN;
			shidi.hDlg = hDlg;
			SetDlgItemText(hDlg, IDC_INSTRUCTIONS, strPage1);	
			SHInitDialog(&shidi);
  		SHSipPreference(hDlg, SIP_DOWN);
			return TRUE;
		break; 

		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK) {
				EndDialog(hDlg, LOWORD(wParam));
				SHSipPreference(hDlg, SIP_DOWN);
				return TRUE;
			}

			int wmId    = LOWORD(wParam); 
			int wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId) {	
				case IDC_NEXT:
					what_page++;
					if (what_page > 3) { what_page = 3; }
					if (what_page == 1) { SetDlgItemText(hDlg, IDC_INSTRUCTIONS, strPage1); }
					if (what_page == 2) { SetDlgItemText(hDlg, IDC_INSTRUCTIONS, strPage2); }
					if (what_page == 3) { SetDlgItemText(hDlg, IDC_INSTRUCTIONS, strPage3); }
				break;
				case IDC_PREVIOUS:
					what_page--;
					if (what_page < 1) { what_page = 1; }
					if (what_page == 1) { SetDlgItemText(hDlg, IDC_INSTRUCTIONS, strPage1); }
					if (what_page == 2) { SetDlgItemText(hDlg, IDC_INSTRUCTIONS, strPage2); }
					if (what_page == 3) { SetDlgItemText(hDlg, IDC_INSTRUCTIONS, strPage3); }
				break;
			}

		break;

	}

  return FALSE;

}