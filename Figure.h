//
// Created by Евгений on 10.01.2023.
//

#pragma once

#include <vector>
#include "Map.h"

class Figure {
private:
    int h, w;
    int x, y;
    float Vy;
    std::vector<std::vector<int>> figure;
    Map* map;
public:
    Figure(int x, int y, Map* map);
    void init();
    void update();
    void print();
    void writeToMapArray(MapArrays targetArray);
    void rotate();
    int getX() const;
    int getY() const;
    int getW() const;
    int getH() const;
    void setX(int value);
    void setY(int value);
    int& operator()(int posX, int posY);
};

