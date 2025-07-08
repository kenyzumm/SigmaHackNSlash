#ifndef ANIMATION_H
#define ANIMATION_H
#include "Game.h"
#include <string>
#include <map>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Rect.hpp>

// Structure describing one animation (frame range, duration, position in spritesheet)
struct AnimationData {
    int startFrame;   // Index of the first frame of the animation
    int endFrame;     // Index of the last frame of the animation
    float frameTime;  // Duration of one frame
    int row;          // Row in the spritesheet
    int colStart;     // Starting column
    int colEnd;       // Ending column
    int numColumns;   // Total number of columns in the spritesheet (needed to calculate frame position)
};

// Enum of animation/player states
enum class AnimState { Idle, Run, Jump, Fall };

// Class responsible for sprite animation based on spritesheet
class Animation {
private:
    int currentFrame; // Current index of the animation frame
    float frameTime;  // Duration of one frame
    float timer;      // Timer to change frame
    std::map<AnimState, AnimationData> animations; // Map of animations for different states
    AnimState currentAnimation; // Current animation state
    sf::Sprite* m_sprite; // Pointer to the sprite on which the animation is displayed
    int frameWidth, frameHeight; // Size of a single frame
    int startX, startY; // Position of the first frame in the texture

public:
    Animation();
    ~Animation();

    // Setters
    void setSprite(sf::Sprite* sprite);
    void setFrameData(int frameW, int frameH, int startX, int startY);
    void setAnimation(AnimState name);
    void addAnimation(AnimState state, int row, int colStart, int colEnd, float frameTime, int numColumns);

    // Updating methods
    void play(float dt);
    void update(float dt);
    // Getters
    bool isFinished() const;
    int getCurrentFrame() const;
    // Returns the current animation state
    AnimState getCurrentState() const;
};
#endif