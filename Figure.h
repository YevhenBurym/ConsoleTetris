//
// Created by Евгений on 10.01.2023.
//

#pragma once

#include <vector>
#include "Map.h"

struct FigureShapes{
    std::vector<std::vector<int>> cube;
    std::vector<std::vector<int>> jRight;
    std::vector<std::vector<int>> jLeft;
    std::vector<std::vector<int>> line;
    std::vector<std::vector<int>> t;
    std::vector<std::vector<int>> zRight;
    std::vector<std::vector<int>> zLeft;
};

class Figure {
private:
    int h, w;
    int x, y;
    int xPrev, yPrev;
    float Vy;
    float velocityCoeff;
    std::vector<std::vector<int>> figure;
    Map* map;
public:
    Figure(int x, int y, std::vector<std::vector<int>>& shape, Map* map);
    void update();
    void print();
    void writeToMapArray(MapArrays targetArray);
    void rotate();
    int getX() const;
    int getY() const;
    int getXPrev() const;
    int getYPrev() const;
    int getW() const;
    int getH() const;
    void setX(int value);
    void setY(int value);
    int& operator()(int posX, int posY);
};

