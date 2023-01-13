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
    this->gameFieldArray = new int[this->height * this->width];
}

Map::~Map() {
    delete[] mapArray;
    delete[] gameFieldArray;
}

int Map::getW() const {
    return this->width;
}

int Map::getH() const {
    return this->height;
}

void Map::update() {
    for (int i = 0; i < this->height; ++i) {
        for (int j = 0; j < this->width; ++j) {
            this->mapArray[(i+1) * this->widthWithBorder + (j+1)] = this->gameFieldArray[i * this->width + j];
        }
    }
}

void Map::print() {
    char element = ' ';
    for (int i = 0; i < this->heightWithBorder; ++i) {
        for (int j = 0; j < this->widthWithBorder; ++j) {
            switch (this->mapArray[i * this->widthWithBorder + j]) {
                case MapElements::BORDER:
                  element = '*';
                  break;
                case MapElements::BRICK:
                  element = '#';
                  break;
                case MapElements::FREE:
                  element = ' ';
                  break;
            }
            std::cout << element;
        }
        std::cout << std::endl;
    }
}

int &Map::operator()(MapArrays arr, int x, int y) {
    if (arr == MapArrays::FOR_PRINTING) {
        if ((x >= 0 && x < this->width) && (y >= 0 && y < this->height)) {
            return this->mapArray[(y + 1) * this->widthWithBorder + (x + 1)];
        }
        if (y >= 0 && y < this->height) {
            return this->mapArray[(y + 1) * this->widthWithBorder + this->width];
        }
        if (x >= 0 && x < this->width) {
            return this->mapArray[this->height * this->widthWithBorder + (x + 1)];
        }
    }
    if (arr == MapArrays::FOR_WRITING) {
        if ((x >= 0 && x < this->width) && (y >= 0 && y < this->height)) {
            return this->gameFieldArray[y * this->width + x];
        }
        if (y >= 0 && y < this->height) {
            return this->mapArray[y * this->width + this->width];
        }
        if (x >= 0 && x < this->width) {
            return this->mapArray[this->height * this->width + x];
        }
    }
    return this->mapArray[this->height * this->widthWithBorder + this->width];

}

void Map::init() {
//    for (int i = 0; i < this->heightWithBorder * this->widthWithBorder; ++i) {
//        this->mapArray[i] = MapElements::FREE;
//    }
    for (int i = 0; i < this->height * this->width; ++i) {
        this->gameFieldArray[i] = MapElements::FREE;
    }
    int lastRow = this->heightWithBorder - 1;
    int lastCol = this->widthWithBorder - 1;

    for ( int x = 0; x < this->widthWithBorder; x++ ) {
        this->mapArray[x] = MapElements::BORDER;
        this->mapArray[lastRow * this->widthWithBorder + x] = MapElements::BORDER;
    }
    for ( int y = 0; y < this->heightWithBorder; y++ ) {
        this->mapArray[y * this->widthWithBorder] = MapElements::BORDER;
        this->mapArray[y * this->widthWithBorder + lastCol] = MapElements::BORDER;
    }
}
