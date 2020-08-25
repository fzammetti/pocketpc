
// ================================================================================================
//
//  GXLib.h
//
//  GXLib GAPI-Based Graphics Library v1.0
//  Writte by Frank W. Zammetti
//  (C)opyright 2002 by Omnytex Technologies
//  All Rights Reserved
//
//  This is a library of graphics functions utilizing Microsoft's GAPI library that performs
//  higher-level functions such as sprites, region stores and restores, region dimming,
//  primitive drawing, character drawing, sprite manipulations and others.
//
//  Miscellaneous Notes
//  -------------------
//
//  Sprites MUST be in RAW format with a 4-byte header.  The first two bytes are the width of the
//  sprite, the next two are the height of the sprite.  Both words are in high-low byte format.
//
//  Palettes MUST be in Microsoft palette format.
//
//  GX_Initialize MUST be called before any other GXLib functions and GX_Exit must be called
//  before exiting the application for proper cleanup.
//
//  All variables used in GXLib are prefixed with GX_.  Any parameters passed into functions are
//  prefixed with GXI_.  Any variables returned from a function is prefixed with GXO_.
//
//  GXLib depends on ZLibCE being available for compilation.  Be sure the header files
//  ZCONF.H, ZLIB.H, ZUTIL.H and ZIOCE.H are in a directory pointed to in the 
//  Tools...Options...Directories screen.  It also depends on ZLIBCE.LIB being available for the
//  build you are doing.  First, be sure to add ZLIBCE.LIB to the Project...Settings...Link
//  screen.  Then, be sure each build target in Tools...Options...Directories points to the
//  directory with the appropriate lib file.  When GXLib was created, these could be found in
//  C:\PROGRAM FILES\MICROSOFT EMBEDDED TOOLS\ZLIBCE.  The header files are in that directory,
//  the lib files are in subdirectories named for each target.

// ================================================================================================


// ************************************************************************************************
// Includes (GAPI)
// ************************************************************************************************
#include "gx.h"
#include "zconf.h"
#include "zlib.h"
#include "zutil.h"
#include "zioce.h"
#include <memory.h>


// ************************************************************************************************
// Defines
// ************************************************************************************************
#define GX_ALIGN_NONE          0
#define GX_ALIGN_LEFT          1
#define GX_ALIGN_CENTER        2
#define GX_ALIGN_RIGHT         3
#define GX_BM_MEMCPY					 4
#define GX_BM_BLIT						 5
#define GX_STACK_MAX					 10000
#define GX_STACK_PUSH(Y, XL, XR, DY) \
				if (sp < stack + GX_STACK_MAX && Y + (DY) >= 0 && Y + (DY) <= 320) \
				{sp->y = Y; sp->xl = XL; sp->xr = XR; sp->dy = DY; sp++;}
#define GX_STACK_POP(Y, XL, XR, DY) \
				{sp--; Y = sp->y+(DY = sp->dy); XL = sp->xl; XR = sp->xr;}


// ************************************************************************************************
// Structures
// ************************************************************************************************
typedef struct {
	int x;
	int y;
} GX_Point;
struct GX_FFSeg {short y, xl, xr, dy;};
struct GX_FFSeg stack[GX_STACK_MAX], *sp = stack;


// ************************************************************************************************
// Globals
// ************************************************************************************************
GXDisplayProperties GX_g_gxdp;																// GAPI display properties struct
GXKeyList					  GX_g_gxkl;																// GAPI keylist struct
signed long	int			GX_xPitch								= NULL;						// GAPI screen X pitch used in all GAPI code
signed long	int			GX_yPitch								= NULL;						// GAPI screen Y pitch used in all GAPI code
unsigned short int*	GX_pScreenBuffer				= NULL;						// Pointer to our screen buffer from GAPI
unsigned short int*	GX_pVidMem							= NULL;						// Pointer to our screen buffer from GAPI
unsigned short int*	GX_pTempArea						= NULL;						// Temporary screen background storage
HINSTANCE						GX_hInst								= NULL;						// Application's instance handle
unsigned char*			GX_currentFont					= NULL;						// Pointer to font uaed internally
unsigned char				GX_savePaletteBytes[5];										// Used for palette rotation functions
unsigned int				GX_FPStartX[320];													// Used in the filled polygon code
unsigned int				GX_FPEndX[320];														// Used in the filled polygon code
unsigned long int		GX_bufferSize						= NULL;						// Size of off-screen buffer
BOOL								GX_isBuffered						= NULL;						// Is GAPI doing double-buffering?
BOOL								GX_BBBypass							= NULL;						// Should we not use GAPI to draw?
BOOL								GX_isIPaq								= NULL;						// True if device is an iPaq other than 38xx series, false otherwise
unsigned short int	GX_BufferMethod					= NULL;						// Specifies which buffer method to use, Blit or Memcpy


// ************************************************************************************************
// GX_Initialize
// Initializes the GXLib library.  Must be called before any other FX function!
// Parameters: Handle to the application's instance (const HINSTANCE GXI_hInst)
//             Handle to the application's main window (const HWND GXI_hWnd
// Returns:    Indication of success or failure, true is good, false is bad (BOOL)
// ************************************************************************************************
BOOL GX_Initialize(const HINSTANCE GXI_hInst, const HWND GXI_hWnd, const unsigned short int GXI_BufferMethod) {
	GX_BufferMethod  = GXI_BufferMethod;
	GX_hInst				 = GXI_hInst;												// Get handle to this app instance
	GXOpenDisplay(GXI_hWnd, GX_FULLSCREEN);						  // Ask GAPI to open the display for us
	// GXIsDisplayDRAMBuffer returns TRUE if GAPI is doing double-buffering for us
	GX_isBuffered		 = GXIsDisplayDRAMBuffer();					// Is GAPI doing double-buffering for us?
  GX_g_gxdp				 = GXGetDisplayProperties();			  // Get the GAPI device parameters
	GX_xPitch				 = GX_g_gxdp.cbxPitch >> 1;					// GAPI X pixel pitch
	GX_yPitch				 = GX_g_gxdp.cbyPitch >> 1;					// GAPI Y pixel pitch
	// If we're dealing with a 3800, fix the GAPI properties
	TCHAR OEMModelInfo[64];
	SystemParametersInfo(SPI_GETOEMINFO, 64, OEMModelInfo, 0);
	_wcsupr(OEMModelInfo);
	if (wcsstr(OEMModelInfo, L"IPAQ")) { // See if it's an iPaq
		if (wcsstr(OEMModelInfo, L"38")) { // See if it's a 38xx
			if (!(GX_g_gxdp.cbxPitch < 0 && GX_g_gxdp.cbyPitch > 0)) { // See if GAPI is broke
				GX_pVidMem				 = (unsigned short int*)0xAC0755A0;
				GX_g_gxdp.cxWidth  = 240;
				GX_g_gxdp.cyHeight = 320;
				GX_g_gxdp.cbxPitch = -640;
				GX_g_gxdp.cbyPitch = 2;
				GX_xPitch					 = GX_g_gxdp.cbxPitch >> 1;
				GX_yPitch					 = GX_g_gxdp.cbyPitch >> 1;
				GX_g_gxdp.cBPP     = 16;
				GX_g_gxdp.ffFormat = 0xA8;
				GX_isBuffered      = false;
				GX_BBBypass				 = true;
			}
		} else { // Other iPaq model
			GX_isIPaq = true;
		}
	}
	if (GX_BufferMethod == GX_BM_BLIT && !GX_isBuffered) {
		GX_xPitch			= 1;
		GX_yPitch			= 240;
		GX_isBuffered = false;
	}
	// Determine our byffer size for double-buffering and region stores/restores
	GX_bufferSize	= 240 * 320 * (GX_g_gxdp.cBPP / 8);
	GX_pTempArea	= (unsigned short int*)malloc(GX_bufferSize); // Allocate our temporary sprite background storage
	// If GAPI is NOT doing double-buffering for us, allocate our back-buffer
	if (!GX_isBuffered) {
		if (GX_BufferMethod == GX_BM_MEMCPY && GX_isIPaq) {
			// Allocate it this way if we'll be doing Memcpy's with it
			GX_pScreenBuffer = (unsigned short int*)malloc(GX_bufferSize + (320 << 1));
			GX_pScreenBuffer += (319 << 1);
		} else { // Or this way if we'll be Blit'ing
			GX_pScreenBuffer = (unsigned short int*)malloc(GX_bufferSize);
		}
	}
  GXOpenInput();															 // Open GAPI for input
  GX_g_gxkl	= GXGetDefaultKeys(GX_NORMALKEYS); // Get the GAPI key codes
	return true;
}


// ************************************************************************************************
// GX_beginDraw
// Routine to begin drawing.
// Simply calls the standard GAPI GXBeginDraw() function.
// ************************************************************************************************
void GX_beginDraw() {
	// If GAPI is doing double-buffering for us, get our screen buffer pointer.
	// Note: If GAPI is NOT doing our double-buffering, then GX_pScreenBuffer is already
	// pointing to our own back-buffer, so no need to do anything here.
	if (GX_isBuffered) { 
		GX_pScreenBuffer = (unsigned short int*)GXBeginDraw();
	}
}


// ************************************************************************************************
// GX_endDraw
// Routine to end drawing.
// Simply calls the standard GAPI GXEndDraw() function.
// ************************************************************************************************
void GX_endDraw() {
	// If GAPI IS doing double-buffering for us, just call GXEndDraw();
	if (GX_isBuffered) {
		GXEndDraw();
	} else { // If GAPI is NOT doing double-buffering for us, flip the back-buffer forward
		if (GX_BBBypass) { // Must be a 38xx series
			memcpy(GX_pVidMem, GX_pScreenBuffer, GX_bufferSize);
		} else { // Not a 38xx series
			if (GX_BufferMethod == GX_BM_BLIT) { // Use the blitter to flip
					int							x				 = NULL;
					int							y				 = NULL;
					int*						GXBuffer = (int*)GXBeginDraw();
					unsigned short*	pSrc		 = GX_pScreenBuffer;
					unsigned short*	pusLine	 = (unsigned short*)GXBuffer;
					unsigned short*	pDest		 = NULL;
					int							gxYPitch = GX_g_gxdp.cbyPitch >> 1;
					int							gxXPitch = GX_g_gxdp.cbxPitch >> 1;
					for (y = GX_g_gxdp.cyHeight; y > 0; y--) {
						pDest = pusLine;
						for (x = GX_g_gxdp.cxWidth; x > 0; x--) {
							*pDest = *pSrc++;			
							pDest	+= gxXPitch;
						}
						pusLine	+= gxYPitch;
					}
			} else { // Use Memcpy to flip
				if (GX_isIPaq) { // Do it this way for iPaq's other than 38xx's
					memcpy((unsigned short int*)GXBeginDraw() - (319 << 1), GX_pScreenBuffer - (319 << 1), GX_bufferSize + (320 << 1));
				} else { // Or this way for any other device (Thanks Compaq, you SUCK!!)
					memcpy((unsigned short int*)GXBeginDraw(), GX_pScreenBuffer, GX_bufferSize);
				}
			}
			GXEndDraw();
		}
	}
}


// ************************************************************************************************
// GX_Exit
// Closes the GXLib library and cleans up.  Must be called before exit the application!
// ************************************************************************************************
void GX_Exit() {
	free(GX_pTempArea); // Deallocate our temporary sprite background storage
	// Deallocate our back-buffer, if applicable
	if (!GX_isBuffered) {
		free(GX_pScreenBuffer);
	}
  GXCloseDisplay();		// Close the GAPI display
  GXCloseInput();			// Close the GAPI key input
}


// ************************************************************************************************
// GX_setCurrentFont
// Saves a pointer to a font for use in certain GX functions (i.e. showFPS) and for debugging
// Parameters: Pointer to the font (unsigned char* GXI_currentFont)
// ************************************************************************************************
void GX_setCurrentFont(unsigned char* GXI_currentFont) {
	GX_currentFont = GXI_currentFont;
}


