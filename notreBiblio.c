
#include "notreBiblio.h"
#include "sauvgarde_charge.h"




//Création de la liste des mots entrés
liste_mot *creer_liste_mot(int id_mot,char *mot)
{

    liste_mot *m = malloc(sizeof(liste_mot));
    m->id_mot=id_mot;
    strcpy(m->mot,mot);
    m->suivant=NULL;

    return m;
}



//Insértion du mot dans cette liste
liste_mot *inserer_mot(liste_mot *liste, liste_mot *m)
{
    if(liste==NULL)
        return m;

    liste_mot *p = liste;
    while(p->suivant != NULL)
        p=p->suivant;
    p->suivant=m;

    return liste;
}




//Choix d'un mot par l'ordinateur
void choisirMotPc(char *MotPc,char *mot_heuristique,liste_mot *mot_deja_entrer, int tailleMot)
{
    liste_mot *liste=NULL;
    liste_mot *L1=NULL;
    liste_mot *L2=NULL;

    char file[10]=""; //pour y stocker le nom du fichier utilise.

    switch(tailleMot)
    {
    case 6 :
        strcpy(file,"dico6.txt");
        break;
    case 7 :
        strcpy(file,"dico7.txt");
        break;
    case 8 :
        strcpy(file,"dico8.txt");
        break;
    case 9 :
        strcpy(file,"dico9.txt");
        break;
    case 10 :
        strcpy(file,"dico10.txt");
        break;
    default :
        printf("erreurPc");
    }





    char mot[11]=""; // aide lors la lecture dans le fichier
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

    //pour controler la jouabilite de l'ordinateur
    /*---------------------------------------------------------------------*/
    int id=0;
    int cpt_heuristique=0; //calcul le nombre des lettres visibles
    for(int i=0; i<tailleMot; i++)
        if(mot_heuristique[i] != ' ')
            cpt_heuristique++;

    while(fscanf(dico,"%s",mot) != EOF)
    {
        int cpt_temp=0;
        for(int i=0; i<tailleMot; i++)
            if(mot[i]==mot_heuristique[i])
                cpt_temp++;

        if(cpt_temp==cpt_heuristique)
        {
            liste_mot *m=creer_liste_mot(id,mot);
            liste= inserer_mot(liste,m);
            id++;
            nbreMots++;
        }
    }

    /*---------------------------------------------------------------------*/

    do
    {
        numMotChoisi=nombreAleatoire(nbreMots);// 0 <= numMotChoisi <= nombre de mots de la liste

        L1=liste;
        while(L1 != NULL && L1->id_mot!=numMotChoisi)
            L1=L1->suivant;
        L1->mot[tailleMot]='\0';

        L2=mot_deja_entrer;
        while(L2 != NULL && strcmp(L2->mot,L1->mot)!=0)
            L2=L2->suivant;


    }
    while(L2 != NULL);

    L1->mot[tailleMot]='\0';
    strcpy(MotPc,L1->mot);




    fclose(dico);
    return; // tout est bien passe
}









void choisirMot(char *MotChoisi, int tailleMot) //choisi le mot secret aleatoiremment dans le dico
{

    char file[10]=""; //pour y stocker le nom du fichier utilise




    switch(tailleMot)
    {
    case 6 :
        strcpy(file,"dico6.txt");
        break;
    case 7 :
        strcpy(file,"dico7.txt");
        break;
    case 8 :
        strcpy(file,"dico8.txt");
        break;
    case 9 :
        strcpy(file,"dico9.txt");
        break;
    case 10 :
        strcpy(file,"dico10.txt");
        break;
    default :
        printf("erreur_choisir_mot\n");
    }



    char mot[11]=""; // aide lors la lecture dans le fichier
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
    MotChoisi[tailleMot]='\0';
    //rendreMotMajuscule(MotChoisi);

    fclose(dico);
    return; // tout est bien passe
}






int motExiste(char *mot)
{
    char file[10]=""; //pour y stocker le nom du fichier utilise

    // ouvrir le dico selon la taille du mot
    switch(strlen(mot))
    {
    case 6 :
        strcpy(file,"dico6.txt");
        break;
    case 7 :
        strcpy(file,"dico7.txt");
        break;
    case 8 :
        strcpy(file,"dico8.txt");
        break;
    case 9 :
        strcpy(file,"dico9.txt");
        break;
    case 10 :
        strcpy(file,"dico10.txt");
        break;
    default :
        return 0;//break;
    }



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












void verifier(char *MotChoisi,char *MotEntrer, int *trouve, int taille)
{
    int i,j;
    char *temp= malloc(taille*sizeof(char));
    MotChoisi[taille]='\0';
    MotEntrer[taille]='\0';
    strcpy(temp,MotChoisi);

    /* Chercher Les Lettres Communes Bien  Placees */
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
                temp[j]='@';
                break;
            }
    }
    free(temp);
}






