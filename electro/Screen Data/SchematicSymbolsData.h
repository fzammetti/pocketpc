	
	typedef struct tagSCHEMATICSYMBOLS {
			TCHAR szSymbolText[64];
			TCHAR intSymbolID;
	} SCHEMATICSYMBOLS;

	int numItemsSchematicSymbols = 144;

  SCHEMATICSYMBOLS SchematicSymbolsTable[] = {
		{TEXT("Ammeter"),																		 IDI_SCHEM_AMMETER},
		{TEXT("And Gate"),																	 IDI_SCHEM_AND_GATE},
		{TEXT("Antenna, Balanced"),													 IDI_SCHEM_ANTENNA_BALANCED},
		{TEXT("Antenna, General"),												   IDI_SCHEM_ANTENNA_GENERAL1},
		{TEXT("Antenna, Loop, Shielded"),										 IDI_SCHEM_ANTENNA_GENERAL2},
		{TEXT("Antenna, Loop, Unshielded"),									 IDI_SCHEM_ANTENNA_LOOP_SHIELDED},
		{TEXT("Antenna, Unbalanced"),												 IDI_SCHEM_ANTENNA_LOOP_UNSHIELDED},
		{TEXT("Antenna, Unbalanced (Alternate)"),						 IDI_SCHEM_ANTENNA_UNBALANCED1},
		{TEXT("Attenuator, Fixed"),													 IDI_SCHEM_ANTENNA_UNBALANCED2},
		{TEXT("Attenuator, Variable"),											 IDI_SCHEM_ATTENUATOR_FIXED},
		{TEXT("Battery"),																		 IDI_SCHEM_ATTENUATOR_VARIABLE},
		{TEXT("Capacitor, Feedthrough"),										 IDI_SCHEM_BATTERY},
		{TEXT("Capacitor, Fixed, Nonpolarized"),             IDI_SCHEM_CAPACITOR_FEEDTHROUGH},
		{TEXT("Capacitor, Fixed, Polarized"),								 IDI_SCHEM_CAPACITOR_FIXED_NOPOLES},
		{TEXT("Capacitor, Ganged, Variable"),							   IDI_SCHEM_CAPACITOR_FIXED_POLES},
		{TEXT("Capacitor, General"),												 IDI_SCHEM_CAPACITOR_GANGED_VARIABLE},
		{TEXT("Capacitor, General (Alternate)"),						 IDI_SCHEM_CAPACITOR_GENERAL},
		{TEXT("Capacitor, Variable, Single"),								 IDI_SCHEM_CAPACITOR_VARIABLE_SINGLE},
		{TEXT("Capacitor, Variable, Split-Stator"),					 IDI_SCHEM_CAPACITOR_VARIABLE_SPLIT_STATOR},
		{TEXT("Cathode, Cold"),															 IDI_SCHEM_CATHODE_COLD},
		{TEXT("Cathode, Directly Heated"),									 IDI_SCHEM_CATHODE_DIRECTLY_HEATED},
		{TEXT("Cathode, Indirectly Heated"),								 IDI_SCHEM_CATHODE_INDIRECTLY_HEATED1},
		{TEXT("Cathode, Indirectly Heated (Alternate)"),		 IDI_SCHEM_CATHODE_INDIRECTLY_HEATED2},
		{TEXT("Cavity Resonator"),													 IDI_SCHEM_CAVITY_RESONATOR},
		{TEXT("Cell"),																			 IDI_SCHEM_CELL},
		{TEXT("Circuit Breaker"),														 IDI_SCHEM_CIRCUIT_BREAKER},
		{TEXT("Coaxial Cable"),															 IDI_SCHEM_COAXIAL_CABLE1},
		{TEXT("Coaxial Cable (Alternate)"),									 IDI_SCHEM_COAXIAL_CABLE2},
		{TEXT("Crystal, Piezoelectric"),										 IDI_SCHEM_CRYSTAL_PIEZOELECTRIC},
		{TEXT("Delay Line"),																 IDI_SCHEM_DELAY_LINE1},
		{TEXT("Delay Line (Alternate)"),										 IDI_SCHEM_DELAY_LINE2},
		{TEXT("Diode, General"),														 IDI_SCHEM_DIODE_GENERAL},
		{TEXT("Diode, Gunn"),																 IDI_SCHEM_DIODE_GUNN},
		{TEXT("Diode, Light emitting"),											 IDI_SCHEM_DIODE_LIGHT_EMITTING},
		{TEXT("Diode, Photo sensitive"),										 IDI_SCHEM_DIODE_PHOTOSENSITIVE},
		{TEXT("Diode, Photovoltaic"),												 IDI_SCHEM_DIODE_PHOTOVOLTAIC},
		{TEXT("Diode, Pin"),																 IDI_SCHEM_DIODE_PIN},
		{TEXT("Diode, Varactor"),														 IDI_SCHEM_DIODE_VARACTOR},
		{TEXT("Diode, Zener"),															 IDI_SCHEM_DIODE_ZENER},
		{TEXT("Directional Coupler"),												 IDI_SCHEM_DIRECTIONAL_COUPLER1},
		{TEXT("Directional Coupler (Alternate)"),						 IDI_SCHEM_DIRECTIONAL_COUPLER2},
		{TEXT("Exclusive-Or Gate"),													 IDI_SCHEM_EXCLUSIVE_OR_GATE},
		{TEXT("Female Contact, General"),										 IDI_SCHEM_FEMALE_CONTACT_GENERAL},
		{TEXT("Ferrite Bead"),															 IDI_SCHEM_FERRITE_BEAD1},
		{TEXT("Ferrite Bead (Alternate)"),									 IDI_SCHEM_FERRITE_BEAD2},
		{TEXT("Fuse"),																			 IDI_SCHEM_FUSE1},
		{TEXT("Fuse (Alternate)"),													 IDI_SCHEM_FUSE2},
		{TEXT("Galvanometer"),															 IDI_SCHEM_GALVANOMETER1},
		{TEXT("Galvanometer (Alternate)"),									 IDI_SCHEM_GALVANOMETER2},
		{TEXT("Ground, Chassis"),														 IDI_SCHEM_GROUND_CHASSIS1},
		{TEXT("Ground, Chassis (Alternate)"),								 IDI_SCHEM_GROUND_CHASSIS2},
		{TEXT("Ground, Earth"),															 IDI_SCHEM_GROUND_EARTH},
		{TEXT("Handset"),											 	  				   IDI_SCHEM_HANDSET},
		{TEXT("Headphone, Double"),													 IDI_SCHEM_HEADPHONE_DOUBLE},
		{TEXT("Headphone, Single"),													 IDI_SCHEM_HEADPHONE_SINGLE},
		{TEXT("Inductor, Air-Core"),												 IDI_SCHEM_INDUCTOR_AIR_CORE},
		{TEXT("Inductor, Bifilar"),													 IDI_SCHEM_INDUCTOR_BIFILAR},
		{TEXT("Inductor, Iron-Core"),												 IDI_SCHEM_INDUCTOR_IRON_CORE},
		{TEXT("Inductor, Tapped"),													 IDI_SCHEM_INDUCTOR_TAPPED},
		{TEXT("Inductor, Variable"),												 IDI_SCHEM_INDUCTOR_VARIABLE1},
		{TEXT("Inductor, Variable (Alternate)"),						 IDI_SCHEM_INDUCTOR_VARIABLE2},
		{TEXT("Integrated Circuit"),												 IDI_SCHEM_INTEGRATED_CIRCUIT},
		{TEXT("Inverter"),																	 IDI_SCHEM_INVERTER},
		{TEXT("Jack, Coaxial"),															 IDI_SCHEM_JACK_COAXIAL},
		{TEXT("Jack, Phone, 2-Conductor"),									 IDI_SCHEM_JACK_PHONE_2CONDUCTOR},
		{TEXT("Jack, Phone, 2-Conductor Interrupting"),			 IDI_SCHEM_JACK_PHONE_2CONDUCTOR_INTERRUPTING},
		{TEXT("Jack, Phone, 3-Conductor"),									 IDI_SCHEM_JACK_PHONE_3CONDUCTOR},
		{TEXT("Jack, Phono"),																 IDI_SCHEM_JACK_PHONO},
		{TEXT("Key, Telegraph"),														 IDI_SCHEM_KEY_TELEGRAPH},
		{TEXT("Lamp, Incandescent"),												 IDI_SCHEM_LAMP_INCANDESCENT},
		{TEXT("Lamp, Neon"),																 IDI_SCHEM_LAMP_NEON},
		{TEXT("Male Contact, General"),											 IDI_SCHEM_MALE_CONTACT_GENERAL},
		{TEXT("Microphone"),																 IDI_SCHEM_MICROPHONE},
		{TEXT("Nand Gate"),																	 IDI_SCHEM_NAND_GATE},
		{TEXT("Negative Voltage Connection"),								 IDI_SCHEM_NEGATIVE_VOLTAGE_CONNECTION},
		{TEXT("Nor Gate"),																	 IDI_SCHEM_NOR_GATE},
		{TEXT("Operational Amplifier"),											 IDI_SCHEM_OPERATIONAL_AMPLIFIER},
		{TEXT("Or Gate"),																		 IDI_SCHEM_OR_GATE},
		{TEXT("Outlet, Utility, 117-V"),										 IDI_SCHEM_OUTLET_UTILITY_117_V},
		{TEXT("Outlet, Utility, 234-V"),										 IDI_SCHEM_OUTLET_UTILITY_234_V},
		{TEXT("Photocell, Tube"),														 IDI_SCHEM_PHOTOCELL_TUBE},
		{TEXT("Plug, Phone, 2-Conductor"),									 IDI_SCHEM_PLUG_PHONE_2CONDUCTOR},
		{TEXT("Plug, Phone, 3-Conductor"),									 IDI_SCHEM_PLUG_PHONE_3CONDUCTOR},
		{TEXT("Plug, Phono"),																 IDI_SCHEM_PLUG_PHONO},
		{TEXT("Plug, Utility, 117-V"),											 IDI_SCHEM_PLUG_UTILITY_117_V},
		{TEXT("Plug, Utility, 234-V"),											 IDI_SCHEM_PLUG_UTILITY_234_V},
		{TEXT("Positive Voltage Connection"),								 IDI_SCHEM_POSITIVE_VOLTAGE_CONNECTION},
		{TEXT("Potentiometer"),															 IDI_SCHEM_POTENTIOMETER1},
		{TEXT("Potentiometer (Alternate)"),									 IDI_SCHEM_POTENTIOMETER2},
		{TEXT("Probe, Radio frequency"),										 IDI_SCHEM_PROBE_RADIO_FREQUENCY},
		{TEXT("Rectifier, Semi conductor"),									 IDI_SCHEM_RECTIFIER_SEMICONDUCTOR},
		{TEXT("Rectifier, Silicon controlled"),							 IDI_SCHEM_RECTIFIER_SILICON_CONTROLLED},
		{TEXT("Rectifier, Tube Type"),											 IDI_SCHEM_RECTIFIER_TUBE_TYPE},
		{TEXT("Relay, DPDT"),																 IDI_SCHEM_RELAY_DPDT},
		{TEXT("Relay, DPST"),																 IDI_SCHEM_RELAY_DPST},
		{TEXT("Relay, SPDT"),																 IDI_SCHEM_RELAY_SPDT},
		{TEXT("Relay, SPST"),																 IDI_SCHEM_RELAY_SPST},
		{TEXT("Resistor"),																	 IDI_SCHEM_RESISTOR},
		{TEXT("Resonator"),																	 IDI_SCHEM_RESONATOR},
		{TEXT("Rheostat"),																	 IDI_SCHEM_RHEOSTAT1},
		{TEXT("Rheostat (Alternate)"),											 IDI_SCHEM_RHEOSTAT2},
		{TEXT("Saturable Reactor"),													 IDI_SCHEM_SATURABLE_REACTOR},
		{TEXT("Shielding"),																	 IDI_SCHEM_SHIELDING},
		{TEXT("Signal Generator"),													 IDI_SCHEM_SIGNAL_GENERATOR},
		{TEXT("Speaker"),																		 IDI_SCHEM_SPEAKER1},
		{TEXT("Speaker (Alternate)"),												 IDI_SCHEM_SPEAKER2},
		{TEXT("Switch, DPDT"),															 IDI_SCHEM_SWITCH_DPDT},
		{TEXT("Switch, DPST"),															 IDI_SCHEM_SWITCH_DPST},
		{TEXT("Switch, Momentary contact"),									 IDI_SCHEM_SWITCH_MOMENTARY},
		{TEXT("Switch, Rotary"),														 IDI_SCHEM_SWITCH_ROTARY},
		{TEXT("Switch, SPDT"),															 IDI_SCHEM_SWITCH_SPDT},
		{TEXT("Switch, SPST"),															 IDI_SCHEM_SWITCH_SPST},
		{TEXT("Terminals, General, Balanced"),							 IDI_SCHEM_TERMINALS_BALANCED},
		{TEXT("Terminals, General, Unbalanced"),						 IDI_SCHEM_TERMINALS_UNBALANCED},
		{TEXT("Test Point"),																 IDI_SCHEM_TEST_POINT},
		{TEXT("Thermocouple"),															 IDI_SCHEM_THERMOCOUPLE1},
		{TEXT("Thermocouple (Alternate)"),									 IDI_SCHEM_THERMOCOUPLE2},
		{TEXT("Thyristor"),																	 IDI_SCHEM_THYRISTOR},
		{TEXT("Transformer, Air-Core"),											 IDI_SCHEM_TRANSFORMER_AIR_CORE},
		{TEXT("Transformer, Iron-Core"),										 IDI_SCHEM_TRANSFORMER_IRON_CORE},
		{TEXT("Transformer, Tapped Primary"),								 IDI_SCHEM_TRANSFORMER_TAPPED_PRIMARY},
		{TEXT("Transformer, Tapped Secondary"),							 IDI_SCHEM_TRANSFORMER_TAPPED_SECONDARY},
		{TEXT("Transistor, Bipolar, NPN"),									 IDI_SCHEM_TRANSISTOR_BIPOLAR_NPN},
		{TEXT("Transistor, Bipolar, PNP"),									 IDI_SCHEM_TRANSISTOR_BIPOLAR_PNP},
		{TEXT("Transistor, Field-Effect, N-Channel"),				 IDI_SCHEM_TRANSISTOR_FIELD_EFFECT_NCHANNEL},
		{TEXT("Transistor, Field-Effect, P-Channel"),				 IDI_SCHEM_TRANSISTOR_FIELD_EFFECT_PCHANNEL},
		{TEXT("Transistor, Metal-Oxide, Dual-Gate"),				 IDI_SCHEM_TRANSISTOR_METAL_OXIDE_DUALGATE},
		{TEXT("Transistor, Metal-Oxide, Single-Gate"),			 IDI_SCHEM_TRANSISTOR_METAL_OXIDE_SINGLEGATE},
		{TEXT("Transistor, Photo sensitive"),								 IDI_SCHEM_TRANSISTOR_PHOTOSENSITIVE},
		{TEXT("Transistor, Unijunction"),										 IDI_SCHEM_TRANSISTOR_UNIJUNCTION},
		{TEXT("Tube, Diode"),																 IDI_SCHEM_TUBE_DIODE},
		{TEXT("Tube, Pentode"),															 IDI_SCHEM_TUBE_PENTODE},
		{TEXT("Tube, Photo multiplier"),										 IDI_SCHEM_TUBE_PHOTOMULTIPLIER},
		{TEXT("Tube, Tetrode"),															 IDI_SCHEM_TUBE_TETRODE},
		{TEXT("Tube, Triode"),															 IDI_SCHEM_TUBE_TRIODE},
		{TEXT("Unspecified Component"),											 IDI_SCHEM_UNSPECIFIED_COMPONENT},
		{TEXT("Voltmeter"),																	 IDI_SCHEM_VOLTMETER},
		{TEXT("Wattmeter"),																	 IDI_SCHEM_WATTMETER1},
		{TEXT("Wattmeter (Alternate)"),											 IDI_SCHEM_WATTMETER2},
		{TEXT("Wires"),																			 IDI_SCHEM_WIRES},
		{TEXT("Wires, Connected, Crossing"),								 IDI_SCHEM_WIRES_CONNECTED_CROSSING1},
		{TEXT("Wires, Connected, Crossing (Alternate)"),     IDI_SCHEM_WIRES_CONNECTED_CROSSING2},
		{TEXT("Wires, Not Connected, Crossing"),             IDI_SCHEM_WIRES_NOT_CONNECTED_CROSSING1},
		{TEXT("Wires, Not Connected, Crossing (Alternate)"), IDI_SCHEM_WIRES_NOT_CONNECTED_CROSSING2},
	};
