/* ---------------------------------------------------------------------------- */
/*  pile.c                                                                      */
/*                  Contient les fonctions associées à la pile                  */
/* ---------------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include "pile.h"
#include "file.h"


char inverserPile(pile_t * pile) {
    char     codeErreur = 1;
    int      i          = 0;                 /*Compteur*/
    typePile     valeur     = 0;                 /*Valeur d'entrée/sortie de la pile ou file*/
    int      nbElems    = pile->sommet + 1;  /*Nombre d'elements dans la pile, à inverser*/
    file_t * file       = initFile(nbElems); /*File temporaire permettant d'inverser la pile*/

    /* Inversion de la pile */
    if (file != NULL) {
        /* On vide la pile, on rempli la file */
        for (i=0; i<nbElems; i++) {
            codeErreur = depiler(pile, &valeur);
            codeErreur = enfiler(file, valeur);
        }

        /* On vide la file, on rempli la pile */
        for (i=0; i<nbElems; i++) {
            codeErreur = defiler(file, &valeur);
            codeErreur = empiler(pile, valeur);
        }

        /* La pile est alors inversée */
        printf("La pile est inversée\n");

        libererFile(file);
    }

    return codeErreur;
}


pile_t * initPile(int capacite) {

    /* Allocation de la pile */
    pile_t * pile = (pile_t*) malloc(sizeof(pile_t));

    if (pile != NULL) { 
        (*pile).base = NULL;

        /* Allocation de la base de la pile */
        (*pile).base = (typePile*)malloc(capacite*sizeof(typePile));
        
        if ((*pile).base != NULL) {
            (*pile).capacite = capacite;
            (*pile).sommet = -1;

        } else {    /* Si l'allocation c'est pas faite, on libère la pile */
            free(pile);     
            pile = NULL;
        }
    }
    return pile;
}


void libererPile(pile_t * pile) {
    /* On libère la base */
    free((*pile).base);
    /* On libère la pile */
    free(pile);
    pile = NULL;
}


int estVidePile(pile_t * pile) {
    return (*pile).sommet == -1;
}


int estPleinePile(pile_t * pile) {
    return (*pile).capacite == (*pile).sommet + 1;
}


int empiler(pile_t * pile, typePile v) {
    int codeErreur = 1;

    /* Si la pile est pleine, on redimensionne, sinon, on empile */
    if (estPleinePile(pile)) {

        /* + 1 pour le cas ou la capacite vaut 1 */
        int nvCapacite = 1.5*(*pile).capacite + 1;

        /* Si le redimensionnement a fonctionne, on empile la valeur */
        if (!redimensionerPile(pile, nvCapacite))
            codeErreur = empiler(pile, v);

    } else {
        codeErreur = 0;
        (*pile).sommet ++;
        (*pile).base [(*pile).sommet] = v;
    }

    return codeErreur;
}


int depiler(pile_t * pile, typePile * v) {
    int codeErreur = 1;
    
    /* Si la pile est non vide, on depile */
    if (!estVidePile(pile)) {
        codeErreur = 0;
        *v = (*pile).base [(*pile).sommet];
        (*pile).sommet --;

        /* Si la pile est tres peu utilise, on diminue la taille */
        if ((*pile).sommet < (int)0.25*(*pile).capacite) {
            int nvCapacite = 0.5*(*pile).capacite + 1;
            redimensionerPile(pile, nvCapacite);
        }
    }

    return codeErreur;
}


int redimensionerPile(pile_t * pile, int nvCapacite) {
    int codeErreur = 1;

    /* On realloc la base */
    typePile * nvBase = realloc((*pile).base, nvCapacite*sizeof(typePile));
    if (nvBase != NULL) {
        codeErreur = 0;
        /* Si l'allocation c'est bien faite, on modifie la base et la capacite */
        (*pile).base = nvBase;
        (*pile).capacite = nvCapacite;
    }
    return codeErreur;
}


void afficherPile(pile_t * pile, void (*pfAfficher) (typePile)) {

    printf("Pile : capacite=%d\n", (*pile).capacite);
    printf("       ");
    
    if(!estVidePile(pile)) {
        /* On affiche chaque element un par un en appellant la fonction d'afichage */
        for (int i=0; i <=(*pile).sommet; i++)
            (*pfAfficher) ( (*pile).base[i] );
    } else {
        printf("vide");
    }

    printf("\n");
}


void afficherPileInt(int nombre) {
    printf("%d ", nombre);
}


void afficherPileChar(char caractere) {
    printf("%c ", caractere);
}


void afficherPileChaineCarac(char * chaine) {
    printf("%s ", chaine);
}
