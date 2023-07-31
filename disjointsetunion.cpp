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

ll get(ll a) {
	return p[a] = (p[a] == a ? a : get(p[a]));
}

void _union(ll a, ll b){
	a = get(a);
	b = get(b);
	if (r[a] == r[b])
		r[a]++;
	if( r[a] > r[b])
		p[b] = a;
	else 
		p[a] = b;

}

void solve() {

	ll n, m;

	cin >> n >> m;

	p.resize(n, 0);
	r.resize(n, 0);

	for (int j = 0; j < n; j++)
		p[j] = j;

	for (int i = 0; i < m; i++) {
		string s;
		int u, v;

		cin >> s >> u >> v;
		u--; v--;
		if (s == "union") {
			_union(u, v);
			/*for (int j = 0; j < n; j++)
				cout << p[j] << " ";
			cout << endl;*/
		}
		else if (s == "get") {
			ll a = get(u);
			ll b = get(v);

			if (a == b) {
				cout << "YES" << endl;
			}
			else {
				cout << "NO" << endl;
			}
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