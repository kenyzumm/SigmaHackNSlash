#include "HUD.h"

HUD::HUD(GameDataRef data) : m_data(data) {
    m_weaponBar = std::nullopt;
    m_dashCooldown = std::nullopt;

    m_font = m_data->assets.getFont("Arial");

    m_dashCooldown = sf::Text(m_font);
    m_dashCooldown->setString("Dash Cooldown: 0");
    m_dashCooldown->setCharacterSize(24);
    m_dashCooldown->setPosition({500, 10});
}

HUD::~HUD() {}

void HUD::update(float dt) {
    // Update the dash cooldown
    if (m_dashCooldown) {
        m_dashCooldown->setString("Dash Cooldown: " + std::to_string(m_dashCooldown->getCharacterSize()));
    }

    sf::Sprite healthHearth(m_data->assets.getTexture("HUD Hearth"));
    for(int i=0; i<5; i++) {
        healthHearth.setPosition({10 + i*64, 10});
        m_healthHearthVector.push_back(healthHearth);
    }
}

void HUD::draw() {
    for(const auto& healthHearth : m_healthHearthVector) {
        m_data->window->draw(healthHearth);
    }
    if(m_weaponBar) m_data->window->draw(*m_weaponBar);
    if(m_dashCooldown) m_data->window->draw(*m_dashCooldown);
}