#include "GameState.h"
#include <fstream>
#include <iostream>

// zapis stanu gry do pliku
void saveGame(const std::string& filename, const Ball& ball, const Paddle& paddle, const std::vector<Brick>& bricks, int score)
{
    std::ofstream file(filename);
    if (!file) return;
    sf::Vector2f bPos = ball.getPosition();
    sf::Vector2f bVel = ball.getVelocity();
    sf::Vector2f pPos = paddle.getPosition();
    file << bPos.x << " " << bPos.y << " " << bVel.x << " " << bVel.y << " "
        << pPos.x << " " << pPos.y << " " << score << " " << bricks.size() << "\n";
    for (auto& br : bricks) {
        sf::Vector2f pos = br.getPosition();
        int hp = br.getHP();
        file << pos.x << " " << pos.y << " " << hp << "\n";
    }
}

// wczytanie stanu gry z pliku
bool loadGame(const std::string& filename, Ball& ball, Paddle& paddle, std::vector<Brick>& bricks, int& score, sf::Vector2f brickSize)
{
    std::ifstream file(filename);
    if (!file) return false;
    float bx, by, vx, vy, px, py;
    int nBricks;
    if (!(file >> bx >> by >> vx >> vy >> px >> py >> score >> nBricks)) return false;

    // Aktualizacja stanu gry
    ball = Ball({ bx,by }, 15.f, { vx,vy });
    paddle.setPosition({ px,py });
    bricks.clear();
    for (int i = 0; i < nBricks; i++) {
        float x, y; int hp;
        if (!(file >> x >> y >> hp)) return false;
        bricks.emplace_back(sf::Vector2f(x, y), brickSize, hp);
    }
    return true;
}