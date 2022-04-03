// CompDecompression.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <bitset>
#include <chrono>
#include <ctime> 
#include <thread>
#include <string>
#include <WTypes.h>

using namespace std;

#define ll long long int

vector<unsigned int> ch;
vector<unsigned int> ch2, ch3;
thread th[10000];
thread thc[1000];
atomic<int> progress(0);
thread thp;
vector<vector<unsigned char>> sth(1000);

bool Existe(map<string, ll>& d, string a) {

	map<string, ll>::iterator itl = d.lower_bound(a);
	if (itl == d.end()) {

		return false;
		
	}
	else {
		if (itl->first == a) {
		
			return true;
		}
		else {
			return false;
		}
	}


}

bool Existe2(map<ll, string>& d, ll a) {

	map<ll, string>::iterator itl = d.lower_bound(a);
	if (itl == d.end()) {

		return false;

	}
	else {
		if (itl->first == a) {

			return true;
		}
		else {
			return false;
		}
	}


}

constexpr int byteleft(int a) {

	int b = a;
	int count = 0;
	while (b > 0) {
		count++;
		b = b / 2;
	}

	return count;

}

constexpr int byteleftc(char a) {

	int b = a;
	int count = 0;
	while (b > 0) {
		count++;
		b = b / 2;
	}

	return count;

}

vector<unsigned char> intToBytes(int paramInt)
{
	vector<unsigned char> arrayOfByte(4);
	for (int i = 0; i < 4; i++)
		arrayOfByte[3 - i] = (paramInt >> (i * 8));
	return arrayOfByte;
}

void Compress_LZW_slow(BSTR name, BSTR named) {

	//string s = "TOBEORNOTTOBEORTOBEORNOT";
			  //TOBEORNOTTOBEORTOBEORNOT
	std::ifstream input(name, std::ios::binary);

	// copies all data into buffer
	std::vector<char> s(std::istreambuf_iterator<char>(input), {});

	cout << "loaded" << endl;
	progress = 5;

	map<string, ll> d;

	for (int i = 0; i <= 255; i++) {
		string c;
		c += (char)i;
		d[c] = i;

	}

	

	ll NUM = 256;
	string w, p, c;
	//w += s[0];
	for (int i = 0; i < s.size(); i++) {
		p = w + s[i];
		//cout << p << endl;

		if (Existe(d, p)) {

			w = p;
		}
		else {
			ch.push_back(d[w]);

			d[p] = NUM;

			NUM++;
			w = s[i];

		}
		progress = 5 + (((double)i / (double)s.size()) * 75.0);;

	}

	ch.push_back(d[w]);
	d[p] = NUM;

	NUM++;

	progress = 10;

	std::ofstream f(named, std::fstream::trunc | std::fstream::binary);


	double po = 7;

	int IPS = 0;
	bool add = false;
	vector<int> ps;
	int count = 0;
	for (int k = 0; k < ch.size(); k++) {
		//cout << ch[k] << endl;
		add = false;
		if (ch[k] <= (pow(2, po + 1) - 1)) {
			count++;
		}
		else {
			add = true;
			ps.push_back(count);
			//std::cout << count << endl;
			count = 1;// k--;
			po++;
		}
	}

	if (!add) {
		ps.push_back(count);
		std::cout << count << endl;
	}

	int sum = 0;
	for (int i = 0; i < ps.size(); i++) {
		sum += ps[i];
	}
	cout << "sum " << sum << " " << ch.size() << endl;

	po = 7;

	unsigned char b = 0;

	//cout << ps[IPS] << endl;
	int l = 7;
	for (int i = 31; i >= 0; i--) {
		if (ps[IPS] & (1 << i)) {
			b |= (1 << l);
		}

		l--;
		if (l == -1) {
			l = 7;
			f << b;

			b = 0;
		}

	}
	//IPS++;

	progress = 15;

	int aps = 0;
	b = 7;
	f << b;// write power
	int i = 0;
	for (i = 0; i < ch.size(); i++) {
		if (ch[i] >= 0 && ch[i] <= 255) {
			b = ch[i];
			f << b;

			aps++;
		}
		else {

			break;
		}
	}
	cout << aps << " " << ps[IPS] << endl;
	po = 7;
	bool write = false, start = true;
	b = 0;
	int pui = 0;

	
	for (; i < ch.size(); i++) {
		progress = 80 + (((double)i / (double)ch.size()) * 20.0);
		
		if (aps == ps[IPS]) {
			po++; IPS++;
			
			if (!write && start == false) {
				f << b;
				write = true;
			}
			start = false;

			unsigned char bi = 0;
			int wx = 0;
			

			int pp[] = { 24, 16, 8, 0 };
			bi = 0;
			unsigned char b2 = 0;
			for (int j = 0; j < 4; j++) {
				bi = (ps[IPS] >> pp[j]);
				
				f << bi;
			}


			b = 0;
			pui = 7;
			
			aps = 0;
			unsigned char by = po;
			f << by;//write power
		}
		
		aps++;
		
		int d85 = 0;
		for (int j = po; j >= 0; j--) {
			write = false;
			if (ch[i] & (1 << j)) {
				b |= (1 << pui);
				d85 |= (1 << j);
			}
			
			pui--;
			if (pui == -1) {
				
				f << b;
				b = 0;
				pui = 7;
				write = true;
			}


		}
		

	}
	if (!write) {
		f << b;
	}


	progress = 100;

}

