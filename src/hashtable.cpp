#include <iostream>
#include <ctime>
#include "hashtable.h"

using namespace std;

hashFunction::hashFunction(){
    srand(time(NULL));
    t = rand() % W;

    for(int i = 0; i < D; i++){
        
    }
}