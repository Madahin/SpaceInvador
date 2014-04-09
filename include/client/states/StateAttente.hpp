#ifndef STATEATTENTE
#define STATEATTENTE

#ifdef DEBUG
#include <iostream>
#include <bitset>
#endif

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "include/client/states/State.hpp"
#include "include/client/states/StateEnJeu.hpp"
#include "include/client/BoardSingleton.hpp"
#include "include/fonctionsUtiles.hpp"

class StateAttente : public State
{
public:
    //!StateAttente
    /*!
        Entrée : TcpSocket * socket
        Sortie:
        Description: constructeur, instancie les variables
    */
    StateAttente(sf::TcpSocket * socket);

    //!~StateAttente
    /*!
        Entrée :
        Sortie:
        Description : destructeur du panneau, Supprime les joueurs
    */
    virtual ~StateAttente();

    //!liberer
    /*!
        Entrée :
        Sortie:
        Description: destructeur, Code pour vider le socket
    */
    virtual void liberer();

    //!initialise
    /*!
        Entrée :
        Sortie:
        Description: initialise le panneau:
            - l'affichage des textes
            - recois les données du serveur sur les autres joueurs
    */
    virtual void initialise();

    //!dessiner
    /*!
        Entrée : RenderWindow &w
        Sortie:
        Description: Affiche les element (textes....)
    */
    virtual void dessiner(sf::RenderWindow &w);

     //!controler
    /*!
        Entrée : Event &e
        Sortie:
        Description: recupere  les evenement, aucun evenement est gere dans ce panneau.
    */
    virtual void controler(const sf::Event &e);

    //!mecanique
    /*!
        Entrée :
        Sortie:
        Description: mecanique du jeu
    */
    virtual void mecanique();

    //!traitePaquet
    /*!
        Entrée :
        Sortie:
        Description: decripte les bit envoye par le protocol UDP
    */
    void traitePaquet();

    //!gereTCP
    /*!
        Entrée :
        Sortie:
        Description: gere l'envoie et la reception de protocol TCP
    */
    void gereTCP();

    //!gereUDP
    /*!
        Entrée :
        Sortie:
        Description: gere l'envoie et la reception de protocol UDP
    */
    void gereUDP();

private:
    sf::TcpSocket * m_socketServeur;
    sf::UdpSocket * m_socketUDP;
    sf::Font m_font;
    sf::Text m_textBoard;
    std::vector<Joueur*> m_listeJoueur;
    std::vector<Entite*> m_listeEntite;
    std::vector<sf::Uint16> m_listePaquet;

    int m_state;

    sf::Thread * m_threadTCP;
    sf::Thread * m_threadUDP;

    sf::Texture m_texVaisseau;
    sf::Texture m_textTir;
};

#endif
