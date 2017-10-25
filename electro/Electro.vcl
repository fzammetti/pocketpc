<html>
<body>
<pre>
<h1>Build Log</h1>
<h3>
--------------------Configuration: Electro - Win32 (WCE ARM) Release--------------------
</h3>
<h3>Command Lines</h3>
Creating command line "rc.exe /l 0x409 /fo"ARMRel/Electro.res" /d UNDER_CE=300 /d _WIN32_WCE=300 /d "UNICODE" /d "_UNICODE" /d "NDEBUG" /d "WIN32_PLATFORM_PSPC" /d "ARM" /d "_ARM_" /r "C:\Temp\etc\Electro v1.2\Electro.rc"" 
Creating temporary file "C:\WINNT\TEMP\RSP3EB.tmp" with contents
[
/nologo /W3 /O2 /D _WIN32_WCE=300 /D "WIN32_PLATFORM_PSPC" /D "ARM" /D "_ARM_" /D UNDER_CE=300 /D "UNICODE" /D "_UNICODE" /D "NDEBUG" /Fp"ARMRel/Electro.pch" /Yu"stdafx.h" /Fo"ARMRel/" /Oxs /MC /c 
"C:\Temp\etc\Electro v1.2\Electro.cpp"
]
Creating command line "clarm.exe @C:\WINNT\TEMP\RSP3EB.tmp" 
Creating temporary file "C:\WINNT\TEMP\RSP3EC.tmp" with contents
[
/nologo /W3 /O2 /D _WIN32_WCE=300 /D "WIN32_PLATFORM_PSPC" /D "ARM" /D "_ARM_" /D UNDER_CE=300 /D "UNICODE" /D "_UNICODE" /D "NDEBUG" /Fp"ARMRel/Electro.pch" /Yc"stdafx.h" /Fo"ARMRel/" /Oxs /MC /c 
"C:\Temp\etc\Electro v1.2\StdAfx.cpp"
]
Creating command line "clarm.exe @C:\WINNT\TEMP\RSP3EC.tmp" 
Creating temporary file "C:\WINNT\TEMP\RSP3ED.tmp" with contents
[
commctrl.lib coredll.lib aygshell.lib /nologo /base:"0x00010000" /stack:0x10000,0x1000 /entry:"WinMainCRTStartup" /incremental:no /pdb:"ARMRel/Electro.pdb" /nodefaultlib:"libc.lib /nodefaultlib:libcd.lib /nodefaultlib:libcmt.lib /nodefaultlib:libcmtd.lib /nodefaultlib:msvcrt.lib /nodefaultlib:msvcrtd.lib /nodefaultlib:oldnames.lib" /out:"ARMRel/Electro.exe" /subsystem:windowsce,3.00 /align:"4096" /MACHINE:ARM 
".\ARMRel\Electro.obj"
".\ARMRel\StdAfx.obj"
".\ARMRel\Electro.res"
]
Creating command line "link.exe @C:\WINNT\TEMP\RSP3ED.tmp"
<h3>Output Window</h3>
Compiling resources...
Compiling...
StdAfx.cpp
Compiling...
Electro.cpp
Linking...



<h3>Results</h3>
Electro.exe - 0 error(s), 0 warning(s)
</pre>
</body>
</html>
