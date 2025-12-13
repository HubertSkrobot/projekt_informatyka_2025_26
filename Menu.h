#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "GameState.h"
#include "Game.h"
//obsługa głównego menu
class Menu {
private:
    std::vector<std::string> items;
    int selectedItem;
    float startX, startY;
    sf::Font font;
    std::vector<sf::Text> itemTexts;
    sf::RectangleShape bg;

public:
    Menu(float width, float height);

    void moveUp();
    void moveDown();
    int getSelectedItem() const { return selectedItem; }

    void draw(sf::RenderTarget& target);
    GameState handleEvent(sf::Event& event, Game& game);  

private:
    void updateColors();
};
