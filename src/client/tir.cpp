#include "include/client/tir.hpp"

Tir::Tir(unsigned int id):
    Entite(id)
{
    m_hitbox.loadFromFile("Ressources/tir_silhouette.png");
}

Tir::Tir(unsigned int id, Joueur & j):
    Tir(id)
{
    setPosition(
        j.getPosition().x + 13  ,
        j.getPosition().y - getGlobalBounds().height - 13
    );
}
Tir::Tir(unsigned int id, Ennemi & j):
    Tir(id)
{
    setPosition(
        j.getPosition().x + ( j.getGlobalBounds().width - m_hitbox.getSize().x ) / 2.f ,
        j.getPosition().y + j.getGlobalBounds().height + 1
    );
}

Tir::~Tir()
{
}

void Tir::bouger()
{
    move(0,VIT);
}
