rem El directorio actual es Skeleton\dependencies\Scripts

cd ..\OgreBuild\SDL2Build\Debug

xcopy SDL2d.dll ..\..\..\..\build\Debug\Main /y

cd ..\Release

xcopy SDL2.dll ..\..\..\..\build\Release\Main /y

rem Devolvemos la ruta de entrada a este archivo
cd ..\Scripts