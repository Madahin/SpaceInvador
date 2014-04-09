#include "include/client/states/StateAttente.hpp"

StateAttente::StateAttente(sf::TcpSocket *socket) :
    m_socketServeur(socket),
    m_socketUDP(nullptr),
    m_state(0),
    m_threadTCP(nullptr)
{
    m_texVaisseau.loadFromFile("Ressources/vaisseaux.png");
    m_textTir.loadFromFile("Ressources/tir.png");
}
StateAttente::~StateAttente()
{
    while(!m_listeJoueur.empty())delete m_listeJoueur.back(), m_listeJoueur.pop_back();
}

void StateAttente::liberer()
{
    m_threadTCP->terminate();
    if(m_socketServeur != nullptr){
        m_socketServeur->disconnect();
        delete m_socketServeur;
        m_socketServeur = nullptr;
    }
}

void StateAttente::initialise()
{
    m_font.loadFromFile("Ressources/8bitoperator.ttf");

    m_textBoard.setFont(m_font);
    m_textBoard.setCharacterSize(24);
    m_textBoard.setString("PATIENTEZ");
    m_textBoard.setPosition(248, 27);
    BoardSingleton::get()->setCenterText(m_textBoard);

    m_socketUDP = new sf::UdpSocket;
    m_socketUDP->bind(sf::Socket::AnyPort);
    m_socketUDP->setBlocking(false);

    sf::Packet p;
    p << CONNECUDP << BoardSingleton::get()->getIdJoueur() << m_socketUDP->getLocalPort();
    unsigned short header;
    do
    {
        m_socketServeur->send(p);
        sf::Packet reponse;
        m_socketServeur->receive(reponse);
        reponse >> header;
        if(header == CONNECUDP){
            unsigned short port;
            reponse >> port;
            BoardSingleton::get()->setPortUDP(port);
        }
    }while(header != CONNECUDP);

    m_threadTCP = new sf::Thread(&StateAttente::gereTCP, this);
    m_threadUDP = new sf::Thread(&StateAttente::gereUDP, this);

    m_threadTCP->launch();
    m_threadUDP->launch();
}

void StateAttente::dessiner(sf::RenderWindow &w)
{
    for(auto e : m_listeEntite){
        w.draw(*e);
    }
    for(auto j : m_listeJoueur){
        w.draw(*j);
    }
}

void StateAttente::controler(const sf::Event &e)
{

}

void StateAttente::mecanique()
{
    if(!m_listePaquet.empty())traitePaquet();

    for(Joueur* j : m_listeJoueur)
    {
        if(j->getInvu())
        {
            if(j->timer.getElapsedTime().asMilliseconds() % 200 == 0)
            {
                if(j->getColor() != sf::Color::White){
                    j->oldColor = j->getColor();
                    j->setColor(sf::Color::White);
                }else{
                    j->setColor(j->oldColor);
                }
            }
            if(j->timer.getElapsedTime().asSeconds() > 3.f){
                j->setInvu(false);
            }
        }
    }

    for(auto e : m_listeEntite){
        e->bouger();
    }

    if(m_state == 1){
        if(BoardSingleton::get()->getPortUDP() != 0){
            m_threadTCP->wait();
            m_threadUDP->wait();
            m_manager->pushState(new StateEnJeu(m_socketServeur, m_socketUDP));
        }else{
            //m_manager->popState();
        }
    }
}

void StateAttente::traitePaquet()
{
    do
    {
        sf::Uint16 paquet = m_listePaquet.back();
        sf::Uint16 header = paquet & 0b1100000000000000;
        header >>=14;
        sf::Uint16 id = paquet & 0b0011110000000000;
        id >>= 10;
        sf::Uint16 data = paquet & 0b0000001111111111;
        Joueur* j = static_cast<Joueur*>(trouveEntiterParId<Joueur*>(m_listeJoueur, id));
        if(j == nullptr){
            j = new Joueur(id);
            j->setTexture(m_texVaisseau);
            j->setTextureRect(sf::IntRect((id)*37,0,37,41));
            m_listeJoueur.push_back(j);
            m_listeEntite.push_back(j);
        }

        switch(header)
        {
            case UDP_SC_SETX:
            {
                j->setPosition(data, j->getPosition().y);
                break;
            }
            case UDP_SC_SETY:
            {
                j->setPosition(j->getPosition().x, data);
                break;
            }
            case UDP_SC_TIR:
            {
                Joueur tmp = (*(j));
                Tir * t = new Tir(((paquet & 0b0000001111100000) >> 5), tmp);
                t->setTexture(m_textTir);
                m_listeEntite.push_back(t);
                break;
            }
            case UDP_SC_INVULNERABLE:
            {
                j->setInvu(true);
                j->timer.restart();
                break;
            }
        }
        m_listePaquet.pop_back();
    }while(!m_listePaquet.empty());
}

void StateAttente::gereTCP()
{
    while(m_state == 0)
    {
        sf::Packet p;
        sf::Socket::Status stat = m_socketServeur->receive(p);
        switch(stat)
        {
            case sf::Socket::Done:
            {
                unsigned short header;
                p >> header;
                switch(header)
                {
                    case LAUNCHGAME:
                    {
                        m_state = 1;
                        p << header;
                        m_socketServeur->send(p);
                        break;
                    }
                    case JOUEURDECO:
                    {
                        int id;
                        p >> id;
                        bool ok = false;
                        for(unsigned int i=0 ; (!ok) && i < m_listeJoueur.size() ; i++){
                            if(id == m_listeJoueur[i]->getId()){
                                delete m_listeJoueur[i];
                                m_listeJoueur.erase(m_listeJoueur.begin() + i);
                                ok = true;
                            }
                        }
                        break;
                    }
                }
                break;
            }
            case sf::Socket::NotReady:
            {
                // Rien de recu
                break;
            }
            case sf::Socket::Disconnected:
            {
                BoardSingleton::get()->setStatePop(2);
                break;
            }
            case sf::Socket::Error:
            {
                // Erreur lors de la reception
                break;
            }
        }
    }
}

void StateAttente::gereUDP()
{
    while(m_state == 0)
    {
        sf::Uint16 paquet;
        std::size_t receive;
        sf::IpAddress adresse = m_socketServeur->getRemoteAddress();
        unsigned short port = BoardSingleton::get()->getPortUDP();
        sf::Socket::Status stat = m_socketUDP->receive((void*)&paquet, sizeof(paquet), receive, adresse, port);
        switch(stat)
        {
            case sf::Socket::Done:
            {
                m_listePaquet.push_back(paquet);
                break;
            }
            case sf::Socket::NotReady:
            {
                // Rien de recu
                break;
            }
            case sf::Socket::Disconnected:
            {
                break;
            }
            case sf::Socket::Error:
            {
                // Erreur lors de la reception
                break;
            }
        }
    }
}
