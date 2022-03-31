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

class Component;
//class SDL_Scancode;
struct tecla {
    bool pressedLastFrame = false;
    bool beingPressed = false;
    bool keyUp = false;
    std::vector<Component*> suscriptores;
};

// Los valores son automaticamente incrementos de 1 en 1 si no estan definidos
enum class InputKeys {
    A = 4,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,W,X,Y,Z,
    RIGHT = 80, LEFT, DOWN, UP, TAB = 43, CTRL = 224, SHIFT = 225,
    SPACE = 205, ESCAPE = 41, ENTER = 88
};

enum class MouseState {
    NONE, CLICK_L, CLICK_R, CLICK_M
};

class Input {
public:
    Input();
    //singleton
    static void setSDLwithOgreTest();
    static int initSDLWindowTest();
    static Input* getInstance();
    bool handleInput();
    bool isKeyPressed(InputKeys key);

    //static std::unordered_map<SDL_KeyCode, tecla> teclas;
    /*void addListener(SDL_KeyCode k, Component* c);*/
private:
   

    std::unordered_set<SDL_Scancode>* lastPressedKeys;
    static Input* _instance;
    int mouseX, mouseY;
    MouseState mouseState;
    
};


#endif