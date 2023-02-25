//
// Created by Евгений on 10.01.2023.
//

#include <iostream>
#include "Game.h"

Game::Game(int width, int height) {
    this->randGenerator = RandGenerator();
    this->createFigShapes();
    this->quit = false;
    this->map = new Map(width, height);
    this->figure = new Figure(width / 2 - 1, 0, this->getRandShape(), this->map);
}

Game::~Game() {
    delete this->map;
    delete this->figure;
}

void Game::createFigShapes() {
    this->shapes.cube = {{1, 1},
                         {1, 1}};
    this->shapes.jRight = {{0, 1},
                           {0, 1},
                           {1, 1}};
    this->shapes.jLeft = {{1, 0},
                          {1, 0},
                          {1, 1}};
    this->shapes.line = {{1},
                         {1},
                         {1},
                         {1}};
    this->shapes.t = {{1, 1, 1},
                      {0, 1, 0}};
    this->shapes.zRight = {{1, 1, 0},
                           {0, 1, 1}};
    this->shapes.zLeft = {{0, 1, 1},
                          {1, 1, 0}};
}

void Game::init() {
    this->map->init();
}

void Game::update() {
    this->checkCollision();         //перевіряє і вирішує колізії
    this->figure->update();         //ітерує Y
    this->map->update();            //копіює усе з FOR_WRITTING

}

void Game::print() {
    system("cls");
    this->figure->print();   //копіює усе в FOR_PRINTING
    this->map->print();      //Просто малює себе
}

void Game::run() {
    const int fps = 60;
    const int frameDelay = 1000 / fps;
    std::chrono::high_resolution_clock::time_point startTime;
    std::chrono::duration<double> frameTime{};

    this->init();

    while (!this->quit) {
        this->inputHandler();
        startTime = std::chrono::high_resolution_clock::now();
        this->update();
        this->print();
        frameTime = std::chrono::high_resolution_clock::now() - startTime;
        if (frameDelay > frameTime.count()) {
            int x = frameDelay - static_cast<int>(frameTime.count());
            std::this_thread::sleep_for(std::chrono::milliseconds(x));
        }
    }
}

void Game::inputHandler() {
    if (_kbhit()) {
        int key = _getch();
        switch (key) {
            case ButtonCode::LEFT:
                this->figure->setX(this->figure->getX() - 1);
                break;
            case ButtonCode::UP:
                this->figure->rotate();
                break;
            case ButtonCode::RIGHT:
                this->figure->setX(this->figure->getX() + 1);
                break;
            case ButtonCode::DOWN:
                this->figure->setY(this->figure->getY() + 1);
                break;
            case ButtonCode::ESCAPE:
                this->quit = true;
                break;
            case ButtonCode::SPACE:
                this->figure->setY(this->figure->getY() + 5);
                break;
            default:
                break;
        }
    }
}

void Game::checkCollision() {
    if (this->figure->getX() < 0) {
        this->figure->setX(0);
    }
    if (this->figure->getY() < 0) {
        this->figure->setY(0);
    }

    if (this->figure->getX() > this->map->getW() - this->figure->getW()) {
        this->figure->setX(this->map->getW() - this->figure->getW());
    }

    if (this->figure->getY() > this->map->getH() - this->figure->getH()) {
        this->figure->setY(this->map->getH() - this->figure->getH());
        this->createNewFigure();
        return;
    }


    for (int xFigOnMap = this->figure->getX(), xFig = 0; xFig < this->figure->getW(); ++xFigOnMap, ++xFig) {
        for (int yFigOnMap = this->figure->getY(), yFig = 0; yFig <this->figure->getH(); ++yFigOnMap, ++yFig) {

            if ((*this->figure)(xFig, yFig) == MapElements::BRICK &&
                (*this->map)(FOR_WRITING, xFigOnMap, yFigOnMap) != MapElements::FREE) {

                if (this->figure->getX() > this->figure->getXPrev()) {
                    this->figure->setX(this->figure->getX() - 1);
                    break;
                } else if (this->figure->getX() < this->figure->getXPrev()) {
                    this->figure->setX(this->figure->getX() + 1);
                    break;
                } else if (this->figure->getY() > this->figure->getYPrev()) {
                    this->figure->setY(this->figure->getY() - 1);
                    this->createNewFigure();
                    return;
                }
            }
        }
    }
}

void Game::createNewFigure() {
    Figure* temp = this->figure;
    this->figure = new Figure(this->map->getW() / 2 - 1, 0, this->getRandShape(), this->map);
    temp->writeToMapArray(FOR_WRITING);
    delete temp;
}

std::vector<std::vector<int>> &Game::getRandShape() {
    uint8_t shapesAmount = 7;
    uint8_t randomShape = (shapesAmount - 1) * this->randGenerator.getRandNumber();
    switch (randomShape) {
        case 0:
            return this->shapes.cube;
            break;
        case 1:
            return this->shapes.jRight;
            break;
        case 2:
            return this->shapes.jLeft;
            break;
        case 3:
            return this->shapes.line;
            break;
        case 4:
            return this->shapes.t;
            break;
        case 5:
            return this->shapes.zRight;
            break;
        case 6:
            return this->shapes.zLeft;
            break;
        default:
            return this->shapes.cube;
            break;
    }
}
