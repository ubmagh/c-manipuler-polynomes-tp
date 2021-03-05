// Types dérivés

typedef struct ax{
    unsigned exposant;
    double scalaire;
    struct ax * next; // liste chainnée
} ax;

typedef struct  Polynome{
    short unsigned degree;// information redandante
    short unsigned num_coefficients;
    struct ax * coefficients ;
}  Polynome;


/*
 ## todo


*/




// Prototypes
void print_Poly( Polynome *P, int indice );
void clear_screen();
void header();
void free_polynom( Polynome ** P );
void free_all( Polynome ***P, int nbr_pols);
void Show_Polynoms( Polynome ** tab_Ps, const int number_Ps );
void new_polynome( Polynome *** tab_Ps, short unsigned * number_Ps );
    static void saisir_coefficient_newPol( Polynome ** poly ); // return degree du polynome rempli
    static void insert_node(Polynome ** poly);
void edit_polynome( Polynome *** tab_Ps, short unsigned number_Ps );
void rem_polynome( Polynome *** tab_Ps, short unsigned * number_Ps );
void add_polynomes( Polynome *** tab_Ps, short unsigned * number_Ps );
    static short unsigned max_degree(short unsigned a, short unsigned b);
void sstract_polynomes( Polynome *** tab_Ps, short unsigned * number_Ps );
    static void delete_zero_axs( Polynome **poly );
void multply_polynomes( Polynome *** tab_Ps, short unsigned * number_Ps );
void comparer_deuxPols( Polynome *** tab_Ps, short unsigned number_Ps );
    static int checkTwoPols( Polynome * pointer1,  Polynome * pointer2);
void Change_sign( Polynome *** tab_Ps, short unsigned number_Ps );
void Dirivee( Polynome *** tab_Ps, short unsigned * number_Ps );
    static Polynome* Get_derivated( Polynome* pointer);
void Calculer_PdeX( Polynome ** tab_Ps, short unsigned number_Ps);
    static double PdeX( Polynome* polynome, double x );
void Trace( Polynome ** tab_Ps, short unsigned number_Ps);
    static char * Pol_toString( Polynome * polynome);
void Newtone_Raphson_estimation( Polynome ** tab_Ps, short unsigned number_Ps);
    static double Suite_Newton_Raphson( Polynome *p_x, Polynome *p_pr_x, double x0, int iteration);






// Définition des fonctions

static double Suite_Newton_Raphson( Polynome *p_x, Polynome *p_pr_x, double xk, int iteration){ /// Recursion

    if( iteration >= MAX_NEWTON_ITERATIONS )
        return xk;
    double val_p_x = PdeX( p_x, xk);    /// P( Xk )
    double val_p_pr_x = PdeX( p_pr_x, xk); /// P'( Xk )

    if( val_p_pr_x==0 ){
        printf(" \n\n\t division par 0 impossible, Ressayer avec un autre Xk, P'(x) =0 ");
        return 0;
    }

    return Suite_Newton_Raphson( p_x, p_pr_x, xk-(val_p_x/val_p_pr_x), iteration+1);
}





void Newtone_Raphson_estimation( Polynome ** tab_Ps, short unsigned number_Ps){
    int choice=0;
    Polynome * p_x=NULL;
    Polynome * p_pr_x=NULL;
    double x0=0,x=0;
    clear_screen();
    header();
    printf("\n\t\t ## Estimation du racine Par la methode de newton-raphson :\n\n");
    if( (number_Ps)<1 ){
        printf(" \n\n\t\t faites d'abord creer un polynome au minimum ! \n\n\n\t ............ Appuyez sur un botton pour continuer .............");
        getch();
        return;
    }


    Show_Polynoms( tab_Ps, number_Ps);
    do{
        printf("\n\t\t  [ newton-raphson] Choisissez un polynome Pi(x) : " );
        scanf(" %d", &choice);
    }while(choice<1 || choice> (number_Ps));

    p_x = tab_Ps[choice-1]; /// P(x)
    p_pr_x = Get_derivated(p_x); /// P'(x)

    printf("\n\t\t  [ newton-raphson ] saisissez une l'estimation x0 (accepte double): " );
    scanf(" %lf", &x0);

    printf("\n\n\t\t [ newton-raphson ] Nombre d'iterations a faire : %d",MAX_NEWTON_ITERATIONS);

    x= Suite_Newton_Raphson( p_x, p_pr_x, x0, 0);// 0 current iteration
    printf("\n\n\n\n\t\t [ newton-raphson ] Resultat : racine = %.10lf   et   p(racine) = %.10lf ", x, PdeX(p_x,x) );
    printf("\n\n\n\t........ Appuyez sur un botton pour continuer ........ \n\n");
    getch();
}




