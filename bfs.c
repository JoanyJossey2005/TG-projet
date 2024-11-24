//
// Created by melan on 24/11/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "bfs.h"

#define MAX_NOM 50
#define MAX_CHAINES 10

/* Fonction BFS pour remonter dans les chaînes alimentaires */
void BFS_predecesseurs(Graphes* graphe, int sommet, int* visit, int** chemins, int* tailles_chemins, int* nb_chemins) {
    int file[graphe->ordre], debut = 0, fin = 0; // File pour BFS
    file[fin++] = sommet; // Ajouter le sommet initial à la file
    visit[sommet] = 1;

    while (debut < fin) {
        int courant = file[debut++];
        chemins[*nb_chemins] = (int*)malloc((graphe->ordre) * sizeof(int)); // Allouer de l'espace pour un nouveau chemin
        int chemin_len = 0;

        pArcs arc = graphe->pSommet[courant]->arc;
        while (arc) {
            if (!visit[arc->sommet]) {
                file[fin++] = arc->sommet; // Ajouter à la file
                visit[arc->sommet] = 1;
            }
            chemins[*nb_chemins][chemin_len++] = arc->sommet; // Ajouter au chemin
            arc = arc->arc_suivant;
        }

        tailles_chemins[*nb_chemins] = chemin_len;
        (*nb_chemins)++;
    }
}

// Fonction pour afficher les chaines alimentaires
void afficher_chaines_alimentaires(Sommets* graphe, int espece) {
    char chaines[MAX_CHAINES][MAX_NOM]; // Tableau pour stocker les chaines alimentaires
    int count = 0;

    // Initialiser les chaines à une valeur vide
    for (int i = 0; i < MAX_CHAINES; i++) {
        chaines[i][0] = '\0';  // Initialisation des chaines vides
    }

    // Parcourir les arcs de l'espece pour creer les chaines alimentaires
    pArcs arc = graphe[espece].arc;
    while (arc) {
        int current_sommet = arc->sommet;

        // Creer la chaine alimentaire en ajoutant les especes
        snprintf(chaines[count], MAX_NOM, "%s -> %s", correspondances[espece], correspondances[current_sommet]);

        // Verifier si la chaine a des successeurs et l'etendre
        pArcs arc_suivant = graphe[current_sommet].arc;
        while (arc_suivant) {
            snprintf(chaines[count] + strlen(chaines[count]), MAX_NOM - strlen(chaines[count]), " -> %s", correspondances[arc_suivant->sommet]);
            arc_suivant = arc_suivant->arc_suivant;
        }

        count++;
        arc = arc->arc_suivant; // Passer à l'arc suivant
    }

    // Afficher les chaines alimentaires generees
    if (count == 0) {
        printf("Aucune chaine alimentaire disponible pour %s.\n", correspondances[espece]);
    } else {
        for (int i = 0; i < count; i++) {
            printf("Chaine %d : %s\n", i + 1, chaines[i]);
        }
    }
}
