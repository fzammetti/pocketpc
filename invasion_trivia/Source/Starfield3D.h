
float stars[302][7]; // 3-D starfield stars
int	  starVariant[302];
int	  starColors[302];


// Called once to initialize the starfield
void initStarfield3D() {
	// Initialize stars for 3-D starfield
	for (unsigned short int i = 1; i < 295; i++) {
		stars[i][0] = (float)(rand() % 70 - 35);
		stars[i][1] = (float)(rand() % 70 - 35);
		stars[i][2] = (float)(rand() % 100 + 1);
		starVariant[i] = (rand() * (4)) / (RAND_MAX + 1);
		starColors[i] = 255;
	}
}


// Called to update and display the starfield
void doStarfield3D(DisplayDevice* display) {
	int i;
	// Move the stars
	for (i = 1; i < 295; i++) {
		stars[i][2] -= 3;
		if (stars[i][2] <= 10) {  // Re-initialize if star is too close
			stars[i][0] = (float)(rand() % 70 - 35);
			stars[i][1] = (float)(rand() % 70 - 35);
			stars[i][2] = (float)(rand() % 100 + 1);
			starVariant[i] = (rand() * (4)) / (RAND_MAX + 1);
			starColors[i] = 0;
		} 
		stars[i][3] = (stars[i][0] / stars[i][2]) * 238 + (238 >> 1);
		stars[i][4] = (stars[i][1] / stars[i][2]) * 318 + (318 >> 1);
		starColors[i] = starColors[i] + 20;
		if (starColors[i] > 255) { starColors[i] = 255; }
	}
	// Draw the stars in their new positions
	for (i = 1; i < 295; i++) {
		int starCol = starColors[i];
		switch (starVariant[i]) {
			case 1:
				display->SetPixel((unsigned short int)stars[i][3], (unsigned short int)stars[i][4], Color(starCol, starCol, starCol));
				display->SetPixel((unsigned short int)stars[i][3] + 1, (unsigned short int)stars[i][4], Color(starCol, starCol, starCol));
				display->SetPixel((unsigned short int)stars[i][3] - 1, (unsigned short int)stars[i][4], Color(starCol, starCol, starCol));
				display->SetPixel((unsigned short int)stars[i][3], (unsigned short int)stars[i][4] - 1, Color(starCol, starCol, starCol));
				display->SetPixel((unsigned short int)stars[i][3], (unsigned short int)stars[i][4] + 1, Color(starCol, starCol, starCol));
			break;
			case 2:
				display->SetPixel((unsigned short int)stars[i][3], (unsigned short int)stars[i][4], Color(starCol, starCol, starCol));
				display->SetPixel((unsigned short int)stars[i][3] + 1, (unsigned short int)stars[i][4], Color(starCol, starCol, starCol));
				display->SetPixel((unsigned short int)stars[i][3], (unsigned short int)stars[i][4] + 1, Color(starCol, starCol, starCol));
				display->SetPixel((unsigned short int)stars[i][3] + 1, (unsigned short int)stars[i][4] + 1, Color(starCol, starCol, starCol));
			break;
			case 3:
				display->SetPixel((unsigned short int)stars[i][3] + 1, (unsigned short int)stars[i][4], Color(starCol, starCol, starCol));
				display->SetPixel((unsigned short int)stars[i][3] - 1, (unsigned short int)stars[i][4], Color(starCol, starCol, starCol));
				display->SetPixel((unsigned short int)stars[i][3], (unsigned short int)stars[i][4] - 1, Color(starCol, starCol, starCol));
				display->SetPixel((unsigned short int)stars[i][3], (unsigned short int)stars[i][4] + 1, Color(starCol, starCol, starCol));
			break;
			default:
				display->SetPixel((unsigned short int)stars[i][3], (unsigned short int)stars[i][4], Color(starCol, starCol, starCol));
			break;
		}
	}
}