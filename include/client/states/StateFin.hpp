#ifndef STATEFIN
#define STATEFIN

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "include/client/states/State.hpp"
#include "include/client/BoardSingleton.hpp"
#include "include/pugixml.hpp"
#include <fstream>
#include <iomanip>
#include <iostream>



class StateFin : public State
{
public:
    //!StateFin
    /*!
        Entrée : TcpSocket * socketTCP, sf::UdpSocket * socketUDP
        Sortie:
        Description: Constructeur, instancie les variables:
            - m_tcpSocket
            - m_udpSocket
    */
    StateFin(sf::TcpSocket * socketTCP, sf::UdpSocket * socketUDP);

    //! ~StateFin
    /*!
        Vide !
        Entrée :
        Sortie:
        Description: destructeur du panneau StateFin
    */
    virtual ~StateFin();

    //!liberer
    /*!
        Vide !
        Entrée :
        Sortie:
        Description: vide la memoire
    */
    virtual void liberer();

    //!initialise
    /*!
        Entrée :
        Sortie:
        Description : initialise le panneau, Initialise tout l'affichage du panneau :
            - l'affichage du GameOver;
            - envoi le score du jouer au serveur;
            - recupere le fichier XML (en String) envoyer par le serveur du classement des joueurs, leurs score et le scores de l'equipe;
            - initialise un document XML;
            - parse le fichier xml reçu;
            - initialise l'affichage du classement;
    */
    virtual void initialise();

    //!dessiner
    /*!
        Affiche le GameOver, le classement des joueurs, leurs scores et le score de l'équipe
        Entrée : RenderWindow &w
        Sortie:
        Description:  Affiche le texte
    */
    virtual void dessiner(sf::RenderWindow &w);

    //!controler
    /*!
        Entrée : Event &e
        Sortie:
        Description: recupere evenement
    */
    virtual void controler(const sf::Event &e);

    //!mecanique
    /*!
        Vide !
        Entrée :
        Sortie:
        Description: mecanique du jeu
    */
    virtual void mecanique();


private:
    sf::TcpSocket * m_socketServeur;
    sf::TcpSocket * m_tcpSocket;
    sf::UdpSocket * m_socketUDP;
    sf::Font m_font;
    sf::Texture m_boardTex;
    sf::Sprite m_boardSprite;
    sf::Text m_textBoard;
    std::string classement;
    pugi::xml_parse_result resultat;
    std::string id;
    std::string score;
    std::string ScoreTeam;
    std::vector<sf::Text> m_afficher;

};

#endif