static char * Pol_toString( Polynome * polynome){
    struct ax * aix = polynome->coefficients;
    char ax[45]="";
    char tmp[20]="";
    char str[200] = "";
    while( aix!=NULL ){
        if(aix->scalaire>=0)
            sprintf( ax, "+%lf", aix->scalaire );
        else
            sprintf( ax, "%lf", aix->scalaire );
        sprintf( tmp, "*(x**%d)",aix->exposant);
        strcat( str, ax);
        strcat( str, tmp);
        aix = aix->next;
    }
    char * STR = (char *) calloc( strlen(str), sizeof(char));
    strcpy( STR, str);
    return STR;
}


void Trace( Polynome ** tab_Ps, short unsigned number_Ps){


    short int tab [number_Ps], interval[2];
    short int i, pol;
    char choice;
    char str[MAX_STRING_CANBE]="" ;
    char tmp[20]="";
    char *polystr=NULL;

    for( i=0; i<number_Ps; i++){
        tab[i]=0;
    }
    clear_screen();
    header();

    printf("\n\n\n\t Avant de continuer assurez que Gnuplot est ajouté au plage des variables globales de votre systeme pour tracer automatiquement les polynomes, sinon executer les commande enregistrees dans le fichier ploter.txt manuelement pour les tracer.");
    printf("\n\t Appuyez sur un botton pour continuer");
    getch();

    if( (number_Ps)<1 ){
        printf(" \n\n\t\t faites d'abord creer un polynome au minimum ! \n\n\n\t ............ Appuyez sur un botton pour continuer .............");
        getch();
        return;
    }
    Show_Polynoms( tab_Ps, number_Ps);
    printf("\n\n\t      [ Tracer un polynome ] Choisir les polynomes à tracer : \n" );
    do{
        do{
            printf("\n\n\t [ Tracer un polynome ] selectionner un polynome : " );
            scanf(" %d", &pol);
        }while(pol<1 || pol> (number_Ps) || (!(int)pol));
        tab[pol-1]=1;

        printf("\n\t Voulez vous selectionner un autre  ? (o/n) :  ");
        choice = getch();

    }while( choice==111 || choice== 79  );

    do{
        printf("\n\n\t Voulez vous choisir un interval ? (o/n) :  ");
        choice = getch();
    }while( choice!=111 && choice!= 110 && choice!= 79 && choice!=78 );

    sprintf( str, "set term qt persist\n");

    if(choice == 111 || choice ==79){
        printf("\n\t saisir l'inteval [ a, b] :  ");
        printf("\n\t saisissez a :  ");
        scanf(" %d", &interval[0]);
        do{
        printf("\n\t saisissez b :  ");
        scanf(" %d", &interval[1]);
        }while(interval[0]>=interval[1]);
        printf("\n\t le traçcage sera dans l'interval: [ %d, %d]   ", interval[0], interval[1]);
        sprintf( tmp, "set xrange[%d:%d]\n", interval[0], interval[1] );
        strcat(str,tmp);
    }

    for(i=0; i<number_Ps; i++){
        if( tab[i] ){
            sprintf( tmp, "P%d(x) = ", i+1);
            strcat( str, tmp);
            polystr = Pol_toString(tab_Ps[i]);
            strcat( str, polystr);
            free(polystr);
            strcat(str, "\n");
        }
    }

    pol = 0; // re-use as flag of first has passed
    for(i=0; i<number_Ps; i++){
        if( tab[i] ){
            if(!pol){
                sprintf( tmp, "plot P%d(x)", i+1);
                strcat( str, tmp);
                pol=1;
            }
            else{
                sprintf( tmp, ", P%d(x)", i+1);
                strcat( str, tmp);
            }
        }
    }

    FILE * filetext = fopen("ploter.txt","w");
     if (filetext != NULL)
    {
        fputs( str, filetext);
        fclose(filetext);
    }else{
        printf("\n\n\n\t Erreur : impossible d'ouvrir un fichier text  ");
        return;
    }

    printf("\n\n\n\t Les polynomes a tracer sont ecrits dans le fichier ploter.txt  \n\n\n\t la trace des polynomes s'affichera en quelques instants .....\n\n\n");

    system("gnuplot -persist -c ploter.txt ");

    Show_Polynoms( tab_Ps, number_Ps);

    printf("\n\n\n\t........ Appuyez sur un botton pour continuer ........ \n\n");
    getch();
}




static double PdeX( Polynome* polynome, double x ){
    struct ax * ax1 = polynome->coefficients;
    double res = 0;
    while( ax1 != NULL){
        res += (ax1->scalaire * pow( x, ax1->exposant ) );
        ax1= ax1->next;
    }
    return res;
}

