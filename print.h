#pragma once

#include <iostream>

#include "linear.h"

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

template <class V>
void print(const V &value);

template <class V>
void print(const std::vector<V> &vec);

template <class M>
void print(const matrix<M> &mat);

void print(const std::vector<gsl_complex> &vec);

template <class V>
void println(const V &value);

void newline(unsigned long times = 1);

template <class V>
void print(const V &value) {
  std::cout << value;
}

template <class V>
void print(const std::vector<V> &vec) {
  unsigned long size = vec.size();
  print("<");
  for (unsigned long i = 0; i < size; i++) {
    print(vec[i]);
    if (i != size - 1) {
      print(", ");
    }
  }
  print(">");
}

template <class M>
void print(const matrix<M> &mat) {
  unsigned long rows = mat.size();
  unsigned long columns = mat[0].size();

  for (unsigned long r = 0; r < rows; r++) {
    if (r != 0) { newline(); }
    print("|");
    for (unsigned long c = 0; c < columns; c++) {
      print(mat[r][c]);
      if (c != columns - 1) {
        print(", ");
      }
    }
    print("|");
  }
}

void print(const std::vector<gsl_complex> &vec) {
  std::cout << "EigenValues" << std::endl;
  for (unsigned long i = 0; i < vec.size(); i++) {
    std::cout << "\u03BB" << i + 1
    << " = " << GSL_REAL(vec[i])
    << " + " << GSL_IMAG(vec[i]) << "i" << std::endl;
  }
}

template <class V>
void println(const V &value) {
  print(value);
  newline();
}

void newline(unsigned long times) {
  for (unsigned long i = 0; i < times; i++) {
    std::cout << std::endl;
  }
}

