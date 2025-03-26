#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Farahlisteint.h"

maillon_int *init_elt()
{
    maillon_int *p_nv_elt = malloc(sizeof(maillon_int));
    p_nv_elt->val = rand() % 21;
    p_nv_elt->p_suiv = NULL;
    return p_nv_elt;
}

maillon_int *ajout_tete_v1(maillon_int *p_tete, maillon_int *p_nv_elt)
{
    p_nv_elt->p_suiv = p_tete;
    p_tete = p_nv_elt;
    return p_tete;
}

void ajout_tete_v2(maillon_int **p_p_tete, maillon_int *p_nv_elt)
{
    p_nv_elt->p_suiv = *p_p_tete;
    *p_p_tete = p_nv_elt;
}

int ajout_tete_v3(maillon_int **p_p_tete, maillon_int *p_nv_elt)
{
    int errorCode = -1;
    if (p_nv_elt != NULL)
    {
        p_nv_elt->p_suiv = *p_p_tete;
        *p_p_tete = p_nv_elt;
        errorCode = 0;
    }
    return errorCode;
}

void parcourir(maillon_int *p_tete)
{
    if (p_tete == NULL)
        printf("liste vide");
    else
        while (p_tete != NULL)
        {
            printf("%d--", p_tete->val);
            p_tete = p_tete->p_suiv;
        }
    putchar('\n');
}

maillon_int *inserer1(maillon_int *p_tete, maillon_int *p_nv_elt)
{
    maillon_int *n, *prec;

    if (p_tete == NULL || p_nv_elt->val <= p_tete->val)
    {
        p_nv_elt->p_suiv = p_tete;
        p_tete = p_nv_elt;
    }
    else
    {
        n = prec = p_tete;
        while (n != NULL && p_nv_elt->val > n->val)
        {
            prec = n;
            n = n->p_suiv;
        }
        p_nv_elt->p_suiv = n;
        prec->p_suiv = p_nv_elt;
    }
    return p_tete;
}

void inserer2(maillon_int **prem, maillon_int *e)
{
    maillon_int *n, *prec;
    if (*prem == NULL || e->val <= (*prem)->val)
    {
        e->p_suiv = *prem;
        *prem = e;
    }
    else
    {
        n = prec = *prem;
        while (n != NULL && e->val > n->val)
        {
            prec = n;
            n = n->p_suiv;
        }
        e->p_suiv = n;
        prec->p_suiv = e;
    }
}

void supprimer_debut(maillon_int **prem)
{
    maillon_int *n;
    if (*prem != NULL)
    {
        n = *prem;
        *prem = (*prem)->p_suiv;
        free(n);
    }
}

// Fonction supprimer_elt � �crire elle recherche dans une liste
// une valeur enti�re pass�e en param�tres et en supprime toutes les occurences

void supprimer_elt(maillon_int **p_tete, int valeur)
//maillon_int **p_tete permet de modifier la t�te de la liste dans la fonction.
{
    maillon_int *p_val;
    maillon_int *n;
    if (*p_tete == NULL){
        printf("liste vide\n");
        return;
    }
    // Supprimer les �l�ments en d�but de liste
    while (*p_tete != NULL && (*p_tete)->val == valeur){
            maillon_int *temp = *p_tete;
            *p_tete = (*p_tete)->p_suiv;
            free(temp);
        }
    // Parcourir le reste de la liste
    maillon_int *courant = *p_tete;
    maillon_int *prec = NULL;
    while (courant != NULL){
        if (courant->val == valeur){
           if (prec != NULL) { // V�rifie si on est pas au d�but
                prec->p_suiv = courant->p_suiv;
            }
            maillon_int *temp = courant;
            courant = courant->p_suiv;
            free(temp);
        }else{
            prec = courant;
            courant = courant->p_suiv;
        }
    }

}


void detruire_liste(maillon_int **prem)
{
    maillon_int *n;
    while (*prem != NULL)
    {
        n = *prem;
        *prem = (*prem)->p_suiv;
        free(n);
    }
}

void detruire_liste2(maillon_int **prem)
{
    while (*prem != NULL)
        supprimer_debut(prem);
}

/* Permet la s�rialisation format binaire dans le fichier
"saveliste.bin" de la liste d'entier (maillon_int) dont
le pointeur sur le premier �l�ment est pass� en param�tre
@input : maillon_int * prem, pointeur sur l'�l�ment de t�te de la liste � s�rialiser
@output : void
@precondition : le r�pertoire courant et le processus p�re permettent l'�criture
                le pointeur prem, est soit NULL (aucune action) soit pointe sur
                le premier �l�ment d'une liste d'entiers
@postcondition : le fichier saveliste.bin contient les �l�ments de la liste
                dont le premier �l�ment est point� par prem.
                Nota : il n'y a pas de lib�ration de la m�moire occup�e par la
                liste. Il faut donc la d�truire avant d'�ventuellement la recharger.
*/
void sauver_liste(maillon_int *prem)
{
    // ouvrir un fichier binaire en �criture : suffixe b
    FILE *f = fopen("saveliste.bin", "wb");
    printf("Ouvertude du fichier %p\n", f);
    // si liste non vide
    if (prem != NULL)
    {
        if (f == NULL)
            fprintf(stderr, "erreur cr�ation fichier :%i\n", errno);
        else // parcourir la liste jusque fin
            while (prem != NULL)
            {
                // �crire chaque maillon en binaire
                if (1 != fwrite(prem, sizeof(maillon_int), 1, f))
                    fprintf(stderr, "Erreur d'�criture du maillon %p\n", prem);
                else
                    // passer au maillon suivant
                    prem = prem->p_suiv;
            }
        fclose(f); // fermer le fichier
    }
    else
        fprintf(stderr, "pas de sauvegarde pour une liste vide\n");
}


maillon_int *load_liste()
{
    FILE *f;
    maillon_int *prem = NULL, *p, e;
    if ((f = fopen("saveliste.bin", "rb")) != NULL)
    {
        prem = malloc(sizeof(maillon_int));
        fread(prem, sizeof(maillon_int), 1, f);
        p = prem;
        while (fread(&e, sizeof(maillon_int), 1, f))
        {
            p->p_suiv = malloc(sizeof(maillon_int));
            p = p->p_suiv;
           *p = e;
            p->p_suiv = NULL;
        }
        fclose(f);
    }
    else
        printf("erreur ou fichier inexistant");
    return prem;
}
