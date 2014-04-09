#ifndef ARRIEREPLAN
#define ARRIEREPLAN

#include <vector>
#include <sstream>
#include <random>
#include <chrono>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "include/client/decor.hpp"

#define NBDECOR 5

class ArrierePlan
{
public:
    //! ArrierePlan
    /*!
        Entrée:
        Sortie:
        Description: constructeur
    */
    ArrierePlan();

    //! ~ArrierePlan
    /*!
        Entrée:
        Sortie:
        Description: destructeur, remet le thread a null
    */
    ~ArrierePlan();

    //! dessiner
    /*!
        Entrée: RenderWindow &w
        Sortie:
        Description: Afficher l'arriere plan
    */
    void dessiner(sf::RenderWindow &w);

    //! ajustFPS
    /*!
        Entrée: float fps
        Sortie:
        Description: Ajuste les FPS
    */
    void ajustFPS(float fps);

    //! addSprite
    /*!
        Entrée:
        Sortie:
        Description:  - Ajouter des elements a l'arriere plan;
                      - Depends de m_nbElemsMax.
    */
    private: void addSprite();

    //! moveSprite
    /*!
        Entrée:
        Sortie:
        Description:  - Fait avancer le decor;
                      - Recharge les elements sortant de l'ecran.
    */
    void moveSprite();

    //! cleanSprite
    /*!
        Entrée:
        Sortie:
        Description: Effacer les elements sortant de l'ecran.
    */
    void cleanSprite();

   //! modifElemMax
    /*!
        Entrée: int delta
        Sortie:
        Description: adapte les elements d'arriere plans au performance de l'ordinateur.
    */
    void modifElemMax(int delta);

    int m_nbElemMax;
    sf::Thread * m_thread;
    std::uniform_int_distribution<int> m_rand;
    std::vector<sf::Texture> m_vecTex;
    std::vector<decor> m_vecDec;
    sf::Mutex m_mutex;
    sf::Mutex m_mutexRand;
    std::default_random_engine m_generator;
};

#endif