void Decompress_LZW_slow(BSTR name, BSTR named) {

	ll v;
	map<ll, string> di;
	for (int i = 0; i <= 255; i++) {
		string c;
		c = (char)i;
		di[i] = c;
	}
	ll NUM = 256;


	std::ifstream input(name, std::ios::binary);

	// copies all data into buffer
	std::vector<unsigned char> s(std::istreambuf_iterator<char>(input), {});

	int lasti = 0;
	int IPS = 0;
	unsigned char b;
	vector<int>ps;
	ch2.clear();
	int pb = 0;

	std::cout << "sz " << s.size() << endl;
	for (int i = 0; i < s.size(); ) {

		int a = int((unsigned char)(s[i]) << 24 |
			(unsigned char)(s[i + 1]) << 16 |
			(unsigned char)(s[i + 2]) << 8 |
			(unsigned char)(s[i + 3]));


		
		i += 4;
		ps.push_back(a);
		

		double po = s[i];
		
		i++;

		lasti = i;
	
		int o = 0;
		int l = 7;
		bool add = false;

		for (int j = 0; j < a; j++) {
			//l = 7;
			o = 0;

			for (int k = po; k >= 0; k--) {
				add = false;
				if (s[i] & (1 << l)) {
					o |= (1 << k);
				}
				l--;

				if (l == -1) {
					
					l = 7;
					i++;
					
					add = true;
				}
			}
			
			ch2.push_back(o);
			pb++;

		}

		

		if (!add)i++;
		

	}
	

	
	string out;
	string in;
	string x = di[ch2[0]];
	out = x;
	for (int i = 1; i < ch2.size(); i++) {
		v = ch2[i];

		if (Existe2(di, v)) {
			in = di[v];
		}
		else {
			in = x + x[0];
		}
		di[NUM] = x + in[0];
		NUM++;
		out += in;
		

		x = in;
	}

	/*for (auto e : di) {
		cout << e.first << " " << e.second << endl;
	}*/

	//cout << out << endl;
	std::ofstream f(named, std::fstream::trunc | std::fstream::binary);
	f << out;


}


void compress_th(vector<int> ps, int IPS, double po, int ind, int indsth) {

	int pp[] = { 24, 16, 8, 0 };

	int pui;
	unsigned char bi = 0, b = 0;
	unsigned char b2 = 0;


	
	for (int j = 0; j < 4; j++) {
		bi = (ps[IPS] >> pp[j]);
		
		sth[indsth].push_back(bi);
	}


	b = 0;
	pui = 7;
		
	bool write = false;
	unsigned char by = po;
	
	sth[indsth].push_back(by);

	
	for (int i = ind; i < ind + ps[IPS]; i++) {
		
		for (int j = po; j >= 0; j--) {
			write = false;
			if (ch[i] & (1 << j)) {
				b |= (1 << pui);

			}
			
			pui--;
			if (pui == -1) {
				
				sth[indsth].push_back(b);
				b = 0;
				pui = 7;
				write = true;
			}


		}

	}

	if (!write) {
		
		sth[indsth].push_back(b);
	}

	


}

