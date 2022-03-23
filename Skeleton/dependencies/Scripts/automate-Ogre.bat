@echo off

rem El directorio actual es Skeleton\dependencies\Scripts

cd ..\OgreBuild\bin\debug

rem Primero las dll de Debug
xcopy Codec_STBI_d.dll ..\..\..\..\exes /y
xcopy DefaultSamples_d.dll ..\..\..\..\exes /y
xcopy OgreBites_d.dll ..\..\..\..\exes /y
xcopy OgreMain_d.dll ..\..\..\..\exes /y
xcopy OgreMeshLodGenerator_d.dll ..\..\..\..\exes /y
xcopy OgreOverlay_d.dll ..\..\..\..\exes /y
xcopy OgrePaging_d.dll ..\..\..\..\exes /y
xcopy OgreProperty_d.dll ..\..\..\..\exes /y
xcopy OgreRTShaderSystem_d.dll ..\..\..\..\exes /y
xcopy OgreTerrain_d.dll ..\..\..\..\exes /y
xcopy OgreVolume_d.dll ..\..\..\..\exes /y
xcopy Plugin_BSPSceneManager_d.dll ..\..\..\..\exes /y
xcopy Plugin_OctreeSceneManager_d.dll ..\..\..\..\exes /y
xcopy Plugin_OctreeZone_d.dll ..\..\..\..\exes /y
xcopy Plugin_ParticleFX_d.dll ..\..\..\..\exes /y
xcopy Plugin_PCZSceneManager_d.dll ..\..\..\..\exes /y
xcopy RenderSystem_GL_d.dll ..\..\..\..\exes /y
xcopy RenderSystem_GL3Plus_d.dll ..\..\..\..\exes /y
xcopy SDL2.dll ..\..\..\..\exes /y
xcopy zlib.dll ..\..\..\..\exes /y

rem Luego las dll de Release

cd ..\release

xcopy Codec_Assimp.dll ..\..\..\..\exes /y
xcopy Codec_STBI.dll ..\..\..\..\exes /y
xcopy DefaultSamples.dll ..\..\..\..\exes /y
xcopy OgreBites.dll ..\..\..\..\exes /y
xcopy OgreMain.dll ..\..\..\..\exes /y
xcopy OgreMeshLodGenerator.dll ..\..\..\..\exes /y
xcopy OgreOverlay.dll ..\..\..\..\exes /y
xcopy OgrePaging.dll ..\..\..\..\exes /y
xcopy OgreProperty.dll ..\..\..\..\exes /y
xcopy OgreRTShaderSystem.dll ..\..\..\..\exes /y
xcopy OgreTerrain.dll ..\..\..\..\exes /y
xcopy OgreVolume.dll ..\..\..\..\exes /y
xcopy Plugin_BSPSceneManager.dll ..\..\..\..\exes /y
xcopy Plugin_DotScene.dll ..\..\..\..\exes /y
xcopy Plugin_OctreeSceneManager.dll ..\..\..\..\exes /y
xcopy Plugin_OctreeZone.dll ..\..\..\..\exes /y
xcopy Plugin_ParticleFX.dll ..\..\..\..\exes /y
xcopy Plugin_PCZSceneManager.dll ..\..\..\..\exes /y
xcopy RenderSystem_GL.dll ..\..\..\..\exes /y
xcopy RenderSystem_GL3Plus.dll ..\..\..\..\exes /y
xcopy SDL2.dll ..\..\..\..\exes /y
xcopy zlib.dll ..\..\..\..\exes /y

rem Devolvemos la ruta de entrada a este archivo
cd ..\..\..\Scripts
