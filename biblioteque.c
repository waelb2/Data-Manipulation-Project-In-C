#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <math.h>
#include "biblioteque.h"




//***************************** La machine abstaite traditionelle **************************
void Ouvrire(FILE **fich , char nom_fich[maximum] , char mode) {
    if (mode == 'A') {
        *fich = fopen(nom_fich , "rb+") ;
        fread(&entete , sizeof(ENTETEF) , 1 , *fich) ;
    }
    else if (mode == 'N') {
        entete.AnneeCourante = 0 ;
        entete.DernierPos = 0 ;
        entete.NbBloc = 0 ;
        entete.NbInsertion = 0 ;
        *fich = fopen(nom_fich , "ab+") ;
        fwrite(&entete , sizeof(ENTETEF) , 1 , *fich) ;
    }
    else {
        printf("Erreur : le mode est incorrect\n\n") ;
        *fich = NULL ;
    }
}
//*******************************************************************************
void Fermer(FILE *fich) {
    fclose(fich) ;
}
//*******************************************************************************
void LireDir(FILE *fich , int i , Tbloc *buffer) {
    fseek(fich , sizeof(ENTETEF) , SEEK_SET) ;
    fseek(fich , sizeof(Tbloc)*(i-1) , SEEK_CUR) ;
    fread(&*buffer , sizeof(Tbloc) , 1 , fich) ;
}
//*******************************************************************************
void EcrireDir(FILE *fich , int i , Tbloc buffer) {
    fseek(fich , sizeof(ENTETEF) , SEEK_SET) ;
    fseek(fich , sizeof(Tbloc)*(i-1) , SEEK_CUR) ;
    fwrite(&buffer , sizeof(Tbloc) , 1 , fich) ;
}

//*******************************************************************************
int Entete(FILE *fich , int i) {
    if (fich == NULL) {
        printf("Il faut ouvrir le fichier\n\n") ;
        return -1 ;
    }
    else {
        rewind(fich) ;
        fread(&entete , sizeof(ENTETEF) , 1 , fich) ;
        if (i == 1) return entete.NbBloc ;
        else if (i == 2) return entete.DernierPos ;
        else if (i == 3) return entete.AnneeCourante ;
        else if (i == 4) return entete.NbInsertion ;
        else {
            printf("le caracteristique n\'exist pas!\n\n") ;
            return -1 ;
            exit(0) ;
        }
    }
}
//*******************************************************************************
void Aff_Entete(FILE *fich , int i , int val) {
    rewind(fich) ;
    if (i == 1) {
        entete.NbBloc = val ;
    }
    else if (i == 2) {
        entete.DernierPos = val ;
    }
    else if (i == 3) {
        entete.AnneeCourante = val ;
    }
    else if (i == 4) {
        entete.NbInsertion = val ;
    }
    else {
        printf("le caracteristique n\'exist pas!\n\n") ;
        exit(0) ;
    }
    fwrite(&entete , sizeof(ENTETEF) , 1 , fich) ;
}
//******************************************************************************************
int nombreChiffres ( int nombre ) {
    int i = 1;
    if (nombre < 0)
    {
        nombre = -nombre;
    }
    while (nombre >= 10)
    {
        nombre /= 10;
        i++;
    }
    return i;
}
//*******************************************************************************
int EcrireEnrgDansChaine( Eleve e , char chaine[b]) {
    char ch1[b] , ch2[b] ;
    int taille ; // taille de la chaine
    int nb ;
    int annee ;
    int j ;
    strcpy(chaine , "") ;
    strcpy(ch1 , "") ;
    strcpy(ch2 , "") ;

    strcat(ch1 , e.numidentite) ;
    strcat(ch1 , "#") ;
    strcat(ch1, e.classeidentite.annee);
    strcat(ch1 , "#") ;
    strcat(ch1, e.classeidentite.numero);
    strcat(ch1 , "#") ;
    strcat(ch1 , e.nom) ;
    strcat(ch1 , "#") ;
    strcat(ch1 , e.prenom) ;
    strcat(ch1 , "#") ;
    strcat(ch1 , e.genre) ;
    strcat(ch1 , "#") ;
    annee = atoi(e.classeidentite.annee) ;
    if ( e.classeidentite.annee[0] == 'P' || annee<=2 ) j = 4 ;
    else j = 8 ;
    for (int i=0 ; i<j ; i++) {
        strcat(ch1 , e.Tab_notes[i].matiere) ;
        strcat(ch1 , "~") ; // pour séparer les matières avec leurs notes
        strcat(ch1 , e.Tab_notes[i].note) ;
        strcat(ch1 , "|") ; // pour séparer chaque matière et leur note avec les autres matières
    }
    taille = strlen(ch1) ;
    nb = nombreChiffres(taille) ;
    strcpy(chaine , "0") ; // caractère d'effacement (il est à '0' donc l'enregistrement n'est pas effacé)
    if ( nb < maximumTaille ) {
        for ( int i=1 ; i<=(maximumTaille - nb) ; i++ ) {
            strcat(chaine , "0") ;
        }
    }
    itoa(taille , ch2 , 10) ; // convertir taille à une chaine dans ch2 pour concaténer la taille
    strcat(chaine , ch2) ;
    strcat(chaine , ch1) ;
    return taille ;
}
//*******************************************************************************

///************************************ Question 1 ******************************************
int tock(char chainesrc[10000] , char chainedest[1000] , char delemeteur , int position) {
// Equivalente à strtock, elle retourne la derniere position du dernier champ extrait
// de la chaine1
    int k = position ;
    int cpt = 0 ;
    strcpy(chainedest , " ") ;
    while ( chainesrc[k] != delemeteur ) {
        if (chainesrc[k] == '\0') return -1 ;
        chainedest[cpt] = chainesrc[k] ;
        k++ ;
        cpt ++ ;
    }
    chainedest[cpt] = '\0' ;
    return(k+1) ;
}
//Fonction qui génère un nombre de Binf à Bsup
int AleaNb(int Binf,int Bsup){
     srand ( time(NULL)*rand() ); // Initialisation de la fonction random().
        return Binf+(rand()%(Bsup-Binf+1));
}
/// a) Fonction qui génère aléatoirement le numéro d’identification de l’élève.
void AleaIdEleve(Eleve *eleve) {
    int IDEleve=0,nb_chiff,alea_nb;
    char ID_Nb[5];
    IDEleve=toupper(eleve->nom[0])*100+toupper(eleve->prenom[strlen(eleve->prenom)-1]); //On prend la mjuscule du premier et du dernier char
    alea_nb= AleaNb(1,99);  //Creation du premier nomber aliatoire.
    IDEleve=IDEleve*alea_nb;
    alea_nb=AleaNb(100,500); //Creation du deuxieme nomber aliatoire.
    IDEleve=IDEleve+alea_nb;
    nb_chiff=log10(IDEleve)+1;
    IDEleve=IDEleve/pow(10,nb_chiff-4); //Le resultat final du ID.
    itoa(IDEleve,ID_Nb,10);
    strcpy(eleve->numidentite,ID_Nb);
}

