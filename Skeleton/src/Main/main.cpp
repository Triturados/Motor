#define SDL_MAIN_HANDLED
#include <iostream>

#include "Game.h"
#include "checkML.h"
//#include <string>
//#include <StringFormater.h>
//#include <Vector3.h>

void main()
{
	//std::string message =
	//	"valor: 454231; vec: 2.13, 4, 0; gravedad: true; nombre: Dani";

	//LoveEngine::StringFormatter sf(message);

	//std::string nombre = sf.getString("nombre");
	//std::cout << nombre << "\n";

	//int valor = sf.getInt("valor");
	//bool gravedad = sf.getBool("gravedad");
	//Utilities::Vector3 vec = sf.getVector3("vec");
	//return;
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	bool success = true;
	Game g;

	//Descomentar estas dos lineas para probar los metodos de testing
	/*g.testing();
	return;*/

	//Inicialización de managers y librerías
	try {
		g.setup();
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
		std::cout << "Error al inicializar el motor.\n";
		return;
	}

	//Ejecución del bucle principal
	try {
		g.loop();
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
		std::cout << "Excepción no controlada.\n";
		success = false;
	}

	if (!success) {
		std::cout << "Error en la destructora del motor.\n";
	}

	std::cout << "Bye bye!";
}