void Grille(char **tab, int **trouve, int ligne, int colonne, int ligne_heuristique)
{
    system("cls");
    Color(15,0);

    printf("\n\n\n");
    for(int i=0; i<colonne; i++)
        printf("+-----");

    printf("+\n");

    for(int i=0; i<ligne; i++) //affichage des lignes
    {
        if(motExiste(tab[i]) == 1 && i != ligne_heuristique) // si le mot existe dans le dico
        {

            for(int j=0; j<colonne; j++)//affichage des colonnes
            {
                if(trouve[i][j]==1)
                {
                    Color(15,0);
                    printf("|");
                    Color(10,0);// on colorie la lettre par la couleur vert
                    printf("  %c  ",tab[i][j]);
                    Color(15,0);
                }
                else
                {
                    if(trouve[i][j]==2)
                    {
                        Color(15,0);
                        printf("|");
                        Color(14,0);//on colorie la lettre par la couleur jaune
                        printf("  %c  ",tab[i][j]);
                        Color(15,0);//revenir au couleur par defaut

                    }
                    else
                    {
                        Color(15,0);
                        printf("|  %c  ",tab[i][j]);
                    }
                }


            }
        }
        else //le mot n'existe pas dans le dico
        {
            if(i == ligne_heuristique)
            {
                Color(3,0);
                for(int j=0; j<colonne; j++)//affichage des colonnes
                {
                    printf("|  %c  ",tab[i][j]);
                }
                Color(7,0);
            }
            else
            {
                Color(15,0);
                for(int j=0; j<colonne; j++)
                    printf("|  %c  ",tab[i][j]); //affichage normal sans couleur
            }

        }

        Color(15,0);
        printf("|\n");
        for(int i=0; i<colonne; i++)
            printf("+-----");

        printf("+\n");
    }
    Color(6,0);
    printf(" Pour quitter la partie tapez &.\n\n");
    Color(7,0);
}








int nombreAleatoire(int nbreMots) // 0 <= genere un nombre aleatoires <= nbreMots
{
    srand(time(NULL)); // initialiser le generateur du temps a 0
    return (rand()%nbreMots);

}







void affecterNbVisbible(char *MotChoisi, char *motDebut, int *trouve, int nbLettreV) //affecter nbLettreV au mot avant de commencer le jeu
{
    trouve[0]=1;
    motDebut[0]=MotChoisi[0];
    for(int k=1; k<nbLettreV; k++)
    {
        int num=nombreAleatoire(strlen(MotChoisi));
        while(trouve[num] == 1)
            num=nombreAleatoire(strlen(MotChoisi));

        trouve[num]=1;

    }

    for(int j=1; j<strlen(MotChoisi); j++)
        if(trouve[j] == 0)
            motDebut[j]=' ';
        else
            motDebut[j]=MotChoisi[j];

}








int verifier_contient_chiffre(char *tab, int tailleMot)
{
    int contient_chiffre=1; // 1: contient au moins un chiffre et 0: contient aucun chiffre

    int temp_cpt=0;
    for(int z=0; z<strlen(tab) && strlen(tab)<=tailleMot; z++)
        if(tab[z]>='A' && tab[z]<='Z')
            temp_cpt++;

    if(temp_cpt == strlen(tab))//strlen(tab) && strlen(tab)<=tailleMot) //ne contient que des lettres
        contient_chiffre=0;

    return contient_chiffre;
}








void controler_mot_entrer(int contient_chiffre, int tailleMot, char *tab, liste_mot *L)
{
    if(strlen(tab) > tailleMot)
    {
        Color(12,0);
        printf("\tMot invalide, il a depasse %d lettres.\n",tailleMot);
        Color(7,0);
    }
    if(strlen(tab) < tailleMot && contient_chiffre == 0)
    {
        Color(12,0);
        printf("\tMot invalide, la longueur est inferieur a %d lettres.\n",tailleMot);
        Color(7,0);
    }

    if(L != NULL)
    {
        Color(12,0);
        printf("\tMot invalide, deja existe.\n");
        Color(7,0);
    }
    if(contient_chiffre == 1 && strlen(tab) <= tailleMot)
    {
        Color(12,0);
        printf("\tMot invalide, il contient des chiffres ou des caracteres speciaux.\n");
        Color(7,0);
    }
}