void Calculer_PdeX( Polynome ** tab_Ps, short unsigned number_Ps ){
    double x=0, res =0;
    int pol=1;
    clear_screen();
    header();
    if( (number_Ps)<1 ){
        printf(" \n\n\t\t faites d'abord creer un polynome au minimum ! \n\n\n\t ............ Appuyez sur un botton pour continuer .............");
        getch();
        return;
    }
    Show_Polynoms( tab_Ps, number_Ps);
    do{
        printf("\n\t\t      [ Calculer Pi(x) ] Choisissez un polynome Pi(x) : " );
        scanf(" %d", &pol);
    }while(pol<1 || pol> (number_Ps));
    printf("\n\t\t      [ Calculer P%d(x) ] Entrez la valeur de x : ", pol );
    scanf(" %lf", &x);

    res=  PdeX( tab_Ps[pol-1], x);
    printf("\n\t\t  [ Calculer P%d(x) ]    P%d( %.3lf ) = %.3lf    \n\t\t", pol, pol, x, res );
    printf("\n\n\n\t........ Appuyez sur un botton pour continuer ........ \n\n");
    getch();
}


static Polynome* Get_derivated( Polynome* pointer){
    Polynome * newPol = (Polynome *) calloc( 1, sizeof(Polynome));
    struct ax * ax1 = NULL;
    struct ax * ax2 = NULL;
    ax1 = pointer->coefficients;
    newPol->coefficients = NULL;
    newPol->num_coefficients = 0;
    newPol->degree = 0;
    if( pointer->degree ){
        newPol->degree = (pointer->degree) -1 ;
        newPol->coefficients = ( struct ax *) calloc( 1, sizeof( struct ax));
        ax2 = newPol->coefficients;
        while( ax1 !=NULL) {
                ax2->scalaire = ax1->scalaire * ax1->exposant;
                ax2->exposant = (ax1->exposant)- 1;
                ax2->next = NULL;
                ax1 = ax1->next;
                if( ( ax1 != NULL) && ax1->exposant ){
                    ax2->next = ( struct ax *) calloc( 1, sizeof( struct ax));
                    ax2= ax2->next;
                    ax2->next = NULL;
                }else{
                    break;
                }
        }
    }
    return newPol;
}


void Dirivee( Polynome *** tab_Ps, short unsigned * number_Ps ){
    int pol1=0;
    Polynome * pointer=NULL;
    Polynome * newPol =NULL;
    clear_screen();
    header();
    if( (*number_Ps)<1 ){
        printf(" \n\n\t\t faites d'abord creer un polynome au minimum ! \n\n\n\t ............ Appuyez sur un botton pour continuer .............");
        getch();
        return;
    }
    Show_Polynoms( *tab_Ps, *number_Ps);
    do{
        printf("\n\t\t      [ Dirivee d'un polynome] Choisissez un polynome Pi(x) : " );
        scanf(" %d", &pol1);
    }while(pol1<1 || pol1> (*number_Ps));
    pointer = (*tab_Ps)[pol1-1];
    newPol = Get_derivated(pointer);
    (* number_Ps)++;
    (* tab_Ps) = (Polynome**) realloc( (* tab_Ps), sizeof(Polynome*));
    (*tab_Ps) [ (*number_Ps)-1 ] = newPol;
    printf("\n\t\t   [ Dirivee d'un polynome] Dirivee de P%d(x) est P%d(x) tel que :  \n\t\t" , pol1, (*number_Ps) );
    print_Poly( (*tab_Ps)[(*number_Ps)-1 ], (*number_Ps) );
    printf("\n\n\n\t........ Appuyez sur un botton pour continuer ........ \n\n");
    getch();
}





void Change_sign( Polynome *** tab_Ps, short unsigned number_Ps ){
    int pol1=0;
    struct ax * ax1 = NULL;
    clear_screen();
    header();
    if( (number_Ps)<1 ){
        printf(" \n\n\t\t faites d'abord creer un polynome au minimum ! \n\n\n\t ............ Appuyez sur un botton pour continuer .............");
        getch();
        return;
    }
    Show_Polynoms( *tab_Ps, number_Ps);
    do{
        printf("\n\t\t      [ Sign d'un polynome] Choisissez un polynome Pi(x) : " );
        scanf(" %d", &pol1);
    }while(pol1<1 || pol1> (number_Ps));


    ax1 = ( (*tab_Ps)[pol1-1] )->coefficients;

    if( ax1 != NULL)
        while(ax1!=NULL){
            ax1->scalaire = - ax1->scalaire;
            ax1 = ax1->next;
        }

    printf("\n\t\t   [ Sign d'un polynome] Sign est changee : \n\t\t" );
    print_Poly( (*tab_Ps)[pol1-1], pol1-1 );

    printf("\n\n\n\t........ Appuyez sur un botton pour continuer ........ \n\n");
    getch();
}





