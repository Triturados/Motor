#pragma once

namespace LoveEngine {
	namespace Singleton {

		enum class positions {
			hola
		};

		typedef void (*singletonIN)(void*, int);
		typedef void* (*singletonOUT)(int);

		void* getElement(positions pos);
		void  addElement(void* elem, positions pos);
	}
}