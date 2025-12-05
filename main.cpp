#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Menu.h"
#include "GameState.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Arkanoid");
    window.setFramerateLimit(60);

    Menu menu(window.getSize().x, window.getSize().y);
    Game game;
    GameState currentState = GameState::Menu;
    sf::Clock deltaClk;

    while (window.isOpen()) { //glowna petla gry
        sf::Time dt = deltaClk.restart();
        sf::Event event;
        while (window.pollEvent(event)) { //przyciski na klawiaturze
            if (event.type == sf::Event::Closed) window.close();
            if (currentState == GameState::Menu) {
                menu.handleEvent(event);
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Enter) {
                        if (menu.getSelectedItem() == 0) {
                            game.reset();
                            currentState = GameState::Playing;
                        }
                        if (menu.getSelectedItem() == 1) {
                            game.load("zapis.txt");
                            currentState = GameState::Playing;
                        }
                        if (menu.getSelectedItem() == 2) currentState = GameState::Exiting;
                    }
                }
            }
            else if (currentState == GameState::Playing) {
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Escape) currentState = GameState::Menu;
                    if (event.key.code == sf::Keyboard::P) game.save("zapis.txt");
                    if (event.key.code == sf::Keyboard::R) {
                        game.reset();
                    }
                }
            }
        }

        if (currentState == GameState::Playing)
            game.update(dt, sf::Vector2f(800.f, 600.f));

        if (currentState == GameState::Exiting) window.close();//wylaczenie gry po wyjsciu

        window.clear(sf::Color::Blue);
        if (currentState == GameState::Menu) menu.draw(window);
        else if (currentState == GameState::Playing) game.render(window);
        window.display();
    }

    return 0;
}