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
    ifstream infile("input_small_new");
    string line;

    /* Scan first line for metric */
    getline(infile, line);
    int metrics = get_metrics(line);
    if(metrics == 0){ // no metric defined, vector was scanned
        metrics = 1; // use euclidean
        my_data.add_vector(line); // insert vector to data
    } 

    /* Scan all vectors and insert in dataset */
    while(getline(infile, line)){
        my_data.add_vector(line);    
    }

    unsigned int data_counter = my_data.get_counter();
    cout << "**Dataset was created succesfully for " << data_counter << " vectors." << endl;

    LSH<int> lsh(metrics, L, k, data_counter);


    /* Insert vectors in lsh buckets */
    for(unsigned int i = 0; i < data_counter; i++){
        vector_item<int>* item = my_data.get_item(i); // get item from dataset
        lsh.add_vector(item); // and place pointer of it in lsh
    }

    cout << "**LSH was created succesfully.\n\nQueries:\n" << endl;

    /* Move to query part */
    ifstream queryfile("query_small_new");
    
    /* Scan first line for radius to be used on current query file */
    getline(queryfile, line);
    int radius = get_radius(line);
    if(radius < 0){ // no radius defined, query was scanned
        radius = 0; // dont scan for neighbours in radius at all
        
        /* Find Neighbours */
        float min_dist = 0.0;
        string min_name = "";
        vector_item<int>* q_vector = new vector_item<int>(line);
        cout << q_vector->get_id() << endl;
        lsh.findANN(*q_vector, radius, min_dist, min_name);
        cout << "\tNearest Neighbour: " << min_name << " with distance: " << min_dist << endl;
        delete q_vector;
    }

    while(getline(queryfile, line)){
        /* Find Neighbours */
        float min_dist = 0.0;
        string min_name = "";
        vector_item<int>* q_vector = new vector_item<int>(line);
        cout << q_vector->get_id() << endl;
        lsh.findANN(*q_vector, radius, min_dist, min_name);
        cout << "\tNearest Neighbour: " << min_name << " with distance: " << min_dist << endl;
        delete q_vector;
    }
}
