#include "include/client/entite.hpp"

Entite::Entite(unsigned int id):
    m_id(id)
{
}
Entite::Entite(unsigned int id, int vie):
    m_id(id),
    m_vie(vie)
{
}

Entite::Entite(const Entite & e):
    m_id(e.m_id),
    m_vie(e.m_vie)
{
    setPosition(e.getPosition().x,e.getPosition().y);
}

Entite::~Entite()
{
}

void Entite::bouger()
{

}

unsigned int Entite::getId()const
{
    return m_id;
}

unsigned int Entite::getVie()const
{
    return m_vie;
}

const sf::Image& Entite::getHitBox()const
{
    return m_hitbox;
}

void Entite::setVie(const unsigned int x)
{
    m_vie=x;
}

void Entite::setId(const unsigned int x)
{
    m_id=x;
}

void Entite::setItBox(const sf::Image &img)
{
    m_hitbox = img;
}

void Entite::baisserVie()
{
    m_vie-=1;
}

bool Entite::operator ==(const unsigned int x)const
{
    return m_id==x;
}

bool Entite::operator !=(const Entite &e)const
{
    return m_id!=e.getId();
}

bool operator ==(const Entite &e, const unsigned int x)
{
    return e.m_id == x;
}

bool Entite::estDansEcran()
{
    return(
        getPosition().x<640 &&
        getPosition().x>0 &&
        getPosition().y<480 &&
        getPosition().y>0
    );
}
