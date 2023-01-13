//
// Created by Евгений on 10.01.2023.
//

#pragma once

#include "Map.h"

class Figure {
private:
    int h, w;
    int x, y;
    float Vy;
    int angle;
    int* figureArray;
    Map* map;
    bool horOrient;
    int checkX(int xVal);
    int checkY(int xVal);
public:
    Figure(int x, int y, Map* map);
    ~Figure();
    void init();
    void update();
    void print();
    void changeOrientation();
    void rotate();
    int getX() const;
    int getY() const;
    void setX(int value);
    void setY(int value);
    int& operator()(int posX, int posY);
};

