
#include "notreBiblio.h"
#include "sauvgarde_charge.h"

void seulJoueur()
{

    int Mode=1;
    liste_mot *mot_deja_entrer=NULL;
    liste_mot *L=NULL;
    int id=0; //id du mot_deja_enter

    int nbtenta=6;
    int tailleMot;
    int nbLettreV=1;
    int i=0; // pour les tentatives
    /**************************************/
     int numero,enregistrer;
    char niveau[MAXCHAINE]; /* le niveau  */
    strcpy(niveau,"niveau-");
    niveau[strlen(niveau)+1]='\0';
    char numPartie[3];
    char nomJ[30];
    int nbPartieG=0;
    float time;
    int score=0;
    /****************************************/
    Color(15,0);
     printf("\n Entrez votre pseudo : ");
    scanf("%s",nomJ);
    Joueur*monjoueur;
    monjoueur=creerJoueur(nomJ);
    creerDossier(nomJ);
    afficher_niveau();
    printf("\n\t Donner votre choix : ");
    scanf("%d",&numero);
    switch(numero)
    {
    case 1 :
        tailleMot=6;
        break;

    case 2 :
        tailleMot=7;
        break;

    case 3 :
        tailleMot=8;
        break;

    case 4 :
        tailleMot=9;
        break;

    case 5 :
        tailleMot=10;
        break;

    default :
        tailleMot=6;
        break;

    }
    couleur(15,0);
    printf("\n");

    itoa(numero,numPartie,10);
    strcat(niveau,numPartie);
    strcat(niveau,".txt");
    niveau[strlen(niveau)+1]='\0';
    strcpy(monjoueur->niveau,niveau);
    system("cls");


/*******************************************************/
    char MotChoisi[10]=""; //pour y stocker le mot secret
    choisirMot(MotChoisi,tailleMot);
    MotChoisi[tailleMot]='\0';


    system("cls");

    printf("\nLe mot secret est : %s",MotChoisi); // c'est a nous,pour afficher le motChoisi
    getch();


    char **tab=(char**) calloc(nbtenta,sizeof(char*));
    for(int x=0; x<nbtenta; x++)
        tab[x]=(char*) calloc(tailleMot,sizeof(char));

    //-->initialisation du grille
    for(int x=0; x<nbtenta; x++)
        for(int y=0; y<tailleMot; y++)
            tab[x][y]=' ';


    int **trouve=(int**) calloc(nbtenta,sizeof(int*));
    for(int x=0; x<nbtenta; x++)
        trouve[x]=(int*) calloc(tailleMot,sizeof(int));


    int *numero_heuristique = calloc(tailleMot,sizeof(int));
    char *lettre_heuristique = calloc(tailleMot,sizeof(char));

    tab[i][tailleMot]='\0';


    affecterNbVisbible(MotChoisi, tab[i],trouve[i], nbLettreV); //affecter nbLettreV au mot avant de commencer le jeu

    tab[i][tailleMot]='\0';

    strcpy(lettre_heuristique,tab[i]);
    for(int x=0; x<tailleMot; x++)
        if(lettre_heuristique[x] != ' ')
            numero_heuristique[x]=1;
        else
            tab[i][x] = '.';

    //affichage de la grille initial
    Grille(tab, trouve,nbtenta,tailleMot,i);


     time = 0;
    int cpt_tenta=nbtenta; //compteur des tentatives du joueur
    do
    {
        /*reeinitialisation de ligne de trouve*/
        for(int x=0; x<tailleMot; x++)
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
        int contient_chiffre=verifier_contient_chiffre(tab[i],tailleMot);


        /*en cas d'erreur*/
        while((contient_chiffre == 1 && strlen(tab[i]) <= tailleMot) || strlen(tab[i]) > tailleMot || strlen(tab[i]) < tailleMot || L != NULL)
        {
            controler_mot_entrer(contient_chiffre,tailleMot,tab[i],L);

            Color(15,0);
            printf("  Veuillez retapez votre mot : ");
            fflush(stdin); // vider la memoire du clavier avant la saisie
            scanf("%s",tab[i]);
            Color(7,0);
            if(tab[i][0]=='&')
                break;
            rendreMotMajuscule(tab[i]);

            // 1: contient au moins un chiffre et 0: contient aucun chiffre
            contient_chiffre=verifier_contient_chiffre(tab[i],tailleMot);

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
            verifier(MotChoisi,tab[i],trouve[i],tailleMot);





        /*--------------------------------------------*/
        if(i<nbtenta-1)
        {
            for(int x=0; x<tailleMot; x++)
                if(trouve[i][x]==1)
                {
                    numero_heuristique[x]=1;
                    lettre_heuristique[x]=tab[i][x];
                }


            for(int x=0; x<tailleMot; x++)
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
        for(int z=0; z<tailleMot; z++)
            if(trouve[i][z]==1)
                cpt++;




        if(cpt == tailleMot ) //s'il a trouve le mot
        {
            if(i<nbtenta-1)
                for(int x=0; x<tailleMot; x++)
                    tab[i+1][x]=0;
            Grille(tab, trouve,nbtenta,tailleMot,(i+1));
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
            Grille(tab, trouve,nbtenta,tailleMot,(i+1));


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

    sauvegarder_Partie(monjoueur,tab,nbtenta,tailleMot,MotChoisi,i,Mode);


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













///////////////////////////////////////////////////////////////////////////////////////////////
void joueurOrdinateur()//l'utilisateur joue contre l'ordinateur
{
    int Mode=2;

    int nbtenta=6;
    int tailleMot;
    int nbLettreV=1;
    int i=0; // pour les tentatives

    /**********************************************/
    int numero,enregistrer;
    char niveau[MAXCHAINE]; /* le niveau  */
    strcpy(niveau,"niveau-");
    niveau[strlen(niveau)+1]='\0';
    char numPartie[3];
    char nomJ[30];
    int nbPartieG=0;
    float time;
    int score=0;

    /****************************************/


    /*********************************************************************/

    printf("\n Entrez votre pseudo : ");
    scanf("%s",nomJ);
    Joueur*monjoueur;
    monjoueur=creerJoueur(nomJ);
    creerDossier(nomJ);
    afficher_niveau();
    printf("\n\t Donner votre choix : ");
    scanf("%d",&numero);
    switch(numero)
    {
    case 1 :
        tailleMot=6;
        break;

    case 2 :
        tailleMot=7;
        break;

    case 3 :
        tailleMot=8;
        break;

    case 4 :
        tailleMot=9;
        break;

    case 5 :
        tailleMot=10;
        break;

    default :
        tailleMot=6;
        break;

    }
    couleur(15,0);
    printf("\n");

    itoa(numero,numPartie,10);
    strcat(niveau,numPartie);
    strcat(niveau,".txt");
    niveau[strlen(niveau)+1]='\0';
    strcpy(monjoueur->niveau,niveau);
    system("cls");
    /***********************************************************************/



    liste_mot *mot_deja_entrer=NULL;
    liste_mot *L=NULL;
    int id=0; //id du mot_deja_enter


    char MotChoisi[10]=""; //pour y stocker le mot secret
    choisirMot(MotChoisi,tailleMot);
    MotChoisi[tailleMot]='\0';


    system("cls");

    printf("\nLe mot secret est : %s",MotChoisi); // c'est a nous,pour afficher le motChoisi
    getch();



    //-->declaration de la grille
    char **tab=(char**) calloc(nbtenta,sizeof(char*));
    for(int x=0; x<nbtenta; x++)
        tab[x]=(char*) calloc(tailleMot,sizeof(char));

    //-->initialisation de la grille
    for(int x=0; x<nbtenta; x++)
        for(int y=0; y<tailleMot; y++)
            tab[x][y]=' ';

    /*-------------------------*/
    for(int x=0; x<nbtenta; x++)
        tab[x][tailleMot]='\0';
    /*-------------------------*/

    /*ici ou se trouve le probleme avec le dico 8*/
    printf("\nverif tailleMot : %d",tailleMot);// il ne s'affiche pas ce printf

    int **trouve=(int**) calloc(nbtenta,sizeof(int*));
    for(int x=0; x<nbtenta; x++)
        trouve[x]=(int*) calloc(tailleMot,sizeof(int));


    int *numero_heuristique = calloc(tailleMot,sizeof(int));
    char *lettre_heuristique = calloc(tailleMot,sizeof(char));

    tab[i][tailleMot]='\0';



    affecterNbVisbible(MotChoisi, tab[i],trouve[i], nbLettreV); //affecter nbLettreV au mot avant de commencer le jeu

    tab[i][tailleMot]='\0';

    strcpy(lettre_heuristique,tab[i]);
    for(int x=0; x<tailleMot; x++)
        if(lettre_heuristique[x] != ' ')
            numero_heuristique[x]=1;
        else
            tab[i][x] = '.';

    //affichage de la grille initial
    Grille(tab, trouve,nbtenta,tailleMot,i);


    time = 0;
    int cpt_tenta=nbtenta/2; //compteur des tentatives du joueur
    do
    {

        if(i%2 == 0)//si le tour du joueur
        {
            /*reeinitialisation de ligne de trouve*/
            for(int x=0; x<tailleMot; x++)
                trouve[i][x]=0;

            printf("\n--> Le tour de %s.\n",monjoueur->pseudo);

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
            int contient_chiffre=verifier_contient_chiffre(tab[i],tailleMot);


            /*en cas d'erreur*/
            while((contient_chiffre == 1 && strlen(tab[i]) <= tailleMot) || strlen(tab[i]) > tailleMot || strlen(tab[i]) < tailleMot || L != NULL)
            {
                controler_mot_entrer(contient_chiffre,tailleMot,tab[i],L);

                Color(15,0);
                printf("  Veuillez retapez votre mot : ");
                fflush(stdin); // vider la memoire du clavier avant la saisie
                scanf("%s",tab[i]);
                Color(7,0);
                if(tab[i][0]=='&')
                    break;
                rendreMotMajuscule(tab[i]);

                // 1: contient au moins un chiffre et 0: contient aucun chiffre
                contient_chiffre=verifier_contient_chiffre(tab[i],tailleMot);

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
                verifier(MotChoisi,tab[i],trouve[i],tailleMot);





            /*--------------------------------------------*/
            if(i<nbtenta-1)
            {
                for(int x=0; x<tailleMot; x++)
                    if(trouve[i][x]==1)
                    {
                        numero_heuristique[x]=1;
                        lettre_heuristique[x]=tab[i][x];
                    }


                for(int x=0; x<tailleMot; x++)
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
            for(int z=0; z<tailleMot; z++)
                if(trouve[i][z]==1)
                    cpt++;




            if(cpt == tailleMot ) //s'il a trouve le mot
            {
                if(i<nbtenta-1)
                    for(int x=0; x<tailleMot; x++)
                        tab[i+1][x]=0;

                Grille(tab, trouve,nbtenta,tailleMot,(i+1));
                Color(10,0);
                printf("\n Bravo '%s', vous avez trouver le mot.\n\n",monjoueur->pseudo);
                Color(7,0);
                /*************************/
                time = clock()*0.001;
                nbPartieG++;
                score+=5;
                /**********************/
                break; // quitter la partie
            }
            else
                Grille(tab, trouve,nbtenta,tailleMot,(i+1));
        }



        if(i%2 != 0)//si le tour de l'ordinateur
        {
            /*reeinitialisation de ligne de trouve*/
            for(int x=0; x<tailleMot; x++)
                trouve[i][x]=0;

            printf("\n--> Le tour d'ordinateur.\n ");
            choisirMotPc(tab[i],lettre_heuristique,mot_deja_entrer,tailleMot);
            Color(15,0);
            printf("    Le mot propose est : '%s', appuyez sur entrer", tab[i]);
            Color(7,0);
            verifier(MotChoisi,tab[i],trouve[i],tailleMot);
            getch();


            /*----------------------------------------------------*/
            //on remplit la liste par les mots qui existent dans la grille

            liste_mot *mot_grille=creer_liste_mot(id,tab[i]);
            mot_deja_entrer= inserer_mot(mot_deja_entrer,mot_grille);
            id++;
            /*----------------------------------------------------*/




            /*--------------------------------------------*/
            if(i<nbtenta-1)
            {
                for(int x=0; x<tailleMot; x++)
                    if(trouve[i][x]==1)
                    {
                        numero_heuristique[x]=1;
                        lettre_heuristique[x]=tab[i][x];
                    }


                for(int x=0; x<tailleMot; x++)
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
            for(int z=0; z<tailleMot; z++)
                if(trouve[i][z]==1)
                    cpt++;



            if(cpt == tailleMot ) //s'il a trouve le mot
            {
                if(i<nbtenta-1)
                    for(int x=0; x<tailleMot; x++)
                        tab[i+1][x]=0;
                Grille(tab, trouve,nbtenta,tailleMot,(i+1));
                printf("\n Perdu, l'ordinateur a pu deviner le mot secret.\n\n");
                 time = clock()*0.001;
                break; // on quitte le jeu
            }
            else //s'il n'a pas trouve le mot
                Grille(tab, trouve,nbtenta,tailleMot,i+1);


        }


        i++; // on incremente a l'essaye suivant
    }
    while(i<nbtenta);  // tant qu'on est pas depasser le nbtenta


    if(i== nbtenta) // si on a depasser le nbtenta
    {
        printf("\n Perdu, le mot cherche etait bien : %s.\n\n",MotChoisi);
        time = clock()*0.001;

    }


    if(i< nbtenta && tab[i][0]=='&')
        printf("\n\n  Vous avez quitter la partie.\n\n");

    /********************************************************************************/

    monjoueur->duree=time;
    monjoueur->nbPartieG=nbPartieG;
    monjoueur->score=score;
    printf("|=>\t Vous souhaitez enregistrer votre partie\n");
    printf("|=>\t Tapez 1 si oui ou 0 si non\n");
    printf("|=>\t\t\t");
    scanf("%d",&enregistrer);
    monjoueur->enregistrer=enregistrer;

    sauvegarder_Partie(monjoueur,tab,nbtenta,tailleMot,MotChoisi,i,Mode);



    /*************************************************************************************/

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
    printf("    --------------------------------------\n");
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
        joueurOrdinateur(); // appel recursive de la fonction du debut du jeu
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








void deuxJoueurs() //l'utilisateur joue contre un autre joueur
{
    int Mode=3;
    liste_mot *mot_deja_entrer=NULL;
    liste_mot *L=NULL;
    int id=0; //id du mot_deja_enter

    int nbtenta=6;
    int tailleMot=6;
    int nbLettreV=1;
    int i=0; // pour les tentatives

    /********************************************************************/
     int numero,enregistrer;
    char niveau[MAXCHAINE]; /* le niveau  */
    strcpy(niveau,"niveau-");
    niveau[strlen(niveau)+1]='\0';
    char numPartie[3];
    char nomJ1[30];
    int nbPartieGJ1=0;
    float time;
    int scoreJ1=0;

    /****************************************/
    int scoreJ2=0;
    char nomJ2[30];
    int nbPartieGJ2=0;

    /*********************************************************************/

    printf("\n Entrez le pseudo de premier joueur : ");
    scanf("%s",nomJ1);
     printf("\n Entrez le pseudo de deuxieme joueur : ");
    scanf("%s",nomJ2);
    Joueur*monjoueur1;
    monjoueur1=creerJoueur(nomJ1);
    Joueur*monjoueur2;
    monjoueur2=creerJoueur(nomJ2);
    creerDossier(nomJ1);
     creerDossier(nomJ2);
    afficher_niveau();
    printf("\t Donner votre choix : ");
    scanf("%d",&numero);
    switch(numero)
    {
    case 1 :
        tailleMot=6;
        break;

    case 2 :
        tailleMot=7;
        break;

    case 3 :
        tailleMot=8;
        break;

    case 4 :
        tailleMot=9;
        break;

    case 5 :
        tailleMot=10;
        break;

    default :
        tailleMot=6;
        break;

    }
    couleur(15,0);
    printf("\n");

    itoa(numero,numPartie,10);
    strcat(niveau,numPartie);
    strcat(niveau,".txt");
    niveau[strlen(niveau)+1]='\0';
    strcpy(monjoueur1->niveau,niveau);
    strcpy(monjoueur2->niveau,niveau);
    system("cls");
    /***********************************************************************/


    char MotChoisi[10]=""; //pour y stocker le mot secret
    choisirMot(MotChoisi,tailleMot);
    MotChoisi[tailleMot]='\0';


    system("cls");

    printf("\n Le mot secret est : %s",MotChoisi); // c'est a nous,pour afficher le motChoisi
    getch();


    char **tab=(char**) calloc(nbtenta,sizeof(char*));
    for(int x=0; x<nbtenta; x++)
        tab[x]=(char*) calloc(tailleMot,sizeof(char));

    //-->initialisation du grille
    for(int x=0; x<nbtenta; x++)
        for(int y=0; y<tailleMot; y++)
            tab[x][y]=' ';


    int **trouve=(int**) calloc(nbtenta,sizeof(int*));
    for(int x=0; x<nbtenta; x++)
        trouve[x]=(int*) calloc(tailleMot,sizeof(int));


    int *numero_heuristique = calloc(tailleMot,sizeof(int));
    char *lettre_heuristique = calloc(tailleMot,sizeof(char));

    tab[i][tailleMot]='\0';


    affecterNbVisbible(MotChoisi, tab[i],trouve[i], nbLettreV); //affecter nbLettreV au mot avant de commencer le jeu

    tab[i][tailleMot]='\0';

    strcpy(lettre_heuristique,tab[i]);
    for(int x=0; x<tailleMot; x++)
        if(lettre_heuristique[x] != ' ')
            numero_heuristique[x]=1;
        else
            tab[i][x] = '.';

    //affichage de la grille initial
    Grille(tab, trouve,nbtenta,tailleMot,i);


   time=0;
    int cpt_tenta1=nbtenta/2; //compteur des tentatives du joueur
    int cpt_tenta2=nbtenta/2;
    do
    {

        if(i%2 == 0)//si le tour du joueur
        {
            /*reeinitialisation de ligne de trouve*/
            for(int x=0; x<tailleMot; x++)
                trouve[i][x]=0;

            printf("\n --> Le tour de %s.\n",monjoueur1->pseudo);

            Color(15,0);
            printf("  Il vous reste %d tentatives, tapez votre mot : ",cpt_tenta1);

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
            int contient_chiffre=verifier_contient_chiffre(tab[i],tailleMot);


            /*en cas d'erreur*/
            while((contient_chiffre == 1 && strlen(tab[i]) <= tailleMot) || strlen(tab[i]) > tailleMot || strlen(tab[i]) < tailleMot || L != NULL)
            {
                controler_mot_entrer(contient_chiffre,tailleMot,tab[i],L);

                Color(15,0);
                printf("  Veuillez retapez votre mot : ");
                fflush(stdin); // vider la memoire du clavier avant la saisie
                scanf("%s",tab[i]);
                Color(7,0);
                if(tab[i][0]=='&')
                    break;
                rendreMotMajuscule(tab[i]);

                // 1: contient au moins un chiffre et 0: contient aucun chiffre
                contient_chiffre=verifier_contient_chiffre(tab[i],tailleMot);

                L=mot_deja_entrer;
                while(L != NULL && strcmp(L->mot,tab[i])!=0)
                    L=L->suivant;

            } // fin de la controle du mot entre par l'utilisateur

            cpt_tenta1--;

            if(tab[i][0]=='&')
                break;

            /*----------------------------------------------------*/
            //on remplit la liste par les mots qui existent dans la grille

            liste_mot *mot_grille=creer_liste_mot(id,tab[i]);
            mot_deja_entrer= inserer_mot(mot_deja_entrer,mot_grille);
            id++;
            /*----------------------------------------------------*/



            if(motExiste(tab[i])==1)
                verifier(MotChoisi,tab[i],trouve[i],tailleMot);





            /*--------------------------------------------*/
            if(i<nbtenta-1)
            {
                for(int x=0; x<tailleMot; x++)
                    if(trouve[i][x]==1)
                    {
                        numero_heuristique[x]=1;
                        lettre_heuristique[x]=tab[i][x];
                    }


                for(int x=0; x<tailleMot; x++)
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
            for(int z=0; z<tailleMot; z++)
                if(trouve[i][z]==1)
                    cpt++;




            if(cpt == tailleMot ) //s'il a trouve le mot
            {
                if(i<nbtenta-1)
                    for(int x=0; x<tailleMot; x++)
                        tab[i+1][x]=0;
                Grille(tab, trouve,nbtenta,tailleMot,(i+1));
                Color(10,0);
                printf("\n Bravo '%s', vous avez trouver le mot.\n",monjoueur1->pseudo);
                Color(7,0);
                /*--------------------------*/
                 time = clock()*0.001;
                nbPartieGJ1++;
                scoreJ1+=5;
               /*----------------------*/

                break; // quitter la partie
            }
            else
                Grille(tab, trouve,nbtenta,tailleMot,(i+1));
        }



        if(i%2 != 0)//si le tour du joueur 2
        {
            /*reeinitialisation de ligne de trouve*/
            for(int x=0; x<tailleMot; x++)
                trouve[i][x]=0;

            printf("\n --> Le tour de %s.\n",monjoueur2->pseudo);

            Color(15,0);
            printf("  Il vous reste %d tentatives, tapez votre mot : ",cpt_tenta2);

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
            int contient_chiffre=verifier_contient_chiffre(tab[i],tailleMot);


            /*en cas d'erreur*/
            while((contient_chiffre == 1 && strlen(tab[i]) <= tailleMot) || strlen(tab[i]) > tailleMot || strlen(tab[i]) < tailleMot || L != NULL)
            {
                controler_mot_entrer(contient_chiffre,tailleMot,tab[i],L);

                Color(15,0);
                printf("  Veuillez retapez votre mot : ");
                fflush(stdin); // vider la memoire du clavier avant la saisie
                scanf("%s",tab[i]);
                Color(7,0);
                if(tab[i][0]=='&')
                    break;
                rendreMotMajuscule(tab[i]);

                // 1: contient au moins un chiffre et 0: contient aucun chiffre
                contient_chiffre=verifier_contient_chiffre(tab[i],tailleMot);

                L=mot_deja_entrer;
                while(L != NULL && strcmp(L->mot,tab[i])!=0)
                    L=L->suivant;

            } // fin de la controle du mot entre par l'utilisateur

            cpt_tenta2--;

            if(tab[i][0]=='&')
                break;

            /*----------------------------------------------------*/
            //on remplit la liste par les mots qui existent dans la grille

            liste_mot *mot_grille=creer_liste_mot(id,tab[i]);
            mot_deja_entrer= inserer_mot(mot_deja_entrer,mot_grille);
            id++;
            /*----------------------------------------------------*/



            if(motExiste(tab[i])==1)
                verifier(MotChoisi,tab[i],trouve[i],tailleMot);





            /*--------------------------------------------*/
            if(i<nbtenta-1)
            {
                for(int x=0; x<tailleMot; x++)
                    if(trouve[i][x]==1)
                    {
                        numero_heuristique[x]=1;
                        lettre_heuristique[x]=tab[i][x];
                    }


                for(int x=0; x<tailleMot; x++)
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
            for(int z=0; z<tailleMot; z++)
                if(trouve[i][z]==1)
                    cpt++;




            if(cpt == tailleMot ) //s'il a trouve le mot
            {
                if(i<nbtenta-1)
                    for(int x=0; x<tailleMot; x++)
                        tab[i+1][x]=0;
                Grille(tab, trouve,nbtenta,tailleMot,(i+1));
                Color(10,0);
                printf("\n Bravo '%s', vous avez trouver le mot.\n",monjoueur2->pseudo);
                Color(7,0);
                 /*--------------------------*/
                 time = clock()*0.001;
                nbPartieGJ2++;
                scoreJ2+=5;
               /*----------------------*/

                break; // quitter la partie
            }
            else
                Grille(tab, trouve,nbtenta,tailleMot,(i+1));

        }


        i++; // on incremente a l'essaye suivant
    }
    while(i<nbtenta);  // tant qu'on est pas depasser le nbtenta


    if(i== nbtenta) // si on a depasser le nbtenta
    {
        printf("\n Perdu, le mot cherche etait bien : %s.\n",MotChoisi);
                         time = clock()*0.001;

    }


    if(i< nbtenta && tab[i][0]=='&')
        printf("\n\n  Vous avez quitter la partie.\n");

      /*************************************************************************/

        monjoueur1->duree=time;
        monjoueur1->nbPartieG=nbPartieGJ1;
        monjoueur1->score=scoreJ1;

         monjoueur2->duree=time;
         monjoueur2->nbPartieG=nbPartieGJ2;
         monjoueur2->score=scoreJ2;

    printf("|=>\t Vous souhaitez enregistrer votre partie\n");
    printf("|=>\t Tapez 1 si oui ou 0 si non\n");
    printf("|=>\t\t\t");
    scanf("%d",&enregistrer);
    monjoueur1->enregistrer=enregistrer;
    monjoueur2->enregistrer=enregistrer;


    sauvegarder_Partie(monjoueur1,tab,nbtenta,tailleMot,MotChoisi,i,Mode);
    sauvegarder_Partie(monjoueur2,tab,nbtenta,tailleMot,MotChoisi,i,Mode);




/*******************************************************/

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

    printf("    Que Voulez-vous faire ?\n\n");
    printf("    -----------------------------------\n");
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























