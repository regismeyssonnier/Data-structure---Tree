// NSat.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>

#include <vector>
#include <algorithm>
using namespace std;

#define SAT 2

void dfs2(vector<vector<int>>& kadj, int f, int x, vector<bool> &vis, vector<int>& li) {

	

	for (int i = 0; i < kadj[x].size(); i++) {
		
		/*if (kadj[x][i] == f) {
			break;
		}*/

		if (!vis[kadj[x][i]]) {
			
			li.push_back(kadj[x][i]);
			vis[kadj[x][i]] = true;
			dfs2(kadj, f, kadj[x][i], vis, li);
			
			
		}
	}

	return;
}

void dfs(vector<vector<int>>& kadj, vector<int> &r) {

	vector<bool> vis(kadj.size(), false);
	vector<int> li;
	
	for (int i = 1; i < kadj.size(); i++) {
		 
		if (!vis[i]) {
			li.push_back(i);
			
			vis[i] = true;
			dfs2(kadj, i, i, vis, li);
			for (int j = li.size() - 1; j >= 0; j--) {
				r.push_back(li[j]);
			}
			li.clear();
		
			
		}
	}

}


void dfsf2(vector<vector<int>>& kadj,  int f, int x, vector<bool>& vis, vector<vector<int>>& r, int ri) {

	///if (x == f)return;
	//if (kadj[x].size() == 1)return;
	for (int i = 0; i < kadj[x].size(); i++) {
		
		if (kadj[x][i] == f) {
			break;
		}

		if (!vis[kadj[x][i]]) {
			
			r[ri].push_back(kadj[x][i]);
			vis[kadj[x][i]] = true;
			dfsf2(kadj, f, kadj[x][i], vis, r, ri);


		}
	}

	return;
}

void dfsf(vector<vector<int>>& kadj, vector<int>& l, vector<vector<int>>& r) {

	vector<bool> vis(l.size()+1, false);
	
	int ri = 0;
	for (int i = l.size()-1; i >= 0 ; i--) {
		
		if (!vis[l[i]]) {
			r[ri].push_back(l[i]);
			
			vis[l[i]] = true;
			dfsf2(kadj, l[i], l[i], vis, r, ri);
			ri++;
		}
	}

}

