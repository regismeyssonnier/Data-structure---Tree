// Held_Karp.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <algorithm>
#include <list>
#include <vector>
#include <set>
#include <map>
#include <deque>

using namespace std;

#define INF 1000000000

class TSP {
public:
    int N;
    vector<set<int>> allSub;
    TSP(int n): N(n) {
        allSub = GenerateSubset();
    }

    int MinCost(int distance[10][10]) {

        

        map<pair<int, set<int>>, int> minCostDP, parent;

        
        for (auto subset : allSub) {
            for (int currentVertex = 1; currentVertex <= N; currentVertex++) {
                if (subset.contains(currentVertex)) {
                    continue;
                }

                pair<int, set<int>> index = { currentVertex, subset };
                int minCost = INF;
                int minPrevVertex = 0;
                set<int>::iterator prevVertex;
                for (prevVertex = subset.begin(); prevVertex != subset.end(); ++prevVertex) {
                    int cost = distance[*prevVertex][currentVertex] + getCost(subset, *prevVertex, minCostDP);
                    if (cost < minCost) {
                        minCost = cost;
                        minPrevVertex = *prevVertex;
                    }
                }

                if (subset.size() == 0) {
                    minCost = distance[0][currentVertex];
                }
                minCostDP[index] = minCost;
                parent[index] = minPrevVertex;
            }



        }

        set<int> subset;
        for (int i = 1; i <= N; ++i) subset.insert(i);

        int mind = numeric_limits<int>::max();
        int prevVertex = -1;

        for (int k : subset) {
            int cost = distance[k][0] + getCost(subset, k, minCostDP);
            if (cost < mind) {
                mind = cost;
                prevVertex = k;
            }
        }

        pair<int, set<int>> index = { 0, subset };
        parent[index] = prevVertex;
        printTour(parent);
        
        return mind;
    }

    void printTour(map<pair<int, set<int>>, int> &parent) {

        set<int> subset;
        for (int i = 0; i <= N; ++i) subset.insert(i);

        int start = 0;
        deque<int> stack;
        while (1) {
            stack.push_front(start);
            subset.erase(start);
            
            if (parent.count({ start, subset }) == 0) {
                break;
            }
            else {
                start = parent[{start, subset}];
            }
        }

        for (int i = 0; i < stack.size(); ++i) {
            cout << stack[i] << ((i < stack.size()-1)?"->":"");
        }cout << endl;

    }

    int getCost(set<int> subset, int prevVertex, map< pair<int, set<int>>, int> minCostDP) {

        subset.erase(prevVertex);
        pair<int, set<int>> index = { prevVertex , subset };
        int cost = minCostDP[index];
        //subset.insert(prevVertex);

        return cost;
    }

    vector<set<int>> GenerateSubset() {

        vector<set<int>> allSub;
        int IND = 1;
        //generate all subset
        for (int b = 0; b < (1 << N); b++) {
            set<int> subset;
            for (int i = 0; i < N; i++) {
                if (b & (1 << i)) subset.insert(i+1);
            }
            allSub.push_back(subset);
            ++IND;
        }

        sort(allSub.begin(), allSub.end(), [](const set<int>& a, const set<int>& b) {
            return a.size() < b.size();
            });

        return allSub;

    }

    void Display_Subset() {
        cout << "start " << endl;
        for (auto subset : allSub) {
            set<int>::iterator sb;
            cout << "subset = " ;
            for (sb = subset.begin(); sb != subset.end(); ++sb) {
                cout << *sb << ", ";
            }
            cout << endl;
        }

    }



};

int main()
{
    int distance[10][10] = {
                            {0, 1, 15, 6},
                            {2, 0, 7, 3},
                            {9, 6, 0, 12},
                            {10, 4, 8, 0}
                           };

    TSP tsp = TSP(3);
    int d = tsp.MinCost(distance);
    tsp.Display_Subset();
    cout << "min distance=" << d << endl;
    
}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