/// b) Fonction qui génère aléatoirement l’identifiant de la classe.
void AleaIdclasse(Eleve *eleve) {
    char salle_nb[3],annee[2];
    int sNb,aNb;
    sNb=AleaNb(1,3);
    aNb=AleaNb(1,6);
    itoa(sNb,salle_nb,10);
    itoa(aNb,annee,10);
    strcpy(eleve->classeidentite.numero,salle_nb);
    if(aNb==6){
        strcpy((eleve->classeidentite).annee,"P");
    }else{
        strcpy((eleve->classeidentite).annee,annee);
    }

}
//Une fonction qui récupère le champ correspendant à nom,prenom et genre
//dans un fichier .txt à partir d'un nombre aléatoire. **/
void GetNomPreGen(FILE *fich ,char chaine[maximum+3],int pos){

    int len=0; //pour tester si on est arrivé à la position choisi aléatoirement.
    char Nom_Prenom_G[maximum+3];
     for(int i=0;i<pos;i++){ // On parcours les noms/prénoms_genres jusqu'à arriver à la position pos

        rewind(fich);           //A chaque fois on se positionne au début du fichier

        fseek(fichier,len+i,SEEK_SET); //On saute à chaque fois  les noms/prénoms_genres déja lus avec fscanf où le pas est len+i len la taille de la chanie précédente le i pour sauter les ";"

        fscanf(fichier,"%[^;]",&Nom_Prenom_G);
        len=len+strlen(Nom_Prenom_G);
        }

        strcpy(chaine,Nom_Prenom_G);
}
/**c) fonction qui genere aleatoirement le nom,prenom et genre d'un etudiant
a partir de deux fichiers text **/
void Alea2Fich(Eleve *eleve)
{
    char prenom_genre[maximum+3] , chaineP[maximum+3] , chaineN[maximum+3] ;
    int AL_PRENOM=AleaNb(1,614),AL_NOM=AleaNb(1,690),j=0; //Notre fichier contient 614 prenoms et 690 noms.
    fichier=fopen("prenoms.txt","r");
    GetNomPreGen(fichier,prenom_genre,AL_PRENOM); //récupèreration du champ : prénom,genre
    if (prenom_genre[0] == '\n') {
        int i = 1 ;
        while (prenom_genre[i] != '\0') {
            chaineP[i-1] = prenom_genre[i] ;
            i++ ;
        }
        chaineP[i] = '\0' ;
    } else strcpy(chaineP , prenom_genre) ;
    strcat(chaineP , ",") ;
    j = tock(chaineP , eleve->prenom , ',' , j) ;//Affectaion du prénom à l'élève.
    j = tock(chaineP , eleve->genre , ',' , j);// Affectaion du genre à l'élève.
    fclose(fichier);
    fichier=fopen("noms.txt","r");
    GetNomPreGen(fichier,chaineN,AL_NOM); //Affectaion du nom à l'élève.
    if (chaineN[0] == '\n') {
        int i = 1 ;
        char ch[maximum+3] ;
        while(chaineN[i] != '\0') {
            ch[i-1] = chaineN[i] ;
            i++ ;
        }
        ch[i] = '\0' ;
        strcpy(eleve->nom , ch) ;
    }
    else strcpy(eleve->nom , chaineN) ;
    fclose(fichier);
}
/** d)Fonction qui extrait les matières de chaque annéee apartir d'un fichier text
Les matières sont ordonnées de sorte que :
 les 3 premières lignes : année Priparative ; les 5 premières ligne 1,2 année
et toute les lignes : 3,4,5 année. **/
void MatNoteFich(Eleve *eleve) {
    char ligne[maximum]; //chaque ligne correspond à une matière.
    int annee , j ;
    char note[3] , chaine[100] ;
    annee = atoi(eleve->classeidentite.annee) ;
    fichier=fopen("matieres.txt","r") ;
    if ( eleve->classeidentite.annee[0] == 'P' || annee<=2 ) j = 4 ;
    else j = 8 ;
    // si il est en préparatoire ou 1er ou 2eme année il a 4 matieres
    // si il est en 3eme ou 4eme ou 5eme année il a 8 matieres
    for (int j2=0 ; j2<j ; j2++) {
        fgets(ligne,maximum,fichier);
        tock(ligne , chaine , ',' , 0) ;
        strcpy(eleve->Tab_notes[j2].matiere,chaine);
        eleve->Tab_notes[j2].matiere[strlen(chaine)] = '\0' ;
        itoa(AleaNb(0,20),note,10);
        note[2] = '\0' ;
        if ( strlen(note) == 2 ) strcpy(eleve->Tab_notes[j2].note , note) ;
        else {
            eleve->Tab_notes[j2].note[0] = '0' ;
            eleve->Tab_notes[j2].note[1] = note[0] ;
        }
        eleve->Tab_notes[j2].note[2] = '\0' ;
    }
    fclose(fichier);
}
//******************************************************************************************
void RechDecIndexID(BufIndexId index , int cle , int *j , int *trouve , int nbinsertion) {
    int inf , sup , m=0 , j2 ;
    inf = 0 ;
    sup = nbinsertion-1 ;
    *trouve = 0 ;
    //printf("Sup = %d\n" , sup) ;
    while ((inf <= sup) && (!*trouve)) {
        m = (inf + sup)/2 ;
        //printf("m = %d\n" , m) ;
        if (index.table[m].Id == cle) {
            *trouve = 1 ;
            j2 = m ;
        }
        else if (index.table[m].Id > cle) {
            sup = m-1 ;
        }

        else if (index.table[m].Id < cle) {
            inf = m+1 ;
        }
        //printf("Sup = %d  , inf = %d\n" , sup , inf) ;
        if (!*trouve || inf>sup) {
            j2 = inf ;
    //printf("j2 = %d\n" , j2) ;
        }
    }
    *j = j2 ;
    //printf("A la fin j = %d\n" , *j) ;
}
//-----------------------------------------------------------------------------------------------------
void RechDecIndexClasse(BufIndexClasse index , char classe[3] , int *j , int *trouve) {
    int inf , sup , m ;
    inf = 0 ;
    sup = NbClasseTotal-1;
    *trouve = 0 ;
    if ( strcmp(classe , "P3") > 0 || (strcmp(classe , "53") > 0 && strcmp(classe , "P1") < 0) ) {
        printf("La classe ne peut etre pas etre existe\n") ;
        *trouve = 0 ;
    }
    else {
        if ( strcmp(classe , "P1") == 0 || strcmp(classe , "P2") == 0 || strcmp(classe , "P3") == 0 ) {
            *trouve = 1 ;
            *j = classe[1] - 49 ;
        }
        else {
            while ((inf <= sup) && (!*trouve)) {
                m = (inf + sup)/2 ;
                if ( strcmp(index.table[m].Idclasse , classe) == 0 ) {
                    *trouve = 1 ;
                    *j = m ;
                }
                else if ( strcmp(index.table[m].Idclasse , classe) > 0 ) {
                    sup = m-1 ;
                }

                else if ( strcmp(index.table[m].Idclasse , classe) < 0 ) {
                    inf = m+1 ;
                }
                if (!trouve || inf>sup) {
                    *j = inf ;
                }
            }
        }
    }
}
//------------------------------------------------------------------------------------------------------
void insertTabIndex(BufIndexId *bufId , int id , int bloc , int pos , int Nbinsertion) {
    int trouve , j , i ;
    RechDecIndexID(*bufId , id , &j , &trouve , Nbinsertion) ;
    if (!trouve && j<NbEtudiantMax-1) {
        i = Nbinsertion ;
        while(i>j) {
            (*bufId).table[i].Id = (*bufId).table[i-1].Id ;
            (*bufId).table[i].Adr.NumBloc = (*bufId).table[i-1].Adr.NumBloc ;
            (*bufId).table[i].Adr.Pos = (*bufId).table[i-1].Adr.Pos ;
            i-- ;
        }
        (*bufId).table[j].Id = id ;
        (*bufId).table[j].Adr.NumBloc = bloc ;
        (*bufId).table[j].Adr.Pos = pos ;
    }
}
//------------------------------------------------------------------------------------------
void triABulle(BufIndexId *bufId , int n) {
     IndexIdEleve temp ;
     int aucun_echange ;
     for(int i = n-1 ; i>=0 ; i--) {
        aucun_echange = 1 ;
        for(int j = 0 ; j<=i ; j++) {
            if( (*bufId).table[j].Id > (*bufId).table[j+1].Id ) {
                temp.Id = (*bufId).table[j+1].Id ;
                temp.Adr.NumBloc = (*bufId).table[j+1].Adr.NumBloc ;
                temp.Adr.Pos = (*bufId).table[j+1].Adr.Pos ;

                (*bufId).table[j+1].Id = (*bufId).table[j].Id ;
                (*bufId).table[j+1].Adr.NumBloc = (*bufId).table[j].Adr.NumBloc ;
                (*bufId).table[j+1].Adr.Pos = (*bufId).table[j].Adr.Pos ;

                (*bufId).table[j].Id = temp.Id ;
                (*bufId).table[j].Adr.NumBloc = temp.Adr.NumBloc ;
                (*bufId).table[j].Adr.Pos = temp.Adr.Pos ;

                aucun_echange = 0 ;
            }
        }
       if (aucun_echange == 1) break ;
    }
}
///************************************ Question 2 ******************************************
int getTailleEleve(FILE *fich , Tbloc buffer , int indice , int bl) {
    char tailleChaine[4] ;
    int i = indice+1 ;
    for (int k = 0 ; k<3 ; k++) {
        if (i >= b) {
            bl++ ;
            LireDir(fich , bl , &buffer) ;
            i = i-b ;
        }
        tailleChaine[k] = buffer.tab[i] ;
        i++ ;
    } // end for k
    return atoi(tailleChaine) ;
}
//------------------------------------------------------------------------------------------int getTailleEleve(Tbloc buffer , int indice) {
int getIdEleve(FILE *fich , Tbloc buffer , int indice , int bl) {
    char Id[5] ;
    int i = indice+4 ;
    for (int k=0 ; k<=3 ; k++) {
        if (i >= b) {
            bl++ ;
            LireDir(fich , bl , &buffer) ;
            i = i-b ;
        }
        Id[k] = buffer.tab[i] ;
        i++ ;
    }
    return atoi(Id) ;
}
//------------------------------------------------------------------------------------------
void getClasse(FILE *fich , Tbloc buffer , int indice , int bl , char classe[3]) {
    int k ;
    int i = indice+9 ;
    for (k=0 ; k<=1 ; k++) {
        if (i >= b) {
            bl++ ;
            LireDir(fich , bl , &buffer) ;
            i = i-b ;
        }
        classe[k] = buffer.tab[i] ;
        i+=2 ;
    }
    classe[2] = '\0' ;
}
//------------------------------------------------------------------------------------------
int getNom(FILE *fich , Tbloc *buffer , int indice , int bl , char nom[maximum]) {
    int k = 0 ;
    int i = indice+13 ;
    do {
        if (i >= b) {
            bl++ ;
            LireDir(fich , bl , buffer) ;
            i = i-b ;
        }
        nom[k] = buffer->tab[i] ;
        k++ ;
        i++ ;
    }while( buffer->tab[i] != '#' ) ;
    nom[k] = '\0' ;
    return (i+1) ;
}
//------------------------------------------------------------------------------------------
int getPrenom(FILE *fich , Tbloc *buffer , int dernierpos , int bl , char prenom[maximum]) {
    int k = 0 ;
    int i = dernierpos ;
    do {
        if (i >= b) {
            bl++ ;
            LireDir(fich , bl , buffer) ;
            i = i-b ;
        }
        prenom[k] = buffer->tab[i] ;
        k++ ;
        i++ ;
    }while( buffer->tab[i] != '#' ) ;
    prenom[k] = '\0' ;
    return (i+1) ;
}
//------------------------------------------------------------------------------------------
void TriTableauString(TabString *tableau , int n) {
 // Ex : tableau.tab[0].str == P,2,Grine,Mohammed,M,
    int aucun_echange ;
    int  p1 , p2 ; // p1 et p2 pour la preorité du chaine j et chaine j+1
    int k , cpt ;
    for(int i = n-1 ; i>=0 ; i--) {
        aucun_echange = 1 ;
        char Strtmp[100] ;
        for(int j = 0 ; j<i ; j++) {
            p1 = 0 ;
            p2 = 0 ;
            char chaineClasse1[3] , chaineClasse2[3] ;
            char chaineNom1[maximum] , chaineNom2[maximum] ;
            char chainePrenom1[maximum] , chainePrenom2[maximum] ;
            chaineClasse1[0] = (*tableau).tab[j].str[0] ;
            chaineClasse1[1] = (*tableau).tab[j].str[2] ;
            chaineClasse1[2] = '\0' ;
            k = 4 ;
            cpt = 0 ;
            while ( (*tableau).tab[j].str[k] != ',' ) {
                chaineNom1[cpt] = (*tableau).tab[j].str[k] ;
                k++ ;
                cpt ++ ;
            }
            chaineNom1[cpt] = '\0' ;
            k++ ;
            cpt = 0 ;
            while ( (*tableau).tab[j].str[k] != ',' ) {
                chainePrenom1[cpt] = (*tableau).tab[j].str[k] ;
                k++ ;
                cpt ++ ;
            }
            chainePrenom1[cpt] = '\0' ;
            //**-*
            chaineClasse2[0] = (*tableau).tab[j+1].str[0] ;
            chaineClasse2[1] = (*tableau).tab[j+1].str[2] ;
            chaineClasse2[2] = '\0' ;
            k = 4 ;
            cpt = 0 ;
            while ((*tableau).tab[j+1].str[k] != ',') {
                chaineNom2[cpt] = (*tableau).tab[j+1].str[k] ;
                k++ ;
                cpt ++ ;
            }
            chaineNom2[cpt] = '\0' ;
            k++ ; ;
            cpt = 0 ;
            while ((*tableau).tab[j+1].str[k] != ',') {
                chainePrenom2[cpt] = (*tableau).tab[j+1].str[k] ;
                k++ ;
                cpt ++ ;
            }
            chainePrenom2[cpt] = '\0' ;
            if (chaineClasse1[0] == 'P') chaineClasse1[0] = '0' ;
            if (chaineClasse2[0] == 'P') chaineClasse2[0] = '0' ;
            if ( strcmp(chaineClasse1 , chaineClasse2) > 0 ) p1 ++ ;
            else if ( strcmp(chaineClasse1 , chaineClasse2) < 0 ) p2 ++ ;
            else {
                // si les classes sont egaux
                if ( strcmp(chaineNom1 , chaineNom2) > 0 ) p1++ ;
                else if ( strcmp(chaineNom1 , chaineNom2) < 0 ) p2++ ;
                else { // si les noms sont egaux
                    if ( strcmp(chainePrenom1 , chainePrenom2) > 0 ) p2++ ;
                    else if ( strcmp(chainePrenom1 , chainePrenom2) < 0 ) p1++ ;
                } // si les noms sont egaux
            } // Fin si les classes sont egaux
            if( p1 > p2 ) {
                strcpy(Strtmp , (*tableau).tab[j+1].str) ;
                strcpy((*tableau).tab[j+1].str , (*tableau).tab[j].str) ;
                strcpy((*tableau).tab[j].str , Strtmp) ;
                aucun_echange = 0 ;
            }
        }
        if (aucun_echange == 1) break ;
    }
}
//---------------------------------------------------------------------------------
int Existe(int ID[1000] , int n , int id) {
    int ex = 0 ;
    for (int k=0 ; k<n ; k++) {
        if ( ID[k] == id ) {
            ex = 1 ;
            break ;
        }
    }
    return ex ;
}
//*--//*-/*/-/*-*-*/-*-*/*-/-*/-*/-/*-/-*/-*/-*/-*/-*/-*/-*/-*/-*/-*/-*/-*/-*/
/** On va mettre les informations aleatoire et on trie les etudiants dans la
mémoire centrale, ensuite on met ses données ordonnées dans un fichier texte
contient dans chaque ligne les champs séparées par des ',' commme suit :
année,sale,nom,prenom,numeroIdentité,genre,
puis on remplis le fichier TOVC directement a partir de ce fichier texte
pour avoir un cout plus petit que le cout de décalage dans le fichier TOVC **/
//*--//*-/*/-/*-*-*/-*-*/*-/-*/-*/-/*-/-*/-*/-*/-*/-*/-*/-*/-*/-*/-*/-*/-*/-*/

