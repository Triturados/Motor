#pragma once
#ifndef _INPUT_H
#define _INPUT_H
#include <../Export.h>

#include <vector>
#include <unordered_map>
#include <string>
#include <Vector2.h>
#include <iostream>
#include <unordered_set>
//#include <SDL.h>

#include "SDL_keycode.h"
#include <SDL_gamecontroller.h>

namespace LoveEngine {
	namespace ECS {
		class Component;
	}

	namespace Input {
		struct lovexport tecla {
			bool pressedLastFrame = false;
			bool beingPressed = false;
			bool keyUp = false;
			std::vector<ECS::Component*> suscriptores;
		};

		enum class lovexport InputKeys {
			A = 4, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
			RIGHT = 80, LEFT, DOWN, UP, TAB = 43, CTRL = 224, SHIFT = 225,
			SPACE = 205, ESCAPE = 41, ENTER = 88
		};

		enum class lovexport MouseState {
			NONE, CLICK_L, CLICK_R, CLICK_M
		};

		const int controllerButtonCount = 15;
		enum class lovexport ControllerButton {
			A, B, X, Y, BACK, GUIDE, START, 
			LSTICK, RSTICK, LS, RS,
			DPAD_UP, DPAD_DOWN, DPAD_LEFT, DPAD_RIGHT,
			LB, LT, RB, RT
		};

		enum class lovexport psControllerButton {
			X, CIRCLE, TRIANGLE, SQUARE, BACK, GUIDE, START,
			LSTICK, RSTICK, LS, RS,
			DPAD_UP, DPAD_DOWN, DPAD_LEFT, DPAD_RIGHT,
			LB, LT, RB, RT
		};

		enum class lovexport ControllerButtonState {
			UP, DOWN, HOLD, NONE
		};

		struct lovexport Controller
		{
			Utilities::Vector2<float> leftJoystick, rightJoystick;
			float leftTrigger, rightTrigger;
			ControllerButtonState buttons[controllerButtonCount];
		};


		class lovexport InputManager {
		public:
			InputManager();
			~InputManager();
			static void setSDLwithOgreTest();
			static void initSDLWindowTest();
			static InputManager* getInstance();
			bool handleInput();
			bool isKeyPressed(InputKeys key);
			bool keyJustPressed(InputKeys key);
			bool mousePressed(MouseState state);
			Utilities::Vector2<float> mousePosition();

			Controller& getController();
			bool controllerConected();
			//static std::unordered_map<SDL_KeyCode, tecla> teclas;
			/*void addListener(SDL_KeyCode k, Component* c);*/
		private:

			Controller controller;
			std::unordered_set<SDL_Scancode>* lastPressedKeys;
			std::unordered_set<SDL_Scancode>* justPressedKeys;
			int mouseX, mouseY;
			MouseState mouseState;

			static InputManager* _instance;

			bool initialiseController();
			SDL_GameController* sdlcontroller;
			//Errores
			static void throwINPUTError(int errorLine);
		};
	}
}
#endif

