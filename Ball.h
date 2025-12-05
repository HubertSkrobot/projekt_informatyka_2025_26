#pragma once
#include <SFML/Graphics.hpp>
#include "Paddle.h"

class Ball {
private:
    sf::CircleShape m_shape;
    sf::Vector2f velocity;
    bool lost = false;

public:
    Ball(sf::Vector2f startPos = { 400.f,400.f }, float radius = 15.f, sf::Vector2f startVel = { 150.f,150.f })
        : velocity(startVel)
    {
        m_shape.setPosition(startPos);
        m_shape.setRadius(radius);
        m_shape.setFillColor(sf::Color::Yellow);
        m_shape.setOrigin(radius, radius);
    }

    void draw(sf::RenderTarget& window) { window.draw(m_shape); }

    void ruch(sf::Time dt, sf::Vector2f windowSize, Paddle& paddle) {
        m_shape.move(velocity * dt.asSeconds());
        sf::Vector2f pos = m_shape.getPosition();
        float r = m_shape.getRadius();
        if (pos.x - r < 0 || pos.x + r >= windowSize.x) velocity.x *= -1; //kolizje z krawedziami bocznymi
        if (pos.y - r < 0) velocity.y *= -1; //kolizja z krawedzia gorna
        if (pos.y + r >= windowSize.y) lost = true; //kolizja z krawedzia dolna. zwraca true dla lost czyli przegrana gra
        if (m_shape.getGlobalBounds().intersects(paddle.getBounds())) velocity.y *= -1; //kolizja z paletka
    }

    sf::FloatRect getShapeBounds() const { return m_shape.getGlobalBounds(); }
    const sf::CircleShape& getShape() const { return m_shape; }
    void bounceX() { velocity.x *= -1; }
    void bounceY() { velocity.y *= -1; }
    bool isLost() const { return lost; }

    sf::Vector2f getVelocity() const { return velocity; }
    void setVelocity(sf::Vector2f v) { velocity = v; }

    sf::Vector2f getPosition() const { return m_shape.getPosition(); }
    void setPosition(sf::Vector2f pos) { m_shape.setPosition(pos); }
};