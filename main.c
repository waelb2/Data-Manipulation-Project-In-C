#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <math.h>
#include "biblioteque.h"

//***************************** Les constantes **********************************
FILE *fichier ;
ENTETEF entete , sss ;
Tbloc buffer;
Eleve eleve ;
IndexIdEleve TabIdEleve[NbEtudiantMax] ;
IndexClasse TabClasse[NbClasseTotal] ;
ENTETEFARCH en ;
BufIndexArchive buf ;
//********************************************************

//***************************** FIN DE DECLARATIONS *****************************

int main()
{
    system("cls") ;
    int choix , x ;
    int trouve , bloc , pos , id , n;
    printf("******************************** BIENVENU DANS NOTRE PROGRAMME  GESTION DE SCOLARITE ********************************\n\n") ;
    do {
        printf(" *************************************************** Menu ***************************************************\n\n") ;
        printf("   1) Creation du fichier initial\n") ;
        printf("   2) Ajouter un eleve dans le fichier initial\n") ;
        printf("   3) Mise a jour d\'un eleve dans le fichier initial\n") ;
        printf("   4) Suppression d\'un eleve dans le fichier initial\n") ;
        printf("   5) Archiver\n") ;
        printf("   6) Simulation des 5 annees\n") ;
        printf("   7) Lister les eleves ayant obtenu une moyenne superieure a 12 sur les 5 annees\n") ;
        printf("   8) Lister les eleves ayant obtenu une moyenne superieure a 12 dans \'annee courante\n") ;
        printf("   9) Transfert d\'un eleve\n\n") ;
        printf("   --------------------------------- Pour l\'affichge ---------------------------------\n\n") ;
        printf("   10) Afficher le fichier initial(TOVC) caractere par caractere apres le chargement initial\n") ;
        printf("   11) Afficher le fichier Archive apres l\'archivage\n") ;
        printf("   12) Afficher les fichier d\'Archive des 5 annees apres la simulation\n") ;
        printf("   13) Afficher le fichier Archive apres l\'archivage par Bloc et par Position\n") ;
        printf("   ----------------------------------------------------------------------------------------\n\n") ;
        printf("   ----------------------------------------- Autre ----------------------------------------\n\n") ;
        printf("   14) Rechercher un eleve dans le fichier Archive du fichier initial\n") ;
        printf("   15) Afficher l\'index des moyennes du fichier d\'archive initial\n") ;
        printf("   ----------------------------------------------------------------------------------------\n") ;
        printf(" ******************************************************************************************************************\n") ;
        printf("   Donner votre choix : ") ;
        scanf("%d" , &choix) ;
        system("cls");
        if (choix == 1) {
            int si ;
            do {
                printf("\n\nRemarque : pour ne pas ecraser le contenu du fichier initial on doit supprimer l\'ancien fichier parceque il va etre cree avec le meme nom!!\ndonc vous devez dire est ce que vous avez deja creer le fichier initial ou non!\n\n") ;
                printf(" Si vous avez deja faire un chargement initial tappez 1 et si c\'est la premiere fois tappez 0 : ") ; scanf("%d" , &si) ;
            }while(si!=1 && si!=0) ;
            if (si == 1) {
                remove("FichierCourant") ;
                remove("fichierIndexClasse") ;
                remove("fichierIndexID") ;
                remove("IndexArchive2022") ;
                remove("Archive2022") ;
            }
            printf("\n\nOn va faire le chargement initial avec 300 eleve de maniere aleatoire : \n\n") ;
            ChargementInitial("FichierCourant" , 300 , 2022) ;
            printf("Le contenu du fichier initial TOVC est comme suit : (affichage caractere par caractere) \n\n") ;
            affichertest("FichierCourant") ;
            }else if (choix == 2) {
                InsertionInitial(eleve) ;
            }else if (choix == 3) {
                printf("\n\nDonner l\'identifiant de l\'eleve que vous devez faire la mis a jours : ") ;
                scanf("%d" , &id) ;
                Mis_a_jour("FichierCourant" , "fichierIndexID" , 2023 , id) ;
            }else if (choix == 4) {
                printf("\n\nDonner l\'identifiant de l\'etudiant : ") ;
                scanf("%d" , &id) ;
                SuppretionInitial(id) ;
            }else if (choix == 5) {
                int si ;
                do {
                    printf("\n\nRemarque : pour ne pas ecraser le contenu du fichier Archive du fichier initial on doit supprimer l\'ancien fichier parceque il va etre cree avec le meme nom!!\ndonc vous devez dire est ce que vous avez deja creer le fichier Archive ou non!\n\n") ;
                    printf("Si vous avez deja creer le fichier archive du fichier initial tappez 1 et si c\'est la premiere fois tappez 0 : ") ; scanf("%d" , &si) ;
                }while(si!=1 && si!=0) ;
                if (si == 1) {
                remove("Archive2022") ;
                remove("IndexArchive2022") ;
                remove("FichierCourant") ;
                remove("fichierIndexClasse") ;
                remove("fichierIndexID") ;
                }
                ChargementInitial("FichierCourant" , 300 , 2022);
                ConstructionArchive("Archive2022" , "FichierCourant" , "fichierIndexID" , 2022) ;
                CreerIndexArchive(&buf , "Archive2022" , 2022) ;
                AfficherArchive("Archive2022") ;
            }else if (choix == 6) {
                int si ;
                do {
                    printf("\n\nRemarque : pour ne pas ecraser le contenu des fichiers des simulations on doit supprimer les ancien fichiers parceque il vont etre cree avec le meme nom!!\n") ;
                    printf("donc vous devez dire est ce que vous avez deja faire la simulation des 5 annee ou non!\n\n") ;
                    printf(" Si vous avez deja faire la simulation des 5 annees tappez 1 et si c\'est la premiere fois tappez 0 : ") ; scanf("%d" , &si) ;
                }while(si!=1 && si!=0) ;
                if (si == 1) {
                    remove("Fichier2023") ;
                    remove("Fichier2024") ;
                    remove("Fichier2025") ;
                    remove("Fichier2026") ;
                    remove("FichierArch2023") ;
                    remove("FichierArch2024") ;
                    remove("FichierArch2025") ;
                    remove("FichierArch2026") ;
                    remove("IndexArchive2023") ;
                    remove("IndexArchive2024") ;
                    remove("IndexArchive2025") ;
                    remove("IndexArchive2026") ;
                    remove("fichierIndexID2023") ;
                    remove("fichierIndexID2024") ;
                    remove("fichierIndexID2025") ;
                    remove("fichierIndexID2026") ;
                    remove("fichierIndexClasse2023") ;
                    remove("fichierIndexClasse2024") ;
                    remove("fichierIndexClasse2025") ;
                    remove("fichierIndexClasse2026") ;
                }
                Simulation5Annee(2023 , 300) ;
                printf("\n\nResultat du simulation : \n\n") ;
                int annee = 2023 ;
                for (int i=1 ; i<=5 ; i++) {
                    char chaine[100] , chAnnee[5] ;
                    strcpy(chaine , "FichierArch") ;
                    itoa(annee , chAnnee , 10) ;
                    strcat(chaine , chAnnee) ;
                    AfficherArchive(chaine) ;
                    annee++ ;
                }
            }else if (choix == 7) {
                Lister(1) ;

            }else if (choix == 8) {
                ListerAnneeInitial() ;
            }else if (choix == 9) {
                float moy ;
                int j , annee , somme = 0 ;
                remplirEtudiantAleatoire(&eleve) ;
                printf("L\'identifiant : %s\n" , eleve.numidentite) ;
                printf("L\'annee de scolarisation : %s\n", eleve.classeidentite.annee) ;
                printf("Le numero de la salle : %s\n" , eleve.classeidentite.numero) ;
                printf("Le nom : %s\n" , eleve.nom) ;
                printf("Le prenom : %s\n" , eleve.prenom) ;
                printf("Le genre : %s\n" , eleve.genre) ;
                annee = atoi(eleve.classeidentite.annee) ;
                if ( eleve.classeidentite.annee[0] == 'P' || annee<=2 ) j = 4 ;
                else j = 8 ;
                for (int i=0 ; i<j ; i++) {
                    somme+=atoi(eleve.Tab_notes[i].note) ;
                }
                moy = ((float)somme)/j ;
                Transfert(eleve , moy) ;
            }else if (choix == 10){
                printf("\n") ;
                affichertest("FichierCourant") ;
            }else if(choix == 11) {
                printf("\n") ;
                AfficherArchive("Archive2022") ;
            }else if(choix == 12) {
                printf("\n") ;
                int annee = 2022 ;
                for (int i=1 ; i<=5 ; i++) {
                    char chaine[100] , chAnnee[5] ;
                    strcpy(chaine , "Archive") ;
                    itoa(annee , chAnnee , 10) ;
                    strcat(chaine , chAnnee) ;
                    AfficherArchive(chaine) ;
                    annee++ ;
                }
            }else if (choix == 13) {
                printf("\n") ;
                AfficherArchiveParBloc("Archive2022") ;
            }else if (choix == 14) {
                EleveArch etudiant ;
                printf("\n\n") ;
                printf("Donner l\'idantifiant de l\'etudiant (de 0 a 9999) : ") ; scanf("%d" , &etudiant.numIdentifiant) ;
                RechercheArchive("Archive2022" , etudiant.numIdentifiant , &trouve , &bloc , &pos) ;
                if (trouve) printf("L\'etudiant existe dans le bloc %d dans la position %d\n\n" , bloc , pos) ;
                else printf("L\'etudiant n\'existe pas!. Il doit etre insere dans le bloc %d dans la position %d\n\n" , bloc , pos) ;
            }else if (choix == 15) {
                fichier = fopen("IndexArchive2022" , "rb") ;
                if (fichier == NULL) printf("\n\n ********** VOUS DEVEZ CONCSTRUIRE LE FICHIER ARCHIVE!! *********\n\n") ;
                else {
                    fread(&buf , sizeof(BufIndexArchive) , 1 , fichier) ;
                    OuvrireArch(&fichier2 , "Archive2022" , 'A') ;
                    n = EnteteArch(fichier2 , 4) ;
                    printf("\n\n ************************************ L\'index des moyennes du fichier Archive ************************************\n\n") ;
                    for (int i=0 ; i<n ; i++) {
                        printf("  > case %d\t:\t  moyenne = %.2f\t  \t   Bloc = %d\t  \t   Pos = %d\n" , i , buf.tab[i].moyenne , buf.tab[i].adr.NumBloc , buf.tab[i].adr.Pos) ;
                    }
                    Fermer(fichier2) ;
                    Fermer(fichier) ;
                }
            }else printf("\n\nLe choix est incorrecte!!\n\n") ;
        printf("\n     si vous voulez quitter le programme tappez 0 et si vous voulez repeter le programme tapez 1 : ") ;
        scanf("%d" , &x) ;
        printf("\n\n") ;
    }while (x != 0) ;
    return 0 ;
}
