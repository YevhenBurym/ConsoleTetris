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
    this->score = 0;
    this->level = 1;
    this->mapArray = std::vector<std::vector<int>>(this->widthWithBorder, std::vector<int>(this->heightWithBorder));
    this->gameField = std::vector<std::vector<int>>(this->width, std::vector<int>(this->height));
}

int Map::getW() const {
    return this->width;
}

int Map::getH() const {
    return this->height;
}

int Map::getCurrentLevel() const {
    return this->level;
}

void Map::update() {
    isLineFilled();
    for (auto i = this->gameField.begin(), i1 = this->mapArray.begin() + 1; i < this->gameField.end(); ++i, ++i1) {
        for (auto j = (*i).begin(), j1 = (*i1).begin() + 1; j < (*i).end(); ++j, ++j1) {
            *j1 = *j;
        }
    }
}

void Map::print() {
    char element = ' ';
    for (auto row = this->mapArray.begin(); row!= this->mapArray.end(); ++row) {
    //for (auto & row : this->mapArray) {
        for (int & col : (*row)) {
            switch (col) {
                case MapElements::BORDER:
                    element = '*';
                    break;
                case MapElements::BRICK:
                    element = '#';
                    break;
                case MapElements::FREE:
                    element = ' ';
                    break;
                default:
                    break;
            }
            std::cout << element;
        }
        if (row == this->mapArray.begin()) {
            std::cout<< "\tLevel: " << this->level;
        } else if (row == this->mapArray.begin() + 1) {
            std::cout<< "\tScore: " << this->score;
        }
        std::cout << std::endl;
    }
}

int &Map::operator()(MapArrays arr, int x, int y) {
    if (arr == MapArrays::FOR_PRINTING) {
        if ((x >= 0 && x < this->width) && (y >= 0 && y < this->height)) {
            return this->mapArray[y + 1][x + 1];
        }
        if (y >= 0 && y < this->height) {
            return this->mapArray[y + 1][this->width];
        }
        if (x >= 0 && x < this->width) {
            return this->mapArray[this->height][x + 1];
        }

    }
    if (arr == MapArrays::FOR_WRITING) {
        if ((x >= 0 && x < this->width) && (y >= 0 && y < this->height)) {
            return this->gameField[y][x];
        }
        if (y >= 0 && y < this->height) {
            return this->gameField[y][this->width];
        }
        if (x >= 0 && x < this->width) {
            return this->gameField[this->height][x];
        }

    }
    return this->mapArray[this->height][this->width];
}

void Map::init() {

    for (auto &row: this->gameField) {
        for (int &col: row) {
            col = MapElements::FREE;
        }
    }

    int lastRow = this->heightWithBorder - 1;
    int lastCol = this->widthWithBorder - 1;

    for (int &col: this->mapArray[0]) {
        col = MapElements::BORDER;
    }
    for (int &col: this->mapArray[lastRow]) {
        col = MapElements::BORDER;
    }
    for (auto &row: this->mapArray) {
        row[0] = MapElements::BORDER;
        row[lastCol] = MapElements::BORDER;
    }

}

void Map::isLineFilled() {
    int filledLinesAmount = 1;
    int linesBeforeLevelUp = 10;
    int lastRow = this->height - 1;
    for (int row = lastRow; row >= 0; --row) {
        bool isFilled = true;
        for (int &col: this->gameField[row]) {
            if (col == MapElements::FREE) {
                isFilled = false;
            }
        }
        if (isFilled) {
            for (int i = 0; i < row; ++i) {
                this->gameField[row - i] = this->gameField[row - i - 1];
            }
            if (filledLinesAmount < linesBeforeLevelUp) {
                filledLinesAmount += 1;
            } else {
                this->level += 1;
                filledLinesAmount = 0;
            }
            this->score += 1;
        }
    }
}