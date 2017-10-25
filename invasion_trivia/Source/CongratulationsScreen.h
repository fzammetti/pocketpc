
// ================================================================================================
// Defines
// ================================================================================================
#define hstNone				 0
#define hstA					 1		
#define hstB					 2
#define hstC					 3
#define hstD					 4
#define hstE					 5
#define hstF					 6
#define hstG					 7
#define hstH					 8
#define hstI					 9
#define hstJ					 10
#define hstK					 11
#define hstL					 12
#define hstM					 13
#define hstN					 14
#define hstO					 15
#define hstP					 16
#define hstQ					 17
#define hstR					 18
#define hstS					 19
#define hstT					 20
#define hstU					 21
#define hstV					 22
#define hstW					 23
#define hstX					 24
#define hstY					 25
#define hstZ					 26
#define hstDash				 27
#define hstPeriod			 28
#define hstExclamation 29
#define hstUnderscore  30
#define hstBackspace   31
#define hstDone				 32


// ================================================================================================
// Globals
// ================================================================================================
Surface* imgCongratsBGround = NULL;
TCHAR		 enteredName[12]		= L"";
SoundFX  sfxCongratsSound;
SoundFX  sfxCongratsDone;
SoundFX  sfxCongratsBackspace;
int			 charsEntered				= 0;
int			 letterTapped			  = hstNone;
int xA					 = 3;		int yA					 = 140;
int xB					 = 28;	int yB					 = 140;
int xC					 = 53;	int yC					 = 140;
int xD					 = 78;	int yD					 = 140;
int xE					 = 103; int yE					 = 140;
int xF					 = 128; int yF					 = 140;
int xG					 = 153; int yG					 = 140;
int xH					 = 178; int yH					 = 140;
int xI					 = 203; int yI					 = 140;
int xJ					 = 228; int yJ					 = 140;
int xK				   = 3;		int yK					 = 170;
int xL					 = 28;	int yL					 = 170;
int xM					 = 53;	int yM					 = 170;
int xN					 = 78;	int yN					 = 170;
int xO					 = 103; int yO				   = 170;
int xP					 = 128; int yP					 = 170;
int xQ					 = 153; int yQ					 = 170;
int xR					 = 178; int yR					 = 170;
int xS					 = 203; int yS					 = 170;
int xT					 = 228; int yT					 = 170;
int xU				   = 3;		int yU					 = 200;
int xV					 = 28;	int yV					 = 200;
int xW					 = 53;	int yW					 = 200;
int xX					 = 78;	int yX					 = 200;
int xY					 = 103; int yY					 = 200;
int xZ					 = 128; int yZ					 = 200;
int xDash				 = 153; int yDash				 = 200;
int xPeriod			 = 178; int yPeriod			 = 200;
int xExclamation = 203; int yExclamation = 200;
int xUnderscore  = 228; int yUnderscore  = 200;
int xBackspace   = 3;		int yBackspace	 = 240;
int xDone				 = 201; int yDone				 = 240;
int xName				 = 0;		int yName				 = 280;

// ================================================================================================
// Loader
// ================================================================================================
void loaderCongratulationsScreen(DisplayDevice* display) {
	imgCongratsBGround = LoadImage(display, IDR_CONGRATSBGROUND);
	sfxCongratsSound.load(_Module.GetModuleInstance(), IDR_SFX_CONGRATS_SOUND);
	sfxCongratsDone.load(_Module.GetModuleInstance(), IDR_SFX_CONGRATS_DONE);
	sfxCongratsBackspace.load(_Module.GetModuleInstance(), IDR_SFX_CONGRATS_BACKSPACE);
}


// ================================================================================================
// Releaser
// ================================================================================================
void releaserCongratulationsScreen() {
	delete imgCongratsBGround;
}


