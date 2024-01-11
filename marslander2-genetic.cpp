#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <algorithm>
#include <random>
#include <chrono>
#include <map>
#include <deque>
#include <cstdlib>
#include <ctime>
#include <cmath>
#define ll long long int 

using namespace std::chrono;

using namespace std;

struct Vector2{
    float x;
    float y;
    Vector2(){};
    Vector2(float xx, float yy):x(xx), y(yy){};
    
};

class Player{
public:
    int id;
    int x;
    int y;
    int light;
    int battery;
    int emergency;
    vector<int> scan;
    Player(){}
    Player(int I, int X, int Y, int L): id(I), x(X), y(Y), light(L), battery(30){
        

    }
};

class Sim{
public :
    
    Vector2 pos, speed;
    int fuel;
    int rotate;
    int power;
    ll score;
    int ind_zone;
    Sim(){

    }


};


class MarsLander{
public:

    int NB_SIM;
    int NB_POP;
    vector<Sim> population, next_gen;
    int turn_game = 0;
    int maxyz = 0;
    int haut_plateau = false;

    MarsLander(int nb_sim, int nb_pop): NB_SIM(nb_sim), NB_POP(nb_pop){

        std::mt19937 rng(std::random_device{}());
        std::uniform_int_distribution<int> drotate(-15, 15);
        std::uniform_int_distribution<int> dpower(0, 4);

        for(int i = 0;i < NB_POP;++i){
            Sim sm;
            sm.rotate = drotate(rng);
            sm.power = dpower(rng);
            sm.score = -1000000000;
            population.push_back(sm);
        }


    }

    void Selection(){
        next_gen = {};
        double sz = (double)population.size()*0.3;
        for(int i = 0;i < sz;++i){
            next_gen.push_back(population[i]);

        }

        std::mt19937 rng(std::random_device{}());
        std::uniform_int_distribution<int> dng(sz, population.size()-1);

        double sz2 = (double)population.size()*0.2;
        for(int i = 0;i<sz2;++i ){
            next_gen.push_back(population[dng(rng)]);
        }
       

    }

    void NextGen(){

        Selection();

        vector<Sim> children;

        std::mt19937 rng(std::random_device{}());
        std::uniform_int_distribution<int> dng(0, next_gen.size()-1);
        std::uniform_int_distribution<int> drotate(-15, 15);
        std::uniform_int_distribution<int> dpower(0, 4);
        std::uniform_int_distribution<int> dcross(0, 2);
        

        int nb_mutate = 0;
        int MAX_MUT = next_gen.size();
        while(children.size() < next_gen.size()){

            Sim par1 = next_gen[dng(rng)];
            Sim par2 = next_gen[dng(rng)];

            Sim child;
            child.rotate = par1.rotate;
            child.power = par2.power;
            child.score = -1000000000;

            if(nb_mutate < MAX_MUT){
                int dcr = dcross(rng);
                if(dcr == 0){
                    child.rotate = drotate(rng);
                    //child.score = par2.score;
                   
                }
                else if(dcr == 1){
                    child.power = dpower(rng);
                    //child.score = par1.score;
                
                }
                else if(dcr == 2){
                    child.rotate = drotate(rng);
                    child.power = dpower(rng);
                }
                ++nb_mutate;

            }

            children.push_back(child);

        }

        next_gen.insert(next_gen.end(), children.begin(), children.end());

        population.swap(next_gen);

        /*for(int i = 0;i < NB_POP;++i){
            cerr << "pos --pop = " << population[i].x << " " << population[i].y << endl;
        }*/


    }

    // Fonction pour simuler le Mars Lander
    void simulateLander(Sim &lander) {
        // Constantes physiques
        const double gravity = -3.711;  // Gravité sur Mars
        const double radianConversion = M_PI / 180.0;  // Conversion d'angle en radians

        // Convertir l'angle en radians
        double rotateRad = (double)lander.rotate * radianConversion;

        // Calculer la nouvelle vitesse horizontale et verticale
        lander.speed.x += sin(rotateRad) * (double)lander.power;
        lander.speed.y += gravity + cos(rotateRad) * (double)lander.power;

        lander.speed.x = max(-500.0f, min(500.0f, lander.speed.x));
        lander.speed.y = max(-500.0f, min(500.0f, lander.speed.y));

        // Calculer la nouvelle position
        lander.pos.x += lander.speed.x;
        lander.pos.y += lander.speed.y;

        // Considérer la consommation de carburant
        lander.fuel -= lander.power;

        // Limiter la puissance entre 0 et 4
        //lander.power = max(0, min(4, lander.power));

        // Mettre à jour les paramètres de rotation
        // Vous pouvez ajouter une logique plus avancée ici pour la rotation si nécessaire
    }

