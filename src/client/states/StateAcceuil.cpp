#include "include/client/states/StateAcceuil.hpp"

sf::Mutex mutex;

StateAcceuil::StateAcceuil()
{

}
StateAcceuil::~StateAcceuil()
{
}

void StateAcceuil::verifConnection()
{
    m_isThreadActive = true;
    mutex.lock();
    m_error_code = 1;
    mutex.unlock();
    sf::Socket::Status status = m_socket->connect(sf::IpAddress(m_ip), 42442, sf::seconds(5));
    if(status != sf::Socket::Done) // Si il y a une erreur de connexion
    {
        mutex.lock();
        m_error_code = 2;
        mutex.unlock();
    }else{
        m_error_code = 5;
        int i = -1;
        sf::Packet p;
        // Le serveur nous dit si il est plein ou nous envois notre position
        m_socket->receive(p);
        p >> i;
        if(i != 0){ // Le serveur nous donne notre position
            mutex.lock();
            BoardSingleton::get()->setColor(i);
            m_error_code = 3;
            mutex.unlock();
        }else{ // Le serveur est plein
            mutex.lock();
            m_error_code = 4;
            mutex.unlock();}
    }

    m_isThreadActive = false;
}

void StateAcceuil::liberer()
{
    if(m_socket != nullptr){
        m_socket->disconnect();
        delete m_socket;
        m_socket = nullptr;
    }
    m_threadTCP->terminate();
    if(m_threadTCP != nullptr){
        delete m_threadTCP;
        m_threadTCP = nullptr;
    }
}

void StateAcceuil::initialise()
{
    m_error_code = 0;
    m_socket = new sf::TcpSocket;
    m_isThreadActive = false;
    m_threadTCP = new sf::Thread(&StateAcceuil::verifConnection, this);
    m_font.loadFromFile("Ressources/8bitoperator.ttf");

    m_titre.setFont(m_font);
    m_titre.setPosition(125, 25);
    m_titre.setCharacterSize(23.25);
    m_titre.setColor(sf::Color(37, 196, 31));
    m_titre.setString("PRESS SPACE TO JOIN GAME");

    BoardSingleton::get()->setCenterText(m_titre);

    m_textIP.setFont(m_font);
    m_textIP.setPosition(150, 223);
    m_textIP.setCharacterSize(30);
    m_textIP.setColor(sf::Color::Black);

    m_IPFieldText.setFont(m_font);
    m_IPFieldText.setPosition(238, 187);
    m_IPFieldText.setCharacterSize(23);
    m_IPFieldText.setColor(sf::Color(37, 196, 31));
    m_IPFieldText.setString("Adresse IP");

    m_etatConnection.setFont(m_font);
    m_etatConnection.setPosition(150, 270);
    m_etatConnection.setCharacterSize(23);
    m_etatConnection.setColor(sf::Color(37, 196, 31));

    m_IPField.setFillColor(sf::Color::White);
    m_IPField.setSize(sf::Vector2f(338, 46));
    m_IPField.setPosition(150,223);
}

void StateAcceuil::dessiner(sf::RenderWindow &w)
{

    w.draw(m_IPFieldText);
    w.draw(m_IPField);
    w.draw(m_textIP);
    w.draw(m_etatConnection);
}

/* Gérer les évènements */
void StateAcceuil::controler(const sf::Event &e)
{
    switch (e.type) {
        case sf::Event::TextEntered:
        {
            char c = static_cast<char>(e.text.unicode);
            if(c == 8){
                if(m_ip.size() > 0)m_ip.pop_back();
            }else if(m_ip.size() < 15 && ((c >= 48 && c <= 57) || c == 46)){
                m_ip.push_back(c);
            }
            m_textIP.setString(m_ip);
            break;
        }
        case sf::Event::KeyReleased:
        {
            if(e.key.code == sf::Keyboard::Space)
            {
                if(!m_isThreadActive){
                    m_threadTCP->launch();
                    m_isThreadActive = true;
                }
            }
            break;
        }
        default:
            break;
    }
}

void StateAcceuil::mecanique()
{
    mutex.lock();
    switch(m_error_code)
    {
        case 0:
        {
            m_etatConnection.setString("");
            break;
        }
        case 1:
        {
            m_etatConnection.setString("Connection...");
            break;
        }
        case 2:
        {
            m_etatConnection.setString("Erreur de connexion");
            break;
        }
        case 3:
        {
            m_etatConnection.setString("Connecter");
            m_threadTCP->wait();
            m_manager->pushState(new StateAttente(m_socket));
            m_socket = nullptr;
            m_error_code = 0;
            break;
        }
        case 4:
        {
            m_etatConnection.setString("Serveur plein");
            break;
        }
        case 5:
        {
            m_etatConnection.setString("En attente du serveur");
        }
    }
    mutex.unlock();
}
