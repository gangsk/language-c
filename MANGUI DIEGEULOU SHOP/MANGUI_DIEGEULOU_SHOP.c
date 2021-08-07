////BIBLIOTHEQUES
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>

//CONSTANTTES
#define CLS system("cls");
#define PAUSE system("pause");
#define VIDER fflush(stdin);

// LES STRUCTURES DU PROJET

typedef struct{
    int j,m,a;
}Date;


typedef struct{
    int id,nbrElement,liste;
    char libelle[30];
}CATEGORIE;


typedef struct{
    int prix,quantiteStock,liste;
    char designation[30],code[10];
    char categorie[30];
    char dateAjout[20];
}ARTICLE;


typedef struct{
    int id,etat,supAdmin,nbrElement;
    char nom[30],prenom[30],tel[20],active[20],bloque[20];
    char login[20],mdp[20];
}USERS;


typedef struct{
    int id,nbrElement;
    char numero[20];
    ARTICLE tabproduits;
    int montants;
    USERS infoUsers;
}VENTE;


//DECLARATION DES VAIABLES SUPER GLOBALES
USERS Users,Session;
VENTE  vente;
ARTICLE article;
CATEGORIE categorie;
Date date;
int cptUser=0,cptCategories=0,finMontant=0,nbProduit=0;

/////////////////**********************************************************************************//////////////////

// LES FONCTIONS

//la fonction gotoxy pour la manipulation du curseur qui recoit deux   parametre ,elle place le curseur  a la position x et y

void gotoxy(int i , int j)
{
    HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c;

    c.X=i;
    c.Y=j;
    SetConsoleCursorPosition(h,c);
}

void color(int col)
{
    HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h,(WORD)col);
}

/////////////////**********************************************************************************//////////////////

// LES FONCTIONS POUR SE CONNECTER
void connexion(){
    puts("\n\n\n\n\n\n\n \t\t\t\t BIENVENUE DANS MANGUI DIEGEULOU SHOP !!!\n\n\n");

    PAUSE
    //VERIFICATION
    FILE *fichuser = NULL;
    char login[30],mdp[30],okLogin[20],verife[20];
    int trouve=0;

  //////////////////MA PAGE DE CONNECTION////////////////////////////////

     do{
            CLS
            printf("\n\t\t\t\t-------------------------------------------------------------");
            printf("\n\t\t\t\t--------------- PAGE DE CONNEXION ---------------------------");
            printf("\n\t\t\t\t-------------------------------------------------------------");
            printf("\n\t\t\t\t-------------------------------------------------------------");
            printf("\n\t\t\t\t---- LOGIN :                                              ---");
            printf("\n\t\t\t\t-------------------------------------------------------------");
            printf("\n\t\t\t\t-------------------------------------------------------------");
            printf("\n\t\t\t\t--- MOT DE PASSE :                                       ---");
            printf("\n\t\t\t\t------------------------------------------------------------");
            printf("\n\t\t\t\t------------------------------------------------------------");
            printf("\n\t\t\t\t---------                                      -------------");
            printf("\n\t\t\t\t-------------------------------------------------------------");
            printf("\n\t\t\t\t-------------------------------------------------------------");

      //les deux gotoxy pour l'emplacement du curseur
    gotoxy(45,5);
    gets(login);
    gotoxy(52,8);
   gets(mdp);
   //METTRES LES INFORMATIONS DANS UN FICHIER
    fichuser = fopen("USERS","rb");
    if(fichuser){
        while(fread(&Users,sizeof(Users),1,fichuser),!feof(fichuser)){
            if(strcasecmp(Users.login,login)==0 && strcasecmp(Users.mdp,mdp)==0){

                strcpy(Session.nom,Users.nom);
                strcpy(Session.prenom,Users.prenom);
                strcpy(Session.tel,Users.tel);
                strcpy(Session.mdp,Users.mdp);
                strcpy(Session.login,Users.login);
                trouve=1;
                if(Users.etat == 0){
                    nouveau_mdp();
                }
                PAUSE
                menuPrincipal();
            }
        }
        if (trouve==0)
        {
            gotoxy(75,11);
            printf("LOGIN OU MOT DE PASSE INCORRECT");
            gotoxy(72,14);
            PAUSE
        }
    }fclose(fichuser);
}while(trouve!=1);

}





