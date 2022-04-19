#include "notreBiblio.h"
#include "sauvgarde_charge.h"

void afficher_niveau()
{
    Color(15,0);
    printf("\n      Niveaux de difficulte :\n");
    printf("------------------------------------\n");
    printf("-->  1) mots de 6 lettres.\n");
    printf("-->  2) mots de 7 lettres.\n");
    printf("-->  3) mots de 8 lettres.\n");
    printf("-->  4) mots de 9 lettres.\n");
    printf("-->  5) mots de 10 lettres.\n\n");

}

/////////////////////////////////////////////////
void afficher_Partie_Sauv(char * pseudo)
{

    char adresse[MAXCHAINE];
    strcpy(adresse,"./joueurs/");
    strcat(adresse,pseudo);
    DIR * rep = opendir(adresse);

    if (rep != NULL)
    {
        struct dirent * ent;
        /* pour eliminer le . et ..*/
        ent = readdir(rep);
        ent = readdir(rep);
        /* Parcourt de dossier */
        while ((ent = readdir(rep)) != NULL)
        {
            printf("\n\n\t\t+ ");
            couleur(11,0);
            printf("%s\n\n", ent->d_name);
            couleur(15,0);
        }
        closedir(rep);
    }
    else
    {
        couleur(4,0);
        printf("-->>\t Erreur d'ouverture le dossier \n");
        couleur(15,0);
    }
}

////////////////////////////////////////////
int creerDossier(char * pseudo)
{
    char adresse[MAXCHAINE];
    strcpy(adresse,"./joueurs/");
    int condition=0;
    DIR * rep = opendir("./joueurs/");
    if (rep != NULL)
    {
        struct dirent * ent;
        while ((ent = readdir(rep)) != NULL)
        {
            if (strcmp(pseudo,ent->d_name)==0)
            {
                couleur(10,0);
                printf("  --> Pseudo deja existe\n");
                couleur(15,0);
                condition=1;
                break;
            }
        }
    }
    if(condition == 0)
    {
        strcat(adresse,pseudo);
        pseudo[strlen(pseudo)+1]='\0';
        CreateDirectory(adresse,NULL);
    }
    return condition;
}

/////////////////////////////////////////////
void supprimerPartie(char * adrs)
{
    int confirmation=0;
    if(adrs != NULL)
    {
        couleur(4,0);
        printf("|=>\t Etes-vous sur de supprimer la partie ! 1 oui 0 si non \n");
        printf("|=>\t\t\t");
        scanf("%d",&confirmation);
        if(confirmation==1)
        {
            remove(adrs);
            couleur(10,0);
            printf("|=>\t Fichier supprime !\n");
            couleur(15,0);
        }
    }
    else
    {
        couleur(4,0);
        printf("|=>\t Erreur de suppression de fichier a l'addresse : %s\n",adrs);
        couleur(15,0);
    }
}

void couleur(int text,int fond) //1er_nombre: couleur texte 2em_nombre : couleur fond
{
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,fond*16+text);
}


//////////////////////////////////////////

/* creation d'un joueur  */
Joueur * creerJoueur(char nom[])
{
    Joueur * joueur=NULL;
    joueur=(Joueur*)malloc(sizeof(Joueur));
    joueur->score=0;
    joueur->nbPartieG=0;
    joueur->duree=0.0;
    joueur->enregistrer=0;
    strcpy(joueur->pseudo,nom);
    joueur->pseudo[strlen(joueur->pseudo)+1]='\0';
    return joueur;
}





void sauvegarder_Partie(Joueur *joueur,char**tab,int ligne,int colonne,char* motChoisi,int nbtentative, int Mode)
{
    FILE * fichier =NULL; /*  declaration d'un poiteur sur les fichier */
    char adressFichier[MAXCHAINE]; /* dessine le dossier des fichier son adresse relative a la mposition actuelle */
    strcpy(adressFichier,"./joueurs/");
    //char **tableau=NULL; /* pointer vers la grille */
    //int i=0; /* compteurs */
    if (joueur != NULL)
    {
        if(joueur->enregistrer ==0)
        {

        }
        else
        {
            strcat(adressFichier,joueur->pseudo);
            strcat(adressFichier,"/");
            strcat(adressFichier,joueur->niveau);
            adressFichier[strlen(adressFichier)+1]='\0';
            /***************************************************************/
            fichier=fopen(adressFichier,"r");
            fseek( fichier,0, SEEK_SET);
            char  lTmpCar;
            int i=0;
            char outTexteLigne[3];
            int myscore=0;
            while((lTmpCar = fgetc(fichier)) != EOF)
            {
                if(lTmpCar == '\n')
                {
                    i++;
                    if(i==12)
                    {
                        fgets(outTexteLigne,4, fichier);
                        myscore=atoi(outTexteLigne);
                    }

                }
            }
            fseek( fichier,0, SEEK_SET);
            char  itiration;
            int j=0;
            char nbPg[3];
            int myPg=0;
            while((itiration = fgetc(fichier)) != EOF)
            {
                if(itiration == '\n')
                {
                    j++;
                    if(j==13)
                    {
                        fgets(nbPg,4, fichier);
                        myPg=atoi(nbPg);
                    }

                }
            }


            fclose(fichier);
            /******************************************************************************************/


            fichier=fopen(adressFichier,"w");

            fputs(joueur->niveau,fichier);
            fprintf(fichier,"\n");

            fprintf(fichier,"%d  ",ligne);
            fprintf(fichier,"\n");

            fprintf(fichier,"%d  ",colonne);
            fprintf(fichier,"\n");

            fprintf(fichier,"%s",motChoisi);
            fprintf(fichier,"\n");

            for(int i=0; i<ligne; i++)
            {

                for(int j=0; j<colonne; j++)
                {


                    fprintf(fichier,"%c",tab[i][j]);

                }


                fprintf(fichier,"\n");


            }

            fprintf(fichier,"%d",nbtentative);
            fprintf(fichier,"\n");

            fputs(joueur->pseudo,fichier);
            fprintf(fichier,"\n");
            fprintf(fichier,"%d",joueur->score+myscore);
            fprintf(fichier,"\n");

            fprintf(fichier,"%d",joueur->nbPartieG+myPg);
            fprintf(fichier,"\n");

            fprintf(fichier,"%f",joueur->duree);
            fprintf(fichier,"\n");

            fprintf(fichier,"%d",Mode);


            fclose(fichier);
        }
        printf("   ------>  ");
        couleur(14,0);
        printf("Partie enregistree !\n");
        couleur(15,0);
        system("cls");

    }
}





