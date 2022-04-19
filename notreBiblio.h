#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include <conio.h>




#ifndef DEF_DICO
#define DEF_DICO






typedef struct liste_mot
{
    int id_mot;
    char mot[10];
    struct liste_mot *suivant;
}liste_mot;




liste_mot *creer_liste_mot(int id_mot,char *mot);

liste_mot *inserer_mot(liste_mot *liste, liste_mot *m);


int nombreAleatoire(int nbreMots);// retourne  0 <= nombre aleatoire <= nbreMots


void choisirMot(char *MotChoisi, int tailleMot); // choisi un mot dans le dico aléatoirement et le met dans MotChoisi


void choisirMotPc(char *MotPc,char *mot_heuristique, liste_mot *mot_deja_entrer, int tailleMot); //choisi un mot dans le dico aléatoirement et le met dans MotPc


int motExiste(char *mot); //verifier l'existence d'un mot dans le dico


void Color(int couleurDuTexte,int couleurDeFond); // fonction d'affichage de couleurs



void verifier(char *MotChoisi,char *MotEntrer, int *trouve, int taille);




void Grille(char **tab, int **trouve, int ligne, int colonne, int ligne_heuristique);



void affecterNbVisbible(char *MotChoisi, char *motDebut, int *trouve, int nbLettreV); //affecter nbLettreV au mot avant de commencer le jeu




void controler_mot_entrer(int contient_chiffre, int tailleMot, char *tab, liste_mot *L);



int verifier_contient_chiffre(char *tab, int tailleMot);







void rendreMotMinuscule(char *mot); // convertir tous les lettres en minuscule


void rendreMotMajuscule(char *mot); // convertir tous les lettres en majuscule


void Menu();


void nouvellePartie(); //debut du jeu



void seulJoueur();

void joueurOrdinateur();

void deuxJoueurs();





















#endif
