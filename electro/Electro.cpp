
// ================================================================================================
// Electro Version 1.2
// Programed by Frank W. Zammetti
// ================================================================================================




// ************************************************************************************************
// Header includes - SYSTEM HEADERS
// ************************************************************************************************
#include "stdafx.h"
#include "Electro.h"
#include <commctrl.h>
#include <aygshell.h>
#include <sipapi.h>
#include <math.h>
#include <tchar.h>




// ************************************************************************************************
// Defines
// ************************************************************************************************
#define Trial true
#define Pi    3.1415926536




// ************************************************************************************************
// Global variable declarations and initializations
// ************************************************************************************************
static SHACTIVATEINFO s_sai;	 									 // For SIP changes
HINSTANCE hInst 												 = NULL; // Handle of the application instance
HWND			hWndCB 												 = NULL; // Handle of our ommand bar
HWND			hWndPB												 = NULL;
HWND			hWnd													 = NULL; // Handle of our application
bool			SplashScreen									 = true; // Is the splash screen still showing?
bool			sortDir												 = false;

HWND			hWndCurrentScreen							 = NULL;

HWND			hWndAbout											 = NULL;
HWND			hWndDCOhmsLaw									 = NULL;
HWND			hWndKFactors									 = NULL;
HWND			hWndDialectricConstants				 = NULL;
HWND			hWndSchematicSymbols					 = NULL;
HWND			hWndMetalAlloyResistances			 = NULL;
HWND			hWndTVChannels								 = NULL;
HWND			hWndResistorColorCode					 = NULL;
HWND			hWndDWTransforms							 = NULL;
HWND			hWndResonance									 = NULL;
HWND			hWndCopperWire								 = NULL;
HWND			hWndOpAmps				 					   = NULL;
HWND			hWndCommonConnectors					 = NULL;
HWND			hWndImpedance									 = NULL;
HWND			hWndCitizensBand							 = NULL;
HWND			hWndThreePhasePower						 = NULL;
HWND			hWndMorseCode									 = NULL;
HWND			hWndRadioFrequencySpectrum		 = NULL;

HWND			hWndChipReference							 = NULL;
HWND			hWndChipReferenceChild				 = NULL;
HWND			hWndChipReferenceSelection		 = NULL;
HWND			hWndChipReferencePinout				 = NULL;
HWND			hWndChipReferenceFunctionTable = NULL;

HWND			hWndReactance									 = NULL;
HWND			hWndReactanceChild						 = NULL;
HWND			hWndReactanceInductive				 = NULL; 
HWND			hWndReactanceCapacitive				 = NULL;

HWND			hWndRCICalc										 = NULL;
HWND			hWndRCICalcChild							 = NULL;
HWND			hWndRCICalcResistance					 = NULL;
HWND			hWndRCICalcCapacitance				 = NULL;
HWND			hWndRCICalcInductance					 = NULL;

HWND			hWndEnergyStored							 = NULL;
HWND			hWndEnergyStoredChild					 = NULL;
HWND			hWndEnergyStoredCapacitor			 = NULL; 
HWND			hWndEnergyStoredInductor			 = NULL;

HWND			hWndTimer555									 = NULL;
HWND			hWndTimer555Child							 = NULL;
HWND			hWndTimer555Monostable				 = NULL;
HWND			hWndTimer555Astable						 = NULL;




