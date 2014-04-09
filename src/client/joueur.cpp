#include "include/client/joueur.hpp"

Joueur::Joueur(unsigned int id):
    Entite(id),
    m_score(0)
{
    m_hitbox.loadFromFile("Ressources/vaisseau_silhouette.png");
}
Joueur::Joueur(const Joueur & j):
    Entite(j),
    m_score(j.m_score)
{
    m_hitbox.loadFromFile("Ressources/vaisseau_silhouette.png");
}

Joueur::~Joueur()
{
}


void Joueur::set_score(const int x)
{
    m_score=x;
}

void Joueur::setInvu(bool b)
{
    m_invulnerable = b;
}

int Joueur::get_score()const
{
    return m_score;
}

bool Joueur::getInvu()const
{
    return m_invulnerable;
}

void Joueur::modifScore(const int difference)
{
    m_score+=difference;
}

