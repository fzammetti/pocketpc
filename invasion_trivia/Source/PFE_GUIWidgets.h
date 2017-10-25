
// ************************************************************************************************
// Defines
// ************************************************************************************************
#define PFE_POPUP_OK    1
#define PFE_POPUP_YESNO 2


// ************************************************************************************************
// Globals
// ************************************************************************************************
Surface* PFE_DropDown_imgDropBox			 = NULL;
Surface* PFE_DropDown_imgLineOne			 = NULL;
Surface* PFE_DropDown_imgLineTwo			 = NULL;
Surface* PFE_DropDown_imgLineThree		 = NULL;
Surface* PFE_DropDown_imgDropDown_0		 = NULL;
Surface* PFE_DropDown_imgDropDown_1		 = NULL;
Surface* PFE_DropDown_imgUpArrow_0		 = NULL;
Surface* PFE_DropDown_imgUpArrow_1		 = NULL;
Surface* PFE_DropDown_imgDownArrow_0	 = NULL;
Surface* PFE_DropDown_imgDownArrow_1	 = NULL;
Surface* PFE_DropDown_imgArrowDivider	 = NULL;
Surface* PFE_Popup_imgBorder					 = NULL;
Surface* PFE_Popup_imgYes_0						 = NULL;
Surface* PFE_Popup_imgNo_0						 = NULL;
Surface* PFE_Popup_imgYes_1						 = NULL;
Surface* PFE_Popup_imgNo_1						 = NULL;
bool		 PFE_Popup_YesPressed					 = false;
bool		 PFE_Popup_NoPressed					 = false;
bool		 PFE_Popup_OkPressed					 = false;
int 		 PFE_Popup_currentButtonOption = 0;
int			 PFE_Popup_locX								 = 29;
int			 PFE_Popup_locY								 = 110;
int			 PFE_Popup_width							 = 181;
int			 PFE_Popup_height							 = 99;


// ************************************************************************************************
// Functions
// ************************************************************************************************

// Loader
void PFE_GUIWidgetsInitialize(DisplayDevice* display) {
	PFE_Popup_imgYes_0 = LoadImage(display, IDR_PFE_POPUP_YES_0);
	PFE_Popup_imgYes_0->SetColorMask(Color(255, 255, 0));
	PFE_Popup_imgNo_0 = LoadImage(display, IDR_PFE_POPUP_NO_0);
	PFE_Popup_imgNo_0->SetColorMask(Color(255, 255, 0));
	PFE_Popup_imgYes_1 = LoadImage(display, IDR_PFE_POPUP_YES_1);
	PFE_Popup_imgYes_1->SetColorMask(Color(255, 255, 0));
	PFE_Popup_imgNo_1 = LoadImage(display, IDR_PFE_POPUP_NO_1);
	PFE_Popup_imgNo_1->SetColorMask(Color(255, 255, 0));
	PFE_Popup_imgBorder = LoadImage(display, IDR_PFE_POPUP_BORDER);
	PFE_Popup_imgBorder->SetColorMask(Color(255, 0, 0));
	PFE_DropDown_imgDropBox = LoadImage(display, IDR_PFE_DROPDOWN_DROPBOX);
	PFE_DropDown_imgDropBox->SetColorMask(Color(0, 0, 0));
	PFE_DropDown_imgDropDown_0 = LoadImage(display, IDR_PFE_DROPDOWN_0);
	PFE_DropDown_imgDropDown_0->SetColorMask(Color(255, 0, 0));
	PFE_DropDown_imgDropDown_1 = LoadImage(display, IDR_PFE_DROPDOWN_1);
	PFE_DropDown_imgDropDown_1->SetColorMask(Color(255, 0, 0));
	PFE_DropDown_imgUpArrow_0 = LoadImage(display, IDR_PFE_DROPDOWN_UPARROW_0);
	PFE_DropDown_imgUpArrow_0->SetColorMask(Color(255, 0, 0));
	PFE_DropDown_imgDownArrow_0 = LoadImage(display, IDR_PFE_DROPDOWN_DOWNARROW_0);
	PFE_DropDown_imgDownArrow_0->SetColorMask(Color(255, 0, 0));
	PFE_DropDown_imgUpArrow_1 = LoadImage(display, IDR_PFE_DROPDOWN_UPARROW_1);
	PFE_DropDown_imgUpArrow_1->SetColorMask(Color(255, 0, 0));
	PFE_DropDown_imgDownArrow_1 = LoadImage(display, IDR_PFE_DROPDOWN_DOWNARROW_1);
	PFE_DropDown_imgDownArrow_1->SetColorMask(Color(255, 0, 0));
	PFE_DropDown_imgArrowDivider = LoadImage(display, IDR_PFE_DROPDOWN_ARROWDIVIDER);
	PFE_DropDown_imgLineOne = LoadImage(display, IDR_PFE_DROPDOWN_DROPBOX_LINEONE);
	PFE_DropDown_imgLineOne->SetColorMask(Color(0, 0, 0));
	PFE_DropDown_imgLineTwo = LoadImage(display, IDR_PFE_DROPDOWN_DROPBOX_LINETWO);
	PFE_DropDown_imgLineTwo->SetColorMask(Color(0, 0, 0));
	PFE_DropDown_imgLineThree = LoadImage(display, IDR_PFE_DROPDOWN_DROPBOX_LINETHREE);
	PFE_DropDown_imgLineThree->SetColorMask(Color(0, 0, 0));
}


