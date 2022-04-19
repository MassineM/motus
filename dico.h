#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



#ifndef DEF_DICO
#define DEF_DICO


struct joueur    //la structure du joueur
{
    char *nom;
    int tentative;
    double duree;
};

typedef struct joueur joueur;





int nombreAleatoire(int nbreMots);// retourne  0 <= nombre aleatoire <= nbreMots


void choisirMot(char *MotChoisi); // choisi un mot dans le dico aléatoirement et le met dans MotChoisi


void choisirMotPc(char *MotPc, int tailleMot); //choisi un mot dans le dico aléatoirement et le met dans MotPc


int motExiste(char *mot); //verifier l'existence d'un mot dans le dico



#endif
