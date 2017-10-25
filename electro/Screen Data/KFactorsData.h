
	typedef struct tagKFACTORS {
		  TCHAR szDB[12];
			TCHAR szK[12];
	}		KFACTORS;

	typedef struct tagKFACTORSCOLS	{
		  TCHAR szText[32];
			int intSize;
	} KFACTORSCOLS;

  KFACTORSCOLS KFactorsColsTable[] = {
    {TEXT("dB"),   75}, 
    {TEXT("K"),    75} 
  };

	int numItemsKFactors = 78;

  KFACTORS KFactorsTable[] = {
    {TEXT("0.05"),  TEXT("1.0058")},
    {TEXT("0.1"),   TEXT("1.0116")},
    {TEXT("0.5"),   TEXT("1.0593")},
    {TEXT("1.0"),   TEXT("1.1220")},
    {TEXT("1.5"),   TEXT("1.1885")},
    {TEXT("2.0"),   TEXT("1.2589")},
    {TEXT("2.5"),   TEXT("1.3335")},
    {TEXT("3.0"),   TEXT("1.4125")},
    {TEXT("3.5"),   TEXT("1.4962")},
    {TEXT("4.0"),   TEXT("1.5849")},
    {TEXT("4.5"),   TEXT("1.6788")},
    {TEXT("5.0"),   TEXT("1.7783")},
    {TEXT("5.5"),   TEXT("1.8837")},
    {TEXT("6.0"),   TEXT("1.9953")},
    {TEXT("6.5"),   TEXT("2.1135")},
    {TEXT("7.0"),   TEXT("2.2387")},
    {TEXT("7.5"),   TEXT("2.3714")},
    {TEXT("8.0"),   TEXT("2.5118")},
    {TEXT("8.5"),   TEXT("2.6607")},
    {TEXT("9.0"),   TEXT("2.8184")},
    {TEXT("9.5"),   TEXT("2.9854")},
    {TEXT("10.0"),  TEXT("3.1623")},
    {TEXT("11.0"),  TEXT("3.5481")},
    {TEXT("12.0"),  TEXT("3.9811")},
    {TEXT("13.0"),  TEXT("4.4668")},
    {TEXT("14.0"),  TEXT("5.0119")},
    {TEXT("15.0"),  TEXT("5.6234")},
    {TEXT("16.0"),  TEXT("6.3096")},
    {TEXT("17.0"),  TEXT("7.0795")},
    {TEXT("18.0"),  TEXT("7.9433")},
    {TEXT("19.0"),  TEXT("8.9125")},
    {TEXT("20.0"),  TEXT("10.0000")},
    {TEXT("21.0"),  TEXT("11.2202")},
    {TEXT("22.0"),  TEXT("12.589")},
    {TEXT("23.0"),  TEXT("14.125")},
    {TEXT("24.0"),  TEXT("15.849")},
    {TEXT("25.0"),  TEXT("17.783")},
    {TEXT("26.0"),  TEXT("19.953")},
    {TEXT("27.0"),  TEXT("22.387")},
    {TEXT("28.0"),  TEXT("25.119")},
    {TEXT("29.0"),  TEXT("28.184")},
    {TEXT("30.0"),  TEXT("31.623")},
    {TEXT("31.0"),  TEXT("35.481")},
    {TEXT("32.0"),  TEXT("39.811")},
    {TEXT("33.0"),  TEXT("44.668")},
    {TEXT("34.0"),  TEXT("50.119")},
    {TEXT("35.0"),  TEXT("56.234")},
    {TEXT("36.0"),  TEXT("63.096")},
    {TEXT("37.0"),  TEXT("70.795")},
    {TEXT("38.0"),  TEXT("79.433")},
    {TEXT("39.0"),  TEXT("89.125")},
    {TEXT("40.0"),  TEXT("100.000")},
    {TEXT("41.0"),  TEXT("112.202")},
    {TEXT("42.0"),  TEXT("125.89")},
    {TEXT("43.0"),  TEXT("141.25")},
    {TEXT("44.0"),  TEXT("158.49")},
    {TEXT("45.0"),  TEXT("177.83")},
    {TEXT("46.0"),  TEXT("199.53")},
    {TEXT("47.0"),  TEXT("223.87")},
    {TEXT("48.0"),  TEXT("251.19")},
    {TEXT("49.0"),  TEXT("281.84")},
    {TEXT("50.0"),  TEXT("316.23")},
    {TEXT("51.0"),  TEXT("354.81")},
    {TEXT("52.0"),  TEXT("398.11")},
    {TEXT("54.0"),  TEXT("501.19")},
    {TEXT("55.0"),  TEXT("562.34")},
    {TEXT("56.0"),  TEXT("630.96")},
    {TEXT("57.0"),  TEXT("707.95")},
    {TEXT("58.0"),  TEXT("794.33")},
    {TEXT("60.0"),  TEXT("1000.0")},
    {TEXT("65.0"),  TEXT("1778.3")},
    {TEXT("70.0"),  TEXT("3162.3")},
    {TEXT("75.0"),  TEXT("5623.4")},
    {TEXT("80.0"),  TEXT("10000")},
    {TEXT("85.0"),  TEXT("17783")},
    {TEXT("90.0"),  TEXT("31623")},
    {TEXT("95.0"),  TEXT("56234")},
    {TEXT("100.0"), TEXT("100000")}
  };
