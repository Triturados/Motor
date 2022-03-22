
namespace LoveSingleton {
	const int singletonCount = 4;

	enum class positions {
		SceneManager, Time, Input, Component
	};

	typedef void (*singletonIN)(void*, int);
	typedef void* (*singletonOUT)(int);
}