#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>
#include <math.h>
#include <map>
#include <queue>

#define ll long long int

vector<ll> p;
vector<ll> r;
vector<ll> mi;
vector<ll> ma;
vector<ll> sz;

ll get(ll a) {
	return p[a] = (p[a] == a ? a : get(p[a]));
}

void _union(ll a, ll b){
	a = get(a);
	b = get(b);
	if (r[a] == r[b])
		r[a]++;
	if (r[a] > r[b]) {
		if (a != b)
			sz[a] += sz[b];
		p[b] = a;
		
		//sz[b] = 0;
		mi[a] = min(mi[a], mi[b]);
		ma[a] = max(ma[a], ma[b]);
	}
	else {
		if (a != b)
			sz[b] += sz[a];
		p[a] = b;
		
		//sz[a] = 0;
		mi[b] = min(mi[a], mi[b]);
		ma[b] = max(ma[a], ma[b]);
	}
		

}

void solve() {

	ll n, m;

	cin >> n >> m;

	p.resize(n, 0);
	r.resize(n, 0);
	mi.resize(n, 0);
	ma.resize(n, 0);
	sz.resize(n, 0);

	for (int j = 0; j < n; j++) {
		p[j] = j;
		mi[j] = j;
		ma[j] = j;
		sz[j] = 1;
	}

	for (int i = 0; i < m; i++) {
		string s;
		int u, v;

		cin >> s;
		
		if (s == "union") {
			cin >> u >> v; u--; v--;
			_union(u, v);
			/*for (int j = 0; j < n; j++)
				cout << p[j] << " ";
			cout << endl;
			for (int j = 0; j < n; j++)
				cout << sz[j] << " + ";
			cout << endl;*/
		}
		else if (s == "get") {
			cin >> u; u--; 
			ll a = get(u);
			
			cout << (mi[a]+1) << " " << (ma[a]+1) << " " << sz[a] << endl;
		}

	}
	

}

int main() {
	// your code goes here
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	//ll T;
	//cin >> T;
	//while (T--) {
		solve();
	//}


	return 0;
}