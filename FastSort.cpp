// FastSort.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <stdlib.h>
using namespace std;

int MAX = 5000;
vector<int> b(MAX);
vector<int> a(MAX);


void FastSort(int l, int r) {
    int m;
    bool exc = false;
    
    
    if (l < r) {
        m = (l + r) / 2;
        //m = fs(l, r, m);
        FastSort(l, m);
        FastSort(m + 1, r);
    }
    


}

int partitionp(int f, int l, int pivot) {
    int tmp = a[f];
    a[f] = a[pivot];
    a[pivot] = tmp;

    int i = f + 1, j = l;
    while (i < j) {
        while (i < j && a[i] < a[f])++i;
        while (i < j && a[j] > a[f])--j;

        tmp = a[i];
        a[i] = a[j];
        a[j] = tmp;
        ++i, --j;
    }
   
    return i;

}

int partitionp2(int f, int l, int pivot) {
    int tmp = a[f];
    a[f] = a[pivot];
    a[pivot] = tmp;

    int i = f + 1, j = l;
    while (i < j) {
        while (i < j && a[i] < a[f])++i;
        while (i < j && a[j] > a[f])--j;

        tmp = a[i];
        a[i] = a[j];
        a[j] = tmp;
        ++i, --j;
    }

    int k;
    for (k = f; k < l; ++k) {
        if (a[k] > a[k+1]) {
            tmp = a[k];
            a[k] = a[k+1];
            a[k] = tmp;
        }
    }

    return k;

}

int partitionp3(int f, int l, int pivot) {
    int tmp = a[f];
    a[f] = a[pivot];
    a[pivot] = tmp;

    int i = f + 1, j = l;
    while (i < j) {
        while (i < j && a[i] < a[f])++i;
        while (i < j && a[j] > a[f])--j;

        tmp = a[i];
        a[i] = a[j];
        a[j] = tmp;
        ++i, --j;
    }

    int k;
    int maxi = numeric_limits<int>::min();
    int ind = 0;
    for (k = f; k <= l; ++k) {
        if (a[k]> maxi) {
            maxi = a[k];
            ind = k;
        }
    }

    return ind;

}

int partition(int f, int l, int pivot) {
    int tmp = a[l];
    a[l] = a[pivot];
    a[pivot] = tmp;

    int j = f;
    for (int i = f; i < l; ++i) {
        if (a[i] <= a[l]) {
            tmp = a[i];
            a[i] = a[j];
            a[j] = tmp;
            ++j;
        }
    }
    tmp = a[l];
    a[l] = a[j];
    a[j] = tmp;

    return j;
}

void quick(int f, int l) {
    int pivot;
    if (f < l) {
     
        pivot = (f + l) / 2;
        pivot = partition(f, l, pivot);
        quick(f, pivot - 1);
        quick(pivot + 1, l);
    }

}

void quick2(int f, int l) {
    int pivot;
    if (f < l) {
        pivot = 0;
        int maxi = numeric_limits<int>::min();
        for (int i = f; i <= l; ++i) {
            if (a[i] > maxi) {
                maxi = a[i];
                pivot = i;
            }
        }
        pivot = partition(f, l, pivot);
        quick(f, pivot - 1);
        quick(pivot + 1, l);
    }

}

void quick3(int f, int l) {
    int pivot;
    if (f < l) {

        pivot = (f + l) / 2;
        pivot = partitionp(f, l, pivot);
        quick(f, pivot - 1);
        quick(pivot + 1, l);
    }

}

void quick4(int f, int l) {
    int pivot;
    if (f < l) {

        pivot = (f + l) / 2;
        pivot = partitionp2(f, l, pivot);
        quick(f, pivot - 1);
        quick(pivot + 1, l);
    }

}

void quick5(int f, int l) {
    int pivot;
    if (f < l) {

        pivot = (f + l) / 2;
        pivot = partitionp3(f, l, pivot);
        quick(f, pivot - 1);
        quick(pivot + 1, l);
    }

}

