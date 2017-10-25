# Microsoft Developer Studio Generated NMAKE File, Based on Omnytex PocketPC Installer.dsp
!IF "$(CFG)" == ""
CFG=Omnytex PocketPC Installer - Win32 Debug
!MESSAGE No configuration specified. Defaulting to Omnytex PocketPC Installer - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Omnytex PocketPC Installer - Win32 Release" && "$(CFG)" != "Omnytex PocketPC Installer - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Omnytex PocketPC Installer.mak" CFG="Omnytex PocketPC Installer - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Omnytex PocketPC Installer - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Omnytex PocketPC Installer - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Omnytex PocketPC Installer - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\Omnytex PocketPC Installer.exe"


CLEAN :
	-@erase "$(INTDIR)\Omnytex PocketPC Installer.obj"
	-@erase "$(INTDIR)\Omnytex PocketPC Installer.pch"
	-@erase "$(INTDIR)\Resource.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\Omnytex PocketPC Installer.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\Omnytex PocketPC Installer.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Resource.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Omnytex PocketPC Installer.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\Omnytex PocketPC Installer.pdb" /machine:I386 /out:"$(OUTDIR)\Omnytex PocketPC Installer.exe" 
LINK32_OBJS= \
	"$(INTDIR)\Omnytex PocketPC Installer.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Resource.res"

"$(OUTDIR)\Omnytex PocketPC Installer.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Omnytex PocketPC Installer - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\Omnytex PocketPC Installer.exe"


CLEAN :
	-@erase "$(INTDIR)\Omnytex PocketPC Installer.obj"
	-@erase "$(INTDIR)\Omnytex PocketPC Installer.pch"
	-@erase "$(INTDIR)\Resource.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\Omnytex PocketPC Installer.exe"
	-@erase "$(OUTDIR)\Omnytex PocketPC Installer.ilk"
	-@erase "$(OUTDIR)\Omnytex PocketPC Installer.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\Omnytex PocketPC Installer.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Resource.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Omnytex PocketPC Installer.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\Omnytex PocketPC Installer.pdb" /debug /machine:I386 /out:"$(OUTDIR)\Omnytex PocketPC Installer.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\Omnytex PocketPC Installer.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Resource.res"

"$(OUTDIR)\Omnytex PocketPC Installer.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("Omnytex PocketPC Installer.dep")
!INCLUDE "Omnytex PocketPC Installer.dep"
!ELSE 
!MESSAGE Warning: cannot find "Omnytex PocketPC Installer.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "Omnytex PocketPC Installer - Win32 Release" || "$(CFG)" == "Omnytex PocketPC Installer - Win32 Debug"
SOURCE=".\Omnytex PocketPC Installer.cpp"

"$(INTDIR)\Omnytex PocketPC Installer.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Omnytex PocketPC Installer.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "Omnytex PocketPC Installer - Win32 Release"

CPP_SWITCHES=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\Omnytex PocketPC Installer.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Omnytex PocketPC Installer.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Omnytex PocketPC Installer - Win32 Debug"

CPP_SWITCHES=/nologo /MLd /W3 /Gm /GX /ZI /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\Omnytex PocketPC Installer.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Omnytex PocketPC Installer.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\Resource.rc

"$(INTDIR)\Resource.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)



!ENDIF 

