/*******************************/
/* dataset.cpp */

/* Name:    Andreas Charalampous
 * A.M :    1115201500195
 * e-mail:  sdi1500195@di.uoa.gr
 */
/********************************/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "dataset.h"

using namespace std;

template class vector_item<int>;
template class dataset<int>;


/*  Implementation of all functions of dataset
 *  and vector_item. Definitions found in
 *  dataset.h.
 */

/////////////////////
//** VECTOR_ITEM **//
/////////////////////
template <class T>
vector_item<T>::vector_item(string& new_vector){
    string point;
	string id;

	istringstream iss(new_vector, istringstream::in); 

    /* Extract item name */
    iss >> id;

    /* Save item name */
    item_id = id;    

    /* Extract all points from string and insert in array */
    int i = 0;
	while( iss >> point )     
	{
        //cout << i << ". " << point << endl;
	    coordinates[i] = stoi(point); 
        i++;
	}
    if(coordinates.size() != D) // check if valid points where given
        cout << "[Creation of vector_item] Invalid dimensions in vector! Abort." << endl;
}


template <class T>
vector_item<T>::vector_item(string& new_vector, int id){
	string point;
	
	istringstream iss(new_vector, istringstream::in); 

    /* Extract all points from string and insert in array */
    int i = 0;
	while( iss >> point )     
	{
        //cout << i << ". " << point << endl;
	    coordinates[i] = stoi(point); 
        i++;
	}
    if(coordinates.size() != D) // check if valid points where given
        cout << "[Creation of vector_item] Invalid dimensions in vector! Abort." << endl;

    /* Save item name */
    item_id = "Item_" + to_string(id);
}

/* Print info about vector_item(Debugging) */
template <class T>
void vector_item<T>::print(){
    cout << "\tI am " << item_id << endl;
    for(int i = 0; i < D; i++)
        cout << "\t" << i << ". " << coordinates[i] << endl;

    cout << "\n" << endl;
}

/* Returns item name */
template <class T>
string vector_item<T>::get_id(){
    return this->item_id;
}

/* Return points array */
template <class T>
array<T, D>& vector_item<T>::get_points(){
    return coordinates;
}

/* Returns size of vector(number of dimensions) */
template <class T>
int vector_item<T>::get_size(){
    return this->coordinates.size();
}




/////////////
// DATASET //
/////////////

/* Push new vector in dataset, increase counter */
template <class T>
void dataset<T>::add_vector(string& new_vector){
    /* Push new vector */
    vectors.push_back(new vector_item<T>(new_vector));
    
    /* Increase num of vectors */
    counter++;
}

template <class T>
int dataset<T>::get_counter(){
    return this->counter;
}

template <class T>
vector_item<T>* dataset<T>::get_item(int index){
    return vectors[index];
}

/* Destroy all vector_items */
template <class T>
dataset<T>::~dataset(){
    for(unsigned int i = 0; i < vectors.size(); i++)
        delete vectors[i];
    vectors.clear();
}

/* Print info about dataset(Debugging) */
template <class T>
void dataset<T>::print(){
    cout << "[Dataset]: " << counter << endl;
    for(unsigned int i = 0; i < vectors.size(); i++)
        vectors[i]->print();

}
