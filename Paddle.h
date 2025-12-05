#pragma once
#include <SFML/Graphics.hpp>

class Paddle {
private:
    sf::RectangleShape m_shape;
    sf::Vector2f velocity;

public:
    Paddle(sf::Vector2f startPos = { 400.f,550.f }, sf::Vector2f size = { 100.f,20.f }, sf::Vector2f startVel = { 300.f,0.f })
        : velocity(startVel)
    {
        m_shape.setPosition(startPos);
        m_shape.setSize(size);
        m_shape.setFillColor(sf::Color::Cyan);
        m_shape.setOrigin(size.x / 2.f, size.y / 2.f);
    }

    void draw(sf::RenderTarget& window) { window.draw(m_shape); }

    void ruch(sf::Time dt, sf::Vector2f windowSize) { //ruch paletki za pomoca klawiszy A i D
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            m_shape.move(-velocity.x * dt.asSeconds(), 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            m_shape.move(velocity.x * dt.asSeconds(), 0.f);

        sf::Vector2f pos = m_shape.getPosition();
        sf::Vector2f half = m_shape.getSize() / 2.f;
        if (pos.x - half.x < 0) pos.x = half.x;
        if (pos.x + half.x > windowSize.x) pos.x = windowSize.x - half.x;
        m_shape.setPosition(pos);
    }

    sf::FloatRect getBounds() const { return m_shape.getGlobalBounds(); }

    sf::Vector2f getPosition() const { return m_shape.getPosition(); }
    void setPosition(sf::Vector2f pos) { m_shape.setPosition(pos); }
};