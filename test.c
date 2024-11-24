//
// Created by DELL 7420 on 24/11/2024.
//
//MARCHE pour 2 graphes SANS PREDESSEUR

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

/* Structure d'un arc */
struct Arcss {
    int sommet; // Numéro du sommet de destination
    int poids;  // Poids de l'arc
    struct Arcss* arc_suivant;
};

/* Alias pour un pointeur sur Arc */
typedef struct Arcss* pArcss;

/* Structure d'un sommet */
struct Sommetss {
    struct Arcss* arc; // Liste des arcs partant de ce sommet
    int valeur;
};

/* Alias pour un pointeur sur Sommet */
typedef struct Sommetss* pSommetss;

/* Structure du graphe */
typedef struct Graphess {
    int ordre;      // Nombre de sommets
    int taille;     // Nombre d'arêtes ou arcs
    int orientation; // 1 si orienté, 0 sinon
    pSommetss* pSommet; // Tableau de pointeurs vers les sommets
} Graphess;

/* Création d'un graphe */
Graphess* CreerGraphes(int ordre) {
    Graphess* graphe = (Graphess*)malloc(sizeof(Graphess));
    graphe->ordre = ordre;
    graphe->taille = 0;
    graphe->orientation = 0;
    graphe->pSommet = (pSommetss*)malloc(ordre * sizeof(pSommetss));

    for (int i = 0; i < ordre; i++) {
        graphe->pSommet[i] = (pSommetss)malloc(sizeof(struct Sommetss));
        graphe->pSommet[i]->arc = NULL;
        graphe->pSommet[i]->valeur = i;
    }

    return graphe;
}

/* Ajouter une arête ou un arc entre deux sommets */
pSommetss* CreerAretes(pSommetss* sommet, int s1, int s2, int poids) {
    pArcss nouvelArc = (pArcss)malloc(sizeof(struct Arcss));
    nouvelArc->sommet = s2;
    nouvelArc->poids = poids;
    nouvelArc->arc_suivant = sommet[s1]->arc;
    sommet[s1]->arc = nouvelArc;
    return sommet;
}

/* Lecture d'un graphe à partir d'un fichier */
Graphess* lire_graphes(char* nomFichier) {
    FILE* fichier = fopen(nomFichier, "r");
    if (!fichier) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    int ordre, taille, orientation;
    fscanf(fichier, "%d", &ordre);

    Graphess* graphe = CreerGraphes(ordre);

    fscanf(fichier, "%d", &taille);
    fscanf(fichier, "%d", &orientation);
    graphe->taille = taille;
    graphe->orientation = orientation;

    int s1, s2, poids;
    for (int i = 0; i < taille; i++) {
        fscanf(fichier, "%d %d %d", &s1, &s2, &poids);
        graphe->pSommet = CreerAretes(graphe->pSommet, s1, s2, poids);

        if (!orientation) {
            graphe->pSommet = CreerAretes(graphe->pSommet, s2, s1, poids);
        }
    }

    fclose(fichier);
    return graphe;
}

/* Lecture de la correspondance des animaux */
char** lire_correspondances(char* nomFichier, int ordre) {
    FILE* fichier = fopen(nomFichier, "r");
    if (!fichier) {
        perror("Erreur lors de l'ouverture du fichier de correspondance");
        exit(EXIT_FAILURE);
    }

    char** correspondance = (char**)malloc(ordre * sizeof(char*));
    for (int i = 0; i < ordre; i++) {
        correspondance[i] = (char*)malloc(50 * sizeof(char)); // On limite chaque nom à 50 caractères
        if (fscanf(fichier, " %[^\n]", correspondance[i]) != 1) {
            perror("Erreur lors de la lecture de la correspondance");
            exit(EXIT_FAILURE);
        }
    }

    fclose(fichier);
    return correspondance;
}

/* Libération de la mémoire de la correspondance */
void liberer_correspondances(char** correspondance, int ordre) {
    for (int i = 0; i < ordre; i++) {
        free(correspondance[i]);
    }
    free(correspondance);
}

/* Affichage des successeurs d'un sommet */
void afficher_successeurss(pSommetss* sommet, int num, char** correspondance) {
    printf("Successeurs du sommet %d (%s) : ", num, correspondance[num]);
    pArcss arc = sommet[num]->arc;
    while (arc) {
        printf("%d (%s, %d) , ", arc->sommet, correspondance[arc->sommet], arc->poids);
        arc = arc->arc_suivant;
    }
    printf("\n");
}

