/* -------------------------------------------------------------------------- */
/* Nom du fichier : arbre.c                                                   */
/* Date de creation : Avril 2020                                              */
/* Auteurs : Cavani Nicolas et Leduque Adrien (G31)                           */
/* Objectif : Manipuler les arbres                                            */
/* -------------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include "pilefile/pile.h"
#include "arbre.h"
#include "fctChaines.h"


/*════════════════════════════════════════════════════════════════════════════*/
/* ------------- Fonctions de création de la notation algébrique ------------ */
/*════════════════════════════════════════════════════════════════════════════*/


char * recupNotaAlgebrique(char * filename) {
	FILE * file = fopen(filename, "r"); /* Fichier contenant la notation */
	int  taille = 100; /* Taille initiale du tableau contenant la notation */

	char caractere = 0; /* Caractère lu dans le fichier */
	int  i         = 0; /* Compteur pour remplir le tableau */

	/* Tableau contenant la notation algébrique, sa taille peut être agrandit */
	char * notation = (char *)calloc(taille, sizeof(char));;

	/* Si les allocations mémoires sont réussies alors : */
	if (file != NULL && notation != NULL) {

		/* Lire le fichier caractère par caractère */
		do {
			caractere = fgetc(file);

			/* Si le caractère lu est valide, il est mit dans le tableau */
			/* Les caractères spéciaux et les espaces (ascii <32) ne sont pas valides */
			if (caractere >= 33 && caractere <= 126) {

				/* Si le tableau n'est pas assez grand, alors il faut l'aggrandir */
				/* Dans agrandireChaine, Si l'aggrandissement n'est pas possible, */
				/* le tableau est libéré et notation vaut NULL */
				if (i == taille - 2) {
					agrandirChaine(&notation, &taille);
				}

				/* Si le tableau n'est pas NULL, le caractère est inséré */
				if (notation != NULL) {
					notation[i] = caractere;
					i++;
				}
			}

		/* Tant qu'on est pas à la fin du fichier et que notation existe */
		} while (caractere != EOF && notation != NULL);

		/* Ajout du caractère de fin de chaine et libération de l'espace mémoire non utilisé situé après */
		notation[i] = '\0';
		ecoTailleChaine(&notation, i+1);

		/* Ferme le fichier */
		fclose(file);
	}
	/* Retourne le tableau contenant la notation ou NULL */
	return notation;
}



/*════════════════════════════════════════════════════════════════════════════*/
/* ------------ Fonctions de création et de traitement de l'arbre ----------- */
/*════════════════════════════════════════════════════════════════════════════*/


elemArbre_t * creerElemArbre() {
	/* Alloue de la mémoire pour un élément de l'arbre */
	elemArbre_t * elemArbre = (elemArbre_t *)malloc(sizeof(elemArbre_t));

	/* Si l'allocation mémoire est réussie alors les champs fils et frere sont initialisés: */
	if (elemArbre != NULL) {
		elemArbre->valeur = '0';
		elemArbre->fils = NULL;
		elemArbre->frere = NULL;

	} else {
		printf("Erreur mémoire lors de l'allocation d'un nouvel élément\n");
	}

	/* Retourne l'élément initialisé ou NULL */
	return elemArbre;
}


