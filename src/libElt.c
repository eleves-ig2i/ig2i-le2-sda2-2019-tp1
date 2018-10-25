/**
 * \file libElt.c
 * \include "libElt.h"
 * \author Nathan Salez
 * \brief code source des fonctions du TAD utilisé pour les piles.
 * \note le type utilisé actuellement est : int
 * \remark constitue un fichier correspondant à la partie 1 du TP1 de SDA2
 * \version 1.0
 * \date 13/09/2018
 */
#include "libElt.h"

void saisirElt(elt_t *e)
{
    scanf("%d",e);
}


void ranger(elt_t* d,elt_t s)
{
    *d = s;
}


void afficherElt(elt_t e)
{
    printf("----> %d\n",e);
}
