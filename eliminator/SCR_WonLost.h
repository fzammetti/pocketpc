LRESULT CALLBACK WonLost(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {

	SHINITDLGINFO shidi;

	switch (message) {

		case WM_INITDIALOG:
			shidi.dwMask = SHIDIM_FLAGS;
 		  shidi.dwFlags = SHIDIF_DONEBUTTON | SHIDIF_SIPDOWN | SHIDIF_SIZEDLGFULLSCREEN;
			shidi.hDlg = hDlg;
			SHInitDialog(&shidi);
  		SHSipPreference(hDlg, SIP_DOWN);
			if (game_won == true) {
				SendMessage(GetDlgItem(hDlg, IDC_WONLOST), STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_YOUWON)));
				if (sound_enabled == true) {
					if (what_sound == 1)  { PlaySound((unsigned short *) IDR_WON_1,  hInst, SND_RESOURCE | SND_ASYNC); }
					if (what_sound == 2)  { PlaySound((unsigned short *) IDR_WON_2,  hInst, SND_RESOURCE | SND_ASYNC); }
					if (what_sound == 3)  { PlaySound((unsigned short *) IDR_WON_3,  hInst, SND_RESOURCE | SND_ASYNC); }
					if (what_sound == 4)  { PlaySound((unsigned short *) IDR_WON_4,  hInst, SND_RESOURCE | SND_ASYNC); }
					if (what_sound == 5)  { PlaySound((unsigned short *) IDR_WON_5,  hInst, SND_RESOURCE | SND_ASYNC); }
					if (what_sound == 6)  { PlaySound((unsigned short *) IDR_WON_6,  hInst, SND_RESOURCE | SND_ASYNC); }
					if (what_sound == 7)  { PlaySound((unsigned short *) IDR_WON_7,  hInst, SND_RESOURCE | SND_ASYNC); }
					if (what_sound == 8)  { PlaySound((unsigned short *) IDR_WON_8,  hInst, SND_RESOURCE | SND_ASYNC); }
					if (what_sound == 9)  { PlaySound((unsigned short *) IDR_WON_9,  hInst, SND_RESOURCE | SND_ASYNC); }
					if (what_sound == 10) { PlaySound((unsigned short *) IDR_WON_10, hInst, SND_RESOURCE | SND_ASYNC); }
				}
			} else {
				SendMessage(GetDlgItem(hDlg, IDC_WONLOST), STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_YOULOST)));
				if (sound_enabled == true) {
					if (what_sound == 1)  { PlaySound((unsigned short *) IDR_LOST_1,  hInst, SND_RESOURCE | SND_ASYNC); }
					if (what_sound == 2)  { PlaySound((unsigned short *) IDR_LOST_2,  hInst, SND_RESOURCE | SND_ASYNC); }
					if (what_sound == 3)  { PlaySound((unsigned short *) IDR_LOST_3,  hInst, SND_RESOURCE | SND_ASYNC); }
					if (what_sound == 4)  { PlaySound((unsigned short *) IDR_LOST_4,  hInst, SND_RESOURCE | SND_ASYNC); }
					if (what_sound == 5)  { PlaySound((unsigned short *) IDR_LOST_5,  hInst, SND_RESOURCE | SND_ASYNC); }
					if (what_sound == 6)  { PlaySound((unsigned short *) IDR_LOST_6,  hInst, SND_RESOURCE | SND_ASYNC); }
					if (what_sound == 7)  { PlaySound((unsigned short *) IDR_LOST_7,  hInst, SND_RESOURCE | SND_ASYNC); }
					if (what_sound == 8)  { PlaySound((unsigned short *) IDR_LOST_8,  hInst, SND_RESOURCE | SND_ASYNC); }
					if (what_sound == 9)  { PlaySound((unsigned short *) IDR_LOST_9,  hInst, SND_RESOURCE | SND_ASYNC); }
					if (what_sound == 10) { PlaySound((unsigned short *) IDR_LOST_10, hInst, SND_RESOURCE | SND_ASYNC); }
				}
			}
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