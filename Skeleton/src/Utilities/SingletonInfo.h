#pragma once

namespace LoveEngine {
	namespace Singleton {
		const int singletonCount = 4;

		enum class positions {
			SceneManager, Time, Input, ComponentFactory
		};

		typedef void (*singletonIN)(void*, int);
		typedef void* (*singletonOUT)(int);

		void* getElement(positions pos);
		void  addElement(void* elem, positions pos);
	}
}