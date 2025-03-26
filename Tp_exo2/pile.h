#ifndef PILE_H_INCLUDED
#define PILE_H_INCLUDED

// Definition de la structure d'une pile
typedef struct {
    int sommet;
    int taille;
    int *pile; // Tableau dynamique
} myPile;

myPile initPile(int taille);
int estVide(myPile P);
int estPleine(myPile P);
void empiler(myPile *P, int valeur);
int depiler(myPile *P);
void libererPile(myPile *P);
void renverserListe(int *Liste,int taille);

#endif // PILE_H_INCLUDED