// ************************************************************************************************
// Header includes - SCREEN HANDLERS
// ************************************************************************************************
#include "WndProc.h"
#include "MiscFuncs.h"
#include ".\Screen Message Handlers\About.h"
#include ".\Screen Data\ChipReferenceData.h"
#include ".\Screen Message Handlers\ChipReference.h"
#include ".\Screen Message Handlers\ChipReferenceSelection.h"
#include ".\Screen Message Handlers\ChipReferencePinout.h"
#include ".\Screen Message Handlers\ChipReferenceFunctionTable.h"
#include ".\Screen Message Handlers\DCOhmsLaw.h"
#include ".\Screen Data\DialectricConstantsData.h"
#include ".\Screen Message Handlers\DialectricConstants.h"
#include ".\Screen Data\MetalAlloyResistancesData.h"
#include ".\Screen Message Handlers\MetalAlloyResistances.h"
#include ".\Screen Data\SchematicSymbolsData.h"
#include ".\Screen Message Handlers\SchematicSymbols.h"
#include ".\Screen Message Handlers\Reactance.h"
#include ".\Screen Message Handlers\ReactanceInductive.h"
#include ".\Screen Message Handlers\ReactanceCapacitive.h"
#include ".\Screen Message Handlers\ResistorColorCode.h"
#include ".\Screen Message Handlers\Resonance.h"
#include ".\Screen Message Handlers\Impedance.h"
#include ".\Screen Message Handlers\RCICalc.h"
#include ".\Screen Message Handlers\RCICalcResistance.h"
#include ".\Screen Message Handlers\RCICalcCapacitance.h"
#include ".\Screen Message Handlers\RCICalcInductance.h"
#include ".\Screen Data\CitizensBandData.h"
#include ".\Screen Message Handlers\CitizensBand.h"
#include ".\Screen Message Handlers\EnergyStored.h"
#include ".\Screen Message Handlers\EnergyStoredCapacitor.h"
#include ".\Screen Message Handlers\EnergyStoredInductor.h"
#include ".\Screen Message Handlers\ThreePhasePower.h"
#include ".\Screen Data\CommonConnectorsData.h"
#include ".\Screen Message Handlers\CommonConnectors.h"
#include ".\Screen Data\TVChannelsData.h"
#include ".\Screen Message Handlers\TVChannels.h"
#include ".\Screen Data\CopperWireData.h"
#include ".\Screen Message Handlers\CopperWire.h"
#include ".\Screen Message Handlers\DWTransforms.h"
#include ".\Screen Data\KFactorsData.h"
#include ".\Screen Message Handlers\KFactors.h"
#include ".\Screen Data\OpAmpsData.h"
#include ".\Screen Message Handlers\OpAmps.h"
#include ".\Screen Message Handlers\MorseCode.h"
#include ".\Screen Data\RadioFrequencySpectrumData.h"
#include ".\Screen Message Handlers\RadioFrequencySpectrum.h"
#include ".\Screen Message Handlers\Timer555.h"
#include ".\Screen Message Handlers\Timer555Monostable.h"
#include ".\Screen Message Handlers\Timer555Astable.h"




BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) {
	TCHAR	szTitle[32];
	TCHAR	szWindowClass[32];
	LoadString(hInstance, IDS_APP_CLASS, szWindowClass, 32);
	LoadString(hInstance, IDS_APP_TITLE, szTitle, 32);
	hInst = hInstance;
	hWnd = FindWindow(szWindowClass, szTitle);	
	if (hWnd) {
		SetForegroundWindow((HWND)(((DWORD)hWnd) | 0x01));    
		return 0;
	} 
	WNDCLASS	wc;
    wc.style			    = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc		= (WNDPROC)WndProc;
    wc.cbClsExtra		  = 0;
    wc.cbWndExtra		  = 0;
    wc.hInstance		  = hInstance;
    wc.hIcon			    = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APP_ICON));
    wc.hCursor			  = 0;
    wc.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName		= 0;
    wc.lpszClassName	= szWindowClass;
	RegisterClass(&wc);
	RECT rect;
	GetClientRect(hWnd, &rect);
	hWnd = CreateWindow(szWindowClass, szTitle, WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
	if (!hWnd) { 
		return FALSE; 
	}
	RECT rc;
	GetWindowRect(hWnd, &rc);
	SHFullScreen(hWnd, SHFS_HIDESIPBUTTON);
	MoveWindow(hWnd, rc.left, rc.top, rc.right, rc.bottom, FALSE); 
	ShowWindow(hWnd, SW_SHOWNORMAL);
	UpdateWindow(hWnd);
	return true;
}




