#include <Windows.h>
#include <Singleton.h>

extern "C" {

	__declspec(dllexport) void* getElement(int idx) {
		return LoveEngine::Singleton::Singleton::getValue(idx);
	}
	__declspec(dllexport) void createElement(void* val, int pos) {
		LoveEngine::Singleton::Singleton::createElement(val, pos);
	}
}

