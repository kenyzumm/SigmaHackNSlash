#ifndef SPLASHSTATE_H
#define SPLASHSTATE_H

#include <DEFINITIONS.h>
#include <State.h>
#include <Game.h>


class SplashState : public State {
    GameDataRef m_data;
    sf::Clock m_clock;
    std::optional<sf::Sprite> m_background;
public:
    SplashState(GameDataRef data);
    ~SplashState();

    // Control
    void init();
    void handleInput();
    void update(float dt);
    void render(float dt);
};

#endif //SPLASHSTATE_H
