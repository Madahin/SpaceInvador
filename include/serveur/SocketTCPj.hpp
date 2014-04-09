#ifndef SOCKETTCPJ
#define SOCKETTCPJ

#include <SFML/Network.hpp>

class SocketTCPj : public sf::TcpSocket
{
public:
    //! Constructeur de SocketTCPj
    /*!
      Entree : int
      Sortie :
      Description : construit un socket et lui donne un ID
    */
    SocketTCPj(int id);
    //! Getter id
    /*!
      Entree :
      Sortie : int
      Description : retourne l'id du socket
    */
    int getId();
    //! Setter id
    /*!
      Entree : int
      Sortie :
      Description : definir l'ID du socket
    */
    void setId(int id);
private:
    int m_id;
};

#endif
