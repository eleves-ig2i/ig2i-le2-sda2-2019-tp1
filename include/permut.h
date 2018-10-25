/**
 * \file permut.h
 * \include "parcours.h" et bibliothèques nécessaires à la fonction epilogue
 * \brief Déclaration des variables et fonctions utilisées dans le programme principal.
 * \remark constitue un fichier correspondant à la partie 2 du TP1 de SDA2
 * \author Nathan Salez
 * \version 1.0
 * \date 14/09/2018
 */

#ifndef SDA2_TP1_SALEZ_PERMUT_H
#define SDA2_TP1_SALEZ_PERMUT_H

#include <math.h>
#include "parcours.h"

#include <sys/types.h>
#include <sys/timeb.h>

#if defined (_WIN32)
#include <windows.h>
#pragma comment(lib, "Ws2_32.lib")
//#elif defined (__unix__)
#else
#define  __unix__
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif


#if defined (_MSC_VER)
/*
 *	Slection du niveau le plus lev d'affichage des messages
 *	d'avertissement
 */
#pragma warning( push, 4 )

/*
 *	Dsactivation de l'affichage des messages d'avertissement lis 
 *	l'utilisation de fonctions dprcies par Visual C++ car remplaées
 *	par des fonctions spcifiques plus sres mais non standards
 */
#pragma warning( disable : 4996 )
#endif
/* ------------------------------------------------------------------------ */
/*		C O N S T A N T E S   &   P R O T O T Y P E S						*/
/* ------------------------------------------------------------------------ */
#define MAXLEN          256

/**
 *  \fn void epilogue(void)
 *  \brief      Squelette pour acceuillir un programme quelconcque
 *              avec excution de la fonction epilogue  la fin du
 *              programme
 *  \author     Samir El Khattabi
 *  \date       10 Octobre 2005
 *  \version    1.0
 *  \remark	Le code source a été transféré ici, pour améliorer la lisibilité du programme principal.
 */
void epilogue(void)
{
    static const char * jour[] = {
            "Dimanche", "Lundi", "Mardi", "Mercredi",
            "Jeudi", "Vendredi", "Samedi"};

    static const char * mois[] = {
            "Janvier", "Fevrier", "Mars"     , "Avril"  , "Mai"     , "Juin"    ,
            "Juillet", "Aout"   , "Septembre", "Octobre", "Novembre", "Decembre",
    };

    time_t ltime;
    struct tm * today;
    char userName[MAXLEN + 1] = "";
    char hostName[MAXLEN + 1] = "";
    unsigned long name_len = MAXLEN + 1;

#if defined (_WIN32)
    WSADATA wsaData;
#endif

    struct hostent * pHostEntry;
    struct in_addr *pinAddr;

#if defined (_WIN32)
    WSAStartup(MAKEWORD(2,2), &wsaData);
#endif

    /*	Nom de l'utilisateur   					                			*/
#if defined (_WIN32)
    GetUserName(userName, &name_len);
#elif defined (__unix__)
    getlogin_r(userName,name_len);
#endif
    printf("\n%-9.9s ", userName);

    /*	Nom de l'ordinateur   								                */
    gethostname(hostName, MAXLEN);

    /* Nom réseau et adresse IP de l'ordinateur								*/
    pHostEntry = gethostbyname(hostName);
    if (pHostEntry != NULL)
    {
        printf("%-13.10s ", pHostEntry->h_name);
        pinAddr = ((struct in_addr *)pHostEntry->h_addr_list[0]);
        if (pinAddr != NULL)
            printf("%s ", inet_ntoa(*pinAddr));
    }

    /*	Date et heure														*/
    tzset();
    time(&ltime);
    today = localtime(&ltime);
    printf("%9s %d %s %4d a %dh %dmn %ds\n",
           jour[today->tm_wday], today->tm_mday,
           mois[today->tm_mon], today->tm_year + 1900,
           today->tm_hour, today->tm_min, today->tm_sec);

#if defined (_WIN32)
    WSACleanup();
#endif
}

/**
 * \fn int noeudValide(const pile_t * ptrPile)
 * \brief Vérifie si le noeud actuel est valide ou non.
 * \param ptrPile pointeur sur la pile représentant le noeud actuel.
 * \return TRUE si le noeud est valide, FALSE sinon.
 * \author Nathan Salez
 * \version 1.0
 * \date 14/09/2018
 */
int noeudValide(const pile_t * ptrPile);


/**
 * \fn unsigned int affiche1Sol (const pile_t * Pile, const char *pMot)
 * \brief Affiche une solution au problème de permutations.
 * \param Pile la pile représentant le noeud actuel.
 * \param pMot pointeur sur le mot initial fourni par l'utilisateur.
 * \return le numéro de la solution indiquée.
 * \todo Prendre en compte les 80 caractères par ligne.
 * \author Nathan Salez
 * \version 1.0
 * \date 14/09/2018
 */
unsigned int affiche1Sol (const pile_t * Pile, const char *pMot);


/**
 * \fn unsigned int permut(pile_t *ptrPile, const char *maChaine)
 * \brief Résoud le problème des permutations d'une chaine de caractères, à l'aide du parcours d'un arbre de recherche de permutations.
 * \param ptrPile pointeur sur une pile
 * \param maChaine pointeur sur une chaine constante.
 * \return le nombre de permutations possibles.
 * \author Nathan Salez
 * \version 1.0
 * \date 14/09/2018
 */
unsigned int permut(pile_t *ptrPile, const char *maChaine);

/**
 * \fn short afficherSautDeLigne(size_t longueurChaine, unsigned int numSolution)
 * \brief Indique s'il faut afficher un espace ou un saut de ligne afin d'avoir un mode affichage console en MAXCARPARLIGNE caractères.
 * \param longueurChaine la longueur de la chaîne de test
 * \param numSolution le numéro de la solution.
 * \return TRUE s'il faut afficher un saut de ligne, FALSE s'il faut afficher un espace.
 * \author Nathan Salez
 * \version 1.0
 * \date 14/09/2018
 */
short afficherSautDeLigne(size_t longueurChaine, unsigned int numSolution);

static unsigned int numeroSolution;


int main(void);



// FONCTIONS DE TEST
/**
 * test de affiche1Sol()
 */
void testAffichageSol();

/**
 * test de NoeudValide()
 */
void testNoeudValide();

#endif //SDA2_TP1_SALEZ_PERMUT_H
