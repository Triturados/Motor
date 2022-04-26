#include <iostream>

#include "Engine.h"
#include "checkML.h"

int main()
{

#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	LoveEngine::Engine engine;

	if (engine.setup()) {
		return -1;
	}

	engine.loop();

	engine.quit();


	std::cout << "Bye bye!";
	return 0;
}