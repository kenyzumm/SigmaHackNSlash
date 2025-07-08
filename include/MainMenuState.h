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
    // Creates menu state and connects to game data
    MainMenuState(GameDataRef data);
    ~MainMenuState();

    // Initializes menu state (loading resources, setting buttons)
    void init();
    // Handles user input (e.g., clicks)
    void handleInput();
    // Updates menu logic (e.g., animations)
    void update(float dt);
    // Renders menu to the screen
    void render(float dt);
};

#endif //MAINMENUSTATE_H
