#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Structure d'un arc */
struct Arc {
    int sommet; // Numéro du sommet de destination
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
        "renard", "hibou", "faucon", "belette", "grenouille"
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
pSommet* CreerArete(pSommet* sommet, int s1, int s2) {
    pArc nouvelArc = (pArc)malloc(sizeof(struct Arc));
    nouvelArc->sommet = s2;
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

    int s1, s2;
    for (int i = 0; i < taille; i++) {
        fscanf(fichier, "%d %d", &s1, &s2);
        graphe->pSommet = CreerArete(graphe->pSommet, s1, s2);

        // Si le graphe est non orienté, ajouter l'arête dans les deux sens
        if (!orientation) {
            graphe->pSommet = CreerArete(graphe->pSommet, s2, s1);
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
        printf("%d (%s) ", arc->sommet, correspondance[arc->sommet]);
        arc = arc->arc_suivant;
    }
    printf("\n");
}

/* Affichage des prédécesseurs d'un sommet */
void afficher_predecesseurs(Graphe* graphe, int num) {
    printf("Predecesseurs du sommet %d (%s) : ", num, correspondance[num]);
    for (int i = 0; i < graphe->ordre; i++) {
        pArc arc = graphe->pSommet[i]->arc;
        while (arc) {
            if (arc->sommet == num) {
                printf("%d (%s) ", i, correspondance[i]);
            }
            arc = arc->arc_suivant;
        }
    }
    printf("\n");
}

/* Affichage complet du graphe */
void graphe_afficher(Graphe* graphe) {
    printf("Graphe d'ordre %d \n", graphe->ordre);
    if (graphe->orientation) {
        printf("Le graphe est oriente.\n");
    } else {
        printf("Le graphe est non oriente.\n");
    }
    printf("\nCorrespondance des sommets avec les animaux :\n");
    for (int i = 0; i < graphe->ordre; i++) {
        printf("%d : %s\n", i, correspondance[i]);
    }
    printf("\nListes d'adjacence :\n");
    for (int i = 0; i < graphe->ordre; i++) {
        afficher_successeurs(graphe->pSommet, i);
        afficher_predecesseurs(graphe, i);
    }
}

int main() {
    char nomFichier[50];
    printf("Entrez le nom du fichier contenant le graphe : ");
    scanf("%s", nomFichier);

    Graphe* graphe = lire_graphe(nomFichier);
    graphe_afficher(graphe);

    // Libération de la mémoire
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
