/** CE PROGRAMME RASSSEMBLE TOUTES LES FONCTIONS NECESSAIRES
 *  AU FONCTIONNEMENT DU JEU 2048 BASIQUE. TOUTES LES EXTENSIONS
 *  SERONT GERES DANS UN SECOND FICHIER

 *  LES TESTS SONT GERES DANS UN AUTRE FICHIER
 **/


/** LES FONCTIONS SONT RANGES PAR THEME DANS CET ORDRE :
        -- AFFICHAGES
        -- DEPLACEMENTS
        -- VERIFICATIONS DE SITUATIONS
        -- RANDOM SPAWN (aleatoires)
        -- INITIALISATION DU JEU
        -- AFFICHAGE DU JEU ET PRISE DE DECISIONS

**/





#include <ncurses.h>	// ncurses, couleur et utilisation des flèches
#include <fstream>      // ifstream, ofstream
#include <iostream>     // cin, cout
#include <vector>
#include <iomanip>      // setw, fulfill
#include <ctime>        // srand( time(0) ) ;
#include <cstdlib>      // rand
using namespace std;
typedef vector< vector<int> > Matrice;

// PENSER A METTRE "srand(time(0))" dans main();

#include "fonctionsStructureMinimale.h"










/*************************************/

//      ---- AFFICHAGES ----

void afficheCase(int valeurCase) {
		// paramétrage des couleurs
	init_pair(1, COLOR_WHITE, COLOR_RED);
	init_pair(2, COLOR_WHITE, COLOR_MAGENTA);
	init_pair(3, COLOR_WHITE, COLOR_YELLOW);
	init_pair(4, COLOR_WHITE, COLOR_GREEN);
	init_pair(5, COLOR_WHITE, COLOR_CYAN);
	init_pair(6, COLOR_WHITE, COLOR_BLUE);
	init_pair(7, COLOR_BLACK, COLOR_WHITE);
	
		// Affichage au cas par cas
	if( valeurCase == 0 ) {
		printw("     ");
	} else {
	if( valeurCase == 2 ) {				// 2
		attron( COLOR_PAIR(1) );
		printw("  2  ");
		attroff( COLOR_PAIR(1) );
	} else {
	if( valeurCase == 4 ) {				// 4
		attron( COLOR_PAIR(2) );
		printw("  4  ");
		attroff( COLOR_PAIR(2) );
	} else {
	if( valeurCase == 8 ) {				// 8
		attron( COLOR_PAIR(3) );
		printw("  8  ");
		attroff( COLOR_PAIR(3) );
	} else {
	if( valeurCase == 16 ) {			// 16
		attron( COLOR_PAIR(4) );
		printw("  16 ");
		attroff( COLOR_PAIR(4) );
	} else {
	if( valeurCase == 32 ) {			// 32
		attron( COLOR_PAIR(5) );
		printw("  32 ");
		attroff( COLOR_PAIR(5) );
	} else {
	if( valeurCase == 64 ) {			// 64
		attron( COLOR_PAIR(6) );
		printw("  64 ");
		attroff( COLOR_PAIR(6) );
	} else {
	if( valeurCase == 128 ) {			// 128
		attron( COLOR_PAIR(7) );
		printw(" 128 ");
		attroff( COLOR_PAIR(7) );
	} else {
	if( valeurCase == 256 ) {			// 256
		attron( COLOR_PAIR(1) );
		printw(" 256 ");
		attroff( COLOR_PAIR(1) );
	} else {
	if( valeurCase == 512 ) {			// 512
		attron( COLOR_PAIR(2) );
		printw(" 512 ");
		attroff( COLOR_PAIR(2) );
	} else {
	if( valeurCase == 1024 ) {			// 1024
		attron( COLOR_PAIR(3) );
		printw(" 1024");
		attroff( COLOR_PAIR(3) );
	} else {
	if( valeurCase == 2048 ) {			// 2048
		attron( COLOR_PAIR(4) );
		printw(" 2048");
		attroff( COLOR_PAIR(4) );
	} else {
		printw("Erreur :Valeur de la case incorrect");
	} } } } } } } } }  } } } // !! Cette ligne peut entraîner des erreurs
					  // si il n'y a pas le bon nombre d'accolades
}


