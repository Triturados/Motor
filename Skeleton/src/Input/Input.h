#pragma once

#ifndef _INPUT_H
#define _INPUT_H

#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>
#include <unordered_set>
#include <SDL.h>

//#include "SDL_keycode.h"
//class SDL_Scancode;

class Component;
struct tecla {
    bool pressedLastFrame = false;
    bool beingPressed = false;
    bool keyUp = false;
    std::vector<Component*> suscriptores;
};

enum class InputKeys {
    A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,W,X,Y,Z
};

enum class MouseState {
    NONE, CLICK_L, CLICK_R, CLICK_M
};

class InputManager {
public:
    InputManager();
    static void setSDLwithOgreTest();
    static void initSDLWindowTest();
    static InputManager* getInstance();
    bool handleInput();
    bool isKeyPressed(InputKeys key);

    //static std::unordered_map<SDL_KeyCode, tecla> teclas;
    /*void addListener(SDL_KeyCode k, Component* c);*/
private:

    std::unordered_set<SDL_Scancode>* lastPressedKeys;
    int mouseX, mouseY;
    MouseState mouseState;

    static InputManager* _instance;

    //Errores
    static void throwINPUTError(int errorLine);
};

#endif