// ================================================================================================
// Handler
// ================================================================================================
void handlerCongratulationsScreen(DisplayDevice* display) {
	if (!ProcessEvents) { ProcessEvents = true; }
	display->Blit(0, 0, imgCongratsBGround); 
	PFE_drawText(display, pFont, L"You achieved a high score!", PFE_ALIGN_CENTER, 0, 60,  gradientR, gradientG, gradientB, true);
	PFE_drawText(display, pFont, L"Earth survives, THIS time.", PFE_ALIGN_CENTER, 0, 78,  gradientR, gradientG, gradientB, true);
	PFE_drawText(display, pFont, L"Please enter your name:",	  PFE_ALIGN_CENTER, 0, 100, gradientR, gradientG, gradientB, true);
	int Rt = 0; int Gt = 0; int Bt = 0; int Rb = 0; int Gb = 0; int Bb = 0;
	// The default colors for the two button states (N=Normal, H=Highlighted)
	int RtN = 255; int GtN = 255;	int BtN = 0;
	int RbN = 255; int GbN = 0;		int BbN = 0;
	int RtH = 0;	 int GtH = 0;		int BtH = 0;
	int RbH = 225; int GbH = 225; int BbH = 225;
	if (letterTapped==hstA) { Rt=RtH;Gt=GtH;Bt=BtH;Rb=RbH;Gb=GbH;Bb=BbH; } else { Rt=RtN;Gt=GtN;Bt=BtN;Rb=RbN;Gb=GbN;Bb=BbN; }
	PFE_drawText(display, pFont, L"A",				 PFE_ALIGN_NONE,	 xA,					 yA,					 Rt, Gt, Bt, Rb, Gb, Bb);
	if (letterTapped==hstB) { Rt=RtH;Gt=GtH;Bt=BtH;Rb=RbH;Gb=GbH;Bb=BbH; } else { Rt=RtN;Gt=GtN;Bt=BtN;Rb=RbN;Gb=GbN;Bb=BbN; }
	PFE_drawText(display, pFont, L"B",				 PFE_ALIGN_NONE,	 xB,					 yB,					 Rt, Gt, Bt, Rb, Gb, Bb);
	if (letterTapped==hstC) { Rt=RtH;Gt=GtH;Bt=BtH;Rb=RbH;Gb=GbH;Bb=BbH; } else { Rt=RtN;Gt=GtN;Bt=BtN;Rb=RbN;Gb=GbN;Bb=BbN; }
	PFE_drawText(display, pFont, L"C",				 PFE_ALIGN_NONE,	 xC,					 yC,					 Rt, Gt, Bt, Rb, Gb, Bb);
	if (letterTapped==hstD) { Rt=RtH;Gt=GtH;Bt=BtH;Rb=RbH;Gb=GbH;Bb=BbH; } else { Rt=RtN;Gt=GtN;Bt=BtN;Rb=RbN;Gb=GbN;Bb=BbN; }	
	PFE_drawText(display, pFont, L"D",				 PFE_ALIGN_NONE,	 xD,					 yD,					 Rt, Gt, Bt, Rb, Gb, Bb);
	if (letterTapped==hstE) { Rt=RtH;Gt=GtH;Bt=BtH;Rb=RbH;Gb=GbH;Bb=BbH; } else { Rt=RtN;Gt=GtN;Bt=BtN;Rb=RbN;Gb=GbN;Bb=BbN; }
	PFE_drawText(display, pFont, L"E",				 PFE_ALIGN_NONE,	 xE,					 yE,					 Rt, Gt, Bt, Rb, Gb, Bb);
	if (letterTapped==hstF) { Rt=RtH;Gt=GtH;Bt=BtH;Rb=RbH;Gb=GbH;Bb=BbH; } else { Rt=RtN;Gt=GtN;Bt=BtN;Rb=RbN;Gb=GbN;Bb=BbN; }
	PFE_drawText(display, pFont, L"F",				 PFE_ALIGN_NONE,	 xF,					 yF,					 Rt, Gt, Bt, Rb, Gb, Bb);
	if (letterTapped==hstG) { Rt=RtH;Gt=GtH;Bt=BtH;Rb=RbH;Gb=GbH;Bb=BbH; } else { Rt=RtN;Gt=GtN;Bt=BtN;Rb=RbN;Gb=GbN;Bb=BbN; }
	PFE_drawText(display, pFont, L"G",				 PFE_ALIGN_NONE,	 xG,					 yG,					 Rt, Gt, Bt, Rb, Gb, Bb);
	if (letterTapped==hstH) { Rt=RtH;Gt=GtH;Bt=BtH;Rb=RbH;Gb=GbH;Bb=BbH; } else { Rt=RtN;Gt=GtN;Bt=BtN;Rb=RbN;Gb=GbN;Bb=BbN; }
	PFE_drawText(display, pFont, L"H",				 PFE_ALIGN_NONE,	 xH,					 yH,					 Rt, Gt, Bt, Rb, Gb, Bb);
	if (letterTapped==hstI) { Rt=RtH;Gt=GtH;Bt=BtH;Rb=RbH;Gb=GbH;Bb=BbH; } else { Rt=RtN;Gt=GtN;Bt=BtN;Rb=RbN;Gb=GbN;Bb=BbN; }
	PFE_drawText(display, pFont, L"I",				 PFE_ALIGN_NONE,	 xI,					 yI,					 Rt, Gt, Bt, Rb, Gb, Bb);
	if (letterTapped==hstJ) { Rt=RtH;Gt=GtH;Bt=BtH;Rb=RbH;Gb=GbH;Bb=BbH; } else { Rt=RtN;Gt=GtN;Bt=BtN;Rb=RbN;Gb=GbN;Bb=BbN; }
	PFE_drawText(display, pFont, L"J",				 PFE_ALIGN_NONE,	 xJ,					 yJ,					 Rt, Gt, Bt, Rb, Gb, Bb);
	if (letterTapped==hstK) { Rt=RtH;Gt=GtH;Bt=BtH;Rb=RbH;Gb=GbH;Bb=BbH; } else { Rt=RtN;Gt=GtN;Bt=BtN;Rb=RbN;Gb=GbN;Bb=BbN; }
	PFE_drawText(display, pFont, L"K",				 PFE_ALIGN_NONE,	 xK,					 yK,					 Rt, Gt, Bt, Rb, Gb, Bb);
	if (letterTapped==hstL) { Rt=RtH;Gt=GtH;Bt=BtH;Rb=RbH;Gb=GbH;Bb=BbH; } else { Rt=RtN;Gt=GtN;Bt=BtN;Rb=RbN;Gb=GbN;Bb=BbN; }
	PFE_drawText(display, pFont, L"L",				 PFE_ALIGN_NONE,	 xL,					 yL,					 Rt, Gt, Bt, Rb, Gb, Bb);
	if (letterTapped==hstM) { Rt=RtH;Gt=GtH;Bt=BtH;Rb=RbH;Gb=GbH;Bb=BbH; } else { Rt=RtN;Gt=GtN;Bt=BtN;Rb=RbN;Gb=GbN;Bb=BbN; }
	PFE_drawText(display, pFont, L"M",				 PFE_ALIGN_NONE,	 xM,					 yM,					 Rt, Gt, Bt, Rb, Gb, Bb);
	if (letterTapped==hstN) { Rt=RtH;Gt=GtH;Bt=BtH;Rb=RbH;Gb=GbH;Bb=BbH; } else { Rt=RtN;Gt=GtN;Bt=BtN;Rb=RbN;Gb=GbN;Bb=BbN; }
	PFE_drawText(display, pFont, L"N",				 PFE_ALIGN_NONE,	 xN,					 yN,					 Rt, Gt, Bt, Rb, Gb, Bb);
	if (letterTapped==hstO) { Rt=RtH;Gt=GtH;Bt=BtH;Rb=RbH;Gb=GbH;Bb=BbH; } else { Rt=RtN;Gt=GtN;Bt=BtN;Rb=RbN;Gb=GbN;Bb=BbN; }
	PFE_drawText(display, pFont, L"O",				 PFE_ALIGN_NONE,	 xO,					 yO,					 Rt, Gt, Bt, Rb, Gb, Bb);
	if (letterTapped==hstP) { Rt=RtH;Gt=GtH;Bt=BtH;Rb=RbH;Gb=GbH;Bb=BbH; } else { Rt=RtN;Gt=GtN;Bt=BtN;Rb=RbN;Gb=GbN;Bb=BbN; }	
	PFE_drawText(display, pFont, L"P",				 PFE_ALIGN_NONE,	 xP,					 yP,					 Rt, Gt, Bt, Rb, Gb, Bb);
	if (letterTapped==hstQ) { Rt=RtH;Gt=GtH;Bt=BtH;Rb=RbH;Gb=GbH;Bb=BbH; } else { Rt=RtN;Gt=GtN;Bt=BtN;Rb=RbN;Gb=GbN;Bb=BbN; }	
	PFE_drawText(display, pFont, L"Q",				 PFE_ALIGN_NONE,	 xQ,					 yQ,					 Rt, Gt, Bt, Rb, Gb, Bb);
	if (letterTapped==hstR) { Rt=RtH;Gt=GtH;Bt=BtH;Rb=RbH;Gb=GbH;Bb=BbH; } else { Rt=RtN;Gt=GtN;Bt=BtN;Rb=RbN;Gb=GbN;Bb=BbN; }
	PFE_drawText(display, pFont, L"R",				 PFE_ALIGN_NONE,	 xR,					 yR,					 Rt, Gt, Bt, Rb, Gb, Bb);
	if (letterTapped==hstS) { Rt=RtH;Gt=GtH;Bt=BtH;Rb=RbH;Gb=GbH;Bb=BbH; } else { Rt=RtN;Gt=GtN;Bt=BtN;Rb=RbN;Gb=GbN;Bb=BbN; }
	PFE_drawText(display, pFont, L"S",				 PFE_ALIGN_NONE,	 xS,					 yS,					 Rt, Gt, Bt, Rb, Gb, Bb);
	if (letterTapped==hstT) { Rt=RtH;Gt=GtH;Bt=BtH;Rb=RbH;Gb=GbH;Bb=BbH; } else { Rt=RtN;Gt=GtN;Bt=BtN;Rb=RbN;Gb=GbN;Bb=BbN; }
	PFE_drawText(display, pFont, L"T",				 PFE_ALIGN_NONE,	 xT,					 yT,					 Rt, Gt, Bt, Rb, Gb, Bb);
	if (letterTapped==hstU) { Rt=RtH;Gt=GtH;Bt=BtH;Rb=RbH;Gb=GbH;Bb=BbH; } else { Rt=RtN;Gt=GtN;Bt=BtN;Rb=RbN;Gb=GbN;Bb=BbN; }
	PFE_drawText(display, pFont, L"U",				 PFE_ALIGN_NONE,	 xU,					 yU,					 Rt, Gt, Bt, Rb, Gb, Bb);
	if (letterTapped==hstV) { Rt=RtH;Gt=GtH;Bt=BtH;Rb=RbH;Gb=GbH;Bb=BbH; } else { Rt=RtN;Gt=GtN;Bt=BtN;Rb=RbN;Gb=GbN;Bb=BbN; }
	PFE_drawText(display, pFont, L"V",				 PFE_ALIGN_NONE,	 xV,					 yV,					 Rt, Gt, Bt, Rb, Gb, Bb);
	if (letterTapped==hstW) { Rt=RtH;Gt=GtH;Bt=BtH;Rb=RbH;Gb=GbH;Bb=BbH; } else { Rt=RtN;Gt=GtN;Bt=BtN;Rb=RbN;Gb=GbN;Bb=BbN; }
	PFE_drawText(display, pFont, L"W",			   PFE_ALIGN_NONE,	 xW,					 yW,					 Rt, Gt, Bt, Rb, Gb, Bb);
	if (letterTapped==hstX) { Rt=RtH;Gt=GtH;Bt=BtH;Rb=RbH;Gb=GbH;Bb=BbH; } else { Rt=RtN;Gt=GtN;Bt=BtN;Rb=RbN;Gb=GbN;Bb=BbN; }
	PFE_drawText(display, pFont, L"X",				 PFE_ALIGN_NONE,	 xX,					 yX,					 Rt, Gt, Bt, Rb, Gb, Bb);
	if (letterTapped==hstY) { Rt=RtH;Gt=GtH;Bt=BtH;Rb=RbH;Gb=GbH;Bb=BbH; } else { Rt=RtN;Gt=GtN;Bt=BtN;Rb=RbN;Gb=GbN;Bb=BbN; }
	PFE_drawText(display, pFont, L"Y",				 PFE_ALIGN_NONE,	 xY,					 yY,					 Rt, Gt, Bt, Rb, Gb, Bb);
	if (letterTapped==hstZ) { Rt=RtH;Gt=GtH;Bt=BtH;Rb=RbH;Gb=GbH;Bb=BbH; } else { Rt=RtN;Gt=GtN;Bt=BtN;Rb=RbN;Gb=GbN;Bb=BbN; }
	PFE_drawText(display, pFont, L"Z",				 PFE_ALIGN_NONE,	 xZ,					 yZ,					 Rt, Gt, Bt, Rb, Gb, Bb);
	if (letterTapped==hstDash) { Rt=RtH;Gt=GtH;Bt=BtH;Rb=RbH;Gb=GbH;Bb=BbH; } else { Rt=RtN;Gt=GtN;Bt=BtN;Rb=RbN;Gb=GbN;Bb=BbN; }
	PFE_drawText(display, pFont, L"-",				 PFE_ALIGN_NONE,	 xDash,				 yDash,				 Rt, Gt, Bt, Rb, Gb, Bb);
	if (letterTapped==hstPeriod) { Rt=RtH;Gt=GtH;Bt=BtH;Rb=RbH;Gb=GbH;Bb=BbH; } else { Rt=RtN;Gt=GtN;Bt=BtN;Rb=RbN;Gb=GbN;Bb=BbN; }
	PFE_drawText(display, pFont, L".",				 PFE_ALIGN_NONE,	 xPeriod,			 yPeriod,			 Rt, Gt, Bt, Rb, Gb, Bb);
	if (letterTapped==hstExclamation) { Rt=RtH;Gt=GtH;Bt=BtH;Rb=RbH;Gb=GbH;Bb=BbH; } else { Rt=RtN;Gt=GtN;Bt=BtN;Rb=RbN;Gb=GbN;Bb=BbN; }
	PFE_drawText(display, pFont, L"!",				 PFE_ALIGN_NONE,	 xExclamation, yExclamation, Rt, Gt, Bt, Rb, Gb, Bb);
	if (letterTapped==hstUnderscore) { Rt=RtH;Gt=GtH;Bt=BtH;Rb=RbH;Gb=GbH;Bb=BbH; } else { Rt=RtN;Gt=GtN;Bt=BtN;Rb=RbN;Gb=GbN;Bb=BbN; }
	PFE_drawText(display, pFont, L"_",	       PFE_ALIGN_NONE,	 xUnderscore,  yUnderscore,	 Rt, Gt, Bt, Rb, Gb, Bb);
	if (letterTapped==hstBackspace) { Rt=RtH;Gt=GtH;Bt=BtH;Rb=RbH;Gb=GbH;Bb=BbH; } else { Rt=RtN;Gt=GtN;Bt=BtN;Rb=RbN;Gb=GbN;Bb=BbN; }
	PFE_drawText(display, pFont, L"Backspace", PFE_ALIGN_NONE,	 xBackspace,   yBackspace,	 Rt, Gt, Bt, Rb, Gb, Bb);
	if (letterTapped==hstDone) { Rt=RtH;Gt=GtH;Bt=BtH;Rb=RbH;Gb=GbH;Bb=BbH; } else { Rt=RtN;Gt=GtN;Bt=BtN;Rb=RbN;Gb=GbN;Bb=BbN; }
	PFE_drawText(display, pFont, L"Done",      PFE_ALIGN_NONE,	 xDone,				 yDone,				 Rt, Gt, Bt, Rb, Gb, Bb);
	PFE_drawText(display, pFont, enteredName,  PFE_ALIGN_CENTER, xName,				 yName,				 0,	 0,	 0,	 0,	 255, 0);
}


