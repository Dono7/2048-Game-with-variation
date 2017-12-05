#include <ncurses.h>	// ncurses, couleur et utilisation fl�che
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




Matrice jouerUnCoup(Matrice plateau) {
	int commande ;


	//Demande la commande
	commande = getch();
	// R:114, Bas/Haut/Gauche/droite : 258 a 261

			//affiche le plateau de jeu, score et msg d'erreur/de fin
	clear();
	affichageJeu(plateau);
	//mvprintw(18, 10, commentaire) ; 	// FAIT PARTI DE L'ANCIENNE VERSION



	if ( not commandeVerifier(commande) ) {
        mvprintw(18,10,"Commande invalide");
		refresh();



	} else {
	plateau = commandeExecuter(commande, plateau);
	plateau = testsDeJeu(plateau);
		refresh();
    }
return plateau;
}




int main(){

        // --INITIALISATIONS DES PARAMS --

		// initialisations pour ncurses
	initscr();
	if ( !has_colors() ) {	// v�rifie que les couleurs sont support�es
		printw("Erreur : Le terminal ne supporte pas les couleurs.");
		getch();
		 return -1;
	}
	start_color();		// active les couleurs
	keypad(stdscr, TRUE); //active les fl�ches du clavier

        // Temps pour l'al�atoire
    srand( time(0) );

        // plateau de jeu
    Matrice plateau;
	plateau = { {2,8,32,4} , {16,64,2,8} , {8,16,32,4} , {2,8,4,2} , {99} } ;
	plateau = { {2,8,4,2} , {2,16,8,4} , {2,8,2,8} , {16,32,4,2} , {99} } ;
	if( mouvmtPossibleHaut(plateau) or mouvmtPossibleDroite(plateau) or mouvmtPossibleGauche(plateau) or mouvmtPossibleBas(plateau) ) {
        mvprintw(21,12,"Un mouvement est possibles");
	} else {
	mvprintw(21,12,"Aucun mouvement n'est possible") ; }
	if( estBloque(plateau) ) {
		affichageJeu(plateau) ;
		mvprintw(22,12,"Test r�ussi : Le jeu est bloqu�");
		refresh; getch();
	} else {
		affichageJeu(plateau) ;
		getch();
		mvprintw(22,12,"Test rate : Le jeu ne d�tecte pas le blocage");
		refresh; getch();

	}


	plateau = plateauInitial(plateau);
	// pour tester le jeu gagnant
    //plateau = { {0,0,0,0} , {0,0,1024,0} , {0,1024,0,0} , {0,0,0,0} , {0} };

	int boucleInfinie = 1;
	while (boucleInfinie == 1) {
		affichageJeu(plateau);
	plateau = jouerUnCoup(plateau);
	}

	endwin();

return 0;
}



