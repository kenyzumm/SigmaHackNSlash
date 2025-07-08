#include "Animation.h"

// Constructor: sets default values for animation fields
Animation::Animation() : currentFrame(0), frameTime(0.1f), timer(0), currentAnimation(AnimState::Idle), m_sprite(nullptr), frameWidth(0), frameHeight(0), startX(0), startY(0) {}
Animation::~Animation() {}

// Connects a pointer to the sprite on which animation frames will be displayed
void Animation::setSprite(sf::Sprite* sprite) {
    m_sprite = sprite;
}

// Sets the frame size and the position of the first frame in the texture
void Animation::setFrameData(int frameW, int frameH, int sX, int sY) {
    frameWidth = frameW;
    frameHeight = frameH;
    startX = sX;
    startY = sY;
    if (m_sprite) {
        m_sprite->setTextureRect(sf::IntRect({startX, startY}, {frameWidth, frameHeight}));
    }
}

// Adds an animation for a given state (Idle, Run, Jump, Fall)
// numColumns is the total number of columns in the spritesheet (needed to calculate the frame position)
void Animation::addAnimation(AnimState state, int row, int colStart, int colEnd, float frameTime, int numColumns) {
    AnimationData data;
    data.startFrame = colStart + row * numColumns; // Index of the first frame in the grid
    data.endFrame = colEnd + row * numColumns;     // Index of the last frame
    data.frameTime = frameTime;
    data.row = row;
    data.colStart = colStart;
    data.colEnd = colEnd;
    data.numColumns = numColumns;
    animations[state] = data;
}

// Sets the current animation (resets the frame counter)
void Animation::setAnimation(AnimState name) {
    if (animations.find(name) != animations.end()) {
        currentAnimation = name;
        currentFrame = animations[name].startFrame;
        frameTime = animations[name].frameTime;
        timer = 0;
        if (m_sprite) {
            int x = startX + currentFrame * frameWidth;
            int y = startY;
            m_sprite->setTextureRect(sf::IntRect({x, y}, {frameWidth, frameHeight}));
        }
    }
}

// Updates the animation: changes the frame if the time has elapsed, calculates the frame position based on numColumns
void Animation::update(float dt) {
    if (animations.find(currentAnimation) == animations.end() || !m_sprite) return;
    timer += dt;
    AnimationData& anim = animations[currentAnimation];
    if (timer >= frameTime) {
        timer = 0;
        currentFrame++;
        if (currentFrame > anim.endFrame) {
            currentFrame = anim.startFrame;
        }
    }
    // Calculate column and row based on frame number and number of columns in the spritesheet
    int frameIdx = currentFrame;
    int col = frameIdx % anim.numColumns;
    int row = frameIdx / anim.numColumns;
    int x = startX + col * frameWidth;
    int y = startY + row * frameHeight;
    m_sprite->setTextureRect(sf::IntRect({x, y}, {frameWidth, frameHeight}));
}

// Returns true if the animation has returned to the beginning (useful for one-time animations)
bool Animation::isFinished() const {
    if (animations.find(currentAnimation) == animations.end()) return true;
    const AnimationData& anim = animations.at(currentAnimation);
    return currentFrame == anim.startFrame;
}

// Returns the index of the current frame
int Animation::getCurrentFrame() const {
    return currentFrame;
}