#ifndef SPLASHSTATE_H
#define SPLASHSTATE_H

#include <DEFINITIONS.h>
#include <State.h>
#include <Game.h>

// Splash screen state
class SplashState : public State {
    GameDataRef m_data;                // Common game data (window, resources, input)
    sf::Clock m_clock;                 // Clock to measure splash duration
    std::optional<sf::Sprite> m_background; // Splash screen background
public:
    // Creates splash state and connects to game data
    SplashState(GameDataRef data);
    ~SplashState();

    // Initializes splash state (loading background)
    void init();
    // Handles user input (e.g., closing window)
    void handleInput();
    // Updates splash logic (proceeds after time)
    void update(float dt);
    // Renders splash on screen
    void render(float dt);
};

#endif //SPLASHSTATE_H
