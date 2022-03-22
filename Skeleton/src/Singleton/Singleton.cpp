#include <Singleton.h>
#include <SingletonInfo.h>

namespace LoveSingleton {
	std::vector<void*> Singleton::elementos(singletonCount, nullptr);

	void Singleton::createElement(void* elem, int position)
	{
		elementos[position] = elem;
	}

	void* Singleton::getValue(int idx)
	{
		return elementos[idx];
	}
}