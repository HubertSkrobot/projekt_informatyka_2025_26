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
                currentState = menu.handleEvent(event, game); // Przeniesiona logika menu
            }
            else if (currentState == GameState::Playing) {
                currentState = game.handleEvent(event); // Przeniesiona logika sterowania w grze do game
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
