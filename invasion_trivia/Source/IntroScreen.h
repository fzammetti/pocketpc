
// ================================================================================================
// Globals
// ================================================================================================
Surface* imgOTXLogo = NULL;
Surface* imgPVLogo	= NULL;
Surface* imgClickGamer	= NULL;
int			 otxX       = NULL;
int      otxY       = NULL;
int      pvX        = NULL;
int      pvY        = NULL;
int			 otxWidth   = NULL;
int			 otxHeight  = NULL;
int			 pvWidth    = NULL;
int			 pvHeight   = NULL;
int      cgX        = NULL;
int      cgY        = NULL;
int			 cgWidth   = NULL;
int			 cgHeight  = NULL;
int			 growFactor = 4; // Must be even
int			 xyAdjust   = growFactor / 2;
int			 fadeValue  = 255;
int			 whichImage = 1; // 1 = CG, 2 = OTX, 3 = PV
int			 growCount  = 0;
int			 FadeStartVal = 30;

// ================================================================================================
// Loader
// ================================================================================================
void loaderIntroScreen(DisplayDevice* display) {
	imgClickGamer = LoadImage(display, IDR_CLICKGAMER);
	imgOTXLogo = LoadImage(display, IDR_OTXLOGO);
	imgPVLogo  = LoadImage(display, IDR_PVLOGO);
	otxWidth   = 2;
	otxHeight  = 2;
	otxX			 = (240 - otxWidth)  / 2;
	otxY			 = (320 - otxHeight) / 2;
	pvWidth	   = 2;
	pvHeight   = 2;
	pvX			   = (240 - pvWidth)   / 2;
	pvY			   = (320 - pvHeight)  / 2;
	cgWidth	   = 2;
	cgHeight   = 2;
	cgX			   = (240 - cgWidth)   / 2;
	cgY			   = (320 - cgHeight)  / 2;
}


// ================================================================================================
// Releaser
// ================================================================================================
void releaserIntroScreen() {
	delete imgOTXLogo;
	delete imgPVLogo;
	delete imgClickGamer;
}


// ================================================================================================
// Handler
// ================================================================================================
void handlerIntroScreen(DisplayDevice* display) {
	if (!ProcessEvents) { ProcessEvents = true; }
	// Set default blending and clear the screen
	display->SetBlending(255);
	display->Clear(Color(0, 0, 0));
	// Set the fade blending value
	display->SetBlending((char)fadeValue);
	// Blit the appropriate image, stretched as required
	if (whichImage == 1) {
		display->BlitStretch(Rect(cgX, cgY + 66, cgWidth + cgX, cgHeight + cgY), imgClickGamer);
	}
	if (whichImage == 2) {
		display->BlitStretch(Rect(otxX, otxY, otxWidth + otxX, otxHeight + otxY), imgOTXLogo);
	}
	if (whichImage == 3) {
		display->BlitStretch(Rect(pvX,  pvY,  pvWidth  + pvX,  pvHeight  + pvY),  imgPVLogo);
	}
	// Stretch and reposition the appropriate image and imcrement the growth counter
	if (whichImage == 1) {
		cgX      = cgX		  - xyAdjust;
		cgY			= cgY		  - (xyAdjust + 1);
		cgWidth  = cgWidth  + growFactor;
		cgHeight = cgHeight + (growFactor + 1);
	}
	if (whichImage == 2) {
		otxX      = otxX		  - xyAdjust;
		otxY			= otxY		  - xyAdjust;
		otxWidth  = otxWidth  + growFactor;
		otxHeight = otxHeight + growFactor;
	}
	if (whichImage == 3) {
		pvX      = pvX			- xyAdjust;
		pvY			 = pvY		  - xyAdjust;
		pvWidth  = pvWidth  + growFactor;
		pvHeight = pvHeight + growFactor;
	}
	growCount++;
	display->SetBlending(255);
	// If we've grown enough and it's time to start fading...
	if ((growCount > FadeStartVal && whichImage != 1) || (growCount > FadeStartVal+25 && whichImage == 1)) {
		// And we haven't faded all the way out yet...
		if (fadeValue > 0) {
			// Decrease the fade counter
			fadeValue = fadeValue - 5;
		} else { // We've hit 0, fade is done, time to switch images
			fadeValue = 255;
			growCount = 0;
			whichImage++;
			FadeStartVal = FadeStartVal - 5;
			// If we've done all images already...
			if (whichImage > 3) {
				// Exit this screen, remembering to reset blending to normal first
				display->SetBlending(255);
				display->Clear(Color(0, 0, 0));
				SceneStarter_TitleScene();
				ProcessEvents = true;
				game.SetVolumeLevel();
				game.currentScreen = csTitleScene;
			}
		}
	}
}

// ================================================================================================
// Event Handlers
// ================================================================================================
void stylusDownIntroScreen(Point stylusPoint) {
}

void stylusMoveIntroScreen(Point stylusPoint) {
}

void stylusUpIntroScreen(Point stylusPoint) {
	if (whichImage != 1) { // Can't abort CG image
		// Begin the Title Screen scene
		SceneStarter_TitleScene();
		ProcessEvents = true;
		game.SetVolumeLevel();
		game.currentScreen = csTitleScene;
	}
}

void keyDownIntroScreen(int key) {
}

void keyUpIntroScreen(int key) {
}
