#ifndef ENTITE
#define ENTITE

#include <vector>
#include <sstream>
#include <random>
#include <cstdlib>
#include <SFML/Graphics.hpp>


class Entite: public sf::Sprite
{
public:
    //! Constructeur d'entite
    /*!
      Entree : unsigned int
      Sortie :
      Description : cree une entite avec un id
    */
    Entite(unsigned int);
    //! Constructeur d'entite
    /*!
      Entree : unsigned int id, int vie
      Sortie :
      Description : cree une entite avec un id et des points de vie
    */
    Entite(unsigned int id, int vie);
    //! Constructeur de recopie d'entite
    /*!
      Entree : const entite &
      Sortie :
      Description :
    */
    Entite(const Entite &);
    //! Destructeur d'entite
    /*!
      Entree :
      Sortie :
      Description :
    */
    ~Entite();

    virtual void bouger();

    //! Getter id
    /*!
      Entree :
      Sortie : unsigned int
      Description : retourne l'id d'une entite
    */
    unsigned int getId()const;
    //! Getter vie
    /*!
      Entree :
      Sortie : unsigned int
      Description : retourne la vie d'une entite
    */
    unsigned int getVie()const;
    //! Getter hitbox
    /*!
      Entree :
      Sortie : sf::Image &
      Description : retourne l'image de HitBox d'une entite
    */
    const sf::Image &getHitBox()const;
    //! Setter id
    /*!
      Entree : const unsigned int
      Sortie :
      Description : definir l'id d'une entite
    */
    void setId(const unsigned int);
    //! Setter vie
    /*!
      Entree : const unsigned int
      Sortie :
      Description : definir la vie d'une entite
    */
    void setVie(const unsigned int);
    //! Setter HitBox
    /*!
      Entree : sf::Image &
      Sortie :
      Description : definir l'image de HitBox d'une entite
    */
    void setItBox(const sf::Image &img);


    //! Baisser la vie
    /*!
      Entree :
      Sortie :
      Description : baisse la vie d'une entite
    */
    void baisserVie();
    //! Surcharge d'operateur ==
    /*!
      Entree : const unsigned int
      Sortie : bool
      Description : verifier si une entite a un id X
    */
    bool operator ==(const unsigned int)const;
    //! Surcharge d'operateur !=
    /*!
      Entree : const entite &
      Sortie : bool
      Description : Verifier que deux entites sont differentes
    */
    bool operator !=(const Entite&)const;
    //! Surcharge d'operateur ==
    /*!
      Entree : const entite&, const unsigned int
      Sortie : bool
      Description : savoir si une entite a un id X
    */
    friend bool operator ==(const Entite&, const unsigned int);


    //! Savoir si une entite est dans l'ecran
    /*!
      Entree :
      Sortie : bool
      Description :verifier les coordonnees d'une entite
    */
    bool estDansEcran();

protected:
    unsigned int m_id;
    unsigned int m_vie;

    sf::Image m_hitbox;
};

#endif
