#include <iostream>
#include <ctime>
#include <random>
#include <cmath>

#include "lsh.h"
#include "utils.h"

using namespace std;


template class euclidean<int>;
template class csimilarity<int>;

euclideanHF::euclideanHF(){
	random_device rd;

	mt19937 gen(rd());

	/* Get random vector */
	for(unsigned int i = 0; i < D; i++){
		normal_distribution<float> nd_random(0.0, 1.0);
		
		v[i] = nd_random(gen);
	}

	/* Get random real number t(displacement) */
	uniform_real_distribution<> real_random(0.0, W);

	t = real_random(gen);
}

int euclideanHF::getValue(array<int, D>& vec){
	float product = vector_product(v, vec);

	float result = (product * t) / W;

	return (int)result;
}

void euclideanHF::print(){

	for (unsigned int i = 0; i < D; i++)
		cout << i << ". " << v[i] << endl;

	cout << "T: " << t << endl;
}


template <class T>
euclidean<T>::euclidean(int k, int dataset_sz){
	this->k = k;
	this->tableSize = dataset_sz / TS_DIVISOR;
	M = pow(2, 32) - 5;

	buckets = new vector<vector_item<T>*>[tableSize];

	for(int i = 0; i < k; i++)
		hfs.push_back(new euclideanHF);

	uniform_int_distribution<int> rand_Z(-20000,20000);
	default_random_engine gen; 

	for(int 0; i < k; i++)
		r.push_back(rand_Z(gen));
}



csimilarityHF::csimilarityHF(){
	random_device rd;

	mt19937 gen(rd());

	/* Get random vector */
	for(unsigned int i = 0; i < D; i++){
		normal_distribution<float> nd_random(0.0, 1.0);
		
		r[i] = nd_random(gen);
	}

}

int csimilarityHF::getValue(array<int, D>& vec){
	
	float product = vector_product(r, vec);
	
	return (product >= 0)? 1 : 0;

}

void csimilarityHF::print(){

	for (unsigned int i = 0; i < D; i++)
		cout << i << ". " << r[i] << endl;

}


template <class T>
csimilarityHT<T>::csimilarityHT(int k, int tableSize) : hashTable<T>(k, tableSize, 1){}