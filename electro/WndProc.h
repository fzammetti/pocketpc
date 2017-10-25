
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

	switch (message) {

		case WM_CREATE: {
			hWndPB = CreateWindow(PROGRESS_CLASS, TEXT("ProgressBar"), WS_BORDER | WS_VISIBLE, 20, 24, 200, 14, hWnd, NULL, hInst, NULL);
		}

		case WM_COMMAND: {

			if (LOWORD(wParam) == IDOK) {
				SHSipPreference(hWnd, SIP_DOWN);
				SendMessage(hWnd, WM_ACTIVATE, MAKEWPARAM(WA_INACTIVE, 0), (LPARAM)hWnd);
				SendMessage(hWnd, WM_CLOSE, 0, 0);
			}

			int wmId    = LOWORD(wParam); 
			int wmEvent = HIWORD(wParam); 

			switch (wmId) {	

				case IDM_HELP: {
					CreateProcess(TEXT("PegHelp.exe"), TEXT("Electro.htm#Main_Contents"), NULL, NULL, FALSE, 0, NULL, NULL, NULL, NULL); 
				break; }

				// Screen-specific help (the question mark on the menu bar)
				case 51928: { 
					if (hWndCurrentScreen == hWndTimer555)							 {	CreateProcess(TEXT("PegHelp.exe"), TEXT("Electro.htm#555Timer"),							 NULL, NULL, FALSE, 0, NULL, NULL, NULL, NULL); }
					if (hWndCurrentScreen == hWndDCOhmsLaw)							 {	CreateProcess(TEXT("PegHelp.exe"), TEXT("Electro.htm#DCOhmsLaw"),							 NULL, NULL, FALSE, 0, NULL, NULL, NULL, NULL); }
					if (hWndCurrentScreen == hWndDWTransforms)					 {	CreateProcess(TEXT("PegHelp.exe"), TEXT("Electro.htm#DWTransforms"),					 NULL, NULL, FALSE, 0, NULL, NULL, NULL, NULL); }
					if (hWndCurrentScreen == hWndEnergyStored)					 {	CreateProcess(TEXT("PegHelp.exe"), TEXT("Electro.htm#EnergyStored"),					 NULL, NULL, FALSE, 0, NULL, NULL, NULL, NULL); }
					if (hWndCurrentScreen == hWndImpedance)							 {	CreateProcess(TEXT("PegHelp.exe"), TEXT("Electro.htm#Impedance"),							 NULL, NULL, FALSE, 0, NULL, NULL, NULL, NULL); }
					if (hWndCurrentScreen == hWndRCICalc)								 {	CreateProcess(TEXT("PegHelp.exe"), TEXT("Electro.htm#RCICalc"),								 NULL, NULL, FALSE, 0, NULL, NULL, NULL, NULL); }
					if (hWndCurrentScreen == hWndReactance)							 {	CreateProcess(TEXT("PegHelp.exe"), TEXT("Electro.htm#Reactance"),							 NULL, NULL, FALSE, 0, NULL, NULL, NULL, NULL); }
					if (hWndCurrentScreen == hWndResistorColorCode)			 {	CreateProcess(TEXT("PegHelp.exe"), TEXT("Electro.htm#ResistorColorCode"),			 NULL, NULL, FALSE, 0, NULL, NULL, NULL, NULL); }
					if (hWndCurrentScreen == hWndResonance)							 {	CreateProcess(TEXT("PegHelp.exe"), TEXT("Electro.htm#Resonance"),							 NULL, NULL, FALSE, 0, NULL, NULL, NULL, NULL); }
					if (hWndCurrentScreen == hWndThreePhasePower)				 {	CreateProcess(TEXT("PegHelp.exe"), TEXT("Electro.htm#ThreePhasePower"),				 NULL, NULL, FALSE, 0, NULL, NULL, NULL, NULL); }
					if (hWndCurrentScreen == hWndChipReference)					 {	CreateProcess(TEXT("PegHelp.exe"), TEXT("Electro.htm#ChipReference"),					 NULL, NULL, FALSE, 0, NULL, NULL, NULL, NULL); }
					if (hWndCurrentScreen == hWndCitizensBand)					 {	CreateProcess(TEXT("PegHelp.exe"), TEXT("Electro.htm#CitizensBand"),					 NULL, NULL, FALSE, 0, NULL, NULL, NULL, NULL); }
					if (hWndCurrentScreen == hWndCommonConnectors)			 {	CreateProcess(TEXT("PegHelp.exe"), TEXT("Electro.htm#CommonConnectors"),			 NULL, NULL, FALSE, 0, NULL, NULL, NULL, NULL); }
					if (hWndCurrentScreen == hWndCopperWire)						 {	CreateProcess(TEXT("PegHelp.exe"), TEXT("Electro.htm#CopperWire"),						 NULL, NULL, FALSE, 0, NULL, NULL, NULL, NULL); }
					if (hWndCurrentScreen == hWndDialectricConstants)		 {	CreateProcess(TEXT("PegHelp.exe"), TEXT("Electro.htm#DialectricConstants"),		 NULL, NULL, FALSE, 0, NULL, NULL, NULL, NULL); }
					if (hWndCurrentScreen == hWndMetalAlloyResistances)  {	CreateProcess(TEXT("PegHelp.exe"), TEXT("Electro.htm#MetalAlloyResistances"),  NULL, NULL, FALSE, 0, NULL, NULL, NULL, NULL); }
					if (hWndCurrentScreen == hWndSchematicSymbols)			 {	CreateProcess(TEXT("PegHelp.exe"), TEXT("Electro.htm#SchematicSymbols"),			 NULL, NULL, FALSE, 0, NULL, NULL, NULL, NULL); }
					if (hWndCurrentScreen == hWndTVChannels)						 {	CreateProcess(TEXT("PegHelp.exe"), TEXT("Electro.htm#TVChannels"),						 NULL, NULL, FALSE, 0, NULL, NULL, NULL, NULL); }
					if (hWndCurrentScreen == hWndRadioFrequencySpectrum) {	CreateProcess(TEXT("PegHelp.exe"), TEXT("Electro.htm#RadioFrequencySpectrum"), NULL, NULL, FALSE, 0, NULL, NULL, NULL, NULL); }
					if (hWndCurrentScreen == hWndKFactors)							 {	CreateProcess(TEXT("PegHelp.exe"), TEXT("Electro.htm#KFactors"),							 NULL, NULL, FALSE, 0, NULL, NULL, NULL, NULL); }
					if (hWndCurrentScreen == hWndOpAmps)								 {	CreateProcess(TEXT("PegHelp.exe"), TEXT("Electro.htm#OpAmps"),								 NULL, NULL, FALSE, 0, NULL, NULL, NULL, NULL); }
					if (hWndCurrentScreen == hWndMorseCode)							 {	CreateProcess(TEXT("PegHelp.exe"), TEXT("Electro.htm#MorseCode"),							 NULL, NULL, FALSE, 0, NULL, NULL, NULL, NULL); }
				break; }

				case IDM_TIMER555: {
					ShowWindow(hWndCurrentScreen, SW_HIDE);
					hWndCurrentScreen = hWndTimer555;
					ShowWindow(hWndCurrentScreen,  SW_SHOWNORMAL);
					ShowWindow(hWndTimer555Child, SW_SHOWNORMAL);
					BringWindowToTop(hWndTimer555Child);
					SHSipPreference(hWnd, SIP_DOWN);
				break; }

				case IDM_MORSE_CODE: {
					ShowWindow(hWndCurrentScreen, SW_HIDE);
					hWndCurrentScreen = hWndMorseCode;
					ShowWindow(hWndCurrentScreen, SW_SHOWNORMAL);
					BringWindowToTop(hWndCurrentScreen);
					SHSipPreference(hWnd, SIP_DOWN);
				break; }

				case IDM_OPAMPS: {
					ShowWindow(hWndCurrentScreen, SW_HIDE);
					hWndCurrentScreen = hWndOpAmps;
					ShowWindow(hWndCurrentScreen, SW_SHOWNORMAL);
					BringWindowToTop(hWndCurrentScreen);
					SHSipPreference(hWnd, SIP_DOWN);
				break; }

				case IDM_KFACTORS: {
					ShowWindow(hWndCurrentScreen, SW_HIDE);
					hWndCurrentScreen = hWndKFactors;
					ShowWindow(hWndCurrentScreen, SW_SHOWNORMAL);
					BringWindowToTop(hWndCurrentScreen);
					SHSipPreference(hWnd, SIP_DOWN);
				break; }

				case IDM_DW_TRANS: {
					ShowWindow(hWndCurrentScreen, SW_HIDE);
					hWndCurrentScreen = hWndDWTransforms;
					ShowWindow(hWndCurrentScreen, SW_SHOWNORMAL);
					BringWindowToTop(hWndCurrentScreen);
					SHSipPreference(hWnd, SIP_DOWN);
				break; }

				case IDM_COMMON_CONNECTORS: {
					ShowWindow(hWndCurrentScreen, SW_HIDE);
					hWndCurrentScreen = hWndCommonConnectors;
					ShowWindow(hWndCurrentScreen, SW_SHOWNORMAL);
					BringWindowToTop(hWndCurrentScreen);
					SHSipPreference(hWnd, SIP_DOWN);
				break; }

				case IDM_IMPEDANCE: {
					ShowWindow(hWndCurrentScreen, SW_HIDE);
					hWndCurrentScreen = hWndImpedance;
					ShowWindow(hWndCurrentScreen, SW_SHOWNORMAL);
					BringWindowToTop(hWndCurrentScreen);
					SHSipPreference(hWnd, SIP_DOWN);
				break; }

				case IDM_ENERGY_STORED: {
					ShowWindow(hWndCurrentScreen, SW_HIDE);
					hWndCurrentScreen = hWndEnergyStored;
					ShowWindow(hWndCurrentScreen,     SW_SHOWNORMAL);
					ShowWindow(hWndEnergyStoredChild, SW_SHOWNORMAL);
					BringWindowToTop(hWndEnergyStoredChild);
					SHSipPreference(hWnd, SIP_DOWN);
				break; }

				case IDM_CITIZENS_BAND: {
					ShowWindow(hWndCurrentScreen, SW_HIDE);
					hWndCurrentScreen = hWndCitizensBand;
					ShowWindow(hWndCurrentScreen, SW_SHOWNORMAL);
					BringWindowToTop(hWndCurrentScreen);
					SHSipPreference(hWnd, SIP_DOWN);
				break; }

				case IDM_RCI_CALC: {
					ShowWindow(hWndCurrentScreen, SW_HIDE);
					hWndCurrentScreen = hWndRCICalc;
					ShowWindow(hWndCurrentScreen, SW_SHOWNORMAL);
					ShowWindow(hWndRCICalcChild,  SW_SHOWNORMAL);
					BringWindowToTop(hWndRCICalcChild);
					SHSipPreference(hWnd, SIP_DOWN);
				break; }

				case IDM_SCHEMATIC_SYMBOLS: {
					ShowWindow(hWndCurrentScreen, SW_HIDE);
					hWndCurrentScreen = hWndSchematicSymbols;
					ShowWindow(hWndCurrentScreen, SW_SHOWNORMAL);
					BringWindowToTop(hWndCurrentScreen);
					SHSipPreference(hWnd, SIP_DOWN);
				break; }

				case IDM_DC_OHMS_LAW: {
					ShowWindow(hWndCurrentScreen, SW_HIDE);
					hWndCurrentScreen = hWndDCOhmsLaw;
					ShowWindow(hWndCurrentScreen, SW_SHOWNORMAL);
					BringWindowToTop(hWndCurrentScreen);
					SHSipPreference(hWnd, SIP_DOWN);
				break; }

				case IDM_REACTANCE: {
					ShowWindow(hWndCurrentScreen, SW_HIDE);
					hWndCurrentScreen = hWndReactance;
					ShowWindow(hWndCurrentScreen,  SW_SHOWNORMAL);
					ShowWindow(hWndReactanceChild, SW_SHOWNORMAL);
					BringWindowToTop(hWndReactanceChild);
					SHSipPreference(hWnd, SIP_DOWN);
				break; }

				case IDM_RESISTOR_COLOR_CODE: {
					ShowWindow(hWndCurrentScreen, SW_HIDE);
					hWndCurrentScreen = hWndResistorColorCode;
					ShowWindow(hWndCurrentScreen, SW_SHOWNORMAL);
					BringWindowToTop(hWndCurrentScreen);
					SHSipPreference(hWnd, SIP_DOWN);
				break; }

				case IDM_RESONANCE: {
					ShowWindow(hWndCurrentScreen, SW_HIDE);
					hWndCurrentScreen = hWndResonance;
					ShowWindow(hWndCurrentScreen, SW_SHOWNORMAL);
					BringWindowToTop(hWndCurrentScreen);
					SHSipPreference(hWnd, SIP_DOWN);
				break; }

				case IDM_THREE_PHASE_POWER: {
					ShowWindow(hWndCurrentScreen, SW_HIDE);
					hWndCurrentScreen = hWndThreePhasePower;
					ShowWindow(hWndCurrentScreen, SW_SHOWNORMAL);
					BringWindowToTop(hWndCurrentScreen);
					SHSipPreference(hWnd, SIP_DOWN);
				break; }

				case IDM_CHIP_REFERENCE: {
					ShowWindow(hWndCurrentScreen, SW_HIDE);
					hWndCurrentScreen = hWndChipReference;
					ShowWindow(hWndCurrentScreen, SW_SHOWNORMAL);
					ShowWindow(hWndChipReferenceChild, SW_SHOWNORMAL);
					BringWindowToTop(hWndChipReferenceChild);
					SHSipPreference(hWnd, SIP_DOWN);
				break; }

				case IDM_TV_CHANNELS: {
					ShowWindow(hWndCurrentScreen, SW_HIDE);
					hWndCurrentScreen = hWndTVChannels;
					ShowWindow(hWndCurrentScreen, SW_SHOWNORMAL);
					BringWindowToTop(hWndCurrentScreen);
					SHSipPreference(hWnd, SIP_DOWN);
				break; }

				case IDM_RADIO_FREQUENCY_SPECTRUM: {
					ShowWindow(hWndCurrentScreen, SW_HIDE);
					hWndCurrentScreen = hWndRadioFrequencySpectrum;
					ShowWindow(hWndCurrentScreen, SW_SHOWNORMAL);
					BringWindowToTop(hWndCurrentScreen);
					SHSipPreference(hWnd, SIP_DOWN);
				break; }

				case IDM_COPPER_WIRE: {
					ShowWindow(hWndCurrentScreen, SW_HIDE);
					hWndCurrentScreen = hWndCopperWire;
					ShowWindow(hWndCurrentScreen, SW_SHOWNORMAL);
					BringWindowToTop(hWndCurrentScreen);
					SHSipPreference(hWnd, SIP_DOWN);
				break; }

				case IDM_DIALECTRIC_CONSTANTS: {
					ShowWindow(hWndCurrentScreen, SW_HIDE);
					hWndCurrentScreen = hWndDialectricConstants;
					ShowWindow(hWndCurrentScreen, SW_SHOWNORMAL);
					BringWindowToTop(hWndCurrentScreen);
					SHSipPreference(hWnd, SIP_DOWN);
				break; }

				case IDM_METAL_ALLOY_RESISTANCES: {
					ShowWindow(hWndCurrentScreen, SW_HIDE);
					hWndCurrentScreen = hWndMetalAlloyResistances;
					ShowWindow(hWndCurrentScreen, SW_SHOWNORMAL);
					BringWindowToTop(hWndCurrentScreen);
					SHSipPreference(hWnd, SIP_DOWN);
				break; }

				case IDM_ABOUT: {
					ShowWindow(hWndCurrentScreen, SW_HIDE);
					hWndCurrentScreen = hWndAbout;
					ShowWindow(hWndCurrentScreen, SW_SHOWNORMAL);
					BringWindowToTop(hWndCurrentScreen);
					SHSipPreference(hWnd, SIP_DOWN);
				break; }

				case IDM_EXIT: {
					SHSipPreference(hWnd, SIP_DOWN);
					SendMessage(hWnd, WM_ACTIVATE, MAKEWPARAM(WA_INACTIVE, 0), (LPARAM)hWnd);
					SendMessage(hWnd, WM_CLOSE, 0, 0);
				break; }

			}

		break; }

		case WM_PAINT: {
			PAINTSTRUCT ps;
			RECT rt;
			TCHAR szText[64]		 = TEXT("");
			HDC hDC							 = NULL;
			HDC hDCMem					 = NULL;
			HBITMAP hBitmap			 = NULL;
			HBITMAP hOldBitmap	 = NULL;
			hDC = BeginPaint(hWnd, &ps);
			hDCMem = CreateCompatibleDC(hDC);
			if (SplashScreen) {
				// Graphics
				hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_SPLASH_SCREEN));
				hOldBitmap = (struct HBITMAP__*)SelectObject(hDCMem, hBitmap);
				BitBlt(hDC, 0, 44, 240, 190, hDCMem, 0,0, SRCCOPY);
				// Text
				rt.top    = 7;
				rt.left   = 0;
				rt.bottom = rt.top + 20;
				rt.right  = 240;
				LoadString(hInst, IDS_INITIALIZING_PLEASE_WAIT, szText, 32);
				DrawText(hDC, szText, wcslen(szText), &rt, DT_CENTER);
				rt.top    = 235;
				rt.left   = 0;
				rt.bottom = rt.top + 20;
				rt.right  = 240;
				LoadString(hInst, IDS_VERSION, szText, 32);
				DrawText(hDC, szText, wcslen(szText), &rt, DT_CENTER);
				rt.top    = 260;
				rt.left   = 0;
				rt.bottom = rt.top + 20;
				rt.right  = 240;
				LoadString(hInst, IDS_COPYRIGHT, szText, 32);
				DrawText(hDC, szText, wcslen(szText), &rt, DT_CENTER);
				rt.top    = 275;
				rt.left   = 0;
				rt.bottom = rt.top + 20;
				rt.right  = 240;
				LoadString(hInst, IDS_ALL_RIGHTS_RESERVED, szText, 32);
				DrawText(hDC, szText, wcslen(szText), &rt, DT_CENTER);
			} else { // NOT the splash screen...
				if (!hWndCurrentScreen) {
					hBitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_TITLEPIC));
					hOldBitmap = (struct HBITMAP__*)SelectObject(hDCMem, hBitmap);
					BitBlt(hDC, 32, 45, 175, 32, hDCMem, 0,0, SRCCOPY);
					rt.top    = 86;
					rt.left   = 0;
					rt.bottom = rt.top + 20;
					rt.right  = 240;
					LoadString(hInst, IDS_VERSION, szText, 32);
					DrawText(hDC, szText, wcslen(szText), &rt, DT_CENTER);
					rt.top    = 130;
					rt.left   = 0;
					rt.bottom = rt.top + 20;
					rt.right  = 240;
					LoadString(hInst, IDS_PROGRAMMEDBY, szText, 60);
					DrawText(hDC, szText, wcslen(szText), &rt, DT_CENTER);
					rt.top    = 170;
					rt.left   = 0;
					rt.bottom = rt.top + 20;
					rt.right  = 240;
					LoadString(hInst, IDS_TITLE_1, szText, 60);
					DrawText(hDC, szText, wcslen(szText), &rt, DT_CENTER);
					rt.top    = 185;
					rt.left   = 0;
					rt.bottom = rt.top + 20;
					rt.right  = 240;
					LoadString(hInst, IDS_TITLE_2, szText, 60);
					DrawText(hDC, szText, wcslen(szText), &rt, DT_CENTER);
					rt.top    = 200;
					rt.left   = 0;
					rt.bottom = rt.top + 20;
					rt.right  = 240;
					LoadString(hInst, IDS_TITLE_3, szText, 60);
					DrawText(hDC, szText, wcslen(szText), &rt, DT_CENTER);
				}
			}
			EndPaint(hWnd, &ps);
			SelectObject(hDCMem, hOldBitmap);
			DeleteObject(hBitmap);
			DeleteObject(hOldBitmap);
			DeleteDC(hDCMem);
		break; }

		case WM_DESTROY: {
			CommandBar_Destroy(hWndCB);
			PostQuitMessage(0);
		break; }

		case WM_SETTINGCHANGE: {
			SHHandleWMSettingChange(hWnd, wParam, lParam, &s_sai);
    break; }

		default: {
			return DefWindowProc(hWnd, message, wParam, lParam);
    break; }

  }

  return 0;

}