#pragma once
#include <array>
#include <vector>
#include <list>


#include "dataset.h"

#define W 4 // window
#define TS_DIVISOR 2 // for tablesize in euclidean



/*******************/
/**** EUCLIDEAN ****/
/*******************/

/* Hash function for euclidean distance metric */
class euclideanHF{
    private:
        std::array<float, D> v; // random vector
        float t; // random displacement
    public:
        /* Con-De structor */
        euclideanHF();
        
        int getValue(std::array<int,D>&); // get hash value
        void print(); // print hash function info
};

template <class T>
class euclidean{
	private:
        int k; // number of hash functions
        int M; // for locating bucket
        int tableSize; // number of buckets
        std::vector<euclideanHF> hfs; // hash functions
        std::vector<vector_item<T>*>* buckets; // all buckets
		std::vector<int> r; // random vector
	public:
        /* Con-De structor */
		euclidean(int, int);


};

/****************************/
/***** COSINE SIMILARITY ****/
/****************************/

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


};