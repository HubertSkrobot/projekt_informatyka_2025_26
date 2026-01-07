#include "Game.h"
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <sstream>

Game::Game()
    : ball({ 400.f,400.f }, 15.f, { 150.f,150.f }),
    paddle({ 400.f,550.f }, { 100.f,20.f }, { 300.f,0.f }),
    score(0), gameOver(false), gameWon(false), brickSize{ 70.f,25.f }
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    font.loadFromFile("arial.ttf");
    scoreLabel.setFont(font);
    scoreLabel.setCharacterSize(18);
    scoreLabel.setFillColor(sf::Color::White);
    scoreLabel.setPosition(10.f, 10.f);

    reset();
}

GameState Game::handleEvent(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            return GameState::Menu;
        }
        if (event.key.code == sf::Keyboard::P) {
            saveGame("zapis.txt", ball, paddle, bricks, score);
        }
        if (event.key.code == sf::Keyboard::R) {
            reset();
        }
    }
    return GameState::Playing;
}

void Game::reset()
{
    ball = Ball({ 400.f,400.f }, 15.f, { 150.f,150.f });
    paddle = Paddle({ 400.f,550.f }, { 100.f,20.f }, { 300.f,0.f });
    bricks.clear();
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 8; x++) {
            int hp = (y % 3) + 1;
            bricks.emplace_back(sf::Vector2f(80.f + x * 90.f, 100.f + y * 40.f), brickSize, hp);
        }
    }
    score = 0;
    gameOver = false;
    gameWon = false;
}

void Game::update(sf::Time dt, sf::Vector2f windowSize)
{
    if (gameOver || gameWon) return;

    paddle.ruch(dt, windowSize);
    ball.ruch(dt, windowSize, paddle);
    sf::FloatRect ballBounds = ball.getShapeBounds();
    float radius = ball.getShape().getRadius();
    sf::Vector2f ballPos = ball.getPosition();

    for (size_t i = 0; i < bricks.size();) {
        sf::FloatRect brickBounds = bricks[i].getBounds();
        if (ballBounds.intersects(brickBounds)) {
            if (ballPos.y > brickBounds.top + brickBounds.height / 2.f) {
                ball.setPosition({ ballPos.x, brickBounds.top + brickBounds.height + radius });
            }
            else {
                ball.setPosition({ ballPos.x, brickBounds.top - radius });
            }

            ball.bounceY();

            if (bricks[i].hit()) {
                bricks.erase(bricks.begin() + i);
                score += 1;
            }
            else {
                score += 1;
                i++;
            }
        }
        else i++;
    }

    if (ball.isLost()) gameOver = true;
    if (bricks.empty()) gameWon = true;

    std::stringstream ss;
    ss << "Score: " << score;
    scoreLabel.setString(ss.str());
}

void Game::render(sf::RenderTarget& target)
{
    for (auto& b : bricks) b.draw(target);
    ball.draw(target);
    paddle.draw(target);
    target.draw(scoreLabel);

    // Wywołanie nowej klasy z odpowiednim parametrem (1 - wygrana, 0 - przegrana)
    if (gameOver) {
        endScreen.render(target, 0);
    }
    else if (gameWon) {
        endScreen.render(target, 1);
    }
}
