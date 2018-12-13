
#include <iostream>;
#include <fstream>;
#include <time.h>;

using namespace std;


// DÉCLARATION DES FONCTIONS

void read(int &n);
void write();
void transpose(int n);
int compute(int n);
void compare(int n);


// DÉCLARATION DES VARIABLES GLOBALES

int const Nmax = 500;
int const voisinage_etoile_max = Nmax * (Nmax - 1) / 2;
int meilleur_obj = 1000000000;

int F[Nmax][Nmax];
int D[Nmax][Nmax];
int Solution[Nmax];
int Meilleure[Nmax];
int Voisinage[voisinage_etoile_max][Nmax];
int Initial[Nmax];


// FONCTION MAIN POUR L'ALGORITHME DU GLOUTON SIMPLE, BASIQUE

void main() {

	setlocale(LC_ALL, "fra");

	// DÉCLARATION DES VARIABLES

	int n = 0;
	time_t start, stop;
	//int loop = 0;

	cout << "\nAlgorithme du glouton simple, basique\n" << endl;

	// LECTURE DU FICHIER DE DONNÉES

	read(n);

	// CALCUL DE LA DIMENSION DU VOISINAGE ÉTOILÉ ET REMPLISSAGE DU VECTEUR INITIAL

	int voisinage_etoile = (n * (n - 1) / 2) + 1;

	for (int i = 0; i < n; i++) {

		Initial[i] = i + 1;

	}



	/* ------------------- BOUCLE PRINCIPALE ------------------- */



	start = time(NULL); // LANCEMENT DU TIMER


	do {

		// CALCUL DU VOISINAGE DU VECTEUR INITIAL PAR OPÉRATION DE TRANSPOSITION

		transpose(n);


		for (int i = 0; i < n; i++) {

			Solution[i] = Initial[i];

		}

		// CALCUL DE TOUTES LES VALEURS DES FONCTIONS OBJECTIF ET COMPARAISON POUR TROUVER LA MEILLEURE

		compare(n);


		for (int i = 0; i < n; i++) {

			Initial[i] = Meilleure[i];

		}

		stop = time(NULL);	// LECTURE DU TEMPS ÉCOULÉ

		//loop++;

	//} while (loop < 10);

	} while (stop - start < 1);	// GARDIEN DE LA BOUCLE : ARRÊT APRÈS 60 SECONDES


	// AFFICHAGE DE LA SOLUTION TROUVÉE

	cout << "Meilleure valeur de la fonction objectif : " << meilleur_obj << "\n" << endl;

	for (int i = 0; i < n; i++) {

		cout << " " << Meilleure[i];

	}

	cout << "\n" << endl;

	system("pause");

}





void read(int &n) {

	ifstream fichier("tai15a.dat", ios::in);

	if (fichier) {

		// Nombre d'usines ou de places disponibles

		fichier >> n;

		// Matrice de Distances

		for (int i = 0; i < n; i++) {

			for (int j = 0; j < n; j++) {

				fichier >> D[i][j];

			}

		}

		// Matrice de flux

		for (int i = 0; i < n; i++) {

			for (int j = 0; j < n; j++) {

				fichier >> F[i][j];

			}

		}


	}

	else {

		cerr << "Impossible d'ouvrir le fichier !" << endl;

	}

}





void transpose(int n) {

	int k = 1, temp = 0, compteur = 0, A[Nmax];
	bool deja_present = false;

	//Voisinage[Nmax][Nmax] = { 0 };

	for (int i = 0; i < n; i++) {

		Voisinage[0][i] = Initial[i];

	}

	for (int i = 0; i < n; i++) {


		for (int j = 0; j < n; j++) {


			if (j != i) {	// CONDITION EMPÊCHANT LA PERMUTATION D'UNE USINE AVEC ELLE-MÊME


				for (int i = 0; i < n; i++) {

					A[i] = Initial[i];

				}

				temp = A[i];

				A[i] = A[j];

				A[j] = temp;

				for (int j = 0; j < k; j++) {

					for (int i = 0; i < n; i++) {

						if (A[i] == Voisinage[j][i]) {

							compteur++;					// COMPTE DU NOMBRE D'ÉLÉMENTS IDENTIQUES AUX DEUX VECTEURS

						}

					}

					if (compteur == n) {

						deja_present = true;
						compteur = 0;

					}

					compteur = 0;

				}

				if (deja_present == false) {

					for (int i = 0; i < n; i++) {

						Voisinage[k][i] = A[i];	// AJOUT DU VECTEUR AU VOISINAGE S'IL NE S'Y TROUVE PAS DÉJÀ

					}

					k++;

				}

				deja_present = false;

			}


		}


	}


}





int compute(int n) {

	int objective = 0;

	for (int i = 0; i < n; i++) {

		for (int j = 0; j < n; j++) {

			objective += F[i][j] * D[Solution[i] - 1][Solution[j] - 1];	// FORMULE DE CALCUL DE L'OBJECTIF

		}

	}

	return objective;

}





void compare(int n) {

	int val_obj = 1000000000;	// VALEUR ARBITRAIRE MAIS IMPORTANTE CAR L'OBJECTIF EST DE MINIMISER

	for (int j = 0; j < (n*(n - 1) / 2) + 1; j++) {

		for (int i = 0; i < n; i++) {

			Solution[i] = Voisinage[j][i];

		}

		val_obj = compute(n);	// APPEL À LA FONCTION DE CALCUL DE L'OBJECTIF

		if (val_obj <= meilleur_obj && val_obj != 0) {	// CONDITION DE COMPARAISON

			meilleur_obj = val_obj;

			for (int k = 0; k < n; k++) {

				Meilleure[k] = Solution[k];

			}

		}

	}

}