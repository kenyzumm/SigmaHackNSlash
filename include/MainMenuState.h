#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include <DEFINITIONS.h>
#include <State.h>
#include <Game.h>

class MainMenuState : public State {
    GameDataRef m_data;
    sf::Clock m_clock;
    std::optional<sf::Sprite> m_background;
    std::optional<sf::Sprite> m_title;
    std::optional<sf::Sprite> m_playButton;
public:
    MainMenuState(GameDataRef data);
    ~MainMenuState();

    // Control
    void init();
    void handleInput();
    void update(float dt);
    void render(float dt);
};

#endif //MAINMENUSTATE_H