static int checkTwoPols( Polynome * pointer1,  Polynome * pointer2){

    if( pointer1 == pointer2 )
        return 1;
    if( (pointer1->degree) != (pointer2->degree ) )
        return 0;
    if( (pointer1->num_coefficients) != (pointer2->num_coefficients))
        return 0;
    struct ax * ax1, *ax2;
    ax1 = pointer1->coefficients;
    ax2 = pointer2->coefficients;
    while( ax1 !=NULL && ax2!=NULL ){
        if( ax1->scalaire != ax2->scalaire )
            return 0;
        if( ax1->exposant != ax2->exposant)
            return 0;

        ax1 = ax1->next;
        ax2 = ax2->next;
    }
     return 1;
}



void comparer_deuxPols( Polynome *** tab_Ps, short unsigned number_Ps ){
    int pol1=0, pol2=0; int res=0;
    clear_screen();
    header();
    if( (number_Ps)<1 ){
        printf(" \n\n\t\t faites d'abord creer un polynome au minimum ! \n\n\n\t ............ Appuyez sur un botton pour continuer .............");
        getch();
        return;
    }
    Show_Polynoms( *tab_Ps, number_Ps);
    do{
        printf("\n\t\t      [ Comparer deux polynomes] Choisissez le premier polynome Pi(x) : " );
        scanf(" %d", &pol1);
    }while(pol1<1 || pol1> (number_Ps));
    do{
        printf("\n\t\t      [ Comparer deux polynomes] Choisissez le deuxieme polynome Pi(x) : " );
        scanf(" %d", &pol2);
    }while(pol2<1 || pol2> (number_Ps));


    res =checkTwoPols(  ((*tab_Ps)[pol1-1]), ((*tab_Ps)[pol2-1]) );
    if( res ){
        printf("\n\n\n\t    Les deux polynomes P%d(x) et P%d(x) Sont identiques \n\n", pol1, pol2);
    }else{
        printf("\n\n\n\t    Les deux polynomes P%d(x) et P%d(x) ne Sont pas identiques \n\n", pol1, pol2);
    }
    printf("\n\n\t");
    print_Poly( ((*tab_Ps)[pol1-1]), pol1 );
    printf("\n\t");
    print_Poly( ((*tab_Ps)[pol2-1]), pol2 );
    printf("\n\n\t........ Appuyez sur un botton pour continuer ........ \n\n");
    getch();
}




void multply_polynomes( Polynome *** tab_Ps, short unsigned * number_Ps ){
    Polynome * newPol = (Polynome *) calloc( 1, sizeof(Polynome));
    Polynome * pointer1;
    Polynome * pointer2;
    struct ax * ax1;
    struct ax * ax2;
    double * tab_Scalaires = NULL;
    short unsigned i,j;
    int pol1=0, pol2=0;
    int exposant1, exposant2; //  int instead of unsigned
    clear_screen();
    header();
    if( (*number_Ps)<1 ){
        printf(" \n\n\t\t faites d'abord creer un polynome au minimum ! \n\n\n\t ............ Appuyez sur un botton pour continuer .............");
        getch();
        return;
    }
    Show_Polynoms( *tab_Ps, *number_Ps);
    do{
        printf("\n\t\t      [ Multiplier deux polynomes] Choisissez le premier polynome Pi(x) : " );
        scanf(" %d", &pol1);
    }while(pol1<1 || pol1> (*number_Ps));
    do{
        printf("\n\t\t      [ Multiplier deux polynomes] Choisissez le deuxieme polynome Pi(x) : " );
        scanf(" %d", &pol2);
    }while(pol2<1 || pol2> (*number_Ps));
    pointer1 = (*tab_Ps)[pol1-1];
    pointer2 = (*tab_Ps)[pol2-1];
    newPol->degree = pointer1->degree + pointer2->degree;
    newPol->num_coefficients= 0;
    newPol->coefficients = NULL;
    if( pointer1->coefficients == NULL || pointer2->coefficients ==NULL ){
        newPol->num_coefficients = 0;
        newPol->degree = 0;
        newPol->coefficients= NULL;
        (*number_Ps)++;
        (*tab_Ps) = (Polynome**) realloc( (*tab_Ps), (*number_Ps) * sizeof(Polynome*) );
        (*tab_Ps)[(*number_Ps)-1] = newPol;
        return;
    }
    tab_Scalaires = (double *) calloc( newPol->degree+1, sizeof(double) );
    for( i=0; i< (newPol->degree+1); i++)
        tab_Scalaires[i] = 0;
    ax1 = pointer1->coefficients;
    ax2 = pointer2->coefficients;
    i = newPol->degree+1;
    while( ax1!=NULL ){
        while( ax2 != NULL ){
            tab_Scalaires[i- ax1->exposant - ax2->exposant-1] += ax1->scalaire * ax2->scalaire;
            ax2 = ax2->next;
        }
        ax2 = pointer2->coefficients;
        ax1 = ax1->next;
    }
    // convertir le tableau des scalaires vers une liste chainnée
    newPol->coefficients = (struct ax *)calloc( 1, sizeof(struct ax));
    ax1 = newPol->coefficients; // re-utiliser ce pointeur
    for( j=0; j<i ; j++){
        if(tab_Scalaires[j]){
            ax1->exposant = i-1- j;
            ax1->scalaire = tab_Scalaires[j];
            if( (j+1)< i && tab_Scalaires[j+1] ){
                ax1->next = (struct ax *)calloc( 1, sizeof(struct ax));;
                ax1 = ax1->next;
            }
        }
    }
    ax1->next = NULL;
    (*number_Ps)++;
    (*tab_Ps) = (Polynome**) realloc( (*tab_Ps), (*number_Ps) * sizeof(Polynome*) );
    (*tab_Ps)[(*number_Ps)-1] = newPol;
    printf(" \n\n\n\t\t la Multiplication des deux polynomes est stockee dans le %d-eme polynome. \n\n\t P%d(x) * P%d(x) = P%d(x) \n\n\t ", *number_Ps, pol1, pol2, *number_Ps );
    print_Poly( newPol, *number_Ps);
    printf("\n\n\t........ Appuyez sur un botton pour continuer ........ \n\n");
    getch();
}