void quick6(int f, int l) {
    int pivot;
    if (f < l) {
        int maxi = numeric_limits<int>::min();
        for (int i = f; i <= l; ++i) {
            if (a[i] > maxi) {
                maxi = a[i];
                pivot = i;
            }
        }
        pivot = partitionp(f, l, pivot);
        quick(f, pivot - 1);
        quick(pivot + 1, l);
    }

}

void load() {

       
    srand(time(NULL));

    for (int i = 0; i < MAX; ++i) {
        b[i] = (rand() % 100000 + 1);
    }

}

void copy() {
 
    for (int i = 0; i < b.size(); ++i) {
        a[i] = b[i];
    }

}


void bubble() {

    for (int i = a.size()-1; i > 0; --i) {
        bool s = true;
        for (int j = 0; j < i; ++j) {
            if (a[j + 1] < a[j]) {
                int tmp = a[j];
                a[j] = a[j + 1];
                a[j+1] = tmp;
                s = false;
            }
        }
        if (s)break;
    }

}

void display(vector<int> a) {
    for (int i = 0; i < a.size()&& i < 50; ++i)cout << a[i] << " ";
    cout << endl;
}

int main()
{
    cout << "Hello Fast Sort \n";

    load();
    copy();

    
    /*display(a);

    auto begin = chrono::high_resolution_clock::now();
  
        FastSort(0, MAX-1);
  
    auto end = chrono::high_resolution_clock::now();
    auto dur = end - begin;
    auto ms = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();

    display(a);

    cout << "fs time "<<  ms << endl<<endl;*/

    copy();
    display(a);
    auto begin = chrono::high_resolution_clock::now();
    sort(a.begin(), a.end());
    auto end = chrono::high_resolution_clock::now();
    auto dur = end - begin;
    auto ms = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();

    display(a);

    cout << "c++ time " << ms << endl << endl;

   /* copy();
    display(a);
    begin = chrono::high_resolution_clock::now();
    bubble();
    end = chrono::high_resolution_clock::now();
    dur = end - begin;
    ms = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();

    display(a);

    cout << "bubble time " << ms << endl << endl;*/

    copy();
    display(a);
    begin = chrono::high_resolution_clock::now();
    quick(0, MAX-1);
    end = chrono::high_resolution_clock::now();
    dur = end - begin;
    ms = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();

    display(a);

    cout << "quick time " << ms << endl << endl;

    copy();
    display(a);
    begin = chrono::high_resolution_clock::now();
    quick2(0, MAX - 1);
    end = chrono::high_resolution_clock::now();
    dur = end - begin;
    ms = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();

    display(a);

    cout << "quick2 time " << ms << endl << endl;

    copy();
    display(a);
    begin = chrono::high_resolution_clock::now();
    quick3(0, MAX - 1);
    end = chrono::high_resolution_clock::now();
    dur = end - begin;
    ms = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();

    display(a);

    cout << "quick3 time " << ms << endl << endl;

    copy();
    display(a);
    begin = chrono::high_resolution_clock::now();
    quick4(0, MAX - 1);
    end = chrono::high_resolution_clock::now();
    dur = end - begin;
    ms = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();

    display(a);

    cout << "quick4 time " << ms << endl << endl;

    copy();
    display(a);
    begin = chrono::high_resolution_clock::now();
    quick5(0, MAX - 1);
    end = chrono::high_resolution_clock::now();
    dur = end - begin;
    ms = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();

    display(a);

    cout << "quick5 time " << ms << endl << endl;

    copy();
    display(a);
    begin = chrono::high_resolution_clock::now();
    quick6(0, MAX - 1);
    end = chrono::high_resolution_clock::now();
    dur = end - begin;
    ms = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();

    display(a);

    cout << "quick6 time " << ms << endl << endl;
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
