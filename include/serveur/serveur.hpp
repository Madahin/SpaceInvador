#ifndef SERVEUR
#define SERVEUR

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include "include/config.hpp"
#include "include/serveur/Joueur.hpp"
#include "include/serveur/SocketTCPj.hpp"
#include "include/serveur/fonctionXML.hpp"
#include <random>
#include <chrono>
#include "include/pugixml.hpp"
#include "ennemi.hpp"

#include <bitset>

class Ennemi;
class Serveur
{
public:
    //! Constructeur de serveur
    /*!
      Entree :
      Sortie :
      Description : cree le serveur
    */
    Serveur();
    //! Destructeur de serveur
    /*!
      Entree :
      Sortie :
      Description :
    */
    ~Serveur();

    //! Lancer le serveur
    /*!
      Entree :
      Sortie :
      Description : lance le serveur et effectue les commandes jusqu'a recevoir "exit"
    */
    void lancer();
    //! Gerer les connections TCP
    /*!
      Entree :
      Sortie :
      Description : attendre des connexions et cree des sockets
    */
    void gereConnexionTCP();
    //! Gerer les protocoles TCP
    /*!
      Entree :
      Sortie :
      Description : Recevoir et envoyer des protocoles TCP
    */
    void gereTCP();
    //! Gerer les protocoles UDP
    /*!
      Entree :
      Sortie :
      Description : Recevoir et envoyer des protocoles UDP
    */
    void gereUDP();
    //! Gerer le lancement de partie
    /*!
      Entree :
      Sortie :
      Description : Lance la partie si au moins un joueur est connecte,
                    Envoie les informations sur les ennemis aux joueurs
                    Previens les joueurs du debut de la partie
    */
    void gereLancementPartie();


    //! Getter vitesseEnnemis
    /*!
      Entree :
      Sortie : float
      Description : retourne la vitesse des ennemis
    */
    float getVitesseEnnemis()const;
    //! Getter vieEnnemis
    /*!
      Entree :
      Sortie : unsigned int
      Description : retourne la vie maximale des ennemis
    */
    unsigned int getVieEnnemis()const;
    //! Getter cadenceEnnemis
    /*!
      Entree :
      Sortie : unsigned int
      Description : retourne le temps de cadence de tir des ennemis
    */
    unsigned int getCadenceEnnemis()const;
    //! ameliorer les ennemis
    /*!
      Entree :
      Sortie :
      Description : ameliorer aleatoirement une des carracteristiques des ennemis
    */
    void ameliorerEnnemis();
    //! convertir un entier en string
    /*!
      Entree : int
      Sortie :
      Description :
    */
    std::string inToString(int x);

    //! Sortir toutes les informations du serveur
    /*!
      Entree :
      Sortie :
      Description : methode de debuggage (mouchard)
    */
    void info();
private:
    bool m_estActif;
    bool m_isTCPLancer;
    bool m_isUDPLancer;

    bool m_partieLancer;

    sf::Thread * m_threadGereConnexionTCP;
    sf::Thread * m_threadGereTCP;
    sf::Thread * m_threadGereUDP;
    sf::Thread * m_threadGereLancementPartie;
    sf::TcpListener m_listener;
    std::vector<SocketTCPj*> m_socketTCPVec;
    std::vector<Joueur*> m_joueurVec;
    std::vector<unsigned int> m_placeLibre;
    sf::UdpSocket m_socketUDP;
    sf::Clock m_attentePartie;
    pugi::xml_document xml_score;


    float m_vitesseEnnemis;
    unsigned int m_vieEnnemis;
    unsigned int m_cadenceEnnemis;
    int m_scoreTeam;
    pugi::xml_document m_FichierScore;

};

#endif
