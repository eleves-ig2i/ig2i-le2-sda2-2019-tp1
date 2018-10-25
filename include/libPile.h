/**
 * \file libPile.h
 * \author Nathan Salez
 * \include <stdlib.h> <assert.h> "libElt.h"
 * \brief déclaration des fonctions et types de la bibliothèque de TAD de gestion de piles
 * \remark constitue un fichier correspondant à la partie 1 du TP1 de SDA2
 * \version 1.0
 * \date 13/09/2018
 */

#ifndef TP1_LIBPILE_H
#define TP1_LIBPILE_H

#include <stdlib.h>
#include <assert.h>

#include "libElt.h"

#define SEUIL_ALLOCATION 5
#define SEUIL_LIBERATION 10

typedef struct
{
    int sommet;  // nb d'éléments dans la pile
    elt_t * data;
}pile_t;


/**
 * \fn void init(pile_t *ptrPile)
 * \brief Initialisation d'une pile : allocation de 5 cases pour data, et sommet vaut 0. Lorsque l'allocation échoue, le programme est arrêté.
 * \remark Il est obligatoire d'utiliser cette fonction avant de manipuler la pile.
 * \param ptrPile pointeur sur une pile_t
 * \author Nathan Salez
 * \version 1.0
 * \date 13/09/2018
 */
void init(pile_t *ptrPile);


/**
 * \fn short is_empty( const pile_t * ptrPile)
 * \brief Vérifie si la pile est vide ou non.
 * \param ptrPile le pointeur sur la pile concernée.
 * \return Retourne 1 si la pile est vide, 0 sinon.
 * \author Nathan Salez
 * \version 1.1
 * \date 14/09/2018
 */
short is_empty( const pile_t * ptrPile);

/**
 * \fn elt_t pop(pile_t *ptrPile)
 * \brief dépile une fois la pile en paramètre, si cette dernière n'est pas vide. Sinon, le programme est arrêté.
 * \remark On suppose que la pile ne contient que des entiers positifs.
 * \param ptrPile pointeur sur une pile_t
 * \return l'élément dépilé
 * \author Nathan Salez
 * \version 1.0
 * \date 13/09/2018
 */
elt_t pop(pile_t *ptrPile);


/**
 * \fn void push(pile_t *ptrPile, elt_t e)
 * \brief empile le 2e argument sur la pile représenté par le 1er argument. Si l'empilation échoue, le programme est arrêté.
 * \param ptrPile pointeur sur une pile_t
 * \param e le elt_t à empiler
 * \author Nathan Salez
 * \version 1.0
 * \date 13/09/2018
 */
void push(pile_t *ptrPile, elt_t e);


/**
 * \fn void printInfoPile(pile_t pile)
 * \brief Affiche la taille d'une pile, et l'élément de son sommet.
 * \param pile, dont les caractéristiques sont à montrer
 * \author Nathan Salez
 * \version 1.0
 * \date 13/09/2018
 */
void printInfoPile(pile_t pile);


/**
 * \fn void printPile(pile_t pile)
 * \brief Affiche le contenu de la pile. (Son sommet est affiché en haut)
 * \param pile La pile à afficher
 * \author Nathan Salez
 * \version 1.0
 * \date 13/09/2018
 */
void printPile(pile_t pile);


/**
 * \fn elt_t sommet(const pile_t * ptrPile)
 * \brief Retourne le dernier élément de la pile, sans la dépiler.
 * \param ptrPile le pointeur sur la pile concernée.
 * \return Le dernier élément de la pile.
 * \author Nathan Salez
 * \version 1.1
 * \date 14/09/2018
 */
elt_t sommet(const pile_t * ptrPile);


/**
 * \fn elt_t valeurSommet (const pile_t * ptrPile, unsigned int i)
 * \brief Permet d'obtenir la valeur du ième élément empilé. Le programme s'arrête si la pile est vide OU si i < sommet.
 * \remark i appartient à l'intervalle [1;pile.sommet]
 * \param ptrPile le pointeur sur la pile concernée.
 * \param i l'index de l'élément empilé
 * \return le ième élément empilé
 * \author Nathan Salez
 * \version 1.1
 * \date 14/09/2018
 */
elt_t valeurSommet (const pile_t * ptrPile, unsigned int i);






#endif //TP1_LIBPILE_H
