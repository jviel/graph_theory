#pragma once

#include "linear.h"
#include <sstream>
#include "print.h"

namespace cli {
  const string argumentError = "wrong number of args supplied";
  const string missingFunctionError = "no function by that name";

  void parse(const vector<string> &args);
  vector<double> getVector(const string &input);

  void parse(const vector<string> &args) {
    string func = args[0];
    if (func == "magnitude") {
      if (args.size() != 2) {
        cerr << argumentError << endl;
      }
      println(magnitude(getVector(args[1])));
    } else if (func == "dot") {
      cout << "dot" << endl;
    } else if (func == "scale") {
      cout << "scale" << endl;
    } else if (func == "lower") {
      cout << "lower" << endl;
    } else {
      cerr << missingFunctionError << endl;
    }

    return;
  }

  vector<double> getVector(const string &input) {
    vector<double> elements;
    string word;

    istringstream iss(input);
    while (iss >> word) {
      double number;
      stringstream ss(word);
      ss >> number;
      if (ss.fail()) {
        cerr << "vector input failed" << endl;
        return {};
      }

      elements.push_back(number);
    }

    if (elements.size() == 0) {
      cout << endl << "Invalid input, try again" << endl;
      return getVector(input);
    }

    return elements;  }

}

