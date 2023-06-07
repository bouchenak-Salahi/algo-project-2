#include <stdio.h>
#include <stdlib.h>

#define MAX_MODULES 1
#define MAX_ETUDIANTS 100

typedef struct {
    float cc;
    float examen;
    float moyenne;
} Module;

typedef struct {
    int matricule;
    char nom[50];
    char prenom[50];
    char date_naissance[20];
    char date_inscription[20];
    Module modules[MAX_MODULES];
} Etudiant;

Etudiant etudiants[MAX_ETUDIANTS];
int nbEtudiants = 0;

void inscrireEtudiant() {
    Etudiant nouvelEtudiant;

    printf("Matricule : ");
    scanf("%d", &nouvelEtudiant.matricule);

    printf("Nom : ");
    scanf("%s", nouvelEtudiant.nom);

    printf("Prénom : ");
    scanf("%s", nouvelEtudiant.prenom);

    printf("Date de naissance : ");
    scanf("%s", nouvelEtudiant.date_naissance);

    printf("Date d'inscription : ");
    scanf("%s", nouvelEtudiant.date_inscription);

    etudiants[nbEtudiants] = nouvelEtudiant;
    nbEtudiants++;

    printf("L'étudiant a été inscrit avec succès.\n");
}

void saisirNotesEtudiant() {
    int matricule;
    int i, j;

    printf("Matricule de l'étudiant : ");
    scanf("%d", &matricule);

    for (i = 0; i < nbEtudiants; i++) {
        if (etudiants[i].matricule == matricule) {
            for (j = 0; j < MAX_MODULES; j++) {
                printf("Module %d - Note CC : ", j + 1);
                scanf("%f", &etudiants[i].modules[j].cc);

                printf("Module %d - Note Examen : ", j + 1);
                scanf("%f", &etudiants[i].modules[j].examen);

                etudiants[i].modules[j].moyenne = (etudiants[i].modules[j].cc + etudiants[i].modules[j].examen) / 2;
            }
            printf("Les notes ont été saisies avec succès.\n");
            return;
        }
    }

    printf("Aucun étudiant avec le matricule %d n'a été trouvé.\n", matricule);
}

void calculerMoyenneEtudiant() {
    int matricule;
    int i, j;

    printf("Matricule de l'étudiant : ");
    scanf("%d", &matricule);

    for (i = 0; i < nbEtudiants; i++) {
        if (etudiants[i].matricule == matricule) {
            float moyenneGenerale = 0;

            for (j = 0; j < MAX_MODULES; j++) {
                moyenneGenerale += etudiants[i].modules[j].moyenne;
            }

            float moyenneEtudiant = moyenneGenerale / MAX_MODULES;
            printf("La moyenne de l'étudiant est : %.2f\n", moyenneEtudiant);
            return;
        }
    }

    printf("Aucun étudiant avec le matricule %d n'a été trouvé.\n", matricule);
}

void afficherEtudiantsAdmis() {
    int i, j;
    int countAdmis = 0;

    for (i = 0; i < nbEtudiants; i++) {
        float moyenneGenerale = 0;

        for (j = 0; j < MAX_MODULES; j++) {
            moyenneGenerale += etudiants[i].modules[j].moyenne;
        }

        float moyenneEtudiant = moyenneGenerale / MAX_MODULES;

        if (moyenneEtudiant >= 10) {
            printf("Matricule : %d\n", etudiants[i].matricule);
            printf("Nom : %s\n", etudiants[i].nom);
            printf("Prénom : %s\n", etudiants[i].prenom);
            printf("Moyenne : %.2f\n", moyenneEtudiant);
            printf("-------------------------\n");
            countAdmis++;
        }
    }

    float pourcentageAdmis = (float) countAdmis / nbEtudiants * 100;
    float pourcentageAjourne = 100 - pourcentageAdmis;

    printf("Pourcentage d'étudiants admis : %.2f%%\n", pourcentageAdmis);
    printf("Pourcentage d'étudiants ajournés : %.2f%%\n", pourcentageAjourne);
}
int main() {
    int choix;

    do {
        printf("===== Gestion des étudiants =====\n");
        printf("1. Inscrire un étudiant\n");
        printf("2. Saisir les notes d'un étudiant\n");
        printf("3. Calculer la moyenne d'un étudiant\n");
        printf("4. Afficher les étudiants admis\n");
        printf("5. Quitter\n");
        printf("Choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                inscrireEtudiant();
                break;
            case 2:
                saisirNotesEtudiant();
                break;
            case 3:
                calculerMoyenneEtudiant();
                break;
            case 4:
                afficherEtudiantsAdmis();
                break;
            case 5:
                printf("Au revoir !\n");
                break;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
        }

        printf("\n");
    } while (choix != 5);

    return 0;
}