
#include <iostream>
#include <time.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
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

int main()
{
    srand(time(NULL));

    string cc = "8172032761370223";

    int a;

    while (cin >> a) {
        if (a == 's')break;

        for (int i = 0; i < 5; i++) {
            cc = "5";
            cc += fill3(to_string(rand() % 1000));
            cc += fill4(to_string(rand() % 10000));
            cc += fill4(to_string(rand() % 10000));
            cc += fill3(to_string(rand() % 1000));

            cout << "CCCODE-CVV " << VALID_CODE(cc) << "-";
            cout << fill3(to_string(rand() % 1000)) << endl;
        }
        
    }
    

}

