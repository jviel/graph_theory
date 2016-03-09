/* file: testing.h
 * description: a simple unit testing framework for testing your code
 */

#pragma once

#include <string>
#include <ctime>
#include <vector>

#include "print.h"

namespace testing {
  #define SHOW_PASSING true // whether or not to show passing tests
  #define USE_COLOR false   // whether or not to use color in the console

  template <class T, class L>
  void expect(const string &name, const T &expected, const L &actual);

  template <class T, class L>
  void expect(const string &name, const T &expected,
              const L &actual, const T &threshold);

  template <class T, class L>
  void expect(const string &name, const T &expected,
              const L &actual) {
    clock_t start = clock();
    auto _actual = actual();
    double duration = (clock() - start) / (double)CLOCKS_PER_SEC;

    bool passed = expected == _actual;

    if (!passed || SHOW_PASSING) {
      if (USE_COLOR) {
        if (!passed) {
          cout << RED << name << ": failed" << RESET << endl;
        } else {
          cout << GREEN << name << ": passed" << RESET << endl;
        }
      } else {
        if (!passed) {
          cout << name << ": failed" << endl;
        } else {
          cout << name << ": passed" << endl;
        }
      }

      cout << "duration = " << duration << " seconds" << endl;

      println("expected = ");
      println(expected);

      println("actual = ");
      println(_actual);
      newline();
    }

    return;
  };

  template <class T, class L>
  void expect(const string &name, const T &expected,
              const L &actual, const T &threshold) {
    clock_t start = clock();
    auto _actual = actual();
    double duration = (clock() - start) / (double)CLOCKS_PER_SEC;

    bool passed = _actual > expected - threshold && _actual < expected + threshold;

    if (!passed || SHOW_PASSING) {
      if (USE_COLOR) {
        if (!passed) {
          cout << RED << name << ": failed" << RESET << endl;
        } else {
          cout << GREEN << name << ": passed" << RESET << endl;
        }
      } else {
        if (!passed) {
          cout << name << ": failed" << endl;
        } else {
          cout << name << ": passed" << endl;
        }
      }

      cout << "duration = " << duration << " seconds" << endl;

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
}