//////////////////////////////////////////////////





void lire_Partie_Existe(char* pseudo)
{

    FILE * fichier =NULL; /*  declaration d'un poiteur sur les fichier */
    char adressFichier[MAXCHAINE]; /* dessine le dossier des fichier son adresse relative a la mposition actuelle */
    int Partie,myLigne,myColonne;
    char ligne[12];
    char colonne[12];
    char motSucret[12];
    char numPartie[3];
    char Niv[30];
    char grilleCharge[12];
    char nombretenta[2];
    int nb_tentative;
    int Mode=0;



    strcpy(adressFichier,"./joueurs/");
    strcat(adressFichier,pseudo);
    strcat(adressFichier,"/");

    //char **tableau=NULL; /* pointer vers la grille */

    couleur(6,0);
    printf("|=>\t Donner le numero de la partie ou -1 pour quitter !\n");
    couleur(15,0);
    printf("|=>\t\t\t");
    scanf("%d",&Partie);
    if(Partie==-1)
    {
        system("cls");
        Menu();
    }
    else
    {
        couleur(15,0);
        itoa(Partie,numPartie,10);
        strcat(adressFichier,"niveau-");
        strcat(adressFichier,numPartie);
        strcat(adressFichier,".txt");
        adressFichier[strlen(adressFichier)+1]='\0';
        fichier=fopen(adressFichier,"r");
        if(fichier==NULL)
        {
            couleur(4,0);
            printf("|=>\t Partie n'existe pas\n");
            couleur(15,0);
        }
        else
        {

            fseek( fichier,0, SEEK_SET);
            fgets(Niv,sizeof(Niv),fichier);
            fgets(ligne,sizeof(ligne),fichier);
            fgets(colonne,sizeof(colonne),fichier);
            fgets(motSucret,sizeof(motSucret),fichier);

            myLigne =atoi(ligne);
            myColonne =atoi(colonne);

            motSucret[myColonne]='\0';

            char** tableau_Recup=calloc(myLigne,sizeof(char*));
            for(int x=0; x<myLigne; x++)
            {
                tableau_Recup[x]= calloc(myColonne,sizeof(char));

            }



            for(int j=0; j<myLigne; j++)
            {

                fgets(grilleCharge,sizeof(grilleCharge),fichier);

                strcpy(tableau_Recup[j],grilleCharge);
                tableau_Recup[myColonne]='\0';

            }
            fgets(nombretenta,sizeof(nombretenta),fichier);
            nb_tentative=atoi(nombretenta);


            char fMode[20];
            for(int i=1; i<=6; i++)
                fgets(fMode,sizeof(fMode),fichier);

            Mode=atoi(fMode);
            printf("Mode : %d",Mode);
            getch();



////////////////////////////

//creation d'une structure joueur
            Joueur*monjoueur=NULL;
            monjoueur=creerJoueur(pseudo);
            strcpy(monjoueur->niveau,Niv);
            switch(Mode)
            {
            case 1 :
                Charge_seulJoueur(monjoueur,tableau_Recup,myLigne,myColonne,motSucret,nb_tentative);
                break;

            case 2 :
                Charge_joueurOrdinateur(monjoueur,tableau_Recup,myLigne,myColonne,motSucret,nb_tentative);
                break;
            case 3 :
                Charge_deuxJoueurs(monjoueur,tableau_Recup,myLigne,myColonne,motSucret,nb_tentative);
                break;

            default :
                printf(" Erreure de chargement !\n");
                break;
            }

            fclose(fichier);
        }


    }
}





