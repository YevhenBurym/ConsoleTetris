//
// Created by Евгений on 10.01.2023.
//

#include <iostream>
#include "Figure.h"

Figure::Figure(int x, int y, std::vector<std::vector<int>>& shape, Map* map) {
    this->x = x;
    this->y = y;
    this->xPrev = 0;
    this->yPrev = 0;
    this->h = shape[0].size();
    this->w = shape.size();
    this->Vy = 0;
    this->figure = shape;
    this->map = map;
    this->velocityCoeff = 0.1;
}

void Figure::update() {
    this->yPrev = this->y;
    this->xPrev = this->x;
    this->Vy += this->velocityCoeff * static_cast<float>(this->map->getCurrentLevel());
    if (this->Vy >= 1) {
        this->y += static_cast<int>(this->Vy);
        this->Vy = 0;
    }

}

void Figure::print() {
    this->writeToMapArray(MapArrays::FOR_PRINTING);
}

void Figure::writeToMapArray(MapArrays targetArray) {
    for (int i = 0; i < this->w; i++) {
        for (int j = 0; j < this->h; j++) {
            if (this->figure[i][j] == MapElements::BRICK) {
                (*this->map)(targetArray, this->x + i, this->y + j) = this->figure[i][j];
            }
        }
    }
}

void Figure::rotate() {
    int rows = this->figure.size();
    int columns = this->figure[0].size();

    std::vector<std::vector<int>> rotatedFigure(columns, std::vector<int>(rows));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            rotatedFigure[columns - j - 1][i] = this->figure[i][j];
            //rotatedFigure[j][rows - i -1] = this->figure[i][j];
        }
    }
    this->figure = rotatedFigure;
    this->w = columns;
    this->h = rows;
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

int Figure::getXPrev() const {
    return this->xPrev;
}

int Figure::getYPrev() const {
    return this->yPrev;
}

int Figure::getW() const {
    return this->w;
}

int Figure::getH() const {
    return this->h;
}

int &Figure::operator()(int posX, int posY) {
    if ( (posX >= 0 && posX < this->w) && (posY >= 0 && posY < this->h) ) {
        return this->figure[posX][posY];
    }
    if (posY >= 0 && posY < this->h) {
        return this->figure[this->w][posY];
    }
    if (posX >= 0 && posX < this->w) {
        return this->figure[posX][this->h];
    }
    return this->figure[this->w][this->h];

}