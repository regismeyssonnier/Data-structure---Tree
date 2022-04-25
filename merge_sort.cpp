#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'countInversions' function below.
 *
 * The function is expected to return a LONG_INTEGER.
 * The function accepts INTEGER_ARRAY arr as parameter.
 */
 long swaps = 0;
 bool is_swap = false;
 void merge(vector<int> &arr, int start, int mid, int end){
     
     deque<int> left, right;
     /*cout << "before : " << endl;
     for(int i = start; i <= end;i++){
         cout << arr[i] << " ";
     }cout << endl;*/
   
     
     for(int i = start; i <= mid;i++){
        left.push_back(arr[i]);
        
     }
     
     for(int i = mid+1; i <= end;i++){
        right.push_back(arr[i]);
        
     }
     
     int indl = 0, indr = 0, inda = start;
     while(left.size() >0 && right.size() > 0){
         
         if(left[0] <= right[0]){
             arr[inda] =left[0];
             left.pop_front();
             
         }
         else{
             arr[inda] = right[0];
             right.pop_front();
            // cout << "left " << left.size() << endl;;
             swaps+=left.size();
         }
         inda++;
     }
     
     if(left.size() > 0){
         while(left.size() > 0){
             arr[inda] = left[0];
             left.pop_front();
             inda++;
         }
     }
      if(right.size() > 0){
         while(right.size() > 0){
             arr[inda] = right[0];
             right.pop_front();
             inda++;
             
         }
     }
     
     /*cout << "after : " << endl;
     for(int i = start; i <= end;i++){
         cout << arr[i] << " ";
     }cout << endl;*/
     
     
 }
 
 void merge_sort(vector<int> &arr, int start, int end){
     
     if(start >= end){
         return ;
     }
     
     int mid = (start+end)/2;
     merge_sort(arr, start, mid);
     merge_sort(arr, mid+1, end);
     merge(arr, start, mid, end);
 }

long countInversions(vector<int> arr) {

    long count = 0;
    
    swaps = 0;
    merge_sort(arr, 0, arr.size()-1);
    
    /*for(int i = 0; i < arr.size();i++){
        cout << arr[i] << " ";
    }cout << endl;*/
    
   
    return swaps;

}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string t_temp;
    getline(cin, t_temp);

    int t = stoi(ltrim(rtrim(t_temp)));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        string n_temp;
        getline(cin, n_temp);

        int n = stoi(ltrim(rtrim(n_temp)));

        string arr_temp_temp;
        getline(cin, arr_temp_temp);

        vector<string> arr_temp = split(rtrim(arr_temp_temp));

        vector<int> arr(n);

        for (int i = 0; i < n; i++) {
            int arr_item = stoi(arr_temp[i]);

            arr[i] = arr_item;
        }

        long result = countInversions(arr);

        fout << result << "\n";
    }

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