/////////////////////////////////////////////////////////////////////////////////////
void Charge_joueurOrdinateur(Joueur*monjoueur,char **tab,int ligne,int colonne,char*motDico,int nbtenta)
{


    liste_mot *mot_deja_entrer=NULL;
    liste_mot *L=NULL;
    int id=0; //id du mot_deja_enter

    int Mode=2;



    int enregistrer;
    int nbPartieG=0;
    float time;
    int score=0;
    int i=nbtenta; // pour parcourir les tableaux


    char MotChoisi[8]; //pour y stocker le mot secret
    strcpy(MotChoisi,motDico);


    system("cls");


    printf("\nLe mot est : %s\n",MotChoisi);
    getch(); // c'est a nous,pour afficher le motChoisi





    int **trouve=(int**) calloc(ligne,sizeof(int*));
    for(int x=0; x<ligne; x++)
        trouve[x]=(int*) calloc(colonne,sizeof(int));



    int *numero_heuristique = calloc(colonne,sizeof(int));
    char *lettre_heuristique = calloc(colonne,sizeof(char));

    if(i<ligne)
        strcpy(lettre_heuristique,tab[i]);


    if(lettre_heuristique[0]=='&')
        for(int x=0; x<colonne; x++)
            lettre_heuristique[x]=' ';

    for(int x=0; x<colonne; x++)
    {
        if(lettre_heuristique[x] != ' ')
            numero_heuristique[x]=1;
        else
            tab[i][x] = '.';
    }


    for(int y=0; y<ligne; y++)
    {

        verifier(MotChoisi,tab[y],trouve[y],colonne);

        for(int x=0; x<colonne; x++)
            if(trouve[y][x]==1)
            {
                numero_heuristique[x]=1;
                lettre_heuristique[x]=tab[y][x];
            }



        for(int x=0; x<colonne; x++)
        {

            if(numero_heuristique[x]==1 && i!=6)
            {

                trouve[i][x]=1;
                tab[i][x]=lettre_heuristique[x];
            }
            if(numero_heuristique[x]==0 && i!=6)
                tab[i][x]='.';
        }


    }


    Grille(tab, trouve,ligne,colonne,i);



    for(int x=0; x<i; x++)
    {
        liste_mot *mot_grille=creer_liste_mot(id,tab[x]);
        mot_deja_entrer= inserer_mot(mot_deja_entrer,mot_grille);
        id++;
    }


    if(i==6 || i==5)              //si la partie est déja fini
    {

        couleur(4,0);
        printf("\tPartie deja jouee\n");
        couleur(15,0);
        afficher_Partie_Sauv(monjoueur->pseudo);
        lire_Partie_Existe(monjoueur->pseudo);

    }



    else
    {
        int cal=0;
        for(int a=0; a<ligne; a++)
        {
            if(strcmp(tab[a],MotChoisi) ==0)
                cal++;
        }
        if(cal!=0)
        {
            printf("partie finie choisir autre partie");
            afficher_Partie_Sauv(monjoueur->pseudo);
            lire_Partie_Existe(monjoueur->pseudo);


        }

        else
        {

            time = 0;
            int cpt_tenta=i; //compteur des tentatives du joueur
            do
            {

                if(i%2 == 0)//si le tour du joueur
                {
                    /*reeinitialisation de ligne de trouve*/
                    for(int x=0; x<colonne; x++)
                        trouve[i][x]=0;

                    printf("\n--> Le tour du joueur.\n");

                    Color(15,0);
                    printf("  Il vous reste %d tentatives, tapez votre mot : ",(cpt_tenta));

                    fflush(stdin); // vider la memoire du clavier avant la saisie
                    scanf("%s",tab[i]);
                    Color(7,0);

                    if(tab[i][0]=='&')
                        break;

                    rendreMotMajuscule(tab[i]);

                    L=mot_deja_entrer;
                    while(L != NULL && strcmp(L->mot,tab[i])!=0)
                        L=L->suivant;

                    // 1: contient au moins un chiffre et 0: contient aucun chiffre
                    int contient_chiffre=verifier_contient_chiffre(tab[i],colonne);


                    /*en cas d'erreur*/
                    while((contient_chiffre == 1 && strlen(tab[i]) <= colonne) || strlen(tab[i]) > colonne || strlen(tab[i]) < colonne || L != NULL)
                    {
                        controler_mot_entrer(contient_chiffre,colonne,tab[i],L);

                        Color(15,0);
                        printf("  Veuillez retapez votre mot : ");
                        fflush(stdin); // vider la memoire du clavier avant la saisie
                        scanf("%s",tab[i]);
                        Color(7,0);
                        if(tab[i][0]=='&')
                            break;
                        rendreMotMajuscule(tab[i]);

                        // 1: contient au moins un chiffre et 0: contient aucun chiffre
                        contient_chiffre=verifier_contient_chiffre(tab[i],colonne);

                        L=mot_deja_entrer;
                        while(L != NULL && strcmp(L->mot,tab[i])!=0)
                            L=L->suivant;

                    } // fin de la controle du mot entre par l'utilisateur

                    cpt_tenta--;

                    if(tab[i][0]=='&')
                        break;

                    /*----------------------------------------------------*/
                    //on remplit la liste par les mots qui existent dans la grille

                    liste_mot *mot_grille=creer_liste_mot(id,tab[i]);
                    mot_deja_entrer= inserer_mot(mot_deja_entrer,mot_grille);
                    id++;
                    /*----------------------------------------------------*/



                    if(motExiste(tab[i])==1)
                        verifier(MotChoisi,tab[i],trouve[i],colonne);





                    /*--------------------------------------------*/
                    if(i<nbtenta-1)
                    {
                        for(int x=0; x<colonne; x++)
                            if(trouve[i][x]==1)
                            {
                                numero_heuristique[x]=1;
                                lettre_heuristique[x]=tab[i][x];
                            }


                        for(int x=0; x<colonne; x++)
                        {
                            if(numero_heuristique[x]==1)
                            {
                                trouve[i+1][x]=1;
                                tab[i+1][x]=lettre_heuristique[x];
                            }
                            if(numero_heuristique[x]==0)
                                tab[i+1][x]='.';
                        }

                    }
                    /*--------------------------------------------*/

                    //calcul du nombre de lettres bien placees
                    int cpt=0;
                    for(int z=0; z<colonne; z++)
                        if(trouve[i][z]==1)
                            cpt++;




                    if(cpt == colonne ) //s'il a trouve le mot
                    {
                        if(i<ligne-1)
                            for(int x=0; x<colonne; x++)
                                tab[i+1][x]=0;

                        Grille(tab, trouve,ligne,colonne,(i+1));
                        Color(10,0);
                        printf("\nBravo '%s' vous avez trouver le mot.\n\n",monjoueur->pseudo);
                        Color(7,0);
                        /*************************/
                        time = clock()*0.001;
                        nbPartieG++;
                        score+=5;
                        /**********************/
                        break; // quitter la partie
                    }
                    else
                        Grille(tab, trouve,ligne,colonne,(i+1));
                }



                if(i%2 != 0)//si le tour de l'ordinateur
                {
                    /*reeinitialisation de ligne de trouve*/
                    for(int x=0; x<colonne; x++)
                        trouve[i][x]=0;

                    printf("\n-->Le tour d'ordinateur.\n ");
                    choisirMotPc(tab[i],lettre_heuristique,mot_deja_entrer,colonne);
                    Color(15,0);
                    printf("    Le mot propose est : '%s', appuyez sur entrer", tab[i]);
                    Color(7,0);
                    verifier(MotChoisi,tab[i],trouve[i],colonne);
                    getch();


                    /*----------------------------------------------------*/
                    //on remplit la liste par les mots qui existent dans la grille

                    liste_mot *mot_grille=creer_liste_mot(id,tab[i]);
                    mot_deja_entrer= inserer_mot(mot_deja_entrer,mot_grille);
                    id++;
                    /*----------------------------------------------------*/




                    /*--------------------------------------------*/
                    if(i<ligne-1)
                    {
                        for(int x=0; x<colonne; x++)
                            if(trouve[i][x]==1)
                            {
                                numero_heuristique[x]=1;
                                lettre_heuristique[x]=tab[i][x];
                            }


                        for(int x=0; x<colonne; x++)
                        {
                            if(numero_heuristique[x]==1)
                            {
                                trouve[i+1][x]=1;
                                tab[i+1][x]=lettre_heuristique[x];
                            }
                            if(numero_heuristique[x]==0)
                                tab[i+1][x]='.';
                        }
                    }
                    /*--------------------------------------------*/



                    int cpt=0;
                    for(int z=0; z<colonne; z++)
                        if(trouve[i][z]==1)
                            cpt++;



                    if(cpt == colonne ) //s'il a trouve le mot
                    {
                        if(i<ligne-1)
                            for(int x=0; x<colonne; x++)
                                tab[i+1][x]=0;
                        Grille(tab, trouve,ligne,colonne,(i+1));
                        printf("\n Perdu, l'ordinateur a pu deviner le mot secret.\n\n");

                        break; // on quitte le jeu
                    }
                    else //s'il n'a pas trouve le mot
                        Grille(tab, trouve,ligne,colonne,i+1);


                }


                i++; // on incremente a l'essaye suivant
            }
            while(i<ligne);  // tant qu'on est pas depasser le nbtenta


            if(i== ligne) // si on a depasser le nbtenta
            {
                printf("\n Perdu, le mot cherche etait bien : %s.\n",MotChoisi);
                time = clock()*0.001;
            }



            monjoueur->duree=time;
            monjoueur->nbPartieG=nbPartieG;
            monjoueur->score=score;
            printf("|=>\t Vous souhaitez enregistrer votre partie\n");
            printf("|=>\t Tapez 1 si oui ou 0 si non\n");
            printf("|=>\t\t\t");
            scanf("%d",&enregistrer);
            monjoueur->enregistrer=enregistrer;


            sauvegarder_Partie(monjoueur,tab,ligne,colonne,MotChoisi,i,Mode);


            /* liberer les espaces alloue*/
            for(int i=0; i<ligne; i++)
                free(trouve[i]);
            free(trouve);

            for(int i=0; i<ligne; i++)
                free(tab[i]);
            free(tab);


            free(numero_heuristique);
            free(lettre_heuristique);



            //------------> FIN DU JEU <-------------






            //Pour une autre partie
            printf("   \n\nQue Voulez-vous faire ?\n");
            printf("   -----------------------------------\n");
            printf("    1)Recommencer une nouvelle partie.\n");
            printf("    2)Changer le mode du jeu.\n");
            printf("    3)Retour vers le menu principal.\n");
            printf("    4)Quitter le jeu.\n");
            int decision=0; //pour y stocker la decision du joueur
            Color(15,0);
            printf("      Entrer votre choix : ");
            fflush(stdin);
            scanf("%d",&decision);
            Color(7,0);


            //Pour une autre partie

            while(decision<=0 || decision >=5) // en cas de choix invalide
            {
                Color(12,0);
                printf("\tChoix invalide.\n");
                Color(7,0);

                Color(15,0);
                printf("      Entrez a nouveau votre choix : ");
                fflush(stdin);
                scanf("%d",&decision);
                Color(7,0);
            }

            if(decision ==1)
            {
                system("cls"); // clean screen
                deuxJoueurs(); // appel recursive de la fonction du debut du jeu
            }
            if(decision ==2)
            {
                system("cls"); // clean screen
                nouvellePartie(); // appel recursive de la fonction du debut du jeu
            }
            if(decision ==3)
            {
                system("cls"); // clean screen
                Menu(); //appel recursive de la fonction qui affiche le menu
            }
            if(decision ==4)
            {
                exit(0);
            }

        }
    }
}









