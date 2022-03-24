@echo off

title Automatizacion - Proceso de compilacion de librerias
echo Comenzando con la automatizacion!

cd Skeleton\dependencies

rem Parte de OGRE
echo Compilando OGRE!

mkdir OgreBuild
cd CMAKE\bin

cmake -S "..\..\OgreSrc" -B "..\..\OgreBuild"

cd ..\..\OgreBuild
msbuild "OGRE.sln" /p:configuration=Debug /t:ALL_BUILD /p:Platform=x64
msbuild "OGRE.sln" /p:configuration=Release /t:ALL_BUILD /p:Platform=x64

echo Compilacion de OGRE terminada!


rem Parte de Bullet
echo Compilando BULLET PHYSICS!

cd ..\

mkdir BulletBuild
cd CMAKE\bin

cmake -D USE_MSVC_RUNTIME_LIBRARY_DLL=TRUE -D BUILD_BULLET2_DEMOS=FALSE -D BUILD_BULLET_ROBOTICS_EXTRA=FALSE -D BUILD_BULLET_ROBOTICS_GUI_EXTRA=FALSE -D BUILD_CPU_DEMOS=FALSE -D BUILD_OPENGL3_DEMOS=FALSE -S "..\..\BulletSrc" -B "..\..\BulletBuild"

 cd ..\..\BulletBuild

msbuild "BULLET_PHYSICS.sln" /p:configuration=Debug /t:ALL_BUILD /p:Platform=x64
msbuild "BULLET_PHYSICS.sln" /p:configuration=Release /t:ALL_BUILD /p:Platform=x64

echo Compilacion de BULLET PHYSICS terminada!



rem Parte de SDL2
echo Compilando SDL2!

cd ..\OgreBuild\SDL2-build
msbuild "SDL2.sln" /p:configuration=Debug /t:ALL_BUILD /p:Platform=x64
msbuild "SDL2.sln" /p:configuration=Release /t:ALL_BUILD /p:Platform=x64

echo Compilacion de SDL2 terminada!



rem Parte de LuaBridge descargando el codigo fuente desde github

cd ..\..\
mkdir LuaBridgeBuild

cd Git\bin

git clone --recurse-submodules https://github.com/vinniefalco/LuaBridge.git ..\..\LuaBridgeSrc

cd ..\..\CMAKE\bin
cmake -D LUABRIDGE_CXX17=TRUE -S "..\..\LuaBridgeSrc" -B "..\..\LuaBridgeBuild"

cd ..\..\LuaBridgeBuild

msbuild "LuaBridge.sln" /p:configuration=Debug /t:ALL_BUILD /p:Platform=x64
msbuild "LuaBridge.sln" /p:configuration=Release /t:ALL_BUILD /p:Platform=x64

echo Compilacion de LuaBridge terminada!

rem rem Moviendo archivos (dll) necesarios (.bat individual para cada libreria)
echo Ejecutando Scripts individuales!

cd ..\Scripts

rem OGRE
call automate-Ogre.bat

rem FMOD
call automate-FMOD.bat

rem LuaBridge
call automate-LuaBridge.bat

rem SDL2
call automate-SDL2.bat


echo Proceso terminado!

pause
exit