void afficheLigne(Matrice plateau, int ligne){
	printw("|");
	afficheCase( plateau[ligne][0] );
	printw("|");
	afficheCase( plateau[ligne][1] );
	printw("|");
	afficheCase( plateau[ligne][2]) ;
	printw("|");
	afficheCase( plateau[ligne][3] );
	printw("|\n"); //retour à la ligne
}

void affichePlateau(Matrice plateau) {
	char const *ligneSeparation = "+-----------------------+\n" ; //initialise la ligne de séparation
	mvprintw(1, (COLS/2) - (25/2), ligneSeparation) ; // Centre le plateau à la deuxième ligne
	move(2, (COLS/2) - (25/2)) ;
	afficheLigne(plateau, 0);
	mvprintw(3, (COLS/2) - (25/2), ligneSeparation) ;
	move(4, (COLS/2) - (25/2)) ;
	afficheLigne(plateau, 1);
	mvprintw(5, (COLS/2) - (25/2), ligneSeparation) ;
	move(6, (COLS/2) - (25/2)) ;
	afficheLigne(plateau, 2);
	mvprintw(7, (COLS/2) - (25/2), ligneSeparation) ;
	move(8, (COLS/2) - (25/2)) ;
	afficheLigne(plateau, 3);
	mvprintw(9, (COLS/2) - (25/2), ligneSeparation) ;
	refresh();
	
	move(11,15); //l'affichage du score se fait sous le tableau avec une marge gauche
	attron(A_REVERSE);
	printw(" SCORE : %d ", plateau[4][0]) ;
	attroff(A_REVERSE);
	move(13,0) ; //prépare le prochain affichage
}



void afficheCommandes(){
	
	move(13,0);		//affichage juste sous le plateau
	printw("Ctrl+C : Quitter \n") ;
	printw("R : Restart \n \n") ;
	printw("Utiliser les fleches pour se deplacer") ;
	move(17,0);

}
















/*************************************/

//      ---- DEPLACEMENTS ----

// --- MOUVEMENTS PARTIELS ---

Matrice deplacementPartielHaut(Matrice plateau) {
    for (int k=0 ; k<3 ; k++) { // L'opération se répète 3 fois pour être sûr qu'une case du bas monte tout en haut
        for (int i=0 ; i<3 ; i++) { // Sur les 3 premières lignes uniquement
            for (int j=0 ; j<4 ; j++) {
                if(plateau[i][j] == 0) { // Si case vide, elle est remplacée par celle du dessous
                    plateau[i][j] = plateau[i+1][j];
                    plateau[i+1][j] = 0;
                } else { }
            }
        }
    }
    return plateau;
}

Matrice deplacementPartielDroite(Matrice plateau) {
    for (int k=0 ; k<3 ; k++) { // L'opération se répète 3 fois
        for (int i=0 ; i<4 ; i++) {
            for (int j=3 ; j>0 ; j--) { // On part de la dernière colonne jusqu'à la deuxième
                if(plateau[i][j] == 0) { // Si case vide, elle est remplacée par celle de gauche
                    plateau[i][j] = plateau[i][j-1];
                    plateau[i][j-1] = 0;
                } else { }
            }
        }
    }
    return plateau;
}

Matrice deplacementPartielBas(Matrice plateau) {
    for (int k=0 ; k<3 ; k++) { // L'opération se répète 3 fois
        for (int i=3 ; i>0 ; i--) { // On part de la dernière ligne jusqu'à la deuxième
            for (int j=0 ; j<4 ; j++) {
                if(plateau[i][j] == 0) { // Si case vide, elle est remplacée par celle du dessus
                    plateau[i][j] = plateau[i-1][j];
                    plateau[i-1][j] = 0;
                } else { }
            }
        }
    }
    return plateau;
}

