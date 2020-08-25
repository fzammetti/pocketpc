

// ================================================================================================
//
//  SXLib.h
//
//  Sound-X Library v1.0
//  Writte by Frank W. Zammetti
//  (C)opyright 2002 by Omnytex Technologies
//  All Rights Reserved
//
//  This is a library of sound functions that allows mixing of WAV files (specifically, music
//  and sound FX).  It allows you to play background music and then play sound FX over it with
//  full control of volume and panning.
//
//  Miscellaneous Notes
//  -------------------
//
//  Music WAV files MUST be stero.  Sound FX WAV files MUST be Mono.  Both must be 16-bit and
//  must be the same sample rate (any rate should be fine).
//
//  SX_Initialize MUST be called before any other SXLib functions and SX_Exit must be called
//  before exiting the application for proper cleanup.
//
//  All variables used in SXLib are prefixed with SX_.  Any parameters passed into functions are
//  prefixed with SXI_.  Any variables returned from a function is prefixed with SXO_.
// ================================================================================================


// ************************************************************************************************
// Structure Definitions
// ************************************************************************************************
typedef struct tagSX_WAVEFILE {
  DWORD           WaveSize;   // Size of file
  LPWAVEFORMATEX  WaveHeader; // Wave Header
  LPBYTE          SampleData; // Wave Bits
}
SX_WAVEFILE, *LWaveFile;

typedef struct tagSX_SOUND {
  bool		Loaded;
  int			Volume;				 // Volume setting
  int			Panning;			 // Panning from 0 (full left) to 255 (full right), default is 127
  DWORD		Samples;			 // Total number of samples in this effect
  DWORD		CurrentSample; // Index to current sample
  LPVOID	WaveFile;			 // Pointer to the loaded wave resource's allocated data
  short*	pData;				 // 16 bit samples
}
SX_SOUND, *PSOUND;


// ************************************************************************************************
// Defines
// ************************************************************************************************
#define SX_TOTAL_AUDIO_BUFFERS		4	 // Number of audio buffers used by waveOutWrite
#define SX_TOTAL_EFFECTS					16 // Number of different FX
#define SX_TOTAL_MUSICS					  16 // Number of different musics
#define SX_TIMERS_PER_BUFFER_TIME 2	
#define SX_SAMPLE_SCALE_FACTOR		2	 // What all samples get divided by when mixing


// ************************************************************************************************
// Globals
// ************************************************************************************************
HWAVEOUT			SX_WaveOut;
WAVEHDR				SX_WaveHeader[SX_TOTAL_AUDIO_BUFFERS];
void* 				SX_WaveBuffer[SX_TOTAL_AUDIO_BUFFERS];		
int						SX_BuffersSent;	
int						SX_NextBuffer;	
int						SX_TimerValueMS;
ULONG					SX_BufferSamples;													 // SX_WaveBuffer size in samples
int						SX_PlayingFX[SX_TOTAL_EFFECTS];						 // Array of FX currently playing
SX_SOUND			SX_EffectsArray[SX_TOTAL_EFFECTS];				 // Array of effect sounds	
SX_SOUND			SX_MusicsArray[SX_TOTAL_MUSICS];					 // Array of musics
int						SX_TotalFXLoaded;													 // How many FX loaded?
int						SX_TotalMusicsLoaded;											 // How many musics loaded?
int						SX_CurrentMusicsIndex;										 // Index into musics array
int						SX_NextMusicsIndex;												 // Index into musics array
DWORD					SX_CurrentMusicSampleIndex;								 // Index to current sample
unsigned char	SX_MusicVolume;
unsigned char SX_FXVolume;
UINT					SX_TimerID												=  NULL;
TCHAR					SX_WaveText[]											= _T("WAVE");
TCHAR         SX_LastError[100]                 = L"";


