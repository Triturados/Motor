#include <Windows.h>
#include <Singleton.h>

extern "C" {

	__declspec(dllexport) void* getElement(int idx) {
		return LoveSingleton::Singleton::getValue(idx);
	}
	__declspec(dllexport) void createElement(void* val, int pos) {
		LoveSingleton::Singleton::createElement(val, pos);
	}
}

