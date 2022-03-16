@echo off

rem El directorio actual es Skeleton\dependencies\Scripts

cd ..\OgreBuild\SDL2-build\Debug

xcopy SDL2d.dll ..\..\..\..\exes /y

cd ..\Release

xcopy SDL2.dll ..\..\..\..\exes /y

rem Devolvemos la ruta de entrada a este archivo
cd ..\..\..\Scripts