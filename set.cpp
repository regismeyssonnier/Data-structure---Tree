#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>
#include <math.h>
#include <map>
#include <queue>
#include <string>
#include <iomanip>
#include <set>
#include <stack>
using namespace std;


#define ll long long int

#define MAX_N 20001
#define ll long long int
using namespace std;
int n, m;



void solve(int ca) {

	int a = 88211;

	cout << a << endl;

	set<int> s;
	int mxn = -1000000;
	int size = 0;
	int i = a;
	int maxi = -1000000;
	while (i > 0) {
		s.insert(i % 10);
		mxn = max(mxn, i % 10);
		maxi = i % 10;
		size++;
		i = i / 10;
		
	}

	int mex = 0;
	for (auto e : s) {
		if (mex == e) {
			mex++;
		}
		else {
			break;
		}
	}

	
	s.insert(mex);
	int mex2 = 0;
	for (auto e : s) {
		//if (e >= maxi) {
			if (mex2 == e) {
				mex2++;
			}
			else {
				break;
			}
		//}
	}

	int mex3 = mxn;
	for (auto e : s) {
		if (e >= mxn) {
			if (mex3 == e) {
				mex3++;
			}
			else {
				break;
			}
		}
	}

	cout << mex << " " << mex2 << " " << mex3 << endl;

	int v = 0;
	if (mex == 0) {
		v = mex3;
		if (mxn == 9) {
			v *= mex2;
		}
		
		for (int i = 0; i < size-1; i++) {
			v *= 10;
		}
		cout << v << endl;
	}
	else {
		v = mex3;
		if (mex3 == 10) {
			//v = mex3 * 10;
			v += mex;
		}
		for (int i = 0; i < size-1; i++) {
			v *= 10;
			v += mex;
		}

		cout << v << endl;
	}


	

}

int main() {
	// your code goes here
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int t=1;
	//cin >> t;
	int i = 1;
	while (i <= t) {
		solve(i); i++;
	}


	return 0;
}