#include "Input.h"
#include "Error_handling.h"
//#include <SDL.h>


InputManager::InputManager() {
	lastPressedKeys = new std::unordered_set<SDL_Scancode>();
	mouseState = MouseState::NONE;
	mouseX = mouseY = 0;
}

//teclas = new std::unordered_map<SDL_KeyCode, tecla>();

bool InputManager::handleInput()
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
	if (!SDL_Init(SDL_INIT_VIDEO)) throwINPUTError(__LINE__);
	//SDL_Surface* screen = SDL_SetVideoMode(640, 480, 0, SDL_OPENGL);
}

int InputManager::initSDLWindowTest() {
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
