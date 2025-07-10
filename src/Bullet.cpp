#include "Bullet.h"
#include "TileMap.h"


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

void Bullet::draw(sf::RenderWindow* window) { window->draw(m_shape); }

bool Bullet::checkTileCollision(const TileMap* tileMap) const {
    if (!tileMap) return false;
    
    // Get bullet bounds as a rectangle (approximation of circle)
    sf::FloatRect bulletBounds = getBounds();
    
    // Convert world coordinates to tile coordinates
    int tileSize = tileMap->getTileSize();
    int startTileX = static_cast<int>(bulletBounds.position.x / tileSize);
    int endTileX = static_cast<int>((bulletBounds.position.x + bulletBounds.size.x) / tileSize);
    int startTileY = static_cast<int>(bulletBounds.position.y / tileSize);
    int endTileY = static_cast<int>((bulletBounds.position.y + bulletBounds.size.y) / tileSize);
    
    // Check all tiles that the bullet might overlap with
    for (int tileY = startTileY; tileY <= endTileY; ++tileY) {
        for (int tileX = startTileX; tileX <= endTileX; ++tileX) {
            if (tileMap->isCollidable(tileX, tileY)) {
                return true; // Collision detected with solid tile
            }
        }
    }
    
    return false; // No collision with solid tiles
}

sf::FloatRect Bullet::getBounds() const {
    float radius = m_shape.getRadius();
    return sf::FloatRect(
        {m_position.x - radius,  // left
        m_position.y - radius},  // top
        {radius * 2,             // width
        radius * 2}              // height
    );
}
