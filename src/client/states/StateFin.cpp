#include "include/client/states/StateFin.hpp"

StateFin::StateFin(sf::TcpSocket * socketTCP, sf::UdpSocket * socketUDP)
{
    m_tcpSocket = socketTCP;
    m_udpSocket = socketUDP;

}
StateFin::~StateFin()
{

}

void StateFin::liberer()
{
    /*
     if(m_socketServeur != nullptr){
        m_socketServeur->disconnect();
        delete m_socketServeur;
        m_socketServeur = nullptr;
    }
    */
}

void StateFin::initialise()
{
    m_font.loadFromFile("Ressources/8bitoperator.ttf");

    m_textBoard.setFont(m_font);
    m_textBoard.setCharacterSize(24);
    m_textBoard.setString("FIN DE JEU");
    m_textBoard.setPosition(248, 27);
    BoardSingleton::get()->setCenterText(m_textBoard);

    sf::Packet p;
    sf::Packet reponse;
    m_socketServeur->receive(reponse);
    unsigned short header;
    reponse >> header;

    p << SCORETCP << BoardSingleton::get()->getScore() << m_tcpSocket->getLocalPort();
    m_socketServeur->send(p);

    if(header == SCORETCP){
        reponse >> classement;
    }

    pugi::xml_document doc;
    std :: ifstream  flux ("weekly-utf-8.xml");
    pugi :: xml_parse_result  resultat=doc.load(classement.c_str());

//!OBTENIR UNE VALEUR D'ATTRIBUT :
//var = monNoeud.attribute("nomAttribut").value();

//! ON CHECK TOUS LES "joueur" DE DOC
int i = 0;
for (pugi::xml_node tool = doc.child("joueur"); tool; tool = tool.next_sibling("joueur")){
    //On check tous les enfants "id"
    for (pugi::xml_node tool2 = doc.child("id"); tool2; tool2 = tool2.next_sibling("id")){
            id = tool2.value();
    }

    //On check tous les enfants "score"
    for (pugi::xml_node tool3 = doc.child("score"); tool3; tool3 = tool3.next_sibling("score")){
            score = tool3.value();
    }

    sf::Text t;
    t.setFont(m_font);
    t.setCharacterSize(14);
    t.setString("joueur "+id+" : "+ score);
    t.setPosition(111, 196 + 30*i);
    m_afficher.push_back(t);
    i++;
}
//!ON CHECK TOUS LES ENFANTS ScoreTeam DE DOC
for (pugi::xml_node tool = doc.child("ScoreTeam"); tool; tool = tool.next_sibling("ScoreTeam")){
            ScoreTeam = tool.value();
            sf::Text t;
            t.setFont(m_font);
            t.setCharacterSize(14);
            t.setString("Score de l'équipe : "+ScoreTeam);
            t.setPosition(111, 316);
            m_afficher.push_back(t);
            i++;
    }

}


void StateFin::dessiner(sf::RenderWindow &w)
{
    w.draw(m_boardSprite);
    for (auto t:m_afficher)
    {
        w.draw(t);
    }

}
/* Gérer les événements */
void StateFin::controler(const sf::Event &e)
{

}

void StateFin::mecanique()
{

}