static void delete_zero_axs( Polynome **poly ){
    struct ax * holder = (*poly)->coefficients; // holds last checked position
    struct ax * traverser = holder; // checkes scalaire if its == 0
    struct ax * destroyer = NULL; // node with scalaire =0 to free it
    struct ax * newCoeff = holder;
    short unsigned flag_StartNewCoef = 1, num_coeff=1;
    if(holder->exposant==0) // rien à changer
        return;
    while( traverser != NULL ){
        if( traverser->scalaire==0  ){
            destroyer = traverser;
            traverser = traverser->next;
            free(destroyer);
        }
        else{
                if(flag_StartNewCoef){
                    newCoeff = traverser;
                    holder = traverser;
                    flag_StartNewCoef = 0;
                }else{
                    holder->next=traverser;
                    holder = holder->next;
                    num_coeff ++ ;
                }
                traverser= traverser->next;
        }
    }
    if( destroyer == newCoeff ){
        newCoeff = ( struct ax *) calloc( 1, sizeof(struct ax));
        newCoeff->exposant = 0;
        newCoeff->next=NULL;
        newCoeff->scalaire=0;
     }
    holder->next = NULL;
    (*poly)->coefficients = newCoeff;
    (*poly)->degree = newCoeff->exposant;
    (*poly)->num_coefficients = num_coeff;
}




void sstract_polynomes( Polynome *** tab_Ps, short unsigned * number_Ps ){
    Polynome * new_poly= (Polynome *) calloc( 1, sizeof(Polynome));
    Polynome * pointer1;
    Polynome * pointer2;
    struct ax * ax1=NULL;
    struct ax * ax2=NULL;
    struct ax * setter= (struct ax*) calloc( 1, sizeof(struct ax));
    int pol1=0, pol2=0;
    int exposant1, exposant2; //  int instead of unsigned
    clear_screen();
    header();
    if( (*number_Ps)<1 ){
        printf(" \n\n\t\t faites d'abord creer un polynome au minimum ! \n\n\n\t ............ Appuyez sur un botton pour continuer .............");
        getch();
        return;
    }
    Show_Polynoms( *tab_Ps, *number_Ps);
    do{
        printf("\n\t\t      [ soustraire deux polynomes] Choisissez le premier polynome Pi(x) : " );
        scanf(" %d", &pol1);
    }while(pol1<1 || pol1> (*number_Ps));
    do{
        printf("\n\t\t      [ soustraire deux polynomes] Choisissez le deuxieme polynome Pi(x) : " );
        scanf(" %d", &pol2);
    }while(pol2<1 || pol2> (*number_Ps));
    new_poly->degree= max_degree( ( (*tab_Ps)[pol1-1])->degree, ((*tab_Ps)[pol2-1])->degree );
    new_poly->num_coefficients = 0;
    new_poly->coefficients = setter;
    pointer1 = (*tab_Ps)[pol1-1];
    pointer2 = (*tab_Ps)[pol2-1];
    ax1 = pointer1->coefficients ;
    ax2 = pointer2->coefficients;
    // p1- p2 <==> ax1-ax2
    while(ax1!= NULL || ax2!=NULL){

        if( ax1!=NULL )
            exposant1 = ax1->exposant;
        else
            exposant1 = -1;
        if( ax2!=NULL )
            exposant2 = ax2->exposant;
        else
            exposant2 = -1;
        if( exposant1 > exposant2 ){
            setter->exposant = exposant1;
            setter->scalaire = ax1->scalaire;
            ax1 = ax1->next;

        }else
        {
            if( exposant1 == exposant2 ){
                setter->exposant = exposant1;
                setter->scalaire = ax1->scalaire - ax2->scalaire;
                ax1 = ax1->next;
                ax2 = ax2->next;
            }else{ // ax1->exposant < ax2->exposant
                setter->exposant = -exposant2;
                setter->scalaire = ax2->scalaire;
                ax2 = ax2->next;
            }
        }
        if( ax1 != NULL || ax2!= NULL ){
            setter->next = (struct ax *) calloc( 1, sizeof(struct ax));
            setter = setter->next;
            (new_poly->num_coefficients) ++;
        }
    }
    ( *number_Ps )++ ;
    delete_zero_axs(&new_poly);
    (*tab_Ps) = (Polynome **) realloc( (*tab_Ps), (*number_Ps)*sizeof(Polynome*));
    (*tab_Ps)[ (*number_Ps)-1 ] = new_poly;
    printf(" \n\n\n\t\t la soustraction des deux polynomes est stockee dans le %d-eme polynome. \n\n\t P%d(x) - P%d(x) = P%d(x) \n\n\t ", *number_Ps, pol1, pol2, *number_Ps );
    print_Poly( new_poly, *number_Ps);
    printf("\n\n\t........ Appuyez sur un botton pour continuer ........ \n\n");
    getch();
}



