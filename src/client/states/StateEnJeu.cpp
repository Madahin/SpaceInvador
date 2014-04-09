#include "include/client/states/StateEnJeu.hpp"

StateEnJeu::StateEnJeu(sf::TcpSocket *socketTCP, sf::UdpSocket *socketUDP) :
    m_gauche(false),
    m_droit(false),
    m_haut(false),
    m_bas(false),
    m_tirer(false),
    m_state(0)
{
    m_tcpSocket = socketTCP;
    m_udpSocket = socketUDP;

    m_textJoueurs.loadFromFile("Ressources/vaisseaux.png");
    m_textTir.loadFromFile("Ressources/tir.png");
    m_textEnnemie.loadFromFile("Ressources/vaisseau_ennemi.png");

    Joueur * j = new Joueur( BoardSingleton::get()->getIdJoueur() );

    j->setTexture(m_textJoueurs);
    j->setTextureRect(sf::IntRect((BoardSingleton::get()->getIdJoueur()-1)*37,0,37,41));

    //On ajoute notre propre joueur au milieu de l'ecran
    auto it=m_liste_mes_entites.begin();
    m_liste_mes_entites.insert ( it , j );
    m_liste_mes_entites[0]->setPosition(320,240);
}
StateEnJeu::~StateEnJeu()
{

}

void StateEnJeu::liberer()
{
    m_threadTCP->terminate();
    m_threadUDP->terminate();
}

void StateEnJeu::initialise()
{
    m_font.loadFromFile("Ressources/8bitoperator.ttf");

    m_textBoard.setFont(m_font);
    m_textBoard.setCharacterSize(12);
    m_textBoard.setString(L"Équipe : \nJoueur : ");
    m_textBoard.setPosition(127,23);

    BoardSingleton::get()->setCenterText(m_textBoard);
    BoardSingleton::get()->montrePanneauGauche(true);
    BoardSingleton::get()->montrePanneauDroit(true);

    m_udpSocket->setBlocking(true);

    m_threadTCP = new sf::Thread(&StateEnJeu::gerer_tcp, this);
    m_threadUDP = new sf::Thread(&StateEnJeu::gerer_udp, this);

    m_threadTCP->launch();
    m_threadUDP->launch();
}

void StateEnJeu::dessiner(sf::RenderWindow &w)
{
    for(auto e : m_liste_autres_entites){
        w.draw(*e);
    }
    for(auto e : m_liste_mes_entites){
        w.draw(*e);
    }
}



/* Gerer les evenements */
void StateEnJeu::controler(const sf::Event &e)
{
    sf::Uint16 paquet = 0;
    if(e.type==sf::Event::KeyPressed)
    {
        switch(e.key.code)
        {
        case sf::Keyboard::Space :
            tirer();
            break;
        case sf::Keyboard::Up :
            m_bas = false;
            m_haut = true;
            break;
        case sf::Keyboard::Down :
            m_haut = false;
            m_bas = true;
            break;
        case sf::Keyboard::Left :
            m_droit = false;
            m_gauche = true;
            break;
        case sf::Keyboard::Right :
            m_gauche = false;
            m_droit = true;
            break;
        default:
            break;
        }
    }else if(e.type == sf::Event::KeyReleased)
    {
        switch(e.key.code)
        {
        case sf::Keyboard::Up :
            m_haut = false;
            break;
        case sf::Keyboard::Down :
            m_bas = false;
            break;
        case sf::Keyboard::Left :
            m_gauche = false;
            break;
        case sf::Keyboard::Right :
            m_droit = false;
            break;
        default:
            break;
        }
    }
    if(paquet){
        m_udpSocket->send((void*)&paquet, sizeof(paquet), m_tcpSocket->getRemoteAddress(), BoardSingleton::get()->getPortUDP());
    }
}

