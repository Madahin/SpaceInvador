#include "include/client/BoardSingleton.hpp"

BoardSingleton::BoardSingleton() :
    m_idJoueur(1),
    m_nbVie(NBVIE),
    m_montrerPanG(false),
    m_montrerPanD(false),
    m_statePop(0)
{
    m_font.loadFromFile("Ressources/8bitoperator.ttf");

    m_boardTex.loadFromFile("Ressources/board.png");
    m_boardTex.setSmooth(true);
    m_boardSprite.setTexture(m_boardTex);
    m_boardSprite.setPosition(2.5, 8.5);

    m_coeurTex.loadFromFile("Ressources/board_coeur.png");
    m_coeurSprite.setTexture(m_coeurTex);
    m_coeurSprite.setPosition(8, 24);

    m_textVie.setFont(m_font);
    m_textVie.setPosition(55, 27);
    m_textVie.setCharacterSize(24);
    m_textVie.setString("X");

    m_textCentre.setFont(m_font);

    m_textTemps.setFont(m_font);
    m_textTemps.setPosition(566, 22);
    m_textTemps.setCharacterSize(12);

    setColor(sf::Color(37, 196, 31));
}

BoardSingleton::~BoardSingleton()
{

}

BoardSingleton * BoardSingleton::get()
{
    if(m_instance == nullptr){
        m_instance = new BoardSingleton;
    }
    return m_instance;
}

void BoardSingleton::setNbVie(int nbVie)
{
    m_nbVie = nbVie;
}

void BoardSingleton::setTemps(int seconde)
{

}

void BoardSingleton::montrePanneauGauche(bool b)
{
    m_montrerPanG = b;
}

void BoardSingleton::montrePanneauDroit(bool b)
{
    m_montrerPanD = b;
}

void BoardSingleton::setCenterText(sf::Text &t)
{
    m_textCentre = t;
    setColor(m_idJoueur);
}

void BoardSingleton::setColor(const sf::Color &c)
{
    m_boardSprite.setColor(c);
    m_coeurSprite.setColor(c);
    m_textVie.setColor(c);
    m_textCentre.setColor(c);
    m_textTemps.setColor(c);
}

void BoardSingleton::setColor(const int c)
{
    m_idJoueur = c;
    switch (c) {
        case 1: // VERT
        {
            setColor(sf::Color(37, 196, 31));
            break;
        }
        case 2: // ROUGE
        {
            setColor(sf::Color(249, 3, 16));
            break;
        }
        case 3: // BLEU
        {
            setColor(sf::Color(37, 196, 189));
            break;
        }
        case 4: // JAUNE
        {
            setColor(sf::Color(240, 196, 31));
            break;
        }
        default:
            break;
    }
}

void BoardSingleton::setStatePop(int n)
{
    m_statePop = n;
}

int BoardSingleton::getIdJoueur()
{
    return m_idJoueur;
}

void BoardSingleton::draw(sf::RenderWindow &w)
{
    w.draw(m_boardSprite);
    if(m_montrerPanG){
        w.draw(m_coeurSprite);
        w.draw(m_textVie);
    }
    if(m_montrerPanD){
        w.draw(m_textTemps);
    }
    w.draw(m_textCentre);
}

void BoardSingleton::kill()
{
    if(m_instance != nullptr){
        delete m_instance;
        m_instance = nullptr;
    }
}

int BoardSingleton::getScore()
{
    return 0;
}

unsigned short BoardSingleton::getPortUDP()
{
    return m_portUDP;
}

int BoardSingleton::getStatePop()
{
    return m_statePop;
}

void BoardSingleton::setPortUDP(unsigned short p)
{
    m_portUDP = p;
}


BoardSingleton* BoardSingleton::m_instance = nullptr;
