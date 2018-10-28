#include <iostream>
#include <bitset>

using namespace std;

int main(int argc, char* argv[]){
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);

    int x = a^b;

    //cout << x << endl;

    int dist = 0;
    while(x > 0){
        if((x | 1) == x)
            dist++;
        x = x >> 1;
    }

    cout << "dist: " << dist << endl;
}    
