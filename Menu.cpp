#include "Menu.h"

Menu::Menu(float width, float height)
    : selectedItem(0), startX(width / 2.f), startY(height / 2.f)
{

    //definicja opcji menu
    items.push_back("Nowa gra");
    items.push_back("Wczytaj zapis");
    items.push_back("Wyjscie");

    if (!font.loadFromFile("arial.ttf")) {
    }

    for (size_t i = 0; i < items.size(); i++) {
        sf::Text t(items[i], font, 24);
        sf::FloatRect lb = t.getLocalBounds();
        t.setOrigin(lb.left + lb.width / 2.f, lb.top + lb.height / 2.f);
        t.setPosition(startX, startY + i * 60.f);
        itemTexts.push_back(t);
    }

    bg.setSize({ width, height });
    bg.setFillColor(sf::Color(50, 50, 50));

    updateColors();
}

void Menu::moveUp() {
    selectedItem--;
    if (selectedItem < 0) selectedItem = items.size() - 1;
    updateColors();
}

void Menu::moveDown() {
    selectedItem++;
    if (selectedItem >= items.size()) selectedItem = 0;
    updateColors();
}

void Menu::draw(sf::RenderTarget& target) {
    target.draw(bg);
    for (auto& t : itemTexts) target.draw(t);
}

GameState Menu::handleEvent(sf::Event& event, Game& game) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W)
            moveUp();
        if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S)
            moveDown();
        if (event.key.code == sf::Keyboard::Enter) {
            if (selectedItem == 0) {
                game.reset();
                return GameState::Playing;
            }
            if (selectedItem == 1) {
                loadGame("zapis.txt", game.ball, game.paddle, game.bricks, game.score, game.brickSize); // Wczytanie stanu gry
                game.gameOver = false; // Upewnienie się, że gra nie jest w stanie 'Game Over' po wczytaniu
                return GameState::Playing;
            }
            if (selectedItem == 2) return GameState::Exiting;
        }
    }
    return GameState::Menu; 
}

void Menu::updateColors() { //wybrana opcja podswietla sie na zielono, reszta na bialo
    for (size_t i = 0; i < itemTexts.size(); i++)
        itemTexts[i].setFillColor(i == selectedItem ? sf::Color::Green : sf::Color::White);
}