// ************************************************************************************************
// GX_loadPalette
// Load a palette resource and returns a pointer to it.
// Parameters: Resource identifier to load (const unsigned int GXI_resourceIdentifier)
//             Name of the group the resource belongs to (const LPTSTR GXI_resourceGroupName)
//						 Flag: Was the palette data compressed with ZLib? (const bool GXI_compressed)
// Returns:    Pointer to the resource loaded (unsigned char*)
// ************************************************************************************************
unsigned char* GX_loadPalette(const unsigned int GXI_resourceIdentifier, const LPTSTR GXI_resourceGroupName, const bool GXI_compressed) {
	if (GXI_compressed) {
		HRSRC		GX_hResInfo;
		HGLOBAL GX_hResource;
		void*   GX_pvRes;
		DWORD   GX_dwSize;
		uLong		GX_comprLen = 1052;
		GX_hResInfo  = FindResource(GX_hInst, MAKEINTRESOURCE(GXI_resourceIdentifier), GXI_resourceGroupName);
		GX_hResource = LoadResource(GX_hInst, GX_hResInfo);
		GX_pvRes		 = LockResource(GX_hResource);
		GX_dwSize		 = SizeofResource(GX_hInst, GX_hResInfo);
		// Allocate a memory buffer to put the uncompressed data into
		Byte*	GX_destBuf	= (Byte*)malloc(GX_comprLen); // Microsoft palette, so it's always 1052 bytes
		// Do the uncompress
		uncompress((Byte*)GX_destBuf, &GX_comprLen, (Byte*)GX_pvRes, GX_dwSize);
		return ((unsigned char*)GX_destBuf) + 24;
	} else {
		HRSRC		GX_hResInfo;
		HGLOBAL GX_hResource;
		void*   GX_pvRes;
		DWORD   GX_dwSize;
		LPVOID  GX_lpMemory;
		// NOTE: Microsoft palette format, color definitions begin on 25th byte, so skip first 24
		GX_hResInfo  = FindResource(GX_hInst, MAKEINTRESOURCE(GXI_resourceIdentifier), GXI_resourceGroupName);
		GX_hResource = LoadResource(GX_hInst, GX_hResInfo);
		GX_pvRes		 = LockResource(GX_hResource);
		GX_dwSize		 = SizeofResource(GX_hInst, GX_hResInfo);
		GX_lpMemory	 = malloc(GX_dwSize);
		memcpy(GX_lpMemory, GX_pvRes, GX_dwSize);
		return ((unsigned char*)GX_lpMemory) + 24;
	}
}


// ************************************************************************************************
// GX_loadFont
// Load a font resource and returns a pointer to it.
// Parameters: Resource identifier to load (const unsigned int GXI_resourceIdentifier)
//             Name of the group the resource belongs to (const LPTSTR GXI_resourceGroupName)
//						 Flag: Was the font data compressed with ZLib? (const bool GXI_compressed)
// Returns:    Pointer to the resourc loaded (unsigned char*)
// ************************************************************************************************
unsigned char* GX_loadFont(const unsigned int GXI_resourceIdentifier, const LPTSTR GXI_resourceGroupName, const bool GXI_compressed) {
	if (GXI_compressed) {
		HRSRC		GX_hResInfo;
		HGLOBAL GX_hResource;
		void*   GX_pvRes;
		DWORD   GX_dwSize;
		uLong		GX_comprLen = 4096;
		GX_hResInfo  = FindResource(GX_hInst, MAKEINTRESOURCE(GXI_resourceIdentifier), GXI_resourceGroupName);
		GX_hResource = LoadResource(GX_hInst, GX_hResInfo);
		GX_pvRes		 = LockResource(GX_hResource);
		GX_dwSize		 = SizeofResource(GX_hInst, GX_hResInfo);
		// Allocate a memory buffer to put the uncompressed data into
		Byte*	GX_destBuf	= (Byte*)malloc(GX_comprLen); // VGA font, so it's always 4096 bytes
		// Do the uncompress
		uncompress((Byte*)GX_destBuf, &GX_comprLen, (Byte*)GX_pvRes, GX_dwSize);
		return (unsigned char*)GX_destBuf;
	} else {
		HRSRC		GX_hResInfo;
		HGLOBAL GX_hResource;
		GX_hResInfo  = FindResource(GX_hInst, MAKEINTRESOURCE(GXI_resourceIdentifier), GXI_resourceGroupName);
		GX_hResource = LoadResource(GX_hInst, GX_hResInfo);
		return (unsigned char*)LockResource(GX_hResource);
	}
}


// ************************************************************************************************
// GX_loadSprite
// Load a sprite resource and returns a pointer to it.  The sprite is copied to an allocated
// chunk of memory so it can be manipulated.
// Parameters: Resource identifier to load (const unsigned int GXI_resourceIdentifier)
//             Name of the group the resource belongs to (const LPTSTR GXI_resourceGroupName)
//						 Flag: Was the sprite data compressed with ZLib? (const bool GXI_compressed)
//						 Length of original sprite data if compressed (uLong GXI_comprLen)
// Returns:    Pointer to the sprite in memory (unsigned char*)
// ************************************************************************************************
unsigned char* GX_loadSprite(const unsigned int GXI_resourceIdentifier, const LPTSTR GXI_resourceGroupName, const bool GXI_compressed, uLong GXI_comprLen) {
	if (GXI_compressed) {
		HRSRC		GX_hResInfo;
		HGLOBAL GX_hResource;
		void*   GX_pvRes;
		DWORD   GX_dwSize;
		GX_hResInfo  = FindResource(GX_hInst, MAKEINTRESOURCE(GXI_resourceIdentifier), GXI_resourceGroupName);
		GX_hResource = LoadResource(GX_hInst, GX_hResInfo);
		GX_pvRes		 = LockResource(GX_hResource);
		GX_dwSize		 = SizeofResource(GX_hInst, GX_hResInfo);
		// Allocate a memory buffer to put the uncompressed data into
		Byte*	GX_destBuf	= (Byte*)malloc(GXI_comprLen);
		// Do the uncompress
		uncompress((Byte*)GX_destBuf, &GXI_comprLen, (Byte*)GX_pvRes, GX_dwSize);
		return (unsigned char*)GX_destBuf;
	} else {
		HRSRC		GX_hResInfo;
		HGLOBAL GX_hResource;
		void*   GX_pvRes;
		DWORD   GX_dwSize;
		GX_hResInfo  = FindResource(GX_hInst, MAKEINTRESOURCE(GXI_resourceIdentifier), GXI_resourceGroupName);
		GX_hResource = LoadResource(GX_hInst, GX_hResInfo);
		GX_pvRes		 = LockResource(GX_hResource);
		GX_dwSize		 = SizeofResource(GX_hInst, GX_hResInfo);
		LPVOID GX_destBuf = malloc(GX_dwSize);
		memcpy(GX_destBuf, GX_pvRes, GX_dwSize);
		return (unsigned char*)GX_destBuf;
	}
}


// ************************************************************************************************
// GX_drawText
// Draw text onto the screen.
// Parameters: Pointer to the font to use (unsigned char* GXI_pFont)
//             Pointer to the string to draw (const TCHAR* GXI_pOutStr)
//             X coordinate of the text upper-left-hand starting point (unsigned int GXI_locX)
//             Y coordinate of the text upper-left-hand starting point (const unsigned int GXI_locY)
//             Red color component of the text to draw (const unsigned int GXI_colR)
//             Green color component of the text to draw (const unsigned int GXI_colG)
//             Blue color component of the text to draw (const unsigned int GXI_colB)
// ************************************************************************************************
void GX_drawText(unsigned char* GXI_pFont, const TCHAR* GXI_pOutStr, const unsigned int GXI_Alignment, unsigned int GXI_locX, const unsigned int GXI_locY, const unsigned int GXI_colR, const unsigned int GXI_colG, const unsigned int GXI_colB) {
	unsigned int				strLen = wcslen(GXI_pOutStr);
	unsigned short int* pPointAddr;
	unsigned char*      pCharStart;
	unsigned int				y;
	unsigned int				pixCol;
	unsigned int				i;
	unsigned int				currChar;
	unsigned int				currRow;
	unsigned int				bitTest;
	unsigned int				yVal;
	switch (GXI_Alignment) {
		case GX_ALIGN_LEFT: {
			GXI_locX = 0;
		break; }
		case GX_ALIGN_CENTER: {
			GXI_locX = wcslen(GXI_pOutStr);
			GXI_locX = (240 - ((GXI_locX << 3) + GXI_locX - 1)) / 2;
		break; }
		case GX_ALIGN_RIGHT: {
			GXI_locX = wcslen(GXI_pOutStr);
			GXI_locX = (240 - (GXI_locX << 3)) - (GXI_locX - 1);
		break; }
	}
	// Calculate our color based on the display type and RGB values, used later
	pixCol = (unsigned short int)(((GXI_colR & 0xf8) << 8) | ((GXI_colG & 0xfc) << 3) | (GXI_colB >> 3));
	for (i = 0; i < strLen; i++) {
		// Get the next character code in the string and advance to the next one
		currChar = (unsigned char)(*GXI_pOutStr);
		GXI_pOutStr++;
		// Set our pointer to the start of THIS character
		pCharStart = GXI_pFont + (currChar << 4);
		// Loop through each row in the character
		for (y = 0; y < 16; y++) {
			// Calculate our Y value for plotting
			yVal = ((GXI_locY + y) * GX_yPitch);
			// Grab the byte representing our current row
			currRow = *(pCharStart + y);
			// Go through each bit in the current row and plot those that should be plotted
			bitTest = 0x01 << 7;
			if ((currRow & bitTest) != 0) {
				pPointAddr  = GX_pScreenBuffer + (GXI_locX * GX_xPitch) + yVal;
				*pPointAddr = pixCol;
			}
			bitTest = 0x01 << 6;
			if ((currRow & bitTest) != 0) {
				pPointAddr  = GX_pScreenBuffer + ((GXI_locX + 1) * GX_xPitch) + yVal;
				*pPointAddr = pixCol;
			}
			bitTest = 0x01 << 5;
			if ((currRow & bitTest) != 0) {
				pPointAddr  = GX_pScreenBuffer + ((GXI_locX + 2) * GX_xPitch) + yVal;
				*pPointAddr = pixCol;
			}
			bitTest = 0x01 << 4;
			if ((currRow & bitTest) != 0) {
				pPointAddr  = GX_pScreenBuffer + ((GXI_locX + 3) * GX_xPitch) + yVal;
				*pPointAddr = pixCol;
			}
			bitTest = 0x01 << 3;
			if ((currRow & bitTest) != 0) {
				pPointAddr  = GX_pScreenBuffer + ((GXI_locX + 4) * GX_xPitch) + yVal;
				*pPointAddr = pixCol;
			}
			bitTest = 0x01 << 2;
			if ((currRow & bitTest) != 0) {
				pPointAddr  = GX_pScreenBuffer + ((GXI_locX + 5) * GX_xPitch) + yVal;
				*pPointAddr = pixCol;
			}
			bitTest = 0x01 << 1;
			if ((currRow & bitTest) != 0) {
				pPointAddr  = GX_pScreenBuffer + ((GXI_locX + 6) * GX_xPitch) + yVal;
				*pPointAddr = pixCol;
			}
			bitTest = 0x01 << 0;
			if ((currRow & bitTest) != 0) {
				pPointAddr  = GX_pScreenBuffer + ((GXI_locX + 7) * GX_xPitch) + yVal;
				*pPointAddr = pixCol;
			}
		}
		// Advance to the next character
		GXI_locX = GXI_locX + 9;
	}
}


