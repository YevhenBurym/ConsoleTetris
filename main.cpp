#include <iostream>
#include "Map.h"
#include "Figure.h"
#include <conio.h>

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


enum ButtonCode {
    LEFT = 75,
    UP = 72,
    RIGHT = 77,
    DOWN = 80
};

int main() {
    Game game(10,10);

    Map map(15, 15);
    Figure fig(5,5, &map);

    int key = 0;
    int angle = 0;
    while (1) {
        system("cls");
        if (_kbhit()) {
            key = _getch();
            if (key == ButtonCode::LEFT) {
                fig.setX(fig.getX() - 1);
            }
            if (key == ButtonCode::UP) {
                angle += 90;
                if (angle == 360) {
                    angle = 0;
                }
                fig.setAngle(angle);
            }
            if (key == ButtonCode::RIGHT) {
                fig.setX(fig.getX() + 1);
            }
            if (key == ButtonCode::DOWN) {
                fig.setY(fig.getY() + 1);
            }
            key = 0;
        }
        fig.print();
        map.print();
    }

    return 0;
}