void ChargementInitial(char nomfich[100] , int n , int AnneeCourante) {
    FILE *fich ;
    Ouvrire(&fich , nomfich , 'N') ;
    FILE *f1 ;
    f1 = fopen("etudiants.txt" , "a") ;
    int cmp , cpt = 0  ;
    char testerClasse[3] ;
    BufIndexId bufId ;
    BufIndexClasse bufClasse ;
    Eleve eleve ;
    int taille , k=0 , l , valDernierPos , valNbBloc ;
    valNbBloc = 0 ;
    valDernierPos = 0 ;
    TabString tableau ;
    int ID[n+1] ;
    for (int i=1 ; i<=n ; i++) { // récupère les données aleatoirement et les tries
                                // puis les mettre dans un fichiers texte
        if (i == 1) AleaIdEleve(&eleve) ; // id
        else {
            do {
               AleaIdEleve(&eleve) ;
            }while( Existe(ID , i , atoi(eleve.numidentite)) ) ;
        }
        ID[i-1] = atoi(eleve.numidentite) ;
        AleaIdclasse(&eleve) ; // classe
        Alea2Fich(&eleve) ; // nom et prenom et genre
        char chaineText[100] ;
        strcpy(chaineText , eleve.classeidentite.annee) ;
        strcat(chaineText , ",") ;
        strcat(chaineText , eleve.classeidentite.numero) ;
        strcat(chaineText , ",") ;
        strcat(chaineText , eleve.nom) ;
        strcat(chaineText , ",") ;
        strcat(chaineText , eleve.prenom) ;
        strcat(chaineText , ",") ;
        strcat(chaineText , eleve.numidentite) ;
        strcat(chaineText , ",") ;
        strcat(chaineText , eleve.genre) ;
        strcat(chaineText , ",") ;
        strcpy( tableau.tab[i-1].str , chaineText ) ;
    } // end for i
    // tri --------------------------------
    TriTableauString(&tableau , n) ;
    // Fin tri ----------------------------
    // remplir le fichier texte ---------
    for (int i=0 ; i<n ; i++) {
        fputs(tableau.tab[i].str , f1) ;
        fputs("\n" , f1) ;
    }
    fclose(f1) ;
    f1 = fopen("etudiants.txt" , "r") ;
    // remplisage le fichier TOVC ********************
    for (int i=1 ; i<=n ; i++) {
        l = 0 ;
        if (i == 1) valDernierPos = 0 ;
        else valDernierPos = k ;
        bufId.table[i-1].Adr.NumBloc = valNbBloc+1 ;
        char chDeListeEtudiant[b] ; // recuperer a partir du fichier
        char chaineDansBuffer[b] ; // ecrire dans buffer
        fgets(chDeListeEtudiant , 80 , f1) ;
        strcpy(eleve.classeidentite.annee , strtok(chDeListeEtudiant , ",")) ;
        strcpy(eleve.classeidentite.numero , strtok(NULL , ",")) ;
        strcpy(eleve.nom , strtok(NULL , ",")) ;
        strcpy(eleve.prenom , strtok(NULL , ",")) ;
        strcpy(eleve.numidentite , strtok(NULL , ",")) ;
        strcpy(eleve.genre , strtok(NULL , ",")) ;
        testerClasse[0] = eleve.classeidentite.annee[0] ;
        testerClasse[1] = eleve.classeidentite.numero[0] ;
        // ------------------ Remplir l'index du classes ----------------------
        if (i == 1) {
            strcpy(bufClasse.table[0].Idclasse , "P1") ;
            bufClasse.table[0].Adr.NumBloc = 1 ;
            bufClasse.table[0].Adr.Pos = 0 ;
            cpt ++ ;
        }
        else {
            cmp = strcmp(bufClasse.table[cpt-1].Idclasse , testerClasse) ;
            if (cmp != 0) { // si la classe est deja ecrite on ne la sauvegarde pas
            strcpy(bufClasse.table[cpt].Idclasse , testerClasse) ;
            bufClasse.table[cpt].Adr.NumBloc = valNbBloc+1 ;
            bufClasse.table[cpt].Adr.Pos = valDernierPos ;
            cpt ++ ;
            }
        }
        // ------------------ Fin remplir l'index du classes ------------------
        // ------------ remplisage des notes ------------------
        MatNoteFich(&eleve) ;
        taille = EcrireEnrgDansChaine(eleve , chaineDansBuffer) ;
        while (l<taille+4) { // remplire le buffer avec l'enregistrement numero k
            buffer.tab[k] = chaineDansBuffer[l] ;
            k++ ;
            l++ ;
            if (k == b) { // Si le bloc est remplie
                k = 0 ;
                valNbBloc++ ;
                EcrireDir(fich , valNbBloc , buffer) ;
            } // Fin Si le bloc est remplie
        } // end while
        // ************ Remplir l'index du identifiant ************************
        bufId.table[i-1].Adr.Pos = valDernierPos ;
        bufId.table[i-1].Id = atoi(eleve.numidentite) ;
        // ************  Fin remplir l'index du identifiant ********************
    } // end for i
    if (k > 0 && k < b) {
        Tbloc buf2 ;
        for (int j2=0 ; j2<k ; j2++) {
            buf2.tab[j2] = buffer.tab[j2] ;
        }
        fwrite(&buf2 , sizeof(Tbloc) , 1 , fich) ;
        valNbBloc ++ ;
    }
    Fermer(fich) ;
    Fermer(f1) ;
    Ouvrire(&fich , nomfich , 'A') ;
    Aff_Entete(fich , 1 , valNbBloc) ; // nombre de blocs total
    Aff_Entete(fich , 2 , k) ; // derniere position
    Aff_Entete(fich , 3 , AnneeCourante) ; // année courante
    Aff_Entete(fich , 4 , n) ; // nombre d'insertions
    FILE *fichierIndexID ;
    FILE *fichierIndexClasse ;
    fichierIndexID = fopen("fichierIndexID" , "ab");
    triABulle( &bufId , Entete(fich , 4)-1 ) ;
    fwrite(&bufId , sizeof(BufIndexId) , 1 , fichierIndexID) ;
    Fermer(fichierIndexID) ;
    fichierIndexClasse = fopen("fichierIndexClasse" , "ab");
    fwrite(&bufClasse , sizeof(bufClasse) , 1 , fichierIndexClasse) ;
    Fermer(fichierIndexClasse) ;
    Fermer(fich) ;
    remove("etudiants.txt") ;
}//fin fonction
//******************************************************************
void affichertest(char nomfich[100]) {
    FILE *fich ;
    int n ;
    Ouvrire(&fich , nomfich , 'A') ;
    if (fich == NULL) printf("\nErreue dans l\'ouverture\n\n") ;
    else { // begin big else
         n = Entete(fich , 1) ;
         for (int i=1 ; i<=n ; i++) {
            printf("Bloc numero : %d\n\n" , i) ;
            LireDir(fich , i , &buffer) ;
            printf("%s\n\n" , buffer.tab) ;
        }
        Fermer(fich) ;
    }
}
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------
void RechercheInitial(Eleve e , int *trouve , int *bloc , int *pos) {
    char ch[3] , classe[3] , nom[maximum] , prenom[maximum] ;
    int trouve2 ,  j  , indice , bl , stop = 0 , taille , ind , dernierbloc , dernierepos ;
    *trouve = 0 ;
    BufIndexId bufId ;
    fichier3 = fopen("fichierIndexID" , "rb") ;
    fread(&bufId , sizeof(BufIndexId) , 1 , fichier3) ;
    Ouvrire(&fichier , "FichierCourant" , 'A') ;
    RechDecIndexID(bufId , atoi(e.numidentite) , &j , &trouve2 , Entete(fichier , 4) ) ;
    if (trouve2) {
        *trouve = 1 ;
        *bloc = bufId.table[j].Adr.NumBloc ;
        *pos = bufId.table[j].Adr.Pos ;
    }
    else { // si l'etudiant n'existe pas
        *trouve = 0 ;
        BufIndexClasse bufcls ;
        fichier2 = fopen("fichierIndexClasse" , "rb") ;
        fread(&bufcls , sizeof(BufIndexClasse) , 1 , fichier2) ;
        strcpy(ch , e.classeidentite.annee) ;
        strcat(ch , e.classeidentite.numero) ;
        RechDecIndexClasse(bufcls , ch , &j , &trouve2) ;
        Fermer(fichier2) ;
        if (!trouve2) {
            printf("La classe de l\'etudiant est incorrect!\n\n") ;
            *trouve = -1 ; // cette valeur ne doit pas etre existé
            *bloc = -1 ;
            *pos = -1 ;
        }
        else { // si la classe est correcte
            indice = bufcls.table[j].Adr.Pos ;
            *bloc = bufcls.table[j].Adr.NumBloc ;
            bl = *bloc ;
            LireDir(fichier , bl , &buffer) ;
            dernierbloc = Entete(fichier , 1) ;
            dernierepos = Entete(fichier , 2) ;
            do {
                if (bl >= dernierbloc && indice >= dernierepos) {
                    *trouve = 0 ;
                    *bloc = Entete(fichier , 1) ;
                    *pos = Entete(fichier , 2) ;
                    stop = 1 ;
                    break ;
                }
                taille = getTailleEleve(fichier , buffer , indice , bl) ;
                getClasse(fichier , buffer , indice , bl , classe) ;
                ind = getNom(fichier , &buffer , indice , bl , nom) ;
                ind = getPrenom(fichier , &buffer , ind , bl , prenom) ;
                if ( strcmp(e.nom , nom) > 0 ) { // sauter a l'enregistrement suivant
                    indice+= taille+4 ;
                    if (indice >= b) {
                        bl ++ ;
                        LireDir(fichier , bl , &buffer) ;
                        indice -= b ;
                    }
                    *pos = indice ;
                    *bloc = bl ;
                }else if ( strcmp(e.nom , nom) < 0 ) { // il doit etre insere dans cette position
                    stop = 1 ;
                    *bloc = bl ;
                    *pos = indice ;
                }else { // si les noms sont identiques
                    if ( strcmp(e.prenom , prenom) < 0 ) {
                        stop = 1 ;
                        *bloc = bl ;
                        *pos = indice ;
                    }else if ( strcmp(e.prenom , prenom) >= 0 ) { // sauter a l'enregistrement suivant
                        indice+= taille+4 ;
                        if (indice >= b) {
                            bl ++ ;
                            LireDir(fichier , bl , &buffer) ;
                            indice -= b ;
                            *bloc = bl ;
                            *pos = indice ;
                        }
                    }
                }

            }while (!stop && strcmp(classe , ch) == 0 ) ; // end while trouve
        } // fin si la classe est correcte
    } // fin si l'etudiant n'existe pas
    Fermer(fichier) ;
}// end function
///--------------------------------------------------------------------------------------
char * strtoupper( char * dest , char * src ) {
    char * result = dest;
    while( (*dest++ = toupper( *src++ )) );
    return result;
}

void remplirEtudiantAleatoire(Eleve *e) {
        AleaIdEleve(e) ;
        AleaIdclasse(e) ;
        Alea2Fich(e) ;
        MatNoteFich(e) ;
}
///--------------------------------------------------------------------------------------

