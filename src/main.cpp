#include <iostream>
#include <fstream>
#include <string>
#include <string>
#include <array>

#include "utils.h"
#include "dataset.h"
#include "metrics.h"


using namespace std;

int main(void){
    dataset<int> my_data;

    ifstream infile("input_small");
    string line;
    while(getline(infile, line)){
        my_data.add_vector(line);    
    }

    euclidean<int> ed(4, my_data.get_counter());

    vector_item<int>* it = my_data.get_item(3000);

    it->print();

    //my_data.print();
}
