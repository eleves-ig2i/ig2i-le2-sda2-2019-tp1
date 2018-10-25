/**
* \file dames.c
* \include "dames.h"
* \brief Contient le code source du programme recherchant toutes les permutations possibles répondant au problème des huits dames (cf sujet TP)
* \remark constitue un fichier correspondant à la partie 3 du TP1 de SDA2
* \author Nathan Salez
* \version 1.0
* \date 15/09/2018
*/


#include "dames.h"

/* ------------------------------------------------------------------------ */
/*		F O N C T I O N     P R I N C I P A L E 		    */
/* ------------------------------------------------------------------------ */
int main(void)
{
    atexit(epilogue);

    int choixContinuer = 0;
    do {
        numeroSolution=0;
        pile_t maPile;
        init(&maPile);

        // Variables utiles pour obtenir la durée de la recherche.
        clock_t tempsDebut, tempsFin;
        float temps;

        int tailleEchiquier;
        do {
            printf("Taille de l'échiquier (entre 4 et 15) : ");
            scanf("%d", &tailleEchiquier);
        } while (tailleEchiquier > 15 || tailleEchiquier < 4);

        int choixAffichage;
        do {
            printf("Choix de l'affichage :\n\t1 : Notation échiqueenne\n\t2 : Affichage pseudo-graphique\n\t3 : Pas d'affichage de solution.\n");
            printf("Votre choix : ");
            scanf("%d", &choixAffichage);
        } while (choixAffichage > finEnum || choixAffichage < 0);
        choixAffichage--;

        if( choixAffichage != aucun)
            printf("Permutations possibles :\n");

        recupererTempsChrono(tempsDebut);
        printf("Nombre de solutions : %lu\n", permut(&maPile, tailleEchiquier, choixAffichage));
        recupererTempsChrono(tempsFin);

        temps = (float) (tempsFin - tempsDebut) / CLOCKS_PER_SEC;
        printf("durée de recherche = %f secondes.\n", temps);

        free(maPile.data);

        printf("Tapez 0 pour arrêter, Tapez un autre nombre pour continuer.\n");
        scanf("%d",&choixContinuer);

    }while(choixContinuer != 0);

#if (0)
    testAffichageSol();
    testNoeudValide();
#endif


    return 0;
}

/* ------------------------------------------------------------------------ */


int noeudValide(const pile_t * ptrPile) {

    if( is_empty(ptrPile) )     // On se trouve au début de la recherche => le noeud est forcément valide.
    {
        return TRUE;
    }

    elt_t derniereValeurEntree = sommet(ptrPile);

    for(unsigned int i = ptrPile->sommet-1; i>0; i--)   // Pire des cas : la pile contient un élément <=> sommet = 1 donc i = 0
    {
        elt_t valeurAux = valeurSommet(ptrPile,i);
        if( valeurAux == derniereValeurEntree )     // Un doublon a été trouvé, le noeud n'est pas valide.
        {
            return FALSE;
        }

        // PARTIE 3 :
        // On détermine si les 2 pièces concernées ne sont pas dans la même diagonale.
        // Pour cela, la valeur absolue de la différence des valeurs (A,B,C,D pour un échiquier de taille 4 par exemple)
        // ne doit pas être égale à la différence de leur index (0,1,2,3)
        if ( abs( derniereValeurEntree - valeurAux ) == ptrPile->sommet - i)
        {
            return FALSE;
        }
    }

    return TRUE;
}




long unsigned int permut(pile_t *ptrPile, int tailleEchiquier, int choixAffichage) {

    assert(0 <= choixAffichage && choixAffichage < finEnum);

    int noeudterminal;

    do {
        // 1) Tant que le noeud courant est valide
        noeudterminal=FALSE;
        while( noeudValide(ptrPile) && noeudterminal == FALSE ) {

            // si c'est un noeud terminal
            if ( noeudTerminal(ptrPile, tailleEchiquier) ) {
                switch(choixAffichage)
                {
                    case normal :
                        numeroSolution = afficherSolNormal(ptrPile,tailleEchiquier);
                        break;

                    case graphique :
                        numeroSolution = afficherSolGraphique(ptrPile,tailleEchiquier);
                        break;

                    case aucun :
                        numeroSolution++;
                        break;

                    default: return 0;
                }
                noeudterminal = TRUE;
            }
                //si c'est pas un noeud terminal
            else {
                passerAuPremierFils(ptrPile);
            }
        }
        // 2) Tant que la recherche n'est pas terminée et noeud courant n'a plus de freres
        while( rechercheTerminee(ptrPile) == 0 && naPlusDeFrere(ptrPile,tailleEchiquier) ) {
            remonterAuPere(ptrPile);
        }

        //3) Si la recherche n'est pas terminée
        if ( rechercheTerminee(ptrPile) == 0 ) {
            passerAuFrereSuivant(ptrPile);
        }
    }while( !rechercheTerminee(ptrPile) );

    return numeroSolution;
}