void InsertionInitial(Eleve e) {
    FILE *fich ;
    int j2 , trouve2 ;
    int trouve ,  j  , pos , bloc  , k , taille , bl , dernierBloc , dernierePosition , stop = 0 , n , test = 0 ;
    char ch[3] , chaine[b] ;
    BufIndexId bufid ;
    BufIndexClasse bufcls ;
        do {
            remplirEtudiantAleatoire(&e) ;
            RechercheInitial(e , &trouve , &bloc , &pos) ;
        }while(pos > b);
        if ( (bloc > 0 && bloc <300) && (pos > 0 && pos <b-1) ) {
            if (trouve){
                printf("\n\nL\'etudiant de l\'identifiant %s est deja existe\n\n" , e.numidentite) ;
            }
            else { // on doit inserer l'etudiant
                /// mis a jours de l'index de l'identifiant
                Ouvrire(&fich , "FichierCourant" , 'A') ;
                n = Entete(fich , 4) ;
                taille = EcrireEnrgDansChaine(e , chaine)+4 ; // pas de decalage = taille
                fichier3 = fopen("fichierIndexID" , "rb") ;
                fread(&bufid , sizeof(BufIndexId) , 1 , fichier3) ;
                insertTabIndex(&bufid , atoi(e.numidentite) , bloc , pos , n ) ;
                n++ ;
                RechDecIndexID(bufid , atoi(e.numidentite) , &j2 , &trouve2 , n) ;
                if (trouve2) {
                    for (int i=0 ; i<n ; i++) {
                        if (i != j2) {
                            if (bufid.table[i].Adr.NumBloc >= bufid.table[j2].Adr.NumBloc) {
                                if (bufid.table[i].Adr.Pos >= bufid.table[j2].Adr.Pos )
                                    bufid.table[i].Adr.Pos+=taille ;
                                if (bufid.table[i].Adr.Pos >= b) {
                                    bufid.table[i].Adr.Pos -= b ;
                                    bufid.table[i].Adr.NumBloc++ ;
                                }
                            }
                        }
                    }
                }else printf("La valeur n\'est pas insere !!\n\n") ;
                Fermer(fichier3) ;
                fichier3 = fopen("fichierIndexID" , "wb") ;
                fwrite(&bufid , sizeof(BufIndexId) , 1 , fichier3) ;
                Fermer(fichier3) ;
                /// Fin mis a jours de l'index de l'identifiant
                dernierBloc = Entete(fich , 1) ; // dernier bloc
                dernierePosition = Entete(fich , 2) ; // derniere position
                if ( (dernierePosition + taille) >= b) {
                    EcrireDir(fich , dernierBloc+1 , buffer2) ;
                    test = 1 ; // si on augmente le nombre de blocs ou non
                }
                bl = bloc ;
                LireDir(fich , bloc , &buffer) ;
                for (int k2 = 0 ; k2<pos ; k2++) { // copier le contenu du bloc dans buffer2
                        buffer2.tab[k2] = buffer.tab[k2] ;
                    } // Fin for k2 copier le contenu du bloc dans buffer 2
                k = pos ;
                for (int k2 = 0 ; k2<taille ; k2++) { // copier l'enregistrement dans buffer2
                    if (k == b) {
                        EcrireDir(fich , bl , buffer2) ;
                        bl++ ;
                        k = 0 ;
                    }
                    buffer2.tab[k] = chaine[k2] ;
                    k++ ;
                } // fin copier l'enregistrement dans buffer2
                if (bloc == dernierBloc && pos == dernierePosition) stop = 1 ;
                while (!stop)
                { // decaler jusqu'a la fin du fichier
                    if (k == b) {
                        EcrireDir(fich , bl , buffer2) ;
                        bl++ ;
                        k = 0 ;
                    }
                    if (pos == b) {
                        bloc++ ;
                        LireDir(fich , bloc , &buffer) ;
                        pos = 0 ;
                    }
                    buffer2.tab[k] = buffer.tab[pos] ;
                    k++ ;
                    pos++ ;
                    if (bloc == dernierBloc && pos == dernierePosition) stop = 1 ;
                } // fin while decaler jusqu'a la fin du fichier
                if (k > 0 && k<b) {
                    for (int j2=0 ; j2<k ; j2++) {
                        buffer3.tab[j2] = buffer2.tab[j2] ;
                    }
                    EcrireDir(fich , bl , buffer3) ;
                }
                /// mis a jours les entetes(1,2,4)
                if (test) Aff_Entete(fich , 1 , bl) ;
                Aff_Entete(fich , 2 , k) ;
                Aff_Entete(fich , 4 , n) ;
                Fermer(fich) ;
                printf("L\'identifiant : %s\n" , e.numidentite) ;
                printf("L\'annee de scolarisation : %s\n", e.classeidentite.annee) ;
                printf("Le numero de la salle : %s\n" , e.classeidentite.numero) ;
                printf("Le nom : %s\n" , e.nom) ;
                printf("Le prenom : %s\n" , e.prenom) ;
                printf("Le genre : %s\n" , e.genre) ;
                printf(" L\'insertion dans le fichier courant est terminee!\n vous pouvez consulter le resultat avec l\'affichage du fichier initial caractere par caractere(choix 9)!\n\n") ;
            } // fin else d'insertion
        }else{ printf("L\'etudiant de l\'identifiant %s est deja existe car l\'identifiant qui a etait remplis aleatoirement est deja existee!\n" , e.numidentite) ;
                printf("Essayez de refaire l\'ajout\n\n") ;
            }
}
//-------------------------------------------------------------------------------------------
void Mis_a_jour(char ficAnCour[maximum] ,char ficIndex[maximum],int annee,int id) {
    int choix,choix2,trouve=0,j,i,d,new_id,k=0,idSize,indiceInd;
    char nId_chaine[5];
    char genre[2],classe,note[3];
    int taille =0;
    FILE *fich2,*fich;
    BufIndexId buff;

    Ouvrire(&fich , ficAnCour , 'A') ;

    fich2 = fopen(ficIndex , "rb");
    fread(&buff , sizeof(BufIndexId) , 1 , fich2) ;

    RechDecIndexID(buff,id,&j,&trouve,Entete(fich,4));  //La recherche d'Id.
    if(!trouve)
    {
        printf("Cet identifiant n'existe pas ! Voulez refaire l'operation ? ");
    }
    else{

        indiceInd=j; // On doit sauvgarder l'indice correspondent à l'id car on va faire une autre recherche pour le nouveau id.
        LireDir(fich ,buff.table[indiceInd].Adr.NumBloc, &buffer); //On lit le bloc correspondent à l'Id dans buffer.
        printf("\n%c",buffer.tab[buff.table[j].Adr.Pos+4]);
        printf("\nQuelle mise à jour voulez vous faire : "); //Le choix d'une mise à jour.
        printf("\n1 : Id\n2 : Genre\n3 : Note\n\nVeuillez choisir un numero svp : ");
        scanf("%d",&choix);

        switch(choix)
        {
            case 1:
                                  // mise à jour de l'Id
                trouve=1;
                while(trouve){
                    printf("\nVeulliez entrer le nouveau identifiant svp : ");
                    scanf("%s",&nId_chaine); //pour prendre en consédiration les cas de 000x 0x... on doit lire l'id tantque une ch de char.

                    new_id=atoi(nId_chaine);  //atoi retourne '0' s'il y a des lettre dans la chaine.
                    idSize=log10(new_id)+1;

                    RechDecIndexID(buff,new_id,&j,&trouve,Entete(fich,4));  //La recherche du nouveau Id.
                    if(trouve)
                    {
                        printf("\nCet Identifiant deja existe ! ");
                    }
                    else{
                        trouve=0;
                    }
                }


                if(strlen(nId_chaine)!=4 && new_id!=0){
                    printf("\nL'identifiant doit etre un entier de 4 chiffre !");
                }
                else{
                    for(k=0;k<4;k++)
                    {

                                if (buff.table[indiceInd].Adr.Pos+4 >= b) {                      //Si on déppasse le bloc.
                                        LireDir(fich , buff.table[indiceInd].Adr.NumBloc+1 , &buffer) ;
                                        buff.table[indiceInd].Adr.Pos = buff.table[indiceInd].Adr.Pos -b;
                                    }

                        buffer.tab[buff.table[indiceInd].Adr.Pos+4]=nId_chaine[k];
                        buff.table[indiceInd].Adr.Pos++;
                    }

                    printf("\n%c",buffer.tab[buff.table[indiceInd].Adr.Pos]);
                    EcrireDir(fich,buff.table[indiceInd].Adr.NumBloc,buffer); //mise à jour du fichier.

                    Fermer(fich2) ;
                    fich2 = fopen(ficIndex , "wb");
                    fread(&buff , sizeof(BufIndexId) , 1 , fich2) ;

                    buff.table[indiceInd].Id=new_id;  //mise à jour de l'index.
                    fwrite(&buff , sizeof(BufIndexId) , 1 , fich2) ;
                    triABulle(&buff , Entete(fich , 4)-1);

                }

            break;

            case 2:
        LireDir(fich ,buff.table[indiceInd].Adr.NumBloc, &buffer);
        printf("\nEntrer le nouveau genre svp : ");
        scanf("%s",&genre);
        genre[1]='\0';

        taille=getTailleEleve(fich,buffer,buff.table[indiceInd].Adr.Pos,buff.table[indiceInd].Adr.NumBloc);
        classe=buffer.tab[buff.table[indiceInd].Adr.Pos+9];

        if (classe=='P' || classe<='2')
        {
            taille=taille+buff.table[indiceInd].Adr.Pos-40;
            if(taille<0)
            {
                LireDir(fich,buff.table[indiceInd].Adr.NumBloc-1,&buffer);
                taille=taille+b;
            }
            else if (taille>=b)
            {
                LireDir(fich,buff.table[indiceInd].Adr.NumBloc+1,&buffer);
                taille=taille-b;
            }
             buffer.tab[taille]=genre[0];
        }
        else{
            taille=taille+buff.table[indiceInd].Adr.Pos-93;
            if(taille<0)
            {
                LireDir(fich,buff.table[indiceInd].Adr.NumBloc-1,&buffer);
                taille=taille+b;
            }
             else if (taille>=b)
            {
                LireDir(fich,buff.table[indiceInd].Adr.NumBloc+1,&buffer);
                taille=taille-b;
            }
            buffer.tab[taille]=genre[0];

        }
        EcrireDir(fich,buff.table[indiceInd].Adr.NumBloc,buffer);

            break;

            case 3:
                LireDir(fich ,buff.table[indiceInd].Adr.NumBloc, &buffer);
                classe=buffer.tab[buff.table[indiceInd].Adr.Pos+9];

            if (classe=='P' || classe<='2')
            {
                printf("\n1 : Arab\n2 : MATHEMATIQUE\n3 : DESIN\n4 : SPORT\n\nVeuillez choisir un numero svp : ");
                scanf("%d",&choix2);
                printf("\nEntrer la nouvelle note : ");
                scanf("%s",note);
                switch(choix2){
                case 1:
                    k=1;
                    for(int i=1;i<=k;i++){
                    while(buffer.tab[buff.table[indiceInd].Adr.Pos]!='|'){
                        if (buff.table[indiceInd].Adr.Pos >= b) {
                            LireDir(fich2 , buff.table[indiceInd].Adr.NumBloc+1 , &buffer) ;
                            buff.table[indiceInd].Adr.Pos = 0;
                        }
                        buff.table[indiceInd].Adr.Pos++;
                    }
                }
                buffer.tab[buff.table[indiceInd].Adr.Pos-2]=note[0];
                buffer.tab[buff.table[indiceInd].Adr.Pos-1]=note[1];
                EcrireDir(fich,buff.table[indiceInd].Adr.NumBloc,buffer);
                break;
                case 2:
                     k=2;
                    for(int i=1;i<=k;i++){
                    while(buffer.tab[buff.table[indiceInd].Adr.Pos]!='|'){
                        if (buff.table[indiceInd].Adr.Pos >= b) {
                            LireDir(fich2 , buff.table[indiceInd].Adr.NumBloc+1 , &buffer) ;
                            buff.table[indiceInd].Adr.Pos = 0;
                        }
                        buff.table[indiceInd].Adr.Pos++;
                    }
                }
                buffer.tab[buff.table[indiceInd].Adr.Pos-2]=note[0];
                buffer.tab[buff.table[indiceInd].Adr.Pos-1]=note[1];
                EcrireDir(fich,buff.table[indiceInd].Adr.NumBloc,buffer);
                break;
                case 3:
                     k=3;
                    for(int i=1;i<=k;i++){
                    while(buffer.tab[buff.table[indiceInd].Adr.Pos]!='|'){
                        if (buff.table[indiceInd].Adr.Pos >= b) {
                            LireDir(fich2 , buff.table[indiceInd].Adr.NumBloc+1 , &buffer) ;
                            buff.table[indiceInd].Adr.Pos = 0;
                        }
                        buff.table[indiceInd].Adr.Pos++;
                    }
                }
                buffer.tab[buff.table[indiceInd].Adr.Pos-2]=note[0];
                buffer.tab[buff.table[indiceInd].Adr.Pos-1]=note[1];
                EcrireDir(fich,buff.table[indiceInd].Adr.NumBloc,buffer);
                break;
                case 4:
                     k=4;
                    for(int i=1;i<=k;i++){
                    while(buffer.tab[buff.table[indiceInd].Adr.Pos]!='|'){
                        if (buff.table[indiceInd].Adr.Pos >= b) {
                            LireDir(fich2 , buff.table[indiceInd].Adr.NumBloc+1 , &buffer) ;
                            buff.table[indiceInd].Adr.Pos = 0;
                        }
                        buff.table[indiceInd].Adr.Pos++;
                    }
                }
                buffer.tab[buff.table[indiceInd].Adr.Pos-2]=note[0];
                buffer.tab[buff.table[indiceInd].Adr.Pos-1]=note[1];
                EcrireDir(fich,buff.table[indiceInd].Adr.NumBloc,buffer);
                break;
                }

            }
            else{
                printf("\n1 : Arab\n2 : MATHEMATIQUE\n3 : DESIN\n4 : SPORT\n\n5 : ED_ISLAMIQUE\n6 : HIS_GEO\n7 : FRANCAIS\n8 :ED_CIVIQUE,\n\nVeuillez choisir un numero svp : ");
                scanf("%d",&choix2);
                printf("\nEntrer la nouvelle note : ");
                scanf("%s",note);
                switch(choix2){
                case 1:
                    k=1;
                    for(int i=1;i<=k;i++){
                    while(buffer.tab[buff.table[indiceInd].Adr.Pos]!='|'){
                        if (buff.table[indiceInd].Adr.Pos >= b) {
                            LireDir(fich2 , buff.table[indiceInd].Adr.NumBloc+1 , &buffer) ;
                            buff.table[indiceInd].Adr.Pos = 0;
                        }
                        buff.table[indiceInd].Adr.Pos++;
                    }
                }
                buffer.tab[buff.table[indiceInd].Adr.Pos-2]=note[0];
                buffer.tab[buff.table[indiceInd].Adr.Pos-1]=note[1];
                EcrireDir(fich,buff.table[indiceInd].Adr.NumBloc,buffer);
                break;
                case 2:
                     k=2;
                    for(int i=1;i<=k;i++){
                    while(buffer.tab[buff.table[indiceInd].Adr.Pos]!='|'){
                        if (buff.table[indiceInd].Adr.Pos >= b) {
                            LireDir(fich2 , buff.table[indiceInd].Adr.NumBloc+1 , &buffer) ;
                            buff.table[indiceInd].Adr.Pos = 0;
                        }
                        buff.table[indiceInd].Adr.Pos++;
                    }
                }
                buffer.tab[buff.table[indiceInd].Adr.Pos-2]=note[0];
                buffer.tab[buff.table[indiceInd].Adr.Pos-1]=note[1];
                EcrireDir(fich,buff.table[indiceInd].Adr.NumBloc,buffer);
                break;
                case 3:
                     k=3;
                    for(int i=1;i<=k;i++){
                    while(buffer.tab[buff.table[indiceInd].Adr.Pos]!='|'){
                        if (buff.table[indiceInd].Adr.Pos >= b) {
                            LireDir(fich2 , buff.table[indiceInd].Adr.NumBloc+1 , &buffer) ;
                            buff.table[indiceInd].Adr.Pos = 0;
                        }
                        buff.table[indiceInd].Adr.Pos++;
                    }
                }
                buffer.tab[buff.table[indiceInd].Adr.Pos-2]=note[0];
                buffer.tab[buff.table[indiceInd].Adr.Pos-1]=note[1];
                EcrireDir(fich,buff.table[indiceInd].Adr.NumBloc,buffer);
                break;
                case 4:
                     k=4;
                    for(int i=1;i<=k;i++){
                    while(buffer.tab[buff.table[indiceInd].Adr.Pos]!='|'){
                        if (buff.table[indiceInd].Adr.Pos >= b) {
                            LireDir(fich2 , buff.table[indiceInd].Adr.NumBloc+1 , &buffer) ;
                            buff.table[indiceInd].Adr.Pos = 0;
                        }
                        buff.table[indiceInd].Adr.Pos++;
                    }
                }
                buffer.tab[buff.table[indiceInd].Adr.Pos-2]=note[0];
                buffer.tab[buff.table[indiceInd].Adr.Pos-1]=note[1];
                EcrireDir(fich,buff.table[indiceInd].Adr.NumBloc,buffer);
                break;
                  case 5:
                    k=5;
                    for(int i=1;i<=k;i++){
                    while(buffer.tab[buff.table[indiceInd].Adr.Pos]!='|'){
                        if (buff.table[indiceInd].Adr.Pos >= b) {
                            LireDir(fich2 , buff.table[indiceInd].Adr.NumBloc+1 , &buffer) ;
                            buff.table[indiceInd].Adr.Pos = 0;
                        }
                        buff.table[indiceInd].Adr.Pos++;
                    }
                }
                buffer.tab[buff.table[indiceInd].Adr.Pos-2]=note[0];
                buffer.tab[buff.table[indiceInd].Adr.Pos-1]=note[1];
                EcrireDir(fich,buff.table[indiceInd].Adr.NumBloc,buffer);
                break;
                case 6:
                     k=6;
                    for(int i=1;i<=k;i++){
                    while(buffer.tab[buff.table[indiceInd].Adr.Pos]!='|'){
                        if (buff.table[indiceInd].Adr.Pos >= b) {
                            LireDir(fich2 , buff.table[indiceInd].Adr.NumBloc+1 , &buffer) ;
                            buff.table[indiceInd].Adr.Pos = 0;
                        }
                        buff.table[indiceInd].Adr.Pos++;
                    }
                }
                buffer.tab[buff.table[indiceInd].Adr.Pos-2]=note[0];
                buffer.tab[buff.table[indiceInd].Adr.Pos-1]=note[1];
                EcrireDir(fich,buff.table[indiceInd].Adr.NumBloc,buffer);
                break;
                case 7:
                     k=7;
                    for(int i=1;i<=k;i++){
                    while(buffer.tab[buff.table[indiceInd].Adr.Pos]!='|'){
                        if (buff.table[indiceInd].Adr.Pos >= b) {
                            LireDir(fich2 , buff.table[indiceInd].Adr.NumBloc+1 , &buffer) ;
                            buff.table[indiceInd].Adr.Pos = 0;
                        }
                        buff.table[indiceInd].Adr.Pos++;
                    }
                }
                buffer.tab[buff.table[indiceInd].Adr.Pos-2]=note[0];
                buffer.tab[buff.table[indiceInd].Adr.Pos-1]=note[1];
                EcrireDir(fich,buff.table[indiceInd].Adr.NumBloc,buffer);
                break;
                case 8:
                     k=8;
                    for(int i=1;i<=k;i++){
                    while(buffer.tab[buff.table[indiceInd].Adr.Pos]!='|'){
                        if (buff.table[indiceInd].Adr.Pos >= b) {
                            LireDir(fich2 , buff.table[indiceInd].Adr.NumBloc+1 , &buffer) ;
                            buff.table[indiceInd].Adr.Pos = 0;
                        }
                        buff.table[indiceInd].Adr.Pos++;
                    }
                }
                buffer.tab[buff.table[indiceInd].Adr.Pos-2]=note[0];
                buffer.tab[buff.table[indiceInd].Adr.Pos-1]=note[1];
                EcrireDir(fich,buff.table[indiceInd].Adr.NumBloc,buffer);
                break;

                }

            }
            break;
            }
            printf("\n\nMise a jour terminee avec succes\n");
        }

    }

