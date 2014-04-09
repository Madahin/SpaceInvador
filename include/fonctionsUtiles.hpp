#ifndef FONCTION_UTILES
#define FONCTION_UTILES

#include <iostream>

#include <vector>

#include <sstream>
#include "include/client/joueur.hpp"
#include "include/client/entite.hpp"

template<typename T>
T trouveEntiterParId(const std::vector<T> &vec, const sf::Uint16 id);
bool collision(const Entite *e1, const Entite *e2);
std::vector<Entite*> getEntiteProche(const Entite *e, const std::vector<Entite*> &vec);
void deleteByID(const int id, std::vector<Entite*> &vec);

std::string intToString(const unsigned int );
int stringToInt(std::string s);
#endif