elemArbre_t * creerArbreNotaAlgebrique(char * notation) {
	int i          = 0; /* Compteur pour parcourir notation et remplir l'arbre */
	int codeErreur = 0; /* Code d'erreur, 0 si pas d'erreur, 1 sinon */
	int taille     = tailleChaine(notation); /* Taille du tableau notation */
	elemArbre_t * arbre = NULL;

	if (notation[0] != '\0') {

		pile_t * pileArbre = initPile(taille/2); /* Pile utilisée pour parcourir l'arbre */

		/* Le premier élément de l'arbre est créé, et empilé */
		arbre = creerElemArbre();
		elemArbre_t * cour = arbre; /* Pointeur courant pour parcourir l'arbre */
		elemArbre_t * nouvElem = NULL; /* Pointeur sur les nouveaux éléments de l'arbre */
		empiler(pileArbre, cour);

		/* Si les allocations mémoires ont réussies alors : */
		if (arbre != NULL && pileArbre != NULL) {

			/* Tant qu'on a pas finit (fin de notation) et pas d'erreur */
			while (notation[i] != '\0' && codeErreur == 0) {

				/* 'x', donc un fils suivera automatiquement, il faut creer 
				un nouvel élément fils et se placer dessus */
				if (notation[i] == '*') {

					nouvElem = creerElemArbre();
					if (nouvElem != NULL) {
						cour->fils = nouvElem;
						cour = nouvElem;

					/* Erreur si la création de l'élément est impossible */
					} else {
						codeErreur = 1;
					}

				/* '+', donc un frère suivera automatiquement, il faut créer
				un nouvel élément frère et se placer dessus. Dans le cas ou cet élément
				à des fils et des freres, il faudra revenir dessus plus tard, alors on
				l'empile */
				} else if (notation[i] == '+') {

					depiler(pileArbre, &cour);
					nouvElem = creerElemArbre();

					if (nouvElem != NULL) {
						cour->frere = nouvElem;
						cour = nouvElem;
						empiler(pileArbre, cour);

					/* Erreur si la création de l'élément est impossible */
					} else {
						codeErreur = 1;
					}

				/* '(', donc une suite de frères va suivre, on empile le premier pour
				y revenir dans le futur */
				} else if (notation[i] == '(') {
					empiler(pileArbre, cour);

				/* ')', donc la suite de frères est terminée, on dépile pour revenir sur
				l'élément précédent cette suite */
				} else if (notation[i] == ')') {
					depiler(pileArbre, &cour);

				/* Si aucun opérateurs liés à la notation algébrique n'est lu précédement, alors
				il s'agit de la valeur du dernier élément créé, donc on la place dans l'arbre */
				} else {
					cour->valeur = notation[i];
				}

				/* Incrémente ce compteur pour avancer dans la lecture de notation */
				i++;
			}

			/* Il faut libérer la mémoire utilisée par la pile */
			libererPile(pileArbre);

			/* Et libérer ce qui a été créé de l'arbre si une erreur c'est produite */
			if (codeErreur == 1) {
				libererArbre(&arbre);
			}

		}
	}

	/* Retourner l'arbre ou NULL */
	return arbre;
}


elemArbre_t * rechercherValeur(elemArbre_t * arbre, char valeur) {
	char fin    = 0; /* Booléen, 1 actions finies, 0 on continue */
	char trouve = 0; /* Booléen, 1 la valeur est trouvée, 0 sinon */

	elemArbre_t * cour = arbre; /* Pointeur courant parcourant l'arbre */
	pile_t * pileArbre = initPile(10); /* Pile utilisée pour parcourir l'arbre */


	/* Si l'allocation mémoire est réussie alors : */
	if (pileArbre != NULL) {

		/* Tant qu'on a pas finit faire : */
		while (!fin) {

			/* Parcours en profondeur de l'arbre, on descend le plus possible
			dans les fils ou tant qu'on a pas trouvé la valeur */
			while (cour != NULL && !trouve) {

				/* Vérification de la valeur, si on la trouve en descendant */
				if (cour->valeur == valeur) {
					trouve = 1;

				/* Sinon on empile l'élément pour y revenir plus tard et parcourir
				ses frères et on descend dans les fils */
				} else {
					empiler(pileArbre, cour);
					cour = cour->fils;
				}
			}

			/* Si la pile n'est pas vide (l'arbre n'est pas finit d'être parcouru)
			et qu'on a pas trouvé la valeur, on dépile un élément et on se place sur son frère */
			if (!estVidePile(pileArbre) && !trouve) {
				depiler(pileArbre, &cour);
				cour = cour->frere;

			/* Sinon le parcours de l'arbre est terminé */
			} else {
				fin = 1;
			}
		}

		/* Il faut libérer la mémoire utilisée par la pile */
		libererPile(pileArbre);
	}

	/* Si l'élément n'a pas été trouvé, message d'erreur et cour prend NULL */
	if (!trouve) {
		printf("La valeur n'a pas été trouvée\n");
		cour = NULL;
	}

	/* Retourne cour, pointant sur l'élément contenant la valeur recherchée ou
	NULL si elle n'a pas été trouvée */
	return cour;
}


