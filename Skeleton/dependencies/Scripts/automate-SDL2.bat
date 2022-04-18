@echo off

rem Este .bat se encuentra en el directorio Dependencies/Scripts

rem Variables de directorios
set SDL2_SOL=..\OgreBuild\SDL2-build\SDL2.sln
set EXES_DIR=..\..\exes\

echo Compilando la solucion de SDL2...

rem Compilacion de la solucion en Debug y en Release
msbuild %SDL2_SOL% /p:configuration=Debug /t:ALL_BUILD /p:Platform=x64
msbuild %SDL2_SOL% /p:configuration=Release /t:ALL_BUILD /p:Platform=x64

echo Solucion de SDL2 compilada.
echo Copiando .dlls...

copy ..\OgreBuild\SDL2-build\Release\SDL2.dll %EXES_DIR% /y 1>nul
copy ..\OgreBuild\SDL2-build\Debug\SDL2d.dll %EXES_DIR% /y 1>nul

echo .Dlls copiadas.
echo Automatizacion de SDL2 terminada.