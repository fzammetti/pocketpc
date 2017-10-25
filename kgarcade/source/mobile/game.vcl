<html>
<body>
<pre>
<h1>Build Log</h1>
<h3>
--------------------Configuration: game - Win32 (WCE ARM) Release--------------------
</h3>
<h3>Command Lines</h3>
Creating command line "rc.exe /l 0x409 /fo"ARMRel/game.res" /i "\temp\KandG Arcade 1.6\source\common" /d UNDER_CE=300 /d _WIN32_WCE=300 /d "UNICODE" /d "_UNICODE" /d "NDEBUG" /d "WIN32_PLATFORM_PSPC" /d "ARM" /d "_ARM_" /r "C:\temp\KandG Arcade 1.6\source\common\game.rc"" 
Creating temporary file "C:\WINDOWS\TEMP\RSP891.tmp" with contents
[
/nologo /W3 /D _WIN32_WCE=300 /D "WIN32_PLATFORM_PSPC" /D "ARM" /D "_ARM_" /D UNDER_CE=300 /D "UNICODE" /D "_UNICODE" /D "NDEBUG" /Fp"ARMRel/game.pch" /YX /Fo"ARMRel/" /Oxs /MC /c 
"C:\temp\KandG Arcade 1.6\source\common\mini_games\a_day_in_the_strife.cpp"
"C:\temp\KandG Arcade 1.6\source\common\mini_games\alien_babble.cpp"
"C:\temp\KandG Arcade 1.6\source\common\mini_games\antigravitator.cpp"
"C:\temp\KandG Arcade 1.6\source\common\mini_games\conquerror.cpp"
"C:\temp\KandG Arcade 1.6\source\common\mini_games\copycat.cpp"
"C:\temp\KandG Arcade 1.6\source\common\mini_games\cosmic_squirrel.cpp"
"C:\temp\KandG Arcade 1.6\source\common\mini_games\deathtrap.cpp"
"C:\temp\KandG Arcade 1.6\source\common\mini_games\defendoh.cpp"
"C:\temp\KandG Arcade 1.6\source\common\mini_games\engineer.cpp"
"C:\temp\KandG Arcade 1.6\source\common\mini_games\far_out_fowl.cpp"
"C:\temp\KandG Arcade 1.6\source\common\mini_games\ffopir_sirtet_paehc.cpp"
"C:\temp\KandG Arcade 1.6\source\common\mini_games\flight_of_doom.cpp"
"C:\temp\KandG Arcade 1.6\source\common\mini_games\glutton.cpp"
"C:\temp\KandG Arcade 1.6\source\common\mini_games\in_memoria.cpp"
"C:\temp\KandG Arcade 1.6\source\common\mini_games\lepar_land.cpp"
"C:\temp\KandG Arcade 1.6\source\common\mini_games\muncher_dude.cpp"
"C:\temp\KandG Arcade 1.6\source\common\mini_games\refluxive.cpp"
"C:\temp\KandG Arcade 1.6\source\common\mini_games\reluctant_hero.cpp"
"C:\temp\KandG Arcade 1.6\source\common\mini_games\son_of_eliminator.cpp"
"C:\temp\KandG Arcade 1.6\source\common\mini_games\squishem.cpp"
"C:\temp\KandG Arcade 1.6\source\common\mini_games\the_bogaz_derby.cpp"
"C:\temp\KandG Arcade 1.6\source\common\mini_games\the_escape.cpp"
"C:\temp\KandG Arcade 1.6\source\common\mini_games\the_redeye_order.cpp"
"C:\temp\KandG Arcade 1.6\source\common\mini_games\trouble_in_vectropolis.cpp"
"C:\temp\KandG Arcade 1.6\source\common\mini_games\virus.cpp"
"C:\temp\KandG Arcade 1.6\source\common\scenes\new_adventure.cpp"
"C:\temp\KandG Arcade 1.6\source\common\scenes\player_died.cpp"
"C:\temp\KandG Arcade 1.6\source\common\scenes\win.cpp"
"C:\temp\KandG Arcade 1.6\source\common\character_interaction.cpp"
"C:\temp\KandG Arcade 1.6\source\common\credits.cpp"
"C:\temp\KandG Arcade 1.6\source\common\final_score.cpp"
"C:\temp\KandG Arcade 1.6\source\common\high_scores.cpp"
"C:\temp\KandG Arcade 1.6\source\common\instructions.cpp"
"C:\temp\KandG Arcade 1.6\source\common\intro_clickgamer.cpp"
"C:\temp\KandG Arcade 1.6\source\common\intro_crackhead.cpp"
"C:\temp\KandG Arcade 1.6\source\common\intro_omnytex.cpp"
"C:\temp\KandG Arcade 1.6\source\common\main_menu.cpp"
"C:\temp\KandG Arcade 1.6\source\common\new_game_type.cpp"
"C:\temp\KandG Arcade 1.6\source\common\options.cpp"
"C:\temp\KandG Arcade 1.6\source\common\title.cpp"
"C:\temp\KandG Arcade 1.6\source\common\walking_around_the_ship.cpp"
"C:\temp\KandG Arcade 1.6\source\common\input_handlers.cpp"
"C:\temp\KandG Arcade 1.6\source\common\main.cpp"
"C:\temp\KandG Arcade 1.6\source\common\process_next_frame.cpp"
"C:\Program Files\libraries\GapiDraw(LicensedVersionForKandGArcade)\include\win32\GapiApplication.cpp"
]
Creating command line "clarm.exe @C:\WINDOWS\TEMP\RSP891.tmp" 
Creating temporary file "C:\WINDOWS\TEMP\RSP892.tmp" with contents
[
aygshell.lib commctrl.lib coredll.lib hss.lib /nologo /base:"0x00010000" /stack:0x10000,0x1000 /entry:"WinMainCRTStartup" /incremental:no /pdb:"ARMRel/game.pdb" /nodefaultlib:"libc.lib /nodefaultlib:libcd.lib /nodefaultlib:libcmt.lib /nodefaultlib:libcmtd.lib /nodefaultlib:msvcrt.lib /nodefaultlib:msvcrtd.lib /nodefaultlib:oldnames.lib" /out:"ARMRel/game.exe" /libpath:"C:\Program Files\libraries\GapiDraw\lib\PocketPC2003-arm" /libpath:"C:\Program Files\libraries\HekkusSoundSystem\lib\arm\release" /subsystem:windowsce,3.00 /align:"4096" /MACHINE:ARM 
".\ARMRel\a_day_in_the_strife.obj"
".\ARMRel\alien_babble.obj"
".\ARMRel\antigravitator.obj"
".\ARMRel\conquerror.obj"
".\ARMRel\copycat.obj"
".\ARMRel\cosmic_squirrel.obj"
".\ARMRel\deathtrap.obj"
".\ARMRel\defendoh.obj"
".\ARMRel\engineer.obj"
".\ARMRel\far_out_fowl.obj"
".\ARMRel\ffopir_sirtet_paehc.obj"
".\ARMRel\flight_of_doom.obj"
".\ARMRel\glutton.obj"
".\ARMRel\in_memoria.obj"
".\ARMRel\lepar_land.obj"
".\ARMRel\muncher_dude.obj"
".\ARMRel\refluxive.obj"
".\ARMRel\reluctant_hero.obj"
".\ARMRel\son_of_eliminator.obj"
".\ARMRel\squishem.obj"
".\ARMRel\the_bogaz_derby.obj"
".\ARMRel\the_escape.obj"
".\ARMRel\the_redeye_order.obj"
".\ARMRel\trouble_in_vectropolis.obj"
".\ARMRel\virus.obj"
".\ARMRel\new_adventure.obj"
".\ARMRel\player_died.obj"
".\ARMRel\win.obj"
".\ARMRel\character_interaction.obj"
".\ARMRel\credits.obj"
".\ARMRel\final_score.obj"
".\ARMRel\high_scores.obj"
".\ARMRel\instructions.obj"
".\ARMRel\intro_clickgamer.obj"
".\ARMRel\intro_crackhead.obj"
".\ARMRel\intro_omnytex.obj"
".\ARMRel\main_menu.obj"
".\ARMRel\new_game_type.obj"
".\ARMRel\options.obj"
".\ARMRel\title.obj"
".\ARMRel\walking_around_the_ship.obj"
".\ARMRel\input_handlers.obj"
".\ARMRel\main.obj"
".\ARMRel\process_next_frame.obj"
".\ARMRel\GapiApplication.obj"
".\ARMRel\game.res"
]
Creating command line "link.exe @C:\WINDOWS\TEMP\RSP892.tmp"
<h3>Output Window</h3>
Compiling resources...
Compiling...
a_day_in_the_strife.cpp
alien_babble.cpp
antigravitator.cpp
conquerror.cpp
copycat.cpp
cosmic_squirrel.cpp
deathtrap.cpp
defendoh.cpp
engineer.cpp
far_out_fowl.cpp
ffopir_sirtet_paehc.cpp
flight_of_doom.cpp
glutton.cpp
in_memoria.cpp
lepar_land.cpp
muncher_dude.cpp
refluxive.cpp
reluctant_hero.cpp
son_of_eliminator.cpp
squishem.cpp
the_bogaz_derby.cpp
the_escape.cpp
the_redeye_order.cpp
trouble_in_vectropolis.cpp
virus.cpp
new_adventure.cpp
player_died.cpp
win.cpp
character_interaction.cpp
credits.cpp
final_score.cpp
high_scores.cpp
instructions.cpp
intro_clickgamer.cpp
intro_crackhead.cpp
intro_omnytex.cpp
main_menu.cpp
new_game_type.cpp
options.cpp
title.cpp
walking_around_the_ship.cpp
input_handlers.cpp
main.cpp
process_next_frame.cpp
GapiApplication.cpp
Linking...



<h3>Results</h3>
game.exe - 0 error(s), 0 warning(s)
</pre>
</body>
</html>
