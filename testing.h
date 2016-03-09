#pragma once
#define SHOW_PASSING true
#define USE_COLOR false

#include <string>
#include <ctime>
#include <vector>

#include "print.h"

template <class T, class L>
void expect(const std::string &name, const T &expected, const L &actual);

template <class T, class L>
void expect(const std::string &name, const T &expected,
            const L &actual, const T &threshold);

template <class T, class L>
void expect(const std::string &name, const T &expected,
            const L &actual) {
  std::clock_t start = std::clock();
  auto _actual = actual();
  double duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;

  bool passed = expected == _actual;

  if (!passed || SHOW_PASSING) {
    if (USE_COLOR) {
      if (!passed) {
        std::cout << RED << name << ": failed" << RESET << std::endl;
      } else {
        std::cout << GREEN << name << ": passed" << RESET << std::endl;
      }
    } else {
      if (!passed) {
        std::cout << name << ": failed" << std::endl;
      } else {
        std::cout << name << ": passed" << std::endl;
      }
    }

    std::cout << "duration = " << duration << " seconds" << std::endl;

    println("expected = ");
    println(expected);

    println("actual = ");
    println(_actual);
    newline();
  }

  return;
};

template <class T, class L>
void expect(const std::string &name, const T &expected,
            const L &actual, const T &threshold) {
  std::clock_t start = std::clock();
  auto _actual = actual();
  double duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;

  bool passed = _actual > expected - threshold && _actual < expected + threshold;

  if (!passed || SHOW_PASSING) {
    if (USE_COLOR) {
      if (!passed) {
        std::cout << RED << name << ": failed" << RESET << std::endl;
      } else {
        std::cout << GREEN << name << ": passed" << RESET << std::endl;
      }
    } else {
      if (!passed) {
        std::cout << name << ": failed" << std::endl;
      } else {
        std::cout << name << ": passed" << std::endl;
      }
    }

    std::cout << "duration = " << duration << " seconds" << std::endl;

    print("expected = ");
    println(expected);

    print("actual = ");
    println(_actual);

    print("threshold = ");
    println(threshold);
    newline();
  }

  return;
};
