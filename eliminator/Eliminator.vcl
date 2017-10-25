<html>
<body>
<pre>
<h1>Build Log</h1>
<h3>
--------------------Configuration: Eliminator - Win32 (WCE ARM) Release--------------------
</h3>
<h3>Command Lines</h3>
Creating command line "rc.exe /l 0x409 /fo"ARMRel/Eliminator.res" /d UNDER_CE=300 /d _WIN32_WCE=300 /d "UNICODE" /d "_UNICODE" /d "NDEBUG" /d "WIN32_PLATFORM_PSPC" /d "ARM" /d "_ARM_" /r "C:\temp\Eliminator 1.6\Eliminator.rc"" 
Creating temporary file "C:\WINDOWS\TEMP\RSP7D4.tmp" with contents
[
/nologo /W3 /D _WIN32_WCE=300 /D "WIN32_PLATFORM_PSPC" /D "ARM" /D "_ARM_" /D UNDER_CE=300 /D "UNICODE" /D "_UNICODE" /D "NDEBUG" /Fp"ARMRel/Eliminator.pch" /Yu"stdafx.h" /Fo"ARMRel/" /Oxs /MC /c 
"C:\temp\Eliminator 1.6\Eliminator.cpp"
]
Creating command line "clarm.exe @C:\WINDOWS\TEMP\RSP7D4.tmp" 
Creating temporary file "C:\WINDOWS\TEMP\RSP7D5.tmp" with contents
[
/nologo /W3 /D _WIN32_WCE=300 /D "WIN32_PLATFORM_PSPC" /D "ARM" /D "_ARM_" /D UNDER_CE=300 /D "UNICODE" /D "_UNICODE" /D "NDEBUG" /Fp"ARMRel/Eliminator.pch" /Yc"stdafx.h" /Fo"ARMRel/" /Oxs /MC /c 
"C:\temp\Eliminator 1.6\StdAfx.cpp"
]
Creating command line "clarm.exe @C:\WINDOWS\TEMP\RSP7D5.tmp" 
Creating temporary file "C:\WINDOWS\TEMP\RSP7D6.tmp" with contents
[
commctrl.lib coredll.lib aygshell.lib /nologo /base:"0x00010000" /stack:0x10000,0x1000 /entry:"WinMainCRTStartup" /incremental:no /pdb:"ARMRel/Eliminator.pdb" /nodefaultlib:"libc.lib /nodefaultlib:libcd.lib /nodefaultlib:libcmt.lib /nodefaultlib:libcmtd.lib /nodefaultlib:msvcrt.lib /nodefaultlib:msvcrtd.lib /nodefaultlib:oldnames.lib" /out:"ARMRel/Eliminator.exe" /subsystem:windowsce,3.00 /align:"4096" /MACHINE:ARM 
".\ARMRel\Eliminator.obj"
".\ARMRel\StdAfx.obj"
".\ARMRel\Eliminator.res"
]
Creating command line "link.exe @C:\WINDOWS\TEMP\RSP7D6.tmp"
<h3>Output Window</h3>
Compiling resources...
Compiling...
StdAfx.cpp
Compiling...
Eliminator.cpp
Linking...



<h3>Results</h3>
Eliminator.exe - 0 error(s), 0 warning(s)
</pre>
</body>
</html>