//////////////////////////////NOUVEAU MOT DE PASSE /////////////////////////////////////////////////////////////////



void nouveau_mdp(){
   FILE *fichuser = NULL;
   char mdp[20],confirme[20];
   fichuser = fopen("USERS","r+b");
   if(fichuser){
                    while(fread(&Users,sizeof(Users),1,fichuser),!feof(fichuser)){
                        if(strcasecmp(Users.login,Session.login)==0&&strcasecmp(Users.mdp,Session.mdp)==0){
                            break;
                        }
                    }
                    CLS
                    gotoxy(65,8);
                    printf("\n\t\t\t\t---------------------------------------------------------------------------------------------------------------------");
                    printf("\n\t\t\t\t---------------------------------------------------------------------------------------------------------------------");
                    printf("\n\t\t\t\t------- FELICITION VOUS AVEZ PUIS VOUS CONNECTER %s %s VEILLIEZ CHANGE VOTRE MOT DE PASSE SVP           ---",Session.prenom,Session.nom);
                    printf("\n\t\t\t\t---------------------------------------------------------------------------------------------------------------------");
                    printf("\n\t\t\t\t---------------------------------------------------------------------------------------------------------------------");
                                                            gotoxy(72,25);
                    PAUSE
                    do{
                            CLS
            printf("\n\t\t\t\t\t\t\t\t------------------------------------------------------------");
            printf("\n\t\t\t\t\t\t\t\t------------------ PAGE DE CONNEXION -----------------------");
            printf("\n\t\t\t\t\t\t\t\t------------------------------------------------------------");
            printf("\n\t\t\t\t\t\t\t\t------------------------------------------------------------");
            printf("\n\t\t\t\t\t\t\t\t--- NOUVEAU MOT DE PASSE :                               ---");
            printf("\n\t\t\t\t\t\t\t\t------------------------------------------------------------");
            printf("\n\t\t\t\t\t\t\t\t------------------------------------------------------------");
            printf("\n\t\t\t\t\t\t\t\t--- CONFIRMATION :                                       ---");
            printf("\n\t\t\t\t\t\t\t\t------------------------------------------------------------");
            printf("\n\t\t\t\t\t\t\t\t---                                                    -----");
            printf("\n\t\t\t\t\t\t\t\t------------------------------------------------------------");
            printf("\n\t\t\t\t\t\t\t\t------------------------------------------------------------");
                     gotoxy(91,5);
                    gets(mdp);
                    gotoxy(83,8);
                    gets(confirme);
                    if(strcasecmp(Session.mdp,mdp)==0){
                            gotoxy(70,10);
                        printf("LE MOT DE PASSE DOIT ETRE DIFFERENT DU PRECEDENT.");
                             gotoxy(94,16);
                        PAUSE
                    }else if(strcasecmp(mdp,confirme)!=0){
                              gotoxy(85,10);
                        printf("CONFIRMATION INCORRECT");
                              gotoxy(60,16);
                        PAUSE
                    }

                    }while(strcasecmp(Session.mdp,mdp)==0||strcasecmp(mdp,confirme)!=0);

                    //fseek: Cette fonction permet d'effectuer la position du pointeur de fichier.
                    fseek(fichuser,-1l*sizeof(Users),SEEK_CUR);
                    strcpy(Users.mdp,mdp);
                     Users.etat = 1;
                     fwrite(&Users,sizeof(Users),1,fichuser);
                     gotoxy(60,16);
                     printf("MOT DE PASSE MODIFIER AVEC SUCCES");
                     gotoxy(60,19);
                                   PAUSE
   }fclose(fichuser);
                       menuPrincipal();
}


//-----------------------------------------------------MENU PRINCIPALE---------------------------------------------------------------------------

//fonction MENU PRINCIPAL

