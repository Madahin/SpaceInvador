#include "include/client/Jeu.hpp"
#include <iostream>

Jeu::Jeu() :
    m_quitter(false),
    m_threadTCP(nullptr),
    m_threadUDP(nullptr),
    m_arrierePlan(nullptr),
    m_icon(nullptr)
{
    m_arrierePlan = new ArrierePlan;
    m_manager.pushState(new StateAcceuil);

    m_icon = new sf::Image;
    m_icon->loadFromFile("Ressources/logo.png");

    m_w.setFramerateLimit(60);
}

Jeu::~Jeu()
{
    if(m_threadTCP != nullptr){
        delete m_threadTCP;
        m_threadTCP = nullptr;
    }
    if(m_threadUDP != nullptr){
        delete m_threadUDP;
        m_threadUDP = nullptr;
    }
    if(m_arrierePlan != nullptr){
        delete m_arrierePlan;
        m_arrierePlan = nullptr;
    }
    if(m_icon != nullptr){
        delete m_icon;
        m_icon = nullptr;
    }
}

void Jeu::jouer()
{
    m_w.create(sf::VideoMode(640,480,32), "Space invader");
#ifndef WINFOIREU
    m_w.setIcon(35,35,m_icon->getPixelsPtr());
#endif

    sf::Clock mecaniqueFrame;
    //sf::Clock clock;

    BoardSingleton * board = BoardSingleton::get();

    mecaniqueFrame.restart();
    while(!m_quitter)
    {
        sf::Event e;
        while(m_w.pollEvent(e))
        {
            if(e.type == sf::Event::Closed){
                m_w.close();
                m_quitter = true;
            }
            m_manager.getEtat()->controler(e);
        }
        m_w.clear();
        m_arrierePlan->dessiner(m_w);
        board->draw(m_w);
        m_manager.getEtat()->dessiner(m_w);
        m_w.display();
        if(mecaniqueFrame.getElapsedTime() >= sf::seconds(1.f/45)){
            m_manager.getEtat()->mecanique();
            mecaniqueFrame.restart();
        }
        //sf::Time frameTime = clock.restart();
        //float f = 1/frameTime.asSeconds();
        //m_arrierePlan->ajustFPS(f);
        if(board->getStatePop() > 0){
            for(int i=board->getStatePop() ; i > 0 ; i--){
                m_manager.popState();
                board->setStatePop(i);
            }
            m_quitter = true;
        }
    }
    m_w.close();
}