void Charge_seulJoueur(Joueur*monjoueur,char **tab,int ligne,int colonne,char*motDico,int nbtenta)
{

    liste_mot *mot_deja_entrer=NULL;
    liste_mot *L=NULL;
    int id=0; //id du mot_deja_enter

    int Mode=1;



    int enregistrer;
    int nbPartieG=0;
    float time;
    int score=0;
    int i=nbtenta; // pour parcourir les tableaux


    char MotChoisi[8]; //pour y stocker le mot secret
    strcpy(MotChoisi,motDico);


    system("cls");


    printf("\nLe mot est : %s\n",MotChoisi);
    getch(); // c'est a nous,pour afficher le motChoisi





    int **trouve=(int**) calloc(ligne,sizeof(int*));
    for(int x=0; x<ligne; x++)
        trouve[x]=(int*) calloc(colonne,sizeof(int));



    int *numero_heuristique = calloc(colonne,sizeof(int));
    char *lettre_heuristique = calloc(colonne,sizeof(char));

    if(i<ligne)
        strcpy(lettre_heuristique,tab[i]);


    if(lettre_heuristique[0]=='&')
        for(int x=0; x<colonne; x++)
            lettre_heuristique[x]=' ';

    for(int x=0; x<colonne; x++)
    {
        if(lettre_heuristique[x] != ' ')
            numero_heuristique[x]=1;
        else
            tab[i][x] = '.';
    }


    for(int y=0; y<ligne; y++)
    {

        verifier(MotChoisi,tab[y],trouve[y],colonne);

        for(int x=0; x<colonne; x++)
            if(trouve[y][x]==1)
            {
                numero_heuristique[x]=1;
                lettre_heuristique[x]=tab[y][x];
            }



        for(int x=0; x<colonne; x++)
        {

            if(numero_heuristique[x]==1 && i!=6)
            {

                trouve[i][x]=1;
                tab[i][x]=lettre_heuristique[x];
            }
            if(numero_heuristique[x]==0 && i!=6)
                tab[i][x]='.';
        }


    }


    Grille(tab, trouve,ligne,colonne,i);



    for(int x=0; x<i; x++)
    {
        liste_mot *mot_grille=creer_liste_mot(id,tab[x]);
        mot_deja_entrer= inserer_mot(mot_deja_entrer,mot_grille);
        id++;
    }


    if(i==6 || i==5)              //si la partie est déja fini
    {

        couleur(4,0);
        printf("\tpartie deja jouee\n");
        couleur(15,0);
        afficher_Partie_Sauv(monjoueur->pseudo);
        lire_Partie_Existe(monjoueur->pseudo);

    }



    else
    {
        int cal=0;
        for(int a=0; a<ligne; a++)
        {
            if(strcmp(tab[a],MotChoisi) ==0)
                cal++;
        }
        if(cal!=0)
        {
            printf("partie finie choisir autre partie");
            afficher_Partie_Sauv(monjoueur->pseudo);
            lire_Partie_Existe(monjoueur->pseudo);


        }

        else
        {

            time = 0;
            int cpt_tenta=i; //compteur des tentatives du joueur
            do
            {
                /*reeinitialisation de ligne de trouve*/
                for(int x=0; x<colonne; x++)
                    trouve[i][x]=0;

                Color(15,0);
                printf("  Il vous reste %d tentatives, tapez votre mot : ",(cpt_tenta));

                fflush(stdin); // vider la memoire du clavier avant la saisie
                scanf("%s",tab[i]);
                Color(7,0);

                if(tab[i][0]=='&')
                    break;

                rendreMotMajuscule(tab[i]);

                L=mot_deja_entrer;
                while(L != NULL && strcmp(L->mot,tab[i])!=0)
                    L=L->suivant;

                // 1: contient au moins un chiffre et 0: contient aucun chiffre
                int contient_chiffre=verifier_contient_chiffre(tab[i],colonne);


                /*en cas d'erreur*/
                while((contient_chiffre == 1 && strlen(tab[i]) <= colonne) || strlen(tab[i]) > colonne || strlen(tab[i]) < colonne || L != NULL)
                {
                    controler_mot_entrer(contient_chiffre,colonne,tab[i],L);

                    Color(15,0);
                    printf("  Veuillez retapez votre mot : ");
                    fflush(stdin); // vider la memoire du clavier avant la saisie
                    scanf("%s",tab[i]);
                    Color(7,0);
                    if(tab[i][0]=='&')
                        break;
                    rendreMotMajuscule(tab[i]);

                    // 1: contient au moins un chiffre et 0: contient aucun chiffre
                    contient_chiffre=verifier_contient_chiffre(tab[i],colonne);

                    L=mot_deja_entrer;
                    while(L != NULL && strcmp(L->mot,tab[i])!=0)
                        L=L->suivant;

                } // fin de la controle du mot entre par l'utilisateur

                cpt_tenta--;

                if(tab[i][0]=='&')
                    break;

                /*----------------------------------------------------*/
                //on remplit la liste par les mots qui existent dans la grille

                liste_mot *mot_grille=creer_liste_mot(id,tab[i]);
                mot_deja_entrer= inserer_mot(mot_deja_entrer,mot_grille);
                id++;
                /*----------------------------------------------------*/



                if(motExiste(tab[i])==1)
                    verifier(MotChoisi,tab[i],trouve[i],colonne);





                /*--------------------------------------------*/
                if(i<nbtenta-1)
                {
                    for(int x=0; x<colonne; x++)
                        if(trouve[i][x]==1)
                        {
                            numero_heuristique[x]=1;
                            lettre_heuristique[x]=tab[i][x];
                        }


                    for(int x=0; x<colonne; x++)
                    {
                        if(numero_heuristique[x]==1)
                        {
                            trouve[i+1][x]=1;
                            tab[i+1][x]=lettre_heuristique[x];
                        }
                        if(numero_heuristique[x]==0)
                            tab[i+1][x]='.';
                    }

                }
                /*--------------------------------------------*/

                //calcul du nombre de lettres bien placees
                int cpt=0;
                for(int z=0; z<colonne; z++)
                    if(trouve[i][z]==1)
                        cpt++;




                if(cpt == colonne ) //s'il a trouve le mot
                {
                    if(i<nbtenta-1)
                        for(int x=0; x<colonne; x++)
                            tab[i+1][x]=0;
                    Grille(tab, trouve,nbtenta,colonne,(i+1));
                    Color(10,0);
                    printf("\n Bravo '%s', vous avez trouver le mot.\n",monjoueur->pseudo);
                    Color(7,0);
                    /****************************/
                    time = clock()*0.001;
                    nbPartieG++;
                    score+=5;
                    /**************************/
                    break; // quitter la partie
                }
                else
                    Grille(tab, trouve,nbtenta,colonne,(i+1));


                i++; // on incremente a l'essaye suivant
            }
            while(i<nbtenta);  // tant qu'on est pas depasser le nbtenta


            if(i== nbtenta) // si on a depasser le nbtenta
            {
                printf("\n Perdu, le mot cherche etait bien : %s.\n",MotChoisi);
                time = clock()*0.001;
            }

            if(i< nbtenta && tab[i][0]=='&')
                printf("\n\n  vous avez quitter la partie.\n");

            /***********************************************************/

            monjoueur->duree=time;
            monjoueur->nbPartieG=nbPartieG;
            monjoueur->score=score;
            printf("|=>\t Vous souhaitez enregistrer votre partie\n");
            printf("|=>\t Tapez 1 si oui ou 0 si non\n");
            printf("|=>\t\t\t");
            scanf("%d",&enregistrer);
            monjoueur->enregistrer=enregistrer;

            sauvegarder_Partie(monjoueur,tab,nbtenta,colonne,MotChoisi,i,Mode);


            /***************************************************************************/


            /* liberer les espaces memoires alloues*/
            for(int i=0; i<nbtenta; i++)
                free(trouve[i]);
            free(trouve);

            for(int i=0; i<nbtenta; i++)
                free(tab[i]);
            free(tab);


            free(numero_heuristique);
            free(lettre_heuristique);



            //------------> FIN DU JEU <-------------

            printf("    Que Voulez-vous faire ?\n");
            printf("   ---------------------------------------\n");
            printf("    1) Recommencer une nouvelle partie.\n");
            printf("    2) Changer le mode du jeu.\n");
            printf("    3) Retour vers le menu principal.\n");
            printf("    4) Quitter le jeu.\n");
            int decision=0; //pour y stocker la decision du joueur
            Color(15,0);
            printf("      Entrer votre choix : ");
            fflush(stdin);
            scanf("%d",&decision);
            Color(7,0);


            //Pour une autre partie

            while(decision<=0 || decision >=5) // en cas de choix invalide
            {
                Color(12,0);
                printf("\tChoix invalide.\n");
                Color(7,0);

                Color(15,0);
                printf("      Entrez a nouveau votre choix : ");
                fflush(stdin);
                scanf("%d",&decision);
                Color(7,0);
            }

            if(decision ==1)
            {
                system("cls"); // clean screen
                seulJoueur(); // appel recursive de la fonction du debut du jeu
            }
            if(decision ==2)
            {
                system("cls"); // clean screen
                nouvellePartie(); // appel recursive de la fonction du debut du jeu
            }
            if(decision ==3)
            {
                system("cls"); // clean screen
                Menu(); //appel recursive de la fonction qui affiche le menu
            }
            if(decision ==4)
            {
                exit(0);
            }










        }




    }
}








