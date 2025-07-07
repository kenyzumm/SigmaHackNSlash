#include "StateMachine.h"
#include "DEFINITIONS.h"

StateMachine::StateMachine() : m_log(LOG_FILEPATH) {}

void StateMachine::addState(stateRef newState, bool isReplacing) {
    this->m_isAdding = true;
    this->m_isReplacing = isReplacing;
    this->m_newState = std::move(newState);
}
void StateMachine::removeState() {
    this->m_isRemoving = true;
}
void StateMachine::processStateChanges() {
    if (this->m_isRemoving && !this->m_states.empty()) {
        this->m_states.pop();
        m_log.log(Logger::Level::DEBUG, "StateMachine: State removed");
        if (!this->m_states.empty()) {
            this->m_states.top()->resume();
        }
        this->m_isRemoving = false;
    }
    if (this->m_isAdding) {
        if (!this->m_states.empty()) {
            if (this->m_isReplacing) {
                this->m_states.pop();
                m_log.log(Logger::Level::DEBUG, "StateMachine: State removed to be replaced");
            } else {
                this->m_states.top()->pause();
            }
        }
        this->m_states.push(std::move(this->m_newState));
        m_log.log(Logger::Level::DEBUG, "StateMachine: State added");
        this->m_states.top()->init();
        this->m_isAdding = false;
    }
}

stateRef &StateMachine::getActiveState() {
    return this->m_states.top();
}

