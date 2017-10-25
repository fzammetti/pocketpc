
	typedef struct tagRADIOFREQUENCYSPECTRUM {
			TCHAR szFrequency[18];
			TCHAR szBandNumber[4];
		  TCHAR szClassification[40];
			TCHAR szAbbreviation[6];
	} RADIOFREQUENCYSPECTRUM;

	typedef struct tagRADIOFREQUENCYSPECTRUMCOLS {
			TCHAR szText[16];
		  int intSize;
	} RADIOFREQUENCYSPECTRUMCOLS;
  
	RADIOFREQUENCYSPECTRUMCOLS RadioFrequencySpectrumColsTable[] = {
    {TEXT("Frequency"),      100},
    {TEXT("Band No."),       70},
    {TEXT("Classification"), 170},
	  {TEXT("Abbreviation"),   80},
  };

	int numItemsRadioFrequencySpectrum = 11;

  RADIOFREQUENCYSPECTRUM RadioFrequencySpectrumTable[] = {	
		{TEXT("30 - 300 Hz"),			TEXT("2"),  TEXT("Extremely Low Frequencies"),  TEXT("ELF")},
		{TEXT("300 - 3000 Hz"),		TEXT("3"),  TEXT("Voice Frequencies"),					TEXT("VF")},
		{TEXT("3 - 30 kHz"),			TEXT("4"),  TEXT("Very Low Frequencies"),			  TEXT("VLF")},
		{TEXT("30 - 300 kHz"),		TEXT("5"),  TEXT("Low Frequencies"),						TEXT("LF")},
		{TEXT("300 - 3000 kHz"),	TEXT("6"),  TEXT("Medium Frequencies"),				  TEXT("MF")},
		{TEXT("3 - 30 MHz"),			TEXT("7"),  TEXT("High Frequencies"),					  TEXT("HF")},
		{TEXT("30 - 300 MHz"),		TEXT("8"),  TEXT("Very High Frequencies"),			TEXT("VHF")},
		{TEXT("300 - 3000 MHz"),	TEXT("9"),  TEXT("Ultra High Frequencies"),		  TEXT("UHF")},
		{TEXT("3 - 30 GHz"),			TEXT("10"), TEXT("Super High Frequencies"),		  TEXT("SHF")},
		{TEXT("30 - 300 GHz"),		TEXT("11"), TEXT("Extremely High Frequencies"), TEXT("EHF")},
		{TEXT("300 GHz - 3 THz"), TEXT("12"), TEXT("----------"),								  TEXT("---")}
  };