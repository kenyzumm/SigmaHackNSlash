#ifndef GAME_H
#define GAME_H

#include <DEFINITIONS.h>
#include "StateMachine.h"
#include "AssetsManager.h"
#include "InputManager.h"

// Structure to store common game data (state machine, window, assets, input)
struct GameData {
    StateMachine machine;         // Game state machine
    sf::RenderWindow* window;     // Pointer to the game window
    AssetsManager assets;         // Asset management
    InputManager input;           // Input handling
};
// Shared pointer to GameData
typedef std::shared_ptr<GameData> GameDataRef;

// Main game class: manages the game loop, window, and states
class Game {
    const float dt = 1.0f / 60.0f; // Constant time step (60 FPS)
    sf::Clock m_clock;             // Clock for measuring time
    GameDataRef m_data = std::make_shared<GameData>(); // Common game data
public:
    Game(int width, int height, std::string title);
    ~Game();
    // Runs the main game loop
    void run();
};

#endif //GAME_H
