#ifndef FONCTIONXML
#define FONCTIONXML

#include <sstream>
#include <SFML/System.hpp>
#include "include/serveur/serveur.hpp"
#include "include/serveur/ennemi.hpp"
#include "include/pugixml.hpp"

class Serveur;
//! Creation d'un document XML concernant les ennemis
/*!
  Entree : Serveur*, unsigned int, float, unsigned int
  Sortie : string
  Description : definit tous les ennemis du niveau a venir dans un XML pour l'envoyer aux clients
*/
std::string creationDocXml_ennemis(Serveur *s, unsigned int cadence, float vitesse, unsigned int vie);
//! Creation d'un document XML concernant les scores de fin de partie
/*!
  Entree : vector<Joueur*>
  Sortie : string
  Description : definit un classement des scores dans un XML pour l'envoyer aux clients
*/
std::string  creationDocXml(std::vector<Joueur*> vec);

#endif
