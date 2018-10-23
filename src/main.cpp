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
    csimilarity<int> cs(4);
    cout << "Creation" << endl;
    int tableSize = my_data.get_counter();
    for(int i = 0; i < tableSize; i++){
        //cout << i << endl;
        vector_item<int>* it = my_data.get_item(i);
        ed.add_vector(it);
        cs.add_vector(it);
    }

    int i = 0;
    ifstream queryfile("query_small");
    while(getline(queryfile, line)){
        float min_dist = 0.0;
        float radius = 0.5;
        string min_name = "";
        vector_item<int>* q_vector = new vector_item<int>(line, i);
        cout << "QueryItem_" << i++ << endl;
        ed.findNN(*q_vector, radius, min_dist, min_name);
        cout << "\tNearest Neighbour: " << min_name << " with distance: " << min_dist << endl;
        delete q_vector;
    }
}