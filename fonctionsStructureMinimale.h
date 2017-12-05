


			//      ---- AFFICHAGES ----
/** LES 2 FONCTIONS AFFICHE SONT DES ANNEXES A LA FONCTION AFFICHEPLATEAU **/ 
void afficheCase(int valeurCase);
void afficheLigne (Matrice plateau, int ligne) ;
void afficheCommandes() ;
/** Affiche uniquement un plateau en couleur centré dans le terminal et va à la ligne
 * @param tableau 2D, plateau de jeu
 * auncun return, seulement de l'affichage par cout
**/
void affichePlateau(Matrice plateau) ;

			// --- DEPLACEMENTS ---

/** DeplacementPartiel décale toutes les cases dans une direction souhaitée, sans fusion
 * @param le plateau de jeu
 * @ return le plateau une fois le mouvement effectué
**/
Matrice deplacementPartielHaut(Matrice plateau) ;
Matrice deplacementPartielDroite(Matrice plateau) ;
Matrice deplacementPartielBas(Matrice plateau) ;
Matrice deplacementPartielGauche(Matrice plateau) ;

/** Fusion des cases de même valeur dans un mouvement donné, et execute un mouvmtPartiel si nécessaire
 * @param plateau de jeu
 * @return le plateau après la fusion
**/
Matrice fusionHaut(Matrice plateau);
Matrice fusionDroite(Matrice plateau);
Matrice fusionBas(Matrice plateau);
Matrice fusionGauche(Matrice plateau);

/** Combine à la fois le DeplacementPartiel et Fusion pour executer le mouvement total
 * @param le plateau de jeu avant le mouvement
 * @return le plateau de jeu après
**/
Matrice deplacementHaut(Matrice plateau) ;
Matrice deplacementDroite(Matrice plateau) ;
Matrice deplacementBas(Matrice plateau) ;
Matrice deplacementGauche(Matrice plateau) ;



			// --- MOUVEMENT POSSIBLES ? ---

	// fonctions de l'ancienne version
// bool mouvmtPossibleHautBas(Matrice plateau) ;
// bool mouvmtPossibleDroiteGauche(Matrice plateau) ;

/** Test si un mouvement est possible est possible dans un certain sens
 * @param le plateau de jeu
 * @return True si le mouvement est possible, False sinon
**/
bool mouvmtPossibleHaut(Matrice plateau) ;
bool mouvmtPossibleDroite(Matrice plateau) ;
bool mouvmtPossibleBas(Matrice plateau) ;
bool mouvmtPossibleGauche(Matrice plateau) ;

			// --- TEST DE SITUATIONS ---

/** Test si le jeu est Bloqué(perdant), ou gagné, à lancer après chaque coup
 * @param le plateau de jeu
 * @return True ou False en fonction de la situation
**/
bool estBloque(Matrice plateau) ;
bool estGagne(Matrice plateau) ;
bool grillePleine(Matrice plateau) ;		// utile ? ...

/** Renvoie le nombre de cases vide du plateau
 * @param le plateau de jeu
 * @return un entier
 **/
int nbrCasesVides(Matrice plateau) ;

			// --- RANDOM ---

/** Indique si un évènement de proba 1/N s'est produit ou non
 * @param n tel que la proba est 1/n
 * @return True si l'évènement se produit, False sinon
**/
bool eventProba1surN(float n) ;

/** fait aléatoirement apparaître un 2 ou un 4 sur la grille en respectant les règles du 2048
 * @param le plateau non plein
 * @return plateau avec un 2 ou 4 apparu
**/
Matrice randomspawn(Matrice plateau);

// --- INITIALISATION DU JEU ---

/** Créer un plateau vide ou initial (avec 2 nombres aléatoires)
 * @param plateau pour la fonction Initial
 * @return un plateau vide ou initial
**/
Matrice plateauVide();
Matrice plateauInitial(Matrice plateau);

// --- AFFICHAGE DU JEU ET PRISE DE DECISION ---

/** Affiche un plateau de jeu et le score
 * @param plateau de jeu qui contient le score
 * aucun return, que de l'affichage par cout
**/
void affichageJeu(Matrice plateau);

/** Vérifie que le mouvement demandé est bien une des commandes existantes 
 * @param la commande en format string
 * @return True si la commande existe, False sinon
**/
bool commandeVerifier(int commande);	

/** Excecute un mouvement ou un restart en fonction de la demande de l utilisateur
 * @param int correspondant à la touche pressée
 * @param le plateau de jeu à modifier eventuellement
 **/
Matrice commandeExecuter(int commande, Matrice plateau) ;	///

/** Test si le jeu est soit gagné soit bloqué et donc perdu
 * @param le plateau de jeu
 * @return un lien vers la fonction correspondante
 **/
Matrice testsDeJeu(Matrice plateau) ;	

/** Affiche le jeu+score, prend la prochaine commande et reagit en fonction 
 * @param le plateau de jeu à afficher
 * @param commentaire en cas d'erreur ou de jeu gagné/perdu
 **/
Matrice jouerUnCoup(Matrice plateau) ;

/** Affiche un message Partie perdue jusqu'à ce que l'utilisateur relance une partie
 * aucun param ou return
 **/
void partiePerdue() ;






