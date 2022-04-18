@echo off

rem Este .bat se encuentra en el directorio Dependencies/Scripts

rem Variables de directorios
set WORKING_DIR=%cd%
set DEPENDENCIES_DIR=..\
set CMAKE_EXE=..\CMAKE\bin\
set LUABRIDGE_SRC=..\LuaBridgeSrc\
set LUABRIDGE_BUILD=..\LuaBridgeBuild\ 
set LUABRIDGE_SOL=..\LuaBridgeBuild\LuaBridge.sln

cd %DEPENDENCIES_DIR%

rem Creamos el directorio donde se van a generar los archivos comprobando si no esta creado ya
if not exist %LUABRIDGE_BUILD% mkdir %LUABRIDGE_BUILD%
if exist %LUABRIDGE_SOL% goto end

echo Generando la build de LuaBridge y compilando la solucion...

cd %CMAKE_EXE%

cmake -D LUABRIDGE_CXX17:BOOL=1 -S %LUABRIDGE_SRC% -B %LUABRIDGE_BUILD%

rem Compilacion de la solucion en Debug y en Release
msbuild %LUABRIDGE_SOL% /p:configuration=Debug /t:ALL_BUILD /p:Platform=x64
msbuild %LUABRIDGE_SOL% /p:configuration=Release /t:ALL_BUILD /p:Platform=x64

cd %WORKING_DIR%

echo Build y Compilacion de LuaBridge terminada.
echo Automatizacion de LuaBridge terminada.

:end