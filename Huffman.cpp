// Huffman.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <fstream> 
using namespace std;
#include <vector>
#include <map>
#include <queue>

#include <string>

#define ll long long int

struct Node {
	Node( char _n, ll _w ) { w = _w; n = _n; };
	ll w;
	char n;
	Node *father;
	Node* sleft;
	Node* sright;
	void Set_Code(char c) {
		code += c;
	};
	string code;
};
class CompNode
{
	bool reverse;
public:
	CompNode(const bool& revparam = false)
	{
		reverse = revparam;
	}
	bool operator() (const Node* lhs, const Node* rhs) const
	{
		if (reverse) return (lhs->w > rhs->w);
		else return (lhs->w < rhs->w);
	}
};

void dfs(Node *&root, int num) {
		
	if (num == 0) {
		
		root->code += root->father->code + '0';
	}
	else if (num == 1) {
		
		root->code += root->father->code + '1';
	}

	if (root->sleft != nullptr) {
		dfs(root->sleft, 0);
	}
	if (root->sright != nullptr) {
		dfs(root->sright, 1);
	}
}

int main()
{
	string s;/* = "AABACDACA f !!!!!!!!!!!ofzen ezofizeoif opiejzf ze^pji ";
	s += "osndfjosdipf fopezfpze fç)ezf à)z)çf à)r à)z izejeh rzàerhezrz er";
	s += "pjsgfsdjfpsdjfpsdf,r perit reptitàer çt";
	*/

	ifstream myfile("text.txt");
	string line;
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			s += line;
		}
		myfile.close();
	}
	else cout << "Unable to open file";

	map<char, ll> f;

	for (int i = 0; i < s.length(); i++) {

		f[s[i]]++;

	}

	int countb = 0;
	vector<Node*> Byte, DelByte;
	priority_queue < Node*, vector <Node*>, CompNode > p(CompNode(true));
	for (auto &e : f) {
		countb += e.second;
		Node* n = new Node(e.first, e.second);
		n->sleft = nullptr;
		n->sright = nullptr;
		p.push(n);
		Byte.push_back(n);
		DelByte.push_back(n);
		//cout << e.first << " " << e.second << endl;
	}
	countb *= 8;
	
	Node* first=nullptr;
	Node* second = nullptr;
	Node* root = nullptr;
	if (s.length() == 1) {
		root = p.top();
		Byte.push_back(first);
		p.pop();
	}
	else {
		while (p.size()> 1) {
			//cout << p.top().n << " " << p.top().w << endl;
			first = p.top();
			p.pop();

			second = p.top();
			p.pop();

			Node* father = new Node('u', first->w + second->w);
			first->father = father;
			second->father = father;
			//if (first->w > second->w) {
				father->sleft = first;
				father->sright = second;
			/* }
			else {
				father->sleft = second;
				father->sright = first;
			}*/
			p.push(father);
			DelByte.push_back(father);
		
		}
		root = new Node('r', first->w + second->w);
		//root->code = '1';
		first->father = root;
		second->father = root;
		root->sleft = second;
		root->sright = first;
		DelByte.push_back(root);

	}
	
	dfs(root, -1);
	
	int huff = 0;
	for (int i = 0; i < Byte.size(); i++) {
		cout << Byte[i]->n << " " << Byte[i]->code << endl;
		huff += Byte[i]->code.length();
	}

	cout << "Text : " << countb << " bits huffman " << huff << " bits "<< endl;
	cout << " soit " << (1.0-((double)huff / (double)countb)) * 100.0 << "% compression" << endl;

	for (int i = 0; i < DelByte.size(); i++) {
		delete DelByte[i];
	}

}

