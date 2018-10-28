/*******************************/
/* lsh.cpp */

/* Name:    Andreas Charalampous
 * A.M :    1115201500195
 * e-mail:  sdi1500195@di.uoa.gr
 */
/********************************/
#include <iostream>
#include <unordered_set>
#include <unordered_map>

#include "hypercube.h"

using namespace std;

template class hypercube<int>;

/*  Implementation of all functions of the class
 *  that is used for LSH. Definitions found in
 *  lsh.h.
 */

/* L: num of tables for each metric, k: num of hash functions, */
/* n: dataset size */ 
template <class T>
hypercube<T>::hypercube(int metric, int k, int probes, int M){
    this->probes = probes;
    this->M = M;
    this->metric = metric;

    f = new unordered_map<int,int>;
    
    if(metrics == 1) // euclidean is defined
        eu_table = new euclidean<T>(k, pow(2, k));
    else if(metrics == 2) // cosine is defined
        cs_table = new csimilarity<T>(k);
}

template <class T>
hypercube<T>::~hypercube(){
    delete eu_table;
    delete cs_table;

    delete f;
}

template <class T>
int hypercube<T>::check_map(int key){
    unordered_map<int,int>::iterator it = f->find(key);
    if(it == f->end()){ // key is not yet registered    
        
        /* Create a new mapping between key and 0/1 */
        random_device rd;
	    mt19937 gen(rd());
        uniform_int_distribution<int> rand_01(0,1);
        
        f[key] = rand_01(gen);

        return f[key];
    }
    else // key was found
        return it->second;
}

template <class T>
void hypercube<T>::add_vector(vector_item<T>* new_vector){    
    int k;
    int bucket_num = 0;

    if(metric == 1){ // use euclidean
        k = eu_table->get_k(); // get number of hash function
        vector<int> hvalues = new vector<int>;
        
        for(int i = 0; i < k; i++){
            /* Get hash function value */
            hvalues.push_back(eu_table->get_val_hf(new_vector, i));

            int fi = hvalues[i];

            /* Get 1 or 0 value from map */
            fi = check_map(fi);

            /* Find bucket */
            bucket_num += fi * pow(2, eu_table->get_k() - i - 1);
        }

        eu_table->add_vector(new_vector, hvalues, bucket_num)
    }
}

template <class T>
void hypercube<T>::findANN(vector_item<T>& query, float radius, float& min_dist, string& ANN_name, ofstream& output){
    unordered_set<string> checked_set; // set that holds items that were checked
    if(metric == 1){
        k = eu_table->get_k(); // get number of hash function
        vector<int> hvalues = new vector<int>;
        
        for(int i = 0; i < k; i++){
            /* Get hash function value */
            hvalues.push_back(eu_table->get_val_hf(new_vector, i));

            int fi = hvalues[i];

            /* Get 1 or 0 value from map */
            fi = check_map(fi);

            /* Find bucket */
           bucket_num += fi * pow(2, this->eu_table->get_k() - i - 1);
        }

        vector<int>* neighbours = find_neighbours(bucket_num, probes);

        int vector_sz = this->eu_table->get_k() + 1; // size of vector
        

        int remaining_probes = probes;
        int remaining_items = M;
        int flag = 0;

        /* Check neighbours found */
        for(int i = 0; i < vector_sz; i++){
            if(flag == 1)
                break;
            for(int j = 0; j < neigbours[i].size(); j++){
                
                remaining_probes--; // about to check another neighbour
                if(remaining_probes < 0){ // no more neighbours to check
                    flag == 1;    
                    break;
                } 

                /* Get bucket from euclidean table */
                int f = neighbours[i][j];
                vector<euclidean_vec<T>*>& buck = eu_table->get_bucket(f);

                /* If radius was given as 0, find only the nearest neighbour */
                if(radius == 0){
                    for(unsigned int i = 0; i < buck.size(); i++){
                        remaining_items--; // about to check another vector
                        if(remaining_items < 0){ // no more neighbours to check
                            flag == 1;    
                            break;
                        } 

                        euclidean_vec<T>* cur_vec = buck[i]; // get current vector

                        vector_item<T>& item = cur_vec->get_vec();

                        string& item_id = item.get_id(); // get item id

                        /* Check if item was not checked already */
                        if(!in_set(checked_set, item_id)){
                            checked_set.insert(item_id);
                            float dist = eucl_distance(query, item);

                            /* Check if nearest neighbour */
                            if(dist <= min_dist || min_dist == 0.0){
                                min_dist = dist;
                                NN_name.assign(item_id);
                            }
                        }
                    } // end for all items in buckets 
                } // end if radius > 0


                /* Else check for items in radius */
                else{
                    for(unsigned int i = 0; i < buck.size(); i++){
                        remaining_items--; // about to check another vector
                        if(remaining_items < 0){ // no more neighbours to check
                            flag == 1;    
                            break;
                        } 
                        
                        euclidean_vec<T>* cur_vec = buck[i]; // get current vector

                        vector_item<T>& item = cur_vec->get_vec();
                        string& item_id = item.get_id(); // get item id

                        /* Check if item was not checked already */
                        if(!in_set(checked_set, item_id)){
                            checked_set.insert(item_id); 
                            float dist = eucl_distance(query, item);

                            /* Print item in radius of query */
                            if(dist <= radius){
                                output << tab << item_id << endl;
                            }
                            
                            /* Check if nearest neighbour */
                            if(dist <= min_dist || min_dist == 0.0){
                                min_dist = dist;
                                NN_name.assign(item_id);
                            }
                        }
                    } // end for all items in buckets
                } // end else radius > 0
            } // end for neighbours in current distance
        } // end for neighbours in probe
    } // end if metric == euclidean
}



template <class T>
vector<int>* hypercube<T>::find_neighbours(int num, int probes){
    vector<int> count; // each cell has number of neighbours in corresponding distance
    int num_of_bits = this->eu_table->get_k();
    int max_distance = num_of_bits + 1;

    /* neihbours[x] = neighbours in hamming distance x, x : {0, 1, 2, 3, ..., max_distance} */
    vector<int>* neighbours = new vector<int>[max_distance]; // neighbours buckets that will be returned

    int remaining_n = probes - 1; // remaining neigbours that need to be found
    neighbours[0].push_back(num); // self bucket must still be checked
    count.push_back(0);

    /* Find how many neihbours must be found in each distance, until probes are reached */
    for(int i = 1; i < max_distance; i++){

        /* Find number of neighbours in i hamming distance */
        int combs = get_combinations(num_of_bits, i);
        if(combs >= remaining_n){ // last neighbours number is found
            count.push_back(remaining_n);
            break;
        } 
        else{
            count.push_back(combs); // keep number of neighbours in distance i and keep searching
            remaining_n -= combs;
        }
    }

    remaining_n = probes - 1
    int max_num = pow(2, num_of_bits); // maximum possible number for number of bits
    for(int i = 0; i < max_num && remaining_n > 0; i++ ){
        if(i == num) // if same number, pass(already placed)
            continue;
        
        /* Compute hamming dist */
        int dist = hamming_dist(i, num);

        /* If neighbour is needed, then save in vector */
        if(count[dist] > 0){
            neihbours[dist].push_back(i);
            count[dist]--;
            remaining_n--;
        }
    }
}