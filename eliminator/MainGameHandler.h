void doMove(HWND, int, int, int);
void checkMoreMoves(HWND);
LRESULT CALLBACK WonLost(HWND, UINT, WPARAM, LPARAM);

LRESULT CALLBACK MainGameHandler(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	
	SHINITDLGINFO shidi;
	TCHAR strElapsed[8] = L"", strTemp[5] = L"";

	switch (message) {

		case WM_INITDIALOG:
			// Create a Done button and size it.  
			shidi.dwMask = SHIDIM_FLAGS;
			shidi.dwFlags = SHIDIF_SIPDOWN | SHIDIF_SIZEDLGFULLSCREEN;
			shidi.hDlg = hDlg;
			SHInitDialog(&shidi);
			SHSipPreference(hDlg, SIP_DOWN);
			return TRUE; 
		break;

		case WM_TIMER:
			// Update the timer if a game is in progress
			if (game_in_progress == true) {
				// Do the actual math... simple...
				elapsed_seconds++;
				if (elapsed_seconds > 60) {
					elapsed_seconds = 0;
					elapsed_minutes++;
				}
				// Clear our strings
				_tcscpy(strTemp, L"");
				_tcscpy(strElapsed, L"");
				// Zero-fill the minutes if applicable
				if (elapsed_minutes < 10) {
					_tcscat(strElapsed, L"0");
				}
				// Copy in the minutes and the colon
				_stprintf(strTemp, TEXT("%d"), elapsed_minutes);
				_tcscat(strElapsed, strTemp);
				_tcscat(strElapsed, L":");
				_tcscpy(strTemp, L"");
				// Zero-fill the seconds if applicable
				if (elapsed_seconds < 10) {
					_tcscat(strElapsed, L"0");
				}
				// Copy in the seconds and show it
				_stprintf(strTemp, TEXT("%d"), elapsed_seconds);
				_tcscat(strElapsed, strTemp);
				SetDlgItemText(hDlg, IDC_ELAPSED, strElapsed);
			}
		break;

		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK) {
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}

			int wmId    = LOWORD(wParam); 
			int wmEvent = HIWORD(wParam); 

      switch (wmId) {	

        case IDC_TILE_1_1:
					doMove(hDlg, 1,  1,  wmId);
				break;
        case IDC_TILE_1_2:
					doMove(hDlg, 1,  2,  wmId);
				break;
        case IDC_TILE_1_3:
					doMove(hDlg, 1,  3,  wmId);
				break;
        case IDC_TILE_1_4:
					doMove(hDlg, 1,  4,  wmId);
				break;
        case IDC_TILE_1_5:
					doMove(hDlg, 1,  5,  wmId);
				break;
        case IDC_TILE_1_6:
					doMove(hDlg, 1,  6,  wmId);
				break;
        case IDC_TILE_1_7:
					doMove(hDlg, 1,  7,  wmId);
				break;
        case IDC_TILE_1_8:
					doMove(hDlg, 1,  8,  wmId);
				break;
        case IDC_TILE_1_9:
					doMove(hDlg, 1,  9,  wmId);
				break;
        case IDC_TILE_1_10:
					doMove(hDlg, 1,  10, wmId);
				break;
        case IDC_TILE_2_1:
					doMove(hDlg, 2,  1,  wmId);
				break;
        case IDC_TILE_2_2:
					doMove(hDlg, 2,  2,  wmId);
				break;
        case IDC_TILE_2_3:
					doMove(hDlg, 2,  3,  wmId);
				break;
        case IDC_TILE_2_4:
					doMove(hDlg, 2,  4,  wmId);
				break;
        case IDC_TILE_2_5:
					doMove(hDlg, 2,  5,  wmId);
				break;
        case IDC_TILE_2_6:
					doMove(hDlg, 2,  6,  wmId);
				break;
        case IDC_TILE_2_7:
					doMove(hDlg, 2,  7,  wmId);
				break;
        case IDC_TILE_2_8:
					doMove(hDlg, 2,  8,  wmId);
				break;
        case IDC_TILE_2_9:
					doMove(hDlg, 2,  9,  wmId);
				break;
        case IDC_TILE_2_10:
					doMove(hDlg, 2,  10, wmId);
				break;
        case IDC_TILE_3_1:
					doMove(hDlg, 3,  1,  wmId);
				break;
        case IDC_TILE_3_2:
					doMove(hDlg, 3,  2,  wmId);
				break;
        case IDC_TILE_3_3:
					doMove(hDlg, 3,  3,  wmId);
				break;
        case IDC_TILE_3_4:
					doMove(hDlg, 3,  4,  wmId);
				break;
        case IDC_TILE_3_5:
					doMove(hDlg, 3,  5,  wmId);
				break;
        case IDC_TILE_3_6:
					doMove(hDlg, 3,  6,  wmId);
				break;
        case IDC_TILE_3_7:
					doMove(hDlg, 3,  7,  wmId);
				break;
        case IDC_TILE_3_8:
					doMove(hDlg, 3,  8,  wmId);
				break;
        case IDC_TILE_3_9:
					doMove(hDlg, 3,  9,  wmId);
				break;
        case IDC_TILE_3_10:
					doMove(hDlg, 3,  10, wmId);
				break;
        case IDC_TILE_4_1:
					doMove(hDlg, 4,  1,  wmId);
				break;
        case IDC_TILE_4_2:
					doMove(hDlg, 4,  2,  wmId);
				break;
        case IDC_TILE_4_3:
					doMove(hDlg, 4,  3,  wmId);
				break;
        case IDC_TILE_4_4:
					doMove(hDlg, 4,  4,  wmId);
				break;
        case IDC_TILE_4_5:
					doMove(hDlg, 4,  5,  wmId);
				break;
        case IDC_TILE_4_6:
					doMove(hDlg, 4,  6,  wmId);
				break;
        case IDC_TILE_4_7:
					doMove(hDlg, 4,  7,  wmId);
				break;
        case IDC_TILE_4_8:
					doMove(hDlg, 4,  8,  wmId);
				break;
        case IDC_TILE_4_9:
					doMove(hDlg, 4,  9,  wmId);
				break;
        case IDC_TILE_4_10:
					doMove(hDlg, 4,  10, wmId);
				break;
        case IDC_TILE_5_1:
					doMove(hDlg, 5,  1,  wmId);
				break;
        case IDC_TILE_5_2:
					doMove(hDlg, 5,  2,  wmId);
				break;
        case IDC_TILE_5_3:
					doMove(hDlg, 5,  3,  wmId);
				break;
        case IDC_TILE_5_4:
					doMove(hDlg, 5,  4,  wmId);
				break;
        case IDC_TILE_5_5:
					doMove(hDlg, 5,  5,  wmId);
				break;
        case IDC_TILE_5_6:
					doMove(hDlg, 5,  6,  wmId);
				break;
        case IDC_TILE_5_7:
					doMove(hDlg, 5,  7,  wmId);
				break;
        case IDC_TILE_5_8:
					doMove(hDlg, 5,  8,  wmId);
				break;
        case IDC_TILE_5_9:
					doMove(hDlg, 5,  9,  wmId);
				break;
        case IDC_TILE_5_10:
					doMove(hDlg, 5,  10, wmId);
				break;
        case IDC_TILE_6_1:
					doMove(hDlg, 6,  1,  wmId);
				break;
        case IDC_TILE_6_2:
					doMove(hDlg, 6,  2,  wmId);
				break;
        case IDC_TILE_6_3:
					doMove(hDlg, 6,  3,  wmId);
				break;
        case IDC_TILE_6_4:
					doMove(hDlg, 6,  4,  wmId);
				break;
        case IDC_TILE_6_5:
					doMove(hDlg, 6,  5,  wmId);
				break;
        case IDC_TILE_6_6:
					doMove(hDlg, 6,  6,  wmId);
				break;
        case IDC_TILE_6_7:
					doMove(hDlg, 6,  7,  wmId);
				break;
        case IDC_TILE_6_8:
					doMove(hDlg, 6,  8,  wmId);
				break;
        case IDC_TILE_6_9:
					doMove(hDlg, 6,  9,  wmId);
				break;
        case IDC_TILE_6_10:
					doMove(hDlg, 6,  10, wmId);
				break;
        case IDC_TILE_7_1:
					doMove(hDlg, 7,  1,  wmId);
				break;
        case IDC_TILE_7_2:
					doMove(hDlg, 7,  2,  wmId);
				break;
        case IDC_TILE_7_3:
					doMove(hDlg, 7,  3,  wmId);
				break;
        case IDC_TILE_7_4:
					doMove(hDlg, 7,  4,  wmId);
				break;
        case IDC_TILE_7_5:
					doMove(hDlg, 7,  5,  wmId);
				break;
        case IDC_TILE_7_6:
					doMove(hDlg, 7,  6,  wmId);
				break;
        case IDC_TILE_7_7:
					doMove(hDlg, 7,  7,  wmId);
				break;
        case IDC_TILE_7_8:
					doMove(hDlg, 7,  8,  wmId);
				break;
        case IDC_TILE_7_9:
					doMove(hDlg, 7,  9,  wmId);
				break;
        case IDC_TILE_7_10:
					doMove(hDlg, 7,  10, wmId);
				break;
        case IDC_TILE_8_1:
					doMove(hDlg, 8,  1,  wmId);
				break;
        case IDC_TILE_8_2:
					doMove(hDlg, 8,  2,  wmId);
				break;
        case IDC_TILE_8_3:
					doMove(hDlg, 8,  3,  wmId);
				break;
        case IDC_TILE_8_4:
					doMove(hDlg, 8,  4,  wmId);
				break;
        case IDC_TILE_8_5:
					doMove(hDlg, 8,  5,  wmId);
				break;
        case IDC_TILE_8_6:
					doMove(hDlg, 8,  6,  wmId);
				break;
        case IDC_TILE_8_7:
					doMove(hDlg, 8,  7,  wmId);
				break;
        case IDC_TILE_8_8:
					doMove(hDlg, 8,  8,  wmId);
				break;
        case IDC_TILE_8_9:
					doMove(hDlg, 8,  9,  wmId);
				break;
        case IDC_TILE_8_10:
					doMove(hDlg, 8,  10, wmId);
				break;
        case IDC_TILE_9_1:
					doMove(hDlg, 9,  1,  wmId);
				break;
        case IDC_TILE_9_2:
					doMove(hDlg, 9,  2,  wmId);
				break;
        case IDC_TILE_9_3:
					doMove(hDlg, 9,  3,  wmId);
				break;
        case IDC_TILE_9_4:
					doMove(hDlg, 9,  4,  wmId);
				break;
        case IDC_TILE_9_5:
					doMove(hDlg, 9,  5,  wmId);
				break;
        case IDC_TILE_9_6:
					doMove(hDlg, 9,  6,  wmId);
				break;
        case IDC_TILE_9_7:
					doMove(hDlg, 9,  7,  wmId);
				break;
        case IDC_TILE_9_8:
					doMove(hDlg, 9,  8,  wmId);
				break;
        case IDC_TILE_9_9:
					doMove(hDlg, 9,  9,  wmId);
				break;
        case IDC_TILE_9_10:
					doMove(hDlg, 9,  10, wmId);
				break;
        case IDC_TILE_10_1:
					doMove(hDlg, 10, 1,  wmId);
				break;
        case IDC_TILE_10_2:
					doMove(hDlg, 10, 2,  wmId);
				break;
        case IDC_TILE_10_3:
					doMove(hDlg, 10, 3,  wmId);
				break;
        case IDC_TILE_10_4:
					doMove(hDlg, 10, 4,  wmId);
				break;
        case IDC_TILE_10_5:
					doMove(hDlg, 10, 5,  wmId);
				break;
        case IDC_TILE_10_6:
					doMove(hDlg, 10, 6,  wmId);
				break;
        case IDC_TILE_10_7:
					doMove(hDlg, 10, 7,  wmId);
				break;
        case IDC_TILE_10_8:
					doMove(hDlg, 10, 8,  wmId);
				break;
        case IDC_TILE_10_9:
					doMove(hDlg, 10, 9,  wmId);
				break;
        case IDC_TILE_10_10:
					doMove(hDlg, 10, 10, wmId);
				break;

			}

		break;

	}

  return FALSE;

}


