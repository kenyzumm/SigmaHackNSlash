#include "MainMenuState.h"
#include "GameState.h"

MainMenuState::MainMenuState(GameDataRef data) : m_data(data) {

}
MainMenuState::~MainMenuState() {}
void MainMenuState::init() {
    // Loading textures to m_data
    m_data->assets.loadTexture("MainMenu Background", MAINMENU_BACKGROUND_PATH);
    m_data->assets.loadTexture("MainMenu Title", MAINMENU_TITLE_PATH);
    m_data->assets.loadTexture("MainMenu PlayButton", MAINMENU_PLAYBUTTON_PATH);

    // Creating Sprites
    m_background = sf::Sprite(m_data->assets.getTexture("MainMenu Background"));
    m_title = sf::Sprite(m_data->assets.getTexture("MainMenu Title"));
    m_playButton = sf::Sprite(m_data->assets.getTexture("MainMenu PlayButton"));

    // Changing positions of sprites
    // m_title.setPosition();
    // m_playButton.setPosition();
}
void MainMenuState::handleInput() {
    while (const std::optional<sf::Event> event = this->m_data->window->pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            this->m_data->window->close();
        }
        if (m_data->input.isSpriteClicked(*m_playButton, sf::Mouse::Button::Left, m_data->window)) {
            m_data->machine.addState(stateRef(new GameState(m_data)), true);
        }
    }
}
void MainMenuState::update(float dt) {}
void MainMenuState::render(float dt) {
    m_data->window->clear();

    m_data->window->draw(*m_background);
    m_data->window->draw(*m_title);
    m_data->window->draw(*m_playButton);

    m_data->window->display();
}
