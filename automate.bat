@echo off

title Automatizacion - Proceso de compilacion de librerias
echo Comenzando con la automatizacion!

@REM rem Parte de OGRE
@REM echo Compilando OGRE!

@REM cd Skeleton\dependencies
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



rem Parte de LuaBridge descargando el codigo fuente desde github

rem cd ..\..\
cd Skeleton\dependencies
mkdir LuaBridgeBuild

cd Git\bin

git clone --recurse-submodules https://github.com/vinniefalco/LuaBridge.git ..\..\LuaBridgeSrc

cd ..\..\CMAKE\bin
cmake -D LUABRIDGE_CXX17=TRUE -S "..\..\LuaBridgeSrc" -B "..\..\LuaBridgeBuild"

cd ..\..\LuaBridgeBuild

msbuild "LuaBridge.sln" /p:configuration=Debug /t:ALL_BUILD /p:Platform=x64
msbuild "LuaBridge.sln" /p:configuration=Release /t:ALL_BUILD /p:Platform=x64

call automate-LuaBridge.bat

echo Compilacion de LuaBridge terminada!



rem Parte de LuaBridge subiendo el codigo fuente al repositorio

@REM cd ..\..\

@REM mkdir LuaBridgeBuild
@REM cd CMAKE\bin
@REM cmake -D LUABRIDGE_CXX17=TRUE -S "..\..\LuaBridgeSrc" -B "..\..\LuaBridgeBuild"

@REM cd ..\..\LuaBridgeBuild

@REM msbuild "LuaBridge.sln" /p:configuration=Debug /t:ALL_BUILD /p:Platform=x64
@REM msbuild "LuaBridge.sln" /p:configuration=Release /t:ALL_BUILD /p:Platform=x64

@REM echo Compilacion de LuaBridge terminada!



rem rem Moviendo archivos (dll) necesarios (.bat individual para cada libreria)
@REM echo Ejecutando Scripts individuales!

@REM cd ..\Scripts

@REM rem OGRE
@REM call automate-Ogre.bat

@REM rem FMOD
@REM call automate-FMOD.bat

@REM rem LuaBridge
@REM @REM call automate-LuaBridge.bat

@REM rem SDL2
@REM call automate-SDL2.bat


echo Proceso terminado!

pause
exit