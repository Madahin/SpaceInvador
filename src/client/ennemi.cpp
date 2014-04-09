#include "include/client/ennemi.hpp"

Ennemi::Ennemi(unsigned int id):
    Entite(id)
{
    m_hitbox.loadFromFile("Ressources/ennemi_silhouette.png");
}


Ennemi::Ennemi(int id,int vie,int ydepart,int pointCadence,int vitesseX,int vitesseY):
    Entite(id),
    m_pointCadence(pointCadence),
    m_vitesseX(vitesseX),
    m_vitesseY(vitesseY)
{
    //On redefinit la position
    this->setPosition(-38.0,(float)ydepart);
}

Ennemi::~Ennemi()
{
}

void Ennemi::bouger()
{
    move(m_vitesseX, m_vitesseY);
}


void Ennemi::setPointCadence(const int x)
{
    m_pointCadence=x;
}
void Ennemi::setVitesseX(const int x)
{
    m_vitesseX=x;
}
void Ennemi::setVitesseY(const int x)
{
    m_vitesseY=x;
}
int Ennemi::getPointCadence()const
{
    return m_pointCadence;
}
int Ennemi::getVitesseX()const
{
    return m_vitesseX;
}
int Ennemi::getVitesseY()const
{
    return m_vitesseY;
}
