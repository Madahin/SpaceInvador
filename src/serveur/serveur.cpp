#include "include/serveur/serveur.hpp"

sf::Mutex mutex;

Serveur::Serveur() :
    m_estActif(true),
    m_isTCPLancer(false),
    m_isUDPLancer(false),
    m_threadGereConnexionTCP(nullptr),
    m_threadGereTCP(nullptr),
    m_threadGereUDP(nullptr),
    m_threadGereLancementPartie(nullptr),
    m_vitesseEnnemis(3),
    m_vieEnnemis(1),
    m_cadenceEnnemis(150)
{
    m_threadGereTCP = new sf::Thread(&Serveur::gereTCP, this);
    m_threadGereUDP = new sf::Thread(&Serveur::gereUDP, this);
    m_threadGereConnexionTCP = new sf::Thread(&Serveur::gereConnexionTCP, this);
    m_threadGereLancementPartie = new sf::Thread(&Serveur::gereLancementPartie, this);
}

Serveur::~Serveur()
{
    m_listener.close();
    if(m_threadGereTCP != nullptr){
        m_threadGereTCP->terminate();
        delete m_threadGereTCP;
        m_threadGereTCP = nullptr;
    }
    if(m_threadGereUDP != nullptr){
        m_threadGereUDP->terminate();
        delete m_threadGereUDP;
        m_threadGereUDP = nullptr;
    }
    if(m_threadGereConnexionTCP != nullptr){
        m_threadGereConnexionTCP->terminate();
        delete m_threadGereConnexionTCP;
        m_threadGereConnexionTCP = nullptr;
    }
    if(m_threadGereLancementPartie != nullptr){
        m_threadGereLancementPartie->terminate();
        delete m_threadGereLancementPartie;
        m_threadGereLancementPartie = nullptr;
    }
    while(!m_socketTCPVec.empty())delete m_socketTCPVec.back(), m_socketTCPVec.pop_back();
    while(!m_joueurVec.empty())delete m_joueurVec.back(), m_joueurVec.pop_back();
}

void Serveur::lancer()
{
    std::cout << "Lancement du serveur" << std::endl;
    m_attentePartie.restart();
    m_threadGereConnexionTCP->launch();
    m_threadGereLancementPartie->launch();
    std::string commande;
    while(commande != "exit")/*info();*/std::cin >> commande;
    m_estActif = false;
    std::cout << "Fermeture en cours" << std::endl;
    m_threadGereLancementPartie->wait();
    m_threadGereConnexionTCP->wait();
    m_threadGereTCP->wait();
    m_threadGereUDP->wait();
}

void Serveur::gereConnexionTCP()
{
    if(m_listener.listen(42442) != sf::Socket::Done){
        mutex.lock();
        m_estActif = false;
        mutex.unlock();
        return;
    }
    m_listener.setBlocking(false);
    while(m_estActif)
    {

        SocketTCPj * client = new SocketTCPj(0);
        if(m_listener.accept((*client)) != sf::Socket::Done){
            // Pas forcement une erreur
            delete client;
        }else{
            mutex.lock();
            int i = 0;
            sf::Packet p;
            if(m_socketTCPVec.size() < 4){
                m_socketTCPVec.push_back(client);
                i = (m_placeLibre.empty()) ? m_socketTCPVec.size() : m_placeLibre.back();
                if(!m_placeLibre.empty())m_placeLibre.pop_back();
                if(!m_placeLibre.empty()){
                    std::cout << "place" << std::endl;
                    for(auto a : m_placeLibre){
                        std::cout << a << std::endl;
                    }
                    m_placeLibre.pop_back();
                }
                m_socketTCPVec.back()->setId(i);
                std::sort(m_socketTCPVec.begin(), m_socketTCPVec.end(),
                          [](SocketTCPj * a, SocketTCPj * b)
                {
                    return a->getId() < b->getId();
                });
                p << i;
                client->send(p);
                client->setBlocking(false);
                std::cout << "Le joueur " << i << " s'est connecter" << std::endl;
                if(!m_isTCPLancer)m_threadGereTCP->launch();
            }else{
                p << i;
                client->send(p);
                delete client;
            }
            mutex.unlock();
        }
        sf::sleep(sf::microseconds(22222)); // on ne fait un tour que 45x par seconde
    }
    m_listener.close();
}

