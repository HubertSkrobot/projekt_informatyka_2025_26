#pragma once
#include <SFML/Graphics.hpp>

class Brick {
private:
    sf::RectangleShape shape;
    int hp;

    void updateColor() { //zmiana koloru przy roznej ilosci hp klocka
        if (hp == 1) shape.setFillColor(sf::Color::Red);
        else if (hp == 2) shape.setFillColor(sf::Color::Green);
        else if (hp >= 3) shape.setFillColor(sf::Color::Yellow);
        else shape.setFillColor(sf::Color::Black);
    }

public:
    Brick(sf::Vector2f pos, sf::Vector2f size, int health)
        : hp(health)
    {
        shape.setPosition(pos);
        shape.setSize(size);
        shape.setOrigin(size.x / 2.f, size.y / 2.f);
        updateColor();
    }

    void draw(sf::RenderTarget& window) { window.draw(shape); }
    sf::FloatRect getBounds() const { return shape.getGlobalBounds(); }

    bool hit() { 
        hp--;
        updateColor();
        return hp <= 0;
    }

    int getHP() const { return hp; }
    void setHP(int h) {
        hp = h;
        if (hp <= 0) hp = 0;
        updateColor();
    }

    sf::Vector2f getPosition() const { return shape.getPosition(); }
    void setPosition(sf::Vector2f pos) { shape.setPosition(pos); }
};