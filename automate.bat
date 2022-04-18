@echo off

title Automatizacion - Proceso de compilacion de librerias
echo Comenzando con la automatizacion!

rem Variables de batch
set WORKING_DIR=%cd%
set SCRIPTS_DIR=.\Skeleton\dependencies\Scripts\
set SOLUTION_DIR=.\Skeleton\
set EXES_DIR=.\Skeleton\exes\

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

cd %WORKING_DIR%

echo Proceso terminado!

pause
exit