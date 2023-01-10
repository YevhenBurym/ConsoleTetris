//
// Created by Евгений on 10.01.2023.
//

#pragma once

#include "Map.h"

class Figure {
private:
    int h;
    int w;
    int x, y;
    int* figureArray;
    Map* map;
public:
    Figure(int x, int y, Map* map);
    ~Figure();
    void init();
    void update();
    void print();
    void selfEraseFromMap();

    int& operator()(int posX, int posY);
};

