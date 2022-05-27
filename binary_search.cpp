// GameBS.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <vector>

using namespace std;

#define ll long long int

ll NB = 10;

bool determine(ll m) {

	bool ans;

	if (NB > m) {
		ans = true;
	}
	else {
		ans = false;
	}

	return ans;
}



ll binary_searchGBS(ll &nb) {

	ll ans = 0;

	ll low = 0, high = numeric_limits<ll>::max(), mid = 0;

	while (low <= high) {

		mid = (low + high) / 2;
		if (determine(mid)) {
			low = mid + 1;
			ans = low;
		}
		else {
			high = mid - 1;
		}
		nb++;
	}

	return ans;
}


int main()
{
	ll nb = 0;
	ll ans = binary_searchGBS(nb);

	cout << ans << " in " << nb << " hit " << endl;


   
}
