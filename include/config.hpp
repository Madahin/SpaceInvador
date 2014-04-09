#ifndef CONFIG
#define CONFG

const unsigned short CONNECUDP = 0;
const unsigned short SCORETCP = 1;
const unsigned short SETX = 2;
const unsigned short SETY = 3;
const unsigned short LAUNCHGAME = 4;
const unsigned short TIRER = 5;
const unsigned short GAMELAUNCHED = 6;
const unsigned short JOUEURDECO = 7;
const unsigned short LISTEENEMIE = 8;

// Les protocoles UDP du client vers le serveur
const unsigned short UDP_CS_SETX     = 0;
const unsigned short UDP_CS_SETY     = 1;
const unsigned short UDP_CS_TIR      = 2;
const unsigned short UDP_CS_CONTACT  = 3;
const unsigned short UDP_CS_IMPACT   = 4;
const unsigned short UDP_CS_SORTIE   = 5;

// Les protocoles UDP du serveur vers le client
const unsigned short UDP_SC_SETX         = 0;
const unsigned short UDP_SC_SETY         = 1;
const unsigned short UDP_SC_TIR          = 2;
const unsigned short UDP_SC_INVULNERABLE = 3;

//Les protocoles TCP du serveur vers le client
const unsigned short TCP_SC_MORT      = 0;
const unsigned short TCP_SC_AMELIORER = 0;
const unsigned short TCP_SC_CREER     = 0;
const unsigned short TCP_SC_TIMER     = 0;
const unsigned short TCP_SC_FIN       = 0;
#endif
