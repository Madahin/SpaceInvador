#include "include/client/arrierePlan.hpp"

ArrierePlan::ArrierePlan() :
    m_nbElemMax(100),
    m_thread(nullptr),
    m_rand(0, 65536),
    m_generator(std::chrono::system_clock::now().time_since_epoch().count())
{
    srand(time(NULL));

    for(int i=0 ; i < NBDECOR ; i++){
        sf::Texture tex;
        std::ostringstream ss;
        ss << "Ressources/decor" << i << ".png";
        tex.loadFromFile(ss.str());
        tex.setSmooth(true);
        m_vecTex.push_back(tex);
    }
    m_thread = new sf::Thread(&ArrierePlan::moveSprite, this);
    m_thread->launch();
}

ArrierePlan::~ArrierePlan()
{
    if(m_thread != nullptr){
        m_thread->terminate();
        delete m_thread;
        m_thread = nullptr;
    }
}

void ArrierePlan::dessiner(sf::RenderWindow &w)
{
    m_mutex.lock();
    for(auto a : m_vecDec){
        w.draw(a);
    }
    m_mutex.unlock();
}

void ArrierePlan::ajustFPS(float fps)
{
    if(fps > 50){
        m_mutex.lock();
        m_nbElemMax = ((m_nbElemMax + 5) >= 100)? 100 : m_nbElemMax + 5;
        m_mutex.unlock();
    }else if(fps < 45){
        m_mutex.lock();
        m_nbElemMax = ((m_nbElemMax - 5) <= 30)? 30 : m_nbElemMax - 5;
        m_mutex.unlock();
    }
}

void ArrierePlan::addSprite()
{
    const int deltaElem = m_nbElemMax - m_vecDec.size();
    for(int i = 0 ; i < deltaElem ; i++)
    {
        m_mutexRand.lock();
        int chance = m_rand(m_generator)%1000, vitesse, facteur, texture;
        m_mutexRand.unlock();
        if(chance < 990)
        {
            m_mutexRand.lock();
            vitesse = (m_rand(m_generator)%19)+1;
            m_mutexRand.unlock();
            facteur = vitesse * 1.5;
            texture=1;
        }else{
            vitesse = 1;
            facteur = 120;
            m_mutexRand.lock();
            texture = m_rand(m_generator)%(NBDECOR-1);
            m_mutexRand.unlock();
        }

        decor decor(vitesse);
        decor.setTexture(m_vecTex.at(texture));
        m_mutexRand.lock();
        decor.setColor(sf::Color(m_rand(m_generator)%256, m_rand(m_generator)%256, m_rand(m_generator)%256));

        decor.setPosition(sf::Vector2f(m_rand(m_generator)%640, -decor.getLocalBounds().height));
        m_mutexRand.unlock();
        decor.setScale(0.2-(facteur/100), 0.2-(facteur/100));
        m_vecDec.push_back(decor);
    }
}

void ArrierePlan::moveSprite()
{
    while (true) {
        addSprite();
        for(unsigned int i=0 ; i < m_vecDec.size() ; i++)
        {
            m_vecDec.at(i).move(0, m_vecDec.at(i).getV());
        }
        cleanSprite();
        sf::sleep(sf::microseconds(22222));
    }
}

void ArrierePlan::cleanSprite()
{
    for(auto iterateur=m_vecDec.begin() ; iterateur != m_vecDec.end() ; ++iterateur)
    {
        if(iterateur->getPosition().y > 600)
        {
            m_vecDec.erase(iterateur);
        }else{
            ++iterateur;
        }
    }
}

void ArrierePlan::modifElemMax(int delta)
{
    m_nbElemMax += delta;
}
