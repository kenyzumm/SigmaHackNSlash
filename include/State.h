#ifndef STATE_H
#define STATE_H

#include <SFML/Graphics.hpp>

class State {
public:
    // Control
    virtual void init() = 0;
    virtual void handleInput() = 0;
    virtual void pause() {}
    virtual void resume() {}
    virtual void update(float dt) = 0;
    virtual void render(float dt) = 0;
};



#endif //STATE_H