int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {
	if (Trial && !checkExpiration()) { return false; }
	MSG msg;
	// Initialize the application, draw the main window with the splash screen
	if (!InitInstance (hInstance, nCmdShow)) { 
		return FALSE; 
	}
	// Set step for progress bar
	SendMessage(hWndPB, PBM_SETSTEP, 5, NULL);

	// INITIALIZE THE SCHEMATICS SYMBOLS LISTVIEW.  THIS TAKES THE MOST TIME SO WE BREAJ
	// IT UP INTO A BUNCH OF PHASES AND INCREMENT THE PROGRESS BAR BETWEEN EACH.

SendMessage(hWndPB, PBM_STEPIT,  NULL, NULL);
	// Prep to fill our Schematic Symbols listview
	hWndSchematicSymbols					 = CreateDialog(hInst, MAKEINTRESOURCE(IDD_SCHEMATIC_SYMBOLS),						 hWnd,							(DLGPROC)SchematicSymbols); 	
	int i = 0;
	HWND hWndLV = GetDlgItem(hWndSchematicSymbols, IDC_LISTVIEW);   
	ListView_DeleteAllItems(hWndLV); // Delete everything from it
	ListView_SetIconSpacing(hWndLV, 68, 96); // Set icon spacing for proper display
	HIMAGELIST myImageList = ImageList_Create(37, 37, FALSE, 3, 0 ); // Create imagelist
	ListView_SetImageList(hWndLV, myImageList, LVSIL_NORMAL); // Attach imagelist to listview
	LV_ITEM	lvItem;
	lvItem.state		  = 0;    
	lvItem.stateMask  = 0;
	lvItem.mask				= LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM | LVIF_STATE;
	lvItem.iSubItem		= 0;
	lvItem.cchTextMax = 64;
	lvItem.iIndent		= 0;
SendMessage(hWndPB, PBM_STEPIT,  NULL, NULL);
	// Fill Schematic Symbols listview - Phase 1 of 4
	for (i = 0; i < 24; i++) {
		ImageList_AddIcon(myImageList, LoadIcon(hInst, MAKEINTRESOURCE(SchematicSymbolsTable[i].intSymbolID)));
		lvItem.iItem			= i;
		lvItem.pszText		= SchematicSymbolsTable[i].szSymbolText;
	  lvItem.lParam			= (LPARAM)&SchematicSymbolsTable[i];
		lvItem.iImage			= i;
		ListView_InsertItem(hWndLV, &lvItem);
  }	
SendMessage(hWndPB, PBM_STEPIT,  NULL, NULL);
	// Fill Schematic Symbols listview - Phase 2 of 4
	for (i = 24; i < 48; i++) {
		ImageList_AddIcon(myImageList, LoadIcon(hInst, MAKEINTRESOURCE(SchematicSymbolsTable[i].intSymbolID)));
		lvItem.iItem			= i;
		lvItem.pszText		= SchematicSymbolsTable[i].szSymbolText;
	  lvItem.lParam			= (LPARAM)&SchematicSymbolsTable[i];
		lvItem.iImage			= i;
		ListView_InsertItem(hWndLV, &lvItem);
  }	
SendMessage(hWndPB, PBM_STEPIT,  NULL, NULL);
	// Fill Schematic Symbols listview - Phase 3 of 4
	for (i = 48; i < 72; i++) {
		ImageList_AddIcon(myImageList, LoadIcon(hInst, MAKEINTRESOURCE(SchematicSymbolsTable[i].intSymbolID)));
		lvItem.iItem			= i;
		lvItem.pszText		= SchematicSymbolsTable[i].szSymbolText;
	  lvItem.lParam			= (LPARAM)&SchematicSymbolsTable[i];
		lvItem.iImage			= i;
		ListView_InsertItem(hWndLV, &lvItem);
  }	
SendMessage(hWndPB, PBM_STEPIT,  NULL, NULL);
	// Fill Schematic Symbols listview - Phase 4 of 4
	for (i = 72; i < 96; i++) {
		ImageList_AddIcon(myImageList, LoadIcon(hInst, MAKEINTRESOURCE(SchematicSymbolsTable[i].intSymbolID)));
		lvItem.iItem			= i;
		lvItem.pszText		= SchematicSymbolsTable[i].szSymbolText;
	  lvItem.lParam			= (LPARAM)&SchematicSymbolsTable[i];
		lvItem.iImage			= i;
		ListView_InsertItem(hWndLV, &lvItem);
  }	
SendMessage(hWndPB, PBM_STEPIT,  NULL, NULL);
	// Fill Schematic Symbols listview - Phase 5 of 4
	for (i = 96; i < 120; i++) {
		ImageList_AddIcon(myImageList, LoadIcon(hInst, MAKEINTRESOURCE(SchematicSymbolsTable[i].intSymbolID)));
		lvItem.iItem			= i;
		lvItem.pszText		= SchematicSymbolsTable[i].szSymbolText;
	  lvItem.lParam			= (LPARAM)&SchematicSymbolsTable[i];
		lvItem.iImage			= i;
		ListView_InsertItem(hWndLV, &lvItem);
  }	
SendMessage(hWndPB, PBM_STEPIT,  NULL, NULL);
	// Fill Schematic Symbols listview - Phase 6 of 4
	for (i = 120; i < 144; i++) {
		ImageList_AddIcon(myImageList, LoadIcon(hInst, MAKEINTRESOURCE(SchematicSymbolsTable[i].intSymbolID)));
		lvItem.iItem			= i;
		lvItem.pszText		= SchematicSymbolsTable[i].szSymbolText;
	  lvItem.lParam			= (LPARAM)&SchematicSymbolsTable[i];
		lvItem.iImage			= i;
		ListView_InsertItem(hWndLV, &lvItem);
  }	
SendMessage(hWndPB, PBM_STEPIT,  NULL, NULL);
	// NOW GO AHEAD AND INITIALIZE ALL THE OTHER SCREENS.  WE DO A FEW AND THEN INCREMENT
  // THE PROGRESSBAR A STEP SO IT LOOKS FAIRLY EVEN DURING INITIALIZATION
	hWndTVChannels								 = CreateDialog(hInst, MAKEINTRESOURCE(IDD_TV_CHANNELS),									 hWnd,							(DLGPROC)TVChannels); 
	hWndRadioFrequencySpectrum		 = CreateDialog(hInst, MAKEINTRESOURCE(IDD_RADIO_FREQUENCY_SPECTRUM),	     hWnd,              (DLGPROC)RadioFrequencySpectrum);
	hWndAbout											 = CreateDialog(hInst, MAKEINTRESOURCE(IDD_ABOUT),												 hWnd,							(DLGPROC)About); 
	hWndResistorColorCode					 = CreateDialog(hInst, MAKEINTRESOURCE(IDD_RESISTOR_COLOR_CODE),					 hWnd,							(DLGPROC)ResistorColorCode); 
SendMessage(hWndPB, PBM_STEPIT,  NULL, NULL);
	hWndDialectricConstants				 = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALECTRIC_CONSTANTS),					 hWnd,							(DLGPROC)DialectricConstants); 
	hWndResonance									 = CreateDialog(hInst, MAKEINTRESOURCE(IDD_RESONANCE),										 hWnd,							(DLGPROC)Resonance); 
	hWndImpedance									 = CreateDialog(hInst, MAKEINTRESOURCE(IDD_IMPEDANCE),										 hWnd,							(DLGPROC)Impedance); 
	hWndOpAmps										 = CreateDialog(hInst, MAKEINTRESOURCE(IDD_OPAMPS),												 hWnd,							(DLGPROC)OpAmps); 