void Compress_LZW_slow_th(BSTR name, BSTR named) {

	//string s = "TOBEORNOTTOBEORTOBEORNOT";
			  //TOBEORNOTTOBEORTOBEORNOT
	//cout << "fuck2" << endl;
	std::ifstream input(name, std::ios::binary);

	// copies all data into buffer
	std::vector<char> s(std::istreambuf_iterator<char>(input), {});

	cout << "loaded" << endl;

	map<string, ll> d;

	for (int i = 0; i <= 255; i++) {
		string c;
		c += (char)i;
		d[c] = i;

	}

	ll NUM = 256;
	string w, p, c;
	
	for (int i = 0; i < s.size(); i++) {
		p = w + s[i];
		

		if (Existe(d, p)) {

			w = p;
		}
		else {
			ch.push_back(d[w]);

			d[p] = NUM;

			NUM++;
			w = s[i];

		}

		progress = 5 + (((double)i / (double)s.size()) * 75.0);;
	}

	

	ch.push_back(d[w]);
	d[p] = NUM;

	NUM++;

	std::ofstream f(named, std::fstream::trunc | std::fstream::binary);


	double po = 7;

	int IPS = 0;
	bool add = false;
	vector<int> ps;
	int count = 0;
	for (int k = 0; k < ch.size(); k++) {
		
		add = false;
		if (ch[k] <= (pow(2, po + 1) - 1)) {
			count++;
		}
		else {
			add = true;
			ps.push_back(count);
			
			count = 1;
			po++;
		}
	}

	if (!add) {
		ps.push_back(count);
		std::cout << count << endl;
	}

	int sum = 0;
	for (int i = 0; i < ps.size(); i++) {
		sum += ps[i];
	}
	

	po = 7;

	unsigned char b = 0;

	
	int l = 7;
	for (int i = 31; i >= 0; i--) {
		if (ps[IPS] & (1 << i)) {
			b |= (1 << l);
		}

		l--;
		if (l == -1) {
			l = 7;
			f << b;

			b = 0;
		}

	}
	

	int aps = 0;
	b = 7;
	f << b;// write power
	int i = 0;
	for (i = 0; i < ch.size(); i++) {
		if (ch[i] >= 0 && ch[i] <= 255) {
			b = ch[i];
			f << b;

			aps++;
		}
		else {

			break;
		}
	}
	f.close();

	
	po = 8;
	bool write = false, start = true;
	b = 0;
	int pui = 0;

	IPS++;

	progress = 85;

	int indsth = 0;
	int indth = 0;
	for (int j = 1; j < ps.size(); j++) {
		
		thc[indth] = thread(compress_th, ps, j, po, i, indsth);
		indth++;
		po++;
		indsth++;
		
		
		i = i + ps[j];
		

		
	}

	for (int j = 0; j < indth; j++) {
		thc[j].join();

	}
	progress = 90;

	std::ofstream ff(named, std::fstream::app | std::fstream::binary);

	for (int j = 0; j < indsth; j++) {
		
		for (int k = 0; k < sth[j].size(); k++) {
			ff << sth[j][k];
		}
		progress = 90 + (((double)j / (double)indsth) * 10.0);
		
	}

		
	progress = 100;

}

void decompress_th_file(vector<unsigned char> s, ll a, ll i, ll po, ll ind) {

	int o = 0;
	int l = 7;
	bool add = false;

	for (int j = 0; j < a; j++) {
		//l = 7;
		o = 0;

		for (int k = po; k >= 0; k--) {
			add = false;
			if (s[i] & (1 << l)) {
				o |= (1 << k);
			}
			l--;

			if (l == -1) {
				
				l = 7;
				i++;

				add = true;
			}
		}

		ch2[ind] = o;
		ind++;

	}

}

void Decompress_LZW_slow_th(BSTR name, BSTR named) {

	ll v;
	map<ll, string> di;
	for (int i = 0; i <= 255; i++) {
		string c;
		c = (char)i;
		di[i] = c;
	}
	ll NUM = 256;


	std::ifstream input(name, std::ios::binary);

	// copies all data into buffer
	std::vector<unsigned char> s(std::istreambuf_iterator<char>(input), {});

	int lasti = 0;
	int IPS = 0;
	unsigned char b;
	vector<int>ps;
	ch2.clear();
	int pb = 0;

	ll size = 0;
	int counth = 0;
	for (int i = 0; i < s.size(); ) {
		int a = int((unsigned char)(s[i]) << 24 |
			(unsigned char)(s[i + 1]) << 16 |
			(unsigned char)(s[i + 2]) << 8 |
			(unsigned char)(s[i + 3]));
		i += 4;
		double po = s[i];
		i++;
		size += a;
		
		double r = ceil((double)a * (po + 1.0) / 8.0);
		i = i + r;
		
		counth++;

		progress = (((double)i / (double)s.size()) * 20.0);

	}

	

	ch2.resize(size, 0);

	
	
	int indth = 0;
	ll lasta = 0;
	for (int i = 0; i < s.size(); ) {
		int a = int((unsigned char)(s[i]) << 24 |
			(unsigned char)(s[i + 1]) << 16 |
			(unsigned char)(s[i + 2]) << 8 |
			(unsigned char)(s[i + 3]));
		i+=4;
		double po = s[i];
		
		i++;

		th[indth] = thread(decompress_th_file, s, a, i, po, lasta);
		indth++;

		
		double r = ceil((double)a * (po + 1.0) / 8.0);
		i = i + r;
		
		lasta += a;
	}

	for (int i = 0; i < indth; i++) {
		th[i].join();
	}

	progress = 80;

	
	string out;
	string in;
	string x = di[ch2[0]];
	out = x;
	for (int i = 1; i < ch2.size(); i++) {
		v = ch2[i];

		if (Existe2(di, v)) {
			in = di[v];
		}
		else {
			in = x + x[0];
		}
		di[NUM] = x + in[0];
		NUM++;
		out += in;
		

		x = in;

		progress = 80 + (((double)i / (double)ch2.size()) * 15.0);
	}

	/*for (auto e : di) {
		cout << e.first << " " << e.second << endl;
	}*/

	
	std::ofstream f(named, std::fstream::trunc | std::fstream::binary);
	f << out;

	progress = 100;

}

