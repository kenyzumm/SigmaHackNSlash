#include "StateMachine.h"

// Constructor: initializes logger
StateMachine::StateMachine() : m_log("StateMachineLogs.txt") {}

// Adds a new state to the stack (can replace the current one)
void StateMachine::addState(stateRef newState, bool isReplacing) {
    this->m_isAdding = true;
    this->m_isReplacing = isReplacing;
    this->m_newState = std::move(newState);
}
// Marks the current state for removal
void StateMachine::removeState() {
    this->m_isRemoving = true;
}
// Processes state changes: adds or removes states from the stack
void StateMachine::processStateChanges() {
    if (this->m_isRemoving && !this->m_states.empty()) {
        this->m_states.pop();
        LOG_DEBUG(m_log, "State removed");
        if (!this->m_states.empty()) {
            this->m_states.top()->resume();
        }
        this->m_isRemoving = false;
    }
    if (this->m_isAdding) {
        if (!this->m_states.empty()) {
            if (this->m_isReplacing) {
                this->m_states.pop();
                LOG_DEBUG(m_log, "State removed to be replaced");
            } else {
                this->m_states.top()->pause();
            }
        }
        this->m_states.push(std::move(this->m_newState));
        LOG_DEBUG(m_log, "State added");
        this->m_states.top()->init();
        this->m_isAdding = false;
    }
}
// Returns a pointer to the active state (at the top of the stack)
stateRef &StateMachine::getActiveState() {
    return this->m_states.top();
}

