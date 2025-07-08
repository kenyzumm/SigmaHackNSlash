#ifndef PLAYER_H
#define PLAYER_H
#include "Movement.h"
#include "Animation.h"
#include "Collision.h"
#include "Game.h"
#include <SFML/Graphics/Sprite.hpp>
#include <optional>
#include <TileMap.h>

class Player {
private:
    GameDataRef m_data;

    Movement m_movement;
    Animation m_animation;
    Collision m_collision;

    float m_dirX, m_dirY;
    bool m_isMoving;
    AnimState m_state;

    std::optional<sf::Sprite> m_sprite;

    // void updateSpritePosition(); // już niepotrzebne

public:
    Player(GameDataRef data);
    ~Player();

    void init();
    void update(float dt, TileMap* tileMap);
    void render(float dt);

    void handleInput();
    void move(float dirX, float dirY, float dt);
    void setPosition(float x, float y);
    float getX() const;
    float getY() const;
    Collision& getCollision();
};
#endif