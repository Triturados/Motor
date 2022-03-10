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

enum class InputKeys {
    A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,W,X,Y,Z
};

class Input {
public:
    //singleton
    static void setSDLwithOgreTest();
    static int initSDLWindowTest();
    static Input* getInstance();
    static bool init();
    void handleInput();
    bool isKeyPressed(InputKeys key);


    //static std::unordered_map<SDL_KeyCode, tecla> teclas;
    /*void addListener(SDL_KeyCode k, Component* c);*/
private:
    Input() {
        lastPressedKeys = new std::unordered_set<SDL_Scancode>();
    };


    std::unordered_set<SDL_Scancode>* lastPressedKeys;
    static Input* _instance;
    
};


#endif