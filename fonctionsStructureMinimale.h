
	// EXTENSION : STRUCT
struct jeuGlobal {
	Matrice plateau; //plateau de jeu de base
	int score;
	Matrice back; //pour revenir un coup en arrière
	int compteur40; //Ma variante : Pour une suppression tous les 40 coups
};

//emplacement temp
struct jeuGlobal suppression40(struct jeuGlobal jeu) ;


			//      ---- AFFICHAGES ----
/** LES 2 FONCTIONS AFFICHE SONT DES ANNEXES A LA FONCTION AFFICHEPLATEAU **/ 
void afficheCase(int valeurCase);
void afficheLigne (Matrice plateau, int ligne) ;
void afficheCommandes() ;
/** Affiche uniquement un plateau en couleur centré dans le terminal et va à la ligne
 * @param tableau 2D, plateau de jeu
 * auncun return, seulement de l'affichage par cout
**/
void affichePlateau(struct jeuGlobal jeu) ;

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
struct jeuGlobal fusionHaut(struct jeuGlobal jeu);
struct jeuGlobal fusionDroite(struct jeuGlobal jeu);
struct jeuGlobal fusionBas(struct jeuGlobal jeu);
struct jeuGlobal fusionGauche(struct jeuGlobal jeu);

/** Combine à la fois le DeplacementPartiel et Fusion pour executer le mouvement total
 * @param le plateau de jeu avant le mouvement
 * @return le plateau de jeu après
**/
struct jeuGlobal deplacementHaut(struct jeuGlobal jeu) ;
struct jeuGlobal deplacementDroite(struct jeuGlobal jeu) ;
struct jeuGlobal deplacementBas(struct jeuGlobal jeu) ;
struct jeuGlobal deplacementGauche(struct jeuGlobal jeu) ;

/** Ecrit le nouveau highscore dans le fichier externe si nécessaire
 * @param Le nouveau score que l'on vient de faire
 * @return un fichier externe qui contient le (nouveau) highscore
 **/
void chargementHighscore(int scoretemp);

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

/** Agit sur le plateau par les règles de ma variante (voir doc annexe)
 * @param le plateau de jeu après avoir joué un coup
 * @return le plateau avec (ou pas) l'augmentation/baisse aléatoire
**/
Matrice baisseOuAug(Matrice plateau);



// --- INITIALISATION DU JEU ---

/** Créer un plateau vide ou initial (avec 2 nombres aléatoires)
 * @param plateau pour la fonction Initial
 * @return un plateau vide ou initial
**/
Matrice plateauVide();
struct jeuGlobal plateauInitial(struct jeuGlobal jeu);

// --- AFFICHAGE DU JEU ET PRISE DE DECISION ---

/** Affiche un plateau de jeu et le score
 * @param plateau de jeu qui contient le score
 * aucun return, que de l'affichage par cout
**/
void affichageJeu(struct jeuGlobal jeu);

/** Vérifie que le mouvement demandé est bien une des commandes existantes 
 * @param la commande en format string
 * @return True si la commande existe, False sinon
**/
bool commandeVerifier(int commande);	

/** Excecute un mouvement ou un restart en fonction de la demande de l utilisateur
 * @param int correspondant à la touche pressée
 * @param le plateau de jeu à modifier eventuellement
 **/
struct jeuGlobal commandeExecuter(int commande, struct jeuGlobal jeu) ;	///

/** Test si le jeu est soit gagné soit bloqué et donc perdu
 * @param le plateau de jeu
 * @return un lien vers la fonction correspondante
 **/
struct jeuGlobal testsDeJeu(struct jeuGlobal jeu) ;	

/** Affiche le jeu+score, prend la prochaine commande et reagit en fonction 
 * @param le plateau de jeu à afficher
 * @param commentaire en cas d'erreur ou de jeu gagné/perdu
 **/
struct jeuGlobal jouerUnCoup(struct jeuGlobal jeu) ;







