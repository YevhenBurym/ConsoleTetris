//
// Created by Евгений on 10.01.2023.
//

#include "Figure.h"

Figure::Figure(int x, int y, Map* map) {
    this->x = x;
    this->y = y;
    this->h = 3;
    this->w = 2;
    this->angle = 0;
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
    this->rotation();
}

void Figure::selfEraseFromMap() {
    for (int i = 1; i < this->x + this->map->getW(); ++i) {
        for (int j = 0; j < this->y + this->h; ++j)
            (*this->map)(i, j) = MapElements::SPACE;
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

void Figure::rotation() {
    switch (this->angle) {
        case 0:
            for ( int i = 0; i < this->w; i++ ) {
                for ( int j = 0; j < this->h; j++ ) {
                    (*this->map)(this->x + i, this->y + j) = (*this)(i,j);
                }
            }
            break;
        case 90:
            for ( int i = 0, k = this->w - 1; i < this->w && k >= 0; i++, k-- ) {
                for ( int j = 0, n = this->h - 1; j < this->h && n >= 0; j++, n-- ) {
                    (*this->map)(this->x + j, this->y + i) = (*this)(i,n);
                }
            }
            break;
        case 180:
            for ( int i = 0, iLast = this->w - 1; i < this->w && iLast >= 0; i++, iLast-- ) {
                for (int  j = 0, jLast = this->h - 1; j < this->h && jLast >= 0; j++, jLast-- ) {
                    (*this->map)(this->x + iLast, this->y + jLast) = (*this)(i,j);
                }
            }
            break;
        case 270:
            for ( int i = 0, k = this->w - 1; i < this->w && k>=0; i++, k-- ) {
                for ( int j = 0; j < this->h; j++ ) {
                    (*this->map)(this->x + j, this->y + i) = (*this)(k,j);
                }
            }
            break;
    }
}

void Figure::setAngle(int value) {
    this->angle = value;
}

void Figure::setX(int value) {
    this->x = value;
}

void Figure::setY(int value) {
    this->y = value;
}

int Figure::getX() const {
    return this->x;
}

int Figure::getY() const {
    return this->y;
}
