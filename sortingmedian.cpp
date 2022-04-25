#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'activityNotifications' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY expenditure
 *  2. INTEGER d
 */

double cs(vector<int>& arr)
{
    int max = *max_element(arr.begin(), arr.end());
    int min = *min_element(arr.begin(), arr.end());
    int range = max - min + 1;
 
    vector<int> count(range), output(arr.size());
    for (int i = 0; i < arr.size(); i++)
        count[arr[i] - min]++;
 
    for (int i = 1; i < count.size(); i++)
        count[i] += count[i - 1];
 
    for (int i = arr.size() - 1; i >= 0; i--) {
        output[count[arr[i] - min] - 1] = arr[i];
        count[arr[i] - min]--;
    }
 
    /*for (int i = 0; i < arr.size(); i++)
        arr[i] = output[i];*/
    int med = arr.size() / 2;
    int ans = 0;
    if(arr.size() & 1){
        return output[med];
    }
    else
    {
        return (double)(output[med] + output[med-1]) / 2.0;    
    }
     
}

int activityNotifications(vector<int> e, int d) {

    //vector<int> m;
    int pd = 0;
    int notif = 0;
    vector<int> m;
    int med = d / 2;
    if(d & 1)med++;
    map<int, int> f;
    
    for(int i = 0;i < d;i++){
        f[e[i]]++;
        
    }
    
    
    for(int i = d;i < e.size();i++){
        
        double ans = 0;
        bool exact = false;
        int acc = 0;
        map<int, int>::iterator it, it2, it3;;
        for(it = f.begin(); it != f.end();it++){
            if(it->second == 0)continue;
            acc += it->second;
            it2 = it;
            it2++;
            if(d & 1){
                if(acc+it2->second == med){
                    exact = true;
                    ans = it2->first;
                    break;
                }
                else if(acc+it2->second > med){
                    exact = true;
                    ans = it2->first;
                    break;
                }
            }
            else{
                it3 = it2;
                it3++;
                if(acc+it2->second == med){
                    exact = true;
                    ans = (double)(it2->first + it3->first) / 2.0;
                    break;
                }
                else if(acc+it2->second > med){
                    ans = it2->first ;
                    exact = true;
                    
                    break;
                }
                
            }
            
        }
        
        f[e[pd]]--;
        f[e[i]]++;
        
        pd++;
        double median ;
                 median = ans;
        
        cout << median << endl;
     
        if((double)e[i] >= 2.0*median){
            notif++;
        }
    }
    
    return notif;

}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int n = stoi(first_multiple_input[0]);

    int d = stoi(first_multiple_input[1]);

    string expenditure_temp_temp;
    getline(cin, expenditure_temp_temp);

    vector<string> expenditure_temp = split(rtrim(expenditure_temp_temp));

    vector<int> expenditure(n);

    for (int i = 0; i < n; i++) {
        int expenditure_item = stoi(expenditure_temp[i]);

        expenditure[i] = expenditure_item;
    }

    int result = activityNotifications(expenditure, d);

    fout << result << "\n";

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