// ************************************************************************************************
// Prototypes
// ************************************************************************************************
static void		CALLBACK SX_SXCallBack	 (HWAVEOUT, UINT, DWORD, DWORD, DWORD);
static void		CALLBACK SX_PlayTimerProc(HWND, UINT, UINT, DWORD);


// ************************************************************************************************
// SX_loadWaveResource
// Used internally by SXLib to load a WAVE resource and parse the WAVE data
// Parameters: The resource ID to load (int SXI_WaveResourceID)
//             Handle to the module the resource belongs to (HMODULE SXI_Module)
//             Wave file descriptor strutcture (LWaveFile SXI_WaveFile)
// Returns:    A pointer to the loaded resource (LPVOID)
// ************************************************************************************************
LPVOID SX_loadWaveResource(int SXI_WaveResourceID, HMODULE SXI_Module, LWaveFile SXI_WaveFile) {
  HGLOBAL hResD;
  void    *pvRes;
  DWORD   dwSize;
	LPVOID  lpMemory;
	HRSRC   hResInfo;
  // Find the resource and load into memory
	hResInfo = FindResource(SXI_Module, MAKEINTRESOURCE(SXI_WaveResourceID), SX_WaveText);
  if ((hResInfo != NULL) && ((hResD = LoadResource(SXI_Module, hResInfo)) != NULL) && ((pvRes = LockResource(hResD)) != NULL)) {
		// If we found it, copy the bits from the resource into our own chunk of memory
    dwSize = SizeofResource(SXI_Module, hResInfo);
    lpMemory = malloc(dwSize);
    memcpy (lpMemory, pvRes, dwSize);
		LPDWORD pdw;
		LPDWORD pdwEnd;
		DWORD   dwRiff;
		DWORD   dwType;
		DWORD   dwLength;
		// Set defaults to NULL or zero
		if (&(SXI_WaveFile->WaveHeader)) { *(&(SXI_WaveFile->WaveHeader))	= NULL;	}
		if (&(SXI_WaveFile->SampleData)) { *(&(SXI_WaveFile->SampleData)) = NULL;	}
		if (&(SXI_WaveFile->WaveSize))   { *(&(SXI_WaveFile->WaveSize))		= 0;		}
		// Set up DWORD pointers to the start of the chunk of memory.
		pdw = (DWORD *)lpMemory;
		// Get the type and length of the chunk of memory
		dwRiff	 = *pdw++;
		dwLength = *pdw++;
		dwType	 = *pdw++;
		// Find the pointer to the end of the chunk of memory
		pdwEnd = (DWORD *)((BYTE *)pdw + dwLength-4);
		// Run through the bytes looking for the tags
		while (pdw < pdwEnd) {
			dwType   = *pdw++;
			dwLength = *pdw++;
			switch (dwType) {
				// Found the format  part
				case mmioFOURCC('f', 'm', 't', ' '):
					if (&(SXI_WaveFile->WaveHeader) && !*(&(SXI_WaveFile->WaveHeader))) {
						// Set the lplpWaveHeader to point to this part of the memory chunk
						*(&(SXI_WaveFile->WaveHeader)) = (LPWAVEFORMATEX)pdw;
						// Check to see if the other two items have been filled out yet (the bits and the size of the
						// bits). If so, then this chunk of memory has been parsed out and we can exit
						if ((!&(SXI_WaveFile->SampleData) || *(&(SXI_WaveFile->SampleData))) && (!&(SXI_WaveFile->WaveSize) || *(&(SXI_WaveFile->WaveSize)))) {
							return lpMemory;
						}
					}
				break;
				// Found the samples
				case mmioFOURCC('d', 'a', 't', 'a'):
					if ((&(SXI_WaveFile->SampleData) && !*(&(SXI_WaveFile->SampleData))) || (&(SXI_WaveFile->WaveSize) && !*(&(SXI_WaveFile->WaveSize)))) {
						// Point the samples pointer to this part of the chunk of memory.
						if (&(SXI_WaveFile->SampleData)) { *(&(SXI_WaveFile->SampleData)) = (LPBYTE)pdw; }
						// Set the size of the wave
						if (&(SXI_WaveFile->WaveSize)) { *(&(SXI_WaveFile->WaveSize)) = dwLength; }
						// Make sure we have our header pointer set up.  If we do, we can exit
						if (!&(SXI_WaveFile->WaveHeader) || *(&(SXI_WaveFile->WaveHeader))) {
							return lpMemory;
						}
					}
				break;
			}
			// Move the pointer through the chunk of memory
			pdw = (DWORD *)((BYTE *)pdw + ((dwLength+1)&~1));
		}
  }
  return NULL; // A problem!
}


