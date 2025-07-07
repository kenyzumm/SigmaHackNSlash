#ifndef GAME_H
#define GAME_H

#include <DEFINITIONS.h>
#include "StateMachine.h"
#include "AssetsManager.h"
#include "InputManager.h"

struct GameData {
    StateMachine machine;
    sf::RenderWindow* window;
    AssetsManager assets;
    InputManager input;
};
typedef std::shared_ptr<GameData> GameDataRef;
class Game {
    const float dt = 1.0f / 60.0f;
    sf::Clock m_clock;
    GameDataRef m_data = std::make_shared<GameData>();
public:
    Game(int width, int height, std::string title);
    ~Game();
    void run();
};



#endif //GAME_H
