
	typedef struct tagDIALECTRICCONSTANTS {
		  TCHAR szMaterial[32];
			TCHAR szDCLower[16];
			TCHAR szDCUpper[16];
	}		DIALECTRICCONSTANTS;

	typedef struct tagDIALECTRICCONSTANTSCOLS	{
		  TCHAR szText[32];
			int intSize;
	} DIALECTRICCONSTANTSCOLS;

  DIALECTRICCONSTANTSCOLS DialectricConstantsColsTable[] = {
    {TEXT("Material"), 110}, 
    {TEXT("Lower"),    60}, 
    {TEXT("Upper"),    60} 
  };

	int numItemsDialectricConstants = 63;

  DIALECTRICCONSTANTS DialectricConstantsTable[] = {
    {TEXT("Air"),                          TEXT("1.0"),  TEXT("1.0")},
    {TEXT("Amber"),                        TEXT("2.6"),  TEXT("2.7")},
    {TEXT("Asbestor Fiber"),               TEXT("3.1"),  TEXT("4.8")},
    {TEXT("Bakelite (Asbestos-based)"),    TEXT("5.0"),  TEXT("22")},
    {TEXT("Bakelite (Mica-filled)"),       TEXT("4.5"),  TEXT("4.8")},
    {TEXT("Barium Titanate"),              TEXT("100"),  TEXT("1250")},
    {TEXT("Beeswax"),                      TEXT("2.4"),  TEXT("2.8")},
    {TEXT("Cambric (Varnished)"),          TEXT("4.0"),  TEXT("4.0")},
    {TEXT("Carbon Tetrachloride"),         TEXT("2.17"), TEXT("2.17")},
    {TEXT("Celluloid"),                    TEXT("4.0"),  TEXT("4.0")},
    {TEXT("Cellulose Acetate"),            TEXT("2.9"),  TEXT("4.5")},
    {TEXT("Durite"),                       TEXT("4.7"),  TEXT("5.1")},
    {TEXT("Ebonite"),                      TEXT("2.7"),  TEXT("2.7")},
    {TEXT("Epoxy Resin"),                  TEXT("3.4"),  TEXT("3.7")},
    {TEXT("Ethyl Alcohol (Absolute)"),     TEXT("6.5"),  TEXT("25")},
    {TEXT("Fiber"),                        TEXT("5.0"),  TEXT("5.0")},
    {TEXT("Formica"),                      TEXT("3.6"),  TEXT("6.0")},
    {TEXT("Glass (Electrical)"),           TEXT("3.8"),  TEXT("14.5")},
    {TEXT("Glass (Photographic)"),         TEXT("7.5"),  TEXT("7.5")},
    {TEXT("Glass (Pyrex)"),                TEXT("4.6"),  TEXT("5.0")},
    {TEXT("Glass (Window)"),               TEXT("7.6"),  TEXT("7.6")},
    {TEXT("Gutta Percha"),                 TEXT("2.4"),  TEXT("2.6")},
    {TEXT("Isolantite"),                   TEXT("6.1"),  TEXT("6.1")},
    {TEXT("Lucite"),                       TEXT("2.5"),  TEXT("2.5")},
    {TEXT("Mica (Electrical)"),            TEXT("4.0"),  TEXT("9.0")},
    {TEXT("Mica (Clear India)"),           TEXT("7.5"),  TEXT("7.5")},
    {TEXT("Mica (Filled Phenolic)"),       TEXT("4.2"),  TEXT("5.2")},
    {TEXT("Micaglass (Titaniun Dioxide)"), TEXT("9.0"),  TEXT("9.3")},
    {TEXT("Micarta"),                      TEXT("3.2"),  TEXT("5.5")},
    {TEXT("Mycalex"),                      TEXT("7.3"),  TEXT("9.3")},
    {TEXT("Mylar"),                        TEXT("4.7"),  TEXT("4.7")},
    {TEXT("Neoprene"),                     TEXT("4.0"),  TEXT("6.7")},
    {TEXT("Nylon"),                        TEXT("3.4"),  TEXT("22.4")},
    {TEXT("Paper (Dry)"),                  TEXT("1.5"),  TEXT("3.0")},
    {TEXT("Paper (Paraffin Coated)"),      TEXT("2.5"),  TEXT("4.0")},
    {TEXT("Paraffin (Solid)"),             TEXT("2.0"),  TEXT("3.0")},
    {TEXT("Plexiglas"),                    TEXT("2.6"),  TEXT("3.5")},
    {TEXT("Polycarbonate"),                TEXT("2.9"),  TEXT("3.2")},
    {TEXT("Polyethylene"),                 TEXT("2.5"),  TEXT("2.5")},
    {TEXT("Polyimide"),                    TEXT("3.4"),  TEXT("3.5")},
    {TEXT("Polystyrene"),                  TEXT("2.4"),  TEXT("3.0")},
    {TEXT("Porcelain (Dry Process)"),      TEXT("5.0"),  TEXT("6.5")},
    {TEXT("Porcelain (Wet Process)"),      TEXT("5.8"),  TEXT("6.5")},
    {TEXT("Quartz"),                       TEXT("5.0"),  TEXT("5.0")},
    {TEXT("Quartz (Fused)"),               TEXT("3.78"), TEXT("3.78")},
    {TEXT("Rubber (Hard)"),                TEXT("2.0"),  TEXT("4.0")},
    {TEXT("Ruby Mica"),                    TEXT("5.4"),  TEXT("5.4")},
    {TEXT("Selenium (Amorphous)"),         TEXT("6.0"),  TEXT("6.0")},
    {TEXT("Shellac (Natural)"),            TEXT("2.9"),  TEXT("3.9")},
    {TEXT("Silicone (Glass, Molding)"),    TEXT("3.2"),  TEXT("4.7")},
    {TEXT("Silicone (Glass, Laminate)"),   TEXT("3.7"),  TEXT("4.3")},
    {TEXT("Slate"),                        TEXT("7.0"),  TEXT("7.0")},
    {TEXT("Soil (Dry)"),                   TEXT("2.4"),  TEXT("2.9")},
    {TEXT("Steatite (Ceramic)"),           TEXT("5.2"),  TEXT("6.3")},
    {TEXT("Steatite (Low Loss)"),          TEXT("4.4"),  TEXT("4.4")},
    {TEXT("Styrofoam"),                    TEXT("1.03"), TEXT("1.03")},
    {TEXT("Teflon"),                       TEXT("2.1"),  TEXT("2.1")},
    {TEXT("Titanium Dioxide"),             TEXT("100"),  TEXT("100")},
    {TEXT("Vaseline"),                     TEXT("2.16"), TEXT("2.16")},
    {TEXT("Vinylite"),                     TEXT("2.7"),  TEXT("7.5")},
    {TEXT("Water (Distilled)"),            TEXT("34"),   TEXT("78")},
    {TEXT("Mineral Waxes"),                TEXT("2.2"),  TEXT("2.3")},
    {TEXT("Wood (Dry)"),                   TEXT("1.4"),  TEXT("2.9")}
  };
