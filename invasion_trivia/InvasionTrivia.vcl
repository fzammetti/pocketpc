<html>
<body>
<pre>
<h1>Build Log</h1>
<h3>
--------------------Configuration: InvasionTrivia - Win32 (WCE ARM) Release--------------------
</h3>
<h3>Command Lines</h3>
Creating command line "rc.exe /l 0x409 /fo"ARMRel/InvasionTrivia.res" /d UNDER_CE=300 /d _WIN32_WCE=300 /d "UNICODE" /d "_UNICODE" /d "NDEBUG" /d "WIN32_PLATFORM_PSPC" /d "ARM" /d "_ARM_" /r "C:\temp\Invasion Trivia 1.2\InvasionTrivia.rc"" 
Creating temporary file "C:\WINDOWS\TEMP\RSP834.tmp" with contents
[
/nologo /W3 /D _WIN32_WCE=300 /D "WIN32_PLATFORM_PSPC" /D "ARM" /D "_ARM_" /D UNDER_CE=300 /D "UNICODE" /D "_UNICODE" /D "NDEBUG" /Fp"ARMRel/InvasionTrivia.pch" /YX /Fo"ARMRel/" /Oxs /MC /c 
"C:\temp\Invasion Trivia 1.2\Source\InvasionTrivia.cpp"
]
Creating command line "clarm.exe @C:\WINDOWS\TEMP\RSP834.tmp" 
Creating temporary file "C:\WINDOWS\TEMP\RSP835.tmp" with contents
[
commctrl.lib coredll.lib aygshell.lib /nologo /base:"0x00010000" /stack:0x10000,0x1000 /entry:"WinMainCRTStartup" /incremental:no /pdb:"ARMRel/InvasionTrivia.pdb" /nodefaultlib:"libc.lib /nodefaultlib:libcd.lib /nodefaultlib:libcmt.lib /nodefaultlib:libcmtd.lib /nodefaultlib:msvcrt.lib /nodefaultlib:msvcrtd.lib /nodefaultlib:oldnames.lib" /out:"ARMRel/InvasionTrivia.exe" /subsystem:windowsce,3.00 /align:"4096" /MACHINE:ARM 
".\ARMRel\InvasionTrivia.obj"
".\ARMRel\InvasionTrivia.res"
]
Creating command line "link.exe @C:\WINDOWS\TEMP\RSP835.tmp"
<h3>Output Window</h3>
Compiling resources...
Compiling...
InvasionTrivia.cpp
Linking...



<h3>Results</h3>
InvasionTrivia.exe - 0 error(s), 0 warning(s)
</pre>
</body>
</html>