// Releaser
void PFE_GUIWidgetsShutdown() {
	delete PFE_Popup_imgYes_0;
	delete PFE_Popup_imgNo_0;
	delete PFE_Popup_imgYes_1;
	delete PFE_Popup_imgNo_1;
	delete PFE_Popup_imgBorder;
	delete PFE_DropDown_imgDropDown_0;
	delete PFE_DropDown_imgDropDown_1;
	delete PFE_DropDown_imgDropBox;
	delete PFE_DropDown_imgUpArrow_0;
	delete PFE_DropDown_imgUpArrow_1;
	delete PFE_DropDown_imgDownArrow_0;
	delete PFE_DropDown_imgDownArrow_1;
	delete PFE_DropDown_imgArrowDivider;
	delete PFE_DropDown_imgLineOne;
	delete PFE_DropDown_imgLineTwo;
	delete PFE_DropDown_imgLineThree;
}


// Draws a popup with the specified text
// Two lines of text, 18 chars max, popup is always centered
// Solid border, 6 pixels, 4 pixels padding between border and contents
// Background is alpha-blended with screen
// Can specify button options (either a single Ok button or a Yes & No buttons)
void PFE_Popup(DisplayDevice* display, TCHAR* textLine1, TCHAR* textLine2, Pixel BorderColor, Pixel FillColor, int buttonOption) {
	PFE_Popup_currentButtonOption = buttonOption;
	// Draw the blended region
	display->SetBlending(160);
	display->FillRect(Rect(PFE_Popup_locX + 6, PFE_Popup_locY + 6, PFE_Popup_locX + PFE_Popup_width  - 5, PFE_Popup_locY + PFE_Popup_height - 5), FillColor);
	display->SetBlending(255);
	// Border
	display->Blit(PFE_Popup_locX, PFE_Popup_locY, PFE_Popup_imgBorder);
	// Draw text
	PFE_drawText(display, pFont, textLine1, PFE_ALIGN_NONE, (240 - wcslen(textLine1) * 9) / 2, PFE_Popup_locY + 15, 255, 255, 255, false);
	PFE_drawText(display, pFont, textLine2, PFE_ALIGN_NONE, (240 - wcslen(textLine2) * 9) / 2, PFE_Popup_locY + 35, 255, 255, 255, false);
	switch (buttonOption) {
		case PFE_POPUP_OK: {
			if (PFE_Popup_OkPressed) {	
				display->Blit(PFE_Popup_locX + 76, PFE_Popup_locY + PFE_Popup_height - 42, PFE_Popup_imgYes_1);
			} else {
				display->Blit(PFE_Popup_locX + 76, PFE_Popup_locY + PFE_Popup_height - 42, PFE_Popup_imgYes_0);
			}
		break; }
		case PFE_POPUP_YESNO: {
			if (PFE_Popup_YesPressed) {	
				display->Blit(PFE_Popup_locX + 40, PFE_Popup_locY + PFE_Popup_height - 42, PFE_Popup_imgYes_1);
			} else {
				display->Blit(PFE_Popup_locX + 40, PFE_Popup_locY + PFE_Popup_height - 42, PFE_Popup_imgYes_0);
			}
			if (PFE_Popup_NoPressed) {
				display->Blit(PFE_Popup_locX + PFE_Popup_width - 66, PFE_Popup_locY + PFE_Popup_height - 42, PFE_Popup_imgNo_1);
			} else {
				display->Blit(PFE_Popup_locX + PFE_Popup_width - 66, PFE_Popup_locY + PFE_Popup_height - 42, PFE_Popup_imgNo_0);
			}
		break; }
	}
}


