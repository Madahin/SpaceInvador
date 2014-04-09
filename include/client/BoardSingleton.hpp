#ifndef BOARDSINGLETON
#define BOARDSINGLETON

#include <SFML/Graphics.hpp>

#define NBVIE 3

class BoardSingleton
{
private:
    //! BoardSingleton
    /*!
        Entrée:
        Sortie:
        Description: constructeur
    */
    BoardSingleton();

    //! ~BoardSingleton
    /*!
        Entrée:
        Sortie:
        Description: destructeur
    */
    ~BoardSingleton();

public:
    //! BoardSingleton * get
    /*!
        Entrée:
        Sortie: m_instance
        Description: retourne BoardSingleton
    */
    static BoardSingleton * get();

    //!kill
    /*!
        Entrée:
        Sortie:
        Description: détruit l'instance de BoardSingleton
    */
    static void kill();

    //!kill
    /*!
        Entrée: int nbVie
        Sortie:
        Description: gestion du nombre de vie
    */
    void setNbVie(int nbVie);

    //!setTemps
    /*!
        Entrée: int seconde
        Sortie:
        Description: spécifier le temps
    */
    void setTemps(int seconde);

    //!montrePanneauGauche
    /*!
        Entrée: bool b
        Sortie:
        Description: gere l'affichage du panneau de gauche
    */
    void montrePanneauGauche(bool b);

    //!montrePanneauDroit
    /*!
        Entrée: bool b
        Sortie:
        Description: gere l'affichage du panneau de droite
    */
    void montrePanneauDroit(bool b);

    //!setCenterText
    /*!
        Entrée: Text &t
        Sortie:
        Description: gere l'affichage du panneau de droite
    */
    void setCenterText(sf::Text &t);

     //!setColor
    /*!
        Entrée: Color &c
        Sortie:
        Description: définie l'id du joueur avec sa couleur qui sera afficher de maniere centré
    */
    void setColor(const sf::Color &c);

    //!setColor
    /*!
        Entrée: int c
        Sortie:
        Description: gere la couleur du joueur
    */
    void setColor(const int c);

    //!setStatePop
    /*!
        Entrée: int n
        Sortie:
        Description: gere la couleur du joueur
    */
    void setStatePop(int n);

    //!getIdJoueur
    /*!
        Entrée: int n
        Sortie:
        Description: permet de recupere l'id du jouer
    */
    int getIdJoueur();

    //!draw
    /*!
        Entrée: RenderWindow &w
        Sortie:
        Description: gere l'affichage du temps et du nombre de vies
    */
    void draw(sf::RenderWindow &w);

       //!getStatePop
    /*!
        Entrée:
        Sortie:
        Description: permet de recupere le score du joueur
    */
    int getScore();

    //!getStatePop
    /*!
        Entrée:
        Sortie:
        Description: permet de recupere statePop
    */
    int getStatePop();


    //!getStatePop
    /*!
        Entrée:
        Sortie: m_statePop
        Description: permet de dépiler un etat, retire un State.
    */
    unsigned short getPortUDP();

    //!setPortUDP
    /*!
        Entrée: unsigned short p
        Sortie:
        Description: permet de definire le port UDP
    */
    void setPortUDP(unsigned short p);

private:
    unsigned short m_portUDP;
    int m_idJoueur;
    int m_nbVie;
    bool m_montrerPanG;
    bool m_montrerPanD;
    int m_statePop;
    sf::Font m_font;

    sf::Texture m_boardTex;
    sf::Texture m_coeurTex;

    sf::Sprite m_boardSprite;
    sf::Sprite m_coeurSprite;

    sf::Text m_textVie;
    sf::Text m_textCentre;
    sf::Text m_textTemps;

    static BoardSingleton * m_instance;

};

#endif
