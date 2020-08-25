<html>
<body>
<pre>
<h1>Build Log</h1>
<h3>
--------------------Configuration: FontTest - Win32 (WCE MIPS) Release--------------------
</h3>
<h3>Command Lines</h3>
Creating command line "rc.exe /l 0x409 /fo"MIPSRel/FontTest.res" /d UNDER_CE=300 /d _WIN32_WCE=300 /d "UNICODE" /d "_UNICODE" /d "NDEBUG" /d "WIN32_PLATFORM_PSPC" /d "MIPS" /d "_MIPS_" /r "C:\Temp\Etc\GXLib\FontTest\FontTest.rc"" 
Creating temporary file "C:\WINDOWS\TEMP\RSP712.tmp" with contents
[
/nologo /W3 /D _WIN32_WCE=300 /D "WIN32_PLATFORM_PSPC" /D "MIPS" /D "_MIPS_" /D UNDER_CE=300 /D "UNICODE" /D "_UNICODE" /D "NDEBUG" /Fp"MIPSRel/FontTest.pch" /Yu"stdafx.h" /Fo"MIPSRel/" /Oxs /MC /c 
"C:\Temp\Etc\GXLib\FontTest\FontTest.cpp"
]
Creating command line "clmips.exe @C:\WINDOWS\TEMP\RSP712.tmp" 
Creating temporary file "C:\WINDOWS\TEMP\RSP713.tmp" with contents
[
/nologo /W3 /D _WIN32_WCE=300 /D "WIN32_PLATFORM_PSPC" /D "MIPS" /D "_MIPS_" /D UNDER_CE=300 /D "UNICODE" /D "_UNICODE" /D "NDEBUG" /Fp"MIPSRel/FontTest.pch" /Yc"stdafx.h" /Fo"MIPSRel/" /Oxs /MC /c 
"C:\Temp\Etc\GXLib\FontTest\StdAfx.cpp"
]
Creating command line "clmips.exe @C:\WINDOWS\TEMP\RSP713.tmp" 
Creating temporary file "C:\WINDOWS\TEMP\RSP714.tmp" with contents
[
commctrl.lib coredll.lib aygshell.lib gx.lib zlibce.lib /nologo /base:"0x00010000" /stack:0x10000,0x1000 /entry:"WinMainCRTStartup" /incremental:no /pdb:"MIPSRel/FontTest.pdb" /nodefaultlib:"libc.lib /nodefaultlib:libcd.lib /nodefaultlib:libcmt.lib /nodefaultlib:libcmtd.lib /nodefaultlib:msvcrt.lib /nodefaultlib:msvcrtd.lib /nodefaultlib:oldnames.lib" /out:"MIPSRel/FontTest.exe" /subsystem:windowsce,3.00 /MACHINE:MIPS 
.\MIPSRel\FontTest.obj
.\MIPSRel\StdAfx.obj
.\MIPSRel\FontTest.res
]
Creating command line "link.exe @C:\WINDOWS\TEMP\RSP714.tmp"
<h3>Output Window</h3>
Compiling resources...
Compiling...
StdAfx.cpp
Compiling...
FontTest.cpp
Linking...



<h3>Results</h3>
FontTest.exe - 0 error(s), 0 warning(s)
</pre>
</body>
</html>
