/*******************************/
/* metrics.cpp */

/* Name:    Andreas Charalampous
 * A.M :    1115201500195
 * e-mail:  sdi1500195@di.uoa.gr
 */
/********************************/
#include <iostream>
#include <ctime>
#include <random>
#include <cmath>

#include "metrics.h"
#include "utils.h"

using namespace std;

template class euclidean_vec<int>;
template class euclidean<int>;
template class csimilarity<int>;


/*  Implementation of all functions of the metrics
 *  that are used in LSH. Definitions found in
 *  metrics.h.
 */


/////////////////
/** EUCLIDEAN **/
/////////////////

/** euclidean_vec **/
template <class T>
euclidean_vec<T>::euclidean_vec(vector_item<T>* vec, long int g){
	this->vec = vec;
	this->g = g;
}

template <class T>
void euclidean_vec<T>::print(){
	cout << "I am item in euclidean vec with g = " << g << " and points:" << endl;
	this->vec->print();
}


/** euclideanHF **/
euclideanHF::euclideanHF(){
	random_device rd;
	mt19937 gen(rd());
	normal_distribution<float> nd_random(0.0, 1.0);

	/* Generate random vector */
	for(unsigned int i = 0; i < D; i++)
		v[i] = nd_random(gen);

	/* Get random real number t(displacement) */
	uniform_real_distribution<> real_random(0.0, W - 0.000001);

	t = real_random(gen);
}

int euclideanHF::getValue(array<int, D>& vec){
	/* Calculation of: floor([ ( p * v ) + t) ] / w) */

	float product = vector_product(v, vec);
	float result = (product + t) / W;

	return (int)result;
}

void euclideanHF::print(){

	for (unsigned int i = 0; i < D; i++)
		cout << i << ". " << v[i] << endl;

	cout << "T: " << t << endl;
}


/** Euclidean metric **/
template <class T>
euclidean<T>::euclidean(int k, int dataset_sz) : k(k){
	random_device rd;
	mt19937 gen(rd()); // for random vector r

	/* Set metric parameters */
	this->tableSize = dataset_sz / TS_DIVISOR;
	M = pow(2, 32) - 5;

	/* Create empty buckets */
	buckets = new vector<euclidean_vec<T>*>[tableSize];
	for(int i = 0; i < tableSize; i++)
		cout << buckets[i].size() << endl;

	/* Create hash functions */
	for(int i = 0; i < k; i++)
		hfs.push_back(euclideanHF());

	/* Generate random vector r */
	uniform_int_distribution<int> rand_Z(MIN_Ri,MAX_Ri); 
	for(int i = 0; i < k; i++)
		r.push_back(rand_Z(gen));
}

template <class T>
int euclidean<T>::get_bucket_num(vector<int>& hvalues){
	long int f = 0.0;

	/* Calculation of: [(r1*h1 + r2*h2 + ... + rk*hk)modM]mod TS */
	for(int i = 0; i < k; i++)
		f += (hvalues[i] * r[i]) % this->M;

	f = f % this->M;
	
	f = f % this->tableSize;

	return f;
}

template <class T>
void euclidean<T>::add_vector(vector_item<T>* new_vector){
	vector<int> hvalues; // values returned from hash functions
	long int g;	// g(p) function
	int f; // f(p) function <-> bucket index 
	
	/* Get vector points */
	array<int, D>* vec_points = &new_vector->get_points();

	/* Get all hash functions values */
	for(int i = 0; i < k; i++)
		hvalues.push_back(hfs[i].getValue(*vec_points));

	/* Compute g(p) */
	g = h_concantenate(hvalues);

	/* Compute f(p) */
	f = get_bucket_num(hvalues);

	buckets[f].push_back(new euclidean_vec<T>(new_vector, g));
}





/////////////////////////
/** COSINE SIMILARITY **/
/////////////////////////
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
csimilarity<T>::csimilarity(int k){
	this->k = k;
	this->tableSize = pow(2, k);

	buckets = new vector<vector_item<T>*>[tableSize];

	for(int i = 0; i < k; i++)
		hfs.push_back(csimilarityHF());
}

template <class T>
void csimilarity<T>::add_vector(vector_item<T>* new_vector){
	int f = 0; // f(p) function <-> bucket index 
	
	/* Get vector points */
	array<int, D>* vec_points = &new_vector->get_points();

	/* Get all hash functions values */
	for(int i = 0; i < k; i++){
		int temp = hfs[i].getValue(*vec_points);
		f += temp * pow(2, k - i - 1); // compute binary value
	}

	buckets[f].push_back(new_vector);
}