// This routine is called whenever a tile is clicked on.  It changes the status of
// the tiles appropriately depending on the condition of the clicked tile, and the
// relevant tiles around it
void doMove(HWND hwnddlg, int clicked_y, int clicked_x, int what_tile) {
	if (game_in_progress == false) { return; }
	TCHAR strPiecesRemaining[5] = L"";
  // If its a playable piece, raise it up, and lower the current piece if one is raised
	if (CurrentStates[clicked_y][clicked_x] == filled_tile) {
		if (piece_up == true) { // Lower currently up piece
			SendMessage(GetDlgItem(hwnd_Playfield, current_up_tile), STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)LoadBitmap(hInst, MAKEINTRESOURCE(what_graphic)));
			CurrentStates[current_y][current_x] = filled_tile;			
		}
		current_up_tile = what_tile; // Record the new tile as our current tile
		SendMessage(GetDlgItem(hwnd_Playfield, what_tile), STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)LoadBitmap(hInst, MAKEINTRESOURCE(what_graphic_up)));
		CurrentStates[clicked_y][clicked_x] = current_piece;
    piece_up = true;
		current_x = clicked_x;
    current_y = clicked_y;
		if (sound_enabled == true) {
			PlaySound((unsigned short *) IDR_PIECE_UP, hInst, SND_RESOURCE | SND_ASYNC);
		}
	// If its the piece that's already up, put it down
	} else if (CurrentStates[clicked_y][clicked_x] == current_piece) {
		SendMessage(GetDlgItem(hwnd_Playfield, what_tile), STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)LoadBitmap(hInst, MAKEINTRESOURCE(what_graphic)));
		CurrentStates[clicked_y][clicked_x] = filled_tile;
		piece_up = false;
		if (sound_enabled == true) {
			PlaySound((unsigned short *) IDR_PIECE_DOWN, hInst, SND_RESOURCE | SND_ASYNC);
		}
	// If its an empty peg and a piece is up...
	}	else if (CurrentStates[clicked_y][clicked_x] == 1 && piece_up == true) {
		// Go through each possible move.  Make sure its geometrically a valid move
    // and make sure there is a playable piece in between the source and destination
		// If it passes both tests, update the status of the middle peg...
		int valid_move = 0;
		int middle_y, middle_x;
		if ((clicked_y == (current_y-2)) && (clicked_x == (current_x+0)) && (CurrentStates[current_y-1][current_x+0] == filled_tile)) {
			valid_move = 1; middle_y = current_y - 1; middle_x = current_x + 0;
		} else if ((clicked_y == (current_y+2)) && (clicked_x == (current_x+0)) && (CurrentStates[current_y+1][current_x+0] == filled_tile)) {
			valid_move = 1; middle_y = current_y + 1; middle_x = current_x + 0;
		} else if ((clicked_y == (current_y+0)) && (clicked_x == (current_x-2)) && (CurrentStates[current_y+0][current_x-1] == filled_tile)) {
			valid_move = 1; middle_y = current_y + 0; middle_x = current_x - 1;
		} else if ((clicked_y == (current_y+0)) && (clicked_x == (current_x+2)) && (CurrentStates[current_y+0][current_x+1] == filled_tile)) {
			valid_move = 1; middle_y = current_y + 0; middle_x = current_x + 1;
		} else if ((clicked_y == (current_y-2)) && (clicked_x == (current_x-2)) && (CurrentStates[current_y-1][current_x-1] == filled_tile)) {
			valid_move = 1; middle_y = current_y - 1; middle_x = current_x - 1;
		} else if ((clicked_y == (current_y-2)) && (clicked_x == (current_x+2)) && (CurrentStates[current_y-1][current_x+1] == filled_tile)) {
			valid_move = 1; middle_y = current_y - 1; middle_x = current_x + 1;
		} else if ((clicked_y == (current_y+2)) && (clicked_x == (current_x-2)) && (CurrentStates[current_y+1][current_x-1] == filled_tile)) {
			valid_move = 1; middle_y = current_y + 1; middle_x = current_x - 1;
		} else if ((clicked_y == (current_y+2)) && (clicked_x == (current_x+2)) && (CurrentStates[current_y+1][current_x+1] == filled_tile)) {
			valid_move = 1; middle_y = current_y + 1; middle_x = current_x + 1;
		}
		// If a valid move was made, update the status of the source and destination
		// and update the graphics accordingly:
		if (valid_move == 1) {
			// Make sure we set our flag so we know no pieces are up now
			piece_up = false;
			// Click piece:   set pattern value to filled and image to filled
			CurrentStates[clicked_y][clicked_x] = filled_tile;
			SendMessage(GetDlgItem(hwnd_Playfield, Tiles[clicked_y][clicked_x]), STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)LoadBitmap(hInst, MAKEINTRESOURCE(what_graphic)));
 			// Current piece: set pattern value to empty and image to empty
			CurrentStates[current_y][current_x] = empty_tile;
			SendMessage(GetDlgItem(hwnd_Playfield, Tiles[current_y][current_x]), STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)LoadBitmap(hInst, MAKEINTRESOURCE(what_graphic_empty)));
			// Middle piece:  set pattern value to empty and image to empty
			CurrentStates[middle_y][middle_x] = empty_tile;
			SendMessage(GetDlgItem(hwnd_Playfield, Tiles[middle_y][middle_x]), STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)LoadBitmap(hInst, MAKEINTRESOURCE(what_graphic_empty)));
      pieces_remaining--;
			_stprintf(strPiecesRemaining, TEXT("%d"), pieces_remaining);
			SetDlgItemText(hwnd_Playfield, IDC_REMAINING, strPiecesRemaining);
			if (sound_enabled == true) {
				PlaySound((unsigned short *) IDR_PIECE_REMOVE, hInst, SND_RESOURCE | SND_ASYNC);
			} 
      checkMoreMoves(hwnddlg);
		}
	}
}


