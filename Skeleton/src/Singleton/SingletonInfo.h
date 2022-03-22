
namespace LoveSingleton {
	const int singletonCount = 3;

	enum class positions {
		SceneManager, Time, Input
	};

	typedef void (*singletonIN)(void*, int);
	typedef void* (*singletonOUT)(int);
}