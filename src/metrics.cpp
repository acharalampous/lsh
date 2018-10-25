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
#include <fstream>

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
euclidean_vec<T>::euclidean_vec(vector_item<T>* vec, vector<int>* g){
	this->vec = vec;
	this->g = g;
}

template <class T>
void euclidean_vec<T>::print(){
	cout << "I am item in euclidean vec with g: " << endl;
	for(unsigned int i = 0; i < this->g->size(); i++)
		cout << (*g)[i];
	cout << endl;

	this->vec->print();
}

template <class T>
vector_item<T>& euclidean_vec<T>::get_vec(){
	return *(this->vec);
}

template <class T>
vector<int>& euclidean_vec<T>::get_g(){
	return *(this->g);
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

/* Get value of hash function */
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
	long long int f = 0;

	/* Calculation of: [(r1*h1 + r2*h2 + ... + rk*hk)modM]mod TS */
	for(int i = 0; i < k; i++)
		f += my_mod(hvalues[i] * r[i] ,this->M);

	f = my_mod(f, this->M);
	
	f = f % this->tableSize;

	return f;
}

template <class T>
void euclidean<T>::add_vector(vector_item<T>* new_vector){
	vector<int>* hvalues = new vector<int>; // values returned from hash functions
	int f; // f(p) function <-> bucket index 
	
	/* Get vector points */
	array<int, D>* vec_points = &new_vector->get_points();

	/* Get all hash functions values */
	for(int i = 0; i < k; i++)
		hvalues->push_back(hfs[i].getValue(*vec_points));

	/* Compute f(p) */
	f = get_bucket_num(*hvalues);

	if(f < 0)
		cout << "OVERFLOW" << endl;
	buckets[f].push_back(new euclidean_vec<T>(new_vector, hvalues));
}

template <class T>
vector<euclidean_vec<T>*>& euclidean<T>::get_bucket(int index){
	return this->buckets[index];
}


template <class T>
void euclidean<T>::findANN(vector_item<T>& query, float radius, float& min_dist, string& NN_name, ofstream& output){
	string tab = "\t";
	vector<int> hvalues; // values returned from hash functions
	int f; // f(p) function <-> bucket index

	/* First we must find the bucket that corresponds to query */
	/* Get vector points */
	array<int, D>* query_points = &(query.get_points());

	/* Get all hash functions values */
	for(int i = 0; i < k; i++)
		hvalues.push_back(hfs[i].getValue(*query_points));

	/* Compute f(p) */
	f = get_bucket_num(hvalues);

	vector<euclidean_vec<T>*>& buck = get_bucket(f);

	/* If radius was given as 0, find only the nearest neighbour */
	if(radius == 0){
		for(unsigned int i = 0; i < buck.size(); i++){
			euclidean_vec<T>* cur_vec = buck[i]; // get current vector
			if(comp_gs(cur_vec->get_g(), hvalues)){ // check if same 
				float dist = eucl_distance(query, cur_vec->get_vec());

				/* Check if nearest neighbour */
				if(dist <= min_dist || min_dist == 0.0){
					min_dist = dist;
					NN_name.assign((cur_vec->get_vec()).get_id());
				}
			}
		}
	}


	/* Else check for items in radius */
	else{
		for(unsigned int i = 0; i < buck.size(); i++){
			euclidean_vec<T>* cur_vec = buck[i]; // get current vector
			if(comp_gs(cur_vec->get_g(), hvalues)){ // check if same 
				float dist = eucl_distance(query, cur_vec->get_vec());

				/* Print item in radius of query */
				if(dist <= radius){
					output << tab << cur_vec->get_vec().get_id() << endl;
				}
				/* Check if nearest neighbour */
				if(dist <= min_dist || min_dist == 0.0){
					min_dist = dist;
					NN_name.assign((cur_vec->get_vec()).get_id());
				}
			}
		}
	}

}

template <class T>
float euclidean<T>::eucl_distance(vector_item<T>& vec1, vector_item<T>& vec2){
	if(vec1.get_size() != vec2.get_size()){
		cout << "Invalid dimensions" << endl;
		exit(0);
	}

	float dist = 0.0;

	array<T, D>& arr1 = vec1.get_points();
	array<T, D>& arr2 = vec2.get_points();


	for(unsigned int i = 0; i < arr1.size(); i++)
		dist += pow(arr1[i] - arr2[i], 2);

	dist = sqrt(dist);

	return dist;
}

template <class T>
int euclidean<T>::comp_gs(vector<int>& g1, vector<int>& g2){
	/* Check if same dimensions */
	if(g1.size() != g2.size())
		return 0;

	/* Check all values */
	for(unsigned int i = 0; i < g1.size(); i++){
		if(g1[i] != g2[i])
			return 0;
	}

	/* Reaching this point means that vectors(gs) are the same */
	return 1;
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

/* Get value of hash function */
int csimilarityHF::getValue(array<int, D>& vec){
	
	float product = vector_product(r, vec);
	
	/* if product > 0 return 1, else return 0 */
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

template <class T>
vector<vector_item<T>*>& csimilarity<T>::get_bucket(int index){
	return this->buckets[index];
}


template <class T>
void csimilarity<T>::findANN(vector_item<T>& query, float radius, float& min_dist, string& NN_name){
	int f = 0; // f(p) function <-> bucket index

	/* First we must find the bucket that corresponds to query */
	/* Get vector points */
	array<int, D>* query_points = &(query.get_points());

	for(int i = 0; i < k; i++){
		int temp = hfs[i].getValue(*query_points);
		f += temp * pow(2, k - i - 1); // compute binary value
	}

	vector<vector_item<T>*>& buck = get_bucket(f);

	for(unsigned int i = 0; i < buck.size(); i++){
		vector_item<T>* cur_vec = buck[i]; // get current vector
		
		/* Calculate distance between vectors */
		float dist = cs_distance(query, *cur_vec);
	
		if(dist <= radius){
			cout << "\t" << cur_vec->get_id() << endl;
		}
		if(dist <= min_dist || min_dist == 0.0){
			min_dist = dist;
			NN_name.assign(cur_vec->get_id());
		}
	}

}

template <class T>
float csimilarity<T>::cs_distance(vector_item<T>& vec1, vector_item<T>& vec2){
	/* Compute ((vec1 * vec2) / (||vec1||*||vec2||)) */
 	if(vec1.get_size() != vec2.get_size()){
		cout << "Invalid dimensions" << endl;
		exit(0);
	}

	float dist;
	float euc_dist = 0.0;
	float arr1_norm = 0.0;
	float arr2_norm = 0.0;

	array<T, D>& arr1 = vec1.get_points();
	array<T, D>& arr2 = vec2.get_points();


	for(unsigned int i = 0; i < arr1.size(); i++){
		euc_dist += (arr1[i] * arr2[i]); // vec1 & vec2
		arr1_norm += arr1[i] * arr1[i]; // ||vec1||
		arr2_norm += arr2[i] * arr2[i]; // ||vec2||
	}

	arr1_norm = sqrt(arr1_norm);
	arr2_norm = sqrt(arr2_norm);

	dist = euc_dist / (arr1_norm * arr2_norm);

	return dist;
}
