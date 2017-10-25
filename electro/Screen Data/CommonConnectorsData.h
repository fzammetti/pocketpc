
	typedef struct tagCOMMONCONNECTORS {
			TCHAR szTitle[64];
			int ResourceID;
			int imgWidth;
			int imgHeight;
	} COMMONCONNECTORS;

	int numCommonConnectors = 45;

  COMMONCONNECTORS CommonConnectorsTable[] = {
		{TEXT("Centronics 36-Pin Female"),						IDB_CENTRONICS_36_FEMALE,								 188, 73},
		{TEXT("Centronics 36-Pin Male"),							IDB_CENTRONICS_36_MALE,									 188, 71},
		{TEXT("Centronics 50-Pin Female"),						IDB_CENTRONICS_50_FEMALE,								 224, 66},
		{TEXT("Centronics 50-Pin Male"),							IDB_CENTRONICS_50_MALE,									 224, 67},
		{TEXT("Coaxial Female"),											IDB_COAX_FEMALE,												 44,  44},
		{TEXT("Coaxial Male"),												IDB_COAX_MALE,													 44,  43},
		{TEXT("DB9 Female"),													IDB_DB9_FEMALE,													 78,  72},
		{TEXT("DB9 Male"),														IDB_DB9_MALE,														 78,  71},
		{TEXT("DB15 High-Density Female"),						IDB_HIGH_DENSITY_DB15_FEMALE,						 108, 72},
		{TEXT("DB15 High-Density Male"),							IDB_HIGH_DENSITY_DB15_MALE,							 110, 70},
		{TEXT("DB25 Female"),													IDB_DB25_FEMALE,												 206, 70},
		{TEXT("DB25 Male"),														IDB_DB25_MALE,													 206, 71},
		{TEXT("DB37 Female"),													IDB_DB37_FEMALE,												 236, 60},
		{TEXT("DB37 Male"),														IDB_DB37_MALE,													 234, 60},
		{TEXT("DB50 Female"),													IDB_DB50_FEMALE,												 236, 69},
		{TEXT("DB50 Male"),														IDB_DB50_MALE,													 234, 67},
		{TEXT("DB50 Mini Female"),										IDB_MINI_DB_50_FEMALE,									 162, 69},
		{TEXT("DB50 Mini Male"),											IDB_MINI_DB_50_MALE,										 170, 67},
		{TEXT("DB68 Mini Female"),										IDB_MINI_DB68_FEMALE,										 204, 66},
		{TEXT("DB68 Mini Male"),											IDB_MINI_DB68_MALE,											 204, 62},
		{TEXT("Fiber Guide (FDDI)"),									IDB_FIBER_GUIDE_FDDI,										 80, 151},
		{TEXT("Fiber Guide (SC)"),										IDB_FIBER_GUIDE_SC,											 34, 150},
		{TEXT("Fiber Guide (ST)"),										IDB_FIBER_GUIDE_ST,											 38, 161},
		{TEXT("Flat Ribbon 50-Position Edge Socket"), IDB_FLAT_RIBBON_50_POSITION_EDGE_SOCKET, 238, 54},
		{TEXT("Flat Ribbon 50-Position IDC Socket"),  IDB_FLAT_RIBBON_IDC_50_POSITION_SOCKET,	 234, 44},
		{TEXT("Infoport Series 1"),										IDB_INFOPORT_SERIES_I,									 194, 30},
		{TEXT("Infoport Series 2"),										IDB_INFOPORT_SERIES_II,									 184, 32},
		{TEXT("InfoPort Series 3 (Keying Option 1)"), IDB_INFOPORT_SERIES_III_KEYING_OPTION_1, 122, 31},
		{TEXT("Infoport Series 3 (Keying Option 2)"), IDB_INFOPORT_SERIES_III_KEYING_OPTION_2, 122, 31},
		{TEXT("Infoport Series 3 (Keying Option 3)"), IDB_INFOPORT_SERIES_III_KEYING_OPTION_3, 122, 31},
		{TEXT("Infoport Series 3 (Keying Option 4)"), IDB_INFOPORT_SERIES_III_KEYING_OPTION_4, 122, 31},
		{TEXT("Mini Centronics 36-Pin Female"),				IDB_MINI_CENTRONICS_36_FEMALE,					 142, 67},
		{TEXT("Mini Centronics 36-Pin Male"),					IDB_MINI_CENTRONICS_36_MALE,						 140, 64},
		{TEXT("Mini Centronics 50-Pin Female"),				IDB_MINI_CENTRONICS_50_FEMALE,					 168, 62},
		{TEXT("Mini Centronics 50-Pin Male"),					IDB_MINI_CENTRONICS_50_MALE,						 168, 61},
		{TEXT("Mini Centronics 60-Pin Female"),				IDB_MINI_CENTRONICS_60_FEMALE,					 192, 59},
		{TEXT("Mini Centronics 60-Pin Male"),					IDB_MINI_CENTRONICS_60_MALE,						 192, 60},
		{TEXT("Modular DEC (6P6C)"),									IDB_MODULAR_DEC_6P6C,										 218, 109},
		{TEXT("Modular RJ11 (6P4C)"),									IDB_MODULAR_RJ11_6P4C,									 218, 104},
		{TEXT("Modular RJ12 (6P6C)"),									IDB_MODULAR_RJ12_6P6C,									 234, 104},
		{TEXT("Modular RJ45"),												IDB_MODULAR_RJ45,												 228, 105},
		{TEXT("Monitor Power Adapter"),								IDB_MONITOR_POWER_ADAPTER,							 216, 118},
		{TEXT("Power Cord"),													IDB_POWER_CORD,													 218, 104},
		{TEXT("Power Extension Cord"),								IDB_POWER_EXTENSION_CORD,								 214, 63},
		{TEXT("SCSI Connector (VHDCI)"),							IDB_SCSI_CONNECTOR_VHDCI,								 184, 49}
};