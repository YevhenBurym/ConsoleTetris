//
// Created by Евгений on 10.01.2023.
//

#pragma once

#include "Map.h"

class Figure {
private:
    int h, w;
    int x, y;
    int angle;
    int* figureArray;
    Map* map;
public:
    Figure(int x, int y, Map* map);
    ~Figure();
    void init();
    void update();
    void print();
    void selfEraseFromMap();
    void rotation();
    void setAngle(int value);
    int getX() const;
    int getY() const;
    void setX(int value);
    void setY(int value);
    int& operator()(int posX, int posY);
};