void StateEnJeu::mecanique()
{
    if(!m_listePaquet.empty())traitePaquet();

    sf::Uint16 paquet = 0;

    if(m_haut){
        if((m_liste_mes_entites[0]->getPosition().y - VITJ) >= 0){
            m_liste_mes_entites[0]->move(0,-VITJ);
        }
        paquet = getPaquetSetY();
        m_udpSocket->send((void*)&paquet, sizeof(paquet), m_tcpSocket->getRemoteAddress(), BoardSingleton::get()->getPortUDP());
    }
    if(m_bas){
        if((m_liste_mes_entites[0]->getPosition().y + m_liste_mes_entites[0]->getGlobalBounds().height) < 480){
            m_liste_mes_entites[0]->move(0,VITJ);
        }
        paquet = getPaquetSetY();
        m_udpSocket->send((void*)&paquet, sizeof(paquet), m_tcpSocket->getRemoteAddress(), BoardSingleton::get()->getPortUDP());
    }
    if(m_gauche){
        if((m_liste_mes_entites[0]->getPosition().x - VITJ) >= 0){
            m_liste_mes_entites[0]->move(-VITJ,0);
        }
        paquet = getPaquetSetX();
        m_udpSocket->send((void*)&paquet, sizeof(paquet), m_tcpSocket->getRemoteAddress(), BoardSingleton::get()->getPortUDP());
    }
    if(m_droit){
        if((m_liste_mes_entites[0]->getPosition().x + m_liste_mes_entites[0]->getGlobalBounds().width) < 640){
            m_liste_mes_entites[0]->move(VITJ,0);
        }
        paquet = getPaquetSetX();
        m_udpSocket->send((void*)&paquet, sizeof(paquet), m_tcpSocket->getRemoteAddress(), BoardSingleton::get()->getPortUDP());
    }

    int cpt_mes_entites=0;
    for(auto it = m_liste_mes_entites.begin() ; it != m_liste_mes_entites.end() ; ++it){
        if(cpt_mes_entites>0)
        {
            (*it)->bouger();
            if(!(*it)->estDansEcran()){
                //Si le tir est sorti, on le supprime
                delete *it;
                m_liste_mes_entites.erase(it);
                //e->setPosition(100,400);
                it = m_liste_mes_entites.begin();
                //cpt_mes_entites--;
                cpt_mes_entites = 0;
            }
        }
        cpt_mes_entites++;
    }
    for(auto e : m_liste_autres_entites){
        e->bouger();
        Ennemi *tmp = dynamic_cast<Ennemi*>(e);
        if(tmp != nullptr){
            const sf::Vector2f &pos = tmp->getPosition();
            if(pos.x > 640){
                tmp->setPosition(-tmp->getGlobalBounds().width, pos.y);
            }if(pos.y > 480){
                tmp->setPosition(pos.x, -tmp->getGlobalBounds().height);
            }if(pos.x < (-tmp->getGlobalBounds().width)){
                tmp->setPosition(640-tmp->getGlobalBounds().width, pos.y);
            }if(pos.y < (-tmp->getGlobalBounds().height)){
                tmp->setPosition(pos.x, 480-tmp->getGlobalBounds().height);
            }
        }
    }

    traiteCollision();

    for(Entite* e : m_liste_mes_entites)
    {
        Joueur* j = static_cast<Joueur*>(e);
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

    /*if(paquet){
        m_udpSocket->send((void*)&paquet, sizeof(paquet), m_tcpSocket->getRemoteAddress(), BoardSingleton::get()->getPortUDP());
    }*/





}

void StateEnJeu::tirer()
{
    if(m_tirer==false)
    {
        //On trouve le nouvel id de tir
        int nouvelId=trouverIdTir(m_liste_mes_entites);
        if(nouvelId==-1)
        {
            m_tirer=false;
        }
        else{
            m_tirer=true;
        }
        //On cree le tir
        if(m_tirer==true)
        {
            Joueur tmp = *static_cast<Joueur*>(m_liste_mes_entites[0]);
            Tir * t = new Tir(nouvelId,tmp);
            t->setTexture(m_textTir);
            m_liste_mes_entites.push_back ( t );
            m_tirer=false;
            //m_liste_mes_entites[BoardSingleton::get()->getIdJoueur()]->setPosition(320,240);
            sf::Uint16 paquet = getPaquetTir(nouvelId);
            m_udpSocket->send((void*)&paquet, sizeof(paquet), m_tcpSocket->getRemoteAddress(), BoardSingleton::get()->getPortUDP());
        }

    }
}

void StateEnJeu::traitePaquet()
{
    do
    {
        sf::Uint16 paquet = m_listePaquet.back();
        //On enregistre  l'identifiant du protocole dans header
        sf::Uint16 header = paquet & 0b1100000000000000;
        header >>=14;
        //On recupere l'id de joueur : les 4 bits suivants
        sf::Uint16 id = paquet & 0b0011110000000000;
        id >>= 10;
        //On recupere dans data les bits suivants
        sf::Uint16 data = paquet & 0b0000001111111111;
        Joueur* j = static_cast<Joueur*>(trouveEntiterParId<Entite*>(m_liste_autres_entites, id));
        //Si l'id de joueur recue n'existe pas, on la cree
        if(j == nullptr){
            j = new Joueur(id);
            j->setTexture(m_textJoueurs);
            j->setTextureRect(sf::IntRect((id)*37,0,37,41));
            m_liste_autres_entites.push_back(j);
            //On trie le vecteur d'autres entites
            std::sort(m_liste_autres_entites.begin(), m_liste_autres_entites.end(),[](Entite * a, Entite * b)
            {
                return a->getId() < b->getId();
            });
        }

        switch(header)
        {
        case UDP_SC_SETX:
        {
            j->setPosition(data, j->getPosition().y);
            //j->setPosition(id, j->getPosition().y);
            break;
        }
        case UDP_SC_SETY:
        {
            j->setPosition(j->getPosition().x, data);
            //j->setPosition(j->getPosition().x, id);
            break;
        }
        case UDP_SC_TIR:
        {
            //On cree un tir à partir du joueur qui a tire et de son id
            Joueur tmp = (*(j));
            //Tir * t = new Tir(((paquet & 0b0000001111100000) >> 5), tmp);
            Tir * t = new Tir(((paquet & 0b0011111111100000) >> 5), tmp);
            t->setTexture(m_textTir);
            m_liste_autres_entites.push_back(t);
            //On trie le vecteur
            std::sort(m_liste_autres_entites.begin(), m_liste_autres_entites.end(),[](Entite * a, Entite * b)
            {
                return a->getId() < b->getId();
            });
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

void StateEnJeu::gerer_udp()
{
    while(m_state == 0)
    {
        sf::Uint16 paquet;
        std::size_t receive;
        sf::IpAddress adresse = m_tcpSocket->getRemoteAddress();
        unsigned short port = BoardSingleton::get()->getPortUDP();
        sf::Socket::Status stat = m_udpSocket->receive((void*)&paquet, sizeof(paquet), receive, adresse, port);
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

void StateEnJeu::gerer_tcp()
{
    while(m_state == 0)
    {
        sf::Packet paquet;
        sf::Socket::Status stat = m_tcpSocket->receive(paquet);
        switch(stat)
        {
        case sf::Socket::Done:
        {
            unsigned short header;
            paquet >> header;
            switch(header)
            {
            case GAMELAUNCHED:
            {

                break;
            }
            case JOUEURDECO:
            {
                int id;
                paquet >> id;
                deleteByID(id, m_liste_autres_entites);
                break;
            }
            case LISTEENEMIE:
            {
                std::string xml;
                paquet >> xml;
                std::cout << xml << std::endl;
                lireXML_ennemi(xml);
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
            BoardSingleton::get()->setStatePop(3);
            break;
        }
        case sf::Socket::Error:
        {
            // Erreur lors de la reception
            break;
        }
        }
        sf::sleep(sf::seconds(1/45));
    }
}

sf::Uint16 StateEnJeu::getPaquetSetX()
{
    sf::Uint16 rep = UDP_CS_SETX << 13;
    rep |= (static_cast<int>(m_liste_mes_entites[0]->getPosition().x) << 3);
    return rep;
}

sf::Uint16 StateEnJeu::getPaquetSetY()
{
    sf::Uint16 rep = UDP_CS_SETY << 13;
    rep |= (static_cast<int>(m_liste_mes_entites[0]->getPosition().y) << 3);
    return rep;
}

sf::Uint16 StateEnJeu::getPaquetTir(sf::Uint16 id)
{
    sf::Uint16 rep = UDP_CS_TIR << 13;
    rep |= ((id & 0b0000000000011111) << 8);
    return rep;
}


/*
E : Vector<Entite *>
S : int
Description : retourne le premier entier libre entre ((idJoueur-1)*33+4) et (idJoueur*33+4)
*/
unsigned int StateEnJeu::trouverIdTir(std::vector <Entite *> v)
{
    int res=-1;
    //On trie le tableau
    std::sort(v.begin(), v.end(),[](Entite * a, Entite * b)
    {
        return a->getId() < b->getId();
    });
    //On trouve le premier id et le dernier id possible
    unsigned int premierId= (( v[0]->getId() - 1 ) * 33 + 4 + 1);
    unsigned int dernierId= ( v[0]->getId() * 33 + 4);

    //Si le vecteur n'a qu'une entree, il n'a que le joueur. On prend donc le premier id
    if(v.size()==1)
    {
        res=premierId;
    }
    else
    {
        //On consulte tout le vecteur jusqu'a trouver un id libre
        //Info : la premiere entree n'entrera dans aucune condition
        bool arriveAuBout(false);
        for(auto e : v){
            //Si l'id est deja pris, on dit qu'on regardera sur le prochain
            if(e->getId() == premierId){premierId++;}
            //Si on est au dernier iD et au'on n'a rien trouve, on retournera -1
            else if(e->getId() == dernierId){arriveAuBout=true;break;}
            //Si l'id est libre, on le prend et on sort de la boucle
            else if(e->getId() > premierId){
                res=premierId;
                break;
            }
        }

        if(arriveAuBout==false && premierId<=dernierId){
            res=premierId;
        }
    }
    //On retourne le nouvel id ou -1 si il n'y a rien de libre
    return res;
}

void StateEnJeu::traiteCollision()
{
    bool vaisseau = true;
    // Je consulte mon vaisseau et tous mes tirs
    for(auto e : m_liste_mes_entites){
        //Je fais une liste des entites proches que je consulte
        std::vector<Entite*> proche = getEntiteProche(e, m_liste_autres_entites);
        for(auto s : proche){
            //Si il y a un contact entre deux elements
            std::cout << s->getId() << " et proche de " << e->getId() << std::endl;
            if(collision(e, s)){
                /*
                 * Un tir a toucher quelque chose
                 */
#ifdef DEBUG
                std::cout << "colision entre " << e->getId() << " et " << s->getId() << std::endl;
#endif
                //!Si il s'agit d'un tir, on le supprime, et on envoie un rapport
                if(!vaisseau)
                {
                    deleteByID(e->getId(), m_liste_mes_entites);
                    sf::Uint16 paquet = 0b1000000000000000;
                    //                  1234567890123456
                    paquet|=s->getId()<<9;
                    paquet|=e->getId()<<4;
                    m_udpSocket->send((void*)&paquet, sizeof(paquet), m_tcpSocket->getRemoteAddress(), BoardSingleton::get()->getPortUDP());
                    //Si il s'agit d'un tir, on le supprimera
                    if( (s->getId()>4 && s->getId()<137) || s->getId()>146){
                        deleteByID(s->getId(),m_liste_autres_entites);
                    }
                }
                //!Si c'est mon vaisseau, je verifie si il touche un vaisseau ou un annemi
                else{
                    //Les id des ennemis vont de 137 a 146
                    //Les id des allies vont de 0 a 4
                    //Le reste sera un tir
                    //!Si c'est un tir, j'envoie impact et je supprime le tir et je perds un pdv
                    if(s->getId()>146){
                        sf::Uint16 paquet = 0b1000000000000000;
                        //                  1234567890123456
                        paquet|=e->getId()<<9;
                        paquet|=s->getId()<<4;
                        m_udpSocket->send((void*)&paquet, sizeof(paquet), m_tcpSocket->getRemoteAddress(), BoardSingleton::get()->getPortUDP());
                        s->baisserVie();
                        e->baisserVie();
                        deleteByID(s->getId(),m_liste_autres_entites);
                    }
                    //!Si c'est mon vaisseau contre un vaisseau, j'envoie contact
                    else{
                        sf::Uint16 paquet = 0b1100000000000000;
                        //                  1234567890123456
                        paquet|=s->getId()<<9;
                        m_udpSocket->send((void*)&paquet, sizeof(paquet), m_tcpSocket->getRemoteAddress(), BoardSingleton::get()->getPortUDP());
                        s->baisserVie();
                        e->baisserVie();
                        if(s->getVie()<=0){deleteByID(s->getId(),m_liste_autres_entites);}
                    }

                }
            }
        }
        if(vaisseau)vaisseau = false;
    }
}


void StateEnJeu::lireXML_ennemi(const std::string &xml){
    std::stringstream ss(xml);
    pugi::xml_document doc;
    doc.load(ss);
    //!On va chercher dans les balises "ennemis"
    for (pugi::xml_node ennemis = doc.child("ennemis"); ennemis; ennemis = ennemis.next_sibling("ennemis"))
    {
        //!On recupere les attributs cadencetir, vitesse, vie
        //std::cout << "Tool " << tool.attribute("Filename").value();
        m_cadenceTir_ennemis=stringToInt(ennemis.attribute("cadencetir").value());
        int vie=stringToInt(ennemis.attribute("vie").value());
        //!On va chercher dans les balises "ennemi"
        int id=137; //Les id d'ennemis vont de 137 à 146
        for (pugi::xml_node ennemi = ennemis.child("ennemi"); ennemi; ennemi = ennemi.next_sibling("ennemi"))
        {
            //!On recupere les attributs pointCadence, vitesseX, vitesseY et ydepart
            int ydepart     =stringToInt(ennemi.attribute("ydepart").value());
            int pointCadence=stringToInt(ennemi.attribute("pointCadence").value());
            int vitesseX    =stringToInt(ennemi.attribute("vitesseX").value());
            int vitesseY    =stringToInt(ennemi.attribute("vitesseY").value());

#ifdef DEBUG
            std::cout << ennemi.attribute("ydepart").value() << " " << pointCadence << " " << vitesseX << " " << vitesseY << std::endl;
#endif

            Ennemi *e = new Ennemi(id,vie,ydepart,pointCadence,vitesseX,vitesseY);
            e->setTexture(m_textEnnemie);
            m_liste_autres_entites.push_back(e);
            id++;
        }
    }
}