void SuppretionInitial(int id) {
    int  bloc , pos ;
    int trv = 0 ;
    int j ;
    FILE *fich ;
    BufIndexId bufid ;
    Ouvrire(&fich , "FichierCourant" , 'A') ;
    fichier = fopen("fichierIndexID" , "rb") ;
    if (fichier == NULL) printf("\n\nVous devez creer le fichier Initial avec chargement initial!!\n\n") ;
    else {
        fread(&bufid , sizeof(BufIndexId) , 1 , fichier) ;
        RechDecIndexID(bufid , id , &j , &trv , Entete(fich , 4)) ;
        if (trv) {
            bloc = bufid.table[j].Adr.NumBloc ;
            pos = bufid.table[j].Adr.Pos ;
            LireDir(fich , bloc , &buffer) ;
            buffer.tab[pos] = '1' ;
            EcrireDir(fich , bloc , buffer) ;
            printf("La suppretion dans le fichier courant est terminee!\n vous pouvez consulter le resultat avec l\'affichage du fichier initial soit normal(choix 10) soit caractere par caractere(choix 9)!\n\n\n\n") ;
        }
        else printf("\n\nL\'etudiant n\'exist pas\n\n") ;
        Fermer(fich) ;
        Fermer(fichier) ;
    }
}
//******************************************************************************************
///************************************ Question 3 ******************************************
/** a) Pour construire un fichier de dossiers scolaires par eleve on doit faire la
recherche de chaque eleve dans le fichier d'archive puis on prend ses informations
et on les stockent dans se dossier avec ses moyennes de chaque année, et pour
faire la recherche d'un eleve :
-La cle sera : le numero de l'identifiant.
-Le type de ce fichier de dossier est : fichier binaire simple, contient la
 structure : {Identifiant , nom , prenom , tableau_des_moyennes[0..5]}
**/
/**b)
i. On va choisir un index dense qui contient toutes les moyennes de toutes les
eleves, dont chaque case contient la moyenne de l'eleve et son emplacement dans
le fichier archive, il accepte les valeurs répétées plusieurs fois, chaque année
on l'archive dans un fichier archive et on l'associé un index contient toutes les
moyennes des eleves archivés.

ii. On va creer l'index a partir le fichier d'archive
**/

void RechDecIndexArchive(BufIndexArchive bufIndArchive , float moyenne , int *trouve , int *j , int nbinsertion) {
    int inf , sup , m=0 ;
    inf = 0 ;
    sup = nbinsertion-1 ;
    *trouve = 0 ;
    if (nbinsertion == 0) *j = 0 ;
    else {
        while ((inf <= sup) && (!*trouve)) {
            m = (inf + sup)/2 ;
            if (bufIndArchive.tab[m].moyenne == moyenne) {
                *trouve = 1 ;
                *j = m ;
            }
            else if (bufIndArchive.tab[m].moyenne > moyenne) {
                sup = m-1 ;
            }

            else if (bufIndArchive.tab[m].moyenne < moyenne) {
                inf = m+1 ;
            }
            if (!*trouve || inf>sup) {
                *j = inf ;
            }
        }
    }
}
//--------------------------------------------------------------------------------------------------------------

void InsertionIndexArchive(BufIndexArchive *bufIndArch , float moyenne , int bloc , int pos , int nbInsert) {
    int trouve , j , i ;
    RechDecIndexArchive(*bufIndArch , moyenne , &trouve , &j , nbInsert) ;
    if (j<NbEtudiantMax-1) {
        i = nbInsert ;
        while(i>j) {
            (*bufIndArch).tab[i].moyenne = (*bufIndArch).tab[i-1].moyenne ;
            (*bufIndArch).tab[i].adr.NumBloc = (*bufIndArch).tab[i-1].adr.NumBloc ;
            (*bufIndArch).tab[i].adr.Pos = (*bufIndArch).tab[i-1].adr.Pos ;
            i-- ;
        }
        (*bufIndArch).tab[j].moyenne = moyenne ;
        (*bufIndArch).tab[j].adr.NumBloc = bloc ;
        (*bufIndArch).tab[j].adr.Pos = pos ;
    }else if (trouve) printf("L'etudiant est deja existe\n\n") ;
    else if (j>=NbEtudiantMax-1) printf("Le tableau est remplie completement\n\n") ;
}
//--------------------------------------------------------------------------------------------------------------
void CreerIndexArchive(BufIndexArchive *bufIndArch , char nomfich[100] , int annee) {
    int nbBloc , i=1 , reste = bArch , dernierpos , cpt=0 ;
    OuvrireArch(&fichier , nomfich , 'A') ;
    nbBloc = EnteteArch(fichier , 1) ;
    dernierpos = Entete(fichier , 2) ;
    while(i <= nbBloc) {
        LireDirArch(fichier , i , &bufferArch) ;
        if (i == nbBloc) reste = dernierpos ;
        for (int j=0 ; j < reste ; j++) {
            InsertionIndexArchive(bufIndArch , bufferArch.tab[j].moyenne , i , j , cpt) ;
            cpt++ ;
        }
        i++ ;
    }
    char chaine[100] , chAnnee[5] ;
    ///--- sauvgarder l'index dans un fichier avec le nom : IndexArchive+annee.
    ///--- Ex : IndexArchive2022
    strcpy(chaine , "IndexArchive") ;
    itoa(annee , chAnnee , 10) ;
    strcat(chaine , chAnnee) ;
    fichier2 = fopen(chaine , "ab") ;
    fwrite(bufIndArch , sizeof(BufIndexArchive) , 1 , fichier2) ;
    Fermer(fichier2) ;
    Fermer(fichier) ;
    printf("\n\n") ;
}
//******************************************************************************************
///************************************ Question 4 ******************************************

/** On va construire le fichier d'archive de type TOF dont chaque bloc est de
structure 'TblocArch', qui contient les informations de l'etudiant (ID , nom ,
prenom) et la moyenne de passage dans l'année courante, et contient aussi
deux autres champs la moyenne min et max (de chaque bloc), ce fichier est ordonnée
par l'identifiant de chaque eleve.
donc quand on faire la simulation de 5 années on va a chaque fois creer un fichier
archive pour chaque année, et donc pour chaque fichier archive on cree leur index
des moyennes.**/
//***************************** La machine abstaite pour le fichier d'archivage (TOF) **************************
void OuvrireArch(FILE **fich , char nom_fich[maximum] , char mode) {
    if (mode == 'A') {
        *fich = fopen(nom_fich , "rb+") ;
        fread(&enteteArch , sizeof(ENTETEFARCH) , 1 , *fich) ;
    }
    else if (mode == 'N') {
        enteteArch.AnneeDeScolarisation = 0 ;
        enteteArch.DernierPos = 0 ;
        enteteArch.NbBloc = 0 ;
        enteteArch.nbInsertion = 0 ;
        *fich = fopen(nom_fich , "ab+") ;
        fwrite(&enteteArch , sizeof(ENTETEFARCH) , 1 , *fich) ;
    }
    else {
        printf("Erreur : le mode est incorrect\n\n") ;
        *fich = NULL ;
    }
}

