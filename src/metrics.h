/*******************************/
/* metrics.h */

/* Name:    Andreas Charalampous
 * A.M :    1115201500195
 * e-mail:  sdi1500195@di.uoa.gr
 */
/********************************/
#pragma once
#include <array>
#include <vector>
#include <list>
#include "dataset.h"

#define W 4 // window
#define TS_DIVISOR 2 // for tablesize in euclidean
/* For random vector r, in euclidean */
#define MIN_Ri -40 
#define MAX_Ri 40


/*  Implementations of all metrics used in LSH  */


/////////////////
/** EUCLIDEAN **/
/////////////////


/** euclidean_vec **/
/* Items(Records) that are hold in buckets. Has pointer to vector */
/* from dataset and the value of g(p).                            */
template <class T>
class euclidean_vec{
    private:
        vector_item<T>* vec; // pointer to vector in dataset
        long int g; // value of g(p)
    public:
        euclidean_vec(vector_item<T>*, long int);
        
        void print();
};


/** euclideanHF **/
/* Hash function for euclidean distance metric */
class euclideanHF{
    private:
        std::array<float, D> v; // random vector
        float t; // random displacement
    public:
        euclideanHF();
        
        int getValue(std::array<int,D>&); // get hash value
        void print(); // print hash function info
};


/** Euclidean metric **/
template <class T>
class euclidean{
	private:
        const int k; // number of hash functions
        long int M; // for locating bucket
        int tableSize; // number of buckets
        std::vector<euclideanHF> hfs; // hash functions
        std::vector<euclidean_vec<T>*>* buckets; // all buckets
		std::vector<int> r; // random vector
	public:
        /* Constructor */
		euclidean(int, int);
        
        /* Returns the result of hash functions for a vector */
        int get_bucket_num(std::vector<int>&);

        /* Add new vector to hash table*/ 
        void add_vector(vector_item<T>*); 
};




/////////////////////////
/** COSINE SIMILARITY **/
/////////////////////////

/** csimilarityHF **/
/* Hash function for cosine similarity metric */
class csimilarityHF{
    private:
        std::array<float, D> r; // random vector
    public:
        /* Con-De structor */
        csimilarityHF();
        
        int getValue(std::array<int,D>&); // get hash value
        void print(); // print hash function info
};

/** csimilarity **/
template <class T>
class csimilarity{
	private:
        int k; // number of hash functions
        int tableSize; // number of buckets
        std::vector<csimilarityHF> hfs; // hash functions
        std::vector<vector_item<T>*>* buckets; // all buckets
	public:
        /* Con-De structor */
		csimilarity(int);

        void add_vector(vector_item<T>*);
};