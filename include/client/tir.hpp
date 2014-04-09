#ifndef CLASSETIR
#define CLASSETIR

#include <vector>
#include <sstream>
#include <random>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "entite.hpp"
#include "joueur.hpp"
#include "ennemi.hpp"

#define VIT -5

class Tir: public Entite
{
public:
    //! Constructeur de tir
    /*!
      Entree : int
      Sortie :
      Description : cree un tir et lui donne un ID
    */
    Tir(unsigned int);
    //! Constructeur de tir de joueur
    /*!
      Entree : unsigned int, Joueur&
      Sortie :
      Description : cree un tir devant le joueur qui l'a tire
    */
    Tir(unsigned int, Joueur &);
    //! Constructeur de tir d'ennemi
    /*!
      Entree : unsigned int, Joueur &
      Sortie :
      Description : cree un tir et le place devant l'ennemi qui l'a tire
    */
    Tir(unsigned int, Ennemi &);
    //! Destructeur de tir
    /*!
      Entree :
      Sortie :
      Description :
    */
    ~Tir();

    //! Faire avancer le tir
    /*!
      Entree :
      Sortie :
      Description : Fait avancer le tir dans la direction dans laquelle il a ete lance
    */
    virtual void bouger();
private:


};

#endif