/* Algorithme de Dijkstra */
void dijkstras(Graphess* graphe, int source, int destination, char** correspondance) {
    int* distances = (int*)malloc(graphe->ordre * sizeof(int));
    int* precedents = (int*)malloc(graphe->ordre * sizeof(int));
    int* visite = (int*)calloc(graphe->ordre, sizeof(int));

    for (int i = 0; i < graphe->ordre; i++) {
        distances[i] = INT_MAX;
        precedents[i] = -1;
    }
    distances[source] = 0;

    for (int i = 0; i < graphe->ordre; i++) {
        int minDistance = INT_MAX;
        int u = -1;

        for (int j = 0; j < graphe->ordre; j++) {
            if (!visite[j] && distances[j] < minDistance) {
                minDistance = distances[j];
                u = j;
            }
        }

        if (u == -1) break;
        visite[u] = 1;

        pArcss arc = graphe->pSommet[u]->arc;
        while (arc) {
            int v = arc->sommet;
            int poids = arc->poids;
            if (!visite[v] && distances[u] + poids < distances[v]) {
                distances[v] = distances[u] + poids;
                precedents[v] = u;
            }
            arc = arc->arc_suivant;
        }
    }

    if (distances[destination] == INT_MAX) {
        printf("Aucun chemin trouvé entre %d (%s) et %d (%s).\n",
               source, correspondance[source], destination, correspondance[destination]);
    } else {
        printf("Chemin le plus court entre %d (%s) et %d (%s) :\n",
               source, correspondance[source], destination, correspondance[destination]);
        printf("Poids total : %d\n", distances[destination]);

        int chemin[graphe->ordre];
        int index = 0;
        for (int at = destination; at != -1; at = precedents[at]) {
            chemin[index++] = at;
        }
        for (int i = index - 1; i >= 0; i--) {
            printf("%d (%s) -> ", chemin[i], correspondance[chemin[i]]);
        }
        printf("\n");
    }

    free(distances);
    free(precedents);
    free(visite);
}

/* Fonction pour trouver les premiers maillons */
void trouver_premiers_maillonss(Graphess* graphe, char** correspondance) {
    printf("\nPremiers maillons (sans prédécesseurs) :\n");
    for (int i = 0; i < graphe->ordre; i++) {
        int a_predecesseur = 0;
        for (int j = 0; j < graphe->ordre; j++) {
            pArcss arc = graphe->pSommet[j]->arc;
            while (arc) {
                if (arc->sommet == i) {
                    a_predecesseur = 1;
                    break;
                }
                arc = arc->arc_suivant;
            }
            if (a_predecesseur) break;
        }
        if (!a_predecesseur) {
            printf("- %d (%s)\n", i, correspondance[i]);
        }
    }
}

/* Fonction pour trouver les derniers maillons */
void trouver_derniers_maillonss(Graphess* graphe, char** correspondance) {
    printf("\nDerniers maillons (sans successeurs) :\n");
    for (int i = 0; i < graphe->ordre; i++) {
        if (graphe->pSommet[i]->arc == NULL) {
            printf("- %d (%s)\n", i, correspondance[i]);
        }
    }
}

/* Fonction pour trouver les espèces avec une seule source d'alimentation */
void trouver_une_seule_source_alimentations(Graphess* graphe, char** correspondance) {
    printf("\nEspèces ayant une seule source d'alimentation :\n");
    for (int i = 0; i < graphe->ordre; i++) {
        int nb_pred = 0;
        for (int j = 0; j < graphe->ordre; j++) {
            pArcss arc = graphe->pSommet[j]->arc;
            while (arc) {
                if (arc->sommet == i) {
                    nb_pred++;
                }
                arc = arc->arc_suivant;
            }
        }
        if (nb_pred == 1) {
            printf("- %d (%s)\n", i, correspondance[i]);
        }
    }
}

/* Programme principal */
int mains() {
    char nomFichierGraphe[50];
    char nomFichierAnimaux[50];

    printf("Entrez le nom du fichier contenant le graphe : ");
    scanf("%s", nomFichierGraphe);
    printf("Entrez le nom du fichier contenant les noms des animaux : ");
    scanf("%s", nomFichierAnimaux);

    Graphess* graphe = lire_graphes(nomFichierGraphe);
    char** correspondance = lire_correspondances(nomFichierAnimaux, graphe->ordre);

    trouver_premiers_maillonss(graphe, correspondance);
    trouver_derniers_maillonss(graphe, correspondance);
    trouver_une_seule_source_alimentations(graphe, correspondance);

    int source, destination;
    printf("Entrez le sommet de départ : ");
    scanf("%d", &source);
    printf("Entrez le sommet de destination : ");
    scanf("%d", &destination);

    dijkstras(graphe, source, destination, correspondance);

    for (int i = 0; i < graphe->ordre; i++) {
        pArcss arc = graphe->pSommet[i]->arc;
        while (arc) {
            pArcss temp = arc;
            arc = arc->arc_suivant;
            free(temp);
        }
        free(graphe->pSommet[i]);
    }

    liberer_correspondances(correspondance, graphe->ordre);
    free(graphe->pSommet);
    free(graphe);

    return 0;
}
