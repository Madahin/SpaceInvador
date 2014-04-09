#ifndef JOUEUR
#define JOUEUR

#include <SFML/System.hpp>
#include <SFML/Network.hpp>

class Joueur
{
public:
    //! Constructeur de joueur
    /*!
      Entree : const unsigned short, const string &, const unsigned short
      Sortie : Joueur
      Description : Cree un joueur avec un id, une adresse ip et un numero de port
    */
    Joueur(const unsigned short id, const std::string &ip, const unsigned short port);
    //! Destructeur de joueur
    /*!
      Entree :
      Sortie :
      Description :
    */
    ~Joueur();

    //! Setter enJeu
    /*!
      Entree : bool
      Sortie :
      Description : definir le joueur comme "dans la partie"
    */
    void setEnJeu(bool j);
    //! Setter PV
    /*!
      Entree : int
      Sortie :
      Description : definir le nombre de points de vie d'un joueur
    */
    void setPV(int pv);
    //! Setter Socket
    /*!
      Entree : UdpSocket*
      Sortie :
      Description : Redefinir la socket du joueur
    */
    void setSocket(sf::UdpSocket * socket);

    //! Getter enJeu
    /*!
      Entree :
      Sortie : bool
      Description : retourne si le joueur est en jeu
    */
    bool getEnJeu();
    //! Getter PV
    /*!
      Entree :
      Sortie : sortie
      Description : retourne le nombre de points de vie du joueur
    */
    int getPV();
    //! Getter ID
    /*!
      Entree :
      Sortie : unsigned short
      Description : retourne l'ID du joueur
    */
    unsigned short getID() const;
    //! Getter adresse IP
    /*!
      Entree :
      Sortie : string
      Description : retourne l'adresse IP du joueur
    */
    std::string getIpAdresse();
    //! Getter Port
    /*!
      Entree :
      Sortie : unsigned short
      Description : retourne le numero de port du joueur
    */
    unsigned short getPort();
    //! Getter de socket
    /*!
      Entree :
      Sortie : UdpSocket*
      Description : retourne le socket du joueur
    */
    sf::UdpSocket* getSocket();
    //! Getter Score
    /*!
      Entree :
      Sortie : int
      Description : definir le score du joueur
    */
    int getScore();
    //! Setter score
    /*!
      Entree : int
      Sortie :
      Description : retourne le score du joueur
    */
    void setScore(int);
    //! declarer le joueur comme touche
    /*!
      Entree :
      Sortie :
      Description : lance le timer d'invulnerablilite du joueur
    */
    void estToucher();
    //! Dire qu'on a ou non la thread UDP
    /*!
      Entree : bool
      Sortie :
      Description :
    */
    void setinitUDP(bool b);
    //! Savoir si le joueur est invincible
    /*!
      Entree :
      Sortie : bool
      Description :
    */
    bool isInvincible();
    //! Getter UDPInit
    /*!
      Entree :
      Sortie : bool
      Description : savoir si on a ou non la thread UDP du client
    */
    bool isUDPInit();
    //! Verifier l'adresse du joueur
    /*!
      Entree : pair <string (ip), short(port)>
      Sortie :
      Description : comparer l'ip et le port d'un joueur
    */
    bool equals(const std::pair<std::string, unsigned short> &p);

private:
    const unsigned short m_id;
    const std::string m_adresse;
    const unsigned short m_port;
    bool m_enJeu;
    bool m_initUDP;
    int m_pv;
    sf::UdpSocket* m_socket;
    sf::Clock m_timer;
    int m_Score;
};

#endif
