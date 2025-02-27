/* ---------------------------------------------------------------------------- */
/*  pile.h                                                                      */
/*          Contient les déclarations des fonctions du fichiers pile.c          */
/* ---------------------------------------------------------------------------- */

#ifndef PILE
#define PILE

#include "../arbre.h"
/* ------------ */
/* Type utilisé */
/* ------------ */
typedef elemArbre_t * typePile;


/* -------------------- */
/* Structure de la pile */
/* -------------------- */
typedef struct pile {
    int        capacite;
    int        sommet;
    typePile * base;
} pile_t;


/* -------------------------------------------------------------- */
/* inverserPile     Inverse la pile passée en paramètre           */
/*                                                                */
/* En entrée :  pile (pile *) : Pile à inverser                   */
/*                                                                */
/* En sortie :  codeErreur (char) booléen : 1 si erreur, 0 sinon  */
/* -------------------------------------------------------------- */
char inverserPile(pile_t * pile);


/* -------------------------------------------------------------- */
/* initPile     Initialise une pile de taille le paramètre taille */
/*                                                                */
/* En entrée :  taille (int) : Taille de la pile                  */
/*                                                                */
/* En sortie :  pile : pointeur sur la pile (pile_t *)            */
/* -------------------------------------------------------------- */
pile_t * initPile(int);

/* --------------------------------------------------------------------- */
/* EstVidePile  Indique si la pile passée en paramètre est vide ou non   */
/*                                                                       */
/* En entrée :  pile (pile_t *) : Pile à tester                          */
/*                                                                       */
/* En sortie :  (int) booléen : 1 si la pile est vide, 0 sinon           */
/* --------------------------------------------------------------------- */
int estVidePile(pile_t *);

/* ------------------------------------------------------------------------- */
/* estPleinePile  Indique si la pile passée en paramètre est pleine ou non   */
/*                                                                           */
/* En entrée :  pile (pile_t *) : Pile à tester                              */
/*                                                                           */
/* En sortie :  (int) booléen : 1 si la pile est pleine, 0 sinon             */
/* ------------------------------------------------------------------------- */
int estPleinePile(pile_t *);

/* ------------------------------------------------------------------ */
/* empiler      Empile une valeur au sommet de la pile,               */
/*                          et l'aggrandit si elle est trop petite    */
/*                                                                    */
/* En entrée :  pile (pile_t *)   : Pile à remplir                    */
/*              valeur (typePile) : Elément à empiler                 */
/*                                                                    */
/* En sortie :  codeErreur (int) booléen : 1 si erreur, 0 sinon       */
/* ------------------------------------------------------------------ */
int empiler(pile_t *, typePile);

/* -------------------------------------------------------------- */
/* depiler      Dépile la valeur au sommet de la pile,            */
/*                          et la réduit si elle peu utilisée     */
/*                                                                */
/* En entrée :  pile (pile_t *)   : Pile à vider                  */
/*              valeur (typePile) : Elément dépilé                */
/*                                                                */
/* En sortie :  codeErreur (int) booléen : 2 si erreur, 0 sinon   */
/* -------------------------------------------------------------- */
int depiler(pile_t *, typePile *);

/* ------------------------------------------------------------ */
/* redimensionerPile    Redimensionne la base de la pile        */
/*                                                              */
/* En entrée : pile (pile_t *) : Pile à redimensionner          */
/*             nvCapacité (int) : Taille de la nouvelle base    */
/*                                                              */
/* En sortie : codeErreur (int) booléen : 1 si erreur, 0 sinon  */
/* ------------------------------------------------------------ */
int redimensionerPile(pile_t *, int);

/* --------------------------------------------------------- */
/* libererPile  Libère la mémoire utilisée par la pile       */
/*                                                           */
/* En entrée :  pile (pile_t *) : Pile à libérer             */
/*                                                           */
/* En sortie :  void                                         */
/* --------------------------------------------------------- */
void libererPile(pile_t *);

/* ---------------------------------------------------------- */
/* afficherPile     Affiche la pile                           */
/*                                                            */
/* En entrée : pile (pile_t *) : Pile à afficher              */
/*             pfAfficher (void (*)(typePile)) : pointeur sur */
/*                       la fonction d'affichage du bon type  */
/* En sortie : void                                           */
/* ---------------------------------------------------------- */
void afficherPile(pile_t *, void (*) (typePile));


/* --------------------------------------------------- */
/* afficherPileInt      Affiche un élément de type int */
/*                                                     */
/* En entrée : nombre (int) : Nombre à afficher        */
/*                                                     */
/* En sortie : void                                    */
/* --------------------------------------------------- */
void afficherPileInt(int);

/* ---------------------------------------------------- */
/* afficherPileChar   Affiche un élément de type char   */
/*                                                      */
/* En entrée : caractere (char) : Caractère à afficher  */
/*                                                      */
/* En sortie : void                                     */
/* ---------------------------------------------------- */
void afficherPileChar(char);

/* --------------------------------------------------------------------------- */
/* afficherPileChaineCarac      Affiche un élément de type chaine de caractère */
/*                                                                             */
/* En entrée : chaine (char *) : Chaine de caractères à afficher               */
/*                                                                             */
/* En sortie : void                                                            */
/* --------------------------------------------------------------------------- */
void afficherPileChaineCarac(char *);


#endif
