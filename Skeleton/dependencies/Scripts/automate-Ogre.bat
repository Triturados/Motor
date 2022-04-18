@echo off

rem Este .bat se encuentra en el directorio Dependencies/Scripts

rem Variables de directorios
set WORKING_DIR=%cd%
set DEPENDENCIES_DIR=..\
set CMAKE_EXE=..\CMAKE\bin\
set OGRE_SRC=..\OgreSrc\
set OGRE_BUILD=..\OgreBuild\ 
set OGRE_SOL=..\OgreBuild\OGRE.sln
set EXES_DIR=..\..\exes\
set DLLS_RELEASE_DIR=..\OgreBuild\bin\release\
set DLLS_DEBUG_DIR=..\OgreBuild\bin\debug\

cd %DEPENDENCIES_DIR%

rem Creamos el directorio donde se van a generar los archivos comprobando si no esta creado ya
if not exist %BUILD_DIR% mkdir %BUILD_DIR%
if exist %OGRE_BUILD_SOL% goto end

echo Generando la build de Ogre y compilando la solucion...

cd %CMAKE_EXE%

cmake -D CMAKE_CONFIGURATION_TYPES:STRING=Debug;Release ^
             -D OGRE_BUILD_COMPONENT_BITES:BOOL=0 ^
             -D OGRE_BUILD_PLUGIN_DOT_SCENE:BOOL=0 ^
             -D OGRE_BUILD_RENDERSYSTEM_D3D9:BOOL=0 ^
             -D OGRE_BUILD_RENDERSYSTEM_GLES2:BOOL=0 ^
             -D OGRE_BUILD_RENDERSYSTEM_TINY:BOOL=0 ^
             -D OGRE_BUILD_RENDERSYSTEM_VULKAN:BOOL=0 ^
             -D OGRE_BUILD_RTSHADERSYSTEM_SHADERS:BOOL=1 ^
             -D OGRE_BUILD_SAMPLES:BOOL=0 ^
             -D OGRE_INSTALL_SAMPLES:BOOL=0 ^
             -S %OGRE_SRC% -B %OGRE_BUILD%

rem Compilacion de la solucion en Debug y en Release
msbuild %OGRE_SOL% /p:configuration=Debug /t:ALL_BUILD /p:Platform=x64
msbuild %OGRE_SOL% /p:configuration=Release /t:ALL_BUILD /p:Platform=x64

echo Build y Compilacion de OGRE terminada.

rem Copia de .dlls
echo Copiando .dlls de Ogre...

cd %DLLS_RELEASE_DIR%

copy OgreMain.dll %EXES_DIR% 1>nul
copy OgreOverlay.dll %EXES_DIR% 1>nul
copy Plugin_ParticleFX.dll %EXES_DIR% 1>nul
copy RenderSystem_GL.dll %EXES_DIR% 1>nul
copy Codec_STBI.dll %EXES_DIR% 1>nul
copy Codec_Assimp.dll %EXES_DIR% 1>nul
copy zlib.dll %EXES_DIR% 1>nul

if %RELEASE_ENGINE% == false (

    cd %DLLS_DEBUG_DIR%

    copy OgreMain_d.dll %EXES_DIR% 1>nul
    copy OgreOverlay_d.dll %EXES_DIR% 1>nul
    copy Plugin_ParticleFX_d.dll %EXES_DIR% 1>nul
    copy RenderSystem_GL_d.dll %EXES_DIR% 1>nul
    copy Codec_STBI_d.dll %EXES_DIR% 1>nul
)

cd %WORKING_DIR%

echo .Dlls copiadas con exito.
echo Automatizacion de Ogre terminada.

:end