void Compress_LZW(BSTR name, BSTR named) {

	//string s = "TOBEORNOTTOBEORTOBEORNOT";
			  //TOBEORNOTTOBEORTOBEORNOT
	std::ifstream input(name, std::ios::binary);

	// copies all data into buffer
	std::vector<char> s(std::istreambuf_iterator<char>(input), {});
	
	cout << "loaded" << endl;
	progress = 5;
	map<string, ll> d;
	
	for (int i = 0; i <= 255; i++) {
		string c;
		c += (char)i;
		d[c] = i;
		
	}

	ll NUM = 256;
	string w, p, c;
	
	for (int i = 0; i < s.size(); i++) {
		p = w + s[i];
		

		if (Existe(d, p)) {

			w = p;
		}
		else {
			ch.push_back(d[w]);
		
			d[p] = NUM;

			NUM++;
			w = s[i];

		}
		progress = 5 + (((double)i / (double)s.size()) * 75.0);;
		
	}

	ch.push_back(d[w]);
	d[p] = NUM;

	NUM++;

	std::ofstream f(named, std::fstream::trunc | std::fstream::binary );
	
	
	double po = 7;

	int IPS = 0;
	bool add = false;
	vector<int> ps;
	int count = 0;
	for (int k = 0; k < ch.size(); k++) {
		
		add = false;
		if (ch[k] <= (pow(2, po + 1) - 1)) {
			count++;
		}
		else {
			add = true;
			ps.push_back(count);
			std::cout << count << endl;
			count = 1;
			po++;
		}
	}

	if (!add) {
		ps.push_back(count);
		std::cout << count << endl;
	}

	int sum = 0;
	for (int i = 0; i < ps.size(); i++) {
		sum += ps[i];
	}
	

	po = 7;

	unsigned char b = 0;

	
	int l = 7;
	for (int i = 31; i >= 0;i--) {
		if (ps[IPS] & (1 << i)) {
			b |= (1 << l);
		}

		l--;
		if (l == -1) {
			l = 7;
			f << b;
		
			b = 0;
		}
		
	}
	

	int aps = 0;
	b = 7;
	f << b;// write power
	int i = 0;
	for (i = 0; i < ch.size(); i++) {
		if (ch[i] >= 0 && ch[i] <= 255) {
			b = ch[i];
			f << b;
			
			aps++;
		}
		else {
			
			break;
		}
	}
	
	po = 7;
	bool write = false, start = true;
	b = 0;
	int pui = 0;

	progress = 85;
	
	
	for (; i < ch.size(); i++) {
		
		
		if(aps == ps[IPS]){
			po++; IPS++;
			
			start = false;

			unsigned char bi = 0;
			int wx = 0;
			

			int pp[] = { 24, 16, 8, 0 };
			bi = 0;
			unsigned char b2 = 0;
			for (int j = 0; j < 4; j++) {
				bi = (ps[IPS] >> pp[j]);
				
				f << bi;
			}
			
			
			b = 0;
			pui = 7;
			
			aps = 0;
			unsigned char by = po;
			f << by;//write power
		}
		
		aps++;
		
		int d85 = 0;
		

		
		
		
		vector<unsigned char> vu = intToBytes(ch[i]);
		int bl = byteleft(ch[i]);
		

		
		bool debut = true;
		int bl2;
		int decl = 0;;

		if (ch[i] == 0) {
			b = 3;
			f << b;
			b = 0;
			f << b;

		}
		else {


			for (int i = 0; i < 4; i++) {
				if (vu[i] != 0 && debut) {
					
					b = i;
					f << b;
					f << vu[i];
					debut = false;
				}
				else if (!debut) {
					f << vu[i];
				}
			}
		}

		progress = 85 + (((double)i / (double)ch.size()) * 15.0);

		

	}
	
		
}

