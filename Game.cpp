//
// Created by Евгений on 10.01.2023.
//

#include "Game.h"

Game::Game(int width, int height) {
    this->quit = false;
    this->map = new Map(width, height);
    this->figure = new Figure(1,0, this->map);
}

Game::~Game() {
    delete this->map;
    delete this->figure;
}

void Game::init() {
    this->figure->init();
    this->map->init();
}

void Game::update() {
    //this->figure->update();
    this->map->update();
}

void Game::print() {
    system("cls");
    this->figure->print();
    this->map->print();
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

void Game::setQuit(bool state) {
    this->quit = state;
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