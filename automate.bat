@echo off

title Automatizacion - Proceso de compilacion de librerias
echo Comenzando con la automatizacion!

cd Skeleton\dependencies

@REM rem Parte de OGRE
@REM echo Compilando OGRE!

@REM mkdir OgreBuild
@REM cd CMAKE\bin

@REM cmake -S "..\..\OgreSrc" -B "..\..\OgreBuild"

@REM cd ..\..\OgreBuild
@REM msbuild "OGRE.sln" /p:configuration=Debug /t:ALL_BUILD /p:Platform=x64
@REM msbuild "OGRE.sln" /p:configuration=Release /t:ALL_BUILD /p:Platform=x64

@REM echo Compilacion de OGRE terminada!


@REM rem Parte de Bullet
@REM echo Compilando BULLET PHYSICS!

@REM cd ..\

@REM mkdir BulletBuild
@REM cd CMAKE\bin

@REM cmake -D USE_MSVC_RUNTIME_LIBRARY_DLL=TRUE -D BUILD_BULLET2_DEMOS=FALSE -D BUILD_BULLET_ROBOTICS_EXTRA=FALSE -D BUILD_BULLET_ROBOTICS_GUI_EXTRA=FALSE -D BUILD_CPU_DEMOS=FALSE -D BUILD_OPENGL3_DEMOS=FALSE -S "..\..\BulletSrc" -B "..\..\BulletBuild"

@REM  cd ..\..\BulletBuild

@REM msbuild "BULLET_PHYSICS.sln" /p:configuration=Debug /t:ALL_BUILD /p:Platform=x64
@REM msbuild "BULLET_PHYSICS.sln" /p:configuration=Release /t:ALL_BUILD /p:Platform=x64

@REM echo Compilacion de BULLET PHYSICS terminada!



@REM rem Parte de SDL2
@REM echo Compilando SDL2!

@REM cd ..\OgreBuild\SDL2-build
@REM msbuild "SDL2.sln" /p:configuration=Debug /t:ALL_BUILD /p:Platform=x64
@REM msbuild "SDL2.sln" /p:configuration=Release /t:ALL_BUILD /p:Platform=x64

@REM echo Compilacion de SDL2 terminada!



rem Parte de LuaBridge 

rem cd ..\..\
mkdir LuaBridgeBuild

cd CMAKE\bin
cmake -D LUABRIDGE_CXX17=TRUE -S "..\..\LuaBridgeSrc" -B "..\..\LuaBridgeBuild"

cd ..\..\LuaBridgeBuild

msbuild "LuaBridge.sln" /p:configuration=Debug /t:ALL_BUILD /p:Platform=x64
msbuild "LuaBridge.sln" /p:configuration=Release /t:ALL_BUILD /p:Platform=x64

echo Compilacion de LuaBridge terminada!

rem rem Moviendo archivos (dll) necesarios (.bat individual para cada libreria)
echo Ejecutando Scripts individuales!

cd ..\Scripts

rem OGRE
rem call automate-Ogre.bat

rem FMOD
rem call automate-FMOD.bat

rem LuaBridge
call automate-LuaBridge.bat

rem SDL2
rem call automate-SDL2.bat


echo Proceso terminado!

pause
exit