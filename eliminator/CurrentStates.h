int CurrentStates[11][11];

void loadCurrentStates() {

	for (int y = 1; y < 11; y++) {
		for (int x = 1; x < 11; x++) {
			CurrentStates[y][x] = Patterns[pattern_index][y][x];
		}
	}

}
