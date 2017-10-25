

// ================================================================================================
//
//  OASIS.h
//
//  OASIS Library v1.0 (Omnytex Action Scene Interpretation System)
//  Written by Frank W. Zammetti
//  (C)opyright 2002 by Omnytex Technologies
//  All Rights Reserved
//
//  This is a library for cut scenes.
//
//  Miscellaneous Notes
//  -------------------
//
//  None
// ================================================================================================


// ************************************************************************************************
// Structure Definitions
// ************************************************************************************************

struct OASIS_ACTOR {
	Surface* pImage; // Pointer to the image of this actor
};

struct OASIS_TEXTACTOR {
	int idString; // ID of the string in the String Table resource
};

struct OASIS_PLAYER {
  unsigned char		 actorID;	// ID matching the ID in the OASIS_Actors array of this player
	bool             hidden;  // True if the player is not on the screen, false otherwise
	signed short int locX;    // X coordinate currently occupied by this player 
	signed short int locY;	  // Y coordinate currently occupied by this player 
};

struct OASIS_AUDIOACTOR {
	SoundFX	SFX; // The Sound FX itself
	int	channel; // Channel the audio actor is currently (or was) playing on as returned by itPlaySFX
};


// ************************************************************************************************
// Globals
// ************************************************************************************************

OASIS_ACTOR			 OASIS_Actors[258];													// Array of actors available for use in the scene
OASIS_AUDIOACTOR OASIS_AudioActors[258];										// Array of audio actors available for use in the scene
OASIS_TEXTACTOR  OASIS_TextActors[258];											// Array of text actors available for use in the scene
OASIS_PLAYER		 OASIS_Players[258];												// Array of players currently used in the scene
unsigned char*	 OASIS_ScriptPointer			 = NULL;					// Pointer to the current position in the script
unsigned char		 OASIS_NumberOfPlayers		 = 0;							// Number of players currently involved in scene
unsigned char		 OASIS_NumberOfAudioActors = 0;							// Total number of audio actors loaded for this scene
TCHAR						 OASIS_ScriptText[]				 = _T("SCRIPTS");


// ************************************************************************************************
// OASIS_loadScriptResource
// Used internally by OASIS to load a SCRIPT resource
// Parameters: The resource ID to load (int OASIS_ScriptResourceID)
//             Handle to the module the resource belongs to (HMODULE OASIS_Module)
// Returns:    A pointer to the loaded resource (LPVOID)
// ************************************************************************************************
LPVOID OASIS_loadScriptResource(int OASIS_ScriptResourceID, HMODULE OASIS_Module) {
  HGLOBAL hResD		 = NULL;
  void    *pvRes	 = NULL;
	HRSRC   hResInfo = NULL;
  // Find the resource and load into memory
	hResInfo = FindResource(OASIS_Module, MAKEINTRESOURCE(OASIS_ScriptResourceID), OASIS_ScriptText);
  hResD = LoadResource(OASIS_Module, hResInfo);
	pvRes = LockResource(hResD);
	return pvRes;
}


// ************************************************************************************************
// OASIS_StartScene
// Called once at the beginning of a new scene
// Parameters: 
// Returns:    
// ************************************************************************************************
void OASIS_StartScene(unsigned char* in_Script, Surface* in_ActorImages[], SoundFX in_AudioActors[], int in_TextActors[]) {
	// Point to the start of the script for this scene
	OASIS_ScriptPointer				= in_Script;
	OASIS_NumberOfPlayers			= 0;
	OASIS_NumberOfAudioActors = 0;
	int i;
	// Load the Actors array with the data from the array passed in
	i = 0;
	while (in_ActorImages[i] != NULL) {
		OASIS_Actors[i].pImage = in_ActorImages[i];
		i++;
	}
	// Load the Audio Actors array with the data from the array passed in
	i = 0;
	while (in_AudioActors[i].getVolume() != 0) {
		OASIS_AudioActors[i].SFX		 = in_AudioActors[i];
		OASIS_AudioActors[i].channel = NULL;
		i++;
		OASIS_NumberOfAudioActors++;
	}
	// Load the Text Actors array with the data from the array passed in
	i = 0;
	while (in_TextActors[i] != -1) {
		OASIS_TextActors[i].idString = in_TextActors[i];
		i++;
	}
}


// ************************************************************************************************
// OASIS_EndScene
// Called once at the end of a scene.
// default volumes and starts playing the silent loop.  This is needed otherwise subsequent
// scenes won't have sound working properly.
// Parameters: 
// Returns:    
// ************************************************************************************************
void OASIS_EndScene() {
	game.itSilenceAllSFX();
}

