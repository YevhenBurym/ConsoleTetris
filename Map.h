//
// Created by Yevhen on 20.05.2022.
//

#ifndef MATRIX_H
#define MATRIX_H

enum MapElements {
    FREE,
    BRICK,
    BORDER
};

enum MapArrays {
    FOR_PRINTING,
    FOR_WRITING
};

class Map {
private:
    int height, width;
    int widthWithBorder, heightWithBorder;
    int* mapArray;
    int* gameFieldArray;
public:
    Map(int width, int height);
    Map(const Map& other) = delete;
    ~Map();
    int getW() const;
    int getH() const;
    void init();
    void print();
    void update();
    int& operator()(MapArrays arr, int x, int y);
};

#endif //MATRIX_H
