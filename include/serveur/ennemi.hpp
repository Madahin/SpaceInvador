#ifndef ENNEMI
#define ENNEMI

#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include "serveur.hpp"
#include <random>
#include <chrono>

class Serveur;
class Ennemi
{
public:
    //! Constructeur d'ennemi
    /*!
      Entree : Serveur*
      Sortie : Ennemi
      Fonctionnement : Cree un ennemi aleatoire en fonction des donnees du serveur
    */
    Ennemi(Serveur *s);
    //! Destructeur d'ennemi
    /*!
      Entree :
      Sortie :
      Fonctionnement :
    */
    ~Ennemi();

    //! Getter vie
    /*!
      Entree :
      Sortie : int
      Fonctionnement : retourne la vie d'un ennemi
    */
    unsigned int getVie()const;
    //! Getter cadence
    /*!
      Entree :
      Sortie : int
      Fonctionnement : retourne le moment auquel l'ennemi doit tirer
    */
    unsigned int getCadence()const;
    //! Getter vitesseX
    /*!
      Entree :
      Sortie : int
      Fonctionnement : retourne la vitesse de deplacement sur l'axe X
    */
    int getVitesseX()const;
    //! Getter vitesseY
    /*!
      Entree :
      Sortie : int
      Fonctionnement : retourne la vitesse de deplacement sur l'axe Y
    */
    int getVitesseY()const;
    //! Getter xDepart
    /*!
      Entree :
      Sortie : int
      Fonctionnement : retourne l'abscisse a laquelle l'ennemi apparaitra
    */
    int getXDepart()const;
    //! Getter yDepart
    /*!
      Entree :
      Sortie : int
      Fonctionnement : retourne l'ordonnee a laquelle l'ennemi apparaitra
    */
    int getYDepart()const;
    //! Setter vie
    /*!
      Entree : const int
      Sortie :
      Fonctionnement : definir la vie de l'ennemi
    */
    void setVie(const int);
    //! Setter Cadence
    /*!
      Entree : const int
      Sortie :
      Fonctionnement : definir le moment de tir de l'ennemi
    */
    void setCadence(const int);
    //! Setter VitesseX
    /*!
      Entree : const int
      Sortie :
      Fonctionnement : definir la vitesse de l'ennemi sur l'axe X
    */
    void setVitesseX(const int);
    //! Setter vitesseY
    /*!
      Entree : const int
      Sortie :
      Fonctionnement : definir la vitesse de l'ennemi sur l'axe Y
    */
    void setVitesseY(const int);
    //! Setter xDepart
    /*!
      Entree : const int
      Sortie :
      Fonctionnement : definir le point d'apparition de l'ennemi sur l'axe X
    */
    void setXDepart(const int);
    //! Setter yDepart
    /*!
      Entree : const int
      Sortie :
      Fonctionnement : definir le point d'apparition de l'ennemi sur l'axe Y
    */
    void setYDepart(const int);

private:
    const Serveur *m_serveur;
    unsigned int m_vie;
    unsigned int m_cadence;
    int m_vitesseX;
    int m_vitesseY;
    int m_XDepart;
    int m_YDepart;
};

#endif
