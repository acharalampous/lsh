#pragma once
#include <array>
#include <vector>
#include <list>

#include "dataset.h"

#define W 4 // window

/* Abstract class of hash Function */
class hashFunction{
    private:

    public:
       	virtual int getValue(std::array<int,D>&) = 0;
};
template <class T>
class hashTable{
	private:
		std::vector<hashFunction*> hfs; // hash functions
		std::vector<vector_item*>* tables; // hash tables
		int k;
	public:


};

/* Hash function for euclidean distance(LSH) */ 
class euclideanHF: public hashFunction{
	private:
		std::array<float, D> v; // random vector
		float t; // random displacement
	
	public:
		/* Con-De structor */
		euclideanHF();
		
		
		int getValue(std::array<int,D>&); // get hash function value
		void print(); // print hash function info
		
};

class csimilarityHF: public hashFunction{
	private:
		std::array<float,D> r; // random vector
	public:
		csimilarityHF();

		int getValue(std::array<int,D>&);
		void print();
};
