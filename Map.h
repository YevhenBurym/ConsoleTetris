//
// Created by Yevhen on 20.05.2022.
//

#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

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
    std::vector<std::vector<int>> mapArray;
    std::vector<std::vector<int>> gameField;
    std::vector<std::vector<int>> nextFigureShape;
    int level;
    int score;
    int filledLinesAmount;
public:
    Map(int width, int height);
    Map(const Map& other) = delete;
    int getW() const;
    int getH() const;
    void init();
    void print();
    void update();
    void isLineFilled();
    int getCurrentLevel() const;
    void setNextFigure(const std::vector<std::vector<int>>& figureShape);
    int& operator()(MapArrays arr, int x, int y);
};

#endif //MATRIX_H
