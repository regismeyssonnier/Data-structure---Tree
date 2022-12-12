#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

struct heap{
    int h[200005];
    int size;
    int I;
    int capacity;
    heap(){
        size = 0;
        I = 0;
        capacity = 200005;
    }
    
    int top(){
        return h[0];        
    }
    void push(int n){
        if(size < capacity){
            h[size] = n;
            int j = size;
            while(true){
                int p = (j-1) / 2;
                if(h[j] < h[p]){
                    int tmp = h[p];
                    h[p] = h[j];
                    h[j] = tmp;
                    j = p;
                    if(j == 0)break;
                }   
                else{
                    break;
                }             
            }
            
            
            size++;
        }
        else{
            cerr << "HEAP FULL" << endl;
        }
    }
    
    void remove(int n){
        bool fi = false;
        int id = 0;
        for(int i = 0;i < size;i++){
            if(h[i] == n){
                id = i;
                fi = true;
                break;
            }
        }      
        
        if(fi){
            int g , d;
            
            h[id] = h[size-1];
            
            int j = id;
            while(true){
                int p = (j-1) / 2;
                if(h[j] < h[p]){
                    int tmp = h[p];
                    h[p] = h[j];
                    h[j] = tmp;
                    j = p;
                    if(j == 0)break;
                }   
                else{
                    break;
                }             
            }
            
            
            while(true){
                g = 2 * id + 1;
                d = 2 * id + 2;
                if(g > size-1)g = -1;
                if(d > size-1)d = -1;
                
               // cout << id << " - " << g << " - " << d << endl;
                if(d == -1 && g == -1){
                    break;
                }
                
                if(d != -1 && g != -1){
                    if(h[g] <= h[d] && h[g] <= h[id]){
                        int tmp = h[id];
                        h[id] = h[g];
                        h[g] = tmp;
                        id = g;
                    }    
                    else if(h[g] > h[d] && h[d] <= h[id]){
                     
                        int tmp = h[id];
                        h[id] = h[d];
                        h[d] = tmp;
                        id = d;
                    } 
                    else{
                        break;
                    }
                                 
                }
                
                if(d == -1 && g != -1){
                    if(h[g] <= h[id]){
                        int tmp = h[id];
                            h[id] = h[g];
                            h[g] = tmp;
                            id = g;
                    }
                    else{
                        break;
                    }
                                
                }
                
                if(d != -1 && g == -1){
                    if(h[d] <= h[id]){
                        int tmp = h[id];
                            h[id] = h[d];
                            h[d] = tmp;
                            id = d;
                    }
                    else{
                        break;
                    }
                }
                
                
                
            }
            
            size--;
            
            //tasser();
            
        }
        else{
            cerr << "ELEMENT NOT FOUND" << endl;
        }
    }
    
    void tasser(){
        bool fi = false;
        int id = 0, idmini = 0;
        int mini = 2000000000;
        for(int i = 0;i < size;i++){
            if(h[i] < mini){
                id = i;
                idmini = i;
                mini = h[i];
                fi = true;
                break;
            }
        }      
        
        if(id != 0){
            int j = idmini;
            while(true){
                int p = (j-1) / 2;
                if(h[j] < h[p]){
                    int tmp = h[p];
                    h[p] = h[j];
                    h[j] = tmp;
                    j = p;
                    if(j == 0)break;
                }   
                else{
                    break;
                }             
            }
            
            
            /*int g , d;
            
            while(true){
                g = 2 * id + 1;
                d = 2 * id + 2;
                if(g > size-1)g = -1;
                if(d > size-1)d = -1;
                
               // cout << id << " - " << g << " - " << d << endl;
                if(d == -1 && g == -1){
                    break;
                }
                
                if(d != -1 && g != -1){
                    if(h[g] <= h[d]){
                        int tmp = h[id];
                        h[id] = h[g];
                        h[g] = tmp;
                        id = g;
                    }    
                    else{
                        int tmp = h[id];
                        h[id] = h[d];
                        h[d] = tmp;
                        id = d;
                    }                
                }
                
                if(d == -1 && g != -1){
                    
                    int tmp = h[id];
                        h[id] = h[g];
                        h[g] = tmp;
                        id = g;
                                    
                }
                
                if(d != -1 && g == -1){
                    
                    int tmp = h[id];
                        h[id] = h[d];
                        h[d] = tmp;
                        id = d;
                                    
                }
                
               
                
            }*/
                        
            
        }
        else{
            cerr << "MIN ELEMENT NOT FOUND" << endl;
        }
    }
    
};

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    
    //priority_queue<int, std::vector<int>, std::greater<int>> p;
    //priority_queue<int, std::vector<int>, std::greater<int>> p(v.begin(), v.end());
    
    int n;
    cin >> n;
    
    heap h;
    
    for(int i = 0;i < n;i++){
        int o;
        cin >> o;
        
        if(o == 1){
            int num;
            cin >> num;
            h.push(num);
        }
        else if (o == 2){
            int num;
            cin >> num;
            h.remove(num);
        }
        else if(o == 3){
            /*for(int i = 0;i < h.size;i++){
                cout << h.h[i] << " ";
            }
            cout << endl; */
            cout << h.top() << endl;
        }
    }
    
    
    return 0;
}
