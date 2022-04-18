@echo off

title Automatizacion - Proceso de reset
echo Comenzando con el reset.

rem Variables de directorio
set WORKING_DIR=%cd%
set OGRE_BUILD_DIR=.\Skeleton\dependencies\OgreBuild\
set BULLET_BUILD_DIR=.\Skeleton\dependencies\BulletBuild\
set LUABRIDGE_BUILD_DIR=.\Skeleton\dependencies\LuaBridgeBuild\

echo Borrando builds de SDL2 y OGRE...
if exist %OGRE_BUILD_DIR% rmdir /s /q %OGRE_BUILD_DIR%
echo Builds de SDL2 y OGRE borradas.

echo Borrando build de Bullet...
if exist %BULLET_BUILD_DIR% rmdir /s /q %BULLET_BUILD_DIR%
echo Build de Bullet borrada.

echo Borrando build de LuaBridge...
if exist %LUA_BUILD_DIR% rmdir /s /q %LUA_BUILD_DIR%
echo Build de LuaBridge borrada.

echo Borrando todas las .dlls copiadas en exes...
del /s .\exes\*.dll 1>nul
echo .Dlls borradas.

echo Reset completado.