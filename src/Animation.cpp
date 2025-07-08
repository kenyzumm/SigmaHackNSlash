#include "Animation.h"

Animation::Animation() : currentFrame(0), totalFrames(0), frameTime(0.1f), timer(0), currentAnimation(""), playing(false), m_sprite(nullptr), frameWidth(0), frameHeight(0), startX(0), startY(0) {}
Animation::~Animation() {}

void Animation::setSprite(sf::Sprite* sprite) {
    m_sprite = sprite;
}

void Animation::setFrameData(int frameW, int frameH, int sX, int sY) {
    frameWidth = frameW;
    frameHeight = frameH;
    startX = sX;
    startY = sY;
    if (m_sprite) {
        m_sprite->setTextureRect(sf::IntRect({startX, startY}, {frameWidth, frameHeight}));
    }
}

void Animation::addAnimation(const std::string& name, int startFrame, int endFrame, float frameTime) {
    animations[name] = {startFrame, endFrame, frameTime};
}

void Animation::setAnimation(const std::string& name) {
    if (animations.find(name) != animations.end()) {
        currentAnimation = name;
        currentFrame = animations[name].startFrame;
        frameTime = animations[name].frameTime;
        timer = 0;
        playing = true;
        if (m_sprite) {
            int x = startX + currentFrame * frameWidth;
            int y = startY;
            m_sprite->setTextureRect(sf::IntRect({x, y}, {frameWidth, frameHeight}));
        }
    }
}

void Animation::play(float dt) {
    if (!playing || currentAnimation.empty() || !m_sprite) return;
    timer += dt;
    const AnimationData& anim = animations[currentAnimation];
    if (timer >= frameTime) {
        timer = 0;
        currentFrame++;
        if (currentFrame > anim.endFrame) {
            currentFrame = anim.startFrame;
            playing = false;
        }
        int x = startX + currentFrame * frameWidth;
        int y = startY;
        m_sprite->setTextureRect(sf::IntRect({x, y}, {frameWidth, frameHeight}));
    }
}

void Animation::update(float dt) {
    play(dt);
}

bool Animation::isFinished() const {
    if (currentAnimation.empty()) return true;
    const AnimationData& anim = animations.at(currentAnimation);
    return !playing && currentFrame == anim.startFrame;
}

int Animation::getCurrentFrame() const {
    return currentFrame;
}