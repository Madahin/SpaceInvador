#ifndef STATEACCEUIL
#define STATEACCEUIL

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include "include/client/states/State.hpp"
#include "include/client/states/StateAttente.hpp"

class StateAcceuil : public State
{
public:

    //!StateAcceuil
    /*!
        Entrée :
        Sortie:
        Description: constructeur
    */
    StateAcceuil();

    //!~StateAcceuil
    /*!
        Entrée :
        Sortie:
        Description : destructeur, vide.
    */
    virtual ~StateAcceuil();

    //!liberer
    /*!
        Entrée :
        Sortie:
        Description: Code pour vider le socket
    */
    virtual void liberer();

    //!initialise
    /*!
        Entrée :
        Sortie:
        Description :   - initialise un nouveau Socket
                        - initialise les elements graphiques
    */
    virtual void initialise();

    //!dessiner
    /*!
        Entrée : RenderWindow &w
        Sortie:
        Description : Affiche les elements graphique
    */
    virtual void dessiner(sf::RenderWindow &w);

    //!controler
    /*!
        Entrée : Event &e
        Sortie:
        Description:  - Controle de saisie de l'adresse ip
                      - verifie si une partie est déjà lancer
    */
    virtual void controler(const sf::Event &e);

    //!mecanique
    /*!
        Entrée :
        Sortie:
        Description : affiche les messages en fonction de l'etat de connection
    */
    virtual void mecanique();

     //!verifConnection
    /*!
        Entrée :
        Sortie:
        Description : vérifie la connection au serveur
    */
    void verifConnection();

private:
    bool m_isThreadActive;
    short m_error_code;

    sf::Font m_font;

    sf::RectangleShape m_IPField;

    sf::Text m_titre;
    sf::Text m_textIP;
    sf::Text m_IPFieldText;
    sf::Text m_etatConnection;

    std::string m_ip;

    sf::TcpSocket * m_socket;
    sf::Thread * m_threadTCP;
};

#endif
