#ifndef STATE
#define STATE

#include "include/config.hpp"
#include "include/client/BoardSingleton.hpp"
#include "include/client/GameStateManager.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

class GameStateManager;

class State
{
public:
    //!State
    /*!
        Entrée:
        Sortie:
        Description: Constructeur
    */
    State();

    //!~State
    /*!
        Entrée:
        Sortie:
        Description: mess m_manager = null;
    */
    virtual ~State();

    virtual void liberer() = 0;
    virtual void initialise() = 0;
    virtual void dessiner(sf::RenderWindow &w) = 0;
    virtual void controler(const sf::Event &e) = 0;
    virtual void mecanique() = 0;

    //!setManager
    /*!
        Entrée: GameStateManager * manager
        Sortie:
        Description: garde référence pour la pile de State
    */
    void setManager(GameStateManager * manager);

protected:
    GameStateManager * m_manager;
    sf::UdpSocket * m_udpSocket;
    sf::TcpSocket * m_tcpSocket;
};

#endif