static short unsigned max_degree(short unsigned a, short unsigned b){
    return (a>b)? a: b;
}




void add_polynomes( Polynome *** tab_Ps, short unsigned * number_Ps ){
    Polynome * new_poly= (Polynome *) calloc( 1, sizeof(Polynome));
    Polynome * pointer1;
    Polynome * pointer2;
    struct ax * ax1=NULL;
    struct ax * ax2=NULL;
    struct ax * setter= (struct ax*) calloc( 1, sizeof(struct ax));
    int pol1=0, pol2=0;
    int exposant1, exposant2; //  int instead of unsigned
    clear_screen();
    header();
    if( (*number_Ps)<1 ){
        printf(" \n\n\t\t faites d'abord creer un polynome au minimum ! \n\n\n\t ............ Appuyez sur un botton pour continuer .............");
        getch();
        return;
    }
    Show_Polynoms( *tab_Ps, *number_Ps);
    do{
        printf("\n\t\t      [ additionner deux polynomes] Choisissez le premier polynome Pi(x) : " );
        scanf(" %d", &pol1);
    }while(pol1<1 || pol1> (*number_Ps));
    do{
        printf("\n\t\t      [ additionner deux polynomes] Choisissez le deuxieme polynome Pi(x) : " );
        scanf(" %d", &pol2);
    }while(pol2<1 || pol2> (*number_Ps));
    new_poly->degree= max_degree( ( (*tab_Ps)[pol1-1])->degree, ((*tab_Ps)[pol2-1])->degree );
    new_poly->num_coefficients = 0;
    new_poly->coefficients = setter;
    pointer1 = (*tab_Ps)[pol1-1];
    pointer2 = (*tab_Ps)[pol2-1];
    ax1 = pointer1->coefficients ;
    ax2 = pointer2->coefficients;
    while(ax1!= NULL || ax2!=NULL){
        if( ax1!=NULL )
            exposant1 = ax1->exposant;
        else
            exposant1 = -1;
        if( ax2!=NULL )
            exposant2 = ax2->exposant;
        else
            exposant2 = -1;
        if( exposant1 > exposant2 ){
            setter->exposant = exposant1;
            setter->scalaire = ax1->scalaire;
            ax1 = ax1->next;
        }else
        {
            if( exposant1 == exposant2 ){
                setter->exposant = exposant1;
                setter->scalaire = ax1->scalaire + ax2->scalaire;
                ax1 = ax1->next;
                ax2 = ax2->next;

            }else{ // ax1->exposant < ax2->exposant
                setter->exposant = exposant2;
                setter->scalaire = ax2->scalaire;
                ax2 = ax2->next;
            }
        }
        if( ax1 != NULL || ax2!= NULL ){
            setter->next = (struct ax *) calloc( 1, sizeof(struct ax));
            setter = setter->next;
            (new_poly->num_coefficients) ++;
        }
    }
    ( *number_Ps )++ ;
    (*tab_Ps) = (Polynome **) realloc( (*tab_Ps), (*number_Ps)*sizeof(Polynome*));
    (*tab_Ps)[ (*number_Ps)-1 ] = new_poly;
    printf(" \n\n\n\t\t la somme des deux polynomes est stockee dans le %d-eme polynome. \n\n\t P%d(x) + P%d(x) = P%d(x) \n\n\t ", *number_Ps, pol1, pol2, *number_Ps );
    print_Poly( new_poly, *number_Ps);
    printf("\n\n\t........ Appuyez sur un botton pour continuer ........ \n\n");
    getch();
}




