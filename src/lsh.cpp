/*******************************/
/* lsh.cpp */

/* Name:    Andreas Charalampous
 * A.M :    1115201500195
 * e-mail:  sdi1500195@di.uoa.gr
 */
/********************************/
#include <iostream>

#include "lsh.h"

using namespace std;

template class LSH<int>;

/*  Implementation of all functions of the class
 *  that is used for LSH. Definitions found in
 *  lsh.h.
 */

/* L: num of tables for each metrics, k: num of hash functions, n: dataset size */ 
template <class T>
LSH<T>::LSH(int metrics, int L, int k, int n){
    this->L = L;
    if(metrics == 1 || metrics == 2){ // euclidean is defined
        for(int i = 0; i < L; i++)
            eu_tables.push_back(new euclidean<T>(k, n));
    }

    if(metrics == 2 || metrics == 3){ // cosine is defined
        for(int i = 0; i < L; i++)
            cs_tables.push_back(new csimilarity<T>(k));
    }
}

template <class T>
void LSH<T>::add_vector(vector_item<T>* new_vector){
    for(unsigned int i = 0; i < eu_tables.size(); i++){
        eu_tables[i]->add_vector(new_vector);
    }

    for(unsigned int i = 0; i < cs_tables.size(); i++){
        cs_tables[i]->add_vector(new_vector);
    }
}

template <class T>
void LSH<T>::findANN(vector_item<T>& query, float radius, float& min_dist, string& ANN_name, ofstream& output){
    for(unsigned int i = 0; i < eu_tables.size(); i++){
        eu_tables[i]->findANN(query, radius, min_dist, ANN_name, output);
    }

    for(unsigned int i = 0; i < cs_tables.size(); i++){
        cs_tables[i]->findANN(query, radius, min_dist, ANN_name);
    }
}