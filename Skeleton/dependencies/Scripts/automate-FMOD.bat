@echo off

rem Este .bat se encuentra en el directorio Dependencies/Scripts

rem Variables de directorios
set EXES_DIR=..\..\exes\

echo Copiando dlls de FMOD...

copy ..\FMODStudioAPIWindows\dlls\fmod.dll %EXES_DIR% /y 1>nul
copy ..\FMODStudioAPIWindows\dlls\fmodL.dll %EXES_DIR% /y 1>nul
copy ..\FMODStudioAPIWindows\dlls\fmodstudio.dll %EXES_DIR% /y 1>nul
copy ..\FMODStudioAPIWindows\dlls\fmodstudioL.dll %EXES_DIR% /y 1>nul

echo .Dlls de FMOD copiadas.
echo Automatizacion de FMOD terminada.