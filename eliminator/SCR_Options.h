LRESULT CALLBACK Options(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	
	SHINITDLGINFO shidi;
  HWND hwndPattern, hwndPieces;
  int z;

	switch (message) {

		case WM_INITDIALOG:
			// Create a Done button and size it.  
			shidi.dwMask = SHIDIM_FLAGS;
			shidi.dwFlags = SHIDIF_DONEBUTTON | SHIDIF_SIPDOWN | SHIDIF_SIZEDLGFULLSCREEN;
			shidi.hDlg = hDlg;
			SHInitDialog(&shidi);

			// Check our sound checkbox if it should be, clear it otherwise
			if (sound_enabled == true) {
				SendMessage(GetDlgItem(hDlg, IDC_SOUND), BM_SETCHECK, (WPARAM)BST_CHECKED, (LPARAM)0);
			} else {
				SendMessage(GetDlgItem(hDlg, IDC_SOUND), BM_SETCHECK, (WPARAM)BST_UNCHECKED, (LPARAM)0);
			}
      // Fill the pattern drop-down and select the current value as default
			hwndPattern = GetDlgItem(hDlg, IDC_PATTERN);
			SendMessage(hwndPattern, CB_ADDSTRING, 0, (LPARAM)L"Full Board");
			SendMessage(hwndPattern, CB_ADDSTRING, 0, (LPARAM)L"Big Cross");
			SendMessage(hwndPattern, CB_ADDSTRING, 0, (LPARAM)L"Diamond");
			SendMessage(hwndPattern, CB_ADDSTRING, 0, (LPARAM)L"Horseshoe");
			SendMessage(hwndPattern, CB_ADDSTRING, 0, (LPARAM)L"Pyramid");
			SendMessage(hwndPattern, CB_ADDSTRING, 0, (LPARAM)L"Inverted Pyramid");
			SendMessage(hwndPattern, CB_ADDSTRING, 0, (LPARAM)L"The Bars");
			SendMessage(hwndPattern, CB_ADDSTRING, 0, (LPARAM)L"Hexagonal");
			SendMessage(hwndPattern, CB_ADDSTRING, 0, (LPARAM)L"X Marks The Spot");
			SendMessage(hwndPattern, CB_ADDSTRING, 0, (LPARAM)L"Spiral");
			SendMessage(hwndPattern, CB_ADDSTRING, 0, (LPARAM)L"Bridges");
			SendMessage(hwndPattern, CB_ADDSTRING, 0, (LPARAM)L"Broken Heart");
			SendMessage(hwndPattern, CB_ADDSTRING, 0, (LPARAM)L"Asymmetry");
			SendMessage(hwndPattern, CB_ADDSTRING, 0, (LPARAM)L"Strange Invaders");
			SendMessage(hwndPattern, CB_ADDSTRING, 0, (LPARAM)L"Entropy");

      SendMessage(hwndPattern, CB_SETCURSEL, pattern_index - 1, 0);
      // Show the correct pattern
      if (pattern_index == 1)  { z = IDB_PREVIEW_PATTERN_FULLBOARD; }
      if (pattern_index == 2)  { z = IDB_PREVIEW_PATTERN_BIGCROSS; }
      if (pattern_index == 3)  { z = IDB_PREVIEW_PATTERN_DIAMOND; }
      if (pattern_index == 4)  { z = IDB_PREVIEW_PATTERN_HORSESHOE; }
      if (pattern_index == 5)  { z = IDB_PREVIEW_PATTERN_PYRAMID; }
      if (pattern_index == 6)  { z = IDB_PREVIEW_PATTERN_INVERTEDPYRAMID; }
      if (pattern_index == 7)  { z = IDB_PREVIEW_PATTERN_THEBARS; }
      if (pattern_index == 8)  { z = IDB_PREVIEW_PATTERN_HEXAGONAL; }
      if (pattern_index == 9)  { z = IDB_PREVIEW_PATTERN_XMARKSTHESPOT; }
      if (pattern_index == 10) { z = IDB_PREVIEW_PATTERN_SPIRAL; }
      if (pattern_index == 11) { z = IDB_PREVIEW_PATTERN_BRIDGES; }
      if (pattern_index == 12) { z = IDB_PREVIEW_PATTERN_HEART; }
      if (pattern_index == 13) { z = IDB_PREVIEW_PATTERN_CHECKERBOARD; }
      if (pattern_index == 14) { z = IDB_PREVIEW_PATTERN_INVADERS; }
      if (pattern_index == 15) { z = IDB_PREVIEW_PATTERN_ENTROPY; }
      SendMessage(GetDlgItem(hDlg, IDC_PATTERN_PREVIEW), STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)LoadBitmap(hInst, MAKEINTRESOURCE(z)));
      // Fill the pieces drop-down
      hwndPieces = GetDlgItem(hDlg, IDC_PIECES);
			SendMessage(hwndPieces, CB_ADDSTRING, 0, (LPARAM)L"Red Marbles");
			SendMessage(hwndPieces, CB_ADDSTRING, 0, (LPARAM)L"Blue Marbles");
			SendMessage(hwndPieces, CB_ADDSTRING, 0, (LPARAM)L"Lime Marbles");
			SendMessage(hwndPieces, CB_ADDSTRING, 0, (LPARAM)L"Brown Marbles");
      SendMessage(hwndPieces, CB_ADDSTRING, 0, (LPARAM)L"Purple Marbles");
      // Select the current value as default and show the correct piece
      if (what_graphic == IDB_MARBLE_RED)    { z = 0; }
      if (what_graphic == IDB_MARBLE_BLUE)   { z = 1; }
      if (what_graphic == IDB_MARBLE_LIME)   { z = 2; }
      if (what_graphic == IDB_MARBLE_BROWN)  { z = 3; }
      if (what_graphic == IDB_MARBLE_PURPLE) { z = 4; }
      SendMessage(hwndPieces, CB_SETCURSEL, z, 0);
			SendMessage(GetDlgItem(hDlg, IDC_PIECES_PREVIEW), STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)LoadBitmap(hInst, MAKEINTRESOURCE(what_graphic)));

			selected_pattern      = pattern_index;
			selected_pieces       = what_graphic;
			selected_pieces_up    = what_graphic_up;
			selected_pieces_empty = what_graphic_empty; 

			SHSipPreference(hDlg, SIP_DOWN);

     return TRUE; 
		break;

		case WM_COMMAND:
      
			if (LOWORD(wParam) == IDOK) {
        if (game_in_progress == false || (pattern_index != selected_pattern || what_graphic != selected_pieces)) {
          if (game_in_progress == true) {
						if (MessageBox(hDlg, L"The change(s) you requested will abort the current game.  Are you sure you want to do this?", L"Confirm...", MB_YESNO | MB_ICONQUESTION) == IDNO) {
							EndDialog(hDlg, LOWORD(wParam));
							return TRUE;
						}
					}
					pattern_index      = selected_pattern;
          what_graphic       = selected_pieces;
          what_graphic_up    = selected_pieces_up;
          what_graphic_empty = selected_pieces_empty;
					game_in_progress	 = true;
					piece_up					 = false;
          // Populate the playfield with the current pattern
	        PopulatePlayfield(hDlg);
          // Reset our current states
	        loadCurrentStates();
					// Reset our elapsed time counter
					elapsed_minutes = 0;
					elapsed_seconds = 0;
					SetDlgItemText(hwnd_Playfield, IDC_ELAPSED, L"");
					// And show the playfield
				  SHSipPreference(hDlg, SIP_DOWN);
					_stprintf(strRemaining, TEXT("%d"), pieces_remaining);
					SetDlgItemText(hwnd_Playfield, IDC_REMAINING, strRemaining);
					ShowWindow(hwnd_Playfield, SW_SHOWNORMAL);
        }
				SHSipPreference(hDlg, SIP_DOWN);
      	EndDialog(hDlg, LOWORD(wParam));
			  return TRUE;
		  }
			
			int wmId    = LOWORD(wParam); 
			int wmEvent = HIWORD(wParam); 

			if (wmId == IDC_SOUND) {
				if (SendMessage(GetDlgItem(hDlg, IDC_SOUND), BM_GETCHECK, (WPARAM)0, (LPARAM)0) == BST_CHECKED) {
					sound_enabled = true;
				} else {
					sound_enabled = false;
				}
			}

      // Show a new pattern preview
      if (wmEvent == CBN_SELCHANGE && wmId == IDC_PATTERN) {
        int iCurSel;
        TCHAR strPattern[25];
        HWND hwndPattern = GetDlgItem(hDlg, IDC_PATTERN);
				iCurSel = SendMessage(hwndPattern, CB_GETCURSEL, 0, 0);
				SendMessage(hwndPattern, CB_GETLBTEXT, iCurSel, (LPARAM)strPattern);
        if (_tcsicmp(strPattern, L"Full Board") == 0) {
			    SendMessage(GetDlgItem(hDlg, IDC_PATTERN_PREVIEW), STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_PREVIEW_PATTERN_FULLBOARD)));
          selected_pattern = 1;
        }
        if (_tcsicmp(strPattern, L"Big Cross") == 0) {
			    SendMessage(GetDlgItem(hDlg, IDC_PATTERN_PREVIEW), STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_PREVIEW_PATTERN_BIGCROSS)));
          selected_pattern = 2;
        }        
        if (_tcsicmp(strPattern, L"Diamond") == 0) {
			    SendMessage(GetDlgItem(hDlg, IDC_PATTERN_PREVIEW), STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_PREVIEW_PATTERN_DIAMOND)));
          selected_pattern = 3;
        } 
        if (_tcsicmp(strPattern, L"Horseshoe") == 0) {
			    SendMessage(GetDlgItem(hDlg, IDC_PATTERN_PREVIEW), STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_PREVIEW_PATTERN_HORSESHOE)));
          selected_pattern = 4;
        } 
        if (_tcsicmp(strPattern, L"Pyramid") == 0) {
			    SendMessage(GetDlgItem(hDlg, IDC_PATTERN_PREVIEW), STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_PREVIEW_PATTERN_PYRAMID)));
          selected_pattern = 5;
        } 
        if (_tcsicmp(strPattern, L"Inverted Pyramid") == 0) {
			    SendMessage(GetDlgItem(hDlg, IDC_PATTERN_PREVIEW), STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_PREVIEW_PATTERN_INVERTEDPYRAMID)));
          selected_pattern = 6;
        } 
        if (_tcsicmp(strPattern, L"The Bars") == 0) {
			    SendMessage(GetDlgItem(hDlg, IDC_PATTERN_PREVIEW), STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_PREVIEW_PATTERN_THEBARS)));
          selected_pattern = 7;
        } 
        if (_tcsicmp(strPattern, L"Hexagonal") == 0) {
			    SendMessage(GetDlgItem(hDlg, IDC_PATTERN_PREVIEW), STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_PREVIEW_PATTERN_HEXAGONAL)));
          selected_pattern = 8;
        } 
        if (_tcsicmp(strPattern, L"X Marks The Spot") == 0) {
			    SendMessage(GetDlgItem(hDlg, IDC_PATTERN_PREVIEW), STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_PREVIEW_PATTERN_XMARKSTHESPOT)));
          selected_pattern = 9;
        } 
        if (_tcsicmp(strPattern, L"Spiral") == 0) {
			    SendMessage(GetDlgItem(hDlg, IDC_PATTERN_PREVIEW), STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_PREVIEW_PATTERN_SPIRAL)));
          selected_pattern = 10;
        } 
        if (_tcsicmp(strPattern, L"Bridges") == 0) {
			    SendMessage(GetDlgItem(hDlg, IDC_PATTERN_PREVIEW), STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_PREVIEW_PATTERN_BRIDGES)));
          selected_pattern = 11;
        } 
        if (_tcsicmp(strPattern, L"Broken Heart") == 0) {
			    SendMessage(GetDlgItem(hDlg, IDC_PATTERN_PREVIEW), STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_PREVIEW_PATTERN_HEART)));
          selected_pattern = 12;
        } 
        if (_tcsicmp(strPattern, L"Asymmetry") == 0) {
			    SendMessage(GetDlgItem(hDlg, IDC_PATTERN_PREVIEW), STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_PREVIEW_PATTERN_CHECKERBOARD)));
          selected_pattern = 13;
        }
        if (_tcsicmp(strPattern, L"Strange Invaders") == 0) {
			    SendMessage(GetDlgItem(hDlg, IDC_PATTERN_PREVIEW), STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_PREVIEW_PATTERN_INVADERS)));
          selected_pattern = 14;
        }
        if (_tcsicmp(strPattern, L"Entropy") == 0) {
			    SendMessage(GetDlgItem(hDlg, IDC_PATTERN_PREVIEW), STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_PREVIEW_PATTERN_ENTROPY)));
          selected_pattern = 15;
        }   
      }

      // Show a new piece preview
      if (wmEvent == CBN_SELCHANGE && wmId == IDC_PIECES) {
        int iCurSel;
        TCHAR strPieces[25];
        HWND hwndPieces = GetDlgItem(hDlg, IDC_PIECES);
				iCurSel = SendMessage(hwndPieces, CB_GETCURSEL, 0, 0);
				SendMessage(hwndPieces, CB_GETLBTEXT, iCurSel, (LPARAM)strPieces);
        if (_tcsicmp(strPieces, L"Red Marbles") == 0) {
			    SendMessage(GetDlgItem(hDlg, IDC_PIECES_PREVIEW), STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_MARBLE_RED)));
          selected_pieces       = IDB_MARBLE_RED;
          selected_pieces_up    = IDB_MARBLE_RED_UP;
          selected_pieces_empty = IDB_MARBLE_EMPTY;
        }
        if (_tcsicmp(strPieces, L"Blue Marbles") == 0) {
			    SendMessage(GetDlgItem(hDlg, IDC_PIECES_PREVIEW), STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_MARBLE_BLUE)));
          selected_pieces       = IDB_MARBLE_BLUE;
          selected_pieces_up    = IDB_MARBLE_BLUE_UP;
          selected_pieces_empty = IDB_MARBLE_EMPTY;          
        }    
        if (_tcsicmp(strPieces, L"Lime Marbles") == 0) {
			    SendMessage(GetDlgItem(hDlg, IDC_PIECES_PREVIEW), STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_MARBLE_LIME)));
          selected_pieces       = IDB_MARBLE_LIME;
          selected_pieces_up    = IDB_MARBLE_LIME_UP;
          selected_pieces_empty = IDB_MARBLE_EMPTY;
        }
        if (_tcsicmp(strPieces, L"Brown Marbles") == 0) {
			    SendMessage(GetDlgItem(hDlg, IDC_PIECES_PREVIEW), STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_MARBLE_BROWN)));
          selected_pieces       = IDB_MARBLE_BROWN;
          selected_pieces_up    = IDB_MARBLE_BROWN_UP;
          selected_pieces_empty = IDB_MARBLE_EMPTY;
        }  
        if (_tcsicmp(strPieces, L"Purple Marbles") == 0) {
			    SendMessage(GetDlgItem(hDlg, IDC_PIECES_PREVIEW), STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)LoadBitmap(hInst, MAKEINTRESOURCE(IDB_MARBLE_PURPLE)));
          selected_pieces       = IDB_MARBLE_PURPLE;
          selected_pieces_up    = IDB_MARBLE_PURPLE_UP;
          selected_pieces_empty = IDB_MARBLE_EMPTY;
        }  
      }

		break;

	}

  return FALSE;

}