// Draws a popup with the specified text
// Two lines of numbers
// Solid border, 6 pixels, 4 pixels padding between border and contents
// Background is alpha-blended with screen
// Can specify button options (either a single Ok button or a Yes & No buttons)
void PFE_Popup(DisplayDevice* display, int number1, int number2, Pixel BorderColor, Pixel FillColor, int buttonOption) {
	PFE_Popup_currentButtonOption = buttonOption;
	// Draw the blended region
	display->SetBlending(160);
	display->FillRect(Rect(PFE_Popup_locX + 6, PFE_Popup_locY + 6, PFE_Popup_locX + PFE_Popup_width - 5, PFE_Popup_locY + PFE_Popup_height - 5), FillColor);
	display->SetBlending(255);
	// Border
	display->Blit(PFE_Popup_locX, PFE_Popup_locY, PFE_Popup_imgBorder);
	// Draw text
	TCHAR szLine1[34] = L"";
	TCHAR szLine2[34] = L"";
	swprintf(szLine1, L"%d", number1);
	swprintf(szLine2, L"%d", number2);
	PFE_drawText(display, pFont, szLine1, PFE_ALIGN_NONE, (240 - wcslen(szLine1) * 9) / 2, PFE_Popup_locY + 15, 255, 255, 255, false);
	PFE_drawText(display, pFont, szLine2, PFE_ALIGN_NONE, (240 - wcslen(szLine2) * 9) / 2, PFE_Popup_locY + 35, 255, 255, 255, false);
	switch (buttonOption) {
		case PFE_POPUP_OK: {
			if (PFE_Popup_OkPressed) {	
				display->Blit(PFE_Popup_locX + 76, PFE_Popup_locY + PFE_Popup_height - 42, PFE_Popup_imgYes_1);
			} else {
				display->Blit(PFE_Popup_locX + 76, PFE_Popup_locY + PFE_Popup_height - 42, PFE_Popup_imgYes_0);
			}
		break; }
		case PFE_POPUP_YESNO: {
			if (PFE_Popup_YesPressed) {	
				display->Blit(PFE_Popup_locX + 40, PFE_Popup_locY + PFE_Popup_height - 42, PFE_Popup_imgYes_1);
			} else {
				display->Blit(PFE_Popup_locX + 40, PFE_Popup_locY + PFE_Popup_height - 42, PFE_Popup_imgYes_0);
			}
			if (PFE_Popup_NoPressed) {
				display->Blit(PFE_Popup_locX + PFE_Popup_width - 66, PFE_Popup_locY + PFE_Popup_height - 42, PFE_Popup_imgNo_1);
			} else {
				display->Blit(PFE_Popup_locX + PFE_Popup_width - 66, PFE_Popup_locY + PFE_Popup_height - 42, PFE_Popup_imgNo_0);
			}
		break; }
	}
}


