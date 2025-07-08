#include "Game.h"
#include "SplashState.h"
#include <iostream>

// Constructor: creates a window, adds the initial state and starts the game loop
Game::Game(int width, int height, std::string title) {
    this->m_data->window = new sf::RenderWindow(sf::VideoMode(sf::Vector2u(width, height)), title, sf::Style::Titlebar | sf::Style::Close, sf::State::Fullscreen);
    this->m_data->machine.addState(stateRef(new SplashState(this->m_data)));
    this->run();
}
Game::~Game() {
    delete this->m_data->window;
}

// Main game loop: handles states, updates and renders the game at a fixed time step
void Game::run() {
    float newTime, frameTime, interpolation;
    float currentTime = this->m_clock.getElapsedTime().asSeconds();
    float accumulator = 0.0f;

    while (this->m_data->window->isOpen()) {
        this->m_data->machine.processStateChanges(); // Process state changes
        newTime = this->m_clock.getElapsedTime().asSeconds();
        frameTime = newTime - currentTime;
        if (frameTime > 0.25f) {
            frameTime = 0.25f;
        }
        currentTime = newTime;
        accumulator += frameTime;
        while (accumulator >= this->dt) {
            this->m_data->machine.getActiveState()->handleInput();
            this->m_data->machine.getActiveState()->update(dt);
            accumulator -= this->dt;
        }
        interpolation = accumulator / this->dt;
        this->m_data->machine.getActiveState()->render(interpolation);
    }
}

