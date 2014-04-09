#include "include/serveur/fonctionXML.hpp"

std::string creationDocXml_ennemis(Serveur *s, unsigned int cadence, float vitesse, unsigned int vie)
{
    //Le document XML que l'on va retourner
    pugi::xml_document doc;
    //On cree un noeud ennemis qui contiendra tous les ennemis (et les attributs generaux)
    pugi::xml_node  ennemis = doc.append_child ( "ennemis" );
    ennemis.append_attribute("cadencetir") = cadence;
    ennemis.append_attribute("vitesse")    = vitesse;
    ennemis.append_attribute("vie")        = vie;

    int n = 10;

    //On ajoute n enfants avec leurs attributs personnels
    std::vector<Ennemi> e;
    for(int i=0 ; i < n ; i++){
        Ennemi tmp(s);
        e.push_back(tmp);
        sf::sleep(sf::seconds(0.01));
    }

    for(int cpt(0);cpt<n;cpt++){
        //On cree un ennemi et on recupere ses informations
        pugi::xml_node ennemi = ennemis.append_child ( "ennemi" );
        ennemi.append_attribute("pointCadence") = e[cpt].getCadence();
        ennemi.append_attribute("vitesseX")     = e[cpt].getVitesseX();
        ennemi.append_attribute("vitesseY")     = e[cpt].getVitesseY();
        ennemi.append_attribute("ydepart")      = e[cpt].getYDepart();
    }
    std::stringstream ss;
    doc.print(ss);
    return ss.str();
}

//creation du fichier xml score
std::string creationDocXml(std::vector<Joueur *> vec)
{
    pugi::xml_document doc;
    // Ajouter noeud avec un nom

    std::vector<std::pair<int,int>> elementPourXml;
    for(auto i : vec)
    {
        pugi::xml_node  Joueur = doc.append_child ( "joueur" );

        std::pair<int,int> a(i->getID(),i->getScore());
        elementPourXml.push_back(a);

        pugi::xml_node id = Joueur.append_child();
        id.set_name("id");


        pugi::xml_node score = Joueur.append_child();
        score.set_name("score");
        //pugi::xml_node  id  =  Joueur.insert_child_before ( "id" ,  elementPourXml.at(0).first);
        //pugi::xml_node score = Joueur.append_child("score", elementPourXml.at(1).second);
    }
    //param.append_attribute("name") = "version";
    //param.append_attribute("value") = 1.1;
    //param.insert_attribute_after("type", param.attribute("name")) = "float";

    std::stringstream ss;
    doc.print(ss);
    return ss.str();
}
