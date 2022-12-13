//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2020
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//

#ifndef AMATH583_CNORM_HPP
#define AMATH583_CNORM_HPP

#include "Timer.hpp"
#include "Vector.hpp"
#include "amath583.hpp"
#include "norm_utils.hpp"

#include <cassert>
#include <cmath>
#include <future>
#include <iomanip>
#include <iostream>
#include <string>
#include <thread>
#include <cstddef>



double worker_a(const Vector& x, size_t begin, size_t end, size_t strides){
  double sum_of_squares = 0.0;
  for (size_t i = begin; i< end; i += strides){
    sum_of_squares += x(i)*x(i);
  }
  return sum_of_squares;
}
// Write me
double cyclic_two_norm(const Vector& x, size_t partitions) {
  double sum = 0.0;
  size_t blocksize = x.num_rows()/partitions; 
  std::vector<std::future<double>> sum_a ;

  for (size_t k= 0; k < partitions; ++k){
    sum_a.push_back(
      std::async(std::launch::async, worker_a, std::cref(x), k*blocksize, (k+1)*blocksize, partitions));
  }

  for (size_t k =0; k< partitions; ++k){
    sum+= sum_a[k].get(); 
  }
  return std::sqrt(sum);
}




#endif    // AMATH583_CNORM_HPP