// This routine checks to see if there are any moves remaining after the last move made 
void checkMoreMoves(HWND hwnddlg) {
  int moves_left = 0;
  for (int y = 1; y < 11; y++) {
    for (int x = 1; x < 11; x++) {
      if (CurrentStates[y][x] == filled_tile) {
        if (
            (CurrentStates[y+1][x+0] == filled_tile &&
             CurrentStates[y-1][x-0] == empty_tile) ||
            (CurrentStates[y-1][x+0] == filled_tile &&
             CurrentStates[y+1][x-0] == empty_tile) ||
            (CurrentStates[y+0][x+1] == filled_tile &&
             CurrentStates[y-0][x-1] == empty_tile) ||
            (CurrentStates[y+0][x-1] == filled_tile &&
             CurrentStates[y-0][x+1] == empty_tile) ||
            (CurrentStates[y+1][x-1] == filled_tile &&
             CurrentStates[y-1][x+1] == empty_tile) ||
            (CurrentStates[y-1][x+1] == filled_tile &&
             CurrentStates[y+1][x-1] == empty_tile) ||
            (CurrentStates[y+1][x+1] == filled_tile &&
             CurrentStates[y-1][x-1] == empty_tile) ||
            (CurrentStates[y-1][x-1] == filled_tile &&
             CurrentStates[y+1][x+1] == empty_tile)
           ) {
          moves_left = 1;
        }
      }
    }
  }
  if (moves_left == 0) { 
    game_in_progress = false;
		what_sound = (rand() * 10 / (RAND_MAX + 1)) + 1;
		if (pieces_remaining == 1) { // Won
			game_won = true;
    } else { // Lost
			game_won = false;
    }
		DialogBox(hInst, (LPCTSTR)IDD_WONLOST, hWnd, (DLGPROC)WonLost);
  }
}