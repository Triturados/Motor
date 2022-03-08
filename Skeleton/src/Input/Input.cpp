#include "Input.h"
Input* Input::_instance = nullptr;

Input* Input::getInstance()
{
	return _instance;
}

//teclas = new std::unordered_map<SDL_KeyCode, tecla>();
bool Input::init()
{
	if (_instance == nullptr) {
		_instance = new Input();
		
	}
	else return false;

	return true;
}

void Input::handleInput()
{
	SDL_Event sdlevent;
	while (SDL_PollEvent(&sdlevent)) {
		switch (sdlevent.type) {
		case SDL_KEYDOWN:
			break;
		case SDL_KEYUP:
			break;
		case SDL_MOUSEMOTION:
			break;
		case SDL_MOUSEBUTTONDOWN:
			break;
		case SDL_MOUSEBUTTONUP:
			break;
		case SDL_QUIT:
			break;
		default:
			break;
		}
	}
}

void Input::addListener(SDL_KeyCode k, Component* c)
{
	/*auto t = teclas
	t->second.suscriptores.push_back(c);*/
}
