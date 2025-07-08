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

    // Initializes the sprite, animations and resets player movement
    void init();
    // Updates player state: movement, collisions, animation
    void update(float dt, TileMap* tileMap);
    // Renders the player on the screen
    void render(float dt);

    // Handles keyboard input and sets direction/jump
    void handleInput();
    // Sets player position and resets speed
    void setPosition(float x, float y);
    // Returns the current X position of the player
    float getX() const;
    // Returns the current Y position of the player
    float getY() const;
};
#endif