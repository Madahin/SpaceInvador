#include "include/client/states/State.hpp"

State::State()
{

}

State::~State()
{
    if(m_manager != nullptr){
        m_manager = nullptr;
    }
}

void State::setManager(GameStateManager * manager)
{
    m_manager = manager;
}