    // Fonction pour calculer la distance verticale entre la trajectoire du Lander et le sol de Mars
    double calculateVerticalDistance(const Sim& lander, const Vector2& surfacePoint) {
        return abs(lander.pos.y - surfacePoint.y);
    }

    ll evaluateTrajectory(Sim& lander, int minz, int maxz, const vector<Vector2>& surface) {
        double minDistance = numeric_limits<double>::max();
        int landingZoneStart = minz/* l'indice du début de la zone d'atterrissage */;
        int landingZoneEnd = maxz/* l'indice de fin de la zone d'atterrissage */;

        // Parcours des points du sol pour trouver la distance minimale
        for (int i = landingZoneStart; i <= landingZoneEnd; ++i) {
            double distance = calculateVerticalDistance(lander, surface[i]);
            minDistance = min(minDistance, distance);
        }

        // Évaluation de la qualité de la trajectoire en fonction de la distance, du carburant et d'autres critères
        double distanceScore = 1.0 / (1.0 + minDistance);
        double fuelScore = (double)lander.fuel / 550.0;  // Ajustez MAX_FUEL selon votre échelle de carburant

        // Ajustez ces poids selon l'importance relative des critères pour vous
        //cerr << distanceScore * 0.6 + fuelScore * 0.4 << endl;
        lander.score = (distanceScore * 0.6 + fuelScore * 0.4) * 100.0;
        return lander.score;
    }


