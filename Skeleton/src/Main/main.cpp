#include <iostream>

#include "Game.h"
#include "checkML.h"

int main()
{

#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	LoveEngine::Game g;

	if (g.setup()) {
		return -1;
	}

	g.loop();

	g.quit();


	std::cout << "Bye bye!";
	return 0;
}