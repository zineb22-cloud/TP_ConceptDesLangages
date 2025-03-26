#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Farahlisteint.h"
int menu()
{
    int choix = 0;
    printf("1 Creer une liste d'entiers compris entre 0 et 20 de taille aleatoire comprise entre 1 et 20\n"
       "2 Ajouter un element entier aleatoire (compris entre 0 et 20) en tete de liste\n"
       "3 Inserer un element entier aleatoire dans sa place dans la liste suivant l'ordre croissant des premiers elements\n"
       "4 Supprimer l'element de tete\n"
       "5 Supprimer tous les maillons d'une valeur donnee\n"
       "6 Detruire liste\n"
       "7 Sauver la liste courante en binaire dans le fichier \"saveliste.bin\"\n"
       "8 Charger une liste depuis le fichier \"saveliste.bin\"\n");

    scanf("%d", &choix);
    while (getchar() != '\n'); // Nettoyer le buffer

    return choix;
}

int main()
{
    maillon_int *premier = NULL;
    int fin = 0;
    int choix, valeur;

    srand((unsigned)time(NULL));
    while (!fin)
    {
        choix = menu();
        switch (choix)
        {
        case 1: // Creer une liste de taille aleatoire
          {
            int taille = rand() % 20+1;
            maillon_int *Liste=NULL;
            int i;
            for (i=0; i<taille ;i++){
                Liste = malloc(sizeof(maillon_int));
                if (Liste == NULL){
                    printf("Erreur allocation memoire\n");
                    exit(1);
                }
                Liste->val = rand()%21;
                Liste->p_suiv=premier;// Ajout en tete
                premier=Liste;
            }
            parcourir(premier);// Afficher la liste generee
            break;
          }
        case 2: // Ajouter un element en tete (version 2)
            ajout_tete_v2(&premier, init_elt());
            parcourir(premier);
            break;

        case 3: // Inserer en ordre croissant (version 2)
            inserer2(&premier, init_elt());
            parcourir(premier);
            break;

        case 4: // Supprimer le premier element
            supprimer_debut(&premier);
            parcourir(premier);
            break;

        case 5: // Supprimer un �l�ment donn�
            printf("Entrez la valeur a supprimer : ");
            scanf("%d", &valeur);
            supprimer_elt(&premier, valeur);
            parcourir(premier);
            break;

        case 6: // Detruire la liste
            detruire_liste(&premier);
            printf("Liste detruite.\n");
            break;

        case 7: // Sauvegarder la liste
            sauver_liste(premier);
            break;

        case 8: // Charger une liste depuis un fichier
            premier = load_liste();
            parcourir(premier);
            break;

        case 0: // Quitter
            detruire_liste(&premier);
            fin = 1;
            break;

        default:
            printf("Choix invalide, essayez encore.\n");
            break;
        }
    }
    return 0;
}
