#include "include/serveur/ennemi.hpp"

Ennemi::Ennemi(Serveur * s):
    m_serveur(s),
    m_vie(m_serveur->getVieEnnemis())
{
    //On definit le point de cadence
    std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> rand(0,m_serveur->getCadenceEnnemis());
    m_cadence = rand(generator);

    //On definit l'orientation aleatoirement(selon 16 possibles)
    std::uniform_int_distribution<int> randOrientation(0,15);
    int orientation=randOrientation(generator);
    switch(orientation % 4)
    {
    case 0 :
        //m_vitesseX=m_serveur->getVitesseEnnemis()*4/5.f;
        m_vitesseX=m_serveur->getVitesseEnnemis()*4/5.f;
        m_vitesseY=m_serveur->getVitesseEnnemis()-m_vitesseX;
        break;
    case 1 :
        m_vitesseX=m_serveur->getVitesseEnnemis()*3/5.f;
        m_vitesseY=m_serveur->getVitesseEnnemis()-m_vitesseX;
        break;
    case 2 :
        m_vitesseX=m_serveur->getVitesseEnnemis()*2/5.f;
        m_vitesseY=m_serveur->getVitesseEnnemis()-m_vitesseX;
        break;
    case 3 :
        m_vitesseX=m_serveur->getVitesseEnnemis()*1/5.f;
        m_vitesseY=m_serveur->getVitesseEnnemis()-m_vitesseX;
        break;
    }
    if(orientation/8 < 1)
    {
        m_vitesseX *= -1;
    }
    if(orientation/4 == 0 || orientation/4==2)
    {
        m_vitesseY *= -1;
    }

    //On definit les coordonnees de depart
    std::uniform_int_distribution<int> randYDepart(0,680*2/3.f);
    m_YDepart=randYDepart(generator);
    m_XDepart=-38;
}

Ennemi::~Ennemi()
{

}


    unsigned int Ennemi::getVie()const
    {
        return m_vie;
    }
    unsigned int Ennemi::getCadence()const
    {
        return m_cadence;
    }
    int Ennemi::getVitesseX()const
    {
        return m_vitesseX;
    }
    int Ennemi::getVitesseY()const
    {
        return m_vitesseY;
    }
    int Ennemi::getXDepart()const
    {
        return m_XDepart;
    }
    int Ennemi::getYDepart()const
    {
        return m_YDepart;
    }


    void Ennemi::setVie(const int x)
    {
        m_vie=x;
    }
    void Ennemi::setCadence(const int x)
    {
        m_cadence=x;
    }
    void Ennemi::setVitesseX(const int x)
    {
        m_vitesseX=x;
    }
    void Ennemi::setVitesseY(const int x)
    {
        m_vitesseY=x;
    }
    void Ennemi::setXDepart(const int x)
    {
        m_XDepart=x;
    }
    void Ennemi::setYDepart(const int x)
    {
        m_YDepart=x;
    }

