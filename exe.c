

#include "dico.h"
#include <myconio.h>

//declaration des prototypes des fonctions
//void seulJoueur();
//void joueurOrdinateur();
//void deuxJoueurs();
//-------------------
//void nouvellePartie();
//void chargerPartie();
//void profile();
//void Apropos();
//void textbackground(int _color);
//------------------------










void verifier(char *MotChoisi,char *MotEntrer, int *trouve, int taille)
{
    int i,j;
    char temp[4]=" ";

    strcpy(temp,MotChoisi);

    for(i=0; i<taille; i++)
    {
        if(MotEntrer[i]== temp[i])
        {
            trouve[i]=1;
            temp[i]='#';
        }
    }

    /* Chercher Les Lettres Communes Mal  Placees */
    for(i=0; i<taille; i++)
    {
        for(j=0; j<taille; j++)
            if(MotEntrer[i]==temp[j] && trouve[i]!=1)
            {
                trouve[i]=2;
                temp[j]='#';
                break;
            }
    }

}








void afficherLettreCouleur(char **tab, int **trouve, int ligne, int colonne)
{
    system("cls");



    for(int i=0; i<colonne; i++)
        printf("+-----");

    printf("+\n");

    for(int i=0; i<ligne; i++)
    {
        ;
        if(motExiste(tab[i]) == 1) // si le mot existe dans le dico
        {
            for(int j=0; j<colonne; j++)
            {

                if(trouve[i][j]==1)
                {
                    printf("|");
                    textcolor(GREEN); // on colorie la lettre par la couleur vert
                    printf("  %c  ",tab[i][j]);
                    textcolor(LIGHTGRAY);
                }
                else
                {
                    if(trouve[i][j]==2)
                    {
                        printf("|");
                        textcolor(YELLOW); //on colorie la lettre par la couleur jaune
                        printf("  %c  ",tab[i][j]);
                        textcolor(LIGHTGRAY);//revenir au couleur par defaut
                    }
                    else
                    {
                        printf("|  %c  ",tab[i][j]);
                    }
                }


            }
        }
        else //n'appartient pas au dico
            for(int j=0; j<colonne; j++)
                printf("|  %c  ",tab[i][j]);


        printf("|\n");

        for(int i=0; i<colonne; i++)
            printf("+-----");

        printf("+\n");
    }
}













void affecterNbVisbible(char *MotChoisi, char *motDebut, int *trouve, int nbLettreV) //affecter nbLettreV au mot avant de commencer le jeu
{

    for(int k=0; k<nbLettreV; k++)
    {

        int num=nombreAleatoire(strlen(MotChoisi));
        while(trouve[num] == 1)
            num=nombreAleatoire(strlen(MotChoisi));

        trouve[num]=1;

    }

    for(int j=0; j<strlen(MotChoisi); j++)
        if(trouve[j] == 0)
            motDebut[j]=' ';
        else
            motDebut[j]=MotChoisi[j];

}











void nouvellePartie() //debut du jeu
{
    printf("Choisir le mode du jeu : \n");
    printf("1) un seul joueur.\n");
    printf("2) un joueur contre l'ordinateur.\n");
    printf("3) un joueur contre un autre joueur.\n");
    int mode=0;
    scanf("%d",&mode);
    clrscr(); //vider l'ecran
    switch(mode)
    {
    case 1:
        //seulJoueur();
        break;

    case 2:
        joueurOrdinateur();
        break;

    case 3:
        //deuxJoueurs();
        break;

    default:
        printf("choix invalide");
        break;
    }
}



void chargerPartie()
{
    printf("\ncharger partie !\n");
}





void profile()
{
    printf("\nprofil !\n");
}




void Apropos()
{
    printf("\na propos !\n");
}







void Menu()
{
    printf("\n   Hello Motus!\n\n");
    printf("1) Nouvelle partie.\n");
    printf("2) Charger partie.\n");
    printf("3) Profil.\n");
    printf("4) A propos du jeu.\n");
    printf("5) Quitter le jeu.\n\n");
    printf("Entrer votre choix : ");
    int choix=0;
    scanf("%d",&choix);
    system("cls"); //vider l'ecran

    switch(choix)//selon le choix de l'utilisateur
    {
    case 1:
        nouvellePartie();
        break;

    case 2:
        chargerPartie();
        break;

    case 3:
        profile();
        break;

    case 4:
        Apropos();
        break;

    case 5:
        printf("vous avez quitter le jeu!\n");
        exit(0);

    default:
        Menu(); //reafficher le menu
        break;
    }

}









void rendreMotMajuscule(char *mot) // convertir tous les lettres en majuscule
{
    for(int z=0; z<strlen(mot); z++)
    {
        if(mot[z]>='a' && mot[z]<='z')
            mot[z]=mot[z]-'a'+'A';
    }

}




void rendreMotMinuscule(char *mot) // convertir tous les lettres en minuscule
{
    for(int z=0; z<strlen(mot); z++)
    {
        if(mot[z]>='A' && mot[z]<='Z')
            mot[z]=mot[z]-'A'+'a';
    }
}










