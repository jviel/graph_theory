/* file: file-io.h
 * description: provides ways for reading and writing data structures to a file
 */

#pragma once

#include <sstream>
#include <stdio.h>
#include <fstream>
#include <map>

#include "linear.h"

namespace file {

  #define VECTORPATH "vectors.txt"
  #define MATRIXPATH "matrices.txt"

  bool createVector(string name, vector<double> vec);
  map<string,vector<double>> readVectors();
  vector<double> readVector(string name);
  bool updateVector(string name, vector<double> vec);
  bool destroyVector(string name);
  bool replaceAllVectors(map<string,vector<double>> vecs);

  bool createMatrix(string name, matrix<double> mat);
  map<string,matrix<double>> readMatrices();
  matrix<double> readMatrix(string name);
  bool updateMatrix(string name, matrix<double> mat);
  bool destroyMatrix(string name);
  bool replaceAllMatrices(map<string,matrix<double>> mats);

  bool createVector(string name, vector<double> vec) {
    for (auto &m : readVectors())
      if (m.first == name)
        return false;

    ofstream file(VECTORPATH, ios::app);
    if (!file.is_open()) { return false; }

    file << "[" << name << "]" << endl;
    for (unsigned long i = 0; i < vec.size(); i++) {
      file << vec[i];
      if (i < vec.size() - 1)
        file << " ";
    }
    file << endl << "[end]" << endl;
    file.close();

    return true;
  }

  map<string,vector<double>> readVectors() {
    string line, name, numberString;
    double number;
    map<string,vector<double>> ret;
    bool reading = false;

    ifstream file(VECTORPATH);
    if (!file.is_open()) { return ret; }

    while(getline(file, line)) {
      if (reading) {
        if (line == "[end]") {
          reading = false;
        } else {
          istringstream elementStream(line);
          while (elementStream >> numberString) {
            stringstream numberStream(numberString);
            numberStream >> number;
            ret[name].push_back(number);
          }
        }
      } else {
        if (line[0] == '[' && line[line.size() - 1] == ']') {
          string s = line.substr(1, line.size() - 2);
          name = s;
          reading = true;
        }
      }
    }

    file.close();
    return ret;
  };

  vector<double> readVector(string name) {
    return readVectors()[name];
  }

  bool updateVector(string name, vector<double> vec) {
    auto vecs = readVectors();

    for (auto &v : vecs) {
      if (v.first == name) {
        vecs[name] = vec;
        return replaceAllVectors(vecs);
      }
    }

    return false;
  }

  bool destroyVector(string name) {
    auto vecs = readVectors();

    vecs.erase(name);

    return replaceAllVectors(vecs);
  }

  bool replaceAllVectors(map<string,vector<double>> vecs) {
    if (remove(VECTORPATH) != 0) { return false; }

    ofstream file(VECTORPATH);
    if (!file.is_open()) { return false; }

    for (auto &nv : vecs) {
      file << "[" << nv.first << "]" << endl;
      for (unsigned long r = 0; r < nv.second.size(); r++) {
        file << nv.second[r];
        if (r < nv.second.size() - 1) {
          file << " ";
        }
      }
      file << endl << "[end]" << endl;
    }
    file.close();
    return true;
  }

  bool createMatrix(string name, matrix<double> mat) {
    for (auto &m : readMatrices())
      if (m.first == name)
        return false;

    ofstream file(MATRIXPATH, ios::app);
    if (!file.is_open()) { return false; }

    unsigned long
      rows = mat.size(),
      columns = mat[0].size();

    file << "[" << name << "]" << endl;
    for (unsigned long r = 0; r < rows; r++) {
      for (unsigned long c = 0; c < columns; c++) {
        file << mat[r][c];
        if (c < columns - 1)
          file << " ";
      }
      if (r < rows - 1)
        file << endl;
    }
    file << endl << "[end]" << endl;
    file.close();

    return true;
  }

  map<string,matrix<double>> readMatrices() {
    string line, name, numberString;
    double number;
    map<string,matrix<double>> ret;
    vector<double> elements;
    bool reading = false;

    ifstream file(MATRIXPATH);
    if (!file.is_open()) { return ret; }

    while(getline(file, line)) {
      if (reading) {
        if (line == "[end]") {
          reading = false;
        } else {
          elements = {};
          istringstream elementStream(line);
          while (elementStream >> numberString) {
            stringstream numberStream(numberString);
            numberStream >> number;
            elements.push_back(number);
          }
          ret[name].push_back(elements);
        }
      } else {
        if (line[0] == '[' && line[line.size() - 1] == ']') {
          string s = line.substr(1, line.size() - 2);
          name = s;
          reading = true;
        }
      }
    }

    file.close();
    return ret;
  };

  matrix<double> readMatrix(string name) {
    return readMatrices()[name];
  }

  bool updateMatrix(string name, matrix<double> mat) {
    auto mats = readMatrices();

    for (auto &m : mats) {
      if (m.first == name) {
        mats[name] = mat;
        return replaceAllMatrices(mats);
      }
    }

    return false;
  }

  bool destroyMatrix(string name) {
    auto mats = readMatrices();

    mats.erase(name);

    return replaceAllMatrices(mats);
  }

  bool replaceAllMatrices(map<string,matrix<double>> mats) {
    if (remove(MATRIXPATH) != 0) { return false; }

    ofstream file(MATRIXPATH);
    if (!file.is_open()) { return false; }

    for (auto &nm : mats) {
      file << "[" << nm.first << "]" << endl;

      unsigned long
        rows = nm.second.size(),
        columns = nm.second[0].size();

      for (unsigned long r = 0; r < rows; r++) {
        for (unsigned long c = 0; c < columns; c++) {
          file << nm.second[r][c];
          if (c < columns - 1)
            file << " ";
        }
        if (r < rows - 1)
          file << endl;
      }

      file << endl << "[end]" << endl;
    }

    file.close();
    return true;
  }
}


