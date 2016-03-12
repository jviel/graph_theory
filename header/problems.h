/* file: problems.h
 * description: working through the problems for exam 4
 */

#pragma once

#include "linear.h"
#include "print.h"

void problem1();
void problem2();
void problem3();
void problem4();
void problem5();
void problem6();
void problem8();
void problem9();
void problem10();

void problem1() {
  matrix<double> a =
    {{0, 1, 0, 1, 0, 0, 0, 0}
    ,{1, 0, 0, 0, 0, 0, 0, 1}
    ,{0, 0, 0, 1, 0, 0, 1, 0}
    ,{1, 0, 1, 0, 1, 1, 0, 1}
    ,{0, 0, 0, 1, 0, 0, 0, 1}
    ,{0, 0, 0, 1, 0, 0, 1, 1}
    ,{0, 0, 1, 0, 0, 1, 0, 1}
    ,{0, 1, 0, 1, 1, 1, 1, 0}};

  cout << "Adjacency" << endl;
  println(a);
  newline();

  cout << "Laplacian" << endl;
  auto l = laplacian(a);
  println(l);
  newline();

  println(eigenvalues(l));
}

void problem2() {
  matrix<double> a =
    {{0, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 1}
    ,{1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 0, 1}
    ,{1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1}
    ,{0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1}
    ,{1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1}
    ,{1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1}
    ,{0, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0}
    ,{0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1}
    ,{1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0}
    ,{0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1}
    ,{1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0}
    ,{1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0}};

  cout << "Symmetric = ";
  println(isSymmetric(a) ? "true" : "false");

  newline();

  cout << "Degree" << endl;
  println(degree(a));

  newline();

  cout << "Laplacian" << endl;
  println(laplacian(a));

  newline();

  cout << "Euler Circuit Exists = ";
  println(hasEulerCircuit<double>(a) ? "true" : "false");
}

void problem3() {
  matrix<double> a =
    //A  B  C  D  E  F  G  H  I  J
    {{0, 1, 1, 0, 1, 0, 0, 0, 1, 1} // A
    ,{1, 0, 0, 0, 0, 0, 1, 0, 0, 0} // B
    ,{1, 0, 0, 0, 0, 0, 1, 1, 0, 1} // C
    ,{0, 0, 0, 0, 0, 1, 0, 0, 0, 0} // D
    ,{1, 0, 0, 0, 0, 0, 0, 0, 1, 1} // E
    ,{0, 0, 0, 1, 0, 0, 0, 0, 0, 1} // F
    ,{0, 1, 1, 0, 0, 0, 0, 1, 0, 0} // G
    ,{0, 0, 1, 0, 0, 0, 1, 0, 0, 1} // H
    ,{1, 0, 0, 0, 1, 0, 0, 0, 0, 0} // I
    ,{1, 0, 1, 0, 1, 1, 0, 1, 0, 0} // J
    };

  auto l = laplacian(a);
  cout << "Laplacian" << endl;
  println(l);

  newline();

  println(eigenvalues(l));

  cout << "Algebraic Connectivity = ";
  println(algebraicConnectivity(l, false));
}

void problem4() {
  matrix<double> l =
    {{ 5,  0, 0, -1, -1, -1,  0,  0, -1, -1}
    ,{ 0,  3, 0,  0,  0,  0, -1, -1,  0, -1}
    ,{ 0,  0, 0,  0,  0,  0,  0,  0,  0,  0}
    ,{-1,  0, 0,  2,  0,  0,  0, -1,  0,  0}
    ,{-1,  0, 0,  0,  3,  0, -1,  0, -1,  0}
    ,{-1,  0, 0,  0,  0,  2, -1,  0,  0,  0}
    ,{0,  -1, 0,  0, -1, -1,  5,  0, -1, -1}
    ,{0,  -1, 0, -1,  0,  0,  0,  3, -1,  0}
    ,{-1,  0, 0,  0, -1,  0, -1, -1,  4,  0}
    ,{-1, -1, 0,  0,  0,  0, -1,  0,  0,  3}};

  auto a = adjacency(l);
  cout << "Adjacency" << endl;
  println(a);

  newline();

  auto c = complement(a);
  cout << "Complement" << endl;
  println(c);

  newline();

  cout << "Algebraic Connectivity = ";
  println(algebraicConnectivity(c));
}

void problem5() {
  matrix<double> l =
    {{ 4, -1, -1, -1,  0,  0, -1,  0,  0,  0}
    ,{-1,  2,  0,  0, -1,  0,  0,  0,  0,  0}
    ,{-1,  0,  1,  0, -1,  0,  0,  0,  0,  0}
    ,{-1,  0,  0,  2, -1,  0,  0,  0,  0,  0}
    ,{ 0, -1,  0, -1,  5,  0, -1,  0, -1, -1}
    ,{ 0,  0,  0,  0,  0,  0,  0,  0,  0,  0}
    ,{-1,  0,  0,  0, -1,  0,  2,  0,  0,  0}
    ,{ 0,  0,  0,  0,  0,  0,  0,  0,  0,  0}
    ,{ 0,  0,  0,  0, -1,  0,  0,  0,  1,  0}
    ,{ 0,  0,  0,  0, -1,  0,  0,  0,  0,  1}};


  auto a = adjacency(l);
  cout << "Adjacency" << endl;
  println(a);

  newline();

  auto c = complement(a);
  cout << "Complement" << endl;
  println(c);

  newline();

  cout << "Algebraic Connectivity = ";
  println(algebraicConnectivity(c));

  newline();

  cout << "Euler Circuit Exists = ";
  println(hasEulerCircuit(c) ? "true" : "false");

  newline();

  cout << "Degree" << endl;
  println(degree(c));
}

