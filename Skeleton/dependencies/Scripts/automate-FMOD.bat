@echo off

rem El directorio actual es Skeleton\dependencies\Scripts

cd ..\FMODStudioAPIWindows\dlls

xcopy fmod.dll ..\..\..\exes /y
xcopy fmodL.dll ..\..\..\exes /y
xcopy fmodstudio.dll ..\..\..\exes /y
xcopy fmodstudioL.dll ..\..\..\exes /y

rem Devolvemos la ruta de entrada a este archivo
cd ..\..\Scripts