// ================================================================================================
// Event Handlers
// ================================================================================================
void stylusDownCongratulationsScreen(Point stylusPoint) {
	Rect menuBounds;
	// A
	menuBounds.Set(xA, yA, xA + 8, yA + 16); if (menuBounds.Contains(stylusPoint)) { letterTapped = hstA; return; }
	// B
	menuBounds.Set(xB, yB, xB + 8, yB + 16); if (menuBounds.Contains(stylusPoint)) { letterTapped = hstB; return; }
	// C
	menuBounds.Set(xC, yC, xC + 8, yC + 16); if (menuBounds.Contains(stylusPoint)) { letterTapped = hstC; return; }
	// D
	menuBounds.Set(xD, yD, xD + 8, yD + 16); if (menuBounds.Contains(stylusPoint)) { letterTapped = hstD; return; }
	// E
	menuBounds.Set(xE, yE, xE + 8, yE + 16); if (menuBounds.Contains(stylusPoint)) { letterTapped = hstE; return; }
	// F
	menuBounds.Set(xF, yF, xF + 8, yF + 16); if (menuBounds.Contains(stylusPoint)) { letterTapped = hstF; return; }
	// G
	menuBounds.Set(xG, yG, xG + 8, yG + 16); if (menuBounds.Contains(stylusPoint)) { letterTapped = hstG; return; }
	// H
	menuBounds.Set(xH, yH, xH + 8, yH + 16); if (menuBounds.Contains(stylusPoint)) { letterTapped = hstH; return; }
	// I
	menuBounds.Set(xI, yI, xI + 8, yI + 16); if (menuBounds.Contains(stylusPoint)) { letterTapped = hstI; return; }
	// J
	menuBounds.Set(xJ, yJ, xJ + 8, yJ + 16); if (menuBounds.Contains(stylusPoint)) { letterTapped = hstJ; return; }
	// K
	menuBounds.Set(xK, yK, xK + 8, yK + 16); if (menuBounds.Contains(stylusPoint)) { letterTapped = hstK; return; }
	// L
	menuBounds.Set(xL, yL, xL + 8, yL + 16); if (menuBounds.Contains(stylusPoint)) { letterTapped = hstL; return; }
	// M
	menuBounds.Set(xM, yM, xM + 8, yM + 16); if (menuBounds.Contains(stylusPoint)) { letterTapped = hstM; return; }
	// N
	menuBounds.Set(xN, yN, xN + 8, yN + 16); if (menuBounds.Contains(stylusPoint)) { letterTapped = hstN; return; }
	// O
	menuBounds.Set(xO, yO, xO + 8, yO + 16); if (menuBounds.Contains(stylusPoint)) { letterTapped = hstO; return; }
	// P
	menuBounds.Set(xP, yP, xP + 8, yP + 16); if (menuBounds.Contains(stylusPoint)) { letterTapped = hstP; return; }
	// Q
	menuBounds.Set(xQ, yQ, xQ + 8, yQ + 16); if (menuBounds.Contains(stylusPoint)) { letterTapped = hstQ; return; }
	// R
	menuBounds.Set(xR, yR, xR + 8, yR + 16); if (menuBounds.Contains(stylusPoint)) { letterTapped = hstR; return; }
	// S
	menuBounds.Set(xS, yS, xS + 8, yS + 16); if (menuBounds.Contains(stylusPoint)) { letterTapped = hstS; return; }
	// T
	menuBounds.Set(xT, yT, xT + 8, yT + 16); if (menuBounds.Contains(stylusPoint)) { letterTapped = hstT; return; }
	// U
	menuBounds.Set(xU, yU, xU + 8, yU + 16); if (menuBounds.Contains(stylusPoint)) { letterTapped = hstU; return; }
	// V
	menuBounds.Set(xV, yV, xV + 8, yV + 16); if (menuBounds.Contains(stylusPoint)) { letterTapped = hstV; return; }
	// W
	menuBounds.Set(xW, yW, xW + 8, yW + 16); if (menuBounds.Contains(stylusPoint)) { letterTapped = hstW; return; }
	// X
	menuBounds.Set(xX, yX, xX + 8, yX + 16); if (menuBounds.Contains(stylusPoint)) { letterTapped = hstX; return; }
	// Y
	menuBounds.Set(xY, yY, xY + 8, yY + 16); if (menuBounds.Contains(stylusPoint)) { letterTapped = hstY; return; }
	// Z
	menuBounds.Set(xZ, yZ, xZ + 8, yZ + 16); if (menuBounds.Contains(stylusPoint)) { letterTapped = hstZ; return; }
	// DASH
	menuBounds.Set(xDash, yDash, xDash + 8, yDash + 16); if (menuBounds.Contains(stylusPoint)) { letterTapped = hstDash; return; }
	// PERIOD
	menuBounds.Set(xPeriod, yPeriod, xPeriod + 8, yPeriod + 16); if (menuBounds.Contains(stylusPoint)) { letterTapped = hstPeriod; return; }
	// EXCLAMATION
	menuBounds.Set(xExclamation, yExclamation, xExclamation + 8, yExclamation + 16); if (menuBounds.Contains(stylusPoint)) { letterTapped = hstExclamation; return; }
	// UNDERSCORE
	menuBounds.Set(xUnderscore, yUnderscore, xUnderscore + 8, yUnderscore + 16); if (menuBounds.Contains(stylusPoint)) { letterTapped = hstUnderscore; return; }
	// BACKSPACE
	menuBounds.Set(xBackspace, yBackspace, xBackspace + (8 * 9), yBackspace + 16); if (menuBounds.Contains(stylusPoint)) { letterTapped = hstBackspace; return; }
	// DONE
	menuBounds.Set(xDone, yDone, xDone + (8 * 4), yDone + 16); if (menuBounds.Contains(stylusPoint)) { letterTapped = hstDone; return; }
}

