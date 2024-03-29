/*******************************/
/* dataset.h */

/* Name:    Andreas Charalampous
 * A.M :    1115201500195
 * e-mail:  sdi1500195@di.uoa.gr
 */
/********************************/
#pragma once
#include <string>
#include <array>
#include <vector>

#define D 128 // number of dimensions

/* Implemenention of data Container that holds vectors as records */


/* Records have id and an array with points on all D dimensions */
template <class T>
class vector_item{
    private:
        std::string item_id; // name of vector
        std::array<T, D> coordinates; // points of vector
    public:
        /* Given the points of vector and id, create a new vector_item */
        vector_item(std::string&);

        /* Accessors */
        std::string& get_id(); // returns id as string
        std::array<T, D>& get_points(); // returns an array with all the points of vector
        int get_size(); // returns size of vector
                
        /* Print vector stats */
        void print();
};

/* Container that holds records(vector_item) */
template <class T>
class dataset{
    private:
        int counter; // num of vectors
        std::vector<vector_item<T>*> vectors; // all vectors
    public:
        /* Con-De Structor */
        dataset(): counter(0){};
        ~dataset();
        
        /* Given a string with all the points, create new record and push */
        void add_vector(std::string&);
        
        /* Accessors */
        int get_counter();
        vector_item<T>* get_item(int); // Returns pointer to the item stored int the index given 
        
        /* Debugging */
        void print();
};