// ************************************************************************************************
// SX_Initialize
// Initializes the SXLib library.  Must be called before any other FX function!
// Parameters: The frequency of all waves to be played (int SXI_Frequency)
//             Size of the playback buffer in milliseconds (int SXI_BufferMS)
// Returns:    Indication of success or failure, true is good, false is bad (bool)
// ************************************************************************************************
bool SX_Initialize(int SXI_Frequency, int SXI_BufferMS) {
	WAVEFORMATEX waveFormat;
	WORD				 Samplesize;
	MMRESULT		 mmResult;
	int					 iBuffer;
	Samplesize = 1;
	Samplesize <<= 1;
	Samplesize <<= 1;
	waveFormat.wFormatTag			 = WAVE_FORMAT_PCM;
	waveFormat.nChannels			 = 2;
	waveFormat.nSamplesPerSec  = SXI_Frequency;
	waveFormat.nAvgBytesPerSec = SXI_Frequency * Samplesize;
	waveFormat.nBlockAlign		 = Samplesize;
	waveFormat.wBitsPerSample  = 16;
	waveFormat.cbSize					 = sizeof(waveFormat);
	mmResult = waveOutOpen(&SX_WaveOut, WAVE_MAPPER, &waveFormat, (DWORD)SX_SXCallBack, 0, CALLBACK_FUNCTION);
	if (mmResult != MMSYSERR_NOERROR) {
		swprintf(SX_LastError, L"%d", mmResult);
		wcscat(SX_LastError, L":\nUnable to initialize SXLib:\n");
		if (mmResult == MMSYSERR_NOERROR)     { wcscat(SX_LastError, L"MMSYSERR_NOERROR");     } // 0
		else if (mmResult == MMSYSERR_INVALHANDLE) { wcscat(SX_LastError, L"MMSYSERR_INVALHANDLE"); } // 5
		else if (mmResult == MMSYSERR_BADDEVICEID) { wcscat(SX_LastError, L"MMSYSERR_BADDEVICEID"); } // 2
		else if (mmResult == MMSYSERR_NODRIVER)		{ wcscat(SX_LastError, L"MMSYSERR_NODRIVER");    } // 6
		else if (mmResult == MMSYSERR_NOMEM)				{ wcscat(SX_LastError, L"MMSYSERR_NOMEM");       } // 7
		else if (mmResult == WAVERR_BADFORMAT)			{ wcscat(SX_LastError, L"WAVERR_BADFORMAT");     } // 32
		else if (mmResult == WAVERR_SYNC)					{ wcscat(SX_LastError, L"WAVERR_SYNC");          } // 35
		else { wcscat(SX_LastError, L"UNKNOWN ERROR"); }
		return false;
	}
	SX_BufferSamples = SXI_Frequency * SXI_BufferMS / (1000 * SX_TOTAL_AUDIO_BUFFERS);
	for (iBuffer = 0; iBuffer < SX_TOTAL_AUDIO_BUFFERS; iBuffer++) {
		SX_WaveBuffer[iBuffer] = malloc(SX_BufferSamples * Samplesize);
		if (SX_WaveBuffer[iBuffer] == 0) {
			wcscpy(SX_LastError, L"100:\nUnable to initialize SXLib:\nCould not allocate buffers");
			return false;
		}
		SX_WaveHeader[iBuffer].lpData = (char*)SX_WaveBuffer[iBuffer];
		SX_WaveHeader[iBuffer].dwBufferLength = SX_BufferSamples * Samplesize;
		mmResult = waveOutPrepareHeader(SX_WaveOut,&SX_WaveHeader[iBuffer],sizeof(WAVEHDR));
		if (!SX_WaveBuffer[iBuffer]||mmResult!=MMSYSERR_NOERROR) {
			wcscpy(SX_LastError, L"200:\nUnable to initialize SXLib:\nCould not perpare headers");
			return false;
		}
	}
	SX_TimerValueMS = (SXI_BufferMS / SX_TOTAL_AUDIO_BUFFERS) / SX_TIMERS_PER_BUFFER_TIME;
	SX_BuffersSent = SX_NextBuffer = 0;
	SX_CurrentMusicSampleIndex		 = 0;
	SX_TotalFXLoaded							 = 0;
	SX_TotalMusicsLoaded					 = 0;
	SX_MusicVolume								 = 255;
	SX_FXVolume										 = 255;
	return true;
}


