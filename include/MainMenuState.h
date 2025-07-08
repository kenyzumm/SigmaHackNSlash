#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include <DEFINITIONS.h>
#include <State.h>
#include <Game.h>

// Main game menu state
class MainMenuState : public State {
    GameDataRef m_data;                    // Common game data (window, resources, input)
    sf::Clock m_clock;                     // Clock for animations/menu
    std::optional<sf::Sprite> m_background; // Menu background
    std::optional<sf::Sprite> m_title;      // Game title
    std::optional<sf::Sprite> m_playButton; // Play button
public:
    MainMenuState(GameDataRef data);
    ~MainMenuState();

    void init();

    // Action
    void handleInput();
    void update(float dt);
    void render(float dt);
};

#endif //MAINMENUSTATE_H
