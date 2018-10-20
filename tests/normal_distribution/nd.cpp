#include <iostream>
#include <random>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <string>
#include <map>
#include <cmath>

using namespace std;

    // unsigned seed = chrono::steady_clock::now().time_since_epoch().count();
    // default_random_engine e(seed);
    // normal_distribution<double> distrN{0.0, 1.0};

    // cout << distrN(e) << endl;

 
int main(){
    random_device rd;
    mt19937 gen(rd());
 
    // values near the mean are the most likely
    // standard deviation affects the dispersion of generated values from the mean
    normal_distribution<float> d(0.0,1.0);
	
	for(int i = 0 ; i < 20; i++){
		normal_distribution<float> dd(0.0,1.0);
		cout << dd(gen) << endl;
	}
}
