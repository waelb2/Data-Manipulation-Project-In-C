#ifndef BIBLIOTEQUE_H_INCLUDED
#define BIBLIOTEQUE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** On va mettre les champs dans le Buffer dans l'ordre comme suit :
    1 octets pour l'effacement (0 non effacé ou 1 effacé)
    3 octets pour la taille de l'enregistrement
    4 octets pour l'identifiant de l'eleve
    1 octets pour l’année de scolarisation
    1 octets pour Le numéro de la salle
    les octets du nom
    les octets du prenom
    1 octets pour le genre
    et les octets du tableau comme suit : matiere1~note1|matiere2~note2 ...
    on doit sepparer chaque champ a partir du cle par le separateur #
    Exemple : 00727899#P#1#CHIKOUCHE#WAFAEE#F#ARAB~14|MATHEMATIQUE~07|DESIN~20|SPORT~12|
**/



//***************************** Les constantes **********************************
#define maximum 30 // taille maximumimum des noms et prenoms
#define maximumTaille 3 // le nombre de chiffres maximumimal pour la taille (la taille d'un enregistrement ne peut pas déppaser 999 octet)
#define NbEtudiantMax 600 // nombre maximumimum des étudiants
#define NbClasseTotal 18  // de P1 à 51 (on design par 51 : année 5 , classe 1 )
#define b 300 // la taille du buffer
#define bArch 50 // la taille du buffer

//*******************************************************************************

//***************************** Les structures **********************************

//************ structures de l'enregistrement ************
typedef struct Classe{
    char annee[2] ; //2 pour éviter la fin de la chaine \0
    char numero[2] ; // Ex : classe 1 (numero = 1)
}Classe;

typedef struct Matiere_Note{
    char matiere[maximum] ; // Ex : matiere = Arabe
    char note[5] ; // Ex : note = 09
}Matiere_Note;

typedef struct Eleve{
    char numidentite[5] ;
    Classe classeidentite ;
    char nom[maximum] ;
    char prenom[maximum] ;
    char genre[2] ; //2 pour éviter la fin de la chaine \0
    Matiere_Note Tab_notes[8] ; // au maximum 8 matieres
}Eleve;
//********************************************************
//***************** structures de fichier ****************
typedef struct Tbloc{
    char tab[b] ;
}Tbloc;

typedef struct ENTETEF{
    int NbBloc ;
    int DernierPos ;
    int AnneeCourante ;
    int NbInsertion ;
}ENTETEF;
//*******************************************************
//****************** Structure d'indexs *****************
typedef struct Adresse{
int NumBloc ;
int Pos ;
}Adresse;
// ------------------------------------------------------------------------------------
typedef struct IndexIdEleve { // index dence pour les matricules des eleves
                              // utilisé pour la recherche dans les fonctions de
                              // suppression et mis a jours. et meme pour verifier
                              // si l'identifiant aleatoire est uniq
    int Id ;
    Adresse Adr ;
}IndexIdEleve;
typedef struct BufIndexId { // Pour stocker et récupèrer l'index à partire du fichier dans un seul accée
    IndexIdEleve table[NbEtudiantMax] ;
}BufIndexId;
// ------------------------------------------------------------------------------------

typedef struct IndexClasse { // index non dense contient le bloc et la position
                             // du premier étudiant dans la classe correspondente
                             // Ex : la classe P3 contient 10 étudiants, donc on
                             // sauvegarde dans l'index le clé P3 et leur adresse
                             // est le numero du bloc et la position du premier
                             // eleve parmis les 10

    char Idclasse[3] ;// Ex : 52 (5eme annee salle 2 )
    Adresse Adr ;
}IndexClasse;
typedef struct BufIndexClasse { // Pour stocker et récupèrer l'index à partire du fichier dans un seul accée
    IndexClasse table[NbClasseTotal] ; // le nombre total des classes ( P1,P2,...,52,53)
}BufIndexClasse;
// ------------------------------------------------------------------------
//****************************************************************************************
typedef struct String {
    char str[100] ;
}String;
typedef struct TabString {
    String tab[1000] ;
}TabString;
///***************************************************************************************
///***************************** Structures de l'archivage **********************************
// ***** Structure de l'index d'Archive ************
typedef struct IndexArchive{ // index dense basé sur les moyennes
    float moyenne ;
    Adresse adr ;
}IndexArchive;
/****/
typedef struct BufIndexArchive{
    IndexArchive tab[NbEtudiantMax] ;
}BufIndexArchive;
//--------------------------------------------------------------------------
typedef struct EleveArch{
    char nom[maximum] ;
    char prenom[maximum] ;
    int  numIdentifiant ;
    float  moyenne ;
}EleveArch;
// ------------------------------------------------------------------------
typedef struct TblocArch{
    EleveArch tab[bArch] ;
    float moyMin ;      //Moyenne min et max pour chaque bloc.
    float moyMax ;
}TblocArch;
// ------------------------------------------------------------------------
typedef struct ENTETEFARCH{   //L'entète pour le fichier d'archivage.
    int NbBloc ;
    int DernierPos ;
    int AnneeDeScolarisation ;
    int nbInsertion ;
}ENTETEFARCH;
///***************************************************************************************
//****************** Variables globales ******************
FILE *fichier , *fichier2 , *fichier3 ;
ENTETEF entete ;
Tbloc buffer , buffer2 , buffer3 ;
Eleve eleve ;
IndexIdEleve TabIdEleve[NbEtudiantMax] ;
IndexClasse TabClasse[NbClasseTotal] ;
ENTETEFARCH enteteArch;
TblocArch bufferArch;
//********************************************************