unsigned int afficherSolNormal(const pile_t * ptrPile, int tailleEchiquier)
{
    assert( ptrPile->sommet == tailleEchiquier );    //On vérifie que pPile contient autant d'éléments que la taille de l'échiquier.

    for(unsigned int i = 1; i <= ptrPile->sommet; i++)
    {
        printf("%c%u", valeurSommet(ptrPile,i)+'a'-1,i );   // Pour c1 : affiche <3 + 'a' -1>1
        // Rappel : on travaille sur une pile d'entiers (1 vaut 'a', 2 vaut 'b', 3 vaut 'c')
    }


    numeroSolution++;

    // On affiche un espace ou un saut de ligne ?
    // ON dispose de : numeroSolution, MAXCARPARLIGNE. et de tailleEchiquier
    if( afficherSautDeLigne( (size_t)tailleEchiquier*2, numeroSolution) )   // Exemple : echiquier de 4 cases => on écrit une chaine de 8 caractères.
    {
        printf("\n");
    }
    else
    {
        printf(" ");    // pour séparer les mots.
    }
    return numeroSolution;
}


short afficherSautDeLigne(size_t longueurChaine, long unsigned int numSolution)
{
    size_t nbDeMotsParLigne = MAXCARPARLIGNE/(longueurChaine+1);    // Exemple : MAXCARPARLIGNE = 20, longueurChaine = 5 => on peut mettre 3 mots par ligne.
    if( numSolution%nbDeMotsParLigne == 0 )     // Si on est au 3e, 6e, 9e mot à afficher, alors on saute une ligne.
    {
        return TRUE;
    }
    else {
        return FALSE;
    }
}


unsigned int afficherSolGraphique(const pile_t * ptrPile, int tailleEchiquier)
{
    printf("Solution %lu :\n",++numeroSolution);

    // Première ligne : On écrit les lettres de colonnes :
    printf("  ");
    for(int i = 1; i <= tailleEchiquier; i++)
    {
        TABULATION();
        printf("%c",i+'A'-1);
    }
    SAUTDELIGNE();

    //On met la première ligne juste en dessous
    afficherLigne(tailleEchiquier);
    SAUTDELIGNE();

    //On effectue <tailleEchiquier> itérations à présent.
    for(int i = 1; i<= tailleEchiquier; i++)
    {
        printf("%d  |",i);
        for(int j=1; j<=tailleEchiquier;j++)
        {
            printf(" ");

            if( valeurSommet(ptrPile,i) == j)   // Exemple : pour la solution b1d2a3c4, dans la 1ere ligne, on affiche R à la 2e itération.
            {
                printf("R");
            }
            else
            {
                printf(" ");
            }
            printf(" |");
        }
        SAUTDELIGNE();

        afficherLigne(tailleEchiquier);
        SAUTDELIGNE();
    }


    return numeroSolution;
}


void afficherLigne(int tailleEchiquier)
{
    TABULATION();
    printf("+");
    for(int i = 1; i<= tailleEchiquier; i++)
    {
        printf("---+");
    }
}



void testNoeudValide()
{
    pile_t maPile;
    init(&maPile);

    int tailleEchiquier = 4;
    printf("Taille d'échiquier choisie : %d",tailleEchiquier);

    printf("On remplit la pile avec la solution suivante (bonne) : b1d2a3c4\n");
    push(&maPile,2);    // b1
    push(&maPile,4);    // d2
    push(&maPile,1);    // a3
    push(&maPile,3);    // c4
    printf("Pile obtenue :\n");
    printPile(maPile);
    printf("Noeud valide = %d\n",noeudValide(&maPile) );
    free(maPile.data);


    tailleEchiquier = 5;
    printf("Taille d'échiquier choisie : %d",tailleEchiquier);

    printf("On modifie la pile pour avoir la solution suivante (mauvaise) : e1a2c3\n");
    init(&maPile);
    push(&maPile,5);    //e1
    push(&maPile,1);    //a2
    push(&maPile,3);    //c3
    printf("Pile obtenue :\n");
    printPile(maPile);
    printf("Noeud valide = %d\n",noeudValide(&maPile) );
    free(maPile.data);
}