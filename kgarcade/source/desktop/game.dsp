# Microsoft Developer Studio Project File - Name="game" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=game - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "game.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "game.mak" CFG="game - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "game - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "game - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "game - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "C:\Program Files\Libraries\GapiDraw\include" /I "C:\Program Files\libraries\HekkusSoundSystem" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib winmm.lib /nologo /subsystem:windows /map /debug /debugtype:both /machine:I386
# SUBTRACT LINK32 /nodefaultlib

!ELSEIF  "$(CFG)" == "game - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib winmm.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# SUBTRACT LINK32 /nodefaultlib

!ENDIF 

# Begin Target

# Name "game - Win32 Release"
# Name "game - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Mini Games"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\common\mini_games\a_day_in_the_strife.cpp
# End Source File
# Begin Source File

SOURCE=..\common\mini_games\alien_babble.cpp
# End Source File
# Begin Source File

SOURCE=..\common\mini_games\antigravitator.cpp
# End Source File
# Begin Source File

SOURCE=..\common\mini_games\conquerror.cpp
# End Source File
# Begin Source File

SOURCE=..\common\mini_games\copycat.cpp
# End Source File
# Begin Source File

SOURCE=..\common\mini_games\cosmic_squirrel.cpp
# End Source File
# Begin Source File

SOURCE=..\common\mini_games\deathtrap.cpp
# End Source File
# Begin Source File

SOURCE=..\common\mini_games\defendoh.cpp
# End Source File
# Begin Source File

SOURCE=..\common\mini_games\engineer.cpp
# End Source File
# Begin Source File

SOURCE=..\common\mini_games\far_out_fowl.cpp
# End Source File
# Begin Source File

SOURCE=..\common\mini_games\ffopir_sirtet_paehc.cpp
# End Source File
# Begin Source File

SOURCE=..\common\mini_games\flight_of_doom.cpp
# End Source File
# Begin Source File

SOURCE=..\common\mini_games\glutton.cpp
# End Source File
# Begin Source File

SOURCE=..\common\mini_games\in_memoria.cpp
# End Source File
# Begin Source File

SOURCE=..\common\mini_games\lepar_land.cpp
# End Source File
# Begin Source File

SOURCE=..\common\mini_games\muncher_dude.cpp
# End Source File
# Begin Source File

SOURCE=..\common\mini_games\refluxive.cpp
# End Source File
# Begin Source File

SOURCE=..\common\mini_games\reluctant_hero.cpp
# End Source File
# Begin Source File

SOURCE=..\common\mini_games\son_of_eliminator.cpp
# End Source File
# Begin Source File

SOURCE=..\common\mini_games\squishem.cpp
# End Source File
# Begin Source File

SOURCE=..\common\mini_games\the_bogaz_derby.cpp
# End Source File
# Begin Source File

SOURCE=..\common\mini_games\the_escape.cpp
# End Source File
# Begin Source File

SOURCE=..\common\mini_games\the_redeye_order.cpp
# End Source File
# Begin Source File

SOURCE=..\common\mini_games\trouble_in_vectropolis.cpp
# End Source File
# Begin Source File

SOURCE=..\common\mini_games\virus.cpp
# End Source File
# End Group
# Begin Group "Cut Scenes"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\common\scenes\new_adventure.cpp
# End Source File
# Begin Source File

SOURCE=..\common\scenes\player_died.cpp
# End Source File
# Begin Source File

SOURCE=..\common\scenes\win.cpp
# End Source File
# End Group
# Begin Group "Screens"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\common\character_interaction.cpp
# End Source File
# Begin Source File

SOURCE=..\common\credits.cpp
# End Source File
# Begin Source File

SOURCE=..\common\final_score.cpp
# End Source File
# Begin Source File

SOURCE=..\common\high_scores.cpp
# End Source File
# Begin Source File

SOURCE=..\common\instructions.cpp
# End Source File
# Begin Source File

SOURCE=..\common\intro_crackhead.cpp
# End Source File
# Begin Source File

SOURCE=..\common\intro_omnytex.cpp
# End Source File
# Begin Source File

SOURCE=..\common\main_menu.cpp
# End Source File
# Begin Source File

SOURCE=..\common\new_game_type.cpp
# End Source File
# Begin Source File

SOURCE=..\common\options.cpp
# End Source File
# Begin Source File

SOURCE=..\common\title.cpp
# End Source File
# Begin Source File

SOURCE=..\common\walking_around_the_ship.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=..\common\input_handlers.cpp
# End Source File
# Begin Source File

SOURCE=..\common\main.cpp
# End Source File
# Begin Source File

SOURCE=..\common\process_next_frame.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\common\Main.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=..\..\Graphics\font1.bin
# End Source File
# Begin Source File

SOURCE=..\common\game.rc
# End Source File
# Begin Source File

SOURCE=..\common\gfx1.bin
# End Source File
# Begin Source File

SOURCE=..\..\graphics\gfx_game_done_off.gif
# End Source File
# Begin Source File

SOURCE=..\..\graphics\gfx_game_done_on.gif
# End Source File
# Begin Source File

SOURCE=..\..\Graphics\Icon.ico
# End Source File
# Begin Source File

SOURCE=..\common\icon.ico
# End Source File
# Begin Source File

SOURCE=.\icon.ico
# End Source File
# Begin Source File

SOURCE=..\common\resource.h
# End Source File
# End Group
# Begin Group "GapiDraw Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE="..\..\..\..\..\Program Files\libraries\GapiDraw\include\GapiApplication.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\Program Files\libraries\GapiDraw\include\GapiApplication.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\..\..\Program Files\libraries\GapiDraw\include\GapiDraw.h"
# End Source File
# End Group
# Begin Group "Documentation"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\docs\beta_build_change_log.txt
# End Source File
# Begin Source File

SOURCE=..\..\docs\beta_testers.txt
# End Source File
# Begin Source File

SOURCE=..\..\docs\history.txt
# End Source File
# Begin Source File

SOURCE=..\..\docs\voiceover_scripts.doc
# End Source File
# End Group
# End Target
# End Project
