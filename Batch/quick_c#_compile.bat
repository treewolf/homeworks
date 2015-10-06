rem TREEWOLF
@echo off
color 0E
echo WILL WRITE OUTPUT TO DIRECTORY OF *THIS* BATCH FILE
echo PREVIOUS OUTPUT FILES WILL BE ERASED IF HAS DEFAULT NAME
set current_env=%CD%
set new_env=%current_env%
echo SETTING ENVIRONMENT TO %new_env%\

cd %current_env%
if exist "a.exe" (
	echo PREVIOUS OUTPUT FILE FOUND. REMOVING...
	del "a.exe"
	echo FILE DELETED
) else (
	echo NO FILE FOUND. CONTINUING...
)
set csc_path=C:/Windows/Microsoft.NET/Framework/v4.0.30319
echo USING %csc_path% FOR COMPILING. IF INCORRECT, EDIT VARIABLE "csc_path"
echo SETTING PATH...
cd %csc_path%
set concat=\a.exe
echo SETTING FILE OUTPUT NAME...
set fullout=%current_env%%concat%
echo FILE OUTPUT NAME SET TO %fullout%
set /p files=ENTER ALL FILES WITH FULL PATH OR DRAG TO WINDOW. SEPARATE FILES WITH A SPACE!:
csc.exe /t:exe /out:%fullout% %files%
cd %current_env%
if exist "a.exe" (
	color 0a
	echo FILE MAKE A SUCCESS!
) else (
	color 0c
	echo FAIL MAKE FAILED.
)
echo PRESS ANY KEY TO EXIT
pause > nul
