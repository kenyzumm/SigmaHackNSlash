#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <memory>
#include <stack>
#include "State.h"
#include "Logger.h"

// Alias na unikalny wskaźnik do stanu
typedef std::unique_ptr<State> stateRef;

// Klasa zarządzająca stosowaniem i przełączaniem stanów gry
class StateMachine {
    std::stack<stateRef> m_states; // Stos stanów (np. menu, gra, pauza)
    stateRef m_newState;           // Nowy stan do dodania
    bool m_isRemoving;             // Czy należy usunąć stan
    bool m_isAdding;               // Czy należy dodać stan
    bool m_isReplacing;            // Czy nowy stan zastępuje obecny
    Logger m_log;                  // Logger do debugowania zmian stanów
public:
    StateMachine();
    ~StateMachine() {}

    // Dodaje nowy stan do stosu (może zastąpić obecny)
    void addState(stateRef newState, bool isReplacing = false);
    // Oznacza obecny stan do usunięcia
    void removeState();
    // Przetwarza zmiany stanów (dodanie/usunięcie)
    void processStateChanges();

    // Zwraca wskaźnik do aktywnego stanu
    stateRef &getActiveState();
};

#endif //STATEMACHINE_H
