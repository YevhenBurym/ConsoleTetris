//
// Created by Евгений on 10.01.2023.
//

#pragma once

#include <conio.h>
#include <thread>
#include <chrono>
#include "Map.h"
#include "Figure.h"
#include "RandomGenerator.h"
#include <random>

enum ButtonCode {
    LEFT = 75,
    UP = 72,
    RIGHT = 77,
    DOWN = 80,
    ESCAPE = 27,
    SPACE = 32
};

class Game {
private:
    Map* map;
    Figure* figure;
    FigureShapes shapes;
    bool quit;
    RandGenerator randGenerator;
    void createFigShapes();
    std::vector<std::vector<int>>& getRandShape();
public:
    Game(int width, int height);
    ~Game();
    void createNewFigure();
    void inputHandler();
    void init();
    void checkCollision();
    void update();
    void print();
    void run();
};