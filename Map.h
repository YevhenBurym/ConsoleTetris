//
// Created by Yevhen on 20.05.2022.
//

#ifndef MATRIX_H
#define MATRIX_H

enum MapElements {
    SPACE,
    BRICK,
    BORDER
};

class Map {
private:
    int height, width;
    int widthWithBorder, heightWithBorder;
    int* mapArray;
public:
    Map(int width, int height);
    Map(const Map& other) = delete;
    ~Map();
    int getW() const;
    int getH() const;
    void print();
    int& operator()(int x, int y);
    const int& operator()(int x, int y) const; // для константных объектов
};

#endif //MATRIX_H