void rem_polynome( Polynome *** tab_Ps, short unsigned * number_Ps ){
    int i;
    int deleted; // index of the deleted polynom
    Polynome ** del_ploy = NULL;
    Polynome * p=NULL;
    char choice;
    clear_screen();
    header();
    if( !(*number_Ps) ){
        printf(" \n\n\t\t Ajouter d'abord un polynome, il n'y a aucun enregistre ! \n\n\n\t ............ Appuyez sur un botton pour continuer .............");
        getch();
        return;
    }
    Show_Polynoms( *tab_Ps, *number_Ps);
    do{
        printf("\n\t\t\t [ Supprimer un polynome] Choisissez le polynome a supprimer par son indice 'i' de Pi(x): " );
        scanf(" %d", &deleted);
    }while(deleted<1 || deleted> (*number_Ps));
    do{
            printf("\n\n\t etes-vous sure de supprimer Polynome P%d ? (o/n) :  ", deleted);
            choice = getch();
        }while( choice!=111 && choice!= 110 && choice!= 79 && choice!=78 );
    if( choice==78 || choice ==110 )
        return;
    p = (*tab_Ps)[deleted-1];
    del_ploy = &( p );
        for( i=deleted-1; i< (*number_Ps)-1; i++ ){
            (*tab_Ps)[i] =  (*tab_Ps)[i+1] ;
        }
        free( &((*tab_Ps)[i]) );
    free_polynom( del_ploy );
    (*number_Ps)--;
    printf(" \n\n\n\t\t\t Polynome P%i a ete supprime, appuyez sur un botton pour continuer ............. \n\n\t ");
    getch();
}


void edit_polynome( Polynome *** tab_Ps, short unsigned number_Ps ){
    clear_screen();
    header();
    unsigned int edited; // index of the edited polynom
    Polynome * pol_handler = NULL;
    Polynome * replacant = (Polynome *) calloc( 1, sizeof(Polynome));
    if( !number_Ps ){
        printf(" \n\n\t\t Ajouter d'abord un polynome, il n'y a aucun enregistre ! \n\n\n\t ............ Appuyez sur un botton pour continuer .............");
        getch();
        return;
    }
    Show_Polynoms( *tab_Ps, number_Ps);
    do{
        printf("\n\t\t\t [ Modifier un polynome] Choisissez le polynome a modifier par son indice 'i' de Pi(x): " );
        scanf(" %d", &edited);
    }while(edited<1 || edited> number_Ps);

    saisir_coefficient_newPol( &replacant );
    pol_handler = (*tab_Ps)[edited-1];
    (*tab_Ps)[edited-1] = replacant;
    printf(" \n\n\n\t\t\t Polynome P%i a ete modifie, appuyez sur un botton pour continuer \n\n\t ", edited);
    free_polynom( &( pol_handler ));
    getch();
}



static void insert_node(Polynome ** poly){
    struct ax * new_node= ( struct ax*) calloc( 1, sizeof(ax)) ;
    struct ax * traveler= (*poly)->coefficients;
    new_node->exposant = 0;
    new_node->scalaire = 0;
    do{
        printf("\n\n\t saisissez l'exposant(entier) du cofficient x^ : ");
        scanf(" %d", &(new_node->exposant) );
    }while (( new_node->exposant )<0 || ( new_node->exposant) > MAX_DEGREE);
    printf( "\n\n\t saisissez le scalaire du cofficient(reel) x^%d : ", new_node->exposant);
    scanf(" %lf", &( new_node->scalaire ));
    new_node->next=NULL;
    if( new_node->exposant > (*poly)->degree ){
        traveler = (*poly)->coefficients;
        (*poly)->coefficients = new_node;
        (*poly)->num_coefficients ++;
        new_node->next = traveler;
        (*poly)->degree = new_node->exposant;
        traveler = NULL;
    }else if(new_node->exposant == (*poly)->degree){
        (*poly)->coefficients->scalaire = new_node->scalaire;
        free(new_node);
    }
        else{
           while( (traveler->next!=NULL) && ((traveler->next->exposant) > (new_node->exposant)) ){
                traveler = traveler->next;
           }
           if(traveler!=NULL){
                if( traveler->exposant == new_node->exposant ){
                    traveler->next->scalaire = new_node->scalaire;
                    free(new_node);
                }
                else{
                    new_node->next = traveler->next;
                    traveler->next = new_node;
                    (*poly)->num_coefficients ++ ;
                }
           }
        }
}



