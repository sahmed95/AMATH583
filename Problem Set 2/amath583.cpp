//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2020
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//

#include "amath583.hpp"
#include "Matrix.hpp"
#include "Vector.hpp"
#include <cmath>
#include <cstddef>
#include <cassert>

void zeroize(Vector& x) {
  for (size_t i=0; i < x.num_rows(); ++i) {
    x(i) = 0.0; 
  }
}

double one_norm(const Vector& x) {
  double sum = 0.0;
  for (size_t i = 0; i < x.num_rows(); ++i) {
    sum += std::abs(x(i));
  }
  return sum;
}

double two_norm(const Vector& x) {
  double norm = 0.0;
  double sum= 0.0;
  for (size_t i = 0; i < x.num_rows(); ++i) {
    sum += x(i)*x(i);
  }
  norm = std::sqrt(sum);
  return norm;
}

double inf_norm(const Vector& x) {
  double result = 0.0;
  double tmp = 0.0;
  for (size_t i = 0; i < x.num_rows(); ++i) {
    tmp = std::abs(x(i));
    result = std::max(result, tmp);
  }
  return result;
}

double dot(const Vector& x, const Vector& y) {
  assert(x.num_rows() == y.num_rows()); 
  double sum = 0.0; 
  for (size_t i = 0; i < x.num_rows(); ++i) {
    sum += x(i)*y(i);
  }
  return  sum;
}

double two_norm_d(const Vector& x) { 
  // WRITE ME / FIX ME -- can you make the function only one line long including return?
  return 0.0;  
}

double one_norm(const Matrix& A) {
  double sum = 0.0;
  for (size_t j = 0; j < A.num_cols(); ++j) {    // for each column
    double tmp = 0.0;
    for (size_t i = 0; i < A.num_rows(); ++i) {    // compute column sum
      tmp += std::abs(A(i, j));
    }
    sum = std::max(sum, tmp);
  }
  return sum;
}


double inf_norm(const Matrix& A) {
  double sum = 0.0;
  for (size_t i = 0; i < A.num_rows(); ++i) {   // for each row
    double tmp = 0.0; 
    for (size_t j = 0; j < A.num_cols(); ++j) {    // compute row sum 
      tmp += std::abs(A(i,j));
    }
    sum = std::max(sum,tmp);
  } 
  return sum;
}


double f_norm(const Matrix& A) {
  double sum = 0.0;
  double norm = 0.0;
  for (size_t i = 0; i < A.num_rows(); ++i) {   
    for (size_t j = 0; j < A.num_cols(); ++j) {    
      sum += A(i,j)*A(i,j);
    }
  }
  norm = std::sqrt(sum);  
  return norm;
}