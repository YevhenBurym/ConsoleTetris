//
// Created by Евгений on 10.01.2023.
//

#include "Figure.h"

Figure::Figure(int x, int y, Map* map) {
    this->x = x;
    this->y = y;
    this->h = 3;
    this->w = 2;
    this->figureArray = new int[this->h * this->w];
    for (int i = 0; i < this->h * this->w; ++i) {
        this->figureArray[i] = MapElements::SPACE;
    }
    this->map = map;
    this->init();
}

Figure::~Figure() {
    delete[] this->figureArray;
}

void Figure::init() {
    (*this)(0,0) = MapElements::SPACE;
    (*this)(0,1) = MapElements::SPACE;
    (*this)(0,2) = MapElements::BRICK;

    (*this)(1,0) = MapElements::BRICK;
    (*this)(1,1) = MapElements::BRICK;
    (*this)(1,2) = MapElements::BRICK;
}

void Figure::update() {
    this->x += 1;
    this->y += 1;
}

void Figure::print() {
    this->selfEraseFromMap();

    for ( int i = 0; i < this->w; i++ ) {
        for ( int j = 0; j < this->h; j++ ) {
            (*this->map)(this->x + i, this->y + j) = (*this)(i,j);
        }
    }
}

int &Figure::operator()(int posX, int posY) {
    if ( (posX >= 0 && posX < this->w) && (posY >= 0 && posY < this->h) ) {
        return this->figureArray[posY * this->w + posX];
    }
    if (posY >= 0 && posY < this->h) {
        return this->figureArray[posY * this->w + this->w];
    }
    if (posX >= 0 && posX < this->w) {
        return this->figureArray[this->h * this->w + posX];
    }
    return this->figureArray[this->h * this->w + this->w];
}

void Figure::selfEraseFromMap() {
    for (int i = 1; i < this->x + this->w; ++i) {
        for (int j = 0; j < this->y + this->h; ++j)
            (*this->map)(i, j) = MapElements::SPACE;
    }
}