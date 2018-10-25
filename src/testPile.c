/**
 * \file testPile.c
 * \brief Code source du programme de test de la bibliothèque libPile
 * \remark constitue un fichier correspondant à la partie 1 du TP1 de SDA2
 * \version 1.0
 * \date 13/09/2018
 * \author Nathan Salez
 */


/* ------------------------------------------------------------------------ */
/*		I N C L U D Es  S T A N D A R Ds									*/
/* ------------------------------------------------------------------------ */

#include <string.h>
#include <math.h>


#include "libPile.h"



#include <time.h>

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
 *  \brief      Squelette pour acceuillir un programme quelconcque
 *              avec excution de la fonction epilogue  la fin du
 *              programme
 *
 *  \author     Samir El Khattabi
 *
 *  \date       10 Octobre 2005
 *
 *  \version    1.0
 *
 *
 *   \remark	ce fichier doit devenir le programme principal
 *				de votre TP (SDA2_TP1_TAD_Pile_Dyn.c, par exemple)
 *
 */
void    epilogue(void);


/**
 *
 * \param choice pointeur sur un int
 */
void printMenuPile(int *choice);


/**
 * \brief Vide le buffer d'entrée
 * \remark A utiliser après chaque saisie d'un int, char.
 *
 */
void viderBuffer();

/* ------------------------------------------------------------------------ */
/*		F O N C T I O N     P R I N C I P A L E 		    */
/* ------------------------------------------------------------------------ */
int main(void)
{
    atexit(epilogue);
    /*  Initialisation du générateur de nombres aléatoires			*/
    srand((unsigned int)time(NULL));

    int choice=0, i=0;
    elt_t element;
    pile_t* maPile;

    printf("Bienvenue dans le programme de test de la bibliothèque libPile. Tapez sur entrée pour continuer.\n\n");

    init(maPile);
    do {
        printMenuPile(&choice);
        switch(choice)
        {
            case 1 :    // Empiler
                printf("Saisissez l'élément à empiler : ");
                saisirElt(&element);
                push(maPile,element);
                printf("L'empilation a réussi !\n");
                printInfoPile(*maPile);
                break;

            case 2 :    // Dépiler
                printf("On dépile la pile.\n");
                element = pop(maPile);
                printf(" Element dépilé : %d\n",element);
                printInfoPile(*maPile);
                break;

            case 3 :    // Afficher la pile
                printPile(*maPile);
                printInfoPile(*maPile);
                break;

            case 4 :    //Obtenir le sommet de la pile
                printf("On récupère l'élément au sommet de la pile.\n");
                printf("Élément récupéré : %d\n",sommet(maPile) );
                printInfoPile(*maPile);
                break;

            case 5 :    //Obtenir le ieme élément de la pile
                printf("On récupère le ième élément de la pile.\n");
                printf("Veuillez saisir i : ");
                scanf("%d",&i);
                element = valeurSommet(maPile,i);
                printf("Ième élément empilé : %d\n",element);
                printInfoPile(*maPile);
                break;


            default : choice = 0;
        }

    }while(choice != 0);


    free(maPile->data);
#if (0)

#endif

    return 0;
}

/* ------------------------------------------------------------------------ */
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


void printMenuPile(int *choice)
{
    printf("Choix possibles :\n");
    printf("1 : Empiler un élément.\n");
    printf("2 : Dépiler un élément.\n");
    printf("3 : Afficher la pile.\n");
    printf("4 : Obtenir le sommet de la pile.\n");
    printf("5 : Obtenir le ième élément de la pile.\n");
    printf("0 : Quitter.\n\n");
    printf("Votre choix : ");
    scanf("%d",choice);

    viderBuffer();
}

void viderBuffer()
{
    int c=0;
    while(c!='\n'&&c!=EOF)
        c=getchar();
}

/* ------------------------------------------------------------- THE END -- */