Matrice deplacementPartielGauche(Matrice plateau) {
    for (int k=0 ; k<3 ; k++) { // L'opération se répète 3 fois
        for (int i=0 ; i<4 ; i++) {
            for (int j=0 ; j<3 ; j++) { // De la première à la dernière colonne
                if(plateau[i][j] == 0) { // Si case vide, elle est remplacée par celle de gauche
                    plateau[i][j] = plateau[i][j+1];
                    plateau[i][j+1] = 0;
                } else { }
            }
        }
    }
    return plateau;
}


// --- FUSION ---

Matrice fusionHaut(Matrice plateau) {
    int launchscan = 0;
    for (int i=0 ; i<3 ; i++) { // Sur les 3 premières lignes uniquement
        for (int j=0 ; j<4 ; j++) {
            if(plateau[i][j] == plateau[i+1][j]) { // Si case identique à celle du dessous, fusion des deux
                plateau[i][j] *= 2;
				plateau[4][0] += plateau[i][j];	// Augmente le score
                plateau[i+1][j]= 0;
                launchscan = 1;
            } else { }
        }
    }
    if (launchscan==1) { plateau = deplacementPartielHaut(plateau) ; } // remonte les cases si nécessaires
    else {} // else sans utilité, simplement pour plus de clareté
    return plateau;
}

Matrice fusionDroite(Matrice plateau) {
    int launchscan = 0;
    for (int i=0 ; i<4 ; i++) {
        for (int j=3 ; j>0 ; j--) { // Depuis la dernière jusqu'à la 2nd colonne
            if(plateau[i][j] == plateau[i][j-1]) { // Si case identique, fusion des deux
                plateau[i][j] *= 2;
				plateau[4][0] += plateau[i][j];	// Augmente le score
                plateau[i][j-1]= 0;
                launchscan = 1;
            } else { }
        }
    }
    if (launchscan==1) { plateau = deplacementPartielDroite(plateau) ; } // Bouger les cases ssi nécessaires
    else { }
    return plateau;
}

Matrice fusionBas(Matrice plateau) {
    int launchscan = 0;
    for (int i=3 ; i>0 ; i--) { // Depuis la dernière jusqu'à la 2nd ligne
        for (int j=0 ; j<4 ; j++) {
            if(plateau[i][j] == plateau[i-1][j]) { // Si case identique, fusion des deux
                plateau[i][j] *= 2;
				plateau[4][0] += plateau[i][j];	// Augmente le score
                plateau[i-1][j]= 0;
                launchscan = 1 ;
            } else { }
        }
    }
    if (launchscan==1) { plateau = deplacementPartielBas(plateau) ; } // Bouger les cases ssi nécessaires
    else {}
    return plateau;
}

Matrice fusionGauche(Matrice plateau) {
    int launchscan = 0;
    for (int i=0 ; i<4 ; i++) {
        for (int j=0 ; j<4 ; j++) { // Depuis la dernière jusqu'à la 2nd colonne
            if(plateau[i][j] == plateau[i][j+1]) { // Si case identique, fusion des deux
                plateau[i][j] *= 2;
				plateau[4][0] += plateau[i][j];	// Augmente le score
                plateau[i][j+1]= 0;
                launchscan = 1;
            } else { }
        }
    }
    if (launchscan==1) { plateau = deplacementPartielGauche(plateau) ; } // Bouger les cases ssi nécessaires
    else {}
    return plateau;
}








/*************************************/

// --- MOUVEMENTS COMPLETS ---

Matrice deplacementHaut(Matrice plateau) {
    if ( mouvmtPossibleHaut(plateau) ) {
        plateau = deplacementPartielHaut(plateau);
        plateau = fusionHaut(plateau) ;
    }
    return plateau;
}

Matrice deplacementDroite(Matrice plateau) {
    if ( mouvmtPossibleDroite(plateau) ) {
        plateau = deplacementPartielDroite(plateau);
        plateau = fusionDroite(plateau) ;
    }
    return plateau;
}

Matrice deplacementBas(Matrice plateau) {
    if ( mouvmtPossibleBas(plateau) ) {
        plateau = deplacementPartielBas(plateau);
        plateau = fusionBas(plateau) ;
    }
    return plateau;
}

