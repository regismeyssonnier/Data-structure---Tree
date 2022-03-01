#include <iostream>
using namespace std;

constexpr int N = 8;
constexpr int MAXT = 2*N;
int tree[MAXT];


int sum(int a, int b) {
    a += N; b += N;
    int s = 0;
    while (a <= b) {
        if (a%2 == 1) s += tree[a++];
        if (b%2 == 0) s += tree[b--];
        a /= 2; b /= 2;
    }
    return s;
}

void add(int k, int x) {
    k += N;
    tree[k] += x;
    for (k /= 2; k >= 1; k /= 2) {
        tree[k] = tree[2*k]+tree[2*k+1];
    }
}

int minimum(int a, int b) {
    a += N; b += N;
    int s = 1000000;
    while (a <= b) {
        if (a%2 == 1) s = min(tree[a++], s);
        if (b%2 == 0) s = min(tree[b--], s);
        a /= 2; b /= 2;
    }
    return s;
}

void addmin(int k, int x) {
    k += N;
    tree[k] = x;
    for (k /= 2; k >= 1; k /= 2) {
        tree[k] = min(tree[2*k],tree[2*k+1]);
    }
}


int main() {
	// your code goes here
	ios_base::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	
	int tab[] = {5, 8, 6, 3, 1, 7, -2, 15};
	
	for(int i = 0;i < N;i++){
	    //add(i, tab[i]);
	    addmin(i, tab[i]);
	}
	
	for(int i = 1;i < (2*N);i++){
	    cout << tree[i] << " ";   
	}cout << endl;
	
	//cout << sum(7, 7) << endl;
	cout << minimum(6,6) << endl;
	
	return 0;
}