void nouvellePartie() //debut du jeu
{
    Color(15,0);
    printf("\n\n +================< CHOIX DU MODE DU JEU >================+\n");
    printf(" |                                                        |\n");
    printf(" |            1) un seul joueur.                          |\n");
    printf(" |            2) un joueur contre l'ordinateur.           |\n");
    printf(" |            3) un joueur contre un autre joueur.        |\n");
    printf(" |            4) Retour vers le menu principal.           |\n");
    printf(" |                                                        |\n");
    printf(" +========================================================+\n");
    printf("\n   Entrer votre choix : ");
    int mode=0;
    fflush(stdin);
    scanf("%d",&mode);
    Color(7,0);

    while(mode <=0 || mode >=5) // en cas de choix invalide
    {
        Color(12,0);
        printf("      Choix invalide !\n");
        Color(7,0);
        Color(15,0);
        printf("\n   Entrer a nouveau votre choix : ");
        fflush(stdin);
        scanf("%d",&mode);
        Color(7,0);
    }
    system("cls"); //vider l'ecran
    switch(mode)
    {
    case 1:
        seulJoueur();
        break;

    case 2:
        joueurOrdinateur();
        break;
    case 3:
        deuxJoueurs();
        break;
    case 4:
        Menu();
        break;

    default:
        nouvellePartie();
        break;
    }
}




void chargerPartie()
{
     char  PseudoCharge[30]=" ";
    couleur(14,0);
    printf("\n\n\n  ----> Vous avez choisi de charger une partie !\n\n");
    printf("\t----> Donnez votre Pseudo ou & pour quitter:  ");
        couleur(15,0);

    scanf("%s",PseudoCharge);
    couleur(15,0);
    if(PseudoCharge[0]=='&')
    {
        system("cls");
        Menu();
    }
    afficher_Partie_Sauv(PseudoCharge);
    lire_Partie_Existe(PseudoCharge);
}












void Aide()
{
    char file[10]="Aide.txt"; //pour y stocker le nom du fichier utilise

    char mot[100]=""; // aide lors la lecture dans le fichier
    FILE *help=NULL; // pointeur vers le dico

    help = fopen(file,"r"); //ouvrir le fichier en mode de lecture seule

    if(help==NULL) // l'ouverture de fichier a echoue
    {
        printf("\tImpossible d'ouvrir le fichier");
        fclose(help);
    }


    while(fgets(mot,sizeof(mot),help) != NULL)
    {
        Color(15,0);
        printf(" %s",mot);
    }
    Color(7,0);


    fclose(help);



    char retour=' ';
    Color(6,0);
    printf("\n          Pour revenir au menu principal, appuyez sur '&'. ");
    Color(7,0);
    fflush(stdin);
    Color(15,0);
    scanf("%c",&retour);
    Color(7,0);

    while(retour != '&') /*en cas d'erreur de frappe*/
    {
        Color(12,0);
        printf("    Choix invalide !\n");
        Color(7,0);

        Color(15,0);
        printf("\n   Veuillez appuyez sur '&' : ");
        fflush(stdin);
        scanf("%c",&retour);
        Color(7,0);
    }
    Menu();
}




void Menu()
{
    system("cls");
    int choix=0;
    Color(15,0);
    printf("\n\n +=====================< MENU PRINCIPAL >=====================+\n");
    printf(" |                                                            |\n");
    printf(" |                         M O T U S                          |\n");
    printf(" |============================================================|\n");
    printf(" |                                                            |\n");
    printf(" |                     1) Nouvelle partie.                    |\n");
    printf(" |                     2) Charger partie.                     |\n");
    printf(" |                     3) Aide.                               |\n");
    printf(" |                     4) Quitter le jeu.                     |\n");
    printf(" |                                                            |\n");
    printf(" +============================================================+\n\n");

    printf("    Entrez votre choix : ");
    fflush(stdin);
    scanf("%d",&choix);
    Color(7,0);


    while(choix <=0 || choix >=5)
    {
        Color(12,0);
        printf("      Choix invalide !\n");
        Color(7,0);
        Color(15,0);
        printf("\n   Entrez a nouveau votre choix : ");
        fflush(stdin);
        scanf("%d",&choix);
        Color(7,0);
    }

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
        Aide();
        break;

    case 4:
        exit(0);

    default:
        Menu(); //reafficher le menu
        break;
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




void rendreMotMajuscule(char *mot) // convertir tous les lettres en majuscule
{
    for(int z=0; z<strlen(mot); z++)
    {
        if(mot[z]>='a' && mot[z]<='z')
            mot[z]=mot[z]-'a'+'A';
    }

}



void Color(int couleurDuTexte,int couleurDeFond) // fonction d'affichage de couleurs
{
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
}













