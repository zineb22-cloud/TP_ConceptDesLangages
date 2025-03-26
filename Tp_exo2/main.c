
#include "pile.h"

int menu()
{
    int choix = 0;
    printf("\n1 Creer une pile\n"
       "2 renverse une liste d'entiers avec une pile\n"
       "3 - Quitter\n");

    scanf("%d", &choix);
    while (getchar() != '\n'); // Nettoyer le buffer

    return choix;
}


int main()
{
    int fin=0;
    myPile P1,P2;
    int var_inserer,choix;
    int taille;


    // Demander la taille et initialise la pile correctement
    while (!fin)
    {
        choix = menu();
        switch (choix)
        {
        case 1:
         {
            printf("Veuillez saisir la taille max de la pile 1\n");
            scanf("%d",&taille);
            P1 = initPile(taille);
            // Remplissage de la pile
            while (!estPleine(P1)){
                printf("Donner une valeur: \n");
                scanf("%d",&var_inserer);
                empiler(&P1,var_inserer);
            }
            printf("contenu de la pile: \n");
            while(!estVide(P1)){
                printf("%d\n",depiler(&P1));
            }
            libererPile(&P1);
            break;
        }
        case 2:
        {
            printf("Veuillez saisir la taille max de la pile 1\n");
            scanf("%d",&taille);
            int liste[taille];
            for (int i = 0; i < taille; i++) {
                    printf("Entrez un nombre : ");
                    scanf("%d", &liste[i]);
                }
            renverserListe(liste, taille);
            break;
        }
        case 3:
                printf("Fin du programme.\n");
                fin = 1;
                break;

            default:
                printf("Choix invalide !\n");
      }
    }

    return 0;
}
