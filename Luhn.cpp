
#include <iostream>
#include <time.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <vector>
#include <fstream> 
using namespace std;

string VALID_CODE(string num) {

    string cc;
    cc = num;

    int ind = 0;
    int sum = 0;
    for (int i = cc.length() - 1; i >= 0; i--) {
        if (ind % 2 == 0) {
            int n = (cc[i] - '0') * 2;
            if (n >= 10) {
                n = (n / 10) + (n % 10);
            }
            sum += n;
            
        }
        else {
            sum += (cc[i] - '0');
           
        }
        ind++;
    }

    int unit;
    if (sum % 10 != 0) {
        unit = 10 - (sum % 10);
        cc = cc + to_string(unit);
    }
    else {
        cc = cc + "0";
    }

    
    return cc;
        

}

string fill3(string n) {
    if (n.length() == 3) {
        return n;
    }
    if (n.length() == 2) {
        return '0' + n;
    }
    if(n.length() == 1) {
        return "00" + n;
    }
    return "0000";
}

string fill4(string n) {
    if (n.length() == 4) {
        return n;
    }
    if (n.length() == 3) {
        return '0' + n;
    }
    if (n.length() == 2) {
        return "00" + n;
    }
    if (n.length() == 1) {
        return "000" + n;
    }
    return "0000";
  
}

string toJSON(vector<string> cc, vector<string> cvv) {

    string ans = "{\"cc\" : [\n";

    for (int i = 0; i < cc.size(); i++) {
        ans += "\t{\n";
        ans += "\t\t\"cccode\" : \"" + cc[i] + "\",\n";
        ans += "\t\t\"cvv\" : \"" + cvv[i] + "\"\n";
        ans += "\t}";
        if (i < cc.size() - 1)
            ans += ",";
        ans += "\n";


    }

    ans += "]}\n";
    return ans;
}

string toJSONjs(vector<string> cc, vector<string> cvv) {

    string ans = "{\"cc\" : [";

    for (int i = 0; i < cc.size(); i++) {
        ans += "{";
        ans += "\"cccode\" : \"" + cc[i] + "\",";
        ans += "\"cvv\" : \"" + cvv[i] + "\"";
        ans += "}";
        if (i < cc.size() - 1)
            ans += ",";
        ans += "";


    }

    ans += "]}";
    return ans;
}

string toCSV(vector<string> cc, vector<string> cvv) {

    string ans = "CCCODE,CVV\n";
    for (int i = 0; i < cc.size(); i++) {
        ans += cc[i] + "," + cvv[i] + "\n";

    }

    return ans;

}

void Menu() {

    cout << "1 - Generate 5 cc code + cvv\n";
    cout << "2 - Generate nb cc code + cvv JSON format \n";
    cout << "3 - Generate nb cc code + cvv JSON js format\n";
    cout << "4 - Generate nb cc code + cvv CVV format\n";
    cout << "9 - Before 2, 3, 4 for saving in file (change path)\n";
    cout << "10 - choose 1 MasterCard, 2 Visa\n";
}

int main()
{
    srand(time(NULL));

    string cc = "8172032761370223";
    string path = "C:\\Users\\";// \\Documents\\";
    string type = "5";
    int a;

    Menu();

    while (cin >> a) {
        if (a == 's')break;

        if (a == 10) {
            cin >> a;
            if (a == 1) {
                type = "5";
            }
            else if (a == 2) {
                type = "4";
            }
            else {
                type = "5";
            }
            Menu();
            continue;
        }

        bool write_f = false;
        if (a == 9) {
            cin >> a;
            write_f = true;
        }

        int nb = 5;
        if (a == 2 || a == 3 || a == 4)
            cin >> nb;

        vector<string> ccode, cvv;
        for (int i = 0; i < nb; i++) {
            cc = type;
            cc += fill3(to_string(rand() % 1000));
            cc += fill4(to_string(rand() % 10000));
            cc += fill4(to_string(rand() % 10000));
            cc += fill3(to_string(rand() % 1000));

            string crc = VALID_CODE(cc);
            cout << to_string(i) + ": CCCODE-CVV " << crc << "-";
            string cv = fill3(to_string(rand() % 1000));
            cout << cv << endl;
            ccode.push_back(crc);
            cvv.push_back(cv);

        }

        if (a == 2) {
            string tjs = toJSON(ccode, cvv);
            if(!write_f)
                cout << tjs << endl;
            else {
                std::ofstream ofs;
                ofs.open(path+"cc.json", std::ofstream::out | std::ofstream::trunc);

                ofs << tjs;

                ofs.close();
            }
        }

        if (a == 3) {
            string tjjs = toJSONjs(ccode, cvv);
            if (!write_f)
                cout << tjjs << endl;
            else {
                std::ofstream ofs;
                ofs.open(path+"ccjs.json", std::ofstream::out | std::ofstream::trunc);

                ofs << tjjs;

                ofs.close();
            }
        }

        if (a == 4) {
            string tcs = toCSV(ccode, cvv);
            if (!write_f)
                cout << tcs << endl;
            else {
                std::ofstream ofs;
                ofs.open(path+"ccc.csv", std::ofstream::out | std::ofstream::trunc);

                ofs << tcs;

                ofs.close();
            }
        }

        Menu();
        
    }
    

}

/*
Commande menu

tape 1 enter
tape 2 enter 5(for 5 cccode json) enter
tape 3 enter 5(for 5 cccode json js) enter
tape 4 enter 5(for 5 cccode csv) enter
tape 9 enter 2 5(for saving in a file 5 cccode json) enter
tape 9 enter 3 5(for saving in a file 5 cccode json js) enter
tape 9 enter 4 5(for saving in a file 5 cccode csv) enter


*/