Matrice deplacementGauche(Matrice plateau) {
    if ( mouvmtPossibleGauche(plateau) ) {
        plateau = deplacementPartielGauche(plateau);
        plateau = fusionGauche(plateau) ;
    }
    return plateau;
}





















/*************************************/

//      ---- VERIFICATIONS DE SITUATIONS ----

// --- MOUVEMENT POSSIBLES ? ---

bool mouvmtPossibleHaut(Matrice plateau) {
    for (int i=1 ; i<4 ; i++) { //i=1 car la première ligne ne peut pas être testée
        for (int j=0 ; j<4 ; j++) {
            if (plateau[i][j] == plateau[i-1][j] and plateau[i][j] != 0) {
                return true;
            } else {
                if (plateau[i-1][j] == 0 and plateau[i][j] != 0) {
                    return true; } else {} //le else n'a pas d'utilité
            }
        }
    } return false ;
}

bool mouvmtPossibleBas(Matrice plateau) {
    for (int i=0 ; i<3 ; i++) { 
        for (int j=0 ; j<4 ; j++) {
            if (plateau[i][j] == plateau[i+1][j] and plateau[i][j] != 0) {
                return true;
            } else {
                if (plateau[i][j] != 0 and plateau[i+1][j] == 0) {
                    return true; } else {} //le else n'a pas d'utilité
            }
        }
    } return false ;
}

bool mouvmtPossibleDroite(Matrice plateau) {
    for (int i=0 ; i<4 ; i++) {
        for (int j=0 ; j<3 ; j++) { //j<3 et non 4 car la dernière colonne n'est pas testée
            if (plateau[i][j] == plateau[i][j+1] and plateau[i][j] != 0) {
                return true ;
            } else {
                if (plateau[i][j] != 0 and plateau[i][j+1] == 0) {
                    return true; }
            }
        }
    } return false;
}

bool mouvmtPossibleGauche(Matrice plateau) {
    for (int i=0 ; i<4 ; i++) {
        for (int j=3 ; j>0 ; j--) { //j<3 et non 4 car la dernière colonne n'est pas testée
            if (plateau[i][j] == plateau[i][j-1] and plateau[i][j] != 0) {
                return true ;
            } else {
                if (plateau[i][j] != 0 and plateau[i][j-1] == 0) {
                    return true; }
            }
        }
    } return false;
}


// --- TEST DE SITUATIONS ---

bool estBloque(Matrice plateau) {
    if ( mouvmtPossibleHaut(plateau) or mouvmtPossibleDroite(plateau) or mouvmtPossibleBas(plateau) or mouvmtPossibleGauche(plateau) ){
        return false;
    } else {
        return true; }
}

bool estGagne(Matrice plateau) {
    for (int i=0; i<4 ; i++) {
        for (int j=0 ; j<4 ; j++) {
            if ( plateau[i][j] >= 2048) {
                return true;
            }
        }
    }
    return false;
}

bool grillePleine(Matrice plateau){
    for (int i=0 ; i<4 ; i++) {
        for (int j=0 ; j<4 ; j++) {
            if (plateau[i][j] > 0) {}
            else { return false ; } // false si une case est vide
        }
    }
    return true;
}


















/*************************************/

// --- RANDOM SPAWN ---


float aleat(){
    float x = rand();
    return x;
}



bool eventProba1surN(float n) {
    // Un place x aléatoirement dans un intervalle entre 0 et n
    float x = rand() * n / (double)RAND_MAX ;
    if (x <= 1) {
        return true;
    } else {
    return false; }
}

int numCasePrSpawn(int n){
	int numCase;
	numCase = rand() % (n-1) - 1; //prend un nbr aleat entre 1 et n
	return numCase;
}

int nbrCasesVides(Matrice plateau){
    int compteur=0;
    for (int i=0 ; i<4 ; i++) {
        for (int j=0 ; j<4 ; j++) {
            if ( plateau[i][j] == 0) {
                compteur++;
            }
        }
    }
    return compteur;
}