//***************************** FIN DE DECLARATIONS *****************************

void Ouvrire(FILE **fich , char nom_fich[maximum] , char mode) ;
void Fermer(FILE *fich) ;
void LireDir(FILE *fich , int i , Tbloc *buffer) ;
void EcrireDir(FILE *fich , int i , Tbloc buffer) ;
int  Entete(FILE *fich , int i) ;
void Aff_Entete(FILE *fich , int i , int val) ;
int nombreChiffres ( int nombre ) ;
int EcrireEnrgDansChaine( Eleve e , char chaine[b])  ;
void afficherEnreg(char chaine[maximum] , int NbmaximumCle , int j) ;
int tock(char chainesrc[10000] , char chainedest[1000] , char delemeteur , int position) ;
void afficherEnreg(char chaine[maximum] , int NbmaximumCle , int j) ;
int AleaNb(int Binf,int Bsup) ;
void AleaIdEleve(Eleve *eleve) ;
void AleaIdclasse(Eleve *eleve) ;
void GetNomPreGen(FILE *fich ,char chaine[maximum+3],int pos) ;
void Alea2Fich(Eleve *eleve) ;
void MatNoteFich(Eleve *eleve) ;
void RechDecIndexID(BufIndexId index , int cle , int *j , int *trouve , int nbinsertion) ;
void RechDecIndexClasse(BufIndexClasse index , char classe[3] , int *j , int *trouve) ;
void insertTabIndex(BufIndexId *bufId , int id , int bloc , int pos , int Nbinsertion) ;
int getTailleEleve(FILE *fich , Tbloc buffer , int indice , int bl) ;
void getClasse(FILE *fich , Tbloc buffer , int indice , int bl , char classe[3]) ;
int getNom(FILE *fich , Tbloc *buffer , int indice , int bl , char nom[maximum]) ;
int getPrenom(FILE *fich , Tbloc *buffer , int dernierpos , int bl , char prenom[maximum]) ;
void TriTableauString(TabString *tableau , int n) ;
int Existe(int ID[1000] , int n , int id) ;
void ChargementInitial(char nomfich[100] , int n , int AnneeCourante) ;
void affichertest(char nomfich[100]) ;
void RechercheInitial(Eleve e , int *trouve , int *bloc , int *pos) ;
char * strtoupper( char * dest , char * src ) ;
void remplirEtudiantAleatoire(Eleve *e) ;
void InsertionInitial(Eleve e) ;
void Mis_a_jour(char ficAnCour[maximum] ,char ficIndex[maximum],int annee,int id) ;
void SuppretionInitial(int id)  ;
void RechDecIndexArchive(BufIndexArchive bufIndArchive , float moyenne , int *trouve , int *j , int nbinsertion) ;
void InsertionIndexArchive(BufIndexArchive *bufIndArch , float moyenne , int bloc , int pos , int nbInsert) ;
void CreerIndexArchive(BufIndexArchive *bufIndArch , char nomfich[100] , int annee) ;
void OuvrireArch(FILE **fich , char nom_fich[maximum] , char mode) ;
void LireDirArch(FILE *fich , int i , TblocArch *bufferArch) ;
void EcrireDirArch(FILE *fich , int i , TblocArch bufferArchive) ;
int EnteteArch(FILE *fich , int i) ;
void Aff_EnteteArch(FILE *fich , int i , int val) ;
float CalculMoy (char ficTOVC[maximum],char ficIndex[maximum],int Id) ;
void ConstructionArchive(char FichierTOF[maximum],char fichierTOVC[maximum],char fichierIndexID[maximum],int anneeCourante) ;
void rechDecBufArchive(TblocArch bufferArchive , int id , int *j , int *trouve , int Nbmax) ;
void RechercheArchive(char nomfich[100] ,int id , int *trouve , int *bloc , int *pos) ;
void Simulation5Annee(int AnneeDebut,int NombreEleves) ;
void Lister(int n) ;
void InsertionArchive(char nomfich[100] , EleveArch e) ;
void Transfert(Eleve e , float moyenne) ;
void AfficherArchive(char nomfich[100]) ;
void AfficherArchiveParBloc(char nomfich[100]) ;
void RechercheSimulation(Eleve e , int *trouve , int *bloc , int *pos , int annee) ;
void InsertionSimulation(Eleve e , int annee) ;

#endif // BIBLIOTEQUE_H_INCLUDED
