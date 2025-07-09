#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <DEFINITIONS.h>
#include <State.h>
#include <Game.h>
#include "Player.h"
#include "TileMap.h"
#include "Logger.h"
#include "HUD.h"
#include "Bullet.h"

// Game state (gameplay)
class GameState : public State {
    GameDataRef m_data;                // Common game data (window, resources, input)
    sf::Clock m_clock;                 // Clock for measuring time
    std::optional<sf::Sprite> m_background; // Game background
    Player* m_player;                  // Pointer to player
    TileMap* m_tileMap;                // Pointer to tile map
    HUD* m_hud;                        // Pointer to HUD
    Logger m_log;
    std::vector<Bullet*> m_bullets; // Kontener na wskaźniki do pocisków
public:
    // Creates game state and connects to game data
    GameState(GameDataRef data);
    ~GameState();

    // Initializes game state (loading resources, setting map and player)
    void init();
    // Handles user input
    void handleInput();
    // Updates game logic (movement, collisions, animations)
    void update(float dt);
    // Renders game on screen
    void render(float dt);
};

#endif //GAMESTATE_H
