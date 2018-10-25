/**
* \file permut.c
* \include "permut.h"
* \brief Contient le code source du programme recherchant toutes les permutations possibles d'un mot, et les affichant.
* \remark constitue un fichier correspondant à la partie 2 du TP1 de SDA2
* \author Nathan Salez
* \version 1.0
* \date 14/09/2018
*/


#include "permut.h"

/* ------------------------------------------------------------------------ */
/*		F O N C T I O N     P R I N C I P A L E 		    */
/* ------------------------------------------------------------------------ */
int main(void)
{
    atexit(epilogue);

    pile_t maPile;
    init(&maPile);

    // Variables utiles pour obtenir la durée de la recherche.
    clock_t tempsDebut,tempsFin;
    float temps;

    char chaineTest[MAXCAR];
    printf("Veuillez saisir la chaine de test : ");
    scanf("%s",chaineTest);

    printf("Permutations possibles :\n");
    recupererTempsChrono(tempsDebut);
    printf("Nombre de solutions : %u\n",permut(&maPile,chaineTest));
    recupererTempsChrono(tempsFin);

    temps = (float)(tempsFin-tempsDebut)/CLOCKS_PER_SEC;
    printf("durée de recherche = %f secondes.\n", temps);

#if (0)
    testAffichageSol();
    testNoeudValide();
#endif

    free(maPile.data);
    return 0;
}

/* ------------------------------------------------------------------------ */


int noeudValide(const pile_t * ptrPile) {

    if( is_empty(ptrPile) )     // On se trouve au début de la recherche => le noeud est forcément valide.
    {
        return TRUE;
    }

    elt_t derniereValeurEntree = sommet(ptrPile);
    // On effectue la recherche qu'avec le dernier élément.
    // Si l'on enlevait cet élément, alors le noeud serait automatiquement valide.

    for(unsigned int i = ptrPile->sommet-1; i>0; i--)   // Pire des cas : la pile contient un élément <=> sommet = 1 donc i = 0
    {
        elt_t valeurAux = valeurSommet(ptrPile,i);
        if( valeurAux == derniereValeurEntree )     // Un doublon a été trouvé, le noeud n'est pas valide.
        {
            return FALSE;
        }
    }

    return TRUE;
}




unsigned int permut(pile_t *ptrPile, const char *maChaine) {
    size_t longueurChaine = strlen(maChaine);
    int noeudterminal;
    do {
        // 1) Tant que le noeud courant est valide
        noeudterminal=FALSE;
        while( noeudValide(ptrPile) && noeudterminal == FALSE ) {

            // si c'est un noeud terminal
            if ( noeudTerminal(ptrPile, longueurChaine) ) {
                numeroSolution = affiche1Sol(ptrPile,maChaine);
                noeudterminal = TRUE;
            }
                //si c'est pas un noeud terminal
            else {
                passerAuPremierFils(ptrPile);
            }
        }
        // 2) Tant que la recherche n'est pas terminée et noeud courant n'a plus de freres
        while( rechercheTerminee(ptrPile) == 0 && naPlusDeFrere(ptrPile,longueurChaine) ) {
            remonterAuPere(ptrPile);
        }

        //3) Si la recherche n'est pas terminée
        if ( rechercheTerminee(ptrPile) == 0 ) {
            passerAuFrereSuivant(ptrPile);
        }
    }while( !rechercheTerminee(ptrPile) );

    printf("\n");
  return numeroSolution;
}


unsigned int affiche1Sol (const pile_t * ptrPile, const char *pMot)
{
    assert( ptrPile->sommet == strlen(pMot) );    //On vérifie que pMot contient autant de caractères que pPile d'éléments.

    for(unsigned int i = 1; i <= ptrPile->sommet; i++)
    {
        printf("%c",pMot[ valeurSommet(ptrPile,i) - 1 ] );
        // valeurSommet(....) retourne la position (1...strlen(chaine) du caractère à afficher.
        // Pour avoir la bonne valeur pour la chaine de caractère, on décrémente cette position de 1.
    }


    numeroSolution++;

    // On affiche un espace ou un saut de ligne ?
    // ON dispose de : numeroSolution, MAXCARPARLIGNE, longueurChaine.
    if( afficherSautDeLigne( strlen(pMot), numeroSolution) )
    {
        printf("\n");
    }
    else
    {
        printf(" ");    // pour séparer les mots.
    }
    return numeroSolution;
}


short afficherSautDeLigne(size_t longueurChaine, unsigned int numSolution)
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



void testAffichageSol()
{
    pile_t ptrPile;
    init(&ptrPile);

    char pMot[MAXCAR] = "lacet";
    printf("Mot choisi : '%s'\n",pMot);

    push(&ptrPile,2);
    push(&ptrPile,3);
    push(&ptrPile,4);
    push(&ptrPile,1);
    push(&ptrPile,5);
    printf("Pile choisie :\n");
    printPile(ptrPile);

    printf("Résultat de la fonction affiche1Sol : ");
    affiche1Sol(&ptrPile,pMot);

    printf("\nOn dépile une fois puis on réutilise la fonction d'affichage, pour faire apparaître l'erreur.\n");
    pop(&ptrPile);

    printf("Résultat de la fonction affiche1Sol : ");
    affiche1Sol(&ptrPile,pMot);


    free(ptrPile.data);
}



void testNoeudValide()
{
    pile_t ptrPile;
    init(&ptrPile);

    char pMot[MAXCAR] = "lacet";
    printf("Mot choisi : '%s'\n",pMot);

    printf("On laisse la pile vide dans un premier temps.\n");
    printf("Noeud valide = %u\n",noeudValide(&ptrPile) );

    printf("On remplit la pile de façon à avoir l'unicité des éléments.\n");
    push(&ptrPile,2);
    push(&ptrPile,3);
    push(&ptrPile,4);
    printf("Pile choisie :\n");
    printPile(ptrPile);
    printf("Noeud valide = %u\n",noeudValide(&ptrPile) );

    printf("On ajoute un doublon.\n");
    push(&ptrPile,2);
    printf("Pile choisie :\n");
    printPile(ptrPile);
    printf("Noeud valide = %u\n",noeudValide(&ptrPile) );

}