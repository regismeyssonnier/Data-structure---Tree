// SegmentTree.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <vector>
using namespace std;

#define ll long long int

struct segtree {
	vector<ll> tree;
	ll N;
	ll _n;

	void init(int n) {
		ll size = 1;
		while (size < n) {
			size *= 2;
		}
		N = size - 1;
		tree.resize(2 * size);
		for (int i = 0; i < tree.size(); i++) {
			tree[i] = 0;
		}

	}

	void build(vector<ll> p) {
		_n = p.size();
		for (int i = 0; i < p.size(); i++) {
			add(i, p[i]);
		}
	}

	ll sumperf(int a, int b, int k, int x, int y) {
		if (b < x || a > y) return 0;
		if (a <= x && y <= b) {

			return tree[k];

		}
		int d = (x + y) / 2;
		return sumperf(a, b, 2 * k, x, d) + sumperf(a, b, 2 * k + 1, d + 1, y);
	}

	ll get_sum(int a, int b) {

		return sumperf(a, b, 1, 0, N);

	}


	void add(ll k, ll x) {
		k += _n + ((tree.size() / 2) - _n);
		tree[k] += x;
		for (k /= 2; k >= 1; k /= 2) {
			tree[k] = tree[2 * k] + tree[2 * k + 1];
		}
	}

};

int main()
{
	ll n, q;

	cin >> n ;

	vector<ll>p(n);

	for (int i = 0; i < n; i++) {
		cin >> p[i];
	}

	segtree seg;
	seg.init(n);
	seg.build(p);


	cout << seg.get_sum(0, 4) << endl;

}

/*
5
5 3 1 5 2
*/