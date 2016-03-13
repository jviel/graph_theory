/* file: user-interface.h
 * description: provides a user interface for dealing with linear algebra
 *              operations provided by the library
 */

#pragma once

#include <sstream>

#include "file-io.h"
#include "print.h"

namespace ui {
  struct menuItem {
    string name;
    vector<char> keys;
    int index;

    menuItem(const string &name, const vector<char> &keys, const int &index) :
      name(name),
      keys(keys),
      index(index)
    {}
  };

  void clearBuffer();
  void launch();
  int menu(string name, vector<menuItem> items);

  void vectors();
  void createVector(const map<string, vector<double>> &vecs);
  void readVectors(const map<string, vector<double>> &vecs);
  void updateVector(const map<string, vector<double>> &vecs);
  void deleteVector(const map<string, vector<double>> &vecs);

  void matrices();
  void operations();

  string getString(string prompt);
  vector<double> getVector(string prompt);
  matrix<double> getMatrix(string prompt);
  matrix<double> getSquareMatrix(string prompt);

  void clearBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }

  void launch() {
    bool quit = false;
    while (!quit) {
      int choice = menu(
        "Main Menu",
        {menuItem("Vectors", {'V'}, 1)
        ,menuItem("Matrices", {'M'}, 2)
        ,menuItem("Operations", {'O'}, 3)
        ,menuItem("Quit", {'Q'}, 4)}
      );

      switch (choice) {
        case 1: vectors(); break;
        case 2: matrices(); break;
        case 3: operations(); break;
        default: quit = true; break;
      }
    }
  }

  int menu(string name, vector<menuItem> items) {
    char input;

    newline(100);
    cout << "=== " << name << " ===" << endl;

    for (auto &item : items) {
      cout << " " << item.index << " (";
      unsigned long size = item.keys.size();
      for (unsigned long i = 0;  i < size; i++) {
        cout << item.keys[i];
        if (i < size - 1) {
          cout << ", ";
        }
      }
      cout << ") - " << item.name << endl;
    }

    while (true) {
      cout << endl << "Input: ";
      cin >> input;
      clearBuffer();

      for (auto &item : items) {
        if (item.index == ((int)input - 48)) { return item.index; }
        for (auto &k : item.keys) {
          if (toupper(k) == toupper(input)) { return item.index; }
        }
      }

      cout << "Invalid input, try again" << endl;
    }

    return 0;
  }

  void vectors() {
    int choice = menu(
      "Vectors",
      {menuItem("Create", {'C'}, 1)
      ,menuItem("Read", {'R'}, 2)
      ,menuItem("Update", {'U'}, 3)
      ,menuItem("Delete", {'D'}, 4)
      ,menuItem("Back", {'B'}, 5)}
    );

    auto vecs = file::readVectors();

    switch (choice) {
      case 1: createVector(vecs); break;
      case 2: readVectors(vecs); break;
      case 3: updateVector(vecs); break;
      case 4: deleteVector(vecs); break;
      default: break;
    }
  }

  void createVector(const map<string, vector<double>> &vecs) {
    newline(100);
    cout << "=== Create ===" << endl;

    if (vecs.size() > 0) {
      cout << "Taken Names";
      for (auto &v : vecs) { cout << " | " << v.first; }
      cout << endl;
    }

    string name = "";

    while (name == "") {
      name = getString("Name");

      for (auto &v : vecs) {
        if (v.first == name) {
          name = "";
          cout << endl << "Name already taken, try again" << endl;
        }
      }
    }

    auto elements = getVector("Elements");

    file::createVector(name, elements);
  }

  void readVectors(const map<string, vector<double>> &vecs) {
    newline(100);
    cout << "=== Read ===" << endl;
    println(vecs);
    cout << "press any key to return...";
    cin.get();
  }

  void updateVector(const map<string, vector<double>> &vecs) {
    newline(100);
    cout << "=== Update ===" << endl;

    if (vecs.size() == 0) {
      cout << "No vectors in memory, press any key to return...";
      cin.get();
      return;
    }

    cout << "Available vectors ";
    for (auto &v : vecs) { cout << " | " << v.first; }
    cout << endl;
    string name = "";
    bool success = false;

    while (!success) {
      name = getString("Name");

      for (auto &v : vecs)
        if (v.first == name)
          success = true;

      if (!success)
        cout << "No vector by that name exists, try again" << endl;
    }
    auto elements = getVector("Elements");

    file::updateVector(name, elements);
  }

  void deleteVector(const map<string, vector<double>> &vecs) {
    newline(100);
    cout << "=== Delete ===" << endl;

    if (vecs.size() == 0) {
      cout << "No vectors in memory, press any key to return...";
      cin.get();
      return;
    }

    cout << "Available vectors ";
    for (auto &v : vecs) { cout << " | " << v.first; }
    cout << endl;
    string name = "";
    bool success = false;

    while (!success) {
      name = getString("Name");

      for (auto &v : vecs)
        if (v.first == name)
          success = true;

      if (!success)
        cout << "No vector by that name exists, try again" << endl;
    }

    file::deleteVector(name);
  }

  void matrices() {

  }

  void operations() {

  }

  string getString(string prompt) {
    string input = "";

    cout << prompt << ": ";
    getline(cin, input);

    while (input == "") {
      cout << endl << "Invalid input, try again" << endl << prompt << ": ";
      getline(cin, input);
    }

    return input;
  }

  vector<double> getVector(string prompt) {
    vector<double> elements;
    cout << prompt << ": ";
    string t, word;
    getline(cin, t);

    istringstream iss(t);
    while (iss >> word) {
      double number;
      stringstream ss(word);
      ss >> number;
      if (ss.fail()) {
        cout << endl << "Invalid input, try again" << endl;
        return getVector(prompt);
      }

      elements.push_back(number);
    }

    if (elements.size() == 0) {
      cout << endl << "Invalid input, try again" << endl;
      return getVector(prompt);
    }

    return elements;
  }

  matrix<double> getMatrix(string prompt) {
    matrix<double> ret;
    vector<double> elements;
    cout << prompt << ": " << endl;
    string t, word;
    unsigned long rowLength = 0;

    do {
      elements = {};

      getline(cin, t);
      istringstream iss(t);
      while (iss >> word) {
        double number;
        stringstream ss(word);
        ss >> number;
        if (ss.fail()) {
          cout << endl << "Invalid input, try again" << endl;
          return getMatrix(prompt);
        }

        elements.push_back(number);
      }

      if (elements.size() != 0) {
        if (rowLength == 0)
          rowLength = elements.size();
        else if (rowLength != elements.size()) {
          cout << endl << "Invalid input, try again" << endl;
          return getMatrix(prompt);
        }
        ret.push_back(elements);
      }
    } while (elements.size() != 0);

    if (ret.size() == 0) {
      cout << "Invalid input, try again" << endl;
      return getMatrix(prompt);
    }

    return ret;
  }

  matrix<double> getSquareMatrix(string prompt) {
    auto mat = getMatrix(prompt);
    if (mat.size() != mat[0].size()) {
      cout << "Invalid input, try again" << endl;
      return getSquareMatrix(prompt);
    }
    return mat;
  }
}

