#include <iostream>
#include <sstream>

#include "dataset.h"

using namespace std;

template class vector_item<int>;
template class dataset<int>;

template <class T>
vector_item<T>::vector_item(string info, int id){
	string point;
	
	istringstream iss(info, istringstream::in); 

    /* Save points in array */
    int i = 0;
	while( iss >> point )     
	{
	    this->coordinates[i] = stoi(point); 
        i++;
	}
    if(i != D)
        cout << "inv points" << endl;

    /* Save item name */
    item_id = "Item_" + to_string(id);
}


template <class T>
void vector_item<T>::print(){
    cout << "I am " << item_id << endl;
    for(int i = 0; i < D; i++)
        cout << i << ". " << coordinates[i] << endl;
}





/////////////
/* DATASET */
/////////////
template <class T>
void dataset<T>::add_vector(string newVector){
    /* Push new vector */
    vectors.push_back(new vector_item<T>(newVector, counter));
    
    /* Increase num of vectors */
    counter++;
}

template <class T>
dataset<T>::~dataset(){
    for(int i = 0; i < vectors.size(); i++)
        delete vectors[i];
    vectors.clear();
}

template <class T>
void dataset<T>::print(){
    cout << counter << endl;
    for(int i = 0; i < vectors.size(); i++)
        vectors[i]->print();

}