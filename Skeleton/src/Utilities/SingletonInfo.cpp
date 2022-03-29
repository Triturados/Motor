#include "SingletonInfo.h"
#include <Windows.h>
#include <cassert>

namespace LoveEngine {
	namespace Singleton {
		void* getElement(positions pos)
		{

#ifdef _DEBUG
			HMODULE hModule = LoadLibrary(TEXT("Singleton_d.dll"));
#else
			HMODULE hModule = LoadLibrary(TEXT("Singleton.dll"));
#endif

			assert(hModule != NULL);

			int idx = (int)pos;

			singletonOUT value = (singletonOUT)GetProcAddress(hModule, "getElement");

			assert(value != NULL);

			FreeLibrary(hModule);
			return value(idx);
		}

		void addElement(void* elem, positions pos)
		{
#ifdef _DEBUG
			HMODULE hModule = LoadLibrary(TEXT("Singleton_d.dll"));
#else
			HMODULE hModule = LoadLibrary(TEXT("Singleton.dll"));
#endif

			assert(hModule != NULL);

			int idx = (int)pos;

			singletonIN value = (singletonIN)GetProcAddress(hModule, "createElement");

			assert(value != NULL);

			value(elem, idx);

			FreeLibrary(hModule);
		}
	}
}
