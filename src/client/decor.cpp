#include "include/client/decor.hpp"

decor::decor(int v) :
    sf::Sprite(),
    m_v(v)
{
}

int decor::getV()
{
    return m_v;
}
