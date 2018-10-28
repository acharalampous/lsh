#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <sys/stat.h>
#include <ctime>

#include "utils.h"
#include "dataset.h"
#include "hypercube.h"

using namespace std;

/* Responsible for the implementation of the LSH algorithm */
/* Given the necessary files, k and L */
int executeHC(ifstream&, ifstream&, ofstream&, int, int, int);

/* In main, all the necessary arguments and file names are extracted */
int main(int argc, char* argv[]){
    int k = -1; // number of hash functions
    int probes = -1;
    int M = -1;

    /* File Names */
    string input_file = "";  
    string query_file = "";
    string output_file = "";
    
    /* Files Content */
    ifstream input;
    ifstream query;
    ofstream output;
    
    int flag = -1; // ckecks if user decided to exit


    /* Check given parameters */
    int result = HC_get_parameters(argc, argv, input_file, query_file, output_file, k, probes, M);
    if(result == -2){
        printValidParameters();
        return -1;
    }

    

    /* While user decides to exit */
    while(flag != 8){

        /* Get input file */
        while(1){ // until correct input file is given

            /* Check if input file was provided by parameters */
            /* Also in case of re-execution, check if user wants another file to be used */
            if(input_file.empty() || (flag != -1 && (!input.is_open()) ) ){
                cout << "Please provide path to input file(dataset), or .. to abort: ";
                fflush(stdout);
                getline(cin, input_file);
                fflush(stdin);
            }

            /* Abort */
            if(!input_file.compare("..")){ 
                cout << "No file was given. Abort." << endl;
                return -2;
            }

            /* Check if file exists */
            struct stat buffer;
            if(stat (input_file.c_str(), &buffer) != 0){
                cout << "File " << input_file << " does not exist. Try again." << endl;
                input_file = "";
                continue;
            }

            if(input.is_open()) // close if file was opened in previous execution
                input.close();

            input.open(input_file); // open file provided 
            if(input.is_open()) // file was succesfully opened
                break;
        }

        /* Get query file */
        while(1){ // until correct file is given
            
            /* Check if query file was provided by parameters */
            if(query_file.empty() || (flag != -1 && (!query.is_open()))){
                cout << "Please provide path to query file, or .. to abort: ";
                fflush(stdout);
                getline(cin, query_file);
                fflush(stdin);
            }

            /* Abort */
            if(!query_file.compare("..")){ 
                cout << "No file was given. Abort." << endl;
                return -2;
            }

            /* Check if file exists */
            struct stat buffer;
            if(stat (query_file.c_str(), &buffer) != 0){
                cout << "File " << query_file << " does not exist. Try again." << endl;
                query_file = "";
                continue;
            }

            if(query.is_open()) // close if file was opened in previous execution
                query.close();
            
            query.open(query_file); // open file provided 
            if(query.is_open()) // file was succesfully opened
                break;
        }

        /* Get output file */
        while(1){ // until correct file is given

            /* Check if output file was provided by parameters */
            if(output_file.empty() || (flag != -1 && (!output.is_open()))){
                cout << "Please provide path to output file, or .. to abort: ";
                fflush(stdout);
                getline(cin, output_file);
                fflush(stdin);
            }

             /* Abort */
            if(!output_file.compare("..")){
                cout << "No file was given. Abort." << endl;
                return -2;
            }

            if(output.is_open()) // close if file was opened in previous execution
                output.close();

            output.open(output_file); // open file provided 
            if(output.is_open()) // file was succesfully opened
                break;
        }

        /* If not k, probes or M were provided, use the defaults */
        if(k == -1)
            k = HC_DEFAULT_K;
        if(probes == -1)
            probes = HC_DEFAULT_PROBES;
        if(M == -1)
            M = 10;

        /* Print Program Parameteres */
        cout << "\n\nParameters Given:" << endl;
        cout << "................." << endl;
        cout << ">Input file: " << input_file << endl;
        cout << ">Query File: " << query_file << endl;
        cout << ">Output File: " << output_file << endl;
        cout << ">Hash functions(k): " << k << endl;
        cout << ">Num Of Probes(probes): " << probes << endl;
        cout << ">Num Of Points to be checked(M): " << M << endl;
        cout << "\n" << endl;

        /* Start the LSH sequence */
        flag = executeHC(input, query, output, k, probes, M);
        if(flag == 8) // user wants to exit
            break;
    }
    cout << "Exiting..." << endl;
}


