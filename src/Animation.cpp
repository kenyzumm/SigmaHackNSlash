#include "Animation.h"

Animation::Animation() : currentFrame(0), totalFrames(0), frameTime(0.1f), timer(0), currentAnimation(AnimState::Idle), playing(false), m_sprite(nullptr), frameWidth(0), frameHeight(0), startX(0), startY(0) {}
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

void Animation::addAnimation(AnimState state, int row, int colStart, int colEnd, float frameTime, int numColumns) {
    AnimationData data;
    data.startFrame = colStart + row * numColumns;
    data.endFrame = colEnd + row * numColumns;
    data.frameTime = frameTime;
    data.row = row;
    data.colStart = colStart;
    data.colEnd = colEnd;
    data.numColumns = numColumns;
    animations[state] = data;
}

void Animation::setAnimation(AnimState name) {
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
    if (!playing || animations.find(currentAnimation) == animations.end() || !m_sprite) return;
    timer += dt;
    AnimationData& anim = animations[currentAnimation];
    if (timer >= frameTime) {
        timer = 0;
        currentFrame++;
        if (currentFrame > anim.endFrame) {
            currentFrame = anim.startFrame;
            playing = false;
        }
    }
    // Wylicz kolumnę i rząd na podstawie currentFrame
    int frameIdx = currentFrame;
    int col = frameIdx % anim.numColumns;
    int row = frameIdx / anim.numColumns;
    int x = startX + col * frameWidth;
    int y = startY + row * frameHeight;
    m_sprite->setTextureRect(sf::IntRect({x, y}, {frameWidth, frameHeight}));
}

void Animation::update(float dt) {
    play(dt);
}

bool Animation::isFinished() const {
    if (animations.find(currentAnimation) == animations.end()) return true;
    const AnimationData& anim = animations.at(currentAnimation);
    return !playing && currentFrame == anim.startFrame;
}

int Animation::getCurrentFrame() const {
    return currentFrame;
}