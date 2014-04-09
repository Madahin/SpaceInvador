#ifndef CLASSEJOUEUR
#define CLASSEJOUEUR

#include <vector>
#include <sstream>
#include <random>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "entite.hpp"


class Joueur: public Entite
{
public:
    //! Constructeur de Joueur
    /*!
      Entree : int
      Sortie :
      Description : Cree un joueur et lui donne un id
    */
    Joueur(unsigned int);
    //! Constructeur de recopie de joueur
    /*!
      Entree : Joueur &
      Sortie :
      Description :
    */
    Joueur(const Joueur &j);
    //! Destructeur de joueur
    /*!
      Entree :
      Sortie :
      Description :
    */
    ~Joueur();
    //! modifier le score
    /*!
      Entree : const int
      Description : additionne l'entier au score de base du joueur
    */
    void modifScore(const int);
    //! Setter score
    /*!
      Entree : const int
      Description : redefinit le score du joueur
    */
    void set_score(const int);
    //! Setter d'invulnerabilite
    /*!
      Entree : bool
      Description : dire si le joueur est invulnerable
    */
    void setInvu(bool);
    //! Getter score
    /*!
      Entree :
      Sortie : int
      Description : retourne le score du joueur
    */
    int get_score()const;
    //! Getter invulnerabilite
    /*!
      Entree :
      Sortie : bool
      Description : savoir si le joueur est invulnerable
    */
    bool getInvu()const;

    sf::Clock timer;
    sf::Color oldColor;

private:
    long int m_score;
    bool m_invulnerable;



};

#endif
