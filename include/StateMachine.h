#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include <memory>
#include <stack>
#include "State.h"
#include "Logger.h"

typedef std::unique_ptr<State> stateRef;
class StateMachine {
    std::stack<stateRef> m_states;
    stateRef m_newState;
    bool m_isRemoving;
    bool m_isAdding;
    bool m_isReplacing;
    Logger m_log;
public:
    StateMachine();
    ~StateMachine() {}

    // Control
    void addState(stateRef newState, bool isReplacing = false);
    void removeState();
    void processStateChanges();

    // Getters
    stateRef &getActiveState();
};



#endif //STATEMACHINE_H