// ************************************************************************************************
// GX_storeRegion
// Routine to store a portion of the screen before a sprite is placed over it
// Parameters: X coordinate of the upper left-hand corner of the region (const unsigned int GXI_regL)
//             Y coordinate of the upper left-hand corner of the region (const unsigned int GXI_regT)
//             X coordinate of the lower right-hand corner of the region (const unsigned int GXI_regR)
//             Y coordinate of the lower right-hand corner of the region (const unsigned int GXI_regB)
// ************************************************************************************************
void GX_storeRegion(const unsigned char* GXI_pSprite, const unsigned char* GXI_pPalette, const unsigned int GXI_transparentColor, const unsigned int GXI_regL, const unsigned int GXI_regT, const unsigned int GXI_regR, const unsigned int GXI_regB) {
	unsigned int				x;
	unsigned int				y;
	unsigned int				yVal;
	unsigned int				calcVal;
	unsigned short int* pSrcAddr;
	unsigned short int* pDestAddr;
	if (GXI_pSprite == NULL) { // Store entire square region
		for (y = GXI_regT; y < GXI_regB; y++) {
			yVal = (y * GX_yPitch);
			for (x = GXI_regL; x < GXI_regR; x++) {
				calcVal = (x * GX_xPitch) + yVal;
				// Point to the address of the next pixel to restore
				pSrcAddr   = GX_pScreenBuffer + calcVal;
				// Point to the correct location of the pixel in the screen buffer
				pDestAddr  = GX_pTempArea			+ calcVal;
				// Write the value of the source pixel into the screen buffer
				*pDestAddr = *pSrcAddr;
			}
		}
	} else { // Use passed-in sprite to only copy region under non-transparent pixels in sprite
		unsigned int pixVal;
		GXI_pSprite = GXI_pSprite + 4; // Skip the width and height header
		for (y = GXI_regT; y < GXI_regB; y++) {
			yVal = (y * GX_yPitch);
			for (x = GXI_regL; x < GXI_regR; x++) {
				// Get the value of this pixel (which is an index into our palette)
				pixVal = *GXI_pSprite;
				// Move on to the next pixel after this
				GXI_pSprite++;
				if (pixVal != GXI_transparentColor) {
					calcVal = (x * GX_xPitch) + yVal;
					// Point to the address of the next pixel to restore
					pSrcAddr   = GX_pScreenBuffer + calcVal;
					// Point to the correct location of the pixel in the screen buffer
					pDestAddr  = GX_pTempArea			+ calcVal;
					// Write the value of the source pixel into the screen buffer
					*pDestAddr = *pSrcAddr;
				}
			}
		}
	}
}


// ************************************************************************************************
// GX_restoreRegion
// Routine to restore a portion of the screen after a sprite has been moved elsewhere
// Parameters: X coordinate of the upper left-hand corner of the region (const unsigned int GXI_regL)
//             Y coordinate of the upper left-hand corner of the region (const unsigned int GXI_regT)
//             X coordinate of the lower right-hand corner of the region (const unsigned int GXI_regR)
//             Y coordinate of the lower right-hand corner of the region (const unsigned int GXI_regB)
// ************************************************************************************************
void GX_restoreRegion(const unsigned char* GXI_pSprite, const unsigned char* GXI_pPalette, const unsigned int GXI_transparentColor, const unsigned int GXI_regL, const unsigned int GXI_regT, const unsigned int GXI_regR, const unsigned int GXI_regB) {
	unsigned int				x;
	unsigned int				y;
	unsigned int				yVal;
	unsigned int				calcVal;
	unsigned short int* pSrcAddr;
	unsigned short int* pDestAddr;
	if (GXI_pSprite == NULL) { // Restore entire square region
		for (y = GXI_regT; y < GXI_regB; y++) {
			yVal = (y * GX_yPitch);
			for (x = GXI_regL; x < GXI_regR; x++) {
				calcVal = (x * GX_xPitch) + yVal;
				// Point to the address of the next pixel to store
				pSrcAddr   = GX_pTempArea + calcVal;
				// Point to the correct location of the pixel in the temporary area
				pDestAddr  = GX_pScreenBuffer + calcVal;
				*pDestAddr = *pSrcAddr;
			}
		}
	} else { // Use passed-in sprite to only copy region under non-transparent pixels in sprite
		unsigned int pixVal;
		GXI_pSprite = GXI_pSprite + 4; // Skip the width and height header
		for (y = GXI_regT; y < GXI_regB; y++) {
			yVal = (y * GX_yPitch);
			for (x = GXI_regL; x < GXI_regR; x++) {
				// Get the value of this pixel (which is an index into our palette)
				pixVal = *GXI_pSprite;
				// Move on to the next pixel after this
				GXI_pSprite++;
				if (pixVal != GXI_transparentColor) {
					calcVal = (x * GX_xPitch) + yVal;
					// Point to the address of the next pixel to store
					pSrcAddr   = GX_pTempArea + calcVal;
					// Point to the correct location of the pixel in the temporary area
					pDestAddr  = GX_pScreenBuffer + calcVal;
					*pDestAddr = *pSrcAddr;
				}
			}
		}
	}
}


// ************************************************************************************************
// GX_fillRegion
// Fills a rectangular region with a given color
// Parameters: X coordinate of the upper left-hand corner of the region (const unsigned int GXI_regL)
//             Y coordinate of the upper left-hand corner of the region (const unsigned int GXI_regT)
//             X coordinate of the lower right-hand corner of the region (const unsigned int GXI_regR)
//             Y coordinate of the lower right-hand corner of the region (const unsigned int GXI_regB)
//             Red color component to fill with (const unsigned int GXI_colR)
//             Green color component to fill with (const unsigned int GXI_colG)
//             Blue color component to fill with (const unsigned int GXI_colB)
// ************************************************************************************************
void GX_fillRegion(const unsigned int GXI_regL, const unsigned int GXI_regT, const unsigned int GXI_regR, const unsigned int GXI_regB, const unsigned int GXI_colR, const unsigned int GXI_colG, const unsigned int GXI_colB) {
	unsigned int				x;
	unsigned int				y;
	unsigned int				yVal;
	unsigned short int  pixCol;
	unsigned short int* pPointAddr;
	// Calculate our color based on the display type and RGB values
	pixCol = (unsigned short int)(((GXI_colR & 0xf8) << 8) | ((GXI_colG & 0xfc) << 3) | (GXI_colB >> 3));
	for (y = GXI_regT; y < GXI_regB; y++) {
		yVal = (y * GX_yPitch);
		for (x = GXI_regL; x < GXI_regR; x++) {
			// Point to the correct memory location for the pixel
			pPointAddr  = GX_pScreenBuffer + (x * GX_xPitch) + yVal;
			// Write color value to memory location for our pixel
			*pPointAddr = pixCol;
		}
	}
}


// ************************************************************************************************
// GX_clearScreen
// Clears the screen, filling it with a given color
// Parameters: Red color component to fill with (const unsigned int GXI_colR)
//             Green color component to fill with (const unsigned int GXI_colG)
//             Blue color component to fill with (const unsigned int GXI_colB)
// ************************************************************************************************
void GX_clearScreen(const unsigned int GXI_colR, const unsigned int GXI_colG, const unsigned int GXI_colB) {
	signed int					x;
	signed int					y;
	unsigned int				yVal;
	unsigned int				pixCol;
	unsigned short int* pPointAddr;
	// Calculate our color based on the display type and RGB values
	pixCol = (unsigned short int)(((GXI_colR & 0xf8) << 8) | ((GXI_colG & 0xfc) << 3) | (GXI_colB >> 3));
	for (y = 320; y > -1; y--) {
		yVal = (y * GX_yPitch);
		for (x = 240; x > -1; x--) {
			// Point to the correct memory location for the pixel
			pPointAddr  = GX_pScreenBuffer + (x * GX_xPitch) + yVal;
			// Write color value to memory location for our pixel
			*pPointAddr = pixCol;
		}
	}
}


// ************************************************************************************************
// GX_dimRegion
// Dims a region of the screen by a given percentage
// Parameters: X coordinate of the upper left-hand corner of the region (const unsigned int GXI_regL)
//             Y coordinate of the upper left-hand corner of the region (const unsigned int GXI_regT)
//             X coordinate of the lower right-hand corner of the region (const unsigned int GXI_regR)
//             Y coordinate of the lower right-hand corner of the region (const unsigned int GXI_regB)
//             Percent of original brightness desired (const unsigned int GXI_dimPercent)
// ************************************************************************************************
void GX_dimRegion(const unsigned int GXI_regL, const unsigned int GXI_regT, const unsigned int GXI_regR, const unsigned int GXI_regB, const unsigned int GXI_dimPercent) {
	unsigned int				x;
	unsigned int				y;
	unsigned int				yVal;
	unsigned int				newR;
	unsigned int				newG;
	unsigned int				newB;
	unsigned int				newPixCol;
	unsigned int				oldPixCol;
	unsigned short int* pPointAddr;
	for (y = GXI_regT; y < GXI_regB; y++) {
		yVal = (y * GX_yPitch);
		for (x = GXI_regL; x < GXI_regR; x++) {
			// Point to the correct memory location for the pixel
			pPointAddr  = GX_pScreenBuffer + (x * GX_xPitch) + yVal;
			// Get color value from memory location for next pixel
			oldPixCol = *pPointAddr;
			newR = (unsigned int)((((oldPixCol & 0xf800) >> 8) * GXI_dimPercent) / 100); 
			newG = (unsigned int)((((oldPixCol & 0x7e0)  >> 3) * GXI_dimPercent) / 100); 
			newB = (unsigned int)((((oldPixCol & 0x001f) << 3) * GXI_dimPercent) / 100); 
			// Calculate our color based on the display type and RGB values
			newPixCol = (unsigned int)(((newR & 0xf8) << 8) | ((newG & 0xfc) << 3) | (newB >> 3));
			// Write color value to memory location for our pixel
			*pPointAddr = newPixCol;
		}
	}
}


// ************************************************************************************************
// GX_drawSpriteTC
// Draws an image on the screen.
// DOES do transparency, DOES do screen bounds checking, DOES NOT do sprite portions
// Parameters: Pointer to the sprite to draw (const unsigned char* pSprite)
//             Pointer to the palette to use for drawing the sprite (const unsigned char* GXI_pPalette)
//             X coordinate of the sprite upper-left-hand starting point (const unsigned int GXI_locX)
//             Y coordinate of the sprite upper-left-hand starting point (const unsigned int GXI_locY)
//             Index into palette of color to use for transparency.  (const unsigned int GXI_transparentColor)
// ************************************************************************************************
void GX_drawSpriteTC(const unsigned char* GXI_pSprite, const unsigned char* GXI_pPalette, const int GXI_locX, const int GXI_locY, const unsigned int GXI_transparentColor) {
	// Get the width and height of our image.  Our image format is simple: it's an RGB .RAW filw
  // with a 4 byte header: the first two bytes are our wifth, the next two are our height.
	const int						 sizeX = (*(GXI_pSprite)		 << 8) + *(GXI_pSprite + 1);
	const int						 sizeY = (*(GXI_pSprite + 2) << 8) + *(GXI_pSprite + 3);
	const unsigned char* pPalIndex;
	unsigned short int*  pPointAddr;
	unsigned int				 pixVal;
	int									 x;
	int									 y;
	unsigned int				 pixCol;
	int									 yVal;
	int									 bcY;
	GXI_pSprite = GXI_pSprite + 4; // Skip the width and height header
	for (y = 0; y < sizeY; y++) {
		yVal = ((GXI_locY + y) * GX_yPitch);
		bcY = GXI_locY + y;
		for (x = 0; x < sizeX; x++) {
			// Get the value of this pixel (which is an index into our palette)
			pixVal = *GXI_pSprite;
			// Move on to the next pixel after this
			GXI_pSprite++;
			// Perform screen bounds clipping checks
			if ((GXI_locX + x) < 0)		{ continue; }
			if ((GXI_locX + x) > 240) { continue; }
			if (bcY < 0)							{ continue; }
			if (bcY > 320)						{ continue; }
			// If this pixel's color isn't the transparent color or transparency isn't in use, draw pixel
			if (pixVal != GXI_transparentColor) {
				// Point to the address of our RGB colors in the palette
				// NOTE: Microsoft palette format, colors are 4 bytes (pixelValue<<2 means pixelValue*4)
				pPalIndex = GXI_pPalette + (pixVal << 2);
				// Calculate our color based on the display type and RGB values
				pixCol = (unsigned int)(((*pPalIndex       & 0xf8) << 8) | 
						  									((*(pPalIndex + 1) & 0xfc) << 3) | 
																 (*(pPalIndex + 2)         >> 3));
				// Point to the correct memory location for the pixel
				pPointAddr  = GX_pScreenBuffer + ((GXI_locX + x) * GX_xPitch) + yVal;
				// Write color value to memory location for our pixel
				*pPointAddr = pixCol;
			}
		}
	}
}