//*******************************************************************************
void LireDirArch(FILE *fich , int i , TblocArch *bufferArchive) {
    fseek(fich , sizeof(ENTETEFARCH) , SEEK_SET) ;
    fseek(fich , sizeof(TblocArch)*(i-1) , SEEK_CUR) ;
    fread(&*bufferArchive , sizeof(TblocArch) , 1 , fich) ;
}
//*******************************************************************************
void EcrireDirArch(FILE *fich , int i , TblocArch bufferArchive) {
    fseek(fich , sizeof(ENTETEFARCH) , SEEK_SET) ;
    fseek(fich , sizeof(TblocArch)*(i-1) , SEEK_CUR) ;
    fwrite(&bufferArchive , sizeof(TblocArch) , 1 , fich) ;
}
//*******************************************************************************
int EnteteArch(FILE *fich , int i) {
    if (fich == NULL) {
        printf("Il faut ouvrir le fichier\n\n") ;
        return -1 ;
    }
    rewind(fich) ;
    fread(&enteteArch , sizeof(ENTETEFARCH) , 1 , fich) ;
    if (i == 1) return enteteArch.NbBloc ;
    else if (i == 2) return enteteArch.DernierPos ;
    else if (i == 3) return enteteArch.AnneeDeScolarisation ;
    else if (i == 4) return enteteArch.nbInsertion ;
    else {
        printf("le caracteristique n\'exist pas!\n\n") ;
        return -1 ;
        exit(0) ;
    }
}
//*******************************************************************************
void Aff_EnteteArch(FILE *fich , int i , int val) {
    rewind(fich) ;
    if (i == 1) {
        enteteArch.NbBloc = val ;
    }
    else if (i == 2) {
        enteteArch.DernierPos = val ;
    }
    else if (i == 3) {
        enteteArch.AnneeDeScolarisation = val ;
    }
    else if (i == 4) {
        enteteArch.nbInsertion = val ;
    }
    else {
        printf("le caracteristique n\'exist pas!\n\n") ;
        exit(0) ;
    }
    fwrite(&enteteArch , sizeof(ENTETEFARCH) , 1 , fich) ;
}
//*******************************************************************************
//*******************************************************************************
float CalculMoy (char ficTOVC[maximum],char ficIndex[maximum],int Id)
{
    int trouve=0,j,indiceNom,indiceCourant,somme=0, k;
    char classe,nom[maximum],prenom[maximum],note[3];
    FILE *fich,*fich2;
    BufIndexId buff;
    Ouvrire(&fich2,ficTOVC,'A');  // On ouvre le fichier TOVC .
    fich=fopen(ficIndex,"rb");     //On ouvre le fichier d'indexId
    fread(&buff,sizeof(BufIndexId),1,fich);
    RechDecIndexID(buff,Id,&j,&trouve,Entete(fich2,4)); //On fait la recherche de l'Id
    if(!trouve){
        printf("\nCet identifiant n'existe pas ! ");
        Fermer(fich);
        Fermer(fich2);
        return -1 ;
    }
    else {
         LireDir(fich2 ,buff.table[j].Adr.NumBloc, &buffer);
         classe=buffer.tab[buff.table[j].Adr.Pos+9];          //On récupère la classe.
         indiceNom=getNom(fich2 ,&buffer,buff.table[j].Adr.Pos , buff.table[j].Adr.NumBloc,nom); //On calcule  la taille du nom et du prénom pour pouvoir accéder aux champs des notes.
         indiceCourant=getPrenom(fich2 ,  &buffer ,  indiceNom ,  buff.table[j].Adr.NumBloc , prenom);
         indiceCourant+=2; //pour sauter la case du genre et #.
         if (classe=='P' || classe<='2') k=4;    //On récupère les notes tout dépend l'année
         else k=8;
         for(int i=1;i<=k;i++){
            while(buffer.tab[indiceCourant]!='|'){
                if (indiceCourant >= b) {
                    LireDir(fich2 , buff.table[j].Adr.NumBloc+1 , &buffer) ;
                    indiceCourant = 0;
                }
                indiceCourant++;
            }
            note[0]=buffer.tab[indiceCourant-2];
            note[1]=buffer.tab[indiceCourant-1];
            indiceCourant++;
            somme+=atoi(note);           //La somme des notes.
        }
        Fermer(fich);
        Fermer(fich2);
        return ((float)somme)/k;       //On retourne la moyenne.

    }
}

