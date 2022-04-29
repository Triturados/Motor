@echo off

rem Este .bat se encuentra en el directorio Dependencies/Scripts

rem Variables de directorios
set CMAKE_EXE=..\CMAKE\bin\cmake.exe
set OGRE_SRC=..\OgreSrc\
set OGRE_BUILD=..\OgreBuild\ 
set OGRE_SOL=..\OgreBuild\OGRE.sln
set EXES_DIR=..\..\exes\

rem Creamos el directorio donde se van a generar los archivos comprobando si no esta creado ya
if not exist ..\OgreBuild\ mkdir ..\OgreBuild\
if exist %OGRE_SOL% goto end

echo Generando la build de Ogre y compilando la solucion...

%CMAKE_EXE%  -D CMAKE_CONFIGURATION_TYPES:STRING=Debug;Release ^
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
msbuild %OGRE_SOL% /p:configuration=Debug /t:ALL_BUILD /p:Platform=x64 /p:PlatformToolset=v142 
msbuild %OGRE_SOL% /p:configuration=Release /t:ALL_BUILD /p:Platform=x64 /p:PlatformToolset=v142

echo Build y Compilacion de OGRE terminada.

rem Copia de .dlls
echo Copiando .dlls de Ogre...

copy ..\OgreBuild\bin\release\OgreMain.dll %EXES_DIR% /y 1>nul
copy ..\OgreBuild\bin\release\OgreOverlay.dll %EXES_DIR% /y 1>nul
copy ..\OgreBuild\bin\release\Plugin_ParticleFX.dll %EXES_DIR% /y 1>nul
copy ..\OgreBuild\bin\release\RenderSystem_GL.dll %EXES_DIR% /y 1>nul
copy ..\OgreBuild\bin\release\Codec_STBI.dll %EXES_DIR% /y 1>nul
copy ..\OgreBuild\bin\release\Codec_Assimp.dll %EXES_DIR% /y 1>nul
copy ..\OgreBuild\bin\release\zlib.dll %EXES_DIR% /y 1>nul
copy ..\OgreBuild\bin\release\OgreBites.dll %EXES_DIR% /y 1>nul
copy ..\OgreBuild\bin\release\OgreRTShaderSystem.dll %EXES_DIR% /y 1>nul

copy ..\OgreBuild\bin\debug\OgreBites_d.dll %EXES_DIR% /y 1>nul
copy ..\OgreBuild\bin\debug\OgreRTShaderSystem_d.dll %EXES_DIR% /y 1>nul
copy ..\OgreBuild\bin\debug\OgreMain_d.dll %EXES_DIR% /y 1>nul
copy ..\OgreBuild\bin\debug\OgreOverlay_d.dll %EXES_DIR% /y 1>nul
copy ..\OgreBuild\bin\debug\Plugin_ParticleFX_d.dll %EXES_DIR% /y 1>nul
copy ..\OgreBuild\bin\debug\RenderSystem_GL_d.dll %EXES_DIR% /y 1>nul
copy ..\OgreBuild\bin\debug\Codec_STBI_d.dll %EXES_DIR% /y 1>nul

echo .Dlls copiadas con exito.
echo Automatizacion de Ogre terminada.

:end