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
		printw("Erreur: Valeur de case incorrecte");
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

void affichePlateau(struct jeuGlobal jeu) {
	char const *ligneSeparation = "+-----------------------+\n" ; //initialise la ligne de séparation
	mvprintw(1, (COLS/2) - (25/2), ligneSeparation) ; // Centre le plateau à la deuxième ligne
	move(2, (COLS/2) - (25/2)) ;
	afficheLigne(jeu.plateau, 0);
	mvprintw(3, (COLS/2) - (25/2), ligneSeparation) ;
	move(4, (COLS/2) - (25/2)) ;
	afficheLigne(jeu.plateau, 1);
	mvprintw(5, (COLS/2) - (25/2), ligneSeparation) ;
	move(6, (COLS/2) - (25/2)) ;
	afficheLigne(jeu.plateau, 2);
	mvprintw(7, (COLS/2) - (25/2), ligneSeparation) ;
	move(8, (COLS/2) - (25/2)) ;
	afficheLigne(jeu.plateau, 3);
	mvprintw(9, (COLS/2) - (25/2), ligneSeparation) ;
	refresh();
	
		//On va chercher la valeur du highscore
	ifstream highscore_file("Highscore") ;
	int highscore;
	highscore_file >> highscore;
	highscore_file.close(); //On ferme le fichier

		//l'affichage du score se fait sous le tableau avec une marge gauche
	attron(A_REVERSE); 			// Permet d'écrire Noir sur Blanc
	mvprintw(11,15, " SCORE : %d ", jeu.score) ;
	mvprintw(12,15, " HIGHSCORE : %d ", highscore) ;
	attroff(A_REVERSE);			// Désactive le noir sur blanc
	move(14,0) ; //prépare le prochain affichage
	
}