// ************************************************************************************************
// GX_drawSpriteC
// Draws an image on the screen.
// DOES NOT do transparency, DOES do screen bounds checking, DOES NOT do sprite portions
// Parameters: Pointer to the sprite to draw (const unsigned char* pSprite)
//             Pointer to the palette to use for drawing the sprite (const unsigned char* GXI_pPalette)
//             X coordinate of the sprite upper-left-hand starting point (const unsigned int GXI_locX)
//             Y coordinate of the sprite upper-left-hand starting point (const unsigned int GXI_locY)
// ************************************************************************************************
void GX_drawSpriteC(const unsigned char* GXI_pSprite, const unsigned char* GXI_pPalette, const int GXI_locX, const int GXI_locY) {
	// Get the width and height of our image.  Our image format is simple: it's an RGB .RAW filw
  // with a 4 byte header: the first two bytes are our wifth, the next two are our height.
	const int						 sizeX = (*(GXI_pSprite)		 << 8) + *(GXI_pSprite + 1);
	const int						 sizeY = (*(GXI_pSprite + 2) << 8) + *(GXI_pSprite + 3);
	const unsigned char* pPalIndex;
	unsigned short int*  pPointAddr;
	unsigned int				 pixVal;
	int									 x;
	int									 y;
	unsigned int				 pixCol;
	int									 yVal;
	int									 bcY;
	GXI_pSprite = GXI_pSprite + 4; // Skip the width and height header
	for (y = 0; y < sizeY; y++) {
		yVal = ((GXI_locY + y) * GX_yPitch);
		bcY = GXI_locY + y;
		for (x = 0; x < sizeX; x++) {
			// Get the value of this pixel (which is an index into our palette)
			pixVal = *GXI_pSprite;
			// Move on to the next pixel after this
			GXI_pSprite++;
			// Perform screen bounds clipping checks
			if ((GXI_locX + x) < 0)		{ continue; }
			if ((GXI_locX + x) > 240) { continue; }
			if (bcY < 0)							{ continue; }
			if (bcY > 320)						{ continue; }
			// Point to the address of our RGB colors in the palette
			// NOTE: Microsoft palette format, colors are 4 bytes (pixelValue<<2 means pixelValue*4)
			pPalIndex = GXI_pPalette + (pixVal << 2);
			// Calculate our color based on the display type and RGB values
			pixCol = (unsigned int)(((*pPalIndex       & 0xf8) << 8) | 
					  									((*(pPalIndex + 1) & 0xfc) << 3) | 
															 (*(pPalIndex + 2)         >> 3));
			// Point to the correct memory location for the pixel
			pPointAddr  = GX_pScreenBuffer + ((GXI_locX + x) * GX_xPitch) + yVal;
			// Write color value to memory location for our pixel
			*pPointAddr = pixCol;
		}
	}
}


// ************************************************************************************************
// GX_drawSpriteT
// Draws an image on the screen.
// DOES do transparency, DOES NOT do screen bounds checking, DOES NOT do sprite portions
// Parameters: Pointer to the sprite to draw (unsigned char* pSprite)
//             Pointer to the palette to use for drawing the sprite (const unsigned char* GXI_pPalette)
//             X coordinate of the sprite upper-left-hand starting point (const unsigned int GXI_locX)
//             Y coordinate of the sprite upper-left-hand starting point (const unsigned int GXI_locY)
//             Index into palette of color to use for transparency.  (const unsigned short int GXI_transparentColor)
// ************************************************************************************************
void GX_drawSpriteT(const unsigned char* GXI_pSprite, const unsigned char* GXI_pPalette, const int GXI_locX, const int GXI_locY, const unsigned int GXI_transparentColor) {
	// Get the width and height of our image.  Our image format is simple: it's an RGB .RAW filw
  // with a 4 byte header: the first two bytes are our wifth, the next two are our height.
	const int						 sizeX = (*(GXI_pSprite)		 << 8) + *(GXI_pSprite + 1);
	const int						 sizeY = (*(GXI_pSprite + 2) << 8) + *(GXI_pSprite + 3);
	const unsigned char* pPalIndex;
	unsigned short int*  pPointAddr;
	unsigned int				 pixVal;
	int									 x;
	int									 y;
	unsigned int				 pixCol;
	int									 yVal;
	GXI_pSprite = GXI_pSprite + 4; // Skip the width and height header
	for (y = 0; y < sizeY; y++) {
		yVal = ((GXI_locY + y) * GX_yPitch);
		for (x = 0; x < sizeX; x++) {
			// Get the value of this pixel (which is an index into our palette)
			pixVal = *GXI_pSprite;
			// Move on to the next pixel after this
			GXI_pSprite++;
			// If this pixel's color isn't the transparent color or transparency isn't in use, draw pixel
			if (pixVal != GXI_transparentColor) {
				// Point to the address of our RGB colors in the palette
				// NOTE: Microsoft palette format, colors are 4 bytes (pixelValue<<2 means pixelValue*4)
				pPalIndex = GXI_pPalette + (pixVal << 2);
				// Calculate our color based on the display type and RGB values
				pixCol = (unsigned int)(((*pPalIndex       & 0xf8) << 8) | 
						  									((*(pPalIndex + 1) & 0xfc) << 3) | 
																 (*(pPalIndex + 2)         >> 3));
				// Point to the correct memory location for the pixel
				pPointAddr  = GX_pScreenBuffer + ((GXI_locX + x) * GX_xPitch) + yVal;
				// Write color value to memory location for our pixel
				*pPointAddr = pixCol;
			}
		}
	}
}


// ************************************************************************************************
// GX_drawSpriteNNN
// Draws an image on the screen.
// DOES NOT do transparency, DOES NOT do screen bounds checking, DOES NOT do sprite portions
// Parameters: Pointer to the sprite to draw (unsigned char* pSprite)
//             Pointer to the palette to use for drawing the sprite (const unsigned char* GXI_pPalette)
//             X coordinate of the sprite upper-left-hand starting point (const unsigned int GXI_locX)
//             Y coordinate of the sprite upper-left-hand starting point (const unsigned int GXI_locY)
// ************************************************************************************************
void GX_drawSpriteNNN(const unsigned char* GXI_pSprite, const unsigned char* GXI_pPalette, const int GXI_locX, const int GXI_locY) {
	// Get the width and height of our image.  Our image format is simple: it's an RGB .RAW filw
  // with a 4 byte header: the first two bytes are our wifth, the next two are our height.
	const int						 sizeX = (*(GXI_pSprite)		 << 8) + *(GXI_pSprite + 1);
	const int						 sizeY = (*(GXI_pSprite + 2) << 8) + *(GXI_pSprite + 3);
	const unsigned char* pPalIndex;
	unsigned short int*  pPointAddr;
	unsigned int				 pixVal;
	int									 x;
	int									 y;
	unsigned int				 pixCol;
	int									 yVal;
	GXI_pSprite = GXI_pSprite + 4; // Skip the width and height header
	for (y = 0; y < sizeY; y++) {
		yVal = ((GXI_locY + y) * GX_yPitch);
		for (x = 0; x < sizeX; x++) {
			// Get the value of this pixel (which is an index into our palette)
			pixVal = *GXI_pSprite;
			// Move on to the next pixel after this
			GXI_pSprite++;
			// Point to the address of our RGB colors in the palette
			// NOTE: Microsoft palette format, colors are 4 bytes (pixelValue<<2 means pixelValue*4)
			pPalIndex = GXI_pPalette + (pixVal << 2);
			// Calculate our color based on the display type and RGB values
			pixCol = (unsigned int)(((*pPalIndex       & 0xf8) << 8) | 
					  									((*(pPalIndex + 1) & 0xfc) << 3) | 
															 (*(pPalIndex + 2)         >> 3));
			// Point to the correct memory location for the pixel
			pPointAddr  = GX_pScreenBuffer + ((GXI_locX + x) * GX_xPitch) + yVal;
			// Write color value to memory location for our pixel
			*pPointAddr = pixCol;
		}
	}
}


// ************************************************************************************************
// GX_drawSpriteTCP
// Draws an image on the screen.
// DOES do transparency, DOES do screen bounds checking, DOES do sprite portions
// Parameters: Pointer to the sprite to draw (const unsigned char* pSprite)
//             Pointer to the palette to use for drawing the sprite (const unsigned char* GXI_pPalette)
//             X coordinate of the sprite upper-left-hand starting point (const unsigned int GXI_locX)
//             Y coordinate of the sprite upper-left-hand starting point (const unsigned int GXI_locY)
//             Index into palette of color to use for transparency.  (const unsigned int GXI_transparentColor)
//						 X coordinate of sprite portion if applicable (const unsigned int GXI_portStartX)
//						 Y coordinate of sprite portion if applicable (const unsigned int GXI_portStartY)
//						 Width of sprite portion if applicable (const unsigned int GXI_portSizeX)
//						 Height of sprite portion if applicable (const unsigned int GXI_portSizeY)
// ************************************************************************************************
void GX_drawSpriteTCP(const unsigned char* GXI_pSprite, const unsigned char* GXI_pPalette, int GXI_locX, int GXI_locY, const unsigned int GXI_transparentColor, const int GXI_portStartX, const int GXI_portStartY, const int GXI_portSizeX, const int GXI_portSizeY) {
	// Get the width and height of our image.  Our image format is simple: it's an RGB .RAW filw
  // with a 4 byte header: the first two bytes are our wifth, the next two are our height.
	const int						 sizeX = (*(GXI_pSprite)		 << 8) + *(GXI_pSprite + 1);
	const int						 sizeY = (*(GXI_pSprite + 2) << 8) + *(GXI_pSprite + 3);
	const unsigned char* pPalIndex;
	unsigned short int*  pPointAddr;
	unsigned int				 pixVal;
	int									 x;
	int									 y;
	int									 locX;
	int									 locY = GXI_locY;
	unsigned int				 pixCol;
	int									 yVal;
	int									 bcY;
	int									 yPosCalc;
	GXI_pSprite = GXI_pSprite + 4; // Skip the width and height header
	for (y = GXI_portStartY; y < (GXI_portStartY + GXI_portSizeY); y++) {
		yPosCalc = y * sizeX; // Source
		yVal = (GXI_locY * GX_yPitch); // Destination
		GXI_locY++;
		locX = GXI_locX;
		bcY = GXI_locY + y;
		for (x = GXI_portStartX; x < (GXI_portStartX + GXI_portSizeX); x++) {
			// Get the value of this pixel (which is an index into our palette)
			pixVal = *(GXI_pSprite + yPosCalc + x);
			// Perform screen bounds clipping checks
			if ((GXI_locX + x) < 0)		{ continue; }
			if ((GXI_locX + x) > 240) { continue; }
			if (bcY < 0)							{ continue; }
			if (bcY > 320)						{ continue; }
			// If this pixel's color isn't the transparent color or transparency isn't in use, draw pixel
			if (pixVal != GXI_transparentColor) {
				// Point to the address of our RGB colors in the palette
				// NOTE: Microsoft palette format, colors are 4 bytes (pixelValue<<2 means pixelValue*4)
				pPalIndex = GXI_pPalette + (pixVal << 2);
				// Calculate our color based on the display type and RGB values
				pixCol = (unsigned int)(((*pPalIndex       & 0xf8) << 8) | 
						  									((*(pPalIndex + 1) & 0xfc) << 3) | 
																 (*(pPalIndex + 2)         >> 3));
				// Point to the correct memory location for the pixel
				pPointAddr  = GX_pScreenBuffer + (locX * GX_xPitch) + yVal;
				// Write color value to memory location for our pixel
				*pPointAddr = pixCol;
				locX++;
			}
		}
	}
}


