
	typedef struct tagOPAMPS {
			TCHAR szTitle[64];
			int		ResourceID;
	} OPAMPS;

	int numOpAmps = 6;

  OPAMPS OpAmpsTable[] = {
		{TEXT("Adding, Subtracting And Scaling Amplifier"),	IDB_OPAMP_ADDING_SUBTRACTING_SCALING_AMPLIFIER},
		{TEXT("Differential Input Amplifier"),							IDB_OPAMP_DIFFERENTIAL_INPUT_AMPLIFIER},
		{TEXT("Differentiating Input Amplifier"),						IDB_OPAMP_DIFFERENTIATING_INPUT_AMPLIFIER},
		{TEXT("Inverting Amplifier"),												IDB_OPAMP_INVERTING_AMPLIFIER},
		{TEXT("Non-Inverting Amplifier"),										IDB_OPAMP_NONINVERTING_AMPLIFIER},
		{TEXT("Voltage Follower"),													IDB_OPAMP_VOLTAGE_FOLLOWER}
};