// ************************************************************************************************
// SX_loadMusic
// Loads a music resource for later playback.
// Parameters: ID of the resource to load (int SXI_ResourceID)
//             Handle to the application the resource belongs to (HINSTANCE SXI_hInst)
// Returns:    A unique ID value representing the loaded resurce (INT)
// ************************************************************************************************
int SX_loadMusic(int SXI_ResourceID, HINSTANCE SXI_hInst) {
	SX_WAVEFILE wavefile;
	SX_MusicsArray[SX_TotalMusicsLoaded].WaveFile = SX_loadWaveResource(SXI_ResourceID, SXI_hInst, &wavefile);
	if (SX_MusicsArray[SX_TotalMusicsLoaded].WaveFile != NULL) {
		SX_MusicsArray[SX_TotalMusicsLoaded].pData = (short *)wavefile.SampleData;
		SX_MusicsArray[SX_TotalMusicsLoaded].Loaded = true;
		SX_MusicsArray[SX_TotalMusicsLoaded].Samples = wavefile.WaveSize / 4;
		SX_TotalMusicsLoaded++;
		return SX_TotalMusicsLoaded;
	}	else {
		return NULL;
	}
}


// ************************************************************************************************
// SX_loadFX
// Loads a sound FX resource for later playback.
// Parameters: ID of the resource to load (int SXI_ResourceID)
//             Handle to the application the resource belongs to (hginstance SXI_hInst)
// Returns:    A unique ID value representing the loaded resurce (int)
// ************************************************************************************************
int SX_loadFX(int SXI_ResourceID, HINSTANCE SXI_hInst) {
	SX_WAVEFILE wavefile;
	SX_EffectsArray[SX_TotalFXLoaded].WaveFile = SX_loadWaveResource(SXI_ResourceID, SXI_hInst, &wavefile);
	if (SX_EffectsArray[SX_TotalFXLoaded].WaveFile != NULL) {
		SX_EffectsArray[SX_TotalFXLoaded].pData = (short *)wavefile.SampleData;
		SX_EffectsArray[SX_TotalFXLoaded].Loaded = true;
		SX_EffectsArray[SX_TotalFXLoaded].Samples = wavefile.WaveSize / 2;
		SX_TotalFXLoaded++;
		return SX_TotalFXLoaded;
	}	else {
		return NULL;
	}
}


// ************************************************************************************************
// SX_setMusicVolume
// Sets the volume for music playback
// Parameters: Volume level from 0-255 (unsigned char SXI_MusicVolume)
// ************************************************************************************************
void SX_setMusicVolume(unsigned char SXI_MusicVolume) {
	SX_MusicVolume = SXI_MusicVolume;
}


