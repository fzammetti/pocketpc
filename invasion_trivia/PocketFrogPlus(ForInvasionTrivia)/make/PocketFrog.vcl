<html>
<body>
<pre>
<h1>Build Log</h1>
<h3>
--------------------Configuration: PocketFrog - Win32 (WCE ARM) Debug--------------------
</h3>
<h3>Command Lines</h3>
Creating temporary file "C:\WINDOWS\TEMP\RSP7F.tmp" with contents
[
/nologo /W3 /Zi /Od /D "DEBUG" /D _WIN32_WCE=300 /D "WIN32_PLATFORM_PSPC" /D "ARM" /D "_ARM_" /D UNDER_CE=300 /D "UNICODE" /D "_UNICODE" /D "_LIB" /Fp"../obj/arm/debug/PocketFrog.pch" /YX /Fo"../obj/arm/debug/" /Fd"../obj/arm/debug/" /MC /c 
"C:\Temp\Etc\PocketFrogPlus\src\display.cpp"
"C:\Temp\Etc\PocketFrogPlus\src\font.cpp"
"C:\Temp\Etc\PocketFrogPlus\src\image.cpp"
"C:\Temp\Etc\PocketFrogPlus\src\input.cpp"
"C:\Temp\Etc\PocketFrogPlus\src\pocketpc.cpp"
"C:\Temp\Etc\PocketFrogPlus\src\rasterizer.cpp"
"C:\Temp\Etc\PocketFrogPlus\src\rect.cpp"
"C:\Temp\Etc\PocketFrogPlus\src\sound.cpp"
"C:\Temp\Etc\PocketFrogPlus\src\soundChannel.cpp"
"C:\Temp\Etc\PocketFrogPlus\src\soundData.cpp"
"C:\Temp\Etc\PocketFrogPlus\src\surface.cpp"
"C:\Temp\Etc\PocketFrogPlus\src\framework\game.cpp"
"C:\Temp\Etc\PocketFrogPlus\src\framework\splashscreen.cpp"
"C:\Temp\Etc\PocketFrogPlus\src\internal\blit16.cpp"
"C:\Temp\Etc\PocketFrogPlus\src\internal\blit4.cpp"
"C:\Temp\Etc\PocketFrogPlus\src\internal\blit8.cpp"
"C:\Temp\Etc\PocketFrogPlus\src\internal\GAPILibrary.cpp"
"C:\Temp\Etc\PocketFrogPlus\src\internal\graphicbuffer.cpp"
"C:\Temp\Etc\PocketFrogPlus\src\internal\memfile.cpp"
"C:\Temp\Etc\PocketFrogPlus\src\internal\raster2d.cpp"
"C:\Temp\Etc\PocketFrogPlus\src\internal\Win32Drivers.cpp"
]
Creating command line "clarm.exe @C:\WINDOWS\TEMP\RSP7F.tmp" 
Creating temporary file "C:\WINDOWS\TEMP\RSP80.tmp" with contents
[
/nologo /out:"../lib/PocketFrog_ARM_Debug.lib" 
\Temp\Etc\PocketFrogPlus\obj\arm\debug\display.obj
\Temp\Etc\PocketFrogPlus\obj\arm\debug\font.obj
\Temp\Etc\PocketFrogPlus\obj\arm\debug\image.obj
\Temp\Etc\PocketFrogPlus\obj\arm\debug\input.obj
\Temp\Etc\PocketFrogPlus\obj\arm\debug\pocketpc.obj
\Temp\Etc\PocketFrogPlus\obj\arm\debug\rasterizer.obj
\Temp\Etc\PocketFrogPlus\obj\arm\debug\rect.obj
\Temp\Etc\PocketFrogPlus\obj\arm\debug\sound.obj
\Temp\Etc\PocketFrogPlus\obj\arm\debug\soundChannel.obj
\Temp\Etc\PocketFrogPlus\obj\arm\debug\soundData.obj
\Temp\Etc\PocketFrogPlus\obj\arm\debug\surface.obj
\Temp\Etc\PocketFrogPlus\obj\arm\debug\game.obj
\Temp\Etc\PocketFrogPlus\obj\arm\debug\splashscreen.obj
\Temp\Etc\PocketFrogPlus\obj\arm\debug\blit16.obj
\Temp\Etc\PocketFrogPlus\obj\arm\debug\blit4.obj
\Temp\Etc\PocketFrogPlus\obj\arm\debug\blit8.obj
\Temp\Etc\PocketFrogPlus\obj\arm\debug\GAPILibrary.obj
\Temp\Etc\PocketFrogPlus\obj\arm\debug\graphicbuffer.obj
\Temp\Etc\PocketFrogPlus\obj\arm\debug\memfile.obj
\Temp\Etc\PocketFrogPlus\obj\arm\debug\raster2d.obj
\Temp\Etc\PocketFrogPlus\obj\arm\debug\Win32Drivers.obj
]
Creating command line "link.exe -lib @C:\WINDOWS\TEMP\RSP80.tmp"
<h3>Output Window</h3>
Compiling...
display.cpp
font.cpp
image.cpp
input.cpp
pocketpc.cpp
rasterizer.cpp
C:\Temp\Etc\PocketFrogPlus\src\rasterizer.cpp(296) : warning C4244: 'initializing' : conversion from 'float' to 'int', possible loss of data
C:\Temp\Etc\PocketFrogPlus\src\rasterizer.cpp(312) : warning C4244: 'initializing' : conversion from 'float' to 'unsigned int', possible loss of data
C:\Temp\Etc\PocketFrogPlus\src\rasterizer.cpp(313) : warning C4244: 'initializing' : conversion from 'float' to 'unsigned int', possible loss of data
C:\Temp\Etc\PocketFrogPlus\src\rasterizer.cpp(326) : warning C4146: unary minus operator applied to unsigned type, result still unsigned
C:\Temp\Etc\PocketFrogPlus\src\rasterizer.cpp(329) : warning C4146: unary minus operator applied to unsigned type, result still unsigned
rect.cpp
sound.cpp
soundChannel.cpp
soundData.cpp
surface.cpp
game.cpp
splashscreen.cpp
blit16.cpp
blit4.cpp
blit8.cpp
GAPILibrary.cpp
graphicbuffer.cpp
memfile.cpp
raster2d.cpp
Win32Drivers.cpp
Creating library...



<h3>Results</h3>
PocketFrog_ARM_Debug.lib - 0 error(s), 5 warning(s)
</pre>
</body>
</html>
