//
//  Labyrinthe.hpp
//  Laby-p3
//
//  Created by OB on 18/02/2021.
//

#ifndef Labyrinthe_hpp
#define Labyrinthe_hpp

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>


class Labyrinthe
{
private:
    int nb_lignes;
    int nb_colonnes;
    int taille;
    char* grille;
    std::string aff;
    
    // Retourne le caractère à afficher pour la valeur val.
    char getAff(char val);

public:
    /// Constructeurs et destructeurs
    Labyrinthe(int nLignes, int nColonnes); //Crée un labyrinthe vide.
    Labyrinthe(char data[]) ; //Crée un labyrinthe à partir d'un descripteur.
    ~Labyrinthe(); //Détruit le labyrinthe courant.
    
    /// Méthodes d'accès
    int getID(int ligne, int colonne); //Retourne l'identifiant d'une cellule.
    int getLigne(int id); //Retourne la ligne de la cellule d'identifiant id.
    int getCol(int id); //Retourne la colonne de la cellule d'identifiant id.
    void modifie(int ligne, int colonne, char x); //Modifie la valeur d'une cellule.
    char lit(int ligne, int colonne); //Retourne la valeur de la cellule de coordonnées (i,j).
    
    /// Méthode d'accès supplémentaires
    int getNbLignes(); //Retourne le nombre de lignes de la grille.
    int getNbColonnes(); //Retourne le nombre de lignes de la grille.
    int lit(int id); //Retourne la valeur de la cellule id.
    void modifie(int id, char x); //Modifie la valeur de la cellule id.

    /// Méthodes d'affichage
    // Initialise les caractères utilisés pour l'affichage. Si motif contient n caractères alors
    // motif[i] est affiché pour représenter une case de valeur i entre 0 et n-2.
    // Toute autre valeur provoque l'affichage du caractère motif[n-1].
    void setAff(const char* motifs);
    void affiche(); // Affiche le labyrinthe.
    void afficheDescr(); //Affiche le descripteur du labyrinthe courant.
    
    /// Méthode de haut niveau
    bool connexe(); //Vérifie si toutes les cellules de valeur 0 sont connectées.
    void genLaby(int nb); //Produit un labyrinthe aléatoire connexe avec nb cases blanches.
    int distMin(int id1, int id2); //Retourne la distance minimum entre les cases id1 et id2.
    
    /// Méthodes de démonstration
    // Matérialise un chemin de longueur minimale entre les cases d'identifiants
    // id1 et id2 en plaçant des valeurs 2 dans les cases de ce chemin.
    void chemin(int id1, int id2);
    // Lance une démonstration de productions de labyrinthes et de recherche de
    // chemins de longueur minimale.
    static void demo();
};

#endif /* Labyrinthe_hpp */
