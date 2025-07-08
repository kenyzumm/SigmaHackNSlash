#ifndef PLAYER_H
#define PLAYER_H
#include "Movement.h"
#include "Animation.h"
#include "Collision.h"
#include "Game.h"
#include <SFML/Graphics/Sprite.hpp>

class Player {
private:
    GameDataRef m_data;
    std::optional<sf::Sprite> m_sprite;

    Movement m_movement;
    Animation m_animation;
    Collision m_collision;

    float m_dirX, m_dirY;
    bool m_isMoving;
    std::string m_state; // np. "idle", "run", "jump"

    // void updateSpritePosition(); // już niepotrzebne

public:
    Player(GameDataRef data);
    ~Player();

    void init();
    void update(float dt);
    void render(float dt);

    void handleInput();
    void move(float dirX, float dirY, float dt);
    void setPosition(float x, float y);
    float getX() const;
    float getY() const;
    Collision& getCollision();
};
#endif