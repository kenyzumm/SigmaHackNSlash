#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <DEFINITIONS.h>
#include <State.h>
#include <Game.h>
#include "Player.h"

class GameState : public State {
    GameDataRef m_data;
    sf::Clock m_clock;
    std::optional<sf::Sprite> m_background;
    Player* m_player;
    
    
    
public:
    GameState(GameDataRef data);
    ~GameState();
    
    // Control
    void init();
    void handleInput();
    void update(float dt);
    void render(float dt);
};

#endif //GAMESTATE_H
