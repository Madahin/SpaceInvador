#include "include/fonctionsUtiles.hpp"
#include <cmath>

template<typename T>
T trouveEntiterParId(const std::vector<T> &vec, const sf::Uint16 id)
{
    bool tmp = true;
    T rep = nullptr;
    for(unsigned int i=0 ; tmp && i < vec.size(); i++){
        if(vec.at(i)->getId() == id){
            rep = vec.at(i);
        }
    }
    return rep;
}

template Entite* trouveEntiterParId(const std::vector<Entite*> &vec, const sf::Uint16 id);
template Joueur* trouveEntiterParId(const std::vector<Joueur*> &vec, const sf::Uint16 id);

bool collision(const Entite *e1, const Entite *e2)
{
#ifndef DEBUG
    return false;
#endif
    bool rep = true;

    /*
     * On recupere les "box" des deux objet
     */
    const sf::FloatRect &box1 = e1->getGlobalBounds();
    const sf::FloatRect &box2 = e2->getGlobalBounds();

    /*
     * On commence par verifier si il a intersection entre les boite
     */

    rep = box1.intersects(box2);

    if(rep)
    {
        /*
         * On recupere la zone de colision entre les boites
         */
        float xe1, xe2, ye1, ye2, we1, he1;

        if(box1.left < box2.left){
            xe1 = box1.left;
            we1 = box1.width;
            xe2 = box2.left;
        }else{
            xe1 = box2.left;
            we1 = box2.width;
            xe2 = box1.left;
        }

        if(box1.top < box2.top){
            ye1 = box1.top;
            he1 = box1.height;
            ye2 = box2.top;
        }else{
            ye1 = box2.top;
            he1 = box2.height;
            ye2 = box1.top;
        }

        /*
         * On construit une "box" correspondant a la zone de colision
         */

        sf::FloatRect box(xe1, ye1, (xe1+we1)-xe2, (ye1+he1)-ye2);

        /*
         * On recupere les masques de hitbox de chaque objet
         */

        const sf::Image &hitbox1 = e1->getHitBox();
        const sf::Image &hitbox2 = e2->getHitBox();

        const int minW = (box1.width < box2.width)? box1.width : box2.width;
        const int minH = (box1.height < box2.height)? box1.height : box2.height;

        /*
         * On verifie pixel par pixel sur la hitbox,
         * si deux pixel au meme emplacement sont noir,
         * il y a colision
         */
        bool ok = true;
        for(int x = 0 ; ok && x < box.width && x < minW; x++){
            for(int y = 0 ; ok && y < box.height && y < minH; y++){
                if(box1.left > box2.left){
                    if(box1.top > box2.top){
                        ok = !(hitbox1.getPixel(x                     ,y                       ) == sf::Color::Black &&
                               hitbox2.getPixel(x+box2.width-box.width,y+box2.height-box.height) == sf::Color::Black);
                    }else{
                        ok = !(hitbox1.getPixel(x,y+box1.height-box.height) == sf::Color::Black &&
                               hitbox2.getPixel(x+box2.width-box.width,y) == sf::Color::Black);
                    }
                }else{
                    if(box1.top > box2.top){
                        ok = !(hitbox1.getPixel(x+box1.width-box.width,y) == sf::Color::Black &&
                               hitbox2.getPixel(x,y+box2.height-box.height) == sf::Color::Black);
                    }else{
                        ok = !(hitbox1.getPixel(x+box1.width-box.width,y+box1.height-box.height) == sf::Color::Black &&
                               hitbox2.getPixel(x,y) == sf::Color::Black);
                    }
                }
            }
        }
        rep = !ok;
    }

    return rep;
}

std::vector<Entite*> getEntiteProche(const Entite *m, const std::vector<Entite*> &vec)
{
    std::vector<Entite*> rep;
    for(auto e : vec)
    {
        const sf::FloatRect &box1 = m->getGlobalBounds();
        const sf::FloatRect &box2 = e->getGlobalBounds();

        if(((box2.left + box2.width) >= (box1.left - box1.width)) &&
                (box2.left <= (box1.left + box1.width)) &&
                ((box2.top + box2.height) >= box1.top) &&
                (box2.top <= (box1.top + box2.height))){
            if(*e != *m)rep.push_back(e);
        }
    }
    return rep;
}

void deleteByID(const int id, std::vector<Entite*> &vec)
{
    bool ok = false;
    for(auto it = vec.begin() ; (!ok) && it != vec.end() ; ++it){
        if(id == (*it)->getId()){
            delete *it;
            vec.erase(it);
            ok = true;
        }
    }
}

std::string intToString(const unsigned int x){
    //Si il n'y a qu'un chiffre, on retourne ce chiffre
    if(x<10)
    {
        int res=(int)'0'+x;
        return (char*)(res);
    }
    //Si il y a plusieurs chiffres, on appelle recursivement
    else
    {
        int res=(int)'0'+x;
        return (intToString(x/10)+((char*)(res)));
    }
}

int stringToInt(std::string s){
    std::stringstream ss(s);
    int res;
    ss >> res;
    return res;
}