// ************************************************************************************************
// GX_drawSpriteTP
// Draws an image on the screen.
// DOES do transparency, DOES NOT do screen bounds checking, DOES do sprite portions
// Parameters: Pointer to the sprite to draw (const unsigned char* pSprite)
//             Pointer to the palette to use for drawing the sprite (const unsigned char* GXI_pPalette)
//             X coordinate of the sprite upper-left-hand starting point (const unsigned int GXI_locX)
//             Y coordinate of the sprite upper-left-hand starting point (const unsigned int GXI_locY)
//             Index into palette of color to use for transparency.  (const unsigned int GXI_transparentColor)
//						 X coordinate of sprite portion if applicable (const unsigned int GXI_portStartX)
//						 Y coordinate of sprite portion if applicable (const unsigned int GXI_portStartY)
//						 Width of sprite portion if applicable (const unsigned int GXI_portSizeX)
//						 Height of sprite portion if applicable (const unsigned int GXI_portSizeY)
// ************************************************************************************************
void GX_drawSpriteTP(const unsigned char* GXI_pSprite, const unsigned char* GXI_pPalette, int GXI_locX, int GXI_locY, const unsigned int GXI_transparentColor, const int GXI_portStartX, const int GXI_portStartY, const int GXI_portSizeX, const int GXI_portSizeY) {
	// Get the width and height of our image.  Our image format is simple: it's an RGB .RAW filw
  // with a 4 byte header: the first two bytes are our wifth, the next two are our height.
	const int						 sizeX = (*(GXI_pSprite)		 << 8) + *(GXI_pSprite + 1);
	const int						 sizeY = (*(GXI_pSprite + 2) << 8) + *(GXI_pSprite + 3);
	const unsigned char* pPalIndex;
	unsigned short int*  pPointAddr;
	unsigned int				 pixVal;
	int									 x;
	int									 y;
	int									 locX;
	int									 locY = GXI_locY;
	unsigned int				 pixCol;
	int									 yVal;
	int									 yPosCalc;
	GXI_pSprite = GXI_pSprite + 4; // Skip the width and height header
	for (y = GXI_portStartY; y < (GXI_portStartY + GXI_portSizeY); y++) {
		yPosCalc = y * sizeX; // Source
		yVal = (GXI_locY * GX_yPitch); // Destination
		GXI_locY++;
		locX = GXI_locX;
		for (x = GXI_portStartX; x < (GXI_portStartX + GXI_portSizeX); x++) {
			// Get the value of this pixel (which is an index into our palette)
			pixVal = *(GXI_pSprite + yPosCalc + x);
			// If this pixel's color isn't the transparent color or transparency isn't in use, draw pixel
			if (pixVal != GXI_transparentColor) {
				// Point to the address of our RGB colors in the palette
				// NOTE: Microsoft palette format, colors are 4 bytes (pixelValue<<2 means pixelValue*4)
				pPalIndex = GXI_pPalette + (pixVal << 2);
				// Calculate our color based on the display type and RGB values
				pixCol = (unsigned int)(((*pPalIndex       & 0xf8) << 8) | 
						  									((*(pPalIndex + 1) & 0xfc) << 3) | 
																 (*(pPalIndex + 2)         >> 3));
				// Point to the correct memory location for the pixel
				pPointAddr  = GX_pScreenBuffer + (locX * GX_xPitch) + yVal;
				// Write color value to memory location for our pixel
				*pPointAddr = pixCol;
				locX++;
			}
		}
	}
}


// ************************************************************************************************
// GX_drawSpriteCP
// Draws an image on the screen.
// DOES NOT do transparency, DOES do screen bounds checking, DOES do sprite portions
// Parameters: Pointer to the sprite to draw (const unsigned char* pSprite)
//             Pointer to the palette to use for drawing the sprite (const unsigned char* GXI_pPalette)
//             X coordinate of the sprite upper-left-hand starting point (const unsigned int GXI_locX)
//             Y coordinate of the sprite upper-left-hand starting point (const unsigned int GXI_locY)
//						 X coordinate of sprite portion if applicable (const unsigned int GXI_portStartX)
//						 Y coordinate of sprite portion if applicable (const unsigned int GXI_portStartY)
//						 Width of sprite portion if applicable (const unsigned int GXI_portSizeX)
//						 Height of sprite portion if applicable (const unsigned int GXI_portSizeY)
// ************************************************************************************************
void GX_drawSpriteCP(const unsigned char* GXI_pSprite, const unsigned char* GXI_pPalette, int GXI_locX, int GXI_locY, const int GXI_portStartX, const int GXI_portStartY, const int GXI_portSizeX, const int GXI_portSizeY) {
	// Get the width and height of our image.  Our image format is simple: it's an RGB .RAW filw
  // with a 4 byte header: the first two bytes are our wifth, the next two are our height.
	const int						 sizeX = (*(GXI_pSprite)		 << 8) + *(GXI_pSprite + 1);
	const int						 sizeY = (*(GXI_pSprite + 2) << 8) + *(GXI_pSprite + 3);
	const unsigned char* pPalIndex;
	unsigned short int*  pPointAddr;
	unsigned int				 pixVal;
	int									 x;
	int									 y;
	int									 locX;
	int									 locY = GXI_locY;
	unsigned int				 pixCol;
	int									 yVal;
	int									 bcY;
	int									 yPosCalc;
	GXI_pSprite = GXI_pSprite + 4; // Skip the width and height header
	for (y = GXI_portStartY; y < (GXI_portStartY + GXI_portSizeY); y++) {
		yPosCalc = y * sizeX; // Source
		yVal = (GXI_locY * GX_yPitch); // Destination
		GXI_locY++;
		locX = GXI_locX;
		bcY = GXI_locY + y;
		for (x = GXI_portStartX; x < (GXI_portStartX + GXI_portSizeX); x++) {
			// Get the value of this pixel (which is an index into our palette)
			pixVal = *(GXI_pSprite + yPosCalc + x);
			// Perform screen bounds clipping checks
			if ((GXI_locX + x) < 0)		{ continue; }
			if ((GXI_locX + x) > 240) { continue; }
			if (bcY < 0)							{ continue; }
			if (bcY > 320)						{ continue; }
			// Point to the address of our RGB colors in the palette
			// NOTE: Microsoft palette format, colors are 4 bytes (pixelValue<<2 means pixelValue*4)
			pPalIndex = GXI_pPalette + (pixVal << 2);
			// Calculate our color based on the display type and RGB values
			pixCol = (unsigned int)(((*pPalIndex       & 0xf8) << 8) | 
					  									((*(pPalIndex + 1) & 0xfc) << 3) | 
															 (*(pPalIndex + 2)         >> 3));
			// Point to the correct memory location for the pixel
			pPointAddr  = GX_pScreenBuffer + (locX * GX_xPitch) + yVal;
			// Write color value to memory location for our pixel
			*pPointAddr = pixCol;
			locX++;
		}
	}
}


// ************************************************************************************************
// GX_drawSpriteP
// Draws an image on the screen.
// DOES NOT do transparency, DOES NOT do screen bounds checking, DOES do sprite portions
// Parameters: Pointer to the sprite to draw (const unsigned char* pSprite)
//             Pointer to the palette to use for drawing the sprite (const unsigned char* GXI_pPalette)
//             X coordinate of the sprite upper-left-hand starting point (const unsigned int GXI_locX)
//             Y coordinate of the sprite upper-left-hand starting point (const unsigned int GXI_locY)
//						 X coordinate of sprite portion if applicable (const unsigned int GXI_portStartX)
//						 Y coordinate of sprite portion if applicable (const unsigned int GXI_portStartY)
//						 Width of sprite portion if applicable (const unsigned int GXI_portSizeX)
//						 Height of sprite portion if applicable (const unsigned int GXI_portSizeY)
// ************************************************************************************************
void GX_drawSpriteP(const unsigned char* GXI_pSprite, const unsigned char* GXI_pPalette, int GXI_locX, int GXI_locY, const int GXI_portStartX, const int GXI_portStartY, const int GXI_portSizeX, const int GXI_portSizeY) {
	// Get the width and height of our image.  Our image format is simple: it's an RGB .RAW filw
  // with a 4 byte header: the first two bytes are our wifth, the next two are our height.
	const int						 sizeX = (*(GXI_pSprite)		 << 8) + *(GXI_pSprite + 1);
	const int						 sizeY = (*(GXI_pSprite + 2) << 8) + *(GXI_pSprite + 3);
	const unsigned char* pPalIndex;
	unsigned short int*  pPointAddr;
	unsigned int				 pixVal;
	int									 x;
	int									 y;
	int									 locX;
	int									 locY = GXI_locY;
	unsigned int				 pixCol;
	int									 yVal;
	int									 yPosCalc;
	GXI_pSprite = GXI_pSprite + 4; // Skip the width and height header
	for (y = GXI_portStartY; y < (GXI_portStartY + GXI_portSizeY); y++) {
		yPosCalc = y * sizeX; // Source
		yVal = (GXI_locY * GX_yPitch); // Destination
		GXI_locY++;
		locX = GXI_locX;
		for (x = GXI_portStartX; x < (GXI_portStartX + GXI_portSizeX); x++) {
			// Get the value of this pixel (which is an index into our palette)
			pixVal = *(GXI_pSprite + yPosCalc + x);
			// Point to the address of our RGB colors in the palette
			// NOTE: Microsoft palette format, colors are 4 bytes (pixelValue<<2 means pixelValue*4)
			pPalIndex = GXI_pPalette + (pixVal << 2);
			// Calculate our color based on the display type and RGB values
			pixCol = (unsigned int)(((*pPalIndex       & 0xf8) << 8) | 
					  									((*(pPalIndex + 1) & 0xfc) << 3) | 
															 (*(pPalIndex + 2)         >> 3));
			// Point to the correct memory location for the pixel
			pPointAddr  = GX_pScreenBuffer + (locX * GX_xPitch) + yVal;
			// Write color value to memory location for our pixel
			*pPointAddr = pixCol;
			locX++;
		}
	}
}


