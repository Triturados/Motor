#include <iostream>

#include "Engine.h"
#include "checkML.h"

#ifdef _DEBUG
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

#else
#include <Windows.h>
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, int nCmdShow) {
#endif

	LoveEngine::Engine engine;

	if (engine.setup()) {
		return -1;
	}

	engine.loop();

	engine.quit();


	std::cout << "Bye bye!";

	std::cout << "\n"
		R"( _                     _____             _            )""\n"
		R"(| |    _____   _____  | ____|_ __   __ _(_)_ __   ___ )""\n"
		R"(| |   / _ \ \ / / _ \ |  _| | '_ \ / _` | | '_ \ / _ \)""\n"
		R"(| |__| (_) \ V /  __/ | |___| | | | (_| | | | | |  __/)""\n"
		R"(|_____\___/ \_/ \___| |_____|_| |_|\__, |_|_| |_|\___|)""\n"
		R"(              a game made with love |___/             )""\n";

	return 0;
}