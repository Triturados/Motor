@echo off

rem El directorio actual es Skeleton\dependencies\Scripts

cd ..\LuaBridgeHelpersFile

xcopy LuaHelpers.h ..\LuaBridgeSrc\Source\LuaBridge\detail /y

rem Devolvemos la ruta de entrada a este archivo
cd ..\Scripts