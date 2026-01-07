#pragma once
#include <SFML/Graphics.hpp>

class EndScreen {
private:
    sf::Font font;
    sf::Text gameOverText;
    sf::RectangleShape gameOverRect;
    sf::Text restartText;
    sf::Text winText;
    sf::RectangleShape winRect;

public:
    EndScreen() {
        font.loadFromFile("arial.ttf");

        // GAME OVER ekran
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

        // GRATULACJE ekran
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
    }

    void render(sf::RenderTarget& target, int status) {
        if (status == 0) { // Przegrana
            target.draw(gameOverRect);
            target.draw(gameOverText);
            target.draw(restartText);
        }
        else if (status == 1) { // Wygrana
            target.draw(winRect);
            target.draw(winText);
            target.draw(restartText);
        }
    }
};
