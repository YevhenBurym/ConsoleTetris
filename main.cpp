#include <iostream>
#include "Map.h"
#include "Figure.h"

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
    fig.print();
    map.print();

    //system("cls");

    fig.update();
    fig.print();
    map.print();
    char key = 0;
//getchar();
//    while (key != ' ') {
//        key = getchar();
//    }

    return 0;
}