int executeHC(ifstream& input, ifstream& query, ofstream& output, int k, int probes, int M){
    dataset<int> my_data; // holds all vectors
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

    /* Get number of vectors, to insert them in LSH */
    unsigned int data_counter = my_data.get_counter();
    cout << "**Dataset was created succesfully for " << data_counter << " vectors." << endl;

    /* Create LSH level */
    hypercube<int>* HC = new hypercube<int>(metrics, k, probes, M);


    /* Insert vectors in hypercube buckets */
    for(unsigned int i = 0; i < data_counter; i++){
        vector_item<int>* item = my_data.get_item(i); // get item from dataset
        HC->add_vector(item); // and place pointer of it in lsh
    }

    if(metrics == 1){
        output << "USING EUCLIDEAN DISTANCE" << endl;
        output << "========================\n\n" << endl;
        cout << "**Hypercube was created succesfully using Euclidean Distance." << endl;
    
    }
    else if(metrics == 2){
        output << "USING COSINE SIMILARITY" << endl;
        output << "=======================\n\n" << endl;
        cout << "**Hypercube was created succesfully using Cosine Similarity." << endl;
    }

    /* Move to query part */
    cout << "**Starting Query sequence\n\n" << endl;
    
    
    /* Scan first line for radius to be used on current query file */
    getline(query, line);
    double radius = get_radius(line);
    if(radius < 0.0){ // no radius defined, query was scanned so it must be done
        radius = 0; // dont scan for neighbours in radius at all
        
        /* Find Neighbours */
        float min_dist = 0.0;
        string min_name = "";

        vector_item<int>* q_vector = new vector_item<int>(line);
        output << "Query: " << q_vector->get_id() << endl;
        output << "*R-near neighbours (R = " << radius << "):" << endl;

        const clock_t begin = clock();
        HC->findANN(*q_vector, radius, min_dist, min_name, output);
        const clock_t end = clock();

        /* Compute time elapsed for ANN searching */
        double hc_time = float(end - begin) /  CLOCKS_PER_SEC;

        const clock_t real_begin = clock();
        float real_dist = exchausting_s<int>(my_data, *q_vector, metrics);
        const clock_t real_end = clock();

        double real_time = float(real_end - real_begin) /  CLOCKS_PER_SEC;

        output << "*Nearest Neighbour: " << min_name << endl;
        output << "*DistanceHC: " << min_dist << endl;
        output << "*DistanceReal: " << real_dist << endl;
        output << "*timeHC: " << hc_time << endl;
        output << "*timeReal: " << real_time << endl;
        output << "\n" << endl;
        delete q_vector;
    }

    while(getline(query, line)){
        /* Find Neighbours */
        float lsh_min_dist = 0.0;
        string lsh_min_name = "";
        
        vector_item<int>* q_vector = new vector_item<int>(line);
        output << "Query: " << q_vector->get_id() << endl;
        output << "*R-near neighbours (R = " << radius << "):" << endl;

        const clock_t lsh_begin = clock();
        HC->findANN(*q_vector, radius, lsh_min_dist, lsh_min_name, output);
        const clock_t lsh_end = clock();
        
        /* Compute time elapsed for ANN searching */
        double hc_time = float(lsh_end - lsh_begin) /  CLOCKS_PER_SEC;
        
        const clock_t real_begin = clock();
        float real_dist = exchausting_s<int>(my_data, *q_vector, metrics);
        const clock_t real_end = clock();

        double real_time = float(real_end - real_begin) /  CLOCKS_PER_SEC;

        output << "*Nearest Neighbour: " << lsh_min_name << endl;
        output << "*DistanceHC: " << lsh_min_dist << endl;
        output << "*DistanceTrue: " << real_dist << endl;
        output << "*timeHC: " << hc_time << endl;
        output << "*timeReal: " << real_time << endl;
        output << "\n" << endl;
        delete q_vector;
    }

    cout << "**HyperCube Algorithm Has Completed. Check output file for results\n" << endl;
    
    // DESTROY EVERYTHING
    delete HC;

    /* Ask user if he wants to continue and we what files */
    int choice = new_execution(input, query, output);
    return choice;
}