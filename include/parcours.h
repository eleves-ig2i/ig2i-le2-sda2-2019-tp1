/**
 * \file parcours.h
 * \author Nathan Salez
 * \include <string.h> <time.h> "libPile.h"
 * \brief déclaration des fonctions, macrofonctions et macro constantes utilisées pour le parcours d'un arbre de recherche de permutations.
 * \remark constitue un fichier correspondant aux parties 2 et 3 du TP1 de SDA2
 * \version 1.0
 * \date 15/09/2018
 */
#ifndef TP1_PARCOURS_H
#define TP1_PARCOURS_H

#include "libPile.h"
#include <string.h>
#include <time.h>

//MACRO CONSTANTES
#define TRUE 1
#define FALSE 0
#define MAXCAR 20
#define MAXCARPARLIGNE 80


//MACRO FONCTION
/**
 * \def remonterAuPere(pp)
 * \brief Dépile une fois la pile utilisée, pour remonter au père d'un noeud.
 * \param pp pointeur sur une pile
 * \author Nathan Salez
 * \version 1.0
 */
#define remonterAuPere(pp)  pop(pp)


/**
 * \brief Empile la valeur minimale Nmin d'un ensemble de nombres sur la pile.
 * \param pp pointeur sur une pile
 * \remark Partie 2 : Nmin vaut 1 car l'ensemble utilisée est la position dans une chaine de caractère (variant de 1 à strlen(chaine) )
 *         Partie 3 : Nmin vaut toujours 1 car l'ensemble utilisée est la totalité des colonnes de l'échiquier (A => 1, B => 2 etc..)
 * \author Nathan Salez
 * \version 1.0
 */
#define passerAuPremierFils(pp) push(pp,1)


/**
 * \brief Prédicat testant si un noeud est terminal.
 * \param pp pointeur sur une pile
 * \param nbElt nombre d'éléments de l'ensemble utilisée.
 * \remark Partie 2 : nbElt vaut strlen(chaine) /// Partie 3 : nbElt est égale à la taile de l'échiquier.
 * \author Nathan Salez
 * \version 1.0
 */
#define noeudTerminal(pp,nbElt) pp->sommet==nbElt


/**
 * \brief Prédicat testant le cas où la recherche est terminée, à l'aide de la fonction is_empty de la bibliothèque libPile
 * \param pp pointeur sur une pile
 * \author Nathan Salez
 * \version 1.0
 */
#define rechercheTerminee(pp) is_empty(pp)


/**
 * \def naPlusDeFrere(pp,nbElt)
 * \brief Prédicat testant si le noeud actuel n'a plus de frère, en effectuant la comparaison entre la dernière valeur empilée et nbElt.
 * \param pp pointeur sur une pile
 * \param nbElt nombre d'éléments de l'ensemble utilisée.
 * \remark Partie 2 : nbElt vaut strlen(chaine) /// Partie 3 : nbElt est égale à la taile de l'échiquier.
 * \author Nathan Salez
 * \version 1.0
 */
#define naPlusDeFrere(pp,nbElt) sommet(pp)==nbElt

/**
 * \def recupererTempsChrono(temps)
 * \brief Macrofonction affectant temps, une valeur à utiliser pour obtenir la durée de la recherche.
 * \param temps , de type clock_t
 * \remark A la fin de la recherche, utiliser le rapport (tempsFin-tempsDebut)/CLOCKS_PER_SEC permet d'obtenir cette durée.
 * \author Nathan Salez
 * \version 1.0
 * \date 14/09/2018
 */
#define recupererTempsChrono(temps) temps = clock();

// FONCTIONS


/**
 * \def passerAuFrereSuivant(ptrPile)
 * \brief Permet de passer au frère suivant dans un arbre de recherche.
 * \param ptrPile pointeur sur la pile représentant le noeud actuel.
 * \author Nathan Salez
 * \version 1.0
 * \date 14/09/2018
 */
#define passerAuFrereSuivant(ptrPile) push(ptrPile,pop(ptrPile)+1)



#endif //TP1_PARCOURS_H
