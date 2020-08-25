
// ************************************************************************************************
// Header includes
// ************************************************************************************************
#include "stdafx.h"
#include "FontTest.h"
#include <commctrl.h>
#include <aygshell.h>
#include <sipapi.h>
#include <stdlib.h>
#include <string.h>
#include "../GXLib.h"


HWND								hWnd						 = NULL;
HINSTANCE					  hInst						 = NULL;
int									timerLoop				 = 0;
//unsigned short*			pSpriteTempArea1 = (unsigned short*)malloc(200000);
unsigned char*			pFonts[300];
TCHAR								fontName[300][25];
int									currentFont = 0;


// ************************************************************************************************
// Grab a pointer to our fonts.  Called from WinMain.
// ************************************************************************************************
void loadFonts() {
  HRSRC		hResInfo	= NULL;
  HGLOBAL	hResource	= NULL;

	int i = 0;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_20S), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"20s"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_8X14), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"8x14"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_9X16SMSF), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"9x16smsf"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_AMBASSAD), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Ambassad"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_ANTIQUE), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Antique"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_APEAUS), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Apeaus"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_APLS10), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Apls10"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_APLS20), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Apls20"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_ARMENIAN), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Armenian"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_ART), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Art"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_ASCIIHX), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Asciihx"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_BACKSLNT), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Backslnt"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_BAUHAUS), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Bauhaus"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_BIG), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Big"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_BIGSERIF), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Bigserif"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_BINARY), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Binary"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_BLOCK), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Block"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_BLOODY), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Bloody"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_BODONI), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Bodoni"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_BOLD), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Bold"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_BOLD0), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Bold0"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_BOLD1), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Bold1"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_BOLD2), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Bold2"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_BOLD3), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Bold3"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_BOLD4), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Bold4"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_BOLD5), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Bold5"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_BOX), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Box"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_BOXROUND), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Boxround"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_BRAILLE), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Braille"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_BROADWAY), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Broadway"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_BRUSH), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Brush"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_CALCULAT), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Calculat"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_CAPITAL), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Capital"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_CAPS), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Caps"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_CIRCLE), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Circle"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_CNTDOWN), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Cntdown"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_COMPUTR1), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Computr1"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_COMPUTR2), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Computr2"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_COMPUTR3), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Computr3"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_COMPUTR4), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Computr4"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_COURIER1), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Courier1"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_COURIER2), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Courier2"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_CP111), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Cp111"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_CP112), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Cp112"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_CYRILL1), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Cyrill1"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_CYRILL4), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Cyrill4"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_CYRILL5), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Cyrill5"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_CYRILL6), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Cyrill6"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_DECORATE), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Decorate"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_DEFAULT), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Default"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_DONNA), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Donna"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_ELEGAND3), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Elegand3"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_ELEGANT1), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Elegant1"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_ELEGANT2), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Elegant2"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_ELERGON), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Elergon"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_EZVGA1), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Ezvga1"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_EZVGA2), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Ezvga2"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_FE8X16), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Fe8x16"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_FLORI), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Flori"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_FRESNO), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Fresno"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_FUTURE), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Future"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_FYVUSH), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Fyvush"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_GAELIC), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Gaelic"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_GOTHIC1), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Gothic1"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_GOTHIC2), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Gothic2"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_GOTHNEW), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Gothnew"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_GRCKSSRF), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Grckssrf"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_GREEK), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Greek"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_HACK4TH), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Hack4th"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_HANDUGLY), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Handugly"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_HANDWRIT), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Handwrit"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_HEARST), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Hearst"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_HEB7BIT), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Heb7bit"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_HEBBOLD1), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Hebbold1"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_HEBBOLD2), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Hebbold2"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_HEBREW), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Hebrew"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_HEBUGLY), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Hebugly"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_HELV1), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Helv1"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_HELV2), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Helv2"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_IBM), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Ibm"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_ITALIC1), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Italic1"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_ITALIC2), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Italic2"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_ITALIC3), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Italic3"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_JULIE), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Julie"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_KANA), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Kana"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_KING), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"King"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_KNIGHT), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Knight"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_KOOL), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Kool"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_LBITALIC), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Lbitalic"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_LBLARGE), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Lblarge"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_LBOCR), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Lbocr"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_LCD), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Lcd"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_LEGEND), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Legend"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_LITE), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Lite"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_MACNTOSH), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Macntosh"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_MEDIEVIL), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Medievil"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_MERP), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Merp"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_MERP1), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Merp1"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_MERP2), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Merp2"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_MODERN1), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Modern1"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_MODERN4), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Modern4"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_MODERN5), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Modern5"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_MORSE), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Morse"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_NUTSO), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Nutso"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_OLDENG1), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Oldeng1"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_OLDENG2), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Oldeng2"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_OLDENG3), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Oldeng3"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_OLDENG4), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Oldeng4"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_OLDENG6), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Oldeng6"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_ORATOR), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Orator"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_OUTLINE), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Outline"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_PARKAVE), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Parkave"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_PEKIGORD), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Pekigord"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_PERCY), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Percy"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_PERSIAN), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Persian"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_POLICE), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Police"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_POOTER), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Pooter"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_PPROMAN), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Pproman"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_PPSSER), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Ppsser"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_PRESTIG1), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Prestig1"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_PRESTIG2), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Prestig2"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_READABL1), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Readabl1"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_READABL2), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Readabl2"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_REVERSE), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Reverse"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_ROMAN1), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Roman1"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_ROMAN2), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Roman2"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_ROMANY), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Romany"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_ROYAL), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Royal"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_RUNES), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Runes"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_RUSSIAN), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Russian"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_SANSERF1), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Sanserf1"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_SANSERF2), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Sanserf2"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_SANSERF3), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Sanserf3"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_SCRAWL), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Scrawl"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_SCRIPT1), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Script1"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_SCRIPT2), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Script2"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_SCRIPT3), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Script3"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_SCRIPT4), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Script4"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_SERIF), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Serif"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_SERIFBIG), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Serifbig"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_SHADE), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Shade"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_SIGGLY), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Siggly"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_SIMPAGAR), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Simpagar"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_SIMPLE), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Simple"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_SLANT), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Slant"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_SMALL), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Small"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_SMOOTH), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Smooth"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_SMVGA), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Smvga"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_SPRANT01), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Sprant01"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_SPRANTO2), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Spranto2"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_SQUARE), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Square"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_STANDARD), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Standard"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_STRETCH), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Stretch"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_SUBSCR1), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Subscr1"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_SUBSCR2), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Subscr2"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_SUPER), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Super"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_SUPSCR1), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Supscr1"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_SUPSCR2), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Supscr2"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_SWISS1), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Swiss1"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_TALLTHIN), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Tallthin"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_TENGWAR), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Tengwar"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_TEXMATH), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Texmath"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_THAI), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Thai"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_THICK), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Thick"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_THIN), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Thin"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_THINSS), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Thinss"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_THNSERIF), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Thnserif"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_TINY), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Tiny"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_TTHINSS), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Tthinss"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_UNDERLIN), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Underlin"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_VGAROM), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Vgarom"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_VOGUE), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Vogue"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_VOYNICH), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Voynich"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_WACKY), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Wacky"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_WEIRD), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Weird"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_WIGGLY), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Wiggly"); i++;
	hResInfo  = FindResource(hInst, MAKEINTRESOURCE(IDR_YIDDISH), TEXT("FONTS"));
	hResource = LoadResource(hInst, hResInfo);
	pFonts[i] = (unsigned char*)LockResource(hResource);
	wcscpy(fontName[i], L"Yiddish"); i++;

	// END OF LIST
	wcscpy(fontName[i], L"EOL");
}