// ************************************************************************************************
// SX_setFXVolume
// Sets the volume for sound FX playback
// Parameters: Volume level from 0-255 (unsigned char SXI_FXVolume)
// ************************************************************************************************
void SX_setFXVolume(unsigned char SXI_FXVolume) {
	SX_FXVolume = SXI_FXVolume;
}


// ************************************************************************************************
// SX_setCurrentMusic
// Sets the music that should be currently playing
// Parameters: ID of the music as returned by SX_loadMusic (int SXI_MusicID)
// ************************************************************************************************
void SX_setCurrentMusic(int SXI_MusicID) {
	SX_NextMusicsIndex				 = SXI_MusicID - 1;
	SX_CurrentMusicSampleIndex = 0;
	SX_CurrentMusicsIndex			 = SX_NextMusicsIndex;
}


// ************************************************************************************************
// SX_playStart
// Begins playback of the music as currently set by a previous call to SX_setCurrentMusic
// ************************************************************************************************
void SX_playStart() {
	if (SX_TimerID) { KillTimer(NULL, SX_TimerID); }
	SX_TimerID = SetTimer(NULL, NULL, SX_TimerValueMS, &SX_PlayTimerProc);
}


// ************************************************************************************************
// SX_playStop
// Ceases playback of the currently playing music as well as any FX that might be playing
// ************************************************************************************************
void SX_playStop() {
	waveOutReset(SX_WaveOut);					 // Stop any currently playing sounds
	KillTimer(NULL, SX_TimerID);			 // Kill our playback timer
	SX_TimerID								 = NULL; // Make sure we have no timer ID going forward
	SX_NextMusicsIndex				 = NULL; // Make sure
	SX_CurrentMusicSampleIndex = NULL; // no music
	SX_CurrentMusicsIndex			 = NULL; // is set to play
	// Set all FX to not be playing
	for (int i = 0; i < SX_TotalFXLoaded + 1; i++) {
		SX_PlayingFX[i]	= false;
	}
}


// ************************************************************************************************
// SX_playFX
// Plays a sound FX, but ONLY if music is currently playing!
// Parameters: ID of the FX as returned by SX_loadFX to play (int SXI_EffectID)
//             Panning value, 0-127 is left, 128-255 is right (unsigned char SXI_Panning) 
// ************************************************************************************************
void SX_playFX(int SXI_EffectID, unsigned char SXI_Panning) {
	SX_PlayingFX[SXI_EffectID - 1]									= true;
	SX_EffectsArray[SXI_EffectID - 1].Panning				= SXI_Panning;
	SX_EffectsArray[SXI_EffectID - 1].CurrentSample = 0;
}


// ************************************************************************************************
// SX_Exit
// Cleans up the SXLib library, memory and other related stuff
// ************************************************************************************************
void SX_Exit() {
	int i;
	for (i = 0; i < SX_TOTAL_AUDIO_BUFFERS; i++) {
		if (SX_WaveHeader[i].dwFlags & WHDR_PREPARED) {
			waveOutUnprepareHeader(SX_WaveOut, &SX_WaveHeader[i],sizeof(WAVEHDR));
		}
		free(SX_WaveBuffer[i]);
	}
	while (waveOutClose(SX_WaveOut) == WAVERR_STILLPLAYING) { Sleep(10); }
	SX_WaveOut = NULL;
	for (i = 0; i < SX_TOTAL_EFFECTS; i++) {
		if (SX_EffectsArray[i].Loaded) {
			free(SX_EffectsArray[i].WaveFile);
			SX_EffectsArray[i].Loaded = false;
		}
	}
	for (i = 0; i < SX_TOTAL_MUSICS; i++) {
		if (SX_MusicsArray[i].Loaded) {
			free(SX_MusicsArray[i].WaveFile);
			SX_MusicsArray[i].Loaded = false;
		}
	}
}


