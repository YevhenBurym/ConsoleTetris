//
// Created by Евгений on 10.01.2023.
//

#pragma once

#include <conio.h>
#include <thread>
#include <chrono>
#include "Map.h"
#include "Figure.h"

enum ButtonCode {
    LEFT = 75,
    UP = 72,
    RIGHT = 77,
    DOWN = 80,
    ESCAPE = 27
};

class Game {
private:
    Map* map;
    Figure* figure;
    bool quit;
public:
    Game(int width, int height);
    ~Game();
    void setQuit(bool state);
    void inputHandler();
    void init();
    void update();
    void print();
    void run();
};

