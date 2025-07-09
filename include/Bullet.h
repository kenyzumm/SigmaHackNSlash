#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>

class Bullet {
    sf::CircleShape m_shape;
    sf::Vector2f m_position;
    sf::Vector2f m_velocity;
    float m_speed;
    float m_direction;
    float m_damage;
    float m_range;

    public:
        Bullet();
        Bullet(const sf::Vector2f& position, const sf::Vector2f& velocity); // Nowy konstruktor
        ~Bullet();
        void update(float dt);
        void draw(sf::RenderWindow* window); // Poprawka literówki
        void setPosition(const sf::Vector2f& pos) { m_position = pos; m_shape.setPosition(pos); }
        void setVelocity(const sf::Vector2f& vel) { m_velocity = vel; }
        sf::Vector2f getPosition() const { return m_position; }
};

#endif // BULLET_H