// ************************************************************************************************
// SX_PlayTimerProc
// This is our timer callback which is called after we start playing via SX_playStart
// Parameters are standard timer callback function parameters
// ************************************************************************************************
void CALLBACK SX_PlayTimerProc(HWND hWnd, UINT nMsg, UINT nIDEvent, DWORD dwTime) {
	while (SX_BuffersSent < SX_TOTAL_AUDIO_BUFFERS) {
		unsigned int iSample, iEffect;
		long mixedSampleLeft, mixedSampleRight;
		long lLeftAdd, lRightAdd;
		for (iSample = 0; iSample < SX_BufferSamples; iSample++) {
			if (SX_MusicsArray[SX_CurrentMusicsIndex].Loaded) {
				mixedSampleLeft = SX_MusicsArray[SX_CurrentMusicsIndex].pData[SX_CurrentMusicSampleIndex * 2] * SX_MusicVolume / 256;
				mixedSampleRight = SX_MusicsArray[SX_CurrentMusicsIndex].pData[SX_CurrentMusicSampleIndex * 2 + 1] * SX_MusicVolume / 256;
				SX_CurrentMusicSampleIndex++;
				// See if we've reached the end of the current music
				if (SX_CurrentMusicSampleIndex == SX_MusicsArray[SX_CurrentMusicsIndex].Samples) {
					SX_CurrentMusicSampleIndex = 0;
					SX_CurrentMusicsIndex			 = SX_NextMusicsIndex;
				}
			} else {
				mixedSampleLeft	 = 0;
				mixedSampleRight = 0;
			}
			// Mix all effects in the currently playing array with the output music
			for (iEffect = 0; iEffect < SX_TOTAL_EFFECTS; iEffect++) {
				// If we are supposed to play an FX and it is valid, go ahead and mix it
				if (SX_PlayingFX[iEffect] && SX_EffectsArray[iEffect].Loaded) {
					// If there is still data for the current effect, add it in
					if (SX_EffectsArray[iEffect].CurrentSample < SX_EffectsArray[iEffect].Samples) {
						lLeftAdd = SX_EffectsArray[iEffect].pData[SX_EffectsArray[iEffect].CurrentSample] * SX_FXVolume * (255 - SX_EffectsArray[iEffect].Panning) / 65536 / SX_SAMPLE_SCALE_FACTOR;
						mixedSampleLeft += (short)lLeftAdd;
						lRightAdd = SX_EffectsArray[iEffect].pData[SX_EffectsArray[iEffect].CurrentSample] *	SX_FXVolume * SX_EffectsArray[iEffect].Panning /	65536 / SX_SAMPLE_SCALE_FACTOR;
						mixedSampleRight += (short)lRightAdd;
					} else {
						SX_PlayingFX[iEffect] = false;
					}
					SX_EffectsArray[iEffect].CurrentSample++;
				}
				((short*)SX_WaveBuffer[SX_NextBuffer])[iSample * 2]			= (short)mixedSampleLeft;
				((short*)SX_WaveBuffer[SX_NextBuffer])[iSample * 2 + 1] = (short)mixedSampleRight;
			}
		}
		waveOutWrite(SX_WaveOut, &SX_WaveHeader[SX_NextBuffer], sizeof(WAVEHDR));
		SX_NextBuffer++;
		if (SX_NextBuffer >= SX_TOTAL_AUDIO_BUFFERS) { SX_NextBuffer %= SX_TOTAL_AUDIO_BUFFERS; }
		SX_BuffersSent++;
	}
}


// ************************************************************************************************
// SX_SXCallBack
// This is the callback required by the waveout function.
// Parameters are standard callback function parameters for the waveout function.
// ************************************************************************************************
void CALLBACK SX_SXCallBack(HWAVEOUT SXI_WaveOut, UINT SXI_Msg, DWORD SXI_Instance, DWORD SXI_ParamA, DWORD SXI_ParamB) {
	if (SXI_Msg == WOM_DONE) {	SX_BuffersSent--; }
}