void Decompress_LZW(BSTR name, BSTR named) {

	ll v;
	map<ll, string> di;
	for (int i = 0; i <= 255; i++) {
		string c;
		c = (char)i;
		di[i] = c;
	}
	ll NUM = 256;


	std::ifstream input(name, std::ios::binary);

	// copies all data into buffer
	std::vector<unsigned char> s(std::istreambuf_iterator<char>(input), {});

	int lasti = 0;
	int IPS = 0;
	unsigned char b;
	vector<int>ps;
	ch2.clear();
	int pb = 0;

	progress = 5;
	
	for (int i = 0; i < s.size(); ) {
		
		int a = int((unsigned char)(s[i]) << 24 |
					(unsigned char)(s[i+1]) << 16 |
					(unsigned char)(s[i+2]) << 8 |
					(unsigned char)(s[i+3]));

		
		
		i += 4;
		ps.push_back(a);
		

		double po = s[i];
		
		i++;

		lasti = i;
		
		int o = 0;
		int l = 7;
		bool add = false;

		int pp[] = { 24, 16, 8, 0 };

		if (po > 7) {
			for (int j = 0; j < a; j++) {
				int lz = s[i];
				i++;
				o = 0;
				for (int k = lz; k < 4; k++) {
					o |= s[i] << pp[k];
					i++;
				}
				ch2.push_back(o);

			}
		}
		else {
			for (int j = 0; j < a; j++) {
				o = s[i];
				ch2.push_back(o);
				i++;
			}
		}

		

		progress = 5 + (((double)i / (double)s.size()) * 80.0);

	}
	
	string out;
	string in;
	string x = di[ch2[0]];
	out = x;
	for (int i = 1; i < ch2.size(); i++) {
		v = ch2[i];

		if (Existe2(di, v)) {
			in = di[v];
		}
		else {
			in = x + x[0];
		}
		di[NUM] = x + in[0];
		NUM++;
		out += in;
		

		x = in;

		progress = 85 + (((double)i / (double)ch2.size()) * 10.0);
	}

	/*for (auto e : di) {
		cout << e.first << " " << e.second << endl;
	}*/

	//cout << out << endl;
	std::ofstream f(named, std::fstream::trunc | std::fstream::binary);
	f << out;

	progress = 100;

}

void get_progress() {

	while (progress < 100) {
		cout << progress << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
}

void init_progression() {
	progress = 0;
}

void get_progression() {

	if (progress == 0)
		thp = thread(get_progress);

}


int  get_progression_interface() {

	return progress;

}

void end_progression() {

	if (progress == 100)
		thp.join();

}


int main()
{
	/*auto start = std::chrono::system_clock::now();
	Compress_LZW("Project1.exe", "text.corm2");
	Decompress_LZW("text.corm2", "prfast.exe");
	auto end = std::chrono::system_clock::now();//144.133*/

	/*auto start = std::chrono::system_clock::now();
	Compress_LZW_slow("text3.txt", "textf2.corm2");
	Decompress_LZW_slow_th("textf2.corm2", "text3f.txt");
	auto end = std::chrono::system_clock::now();//139.291*/
	
	BSTR n1 = SysAllocString(L"text.txt");
	BSTR n2 = SysAllocString(L"textf.corm2");
	BSTR n3 = SysAllocString(L"textf.corm2");
	BSTR n4 = SysAllocString(L"text3fd.txt");

	auto start = std::chrono::system_clock::now();
	init_progression();
	get_progression();
	Compress_LZW_slow(n1, n2);
	//thread thb = thread(Compress_LZW_slow, "text.txt", "textf.corm2");
	//thb.join();
	end_progression();
	

	init_progression();
	get_progression();
	Decompress_LZW_slow_th(n3, n4);
	end_progression();
	auto end = std::chrono::system_clock::now();//63.9795
	
	//cth 64.082
	//c 63.888
	std::chrono::duration<double> elapsed_seconds = end - start;
	std::time_t end_time = std::chrono::system_clock::to_time_t(end);

	std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
	

	/*int sz = 0;
	for (auto e : d) {
		sz += e.first.length() + e.second;
	}

	for (int i = 0; i < ch.size(); i++) {
		cout << ch[i] << " " << (char)ch[i] << endl;
	}
	*/
	/*for (int i = 0; i < ch.size(); i++) {
		cout << di[ch[i]] << " ";
	}cout << endl;*/


	//cout <<"res = "<< out << endl;
	
	//cout << "taille " << s.size() << " compresser " << ch.size() << endl;
	

}
