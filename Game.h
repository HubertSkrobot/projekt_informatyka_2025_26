#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Ball.h"
#include "Paddle.h"
#include "klocek.h"
#include "GameState.h" 
#include "EndScreen.h"

class Game {
private:
    sf::Font font;
    sf::Text scoreLabel;
    EndScreen endScreen;

public:
    Ball ball;
    Paddle paddle;
    std::vector<Brick> bricks;
    int score;
    bool gameOver;
    bool gameWon;
    sf::Vector2f brickSize;
    Game();
    GameState handleEvent(sf::Event& event);
    void update(sf::Time dt, sf::Vector2f windowSize);
    void render(sf::RenderTarget& target);
    void reset();

    bool isGameOver() const { return gameOver; }
};
