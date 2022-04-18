@echo off

rem Este .bat se encuentra en el directorio Dependencies/Scripts

rem Variables de directorios
set WORKING_DIR=%cd%
set DEPENDENCIES_DIR=..\
set SDL2_SOL=..\OgreBuild\SDL2-build\SDL2.sln
set EXES_DIR=..\..\exes\
set DLLS_RELEASE_DIR=..\OgreBuild\SDL2-build\Release\
set DLLS_DEBUG_DIR=..\OgreBuild\SDL2-build\Debug\

echo Compilando la solucion de SDL2...

rem Compilacion de la solucion en Debug y en Release
msbuild %SDL2_SOL% /p:configuration=Debug /t:ALL_BUILD /p:Platform=x64
msbuild %SDL2_SOL% /p:configuration=Release /t:ALL_BUILD /p:Platform=x64

echo Solucion de SDL2 compilada.
echo Copiando .dlls...

cd %DLLS_RELEASE_DIR%
copy SDL2.dll %EXES_DIR% 1>nul

if %RELEASE_ENGINE% == false (
    cd %DLLS_DEBUG_DIR%
    copy SDL2d.dll %EXES_DIR% 1>nul
)

cd %WORKING_DIR%

echo .Dlls copiadas.
echo Automatizacion de SDL2 terminada.