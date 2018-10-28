#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int get_combinations(int a, int b){
    /* Computes comb(a,b) = a! / (b! * (a - b)!) */
    int diff = a - b;

    return ( get_factorial(a) / ( get_factorial(b) * get_factorial(diff)) );


}

int get_factorial(int num){
    int total = 1;
    for(int i = 2; i < num; i++){
        total *= i;
    }

    return total;
}

int hamming_dist(int x, int y){
    int x_or = x ^ y; // find different bits

    int dist = 0; // hamming_dist
    while(x > 0){ // check all bits
        if((x | 1) == x) // if true, means the leftmost bit is 1, hence different
            dist++;
        x = x >> 1;
    }
}

void print(int num, int probes, int k){
    vector<int> count; // each cell has number of neighbours in corresponding distance
    int num_of_bits = k;
    int max_distance = num_of_bits;

    /* neihbours[x] = neighbours in hamming distance x, x : {0, 1, 2, 3, ..., max_distance} */
    vector<int>* neighbours = new vector<int>[max_distance]; // neighbours buckets that will be returned
    // for(int i = 0; i < max_distance; i++)
    //     neighbours->push_back(vector<int>());

    int remaining_n = probes - 1; // remaining neigbours that need to be found
    neighbours[0].push_back(num); // self bucket must still be checked
    count.push_back(0);

    /* Find how many neihbours must be found in each distance, until probes are reached */
    for(int i = 1; i < max_distance; i++){

        /* Find number of neighbours in i hamming distance */
        int combs = get_combinations(num_of_bits, i);
        if(combs >= remaining_n) // last neighbours number is found
            count.push_back(remaining_n);
        else{
            count.push_back(combs); // keep number of neighbours in distance i and keep searching
            remaining_n -= combs;
        }
    }

    remaining_n = probes - 1;
    int max_num = pow(2, num_of_bits); // maximum possible number for number of bits
    for(int i = 0; i < max_num && remaining_n > 0; i++ ){
        if(i == num) // if same number, pass(already placed)
            continue;
        
        /* Compute hamming dist */
        int dist = hamming_dist(i, num);

        /* If neighbour is needed, then save in vector */
        if(count[dist] > 0){
            neighbours[dist].push_back(i);
            count[dist]--;
            remaining_n--;
        }
    }
}




int main(argv){
    int num = atoi()
}


