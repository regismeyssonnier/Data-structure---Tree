// Trie.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Node {

	Node *son[256];
	bool end_mark = false;

	Node() {
		for (int i = 0; i < 256; i++) {
			son[i] = NULL;
		}
		end_mark = false;
	}

};

struct trie {
	Node* root;
	
	trie(){
		root = new Node();
	}

	

	void Add(string s) {

		Node* curr = root;

		for (int i = 0; i < s.length(); i++) {
			if (curr->son[(int)s[i]] == NULL) {
				curr->son[(int)s[i]] = new Node();
				
			}

			curr = curr->son[(int)s[i]];
			
		}

		curr->end_mark = true;

	}

	bool Search(string s) {
		Node* curr = root;
		if (s.length() == 0)return false;

		for (int i = 0; i < s.length(); i++) {
			
			if (curr->end_mark && i < s.length() -1) {
				return true;
			}
			curr = curr->son[(int)s[i]];
			if (curr == NULL) {
				return false;
			}
			
		}

		return false;

	}

	bool Exist(string s) {

		Node* curr = root;
		if (s.length() == 0)return false;

		for (int i = 0; i < s.length(); i++) {
						
			curr = curr->son[(int)s[i]];
			if (curr == NULL ) {
		
				return false;
			}

		}

		if (curr != NULL && curr->end_mark)
			return true;
		else return false;


	}

	
};


int main()
{
	trie t;

	t.Add("aadfabbb");
	t.Add("aaab");
	t.Add("bbbc");
	t.Add("bcbcggfg");

	if (t.Search("bbbcfgegr")) {
		cout << "have prefix " << endl;
	}
	else {
		cout << "have not a prefix " << endl;
	}

	if (t.Exist("bcbcggfg")) {
		cout << "exists " << endl;
	}
	else {
		cout << "doesnt exist " << endl;
	}
		

}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
