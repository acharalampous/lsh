/*******************************/
/* utils.cpp */

/* Name:    Andreas Charalampous
 * A.M :    1115201500195
 * e-mail:  sdi1500195@di.uoa.gr
 */
/********************************/
#include <iostream>
#include <cmath>
#include "utils.h"
#include "dataset.h"

using namespace std;

/*  All functions implementions that are defined in utils.h */

/* Compute inner product of two vectors */
float vector_product(std::array<float, D>& vec1, std::array<int, D>& vec2){
    float product = 0.0;

    for(unsigned int i = 0; i < D; i++)
        product += vec1[i] * vec2[i];

    return product;
}

long long int h_concantenate(vector<int>& hs){
    /* Creates a string with the concatenated ints, and then it is */
    /* returned converted back to int.                             */

    string res_str("");
    for(unsigned int i = 0; i < hs.size(); i++)
        res_str += to_string(abs(hs[i]));


    return stoll(res_str);
}

/* Computes and returns the modulo of the ginen values a mod b */
long long int my_mod(int a, long int b){
	long long int res = a - ((floor( (long double)a / (long double)b) ) * b); 
    return res;
}

int get_metrics(string& metrics){
    int result = 0;
    if(metrics.empty()) // no definition -> use euclidean only
        return 1;
    
    if(metrics.compare(0, 9, "@metric ")) // check if metrics given
        return 0;

    if(metrics.find("euclidean") != string::npos) // euclidean is defined
        result = 1;
    
    if(metrics.find("cosine") != string::npos) // cosine is defined
        result |= 2;

    return result;
}

float get_radius(std::string& radius){
    if(radius.compare(0, 9, "Radius: <")) // check if metrics given
        return 0;

    int pos1 = radius.find('<');
    int pos2 = radius.find('>');

    string temp = radius.substr(pos1, pos2 - pos1);

    float result = stof(temp);

    return result;
}