int main()
{
	int n = 4;
	bool a, b, c, d;

	//string lvar = "(avnb)^(navb)^(navnb)^(avnc)";
	string lvar = "(bvna)^(navnb)^(avc)^(nbvnc)^(avd)";
	//string lvar = "(avb)^(avnb)^(navc)^(navnc)";

	vector<vector<int>> adj(SAT * (n )+1), kadj(SAT * (n)+1), form;
	vector<bool> par(SAT * (n + 1));

	cout << lvar << endl;
	bool open = false;
	for (int i = 0; i < lvar.length(); i++) {

		if (lvar[i] == '(') {
			open = true;
		}
		else if ((lvar[i] >= 'a' && lvar[i] <= 'z') || lvar[i]=='n' && open) {
			int i1=i, i2=i+2, k = 1, l = 1, m=1, p=1;
			bool n1 = false, n2 = false;
			if (lvar[i] == 'n') {
				i1 = i + 1;
				n1 = true;
				k = n+ 1;
				l = 1;
			}
			else {
				k = 1;
				l = n + 1;
			}
			
			if (lvar[i1 + 2] == 'n') {
				i2 = i1 + 3;
				n2 = true;
				m = 1;
				p = n + 1;
			}
			else {
				m = n + 1;
				p = 1;
				i2 = i1 + 2;
			}

			vector<int> v;
			int ev = (lvar[i1] - 'a') + 1;
			if (!n1)ev += n;
			int ev2 = (lvar[i2] - 'a') + 1;
			if (!n2)ev2 += n;
			v.push_back(ev);
			v.push_back(ev2);
			form.push_back(v);
			
			///cout << i1 << " " << lvar[i2] << endl;
			//cout << (lvar[i1] - 'a') + 1 << " " << ((lvar[i2] - 'a') + n + 1) << endl;
			adj[(lvar[i1] - 'a') + k].push_back((lvar[i2] - 'a') + m);
			adj[(lvar[i2] - 'a') + p].push_back((lvar[i1] - 'a') + l);
			i = i2;
		}
		else if (lvar[i] == ')') {
			open = false;
		}
		else if (lvar[i] == '^')continue;

	}

	for (int i = 1; i < 2 * (n)+1; i++) {
		if (adj[i].size() > 0) {
			for (int j = 0; j < adj[i].size(); j++) {
				kadj[adj[i][j]].push_back(i);
				//kadj[i].push_back(adj[i][j]);
			}
		}
	}

	for (int i = 1; i < 2 * (n )+1; i++) {
		cout << "i : "<<i << " = ";
		for (int j = 0; j < adj[i].size(); j++) {
			cout << adj[i][j] << " ";
		}cout << endl;
 	}
	cout << "---------------------------------" << endl;
	for (int i = 1; i < 2 * (n)+1; i++) {
		cout << "i : " << i << " = ";
		for (int j = 0; j < kadj[i].size(); j++) {
			cout << kadj[i][j] << " ";
		}cout << endl;
	}
	cout << "---------------------------------" << endl;

	vector<vector<int>> r(2 * (n )+1), r3(2 * (n)+1);
	vector<int> r2;
	dfs(adj, r2);

	/*for (int i = 0; i < r2.size(); i++) {
		cout << r2[i] << " - ";
	}cout << endl; */
	
	dfsf(kadj, r2, r);
		

	for (int i = 0; i < r.size(); i++) {
		if (r[i].size() > 0) {
			for (int j = 0; j < r[i].size(); j++) {
				cout << r[i][j] << " ";
			}cout << endl;
		}
	}

	bool verified = true;
	for (int i = 0; i < r.size(); i++) {
		
		if (r[i].size() > 0) {
			sort(r[i].begin(), r[i].end());
			for (int j = 0; j < r[i].size(); j++) {
				int sc;
				if (r[i][j] <= n) {
					sc = r[i][j] + n;
				}
				else {
					sc = r[i][j] - n;
				}
				if (binary_search(r[i].begin(), r[i].end(), sc)) {
					verified = false;
					break;
				}
			}
			if (!verified)break;
		}
	}

	vector<int> rr;
	vector<bool> rr2(2*n+1);
	vector<int> vis(2 * n + 1, false);
	for (int i = r.size()-1; i >= 0 ; i--) {
		for (int j = 0; j < r[i].size(); j++) {
			if (!vis[r[i][j]]) {
				if (r[i][j] <= n) {
					vis[r[i][j]] = true;
					vis[r[i][j] + n] = true;
				}
				else {
					vis[r[i][j]-n] = true;
					vis[r[i][j]] = true;
				}
				rr.push_back(r[i][j]);
			}
		}
	}

	for (int i = 0; i < rr.size(); i++) {
		
		
		if (rr[i] <= n) {
			char c = ((rr[i] - 1) + 'a');
			cout << c << " = false" << endl;
			rr2[rr[i]] = false;
			rr2[rr[i]+n] = false;
		}
		else {
			char c = ((rr[i]-n - 1) + 'a');
			cout << c << " = true" << endl;
			rr2[rr[i]] = true;
			rr2[rr[i]-n] = true;
		}
		
	}
	
	/*for (int i = 0; i < rr2.size(); i++) {
		cout << i << " : " << rr2[i] << endl;
	}*/

	bool st = true, rst = true, init = true;;
	for (int i = 0; i < form.size(); i++) {
		bool res = false;
		for (int j = 0; j < form[i].size(); j++) {
			
			if (form[i][j] <= n) {
				res = res | !rr2[form[i][j]];
			}
			else {
				res = res | rr2[form[i][j]];
			}
			

			cout << form[i][j] << " ";
		}cout << "^ ";
		if (init) {
			init = false;
			rst = res;
		}
		else
			rst = rst & res;
		
		if (!rst)st = false;
	}cout << endl;
   
	cout << "Final result:" << endl;
	if (st) {
		cout << "TRUE" << endl;
	}
	else {
		cout << "IMPOSSIBLE" << endl;
	}

	if (verified) {
		cout << "RTRUE" << endl;
	}
	else {
		cout << "RIMPOSSIBLE" << endl;
	}
}