SendMessage(hWndPB, PBM_STEPIT,  NULL, NULL);
	hWndKFactors									 = CreateDialog(hInst, MAKEINTRESOURCE(IDD_KFACTORS),											 hWnd,							(DLGPROC)KFactors); 
	hWndMetalAlloyResistances			 = CreateDialog(hInst, MAKEINTRESOURCE(IDD_METAL_ALLOY_RESISTANCES),			 hWnd,							(DLGPROC)MetalAlloyResistances); 
	hWndDCOhmsLaw									 = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DC_OHMS_LAW),									 hWnd,							(DLGPROC)DCOhmsLaw); 
	hWndMorseCode									 = CreateDialog(hInst, MAKEINTRESOURCE(IDD_MORSE_CODE),										 hWnd,							(DLGPROC)MorseCode); 
SendMessage(hWndPB, PBM_STEPIT,  NULL, NULL);
	hWndChipReference							 = CreateDialog(hInst, MAKEINTRESOURCE(IDD_CHIP_REFERENCE),                hWnd,							(DLGPROC)ChipReference); 
	hWndChipReferenceSelection		 = CreateDialog(hInst, MAKEINTRESOURCE(IDD_CHIP_REFERENCE_SELECTION),			 hWndChipReference, (DLGPROC)ChipReferenceSelection); 
	hWndChipReferencePinout				 = CreateDialog(hInst, MAKEINTRESOURCE(IDD_CHIP_REFERENCE_PINOUT),				 hWndChipReference, (DLGPROC)ChipReferencePinout); 
	hWndChipReferenceFunctionTable = CreateDialog(hInst, MAKEINTRESOURCE(IDD_CHIP_REFERENCE_FUNCTION_TABLE), hWndChipReference, (DLGPROC)ChipReferenceFunctionTable); 
