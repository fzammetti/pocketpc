
// ************************************************************************************************
// Header includes
// ************************************************************************************************
#include "stdafx.h"
#include "GXLibTest.h"
#include <commctrl.h>
#include <aygshell.h>
#include <sipapi.h>
#include <stdlib.h>
#include <string.h>
#include "../GXLib.h"


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
   TCHAR GXLibTestVersion[25] = L"**** GXLibTest v7.0 ****";
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// Globals
HWND							 hWnd														= NULL;
HINSTANCE					 hInst													= NULL;
int								 timerLoop											= 0;
unsigned char			 CurrentScreen									= 0;
unsigned char*		 pBoxFont												= NULL;
unsigned char*		 pPicturePalette								= NULL;
unsigned char*		 pPicture												= NULL;
unsigned char*		 pSpeedTestBKGroundPalette			= NULL;
unsigned char*		 pSpeedTestBackgroundSprite			= NULL;
unsigned char*		 pSpeedTestSprite1Palette				= NULL;
unsigned char*		 pSpeedTestSprite2Palette				= NULL;
unsigned char*		 pSpeedTestSprite3Palette				= NULL;
unsigned char*		 pSpeedTestSprite4Palette			  = NULL;
unsigned char*		 apSpeedTestSprite1Sprites[10];
unsigned char*		 apSpeedTestSprite2Sprites[20];
unsigned char*		 apSpeedTestSprite3Sprites[10];
unsigned char*		 apSpeedTestSprite4Sprites[20];
char							 roomCurrentTemp[30][30];
unsigned char*		 pGameWallsMoving1Palette				= NULL;
unsigned char*		 pGameWallsMoving2Palette				= NULL;
unsigned char*		 pGameWallsMoving3Palette				= NULL;
unsigned char*		 pGameWallsMoving4Palette				= NULL;
unsigned char*		 pGameWallsMoving1Sprite				= NULL;
unsigned char*		 pGameWallsMoving2Sprite				= NULL;
unsigned char*		 pGameWallsMoving3Sprite				= NULL;
unsigned char*		 pGameWallsMoving4Sprite				= NULL;
BOOL							 doSprites											= true;
BOOL							 doBackground										= true;
BOOL							 doWalls												= true;
BOOL							 doText													= true;
BOOL							 gsdone													= false;
unsigned char*		 pGradientPalette								= NULL;
unsigned char*		 pGradient											= NULL;
unsigned char*		 pHFlip													= NULL;
unsigned char*		 pVFlip													= NULL;
unsigned char*		 pFullScreenBox									= NULL;
unsigned char*		 pFullScreenBoxPalette					= NULL;
int								 sinc[1800];
unsigned int			 pal[260][3];
float							 stars[300][5];
unsigned short int plasmaDir											= 1;														

