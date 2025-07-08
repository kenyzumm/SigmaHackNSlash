#ifndef PLAYER_H
#define PLAYER_H
#include "Movement.h"
#include "Animation.h"
#include "Collision.h"
#include "Game.h"
#include <SFML/Graphics/Sprite.hpp>
#include <optional>
#include <TileMap.h>

// Class representing the player: handles movement, animations, collisions with the map and rendering
class Player {
private:
    GameDataRef m_data; // Common game data (window, resources, input)
    Movement m_movement; // Responsible for player movement physics
    Animation m_animation; // Responsible for player sprite animations
    float m_dirX; // Movement direction on the X axis (-1, 0, 1)
    bool m_isMoving; // Whether the player is moving
    std::optional<sf::Sprite> m_sprite; // Player sprite (may not be loaded)

public:
    // Creates the player and connects it to game data
    Player(GameDataRef data);
    ~Player();

    void init();
    // Action
    void update(float dt, TileMap* tileMap);
    void render(float dt);
    void handleInput();
    // Setters
    void setPosition(float x, float y);
    // Getters
    // Returns the current X position of the player
    float getX() const;
    // Returns the current Y position of the player
    float getY() const;
    // Returns if the player is currently moving
    bool isMoving() const;
};
#endif