void menuPrincipal(){



   // system("pause");
    system("cls");

    puts("\n\n\n");


                printf("\t\t\t      §              §   § § § § § §  §           §  § § § § § §  §       §  § \n");system("color 0c");_sleep(25);
                printf("\t\t\t      § §          § §   §         §  § §         §  §            §       §  § \n");system("color 0f");_sleep(25);
                printf("\t\t\t      §   §      §   §   §         §  §   §       §  §            §       §  § \n");system("color 0c");_sleep(25);
                printf("\t\t\t      §     §  §     §   § § § § § §  §     §     §  §   § § § §  §       §  § \n");system("color 0f");_sleep(25);
                printf("\t\t\t      §       §      §   §         §  §       §   §  §         §  §       §  § \n");system("color 0c");_sleep(25);
                printf("\t\t\t      §              §   §         §  §         § §  §         §  §       §  § \n");system("color 0c");_sleep(25);
                printf("\t\t\t      §              §   §         §  §           §  § § § § § §  § § § § §  § \n");system("color 0c");_sleep(25);



    puts("\n\n\n\n\n\n\n");
                            printf("\t\t\t    §          §   §  § § § § § §   § § § § § § §  §           §  §             § § § § § §  §         §\n");system("color 0c");_sleep(25);
                            printf("\t\t\t    §  §       §   §  §             §              §           §  §             §         §  §         §\n");system("color 0c");_sleep(25);
                            printf("\t\t\t    §    §     §   §  §             §              §           §  §             §         §  §         §\n");system("color 0c");_sleep(25);
                            printf("\t\t\t    §      §   §   §  § § § § § §   §              §           §  §             §         §  §         §\n");system("color 0c");_sleep(25);
                            printf("\t\t\t    §     §    §   §  §             §     § § § §  §           §  §             §         §  §         §\n");system("color 0c");_sleep(25);
                            printf("\t\t\t    §  §       §   §  §             §           §  §           §  §             §         §  §         §\n");system("color 0c");_sleep(25);
                            printf("\t\t\t    § §        §   §  §             §           §  §           §  §             §         §  §         §\n");system("color 0c");_sleep(25);
                            printf("\t\t\t    §          §   §  § § § § § §   § § § § § § §  § § § § § § §  § § § § § §   § § § § § §  § § § § § §\n");system("color 0c");_sleep(25);



    puts("\n\n\n\n\n\n\n");




                        printf("\t\t\t  § § § § § §   §         §    § § § § § § §   § § § § §\n");system("color 0c");_sleep(25);
                        printf("\t\t\t  §             §         §    §           §   §       §\n");system("color 0c");_sleep(25);
                        printf("\t\t\t  §             §         §    §           §   §       §\n");system("color 0c");_sleep(25);
                        printf("\t\t\t  §             §         §    §           §   § § § § §\n");system("color 0c");_sleep(25);
                        printf("\t\t\t  § § § § § §   § § § § § §    §           §   §        \n");system("color 0c");_sleep(25);
                        printf("\t\t\t            §   §         §    §           §   §        \n");system("color 0c");_sleep(25);
                        printf("\t\t\t            §   §         §    §           §   §        \n");system("color 0c");_sleep(25);
                        printf("\t\t\t            §   §         §    §           §   §        \n");system("color 0c");_sleep(25);
                        printf("\t\t\t  § § § § § §   §         §    § § § § § § §   §        \n");system("color 0c");_sleep(25);




    system("color 0d");_sleep(10);
    system("color 0c");_sleep(10);
    system("color 0d");_sleep(10);
    system("color 0c");_sleep(10);
    system("color 0d");_sleep(10);
    system("color 0c");_sleep(10);
    system("cls");
    //_sleep(10);




puts("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");






    printf("\t\t\t\t\t\t   #######  #  ######  #     #  #        #  ######  #     #  #    #  ######    \n");system("color 0c");_sleep(25);
    printf("\t\t\t\t\t\t   #     #  #  #       # #   #   #      #   #       # #   #  #    #  #         \n");system("color 0f");_sleep(25);
    printf("\t\t\t\t\t\t   ######   #  ####    #  #  #    #    #    ####    #  #  #  #    #  ####      \n");system("color 0c");_sleep(25);
    printf("\t\t\t\t\t\t   #     #  #  #       #   # #     #  #     #       #   # #  #    #  #         \n");system("color 0f");_sleep(25);
    printf("\t\t\t\t\t\t   #######  #  ######  #     #      ##      ######  #     #  ######  ######    \n");system("color 0c");_sleep(25);



    system("color 0d");_sleep(10);
    system("color 0c");_sleep(10);
    system("color 0d");_sleep(10);
    system("color 0c");_sleep(10);
    system("color 0d");_sleep(10);
    system("color 0c");_sleep(10);
    system("cls");


    //_sleep(10);

puts("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");



        puts("\t\t\t\t\t\t\t\t #######    #######    #######    #######       ");_sleep(100);system("color 01");
        puts("\t\t\t\t\t\t\t\t #          #     #    #     #    #     #       ");_sleep(100);system("color 02");
        puts("\t\t\t\t\t\t\t\t #  ####    #     #    #     #    #  ###        ");_sleep(100);system("color 03");
        puts("\t\t\t\t\t\t\t\t #     #    #     #    #     #    #    #        ");_sleep(100);system("color 00");
        puts("\t\t\t\t\t\t\t\t #######    #######    #######    #     #       ");_sleep(100);system("color 04");

        puts("\n\n");

        puts("\t\t\t\t\t\t\t\t #######    #######    #          #              ");_sleep(100);system("color 05");
        puts("\t\t\t\t\t\t\t\t #          #     #    #          #              ");_sleep(100);system("color 06");
        puts("\t\t\t\t\t\t\t\t #          #     #    #          #              ");_sleep(100);system("color 07");
        puts("\t\t\t\t\t\t\t\t ######     #######    #          #              ");_sleep(100);system("color 08");
        puts("\t\t\t\t\t\t\t\t #          #     #    #          #              ");_sleep(100);system("color 09");
        puts("\t\t\t\t\t\t\t\t #          #     #    #######    #######        ");_sleep(100);system("color 0a");

        puts("\n\n");

        puts("\t\t\t\t\t\t\t\t #######    #     #    #######    #######         ");_sleep(100);system("color 0b");
        puts("\t\t\t\t\t\t\t\t #          #     #    #     #    #     #         ");_sleep(100);system("color 0c");
        puts("\t\t\t\t\t\t\t\t #          #     #    #     #    #     #         ");_sleep(100);system("color 0d");
        puts("\t\t\t\t\t\t\t\t #######    #######    #     #    #######         ");_sleep(100);system("color 00");
        puts("\t\t\t\t\t\t\t\t       #    #     #    #     #    #               ");_sleep(100);system("color 0e");
        puts("\t\t\t\t\t\t\t\t       #    #     #    #     #    #               ");_sleep(100);system("color 0f");
        puts("\t\t\t\t\t\t\t\t #######    #     #    #######    #               ");_sleep(100);system("color 01");


    printf("\n\n\n");
    system("color 5f");_sleep(100);

    printf("\t\t\t\t\t   #######   #######  #      #  ##########   #     #######     #      #  #######  \n");_sleep(100);
    printf("\t\t\t\t\t   #      #  #     #  #      #      ##       #    #       #    #      #  #        \n");_sleep(100);
    printf("\t\t\t\t\t   #      #  #     #  #      #      ##       #   #         #   #      #  #        \n");_sleep(100);
    printf("\t\t\t\t\t   #  ####   #     #  #      #      ##       #   #         #   #      #  #####    \n");_sleep(100);
    printf("\t\t\t\t\t   #      #  #     #  #      #      ##       #   #       # #   #      #  #        \n");_sleep(100);
    printf("\t\t\t\t\t   #      #  #     #  #      #      ##       #    #       #    #      #  #        \n");_sleep(100);
    printf("\t\t\t\t\t   #######   #######  ########      ##       #     #######  #  ########  #######  \n");_sleep(100);

        system("color 5f");_sleep(100);


printf("\n\n");
    system("pause");


    system("mode con LINES=39 COLS=170");
    int choix;
    char temps[20];
    printf("\n\n\t\t\t\t\t\t\tBIENVENU(E) %s %s\n",Session.prenom,Session.nom);
    PAUSE
    do{
        CLS
    printf("\n\n\n\n\n\t\t\t\t\t\t\tUTILISATEUR CONNECTE(E) : %s %s\n",Session.prenom,Session.nom);
    printf("\n\t\t\t\t\t\t\t%s %s",__TIME__,__DATE__);

            printf("\n\n\n\n");
            printf("\n\n\n\n\t\t\t\t\t\t\t____________________________________________________________");
            printf("\n\t\t\t\t\t\t\t################## MENU PRINCIPAL ##########################");
            printf("\n\t\t\t\t\t\t\t############################################################");
            printf("\n\t\t\t\t\t\t\t############################################################");
            printf("\n\t\t\t\t\t\t\t####   1---------- Ajouter un utilisateur               ####");
            printf("\n\t\t\t\t\t\t\t############################################################");
            printf("\n\t\t\t\t\t\t\t####   2---------- Lister des utilisateur               ####");
            printf("\n\t\t\t\t\t\t\t############################################################");
            printf("\n\t\t\t\t\t\t\t####   3---------- Ajouter une categorie                ####");
            printf("\n\t\t\t\t\t\t\t############################################################");
            printf("\n\t\t\t\t\t\t\t####   4---------- Lister les categories                ####");
            printf("\n\t\t\t\t\t\t\t############################################################");
            printf("\n\t\t\t\t\t\t\t####   5---------- Ajouter un produit                   ####");
            printf("\n\t\t\t\t\t\t\t############################################################");
            printf("\n\t\t\t\t\t\t\t####   6---------- Lister les produits                  ####");
            printf("\n\t\t\t\t\t\t\t############################################################");
            printf("\n\t\t\t\t\t\t\t####   7---------- Imprimer  l'etat du jour             ####");
            printf("\n\t\t\t\t\t\t\t############################################################");
            printf("\n\t\t\t\t\t\t\t####   8---------- Effectuer une vente                  ####");
            printf("\n\t\t\t\t\t\t\t############################################################");
            printf("\n\t\t\t\t\t\t\t####   9---------- Deconnecter                          ####");
            printf("\n\t\t\t\t\t\t\t############################################################");
            printf("\n\t\t\t\t\t\t\t####   10---------- Fermer le programme                 ####");
            printf("\n\t\t\t\t\t\t\t############################################################");
            printf("\n\t\t\t\t\t\t\t####   11---------- Bloquer ou Debloquer un user        ####");
            printf("\n\t\t\t\t\t\t\t############################################################");
            printf("\n\t\t\t\t\t\t\t############################################################");
            printf("\n\t\t\t\t\t\t\t############################################################");
            printf("\n\t\t\t\t\t\t\t####   Faites votre chsoix:");
            scanf("%d",&choix);
            printf("\n\t\t\t\t\t\t\t############################################################");


    switch(choix){
    case 1 :
        //ajoutUser(); PAUSE
        break;
    case 2:
        //listUsers(); PAUSE
        break;
    case 3:
        //ajoutCategorie(); PAUSE
        break;
    case 4:
        //listCategories(); PAUSE
        break;
    case 5:
        //ajoutArticle(); PAUSE
        break;
    case 6:
        //listProduits(); PAUSE
        break;
    case 7:
        //etatJournalier(); PAUSE
        break;
    case 8:
        PAUSE
        VIDER
        //Vente();
        break;
    case 9:
        PAUSE
        VIDER
        CLS
        connexion();
        break;
    case 10:
        return 0;
        break;
    case 11:
        //bloque_debloque_users(); PAUSE
        break;
        default : {
             printf("choix invalide");
        }
    }
}while(1);
}


//______________________________________________________________________________________________________________


















































//-----------------------------------------------------------------------------------------------------///////

    // LES METHODES OU FONCTIONS

main(){

    connexion();
    //menuPrincipal();


}

