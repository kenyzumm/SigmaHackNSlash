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
    SplashState(GameDataRef data);
    ~SplashState();

    void init();
    // Action
    void handleInput();
    void update(float dt);
    void render(float dt);
};

#endif //SPLASHSTATE_H