char insererFils(elemArbre_t * arbre, char valeurPere, char nouvValeur) {
	char codeErreur = 0; /* Code d'erreur, 0 si pas d'erreur, 1 sinon*/

	/* Pointeur sur le nouvel élément à insérer */
	elemArbre_t * nouvElem = creerElemArbre();

	/* Si l'allocation mémoire est réussie alors : */
	if (nouvElem != NULL) {
		/* On rempli le champ valeur de l'élément */
		nouvElem->valeur = nouvValeur;

		/* On effectue la recherche du père du nouvel élément à insérer */
		/* cour est le pointeur courant parcourant les fils de l'élément trouvé */
		elemArbre_t * cour = rechercherValeur(arbre, valeurPere);

		/* Si la recherche a aboutie */		
		if (cour != NULL) {

			/* prec est le pointeur précédent cour, la où il faudra insérer le nouvel élément */
			/* Au debut, on considère que cour n'a pas de fils */
			elemArbre_t ** prec = &(cour->fils);
			cour = cour->fils;

			/* Si cour a un fils, il faut se placer sur le dernier frère avant
			d'insérer le nouvel élément */
			if (cour != NULL) {

				/* On se place sur le bon frère avant l'insertion (ordre alphabetique) */
				while (cour != NULL && cour->valeur < nouvValeur) {
					prec = &(cour->frere);
					cour = cour->frere;
				}

			}
			/* On insère le nouvel élément dans l'arbre et on replace le pointeur
			sur la suite des frères*/
			*prec = nouvElem;
			nouvElem->frere = cour;

		/* La recherche n'a pas aboutie, on libère le nouvel élément */
		} else {
			free(nouvElem);
			codeErreur = 1;
		}

	/* L'allocation du nouvel élément n'a pas aboutie */
	} else {
		codeErreur = 1;
	}

	/* Retourne le code d'erreur */
	return codeErreur;
}


char libererArbre(elemArbre_t ** arbre) {
	char fin        = 0; /* Booléen, 1 actions finies, 0 on continue */
	char codeErreur = 0; /* Code d'erreur, 0 si pas d'erreur, 1 sinon */


	elemArbre_t * prec = *arbre; /* Pointeur précédent cour */
	elemArbre_t * cour = *arbre; /* Pointeur courant parcourant l'arbre */
	pile_t * pileArbre = initPile(10); /* Pile utilisée pour parcourir l'arbre */


	/* Si l'allocation de la pile à réussie alors : */
	if (pileArbre != NULL) {

		/* Tant qu'on a pas finit les actions */
		while (!fin) {

			/* Parcours en profondeur de l'arbre, on descend le plus possible
			dans les fils */
			while (cour != NULL) {
				empiler(pileArbre, cour);
				cour = cour->fils;
			}

			/* Si la pile n'est pas vide (l'arbre n'est pas finit d'être parcouru),
			on dépile un élément et on se place sur son frère.
			Puisque tous les éléments de l'arbre rentrent dans la pile, on peut
			les libérer au fur et à mesure que l'on dépile */
			if (!estVidePile(pileArbre)) {
				depiler(pileArbre, &cour);
				prec = cour;
				cour = cour->frere;
				free(prec);

			/* Si la pile est vide, on a terminé le parcours */
			} else {
				fin = 1;
			}
		}

		/* Il faut libérer la mémoire utilisée par la pile */
		libererPile(pileArbre);

	/* Si la pile n'a pas pu être alloué, erreur */
	} else {
		codeErreur = 1;
	}

	/* L'arbre est alors vide */
	(*arbre) = NULL;

	/* Retourne le code erreur */
	return codeErreur;
}
