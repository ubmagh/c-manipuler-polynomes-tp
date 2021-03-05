#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <string.h>
#ifdef _WIN32
#define WINDOWS 1
#else
#define WINDOWS 0
#endif // _WIN32
#define MAX_DEGREE 10
#define MAX_STRING_CANBE 400
#define MAX_NEWTON_ITERATIONS 12
#include "TP2.h"

int main(){


    Polynome ** tab_Polynomes=NULL;
    short unsigned number_pols=0;
    short unsigned choice=0;



///# Menu start
menu:
    clear_screen();
    header();
    printf(" \n\t [Menu] Saisissez un chiffre pour :  \n");
    printf("\n\n\t\t 1. Afficher les Polynomes enregistres ");
    printf("\n\n\t\t 2. Gerer les Polynomes enregistres ");
    printf("\n\n\t\t 3. Manipuler les Polynomes enregistres ");
    printf("\n\n\t\t 4. Calcule de racine approchee methode de Newton-Raphson ");
    printf("\n\n\t\t 0. Quitter ");
    do{
    printf("\n\n\t\t\t Votre choix est : ");
    choice = getch();
    choice -=48;
    printf(" %d", choice);
    }while(choice >4 || choice<0);

    switch(choice){
    case 0:
        goto exit;
        break;
    case 1:
        clear_screen();
        Show_Polynoms( tab_Polynomes, number_pols);
        printf("\n\n\t ....... Appuyez sur un botton pour continuer .........");
        getch();
        goto menu;
        break;
    case 2:
        goto Gestion_Pols;
        break;
    case 3:
        goto Manipuler_Pols;
        break;
    case 4:
        goto Newtone_Raphson;
        break;
    }
///# Menu end




///# manage polynoms Start #
Gestion_Pols:
    clear_screen();
    header();
    printf(" \n\t [Gestion des polynomes enregistres] Saisissez un chiffre pour :  \n");
    printf("\n\n\t\t 1. Ajouter un nouveau polynome ");
    printf("\n\n\t\t 2. Resaisir un polynom ");
    printf("\n\n\t\t 3. Supprimer un polynom ");
    printf("\n\n\t\t 0. Retourner au menu principal");

    do{
    printf("\n\n\t\t\t Votre choix est : ");
    choice = getch();
    choice -=48;
    printf(" %d", choice);
    }while(choice >3 || choice<0);

    if(!choice)
        goto menu;
    switch(choice){
    case 1:
        new_polynome( &tab_Polynomes, &number_pols);
        break;
    case 2:
        edit_polynome( &tab_Polynomes, number_pols);
        break;
    case 3:
        rem_polynome( &tab_Polynomes, &number_pols);
        break;
    }
    goto Gestion_Pols;
///# manage polynoms End #



///#  play with polynoms Start #
Manipuler_Pols:
    clear_screen();
    header();
    printf(" \n\t [Manipuler les Polynomes enregistres] Saisissez un chiffre pour :  \n");
    printf("\n\n\t\t 1. additioner deux polynomes ");
    printf("\n\n\t\t 2. soustraire deux polynomes ");
    printf("\n\n\t\t 3. multiplier deux polynomes ");
    printf("\n\n\t\t 4. Comparer deux polynomes ");
    printf("\n\n\t\t 5. Changer le signe d'un polynome ");
    printf("\n\n\t\t 6. La dirivee d'un polynome ");
    printf("\n\n\t\t 7. calculer Pi(x)");
    printf("\n\n\t\t 8. Creer la Trace d'un polynome ");
    printf("\n\n\t\t 0. Retourner au menu principal");

    do{
    printf("\n\n\t\t\t Votre choix est : ");
    choice = getch();
    choice -=48;
    printf(" %d", choice);
    }while(choice >8 || choice<0);

    if(!choice)
        goto menu;
    switch(choice){
        case 1:
            add_polynomes( &tab_Polynomes, &number_pols);
            break;
        case 2:
            sstract_polynomes( &tab_Polynomes, &number_pols);
            break;
        case 3:
            multply_polynomes( &tab_Polynomes, &number_pols);
            break;
        case 4:
            comparer_deuxPols( &tab_Polynomes, number_pols);
            break;
        case 5:
            Change_sign( &tab_Polynomes, number_pols);
            break;
        case 6:
            Dirivee( &tab_Polynomes, &number_pols);
            break;
        case 7:
            Calculer_PdeX( tab_Polynomes, number_pols);
            break;
        case 8:
            Trace( tab_Polynomes, number_pols );
            break;
        case 0:
            goto menu;
            break;
    }
    goto Manipuler_Pols;
///# manage polynoms End #


///# Start Newtone_Raphson  ###

Newtone_Raphson:
    Newtone_Raphson_estimation( tab_Polynomes, number_pols);
goto menu;
/// ## End Newtone_Raphson ##

exit:
    do{
            printf("\n\n\t etes-vous sure de Quitter ? (o/n) :  ");
            choice = getch();
        }while( choice!=111 && choice!= 110 && choice!= 79 && choice!=78 );
    if( choice==78 || choice ==110 )
        goto menu;
    printf("\n\n\t Liberation de ressources ....");
    free_all(&tab_Polynomes, number_pols);
    printf("\n\t termine ");
    exit(0);
    return 0;
}
