#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Ball.h"
#include "Paddle.h"
#include "klocek.h"
#include "GameState.h" 

class Game {
private:
    sf::Font font;
    sf::Text scoreLabel;
    sf::Text gameOverText;
    sf::RectangleShape gameOverRect;
    sf::Text restartText;

    sf::Text winText;
    sf::RectangleShape winRect;

public:
    Ball ball;
    Paddle paddle;
    std::vector<Brick> bricks;
    int score;
    bool gameOver; //ekran przegranej
    bool gameWon; //wygranej
    sf::Vector2f brickSize;
    Game();
    GameState handleEvent(sf::Event& event); 
    void update(sf::Time dt, sf::Vector2f windowSize);
    void render(sf::RenderTarget& target);
    void reset();

    bool isGameOver() const { return gameOver; } //sprawdzenie czy pilka spadla
};
