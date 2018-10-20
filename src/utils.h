/*******************************/
/* utils.h */

/* Name:    Andreas Charalampous
 * A.M :    1115201500195
 * e-mail:  sdi1500195@di.uoa.gr
 */
/********************************/
#pragma once
#include <array>
#include <vector>
#include "dataset.h"

/*  Header file for all variant functions and structs used
 *  to complete the LSH algorithm.
 */

/* Given two arrays(vectors), calculates and returns their inner product */  
float vector_product(std::array<float,D>&, std::array<int, D>&);

/* Given a number of integers, concantetates them and returns the value */
long int h_concantenate(std::vector<int>&);