#pragma once
#include <string>
#include <array>
#include <vector>

#define D 6


template <class T>
class vector_item{
    private:
        std::string item_id; // name of vector
        std::array<T, 128> coordinates; // points of vector
    public:
        /* Given the points of vector and id, create a new vector_item */
        vector_item(std::string, int);
        ~vector_item(){std::cout << "i got destroyed" << std::endl;};

        /* Print vector stats */
        void print();

        /* Mutators */
        //void set_id(int); // set new id given a number(id)
        //void set_id(std::string); // set new id given a string(full_name)

        /* Accessors */
        //std::string get_id();
        //std::array<T, 128> get_points();
};

template <class T>
class dataset{
    private:
        int counter;
        std::vector<vector_item<T>*> vectors;
    public:
        dataset(): counter(0){};
        ~dataset();
        
        void add_vector(std::string);
        void print();
};