#include "include/client/GameStateManager.hpp"

GameStateManager::GameStateManager()
{

}

GameStateManager::~GameStateManager()
{
    while(!m_pile.empty()){
        popState();
    }
}

void GameStateManager::setEtat(State *etat)
{
    etat->setManager(this);
    popState();
    pushState(etat);
}

State* GameStateManager::getEtat()
{
    return ((m_pile.empty()) ? nullptr : m_pile.top());
}

void GameStateManager::pushState(State *etat)
{
    etat->setManager(this);
    m_pile.push(etat);
    m_pile.top()->initialise();
}

void GameStateManager::popState()
{
    if(!m_pile.empty()){
        m_pile.top()->liberer();
        if(m_pile.top() != nullptr){
            delete m_pile.top();
            m_pile.top() = nullptr;
        }
        m_pile.pop();
    }
}