void afficheCommandes(){
		//Le move ci-dessous est désactivé car il est géré par la fonction
		//affichePlateau, voire quelques lignes plus haut
	//move(14,0);	
	printw("Ctrl+C : Quitter \n") ;
	printw("R : Restart \n") ;
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

struct jeuGlobal fusionHaut(struct jeuGlobal jeu) {
    int launchscan = 0;
    for (int i=0 ; i<3 ; i++) { // Sur les 3 premières lignes uniquement
        for (int j=0 ; j<4 ; j++) {
            if(jeu.plateau[i][j] == jeu.plateau[i+1][j]) { // Si case identique à celle du dessous, fusion des deux
                jeu.plateau[i][j] *= 2;
				jeu.score += jeu.plateau[i][j];	// Augmente le score
                jeu.plateau[i+1][j]= 0;
                launchscan = 1;
            } else { }
        }
    }
    if (launchscan==1) { jeu.plateau = deplacementPartielHaut(jeu.plateau) ; } // remonte les cases si nécessaires
    else {} // else sans utilité, simplement pour plus de clareté
	chargementHighscore(jeu.score) ; // Enregistre le score dans highscore si le meilleur score est battu
    return jeu;
}

struct jeuGlobal fusionDroite(struct jeuGlobal jeu) {
    int launchscan = 0;
    for (int i=0 ; i<4 ; i++) {
        for (int j=3 ; j>0 ; j--) { // Depuis la dernière jusqu'à la 2nd colonne
            if(jeu.plateau[i][j] == jeu.plateau[i][j-1]) { // Si case identique, fusion des deux
                jeu.plateau[i][j] *= 2;
				jeu.score += jeu.plateau[i][j];	// Augmente le score
                jeu.plateau[i][j-1]= 0;
                launchscan = 1;
            } else { }
        }
    }
    if (launchscan==1) { jeu.plateau = deplacementPartielDroite(jeu.plateau) ; } // Bouger les cases ssi nécessaires
    else { }
	chargementHighscore(jeu.score) ; // Enregistre le score dans highscore si le meilleur score est battu
    return jeu;
}

struct jeuGlobal fusionBas(struct jeuGlobal jeu) {
    int launchscan = 0;
    for (int i=3 ; i>0 ; i--) { 
        for (int j=0 ; j<4 ; j++) {
            if(jeu.plateau[i][j] == jeu.plateau[i-1][j]) { // Si case identique, fusion des deux
                jeu.plateau[i][j] *= 2;
				jeu.score += jeu.plateau[i][j];	// Augmente le score
                jeu.plateau[i-1][j]= 0;
                launchscan = 1 ;
            } else { }
        }
    }
    if (launchscan==1) { jeu.plateau = deplacementPartielBas(jeu.plateau) ; } // Bouger les cases ssi nécessaires
    else {}
	chargementHighscore(jeu.score) ; // Enregistre le score dans highscore si le meilleur score est battu	
    return jeu;
}

struct jeuGlobal fusionGauche(struct jeuGlobal jeu) {
    int launchscan = 0;
    for (int i=0 ; i<4 ; i++) {
        for (int j=0 ; j<3 ; j++) { 
            if(jeu.plateau[i][j] == jeu.plateau[i][j+1]) { // Si case identique, fusion des deux
                jeu.plateau[i][j] *= 2;
				jeu.score += jeu.plateau[i][j];	// Augmente le score
                jeu.plateau[i][j+1]= 0;
                launchscan = 1;
            } else { }
        }
    }
    if (launchscan==1) { jeu.plateau = deplacementPartielGauche(jeu.plateau) ; } // Bouger les cases ssi nécessaires
    else {}
	chargementHighscore(jeu.score) ; // Enregistre le score dans highscore si le meilleur score est battu
    return jeu;
}













/*************************************/

// --- MOUVEMENTS COMPLETS ---

struct jeuGlobal deplacementHaut(struct jeuGlobal jeu) {
    if ( mouvmtPossibleHaut(jeu.plateau) ) {
        jeu.plateau = deplacementPartielHaut(jeu.plateau);
        jeu = fusionHaut(jeu) ;
    }
    return jeu;
}

struct jeuGlobal deplacementDroite(struct jeuGlobal jeu) {
    if ( mouvmtPossibleDroite(jeu.plateau) ) {
        jeu.plateau = deplacementPartielDroite(jeu.plateau);
        jeu = fusionDroite(jeu) ;
    }
    return jeu;
}

struct jeuGlobal deplacementBas(struct jeuGlobal jeu) {
    if ( mouvmtPossibleBas(jeu.plateau) ) {
        jeu.plateau = deplacementPartielBas(jeu.plateau);
        jeu = fusionBas(jeu) ;
    }
    return jeu;
}

struct jeuGlobal deplacementGauche(struct jeuGlobal jeu) {
    if ( mouvmtPossibleGauche(jeu.plateau) ) {
        jeu.plateau = deplacementPartielGauche(jeu.plateau);
        jeu = fusionGauche(jeu) ;
    }
    return jeu;
}



// --- ECRITURE DU HIGHSCORE DANS UN FICHIER EXTERNE ---

void chargementHighscore(int scoretemp) {
		
		//On va chercher la valeur du highscore
	ifstream highscore_file("Highscore") ;
	int highscoretemp;
	highscore_file >> highscoretemp;
	highscore_file.close(); //On ferme le fichier

	if (highscoretemp < scoretemp) {
		ofstream highscore_file("Highscore") ; //Nom utilisable car il a déjà été close avant
		highscore_file << scoretemp;	// On écrit le score actuel dans le fichier, ça le remplace
		highscore_file.close(); // fermeture
	} else {}
	
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
    if ( mouvmtPossibleHaut(plateau) or mouvmtPossibleDroite(plateau) or mouvmtPossibleGauche(plateau) or mouvmtPossibleBas(plateau) ){
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
	numCase = rand() % n + 1; //prend un nbr aleat entre 1 et n
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
	int numCase = numCasePrSpawn( casesVides ) ; //Détermine quelle case va 
    int numCompteur=0; 
	for (int i=0 ; i<4 ; i++) {     // Balaye le plateau à la recherche de cases vides
		for (int j=0 ; j<4 ; j++) { 
			if ( plateau[i][j] == 0) {  //Trouve une case vide
				numCompteur++;
				if (numCompteur == numCase) {// Si c'est la bonne case
					plateau[i][j] = nbrQuiSpawn ; // On assigne le nombre à la case
					return plateau;
				} 
			} 
		} 
	} 
	return plateau; //inutile, mais au cas où
} 











/*************************************/

// --- INITIALISATION DU JEU ---


Matrice plateauVide(){
    Matrice m;
    m = { {0,0,0,0} , {0,0,0,0} , {0,0,0,0} , {0,0,0,0} };
    return m;
}

struct jeuGlobal plateauInitial(struct jeuGlobal jeu){
    jeu.plateau = plateauVide();
	jeu.score = 0;
    jeu.plateau = randomspawn(jeu.plateau);
    jeu.plateau = randomspawn(jeu.plateau);
    return jeu;
}



/*************************************/

// --- AFFICHAGE DU JEU ET PRISE DE DECISION ---

void affichageJeu(struct jeuGlobal jeu){

    affichePlateau(jeu) ;
	
	afficheCommandes();

}

bool commandeVerifier(int commande) {
    if (commande!=114 and commande!=258 and commande!=259 and commande!=260 and commande!=261) { // commande incorrecte
        return false;
    } else {
    return true;
    }
}

struct jeuGlobal commandeExecuter(int commande, struct jeuGlobal jeu) {
            // -- RESTART --
    if (commande==114) {
        jeu = plateauInitial(jeu);
		mvprintw(18, 10, "Le jeu a ete relance. Enjoy :p") ;
        return jeu;
    }  else {

            // -- HAUT --
    if (commande==259) { 
        if ( not mouvmtPossibleHaut(jeu.plateau) ) { 
			mvprintw(18, 10, "Mouvement impossible") ;
            return jeu;
         } else { 
        jeu = deplacementHaut(jeu);
        jeu.plateau = randomspawn(jeu.plateau);
        return jeu;
         }
    }

                // -- DROITE --
    if (commande==261) {
        if ( not mouvmtPossibleDroite(jeu.plateau) ) {
			mvprintw(18, 10, "Mouvement impossible") ;
            return jeu;
        } else {
        jeu = deplacementDroite(jeu);
        jeu.plateau = randomspawn(jeu.plateau);
        return jeu;
        }
    }

            // -- Bas --
    if (commande==258) {
        if ( not mouvmtPossibleBas(jeu.plateau) ) {
			mvprintw(18, 10, "Mouvement impossible") ;
            return jeu;
        } else {
        jeu = deplacementBas(jeu);
        jeu.plateau = randomspawn(jeu.plateau);
        return jeu;
        }
    }

                // -- GAUCHE --
    if (commande==260) {
        if ( not mouvmtPossibleGauche(jeu.plateau) ) {
			mvprintw(18, 10, "Mouvement impossible") ;
            return jeu;
        } else {
        jeu = deplacementGauche(jeu);
        jeu.plateau = randomspawn(jeu.plateau);
        return jeu;
        }
    }

    }  return jeu;
}


struct jeuGlobal testsDeJeu(struct jeuGlobal jeu) {

    if ( estGagne(jeu.plateau) ) {
				//On affiche le plateau gagnant
		clear();
		affichageJeu(jeu);

		mvprintw(18, 10, "OUE C GAGNEEEE... On recommence ? Appuyer sur R pour Restart") ;
		
			//On demande d'appuyer sur R
		int c=0;
		while (c != 114) {
			c = getch();
		}
		clear();
		mvprintw(18, 10, "Le jeu a ete relance. Enjoy :p") ;

			//On prépare un jeu relancé
		jeu = plateauInitial(jeu) ;

        return jeu;
    } else {
    if ( estBloque(jeu.plateau) ) {
			//On affiche le plateau perdant
		clear();
		affichageJeu(jeu);
		mvprintw(18,10, "Partie perdue... :'( Appuyer sur R pour relancer une partie.") ;
		
			//On demande d'appuyer sur R
		int c=0;
		while (c != 114) {
			c = getch();
		}
		clear();
		mvprintw(18, 10, "Le jeu a ete relance. Enjoy :p") ;

			//On prépare un jeu relancé
		jeu = plateauInitial(jeu) ;

		return jeu;
    } else {
		//Si la partie est ni perdue ni gagné, on fait rien
    return jeu;}

    }

}