void stylusMoveCongratulationsScreen(Point stylusPoint) {
}

void stylusUpCongratulationsScreen(Point stylusPoint) {
	Rect menuBounds;
	// A
	menuBounds.Set(xA, yA, xA + 8, yA + 16);
	if (menuBounds.Contains(stylusPoint) && letterTapped == hstA) { game.itPlaySFX(&sfxCongratsSound, false);
		if (charsEntered < 8) {	enteredName[charsEntered] = 'A'; charsEntered++; } letterTapped = hstNone; return;
	}
	// B
	menuBounds.Set(xB, yB, xB + 8, yB + 16);
	if (menuBounds.Contains(stylusPoint) && letterTapped == hstB) { game.itPlaySFX(&sfxCongratsSound, false);
		if (charsEntered < 8) {	enteredName[charsEntered] = 'B'; charsEntered++; } letterTapped = hstNone; return;
	}
	// C
	menuBounds.Set(xC, yC, xC + 8, yC + 16);
	if (menuBounds.Contains(stylusPoint) && letterTapped == hstC) { game.itPlaySFX(&sfxCongratsSound, false);
		if (charsEntered < 8) {	enteredName[charsEntered] = 'C'; charsEntered++; } letterTapped = hstNone; return;
	}
	// D
	menuBounds.Set(xD, yD, xD + 8, yD + 16);
	if (menuBounds.Contains(stylusPoint) && letterTapped == hstD) { game.itPlaySFX(&sfxCongratsSound, false);
		if (charsEntered < 8) {	enteredName[charsEntered] = 'D'; charsEntered++; } letterTapped = hstNone; return;
	}
	// E
	menuBounds.Set(xE, yE, xE + 8, yE + 16);
	if (menuBounds.Contains(stylusPoint) && letterTapped == hstE) { game.itPlaySFX(&sfxCongratsSound, false);
		if (charsEntered < 8) {	enteredName[charsEntered] = 'E'; charsEntered++; } letterTapped = hstNone; return;
	}
	// F
	menuBounds.Set(xF, yF, xF + 8, yF + 16);
	if (menuBounds.Contains(stylusPoint) && letterTapped == hstF) { game.itPlaySFX(&sfxCongratsSound, false);
		if (charsEntered < 8) {	enteredName[charsEntered] = 'F'; charsEntered++; } letterTapped = hstNone; return;
	}
	// G
	menuBounds.Set(xG, yG, xG + 8, yG + 16);
	if (menuBounds.Contains(stylusPoint) && letterTapped == hstG) { game.itPlaySFX(&sfxCongratsSound, false);
		if (charsEntered < 8) {	enteredName[charsEntered] = 'G'; charsEntered++; } letterTapped = hstNone; return;
	}
	// H
	menuBounds.Set(xH, yH, xH + 8, yH + 16);
	if (menuBounds.Contains(stylusPoint) && letterTapped == hstH) { game.itPlaySFX(&sfxCongratsSound, false);
		if (charsEntered < 8) {	enteredName[charsEntered] = 'H'; charsEntered++; } letterTapped = hstNone; return;
	}
	// I
	menuBounds.Set(xI, yI, xI + 8, yI + 16);
	if (menuBounds.Contains(stylusPoint) && letterTapped == hstI) { game.itPlaySFX(&sfxCongratsSound, false);
		if (charsEntered < 8) {	enteredName[charsEntered] = 'I'; charsEntered++; } letterTapped = hstNone; return;
	}
	// J
	menuBounds.Set(xJ, yJ, xJ + 8, yJ + 16);
	if (menuBounds.Contains(stylusPoint) && letterTapped == hstJ) { game.itPlaySFX(&sfxCongratsSound, false);
		if (charsEntered < 8) {	enteredName[charsEntered] = 'J'; charsEntered++; } letterTapped = hstNone; return;
	}
	// K
	menuBounds.Set(xK, yK, xK + 8, yK + 16);
	if (menuBounds.Contains(stylusPoint) && letterTapped == hstK) { game.itPlaySFX(&sfxCongratsSound, false);
		if (charsEntered < 8) {	enteredName[charsEntered] = 'K'; charsEntered++; } letterTapped = hstNone; return;
	}
	// L
	menuBounds.Set(xL, yL, xL + 8, yL + 16);
	if (menuBounds.Contains(stylusPoint) && letterTapped == hstL) { game.itPlaySFX(&sfxCongratsSound, false);
		if (charsEntered < 8) {	enteredName[charsEntered] = 'L'; charsEntered++; } letterTapped = hstNone; return;
	}
	// M
	menuBounds.Set(xM, yM, xM + 8, yM + 16);
	if (menuBounds.Contains(stylusPoint) && letterTapped == hstM) { game.itPlaySFX(&sfxCongratsSound, false);
		if (charsEntered < 8) {	enteredName[charsEntered] = 'M'; charsEntered++; } letterTapped = hstNone; return;
	}
	// N
	menuBounds.Set(xN, yN, xN + 8, yN + 16);
	if (menuBounds.Contains(stylusPoint) && letterTapped == hstN) { game.itPlaySFX(&sfxCongratsSound, false);
		if (charsEntered < 8) {	enteredName[charsEntered] = 'N'; charsEntered++; } letterTapped = hstNone; return;
	}
	// O
	menuBounds.Set(xO, yO, xO + 8, yO + 16);
	if (menuBounds.Contains(stylusPoint) && letterTapped == hstO) { game.itPlaySFX(&sfxCongratsSound, false);
		if (charsEntered < 8) {	enteredName[charsEntered] = 'O'; charsEntered++; } letterTapped = hstNone; return;
	}
	// P
	menuBounds.Set(xP, yP, xP + 8, yP + 16);
	if (menuBounds.Contains(stylusPoint) && letterTapped == hstP) { game.itPlaySFX(&sfxCongratsSound, false);
		if (charsEntered < 8) {	enteredName[charsEntered] = 'P'; charsEntered++; } letterTapped = hstNone; return;
	}
	// Q
	menuBounds.Set(xQ, yQ, xQ + 8, yQ + 16);
	if (menuBounds.Contains(stylusPoint) && letterTapped == hstQ) { game.itPlaySFX(&sfxCongratsSound, false);
		if (charsEntered < 8) {	enteredName[charsEntered] = 'Q'; charsEntered++; } letterTapped = hstNone; return;
	}
	// R
	menuBounds.Set(xR, yR, xR + 8, yR + 16);
	if (menuBounds.Contains(stylusPoint) && letterTapped == hstR) { game.itPlaySFX(&sfxCongratsSound, false);
		if (charsEntered < 8) {	enteredName[charsEntered] = 'R'; charsEntered++; } letterTapped = hstNone; return;
	}
	// S
	menuBounds.Set(xS, yS, xS + 8, yS + 16);
	if (menuBounds.Contains(stylusPoint) && letterTapped == hstS) { game.itPlaySFX(&sfxCongratsSound, false);
		if (charsEntered < 8) {	enteredName[charsEntered] = 'S'; charsEntered++; } letterTapped = hstNone; return;
	}
	// T
	menuBounds.Set(xT, yT, xT + 8, yT + 16);
	if (menuBounds.Contains(stylusPoint) && letterTapped == hstT) { game.itPlaySFX(&sfxCongratsSound, false);
		if (charsEntered < 8) {	enteredName[charsEntered] = 'T'; charsEntered++; } letterTapped = hstNone; return;
	}
	// U
	menuBounds.Set(xU, yU, xU + 8, yU + 16);
	if (menuBounds.Contains(stylusPoint) && letterTapped == hstU) { game.itPlaySFX(&sfxCongratsSound, false);
		if (charsEntered < 8) {	enteredName[charsEntered] = 'U'; charsEntered++; } letterTapped = hstNone; return;
	}
	// V
	menuBounds.Set(xV, yV, xV + 8, yV + 16);
	if (menuBounds.Contains(stylusPoint) && letterTapped == hstV) { game.itPlaySFX(&sfxCongratsSound, false);
		if (charsEntered < 8) {	enteredName[charsEntered] = 'V'; charsEntered++; } letterTapped = hstNone; return;
	}
	// W
	menuBounds.Set(xW, yW, xW + 8, yW + 16);
	if (menuBounds.Contains(stylusPoint) && letterTapped == hstW) { game.itPlaySFX(&sfxCongratsSound, false);
		if (charsEntered < 8) {	enteredName[charsEntered] = 'W'; charsEntered++; } letterTapped = hstNone; return;
	}
	// X
	menuBounds.Set(xX, yX, xX + 8, yX + 16);
	if (menuBounds.Contains(stylusPoint) && letterTapped == hstX) { game.itPlaySFX(&sfxCongratsSound, false);
		if (charsEntered < 8) {	enteredName[charsEntered] = 'X'; charsEntered++; } letterTapped = hstNone; return;
	}
	// Y
	menuBounds.Set(xY, yY, xY + 8, yY + 16);
	if (menuBounds.Contains(stylusPoint) && letterTapped == hstY) { game.itPlaySFX(&sfxCongratsSound, false);
		if (charsEntered < 8) {	enteredName[charsEntered] = 'Y'; charsEntered++; } letterTapped = hstNone; return;
	}
	// Z
	menuBounds.Set(xZ, yZ, xZ + 8, yZ + 16);
	if (menuBounds.Contains(stylusPoint) && letterTapped == hstZ) { game.itPlaySFX(&sfxCongratsSound, false);
		if (charsEntered < 8) {	enteredName[charsEntered] = 'Z'; charsEntered++; } letterTapped = hstNone; return;
	}
	// DASH
	menuBounds.Set(xDash, yDash, xDash + 8, yDash + 16);
	if (menuBounds.Contains(stylusPoint) && letterTapped == hstDash) { game.itPlaySFX(&sfxCongratsSound, false);
		if (charsEntered < 8) {	enteredName[charsEntered] = '-'; charsEntered++; } letterTapped = hstNone; return;
	}
	// PERIOD
	menuBounds.Set(xPeriod, yPeriod, xPeriod + 8, yPeriod + 16);
	if (menuBounds.Contains(stylusPoint) && letterTapped == hstPeriod) { game.itPlaySFX(&sfxCongratsSound, false);
		if (charsEntered < 8) {	enteredName[charsEntered] = '.'; charsEntered++; } letterTapped = hstNone; return;
	}
	// EXCLAMATION
	menuBounds.Set(xExclamation, yExclamation, xExclamation + 8, yExclamation + 16);
	if (menuBounds.Contains(stylusPoint) && letterTapped == hstExclamation) { game.itPlaySFX(&sfxCongratsSound, false);
		if (charsEntered < 8) {	enteredName[charsEntered] = '!'; charsEntered++; } letterTapped = hstNone; return;
	}
	// UNDERSCORE
	menuBounds.Set(xUnderscore, yUnderscore, xUnderscore + 8, yUnderscore + 16);
	if (menuBounds.Contains(stylusPoint) && letterTapped == hstUnderscore) { game.itPlaySFX(&sfxCongratsSound, false);
		if (charsEntered < 8) {	enteredName[charsEntered] = '_'; charsEntered++; } letterTapped = hstNone; return;
	}
	// BACKSPACE
	menuBounds.Set(xBackspace, yBackspace, xBackspace + (8 * 9), yBackspace + 16);
	if (menuBounds.Contains(stylusPoint) && letterTapped == hstBackspace) { game.itPlaySFX(&sfxCongratsBackspace, false);
		if (charsEntered > 0) {	charsEntered--;	enteredName[charsEntered] = NULL;	}
		letterTapped = hstNone; 
		return;
	}
	// DONE
	menuBounds.Set(xDone, yDone, xDone + (8 * 4), yDone + 16);
	if (menuBounds.Contains(stylusPoint) && letterTapped == hstDone) { game.itPlaySFX(&sfxCongratsDone, false);
		// Save the point level reached, character used and name in the proper array, then save the HSS file
		if (wcscmp(enteredName, L"") == 0) { wcscpy(enteredName, L"None"); }
		if (game.difficultyLevel == dlEasy) {
			HighScoreEasy.pointLevelReached = (unsigned char)game.currentPointLevel;
			HighScoreEasy.characterUsed = game.CharacterInUse;
			wcscpy(HighScoreEasy.playerName, enteredName);
			game.writeHSSFile();
		}
		if (game.difficultyLevel == dlNormal) {
			HighScoreNormal.pointLevelReached = (unsigned char)game.currentPointLevel;
			HighScoreNormal.characterUsed = game.CharacterInUse;
			wcscpy(HighScoreNormal.playerName, enteredName);
			game.writeHSSFile();
		}
		if (game.difficultyLevel == dlHard) {
			HighScoreHard.pointLevelReached = (unsigned char)game.currentPointLevel;
			HighScoreHard.characterUsed = game.CharacterInUse;
			wcscpy(HighScoreHard.playerName, enteredName);
			game.writeHSSFile();
		}
		_wcsset(enteredName, NULL);
		charsEntered = 0;
		letterTapped = hstNone;
		game.itPlayThemeMusic();
		ProcessEvents = false;
		letterTapped = hstNone; 
		game.currentScreen = csHighScoresScreen;
		return;
	}
	letterTapped = hstNone;
}

void keyDownCongratulationsScreen(int key) {
}

void keyUpCongratulationsScreen(int key) {
}