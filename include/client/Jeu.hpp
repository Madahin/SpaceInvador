#ifndef JEU
#define JEU

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include "include/client/arrierePlan.hpp"
#include "include/client/GameStateManager.hpp"
#include "include/client/states/StateAcceuil.hpp"
#include "include/client/BoardSingleton.hpp"

class Jeu
{
public:
    //! Constructeur de jeu
    /*!
      Entree :
      Sortie :
      Description :
    */
    Jeu();
    //! Destructeur de jeu
    /*!
      Entree :
      Sortie :
      Description :
    */
    ~Jeu();

    //! Boucle principale du jeu
    /*!
      Entree :
      Sortie :
      Description :
    */
    void jouer();

private:
    bool m_quitter;
    sf::Thread * m_threadTCP;
    sf::Thread * m_threadUDP;
    ArrierePlan * m_arrierePlan;
    sf::Image * m_icon;
    sf::UdpSocket m_socketUDP;
    sf::TcpSocket m_socketTCP;
    sf::TcpListener m_listenerTCP;
    sf::RenderWindow m_w;
    GameStateManager m_manager;
};

#endif
