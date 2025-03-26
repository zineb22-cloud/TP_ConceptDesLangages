#include "pile.h"
#include <stdlib.h>
#include <stdio.h>
// Initialisation de la pile
myPile initPile(int taille) {
    myPile P;
    P.taille = taille;
    P.sommet = 0;
    P.pile = (int *)malloc(taille * sizeof(int));
    if (P.pile == NULL) {
        printf("Erreur d'allocation mémoire !\n");
        exit(1);
    }
    return P;
}

// Verifie si la pile est vide
int estVide(myPile P) {
    return P.sommet == 0;
}

// Verifie si la pile est pleine
int estPleine(myPile P) {
    return P.sommet == P.taille;
}

// Empiler un element
void empiler(myPile *P, int valeur) {
    if (estPleine(*P)) {
        //Verifie d'abord si la pile est pleine.
        printf("Erreur : Pile pleine !\n");
        return;
    }
    P->pile[P->sommet] = valeur;
    P->sommet++;
}

int sommet(myPile P){
    if (estVide(P)){
        printf("Erreur: Pile Vide\n");
        return -1;
    }
    return P.pile[P.sommet - 1];
}

// Depiler un element
int depiler(myPile *P) {
    if (estVide(*P)) {
        printf("Erreur : Pile vide !\n");
        return -1;
    }
    P->sommet--;
    return P->pile[P->sommet]; //retourne la valeur de l'element supprimer
}

// Liberer la memoire de la pile
void libererPile(myPile *P) {
    free(P->pile);
}
void renverserListe(int *Liste,int taille){
    myPile P = initPile(taille);
    for (int i = 0; i<taille; i++){
        empiler(&P,Liste[i]);
    }
    printf("Liste renverser: \n");

    while (!estVide(P)){
        printf("%d ",depiler(&P));
    }
    libererPile(&P);
}