void problem6() {
  matrix<double> a =
    {{0,1,0,1,1,0,1,0,0,0,0}
    ,{1,0,1,0,0,0,0,1,0,1,0}
    ,{0,1,0,1,0,1,0,0,0,0,0}
    ,{1,0,1,0,0,0,0,0,1,0,1}
    ,{1,0,0,0,0,1,0,0,0,1,0}
    ,{0,0,1,0,1,0,1,1,1,0,0}
    ,{1,0,0,0,0,1,0,0,0,0,1}
    ,{0,1,0,0,0,1,0,0,0,0,1}
    ,{0,0,0,1,0,1,0,0,0,1,0}
    ,{0,1,0,0,1,0,0,0,1,0,1}
    ,{0,0,0,1,0,0,1,1,0,1,0}};

  auto c = complement(a);
  cout << "Complement" << endl;
  println(c);

  newline();

  cout << "Algebraic Connectivity = ";
  println(algebraicConnectivity(c));
}


void problem8() {
  matrix<double> a =
    {{0, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 1}
    ,{1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 0, 1}
    ,{1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1}
    ,{0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1}
    ,{1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1}
    ,{1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1}
    ,{0, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0}
    ,{0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1}
    ,{1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0}
    ,{0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1}
    ,{1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0}
    ,{1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0}};

  auto d = degree(a);

  unsigned long size = a.size();

  matrix<double> m(size, vector<double>(size, 0));

  for (unsigned long r = 0; r < size; r++) {
    for (unsigned long c = 0; c < size; c++) {
      if(a[r][c] == 1) {
        m[r][c] = d[r][r] + d[c][c];
      }
    }
  }

  cout << "weighted adjacency matrix" << endl;
  println(m);

  newline();

  auto msp = minimalSpanningTree(m);
  auto cost = costOfRoute(m, msp);
  auto amsp = adjacency(m, msp);

  cout << "adjacency matrix of minimal spanning tree" << endl;
  println(amsp);

  newline();

  cout << "cost of route = " << cost;
}

void problem9() {
  matrix<double> a =
    {{0,1,0,1,1,0,1,0,0,0,0}
    ,{1,0,1,0,0,0,0,1,0,1,0}
    ,{0,1,0,1,0,1,0,0,0,0,0}
    ,{1,0,1,0,0,0,0,0,1,0,1}
    ,{1,0,0,0,0,1,0,0,0,1,0}
    ,{0,0,1,0,1,0,1,1,1,0,0}
    ,{1,0,0,0,0,1,0,0,0,0,1}
    ,{0,1,0,0,0,1,0,0,0,0,1}
    ,{0,0,0,1,0,1,0,0,0,1,0}
    ,{0,1,0,0,1,0,0,0,1,0,1}
    ,{0,0,0,1,0,0,1,1,0,1,0}};

  auto d = degree(a);

  unsigned long size = a.size();

  matrix<double> m(size, vector<double>(size, 0));

  for (unsigned long r = 0; r < size; r++) {
    for (unsigned long c = 0; c < size; c++) {
      if(a[r][c] == 1) {
        m[r][c] = d[r][r] + d[c][c];
      }
    }
  }

  cout << "weighted adjacency matrix" << endl;
  println(m);

  newline();

  auto msp = minimalSpanningTree(m);

  if (msp.size() == 0) {
    cout << "no minimal spanning tree exists";
    return;
  }

  auto cost = costOfRoute(m, msp);
  auto amsp = adjacency(m, msp);

  cout << "adjacency matrix of minimal spanning tree" << endl;
  println(amsp);

  newline();

  cout << "cost of route = " << cost;
}

void problem10() {
  /*
  matrix<double> a =
    {{0,1,0,1,1,0,1,0,0,0,0}
    ,{1,0,1,0,0,0,0,1,0,1,0}
    ,{0,1,0,1,0,1,0,0,0,0,0}
    ,{1,0,1,0,0,0,0,0,1,0,1}
    ,{1,0,0,0,0,1,0,0,0,1,0}
    ,{0,0,1,0,1,0,1,1,1,0,0}
    ,{1,0,0,0,0,1,0,0,0,0,1}
    ,{0,1,0,0,0,1,0,0,0,0,1}
    ,{0,0,0,1,0,1,0,0,0,1,0}
    ,{0,1,0,0,1,0,0,0,1,0,1}
    ,{0,0,0,1,0,0,1,1,0,1,0}};
  */

  matrix<double> a;

  auto i = incidence(a);

  vector<unsigned long> path;
  println(i);
}
