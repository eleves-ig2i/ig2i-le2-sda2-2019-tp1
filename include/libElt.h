/**
 * \file libElt.h
 * \include <stdio.h>
 * \author Nathan Salez
 * \brief déclaration des fonctions et du TAD utilisé pour les piles.
 * \note le type utilisé actuellement est : int
 * \remark constitue un fichier correspondant à la partie 1 du TP1 de SDA2
 * \version 1.0
 * \date 13/09/2018
 */

#ifndef TP1_LIBELT_H
#define TP1_LIBELT_H

#include <stdio.h>

typedef int elt_t;


void saisirElt(elt_t* e);
void ranger(elt_t* d, elt_t s);
void afficherElt(elt_t e);

#endif //TP1_LIBELT_H
