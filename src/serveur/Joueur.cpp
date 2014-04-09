#include "include/serveur/Joueur.hpp"

Joueur::Joueur(const unsigned short id, const std::string &ip, const unsigned short port) :
    m_id(id),
    m_adresse(ip),
    m_port(port),
    m_enJeu(false),
    m_initUDP(false),
    m_pv(3),
    m_socket(nullptr)
{
}

Joueur::~Joueur()
{
    if(m_socket != nullptr){
        delete m_socket;
        m_socket = nullptr;
    }
}

void Joueur::setEnJeu(bool j)
{
    m_enJeu = j;
}

void Joueur::setPV(int pv)
{
    m_pv = pv;
}

void Joueur::setSocket(sf::UdpSocket * socket)
{
    m_socket = socket;
}

bool Joueur::getEnJeu()
{
    return m_enJeu;
}

int Joueur::getPV()
{
    return m_pv;
}

unsigned short Joueur::getID() const
{
    return m_id;
}

std::string Joueur::getIpAdresse()
{
    return m_adresse;
}

unsigned short Joueur::getPort()
{
    return m_port;
}

sf::UdpSocket* Joueur::getSocket()
{
    return m_socket;
}

void Joueur::estToucher()
{
    m_timer.restart();
}

bool Joueur::isInvincible()
{
    bool rep = false;
    if(m_timer.getElapsedTime() < sf::seconds(3)){
        rep = true;
    }
    return rep;
}

bool Joueur::equals(const std::pair<std::string, unsigned short> &p)
{
    return ((m_adresse == p.first)&&(m_port == p.second));
}

void Joueur::setScore(int score)
{
    m_Score = score;
}

int Joueur::getScore()
{
    return m_Score;
}

void Joueur::setinitUDP(bool b)
{
    m_initUDP = b;
}

bool Joueur::isUDPInit()
{
    return m_initUDP;
}