void Charge_deuxJoueurs(Joueur*monjoueur,char **tab,int ligne,int colonne,char*motDico,int nbtenta)
{


    liste_mot *mot_deja_entrer=NULL;
    liste_mot *L=NULL;
    int id=0; //id du mot_deja_enter

    int Mode=2;



    int enregistrer;
    int nbPartieG=0;
    float time;
    int score=0;
    int i=nbtenta; // pour parcourir les tableaux


    char MotChoisi[8]; //pour y stocker le mot secret
    strcpy(MotChoisi,motDico);


    system("cls");


    printf("\nLe mot est : %s\n",MotChoisi);
    getch(); // c'est a nous,pour afficher le motChoisi





    int **trouve=(int**) calloc(ligne,sizeof(int*));
    for(int x=0; x<ligne; x++)
        trouve[x]=(int*) calloc(colonne,sizeof(int));



    int *numero_heuristique = calloc(colonne,sizeof(int));
    char *lettre_heuristique = calloc(colonne,sizeof(char));

    if(i<ligne)
        strcpy(lettre_heuristique,tab[i]);


    if(lettre_heuristique[0]=='&')
        for(int x=0; x<colonne; x++)
            lettre_heuristique[x]=' ';

    for(int x=0; x<colonne; x++)
    {
        if(lettre_heuristique[x] != ' ')
            numero_heuristique[x]=1;
        else
            tab[i][x] = '.';
    }


    for(int y=0; y<ligne; y++)
    {

        verifier(MotChoisi,tab[y],trouve[y],colonne);

        for(int x=0; x<colonne; x++)
            if(trouve[y][x]==1)
            {
                numero_heuristique[x]=1;
                lettre_heuristique[x]=tab[y][x];
            }



        for(int x=0; x<colonne; x++)
        {

            if(numero_heuristique[x]==1 && i!=6)
            {

                trouve[i][x]=1;
                tab[i][x]=lettre_heuristique[x];
            }
            if(numero_heuristique[x]==0 && i!=6)
                tab[i][x]='.';
        }


    }


    Grille(tab, trouve,ligne,colonne,i);



    for(int x=0; x<i; x++)
    {
        liste_mot *mot_grille=creer_liste_mot(id,tab[x]);
        mot_deja_entrer= inserer_mot(mot_deja_entrer,mot_grille);
        id++;
    }


    if(i==6 || i==5)              //si la partie est déja fini
    {

        couleur(4,0);
        printf("\tpartie deja jouee\n");
        couleur(15,0);
        afficher_Partie_Sauv(monjoueur->pseudo);
        lire_Partie_Existe(monjoueur->pseudo);

    }



    else
    {
        int cal=0;
        for(int a=0; a<ligne; a++)
        {
            if(strcmp(tab[a],MotChoisi) ==0)
                cal++;
        }
        if(cal!=0)
        {
            printf("partie finie choisir autre partie");
            afficher_Partie_Sauv(monjoueur->pseudo);
            lire_Partie_Existe(monjoueur->pseudo);


        }

        else
        {

            time = 0;
            int cpt_tenta=i; //compteur des tentatives du joueur
            do
            {

                if(i%2 == 0)//si le tour du joueur
                {
                    /*reeinitialisation de ligne de trouve*/
                    for(int x=0; x<colonne; x++)
                        trouve[i][x]=0;

                    printf("\n--> Le tour du joueur.\n");

                    Color(15,0);
                    printf("  Il vous reste %d tentatives, tapez votre mot : ",(cpt_tenta));

                    fflush(stdin); // vider la memoire du clavier avant la saisie
                    scanf("%s",tab[i]);
                    Color(7,0);

                    if(tab[i][0]=='&')
                        break;

                    rendreMotMajuscule(tab[i]);

                    L=mot_deja_entrer;
                    while(L != NULL && strcmp(L->mot,tab[i])!=0)
                        L=L->suivant;

                    // 1: contient au moins un chiffre et 0: contient aucun chiffre
                    int contient_chiffre=verifier_contient_chiffre(tab[i],colonne);


                    /*en cas d'erreur*/
                    while((contient_chiffre == 1 && strlen(tab[i]) <= colonne) || strlen(tab[i]) > colonne || strlen(tab[i]) < colonne || L != NULL)
                    {
                        controler_mot_entrer(contient_chiffre,colonne,tab[i],L);

                        Color(15,0);
                        printf("  Veuillez retapez votre mot : ");
                        fflush(stdin); // vider la memoire du clavier avant la saisie
                        scanf("%s",tab[i]);
                        Color(7,0);
                        if(tab[i][0]=='&')
                            break;
                        rendreMotMajuscule(tab[i]);

                        // 1: contient au moins un chiffre et 0: contient aucun chiffre
                        contient_chiffre=verifier_contient_chiffre(tab[i],colonne);

                        L=mot_deja_entrer;
                        while(L != NULL && strcmp(L->mot,tab[i])!=0)
                            L=L->suivant;

                    } // fin de la controle du mot entre par l'utilisateur

                    cpt_tenta--;

                    if(tab[i][0]=='&')
                        break;

                    /*----------------------------------------------------*/
                    //on remplit la liste par les mots qui existent dans la grille

                    liste_mot *mot_grille=creer_liste_mot(id,tab[i]);
                    mot_deja_entrer= inserer_mot(mot_deja_entrer,mot_grille);
                    id++;
                    /*----------------------------------------------------*/



                    if(motExiste(tab[i])==1)
                        verifier(MotChoisi,tab[i],trouve[i],colonne);





                    /*--------------------------------------------*/
                    if(i<nbtenta-1)
                    {
                        for(int x=0; x<colonne; x++)
                            if(trouve[i][x]==1)
                            {
                                numero_heuristique[x]=1;
                                lettre_heuristique[x]=tab[i][x];
                            }


                        for(int x=0; x<colonne; x++)
                        {
                            if(numero_heuristique[x]==1)
                            {
                                trouve[i+1][x]=1;
                                tab[i+1][x]=lettre_heuristique[x];
                            }
                            if(numero_heuristique[x]==0)
                                tab[i+1][x]='.';
                        }

                    }
                    /*--------------------------------------------*/

                    //calcul du nombre de lettres bien placees
                    int cpt=0;
                    for(int z=0; z<colonne; z++)
                        if(trouve[i][z]==1)
                            cpt++;




                    if(cpt == colonne ) //s'il a trouve le mot
                    {
                        if(i<ligne-1)
                            for(int x=0; x<colonne; x++)
                                tab[i+1][x]=0;

                        Grille(tab, trouve,ligne,colonne,(i+1));
                        Color(10,0);
                        printf("\nBravo '%s' vous avez trouver le mot.\n\n",monjoueur->pseudo);
                        Color(7,0);
                        /*************************/
                        time = clock()*0.001;
                        nbPartieG++;
                        score+=5;
                        /**********************/
                        break; // quitter la partie
                    }
                    else
                        Grille(tab, trouve,ligne,colonne,(i+1));
                }



                if(i%2 != 0)//si le tour de l'ordinateur
                {
                    /*reeinitialisation de ligne de trouve*/
                    for(int x=0; x<colonne; x++)
                        trouve[i][x]=0;

                    printf("\n--> Le tour du joueur.\n");

                    Color(15,0);
                    printf("  Il vous reste %d tentatives, tapez votre mot : ",(cpt_tenta));

                    fflush(stdin); // vider la memoire du clavier avant la saisie
                    scanf("%s",tab[i]);
                    Color(7,0);

                    if(tab[i][0]=='&')
                        break;

                    rendreMotMajuscule(tab[i]);

                    L=mot_deja_entrer;
                    while(L != NULL && strcmp(L->mot,tab[i])!=0)
                        L=L->suivant;

                    // 1: contient au moins un chiffre et 0: contient aucun chiffre
                    int contient_chiffre=verifier_contient_chiffre(tab[i],colonne);


                    /*en cas d'erreur*/
                    while((contient_chiffre == 1 && strlen(tab[i]) <= colonne) || strlen(tab[i]) > colonne || strlen(tab[i]) < colonne || L != NULL)
                    {
                        controler_mot_entrer(contient_chiffre,colonne,tab[i],L);

                        Color(15,0);
                        printf("  Veuillez retapez votre mot : ");
                        fflush(stdin); // vider la memoire du clavier avant la saisie
                        scanf("%s",tab[i]);
                        Color(7,0);
                        if(tab[i][0]=='&')
                            break;
                        rendreMotMajuscule(tab[i]);

                        // 1: contient au moins un chiffre et 0: contient aucun chiffre
                        contient_chiffre=verifier_contient_chiffre(tab[i],colonne);

                        L=mot_deja_entrer;
                        while(L != NULL && strcmp(L->mot,tab[i])!=0)
                            L=L->suivant;

                    } // fin de la controle du mot entre par l'utilisateur

                    cpt_tenta--;

                    if(tab[i][0]=='&')
                        break;

                    /*----------------------------------------------------*/
                    //on remplit la liste par les mots qui existent dans la grille

                    liste_mot *mot_grille=creer_liste_mot(id,tab[i]);
                    mot_deja_entrer= inserer_mot(mot_deja_entrer,mot_grille);
                    id++;
                    /*----------------------------------------------------*/



                    if(motExiste(tab[i])==1)
                        verifier(MotChoisi,tab[i],trouve[i],colonne);





                    /*--------------------------------------------*/
                    if(i<nbtenta-1)
                    {
                        for(int x=0; x<colonne; x++)
                            if(trouve[i][x]==1)
                            {
                                numero_heuristique[x]=1;
                                lettre_heuristique[x]=tab[i][x];
                            }


                        for(int x=0; x<colonne; x++)
                        {
                            if(numero_heuristique[x]==1)
                            {
                                trouve[i+1][x]=1;
                                tab[i+1][x]=lettre_heuristique[x];
                            }
                            if(numero_heuristique[x]==0)
                                tab[i+1][x]='.';
                        }

                    }
                    /*--------------------------------------------*/

                    //calcul du nombre de lettres bien placees
                    int cpt=0;
                    for(int z=0; z<colonne; z++)
                        if(trouve[i][z]==1)
                            cpt++;




                    if(cpt == colonne ) //s'il a trouve le mot
                    {
                        if(i<ligne-1)
                            for(int x=0; x<colonne; x++)
                                tab[i+1][x]=0;

                        Grille(tab, trouve,ligne,colonne,(i+1));
                        Color(10,0);
                        printf("\nBravo '%s' vous avez trouver le mot.\n\n",monjoueur->pseudo);
                        Color(7,0);
                        /*************************/
                        time = clock()*0.001;
                        nbPartieG++;
                        score+=5;
                        /**********************/
                        break; // quitter la partie
                    }
                    else
                        Grille(tab, trouve,ligne,colonne,(i+1));

                }


                i++; // on incremente a l'essaye suivant
            }
            while(i<ligne);  // tant qu'on est pas depasser le nbtenta


            if(i== ligne) // si on a depasser le nbtenta
            {
                printf("\nPerdu, le mot cherche etait bien : %s.\n",MotChoisi);
                time = clock()*0.001;
            }



            monjoueur->duree=time;
            monjoueur->nbPartieG=nbPartieG;
            monjoueur->score=score;
            printf("|=>\t Vous souhaitez enregistrer votre partie\n");
            printf("|=>\t Tapez 1 si oui ou 0 si non\n");
            printf("|=>\t\t\t");
            scanf("%d",&enregistrer);
            monjoueur->enregistrer=enregistrer;


            sauvegarder_Partie(monjoueur,tab,ligne,colonne,MotChoisi,i,Mode);


            /* liberer les espaces alloue*/
            for(int i=0; i<ligne; i++)
                free(trouve[i]);
            free(trouve);

            for(int i=0; i<ligne; i++)
                free(tab[i]);
            free(tab);


            free(numero_heuristique);
            free(lettre_heuristique);



            //------------> FIN DU JEU <-------------






            //Pour une autre partie
            printf("   \n\nQue Voulez-vous faire ?\n");
            printf("   -----------------------------------\n");
            printf("    1)Recommencer une nouvelle partie.\n");
            printf("    2)Changer le mode du jeu.\n");
            printf("    3)Retour vers le menu principal.\n");
            printf("    4)Quitter le jeu.\n");
            int decision=0; //pour y stocker la decision du joueur
            Color(15,0);
            printf("      Entrer votre choix : ");
            fflush(stdin);
            scanf("%d",&decision);
            Color(7,0);


            //Pour une autre partie

            while(decision<=0 || decision >=5) // en cas de choix invalide
            {
                Color(12,0);
                printf("\tChoix invalide.\n");
                Color(7,0);

                Color(15,0);
                printf("      Entrez a nouveau votre choix : ");
                fflush(stdin);
                scanf("%d",&decision);
                Color(7,0);
            }

            if(decision ==1)
            {
                system("cls"); // clean screen
                deuxJoueurs(); // appel recursive de la fonction du debut du jeu
            }
            if(decision ==2)
            {
                system("cls"); // clean screen
                nouvellePartie(); // appel recursive de la fonction du debut du jeu
            }
            if(decision ==3)
            {
                system("cls"); // clean screen
                Menu(); //appel recursive de la fonction qui affiche le menu
            }
            if(decision ==4)
            {
                exit(0);
            }

        }
    }


}























