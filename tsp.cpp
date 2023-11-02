#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
#include <map>
#include <queue>
#include <math.h>
#include <random>
#include <chrono>
#include <deque>
using namespace std::chrono;
using namespace std;


/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

vector<vector<int>>g(1001, vector<int>(1801, 0));
vector<vector<int>>gr(305);

struct Edge {
    int ng;
    list<Edge>::iterator it;
    Edge(int _adj) : ng(_adj) {}
};

map<pair<int, int>, int>medges;
map<pair<int, int>, int>mednum;
map<int, bool>msom;
vector<int> path, path2;
vector<list<Edge>> lg;
vector<bool>vis(301, false);
void Hierholzer(int v) {
    

    while (lg[v].size() > 0) {
        int adj = lg[v].front().ng;
        //lg[adj].erase(lg[v].front().it);
        lg[v].pop_front();
        Hierholzer(adj);
    }
 

    path2.push_back(v);
    //cerr << v << endl;
    if(msom.count(v) == 0 ){
        vis[v] = true;
        path.emplace_back(v);
        msom[v] = true;
        //if(path.size() > 0 && medges.count({ v, path[path.size() - 1]  }) > 0) {
            
        //}

    }

   
}

vector<int> p;
vector<int> r;

int get(int a) {
    return p[a] = (p[a] == a ? a : get(p[a]));
}

void _union(int a, int b) {
    a = get(a);
    b = get(b);
    if (r[a] == r[b])
        r[a]++;
    if (r[a] > r[b])
        p[b] = a;
    else
        p[a] = b;

}


double distance(int x, int y, int x2, int y2){
    return sqrt((x-x2)*(x-x2) + (y-y2)*(y-y2));
}

vector<pair<int, int>>vs;
double calc_dist(vector<int> &p, int n){

    double td = 0;
    for(int i = 0;i < p.size();++i){
        td += distance(vs[p[i]].first, vs[p[i]].second, vs[p[(i+1)%p.size()]].first, vs[p[(i+1)%p.size()]].second);
    }

    return td;

}

void dfs(int s){

    vis[s] = true;
    path.push_back(s);

    for(int i = 0;i < gr[s].size();++i){
        if(!vis[gr[s][i]]){
            dfs(gr[s][i]);
        }
    }

    


}

int main()
{
    
    int n; // This variables stores how many nodes are given
    cin >> n; cin.ignore();
    int num = 0;
    
    

    for (int i = 0; i < n; i++) {
        int x; // The x coordinate of the given node
        int y; // The y coordinate of the given node
        cin >> x >> y; cin.ignore();
        //g[y][x] = 1000;
       // x*=2, y*=2;
        mednum[{x, y}] = num;
        vs.push_back({x, y});
        num++;
    }

    auto startm = high_resolution_clock::now();

    p.resize(n+1, 0);
    r.resize(n+1, 0);

    for (int j = 0; j <= n; j++)
        p[j] = j;



    

    

    //sort(vs.begin(), vs.end());
    //random_shuffle(vs.begin(), vs.end());
    


    lg.resize(n+1);
    vector<pair<int, pair<int, int>>>edges;

    
  
    int d1=1000000, d2 = 1000000;
    int ind1, ind2;
    for(int i = 0;i < vs.size();++i){
        vector<pair<double, int>>vd;
        int count = 0;
        for(int j = 0;j < vs.size();++j){
            if(i == j)continue;
            
            double d = distance(vs[i].first, vs[i].second, vs[j].first, vs[j].second);
            //cerr << d << endl;
            vd.push_back({d, j});
           

        }

        sort(vd.begin(), vd.end());

        int nb = 0;
        for(int j = 0;j < vd.size();++j){
            int x = mednum[{vs[i].first, vs[i].second}];
            int y = mednum[{vs[vd[j].second].first, vs[vd[j].second].second}];

            //int d = distance(vs[x].first, vs[x].second, vs[y].first, vs[y].second);
            //if(medges.count({x, y}) == 0 && medges.count({y, x}) == 0  ){

               edges.push_back({vd[j].first, {x, y}});
               //edges.push_back({vd[j].first, {y, x}});
                //cerr << x << " " << y << endl;
                medges[{x, y}]++;
                medges[{y, x}]++;
                
                int a = x;
                int b = y;
              
                lg[a].emplace_front(b);
                lg[b].emplace_front(a);
                //lg[a].begin()->it = lg[b].begin();
                //lg[b].begin()->it = lg[a].begin();
                nb++;
                if(nb == 4)break;
           // }

        }

    }

    //Hierholzer(0);
    


    /*
    for(int i = 0;i < vs.size();++i){
        vector<pair<double, int>>vd;
        int count = 0;
        for(int j = 0;j < vs.size();++j){
            if(i == j)continue;
            int x = mednum[{vs[i].first, vs[i].second}];
            int y = mednum[{vs[j].first, vs[j].second}];
            //if(medges.count({x, y}) == 0 && medges.count({y, x}) == 0  ){
               
                //cerr << x << " " << y << endl;
                medges[{x, y}]++;
                medges[{y, x}]++;
                double d = distance(vs[i].first, vs[i].second, vs[j].first, vs[j].second);
                //cerr << d << endl;
                edges.push_back({d, {mednum[{vs[i].first, vs[i].second}], mednum[{vs[j].first, vs[j].second}]}});
            
            //}

        }

    }*/


    sort(edges.begin(), edges.end(), [](pair<int, pair<int, int>> a, pair<int, pair<int, int>> b) {
        return a.first < b.first;
        });

    
    vector<pair<int, int>>ve;
    int count = 0;
    int  w = 0;
    for (const auto e : edges) {
        if (get(e.second.first) != get(e.second.second)) {
            _union(e.second.first, e.second.second);
            ve.push_back({e.second.first, e.second.second});
            gr[e.second.first].push_back((e.second.second));
            gr[e.second.second].push_back((e.second.first));

            w += e.first;
            ++count;
        }

    }

    cerr << w << endl;


    dfs(0);

    /*for(int i = 0;i < path2.size();++i){
        cerr << path2[i] << " " ;
        //cerr << path[i] << " " ;
    }
    cerr << endl;*/


    

    double td = calc_dist(path, n);
 
    cerr << "distance " <<  td << endl;

    
    
    //startm = high_resolution_clock::now();
    auto getTime2 = [&]()-> bool {
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - startm);
        return(duration.count() <= 5000);
    };

    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dij(0, n-1);

    int i = n-1;
    while(getTime2()){
        
        //for(int j = 0;j < n;++j){
        for(int j = n-1;j>=0;--j){


            
            //int s = dij(rng), e = dij(rng);
            //int ss = min(e, s);
            //int ee = max(e,s);
            //s = ss, e = ee;
            int s = min(i, j);
            int e = max(i, j);
            int ls = s, le = e;
            while(s < e){
                //int tmp = path[s];
                //path[s] = path[e];
                //path[e] = tmp;

                path[s] = path[s] ^ path[e];
                path[e] = path[s] ^ path[e];
                path[s] = path[s] ^ path[e];

                s++;
                e--;
            }
        
            double d2 = calc_dist(path, n);

            if(d2 > td){
                int s = ls, e = le;
                while(s < e){
                    //int tmp = path[s];
                    //path[s] = path[e];
                    //path[e] = tmp;

                    path[s] = path[s] ^ path[e];
                    path[e] = path[s] ^ path[e];
                    path[s] = path[s] ^ path[e];

                    s++;
                    e--;
                }
                
            }
            else{
                td = d2;
                
            }
                    


        }

        //i = (i+1)%n;
        i = (i-1+n)%n;

    }

