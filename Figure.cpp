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
    this->Vy = 0;
    this->horOrient = false;
    this->figureArray = new int[this->h * this->w];
    for (int i = 0; i < this->h * this->w; ++i) {
        this->figureArray[i] = MapElements::FREE;
    }

    this->figure = std::vector<std::vector<int>>(this->w);
    for ( auto &column : this->figure) {
        column = std::vector<int>(this->h);
    }

    this->map = map;
    this->init();
}

Figure::~Figure() {
    delete[] this->figureArray;
}

void Figure::init() {
    (*this)(0,0) = MapElements::FREE;
    (*this)(0,1) = MapElements::FREE;
    (*this)(0,2) = MapElements::BRICK;

    (*this)(1,0) = MapElements::BRICK;
    (*this)(1,1) = MapElements::BRICK;
    (*this)(1,2) = MapElements::BRICK;

    this->figure[0][0] = MapElements::FREE;
    this->figure[0][1] = MapElements::FREE;
    this->figure[0][2] = MapElements::BRICK;
    this->figure[1][0] = MapElements::BRICK;
    this->figure[1][1] = MapElements::BRICK;
    this->figure[1][2] = MapElements::BRICK;

}

void Figure::update() {
    float velocityCoeff = 0.2;
    this->Vy += velocityCoeff;
    if (this->Vy >= 1) {
        this->y += static_cast<int>(this->Vy);
        this->Vy = 0;
    }
}

void Figure::print() {
    this->writeToMapArray(MapArrays::FOR_PRINTING);
}

int &Figure::operator()(int posX, int posY) {
//    if ( (posX >= 0 && posX < this->w) && (posY >= 0 && posY < this->h) ) {
//        return this->figureArray[posY * this->w + posX];
//    }
//    if (posY >= 0 && posY < this->h) {
//        return this->figureArray[posY * this->w + this->w];
//    }
//    if (posX >= 0 && posX < this->w) {
//        return this->figureArray[this->h * this->w + posX];
//    }
//    return this->figureArray[this->h * this->w + this->w];

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

void Figure::writeToMapArray(MapArrays targetArray) {
    switch (this->angle) {
        case 0: {

            for (int i = 0; i < this->w; i++) {
                for (int j = 0; j < this->h; j++) {
                    if ((*this)(i, j) == MapElements::BRICK) {
                        (*this->map)(targetArray, this->x + i, this->y + j) = this->figure[i][j];
                    }
                }
            }

            this->horOrient = false;
        }
        break;
        case 90: {

            for (int i = 0, k = this->w - 1; i < this->w && k >= 0; i++, k--) {
                for (int j = 0, n = this->h - 1; j < this->h && n >= 0; j++, n--) {
                    if ((*this)(i, n) == MapElements::BRICK) {
                        (*this->map)(targetArray, this->x + j, this->y + i) = this->figure[i][n];
                    }
                }
            }
            this->horOrient = true;
        }
        break;
        case 180: {

            for ( int i = 0, iLast = this->w - 1; i < this->w && iLast >= 0; i++, iLast-- ) {
                for (int  j = 0, jLast = this->h - 1; j < this->h && jLast >= 0; j++, jLast-- ) {
                    if ((*this)(i, j) == MapElements::BRICK) {
                        (*this->map)(targetArray, this->x + iLast, this->y + jLast) = this->figure[i][j];
                    }
                }
            }
            this->horOrient = false;
        }
        break;
        case 270: {

            for ( int i = 0, k = this->w - 1; i < this->w && k>=0; i++, k-- ) {
                for ( int j = 0; j < this->h; j++ ) {
                    if ((*this)(k, j) == MapElements::BRICK) {
                        (*this->map)(targetArray, this->x + j, this->y + i) = this->figure[k][j];
                    }
                }
            }
            this->horOrient = true;
        }
        break;
    }


// треба перевірити функцію. Теоретично вона повертає фігуру постіной на 90 градусів за годинниковою стрілкою
//    vector<vector<int>> rotateTetromino(vector<vector<int>> &tetromino) {
//        int rows = tetromino.size();
//        int columns = tetromino[0].size();
//
//        vector<vector<int>> rotatedTetromino(columns, vector<int>(rows));
//
//        for (int i = 0; i < rows; i++) {
//            for (int j = 0; j < columns; j++) {
//                rotatedTetromino[j][rows - i - 1] = tetromino[i][j];
//            }
//        }
//
//        return rotatedTetromino;
//    }
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

void Figure::rotate() {
    this->angle += 90;
    if (this->angle == 360) {
        this->angle = 0;
    }
}

int Figure::getW() const {
    int factWidth = this->w;
    if (this->horOrient) {
        factWidth += this->h - this->w;
    }
    return factWidth;
}

int Figure::getH() const {
    int factHeight = this->h;
    if (this->horOrient) {
        factHeight -= this->h - this->w;
    }
    return factHeight;
}
