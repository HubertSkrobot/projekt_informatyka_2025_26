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
    std::srand(static_cast<unsigned>(std::time(nullptr))); //RNG
    font.loadFromFile("arial.ttf"); //ladowanie czcionki
    scoreLabel.setFont(font);
    scoreLabel.setCharacterSize(18);
    scoreLabel.setFillColor(sf::Color::White);
    scoreLabel.setPosition(10.f, 10.f);

    //GAME OVER ekran
    gameOverRect.setSize(sf::Vector2f(400.f, 100.f));
    gameOverRect.setFillColor(sf::Color::Red);
    gameOverRect.setOrigin(gameOverRect.getSize() / 2.f);
    gameOverRect.setPosition(400.f, 300.f);

    gameOverText.setFont(font);
    gameOverText.setCharacterSize(24);
    gameOverText.setString("Game Over");
    gameOverText.setFillColor(sf::Color::White);
    sf::FloatRect tb = gameOverText.getLocalBounds();
    gameOverText.setOrigin(tb.left + tb.width / 2.f, tb.top + tb.height / 2.f);
    gameOverText.setPosition(400.f, 300.f);

    restartText.setFont(font);
    restartText.setCharacterSize(18);
    restartText.setString("Nacisnij R, aby zrestartowac lub ESC, aby wrocic do menu.");
    sf::FloatRect rb = restartText.getLocalBounds();
    restartText.setOrigin(rb.left + rb.width / 2.f, rb.top + rb.height / 2.f - 50);
    restartText.setPosition(400.f, 350.f);

    //GRATULACJE ekran
    winRect.setSize(sf::Vector2f(400.f, 100.f));
    winRect.setFillColor(sf::Color::Green);
    winRect.setOrigin(winRect.getSize() / 2.f);
    winRect.setPosition(400.f, 300.f);

    winText.setFont(font);
    winText.setCharacterSize(24);
    winText.setString("Gratulacje!");
    winText.setFillColor(sf::Color::White);
    sf::FloatRect wb = winText.getLocalBounds();
    winText.setOrigin(wb.left + wb.width / 2.f, wb.top + wb.height / 2.f);
    winText.setPosition(400.f, 300.f);

    reset();
}

GameState Game::handleEvent(sf::Event& event) { //klawisze podczas gry
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            return GameState::Menu; // Powrót do menu po esc
        }
        if (event.key.code == sf::Keyboard::P) {
            saveGame("zapis.txt", ball, paddle, bricks, score); // Zapis stanu gry po P
        }
        if (event.key.code == sf::Keyboard::R) {
            reset(); // Reset gry po R
        }
    }
    return GameState::Playing;
}

void Game::reset()//resetowanie gry
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

    for (size_t i = 0; i < bricks.size();) { //sprawdzanie kolizji z klockami
        sf::FloatRect brickBounds = bricks[i].getBounds();
        if (ballBounds.intersects(brickBounds)) {
            // Logika kolizji
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

    std::stringstream ss;//aktualizacja wyniku  
    ss << "Score: " << score;
    scoreLabel.setString(ss.str());
}

void Game::render(sf::RenderTarget& target)
{
    for (auto& b : bricks) b.draw(target);
    ball.draw(target);
    paddle.draw(target);
    target.draw(scoreLabel);

    if (gameOver) {
        target.draw(gameOverRect);
        target.draw(gameOverText);
        target.draw(restartText);
    }
    else if (gameWon) {
        target.draw(winRect);
        target.draw(winText);
        target.draw(restartText);
    }
}
