#define SDL_MAIN_HANDLED
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

	bool success = true;
	try {
		g.quit();
	}
	catch (std::exception e) {
		std::cout << e.what() << "\n";
		success = false;
	}
	catch (...) {
		std::cout << "Excepción no controlada.\n";
		success = false;
	}

	if (!success) {
		std::cout << "Error en la destructora del motor.\n";
	}

	std::cout << "Bye bye!";
	return 0;
}