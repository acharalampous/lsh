#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <sys/stat.h>
#include <ctime>

#include "utils.h"
#include "dataset.h"
#include "lsh.h"

using namespace std;

/* Responsible for the implementation of the LSH algorithm */
/* Given the necessary files, k and L */
int executeLSH(ifstream&, ifstream&, ofstream&, int, int);

/* In main, all the necessary arguments and file names are extracted */
int main(int argc, char* argv[]){
    int k = -1; // number of hash functions
    int L = -1; // number of hash tables
    
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
    int result = get_parameters(argc, argv, input_file, query_file, output_file, k, L);
    if(result == -2){
        printValidParameters();
        return -1;
    }

    /* If not k or L were provided, use the defaults */
    if(k == -1)
        k = DEFAULT_K;
    if(L == -1)
        L = DEFAULT_L;

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

        /* Print Program Parameteres */
        cout << "\n\nParameters Given:" << endl;
        cout << "................." << endl;
        cout << ">Input file: " << input_file << endl;
        cout << ">Query File: " << query_file << endl;
        cout << ">Output File: " << output_file << endl;
        cout << ">Hash functions(k): " << k << endl;
        cout << ">Hash tables(L): " << L << endl;
        cout << "\n" << endl;

        /* Start the LSH sequence */
        flag = executeLSH(input, query, output, k, L);
        if(flag == 8) // user wants to exit
            break;
    }
    cout << "Exiting..." << endl;
}


int executeLSH(ifstream& input, ifstream& query, ofstream& output, int k, int L){
    dataset<int> my_data; // holds all vectors
    string line;

    /* Scan first line from input file for metric */
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
    cout << "**Dataset was created succesfully for " << data_counter << " vectors.\n" << endl;

    /* Create LSH level */
    LSH<int>* lsh = new LSH<int>(metrics, L, k, data_counter);


    /* Insert vectors from dataset in lsh buckets */
    for(unsigned int i = 0; i < data_counter; i++){
        vector_item<int>* item = my_data.get_item(i); // get item from dataset
        lsh->add_vector(item); // and place pointer of it in lsh
    }


    if(metrics == 1){
        output << "LSH USING EUCLIDEAN DISTANCE" << endl;
        output << "============================\n\n" << endl;
        cout << "**LSH was created succesfully using Euclidean Distance.\n" << endl;
    
    }
    else if(metrics == 2){
        output << "LSH USING COSINE SIMILARITY" << endl;
        output << "===========================\n\n" << endl;
        cout << "**LSH was created succesfully using Cosine Similarity.\n" << endl;
    }

    /* Move to query part */
    cout << "**Starting Query sequence\n\n" << endl;
    
    double max_approx = 0.0; // maximum approximation (LSH_time / Real_time)
    long double avg_lsh_time = 0.0; // avg lsh ANN time
    long double avg_real_time = 0.0; // avg exchausting search time
    int total_queries = 0; // number of queries-vectors checked


    /* Scan first line for radius to be used on current query file */
    getline(query, line);
    int radius = get_radius(line);
    if(radius < 0){ // no radius defined, query was scanned so it must be checked
        radius = 0; // dont scan for neighbours in radius at all
        
        /* Find Neighbours */
        float lsh_min_dist = 0.0; // will hold the minimum distance
        string min_name = ""; // will hold the nearest neighbour's id
        vector_item<int>* q_vector = new vector_item<int>(line); // create a new vector_item with the given points
        total_queries++;

        output << "Query: " << q_vector->get_id() << endl;
        output << "*R-near neighbours (R = " << radius << "):" << endl;

        const clock_t lsh_begin = clock();
        lsh->findANN(*q_vector, radius, lsh_min_dist, min_name, output);
        const clock_t lsh_end = clock();

        /* Compute time elapsed for LSH ANN searching */
        double lsh_time = double(lsh_end - lsh_begin) /  CLOCKS_PER_SEC;

        const clock_t real_begin = clock();
        float real_dist = exchausting_s<int>(my_data, *q_vector, metrics);
        const clock_t real_end = clock();

        /* Compute time elapsed for excausting search */
        double real_time = double(real_end - real_begin) /  CLOCKS_PER_SEC;

        output << "*Nearest Neighbour: " << min_name << endl;
        output << "*DistanceLSH: " << lsh_min_dist << endl;
        output << "*DistanceTrue: " << real_dist << endl;
        output << "*timeLSH: " << lsh_time << endl;
        output << "*timeReal: " << real_time << endl;
        output << "\n" << endl;

        double approx = lsh_min_dist / real_dist;
        if(approx >= max_approx) // if current approximation larger that max, re set max
            max_approx = approx;
        
        avg_lsh_time += lsh_time; // add to total lsh_time
        avg_real_time += real_time; // add to total real_time

        delete q_vector;
    }

    while(getline(query, line)){
        /* Find Neighbours */
        float lsh_min_dist = 0.0;
        string lsh_min_name = "";
        
        vector_item<int>* q_vector = new vector_item<int>(line);
        total_queries++;

        output << "Query: " << q_vector->get_id() << endl;
        output << "*R-near neighbours (R = " << radius << "):" << endl;

        const clock_t lsh_begin = clock();
        lsh->findANN(*q_vector, radius, lsh_min_dist, lsh_min_name, output);
        const clock_t lsh_end = clock();
        
        /* Compute time elapsed for ANN searching */
        double lsh_time = double(lsh_end - lsh_begin) /  CLOCKS_PER_SEC;
        
        const clock_t real_begin = clock();
        float real_dist = exchausting_s<int>(my_data, *q_vector, metrics);
        const clock_t real_end = clock();

        double real_time = double(real_end - real_begin) /  CLOCKS_PER_SEC;

        output << "*Nearest Neighbour: " << lsh_min_name << endl;
        output << "*DistanceLSH: " << lsh_min_dist << endl;
        output << "*DistanceTrue: " << real_dist << endl;
        output << "*timeLSH: " << lsh_time << endl;
        output << "*timeReal: " << real_time << endl;
        output << "\n" << endl;

        double approx = lsh_min_dist / real_dist;
        if(approx >= max_approx)
            max_approx = approx;

        avg_lsh_time += lsh_time;
        avg_real_time += real_time;

        delete q_vector;
    }

    avg_lsh_time = avg_lsh_time / total_queries;
    avg_real_time = avg_real_time / total_queries;


    cout << "**Query sequence for " << total_queries << " queries finished succesfully." << endl;
    cout << "\tMax Approximation: " << max_approx << endl;
    cout << "\tAverage LSH ANN time: " << avg_lsh_time << endl;
    cout << "\tAverage Excausting search time: " << avg_real_time << endl;
    cout << "\tLSH total size: " << lsh->get_total_size() << " bytes \n" << endl;

    cout << "**LSH Algorithm Has Completed. Check output file for results\n" << endl;
    
    // DESTROY EVERYTHING
    delete lsh;

    /* Ask user if he wants to continue and we what files */
    int choice = new_execution(input, query, output);
    return choice;
}