#include <iostream>
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
    void update();
    void print();
};

Figure::Figure(int x, int y, Map* map) {
    this->x = x;
    this->y = y;
    this->h = 2;
    this->w = 3;
    this->figureArray = new int[this->h * this->w];
    this->map = map;
}

Figure::~Figure() {
    delete[] this->figureArray;
}

void Figure::update() {
    this->x += 1;
    this->y += 1;
}

void Figure::print() {

    //this->figureArray[this->y * this->w + this->x];
    for (int i = 1; i < this->x; ++i) {
        for (int j = 0; j < this->y; ++j)
        (*this->map)(i, j) = MapElements::SPACE;
    }
    (*this->map)(0, this->y) = MapElements::BRICK;
    (*this->map)(this->x, this->y) = MapElements::BRICK;
    (*this->map)(this->x, this->y + 1) = MapElements::BRICK;
    (*this->map)(this->x, this->y + 2) = MapElements::BRICK;
    (*this->map)(this->x-1, this->y + 2) = MapElements::BRICK;
}



class Game {
private:
    Map* map;
public:
    Game(int width, int height);
    void init();
    ~Game();
};

Game::Game(int width, int height) {
    this->map = new Map(width, height);
}

Game::~Game() {
    delete this->map;
}

void Game::init() {

}



int main() {
    Game game(10,10);

    Map map(15, 15);
    Figure fig(5,5, &map);

    //map(11,3) = MapElements::BRICK;
    //fig.print();
    map.print();

    //system("cls");

    fig.update();
    //fig.print();
    //map.print();
    char key = 0;
//getchar();
//    while (key != ' ') {
//        key = getchar();
//    }

    return 0;
}

