
#include "dico.h"


void choisirMot(char *MotChoisi) //choisi le mot secret aleatoiremment dans le dico
{
    int tailleMot=0;

    char file[12]=""; //pour y stocker le nom du fichier utilise

    do
    {
        printf("\nChoisissez la taille du mot, 6 ou 7 lettres : ");
        scanf("%d",&tailleMot);

    }while(tailleMot!=6 && tailleMot!=7);


    if(tailleMot==6)
        strcpy(file,"dico6.txt");
    if(tailleMot==7)
        strcpy(file,"dico7.txt");



    char mot[10]=""; // aide lors la lecture dans le fichier
    FILE *dico=NULL; // pointeur vers le dico
    int nbreMots=0;  // nombre de mots dans le dico
    int numMotChoisi=0; // numero de la ligne du mot choisi

    dico = fopen(file,"r"); //ouvrir le fichier en mode de lecture seule

    if(dico==NULL) // l'ouverture de fichier a echoue
    {
        printf("\tImpossible d'ouvrir le fichier");
        fclose(dico);
        return;
    }


    while(fscanf(dico,"%s",mot) != EOF)
        nbreMots++;//calcul le nombre de mots dans le dico

    numMotChoisi=nombreAleatoire(nbreMots);// 0 <= numMotChoisi <= nombre de mots du dico


    rewind(dico); // curseur a la position 0 du fichier

    while(numMotChoisi > 0) //pour stationner le curseur devant la ligne du mot secret
    {
        int c = fgetc(dico);
        if(c == '\n')
            numMotChoisi--;
    }

    fscanf(dico,"%s",MotChoisi);
    MotChoisi[strlen(MotChoisi)]='\0';

    fclose(dico);
    return; // tout est bien passe
}






void choisirMotPc(char *MotPc, int tailleMot) // tailleMot sera apres 'strlen(MotChoisi)+1'
{

    char file[12]=""; //pour y stocker le nom du fichier utilise


    if(tailleMot==6)
        strcpy(file,"dico6.txt");
    if(tailleMot==7)
        strcpy(file,"dico7.txt");



    char mot[10]=""; // aide lors la lecture dans le fichier
    FILE *dico=NULL; // pointeur vers le dico
    int nbreMots=0;  // nombre de mots dans le dico
    int numMotChoisi=0; // numero de la ligne du mot choisi

    dico = fopen(file,"r"); //ouvrir le fichier en mode de lecture seule

    if(dico==NULL) // l'ouverture de fichier a echoue
    {
        printf("\tImpossible d'ouvrir le fichier");
        fclose(dico);
        return;
    }


    while(fscanf(dico,"%s",mot) != EOF)
        nbreMots++;//calcul le nombre de mots dans le dico

    numMotChoisi=nombreAleatoire(nbreMots);// 0 <= numMotChoisi <= nombre de mots du dico


    rewind(dico); // curseur a la position 0 du fichier

    while(numMotChoisi > 0) //pour stationner le curseur devant la ligne du mot secret
    {
        int c = fgetc(dico);
        if(c == '\n')
            numMotChoisi--;
    }

    fscanf(dico,"%s",MotPc);
    MotPc[strlen(MotPc)]='\0';

    fclose(dico);
    return; // tout est bien passe
}







int motExiste(char *mot)
{
    char file[12]=""; //pour y stocker le nom du fichier utilise

    // ouvrir le dico selon la taille du mot
    if(strlen(mot)==6)
        strcpy(file,"dico6.txt");
    if(strlen(mot)==7)
        strcpy(file,"dico7.txt");

    char temp[10]="";
    FILE *dico=NULL; // pointeur vers le dico
    dico = fopen(file,"r"); //ouvrir le fichier en mode lecture seule


    while(fscanf(dico,"%s", temp) != EOF) //lire d'apres le fichier tant qu'on est pas arrive a sa fin
    {
        if(strcmp(mot,temp)==0) // si mot et temp sont identiques
        {
            fclose(dico);
            return 1; // le mot existe dans le dico
        }

    }

    fclose(dico);
    return 0; // le mot n'existe pas dans le dico
}




int nombreAleatoire(int nbreMots) // 0 <= genere un nombre aleatoires <= nbreMots
{
    srand(time(NULL)); // initialiser le generateur du temps a 0
    return (rand()%nbreMots);

}
