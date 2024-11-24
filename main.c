#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

/* Structure d'un arc */
struct Arc {
    int sommet; // Numéro du sommet de destination
    int poids;  // Poids de l'arc
    struct Arc* arc_suivant;
};

/* Alias pour un pointeur sur Arc */
typedef struct Arc* pArc;

/* Structure d'un sommet */
struct Sommet {
    struct Arc* arc; // Liste des arcs partant de ce sommet
    int valeur;
};

/* Alias pour un pointeur sur Sommet */
typedef struct Sommet* pSommet;

/* Structure du graphe */
typedef struct Graphe {
    int ordre;      // Nombre de sommets
    int taille;     // Nombre d'arêtes ou arcs
    int orientation; // 1 si orienté, 0 sinon
    pSommet* pSommet; // Tableau de pointeurs vers les sommets
} Graphe;

/* Correspondance entre les sommets et les animaux */
const char* correspondance[] = {
        "herbe", "lapin", "souris", "insecte",
        "renard", "hibou", "faucon", "belette", "grenouille", "loup", "cerf", "escargot",
        "chouette", "ecureuil", "vipere", "blaireau"
};

/* Création d'un graphe */
Graphe* CreerGraphe(int ordre) {
    Graphe* graphe = (Graphe*)malloc(sizeof(Graphe));
    graphe->ordre = ordre;
    graphe->taille = 0;
    graphe->orientation = 0;
    graphe->pSommet = (pSommet*)malloc(ordre * sizeof(pSommet));

    for (int i = 0; i < ordre; i++) {
        graphe->pSommet[i] = (pSommet)malloc(sizeof(struct Sommet));
        graphe->pSommet[i]->arc = NULL;
        graphe->pSommet[i]->valeur = i;
    }

    return graphe;
}


/* Ajouter une arête ou un arc entre deux sommets */
pSommet* CreerArete(pSommet* sommet, int s1, int s2, int poids) {
    pArc nouvelArc = (pArc)malloc(sizeof(struct Arc));
    nouvelArc->sommet = s2;
    nouvelArc->poids = poids;
    nouvelArc->arc_suivant = sommet[s1]->arc;
    sommet[s1]->arc = nouvelArc;
    return sommet;
}

/* Lecture d'un graphe à partir d'un fichier */
Graphe* lire_graphe(char* nomFichier) {
    FILE* fichier = fopen(nomFichier, "r");
    if (!fichier) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    int ordre, taille, orientation;
    fscanf(fichier, "%d", &ordre);

    Graphe* graphe = CreerGraphe(ordre);

    fscanf(fichier, "%d", &taille);
    fscanf(fichier, "%d", &orientation);
    graphe->taille = taille;
    graphe->orientation = orientation;

    int s1, s2, poids;
    for (int i = 0; i < taille; i++) {
        fscanf(fichier, "%d %d %d", &s1, &s2, &poids);
        graphe->pSommet = CreerArete(graphe->pSommet, s1, s2, poids);

        if (!orientation) {
            graphe->pSommet = CreerArete(graphe->pSommet, s2, s1, poids);
        }
    }

    fclose(fichier);
    return graphe;
}

/* Affichage des successeurs d'un sommet */
void afficher_successeurs(pSommet* sommet, int num) {
    printf("Successeurs du sommet %d (%s) : ", num, correspondance[num]);
    pArc arc = sommet[num]->arc;
    while (arc) {
        printf("%d (%s,%d) , ", arc->sommet, correspondance[arc->sommet], arc->poids);
        arc = arc->arc_suivant;
    }
    printf("\n");
}

/* Algorithme de Dijkstra */
void dijkstra(Graphe* graphe, int source, int destination) {
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

        pArc arc = graphe->pSommet[u]->arc;
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
        printf("Poids totale : %d\n", distances[destination]);

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

void trouver_premiers_maillons(Graphe* graphe) {
    printf("\nPremiers maillons (sans predecesseurs) :\n");
    for (int i = 0; i < graphe->ordre; i++) {
        int a_predecesseur = 0;
        for (int j = 0; j < graphe->ordre; j++) {
            pArc arc = graphe->pSommet[j]->arc;
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

void trouver_derniers_maillons(Graphe* graphe) {
    printf("\nDerniers maillons (sans successeurs) :\n");
    for (int i = 0; i < graphe->ordre; i++) {
        if (graphe->pSommet[i]->arc == NULL) {
            printf("- %d (%s)\n", i, correspondance[i]);
        }
    }
}

void trouver_une_seule_source_alimentation(Graphe* graphe) {
    printf("\nEspeces ayant une seule source d'alimentation :\n");
    for (int i = 0; i < graphe->ordre; i++) {
        int nb_pred = 0;
        for (int j = 0; j < graphe->ordre; j++) {
            pArc arc = graphe->pSommet[j]->arc;
            while (arc) {
                if (arc->sommet == i) {
                    nb_pred++;
                    if (nb_pred > 1) break;
                }
                arc = arc->arc_suivant;
            }
            if (nb_pred > 1) break;
        }
        if (nb_pred == 1) {
            printf("- %d (%s)\n", i, correspondance[i]);
        }
    }
}

/* Affichage complet du graphe */
void graphe_afficher(Graphe* graphe) {
    printf("Graphe d'ordre %d\n", graphe->ordre);
    if (graphe->orientation) {
        printf("Le graphe est oriente.\n");
    } else {
        printf("Le graphe est non oriente.\n");
    }
    printf("\nListes d'adjacence :\n");
    for (int i = 0; i < graphe->ordre; i++) {
        afficher_successeurs(graphe->pSommet, i);
    }
}

int main() {
    char nomFichier[50];
    printf("Entrez le nom du fichier contenant le graphe : ");
    scanf("%s", nomFichier);

    Graphe* graphe = lire_graphe(nomFichier);
    graphe_afficher(graphe);

    trouver_premiers_maillons(graphe);
    trouver_derniers_maillons(graphe);
    trouver_une_seule_source_alimentation(graphe);


    int source, destination;
    printf("Entrez le sommet de depart : ");
    scanf("%d", &source);
    printf("Entrez le sommet de destination : ");
    scanf("%d", &destination);

    dijkstra(graphe, source, destination);



    for (int i = 0; i < graphe->ordre; i++) {
        pArc arc = graphe->pSommet[i]->arc;
        while (arc) {
            pArc temp = arc;
            arc = arc->arc_suivant;
            free(temp);
        }
        free(graphe->pSommet[i]);
    }
    free(graphe->pSommet);
    free(graphe);

    return 0;
}