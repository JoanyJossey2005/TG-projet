//
// Created by melan on 24/11/2024.
//

#include "dijkstra.h"


#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>

#define MAX 999999999
/*
// sous programme pour trouver le numero d'un sommet
int trouverNumSommet(Sommet* s, int nombreSommets, int num) {
    for (int i = 0; i < nombreSommets; i++) {
        if (s[i].num == num) {
            return i;
        }
    }
    return -1;
}

// sous programme pour ajouter une arete entre deux sommets entrés en parametres ainsi que son poids
void ajouterArete(Sommet* sommets, int s1, int s2, int poids) {
    sommets[s1].adjacences = realloc(sommets[s1].adjacences,
                                     (sommets[s1].nb_arete + 1) * sizeof(Arete));
    sommets[s1].adjacences[sommets[s1].nb_arete].destination = s2;
    sommets[s1].adjacences[sommets[s1].nb_arete].poids = poids;
    sommets[s1].nb_arete++;
}

// sous programme pour charger le graphe à partir du fichier
void chargerGraphe(const char* nom, Graphe* g) {
    FILE* fichier = fopen(nom, "r");
    if (!fichier) {
        printf("Impossible d'ouvrir le fichier\n");
        return;
    }

    fscanf(fichier, "%d", &g->nombreSommets);
    g->sommets = (Sommet*)malloc(g->nombreSommets * sizeof(Sommet));

    // lire les numéros des sommets
    for (int i = 0; i < g->nombreSommets; i++) {
        fscanf(fichier, "%d", &g->sommets[i].num);
        g->sommets[i].nb_arete = 0;
        g->sommets[i].adjacences = NULL;
    }

    fscanf(fichier, "%d", &g->nombreAretes);

    // lire les aretes et leur poids
    for (int i = 0; i < g->nombreAretes; i++) {
        int id1, id2, poids;
        fscanf(fichier, "%d %d %d", &id1, &id2, &poids);

        int index1 = trouverNumSommet(g->sommets, g->nombreSommets, id1);
        int index2 = trouverNumSommet(g->sommets, g->nombreSommets, id2);

        if (index1 == -1 || index2 == -1) {
            printf("Sommet non trouve\n");
            continue;
        }

        // ajouter une arête entre les deux sommets
        ajouterArete(g->sommets, index1, index2, poids);
        ajouterArete(g->sommets, index2, index1, poids);
    }

    fclose(fichier);
}

// sous programme qui fait l'algorithme de Dijkstra
void algo_dijkstra(Graphe* g, int depart, int arrivee) {
    int nb_sommets = g->nombreSommets;
    int* dist = (int*)malloc(nb_sommets * sizeof(int));
    int* pred = (int*)malloc(nb_sommets * sizeof(int));
    bool* marque = (bool*)malloc(nb_sommets * sizeof(bool));
    int nbSommetExplore = 0;

    int dep = trouverNumSommet(g->sommets, nb_sommets, depart);
    int arr = trouverNumSommet(g->sommets, nb_sommets, arrivee);

    if (dep == -1 || arr == -1) {
        printf("Sommet de depart ou d'arrivee non trouve\n");
        free(dist);
        free(pred);
        free(marque);
        return;
    }

    for (int i = 0; i < nb_sommets; i++) {
        dist[i] = MAX;
        pred[i] = -1;
        marque[i] = false;
    }
    dist[dep] = 0;

    for (int i = 0; i < nb_sommets; i++) {
        int minDist = MAX;
        int sommetMin = -1;

        for (int j = 0; j < nb_sommets; j++) {
            if (!marque[j] && dist[j] < minDist) {
                minDist = dist[j];
                sommetMin = j;
            }
        }

        if (sommetMin == -1) {
            break;
        }

        marque[sommetMin] = true;
        nbSommetExplore++;

        for (int j = 0; j < g->sommets[sommetMin].nb_arete; j++) {
            Arete adj = g->sommets[sommetMin].adjacences[j];
            int nouvelleDist = dist[sommetMin] + adj.poids;
            if (nouvelleDist < dist[adj.destination]) {
                dist[adj.destination] = nouvelleDist;
                pred[adj.destination] = sommetMin;
            }
        }
    }

    if (dist[arr] == MAX) {
        printf("Aucun chemin trouve de %d a %d\n", depart, arrivee);
    } else {
        printf("La longueur du plus court chemin de %d a %d est %d\n", depart, arrivee, dist[arr]);
        printf("Le chemin est : ");
        int temp = arr;
        while (temp != -1) {
            printf("%d ", g->sommets[temp].num);
            temp = pred[temp];
        }
        printf("\n");
    }
    printf("Nombre de sommets explores (Dijkstra) : %d\n", nbSommetExplore);

    free(dist);
    free(pred);
    free(marque);
}*/