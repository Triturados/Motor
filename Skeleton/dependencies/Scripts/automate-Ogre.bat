rem El directorio actual es Skeleton\dependencies\Scripts

cd ..\OgreBuild\bin\debug

rem Primero las dll de Debug
xcopy Codec_STBI_d.dll ..\..\..\..\build\Debug\Main /y
xcopy DefaultSamples_d.dll ..\..\..\..\build\Debug\Main /y
xcopy OgreBites_d.dll ..\..\..\..\build\Debug\Main /y
xcopy OgreMain_d.dll ..\..\..\..\build\Debug\Main /y
xcopy OgreMeshLodGenerator_d.dll ..\..\..\..\build\Debug\Main /y
xcopy OgreOverlay_d.dll ..\..\..\..\build\Debug\Main /y
xcopy OgrePaging_d.dll ..\..\..\..\build\Debug\Main /y
xcopy OgreProperty_d.dll ..\..\..\..\build\Debug\Main /y
xcopy OgreRTShaderSystem_d.dll ..\..\..\..\build\Debug\Main /y
xcopy OgreTerrain_d.dll ..\..\..\..\build\Debug\Main /y
xcopy OgreVolume_d.dll ..\..\..\..\build\Debug\Main /y
xcopy Plugin_BSPSceneManager_d.dll ..\..\..\..\build\Debug\Main /y
xcopy Plugin_OctreeSceneManager_d.dll ..\..\..\..\build\Debug\Main /y
xcopy Plugin_OctreeZone_d.dll ..\..\..\..\build\Debug\Main /y
xcopy Plugin_ParticleFX_d.dll ..\..\..\..\build\Debug\Main /y
xcopy Plugin_PCZSceneManager_d.dll ..\..\..\..\build\Debug\Main /y
xcopy RenderSystem_GL_d.dll ..\..\..\..\build\Debug\Main /y
xcopy RenderSystem_GL3Plus_d.dll ..\..\..\..\build\Debug\Main /y
xcopy SDL2.dll ..\..\..\..\build\Debug\Main /y
xcopy zlib.dll ..\..\..\..\build\Debug\Main /y

rem Luego las dll de Release

xcopy Codec_Assimp.dll ..\..\..\..\build\Release\Main /y
xcopy Codec_STBI.dll ..\..\..\..\build\Release\Main /y
xcopy DefaultSamples.dll ..\..\..\..\build\Release\Main /y
xcopy OgreBites.dll ..\..\..\..\build\Release\Main /y
xcopy OgreMain.dll ..\..\..\..\build\Release\Main /y
xcopy OgreMeshLodGenerator.dll ..\..\..\..\build\Release\Main /y
xcopy OgreOverlay.dll ..\..\..\..\build\Release\Main /y
xcopy OgrePaging.dll ..\..\..\..\build\Release\Main /y
xcopy OgreProperty.dll ..\..\..\..\build\Release\Main /y
xcopy OgreRTShaderSystem.dll ..\..\..\..\build\Release\Main /y
xcopy OgreTerrain.dll ..\..\..\..\build\Release\Main /y
xcopy OgreVolume.dll ..\..\..\..\build\Release\Main /y
xcopy Plugin_BSPSceneManager.dll ..\..\..\..\build\Release\Main /y
xcopy Plugin_DotScene.dll ..\..\..\..\build\Release\Main /y
xcopy Plugin_OctreeSceneManager.dll ..\..\..\..\build\Release\Main /y
xcopy Plugin_OctreeZone.dll ..\..\..\..\build\Release\Main /y
xcopy Plugin_ParticleFX.dll ..\..\..\..\build\Release\Main /y
xcopy Plugin_PCZSceneManager.dll ..\..\..\..\build\Release\Main /y
xcopy RenderSystem_GL.dll ..\..\..\..\build\Release\Main /y
xcopy RenderSystem_GL3Plus.dll ..\..\..\..\build\Release\Main /y
xcopy SDL2.dll ..\..\..\..\build\Release\Main /y
xcopy zlib.dll ..\..\..\..\build\Release\Main /y

rem Devolvemos la ruta de entrada a este archivo
cd ..\Scripts
