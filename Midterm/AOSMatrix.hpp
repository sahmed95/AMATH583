//
// This file is part of the course materials for AMATH483/583 at the University of Washington,
// Spring 2020
//
// Licensed under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
// https://creativecommons.org/licenses/by-nc-sa/4.0/
//
// Author: Andrew Lumsdaine
//
#ifndef AMATH583_AOS_HPP
#define AMATH583_AOS_HPP

#include <cassert>
#include <tuple>
#include <vector>

#include "Vector.hpp"

class AOSMatrix {
private:
  typedef std::tuple<size_t, size_t, double> element;

public:
  AOSMatrix(size_t M, size_t N) : num_rows_(M), num_cols_(N) {}

  void push_back(size_t i, size_t j, double val) { /* Write Me */
    assert(i < num_rows_ && i >= 0);
    assert(j < num_cols_ && j >= 0);

    storage_.push_back(element(i, j, val));
  }

  void clear() { storage_.clear(); }

  void reserve(size_t n) {
    assert(n >= 0);

    storage_.reserve(n);
  }

  size_t num_rows() const { return num_rows_; }
  size_t num_cols() const { return num_cols_; }
  size_t num_nonzeros() const { return storage_.size(); }

  void stream_coordinates(std::ostream& output_file) const { /* Write Me */
    for (size_t i = 0; i < storage_.size(); ++i) {
      output_file << std::get<0>(storage_[i]) << " ";
      output_file << std::get<1>(storage_[i]) << " ";
      output_file << std::get<2>(storage_[i]) << " ";
      output_file << std::endl;
    }
  }

  void matvec(const Vector& x, Vector& y) const {
   for (size_t m = 0; m < storage_.size(); ++m) {
      element aik = storage_[m];
      y(std::get<0>(aik)) += std::get<2>(aik) * x(std::get<1>(aik));
    }
  }


  void t_matvec(const Vector& x, Vector& y) const {
   for (size_t m = 0; m < storage_.size(); ++m) {
      element aik = storage_[m];
      y(std::get<1>(aik)) += std::get<2>(aik) * x(std::get<0>(aik));
    }
  }

  void matmat(const Matrix& B, Matrix& C) const {
    for (size_t j = 0; j < C.num_cols(); ++j) {
      for (size_t m = 0; m < storage_.size(); ++m) {
        element aik = storage_[m]; 
        C(std::get<0>(aik), j) += std::get<2>(aik) * B(std::get<1>(aik),j);
      }
    }
  }

private:
  size_t               num_rows_, num_cols_;
  std::vector<element> storage_;
};

#endif    // AMATH583_AOS_HPP
