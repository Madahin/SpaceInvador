#include "include/serveur/SocketTCPj.hpp"

SocketTCPj::SocketTCPj(int id) :
    sf::TcpSocket(),
    m_id(id)
{
}

int SocketTCPj::getId()
{
    return m_id;
}

void SocketTCPj::setId(int id)
{
    m_id = id;
}
