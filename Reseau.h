/*
 *
 * JUSTE POUR LE COMMIT
 * INUTILE
 */

#ifndef RESEAU_H_INCLUDED
#define RESEAU_H_INCLUDED

/// Le Reseau représente un graphe dans son ensemble

/// La construction du réseau se fait à partir d'un fichier
/// dont le nom est passé en paramètre
Station ** ouvrir_reseau(char * nomFichier, int *ordre);

/// afficher toutes les stations du reseau
void afficher_reseau(Station **stations, int ordre);

/// Remet toutes les fréquences des stations à 0 (non affectées)
void resetFrequences(Station ** stations, int ordre);

/// L'algorithme suivant trouve une coloration
/// en essayant systématiquement toutes les combinaisons
/// d'affectations avec 1 couleur, puis 2 couleurs, puis 3 ...
/// Cet algorithme garantit donc une meilleure coloration
/// ( nombre de couleur utilisées = nombre chromatique )
/// mais il présente un grave inconvénient... Lequel ?
void attribuerSystematique(int* nbFrequences, Station ** stations, int ordre);


/// ************* CODE ETUDIANT *************
/*
 * Procédure de l'algorithme naif vu en cours qui trouve une coloration en respect
 * des étapes de cet algorithme
 * Paramètres :
 *             OUT (sortie/résultat) nbFrequences : pointeur sur le nombre de fréquences
 *             IN (entrée) stations : matrice dynamique de stations
 *             IN (entrée) ordre : nombre de stations
 */
void attribuerNaif(int* nbFrequences, Station ** stations, int ordre);

/*
 * Procédure de l'algorithme Welsh & Powell vu en cours qui trouve une coloration en respect
 * des étapes de cet algorithme
 * Paramètres :
 *             OUT (sortie/résultat) nbFrequences : pointeur sur le nombre de fréquences
 *             IN (entrée) stations : matrice dynamique de stations
 *             IN (entrée) ordre : nombre de stations
 */
void attribuerWelshPowell(int* nbFrequences, Station ** stations, int ordre);

#endif // RESEAU_H_INCLUDED