SendMessage(hWndPB, PBM_STEPIT,  NULL, NULL);
	hWndCommonConnectors					 = CreateDialog(hInst, MAKEINTRESOURCE(IDD_COMMON_CONNECTORS),						 hWnd,							(DLGPROC)CommonConnectors); 
	hWndCitizensBand							 = CreateDialog(hInst, MAKEINTRESOURCE(IDD_CITIZENS_BAND),	               hWnd,              (DLGPROC)CitizensBand);     
	hWndThreePhasePower						 = CreateDialog(hInst, MAKEINTRESOURCE(IDD_THREE_PHASE_POWER),						 hWnd,							(DLGPROC)ThreePhasePower); 
SendMessage(hWndPB, PBM_STEPIT,  NULL, NULL);
	hWndDWTransforms							 = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DW_TRANSFORMS),								 hWnd,							(DLGPROC)DWTransforms); 
	hWndReactance									 = CreateDialog(hInst, MAKEINTRESOURCE(IDD_REACTANCE),										 hWnd,							(DLGPROC)Reactance); 
	hWndReactanceInductive				 = CreateDialog(hInst, MAKEINTRESOURCE(IDD_REACTANCE_INDUCTIVE),					 hWndReactance,			(DLGPROC)ReactanceInductive); 
	hWndReactanceCapacitive				 = CreateDialog(hInst, MAKEINTRESOURCE(IDD_REACTANCE_CAPACITIVE),					 hWndReactance,			(DLGPROC)ReactanceCapacitive); 
SendMessage(hWndPB, PBM_STEPIT,  NULL, NULL);
	hWndRCICalc										 = CreateDialog(hInst, MAKEINTRESOURCE(IDD_RCICALC),											 hWnd,							(DLGPROC)RCICalc); 
	hWndRCICalcResistance					 = CreateDialog(hInst, MAKEINTRESOURCE(IDD_RCICALC_RESISTANCE),						 hWndRCICalc,				(DLGPROC)RCICalcResistance); 
	hWndRCICalcCapacitance				 = CreateDialog(hInst, MAKEINTRESOURCE(IDD_RCICALC_CAPACITANCE),					 hWndRCICalc,				(DLGPROC)RCICalcCapacitance); 
	hWndRCICalcInductance					 = CreateDialog(hInst, MAKEINTRESOURCE(IDD_RCICALC_INDUCTANCE),						 hWndRCICalc,				(DLGPROC)RCICalcInductance); 
SendMessage(hWndPB, PBM_STEPIT,  NULL, NULL);
	hWndEnergyStored							 = CreateDialog(hInst, MAKEINTRESOURCE(IDD_ENERGY_STORED),								 hWnd,							(DLGPROC)EnergyStored); 
	hWndEnergyStoredCapacitor			 = CreateDialog(hInst, MAKEINTRESOURCE(IDD_ENERGY_STORED_CAPACITOR),			 hWndEnergyStored,	(DLGPROC)EnergyStoredCapacitor); 
	hWndEnergyStoredInductor			 = CreateDialog(hInst, MAKEINTRESOURCE(IDD_ENERGY_STORED_INDUCTOR),				 hWndEnergyStored,	(DLGPROC)EnergyStoredInductor); 
	hWndCopperWire								 = CreateDialog(hInst, MAKEINTRESOURCE(IDD_COPPER_WIRE),									 hWnd,							(DLGPROC)CopperWire); 
	hWndTimer555									 = CreateDialog(hInst, MAKEINTRESOURCE(IDD_TIMER555),											 hWnd,							(DLGPROC)Timer555); 
	hWndTimer555Monostable				 = CreateDialog(hInst, MAKEINTRESOURCE(IDD_TIMER555_MONOSTABLE),					 hWndTimer555,			(DLGPROC)Timer555Monostable); 
	hWndTimer555Astable						 = CreateDialog(hInst, MAKEINTRESOURCE(IDD_TIMER555_ASTABLE),							 hWndTimer555,			(DLGPROC)Timer555Astable); 