// ************************************************************************************************
// OASIS_DoScene
// Called for each frame of animation for a scene
// Parameters: 
// Returns:    
// ************************************************************************************************
unsigned short int OASIS_DoScene(DisplayDevice* in_Display) { 

	if (!ProcessEvents) { ProcessEvents = true; }

	// If the pointer currently points to the end of the script, exit now indicating this condition
	if (*OASIS_ScriptPointer == 0x40) { // ("@")
		return 1; 
	}

	// Not at the end of the script, so we must be about to process a frame
	while (*OASIS_ScriptPointer != 0x21) { // Process until end of frame indicator is found ("!")
		unsigned char nextCmd = *OASIS_ScriptPointer;
		OASIS_ScriptPointer++;
		switch (nextCmd) {

			// Add Player To Scene
			case 0x41: { // A
				// Get the ID of the actor
				unsigned char actorID = *OASIS_ScriptPointer++;
				// Add the actor to the array of players
				OASIS_Players[OASIS_NumberOfPlayers].actorID = actorID;
				OASIS_Players[OASIS_NumberOfPlayers].hidden  = true;
				OASIS_Players[OASIS_NumberOfPlayers].locX		 = 9999;
				OASIS_Players[OASIS_NumberOfPlayers].locY		 = 9999;
				// Increase our player count
				OASIS_NumberOfPlayers++;
			break; }

			// Change Actor ID Of Player
			case 0x49: { // I
				// Get the ID of the Player
				unsigned char playerID = *OASIS_ScriptPointer++;
				// Get the ID of the Actor to replace this Player with
				unsigned char actorID  = *OASIS_ScriptPointer++;
				// Update the ID of the player
				OASIS_Players[playerID].actorID = actorID;
			break; }

			// Hide All Players
			case 0x45: { // E
				// Set hidden to true for all players
				for (int i = 0; i < OASIS_NumberOfPlayers; i++) {
					OASIS_Players[i].hidden	 = true;
				}				
			break; }

			// Hide Player
			case 0x48: { // H
				// Get the ID of the Player
				unsigned char playerID = *OASIS_ScriptPointer++;
				// Toggle it's hidden state
				OASIS_Players[playerID].hidden = true;
			break; }

			// Unhide Player
			case 0x55: { // U
				// Get the ID of the Player
				unsigned char playerID = *OASIS_ScriptPointer++;
				// Toggle it's hidden state
				OASIS_Players[playerID].hidden = false;
			break; }

			// Put Player To Screen Location
			case 0x50: { // P
				// Get the ID of the player
				unsigned char playerID = *OASIS_ScriptPointer++;
				// Get the X coordinate to put the player at (2 bytes)
				unsigned short int negativeXIndicator = *OASIS_ScriptPointer++;
				unsigned short int locX = (unsigned short int)((*OASIS_ScriptPointer << 8) + *(OASIS_ScriptPointer + 1));
				OASIS_ScriptPointer = OASIS_ScriptPointer + 2;
				// Get the Y coordinate to put the player at (2 bytes)
				unsigned short int negativeYIndicator = *OASIS_ScriptPointer++;
				unsigned short int locY = (unsigned short int)((*OASIS_ScriptPointer << 8) + *(OASIS_ScriptPointer + 1));
				OASIS_ScriptPointer = OASIS_ScriptPointer + 2;
				// Update the player's coordinates
				if (negativeXIndicator == 1) {
					OASIS_Players[playerID].locX = (short)(locX * -1);
				} else {
					OASIS_Players[playerID].locX = locX;
				}
				if (negativeYIndicator == 1) {
					OASIS_Players[playerID].locY = (short)(locY * -1);
				} else {
					OASIS_Players[playerID].locY = locY;
				}
			break; }

			// Move Player On Screen
			case 0x4d: { // M
				// Get the ID of the player
				unsigned char playerID = *OASIS_ScriptPointer++;
				// Get the number of pixels to move (2 bytes)
				unsigned short int numPixels = (unsigned short int)((*OASIS_ScriptPointer << 8) + *(OASIS_ScriptPointer + 1));
				OASIS_ScriptPointer = OASIS_ScriptPointer + 2;
				// Get the direction to move
				unsigned char dirMove = *OASIS_ScriptPointer++;
				// Update the player's coordinates
				switch (dirMove) {
					case 0x55: { // Up
						OASIS_Players[playerID].locY = (short)(OASIS_Players[playerID].locY - numPixels);
					break; }
					case 0x44: { // Down
						OASIS_Players[playerID].locY = (short)(OASIS_Players[playerID].locY + numPixels);
					break; }
					case 0x4c: { // Left
						OASIS_Players[playerID].locX = (short)(OASIS_Players[playerID].locX - numPixels);
					break; }
					case 0x52: { // Right
						OASIS_Players[playerID].locX = (short)(OASIS_Players[playerID].locX + numPixels);
					break; }
				}
			break; }

			// Play Sound FX
			case 0x58: { // X
				// Get the ID of the Audio Actor
				unsigned char audioactorID = *OASIS_ScriptPointer++;
				// Get the loop flag
				unsigned char loopFlag = *OASIS_ScriptPointer++;
				// Play the Sound FX
				bool lf = false;
				if (loopFlag == 1) { lf = true; }
				OASIS_AudioActors[audioactorID].channel = game.itPlaySFX(&OASIS_AudioActors[audioactorID].SFX, lf);
			break; }

			// Stop Sound FX
			case 0x53: { // S
				// Get the ID of the Audio Actor
				unsigned char audioactorID = *OASIS_ScriptPointer++;
				// Stop the sound FX
				game.itStopSFX(OASIS_AudioActors[audioactorID].channel);
				OASIS_AudioActors[audioactorID].channel = NULL;
			break; }

			// Change Sound FX Volume
			case 0x46: { // F
				// Get the ID of the Audio Actor
				unsigned char audioactorID = *OASIS_ScriptPointer++;
				// Get the volume
				unsigned char volume = *OASIS_ScriptPointer++;
				// Change volume of the specified audio actor
				game.itSetVolume(OASIS_AudioActors[audioactorID].channel, volume);
			break; }

			// Silence All Sound FX
			case 0x4c: { // S
				// Stop the sound FX
				game.itSilenceAllSFX();
				for (int i = 0; i < OASIS_NumberOfAudioActors; i++) {
					OASIS_AudioActors[i].channel = NULL;
				}
			break; }

			// Restore Default Volume
			case 0x52: { // R
				// Set the default volume of all audio actors
				for (int i = 0; i < OASIS_NumberOfAudioActors; i++) {
					OASIS_AudioActors[i].SFX.setVolume(64);
				}
			break; }

			// Clear screen
			case 0x43: { // C
				// Get the red color component
				unsigned char colR	= *OASIS_ScriptPointer++;
				// Get the green color component
				unsigned char colG = *OASIS_ScriptPointer++;
				// Get the blue color component
				unsigned char colB = *OASIS_ScriptPointer++;
				// Do the clear right now
				in_Display->Clear(Color(colR, colG, colB));
			break; }

			// Show Text
			case 0x54: { // T
				// Get the ID of the Text Actor
				unsigned char textActorID = *OASIS_ScriptPointer++;
				// Get the Red color component
				unsigned char colR = *OASIS_ScriptPointer++;
				// Get the Green color component
				unsigned char colG = *OASIS_ScriptPointer++;
				// Get the Blue color component
				unsigned char colB = *OASIS_ScriptPointer++;
				// Get the Bounds Top (2 bytes)
				unsigned short int locX = (unsigned short int)((*OASIS_ScriptPointer << 8) + *(OASIS_ScriptPointer + 1));
				OASIS_ScriptPointer = OASIS_ScriptPointer + 2;
				// Get the Bounds Left (2 bytes)
				unsigned short int locY = (unsigned short int)((*OASIS_ScriptPointer << 8) + *(OASIS_ScriptPointer + 1));
				OASIS_ScriptPointer = OASIS_ScriptPointer + 2;
				// Get the Align Setting
				unsigned char alignSetting = *OASIS_ScriptPointer++;
				int alignCode = 0;
				if (alignSetting == 0x63) { alignCode = PFE_ALIGN_CENTER; } // c
				if (alignSetting == 0x6c) { alignCode = PFE_ALIGN_LEFT; } // l
				if (alignSetting == 0x72) { alignCode = PFE_ALIGN_RIGHT; } // r
				TCHAR szText[32] = L"";
				LoadString(hInst, OASIS_TextActors[textActorID].idString, szText, 32);
				PFE_drawText(in_Display, pFont, szText, alignCode, locX, locY, colR, colG, colB);
			break; }

		}
	}
	// Scene just ended, point to the next byte (either the next frame or the end of the script)
	OASIS_ScriptPointer++;
	// Oh, and uh... DRAW THE PLAYERS!!
	for (int i = 0; i < OASIS_NumberOfPlayers; i++) {
		if (!OASIS_Players[i].hidden) {
			in_Display->Blit(OASIS_Players[i].locX, OASIS_Players[i].locY, OASIS_Actors[OASIS_Players[i].actorID].pImage);
		}
	}
	// Exit normally
	return 0;
}