// ************************************************************************************************
// GX_drawSprite
// This is the base sprite drawing function that is always called.  It looks at the parameters
// passed in and calls the appropriate version of the drawSprite code.
// Parameters: Pointer to the sprite to draw (const unsigned char* pSprite)
//             Pointer to the palette to use for drawing the sprite (const unsigned char* GXI_pPalette)
//             X coordinate of the sprite upper-left-hand starting point (const unsigned int GXI_locX)
//             Y coordinate of the sprite upper-left-hand starting point (const unsigned int GXI_locY)
//						 Should transparency be done? (const BOOL GXI_transparency)
//             Index into palette of color to use for transparency if applicable (const unsigned int GXI_transparentColor)
//						 Should screen bounds checking be done? (const BOOL GXI_boundsChecking)
//						 Should a portion of a sprite be drawn? (const BOOL GXI_spritePortion)
//						 X coordinate of sprite portion if applicable (const unsigned int GXI_portStartX)
//						 Y coordinate of sprite portion if applicable (const unsigned int GXI_portStartY)
//						 Width of sprite portion if applicable (const unsigned int GXI_portSizeX)
//						 Height of sprite portion if applicable (const unsigned int GXI_portSizeY)
// ************************************************************************************************
void GX_drawSprite(const unsigned char* GXI_pSprite, const unsigned char* GXI_pPalette, const int GXI_locX, const int GXI_locY, const BOOL GXI_transparency, const unsigned int GXI_transparentColor, const BOOL GXI_boundsChecking, const BOOL GXI_spritePortion, const unsigned int GXI_portStartX, const unsigned int GXI_portStartY, const unsigned int GXI_portSizeX, const unsigned int GXI_portSizeY) {
	// T (Transparency, NO Bounds Checking, NO Sprite Portion)
	if (GXI_transparency && !GXI_boundsChecking && !GXI_spritePortion) {
		GX_drawSpriteT(GXI_pSprite, GXI_pPalette, GXI_locX, GXI_locY, GXI_transparentColor);
		return;
	}
	// NNN (NO Transparency, NO Bounds Checking, NO Sprite Portion)
	if (!GXI_transparency && !GXI_boundsChecking && !GXI_spritePortion) {
		GX_drawSpriteNNN(GXI_pSprite, GXI_pPalette, GXI_locX, GXI_locY);
		return;
	}
	// TC (Transparency, Bounds Checking, NO Sprite Portion)
	if (GXI_transparency && GXI_boundsChecking && !GXI_spritePortion) {
		GX_drawSpriteTC(GXI_pSprite, GXI_pPalette, GXI_locX, GXI_locY, GXI_transparentColor);
		return;
	}
	// TCP (Transparency, Bounds Checking, Sprite Portion)
	if (GXI_transparency && GXI_boundsChecking && GXI_spritePortion) {
		GX_drawSpriteTCP(GXI_pSprite, GXI_pPalette, GXI_locX, GXI_locY, GXI_transparentColor, GXI_portStartX, GXI_portStartY, GXI_portSizeX, GXI_portSizeY);
		return;
	}
	// TP (Transparency, NO Bounds Checking, Sprite Portion)
	if (GXI_transparency && !GXI_boundsChecking && GXI_spritePortion) {
		GX_drawSpriteTP(GXI_pSprite, GXI_pPalette, GXI_locX, GXI_locY, GXI_transparentColor, GXI_portStartX, GXI_portStartY, GXI_portSizeX, GXI_portSizeY);
		return;
	}
	// C (NO Transparency, Bounds Checking, NO Sprite Portion)
	if (!GXI_transparency && GXI_boundsChecking && !GXI_spritePortion) {
		GX_drawSpriteC(GXI_pSprite, GXI_pPalette, GXI_locX, GXI_locY);
		return;
	}
	// CP (NO Transparency, Bounds Checking, Sprite Portion)
	if (!GXI_transparency && GXI_boundsChecking && GXI_spritePortion) {
		GX_drawSpriteCP(GXI_pSprite, GXI_pPalette, GXI_locX, GXI_locY, GXI_portStartX, GXI_portStartY, GXI_portSizeX, GXI_portSizeY);
		return;
	}
	// P (NO Transparency, NO Bounds Checking, Sprite Portion)
	if (!GXI_transparency && !GXI_boundsChecking && GXI_spritePortion) {
		GX_drawSpriteP(GXI_pSprite, GXI_pPalette, GXI_locX, GXI_locY, GXI_portStartX, GXI_portStartY, GXI_portSizeX, GXI_portSizeY);
		return;
	}
}


// ************************************************************************************************
// GX_drawPoint
// Draws a single pixel point on the screen.
// Parameters: X coordinate of the pixel to draw (const unsigned int GXI_locX)
//             Y coordinate of th epixel to draw (const unsigned int GXI_locY)
//             Red color component of the point to draw (const unsigned int GXI_colR)
//             Green color component of the point to draw (const unsigned int GXI_colG)
//             Blue color component of the point to draw (const unsigned int GXI_colB)
// ************************************************************************************************
void GX_drawPoint(const unsigned int GXI_locX, const unsigned int GXI_locY, const unsigned int GXI_colR, const unsigned int GXI_colG, const unsigned int GXI_colB) {
	if (GXI_locX < 0 || GXI_locX > 240 || GXI_locY < 0 || GXI_locY > 320) { return; }
  unsigned int  pixCol;
	unsigned short int* pPointAddr;
	// Calculate our color based on the display type and RGB values
	pixCol = (unsigned short int)(((GXI_colR & 0xf8) << 8) | ((GXI_colG & 0xfc) << 3) | (GXI_colB >> 3));
	// Point to the correct memory location for the pixel
	pPointAddr  = GX_pScreenBuffer + (GXI_locX * GX_xPitch) + (GXI_locY * GX_yPitch);
	// Write color value to memory location for our pixel
	*pPointAddr = pixCol;
}


// ************************************************************************************************
// GX_shiftSpriteLeft
// Shifts a sprite to the left.
// Parameters: Pointer to the sprite to rotate (unsigned char* GXI_pSprite)
// ************************************************************************************************
void GX_shiftSpriteLeft(unsigned char* GXI_pSprite) {
	// Get the width and height of our image.  Our image format is simple: it's an RGB .RAW filw
  // with a 4 byte header: the first two bytes are our wifth, the next two are our height.
	const unsigned int sizeX = (*(GXI_pSprite)		 << 8) + *(GXI_pSprite + 1);
	const unsigned int sizeY = (*(GXI_pSprite + 2) << 8) + *(GXI_pSprite + 3);
	unsigned int			 x;
	unsigned int			 y;
	unsigned char*     pPointAddr;
	unsigned char      tempVal;
	GXI_pSprite = GXI_pSprite + 4; // Skip the width and height header
	for (y = 0; y < sizeY; y++) {
		pPointAddr = (GXI_pSprite + (y * sizeX));
		tempVal		 = *pPointAddr;
		for (x = 0; x < sizeX - 1; x++) {
			*(pPointAddr + x) = *(pPointAddr + x + 1);
		}
		*(pPointAddr + sizeX - 1) = tempVal;
	}
}


// ************************************************************************************************
// GX_shiftSpriteRight
// Shifts a sprite to the right.
// Parameters: Pointer to the sprite to rotate (unsigned char* GXI_pSprite)
// ************************************************************************************************
void GX_shiftSpriteRight(unsigned char* GXI_pSprite) {
	const unsigned int sizeX = (*(GXI_pSprite)		 << 8) + *(GXI_pSprite + 1);
	const unsigned int sizeY = (*(GXI_pSprite + 2) << 8) + *(GXI_pSprite + 3);
	unsigned int	  	 x;
  unsigned int			 y;
	unsigned char*     pPointAddr;
	unsigned char      tempVal;
	GXI_pSprite = GXI_pSprite + 4; // Skip the width and height header
	for (y = 0; y < sizeY; y++) {
		pPointAddr = (GXI_pSprite + (y * sizeX));
		tempVal		 = *(pPointAddr + sizeX - 1);
		for (x = sizeX - 1; x > 0; x--) {
			*(pPointAddr + x) = *(pPointAddr + x - 1);
		}
		*(pPointAddr) = tempVal;
	}
}


// ************************************************************************************************
// GX_shiftSpriteUp
// Shifts a sprite up.
// Parameters: Pointer to the sprite to rotate (unsigned char* GXI_pSprite)
// ************************************************************************************************
void GX_shiftSpriteUp(unsigned char* GXI_pSprite) {
	const unsigned int sizeX = (*(GXI_pSprite)		 << 8) + *(GXI_pSprite + 1);
	const unsigned int sizeY = (*(GXI_pSprite + 2) << 8) + *(GXI_pSprite + 3);
	unsigned int			 x;
	unsigned int			 y;
	unsigned char*     pPointAddr;
	unsigned char      tempVal;
	GXI_pSprite = GXI_pSprite + 4; // Skip the width and height header
	for (x = 0; x < sizeX; x++) {
		pPointAddr = (GXI_pSprite + x);
		tempVal		 = *pPointAddr;
		for (y = 0; y < sizeY; y++) {
			*(pPointAddr + (sizeX * y)) = *(pPointAddr + (sizeX * (y + 1)));
		}
		*(pPointAddr + (sizeX * (sizeY - 1))) = tempVal;
	}
}


// ************************************************************************************************
// GX_shiftSpriteDown
// Shifts a sprite down.
// Parameters: Pointer to the sprite to rotate (unsigned char* GXI_pSprite)
// ************************************************************************************************
void GX_shiftSpriteDown(unsigned char* GXI_pSprite) {
	const unsigned int sizeX = (*(GXI_pSprite)		 << 8) + *(GXI_pSprite + 1);
	const unsigned int sizeY = (*(GXI_pSprite + 2) << 8) + *(GXI_pSprite + 3);
	unsigned int			 x;
	unsigned int			 y;
	unsigned char*		 pPointAddr;
	unsigned char			 tempVal;
	GXI_pSprite = GXI_pSprite + 4; // Skip the width and height header
	for (x = 0; x < sizeX; x++) {
		pPointAddr = (GXI_pSprite + x);
		tempVal		 = *(pPointAddr + (sizeX * (sizeY - 1)));
		for (y = sizeY - 1; y > 0; y--) {
			*(pPointAddr + (sizeX * y)) = *(pPointAddr + (sizeX * (y - 1)));
		}
		*pPointAddr = tempVal;
	}
}


// ************************************************************************************************
// GX_getSpriteWidth
// Returns the width of a sprite.
// Parameters: Pointer to the sprite (const unsigned char* GXI_pSprite)
// ************************************************************************************************
unsigned short int GX_getSpriteWidth(const unsigned char* GXI_pSprite) {
	return (unsigned int)(*GXI_pSprite << 8) + *(GXI_pSprite + 1);
}


// ************************************************************************************************
// GX_getSpriteHeight
// Returns the height of a sprite.
// Parameters: Pointer to the sprite (const unsigned char* GXI_pSprite)
// ************************************************************************************************
unsigned short int GX_getSpriteHeight(const unsigned char* GXI_pSprite) {
	return (unsigned int)(*(GXI_pSprite + 2) << 8) + *(GXI_pSprite + 3);
}


// ************************************************************************************************
// GX_showFPS
// Routine to calculate and show the frame rate (FPS) in the upper left-hand corner
// ************************************************************************************************
void GX_showFPS() {
	static DWORD				GX_previousTickCount = GetTickCount();
	static unsigned int GX_countFPS					 = 0;
	static unsigned int GX_lastFPS					 = 0;
	TCHAR szOut[4] = L"";
	swprintf(szOut, TEXT("%d"), GX_lastFPS);
	GX_fillRegion(0, 0, 28, 18, 0, 0, 0);
	GX_drawText(GX_currentFont, szOut, GX_ALIGN_NONE, 1, 1, 255, 255, 255);
	// Calculate frame rate
	DWORD currentTickCount = GetTickCount();
	if ((currentTickCount - GX_previousTickCount) >= 1000) {
		GX_previousTickCount = currentTickCount;
		GX_lastFPS  = GX_countFPS;
		GX_countFPS = 0;
	} else {
		GX_countFPS++;
	}
}


// ************************************************************************************************
// GX_paletteShiftLeft
// Shifts a portion of a palette to the left.
// Parameters: Pointer to the palette (unsigned char* GXI_pPalette)
//             Index into the palette to start the shift at (unsigned char GXI_shiftStart)
//             Index into the palette to stop the shift at (unsigned char GXI_shiftEnd)
// ************************************************************************************************
void GX_paletteShiftLeft(unsigned char* GXI_pPalette, unsigned char GXI_shiftStart, unsigned char GXI_shiftEnd) {
	GXI_pPalette = GXI_pPalette + (GXI_shiftStart << 2);
	for (unsigned char i = 0; i < (GXI_shiftEnd - GXI_shiftStart); i++) {
		*(GXI_pPalette)			= *(GXI_pPalette + 4);
		*(GXI_pPalette + 1) = *(GXI_pPalette + 5);
		*(GXI_pPalette + 2) = *(GXI_pPalette + 6);
		*(GXI_pPalette + 3) = *(GXI_pPalette + 7);
		GXI_pPalette = GXI_pPalette + 4;
	}
}


// ************************************************************************************************
// GX_paletteShiftRight
// Shifts a portion of a palette to the right.
// Parameters: Pointer to the palette (unsigned char* GXI_pPalette)
//             Index into the palette to start the shift at (unsigned char GXI_shiftStart)
//             Index into the palette to stop the shift at (unsigned char GXI_shiftEnd)
// ************************************************************************************************
void GX_paletteShiftRight(unsigned char* GXI_pPalette, unsigned char GXI_shiftStart, unsigned char GXI_shiftEnd) {
	GXI_pPalette = GXI_pPalette + (GXI_shiftEnd << 2) - 4;
	for (unsigned char i = 0; i < (GXI_shiftEnd - GXI_shiftStart); i++) {
		*(GXI_pPalette + 4) = *(GXI_pPalette);
		*(GXI_pPalette + 5) = *(GXI_pPalette + 1);
		*(GXI_pPalette + 6) = *(GXI_pPalette + 2);
		*(GXI_pPalette + 7) = *(GXI_pPalette + 3);
		GXI_pPalette = GXI_pPalette - 4;
	}
}


