//#define SDL_MAIN_HANDLED
//#include <iostream>
//#include "Game.h"
//
//#ifdef _DEBUG
//#include "checkML.h"
//#endif
//
////Versi�n 1 : Variable global y funci�n como par�metro
//Game g;
//
//void setup() {
//	g.setup();
//}
//void loop() {
//	g.loop();
//}
//void quit() {
//	g.quit();
//}
//void testing() {
//	g.testing();
//}
//
//bool checkExceptions(void(*func)(void)) {
//
//	try {
//		func();
//	}
//	catch (std::exception e) {
//		std::cout << e.what() << "\n";
//		return false;
//	}
//	catch (...) {
//		std::cout << "Excepci�n no controlada\n";
//		return false;
//	}
//
//	return true;
//}
//
//void main()
//{
//#ifdef _DEBUG
//	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
//#endif
//
//	/*testing();
//
//	return;*/
//
//	//Inicializaci�n de managers y librer�as
//	if (!checkExceptions(setup)) std::cout << "Error al inicializar el motor\n";
//
//	//Ejecuci�n del bucle principal
//	if (!checkExceptions(loop)) std::cout << "Error en el bucle principal del motor\n";
//
//	//Destructora del motor
//	if (!checkExceptions(quit)) std::cout << "Error en la destructora del motor\n";
//
//	std::cout << "Bye bye!";
//}

//Versi�n 2: Todas las comprobaciones de excepciones en el main
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

	//Inicializaci�n de managers y librer�as
	try {
		g.testing();
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

//Versi�n 3: Encapsularlo en el Game
