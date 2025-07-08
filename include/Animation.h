#ifndef ANIMATION_H
#define ANIMATION_H
#include "Game.h"
#include <string>
#include <map>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Rect.hpp>

struct AnimationData {
    int startFrame;
    int endFrame;
    float frameTime;
    int row;
    int colStart;
    int colEnd;
    int numColumns;
};

// Wspólny enum dla stanu gracza i animacji
enum class AnimState { Idle, Run, Jump, Fall };

class Animation {
private:
    int currentFrame;
    int totalFrames;
    float frameTime;
    float timer;

    std::map<AnimState, AnimationData> animations;
    AnimState currentAnimation;
    bool playing;

    sf::Sprite* m_sprite; // wskaźnik na sprite
    int frameWidth, frameHeight;
    int startX, startY; // pozycja pierwszej klatki

public:
    Animation();
    ~Animation();

    void setSprite(sf::Sprite* sprite);
    void setFrameData(int frameW, int frameH, int startX, int startY);
    void addAnimation(AnimState state, int row, int colStart, int colEnd, float frameTime, int numColumns);
    void setAnimation(AnimState name);
    void play(float dt);
    void update(float dt);
    bool isFinished() const;
    int getCurrentFrame() const;
};
#endif