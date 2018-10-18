#pragma once
#include <array>

#include "dataset.h"

#define W 4 // window

/* Abstract class of hash Function */
class hashFunction{
    private:

    public:
       	virtual int getValue() = 0;
};

/* Hash function for euclidean distance(LSH) */ 
class euclideanHF: public hashFunction{
	private:
		std::array<float, D> v; // random vector
		float t; // random displacement
	
	public:
		/* Con-De structor */
		euclideanHF();
		int getValue();
		 

};