void Serveur::gereTCP()
{
#ifdef DEBUG
    std::cout << "Lancement de la threade TCP" << std::endl;
#endif
    m_isTCPLancer = true;
    for(unsigned int i=0 ; m_estActif && (i < m_socketTCPVec.size()) ;)
    {
        sf::Packet p;
        mutex.lock();
        sf::Socket::Status stat = m_socketTCPVec.at(i)->receive(p);
        mutex.unlock();
        switch(stat)
        {
            case sf::Socket::Done:
            {
                // On traite le paquet
                unsigned short header;
                p >> header;
                switch(header)
                {
                    case CONNECUDP:
                    {
                        int idJoueur;
                        unsigned short localPort;
                        p >> idJoueur >> localPort;
                        std::cout << "Joueur : " << idJoueur << std::endl;
                        Joueur * j = new Joueur(idJoueur,
                                                m_socketTCPVec.at(i)->getRemoteAddress().toString(),
                                                localPort);
                        sf::UdpSocket * socket = new sf::UdpSocket;
                        socket->bind(sf::Socket::AnyPort);
                        sf::Packet reponse;
                        reponse << CONNECUDP << socket->getLocalPort();
                        std::cerr << "envoie" << std::endl;
                        m_socketTCPVec.at(idJoueur - 1)->send(reponse);
                        std::cerr << "envoyer" << std::endl;
                        socket->setBlocking(false);
                        j->setSocket(socket);
                        m_joueurVec.push_back(j);

                        std::sort(m_joueurVec.begin(), m_joueurVec.end(),
                                  [](Joueur * a, Joueur * b)
                        {
                            return a->getID() < b->getID();
                        });
#ifdef DEBUG
                        std::cout << "Liste JoueurVec" << std::endl;
                        for(auto j : m_joueurVec){
                            std::cout << j->getID() << std::endl;
                        }
#endif

                        if(!m_isUDPLancer)m_threadGereUDP->launch();
                        break;
                    }
                    case LAUNCHGAME:
                    {
                        m_joueurVec.at(i)->setEnJeu(true);
                        m_attentePartie.restart();
                        break;
                    }
                    case SCORETCP:
                    {
                        int scoreJoueur;
                        p >> scoreJoueur;

                        //on insere le score dans le vecteur du joueur
                        m_joueurVec[i]->setScore(scoreJoueur);


                        //tri du score des joueurs en mode décroissant
                        std::sort(m_joueurVec.begin(), m_joueurVec.end(),
                                  [](Joueur * a, Joueur * b)
                        {
                            return a->getScore() > b->getScore();
                        });

                        //packet de réponse
                        sf::Packet reponse; //initialisation du packet
                        reponse << SCORETCP; //header du packet
                        reponse << creationDocXml(m_joueurVec); //contenu du packet le xml en flux de données
                        for(auto s : m_socketTCPVec){// pour tous les joueurs
                            s->send(reponse);
                        }

                        break;
                    }

                    default:
                    {
                        std::cerr << "Paquet corrumpu" << std::endl;
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
                std::cout << "Le joueur " << i+1 << " s'est deconnecter" << std::endl;
                m_placeLibre.push_back(i+1);
                m_placeLibre.push_back(m_socketTCPVec.at(i)->getId());
                std::sort(m_placeLibre.begin(), m_placeLibre.end(),
                          [](const int & a, const int & b)
                {

                    return a > b;
                });

                delete m_socketTCPVec[i];
                m_socketTCPVec.erase(m_socketTCPVec.begin()+i);

                delete m_joueurVec[i];
                m_joueurVec.erase(m_joueurVec.begin()+i);

                for(auto j : m_socketTCPVec){
                    sf::Packet info;
                    info << JOUEURDECO << i;
                    j->send(info);
                }

                i--;

                int enJeu = 0;
                for(auto j : m_joueurVec){
                    if(j->getEnJeu())enJeu++;
                }
                if(enJeu == 0){
                    m_partieLancer = false;
                    m_threadGereLancementPartie->launch();
                    std::cout << "Partie terminer" << std::endl;
                }
                break;
            }
            case sf::Socket::Error:
            {
                // Erreur lors de la reception
                break;
            }
        }
        if(!m_partieLancer){
            for(unsigned int j=0 ; j < m_joueurVec.size() ; j++){
                if(!m_joueurVec.at(j)->getEnJeu()){
                    sf::Packet paquet;
                    paquet << LAUNCHGAME;
                    m_socketTCPVec.at(j)->send(paquet);
#ifdef DB
                    std::cout << "invitation envoye a " << j+1 << std::endl;
#endif
                }
            }
        }



        i = (i >= m_socketTCPVec.size() -1) ? 0 : i+1;
        sf::sleep(sf::microseconds(22222)); // on ne fait un tour que 45x par seconde
    }
    m_isTCPLancer = false;
#ifdef DEBUG
    std::cout << "Fin de la threade TCP" << std::endl;
#endif
}

void Serveur::gereUDP()
{
#ifdef DEBUG
    std::cout << "Lancement de la threade UDP" << std::endl;
#endif
    m_isUDPLancer = true;
    for(unsigned int i=0 ; m_estActif && (i < m_joueurVec.size()) ;)
    {
        sf::Uint16 paquet;
        sf::IpAddress ipSender;
        unsigned short portSender;
        std::size_t receive = 0;
        mutex.lock();
        sf::Socket::Status stat = m_joueurVec.at(i)->getSocket()->receive((void*)&paquet,
                                                                          sizeof(paquet),
                                                                          receive,
                                                                          ipSender,
                                                                          portSender);
        mutex.unlock();
        switch(stat)
        {
            case sf::Socket::Done:
            {
                // On traite le paquet

                sf::Uint16 header = ((paquet & 0b1110000000000000) >> 13);
                sf::Uint16 reponse;

                switch (header) {
                    case UDP_CS_SETX:
                    {
                        reponse  = UDP_SC_SETX << 14;
                        reponse |= (static_cast<sf::Uint16>(i) & 0b0000000000001111) << 10;
                        reponse |= ((paquet & 0b0001111111111000) >> 3);
                        break;
                    }
                    case UDP_CS_SETY:
                    {
                        reponse  = UDP_SC_SETY << 14;
                        reponse |= (static_cast<sf::Uint16>(i) & 0b0000000000001111) << 10;
                        reponse |= ((paquet & 0b0001111111111000) >> 3);
                        break;
                    }
                    case UDP_CS_TIR:
                    {
                        reponse = UDP_SC_TIR << 14;
                        reponse |= ((static_cast<sf::Uint16>(i) & 0b0000000000001111) << 10);
                        reponse |= ((paquet & 0b0001111100000000) >> 3);
                        break;
                    }
                    case UDP_CS_CONTACT:
                    {
                        reponse = UDP_SC_INVULNERABLE << 14;
                        reponse |= ((static_cast<sf::Uint16>(i) & 0b0000000000001111) << 10);
                        // const sf::Uint16 id = ((paquet & 0b0001111000000000) >> 9);
                        // Sauvegarder les degat fait au enemie si l'ID et >= 4
                        break;
                    }
                    case UDP_CS_IMPACT:
                    {
                        reponse = UDP_SC_INVULNERABLE << 14;
                        const sf::Uint16 id = ((paquet & 0b0001111000000000) >> 9);
                        if(id < 4){
                            reponse |= (id << 10);
                        }else{
                            continue;
                        }
                        std::cout << std::bitset<16>(reponse) << std::endl;
                        break;
                    }
                    default:
                        continue;
                        break;
                }
                std::pair<std::string, unsigned short> p(ipSender.toString(), portSender);
                for(unsigned int j=0; j < m_joueurVec.size() ; j++){
                    Joueur * joueur = m_joueurVec.at(j);
                    if(!joueur->equals(p)){
                        m_socketUDP.send((void*)&reponse, sizeof(reponse),joueur->getIpAdresse(),joueur->getPort());
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
                std::cout << "Le joueur " << i+1 << "s'est deconnecter(UDP)" << std::endl;
                delete m_joueurVec[i];
                m_joueurVec.erase(m_joueurVec.begin()+i);
                i--;
                break;
            }
            case sf::Socket::Error:
            {
                // Erreur lors de la reception
                std::cout << "erreur lors de la reception du paquet UDP" << std::endl;
                break;
            }
        }
        //std::cout << "index udp : " << i << std::endl;
        i = (i >= m_joueurVec.size() -1) ? 0 : i+1;
        sf::sleep(sf::microseconds(100)); // on ne fait un tour que 45x par seconde
    }
    m_isUDPLancer = false;
#ifdef DEBUG
    std::cout << "Fin de la threade UDP" << std::endl;
#endif
}

void Serveur::gereLancementPartie()
{
    m_vitesseEnnemis=5;
    m_vieEnnemis=1;
    m_cadenceEnnemis=150;
    while(!m_partieLancer)
    {
        bool commencer = true;
        for(auto j : m_joueurVec){
            if(!j->getEnJeu()){
                commencer = false;
                break;
            }
        }
        if(commencer && (m_joueurVec.size() > 0) && (m_attentePartie.getElapsedTime() >= sf::seconds(10))){
            m_partieLancer = true;
            std::cout << "Partie lancer" << std::endl;
            sf::Packet p;

            //Creation et envoi du document XML sur les ennemis
            p << LISTEENEMIE;
            p << creationDocXml_ennemis(this, m_cadenceEnnemis, m_vitesseEnnemis, m_vieEnnemis);
            for(SocketTCPj *s : m_socketTCPVec){
                s->send(p);
            }

            //Envoi du lancement de partie a tous les joueurs
            p.clear();
            p << GAMELAUNCHED;
            for(SocketTCPj *s : m_socketTCPVec){
                s->send(p);
            }
        }
        sf::sleep(sf::microseconds(22222));
    }
}

float Serveur::getVitesseEnnemis()const
{
    return m_vitesseEnnemis;
}

unsigned int Serveur::getVieEnnemis()const
{
    return m_vieEnnemis;
}

unsigned int Serveur::getCadenceEnnemis()const
{
    return m_cadenceEnnemis;
}

void Serveur::ameliorerEnnemis()
{
    std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> rand(0,3);
    int chance = rand(generator);
    switch(chance)
    {
        case 0:
            m_vitesseEnnemis*=0.9;
            break;
        case 1:
            m_vieEnnemis++;
            break;
        case 2:
            m_cadenceEnnemis*=0.9;
            break;
        default :
            break;
    }
}

void Serveur::info()
{
    std::cout << "nb joueur : " << m_joueurVec.size() << "/" << m_socketTCPVec.size() << std::endl;
    for(auto j : m_joueurVec){
        std::cout << j->getID() << std::endl;
    }
    for(auto j : m_socketTCPVec){
        std::cout << j->getId() << std::endl;
    }

    std::cout << m_placeLibre.size() << " place libre" << std::endl;
    for(auto j : m_placeLibre){
        std::cout << j << std::endl;
    }
}

