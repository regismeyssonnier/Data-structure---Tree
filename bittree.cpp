#include <iostream>
using namespace std;

constexpr int N = 8+1;
int tree[N];

int sum(int k) {
    int s = 0;
    while (k >= 1) {
        s += tree[k];
        k -= k&-k;
    }
    return s;
}

void add(int k, int x) {
    while (k <= N) {
        tree[k] += x;
        k += k&-k;
    }
}

int inter(int a, int b){
    
    return sum(b) - sum(a-1);
}

int main() {
	// your code goes here
	ios_base::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	
	int tab[] = {1, 3, 4, 8, 6, 1, 4, 2};
	
	for(int i = 1;i <= N;i++){
	    add(i, tab[i-1]);
	    
	}
	
	cout << sum(3) << endl;
	cout << inter(3, 6) << endl;
	
	return 0;
}
