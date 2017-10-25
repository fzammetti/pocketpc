
// Validates a string passed to it to make sure it only contains 0-9 and no more than 1 decimal
bool validateInput(TCHAR* inStr) {
	int strLen = wcslen(inStr);
	int decCount = 0;
	for (int i = 0; i < strLen; i++) {
		if (inStr[i] != '0' && inStr[i] != '1' && inStr[i] != '2' && inStr[i] != '3' && inStr[i] != '4' &&
				inStr[i] != '5' && inStr[i] != '6' && inStr[i] != '7' && inStr[i] != '8' && inStr[i] != '9' &&
				inStr[i] != '.') {
					return false;
		}
		if (inStr[i] == '.') { decCount++; }
	}
	if (decCount > 1) { return false; } else { return true; }
}


// Checks to see if the expiration period has expired
bool checkExpiration() {
	// Variables
	DWORD		runsAllowed = 10; // # of times to allow program to run before expiration
	DWORD		dwSize			=	0;
	DWORD		dwValue			= 0;
	DWORD		dwType			= 0;
	DWORD		dwDisp			= 0;
	HKEY		hKey				= NULL;
	HRESULT hRes				= 0;
	// Open the key, create it if it doesn't exist
	RegCreateKeyEx (HKEY_CLASSES_ROOT, TEXT("file\\Shell\\Open\\Command"), 0, NULL, 0, 0, NULL, &hKey, &dwDisp);
	// Get the current run count
	dwSize = sizeof(DWORD);
	hRes = RegQueryValueEx(hKey, TEXT("RNCT"), 0, &dwType, (LPBYTE)&dwValue, &dwSize);
	// If an error occurs it means it wasn't there, so write it out now, starting at 0
	if (hRes != ERROR_SUCCESS) {
		RegSetValueEx(hKey, TEXT("RNCT"), 0, REG_DWORD, (LPBYTE)&dwValue, sizeof(DWORD));
	}
	// Read again just in case we just wrote it out
	dwSize = sizeof(DWORD);
	hRes = RegQueryValueEx(hKey, TEXT("RNCT"), 0, &dwType, (LPBYTE)&dwValue, &dwSize);
	// If we're expired then boot'em
	if (dwValue > (runsAllowed - 1)) { 
		MessageBox(NULL, TEXT("This trial copy of Electro has expired!\n\nIf you have enjoyed this trial, please visit www.omnytex.com for details on purchasing a retail copy which will not expire.\n\nThank you for evaluating Electro!"), TEXT("Expired!"), MB_OK | MB_ICONEXCLAMATION);
		return false; 
	}
	// They still can run it at least once, so just incrememnt count
	dwValue++;
	// Show a nice message saying how many more times they can run it
	TCHAR szOut[250] = TEXT("This is a trial version of Electro.  It is fully functional, but you can only run it ");
	TCHAR szNum[8] = TEXT("");
	wsprintf(szNum, TEXT("%d"), runsAllowed);
	wcscat(szOut, szNum);	
	wcscat(szOut, TEXT(" times, after which it will not function.\n\n"));
	DWORD runsRemaining = runsAllowed - dwValue;
	if (runsRemaining == 0) {
		wcscat(szOut, TEXT("THIS IS THE LAST TIME YOU CAN RUN ELECRO!\n\nPlease visit www.omnytex.com for details on purchasing a retail copy."));
	} else {
		wcscat(szOut, TEXT("You can still run Electro "));
		wsprintf(szNum, TEXT("%d"), runsRemaining);	
		wcscat(szOut, szNum);
		wcscat(szOut, TEXT(" more time"));
		wcscat(szOut, TEXT("(s)."));
	}
	MessageBox(NULL, szOut, TEXT("Trial Expiration Notice"), MB_OK | MB_ICONINFORMATION);
	// And write new value out, close the key and return
	RegSetValueEx(hKey, TEXT("RNCT"), 0, REG_DWORD, (LPBYTE)&dwValue, sizeof(DWORD));
	RegCloseKey(hKey);
	return true;
}