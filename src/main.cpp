#include <iostream>
#include <fstream>
#include <string>
#include <string>
#include <array>
#include <sys/stat.h>
#include <ctime>

#include "utils.h"
#include "dataset.h"
#include "lsh.h"


using namespace std;

int executeLSH(ifstream&, ifstream&, ofstream&, int, int);

int main(int argc, char* argv[]){
    dataset<int> my_data;
    int k = -1;
    int L = -1;
    string input_file = "";
    string query_file = "";
    string output_file = "";
    ifstream input;
    ifstream query;
    ofstream output;
    int flag = -1;


    /* Check given parameters */
    int result = get_parameters(argc, argv, input_file, query_file, output_file, k, L);
    if(result == -2){
        printValidParameters();
        return -1;
    }

    if(k == -1)
        k = DEFAULT_K;
    if(L == -1)
        L = DEFAULT_L;

    /* While user decides to exit */
    while(flag != 8){
        /* Get input file */
        while(1){ // until correct input file is given
            /* Check if input file was provided by parameters */
            if(input_file.empty() || flag != -1){
                cout << "Please provide path to input file(dataset), or .. to abort: ";
                fflush(stdout);
                getline(cin, input_file);
                fflush(stdin);
            }

            if(!input_file.compare("..")){ // Abort
                cout << "No file was given. Abort." << endl;
                return -2;
            }

            struct stat buffer;
            if(stat (input_file.c_str(), &buffer) != 0){
                cout << "File " << input_file << " does not exist. Try again." << endl;
                input_file = "";
                continue;
            }

            input.open(input_file); // open file provided 
            if(input.is_open()) // file was succesfully opened
                break;
        }

        /* Get query file */
        while(1){ // until correct file is given
            /* Check if query file was provided by parameters */
            if(query_file.empty() || flag != -1){
                cout << "Please provide path to query file, or .. to abort: ";
                fflush(stdout);
                getline(cin, query_file);
                fflush(stdin);
            }

            if(!query_file.compare("..")){ // Abort
                cout << "No file was given. Abort." << endl;
                return -2;
            }

            struct stat buffer;
            if(stat (query_file.c_str(), &buffer) != 0){
                cout << "File " << query_file << " does not exist. Try again." << endl;
                query_file = "";
                continue;
            }

            query.open(query_file); // open file provided 
            if(query.is_open()) // file was succesfully opened
                break;
        }

        /* Get output file */
        while(1){ // until correct file is given
            /* Check if output file was provided by parameters */
            if(output_file.empty() || flag != -1){
                cout << "Please provide path to output file, or .. to abort: ";
                fflush(stdout);
                getline(cin, output_file);
                fflush(stdin);
            }

            if(!output_file.compare("..")){ // Abort
                cout << "No file was given. Abort." << endl;
                return -2;
            }

            output.open(output_file); // open file provided 
            if(output.is_open()) // file was succesfully opened
                break;
        }

        cout << "\n\nParameters Given:" << endl;
        cout << "................." << endl;
        cout << ">Input file: " << input_file << endl;
        cout << ">Query File: " << query_file << endl;
        cout << ">Output File: " << output_file << endl;
        cout << ">Hash functions(k): " << k << endl;
        cout << ">Hash tables(L): " << L << endl;
        cout << "\n" << endl;

        flag = executeLSH(input, query, output, k, L);
        if(flag == 8)
            break;
    }
    cout << "Exiting..." << endl;
}




int executeLSH(ifstream& input, ifstream& query, ofstream& output, int k, int L){
    dataset<int> my_data;   
    

    string line;

    /* Scan first line for metric */
    getline(input, line);
    int metrics = get_metrics(line);
    if(metrics == 0){ // no metric defined, vector was scanned
        metrics = 1; // use euclidean
        my_data.add_vector(line); // insert vector to data
    } 

    /* Scan all vectors and insert in dataset */
    while(getline(input, line)){
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

    if(metrics == 1){
        output << "USING EUCLIDEAN DISTANCE" << endl;
        output << "........................\n\n" << endl;
        cout << "**LSH was created succesfully using Euclidean Distance.\n\n" << endl;
    
    }
    else if(metrics == 2){
        output << "USING COSINE SIMILARITY" << endl;
        output << ".......................\n\n" << endl;
        cout << "**LSH was created succesfully using Cosine Similarity.\n\n" << endl;
    }



    /* Move to query part */
    
    /* Scan first line for radius to be used on current query file */
    getline(query, line);
    int radius = get_radius(line);
    if(radius < 0){ // no radius defined, query was scanned
        radius = 0; // dont scan for neighbours in radius at all
        
        /* Find Neighbours */
        float min_dist = 0.0;
        string min_name = "";
        vector_item<int>* q_vector = new vector_item<int>(line);
        output << "Query: " << q_vector->get_id() << endl;
        output << "*R-near neighbours (R = " << radius << "):" << endl;

        const clock_t begin = clock();
        lsh.findANN(*q_vector, radius, min_dist, min_name, output);
        const clock_t end = clock();

        double query_time = float(end - begin) /  CLOCKS_PER_SEC;

        output << "*Nearest Neighbour: " << min_name << endl;
        output << "*DistanceLSH: " << min_dist << endl;
        output << "*timeLSH: " << query_time << endl;
        output << "\n" << endl;
        delete q_vector;
    }

    while(getline(query, line)){
        /* Find Neighbours */
        float min_dist = 0.0;
        string min_name = "";
        vector_item<int>* q_vector = new vector_item<int>(line);
        output << "Query: " << q_vector->get_id() << endl;
        output << "*R-near neighbours (R = " << radius << "):" << endl;

        const clock_t begin = clock();
        lsh.findANN(*q_vector, radius, min_dist, min_name, output);
        const clock_t end = clock();
        
        double query_time = float(end - begin) /  CLOCKS_PER_SEC;
        
        output << "*Nearest Neighbour: " << min_name << endl;
        output << "*DistanceLSH: " << min_dist << endl;
        output << "*timeLSH: " << query_time << endl;
        output << "\n" << endl;
        delete q_vector;
    }

    cout << "**LSH Algorithm Has Completed.\n" << endl;
    

    // DESTROY EVERYTHING
    int choice = new_execution(input, query, output);
    return choice;
}