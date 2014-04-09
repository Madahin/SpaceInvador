#ifndef CLASSEENEMI
#define CLASSEENNEMI

#include <vector>
#include <sstream>
#include <random>
#include <cstdlib>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "entite.hpp"


class Ennemi: public Entite
{
public:
    //! Ennemi
    /*!
        Entrée: int id
        Sortie:
        Description: Constructeur
    */
    Ennemi(unsigned int);

    //! ~Ennemi
    /*!
        Entrée:
        Sortie:
        Description: destructeur
    */
    ~Ennemi();

    //! Ennemi
    /*!
        Entrée: int id,int vie,int ydepart,int pointCadence,int vitesseX,int vitesseY
        Sortie:
        Description: Constructeur surcharge, definie les caracteristiques de l'ennemi
    */
    Ennemi(int id,int vie,int ydepart,int pointCadence,int vitesseX,int vitesseY);

    //! bouger
    /*!
        Entrée:
        Sortie:
        Description: permet de géré le déplacement de l'ennemi
    */
    virtual void bouger();


    //! setPointCadence
    /*!
        Entrée:
        Sortie:
        Description: permet de definir la cadence de tire
    */
    void setPointCadence(const int x);

    //! setVitesseX
    /*!
        Entrée:
        Sortie:
        Description: permet de definir la vitesse en X
    */
    void setVitesseX(const int x);

    //! setVitesseY
    /*!
        Entrée:
        Sortie:
        Description: permet de definir la vitesse en Y
    */
    void setVitesseY(const int x);

    //! getPointCadence
    /*!
        Entrée:
        Sortie:
        Description: permet de recupere la valeur de cadance des tirs
    */
    int getPointCadence()const;

    //! getVitesseX
    /*!
        Entrée:
        Sortie:
        Description: permet de recupere la vitesse de déplacement en X
    */
    */
    int getVitesseX()const;

    //! getVitesseY
    /*!
        Entrée:
        Sortie:
        Description: permet de recupere la vitesse de déplacement en Y
    */
    int getVitesseY()const;
private:
    int m_pointCadence;
    int m_vitesseX;
    int m_vitesseY;


};

#endif