    string Play(Sim sm_start, vector<Vector2>land, int minz, int maxz, int time){
        for(int i = 0;i < NB_POP;++i)population[i].score = -1000000000;

        auto startm = high_resolution_clock::now();;
        
        auto getTime = [&]()-> bool {
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<milliseconds>(stop - startm);
            return(duration.count() <= time);
        };

        int nb_sim = 0;
        int ind = 0;
        int nb_turn = 0;
        Sim best_sim;
        best_sim.score = -1000000000;
        int nb_score = 0;
        int ind_score = 0;

        
        while(getTime()){

            

            Sim sm;
            
            sm.rotate = max(-90, min(90, population[ind].rotate + sm_start.rotate));
            sm.power = population[ind].power;
            sm.pos.x = sm_start.pos.x;
            sm.pos.y = sm_start.pos.y;
            sm.speed.x = sm_start.speed.x;
            sm.speed.y = sm_start.speed.y;
            sm.fuel = sm_start.fuel;

             //cerr << "Before simulateLander: x=" << sm.pos.x << " y=" << sm.pos.y << " rotate=" << sm.rotate << " power=" << sm.power << endl;

            simulateLander(sm);

            //cerr << "After simulateLander: x=" << sm.pos.x << " y=" << sm.pos.y << " rotate=" << sm.rotate << " power=" << sm.power << endl;


            Vector2 surfacepoint;
            int DY = 0;
            int inddy = 0;
            for(int i = 0;i < land.size()-1;++i){
                if(sm.pos.x >= sm_start.pos.x){
                    if(sm.pos.x >= land[i].x && sm.pos.x < land[i+1].x){
                        inddy = i+1;
                        break;
                    }

                }
                else{
                    if(sm.pos.x >= land[i].x && sm.pos.x < land[i+1].x){
                        inddy = i;
                        break;
                    }

                }
            }

            DY = sm.pos.y - max(land[minz].y, land[inddy].y)+10;
            int midx = (land[minz].x + land[maxz].x) / 2;
            int dist  = abs(sm.pos.x - midx);// + (sm.pos.y - land[minz].y)*(sm.pos.y - land[minz].y));


            int score_att = 0;
            int bonus = 0;
            
           
            /*if (sm_start.pos.x < midx) {
                if (sm.speed.x <= 0) {
                    score_att += abs(sm.speed.x) * 200;
                }
                else {
                    if(sm.speed.x > 10)
                        score_att += abs(sm.speed.x) * 200;
                    else
                        bonus += abs(sm.speed.x) * 100;  // Utilisez abs(sm.speed.x) ici
                }
            }
            else {
                if (sm.speed.x >= 0) {
                    score_att += sm.speed.x * 200;
                }
                else {
                    if(sm.speed.x < -10)
                        score_att += abs(sm.speed.x) * 200;
                    else
                        bonus += abs(sm.speed.x) * 100;  // Utilisez abs(sm.speed.x) ici
                }
            }
            

            if (sm.pos.y < max(land[minz].y, land[inddy].y) + 10) {
                if (sm.speed.y <= 0)
                    score_att += abs(sm.speed.y) * 200;
                else
                    bonus += abs(sm.speed.y) * 200;  // Utilisez abs(sm.speed.y) ici
            }
            else {
                if (sm.speed.y >= 0)
                    score_att += sm.speed.y * 200;
                else
                    bonus += abs(sm.speed.y) * 200;  // Utilisez abs(sm.speed.y) ici
            }*/

           // if (sm_start.pos.x < midx && sm.rotate )

            if (sm.speed.y < -20 || sm.speed.y > 20 || sm.speed.y == 0)score_att += abs(sm.speed.y) * 10000 ;
            else bonus += abs(sm.speed.y) * sm.power;
            if (sm.speed.x > 10 || sm.speed.x < -10 || sm.speed.x == 0)score_att += abs(sm.speed.x) * 10000 ;
            else{
                bonus += abs(sm.speed.x) * sm.power;
            
            }
            
            
            


            if(sm.pos.x >= land[minz].x && sm.pos.x <= land[maxz].x){
                if(sm.speed.x > 15){
                    int angle = 0;
                    int dangle = 0;
                    if(dist > 2000)dangle = -15;
                    else dangle = -30;
                    if(sm.speed.y > dangle)angle = 90;
                    else angle = 45 ;
                    if(sm.rotate > 0 && sm.rotate < angle)
                        bonus += abs(sm.rotate)*1000 * sm.power;
                    else
                        score_att += abs(sm.rotate)*1000;
                }

                if(sm.speed.x < -15){
                    int angle = 0;
                    int dangle = 0;
                    if(dist > 2000)dangle = -15;
                    else dangle = -30;
                    if(sm.speed.y > dangle)angle = -90;
                    else angle = -45 ;

                    if(sm.rotate < 0 && sm.rotate > angle ) 
                        if(sm.pos.y >= 2900)bonus += abs(sm.rotate)*1000;
                        else bonus += abs(sm.rotate)*1000 * sm.power;
                    else
                        score_att += abs(sm.rotate)*1000;
                }

                score_att += abs(sm.rotate)*1000;
                DY = sm.pos.y - land[minz].y;
                DY *= 100;
            }
            else if (this->haut_plateau) {
                DY = sm.pos.y - land[minz].y;
                DY *= 100;             

                /*if(DY < 0){
                    if(sm.speed.x < 0){
                        if(sm.rotate >= 0){
                            score_att += abs(sm.rotate)*1000;
                        }
                        else{
                            bonus += abs(sm.rotate)* sm.power*1000;
                        }
                    }
                }*/

                if(sm.pos.y >= 2800){
                    score_att += sm.pos.y * 1000;
                    bonus += (90 - (abs(sm.rotate)-90))* (2 - abs(sm.power-2))*1000;
                }
                else{
                    bonus += (90 - (abs(sm.rotate)-90))* sm.power*1000;
                    score_att += abs(sm.rotate)*1000;
                }

                if(DY < 0)DY = -DY;
            }
            else{
                if(sm.speed.x < -40){
                    int angle = 0;
                    int dangle = -10;
                    if(dist > 800)dangle = -10;
                    else dangle = -30;
                    if(sm.speed.y > dangle)angle = -90;
                    else angle = -40;
                    
                    if(sm.rotate < 0 && sm.rotate > angle)
                        bonus += abs(sm.rotate)*1000 * sm.power;
                    else
                        score_att += abs(sm.rotate)*1000;
                }
            
                if(sm.speed.x > 40){
                    int angle = 0;
                    int dangle = -10;
                    if(dist > 800)dangle = -10;
                    else dangle = -30;
                    if(sm.speed.y > dangle)angle = 90;
                    else angle = 40;
                    if(sm.rotate > 0 && sm.rotate < angle)
                        bonus += abs(sm.rotate)*1000 * sm.power;
                    else
                        score_att += abs(sm.rotate)*1000;
                }





            }


            sm.score = (100000- dist) - DY - score_att + bonus + sm.fuel/2;
  
            //sm.score = evaluateTrajectory(sm, minz, maxz, land);

            if(sm.score > best_sim.score){
                best_sim = sm;
                nb_score = nb_turn;
                ind_score = ind;
            }

            population[ind].score = sm.score;

            nb_sim++;
            if(nb_sim == NB_SIM){
                sort(population.begin(), population.end(), [](Sim a, Sim b) -> bool {
                    return a.score > b.score;
                });
                nb_sim = 0;
                this->NextGen();
                for(int i = 0;i < NB_POP;++i)population[i].score = -1000000000;

            }

            nb_turn++;
            ind = (ind + 1) % NB_POP;


        }

        int midx = (land[minz].x + land[maxz].x) / 2;
        int dist  = abs(best_sim.pos.x - midx);
        cerr << "dist " << dist << endl; 

        cerr << "turn " << nb_turn << " " << endl;
        cerr << "R " << best_sim.rotate << " P " << best_sim.power << endl; 
        cerr << "score "<< best_sim.score << " " << nb_score << " " << ind_score << endl;
        cerr << best_sim.pos.x << " " << best_sim.pos.y << endl;
        return to_string(best_sim.rotate) + " " + to_string(best_sim.power);

    }


};



