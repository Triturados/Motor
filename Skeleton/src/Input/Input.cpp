#include "Input.h"
//#include <SDL.h>
#include <cassert>
#include <SingletonInfo.h>

Input* Input::_instance = nullptr;

Input* Input::getInstance()
{
	if (_instance == nullptr) {
		_instance = static_cast<Input*>(LoveEngine::Singleton::getElement(LoveEngine::Singleton::positions::Input));
	}
	return _instance;
}

Input::Input()
{
	if (_instance != nullptr) {
		assert(false);
	}

	Input::_instance = this;
	LoveEngine::Singleton::addElement(this, LoveEngine::Singleton::positions::Input);
}

//teclas = new std::unordered_map<SDL_KeyCode, tecla>();


bool Input::handleInput()
{
	SDL_Event sdlevent;
	while (SDL_PollEvent(&sdlevent)) {
		switch (sdlevent.type) {
		case SDL_KEYDOWN:
		{
			int enumvalue = (int)sdlevent.key.keysym.scancode - 4;
			std::cout << enumvalue << std::endl;

			lastPressedKeys->insert(sdlevent.key.keysym.scancode);
			break;
		}
		case SDL_KEYUP:
			lastPressedKeys->erase(sdlevent.key.keysym.scancode);
			std::cout << "Tecla soltada: " << (int)sdlevent.key.keysym.scancode << std::endl;
			break;
		case SDL_MOUSEMOTION:
			SDL_GetMouseState(&mouseX, &mouseY);
			std::cout << "Ratón movido: " << mouseX << " " << mouseY << std::endl;
			break;
		case SDL_MOUSEBUTTONDOWN:
			if(sdlevent.button.button == SDL_BUTTON_LEFT)
				mouseState = MouseState::CLICK_L;
			else if(sdlevent.button.button == SDL_BUTTON_RIGHT)
				mouseState = MouseState::CLICK_R;
			else if (sdlevent.button.button == SDL_BUTTON_MIDDLE)
				mouseState = MouseState::CLICK_M;
			std::cout << "Ratón pulsado: " << (int)MouseState::CLICK_M << std::endl;
			break;
		case SDL_MOUSEBUTTONUP:
			mouseState = MouseState::NONE;
			std::cout << "Ratón soltado." << std::endl;
			break;
		case SDL_QUIT:
			return false;
			break;
		default:
			break;
		}
	}
	return true;
}
bool Input::isKeyPressed(InputKeys key)
{
	return lastPressedKeys->count((SDL_Scancode)((int)key + 4));
}

//
//void Input::addListener(SDL_KeyCode k, Component* c)
//{
//	/*auto t = teclas
//	t->second.suscriptores.push_back(c);*/
//}


void Input::setSDLwithOgreTest() {
	SDL_Init(SDL_INIT_VIDEO);
	//SDL_Surface* screen = SDL_SetVideoMode(640, 480, 0, SDL_OPENGL);
}

int Input::initSDLWindowTest() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "Failed to initialize the SDL2 library\n";
		return -1;
	}

	SDL_Window* window = SDL_CreateWindow("SDL2 Window",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		680, 480,
		0);

	if (!window)
	{
		std::cout << "Failed to create window\n";
		return -1;
	}

	SDL_Surface* window_surface = SDL_GetWindowSurface(window);

	if (!window_surface)
	{
		std::cout << "Failed to get the surface from the window\n";
		return -1;
	}

	SDL_UpdateWindowSurface(window);

	SDL_Delay(5000);
}