//
// Created by Евгений on 10.01.2023.
//

#include <iostream>
#include "Game.h"

Game::Game() {
    int width = 20;
    int height = 20;
    this->state = GameState::MENU;
    this->showMenu();
    this->randGenerator = RandGenerator();
    this->createFigShapes();
    this->quit = false;
    this->map = new Map(width, height);
    std::vector<std::vector<int>> shape = this->getRandShape();
    this->nextShape = this->getRandShape();
    this->figure = new Figure(width / 2 - 1, 0, shape, this->map);
    this->map->setNextFigure(this->nextShape);
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

    //this->init();

    while (!this->quit) {
        this->inputHandler();
        startTime = std::chrono::high_resolution_clock::now();
        if (this->state == GameState::PLAY) {
            this->update();
        }
        if (this->state == GameState::PLAY) {
            this->print();
        }
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
            if (this->state == GameState::PLAY) {
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
                    case ButtonCode::SPACE:
                        this->findFieldBottom();
                        break;
                    default:
                        break;
                }
            } else {
                switch (key) {
                    case ButtonCode::Y:
                        this->state = GameState::PLAY;
                        this->init();
                        break;
                    case ButtonCode::N:
                        this->quit = true;
                        break;
                    default:
                        break;
                }
            }
            if (key == ButtonCode::ESCAPE) {
                this->quit = true;
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
        for (int yFigOnMap = this->figure->getY(), yFig = 0; yFig < this->figure->getH(); ++yFigOnMap, ++yFig) {

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
    Figure *temp = this->figure;
    std::vector<std::vector<int>> shape = this->getRandShape();
    this->figure = new Figure(this->map->getW() / 2 - 1, 0, this->nextShape, this->map);
    temp->writeToMapArray(FOR_WRITING);
    delete temp;
    this->nextShape = this->getRandShape();
    this->map->setNextFigure(this->nextShape);

    for (int xFigOnMap = this->figure->getX(), xFig = 0; xFig < this->figure->getW(); ++xFigOnMap, ++xFig) {
        for (int yFigOnMap = this->figure->getY(), yFig = 0; yFig < this->figure->getH(); ++yFigOnMap, ++yFig) {
            if ((*this->figure)(xFig, yFig) == MapElements::BRICK &&
                (*this->map)(FOR_WRITING, xFigOnMap, yFigOnMap) != MapElements::FREE) {
                this->state = GameState::GAMEOVER;
                system("cls");
                this->showGameOver();
                return;
            }
        }
    }
}

std::vector<std::vector<int>> Game::getRandShape() {
    uint8_t shapesAmount = 7;
    uint8_t maxRotationsAmount = 3;
    uint8_t randomShape = (shapesAmount - 1) * this->randGenerator.getRandNumber();
    uint8_t rotationsAmount = maxRotationsAmount * this->randGenerator.getRandNumber();
    std::vector<std::vector<int>> currentShape;
    switch (randomShape) {
        case 0:
            currentShape = this->shapes.cube;
            break;
        case 1:
            currentShape = this->shapes.jRight;
            break;
        case 2:
            currentShape = this->shapes.jLeft;
            break;
        case 3:
            currentShape = this->shapes.line;
            break;
        case 4:
            currentShape = this->shapes.t;
            break;
        case 5:
            currentShape = this->shapes.zRight;
            break;
        case 6:
            currentShape = this->shapes.zLeft;
            break;
        default:
            currentShape = this->shapes.cube;
            break;
    }

    for (int rotation = 0; rotation <= rotationsAmount; ++rotation) {
        int rows = currentShape.size();
        int columns = currentShape[0].size();
        std::vector<std::vector<int>> rotatedShape(columns, std::vector<int>(rows));

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                rotatedShape[columns - j - 1][i] = currentShape[i][j];
            }
        }
        currentShape = rotatedShape;
    }
    return currentShape;
}

void Game::findFieldBottom() {
    int y = this->figure->getY();
    int x = this->figure->getX();
    int mapH = this->map->getH();
    int figH = this->figure->getH();
    int figW = this->figure->getW();

    for (int shiftY = 0; shiftY < (mapH - (y + figH - 1)); ++shiftY) {
        for (int xFigOnMap = x, xFig = 0; xFig < figW; ++xFigOnMap, ++xFig) {
            for (int yFigOnMap = y, yFig = 0; yFig < figH; ++yFigOnMap, ++yFig) {

                if ((*this->figure)(xFig, yFig) == MapElements::BRICK &&
                    (*this->map)(FOR_WRITING, xFigOnMap, yFigOnMap + shiftY) != MapElements::FREE) {

                    this->figure->setY(y + shiftY - 1);
                    this->createNewFigure();
                    return;
                }
            }
        }
    }
    this->figure->setY(mapH - figH);
    this->createNewFigure();
}

void Game::showMenu() {
    std::cout << "   =====CONSOLE TETRIS=====\n\n";
    std::cout << "    Do you wanna play?\n";
    std::cout << "    y - play, n - quit\n";
}

void Game::showGameOver() {
    std::cout << "\n\n   GAME OVER!\n\n";
    std::cout << "   Retry? [y/n]";
}

