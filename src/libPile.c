/**
 * \file libPile.c
 * \author Nathan Salez
 * \include "libPile.h"
 * \brief code source des fonctions de la bibliothèque de TAD de gestion de piles
 * \remark constitue un fichier correspondant à la partie 1 du TP1 de SDA2
 * \version 1.0
 * \date 13/09/2018
 */
#include "libPile.h"


void init(pile_t *ptrPile)
{
    ptrPile->sommet = 0;
    ptrPile->data = (elt_t*) malloc( SEUIL_ALLOCATION*sizeof(elt_t) );
    assert(ptrPile->data != NULL);
}


short is_empty( const pile_t * ptrPile)
{
    return ptrPile->sommet == 0;   // si la pile est vide, alors sommet == 0, et on retourne 1
}


elt_t pop(pile_t *ptrPile)
{
    assert( ! is_empty(ptrPile) );
    elt_t rtrnValue = ptrPile->data[--ptrPile->sommet];

    if( (ptrPile->sommet + 1)%SEUIL_LIBERATION == 0 )
    //Lorsqu'on passe de SEUIL_LIBERATION éléments à SEUIL_LIBERATION-1, on réalloue la mémoire (on en libère)
    {
        ptrPile->data = (elt_t*) realloc(ptrPile->data, (ptrPile->sommet+1)*sizeof(elt_t) );
        assert( ptrPile->data != NULL);
    }

    return rtrnValue;
}



void push(pile_t *ptrPile, elt_t e)
{
    if( (ptrPile->sommet+1)%SEUIL_ALLOCATION == 0 )
    // LOrsqu'on passe de SEUIL_ALLOCATION-1 à SEUIL_ALLOCATION, on réalloue la mémoire (on en ajoute)
    {
        ptrPile->data = (elt_t*) realloc(ptrPile->data, (ptrPile->sommet+1+SEUIL_ALLOCATION)*sizeof(elt_t) );
        assert( ptrPile->data != NULL);
    }

    ptrPile->data[ptrPile->sommet] = e;   // on incrémente sommet après l'opération.
    ptrPile->sommet++;
}


void printInfoPile(pile_t pile)
{
    printf("Informations de la pile : taille = %zu & sommet = %d\n\n",pile.sommet*sizeof(elt_t), sommet(&pile) );    // afficher un size_t <=> %zu
}


void printPile(pile_t pile)
{
    if( is_empty(&pile) )
    {
        printf("La pile est vide !\n");
    }
    else {
        for (int i = pile.sommet-1; i >= 0; i--)
        {
            afficherElt( *(pile.data+i) );  // <===> pile.data[i]
        }
    }
}


elt_t sommet(const pile_t * ptrPile)
{
    assert( !is_empty(ptrPile) );
    return *(ptrPile->data+ptrPile->sommet-1);
}


elt_t valeurSommet (const pile_t * ptrPile, unsigned int i)
{
    assert(0<i && i<=ptrPile->sommet);
    return *(ptrPile->data+i-1);
}
