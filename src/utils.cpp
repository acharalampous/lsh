#include <iostream>
#include <array>

#include "utils.h"
#include "dataset.h"

using namespace std;

float vector_product(std::array<float, D> vec1, std::array<int, D> vec2){
    float product = 0.0;

    for(unsigned int i = 0; i < D; i++)
        product = vec1[i] * vec2[i];

    return product;
}