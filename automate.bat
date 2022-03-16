@echo off

title Automatizacion - Proceso de compilacion de librerias
echo Comenzando con la automatizacion!

rem Modulos: 
rem -MsBuild : Script que encuentra la ruta donde se encuentra el ejecutable de 
rem x64 Native Tools Command Prompt, necesario para el comando msbuild. Usamos esas tools
rem para poder compilar facilmente soluciones de Visual Studio.

rem Import-Module Scripts\MsBuild.psm1

rem Parte de OGRE
echo Compilando OGRE!

cd Skeleton\dependencies
mkdir OgreBuild
dir
cd CMAKE\bin

cmake -D SDL2_DIR=..\..\OgreBuild\Dependencies\cmake -S "..\..\OgreSrc" -B "..\..\OgreBuild"
 
 rem -D OGRE_INSTALL_SAMPLES=FALSE,
 rem -D OGRE_INSTALL_DOCS=FALSE,
 rem -D OGRE_INSTALL_PDB=FALSE,
 rem -D OGRE_BUILD_TOOLS=FALSE, 
 rem -D OGRE_BUILD_PLUGIN_OCTREE=FALSE,
 rem -D OGRE_BUILD_RENDERSYSTEM_GL3PLUS=FALSE,
 rem -D OGRE_BUILD_RENDERSYSTEM_GL=FALSE,


cd ..\..\OgreBuild
msbuild "OGRE.sln" /p:configuration=Debug /t:ALL_BUILD /p:Platform=x64
msbuild "OGRE.sln" /p:configuration=Release /t:ALL_BUILD /p:Platform=x64

rem Parte de Bullet
echo Compilando BULLET PHYSICS!

cd ..\

mkdir BulletBuild
cd CMAKE\bin

cmake -D USE_MSVC_RUNTIME_LIBRARY_DLL=TRUE -D BUILD_BULLET2_DEMOS=FALSE -D BUILD_BULLET_ROBOTICS_EXTRA=FALSE -D BUILD_BULLET_ROBOTICS_GUI_EXTRA=FALSE -D BUILD_CPU_DEMOS=FALSE -D BUILD_OPENGL3_DEMOS=FALSE -S "..\..\BulletSrc" -B "..\..\BulletBuild"

 cd ..\..\BulletBuild

msbuild "BULLET_PHYSICS.sln" /p:configuration=Debug /t:ALL_BUILD /p:Platform=x64
msbuild "BULLET_PHYSICS.sln" /p:configuration=Release /t:ALL_BUILD /p:Platform=x64

rem Parte de SDL2
echo Compilando SDL2!

cd ..\OgreBuild\SDL2-build
msbuild "SDL2.sln" /p:configuration=Debug /t:ALL_BUILD /p:Platform=x64
msbuild "SDL2.sln" /p:configuration=Release /t:ALL_BUILD /p:Platform=x64


rem Moviendo archivos (dll) necesarios (.bat individual para cada libreria)
echo Ejecutando Scripts individuales!

cd ..\..\Scripts

rem OGRE
call automate-Ogre.bat

rem FMOD
call automate-FMOD.bat

rem SDL2
call automate-SDL2.bat

rem Compilamos la solucion del motor
echo Compilando la solucion del motor!

cd ..\..\

msbuild "Skeleton.sln" /p:configuration=Debug /p:Platform=x64
msbuild "Skeleton.sln" /p:configuration=Release /p:Platform=x64

echo Proceso terminado!

pause
exit