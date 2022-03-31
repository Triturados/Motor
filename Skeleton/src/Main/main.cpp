#define SDL_MAIN_HANDLED
#include <iostream>

#include "Game.h"
#include "checkML.h"

void main()
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	bool success = true;
	Game g;

	//Descomentar estas dos lineas para probar los metodos de testing
	//g.testing();
	//return;

	//Inicializaci�n de managers y librer�as
	try {
		g.setup();
	}
	catch (std::exception e) {
		std::cout << e.what() << "\n";
		success = false;
	}
	catch (...) {
		std::cout << "Excepci�n no controlada.\n";
		success = false;
	}

	if (!success) {
		std::cout << "Error al inicializar el motor.\n";
		return;
	}

	//Ejecuci�n del bucle principal
	try {
		g.loop();
	}
	catch (std::exception e) {
		std::cout << e.what() << "\n";
		success = false;
	}
	catch (...) {
		std::cout << "Excepci�n no controlada.\n";
		success = false;
	}

	if (!success) {
		std::cout << "Error en el bucle principal del motor.\n";
		return;
	}

	//Destructora del motor
	try {
		g.quit();
	}
	catch (std::exception e) {
		std::cout << e.what() << "\n";
		success = false;
	}
	catch (...) {
		std::cout << "Excepci�n no controlada.\n";
		success = false;
	}

	if (!success) {
		std::cout << "Error en la destructora del motor.\n";
		return;
	}

	std::cout << "Bye bye!";
}