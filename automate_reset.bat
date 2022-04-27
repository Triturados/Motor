@echo off

title Automatizacion - Proceso de reset
echo Comenzando con el reset.

rem Variables de directorio
set WORKING_DIR=%cd%
set OGRE_BUILD_DIR=.\Skeleton\dependencies\OgreBuild\
set BULLET_BUILD_DIR=.\Skeleton\dependencies\BulletBuild\
set LUABRIDGE_BUILD_DIR=.\Skeleton\dependencies\LuaBridgeBuild\
set EXES_DIR=.\Skeleton\exes\
set LIBS_DIR=.\Skeleton\libs\
set TEMP_DIR=.\Skeleton\temp\

echo Borrando builds de SDL2 y OGRE...
if exist %OGRE_BUILD_DIR% rmdir /s /q %OGRE_BUILD_DIR%
echo Builds de SDL2 y OGRE borradas.

echo Borrando build de Bullet...
if exist %BULLET_BUILD_DIR% rmdir /s /q %BULLET_BUILD_DIR%
echo Build de Bullet borrada.

echo Borrando build de LuaBridge...
if exist %LUABRIDGE_BUILD_DIR% rmdir /s /q %LUABRIDGE_BUILD_DIR%
echo Build de LuaBridge borrada.

echo Borrando la carpeta libs
if exist %LIBS_DIR% rmdir /s /q %LIBS_DIR%
echo Directorio libs borrado.

echo Borrando la carpeta temp
if exist %TEMP_DIR% rmdir /s /q %TEMP_DIR%
echo Directorio temp borrado.

echo Borrando la carpeta exes
if exist %EXES_DIR% rmdir /s /q %EXES_DIR%
echo Directorio exes borrado.

echo Reset completado.