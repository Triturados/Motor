@echo off

rem Este .bat se encuentra en el directorio Dependencies/Scripts

rem Variables de directorios
set WORKING_DIR=%cd%
set DEPENDENCIES_DIR=..\
set CMAKE_EXE=..\CMAKE\bin\
set BULLET_SRC=..\BulletSrc\
set BULLET_BUILD=..\BulletBuild\ 
set BULLET_SOL=..\BulletBuild\BULLET_PHYSICS.sln

cd %DEPENDENCIES_DIR%

rem Creamos el directorio donde se van a generar los archivos comprobando si no esta creado ya
if not exist %BULLET_BUILD% mkdir %BULLET_BUILD%
if exist %BULLET_SOL% goto end

echo Generando la build de Bullet y compilando la solucion...

cd %CMAKE_EXE%

cmake -D CMAKE_CONFIGURATION_TYPES:STRING=Debug;Release ^
      -D BUILD_BULLET2_DEMOS:BOOL=0 ^
      -D BUILD_CPU_DEMOS:BOOL=0 ^
      -D BUILD_OPENGL3_DEMOS:BOOL=0 ^
      -D USE_MSVC_RUNTIME_LIBRARY_DLL:BOOL=1 ^
      -S %BULLET_SRC% -B %BULLET_BUILD%

rem Compilacion de la solucion en Debug y en Release
msbuild %BULLET_SOL% /p:configuration=Debug /t:ALL_BUILD /p:Platform=x64
msbuild %BULLET_SOL% /p:configuration=Release /t:ALL_BUILD /p:Platform=x64

cd %WORKING_DIR%

echo Build y Compilacion de Bullet terminada.
echo Automatizacion de Ogre terminada.

:end