void ConstructionArchive(char FichierTOF[maximum],char fichierTOVC[maximum],char fichierIndexID[maximum],int anneeCourante)
{
    int j,i,n ;
    float moyMin,moyMax;
    FILE *fich2,*fich,*fich3;
    BufIndexId buff;
    TblocArch buffArch;
    char nom[maximum],prenom[maximum];
    fich2=fopen(fichierIndexID,"rb");    //On ouvre le fichier d'indexID pour remplir l'archive, ordonné selon id (index).
    fread(&buff,sizeof(BufIndexId),1,fich2);
    Ouvrire(&fich,fichierTOVC,'A');      // On ouvre le fichier TOVC .
    OuvrireArch(&fich3,FichierTOF,'N'); // on creer le fichier archive
    i=1;j=0;
    n=Entete(fich,4);
    moyMax=0;
    for(int k=0;k<n;k++)
    {
        if(j<bArch)
        {
            if(j==0 && i!=1) k=k-1; //Pour éviter les affectation dans Else (le cas de la premiere case pour chaque bloc).
            LireDir(fich ,buff.table[k].Adr.NumBloc, &buffer); //Pour le TOVC
            int indprenom=getNom(fich,&buffer,buff.table[k].Adr.Pos,buff.table[k].Adr.NumBloc,nom); //Récupération du nom.
            getPrenom(fich,&buffer,indprenom,buff.table[k].Adr.NumBloc,prenom);
            strcpy( buffArch.tab[j].nom,nom);  //Affectation du nom.
            strcpy( buffArch.tab[j].prenom,prenom);  //Affectation du prénom.
            buffArch.tab[j].moyenne=CalculMoy(fichierTOVC,fichierIndexID,buff.table[k].Id); //Calcul et affectation de la moyenne.
            buffArch.tab[j].numIdentifiant=buff.table[k].Id;              //Affectation de l'ID
            if(j==0) moyMin=buffArch.tab[0].moyenne;
            if(buffArch.tab[j].moyenne>moyMax) moyMax=buffArch.tab[j].moyenne;
            if(buffArch.tab[j].moyenne<moyMin) moyMin=buffArch.tab[j].moyenne;
            j++;
        }
        else{
            buffArch.moyMin=moyMin; //Affectation des moyennes Min et Max.
            buffArch.moyMax=moyMax;
            EcrireDirArch(fich3,i,buffArch); //Ecriture du bloc.
            moyMax=0;
            i++;
            j=0;
        }
    }
    buffArch.moyMin=moyMin; //Affectation des moyennes Min et Max.
    buffArch.moyMax=moyMax;
    EcrireDirArch(fich3,i,buffArch); //Ecriture du bloc.
    Fermer(fich3);
    OuvrireArch(&fich3,FichierTOF,'A');
    //Affectation des entetes.
    Aff_EnteteArch(fich3 , 1 , i) ;
    Aff_EnteteArch(fich3 , 4 , n) ;
    if (j == 0) j = bArch ;
    Aff_EnteteArch(fich3 , 2 , j);
    Aff_EnteteArch(fich3 , 3 , anneeCourante );
    Fermer(fich);
    Fermer(fich2);
    Fermer(fich3);
}
/**
 a)Quand on fait l'archivage on doit parcourir tout le fichier TOVC des élèves pour
   récupérer les informations de chaque étudiant et pour calculer la moyenne de
   passage aussi, et puis on les stockent dans le fichier archive.
   Donc le coût de l'archivage est le nombre d'accés au fichiers courant(TOVC) et
   archive.
   - Pour le fichier courant(TOVC), on doit parcourir tout le fichier, donc le
     nombre d'accés au ce fichier est le nombre de blocs qui forme ce fichier
     donc on le note N1, avec : N1 = Entete(FichierTOVC , 1) qui design le nombre
     de blocs total.
   - Pour le fichier archive, c'est le nombre d'écritures qu'on fait pour remplir
     ce fichier, c'est aussi le nombre de blocs total formés, on a chaque bloc peut
     contenir 50 élèves(bArch=50), donc le nombre de blocs formés est le
     nombre total des élèves divisée sur la taille du bloc, on le note N2 avec :
     N2 = Entete(fichierArchive , 1)/bArch

    -> et Donc le coût de l'archivage est N1+N2
**/
char getGenre(FILE *fich , Tbloc buffer , int pos , int bl,int taille)
{
    char genre,classe;

    classe=buffer.tab[pos+9];
     if (classe=='P' || classe<='2')
        {
            taille=taille+pos-40;
            if(taille<0)
            {
                LireDir(fich,bl-1,&buffer);
                taille=taille+b;
            }
            else if (taille>=b)
            {
                LireDir(fich,bl+1,&buffer);
                taille=taille-b;
            }
            genre=buffer.tab[taille];
        }
        else{
            taille=taille+pos-93;
            if(taille<0)
            {
                LireDir(fich,bl-1,&buffer);
                taille=taille+b;
            }
             else if (taille>=b)
            {
                LireDir(fich,bl+1,&buffer);
                taille=taille-b;
            }
            genre=buffer.tab[taille];

        }

    return genre ;
}
void Simulation5Annee(int AnneeDebut,int NombreEleves)
{
    int cls,clsP,idNum, NvEleves=0;
    char nomFichInd[maximum],nomFichIndPrec[maximum],nomFichIndCls[maximum], nomFichPrec[maximum],nomFich[maximum],nomFichArch[maximum],AnneeCh[5],nom[maximum],prenom[maximum],  classe[3],Id[5];
    FILE *fich,*fich2,*fich3,*f1;
    BufIndexArchive buffIndArch ;
    BufIndexId buff;
    Eleve elev;
    TabString tableau;

    strcpy(nomFich,"Fichier");    //Manipulation des chaines (noms des fichiers).
    strcpy(nomFichArch,"FichierArch");
    strcpy(nomFichInd,"fichierIndexID");
    strcpy(nomFichIndCls,"fichierIndexClasse");
    itoa(AnneeDebut , AnneeCh , 10) ;
    strcat(nomFich , AnneeCh) ;
    strcat(nomFichArch , AnneeCh) ;
    strcat(nomFichInd,AnneeCh);
    strcat(nomFichIndCls,AnneeCh);


    ChargementInitial(nomFich,  NombreEleves , AnneeDebut); //Création du premier fichier.
    ConstructionArchive(nomFichArch,nomFich,"fichierIndexID",AnneeDebut); //Archivage du premier fichier.
    CreerIndexArchive(&buffIndArch , nomFichArch ,AnneeDebut);

    for(int z=1;z<5;z++){
    strcpy(nomFichPrec,nomFich);      //Sauvgarde du nom du fichier précédent, on l'aura besion.

    if(z==1) strcpy(nomFichIndPrec,"fichierIndexID");
    else strcpy(nomFichIndPrec,nomFichInd);

    Ouvrire(&fich,nomFich,'A');
    fich2=fopen(nomFichIndPrec,"rb");
    fread(&buff , sizeof(BufIndexId) , 1 , fich2) ;


        AnneeDebut++;

        strcpy(nomFich,"Fichier");    //Manipulation des chaines pour l'année prochaine.
        strcpy(nomFichArch,"FichierArch");
        strcpy(nomFichInd,"fichierIndexID");
        strcpy(nomFichIndCls,"fichierIndexClasse");
        itoa(AnneeDebut , AnneeCh , 10) ;
        strcat(nomFich , AnneeCh) ;
        strcat(nomFichArch , AnneeCh) ;
        strcat(nomFichInd,AnneeCh);
        strcat(nomFichIndCls,AnneeCh);

        Ouvrire(&fich3,nomFich,'N');   //Création du fichierTOVC de la prochaine année.
        //On l'a besion pour le premier eng dans ce fichier qui doit pas etre vide avant l'insertion.
        //On est obligé de charger le fichier par au moins un eng.
        f1 = fopen("etudiants2022.txt" , "a") ;

int l=0;
    for(int i=0;i<Entete(fich,4);i++)
    {
        LireDir(fich,buff.table[i].Adr.NumBloc,&buffer);

        //Récupération des informations pour chaque élève.
        getClasse(fich,buffer,buff.table[i].Adr.Pos,buff.table[i].Adr.NumBloc,classe);
        int tailleEnrg= getTailleEleve(fich,buffer,buff.table[i].Adr.Pos,buff.table[i].Adr.NumBloc);
        char genre= getGenre(fich ,buffer ,buff.table[i].Adr.Pos , buff.table[i].Adr.NumBloc,tailleEnrg );
        int indicePrenom=getNom(fich,&buffer,buff.table[i].Adr.Pos,buff.table[i].Adr.NumBloc,nom);
        getPrenom(fich,&buffer,indicePrenom,buff.table[i].Adr.NumBloc,prenom);
        float moy=CalculMoy(nomFichPrec,nomFichIndPrec,buff.table[i].Id);

        strcpy(elev.nom,nom);
        strcpy(elev.prenom,prenom);
        itoa(buff.table[i].Id ,elev.numidentite , 10) ;
        elev.genre[0]=genre;
        elev.genre[1]='\0';

        if(classe[0]=='P')
        {
            classe[0]='0';
        }
        cls=atoi(classe);

        if(moy>=10)
        {
            cls+=10;                   //L'élève passe à la prochaine année.
            itoa(cls,classe,10);
            elev.classeidentite.annee[0]=classe[0];
            elev.classeidentite.numero[0]=classe[1];
        }
        else
        {
            elev.classeidentite.annee[0]=classe[0];     //Sinon il reste dans la meme année.
            elev.classeidentite.numero[0]=classe[1];
        }


        if(elev.classeidentite.annee[0]!='6')
        {
                 if(elev.classeidentite.annee[0]=='0') //Le cas des redoublants pour l'année priparative.
            {
                elev.classeidentite.annee[0]='P';
            }

                char chaineText[100] ;
                strcpy(chaineText , elev.classeidentite.annee) ;
                strcat(chaineText , ",") ;
                strcat(chaineText , elev.classeidentite.numero) ;
                strcat(chaineText , ",") ;
                strcat(chaineText , elev.nom) ;
                strcat(chaineText , ",") ;
                strcat(chaineText , elev.prenom) ;
                strcat(chaineText , ",") ;
                strcat(chaineText , elev.numidentite) ;
                strcat(chaineText , ",") ;
                strcat(chaineText , elev.genre) ;
                strcat(chaineText , ",") ;
                strcpy(tableau.tab[l].str , chaineText ) ;
            // end for i
            // tri --------------------------------

                l++;
            }
        else{
            NvEleves++;
        }


    }
     TriTableauString(&tableau , l) ;
      for (int a=0 ; a<l ; a++)
        {
            fputs(tableau.tab[a].str , f1) ;
            fputs("\n" , f1) ;
        }

        fclose(f1);

          f1 = fopen("etudiants2022.txt" , "r") ;
    // remplisage le fichier TOVC ********************
    int k=0,cpt=0 ,p,valDernierPos=0,valNbBloc=0,cmp,taille;
    char testerClasse[3];
    BufIndexClasse bufClasse;
    BufIndexId buffId;

    for (int i=1 ; i<=l ; i++) {
        p = 0 ;
        if (i == 1) valDernierPos = 0 ;
        else valDernierPos = k ;
        buffId.table[i-1].Adr.NumBloc = valNbBloc+1 ;
        char chDeListeEtudiant[b] ; // recuperer a partir du fichier
        char chaineDansBuffer[b] ; // ecrire dans buffer
        fgets(chDeListeEtudiant , 80 , f1) ;
        strcpy(elev.classeidentite.annee , strtok(chDeListeEtudiant , ",")) ;
        strcpy(elev.classeidentite.numero , strtok(NULL , ",")) ;
        strcpy(elev.nom , strtok(NULL , ",")) ;
        strcpy(elev.prenom , strtok(NULL , ",")) ;
        strcpy(elev.numidentite , strtok(NULL , ",")) ;
        strcpy(elev.genre , strtok(NULL , ",")) ;
        testerClasse[0] = elev.classeidentite.annee[0] ;
        testerClasse[1] = elev.classeidentite.numero[0] ;
        // ------------------ Remplir l'index du classes ----------------------
        if (i == 1) {
            strcpy(bufClasse.table[0].Idclasse , "P1") ;
            bufClasse.table[0].Adr.NumBloc = 1 ;
            bufClasse.table[0].Adr.Pos = 0 ;
            cpt ++ ;
        }
        else {
            cmp = strcmp(bufClasse.table[cpt-1].Idclasse , testerClasse) ;
            if (cmp != 0) { // si la classe est deja ecrite on ne la sauvegarde pas
            strcpy(bufClasse.table[cpt].Idclasse , testerClasse) ;
            bufClasse.table[cpt].Adr.NumBloc = valNbBloc+1 ;
            bufClasse.table[cpt].Adr.Pos = valDernierPos ;
            cpt ++ ;
            }
        }
        // ------------------ Fin remplir l'index du classes ------------------
        // ------------ remplisage des notes ------------------
        MatNoteFich(&elev) ;
        taille = EcrireEnrgDansChaine(elev , chaineDansBuffer) ;
        while (p<taille+4) { // remplire le buffer avec l'enregistrement numero k
            buffer2.tab[k] = chaineDansBuffer[p] ;
            k++ ;
            p++ ;
            if (k == b) { // Si le bloc est remplie
                k = 0 ;
                valNbBloc++ ;
                EcrireDir(fich3 , valNbBloc , buffer2) ;

            } // Fin Si le bloc est remplie
        } // end while
        // ************ Remplir l'index du identifiant ************************
        buffId.table[i-1].Adr.Pos = valDernierPos ;
        buffId.table[i-1].Id = atoi(elev.numidentite) ;
        // ************  Fin remplir l'index du identifiant ********************
    } // end for i
       if (k > 0 && k < b) {
        Tbloc buf2 ;
        for (int j2=0 ; j2<k ; j2++) {
            buf2.tab[j2] = buffer.tab[j2] ;
        }
        fwrite(&buf2 , sizeof(Tbloc) , 1 , fich3) ;
        valNbBloc ++ ;
    }

    Fermer(fich3) ;
    Fermer(f1) ;
    Ouvrire(&fich3 , nomFich , 'A') ;
    Aff_Entete(fich3 , 1 , valNbBloc) ; // nombre de blocs total
    Aff_Entete(fich3 , 2 , k) ; // derniere position
    Aff_Entete(fich3 , 3 , AnneeDebut) ; // année courante
    Aff_Entete(fich3 , 4 , l) ; // nombre d'insertions
    FILE *fichierIndexID ;
    FILE *fichierIndexClasse ;
    fichierIndexID = fopen(nomFichInd , "ab");
    triABulle( &buffId , Entete(fich3 , 4)-1 ) ;
    fwrite(&buffId , sizeof(BufIndexId) , 1 , fichierIndexID) ;
    Fermer(fichierIndexID) ;
    fichierIndexClasse = fopen(nomFichIndCls , "ab");
    fwrite(&bufClasse , sizeof(bufClasse) , 1 , fichierIndexClasse) ;
    Fermer(fichierIndexClasse) ;
    Fermer(fich3) ;
    remove("etudiants2022.txt") ;

    //L'insertion des neauveaux élève pour cette année.
    char salle[2];
        Alea2Fich(&elev);
        cls=AleaNb(1,3);
        itoa(cls,salle,10);
        elev.classeidentite.annee[0]='P';
        elev.classeidentite.annee[1]='\0';
        strcpy(elev.classeidentite.numero,salle);
        MatNoteFich(&elev);

        Ouvrire(&fich3 , nomFich , 'A') ;
        fichierIndexID = fopen(nomFichInd , "ab");
        fread(&buff,sizeof(BufIndexId),1,fichierIndexID);
        int trouve=1;
        while(trouve)
        {
            AleaIdEleve(&elev);
            idNum=atoi(elev.numidentite);
            RechDecIndexID(buff,idNum,&k,&trouve,Entete(fich3,4)); //On fait la recherche de l'Id
        }
        Fermer(fich3);
        Fermer(fichierIndexID);

    Ouvrire(&fich3,nomFich,'A');

    //Création du fichier archive et son index.
    ConstructionArchive(nomFichArch,nomFich,nomFichInd,AnneeDebut); //Archivage du premier fichier.
    CreerIndexArchive(&buffIndArch , nomFichArch ,AnneeDebut);


    Fermer(fich3);
    Fermer(fich);
    Fermer(fich2);
}
}
//*******************************************************************************
void ListerAnneeInitial() {
    BufIndexArchive buf ;
    int trouve , j , nb , pos , bl ;
    OuvrireArch(&fichier , "Archive2022" , 'A') ;
    fichier2 = fopen("IndexArchive2022" , "rb") ;
    fread(&buf , sizeof(BufIndexArchive) , 1 , fichier2) ;
    nb = EnteteArch(fichier , 4) ;
    RechDecIndexArchive(buf , 12 , &trouve , &j , nb) ;
    while(buf.tab[j].moyenne == 12) {
        j++ ;
    }
    printf("\n\n******************** Les eleves ayant obtenu une moyenne superieure(strictement) a 12 dans l'annee %d ********************\n\n" , EnteteArch(fichier , 3)) ;
    for (int i=j ; i<nb ; i++ ) {
        bl = buf.tab[i].adr.NumBloc ;
        LireDirArch(fichier , bl , &bufferArch) ;
        pos = buf.tab[i].adr.Pos ;
        printf("Id = %d\t     " , bufferArch.tab[pos].numIdentifiant) ;
        printf("Nom = %8s\t      " , bufferArch.tab[pos].nom) ;
        printf("Prenom = %8s\t\t      " , bufferArch.tab[pos].prenom) ;
        printf("\tMoyenne = %.2f\n\n" , bufferArch.tab[pos].moyenne) ;
    }
    Fermer(fichier2) ;
    Fermer(fichier) ;
}
void Lister(int n) {
    BufIndexArchive buf ;
    int trouve , j , nb , pos , bl ;
    if (n == 1) {
        ListerAnneeInitial() ;
    }
    else {
        int annee = 2023 ;
        /**premier annee**/ ListerAnneeInitial() ;
        /// les autres 4 annees
        for (int k = 1 ; k<=4 ; k++) {
            char chaine[maximum] , chAnne[5] , chaine2[maximum] ;
            strcpy(chaine , "FichierArch") ;
            itoa(annee , chAnne , 10) ;
            strcat(chaine , chAnne) ;
            OuvrireArch(&fichier , chaine , 'A') ;
            strcpy(chaine2 , "IndexArchive" ) ;
            strcat(chaine2 , chAnne) ;
            fichier2 = fopen(chaine2, "rb") ;
            fread(&buf , sizeof(BufIndexArchive) , 1 , fichier2) ;
            nb = EnteteArch(fichier , 4) ;
            RechDecIndexArchive(buf , 12 , &trouve , &j , nb) ;
            while(buf.tab[j].moyenne == 12) {
                j++ ;
            }
            printf("\n\n******************** Les eleves ayant obtenu une moyenne superieure(strictement) a 12 dans l'annee %d ********************\n\n" , EnteteArch(fichier , 3)) ;
            for (int i=j ; i<nb ; i++ ) {
                bl = buf.tab[i].adr.NumBloc ;
                LireDirArch(fichier , bl , &bufferArch) ;
                pos = buf.tab[i].adr.Pos ;
                printf("Id = %d\t     " , bufferArch.tab[pos].numIdentifiant) ;
                printf("Nom = %8s\t      " , bufferArch.tab[pos].nom) ;
                printf("Prenom = %8s\t\t      " , bufferArch.tab[pos].prenom) ;
                printf("\tMoyenne = %.2f\n\n" , bufferArch.tab[pos].moyenne) ;
            }
            Fermer(fichier2) ;
            Fermer(fichier) ;
            annee++ ;
        } // end for i
    }// end else
} // end function
///************************************ Question 5 ******************************************
/** Quand on faire le transfert d'un etudiant on suppose qu'il est suppremer de
l'ancien ecole et son dossier scolaire est deja pret, ce dossier contient les
informations de l'eleve et leur moyennes de passage de l'année courante et les
autres année précedentes.Donc on l'ajout dans le fichier initial qui est le fichier
de l'année courante et dans le fichier d'archive, donc on doit inserer l'eleve dans
le fichier courant (Insertion) et on fait un module pour l'insertion dans l'archive
ainsi que l'index.
**/
void rechDecBufArchive(TblocArch bufferArchive , int id , int *j , int *trouve , int Nbmax) {
    int inf , sup , m=0 ;
    inf = 0 ;
    sup = Nbmax - 1 ; // nombre maximal des enregistrements dans le buffer
    *trouve = 0 ;
    while ((inf <= sup) && (!*trouve)) {
        m = (inf + sup)/2 ;
        if (bufferArchive.tab[m].numIdentifiant == id) {
            *trouve = 1 ;
            *j = m ;
        }
        else if (bufferArchive.tab[m].numIdentifiant > id) {
            sup = m-1 ;
        }

        else if (bufferArchive.tab[m].numIdentifiant < id) {
            inf = m+1 ;
        }
        if (!trouve || inf>sup) {
            *j = inf ;
        }
    }
} // end function
//**************************************************************************************************
void RechercheArchive(char nomfich[100] , int id , int *trouve , int *bloc , int *pos) {
    int j2 = 0 , trv = 0 , sup , inf , m=0  , bl , nb ;
    Ouvrire(&fichier , nomfich , 'A') ;
    *trouve = 0 ;
    sup = EnteteArch(fichier , 1) ;
    bl = sup ;
    inf = 1 ;
    nb = EnteteArch(fichier , 2) ;
    int cbon = 0 ; //si le valeur doit etre insere dans un bloc
    while (inf <= sup && !trv && !cbon) { //while
        m = (inf + sup)/2 ;
        LireDirArch(fichier , m , &bufferArch) ;
        if (m != bl) rechDecBufArchive(bufferArch , id , &j2 , &trv , bArch) ;
        else rechDecBufArchive(bufferArch , id , &j2 , &trv , nb) ;
        if (trv) { // si la valeur est dans le Bloc
            *trouve = 1 ;
            *bloc = m ;
            *pos = j2 ;
            cbon = 1 ;
        } // fin si la valeur est dans le Bloc
        else { // si la valeur n'est pas dans le Bloc
            if (m != bl) { // travailler avec bArch
                if (id > bufferArch.tab[bArch-1].numIdentifiant) {
                    inf = m+1 ;
                }
                else if (id < bufferArch.tab[0].numIdentifiant) {
                sup = m-1 ;
                }
                else if (id > bufferArch.tab[0].numIdentifiant && id < bufferArch.tab[bArch-1].numIdentifiant) {
                    *trouve = 0 ;
                    *bloc = m ;
                    *pos = j2 ;
                    cbon = 1 ;
                }
            } // fin travailler avec bArch
            else { // si on a dans le dernier bloc
                if (id > bufferArch.tab[nb-1].numIdentifiant) {
                    inf = m+1 ;
                }
                else if (id < bufferArch.tab[0].numIdentifiant) {
                sup = m-1 ;
                }
                else if (id > bufferArch.tab[0].numIdentifiant && id < bufferArch.tab[nb-1].numIdentifiant) {
                    *trouve = 0 ;
                    *bloc = m ;
                    *pos = j2 ;
                    cbon = 1 ;
                }
            } // Fin si on a dans le dernier bloc
        } // fin si la valeur n'est pas dans le Bloc
    } // End Big while
    if ( (!trv) && (inf > sup) && (j2 < bArch)) {
        *trouve = 0 ;
        *bloc = m ;
        *pos = j2 ;
    }
    else if ( (!trv) && (inf > sup) && (j2 == bArch) ) {
        *trouve = 0 ;
        *bloc = inf ;
        *pos = 0 ;
    }
    fclose(fichier) ;
} // end of function