static void saisir_coefficient_newPol(Polynome ** poly){ //
    short confirm_add = 0 ;
    char choice;
    (*poly)->num_coefficients = 1;
    (*poly)->coefficients = (ax*) calloc( 1, sizeof(ax));
    (*poly)->coefficients->next = NULL;
    (*poly)->coefficients->scalaire =0;
    (*poly)->coefficients->exposant =0;
    (*poly)->degree = 0;
    do{
        printf("\n\n\t saisissez l'exposant(entier) du premier cofficient x^ : ");
        scanf(" %d", &((*poly)->coefficients->exposant) );
        (*poly)->degree =(*poly)->coefficients->exposant ; // initiate polynom degree
    }while (((*poly)->coefficients->exposant)<0 || ((*poly)->coefficients->exposant)> MAX_DEGREE);
    printf( "\n\n\t saisissez le scalaire du cofficient(reel) x^%d : ", (*poly)->coefficients->exposant);
    scanf(" %lf", &( (*poly)->coefficients->scalaire ));
    do{
        do{
            printf("\n\n\t Voulez vous insérer un autre coefficient ? (o/n) :  ");
            choice = getch();
        }while( choice!=111 && choice!= 110 && choice!= 79 && choice!=78 );

        if( choice ==111 || choice == 79 ){
            insert_node( poly );
        }
    }while(choice!=110 && choice!=78);
}



void new_polynome( Polynome *** tab_Ps, short unsigned * number_Ps ){
    clear_screen();
    header();
    short tmp;
    printf("\n\t\t\t [ Ajouter un polynome] \n\n\n\t\t L'ajout du polynome P%d(x) \n\n", (*number_Ps)+1 );
    (*number_Ps)++;
    if( (*tab_Ps) == NULL )
        (*tab_Ps) = (Polynome**) calloc( (*number_Ps), sizeof(Polynome*) ); // alouer l'espace pour un tableau des pointeurs sur polynomes
    else
        (*tab_Ps) = (Polynome**) realloc( (*tab_Ps), (*number_Ps)*sizeof(Polynome*) ); // alouer l'espace pour un tableau des pointeurs sur polynomes
    (*tab_Ps)[(*number_Ps)-1 ]  = (Polynome *) calloc( 1, sizeof(Polynome) ); // alouer l'espace pour un polynome
    saisir_coefficient_newPol( &((*tab_Ps)[ (*number_Ps)-1 ]) ); //saisir les coefficients
}





void Show_Polynoms(  Polynome ** tab_Ps, const int number_Ps ){
    if( !number_Ps )
         printf("\n\n \t\t Aucun polynome n'a ete enregistre ! \n");
    else{
         printf("\n\n\t Les Polynomes Enregistres : \n");
         for( int i=0; i<number_Ps; i++){
            printf("\n\n\t\t");
            print_Poly( tab_Ps[i], i+1 );
         }
            printf("\n");
    }
}

void print_Poly( Polynome *P, int indice ){
    short unsigned first = 1;
    ax * index = P->coefficients;
    printf("P%d(x) = ", indice);
    if( index == NULL )
        printf(" 0 ");
    else
    while(1){
            if( first ){
                if( index->scalaire>=0 )
                    printf(" %.2f ", index->scalaire);
                else
                    printf(" - %.2f ", -index->scalaire);
                if(index->exposant)
                    printf("* x^%d  ", index->exposant);
                first = 0;
            }else{
                if( index->scalaire>=0 )
                    printf("+  %.2f ", index->scalaire);
                else
                    printf("-  %.2f ", -index->scalaire);
                if(index->exposant)
                    printf("* x^%d  ", index->exposant);
            }
        if(index->next == NULL)
                    break;
        index = index->next;
    }
}

void clear_screen(){
    if(WINDOWS)
        system("cls");
    else
        system("clear");
}

void free_all( Polynome ***P, int nbr_pols){
for(int i =0; i<nbr_pols; i++)
 free_polynom( &( (*P)[i]) );
free( *P);
}

void free_polynom( Polynome ** P ){
    short unsigned i  = (*P)->num_coefficients;
    struct ax ** freeer=NULL;
    struct ax ** next_toBe_freed=NULL;
    freeer  = & ((*P)->coefficients);
    if( ((*freeer)->next) ){
        next_toBe_freed  =  &( (*freeer)->next) ;
    }
    while( i ){
        free( *freeer );
        if( next_toBe_freed && (*next_toBe_freed)->next != NULL ){
            freeer = next_toBe_freed;
            next_toBe_freed = & ( (*next_toBe_freed)->next );
        }
        i--;
    }
    free(*P);
}

void header(){
printf("\n\n\t ########################## Polynomes TP2 - MAGHDAOUI Ayoub - BDCC ##########################\n\n");
}
