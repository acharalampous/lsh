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
    int k = 4;
    int L = 5;
    ifstream infile("input_small");
    string line;

    getline(infile, line);
    int metrics = get_metrics(line);
    if(metrics == 0){ // no metric defined, vector was scanned
        metrics = 1; // use euclidean
        my_data.add_vector(line); // insert vector to data
    } 

    while(getline(infile, line)){
        my_data.add_vector(line);    
    }

    LSH<int> lsh(metrics, L, k, my_data.get_counter());

    cout << "Creation" << endl;
    int tableSize = my_data.get_counter();
    for(int i = 0; i < tableSize; i++){
        vector_item<int>* item = my_data.get_item(i);
        lsh.add_vector(item);
    }

    int i = 0;
    ifstream queryfile("query_small");
    
    getline(queryfile, line);
    int radius = get_radius(line);
    if(radius <= 0){ // no radius defined, query was scanned
        radius = 0; // dont scan for neighbours in radius at all
        
        /* Find Neighbours */
        float min_dist = 0.0;
        string min_name = "";
        vector_item<int>* q_vector = new vector_item<int>(line, i);
        cout << "QueryItem_" << i++ << endl;
        lsh.findANN(*q_vector, radius, min_dist, min_name);
        cout << "\tNearest Neighbour: " << min_name << " with distance: " << min_dist << endl;
        delete q_vector;
    }

    while(getline(queryfile, line)){
        float min_dist = 0.0;
        float radius = 0.5;
        string min_name = "";
        vector_item<int>* q_vector = new vector_item<int>(line, i);
        cout << "QueryItem_" << i++ << endl;
        lsh.findANN(*q_vector, radius, min_dist, min_name);
        cout << "\tNearest Neighbour: " << min_name << " with distance: " << min_dist << endl;
        delete q_vector;
    }
}
