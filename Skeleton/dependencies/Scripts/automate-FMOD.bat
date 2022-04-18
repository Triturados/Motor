@echo off

rem Este .bat se encuentra en el directorio Dependencies/Scripts

rem Variables de directorios
set WORKING_DIR=%cd%
set FMOD_DLLS_DIR=..\FMODStudioAPIWindows\dlls\
set EXES_DIR=..\..\exes\

cd %FMOD_DLLS_DIR%

echo Copiando dlls de FMOD...

copy fmod.dll %EXES_DIR% 1>nul
copy fmodL.dll %EXES_DIR% 1>nul
copy fmodstudio.dll %EXES_DIR% 1>nul
copy fmodstudioL.dll %EXES_DIR% 1>nul

echo .Dlls de FMOD copiadas.
echo Automatizacion de FMOD terminada.

cd %WORKING_DIR%