// ************************************************************************************************
// GX_storePaletteEntry
// Stores a color from the palette in temporary storage.
// Parameters: Pointer to the palette (unsigned char* GXI_pPalette)
//             Index into the palette to store (unsigned short int GXI_colorIndex)
// ************************************************************************************************
void GX_storePaletteEntry(unsigned char* GXI_pPalette, const unsigned int GXI_colorIndex) {
	GXI_pPalette = GXI_pPalette + (GXI_colorIndex << 2);
	GX_savePaletteBytes[0] = *(GXI_pPalette);
	GX_savePaletteBytes[1] = *(GXI_pPalette + 1);
	GX_savePaletteBytes[2] = *(GXI_pPalette + 2);
	GX_savePaletteBytes[3] = *(GXI_pPalette + 3);
}


// ************************************************************************************************
// GX_restorePaletteEntry
// Restores a color in the palette from temporary storage.
// Parameters: Pointer to the palette (unsigned char* GXI_pPalette)
//             Index into the palette to restore (unsigned short int GXI_colorIndex)
// ************************************************************************************************
void GX_restorePaletteEntry(unsigned char* GXI_pPalette, const unsigned int GXI_colorIndex) {
	GXI_pPalette = GXI_pPalette + (GXI_colorIndex << 2);
	*(GXI_pPalette)			= GX_savePaletteBytes[0];
	*(GXI_pPalette + 1) = GX_savePaletteBytes[1];
	*(GXI_pPalette + 2) = GX_savePaletteBytes[2];
	*(GXI_pPalette + 3) = GX_savePaletteBytes[3];
}


// ************************************************************************************************
// GX_drawLine
// Draws a line in the specified color.
// Parameters: X coordinate of first line endpoint (unsigned short int GXI_x1)
//             Y coordinate of first line endpoint (unsigned short int GXI_y1)
//             X coordinate of second line endpoint (unsigned short int GXI_x2)
//             Y coordinate of second line endpoint (unsigned short int GXI_y2)
//             Y coordinate of first line endpoint (unsigned short int GXI_y1)
//             Red color component of the lines (unsigned short int GXI_colR)
//             Green color component of the line (unsigned short int GXI_colG)
//             Blue color component of the line (unsigned short int GXI_colB)
// ************************************************************************************************
void GX_drawLine(unsigned short int GXI_x1, unsigned short int GXI_y1, unsigned short int GXI_x2, unsigned short int GXI_y2, unsigned short int GXI_colR, unsigned short int GXI_colG, unsigned short int GXI_colB) {
  unsigned short int  pixCol;
	unsigned short int* pPointAddr;
	int			            x;
	int			            y;
	int			            dX;
	int			            dY;
	int			            incX;
	int			            incY;
	int			            balance;
	pixCol = (unsigned short int)(((GXI_colR & 0xf8) << 8) | ((GXI_colG & 0xfc) << 3) | (GXI_colB >> 3));
	if (GXI_x2 >= GXI_x1)	{
		dX = GXI_x2 - GXI_x1;
		incX = 1;
	}	else {
		dX = GXI_x1 - GXI_x2;
		incX = -1;
	}
	if (GXI_y2 >= GXI_y1) {
		dY = GXI_y2 - GXI_y1;
		incY = 1;
	}	else {
		dY = GXI_y1 - GXI_y2;
		incY = -1;
	}
	x = GXI_x1;
	y = GXI_y1;
	if (dX >= dY) {
		dY <<= 1;
		balance = dY - dX;
		dX <<= 1;
		while (x != GXI_x2) {
			pPointAddr  = GX_pScreenBuffer + (x * GX_xPitch) + (y * GX_yPitch);
			*pPointAddr = pixCol;
			if (balance >= 0) {
				y += incY;
				balance -= dX;
			}
			balance += dY;
			x += incX;
		} 		
		pPointAddr  = GX_pScreenBuffer + (x * GX_xPitch) + (y * GX_yPitch);
		*pPointAddr = pixCol;
	} else {
		dX <<= 1;
		balance = dX - dY;
		dY <<= 1;
		while (y != GXI_y2) {
			pPointAddr  = GX_pScreenBuffer + (x * GX_xPitch) + (y * GX_yPitch);
			*pPointAddr = pixCol;
			if (balance >= 0) {
				x += incX;
				balance -= dY;
			}
			balance += dX;
			y += incY;
		}
		pPointAddr  = GX_pScreenBuffer + (x * GX_xPitch) + (y * GX_yPitch);
		*pPointAddr = pixCol;
	}
}


// ************************************************************************************************
// GX_drawCircle
// Draws a circle in the specified color.
// Parameters: X coordinate of first line endpoint (unsigned short int GXI_x1)
//             Y coordinate of first line endpoint (unsigned short int GXI_y1)
//             X coordinate of second line endpoint (unsigned short int GXI_x2)
//             Y coordinate of second line endpoint (unsigned short int GXI_y2)
//             Y coordinate of first line endpoint (unsigned short int GXI_y1)
//             Red color component of the lines (unsigned short int GXI_colR)
//             Green color component of the line (unsigned short int GXI_colG)
//             Blue color component of the line (unsigned short int GXI_colB)
// ************************************************************************************************
void GX_drawCircle(int GXI_xPos, int GXI_yPos, int GXI_radius, int GXI_colR, int GXI_colG, int GXI_colB) {
	unsigned short int  pixCol;
	unsigned short int* pPointAddr;
	pixCol = (unsigned short int)(((GXI_colR & 0xf8) << 8) | ((GXI_colG & 0xfc) << 3) | (GXI_colB >> 3));
  int d;
  int y;
  int x;
  x = 0;
  y = GXI_radius; 
  d = 1 - GXI_radius;
	pPointAddr  = GX_pScreenBuffer + ((x + GXI_xPos)  * GX_xPitch) + ((y + GXI_yPos)  * GX_yPitch);
	*pPointAddr = pixCol;
	pPointAddr  = GX_pScreenBuffer + ((y + GXI_xPos)  * GX_xPitch) + ((x + GXI_yPos)  * GX_yPitch);
	*pPointAddr = pixCol;
	pPointAddr  = GX_pScreenBuffer + ((y + GXI_xPos)  * GX_xPitch) + ((-x + GXI_yPos) * GX_yPitch);
	*pPointAddr = pixCol;
	pPointAddr  = GX_pScreenBuffer + ((x + GXI_xPos)  * GX_xPitch) + ((-y + GXI_yPos) * GX_yPitch);
	*pPointAddr = pixCol;
	pPointAddr  = GX_pScreenBuffer + ((-x + GXI_xPos) * GX_xPitch) + ((-y + GXI_yPos) * GX_yPitch);
	*pPointAddr = pixCol;
	pPointAddr  = GX_pScreenBuffer + ((-y + GXI_xPos) * GX_xPitch) + ((-x + GXI_yPos) * GX_yPitch);
	*pPointAddr = pixCol;
	pPointAddr  = GX_pScreenBuffer + ((-y + GXI_xPos) * GX_xPitch) + ((x + GXI_yPos)  * GX_yPitch);
	*pPointAddr = pixCol;
	pPointAddr  = GX_pScreenBuffer + ((-x + GXI_xPos) * GX_xPitch) + ((y + GXI_yPos)  * GX_yPitch);
	*pPointAddr = pixCol;
  while ( y > x ) {
		if ( d < 0 ) {
			d += x * 2 + 3;
			x++;
		} else {
			d += (x - y) * 2 + 5;
			x++;
			y--;
		}
		pPointAddr  = GX_pScreenBuffer + ((x + GXI_xPos)  * GX_xPitch) + ((y + GXI_yPos)  * GX_yPitch);
		*pPointAddr = pixCol;
		pPointAddr  = GX_pScreenBuffer + ((y + GXI_xPos)  * GX_xPitch) + ((x + GXI_yPos)  * GX_yPitch);
		*pPointAddr = pixCol;
		pPointAddr  = GX_pScreenBuffer + ((y + GXI_xPos)  * GX_xPitch) + ((-x + GXI_yPos) * GX_yPitch);
		*pPointAddr = pixCol;
		pPointAddr  = GX_pScreenBuffer + ((x + GXI_xPos)  * GX_xPitch) + ((-y + GXI_yPos) * GX_yPitch);
		*pPointAddr = pixCol;
		pPointAddr  = GX_pScreenBuffer + ((-x + GXI_xPos) * GX_xPitch) + ((-y + GXI_yPos) * GX_yPitch);
		*pPointAddr = pixCol;
		pPointAddr  = GX_pScreenBuffer + ((-y + GXI_xPos) * GX_xPitch) + ((-x + GXI_yPos) * GX_yPitch);
		*pPointAddr = pixCol;
		pPointAddr  = GX_pScreenBuffer + ((-y + GXI_xPos) * GX_xPitch) + ((x + GXI_yPos)  * GX_yPitch);
		*pPointAddr = pixCol;
		pPointAddr  = GX_pScreenBuffer + ((-x + GXI_xPos) * GX_xPitch) + ((y + GXI_yPos)  * GX_yPitch);
		*pPointAddr = pixCol;
  }
}


// ************************************************************************************************
// GX_drawPolygon
// Draws a polygon in the specified color.
// Parameters: Array of points (vertex) in the polygon (GX_Point GXI_points[])
//             The number of points in the polygon (unsigned short in GXI_numPoints)
//             Red color component of the lines (unsigned short int GXI_colR)
//             Green color component of the line (unsigned short int GXI_colG)
//             Blue color component of the line (unsigned short int GXI_colB)
// ************************************************************************************************
void GX_drawPolygon(GX_Point GXI_points[], unsigned short int GXI_numPoints, int GXI_colR, int GXI_colG, int GXI_colB) {
  unsigned short int  pixCol;
	unsigned short int* pPointAddr;
	int			            x;
	int			            y;
	int			            dX;
	int			            dY;
	int			            incX;
	int			            incY;
	int			            balance;
	int									firstPointX = GXI_points[0].x;
	int									firstPointY = GXI_points[1].y;
	int									lastPointX;
	int									lastPointY;
	unsigned short int	x1;
	unsigned short int	y1;
	unsigned short int	x2;
	unsigned short int	y2;
	pixCol = (unsigned short int)(((GXI_colR & 0xf8) << 8) | ((GXI_colG & 0xfc) << 3) | (GXI_colB >> 3));
	// Connect each point in our array to the next in sequence
	for (unsigned short int i = 0; i < (GXI_numPoints - 1) * 2; i = i + 2) {
		x1 = GXI_points[i].x;
		y1 = GXI_points[i + 1].y;
		x2 = GXI_points[i + 2].x;
		y2 = GXI_points[i + 3].y;
		if (x2 >= x1)	{
			dX = x2 - x1;
			incX = 1;
		}	else {
			dX = x1 - x2;
			incX = -1;
		}
		if (y2 >= y1) {
			dY = y2 - y1;
			incY = 1;
		}	else {
			dY = y1 - y2;
			incY = -1;
		}
		x = x1;
		y = y1;
		if (dX >= dY) {
			dY <<= 1;
			balance = dY - dX;
			dX <<= 1;
			while (x != x2) {
				pPointAddr  = GX_pScreenBuffer + (x * GX_xPitch) + (y * GX_yPitch);
				*pPointAddr = pixCol;
				if (balance >= 0) {
					y += incY;
					balance -= dX;
				}
				balance += dY;
				x += incX;
			} 		
			pPointAddr  = GX_pScreenBuffer + (x * GX_xPitch) + (y * GX_yPitch);
			*pPointAddr = pixCol;
		} else {
			dX <<= 1;
			balance = dX - dY;
			dY <<= 1;
			while (y != y2) {
				pPointAddr  = GX_pScreenBuffer + (x * GX_xPitch) + (y * GX_yPitch);
				*pPointAddr = pixCol;
				if (balance >= 0) {
					x += incX;
					balance -= dY;
				}
				balance += dX;
				y += incY;
			}
			pPointAddr  = GX_pScreenBuffer + (x * GX_xPitch) + (y * GX_yPitch);
			*pPointAddr = pixCol;
		}
		lastPointX = GXI_points[i + 2].x;
		lastPointY = GXI_points[i + 3].y;
	}
	// Connect the last and first points together
	x1 = lastPointX;
	y1 = lastPointY;
	x2 = firstPointX;
	y2 = firstPointY;
	if (x2 >= x1)	{
		dX = x2 - x1;
		incX = 1;
	}	else {
		dX = x1 - x2;
		incX = -1;
	}
	if (y2 >= y1) {
		dY = y2 - y1;
		incY = 1;
	}	else {
		dY = y1 - y2;
		incY = -1;
	}
	x = x1;
	y = y1;
	if (dX >= dY) {
		dY <<= 1;
		balance = dY - dX;
		dX <<= 1;
		while (x != x2) {
			pPointAddr  = GX_pScreenBuffer + (x * GX_xPitch) + (y * GX_yPitch);
			*pPointAddr = pixCol;
			if (balance >= 0) {
				y += incY;
				balance -= dX;
			}
			balance += dY;
			x += incX;
		} 		
		pPointAddr  = GX_pScreenBuffer + (x * GX_xPitch) + (y * GX_yPitch);
		*pPointAddr = pixCol;
	} else {
		dX <<= 1;
		balance = dX - dY;
		dY <<= 1;
		while (y != y2) {
			pPointAddr  = GX_pScreenBuffer + (x * GX_xPitch) + (y * GX_yPitch);
			*pPointAddr = pixCol;
			if (balance >= 0) {
				x += incX;
				balance -= dY;
			}
			balance += dX;
			y += incY;
		}
		pPointAddr  = GX_pScreenBuffer + (x * GX_xPitch) + (y * GX_yPitch);
		*pPointAddr = pixCol;
	}
}


