#include <SDL.h>

//
//#undef main
#include "Input.h"
//#include <SDL.h>
#include <iostream>

int main(int argc, char* argv[]) {
	std::cout << SDL_SCANCODE_A << std::endl; //4
	std::cout << SDL_SCANCODE_Z << std::endl; //29
	std::cout << SDLK_a << std::endl; //97
	std::cout << SDLK_z << std::endl; //122

	//The window we'll be rendering to
	SDL_Window* window = NULL;

	//The surface contained by the window
	SDL_Surface* screenSurface = NULL;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		//Create window
		window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 800, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
	}
	
	while (true)
	{

	}

	/*Input::init();
	Input* inputMNGR = Input::getInstance();
	inputMNGR->handleInput();*/
	return 0;
}

