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
    // ÉTAPE 3 : Recherche des chaînes contenant le mot,
    //           sauvegarde de la plus grande, et remplacement par "naima"
    // --------------------------------------------------------
    auto debut_recherche = chrono::high_resolution_clock::now();

    bool trouve = false;
    string plusGrandeChaine = "";
    bool sousChaineTrouvee = false;
    int compteurRemplacements = 0;

    // Utilisation d'une référence (&motActuel) pour pouvoir modifier le vector en place
    for (string& motActuel : vecteurMots) {
        if (motActuel.find(mot1) != string::npos) {
            trouve = true;
            sousChaineTrouvee = true;

            // Garder en mémoire la plus grande chaîne avant de la remplacer
            if (motActuel.length() > plusGrandeChaine.length()) {
                plusGrandeChaine = motActuel;
            }

            // Remplacement du mot trouvé par "naima" dans le vector
            motActuel = "naima";
            compteurRemplacements++;
        }
    }

    auto fin_recherche = chrono::high_resolution_clock::now();
    chrono::duration<double, micro> temps_recherche = fin_recherche - debut_recherche;

    // --------------------------------------------------------
    // Affichage des résultats
    // --------------------------------------------------------
    cout << "\n========================================" << endl;
    cout << "RESULTATS DE LA RECHERCHE ET REMPLACEMENT" << endl;
    cout << "========================================" << endl;

    if (trouve) {
        cout << "Resultat : LE MOT EXISTE DANS LE FICHIER (sous forme de sous-chaine)" << endl;
        cout << "-> Nombre total de mots remplaces par 'naima' dans le vector : " << compteurRemplacements << endl;
    } else {
        cout << "Resultat : LE MOT N'EXISTE PAS DANS LE FICHIER" << endl;
    }

    cout << "\n========================================" << endl;
    cout << "PLUS GRANDE CHAINE CONTENANT LE MOT" << endl;
    cout << "========================================" << endl;

    if (sousChaineTrouvee) {
        cout << "La plus grande chaine contenant '" << mot1 << "' etait : " << plusGrandeChaine << endl;
        cout << "Longueur de cette chaine : " << plusGrandeChaine.length() << " caracteres" << endl;
    } else {
        cout << "Aucune chaine dans le vecteur ne contient '" << mot1 << "'." << endl;
    }

    cout << "\nTemps de traitement global (recherche + remplacement + plus grande chaîne) : "
         << temps_recherche.count()
         << " microsecondes" << endl;

    return 0;
}
