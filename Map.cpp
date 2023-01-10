//
// Created by Yevhen on 20.05.2022.
//

#include <iostream>
#include "Map.h"

Map::Map(int width, int height) {
    this->height = height;
    this->width = width;
    this->widthWithBorder = width + 2;
    this->heightWithBorder = height + 2;
    this->mapArray = new int[this->heightWithBorder * this->widthWithBorder];

    int lastRow = this->heightWithBorder - 1;
    int lastCol = this->widthWithBorder - 1;

    for (int i = 1; i < this->height * this->width; ++i) {
        this->mapArray[i] = MapElements::SPACE;
    }

    for ( int x = 0; x < this->widthWithBorder; x++ ) {
        this->mapArray[x] = MapElements::BORDER;
        this->mapArray[lastRow * this->widthWithBorder + x] = MapElements::BORDER;
    }
    for ( int y = 0; y < this->heightWithBorder; y++ ) {
        this->mapArray[y * this->widthWithBorder] = MapElements::BORDER;
        this->mapArray[y * this->widthWithBorder + lastCol] = MapElements::BORDER;
    }

//    for (int i = 0; i < heightWithBorder * widthWithBorder; ++i) {
//        this->mapArray[i] = 0;
//    }


}

Map::~Map() {
    delete[] mapArray;
}

int Map::getW() const {
    return this->width;
}

int Map::getH() const {
    return this->height;
}

void Map::print() {
    char element = ' ';
    for (int i = 0; i < this->heightWithBorder; ++i) {
        for (int j = 0; j < this->widthWithBorder; ++j) {
            switch (mapArray[i * this->widthWithBorder + j]) {
                case MapElements::BORDER:
                  element = '*';
                  break;
                case MapElements::BRICK:
                  element = '#';
                  break;
                case MapElements::SPACE:
                  element = ' ';
                  break;
            }
            std::cout << element;
        }
        std::cout << std::endl;
    }
}

int &Map::operator()(int x, int y) {
    int xWithBorder = x + 1;
    int yWithBorder = y + 1;

    if ( (xWithBorder >= 0 && xWithBorder < this->width) && (yWithBorder >= 0 && yWithBorder < this->height) ) {
        return this->mapArray[yWithBorder * this->widthWithBorder + xWithBorder];
    }
    if (yWithBorder >= 0 && yWithBorder < this->height) {
        return this->mapArray[yWithBorder * this->widthWithBorder + this->width];
    }
    if (xWithBorder >= 0 && xWithBorder < this->width) {
        return this->mapArray[this->height * this->widthWithBorder + xWithBorder];
    }
    return this->mapArray[this->height * this->widthWithBorder + this->width];
}