#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Train{
    char villeDepart[50];
    char villeArriver[50];
    int heureDepart,minDepart;
    int heureArriver,minArriver;
    int distance;
    struct Train *horaire_suiv;
}Train;

void ajouterHoraire(Train **tete_liste){//pour modifier le pointeur de tete dans main()
    Train *nouvelHoraire = (Train*)malloc(sizeof(Train));
    if (nouvelHoraire == NULL){
        printf("Erreur d'allocation de memoire \n");
        exit(1);
    }
    printf("Veuillez saisir toutes les informations d'un nouvel horaire.\n");
    printf("Ville de Depart: \n");
    scanf("%s",nouvelHoraire->villeDepart);
    printf("Ville d'arriver: \n");
    scanf("%s",nouvelHoraire->villeArriver);
    printf("Heure de depart (heure et minute) : \n");
    scanf("%d %d",&nouvelHoraire->heureDepart,&nouvelHoraire->minDepart);
    printf("Heure d'arriver (heure et minute) : \n");
    scanf("%d %d",&nouvelHoraire->heureArriver,&nouvelHoraire->minArriver);
    printf("Distance entre les villes : \n");
    scanf("%d",&nouvelHoraire->distance);

    nouvelHoraire->horaire_suiv = *tete_liste;
    *tete_liste = nouvelHoraire;
    printf("Horaire ajouter avec succes.\n");
    }


void afficherHoraires(Train *tete_liste){
    if (tete_liste==NULL){
        printf("Aucune horaire disponible\n");
        return;
    }
    while (tete_liste!=NULL){
        printf("Ville depart %s -> ville arriver %s | heure de depart %02d:%02d -> heure d'arriver %02d:%02d | distance %d.",
               tete_liste->villeDepart,tete_liste->villeArriver,
               tete_liste->heureDepart,tete_liste->minDepart,
               tete_liste->heureArriver,tete_liste->minArriver,
               tete_liste->distance
               );
               tete_liste=tete_liste->horaire_suiv;
    }
}

void afficherTrainDonnee(Train *tete_liste){
    if (tete_liste==NULL){
        printf("Liste Vide.\n");
        return;
    }
    char nouvVille[50];
    printf("Veuillez saisir votre ville de depart: \n");
    scanf("%s",nouvVille);
    int Trouver=0;
    printf("\nTrain au depart de %s: \n",nouvVille);

    while (tete_liste!=NULL){
         if (strcmp(nouvVille, tete_liste->villeDepart) == 0) {
            printf("%s -> %s | %02d:%02d -> %02d:%02d | Distance : %d\n",
                   tete_liste->villeDepart, tete_liste->villeArriver,
                   tete_liste->heureDepart, tete_liste->minDepart,
                   tete_liste->heureArriver, tete_liste->minArriver,
                   tete_liste->distance);

            Trouver = 1;
        }
        tete_liste = tete_liste->horaire_suiv;
    }
    if(!Trouver){
        printf("Aucun horaire disponible pour cette ville.\n");
    }

}
double calculeDuree(int hDep,int minDep,int hArr,int minArr){
    return (hArr +minArr/60) - (hDep+minDep/60);
}
void determinTrajet(Train *tete_liste){
    if (tete_liste==NULL){
        printf("Liste vide.\n");
        return ;
    }
    Train *trainMax=NULL;
    double vitesseMax= 0.0;
    while (tete_liste!=NULL){
        double duree = calculeDuree(tete_liste->heureDepart,tete_liste->minDepart,
                                    tete_liste->heureArriver,tete_liste->minArriver);

        if (duree>0){
            double vitesse = tete_liste->distance/duree;
            if (vitesse>vitesseMax){
                vitesseMax=vitesse;
                trainMax=tete_liste;
            }
        }
        tete_liste = tete_liste->horaire_suiv;

        if (trainMax!=NULL){
            printf("\n Trajet le plus rapide: \n");
            printf("%s -> %s | %02d:%02d -> %02d:%02d | Distance : %d  | Vitesse Moyenne : %.2f\n",
               trainMax->villeDepart, trainMax->villeArriver,
               trainMax->heureDepart, trainMax->minDepart,
               trainMax->heureArriver, trainMax->minArriver,
               trainMax->distance, vitesseMax);
    } else {
        printf("Aucun trajet valide trouver.\n");
    }
        }
}
int menu()
{
    int choix = 0;
    printf("\n1 Ajouter un horaire\n"
       "2 Afficher les horaires\n"
       "3 Afficher Train donner.\n"
       "4 détermine le trajet sur lequel la vitesse moyenne est la plus élevée.\n"
       "5 Quitter\n");

    scanf("%d", &choix);
    while (getchar() != '\n'); // Nettoyer le buffer

    return choix;
}

int main()
{
    Train *L=NULL;
    int choix;
    do {
        choix=menu();
        switch (choix){
        case 1 :
            ajouterHoraire(&L);
            break;
        case 2:
            afficherHoraires(L);
            break;
        case 3:
            afficherTrainDonnee(L);
            break;
        case 4:
            determinTrajet(L);
            break;
        case 5:
            printf("Fin du programme.\n");
            break;
        default:
            printf("Choix invalide.\n");

    }
    }while (choix != 5);
    return 0;

}
