//
// Created by Евгений on 10.01.2023.
//

#include <iostream>
#include "Game.h"

Game::Game(int width, int height) {
    this->quit = false;
    this->map = new Map(width, height);
    this->figure = new Figure(width / 2 - 1, 0, this->map);
}

Game::~Game() {
    delete this->map;
    delete this->figure;
}

void Game::init() {
    this->figure->init();
    this->map->init();

    (*this->map)(FOR_WRITING, this->map->getW() - 13, this->map->getH() - 5) = MapElements::BORDER;
    (*this->map)(FOR_WRITING, this->map->getW() - 13, this->map->getH() - 6) = MapElements::BORDER;
    (*this->map)(FOR_WRITING, this->map->getW() - 13, this->map->getH() - 7) = MapElements::BORDER;
    (*this->map)(FOR_WRITING, this->map->getW() - 13, this->map->getH() - 8) = MapElements::BORDER;
    (*this->map)(FOR_WRITING, this->map->getW() - 13, this->map->getH() - 9) = MapElements::BORDER;


    (*this->map)(FOR_WRITING, this->map->getW() - 5, this->map->getH() - 5) = MapElements::BORDER;
    (*this->map)(FOR_WRITING, this->map->getW() - 5, this->map->getH() - 4) = MapElements::BORDER;
    (*this->map)(FOR_WRITING, this->map->getW() - 5, this->map->getH() - 3) = MapElements::BORDER;
    (*this->map)(FOR_WRITING, this->map->getW() - 4, this->map->getH() - 5) = MapElements::BORDER;
    (*this->map)(FOR_WRITING, this->map->getW() - 4, this->map->getH() - 4) = MapElements::BORDER;
    (*this->map)(FOR_WRITING, this->map->getW() - 4, this->map->getH() - 3) = MapElements::BORDER;
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

/*Перевірка боків фігури*/
    int lastFigXRelToSelf = this->figure->getW() - 1;
    int lastFigYRelToSelf = this->figure->getH() - 1;
    int lastFigXRelToMap = this->figure->getX() + lastFigXRelToSelf;
    int lastFigYRelToMap = this->figure->getY() + lastFigYRelToSelf;

//    /*Перевірка лівої частини фігури*/
//    for (int yFigOnMap = this->figure->getY(), yFig = 0; yFig < this->figure->getH(); ++yFigOnMap, ++yFig) {
//        if ((*this->figure)(0, yFig) == MapElements::BRICK &&
//            (*this->map)(FOR_WRITING, this->figure->getX(), yFigOnMap) != MapElements::FREE) {
//            this->figure->setX(this->figure->getX() + 1);
//        }
//    }

//    /*Перевірка низу фігури*/
//    for (int xFigOnMap = this->figure->getX(), xFig = 0; xFig < this->figure->getW(); ++xFigOnMap, ++xFig) {
//        if ((*this->figure)(xFig, lastFigYRelToSelf) == MapElements::BRICK &&
//            (*this->map)(FOR_WRITING, xFigOnMap, lastFigYRelToMap) != MapElements::FREE) {
//            this->figure->setY(this->figure->getY() - 1);
//            this->createNewFigure();
//            return;
//        }
//    }



    for (int xFigOnMap = this->figure->getX(), xFig = 0; xFig < this->figure->getW(); ++xFigOnMap, ++xFig) {
        for (int yFigOnMap = this->figure->getY(), yFig = 0; yFig <this->figure->getH(); ++yFigOnMap, ++yFig) {

            /*Перевірка низу фігури*/
//            if ((*this->figure)(i, this->figure->getH() - 1) == MapElements::BRICK &&
//                (*this->map)(FOR_WRITING, xFig, lastFigYRelToMap) != MapElements::FREE) {
//                this->figure->setY(this->figure->getY() - 1);
////                std::cout << "figure point: "<<i <<", "<< j<<"= " << (*this->figure)(i, j) << std::endl;
////                std::cout <<"Writing array point: "<< xFig <<", "<< yFig <<"= " << (*this->map)(FOR_WRITING, xFig, yFig) << std::endl;
//                this->createNewFigure();
//                return;
//            }

/*Перевірка боків фігури*/
            /*Перевірка лівої частини фігури*/
            if ((*this->figure)(xFig, yFig) == MapElements::BRICK &&
                (*this->map)(FOR_WRITING, xFigOnMap, yFigOnMap) != MapElements::FREE) {


                if (this->figure->getY() > this->figure->getYPrev()) {
                    if (this->figure->getX() > this->figure->getXPrev()) {
                        this->figure->setX(this->figure->getX() - 1);
                    } else if (this->figure->getX() < this->figure->getXPrev()) {
                        this->figure->setX(this->figure->getX() + 1);
                    }
                    this->figure->setY(this->figure->getY() - 1);
                    this->createNewFigure();
                    return;
                } else {
                    if (this->figure->getX() > this->figure->getXPrev()) {
                        this->figure->setX(this->figure->getX() - 1);
                        break;
                    } else if (this->figure->getX() < this->figure->getXPrev()) {
                        this->figure->setX(this->figure->getX() + 1);
                        break;
                    }
                }

            }
//            if ((*this->figure)(i, j) == MapElements::BRICK &&
//                (*this->map)(FOR_WRITING, xFig, yFig) != MapElements::FREE) {
//                if (xFig == lastFigXRelToMap) {
//                    this->figure->setX(this->figure->getX() - 1);
//                } else {
//                    this->figure->setX(this->figure->getX() + 1);
//                }
//                break;
//            }
        }
    }
}

void Game::createNewFigure() {
    Figure* temp = this->figure;
    this->figure = new Figure(this->map->getW() / 2 - 1, 0, this->map);
    temp->writeToMapArray(FOR_WRITING);
    delete temp;
}
