#include "Bullet.h"


Bullet::Bullet(const sf::Vector2f& position, const sf::Vector2f& velocity) {
    m_shape.setRadius(5);
    m_shape.setFillColor(sf::Color::White);
    m_position = position;
    m_velocity = velocity;
    m_shape.setPosition(position);
    m_speed = 1000;
    m_direction = 0;
    m_damage = 10;
    m_range = 1000;
}

Bullet::~Bullet() {}

void Bullet::update(float dt) {
    m_position += m_velocity * dt;
    m_shape.setPosition(m_position);
}

void Bullet::draw(sf::RenderWindow* window) {
    window->draw(m_shape);
}