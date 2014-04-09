#ifndef DECOR
#define DECOR

#include <SFML/Graphics.hpp>

class decor : public sf::Sprite
{
public:
    //!decor
    /*!
        Entrée: int v
        Sortie:
        Description: constructeur
    */
    decor(int v);

     //!decor
    /*!
        Entrée:
        Sortie: int m_v
        Description: retourne le décor
    */
    int getV();
private:
    int m_v;
};

#endif
