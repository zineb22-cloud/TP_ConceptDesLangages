#ifndef FARAH_LISTE_INT_H
#define FARAH_LISTE_INT_H

typedef struct maillon_int {
    int val;
    struct maillon_int *p_suiv;
} maillon_int;

// Déclaration des fonctions
maillon_int* init_elt();
void afficheListe(maillon_int *p_tete);
void ajout_tete_v2(maillon_int **p_tete, maillon_int *nouveau);
void inserer2(maillon_int **p_tete, maillon_int *nouveau);
void supprimer_debut(maillon_int **p_tete);
void supprimer_elt(maillon_int **p_tete, int valeur);
void detruire_liste(maillon_int **p_tete);
void sauver_liste(maillon_int *p_tete);
maillon_int* load_liste();

#endif

