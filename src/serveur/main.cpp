#include "include/serveur/serveur.hpp"
#include <cstdlib>

int main()
{
    Serveur *s = new Serveur;
    s->lancer();
    delete s;
    s = nullptr;
    return 0;
}