void InsertionArchive(char nomfich[100] , EleveArch e) {
    int trouve , bloc , pos , nb , k , dernierBloc , dernierePosition , bl , test=0 , stop=0 , n ;
    OuvrireArch(&fichier , nomfich , 'A') ;
    RechercheArchive(nomfich , e.numIdentifiant , &trouve , &bloc , &pos) ;
    if (trouve) printf("L\'eleve est deja existe!!\n\n") ;
    else {
        /// mis a jours de l'index de la moyenne
        BufIndexArchive buf ;
        OuvrireArch(&fichier , nomfich , 'A') ;
        char chaine[100] , chAnnee[5] ;
        strcpy(chaine , "IndexArchive") ;
        n = EnteteArch(fichier , 3) ;
        itoa(n , chAnnee , 10) ;
        strcat(chaine , chAnnee) ;
        fichier2 = fopen(chaine , "rb") ;
        n = EnteteArch(fichier , 4) ;
        fread(&buf , sizeof(BufIndexArchive) , 1 , fichier2) ;
        InsertionIndexArchive(&buf , e.moyenne , bloc , pos , n) ;
        n++ ;
        Fermer(fichier2) ;
        fichier2 = fopen(chaine , "wb") ;
        fwrite(&buf , sizeof(BufIndexArchive) , 1 , fichier2) ;
        Fermer(fichier2) ;
        /// Fin mis a jours de l'index de la moyenne
        TblocArch bufferArch2 ;
        dernierBloc = EnteteArch(fichier , 1) ;
        dernierePosition = EnteteArch(fichier , 2) ;
        if (dernierePosition == bArch) {
            EcrireDirArch(fichier , dernierBloc+1 , bufferArch2) ;
            test = 1 ;
        }
        bl = bloc ;
        LireDirArch(fichier , bloc , &bufferArch) ;
        for (int j=0 ; j<pos ; j++) {
            bufferArch2.tab[j].moyenne = bufferArch.tab[j].moyenne ;
            strcpy(bufferArch2.tab[j].nom , bufferArch.tab[j].nom) ;
            strcpy(bufferArch2.tab[j].prenom , bufferArch.tab[j].prenom) ;
            bufferArch2.tab[j].numIdentifiant = bufferArch.tab[j].numIdentifiant ;
        }
        k = pos ;
        bufferArch2.tab[k].moyenne = e.moyenne ;
        strcpy(bufferArch2.tab[k].nom , e.nom) ;
        strcpy(bufferArch2.tab[k].prenom , e.prenom) ;
        bufferArch2.tab[k].numIdentifiant = e.numIdentifiant ;
        k++ ;
        if ( e.moyenne > bufferArch.moyMax ) {
            bufferArch2.moyMax = e.moyenne ;
            bufferArch2.moyMin = bufferArch.moyMin ;
        }
        else if ( e.moyenne < bufferArch.moyMin ) {
            bufferArch2.moyMin = e.moyenne ;
            bufferArch2.moyMax = bufferArch.moyMax;
        }
        else {
            bufferArch2.moyMax = bufferArch.moyMax ;
            bufferArch2.moyMin = bufferArch.moyMin ;
        }
        if (bloc == dernierBloc && pos == dernierePosition) stop = 1 ;
        while(!stop) {
            if (bloc == dernierBloc) nb = dernierePosition ;
            else nb = bArch ;
            if (k == nb) {
                if (bufferArch2.tab[0].moyenne > bufferArch.moyMax)
                    bufferArch2.moyMax = bufferArch2.tab[0].moyenne ;
                else if (bufferArch2.tab[0].moyenne < bufferArch.moyMin)
                    bufferArch2.moyMin = bufferArch2.tab[0].moyenne ;
                else {
                    bufferArch2.moyMax = bufferArch.moyMax ;
                    bufferArch2.moyMin = bufferArch.moyMin ;
                }
                EcrireDirArch(fichier , bl , bufferArch2) ;
                bl++ ;
                k = 0 ;
            }
            if (pos == nb) {
                    bloc++ ;
                    LireDirArch(fichier , bloc , &bufferArch) ;
                    pos = 0 ;
            }
            bufferArch2.tab[k].moyenne = bufferArch.tab[pos].moyenne ;
            strcpy(bufferArch2.tab[k].nom , bufferArch.tab[pos].nom) ;
            strcpy(bufferArch2.tab[k].prenom , bufferArch.tab[pos].prenom) ;
            bufferArch2.tab[k].numIdentifiant = bufferArch.tab[pos].numIdentifiant ;
            k++ ;
            pos++ ;
            if (bloc == dernierBloc && pos == dernierePosition) stop = 1 ;
        } // fin de decalage (while(!stop))
        if (k > 0 && k<bArch) {
            TblocArch bufferArch3 ;
            for (int j2=0 ; j2<k ; j2++) {
                buffer3.tab[j2] = buffer2.tab[j2] ;
                bufferArch3.tab[j2].moyenne = bufferArch2.tab[j2].moyenne ;
                strcpy(bufferArch3.tab[j2].nom , bufferArch2.tab[j2].nom) ;
                strcpy(bufferArch3.tab[j2].prenom , bufferArch2.tab[j2].prenom) ;
                bufferArch3.tab[j2].numIdentifiant = bufferArch2.tab[j2].numIdentifiant ;
            }
            EcrireDirArch(fichier , bl , bufferArch3) ;
        }
        /// mis a jours les entetes(1,2,4)
        if (test) Aff_EnteteArch(fichier , 1 , bl) ;
        Aff_EnteteArch(fichier , 2 , k) ;
        Aff_EnteteArch(fichier , 4 , n) ;
        Fermer(fichier) ;
        printf("L\'insertion dans l\'archive est terminee!\n\n") ;

    } // fin else
} // fin fonction
//**************************************************************************************************

void Transfert(Eleve e , float moyenne) {
    /**1) insertion dans le fichier de l'annee courante (FichierCourant2022) **/
    InsertionInitial(e) ;
    /**2) insertion dans le fichier archive courant (Archive) **/
    EleveArch eArch ;
    eArch.moyenne = moyenne ;
    eArch.numIdentifiant = atoi(e.numidentite) ;
    strcpy(eArch.nom , e.nom) ;
    strcpy(eArch.prenom , e.prenom) ;
    InsertionArchive("Archive2022" , eArch) ;
    printf(" Le Transfert dans le fichier initial et le fichier d\'archive est terminee!\n vous pouvez consulter le resultat avec l\'affichage du fichier initial soit normal soit caractere par caractere et meme l'affichage dans le fichier archive!\n\n") ;
}
//**************************************************************************************************
int ValeurFausse(char chaine[100]) {
    int k = strlen(chaine) ;
    for (int i=0 ; i<k ; i++) {
        if (chaine[i] == '#') return 1 ;
    }
    return 0 ;
}
//---------------------------------------------------------------------------------------------------------------------------------
void AfficherArchive(char nomfich[100]) {
    OuvrireArch(&fichier , nomfich , 'A') ;
    int i = 1 , reste = bArch , n , n2 ;
    n = Entete(fichier , 1) ;
    n2 = EnteteArch(fichier , 2) ; // derniere position
    printf("\n\n*********************************** Archive de l\'annee %d ***********************************\n\n\n" , EnteteArch(fichier , 3)) ;
    printf("   Id\t") ;
    printf("                        Nom\t") ;
    printf("                     Preonom\t") ;
    printf("                   Moyenne\n\n") ;
        while(i <= n) {
        LireDirArch(fichier , i , &bufferArch) ;
        if (i == n) reste = n2 ;
        for (int j=0 ; j < reste ; j++) {
            if (!ValeurFausse(bufferArch.tab[j].nom) && !ValeurFausse(bufferArch.tab[j].prenom)){
                printf("   %d\t" , bufferArch.tab[j].numIdentifiant) ;
                printf("             %15s\t" ,bufferArch.tab[j].nom ) ;
                printf("             %15s\t" , bufferArch.tab[j].prenom) ;
                printf("                     %.2f\n\n" , bufferArch.tab[j].moyenne) ;
            }
        }
        i++ ;
    }
    Fermer(fichier) ;
}
 void AfficherArchiveParBloc(char nomfich[100]) {
    OuvrireArch(fichier , nomfich , 'A') ;
    int i = 1 , reste = bArch , n , n2 ;
    n = Entete(fichier , 1) ;
    n2 = EnteteArch(fichier , 2) ; // derniere position
    printf("\n\n*********************************** Archive de l\'annee %d Par Bloc et Position ***********************************\n\n\n" , EnteteArch(fichier , 3)) ;
    printf("                    Id\t") ;
    printf("                        Nom\t") ;
    printf("                     Preonom\t") ;
    printf("               Moyenne\n\n") ;
        while(i <= n) {
        printf("\n ==>> Bloc numero %d\n\n" , i) ;
        LireDirArch(fichier , i , &bufferArch) ;
        if (i == n) reste = n2 ;
        for (int j=0 ; j < reste ; j++) {
            printf(" >Position %d :\t" , j) ;
            printf("   %d\t" , bufferArch.tab[j].numIdentifiant) ;
            printf("             %15s\t" ,bufferArch.tab[j].nom ) ;
            printf("             %15s\t" , bufferArch.tab[j].prenom) ;
            printf("                %.2f\n\n" , bufferArch.tab[j].moyenne) ;
        }
        i++ ;
    }
    Fermer(fichier) ;
}
//////////////////////////////////////////////////////////////////////////////