// ------------------------------------------------------------------------------------------------
// WNDPROC - WNDPROC - WNDPROC - WNDPROC - WNDPROC - WNDPROC - WNDPROC - WNDPROC - WNDPROC
// ------------------------------------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
		// Stylus was lifted off screen
		case WM_LBUTTONUP: {

			if (CurrentScreen == 0) { // Handle function selection screen taps
				// 3-D Starfield
				if (LOWORD(lParam) > 0 && LOWORD(lParam) < 240 && HIWORD(lParam) > 32 && HIWORD(lParam) < 49) {
					CurrentScreen = 12;
					GX_beginDraw();
						GX_clearScreen(0, 0, 0);
					GX_endDraw();
				}
				// Lines
				if (LOWORD(lParam) > 0 && LOWORD(lParam) < 240 && HIWORD(lParam) > 52 && HIWORD(lParam) < 69) {
					CurrentScreen = 1;
					GX_beginDraw();
						GX_clearScreen(0, 0, 0);
					GX_endDraw();
				}
				// Circles
				if (LOWORD(lParam) > 0 && LOWORD(lParam) < 240 && HIWORD(lParam) > 72 && HIWORD(lParam) < 89) {
					CurrentScreen = 2;
					GX_beginDraw();
						GX_clearScreen(0, 0, 0);
					GX_endDraw();
				}
				// Polygons (non-filled)
				if (LOWORD(lParam) > 0 && LOWORD(lParam) < 240 && HIWORD(lParam) > 92 && HIWORD(lParam) < 109) {
					CurrentScreen = 3;
					GX_beginDraw();
						GX_clearScreen(0, 0, 0);
					GX_endDraw();
				}
				// Polygons (filled)
				if (LOWORD(lParam) > 0 && LOWORD(lParam) < 240 && HIWORD(lParam) > 112 && HIWORD(lParam) < 129) {
					CurrentScreen = 4;
					GX_beginDraw();
						GX_clearScreen(0, 0, 0);
					GX_endDraw();
				}
				// Flood Fill
				if (LOWORD(lParam) > 0 && LOWORD(lParam) < 240 && HIWORD(lParam) > 132 && HIWORD(lParam) < 149) {
					CurrentScreen = 5;
					GX_beginDraw();
						GX_clearScreen(0, 0, 0);
					GX_endDraw();
				}
				// Max FPS Test
				if (LOWORD(lParam) > 0 && LOWORD(lParam) < 240 && HIWORD(lParam) > 252 && HIWORD(lParam) < 269) {
					CurrentScreen = 6;
					GX_beginDraw();
						GX_clearScreen(0, 0, 0);
					GX_endDraw();
				}
				// Region Functions
				if (LOWORD(lParam) > 0 && LOWORD(lParam) < 240 && HIWORD(lParam) > 152 && HIWORD(lParam) < 169) {
					CurrentScreen = 7;
					GX_beginDraw();
						GX_clearScreen(0, 0, 0);
						GX_drawSprite(pSpeedTestBackgroundSprite, pSpeedTestBKGroundPalette, 0,   0, false, 0, false, false, 0, 0, 0, 0);
						GX_drawSprite(pSpeedTestBackgroundSprite, pSpeedTestBKGroundPalette, 80,  0, false, 0, false, false, 0, 0, 0, 0);
						GX_drawSprite(pSpeedTestBackgroundSprite, pSpeedTestBKGroundPalette, 160, 0, false, 0, false, false, 0, 0, 0, 0);
						GX_drawSprite(pSpeedTestBackgroundSprite, pSpeedTestBKGroundPalette, 0,   80, false, 0, false, false, 0, 0, 0, 0);
						GX_drawSprite(pSpeedTestBackgroundSprite, pSpeedTestBKGroundPalette, 80,  80, false, 0, false, false, 0, 0, 0, 0);
						GX_drawSprite(pSpeedTestBackgroundSprite, pSpeedTestBKGroundPalette, 160, 80, false, 0, false, false, 0, 0, 0, 0);
						GX_drawSprite(pSpeedTestBackgroundSprite, pSpeedTestBKGroundPalette, 0,   160, false, 0, false, false, 0, 0, 0, 0);
						GX_drawSprite(pSpeedTestBackgroundSprite, pSpeedTestBKGroundPalette, 80,  160, false, 0, false, false, 0, 0, 0, 0);
						GX_drawSprite(pSpeedTestBackgroundSprite, pSpeedTestBKGroundPalette, 160, 160, false, 0, false, false, 0, 0, 0, 0);
						GX_drawSprite(pSpeedTestBackgroundSprite, pSpeedTestBKGroundPalette, 0,   240, false, 0, false, false, 0, 0, 0, 0);
						GX_drawSprite(pSpeedTestBackgroundSprite, pSpeedTestBKGroundPalette, 80,  240, false, 0, false, false, 0, 0, 0, 0);
						GX_drawSprite(pSpeedTestBackgroundSprite, pSpeedTestBKGroundPalette, 160, 240, false, 0, false, false, 0, 0, 0, 0);
						GX_storeRegion(NULL, NULL, NULL, 60, 200, 160, 285);
					GX_endDraw();
				}
				// Palette Manipulations
				if (LOWORD(lParam) > 0 && LOWORD(lParam) < 240 && HIWORD(lParam) > 172 && HIWORD(lParam) < 189) {
					CurrentScreen = 8;
					GX_beginDraw();
						GX_clearScreen(0, 0, 0);
					GX_endDraw();
				}
				// Sprite Manipulations
				if (LOWORD(lParam) > 0 && LOWORD(lParam) < 240 && HIWORD(lParam) > 192 && HIWORD(lParam) < 209) {
					CurrentScreen = 9;
					pPicturePalette = GX_loadPalette(IDR_PICTURE_PALETTE,	TEXT("MISC"), true);
					GX_beginDraw();
						GX_clearScreen(0, 0, 0);
					GX_endDraw();
				}
				// Plasma
				if (LOWORD(lParam) > 0 && LOWORD(lParam) < 240 && HIWORD(lParam) > 212 && HIWORD(lParam) < 229) {
					CurrentScreen = 10;
					plasmaDir = 1;
					GX_beginDraw();
						GX_clearScreen(0, 0, 0);
					GX_endDraw();
				}
				// Full Screen Box
				if (LOWORD(lParam) > 0 && LOWORD(lParam) < 240 && HIWORD(lParam) > 232 && HIWORD(lParam) < 249) {
					CurrentScreen = 11;
					GX_beginDraw();
						GX_clearScreen(0, 0, 0);
					GX_endDraw();
				}
				// Grayscale Image
				if (LOWORD(lParam) > 0 && LOWORD(lParam) < 240 && HIWORD(lParam) > 272 && HIWORD(lParam) < 289) {
					CurrentScreen = 13;
					gsdone = false;
					pPicturePalette = GX_loadPalette(IDR_PICTURE_PALETTE,	TEXT("MISC"), true);
					GX_beginDraw();
						GX_clearScreen(0, 0, 0);
					GX_endDraw();
				}
				// Exit
				if (LOWORD(lParam) > 0 && LOWORD(lParam) < 240 && HIWORD(lParam) > 300 && HIWORD(lParam) < 316) {
					PostQuitMessage(0);
				}

			} else if (CurrentScreen == 6) { // Handle taps on Max FPS Test screen		
				if (LOWORD(lParam) >= 158 && LOWORD(lParam) <= 170 && HIWORD(lParam) >= 2 && HIWORD(lParam) <= 22) { 
					doSprites = !doSprites;
				} else if (LOWORD(lParam) >= 178 && LOWORD(lParam) <= 190 && HIWORD(lParam) >= 2 && HIWORD(lParam) <= 22) { 
					doWalls = !doWalls;
				} else if (LOWORD(lParam) >= 198 && LOWORD(lParam) <= 210 && HIWORD(lParam) >= 2 && HIWORD(lParam) <= 22) { 
					doBackground = !doBackground;
				} else if (LOWORD(lParam) >= 218 && LOWORD(lParam) <= 230 && HIWORD(lParam) >= 2 && HIWORD(lParam) <= 22) { 
					doText = !doText;
				} else {
					CurrentScreen = 0;
					GX_beginDraw();
						GX_clearScreen(0, 0, 0);
					GX_endDraw();
				}

			} else if (CurrentScreen == 10) { // Handle taps on Plasma test
				if (plasmaDir == 2) {
					CurrentScreen = 0;
					GX_beginDraw();
						GX_clearScreen(0, 0, 0);
					GX_endDraw();
				} else {
					plasmaDir = 2;
				}

			} else if (CurrentScreen == 13) { // Handle taps on Grayscale Image		
				if (gsdone) {
					CurrentScreen = 0;
					GX_beginDraw();
						GX_clearScreen(0, 0, 0);
					GX_endDraw();
				} else {
					GX_grayscaleImage(pPicturePalette);
					gsdone = true;
				}

			} else { // Handle taps on any other screen

				CurrentScreen = 0;
				GX_beginDraw();
					GX_clearScreen(0, 0, 0);
				GX_endDraw();	

			}

		break; }

		// MAIN TIMER LOOP
		case WM_TIMER: {
			
			switch (CurrentScreen) {
				
				case 0: { // Function selection screen
					GX_beginDraw();
						GX_drawText(pBoxFont, GXLibTestVersion,						 GX_ALIGN_CENTER, 0, 10,  255, 255, 255);	
						GX_drawText(pBoxFont, L"3-D Starfield",						 GX_ALIGN_CENTER, 0, 33,  255, 255, 255);	
						GX_drawText(pBoxFont, L"Lines",										 GX_ALIGN_CENTER, 0, 53,  255, 255, 255);	
						GX_drawText(pBoxFont, L"Circles",									 GX_ALIGN_CENTER, 0, 73,  255, 255, 255);	
						GX_drawText(pBoxFont, L"Polygons (non-filled)",		 GX_ALIGN_CENTER, 0, 93,  255, 255, 255);	
						GX_drawText(pBoxFont, L"Polygons (filled)",				 GX_ALIGN_CENTER, 0, 113, 255, 255, 255);	
						GX_drawText(pBoxFont, L"Flood fill",							 GX_ALIGN_CENTER, 0, 133, 255, 255, 255);	
						GX_drawText(pBoxFont, L"Region functions",				 GX_ALIGN_CENTER, 0, 153, 255, 255, 255);	
						GX_drawText(pBoxFont, L"Palette manipulations",		 GX_ALIGN_CENTER, 0, 173, 255, 255, 255);	
						GX_drawText(pBoxFont, L"Sprite manipulations",		 GX_ALIGN_CENTER, 0, 193, 255, 255, 255);	
						GX_drawText(pBoxFont, L"Plasma",									 GX_ALIGN_CENTER, 0, 213, 255, 255, 255);	
						GX_drawText(pBoxFont, L"Full Screen Box",					 GX_ALIGN_CENTER, 0, 233, 255, 255, 255);	
						GX_drawText(pBoxFont, L"Max FPS Test",						 GX_ALIGN_CENTER, 0, 253, 255, 255, 255);	
						GX_drawText(pBoxFont, L"Grayscale Image",					 GX_ALIGN_CENTER, 0, 273, 255, 255, 255);	
						GX_drawText(pBoxFont, L"********* Exit *********", GX_ALIGN_CENTER, 0, 300, 255, 255, 255);	
					GX_endDraw();	
				break; }

				case 1: { // Lines
					unsigned short int cR = (unsigned short int)(rand() * 256 / (RAND_MAX + 1)); 
					unsigned short int cG = (unsigned short int)(rand() * 256 / (RAND_MAX + 1)); 
					unsigned short int cB = (unsigned short int)(rand() * 256 / (RAND_MAX + 1)); 
					unsigned short int x1 = (unsigned short int)(rand() * 240 / (RAND_MAX + 1)); 
					unsigned short int y1 = (unsigned short int)(rand() * 320 / (RAND_MAX + 1)); 
					unsigned short int x2 = (unsigned short int)(rand() * 240 / (RAND_MAX + 1)); 
					unsigned short int y2 = (unsigned short int)(rand() * 320 / (RAND_MAX + 1)); 
					GX_beginDraw();
						GX_drawLine(x1, y1, x2, y2, cR, cG, cB);
						GX_showFPS();
					GX_endDraw();
				break; }

				case 2: { // Circles
					static unsigned short int crad		= 10;
					static unsigned short int craddir = 1;
					unsigned short int cR = 255; 
					unsigned short int cG = 255; 
					unsigned short int cB = 255; 
					GX_beginDraw();
						GX_clearScreen(0, 0, 0);
						GX_drawCircle(120, 160, crad, cR, cG, cB);
						GX_showFPS();
					GX_endDraw();
					if (craddir == 1) { crad++; } else { crad--; }
					if (crad > 100) { craddir = 0; }
					if (crad < 10 ) { craddir = 1; }
				break; }

				case 3: { // Polygons (non-filled)
						static unsigned short numPoints = 25;
						static GX_Point PNFPoints[50];
						static unsigned short int cR; 
						static unsigned short int cG; 
						static unsigned short int cB; 
						unsigned short int i;
						cR = (unsigned short int)(rand() * 256 / (RAND_MAX + 1)); 
						cG = (unsigned short int)(rand() * 256 / (RAND_MAX + 1)); 
						cB = (unsigned short int)(rand() * 256 / (RAND_MAX + 1)); 
						numPoints++;
						if (numPoints > 20) {
							numPoints = 3;
						}
						for (i = 0; i < numPoints * 2; i = i + 2) {
							PNFPoints[i].x			= (unsigned short int)(rand() * 220 / (RAND_MAX + 1));
							PNFPoints[i + 1].y  = (unsigned short int)(rand() * 300 / (RAND_MAX + 1)); 
						}
					GX_beginDraw();
						GX_clearScreen(0, 0, 0);
						GX_drawPolygon(PNFPoints, numPoints, cR, cG, cB);
						GX_showFPS();
					GX_endDraw();
				break; }

				case 4: { // Polygons (filled)
					int numPoints = (unsigned short int)(rand() * 10 / (RAND_MAX + 1)); 
					GX_Point FPPoints[12];
					unsigned short int cR; 
					unsigned short int cG; 
					unsigned short int cB; 
					int i;
					cR = (unsigned short int)(rand() * 256 / (RAND_MAX + 1)); 
					cG = (unsigned short int)(rand() * 256 / (RAND_MAX + 1)); 
					cB = (unsigned short int)(rand() * 256 / (RAND_MAX + 1)); 
					for (i = 0; i < numPoints; i++) {
						FPPoints[i].x = (unsigned short int)(rand() * 240 / (RAND_MAX + 1));
						FPPoints[i].y = (unsigned short int)(rand() * 320 / (RAND_MAX + 1)); 
					}
					GX_beginDraw();
						GX_drawPolygonFilled(FPPoints, numPoints, cR, cG, cB);
						GX_showFPS();
					GX_endDraw();
				break; }

				case 5: { // Flood Fill
					static unsigned short int crad		= 10;
					static unsigned short int craddir = 1;
					unsigned short int cR1 = 0; 
					unsigned short int cG1 = 255; 
					unsigned short int cB1 = 0; 
					static unsigned short int cR2 = 255; 
					static unsigned short int cG2 = 0; 
					static unsigned short int cB2 = 0;
					GX_beginDraw();
						GX_clearScreen(0, 0, 0);
						GX_drawCircle(120, 160, crad, cR1, cG1, cB1);
						GX_floodFill(122, 162, cR2, cG2, cB2);
						GX_showFPS();
					GX_endDraw();
					if (craddir == 1) { crad++; } else { crad--; }
					if (crad > 100) { craddir = 0; cR2 = 0; cG2 = 0, cB2 = 255; }
					if (crad < 10 ) { craddir = 1; cR2 = 255; cG2 = 0, cB2 = 0; }
				break; }

				case 6: { // Maximum FPS test
					static unsigned short int Sprite1AnimFrame		 = 0;
					static unsigned short int Sprite2AnimFrame		 = 0;
					static unsigned short int Sprite3AnimFrame		 = 0;
					static unsigned short int Sprite4AnimFrame		 = 0;
					static unsigned short int SpriteAnimFrameDelay = 0;
					static int Sprite1X						 = 60;
					static int Sprite1Y						 = 200;
					static unsigned short int Sprite2X						 = 10;
					static unsigned short int Sprite2Y						 = 10;
					static unsigned short int Sprite3X						 = 80;
					static unsigned short int Sprite3Y						 = 120;
					static unsigned short int Sprite4X						 = 120;
					static unsigned short int Sprite4Y						 = 200;
					static unsigned short int Sprite1XDir					 = 0;
					static unsigned short int Sprite1YDir					 = 0;
					static unsigned short int Sprite2XDir					 = 1;
					static unsigned short int Sprite2YDir					 = 0;
					static unsigned short int Sprite3XDir					 = 0;
					static unsigned short int Sprite3YDir					 = 1;
					static unsigned short int Sprite4XDir					 = 1;
					static unsigned short int Sprite4YDir					 = 1;
					static unsigned short int BGCount							 = 0;
					static unsigned short int BGDir								 = 1;
					short int									currentX						 = 0;
					short int									currentY						 = 0;
					TCHAR											szOut[10]						 = L"";
					TCHAR											szOutX[4]						 = L"";
					TCHAR											szOutY[4]						 = L"";
					short int									row									 = 0;
					short int									col									 = 0;
					GX_beginDraw();
						if (doBackground) {
							GX_drawSprite(pSpeedTestBackgroundSprite, pSpeedTestBKGroundPalette, 0,   0, false, 0, false, false, 0, 0, 0, 0);
							GX_drawSprite(pSpeedTestBackgroundSprite, pSpeedTestBKGroundPalette, 80,  0, false, 0, false, false, 0, 0, 0, 0);
							GX_drawSprite(pSpeedTestBackgroundSprite, pSpeedTestBKGroundPalette, 160, 0, false, 0, false, false, 0, 0, 0, 0);
							GX_drawSprite(pSpeedTestBackgroundSprite, pSpeedTestBKGroundPalette, 0,   80, false, 0, false, false, 0, 0, 0, 0);
							GX_drawSprite(pSpeedTestBackgroundSprite, pSpeedTestBKGroundPalette, 80,  80, false, 0, false, false, 0, 0, 0, 0);
							GX_drawSprite(pSpeedTestBackgroundSprite, pSpeedTestBKGroundPalette, 160, 80, false, 0, false, false, 0, 0, 0, 0);
							GX_drawSprite(pSpeedTestBackgroundSprite, pSpeedTestBKGroundPalette, 0,   160, false, 0, false, false, 0, 0, 0, 0);
							GX_drawSprite(pSpeedTestBackgroundSprite, pSpeedTestBKGroundPalette, 80,  160, false, 0, false, false, 0, 0, 0, 0);
							GX_drawSprite(pSpeedTestBackgroundSprite, pSpeedTestBKGroundPalette, 160, 160, false, 0, false, false, 0, 0, 0, 0);
							GX_drawSprite(pSpeedTestBackgroundSprite, pSpeedTestBKGroundPalette, 0,   240, false, 0, false, false, 0, 0, 0, 0);
							GX_drawSprite(pSpeedTestBackgroundSprite, pSpeedTestBKGroundPalette, 80,  240, false, 0, false, false, 0, 0, 0, 0);
							GX_drawSprite(pSpeedTestBackgroundSprite, pSpeedTestBKGroundPalette, 160, 240, false, 0, false, false, 0, 0, 0, 0);
						}
						if (doWalls) {
							for (row = 0; row < 24; row++) {
								for (col = 0; col < 24; col++) {
									currentX = col * 10;
									currentY = (row * 10) + 40;
									switch (roomCurrentTemp[row + 1][col]) {
										case '1': {
											GX_drawSprite(pGameWallsMoving1Sprite, pGameWallsMoving1Palette, currentX, currentY, false, 0, false, false, 0, 0, 0, 0);
										break; }
										case '2': {
											GX_drawSprite(pGameWallsMoving2Sprite, pGameWallsMoving2Palette, currentX, currentY, false, 0, false, false, 0, 0, 0, 0);
										break; }
										case '3': {
											GX_drawSprite(pGameWallsMoving3Sprite, pGameWallsMoving3Palette, currentX, currentY, false, 0, false, false, 0, 0, 0, 0);
										break; }
										case '4': {
											GX_drawSprite(pGameWallsMoving4Sprite, pGameWallsMoving4Palette, currentX, currentY, false, 0, false, false, 0, 0, 0, 0);
										break; }
									}
								}
							}
						}
						if (doSprites) {
							GX_drawSprite(apSpeedTestSprite1Sprites[Sprite1AnimFrame], pSpeedTestSprite1Palette, Sprite1X, Sprite1Y, true, 0, true, false, 0, 0, 0, 0);
							GX_drawSprite(apSpeedTestSprite2Sprites[Sprite2AnimFrame], pSpeedTestSprite2Palette, Sprite2X, Sprite2Y, true, 0, false, false, 0, 0, 0, 0);
							GX_drawSprite(apSpeedTestSprite3Sprites[Sprite3AnimFrame], pSpeedTestSprite3Palette, Sprite3X, Sprite3Y, true, 0, false, false, 0, 0, 0, 0);
							GX_drawSprite(apSpeedTestSprite4Sprites[Sprite4AnimFrame], pSpeedTestSprite4Palette, Sprite4X, Sprite4Y, true, 0, false, false, 0, 0, 0, 0);
						}
						GX_showFPS();
						if (doText) {
							wcscpy(szOut, L"");
							swprintf(szOutX, TEXT("%d"), Sprite1X);
							swprintf(szOutY, TEXT("%d"), Sprite1Y);
							wcscat(szOut, szOutX);
							wcscat(szOut, L":");
							wcscat(szOut, szOutY);
							GX_drawText(pBoxFont, szOut, GX_ALIGN_NONE, 5, 285, 255, 255, 255);
							wcscpy(szOut, L"");
							swprintf(szOutX, TEXT("%d"), Sprite2X);
							swprintf(szOutY, TEXT("%d"), Sprite2Y);
							wcscat(szOut, szOutX);
							wcscat(szOut, L":");
							wcscat(szOut, szOutY);
							GX_drawText(pBoxFont, szOut, GX_ALIGN_NONE, 5, 305, 255, 255, 255);
							wcscpy(szOut, L"");
							swprintf(szOutX, TEXT("%d"), Sprite3X);
							swprintf(szOutY, TEXT("%d"), Sprite3Y);
							wcscat(szOut, szOutX);
							wcscat(szOut, L":");
							wcscat(szOut, szOutY);
							GX_drawText(pBoxFont, szOut, GX_ALIGN_NONE, 175, 285, 255, 255, 255);
							wcscpy(szOut, L"");
							swprintf(szOutX, TEXT("%d"), Sprite1X);
							swprintf(szOutY, TEXT("%d"), Sprite1Y);
							wcscat(szOut, szOutX);
							wcscat(szOut, L":");
							wcscat(szOut, szOutY);
							GX_drawText(pBoxFont, szOut, GX_ALIGN_NONE, 175, 305, 255, 255, 255);
						}
						GX_fillRegion(158, 2, 170, 22, 0, 0, 0);
						GX_drawText(pBoxFont, L"S",  GX_ALIGN_NONE, 160, 4,  255, 255, 255);
						GX_fillRegion(178, 2, 190, 22, 0, 0, 0);
						GX_drawText(pBoxFont, L"W",  GX_ALIGN_NONE, 180, 4,  255, 255, 255);	
						GX_fillRegion(198, 2, 210, 22, 0, 0, 0);
						GX_drawText(pBoxFont, L"B",  GX_ALIGN_NONE, 200, 4,  255, 255, 255);	
						GX_fillRegion(218, 2, 230, 22, 0, 0, 0);
						GX_drawText(pBoxFont, L"T",  GX_ALIGN_NONE, 220, 4,  255, 255, 255);	
					GX_endDraw();
					if (doBackground) {	
						if (BGDir == 1) {
							GX_shiftSpriteLeft(pSpeedTestBackgroundSprite);
							GX_shiftSpriteUp(pSpeedTestBackgroundSprite);
						}
						if (BGDir == 2) {
							GX_shiftSpriteRight(pSpeedTestBackgroundSprite);
							GX_shiftSpriteUp(pSpeedTestBackgroundSprite);
						}
						if (BGDir == 3) {
							GX_shiftSpriteRight(pSpeedTestBackgroundSprite);
							GX_shiftSpriteDown(pSpeedTestBackgroundSprite);
						}
						if (BGDir == 4) {
							GX_shiftSpriteLeft(pSpeedTestBackgroundSprite);
							GX_shiftSpriteDown(pSpeedTestBackgroundSprite);
						}
						BGCount++;
						if (BGCount > 100) {
							BGCount = 0;
							BGDir++;
							if (BGDir > 4) { BGDir = 1; }
						}
					}
					if (doWalls) {
						GX_shiftSpriteLeft(pGameWallsMoving1Sprite);
						GX_shiftSpriteRight(pGameWallsMoving2Sprite);
						GX_shiftSpriteUp(pGameWallsMoving3Sprite);
						GX_shiftSpriteDown(pGameWallsMoving4Sprite);
					}
					if (doSprites) {
						SpriteAnimFrameDelay++;
						if (SpriteAnimFrameDelay > 2) {
							SpriteAnimFrameDelay = 0;
							Sprite1AnimFrame++;
							if (apSpeedTestSprite1Sprites[Sprite1AnimFrame] == NULL) { Sprite1AnimFrame = 0; }
							Sprite2AnimFrame++;
							if (apSpeedTestSprite2Sprites[Sprite2AnimFrame] == NULL) { Sprite2AnimFrame = 0; }
							Sprite3AnimFrame++;
							if (apSpeedTestSprite3Sprites[Sprite3AnimFrame] == NULL) { Sprite3AnimFrame = 0; }
							Sprite4AnimFrame++;
							if (apSpeedTestSprite4Sprites[Sprite4AnimFrame] == NULL) { Sprite4AnimFrame = 0; }
						}
						if (Sprite1XDir == 0) { Sprite1X--; }
						if (Sprite2XDir == 0) { Sprite2X--; }
						if (Sprite3XDir == 0) { Sprite3X--; }
						if (Sprite4XDir == 0) { Sprite4X--; }
						if (Sprite1YDir == 0) { Sprite1Y--; }
						if (Sprite2YDir == 0) { Sprite2Y--; }
						if (Sprite3YDir == 0) { Sprite3Y--; }
						if (Sprite4YDir == 0) { Sprite4Y--; }
						if (Sprite1XDir == 1) { Sprite1X++; }
						if (Sprite2XDir == 1) { Sprite2X++; }
						if (Sprite3XDir == 1) { Sprite3X++; }
						if (Sprite4XDir == 1) { Sprite4X++; }
						if (Sprite1YDir == 1) { Sprite1Y++; }
						if (Sprite2YDir == 1) { Sprite2Y++; }
						if (Sprite3YDir == 1) { Sprite3Y++; }
						if (Sprite4YDir == 1) { Sprite4Y++; }
						if (Sprite1X < 0 - 10 - GX_getSpriteWidth(apSpeedTestSprite1Sprites[0])) { Sprite1XDir = 1; }
						if (Sprite2X < 2) { Sprite2XDir = 1; }
						if (Sprite3X < 2) { Sprite3XDir = 1; }
						if (Sprite4X < 2) { Sprite4XDir = 1; }
						if (Sprite1Y < 0 - 10 - GX_getSpriteHeight(apSpeedTestSprite1Sprites[0])) { Sprite1YDir = 1; }
						if (Sprite2Y < 2) { Sprite2YDir = 1; }
						if (Sprite3Y < 2) { Sprite3YDir = 1; }
						if (Sprite4Y < 2) { Sprite4YDir = 1; }
						if (Sprite1X > 250) { Sprite1XDir = 0; }
						if (Sprite2X > 238 - GX_getSpriteWidth(apSpeedTestSprite2Sprites[0])) { Sprite2XDir = 0; }
						if (Sprite3X > 238 - GX_getSpriteWidth(apSpeedTestSprite3Sprites[0])) { Sprite3XDir = 0; }
						if (Sprite4X > 238 - GX_getSpriteWidth(apSpeedTestSprite4Sprites[0])) { Sprite4XDir = 0; }
						if (Sprite1Y > 330) { Sprite1YDir = 0; }
						if (Sprite2Y > 318 - GX_getSpriteHeight(apSpeedTestSprite2Sprites[0])) { Sprite2YDir = 0; }
						if (Sprite3Y > 318 - GX_getSpriteHeight(apSpeedTestSprite3Sprites[0])) { Sprite3YDir = 0; }
						if (Sprite4Y > 318 - GX_getSpriteHeight(apSpeedTestSprite4Sprites[0])) { Sprite4YDir = 0; }
					}
				break; }

				case 7: { // Region functions
					static unsigned short int SpriteAnimFrame			 = 0;
					static unsigned short int SpriteAnimFrameDelay = 0;
					static unsigned short int SpriteX							 = 60;
					static unsigned short int SpriteY							 = 200;
					static unsigned short int SpriteXprevious			 = 60;
					static unsigned short int SpriteYprevious			 = 200;
					static unsigned short int SpriteXDir					 = 0;
					static unsigned short int SpriteYDir					 = 0;
					GX_beginDraw();
						GX_restoreRegion(NULL, NULL, NULL, SpriteXprevious, SpriteYprevious, SpriteXprevious + 100, SpriteYprevious + 85);
						GX_storeRegion(NULL, NULL, NULL, SpriteX, SpriteY, SpriteX + 100, SpriteY + 85);
						GX_drawSprite(pSpeedTestBackgroundSprite, pSpeedTestBKGroundPalette, 0,   240, false, 0, false, false, 0, 0, 0, 0);
						GX_drawSprite(pSpeedTestBackgroundSprite, pSpeedTestBKGroundPalette, 80,  240, false, 0, false, false, 0, 0, 0, 0);
						GX_drawSprite(pSpeedTestBackgroundSprite, pSpeedTestBKGroundPalette, 160, 240, false, 0, false, false, 0, 0, 0, 0);
						GX_drawSprite(apSpeedTestSprite4Sprites[SpriteAnimFrame], pSpeedTestSprite4Palette, SpriteX, SpriteY, true, 0, false, false, 0, 0, 0, 0);
						GX_dimRegion(0, 240, 240, 320, 60);
						GX_drawText(pBoxFont, L"Realtime dimming", GX_ALIGN_CENTER, NULL, 272, 255, 255, 255);
						GX_showFPS();
					GX_endDraw();
					SpriteXprevious = SpriteX;
					SpriteYprevious = SpriteY;
					SpriteAnimFrameDelay++;
					if (SpriteAnimFrameDelay > 2) {
						SpriteAnimFrameDelay = 0;
						SpriteAnimFrame++;
						if (apSpeedTestSprite4Sprites[SpriteAnimFrame] == NULL) { SpriteAnimFrame = 0; }
					}
					if (SpriteXDir == 0) { SpriteX--; }
					if (SpriteYDir == 0) { SpriteY--; }
					if (SpriteXDir == 1) { SpriteX++; }
					if (SpriteYDir == 1) { SpriteY++; }
					if (SpriteX < 2) { SpriteXDir = 1; }
					if (SpriteY < 2) { SpriteYDir = 1; }
					if (SpriteX > 238 - GX_getSpriteWidth(apSpeedTestSprite4Sprites[0])) { SpriteXDir = 0; }
					if (SpriteY > 318 - GX_getSpriteHeight(apSpeedTestSprite4Sprites[0])) { SpriteYDir = 0; }
				break; }

				case 8: { // Palette Manipulations
					static int pmcount = 0;
					static int pmdir   = 0;
					GX_beginDraw();
						GX_drawSprite(pGradient, pGradientPalette, 0, 0, false, 0, false, false, 0, 0, 0, 0);
						GX_showFPS();
					GX_endDraw();
					if (pmdir == 0) {
						GX_storePaletteEntry(pGradientPalette, 0);
						GX_paletteShiftLeft(pGradientPalette, 0, 50);
						GX_restorePaletteEntry(pGradientPalette, 50);
					}
					if (pmdir == 1) {
						GX_storePaletteEntry(pGradientPalette, 50);
						GX_paletteShiftRight(pGradientPalette, 0, 50);
						GX_restorePaletteEntry(pGradientPalette, 0);
					}
					pmcount++;
					if (pmcount > 100) { 
						pmcount = 0;
						if (pmdir == 0) {
							pmdir = 1;
						} else {
							pmdir = 0;
						}
					}
				break; }

				case 9: { // Sprite Manipulations
					static unsigned short int BGCount		= 0;
					static unsigned short int BGDir			= 1;
					static unsigned short	int	FlipDelay = 0;
					GX_beginDraw();
						// Faces for horizontal mirror function (the first for even # of pixels, the second for odd)
						GX_drawSprite(apSpeedTestSprite3Sprites[0],	pSpeedTestSprite3Palette, 40, 20, false, 0, false, false, 0, 0, 0, 0);
						GX_drawSprite(pHFlip, pSpeedTestSprite3Palette, 160, 20, false, 0, false, false, 0, 0, 0, 0);
						// Face for vertical function (the first for even # of lines, the second for odd)
						GX_drawSprite(apSpeedTestSprite3Sprites[1], pSpeedTestSprite3Palette, 40, 80, false, 0, false, false, 0, 0, 0, 0);
						GX_drawSprite(pVFlip, pSpeedTestSprite3Palette, 160, 80, false, 0, false, false, 0, 0, 0, 0);
						// Tile for shifts
						GX_drawSprite(pSpeedTestBackgroundSprite, pSpeedTestBKGroundPalette, 80,   140, false, 0, false, false, 0, 0, 0, 0);
						GX_showFPS();
						GX_drawText(pBoxFont, L"Draw", GX_ALIGN_NONE, 4, 250, 255, 255, 255);
						GX_drawText(pBoxFont, L"Sprite", GX_ALIGN_NONE, 4, 270, 255, 255, 255);
						GX_drawText(pBoxFont, L"Portion:", GX_ALIGN_NONE, 4, 290, 255, 255, 255);
						GX_drawSprite(pPicture, pPicturePalette, 80, 240, false, NULL, false, true, 50, 60, 150, 78);
					GX_endDraw();
					// Tile shifts
					if (BGDir == 1) {
						GX_shiftSpriteLeft(pSpeedTestBackgroundSprite);
						GX_shiftSpriteUp(pSpeedTestBackgroundSprite);
					}
					if (BGDir == 2) {
						GX_shiftSpriteRight(pSpeedTestBackgroundSprite);
						GX_shiftSpriteUp(pSpeedTestBackgroundSprite);
					}
					if (BGDir == 3) {
						GX_shiftSpriteRight(pSpeedTestBackgroundSprite);
						GX_shiftSpriteDown(pSpeedTestBackgroundSprite);
					}
					if (BGDir == 4) {
						GX_shiftSpriteLeft(pSpeedTestBackgroundSprite);
						GX_shiftSpriteDown(pSpeedTestBackgroundSprite);
					}
					BGCount++;
					if (BGCount > 40) {
						BGCount = 0;
						BGDir++;
						if (BGDir > 4) { BGDir = 1; }
					}
					FlipDelay++;
					if (FlipDelay > 50) {
						FlipDelay = 0;
						GX_mirrorSpriteH(apSpeedTestSprite3Sprites[0]);		
						GX_mirrorSpriteH(pHFlip);		
						GX_mirrorSpriteV(apSpeedTestSprite3Sprites[1]);		
						GX_mirrorSpriteV(pVFlip);				
					}
				break; }

				case 10: { // Plasma
					static unsigned int aval = 1;
					unsigned int				avall;
					unsigned int				avalr;
					unsigned char				z;
					int									e;
					int									f;
					unsigned short int* x;
					unsigned short int*	y;
					if (aval > 720) {
						aval = 0;
					}
					aval++;
					avall = aval << 1;
					avalr = aval >> 1;
					GX_beginDraw();
						switch (plasmaDir) {
							case 1: {
								for (int c = 0; c < 240; c++) {
									e = 75 + ((sinc[(c << 1) + avalr] + sinc[c + avall] + (sinc[(c >> 1) + aval] << 1)) >> 6);
									y = GX_pScreenBuffer + (c * GX_xPitch);
									for (int d = 0; d < 320; d++) {
										f = 75 + (((sinc[d + avall] << 1) + sinc[(d << 1) + avalr] + (sinc[d + aval] << 1)) >> 5);
										z = ((e * f) >> 5);
										*(y + (d * GX_yPitch)) = 
										 (unsigned short int)(((pal[z][0] & 0xf8) << 8) | 
										 ((pal[z][1] & 0xfc) << 3) | (pal[z][2] >> 3));
									}
								}
							break; }
							case 2: {
								for (int c = 0; c < 320; c++) {
										e = 75 + ((sinc[(c << 1) + avalr] + sinc[c + avall] + (sinc[(c >> 1) + aval] << 1)) >> 6);
										x = GX_pScreenBuffer + (c * GX_yPitch);
										for (int d = 0; d < 240; d++) {
												f = 75 + (((sinc[d + avall] << 1) + sinc[(d << 1) + avalr] + (sinc[d + aval] << 1)) >> 5);
												z = ((e * f) >> 5);
												*(x + (d * GX_xPitch)) =
												 (unsigned short int)(((pal[z][0] & 0xf8) << 8) |
												 ((pal[z][1] & 0xfc) << 3) | (pal[z][2] >> 3));
										}
								}
							break; }
						}
						GX_drawText(pBoxFont, L"Tap to change direction",      GX_ALIGN_RIGHT, NULL, 20,  255, 255, 0);
						GX_drawText(pBoxFont, L"Tap again to exit",				     GX_ALIGN_LEFT,  NULL, 300, 255, 255, 0);
						GX_showFPS();
					GX_endDraw();
				break; }

				case 11: { // Full Screen Box
					GX_beginDraw();
						GX_drawSprite(pFullScreenBox,	pFullScreenBoxPalette, 0, 0, false, 0, false, false, 0, 0, 0, 0);
						GX_drawText(pBoxFont, L"That's all it is!",				GX_ALIGN_CENTER, NULL, 60,  255, 255, 255);
						GX_drawText(pBoxFont, L"This is to be sure",			GX_ALIGN_CENTER, NULL, 100, 255, 255, 255);
						GX_drawText(pBoxFont, L"video memory is fully",		GX_ALIGN_CENTER, NULL, 120,  255, 255, 255);
						GX_drawText(pBoxFont, L"filled from the back",		GX_ALIGN_CENTER, NULL, 140, 255, 255, 255);
						GX_drawText(pBoxFont, L"buffer when GXLib is",    GX_ALIGN_CENTER, NULL, 160, 255, 255, 255);
						GX_drawText(pBoxFont, L"doing double-buffering.", GX_ALIGN_CENTER, NULL, 180, 255, 255, 255);
						GX_drawText(pBoxFont, L"Tap to exit any time.",   GX_ALIGN_CENTER, NULL, 240, 255, 255, 255);
					GX_endDraw();
				break; }

				case 12: { // 3-D Starfield
					int i;
					GX_beginDraw();
						// Erase the stars from their current locations
						for (i = 1; i < 295; i++) {
							GX_drawPoint((unsigned short int)stars[i][3], (unsigned short int)stars[i][4], 0, 0, 0);
						}			
						// Move the stars
						for (i = 1; i < 295; i++) {
							stars[i][2] -= 3;
							if (stars[i][2] <= 10) {  // Re-initialize if star is too close
								stars[i][0] = (float)(rand() % 70 - 35);
								stars[i][1] = (float)(rand() % 70 - 35);
								stars[i][2] = (float)(rand() % 100 + 1);
							} 
							stars[i][3] = (stars[i][0] / stars[i][2]) * 238 + (238 >> 1);
							stars[i][4] = (stars[i][1] / stars[i][2]) * 318 + (318 >> 1);
						}
						// Draw the stars in their new positions
						int starCol;
						for (i = 1; i < 295; i++) {
							starCol = 254 - (int)(stars[i][2] * 2);
							GX_drawPoint((unsigned short int)stars[i][3], (unsigned short int)stars[i][4], starCol, starCol, starCol);
						}
						GX_showFPS();
					GX_endDraw();
				break; }

				case 13: { // Grayscale Image
					GX_beginDraw();
						GX_drawSprite(pPicture,	pPicturePalette, 0, 0, false, 0, false, false, 0, 0, 0, 0);
						GX_drawText(pBoxFont, L"Tap to grayscale",      GX_ALIGN_RIGHT, 0, 20,  255, 255, 0);
						GX_drawText(pBoxFont, L"Tap again to exit",     GX_ALIGN_LEFT,  0, 300, 255, 255, 0);						
						GX_showFPS();
					GX_endDraw();
				break; }

			}

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

	// See which buffer method they want to use
	unsigned short int SelectedBufferMethod = 0;
	switch (MessageBox(NULL, L"If GAPI is not doing double-buffering for us, GXLib will do it instead.\n\nWhich method do you want GXLib to use in that case?\n\nPress YES for MEMCPY\nPress NO for BLITTING", L"Buffer Method Selection", MB_YESNO)) {
		case IDYES:
			SelectedBufferMethod = GX_BM_MEMCPY;
		break;
		case IDNO:
			SelectedBufferMethod = GX_BM_BLIT;
		break;
		default:
			SelectedBufferMethod = GX_BM_MEMCPY;
		break;
	}

	MSG msg;

	// Create our main window and initialize the application
	if (!InitInstance (hInstance, nCmdShow)) { 
		return FALSE;
	}

	// Initialize GXLib
	if (!GX_Initialize(hInst, hWnd, SelectedBufferMethod)) { // If false returned, something went wrong, so get outta here
		return false;
	}

	// Initialize stars for 3-D Starfield
	srand(GetTickCount());
	for (unsigned short int i = 1; i < 295; i++) {
		stars[i][0] = (float)(rand() % 70 - 35);
		stars[i][1] = (float)(rand() % 70 - 35);
		stars[i][2] = (float)(rand() % 100 + 1);
	}

	// Precalc table for plasma
	for (int k = 0; k < 1800; k++) {
		sinc[k] = (int)(sin((3.1416 * k) / 180) * 1024);
	}
	// Create palette for plasma
	unsigned int r = 0, g = 0, b = 0;
	unsigned int j;
	for (j = 0; j < 260; j++) {
		pal[j][0] = 0; pal[j][1] = 0; pal[j][2] = 0;
	}
	for (j = 0; j < 42; j++) {
		pal[j][0] = r; pal[j][1] = g; pal[j][2] = b; r = r + 5;
	}
	for (j = 42; j < 84; j++) {
		pal[j][0] = r; pal[j][1] = g; pal[j][2] = b; g = g + 5;
	}
	for (j = 84; j < 126; j++) {
		pal[j][0] = r; pal[j][1] = g; pal[j][2] = b; b = b + 5;
	}
	for (j = 126; j < 168; j++) {
		pal[j][0] = r; pal[j][1] = g; pal[j][2] = b; r = r - 5;
	}
	for (j = 168; j < 210; j++) {
		pal[j][0] = r; pal[j][1] = g; pal[j][2] = b; g = g - 5;
	}
	for (j = 210; j < 250; j++) {
		pal[j][0] = r; pal[j][1] = g; pal[j][2] = b; b = b - 5;
	}

  pBoxFont											= GX_loadFont(IDR_BOX, TEXT("FONTS"), true);
	GX_setCurrentFont(pBoxFont);	// Set a font for GAPI to use
	strcpy(roomCurrentTemp[0],		"");
	strcpy(roomCurrentTemp[1],		"3333333333    3333333333");
	strcpy(roomCurrentTemp[2],		"3                      3");
	strcpy(roomCurrentTemp[3],		"3                      3");
	strcpy(roomCurrentTemp[4],		"3                      3");
	strcpy(roomCurrentTemp[5],		"3                      3");
	strcpy(roomCurrentTemp[6],		"3      1111111111      3");
	strcpy(roomCurrentTemp[7],		"3      2        2      3");
	strcpy(roomCurrentTemp[8],		"3      2        2      3");
	strcpy(roomCurrentTemp[9],		"3      2        2      3");
	strcpy(roomCurrentTemp[10],		"3      2        2      3");
	strcpy(roomCurrentTemp[11],		"       2        2       ");
	strcpy(roomCurrentTemp[12],		"       2        2       ");
	strcpy(roomCurrentTemp[13],		"       2        2       ");
	strcpy(roomCurrentTemp[14],		"       2        2       ");
	strcpy(roomCurrentTemp[15],		"4      2        2      4");
	strcpy(roomCurrentTemp[16],		"4      2        2      4");
	strcpy(roomCurrentTemp[17],		"4      2        2      4");
	strcpy(roomCurrentTemp[18],		"4      2        2      4");
	strcpy(roomCurrentTemp[19],		"4      1111111111      4");
	strcpy(roomCurrentTemp[20],		"4                      4");
	strcpy(roomCurrentTemp[21],		"4                      4");
	strcpy(roomCurrentTemp[22],		"4                      4");
	strcpy(roomCurrentTemp[23],		"4                      4");
	strcpy(roomCurrentTemp[24],		"4444444444    4444444444");
  pGameWallsMoving1Palette			= GX_loadPalette(IDR_WALLS_MOVING_1_PALETTE,	TEXT("WALLS"), true);
  pGameWallsMoving2Palette			= GX_loadPalette(IDR_WALLS_MOVING_2_PALETTE,	TEXT("WALLS"), true);
  pGameWallsMoving3Palette			= GX_loadPalette(IDR_WALLS_MOVING_3_PALETTE,	TEXT("WALLS"), true);
  pGameWallsMoving4Palette			= GX_loadPalette(IDR_WALLS_MOVING_4_PALETTE,	TEXT("WALLS"), true);
	pGameWallsMoving1Sprite				= GX_loadSprite(IDR_WALLS_MOVING_1, TEXT("WALLS"), true, 104);
	pGameWallsMoving2Sprite				=	GX_loadSprite(IDR_WALLS_MOVING_2, TEXT("WALLS"), true, 104);
	pGameWallsMoving3Sprite				= GX_loadSprite(IDR_WALLS_MOVING_3, TEXT("WALLS"), true, 104);
	pGameWallsMoving4Sprite				= GX_loadSprite(IDR_WALLS_MOVING_4, TEXT("WALLS"), true, 104);
  pSpeedTestBKGroundPalette			= GX_loadPalette(IDR_MAX_FPS_TEST_BACKGROUND_PALETTE,	TEXT("MAX_FPS_TEST"), true);
	pSpeedTestBackgroundSprite		= GX_loadSprite(IDR_MAX_FPS_TEST_BACKGROUND, TEXT("MAX_FPS_TEST"), true, 6404);
  pSpeedTestSprite1Palette			= GX_loadPalette(IDR_MAX_FPS_TEST_SPRITE_1_PALETTE,		TEXT("MAX_FPS_TEST"), true);
  apSpeedTestSprite1Sprites[0]  = GX_loadSprite	(IDR_MAX_FPS_TEST_SPRITE_1_FRAME_1,		TEXT("MAX_FPS_TEST"), true, 7660);
  apSpeedTestSprite1Sprites[1]  = GX_loadSprite	(IDR_MAX_FPS_TEST_SPRITE_1_FRAME_2,		TEXT("MAX_FPS_TEST"), true, 7660);
  apSpeedTestSprite1Sprites[2]  = GX_loadSprite	(IDR_MAX_FPS_TEST_SPRITE_1_FRAME_3,		TEXT("MAX_FPS_TEST"), true, 7660);
	apSpeedTestSprite1Sprites[3]  = NULL;
  pSpeedTestSprite2Palette			= GX_loadPalette(IDR_MAX_FPS_TEST_SPRITE_2_PALETTE,		TEXT("MAX_FPS_TEST"), true);
  apSpeedTestSprite2Sprites[0]  = GX_loadSprite	(IDR_MAX_FPS_TEST_SPRITE_2_FRAME_1,		TEXT("MAX_FPS_TEST"), true, 1028);
  apSpeedTestSprite2Sprites[1]  = GX_loadSprite	(IDR_MAX_FPS_TEST_SPRITE_2_FRAME_2,		TEXT("MAX_FPS_TEST"), true, 1028);
  apSpeedTestSprite2Sprites[2]  = GX_loadSprite	(IDR_MAX_FPS_TEST_SPRITE_2_FRAME_3,		TEXT("MAX_FPS_TEST"), true, 1028);
  apSpeedTestSprite2Sprites[3]  = GX_loadSprite	(IDR_MAX_FPS_TEST_SPRITE_2_FRAME_4,		TEXT("MAX_FPS_TEST"), true, 1028);
  apSpeedTestSprite2Sprites[4]  = GX_loadSprite	(IDR_MAX_FPS_TEST_SPRITE_2_FRAME_5,		TEXT("MAX_FPS_TEST"), true, 1028);
  apSpeedTestSprite2Sprites[5]  = GX_loadSprite	(IDR_MAX_FPS_TEST_SPRITE_2_FRAME_6,		TEXT("MAX_FPS_TEST"), true, 1028);
  apSpeedTestSprite2Sprites[6]  = GX_loadSprite	(IDR_MAX_FPS_TEST_SPRITE_2_FRAME_7,		TEXT("MAX_FPS_TEST"), true, 1028);
  apSpeedTestSprite2Sprites[7]  = GX_loadSprite	(IDR_MAX_FPS_TEST_SPRITE_2_FRAME_8,		TEXT("MAX_FPS_TEST"), true, 1028);
  apSpeedTestSprite2Sprites[8]  = GX_loadSprite	(IDR_MAX_FPS_TEST_SPRITE_2_FRAME_9,		TEXT("MAX_FPS_TEST"), true, 1028);
  apSpeedTestSprite2Sprites[9]  = GX_loadSprite	(IDR_MAX_FPS_TEST_SPRITE_2_FRAME_10,	TEXT("MAX_FPS_TEST"), true, 1028);
	apSpeedTestSprite2Sprites[10] = NULL;
  pSpeedTestSprite3Palette			= GX_loadPalette(IDR_MAX_FPS_TEST_SPRITE_3_PALETTE,		TEXT("MAX_FPS_TEST"), true);
  apSpeedTestSprite3Sprites[0]  = GX_loadSprite	(IDR_MAX_FPS_TEST_SPRITE_3_FRAME_1,		TEXT("MAX_FPS_TEST"), true, 1524);
  apSpeedTestSprite3Sprites[1]  = GX_loadSprite	(IDR_MAX_FPS_TEST_SPRITE_3_FRAME_2,		TEXT("MAX_FPS_TEST"), true, 1524);
	apSpeedTestSprite3Sprites[2]  = NULL;
  pSpeedTestSprite4Palette			= GX_loadPalette(IDR_MAX_FPS_TEST_SPRITE_4_PALETTE,		TEXT("MAX_FPS_TEST"), true);
  apSpeedTestSprite4Sprites[0]  = GX_loadSprite	(IDR_MAX_FPS_TEST_SPRITE_4_FRAME_1,		TEXT("MAX_FPS_TEST"), true, 8504);
  apSpeedTestSprite4Sprites[1]  = GX_loadSprite	(IDR_MAX_FPS_TEST_SPRITE_4_FRAME_2,		TEXT("MAX_FPS_TEST"), true, 8504);
  apSpeedTestSprite4Sprites[2]  = GX_loadSprite	(IDR_MAX_FPS_TEST_SPRITE_4_FRAME_3,		TEXT("MAX_FPS_TEST"), true, 8504);
  apSpeedTestSprite4Sprites[3]  = GX_loadSprite	(IDR_MAX_FPS_TEST_SPRITE_4_FRAME_4,		TEXT("MAX_FPS_TEST"), true, 8504);
  apSpeedTestSprite4Sprites[4]  = GX_loadSprite	(IDR_MAX_FPS_TEST_SPRITE_4_FRAME_5,		TEXT("MAX_FPS_TEST"), true, 8504);
  apSpeedTestSprite4Sprites[5]  = GX_loadSprite	(IDR_MAX_FPS_TEST_SPRITE_4_FRAME_6,		TEXT("MAX_FPS_TEST"), true, 8504);
  apSpeedTestSprite4Sprites[6]  = GX_loadSprite	(IDR_MAX_FPS_TEST_SPRITE_4_FRAME_7,		TEXT("MAX_FPS_TEST"), true, 8504);
  apSpeedTestSprite4Sprites[7]  = GX_loadSprite	(IDR_MAX_FPS_TEST_SPRITE_4_FRAME_8,		TEXT("MAX_FPS_TEST"), true, 8504);
  apSpeedTestSprite4Sprites[8]  = GX_loadSprite	(IDR_MAX_FPS_TEST_SPRITE_4_FRAME_9,		TEXT("MAX_FPS_TEST"), true, 8504);
  apSpeedTestSprite4Sprites[9]  = GX_loadSprite	(IDR_MAX_FPS_TEST_SPRITE_4_FRAME_10,	TEXT("MAX_FPS_TEST"), true, 8504);
  apSpeedTestSprite4Sprites[10] = GX_loadSprite	(IDR_MAX_FPS_TEST_SPRITE_4_FRAME_11,	TEXT("MAX_FPS_TEST"), true, 8504);
  apSpeedTestSprite4Sprites[11] = GX_loadSprite	(IDR_MAX_FPS_TEST_SPRITE_4_FRAME_12,	TEXT("MAX_FPS_TEST"), true, 8504);
  apSpeedTestSprite4Sprites[12] = GX_loadSprite	(IDR_MAX_FPS_TEST_SPRITE_4_FRAME_13,	TEXT("MAX_FPS_TEST"), true, 8504);
  apSpeedTestSprite4Sprites[13] = GX_loadSprite	(IDR_MAX_FPS_TEST_SPRITE_4_FRAME_14,	TEXT("MAX_FPS_TEST"), true, 8504);
  apSpeedTestSprite4Sprites[14] = GX_loadSprite	(IDR_MAX_FPS_TEST_SPRITE_4_FRAME_15,	TEXT("MAX_FPS_TEST"), true, 8504);
	apSpeedTestSprite4Sprites[15] = NULL;
  pGradientPalette							= GX_loadPalette(IDR_GRADIENT_PALETTE, TEXT("GRADIENT"), true);
  pGradient											= GX_loadSprite	(IDR_GRADIENT, TEXT("GRADIENT"), true, 76804);
  pHFlip = GX_loadSprite(IDR_HFLIP,	TEXT("MISC"), true, 1564);
  pVFlip = GX_loadSprite(IDR_VFLIP,	TEXT("MISC"), true, 1562);
  pFullScreenBoxPalette					= GX_loadPalette(IDR_FULLSCREENBOXPALETTE, TEXT("MISC"), true);
  pFullScreenBox								= GX_loadSprite	(IDR_FULLSCREENBOX,				 TEXT("MISC"), true, 76804);
  pPicture											= GX_loadSprite	(IDR_PICTURE,							 TEXT("MISC"), true, 76804);
	pPicturePalette = GX_loadPalette(IDR_PICTURE_PALETTE,	TEXT("MISC"), true);




	// Start our main timer
	timerLoop = SetTimer(hWnd, 1, 20, NULL);
	// Main message handling loop.  Keep doing it until we exit in WinProc.
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	KillTimer(hWnd, timerLoop);
  GX_Exit();
	return msg.wParam;			// BYE-BYE!
}