/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

int main()
{
    int surface_n; // the number of points used to draw the surface of Mars.
    cin >> surface_n; cin.ignore();

    vector<Vector2> land;
    for (int i = 0; i < surface_n; i++) {
        int land_x; // X coordinate of a surface point. (0 to 6999)
        int land_y; // Y coordinate of a surface point. By linking all the points together in a sequential fashion, you form the surface of Mars.
        cin >> land_x >> land_y; cin.ignore();
        land.push_back(Vector2{(float)land_x, (float)land_y});

    }

    int maxy = -1000;
    float maxzone = -1000;
    int minplane = 100000, maxplane = -100000;
    for (int i = 0; i < land.size()-1; i++) {
        if(land[i].y == land[i+1].y){
            minplane = min(minplane, i);
            maxplane = max(maxplane, i+1);
            maxy = land[i].y;
        }
        maxzone = max(maxzone, land[i].y);


    }

    cerr << minplane << " " << maxplane << endl;

    MarsLander lander(100, 100);

    lander.maxyz = maxy;

    if(maxzone == maxy){
        lander.haut_plateau = true;
    }

    // game loop
    while (1) {
        int x;
        int y;
        int h_speed; // the horizontal speed (in m/s), can be negative.
        int v_speed; // the vertical speed (in m/s), can be negative.
        int fuel; // the quantity of remaining fuel in liters.
        int rotate; // the rotation angle in degrees (-90 to 90).
        int power; // the thrust power (0 to 4).
        cin >> x >> y >> h_speed >> v_speed >> fuel >> rotate >> power; cin.ignore();

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;

        Sim sm_start;

        for (int i = 0; i < land.size()-1; i++) {
            if(x >= land[i].x && x <= land[i+1].x){
                sm_start.ind_zone = i;
            }


        }

        cerr << "x " << x << " " << y << " "<< rotate << endl;



        
        sm_start.pos.x = x;
        sm_start.pos.y = y;
        sm_start.speed.x = h_speed;
        sm_start.speed.y = v_speed;
        sm_start.fuel = fuel;
        sm_start.rotate = rotate;
        sm_start.power = power;

        //if(lander.turn_game > 0){

            string ans = lander.Play(sm_start, land, minplane, maxplane, 90);


            // rotate power. rotate is the desired rotation angle. power is the desired thrust power.
            cout << ans << endl;
        /*}
        else{
            if(sm_start.ind_zone < minplane)
                cout << "-90 4" << endl;
            else
                cout << "90 4" << endl;

        }*/

        lander.turn_game++;
    }
}