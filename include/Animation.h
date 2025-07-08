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
};

class Animation {
private:
    int currentFrame;
    int totalFrames;
    float frameTime;
    float timer;

    std::map<std::string, AnimationData> animations;
    std::string currentAnimation;
    bool playing;

    sf::Sprite* m_sprite; // wskaźnik na sprite
    int frameWidth, frameHeight;
    int startX, startY; // pozycja pierwszej klatki

public:
    Animation();
    ~Animation();

    void setSprite(sf::Sprite* sprite);
    void setFrameData(int frameW, int frameH, int startX, int startY);
    void addAnimation(const std::string& name, int startFrame, int endFrame, float frameTime);
    void setAnimation(const std::string& name);
    void play(float dt);
    void update(float dt);
    bool isFinished() const;
    int getCurrentFrame() const;
};
#endif