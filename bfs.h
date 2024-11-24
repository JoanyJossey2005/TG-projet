//
// Created by melan on 24/11/2024.
//

#ifndef TG_PROJET_BFS_H
#define TG_PROJET_BFS_H
/* Structure d'un arc */
typedef struct Arcs {
    int sommet; // Numéro du sommet de destination
    int poids;  // Poids de l'arc
    struct Arcs* arc_suivant;
}Arcs;

/* Alias pour un pointeur sur Arc */
typedef struct Arcs* pArcs;

/* Structure d'un sommet */
typedef struct Sommets {
    struct Arcs* arc; // Liste des arcs partant de ce sommet
    int valeur;
}Sommets;

/* Alias pour un pointeur sur Sommet */
typedef struct Sommets* pSommets;

/* Structure du graphe */
typedef struct Graphes {
    int ordre;      // Nombre de sommets
    int taille;     // Nombre d'arêtes ou arcs
    int orientation; // 1 si orienté, 0 sinon
    pSommets* pSommet; // Tableau de pointeurs vers les sommets
} Graphes;

/* Correspondance entre les sommets et les animaux */
const char* correspondances[] = {
        "herbe", "lapin", "souris", "insecte",
        "renard", "hibou", "faucon", "belette", "grenouille", "loup", "cerf", "escargot",
        "chouette", "ecureuil", "vipere", "blaireau"
};
#endif //TG_PROJET_BFS_H