// ************************************************************************************************
// GX_PolyLineCalc
// Used by the GX_drawPolygonFilled to calculate the lines to draw the polygon with.
// Parameters: Endpoints of the line to calculate with (int x1, int y2, int x2, int y2)
// ************************************************************************************************
static void GX_PolyLineCalc(int x1, int y1, int x2, int y2) {
	int  tmp;
	int  y;
  long x;
	long m;
	if (y2 != y1) {
		if (y2 < y1) {
			tmp = y1;
			y1  = y2;
			y2  = tmp;
			tmp = x1;
			x1  = x2;
			x2  = tmp;
		}
		x = (long)x1<<8;
		m = ((long)(x2 - x1) << 8) / ((long)(y2 - y1));
		x += m;
		y1++;
		for (y = y1; y <= y2; y++) {
			if ((y >= 0) & (y < 320)) {
				if (GX_FPStartX[y] == -16000) {
					GX_FPStartX[y] = x >> 8;
				} else {
					GX_FPEndX[y] = x >> 8;
				}
			}
			x += m;
		}
	}
}


// ************************************************************************************************
// GX_drawPolygonFilled
// Draws a filled polygon in the specified color.
// Parameters: Array of points (vertex) in the polygon (GX_Point GXI_points[])
//             The number of points in the polygon (unsigned short in GXI_NumVertex)
//             Red color component of the lines (unsigned short int GXI_colR)
//             Green color component of the line (unsigned short int GXI_colG)
//             Blue color component of the line (unsigned short int GXI_colB)
// ************************************************************************************************
void GX_drawPolygonFilled(GX_Point GXI_VertexList[], int GXI_NumVertex, int GXI_colR, int GXI_colG, int GXI_colB) {
	int i;
	GX_Point *curpt;
	GX_Point	*nextpt;
	curpt	 = GXI_VertexList;
	nextpt = GXI_VertexList + 1;
	for (i = 0; i < 320; i++) {
		GX_FPStartX[i] = -16000;
    GX_FPEndX[i]		= -16000;
  }
  for (i = 1; i < GXI_NumVertex; i++) {
	  GX_PolyLineCalc(curpt->x, curpt->y, nextpt->x, nextpt->y);
    curpt += 1;
    nextpt += 1;
  }
  nextpt = GXI_VertexList;
  GX_PolyLineCalc(curpt->x, curpt->y, nextpt->x, nextpt->y);
  for (i = 0; i < 320; i++) {
    if (GX_FPStartX[i] != -16000) {
			if (GX_FPEndX[i] == -16000) {
				GX_FPEndX[i] = GX_FPStartX[i];
			}
			GX_drawLine(GX_FPStartX[i], i, GX_FPEndX[i], i, GXI_colR, GXI_colG, GXI_colB);
		}
	}
}


// ************************************************************************************************
// GX_floodFill
// Fills any region on the screen (does NOTE have to be rectangular!) with the specified color
// Parameters: Point to start filling from (int GXI_x, int GXI_y)
//             Color to fill with (int GXI_colR, GXI_colG, GXI_colB)
// ************************************************************************************************
void GX_floodFill(int GXI_x, int GXI_y, int GXI_colR, int GXI_colG, int GXI_colB) {
	int nv = (unsigned short int)(((GXI_colR & 0xf8) << 8) | ((GXI_colG & 0xfc) << 3) | (GXI_colB >> 3));
	int l;
	int x1;
	int x2;
	int dy;
  int ov;
  ov = *(GX_pScreenBuffer + (GXI_x * GX_xPitch) + (GXI_y * GX_yPitch));
  if (ov == nv || GXI_x < 0 || GXI_x > 240 || GXI_y < 0 || GXI_y > 320) { return; }
  GX_STACK_PUSH(GXI_y, GXI_x, GXI_x, 1);
  GX_STACK_PUSH(GXI_y + 1, GXI_x, GXI_x, -1);
  while (sp > stack) {
		GX_STACK_POP(GXI_y, x1, x2, dy);
		for (GXI_x = x1; GXI_x >= 0 && *(GX_pScreenBuffer + (GXI_x * GX_xPitch) + (GXI_y * GX_yPitch)) == ov; GXI_x--)
			*(GX_pScreenBuffer + (GXI_x * GX_xPitch) + (GXI_y * GX_yPitch)) = nv;
			if (GXI_x >= x1) { goto skip; }
				l = GXI_x + 1;
			if (l < x1)
				GX_STACK_PUSH(GXI_y, l, x1 - 1, -dy);
			GXI_x = x1 + 1;
			do {
				for (; GXI_x <= 240 && *(GX_pScreenBuffer + (GXI_x * GX_xPitch) + (GXI_y * GX_yPitch)) == ov; GXI_x++)
					*(GX_pScreenBuffer + (GXI_x * GX_xPitch) + (GXI_y * GX_yPitch)) = nv;
					GX_STACK_PUSH(GXI_y, l, GXI_x - 1, dy);
					if (GXI_x > x2 + 1) 
						GX_STACK_PUSH(GXI_y, x2 + 1, GXI_x - 1, -dy);
						skip:	for (GXI_x++; GXI_x <= x2 && *(GX_pScreenBuffer + (GXI_x * GX_xPitch) + (GXI_y * GX_yPitch)) != ov; GXI_x++);
						l = GXI_x;
			} while (GXI_x <= x2);
   }
}


// ************************************************************************************************
// GX_mirrorSpriteH
// Flips a sprite horizontally (left-right mirror).
// Parameters: Pointer to the sprite to flip (unsigned char* GXI_pSprite)
// ************************************************************************************************
void GX_mirrorSpriteH(unsigned char* GXI_pSprite) {
	// Get the width and height of our image.  Our image format is simple: it's an RGB .RAW filw
  // with a 4 byte header: the first two bytes are our wifth, the next two are our height.
	const unsigned int sizeX = (*(GXI_pSprite)		 << 8) + *(GXI_pSprite + 1);
	const unsigned int sizeY = (*(GXI_pSprite + 2) << 8) + *(GXI_pSprite + 3);
	unsigned int			 x;
	unsigned int			 y;
	unsigned int			 halfWidth;
	unsigned char*     pPointAddr;
	unsigned char      tempVal;
	unsigned int			 leftHalf;
	unsigned int			 rightHalf;
	unsigned char*		 sprIdxCalcA;
	unsigned char*		 sprIdxCalcB;
	GXI_pSprite = GXI_pSprite + 4; // Skip the width and height header
	// Cut the width of the sprite in half for use in our flip loop
	halfWidth		= sizeX / 2;
	// If the width of the sprite is odd, we make a slight adjustment so it works right
	if (sizeX % 2 != 0) { 
		halfWidth++;
	}
	// Go through each line of the sprite
	for (y = 0; y < sizeY; y++) {
		// Used to flip (duh!)
		leftHalf	= 0;
		rightHalf = sizeX;
		// Calculate the start of the current line
		sprIdxCalcA = GXI_pSprite + (y * sizeX);
		// Go through the current line
		for (x = 0; x < halfWidth; x++) {
			// Grab the first pixel on the left side temporarily
			pPointAddr		 = (sprIdxCalcA + leftHalf);
			tempVal				 = *pPointAddr;
			// Calculate the corresponding pixel on the right side
			sprIdxCalcB		 = sprIdxCalcA + rightHalf;
			// Set the first pixel to it's counterpart from above
			*pPointAddr		 = *(sprIdxCalcB);
			// Set the counterpart to our temp value
			*(sprIdxCalcB) = tempVal;
			// Make sure we move to the next set of pixels
			leftHalf++;
			rightHalf--;
		}
	}
}


// ************************************************************************************************
// GX_mirrorSpriteV
// Flips a sprite vertically (top-bottom mirror).
// Parameters: Pointer to the sprite to flip (unsigned char* GXI_pSprite)
// ************************************************************************************************
void GX_mirrorSpriteV(unsigned char* GXI_pSprite) {
	// Get the width and height of our image.  Our image format is simple: it's an RGB .RAW filw
  // with a 4 byte header: the first two bytes are our wifth, the next two are our height.
	const unsigned int sizeX = (*(GXI_pSprite)		 << 8) + *(GXI_pSprite + 1);
	const unsigned int sizeY = (*(GXI_pSprite + 2) << 8) + *(GXI_pSprite + 3);
	unsigned int			 x;
	unsigned int			 y;
	unsigned int			 a;
	unsigned int			 halfHeight;
	unsigned char      tempVal;
	unsigned char*		 sprIdxCalcA;
	unsigned char*		 sprIdxCalcB;
	GXI_pSprite = GXI_pSprite + 4; // Skip the width and height header
	// Cut the height of the sprite in half for use in our flip loop
	halfHeight	= sizeY / 2;
	// If the height of the sprite is odd, we make a slight adjustment so it works right
	if (sizeY % 2 != 0) { 
		halfHeight++;
	}
	a = sizeY - 1; // This references the mirror line to the current line
	// Go through each pixel across the sprite
	for (y = 0; y < halfHeight; y++) {
		// Calculate the start of the current line
		sprIdxCalcA = GXI_pSprite + (y * sizeX);
		// Calculate the start of the corresponding mirror line
		sprIdxCalcB = GXI_pSprite + (a * sizeX);
		a--; // Next mirror line after this
		for (x = 0; x < sizeX; x++) {
			tempVal						 = *(sprIdxCalcA + x);
			*(sprIdxCalcA + x) = *(sprIdxCalcB + x);
			*(sprIdxCalcB + x) = tempVal;
		}
	}	
}


// ************************************************************************************************
// GX_grayscaleImage
// Converts a palette to grayscale.
// Parameters: Pointer to the palette (unsigned char* GXI_pPalette)
// ************************************************************************************************
void GX_grayscaleImage(unsigned char* GXI_pPalette) {
	int rgb;
	for (unsigned char i = 0; i < 255; i++) {
		rgb = *(GXI_pPalette) + *(GXI_pPalette + 1) + *(GXI_pPalette + 2);
		rgb = rgb / 3;
		*(GXI_pPalette) = rgb;
		*(GXI_pPalette + 1) = rgb;
		*(GXI_pPalette + 2) = rgb;
		GXI_pPalette = GXI_pPalette + 4;
	}
}