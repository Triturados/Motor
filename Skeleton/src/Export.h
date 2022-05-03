#pragma once

//#ifdef LOVEXPORT
#define lovexport __declspec( dllexport )
//#elif
//#define lovexport __declspec( dllimport )
//#endif
#define clovexport extern "C" lovexport
