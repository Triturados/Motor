@echo off

title Automatizacion - Proceso de compilacion de librerias
echo Comenzando con la automatizacion!

rem Modulos: 
rem -MsBuild : Script que encuentra la ruta donde se encuentra el ejecutable de 
rem Native Tools Command Prompt, necesario para el comando msbuild. Usamos esas tools
rem para poder compilar facilmente soluciones de Visual Studio.

rem Import-Module Scripts\MsBuild.psm1

rem Parte de OGRE

cd Skeleton\dependencies\OgreSrc
mkdir OgreBuild
cd ..\CMAKE\bin
cmake -D OGRE_BUILD_RENDERSYSTEM_D3D9=FALSE -D OGRE_BUILD_RENDERSYSTEM_GL3PLUS=FALSE -D OGRE_BUILD_RENDERSYSTEM_GL=FALSE -D OGRE_BUILD_RENDERSYSTEM_GLES2=FALSE -D OGRE_BUILD_PLUGIN_ASSIMP=FALSE -D OGRE_BUILD_PLUGIN_BSP=FALSE -D OGRE_BUILD_PLUGIN_OCTREE=FALSE -D OGRE_BUILD_PLUGIN_DOT_SCENE=FALSE -D OGRE_BUILD_PLUGIN_PCZ=FALSE -D OGRE_BUILD_COMPONENT_TERRAIN=FALSE -D OGRE_BUILD_COMPONENT_VOLUME=FALSE -D OGRE_BUILD_COMPONENT_BITES=FALSE -D OGRE_BUILD_COMPONENT_PYTHON=FALSE -D OGRE_BUILD_COMPONENT_JAVA=FALSE -D OGRE_BUILD_COMPONENT_CSHARP=FALSE -D OGRE_INSTALL_CMAKE=FALSE -D OGRE_INSTALL_SAMPLES=FALSE -D OGRE_INSTALL_DOCS=FALSE -D OGRE_INSTALL_PDB=FALSE -D OGRE_BUILD_TOOLS=FALSE -S "..\..\OgreSrc" -B "..\..\OgreBuild"
cd ..\..\OgreBuild
msbuild "OGRE.sln" /p:configuration=Debug
msbuild "OGRE.sln" /p:configuration=Release

rem Parte de Bullet

cd ..\BulletSrc
mkdir BulletBuild
cd ..\CMAKE\bin 
cmake -D USE_MSVC_RUNTIME_LIBRARY_DLL=TRUE -S "..\..\BulletSrc" -B "..\..\BulletBuild"
cd ..\..\BulletBuild
msbuild "OGRE.sln" /p:configuration=Debug
msbuild "OGRE.sln" /p:configuration=Release

rem Parte de SDL2

cd ..\OgreBuild\SDL2-build
msbuild "SDL2.sln" /p:configuration=Debug
msbuild "SDL2.sln" /p:configuration=Release

rem Ya estan compiladas todas las librerias, ahora toca compilar la solucion del motor para
rem generan el directorio Skeleton\build\Main donde se van a mover todas las dll necesarias

cd ..\..\..\..\Skeleton
msbuild "Skeleton.sln" /p:configuration=Debug
msbuild "Skeleton.sln" /p:configuration=Release

rem Moviendo archivos (dll) necesarios (.bat individual para cada libreria)

cd dependencies\Scripts

rem OGRE
call automate-Ogre.bat

rem FMOD
call automate-FMOD.bat

rem SDL2
call automate-SDL2.bat

pause
exit