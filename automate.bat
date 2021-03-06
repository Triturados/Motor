@echo off

title Automatizacion - Proceso de compilacion de librerias
echo Comenzando con la automatizacion!

rem Variables de batch
set ENGINE_ROOT_DIR=%cd%
set SCRIPTS_DIR=.\Skeleton\dependencies\Scripts\
set SKELETON_SLN=.\Skeleton\Skeleton.sln
set EXES_DIR=.\Skeleton\exes\
set SKELETON_DIR=.\Skeleton\

if not exist %EXES_DIR% mkdir %EXES_DIR%

cd %SCRIPTS_DIR%

rem Comilacion y copia de dlls de OGRE
call automate-Ogre.bat

rem Compilacion y copia de dlls de SDL2
call automate-SDL2.bat

rem Compilacion de Bullet
call automate-Bullet.bat

rem Compilacion de LuaBridge
call automate-LuaBridge.bat

rem Copia de dlls de FMOD
call automate-FMOD.bat

cd %ENGINE_ROOT_DIR%

rem Compilacion de la solucion del motor
msbuild %SKELETON_SLN% /p:configuration=Debug /p:Platform=x64
msbuild %SKELETON_SLN% /p:configuration=Release /p:Platform=x64

echo Proceso terminado!