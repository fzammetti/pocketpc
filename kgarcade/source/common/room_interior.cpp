
#include "main.h"


namespace ns_RoomInterior {


// ****************************************************************************************************************
// Globals
// ****************************************************************************************************************
CGapiSurface* floor_tiles[2];


} // End of namespace


// ****************************************************************************************************************
// ProcessNextFrame handler
// ****************************************************************************************************************
void CGame::pnfRoomInterior(CGapiSurface* backbuffer, DWORD dwFlags) {

	using namespace ns_RoomInterior;

	// Clear the screen
	backbuffer->FillRect(NULL, RGB(0, 0, 0), 0, NULL);

	// Draw box around status area
	backbuffer->DrawRect(CRect(0, 280, 240, 320), RGB(255, 0, 0), NULL, NULL);

	// Draw the floors
	int tile_number = 0;
	for (int x = 0; x < 24; x++) {
		backbuffer->BltFast(x * 10, 50,  floor_tiles[tile_number], NULL, GDBLTFAST_KEYSRC, NULL);
		backbuffer->BltFast(x * 10, 120, floor_tiles[tile_number], NULL, GDBLTFAST_KEYSRC, NULL);
		backbuffer->BltFast(x * 10, 190, floor_tiles[tile_number], NULL, GDBLTFAST_KEYSRC, NULL);
		backbuffer->BltFast(x * 10, 260, floor_tiles[tile_number], NULL, GDBLTFAST_KEYSRC, NULL);
		tile_number++;
		if (tile_number > 1) { tile_number = 0; }
	}

}


// ****************************************************************************************************************
// StylusDown handler
// ****************************************************************************************************************
void CGame::sdRoomInterior(POINT p) {

	using namespace ns_RoomInterior;

}


// ****************************************************************************************************************
// StylusUp handler
// ****************************************************************************************************************
void CGame::suRoomInterior(POINT p) {

	using namespace ns_RoomInterior;

	Shutdown();

}


// ****************************************************************************************************************
// StylusMove handler
// ****************************************************************************************************************
void CGame::smRoomInterior(POINT p) {

	using namespace ns_RoomInterior;

}


// ****************************************************************************************************************
// KeyDown handler
// ****************************************************************************************************************
void CGame::kdRoomInterior(DWORD dwKey, GDKEYLIST& keylist) {

	using namespace ns_RoomInterior;

}


// ****************************************************************************************************************
// KeyUp handler
// ****************************************************************************************************************
void CGame::kuRoomInterior(DWORD dwKey, GDKEYLIST& keylist) {

	using namespace ns_RoomInterior;

}


// ****************************************************************************************************************
// Loader
// ****************************************************************************************************************
void CGame::loadRoomInterior(CGapiSurface* backbuffer, DWORD dwFlags) {

	using namespace ns_RoomInterior;

	// Move on to the next step
	loading_step++;

	// Do the appropriate step
	switch(loading_step) {

		case 1: {
			floor_tiles[0] = new CGapiSurface();
			HRESULT hr;
			hr = floor_tiles[0]->CreateSurface (0, m_config.hInstance, GFX_ROOM_INTERIOR_FLOOR_TILE_1, TEXT("GRAPHICS"));
			floor_tiles[0]->SetColorKey(RGB(255, 128, 255));
			floor_tiles[1] = new CGapiSurface();
			floor_tiles[1]->CreateSurface (0, m_config.hInstance, GFX_ROOM_INTERIOR_FLOOR_TILE_2, TEXT("GRAPHICS"));
			floor_tiles[1]->SetColorKey(RGB(255, 128, 255));
		break; }

		// End of loading
		default: {
			loading	= false;
		break; }

	}

	// Show the Loading screen
	showLoadingScreen(backbuffer, dwFlags);

}


// ****************************************************************************************************************
// Destroyer
// ****************************************************************************************************************
void CGame::destroyRoomInterior(CGapiSurface* backbuffer, DWORD dwFlags) {

	using namespace ns_RoomInterior;

	// Move on to the next step
	destroying_step++;

	// Do the appropriate step
	switch(destroying_step) {

		case 1: {
			delete floor_tiles[0];
			delete floor_tiles[1];
		break; }

		default: {
			// All done destroying, start loading the next screen
			current_screen = screen_after_destroy;
			doLoad();
		break; }

	}

	// Show the Loading screen
	showLoadingScreen(backbuffer, dwFlags);

}


// ****************************************************************************************************************
// Utility functions
// ****************************************************************************************************************
namespace ns_RoomInterior {

} // End of namespace