/*******************************/
/* utils.h */

/* Name:    Andreas Charalampous
 * A.M :    1115201500195
 * e-mail:  sdi1500195@di.uoa.gr
 */
/********************************/
#pragma once
#include <array>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_set>

#include "dataset.h"

/*  Header file for all variant functions and structs used
 *  to complete the LSH algorithm.
 */

/* Extract parameters that were given during execution */ 
int get_parameters(int, char**, std::string&, std::string&, std::string&, int&, int&);
int HC_get_parameters(int, char**, std::string&, std::string&, std::string&, int&, int&, int&);

/*  Print the valid form of given parameters */
void printValidParameters();
void HC_printValidParameters();

/*  Given a string, it check char-char to see if integer.   */
/*  Is yes, returns 1, else 0.                              */
int isNumber(char*);

/* Returns the number of digits of integer's binary form */
int get_int_len(int);

/* Computes and returns number of combinations (Comb(a,b)) */
int get_combinations(int, int);

/* Computes and returns the factorial of the given number */
int get_factorial(int);

/* Computes and returns the hamming distance of two integer(their binary form) */
int hamming_dist(int, int);

/* Given two arrays(vectors), calculates and returns their inner product */  
float vector_product(std::array<float,D>&, std::array<int, D>&);

/* Given a number of integers, concantetates them and returns the value */
long long int h_concantenate(std::vector<int>&);

/* Returns the modulo of the given integers */
long long int my_mod(int, long int);

/* Extract metrics from string, and return the corresponding number */
int get_metrics(std::string&);

/* Extract radius from query file and return it */
double get_radius(std::string&);

/* Computes the euclidean distance of 2 vectors */
template <class T>
float eucl_distance(vector_item<T>&, vector_item<T>&);

/* Computes the cosine distance of 2 vectors */
template <class T>
float cs_distance(vector_item<T>&, vector_item<T>&);

/* Asks user if he wants to continue to a new execution and if he wants */
/* to use different files, returning the corresponding choice */
int new_execution(std::ifstream&, std::ifstream&, std::ofstream&);

/* Search given set if contains string(item_id). Returns 1 if exists, else 0 */
int in_set(std::unordered_set<std::string>&, std::string&);

/* Performs exchausting search in the given dataset using the metric provided */
/* Finally returns the minimum distance */
template <class T>
float exchausting_s(dataset<T>&, vector_item<T>&, int);
