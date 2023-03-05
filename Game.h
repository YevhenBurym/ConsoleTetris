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
    SPACE = 32,
    Y = 121,
    N = 110
};

enum GameState {
    MENU = 0,
    PLAY = 1,
    GAMEOVER = 2
};

class Game {
private:
    GameState state;
    Map* map;
    Figure* figure;
    FigureShapes shapes;
    std::vector<std::vector<int>> nextShape;
    bool quit;
    RandGenerator randGenerator;
    void findFieldBottom();
    void createFigShapes();
    std::vector<std::vector<int>> getRandShape();
public:
    Game();
    ~Game();
    void createNewFigure();
    void inputHandler();
    void init();
    void checkCollision();
    void update();
    void print();
    void run();
    void showMenu();
    void showGameOver();
};