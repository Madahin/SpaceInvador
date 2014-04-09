#ifndef STATEENJEU
#define STATEENJEU

#ifdef DEBUG
#include <iostream>
#include <bitset>
#endif

#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <vector>
#include "include/client/states/State.hpp"
#include "include/client/joueur.hpp"
#include "include/client/tir.hpp"
#include "include/client/BoardSingleton.hpp"
#include "include/fonctionsUtiles.hpp"
#include <SFML/Network.hpp>
#include "include/pugixml.hpp"

#define VITJ 5

class StateEnJeu : public State
{
public:

    //!StateEnJeu
    /*!
        Entrée:TcpSocket * socketTCP, UdpSocket * socketUDP
        Sortie:
        Description: Constructeur
    */
    StateEnJeu(sf::TcpSocket * socketTCP, sf::UdpSocket * socketUDP);

    //!~StateEnJeu
    /*!
        Entrée:
        Sortie:
        Description: Destructeur
    */
    virtual ~StateEnJeu();

     //!libere
    /*!
        Entrée:
        Sortie:
        Description: detruit le thread TCP et UDP
    */
    virtual void liberer();

     //!initialise
    /*!
        Entrée:
        Sortie:
        Description: permet d'initialiser les elements du State
    */
    virtual void initialise();

     //!dessiner
    /*!
        Entrée: RenderWindow &w
        Sortie:
        Description: Affiche les éléments graphique
    */
    virtual void dessiner(sf::RenderWindow &w);

    //!controler
    /*!
        Entrée:Event &e
        Sortie:
        Description: gere la gestion des evenements neccessaire au jeux (gestion du clavier...)
    */
    virtual void controler(const sf::Event &e);

    //!mecanique
    /*!
        Entrée:
        Sortie:
        Description: gere la mecanique du panneau, le jeu .....
    */
    virtual void mecanique();

    //!tirer
    /*!
        Entrée:
        Sortie:
        Description: gere les tires
    */
    void tirer();

    //!traitePaquet
    /*!
        Entrée:
        Sortie:
        Description: decripte les bit envoye par le protocol UDP
    */
    void traitePaquet();
    /* Ajouter si il faut des joueurs dont on recoit des donnees */

    //!gerer_udp
    /*!
        Entrée:
        Sortie:
        Description: gere l'envoie et la reception de protocol UDP
    */
    void gerer_udp();

    //!gerer_tcp
    /*!
        Entrée:
        Sortie:
        Description: gere l'envoie et la reception de protocol TCP
    */
    void gerer_tcp();

    //!traiteCollision
    /*!
        Entrée:
        Sortie:
        Description: s'occupe de la gestion des collisions entre les joueurs et les ennemis
    */
    void traiteCollision();

     //!getPaquetSetX
    /*!
        Entrée:
        Sortie:
        Description: permet de récupere la position X
    */
    sf::Uint16 getPaquetSetX();

     //!getPaquetSetY
    /*!
        Entrée:
        Sortie:
        Description: permet de récupere la position Y
    */
    sf::Uint16 getPaquetSetY();

     //!getPaquetTir
    /*!
        Entrée: Uint16 id
        Sortie:
        Description: permet de récupere les données du tir
    */
    sf::Uint16 getPaquetTir(sf::Uint16 id);

    //!lireXML_ennemi
    /*!
        Entrée: std::string &xml
        Sortie:
        Description: permet de parser le fichier xml pour récupere les données sur les ennemis
    */
    void lireXML_ennemi(const std::string &xml);

private:
    sf::Font m_font;
    sf::Text m_textBoard;
    sf::Texture m_textJoueurs;
    sf::Texture m_textTir;
    sf::Texture m_textEnnemie;
    std::vector <Entite*> m_liste_mes_entites;
    std::vector <Entite*> m_liste_autres_entites;
    std::vector<sf::Uint16> m_listePaquet;

    sf::Thread * m_threadTCP;
    sf::Thread * m_threadUDP;

    bool m_gauche;
    bool m_droit;
    bool m_haut;
    bool m_bas;
    /* Un booleen qui dit 'on va tirer' */
    bool m_tirer;

    int m_state;

    int m_cadenceTir_ennemis;

    //!trouverIdTir
    /*!
        Entrée: <Entite *> v
        Sortie:
        Description: permet de récuperer l'id du tire
    */
    unsigned int trouverIdTir(std::vector <Entite *> v);

};

#endif
