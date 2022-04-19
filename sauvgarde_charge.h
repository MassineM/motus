
#include <dirent.h>
#define MAXCHAINE 250 /* La longeur maximum d'une chaine de caractere */
#define Max 100 // dimention de tableau des noms


#ifndef DEF_SAUV
#define DEF_SAUV


struct joueur    //la structure du joueur
{
     char pseudo[Max];
     int score;
     int nbPartieG;
     float duree;
     char niveau[MAXCHAINE];
     int enregistrer;

};
typedef struct joueur Joueur;



typedef struct niveau
{
    int nbreTenta;
    int tailleMot;
    int nbreLettreV;
}Niveau;


int creerDossier(char * pseudo);

void couleur(int text,int fond);

Joueur * creerJoueur(char nom[]);

void sauvegarder_Partie(Joueur * joueur,char**tab,int ligne,int colonne,char *motChoisi,int nbtentative,int Mode);

void afficher_niveau();

void lire_Partie_Existe(char* pseudo);

//void supprimerPartie(char * adrs);
//void afficherStatistiques(Joueur * joueur)

void afficher_Partie_Sauv(char * pseudo);

void Charge_seulJoueur(Joueur*monjoueur,char **table,int ligne,int colonne,char*motDico,int nbtenta);

void Charge_joueurOrdinateur(Joueur*monjoueur,char **table,int ligne,int colonne,char*motDico,int nbtenta);

void Charge_deuxJoueurs(Joueur*monjoueur,char **table,int ligne,int colonne,char*motDico,int nbtenta);



#endif
