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




struct jeuGlobal jouerUnCoup(struct jeuGlobal jeu) {
	int commande ;


	//Demande la commande
	commande = getch();
	// R:114, Bas/Haut/Gauche/droite : 258 a 261

			//affiche le plateau de jeu, score et msg d'erreur/de fin
	clear();
	affichageJeu(jeu);
	//mvprintw(18, 10, commentaire) ; 	// FAIT PARTI DE L'ANCIENNE VERSION


		// On vérifie que la commande rentrée existe
	if ( not commandeVerifier(commande) ) {
        mvprintw(18,10,"Commande invalide");
		refresh();

		// On execute le mvmt et test si le jeu est gagne/perdu
	} else {
	jeu = commandeExecuter(commande, jeu);
	jeu = testsDeJeu(jeu);
		refresh();
    }
return jeu;
}




int main(){

        // --INITIALISATIONS DES PARAMS --

		// initialisations pour ncurses
	initscr();
	if ( !has_colors() ) {	// vérifie que les couleurs sont supportées
		printw("Erreur : Le terminal ne supporte pas les couleurs.") ;
		getch();
		 return -1;
	}
	start_color();		// active les couleurs
	keypad(stdscr, TRUE); //active les flèches du clavier

        // Temps pour l'aléatoire
    srand( time(0) );

	
	
        // plateau de jeu
	struct jeuGlobal jeu;	// EXTENSIONS STRUCT
    //Matrice plateau;		//Ancienne version
	jeu = plateauInitial(jeu);
	// pour tester le jeu gagnant :
    //jeu.plateau = { {0,0,0,0} , {0,0,1024,0} , {0,1024,0,0} , {0,0,0,0}  };
    jeu.plateau = { {0,0,4,0} , {0,0,8,0} , {2,32,64,32} , {1024,512,128,64}  };

	int boucleInfinie = 1;
	while (boucleInfinie == 1) {
		affichageJeu(jeu);
	jeu = jouerUnCoup(jeu);
	}

	endwin();

return 0;
}