SendMessage(hWndPB, PBM_STEPIT,  NULL, NULL);
	// Move children of screens with tabs into place
	MoveWindow(hWndChipReferenceSelection,		 0, 52, 240, 220, true); 
	MoveWindow(hWndChipReferencePinout,				 0, 52, 240, 220, true); 
	MoveWindow(hWndChipReferenceFunctionTable, 0, 52, 240, 220, true); 
	MoveWindow(hWndTimer555Monostable,				 0, 52, 240, 220, true); 
	MoveWindow(hWndTimer555Astable,						 0, 52, 240, 220, true);
SendMessage(hWndPB, PBM_STEPIT,  NULL, NULL);
	MoveWindow(hWndReactanceInductive,				 0, 52, 240, 220, true); 
	MoveWindow(hWndReactanceCapacitive,				 0, 52, 240, 220, true);
	MoveWindow(hWndRCICalcResistance,				   0, 52, 240, 220, true); 
SendMessage(hWndPB, PBM_STEPIT,  NULL, NULL);
	MoveWindow(hWndRCICalcCapacitance,				 0, 52, 240, 220, true); 
	MoveWindow(hWndRCICalcInductance,					 0, 52, 240, 220, true); 
	MoveWindow(hWndEnergyStoredCapacitor,			 0, 52, 240, 220, true); 
	MoveWindow(hWndEnergyStoredInductor,			 0, 52, 240, 220, true);
SendMessage(hWndPB, PBM_STEPIT,  NULL, NULL);
	// Set the default children of screens with tabs
	hWndChipReferenceChild = hWndChipReferenceSelection;
	hWndReactanceChild		 = hWndReactanceInductive;
	hWndRCICalcChild			 = hWndRCICalcResistance;
	hWndEnergyStoredChild	 = hWndEnergyStoredCapacitor;
	hWndTimer555Child			 = hWndTimer555Monostable;
SendMessage(hWndPB, PBM_STEPIT,  NULL, NULL);
	// Create the menubar
	SHMENUBARINFO mbi;
	memset(&mbi, 0, sizeof(SHMENUBARINFO));
	mbi.cbSize     = sizeof(SHMENUBARINFO);
	mbi.hwndParent = hWnd;
	mbi.nToolBarId = IDM_MENU;
	mbi.hInstRes   = hInst;
	mbi.nBmpId     = 0;
	mbi.cBmpImages = 0;
	if (!SHCreateMenuBar(&mbi)) { return NULL; }

	CommandBar_AddBitmap(mbi.hwndMB, hInst, IDB_TOOLBAR_ICONS, 1, 16, 16); 
	TBBUTTON myButtons;
	myButtons.fsState		= TBSTATE_ENABLED;
	myButtons.iBitmap		= -1;
	myButtons.idCommand = -1;
	myButtons.dwData		= -1;
	myButtons.fsStyle		= TBSTYLE_SEP;
	myButtons.iString		= -1;
	CommandBar_AddButtons(mbi.hwndMB, 1, &myButtons); 
	myButtons.fsState		= TBSTATE_ENABLED;
	myButtons.iBitmap		= 0;
	myButtons.idCommand = 51928;
	myButtons.dwData		= 0;
	myButtons.fsStyle		= TBSTATE_ENABLED;
	myButtons.iString		= -1;
	CommandBar_AddButtons(mbi.hwndMB, 1, &myButtons); 

	hWndCB = mbi.hwndMB;
	DestroyWindow(hWndPB);
	SplashScreen = false; // Stop painting the splash screen in WNDPROC_PAINT

	// Draw the main window now
	InvalidateRect(hWnd, NULL, true);
	UpdateWindow(hWnd);

	// Begin message processing
	while (GetMessage(&msg, NULL, 0, 0)) {
    TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
