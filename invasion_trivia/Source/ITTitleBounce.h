
Surface* imgInvasionTriviaTitle	 = NULL;
int			 bounceValsIndex         = 0;
int			 bounceVals[428]				 = {
				 1, 2, 4, 5, 6, 8, 9, 10, 12, 13, 14, 15, 17, 18, 19, 20, 22, 23, 24, 25, 26,
				 28, 29, 30, 31, 32, 33, 34, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47,
				 48, 49, 50, 51, 52, 52, 53, 54, 55, 56, 57, 58, 58, 59, 60, 61, 61, 62, 63, 
				 64, 64, 65, 66, 66, 67, 68, 68, 69, 69, 70, 71, 71, 72, 72, 73, 73, 74, 74,
				 74, 75, 75, 76, 76, 76, 77, 77, 77, 78, 78, 78, 79, 79, 79, 79, 79, 80, 80,
				 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80,
				 80, 80, 79, 79, 79, 79, 79, 78, 78, 78, 77, 77, 77, 76, 76, 76, 75, 75, 74,
				 74, 74, 73, 73, 72, 72, 71, 71, 70, 69, 69, 68, 68, 67, 66, 66, 65, 64, 64,
				 63, 62, 61, 61, 60, 59, 58, 58, 57, 56, 55, 54, 53, 52, 52, 51, 50, 49, 48,
				 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 34, 33, 32, 31, 30, 29, 28,
				 26, 25, 24, 23, 22, 20, 19, 18, 17, 15, 14, 13, 12, 10, 9, 8, 6, 5, 4, 2, 1,
				 -1, -2, -4, -5, -6, -8, -9, -10, -12, -13, -14, -15, -17, -18, -19, -20, -22,
				 -23, -24, -25, -26, -28, -29, -30, -31, -32, -33, -34, -36, -37, -38, -39, -40,
				 -41, -42, -43, -44, -45, -46, -47, -48, -49, -50, -51, -52, -52, -53, -54, -55,
				 -56, -57, -58, -58, -59, -60, -61, -61, -62, -63, -64, -64, -65, -66, -66, -67,
				 -68, -68, -69, -69, -70, -71, -71, -72, -72, -73, -73, -74, -74, -74, -75, -75,
				 -76, -76, -76, -77, -77, -77, -78, -78, -78, -79, -79, -79, -79, -79, -80, -80,
				 -80, -80, -80, -80, -80, -80, -80, -80, -80, -80, -80, -80, -80, -80, -80, -80,
				 -80, -80, -80, -80, -80, -79, -79, -79, -79, -79, -78, -78, -78, -77, -77, -77,
				 -76, -76, -76, -75, -75, -74, -74, -74, -73, -73, -72, -72, -71, -71, -70, -69,
				 -69, -68, -68, -67, -66, -66, -65, -64, -64, -63, -62, -61, -61, -60, -59, -58,
				 -58, -57, -56, -55, -54, -53, -52, -52, -51, -50, -49, -48, -47, -46, -45, -44,
				 -43, -42, -41, -40, -39, -38, -37, -36, -34, -33, -32, -31, -30, -29, -28, -26,
				 -25, -24, -23, -22, -20, -19, -18, -17, -15, -14, -13, -12, -10, -9, -8, -6,
				 -5, -4, -2, -1
				};


// Called to prepare the bounce
void loaderITTitleBounce(DisplayDevice* display) {
	// Load the Invasion: Trivia title graphic
	imgInvasionTriviaTitle = LoadImage(display, IDR_INVASIONTRIVIA_TITLE);
	imgInvasionTriviaTitle->SetColorMask(Color(255, 255, 255));
}


// Called to clean up after the bounce
void releaserITTitleBounce() {
	delete imgInvasionTriviaTitle;
}


// Called to perform the bounce
void doITTitleBounce(DisplayDevice* display) {
	display->Blit(bounceVals[bounceValsIndex], 10, imgInvasionTriviaTitle);
	bounceValsIndex = bounceValsIndex + 5;
	if (bounceValsIndex > 425) {
		bounceValsIndex = 0;
	}
}