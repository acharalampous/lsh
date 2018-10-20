#include <iostream>
#include <fstream>
#include <string>
#include <string>
#include <array>

#include "utils.h"
#include "dataset.h"
#include "lsh.h"


using namespace std;

int main(void){
    dataset<int> my_data;

    ifstream infile("input_small");
    string line;
    while(getline(infile, line)){
        my_data.add_vector(line);    
    }

    

    //my_data.print();
}
