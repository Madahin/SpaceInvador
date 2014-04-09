#ifndef GAMESTATEMANAGER
#define GAMESTATEMANAGER

#include <stack>
#include "include/client/states/State.hpp"

class State;

class GameStateManager
{
public:
    //! Constructeur de GameStateManager
    /*!
      Entree :
      Sortie :
      Description :
    */
    GameStateManager();
    //! Destructeur de GameStateManager
    /*!
      Entree :
      Sortie :
      Description :
    */
    ~GameStateManager();

    //! Setter Etat
    /*!
      Entree : State*
      Sortie :
      Description : definir l'etat du jeu en haut de la pile (attente, enjeu,...)
    */
    void setEtat(State* etat);
    //! Getter Etat
    /*!
      Entree :
      Sortie : State *
      Description : retourne l'etat dans lequel le jeu se situe
    */
    State *getEtat();
    //! Ajouter un nouvel etat
    /*!
      Entree : State *
      Sortie :
      Description : ajouter un etat en haut de la pile (celui qui sera pris en compte)
    */
    void pushState(State* etat);
    //! Enlever l'etat actuel
    /*!
      Entree :
      Sortie :
      Description : Enlever l'etat de jeu et passer au precedent
    */
    void popState();
private:
    std::stack<State*> m_pile;
};

#endif
