#pragma once

#ifndef _INPUT_H
#define _INPUT_H

#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>
#include <SDL.h>
//#include "SDL_keycode.h"

class Component;
struct tecla {
    bool pressedLastFrame = false;
    std::vector<Component*> suscriptores;
};


class Input {
public:
    //singleton
    static Input* getInstance();
    static bool init();
    void handleInput();

    //static std::unordered_map<SDL_KeyCode, tecla> teclas;
    void addListener(SDL_KeyCode k, Component* c);
private:
    Input() {};
    static Input* _instance;
};


#endif