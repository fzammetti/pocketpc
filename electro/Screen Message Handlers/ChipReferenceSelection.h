
LRESULT CALLBACK ChipReferenceSelection(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {

	switch (message) {

		case WM_INITDIALOG: {
			SHINITDLGINFO shidi;
			shidi.dwMask	= SHIDIM_FLAGS;
 		  shidi.dwFlags = SHIDIF_SIZEDLGFULLSCREEN;
			shidi.hDlg		= hDlg;
			SHInitDialog(&shidi);
      // Fill our listview
      HWND hWndLB = GetDlgItem(hDlg, IDC_CHIP_REFERENCE_LISTBOX);
			SendMessage(hWndLB, LB_SETHORIZONTALEXTENT, (WPARAM)500, 0); // Set scroll width of select box
			TCHAR outStr[128] = TEXT("");
			for (int i = 0; i < numItemsChipReference; i++) {
				wcscpy(outStr, TEXT(""));
				wcscat(outStr, ChipReferenceTable[i].szPartNumber);
				wcscat(outStr, TEXT(" - "));
				wcscat(outStr, ChipReferenceTable[i].szDescription);
				SendMessage(hWndLB, LB_ADDSTRING, 0, (LPARAM)outStr); 
      }
			return true;
		break; }

		case WM_COMMAND: {
			if (LOWORD(wParam) == IDOK) {
				ShowWindow(hWndCurrentScreen, SW_HIDE);
				SHSipPreference(hWnd, SIP_DOWN);
				return true;
			}
if (HIWORD(wParam) == EN_SETFOCUS) {
	SetFocus(GetDlgItem(hDlg, IDC_CHIP_REFERENCE_LISTBOX));
}
			// If an item is selected...
			if (HIWORD(wParam) == LBN_SELCHANGE) {
				// Get the index of our selected item
				int selectionIndex = SendMessage(GetDlgItem(hDlg, IDC_CHIP_REFERENCE_LISTBOX), LB_GETCURSEL, 0, 0);
				// Load the details for this part on the selection tab
				SetDlgItemText(hDlg, IDC_CHIP_DESCRIPTION, ChipReferenceTable[selectionIndex].szDetails);
				// Create the title text for the pinout and function table tabs and show them
				TCHAR outStr[128] = TEXT("");				
				wcscat(outStr, ChipReferenceTable[selectionIndex].szPartNumber);
				wcscat(outStr, TEXT(" - "));
				wcscat(outStr, ChipReferenceTable[selectionIndex].szDescription);
				SetDlgItemText(hWndChipReferencePinout, IDC_CHIP_DETAIL_TITLE, outStr);
				SetDlgItemText(hWndChipReferenceFunctionTable, IDC_CHIP_DETAIL_TITLE, outStr);
				// Update the pinouts for this part
				SetDlgItemText(hWndChipReferencePinout, IDC_PIN1,  ChipReferenceTable[selectionIndex].szPin1);
				SetDlgItemText(hWndChipReferencePinout, IDC_PIN2,  ChipReferenceTable[selectionIndex].szPin2);
				SetDlgItemText(hWndChipReferencePinout, IDC_PIN3,  ChipReferenceTable[selectionIndex].szPin3);
				SetDlgItemText(hWndChipReferencePinout, IDC_PIN4,  ChipReferenceTable[selectionIndex].szPin4);
				SetDlgItemText(hWndChipReferencePinout, IDC_PIN5,  ChipReferenceTable[selectionIndex].szPin5);
				SetDlgItemText(hWndChipReferencePinout, IDC_PIN6,  ChipReferenceTable[selectionIndex].szPin6);
				SetDlgItemText(hWndChipReferencePinout, IDC_PIN7,  ChipReferenceTable[selectionIndex].szPin7);
				SetDlgItemText(hWndChipReferencePinout, IDC_PIN8,  ChipReferenceTable[selectionIndex].szPin8);
				SetDlgItemText(hWndChipReferencePinout, IDC_PIN9,  ChipReferenceTable[selectionIndex].szPin9);
				SetDlgItemText(hWndChipReferencePinout, IDC_PIN10, ChipReferenceTable[selectionIndex].szPin10);
				SetDlgItemText(hWndChipReferencePinout, IDC_PIN11, ChipReferenceTable[selectionIndex].szPin11);
				SetDlgItemText(hWndChipReferencePinout, IDC_PIN12, ChipReferenceTable[selectionIndex].szPin12);
				SetDlgItemText(hWndChipReferencePinout, IDC_PIN13, ChipReferenceTable[selectionIndex].szPin13);
				SetDlgItemText(hWndChipReferencePinout, IDC_PIN14, ChipReferenceTable[selectionIndex].szPin14);
				// Build the function table headers
				SetDlgItemText(hWndChipReferenceFunctionTable, IDC_FT_COL_1_HEAD, ChipReferenceTable[selectionIndex].szFTCol1Head);
				SetDlgItemText(hWndChipReferenceFunctionTable, IDC_FT_COL_2_HEAD, ChipReferenceTable[selectionIndex].szFTCol2Head);
				SetDlgItemText(hWndChipReferenceFunctionTable, IDC_FT_COL_3_HEAD, ChipReferenceTable[selectionIndex].szFTCol3Head);
				SetDlgItemText(hWndChipReferenceFunctionTable, IDC_FT_COL_4_HEAD, ChipReferenceTable[selectionIndex].szFTCol4Head);
				SetDlgItemText(hWndChipReferenceFunctionTable, IDC_FT_COL_5_HEAD, ChipReferenceTable[selectionIndex].szFTCol5Head);
				SetDlgItemText(hWndChipReferenceFunctionTable, IDC_FT_COL_6_HEAD, ChipReferenceTable[selectionIndex].szFTCol6Head);
				SetDlgItemText(hWndChipReferenceFunctionTable, IDC_FT_COL_7_HEAD, ChipReferenceTable[selectionIndex].szFTCol7Head);
				// Build the function table row 1
				SetDlgItemText(hWndChipReferenceFunctionTable, IDC_FT_ROW_1_1, ChipReferenceTable[selectionIndex].szFTRow1_1);
				SetDlgItemText(hWndChipReferenceFunctionTable, IDC_FT_ROW_1_2, ChipReferenceTable[selectionIndex].szFTRow1_2);
				SetDlgItemText(hWndChipReferenceFunctionTable, IDC_FT_ROW_1_3, ChipReferenceTable[selectionIndex].szFTRow1_3);
				SetDlgItemText(hWndChipReferenceFunctionTable, IDC_FT_ROW_1_4, ChipReferenceTable[selectionIndex].szFTRow1_4);
				SetDlgItemText(hWndChipReferenceFunctionTable, IDC_FT_ROW_1_5, ChipReferenceTable[selectionIndex].szFTRow1_5);
				SetDlgItemText(hWndChipReferenceFunctionTable, IDC_FT_ROW_1_6, ChipReferenceTable[selectionIndex].szFTRow1_6);
				SetDlgItemText(hWndChipReferenceFunctionTable, IDC_FT_ROW_1_7, ChipReferenceTable[selectionIndex].szFTRow1_7);
				// Build the function table row 2
				SetDlgItemText(hWndChipReferenceFunctionTable, IDC_FT_ROW_2_1, ChipReferenceTable[selectionIndex].szFTRow2_1);
				SetDlgItemText(hWndChipReferenceFunctionTable, IDC_FT_ROW_2_2, ChipReferenceTable[selectionIndex].szFTRow2_2);
				SetDlgItemText(hWndChipReferenceFunctionTable, IDC_FT_ROW_2_3, ChipReferenceTable[selectionIndex].szFTRow2_3);
				SetDlgItemText(hWndChipReferenceFunctionTable, IDC_FT_ROW_2_4, ChipReferenceTable[selectionIndex].szFTRow2_4);
				SetDlgItemText(hWndChipReferenceFunctionTable, IDC_FT_ROW_2_5, ChipReferenceTable[selectionIndex].szFTRow2_5);
				SetDlgItemText(hWndChipReferenceFunctionTable, IDC_FT_ROW_2_6, ChipReferenceTable[selectionIndex].szFTRow2_6);
				SetDlgItemText(hWndChipReferenceFunctionTable, IDC_FT_ROW_2_7, ChipReferenceTable[selectionIndex].szFTRow2_7);
				// Build the function table row 3
				SetDlgItemText(hWndChipReferenceFunctionTable, IDC_FT_ROW_3_1, ChipReferenceTable[selectionIndex].szFTRow3_1);
				SetDlgItemText(hWndChipReferenceFunctionTable, IDC_FT_ROW_3_2, ChipReferenceTable[selectionIndex].szFTRow3_2);
				SetDlgItemText(hWndChipReferenceFunctionTable, IDC_FT_ROW_3_3, ChipReferenceTable[selectionIndex].szFTRow3_3);
				SetDlgItemText(hWndChipReferenceFunctionTable, IDC_FT_ROW_3_4, ChipReferenceTable[selectionIndex].szFTRow3_4);
				SetDlgItemText(hWndChipReferenceFunctionTable, IDC_FT_ROW_3_5, ChipReferenceTable[selectionIndex].szFTRow3_5);
				SetDlgItemText(hWndChipReferenceFunctionTable, IDC_FT_ROW_3_6, ChipReferenceTable[selectionIndex].szFTRow3_6);
				SetDlgItemText(hWndChipReferenceFunctionTable, IDC_FT_ROW_3_7, ChipReferenceTable[selectionIndex].szFTRow3_7);
				// Build the function table row 4
				SetDlgItemText(hWndChipReferenceFunctionTable, IDC_FT_ROW_4_1, ChipReferenceTable[selectionIndex].szFTRow4_1);
				SetDlgItemText(hWndChipReferenceFunctionTable, IDC_FT_ROW_4_2, ChipReferenceTable[selectionIndex].szFTRow4_2);
				SetDlgItemText(hWndChipReferenceFunctionTable, IDC_FT_ROW_4_3, ChipReferenceTable[selectionIndex].szFTRow4_3);
				SetDlgItemText(hWndChipReferenceFunctionTable, IDC_FT_ROW_4_4, ChipReferenceTable[selectionIndex].szFTRow4_4);
				SetDlgItemText(hWndChipReferenceFunctionTable, IDC_FT_ROW_4_5, ChipReferenceTable[selectionIndex].szFTRow4_5);
				SetDlgItemText(hWndChipReferenceFunctionTable, IDC_FT_ROW_4_6, ChipReferenceTable[selectionIndex].szFTRow4_6);
				SetDlgItemText(hWndChipReferenceFunctionTable, IDC_FT_ROW_4_7, ChipReferenceTable[selectionIndex].szFTRow4_7);
				// Build the function table row 5
				SetDlgItemText(hWndChipReferenceFunctionTable, IDC_FT_ROW_5_1, ChipReferenceTable[selectionIndex].szFTRow5_1);
				SetDlgItemText(hWndChipReferenceFunctionTable, IDC_FT_ROW_5_2, ChipReferenceTable[selectionIndex].szFTRow5_2);
				SetDlgItemText(hWndChipReferenceFunctionTable, IDC_FT_ROW_5_3, ChipReferenceTable[selectionIndex].szFTRow5_3);
				SetDlgItemText(hWndChipReferenceFunctionTable, IDC_FT_ROW_5_4, ChipReferenceTable[selectionIndex].szFTRow5_4);
				SetDlgItemText(hWndChipReferenceFunctionTable, IDC_FT_ROW_5_5, ChipReferenceTable[selectionIndex].szFTRow5_5);
				SetDlgItemText(hWndChipReferenceFunctionTable, IDC_FT_ROW_5_6, ChipReferenceTable[selectionIndex].szFTRow5_6);
				SetDlgItemText(hWndChipReferenceFunctionTable, IDC_FT_ROW_5_7, ChipReferenceTable[selectionIndex].szFTRow5_7);
				// Build the function table row 6
				SetDlgItemText(hWndChipReferenceFunctionTable, IDC_FT_ROW_6_1, ChipReferenceTable[selectionIndex].szFTRow6_1);
				SetDlgItemText(hWndChipReferenceFunctionTable, IDC_FT_ROW_6_2, ChipReferenceTable[selectionIndex].szFTRow6_2);
				SetDlgItemText(hWndChipReferenceFunctionTable, IDC_FT_ROW_6_3, ChipReferenceTable[selectionIndex].szFTRow6_3);
				SetDlgItemText(hWndChipReferenceFunctionTable, IDC_FT_ROW_6_4, ChipReferenceTable[selectionIndex].szFTRow6_4);
				SetDlgItemText(hWndChipReferenceFunctionTable, IDC_FT_ROW_6_5, ChipReferenceTable[selectionIndex].szFTRow6_5);
				SetDlgItemText(hWndChipReferenceFunctionTable, IDC_FT_ROW_6_6, ChipReferenceTable[selectionIndex].szFTRow6_6);
				SetDlgItemText(hWndChipReferenceFunctionTable, IDC_FT_ROW_6_7, ChipReferenceTable[selectionIndex].szFTRow6_7);
				// Build the function table row 7
				SetDlgItemText(hWndChipReferenceFunctionTable, IDC_FT_ROW_7_1, ChipReferenceTable[selectionIndex].szFTRow7_1);
				SetDlgItemText(hWndChipReferenceFunctionTable, IDC_FT_ROW_7_2, ChipReferenceTable[selectionIndex].szFTRow7_2);
				SetDlgItemText(hWndChipReferenceFunctionTable, IDC_FT_ROW_7_3, ChipReferenceTable[selectionIndex].szFTRow7_3);
				SetDlgItemText(hWndChipReferenceFunctionTable, IDC_FT_ROW_7_4, ChipReferenceTable[selectionIndex].szFTRow7_4);
				SetDlgItemText(hWndChipReferenceFunctionTable, IDC_FT_ROW_7_5, ChipReferenceTable[selectionIndex].szFTRow7_5);
				SetDlgItemText(hWndChipReferenceFunctionTable, IDC_FT_ROW_7_6, ChipReferenceTable[selectionIndex].szFTRow7_6);
				SetDlgItemText(hWndChipReferenceFunctionTable, IDC_FT_ROW_7_7, ChipReferenceTable[selectionIndex].szFTRow7_7);
				// Build the function table row 8
				SetDlgItemText(hWndChipReferenceFunctionTable, IDC_FT_ROW_8_1, ChipReferenceTable[selectionIndex].szFTRow8_1);
				SetDlgItemText(hWndChipReferenceFunctionTable, IDC_FT_ROW_8_2, ChipReferenceTable[selectionIndex].szFTRow8_2);
				SetDlgItemText(hWndChipReferenceFunctionTable, IDC_FT_ROW_8_3, ChipReferenceTable[selectionIndex].szFTRow8_3);
				SetDlgItemText(hWndChipReferenceFunctionTable, IDC_FT_ROW_8_4, ChipReferenceTable[selectionIndex].szFTRow8_4);
				SetDlgItemText(hWndChipReferenceFunctionTable, IDC_FT_ROW_8_5, ChipReferenceTable[selectionIndex].szFTRow8_5);
				SetDlgItemText(hWndChipReferenceFunctionTable, IDC_FT_ROW_8_6, ChipReferenceTable[selectionIndex].szFTRow8_6);
				SetDlgItemText(hWndChipReferenceFunctionTable, IDC_FT_ROW_8_7, ChipReferenceTable[selectionIndex].szFTRow8_7);
			} 
		break; }

		default: {
			return DefWindowProc(hWnd, message, wParam, lParam);
    break; }

	}

  return FALSE;

}
  