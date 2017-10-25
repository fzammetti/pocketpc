@echo off
cls

set AppName=InvasionTrivia

REM --------------------------------------------------------------------------
REM Copy the ReadMe.txt file into the Distribution directories
REM --------------------------------------------------------------------------
echo Copying ReadMe.txt file...
copy ..\Docs\ReadMe.txt .\Distribution
copy setup.ini .\Distribution

REM --------------------------------------------------------------------------
REM Create version and copy to distribution directory
REM --------------------------------------------------------------------------
echo Creating and copying CAB and DAT files for version...
erase cwizerr.log
CABWiz %AppName%.inf /err cwizerr.log /cpu ARM
move %AppName%.ARM.CAB .\Distribution
move %AppName%.ARM.DAT .\Distribution

REM --------------------------------------------------------------------------
REM Zip up Distributions
REM --------------------------------------------------------------------------
wzzip .\Distribution\%AppName%.zip .\Distribution\*.*
