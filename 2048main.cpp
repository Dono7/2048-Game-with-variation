#include <ncurses.h>	// ncurses, couleur et utilisation flèche
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


void partiePerdue(){
	mvprintw(18,10, "Partie perdue... Appuyer sur R pour relancer une partie.") ;
	int c=0;
	while (c != 114) {
		c = getch();
	}
	Matrice plateau = plateauVide() ;
	plateau = plateauInitial(plateau) ;
	mvprintw(18, 10, "Partie relancée ! Bonne chance. :) ") ;
	jouerUnCoup(plateau) ;
	
}


Matrice jouerUnCoup(Matrice plateau) {
	int commande ; 

		//affiche le plateau de jeu, score et msg d'erreur/de fin
	clear();
	affichageJeu(plateau); 
	//mvprintw(18, 10, commentaire) ; 	FAIT PARTIE DE L'ANCIENNE VERSION
	refresh();
	
	//Demande la commande
	cin >> commande ; 
	commande = getch();
	// R:114, Bas/Haut/Gauche/droite : 258 a 261
	
	if ( not commandeVerifier(commande) ) { 
        mvprintw(18,10,"Commande invalide"); 
    } else { 
	plateau = commandeExecuter(commande, plateau); 
		//mvprintw(17,17,"CommandeExecuter fait");
		//getch();
	plateau = testsDeJeu(plateau); 
		//mvprintw(18,17,"testsDeJeu fait");
		//getch();
    }  
        return plateau; 
}




int main(){

        // --INITIALISATIONS DES PARAMS --

		// initialisations pour ncurses
	initscr();
	if ( !has_colors() ) {	// vérifie que les couleurs sont supportées
		printw("Erreur : Le terminal ne supporte pas les couleurs.");
		getch();
		 return -1;
	} 
	start_color();		// active les couleurs
	keypad(stdscr, TRUE); //active les flèches du clavier
	
        // Temps pour l'aléatoire
    srand( time(0) );
	
        // plateau de jeu
    Matrice plateau;
	plateau = plateauInitial(plateau);
    //plateau = { {0,0,0,0} , {0,0,1024,0} , {0,1024,0,0} , {0,0,0,0} , {0} };
	//mvprintw(15, 15, "LE TXT S'AFFICHE?");
	//getch();

	int boucleInfinie = 1;
	while (boucleInfinie == 1) {
	plateau = jouerUnCoup(plateau); 
	}


		//permet d'observer ce qui se passe en fin de programme
		//afin de trouver d'oÃ¹ vient l'erreur Core Dumped
	getch();
	endwin();

return 0;
}



