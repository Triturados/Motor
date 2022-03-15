rem El directorio actual es Skeleton\dependencies\Scripts

cd ..\FMODStudioAPIWindows\dlls

xcopy fmod.dll ..\..\..\..\build\Debug\Main /y
xcopy fmodL.dll ..\..\..\..\build\Debug\Main /y
xcopy fmodstudio.dll ..\..\..\..\build\Debug\Main /y
xcopy fmodstudioL.dll ..\..\..\..\build\Debug\Main /y

xcopy fmod.dll ..\..\..\..\build\Release\Main /y
xcopy fmodL.dll ..\..\..\..\build\Release\Main /y
xcopy fmodstudio.dll ..\..\..\..\build\Release\Main /y
xcopy fmodstudioL.dll ..\..\..\..\build\Release\Main /y

rem Devolvemos la ruta de entrada a este archivo
cd ..\Scripts