/*
    int i = n-1;
    while(getTime2()){

        int ii = (i+1)%n;

        
        
        for(int j = 0;j < n;++j){
        //for(int j = n-1;j>=0;--j){

            if(i == j)continue;

            double c1 = distance(vs[path[i]].first, vs[path[i]].second, vs[path[ii]].first, vs[path[ii]].second);

            int jj = (j+1)%n;
            double c2 = distance(vs[path[j]].first, vs[path[j]].second, vs[path[jj]].first, vs[path[jj]].second);

            double c3 = distance(vs[path[i]].first, vs[path[i]].second, vs[path[j]].first, vs[path[j]].second);
            double c4 = distance(vs[path[ii]].first, vs[path[ii]].second, vs[path[jj]].first, vs[path[jj]].second);

            

            if(c1 >c3+c4){
                int s = min(i, j);
                int e = max(i, j);
                int ls=s, le = e;
                while(s < e){
                    int tmp = path[s];
                    path[s] = path[e];
                    path[e] = tmp;
                    s++;
                    e--;
                }

                double d2 = calc_dist(path, n);

                if(d2 > td){
                    int s = ls, e = le;
                    while(s < e){
                        int tmp = path[s];
                        path[s] = path[e];
                        path[e] = tmp;
                        s++;
                        e--;
                    }
                    
                }
                else{
                    td = d2;
                    
                }
                
            }
                   


        }

        i = (i+1)%n;
        //i = (i-1+n)%n;

    }
    */

    //startm = high_resolution_clock::now();
    /*auto getTime1 = [&]()-> bool {
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - startm);
        return(duration.count() <= 4500);
    };
    int i = 0;

    while(getTime1()){
        
       
            int s = vs[i].first;
            int e = vs[(i+1)%ve.size()].first;
            int ls = s, le = e;
            while(s < e){
                int tmp = path[s];
                path[s] = path[e];
                path[e] = tmp;
                s++;
                e--;
            }
        
            double d2 = calc_dist(path, n);

            if(d2 > td){
                int s = ls, e = le;
                while(s < e){
                    int tmp = path[s];
                    path[s] = path[e];
                    path[e] = tmp;
                    s++;
                    e--;
                }
                
            }
            else{
                td = d2;
                
            }
                    

            i = (i+1)%ve.size();

        //}

        //i = (i+1)%n;
        //i = (i-1+n)%n;

    }*/

    
    

    cerr << "distance " <<  td << endl;

    int indz  = 0;
    for(int i = 0;i < path.size();++i){
        //cerr << path[i] << " " ;
        if(path[i] == 0){
            indz = i;
            break;
        }
        //cerr << path[i] << " " ;
    }
    //cerr << endl;

    /*for(int i = 0;i < path2.size();++i){
        cerr << path2[i] << " " ;
        //cerr << path[i] << " " ;
    }cerr << endl;*/

    int j = 0;
    i = indz;
    while(j < path.size()+1){
        cout << path[i] << " ";
        i = (i+1)%n;
        j++;
    }


    /*cout << 0 << " " ;
    for(int i = 0;i < path.size();++i){
        cout << path[i] << " " ;
        //cerr << path[i] << " " ;
    }*/
    

    
    cout << endl;


}