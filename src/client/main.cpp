#include <cstdlib>
#include <ctime>
#include "include/pugixml.hpp"
#include "include/client/Jeu.hpp"

int main()
{
    srand(time(NULL));
    pugi::xml_document doc;

    Jeu *j = new Jeu;
    j->jouer();
    delete j;
    j = nullptr;
    return 0;
}
