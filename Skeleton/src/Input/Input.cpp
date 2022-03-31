#include "Input.h"
#include "Error_handling.h"
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
			std::cout << "Rat�n movido: " << mouseX << " " << mouseY << std::endl;
			break;
		case SDL_MOUSEBUTTONDOWN:
			if(sdlevent.button.button == SDL_BUTTON_LEFT)
				mouseState = MouseState::CLICK_L;
			else if(sdlevent.button.button == SDL_BUTTON_RIGHT)
				mouseState = MouseState::CLICK_R;
			else if (sdlevent.button.button == SDL_BUTTON_MIDDLE)
				mouseState = MouseState::CLICK_M;
			std::cout << "Rat�n pulsado: " << (int)MouseState::CLICK_M << std::endl;
			break;
		case SDL_MOUSEBUTTONUP:
			mouseState = MouseState::NONE;
			std::cout << "Rat�n soltado." << std::endl;
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
bool InputManager::isKeyPressed(InputKeys key)
{
	return lastPressedKeys->count((SDL_Scancode)((int)key + 4));
}

//
//void Input::addListener(SDL_KeyCode k, Component* c)
//{
//	/*auto t = teclas
//	t->second.suscriptores.push_back(c);*/
//}

void InputManager::setSDLwithOgreTest() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) throwINPUTError(__LINE__);
	//SDL_Surface* screen = SDL_SetVideoMode(640, 480, 0, SDL_OPENGL);
}

void InputManager::initSDLWindowTest() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) throwINPUTError(__LINE__);

	SDL_Window* window = SDL_CreateWindow("SDL2 Window",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		680, 480,
		0);

	if (!window) throwINPUTError(__LINE__);

	SDL_Surface* window_surface = SDL_GetWindowSurface(window);

	if (!window_surface) throwINPUTError(__LINE__);

	if(SDL_UpdateWindowSurface(window) < 0)  throwINPUTError(__LINE__);

	SDL_Delay(5000);
}

void InputManager::throwINPUTError(int errorLine) {
	LoveEngine::ErrorHandling::throwError(__PROJECT_NAME__, errorLine, __FILENAME__, SDL_GetError());
}
