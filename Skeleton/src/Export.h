#pragma once

#define lovexport __declspec( dllexport )
#define clovexport extern "C" lovexport
