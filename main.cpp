#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <vector>
#include <algorithm>
#include <filesystem>

using namespace std;

// ============================================================
// PROGRAMME PRINCIPAL
// ============================================================
int main() {
    string chemin = "mots.txt";

    // Vérification de l'existence du fichier
    if (!filesystem::exists(chemin)) {
        cout << "ERREUR : Le fichier 'mots.txt' n'existe pas." << endl;
        cout << "Veuillez d'abord executer le script de generation du fichier." << endl;
        return 1;
    }

    ifstream fichier(chemin);
    if (!fichier) {
        cout << "ERREUR : Fichier impossible a ouvrir." << endl;
        return 1;
    }

    // --------------------------------------------------------
    // ÉTAPE 1 : Stockage des mots dans un vector
    // --------------------------------------------------------
    cout << "Chargement des donnees du fichier dans le vector..." << endl;

    auto debut_chargement = chrono::high_resolution_clock::now();

    vector<string> vecteurMots;
    string motLu;
    while (fichier >> motLu) {
        vecteurMots.push_back(motLu);
    }
    fichier.close();

    auto fin_chargement = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> temps_chargement = fin_chargement - debut_chargement;

    cout << "Chargement termine avec succes !" << endl;
    cout << "Nombre de mots charges : " << vecteurMots.size() << endl;
    cout << "Temps de chargement en mémoire : " << temps_chargement.count() << " ms\n" << endl;

    // --------------------------------------------------------
    // ÉTAPE 2 : Saisie du mot à rechercher
    // --------------------------------------------------------
    string mot1;
    cout << "Entrez le mot a rechercher : ";
    cin >> mot1;

    // --------------------------------------------------------
    // ÉTAPE 3 : Recherche de l'existence exacte + Remplacement par "naima"
    // --------------------------------------------------------
    auto debut_recherche = chrono::high_resolution_clock::now();

    auto it = find(vecteurMots.begin(), vecteurMots.end(), mot1);
    bool trouve = (it != vecteurMots.end());

    auto fin_recherche = chrono::high_resolution_clock::now();
    chrono::duration<double, micro> temps_recherche = fin_recherche - debut_recherche;

    // --------------------------------------------------------
    // ÉTAPE 4 : Recherche de la plus grande chaîne contenant mot1
    // --------------------------------------------------------
    auto debut_plus_long = chrono::high_resolution_clock::now();

    string plusGrandeChaine = "";
    bool sousChaineTrouvee = false;

    for (const string& motActuel : vecteurMots) {
        // Vérifie si mot1 est une sous-chaîne de motActuel (renvoie != string::npos si trouvé)
        if (motActuel.find(mot1) != string::npos) {
            sousChaineTrouvee = true;
            if (motActuel.length() > plusGrandeChaine.length()) {
                plusGrandeChaine = motActuel;
            }
        }
    }

    auto fin_plus_long = chrono::high_resolution_clock::now();
    chrono::duration<double, micro> temps_plus_long = fin_plus_long - debut_plus_long;

    // --------------------------------------------------------
    // Affichage des résultats
    // --------------------------------------------------------
    cout << "\n========================================" << endl;
    cout << "RESULTAT DE LA RECHERCHE (EXISTENCE DU MOT)" << endl;
    cout << "========================================" << endl;

    if (trouve) {
        cout << "Resultat : LE MOT EXISTE DANS LE FICHIER" << endl;

        // Remplacement du mot trouvé par "naima" uniquement dans le vector
        *it = "naima";
        cout << "-> Le mot a ete modifie par 'naima' dans le vector en memoire." << endl;
    } else {
        cout << "Resultat : LE MOT N'EXISTE PAS DANS LE FICHIER" << endl;
    }

    cout << "Temps de recherche pur (existence) : "
         << temps_recherche.count()
         << " microsecondes" << endl;

    cout << "\n========================================" << endl;
    cout << "PLUS GRANDE CHAINE CONTENANT LE MOT" << endl;
    cout << "========================================" << endl;

    if (sousChaineTrouvee) {
        cout << "La plus grande chaine contenant '" << mot1 << "' est : " << plusGrandeChaine << endl;
        cout << "Longueur de cette chaine : " << plusGrandeChaine.length() << " caracteres" << endl;
    } else {
        cout << "Aucune chaine dans le vecteur ne contient '" << mot1 << "'." << endl;
    }

    cout << "Temps de recherche (plus grande chaine) : "
         << temps_plus_long.count()
         << " microsecondes" << endl;

    return 0;
}
