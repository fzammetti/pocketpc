
	typedef struct tagMETALALLOYSRESISTANCES {
			TCHAR szMaterial[32];
			TCHAR szSymbol[32];
		  TCHAR szResistance[32];
	} METALALLOYSRESISTANCES;

	typedef struct tagMETALALLOYSRESISTANCESCOLS {
			TCHAR szText[32];
		  int intSize;
	} METALALLOYSRESISTANCESCOLS;
  
	METALALLOYSRESISTANCESCOLS MetalAlloyResistancesColsTable[] = {
    {TEXT("Material"),    100}, 
    {TEXT("Symbol"),      60}, 
    {TEXT("Resistance"),  70}
  };

	int numItemsMetalAlloyResistances = 37;

  METALALLOYSRESISTANCES MetalAlloyResistancesTable[] = {
    {TEXT("Nichrome"),          TEXT("Ni-Fe-Cr"),     TEXT("675")},
    {TEXT("Tophet A"),          TEXT("Ni-Cr"),        TEXT("659")},
    {TEXT("Tophet A"),          TEXT("Ni-Cr"),        TEXT("659")},
    {TEXT("Nichrome V"),        TEXT("Ni-Cr"),        TEXT("650")},
    {TEXT("Chromax"),           TEXT("Cr-Ni-Fe"),     TEXT("610")},
    {TEXT("Steel, Stainless"),  TEXT("C-Cr-Ni-Fe"),   TEXT("549")},
    {TEXT("Chromel"),           TEXT("Ni-Cr"),        TEXT("427")},
    {TEXT("Steel, Manganese"),  TEXT("Mn-C-Fe"),      TEXT("427")},
    {TEXT("Kovar A"),           TEXT("Ni-Co-Mn-Fe"),  TEXT("1732")},
    {TEXT("Titanium"),          TEXT("Ti"),           TEXT("292")},
    {TEXT("Constantan"),        TEXT("Cu-Ni"),        TEXT("270")},
    {TEXT("Manganin"),          TEXT("Cu-Mn-Ni"),     TEXT("268")},
    {TEXT("Monel"),             TEXT("Ni-Cu-Fe-Mn"),  TEXT("256")},
    {TEXT("Arsenic"),           TEXT("As"),           TEXT("214")},
    {TEXT("Alumel"),            TEXT("Ni-Al-Mn-Si"),  TEXT("203")},
    {TEXT("Nickel-Silver"),     TEXT("Cu-Zn-Ni"),     TEXT("171")},
    {TEXT("Lead"),              TEXT("Pb"),           TEXT("134")},
    {TEXT("Steel"),             TEXT("C-Fe"),         TEXT("103")},
    {TEXT("Manganese-Nickel"),  TEXT("Ni-Mn"),        TEXT("85")},
    {TEXT("Tantalum"),          TEXT("Ta"),           TEXT("79.9")},
    {TEXT("Tin"),               TEXT("Sn"),           TEXT("69.5")},
    {TEXT("Palladium"),         TEXT("Pd"),           TEXT("65.9")},
    {TEXT("Platinum"),          TEXT("Pt"),           TEXT("63.8")},
    {TEXT("Iron"),              TEXT("Fe"),           TEXT("60.14")},
    {TEXT("Nickel, Pure"),      TEXT("Ni"),           TEXT("60")},
    {TEXT("Phosphor-Bronze"),   TEXT("Sn-P-Cu"),      TEXT("57.38")},
    {TEXT("High-Brass"),        TEXT("Cu-Zn"),        TEXT("50")},
    {TEXT("Potassium"),         TEXT("K"),            TEXT("42.7")},
    {TEXT("Molybdenum"),        TEXT("Mo"),           TEXT("34.27")},
    {TEXT("Tungsten"),          TEXT("W"),            TEXT("33.22")},
    {TEXT("Rhodium"),           TEXT("Rh"),           TEXT("31")},
    {TEXT("Aluminum"),          TEXT("Al"),           TEXT("16.06")},
    {TEXT("Chromium"),          TEXT("Cr"),           TEXT("15.87")},
    {TEXT("Gold"),              TEXT("Au"),           TEXT("14.55")},
    {TEXT("Copper"),            TEXT("Cu"),           TEXT("10.37")},
    {TEXT("Silver"),            TEXT("Ag"),           TEXT("9.706")},
    {TEXT("Selenium"),          TEXT("Se"),           TEXT("7.3")}
  };