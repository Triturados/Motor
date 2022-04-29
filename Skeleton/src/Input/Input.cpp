#include "Input.h"
#include "Error_handling.h"
#include <cassert>
#include <SingletonInfo.h>
#include <string>
#include <Vector2.h>
#include <SDL.h>
namespace LoveEngine {
	namespace Input {

		InputManager* InputManager::_instance = nullptr;

		InputManager* InputManager::getInstance()
		{
			return _instance;
		}

		InputManager::InputManager()
		{
			if (_instance != nullptr) {
				assert("No se ha podido crear la instancia del InputManager.", false);
			}

			InputManager::_instance = this;
			lastPressedKeys = new std::unordered_set<SDL_Scancode>();
			justPressedKeys = new std::unordered_set<SDL_Scancode>();
			mouseState = MouseState::NONE;
			mouseX = mouseY = 0;
			_mouseWheel = 0;

			InputManager::_instance = this;
			//LoveEngine::Singleton::addElement(this, LoveEngine::Singleton::positions::Input);

			if (!initialiseController()) {
				std::cout << "No se pudo inicializar ningun mando\n";
			}
		}

		InputManager::~InputManager()
		{
			delete lastPressedKeys;
			delete justPressedKeys;
			SDL_GameControllerClose(sdlcontroller);
		}

		void InputManager::mouseVisibility(bool inGame)
		{
			if (inGame)	SDL_SetRelativeMouseMode(SDL_TRUE);
			else SDL_SetRelativeMouseMode(SDL_FALSE);
		}

		bool InputManager::handleInput()
		{
			// Se vacian las teclas que fueron pulsadas justo en frame anterior
			bool mouseclicked = false;
			float mouseWheelValue = 0;
			justPressedKeys->clear();

			
			SDL_Event sdlevent;
			while (SDL_PollEvent(&sdlevent)) {
				switch (sdlevent.type) {
				case SDL_KEYDOWN:
				{
					if (lastPressedKeys->count(sdlevent.key.keysym.scancode) == 0)
						justPressedKeys->insert(sdlevent.key.keysym.scancode);
					lastPressedKeys->insert(sdlevent.key.keysym.scancode);
					break;
				}
				case SDL_KEYUP:
					lastPressedKeys->erase(sdlevent.key.keysym.scancode);
					//std::cout << "Tecla soltada: " << (int)sdlevent.key.keysym.scancode << std::endl;
					break;
				case SDL_MOUSEMOTION:
					relmouseX = sdlevent.motion.xrel;
					relmouseY = sdlevent.motion.yrel;
					SDL_GetMouseState(&mouseX, &mouseY);
					//std::cout << "Raton movido: " << mouseX << " " << mouseY << std::endl;
					break;
				case SDL_MOUSEBUTTONDOWN:
					if (sdlevent.button.button == SDL_BUTTON_LEFT) {
						mouseclicked = true;
						mouseState = MouseState::CLICK_L;
					}

					else if (sdlevent.button.button == SDL_BUTTON_RIGHT)
						mouseState = MouseState::CLICK_R;
					else if (sdlevent.button.button == SDL_BUTTON_MIDDLE) {
						mouseState = MouseState::CLICK_M;
						std::cout << "Raton pulsado: " << (int)MouseState::CLICK_M << std::endl;
					}

					break;
				case SDL_MOUSEBUTTONUP:
					//clickJustPressed = false;
					mouseState = MouseState::NONE;
					break;
				case SDL_QUIT:
					return false;
					break;
				case SDL_JOYBUTTONDOWN: {
					button = (int)sdlevent.cbutton.button;
					if (button < controllerButtonCount) {

						buttonState = controller.buttons[button];
						if (buttonState != ControllerButtonState::DOWN && buttonState != ControllerButtonState::HOLD) {
							buttonState = ControllerButtonState::DOWN;
						}
						else if (buttonState == ControllerButtonState::DOWN) {
							buttonState = ControllerButtonState::HOLD;
						}
					}

					//std::cout << "Boton pulsado: " << (int)sdlevent.cbutton.button << std::endl;
					break;
				}
				case SDL_JOYBUTTONUP: {

					int button = (int)sdlevent.cbutton.button;
					if (button < controllerButtonCount) {

						buttonState = controller.buttons[button];
						if (buttonState != ControllerButtonState::UP && buttonState != ControllerButtonState::NONE) {
							buttonState = ControllerButtonState::UP;
						}
						else if (buttonState == ControllerButtonState::UP) {
							buttonState = ControllerButtonState::NONE;
						}
					}
					break;
				}
				case SDL_JOYAXISMOTION:
					if (std::abs(sdlevent.jaxis.value) > 8000) {
						float val = (sdlevent.jaxis.value - 8000) / 32000.0f;

						int stick = (int)sdlevent.jaxis.axis;

						if (stick == 3) {
							controller.leftTrigger = val;
						}
						else if (stick == 4) {
							controller.rightTrigger = val;
						}
						else {
							val *= -1;
							Utilities::Vector2<float>& js = stick > 1 ? controller.rightJoystick : controller.leftJoystick;
							(stick % 2 ? js.y : js.x) = val;
						}
					}
					break;
				case SDL_MOUSEWHEEL:
					mouseWheelValue = sdlevent.wheel.preciseY;
					break;
				default:

					break;
				}
			}

			clickJustPressed =  mouseclicked;
			_mouseWheel = mouseWheelValue;
			return true;
		}

		bool InputManager::isKeyPressed(InputKeys key)
		{
			return lastPressedKeys->count((SDL_Scancode)((int)key));
		}

		bool InputManager::keyJustPressed(InputKeys key)
		{
			return justPressedKeys->count((SDL_Scancode)((int)key));
		}

		bool InputManager::mousePressed(MouseState state)
		{
			return mouseState == state;
		}

		float InputManager::mouseWheel()
		{
			return _mouseWheel;
		}

		Utilities::Vector2<int> InputManager::mousePosition()
		{
			return Utilities::Vector2<int>(mouseX, mouseY);
		}

		Utilities::Vector2<float> InputManager::relativeMousePosition()
		{
			return Utilities::Vector2<float>(relmouseX, relmouseY);
		}

		bool InputManager::isControllerButtonPressed(ControllerButton b)
		{
			return (int)b == button;
		}
		bool InputManager::isControllerButtonState(ControllerButtonState s)
		{
			return s == buttonState;
		}

		Controller& InputManager::getController()
		{
			return controller;
			// TODO: Insertar una instrucción "return" aquí
		}

		bool InputManager::justClicked()
		{
			return clickJustPressed;
		}

		bool InputManager::controllerConected()
		{
			return sdlcontroller != NULL;
		}

		//teclas = new std::unordered_map<SDL_KeyCode, tecla>();

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

			if (SDL_UpdateWindowSurface(window) < 0)  throwINPUTError(__LINE__);

			SDL_Delay(5000);
		}

		bool InputManager::initialiseController()
		{
			sdlcontroller = NULL;

			for (int i = 0; i < SDL_NumJoysticks(); ++i) {
				if (SDL_IsGameController(i)) {
					sdlcontroller = SDL_GameControllerOpen(i);
					if (sdlcontroller) {
						return true;
					}
				}
			}

			return false;
		}

		void InputManager::throwINPUTError(int errorLine) {
			LoveEngine::ErrorHandling::throwError(__PROJECT_NAME__, errorLine, __FILENAME__, SDL_GetError());
		}

	}
}