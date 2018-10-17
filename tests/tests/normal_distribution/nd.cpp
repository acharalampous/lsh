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
    std::random_device rd{};
    std::mt19937 gen{rd()};
 
    // values near the mean are the most likely
    // standard deviation affects the dispersion of generated values from the mean
    std::normal_distribution<> d(0.0,0.2);
 
    std::map<int, int> hist{};
    for(int n=0; n<10000; ++n) {
        ++hist[std::round(d(gen))];
    }
    for(auto p : hist) {
        std::cout << std::setw(2)
                  << p.first << ' ' << std::string(p.second/200, '*') << '\n';
    }
}