// ------------------------------------------------------------------------------------------------
// WNDPROC - WNDPROC - WNDPROC - WNDPROC - WNDPROC - WNDPROC - WNDPROC - WNDPROC - WNDPROC
// ------------------------------------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
		case WM_KEYUP: {
			PostQuitMessage(0);
		break; }
		// Stylus was lifted off screen
		case WM_LBUTTONUP: {
			if (LOWORD(lParam) > 180 && LOWORD(lParam) < 240 && HIWORD(lParam) > 280 && HIWORD(lParam) < 320) {
				currentFont++;
				if (wcscmp(fontName[currentFont], TEXT("EOL")) == 0) { currentFont = 0; }
				GX_beginDraw();
					GX_clearScreen(0, 0, 0);
				GX_endDraw();
			}
			if (LOWORD(lParam) > 0 && LOWORD(lParam) < 60 && HIWORD(lParam) > 280 && HIWORD(lParam) < 320) {
				currentFont--;
				if (currentFont < 0) { currentFont = 0; }
				GX_beginDraw();
					GX_clearScreen(0, 0, 0);
				GX_endDraw();
			}
		break; }
		// MAIN TIMER LOOP
		case WM_TIMER: {
			GX_beginDraw();
				TCHAR fontNumber[4];
				swprintf(fontNumber, L"%d", currentFont + 1);
				TCHAR fnout[20];
				wcscpy(fnout, L"Font #");
				wcscat(fnout, fontNumber);
				wcscat(fnout, L" Name:");
				GX_drawText(pFonts[currentFont], fnout,									 GX_ALIGN_CENTER, 0,   12,  255, 255, 255);	
				GX_drawText(pFonts[currentFont], fontName[currentFont],	 GX_ALIGN_CENTER, 0,   42,  255, 255, 255);	
				GX_drawText(pFonts[currentFont], L"aAbBcCdDeEfFgGhHiI",  GX_ALIGN_CENTER, 0,   72,  255, 255, 255);
				GX_drawText(pFonts[currentFont], L"jJkKlLmMnNoOpPqQrR",	 GX_ALIGN_CENTER, 0,   102, 255, 255, 255);	
				GX_drawText(pFonts[currentFont], L"sStTuUvVwWyYxXzZ",	   GX_ALIGN_CENTER, 0,   132, 255, 255, 255);	
				GX_drawText(pFonts[currentFont], L"012345789",           GX_ALIGN_CENTER, 0,   162, 255, 255, 255);	
				GX_drawText(pFonts[currentFont], L"`~!@#$%^&*()-=\\",    GX_ALIGN_CENTER, 0,   192, 255, 255, 255);
				GX_drawText(pFonts[currentFont], L"_+|[]{};':\",./<>?",  GX_ALIGN_CENTER, 0,   222, 255, 255, 255);	
				GX_drawText(pFonts[currentFont], L"PREV",								 GX_ALIGN_LEFT,   0,   290, 255, 0,   0);	
				GX_drawText(pFonts[currentFont], L"NEXT",								 GX_ALIGN_RIGHT,  0,   290, 0,   255, 0);	
			GX_endDraw();	
		break; }
		case WM_DESTROY: {
			PostQuitMessage(0);
		break; }
		default: {
			return DefWindowProc(hWnd, message, wParam, lParam);
		break; }

   }
   return 0;
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Program initialization, Called from WinMain.
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) {
	TCHAR	szTitle[16]				= L"";
	TCHAR	szWindowClass[16] = L"";
	LoadString(hInstance, IDS_TITLE,			 szTitle, 			15);
	LoadString(hInstance, IDS_WINDOWCLASS, szWindowClass, 15);
	hInst = hInstance;
	// See if our window already exists.  If it does, activate it and exit.
	hWnd  = FindWindow(szWindowClass, szTitle);	
	if (hWnd) {
		SetForegroundWindow ((HWND)(((DWORD)hWnd) | 0x01));    
		return 0;
	} 
	// It doesn't already exist, so let's create it, black and full-screen.
	WNDCLASS	wc;
    wc.style				 = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc	 = (WNDPROC)WndProc;
    wc.cbClsExtra		 = 0;
    wc.cbWndExtra		 = 0;
    wc.hInstance		 = hInstance;
    wc.hIcon				 = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON));
    wc.hCursor			 = 0;
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.lpszMenuName	 = 0;
		wc.lpszClassName = szWindowClass;
	RegisterClass(&wc);
	hWnd = CreateWindow(szWindowClass, szTitle, WS_VISIBLE, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics (SM_CYSCREEN), NULL, NULL, hInstance, NULL);
	if (!hWnd) { return FALSE; }
	SHFullScreen(hWnd, SHFS_HIDETASKBAR); // Get rid of the taskbar and show our window
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	return TRUE;
}


// ################################################################################################
// ##### WinMain - Program execution begins here!                                             #####
// ################################################################################################
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {

	MSG msg;

	// Create our main window and initialize the application
	if (!InitInstance (hInstance, nCmdShow)) { 
		return FALSE;
	}

	// Initialize GXLib
	if (!GX_Initialize(hInst, hWnd, GX_BM_MEMCPY)) { // If false returned, something went wrong, so get outta here
		return false;
	}

	// Load our game-specific graphics, palettes and fonts (really just grabbing pointers for later)
	// Fonts
	loadFonts();

	// Start our Intro screen timer
	timerLoop = SetTimer(hWnd, 1, 30, NULL);

	// Main message handling loop.  Keep doing it until we exit the game in WinProc.
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	KillTimer(hWnd, timerLoop);
  GXCloseDisplay();   // Close the GAPI display
  GXCloseInput();     // Close the GAPI key input
	return msg.wParam;  // BYE-BYE!
}
