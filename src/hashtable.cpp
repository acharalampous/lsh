#include <iostream>
#include <ctime>
#include <random>

#include "hashtable.h"
#include "utils.h"

using namespace std;

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

int euclideanHF::getValue(array<int, D> vec){
	float product = vector_product(v, vec);

	float result = (product * t) / W;

	return (int)result;
}

void euclideanHF::print(){

	for (unsigned int i = 0; i < D; i++)
		cout << i << ". " << v[i] << endl;

	cout << "T: " << t << endl;
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

int csimilarityHF::getValue(array<int, D> vec){
	
	float product = vector_product(r, vec);
	
	return (product >= 0)? 1 : 0;

}

void csimilarityHF::print(){

	for (unsigned int i = 0; i < D; i++)
		cout << i << ". " << r[i] << endl;

}