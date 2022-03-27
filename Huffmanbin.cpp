// Huffman.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <fstream> 
#include <iterator>
using namespace std;
#include <vector>
#include <map>
#include <queue>

#include <string>

#define ll long long int



struct Node {
	Node(char _n, ll _w) { w = _w; n = _n; };
	ll w;
	unsigned char n;
	unsigned char a;
	Node* father;
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

void Encode_file(vector<Node*>& n, vector<Node*>& tex) {

	std::ofstream f("enc.txt", std::fstream::trunc | std::fstream::binary);

	int mx = -1;
	for (int i = 0; i < n.size(); i++) {
		//cout << n[i]->n << " " << n[i]->code << endl;
		mx = max(mx, (int)n[i]->code.length());
	}

	cout << "max length " << n.size() << endl;

	for (int i = n.size() - 2; i >= 0; i--) {
		//if (n[i]->n == 'r')continue;
		//n[i]->n = 'u';
		f << n[i]->n;// write character

		unsigned char sz = (unsigned char)n[i]->code.length();
		//cout << (int)sz << endl;

		f << sz;//write nb bit to read
				
		int szc = n[i]->code.length() / 8;
		double szcd = (double)n[i]->code.length() / 8.0;
		
		if ((double)szc < szcd)szc++;

		

		//cout << "nb octet " << szc << endl;

		unsigned char b = 0;
		//n[i]->code = "11111111";
		int l = 7;
		bool write = false;
		for (int j = 0; j < n[i]->code.length(); j++) {
			//cout << "l " << l << endl;
			write = false;
			if (n[i]->code[j] == '1') {
				b |= (1 << l);
				////cout << (int)b << " " << i <<endl;
			}
			l--;
			if (l == -1) {
				//cout << "b " << (int)b << endl;
				f << b;//write code bin
				//if(b == 0)cout << "b " << (int)b << " " << i << " " << n[i]->code[j]  << endl;
				l = 7;
				b = 0;
				write = true;
				
			}
		}

		if (!write) {

			f << b;//write code bin
			//if (b == 0)cout << "--b " << (int)b << " " << i << " "  << endl;
			//cout << "-b " << (int)b << endl;
		}
				
		//system("pause");
	}

	unsigned char b = 255;
	f << b << b;//end of table

	std::ifstream input("text.txt", std::ios::binary);

	// copies all data into buffer
	std::vector<unsigned char> s(std::istreambuf_iterator<char>(input), {});

	b = 0;
	int ib = 7;
	bool write = false;
	for (int i = 0; i < s.size(); i++) {

		for (int j = 0; j < tex.size(); j++) {
			if (s[i] == tex[j]->a) {
				
				for (int k = 0; k < tex[j]->code.length(); k++) {
					write = false;
					if (tex[j]->code[k] == '1') {
						b |= (1 << ib);
					}

					ib--;
					if (ib == -1) {
						f << b;
						ib = 7;
						b = 0;
						write = true;
					}

				}
								

			}
		}

	}

	if (!write) {
		f << b;
	}


}

void dfs_test(Node * &root, int &nb) {

	nb++;

	cout << root->n <<  " " << root->code << endl;

	if (root->sleft != nullptr) {
		dfs_test(root->sleft, nb);
	}
	if (root->sright != nullptr ) {
		dfs_test(root->sright, nb);
	}

}

void dfsdec(Node*& root, Node*& son, int i) {

	if (root == nullptr)return;
	if (i == son->code.length()-1) {
		if (son->code[i] == '0') {
			root->sleft = son;
			//cout << "left " << root->code << " " << son->code << endl;
		}
		else if (son->code[i] == '1')
		{
			root->sright = son;
			//cout << "right " << root->code << " " << son->code << endl;
		}
		//cout << i << " " << son->code.length() - 1 << endl;
		//cout << "son " <<son->n << endl;
		//son->sleft = nullptr;
		//son->sright = nullptr;
		return;
	}
	
	///cout << "coder  " << root->code[i] << " " << root->code << endl;
	///cout << "code   " << son->code[i] << " " << son->code << endl;
	//cout << i << " " << son->code.length() - 1 <<  " " << root->n <<endl;
	
	if (root->sleft != nullptr ){
		if (son->code[i] == '0') {
			//cout << "lleft" << endl;
			//i++;
			dfsdec(root->sleft, son, i+1);
			
		}
	}
	if (root->sright != nullptr ){
		if(son->code[i] == '1') {
			//i++;
			//cout << "rright" << endl;
			//i++;
			dfsdec(root->sright, son, i+1);
			
		}
	}
	


}

unsigned char dfs_decode(Node*& root, int i, vector<unsigned char> s, int &j, int &r, vector<char> &c, int &ind, int ro) {

	if (i == -1) {
		i = 7;
		j++;
		if (j == s.size())return '0';
		//cout << -1 << endl;
		r = -1;
		//return '0';
	}

	int code;
	code = s[j] & (1 << i);

	//cout << ro << " " << root->n << " " << i << " j " << j << endl;
	//cout << root->sleft << endl;
	//cout << root->sright << endl;
	if (root->sleft == nullptr && ro == 0) {
		r = 1;
		ind = i;
		//cout << "left " << 0 << endl;
		c.push_back(root->n);
		return root->n;
	}

	if (root->sright == nullptr && ro > 0) {
		r = 1;
		ind = i;
		//cout << "right " << 1 << endl;
		c.push_back(root->n);
		return root->n;
	}
	

	
	//cout << "code " << code << " i " << i << " j " << j <<endl;
	//cout << root->a << endl;
	

	if ( code == 0) {
		//cout << "-left " << 0 << endl;
		
		dfs_decode(root->sleft,  i-1, s, j, r, c, ind, code);
	}

	if ( code > 0) {
		//cout << "-right " << 1 << endl;
		
		dfs_decode(root->sright,  i-1, s, j, r, c, ind, code);
	}

}

void Decode_file(vector<Node*>& n) {

	std::ifstream input("enc.txt", std::ios::binary);

	// copies all data into buffer
	std::vector<unsigned char> s(std::istreambuf_iterator<char>(input), {});
	cout << "read " << endl;

	/*for (int i = 0; i < s.size(); i++) {

		if (s[i] == 255 && s[i + 1] == 255)break;
		int szc = s[i] / 8;
		double szcd = (double)s[i] / 8.0;

		if ((double)szc < szcd)szc++;
		cout << (int)s[i] << " " << szc<< endl;

	}*/

	
	unsigned char b, letter;
	int i, I;
	for (i = 0; i < s.size(); i++) {

		if (s[i] == 255 && s[i + 1] == 255)break;

		letter = s[i];
		//cout << "letter " << letter << endl;
		i++;

		unsigned int nb_byte = s[i];
		//cout << "size : " << nb_byte << endl;

		Node* no = new Node(letter, 0);
		
		int szc = s[i] / 8;
		double szcd = (double)s[i] / 8.0;

		if ((double)szc < szcd)szc++;
		//cout << "size : " << szc << endl;

		i++;
		
		string r;
		for (int j = 0; j < szc; j++) {
			//cout << "si " << (int)s[i] << endl;
			for (int k = 7; k >= 0; k--) {
				if ((s[i] & (1 << k)) > 0) {
					r += '1';
				}
				else {
					r += '0';
				}
				nb_byte--;
				if (nb_byte == 0)break;
			}
			if (nb_byte == 0)break;
			i++;
		}
		

		no->code = r;

		//cout << r << endl;

		n.push_back(no);

	}
	I = i+2;
	
	Node* root = new Node('r', 0);
	root->code = '3';
	root->sleft = nullptr;
	root->sright = nullptr;
	n.push_back(root);

	//sort(n.begin(), n.end(), [](Node* a, Node* b) {return a->code < b->code; });

	for (int i = 0; i < n.size()-1; i++) {
		//cout << "node " << n[i]->n << " " << n[i]->code << endl;
		Node* son = new Node(n[i]->n, 0);
		son->a = n[i]->a;
		son->n = n[i]->n;
		son->code = n[i]->code;
		son->sleft = nullptr;
		son->sright = nullptr;

		dfsdec(root, son, 0);

		//cout << n[i]->code << endl;;

	}

	int nb = 0;

	//dfs_test(root, nb);
	//cout << "nb " << nb << " " << n.size() << endl;

	string texte;
	int ind = 7;
	int r = 0;
	int index = 0;
	vector<char> ch;
	for (int j = I;  j < s.size(); ) {
		//cout << (int)s[j] << endl;
		unsigned char c = dfs_decode(root, ind, s, j, r, ch, index, -1);
		if (r == 1) {
			//cout << c;
			ind = index;
			/*f(ind == 0) {
				ind = 7;
				j++;
				
			}*/
		}
		else {
			ind = 7;
			j++;
		}
		//cout <<j << " " << s.size() << endl;
		//cout << " - "<< j;
	}
	cout << endl;
	
	

	std::ofstream f("dec.txt", std::fstream::trunc | std::fstream::binary);

	for (int i = 0; i < ch.size(); i++) {
		//cout << ch[i];
		f << ch[i];
	}

	/*for (int i = 0; i < n.size(); i++) {
		cout << n[i]->n << " " << n[i]->code << endl;
		
	}*/

}


void dfs(Node*& root, int num) {

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
	/*string s; = "AABACDACA f !!!!!!!!!!!ofzen ezofizeoif opiejzf ze^pji ";
	s += "osndfjosdipf fopezfpze fç)ezf à)z)çf à)r à)z izejeh rzàerhezrz er";
	s += "pjsgfsdjfpsdjfpsdf,r perit reptitàer çt";
	*/

	/*ifstream myfile("text.txt");
	string line;
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			s += line;
		}
		myfile.close();
	}
	else {
		cout << "Unable to open file";
		return 0;
	}*/

	
	std::ifstream input("text.txt", std::ios::binary);

	// copies all data into buffer
	std::vector<unsigned char> s(std::istreambuf_iterator<char>(input), {});

	cout << s.size() << endl;
	map<char, ll> f;

	for (int i = 0; i < s.size(); i++) {

		f[s[i]]++;

	}

	int countb = 0;
	vector<Node*> Byte, DelByte;
	priority_queue < Node*, vector <Node*>, CompNode > p(CompNode(true));
	for (auto& e : f) {
		countb += e.second;
		Node* n = new Node(e.first, e.second);
		n->a = e.first;
		n->sleft = nullptr;
		n->sright = nullptr;
		p.push(n);
		Byte.push_back(n);
		DelByte.push_back(n);
		//cout << e.first << " " << e.second << endl;
	}
	countb *= 8;

	Node* first = nullptr;
	Node* second = nullptr;
	Node* root = nullptr;
	if (s.size() == 1) {
		root = p.top();
		Byte.push_back(first);
		p.pop();
	}
	else {
		while (p.size() > 1) {
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
		//root = new Node('r', first->w + second->w);
		root = p.top();
		root->n = 'r';
		p.pop();
		//root->code = '1';
		//first->father = root;
		//second->father = root;
		//root->sleft = second;
		//root->sright = first;
		//DelByte.push_back(root);

	}

	dfs(root, -1);

	

	int huff = 0;
	for (int i = 0; i < Byte.size(); i++) {
		//cout << Byte[i]->n << " " << Byte[i]->code << endl;
		huff += Byte[i]->code.length() * f[Byte[i]->n];
	}

	cout << "Text : " << countb << " bits huffman " << huff << " bits " << endl;
	cout << " soit " << (1.0 - ((double)huff / (double)countb)) * 100.0 << "% compression" << endl;

	int mx = -1, total = 0;
	for (int i = 0; i < DelByte.size(); i++) {
		//cout << DelByte[i]->n << " " << DelByte[i]->code << endl;
		total += DelByte[i]->code.length();
		mx = max(mx, (int)DelByte[i]->code.length());
	}
	cout << "max length " << mx << endl;
	total = total/8  + DelByte.size();

	cout << "total " << total << endl;
	cout << "size " << DelByte.size() << endl;;
	Encode_file(DelByte, Byte);
	cout << "end encoding" << endl;
	vector<Node*> n;
	Decode_file(n);

	cout << endl << "---------------------------------" << endl;
	/*bool equal = true;
	int j = DelByte.size() - 2;
	for (int i = 0; i < n.size()-1; i++) {
		//cout << n[i]->n << " " << DelByte[j]->n << endl;
		//cout << n[i]->code << " " << DelByte[j]->code << endl;;
		if (n[i]->code != DelByte[j]->code) {
			equal = false;
			//break;
		}
		//cout << i << " " << j << endl;
		j--;
	}*/

	//if (equal)cout << "Equal" << endl;
	//else cout << "not equal " << endl;

	//cout << (1 << 7) << endl;
	for (int i = 0; i < DelByte.size(); i++) {
		delete DelByte[i];
	}

	

}

