#include <SDL.h>


#undef main
#include "Input.h"
//#include <SDL.h>
#include <iostream>

int main(int argc, char* argv[]) {
	//std::cout << SDL_SCANCODE_A << std::endl;
	//std::cout << SDL_SCANCODE_Z;
	Input::init();
	Input* inputMNGR = Input::getInstance();
	inputMNGR->handleInput();
	return 0;
}