int deuxOuQuatre(){
    if ( eventProba1surN(10) ) {
        return 4;
    } else {
    return 2 ;}
}


Matrice randomspawn(Matrice plateau){
    int nbrQuiSpawn = deuxOuQuatre() ; // choisi entre 2 et 4
    int casesVides = nbrCasesVides(plateau) ;
	int numCase = numCasePrSpawn( casesVides ) ;
    int confirmation=0;
    //while (confirmation == 0) {
        for (int i=0 ; i<4 ; i++) {     // Balaye le plateau à la recherche de cases vides
            for (int j=0 ; j<4 ; j++) {
                if ( plateau[i][j] == 0) { //Si la case correspond à notre numéro
                    if ( plateau[i][j] == numCase ) {    // Si l'event est validé
                        plateau[i][j] = nbrQuiSpawn ; // On assigne le nombre à la case
                        return plateau;
                        confirmation++; //inutile, juste au cas où, pour éviter un problème avec une boucle infinie
                    }
                }
            }
        }
   //}
}











/*************************************/

// --- INITIALISATION DU JEU ---


Matrice plateauVide(){
    Matrice m;
    m = { {0,0,0,0} , {0,0,0,0} , {0,0,0,0} , {0,0,0,0} , {0} };
    return m;
}

Matrice plateauInitial(Matrice plateau){
    plateau = plateauVide();
    plateau = randomspawn(plateau);
    plateau = randomspawn(plateau);
    return plateau;
}



/*************************************/

// --- AFFICHAGE DU JEU ET PRISE DE DECISION ---

void affichageJeu(Matrice plateau){

    affichePlateau(plateau) ;
	
	afficheCommandes();

}

bool commandeVerifier(int commande) {
    if (commande!=114 and commande!=258 and commande!=259 and commande!=260 and commande!=261) { // commande incorrecte
        return false;
    } else {
    return true;
    }
}

Matrice commandeExecuter(int commande, Matrice plateau) {
            // -- RESTART --
    if (commande==114) {
        plateau = plateauInitial(plateau);
        jouerUnCoup(plateau) ;
		mvprintw(18, 10, "Le jeu a ete relance. Enjoy :p") ;
        return plateau;
    } else {

            // -- HAUT --
    if (commande==259) {
        if ( not mouvmtPossibleHaut(plateau) ) {
            jouerUnCoup(plateau) ;
			mvprintw(18, 10, "Mouvement impossible") ;
            return plateau;
        } else {
        plateau = deplacementHaut(plateau);
        plateau = randomspawn(plateau);
        return plateau;
        }
    }

                // -- DROITE --
    if (commande==261) {
        if ( not mouvmtPossibleDroite(plateau) ) {
            jouerUnCoup(plateau) ;
			mvprintw(18, 10, "Mouvement impossible") ;
            return plateau;
        } else {
        plateau = deplacementDroite(plateau);
        plateau = randomspawn(plateau);
        return plateau;
        }
    }

            // -- Bas --
    if (commande==258) {
        if ( not mouvmtPossibleBas(plateau) ) {
            jouerUnCoup(plateau) ;
			mvprintw(18, 10, "Mouvement impossible") ;
            return plateau;
        } else {
        plateau = deplacementBas(plateau);
        plateau = randomspawn(plateau);
        return plateau;
        }
    }

                // -- GAUCHE --
    if (commande==260) {
        if ( not mouvmtPossibleGauche(plateau) ) {
            jouerUnCoup(plateau) ;
			mvprintw(18, 10, "Mouvement impossible") ;
            return plateau;
        } else {
        plateau = deplacementGauche(plateau);
        plateau = randomspawn(plateau);
        return plateau;
        }
    }

    }
}


Matrice testsDeJeu(Matrice plateau) {

    if ( estGagne(plateau) ) {
		jouerUnCoup(plateau) ;
		mvprintw(18, 10, "OUE C GAGNEEEE... On recommence ? Appuyer sur R pour Restart") ;
        return plateau;
    } else {
    if ( estBloque(plateau) ) {
		partiePerdue();
		return plateau;
    } else {
    return plateau;}

    }

}










