/* file: tests.h
 * description: contains the tests for the program to make sure it works as
 *              expected
 */

#pragma once

#include "testing.h"

void runTests();
void testDegreeMatrix();
void testLaplacianMatrix();
void testAlgebraicConnectivity();
void testIncidenceMatrix();
void testEulerCircuit();

void runTests() {
  testDegreeMatrix();
  testLaplacianMatrix();
  testAlgebraicConnectivity();
  testIncidenceMatrix();
  testEulerCircuit();
}

void testDegreeMatrix() {
  testing::expect(
    "degree matrix 1",
    (matrix<int>)
    {{2, 0, 0, 0}
    ,{0, 3, 0, 0}
    ,{0, 0, 3, 0}
    ,{0, 0, 0, 2}},
    [](){ return degree<int>(
    {{0, 1, 1, 0}
    ,{1, 0, 1, 1}
    ,{1, 1, 0, 1}
    ,{0, 1, 1, 0}});}
  );

  testing::expect(
    "degree matrix 2",
    (matrix<int>)
    {{1, 0, 0, 0}
    ,{0, 2, 0, 0}
    ,{0, 0, 2, 0}
    ,{0, 0, 0, 0}},
    [](){ return degree<int>(
    {{0, 1, 0, 0}
    ,{0, 0, 1, 1}
    ,{1, 0, 0, 1}
    ,{0, 0, 0, 0}});}
  );
}

void testLaplacianMatrix() {
  testing::expect(
    "laplacian matrix",
    (matrix<int>)
    {{2, -1, -1, 0}
    ,{-1, 2, 0, -1}
    ,{-1, 0, 2, -1}
    ,{0, -1, -1, 2}},
    [](){ return laplacian<int>(
    {{0, 1, 1, 0}
    ,{1, 0, 0, 1}
    ,{1, 0, 0, 1}
    ,{0, 1, 1, 0}});}
  );
}

void testAlgebraicConnectivity() {
  testing::expect(
    "algebraic connectivity",
    0.722,
    [](){ return algebraicConnectivity<double>(
    {{0, 1, 0, 0, 1, 0}
    ,{1, 0, 1, 0, 1, 0}
    ,{0, 1, 0, 1, 0, 0}
    ,{0, 0, 1, 0, 1, 1}
    ,{1, 1, 0, 1, 0, 0}
    ,{0, 0, 0, 1, 0, 0}});},
    0.001
  );
}

void testIncidenceMatrix() {
  testing::expect(
    "incidence matrix",
    (matrix<int>)
    {{1, 1, 1, 0}
    ,{1, 0, 0, 0}
    ,{0, 1, 0, 1}
    ,{0, 0, 1, 1}},
    [](){ return incidence<int>(
    {{0, 1, 1, 1}
    ,{1, 0, 0, 0}
    ,{1, 0, 0, 1}
    ,{1, 0, 1, 0}}
    );}
  );
}

void testEulerCircuit() {
  matrix<double> a =
    {{0, 1, 1, 0, 0}
    ,{1, 0, 1, 0, 0}
    ,{1, 1, 0, 1, 1}
    ,{0, 0, 1, 0, 1}
    ,{0, 0, 1, 1, 0}};

  testing::expect(
    "euler circuit",
    (vector<int>){0, 1, 2, 3, 4, 2, 0},
    [=](){ return eulerCircuit(a); }
  );
}