// This is called from the screen's own stylusDown handler when a popup is on the screen
void PFE_popupStylusDown(Point stylusPoint) {
	Rect buttonBounds;
	switch (PFE_Popup_currentButtonOption) {
		case PFE_POPUP_YESNO: {
			// Yes
			buttonBounds.Set(PFE_Popup_locX + 40, PFE_Popup_locY + PFE_Popup_height - 42, PFE_Popup_locX + 40 + PFE_Popup_imgYes_0->GetWidth(), PFE_Popup_locY + PFE_Popup_height - 42 + PFE_Popup_imgYes_0->GetHeight());
			if (buttonBounds.Contains(stylusPoint)) {
				PFE_Popup_YesPressed = true;
				return;
			}
			// No
			buttonBounds.Set(PFE_Popup_locX + PFE_Popup_width - 66, PFE_Popup_locY + PFE_Popup_height - 42, PFE_Popup_locX + PFE_Popup_width - 66 + PFE_Popup_imgNo_0->GetWidth(), PFE_Popup_locY + PFE_Popup_height - 42 + PFE_Popup_imgNo_0->GetHeight());
			if (buttonBounds.Contains(stylusPoint)) {
				PFE_Popup_NoPressed = true;
				return;
			}
		break; }
		case PFE_POPUP_OK: {
			buttonBounds.Set(PFE_Popup_locX + 76, PFE_Popup_locY + PFE_Popup_height - 42, PFE_Popup_locX + 76 + PFE_Popup_imgYes_0->GetWidth(), PFE_Popup_locY + PFE_Popup_height - 42 + PFE_Popup_imgYes_0->GetHeight());
			if (buttonBounds.Contains(stylusPoint)) {
				PFE_Popup_OkPressed = true;
				return;
			}
		break; }
	}
	PFE_Popup_YesPressed = false;
	PFE_Popup_NoPressed  = false;
	PFE_Popup_OkPressed	 = false;
	PFE_Popup_currentButtonOption = 0;
}


// This is called from the screen's own styludUp handler when a popup is on the screen.
// It returns 1 if the Yes button is clicked, 2 if the No button is clicked, 3 for Ok, 0 otherwise.
int PFE_popupStylusUp(Point stylusPoint) {
	Rect buttonBounds;
	int retVal = 0;
	switch (PFE_Popup_currentButtonOption) {
		case PFE_POPUP_YESNO: {
			// Yes
			buttonBounds.Set(PFE_Popup_locX + 40, PFE_Popup_locY + PFE_Popup_height - 42, PFE_Popup_locX + 40 + PFE_Popup_imgYes_0->GetWidth(), PFE_Popup_locY + PFE_Popup_height - 42 + PFE_Popup_imgYes_0->GetHeight());
			if (buttonBounds.Contains(stylusPoint) && PFE_Popup_YesPressed) {
				retVal = 1;
			}
			// No
			buttonBounds.Set(PFE_Popup_locX + PFE_Popup_width - 66, PFE_Popup_locY + PFE_Popup_height - 42, PFE_Popup_locX + PFE_Popup_width - 66 + PFE_Popup_imgNo_0->GetWidth(), PFE_Popup_locY + PFE_Popup_height - 42 + PFE_Popup_imgNo_0->GetHeight());
			if (buttonBounds.Contains(stylusPoint) && PFE_Popup_NoPressed) {
				retVal = 2;
			}
		break; }
		case PFE_POPUP_OK: {
			buttonBounds.Set(PFE_Popup_locX + 76, PFE_Popup_locY + PFE_Popup_height - 42, PFE_Popup_locX + 76 + PFE_Popup_imgYes_0->GetWidth(), PFE_Popup_locY + PFE_Popup_height - 42 + PFE_Popup_imgYes_0->GetHeight());
			if (buttonBounds.Contains(stylusPoint) && PFE_Popup_OkPressed) {
				retVal = 3;
			}
		break; }
	}
	PFE_Popup_YesPressed = false;
	PFE_Popup_NoPressed  = false;
	PFE_Popup_OkPressed	 = false;
	PFE_Popup_currentButtonOption = 0;
	return retVal;
}