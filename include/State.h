#ifndef STATE_H
#define STATE_H

#include <SFML/Graphics.hpp>

// Klasa bazowa dla wszystkich stanów gry (ekranów)
// Pozwala na polimorficzne zarządzanie ekranami (menu, gra, splash itp.)
class State {
public:
    // Wywoływane przy inicjalizacji stanu (np. ładowanie zasobów)
    virtual void init() = 0;
    // Obsługuje wejście użytkownika (np. klawiatura, mysz)
    virtual void handleInput() = 0;
    // Zatrzymuje stan (np. gdy przechodzimy do innego stanu w tle)
    virtual void pause() {}
    // Wznawia stan po pauzie
    virtual void resume() {}
    // Aktualizuje logikę stanu (np. ruch, AI, fizyka)
    virtual void update(float dt) = 0;
    // Renderuje stan na ekranie
    virtual void render(float dt) = 0;
};

#endif //STATE_H
