/* file: linear.h
 * description: provides functions for doing linear algebra operations
 */

#pragma once

#include <vector>
#include <map>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_permutation.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_eigen.h>
#include <gsl/gsl_vector.h>
#include <utility>
#include <iostream>
#include <math.h>

using namespace std;

template <class M>
using matrix = vector<vector<M>>;

template <class V>
double magnitude(const vector<V> &v);

template <class V>
V dot(const vector<V> &as, const vector<V> &bs);

template <class V>
vector<V> scale(const V s, const vector<V> &vec);

template <class M>
matrix<M> lower(const matrix<M> &mat);

template <class M>
matrix<M> upper(const matrix<M> &mat);

template <class M>
vector<M> column(const unsigned long &c, const matrix<M> &mat);

template <class M>
matrix<M> innerProduct(const vector<M> &a, const matrix<M> &b);

template <class M>
matrix<M> innerProduct(const matrix<M> &a, const vector<M> &b);

template <class M>
matrix<M> innerProduct(const matrix<M> &a, const matrix<M> &b);

template <class M>
matrix<M> outerProduct(const matrix<M> &a, const matrix<M> &b);

template <class M>
matrix<M> diagonal(const matrix<M> &mat);

template <class M>
matrix<M> minorDiagonal(const matrix<M> &mat);

template <class M>
M trace(const matrix<M> &mat);

template <class M>
matrix<M> scale(const M &s, const matrix<M> &mat);

template <class M>
matrix<M> subtract(const matrix<M> &a, const matrix<M> &b);

template <class M>
matrix<M> transpose(const matrix<M> &mat);

template <class M>
matrix<M> adjacency(const matrix<M> &laplacian);

template <class M>
matrix<M> adjacency(const vector<char> &nodes,
                    const vector<vector<char>> &edges);

template <class M>
matrix<M> adjacency(const matrix<M> &mat,
                    const vector<pair<int,int>> &edges);

template <class M>
matrix<M> complement(const matrix<M> &mat);

template <class M>
matrix<M> degree(const matrix<M> &adjacency);

template <class M>
matrix<M> laplacian(const matrix<M> &adjacency, const matrix<M> &degree);

template <class M>
matrix<M> laplacian(const matrix<M> &adjacency);

template <class M>
matrix<M> incidence(const matrix<M> &adjacency);

template <class M>
M algebraicConnectivity(const matrix<M> &mat, bool adjacency = true);

template <class M>
gsl_matrix * toGslMatrix(const matrix<M> &mat);

template <class M>
matrix<M> fromGslMatrix(gsl_matrix * mat);

template <class M>
vector<gsl_complex> eigenvalues(const matrix<M> &mat);
vector<gsl_complex> eigenvalues(gsl_matrix * m);

template <class M>
double determinant(const matrix<M> &mat);
double determinant(gsl_matrix * m);

template <class M>
bool connected(const matrix<M> &mat, bool adjacency = true);

template <class M>
bool hasEulerCircuit(const matrix<M> &mat);

template <class M>
vector<int> eulerCircuit(const matrix<M> &adjacency);

template <class M>
vector<pair<int,int>> minimalSpanningTree(const matrix<M> &adjacency);

template <class M>
M costOfRoute(const matrix<M> &adjacency, const vector<pair<int,int>> &path);

template <class M>
gsl_complex spectralGap(const matrix<M> &mat, bool adjacency = true);

template <class M>
gsl_complex spectralRadius(const matrix<M> &adjacency);

template <class M>
unsigned long connectedComponents(const matrix<M> &mat, bool adjacency = true);

template <class M>
unsigned long numSpanningTrees(const matrix<M> &mat, bool adjacency = true);

template <class M>
bool isSymmetric(const matrix<M> &mat);

template <class M>
bool isSquare(const matrix<M> &mat);

template <class M>
bool isJagged(const matrix<M> &mat);

template <class V>
double magnitude(const vector<V> &v) {
  double sum = 0;

  for (unsigned long i = 0; i < v.size(); i++)
    sum += pow((double)v[i], 2);

  return sqrt(sum);
}

template <class V>
V dot(const vector<V> &as, const vector<V> &bs) {
  if (as.size() != bs.size())
    throw invalid_argument("Vectors must have the same dimensions");

  V ret = 0;
  for (unsigned long i = 0; i < as.size(); i++)
    ret += (as[i] * bs[i]);

  return ret;
}

template <class V>
vector<V> scale(const V s, const vector<V> &vec) {
  vector<V> ret;

  for (unsigned long i = 0; i < vec.size(); i++)
    ret.push_back(vec[i] * s);

  return ret;
}

template <class M>
matrix<M> lower(const matrix<M> &mat) {
  if (isJagged(mat))
    throw invalid_argument("Matrix cannot be jagged");

  if (!isSquare(mat))
    throw invalid_argument("Matrix must be square");

  const unsigned long size = mat.size();

  matrix<M> ret(size, vector<M>(size));

  for (unsigned long r = 0; r < size; r++)
    for (unsigned long c = 0; c < size; c++)
      ret[r][c] = c <= r ? mat[r][c] : (M)0;

  return ret;
}

template <class M>
matrix<M> upper(const matrix<M> &mat) {
  if (isJagged(mat))
    throw invalid_argument("Matrix cannot be jagged");

  if (!isSquare(mat))
    throw invalid_argument("Matrix must be square");

  const unsigned long size = mat.size();

  matrix<M> ret(size, vector<M>(size));

  for (unsigned long r = 0; r < size; r++)
    for (unsigned long c = 0; c < size; c++)
      ret[r][c] = c >= r ? mat[r][c] : (M)0;

  return ret;
}

template <class M>
vector<M> column(const unsigned long &c, const matrix<M> &mat) {
  if (isJagged(mat))
    throw invalid_argument("Matrix cannot be jagged");

  unsigned long rows = mat.size();

  vector<M> ret;

  for (unsigned long r = 0; r < rows; r++)
    ret.push_back(mat[r][c]);

  return ret;
}

template <class M>
matrix<M> innerProduct(const vector<M> &a, const matrix<M> &b) {
  return innerProduct({a}, b);
}

template <class M>
matrix<M> innerProduct(const matrix<M> &a, const vector<M> &b) {
  return innerProduct(a, transpose({b}));
}

template <class M>
matrix<M> innerProduct(const matrix<M> &a, const matrix<M> &b) {
  if (isJagged(a) || isJagged(b))
    throw invalid_argument("Matrix cannot be jagged");

  if (a[0].size() != b.size())
    throw invalid_argument("Invalid matrix dimensions");

  const unsigned long
    rows = a.size(),
    columns = b[0].size();

  matrix<M> ret(rows, vector<M>(columns));

  for (unsigned long r = 0; r < rows; r++)
    for (unsigned long c = 0; c < columns; c++)
      ret[r][c] = dot(a[r], column(c, b));

  return ret;
}

template <class M>
matrix<M> outerProduct(const matrix<M> &a, const matrix<M> &b) {
  if (isJagged(a) || isJagged(b))
    throw invalid_argument("Matrix cannot be jagged");

  const unsigned long
    aRows = a.size(),
    aColumns = a[0].size(),
    bRows = b.size(),
    bColumns = b[0].size(),
    rows = aRows * bRows,
    columns = aColumns * bColumns;

  unsigned long
    sRows = 0,
    sColumns = 0;

  matrix<M>
    ret(rows, vector<M>(columns)),
    s;

  for (unsigned long r = 0; r < aRows; r++) {
    for (unsigned long c = 0; c < aColumns; c++) {
      s = scale(a[r][c], b);
      sRows = s.size();
      sColumns = s[0].size();

      for (unsigned long sr = 0; sr < sRows; sr++) {
        for (unsigned long sc = 0; sc < sColumns; sc++) {
          ret[(r * sRows) + sr][(c * sColumns) + sc] = s[sr][sc];
        }
      }
    }
  }

  return ret;
}

template <class M>
matrix<M> diagonal(const matrix<M> &mat) {
  if (isJagged(mat))
    throw invalid_argument("Matrix cannot be jagged");

  if (!isSquare(mat))
    throw invalid_argument("Matrix must be square");

  const unsigned long size = mat.size();

  matrix<M> ret(size, vector<M>(size, (M)0));

  for (unsigned long i = 0; i < size; i++)
    ret[i][i] = mat[i][i];

  return ret;
}

template <class M>
matrix<M> minorDiagonal(const matrix<M> &mat) {
  if (isJagged(mat))
    throw invalid_argument("Matrix cannot be jagged");

  if (!isSquare(mat))
    throw invalid_argument("Matrix must be square");

  const unsigned long size = mat.size();

  matrix<M> ret(size, vector<M>(size, 0));

  for (unsigned long r = 0; r < size; r++)
    for (unsigned long c = 0; c < size; c++)
      if (c + r + 1 == size)
        ret[r][c] = mat[r][c];

  return ret;
}

template <class M>
M trace(const matrix<M> &mat) {
  if (isJagged(mat))
    throw invalid_argument("Matrix cannot be jagged");

  if (!isSquare(mat))
    throw invalid_argument("Matrix must be square");

  M sum = 0;

  const unsigned long size = mat.size();

  for (unsigned long r = 0; r < size; r++)
    for (unsigned long c = 0; c < size; c++)
      if (r == c)
        sum += mat[r][c];

  return sum;
}

template <class M>
matrix<M> scale(const M &s, const matrix<M> &mat) {
  if (isJagged(mat))
    throw invalid_argument("Matrix cannot be jagged");

  unsigned long
    rows = mat.size(),
    columns = mat[0].size();

  matrix<M> ret(rows, vector<M>(columns));

  for (unsigned long r = 0; r < rows; r++)
    for (unsigned long c = 0; c < columns; c++)
      ret[r][c] = mat[r][c] * s;

  return ret;
}

template <class M>
matrix<M> subtract(const matrix<M> &a, const matrix<M> &b) {
  if (isJagged(a) || isJagged(b))
    throw invalid_argument("Matrix cannot be jagged");

  if (a.size() != b.size() || a[0].size() != b[0].size())
    throw invalid_argument("Matrices are not the same size");

  unsigned long size = a.size();
  matrix<M> ret(size, vector<M>(size));

  for (unsigned long r = 0; r < size; r++)
    for (unsigned long c = 0; c < size; c++)
      ret[r][c] = b[r][c] - a[r][c];

  return ret;
}

template <class M>
matrix<M> transpose(const matrix<M> &mat) {
  if (isJagged(mat))
    throw invalid_argument("Matrix cannot be jagged");

  unsigned long
    rows = mat.size(),
    columns = mat[0].size();

  matrix<M> ret(columns, vector<M>(rows));

  for (unsigned long r = 0; r < rows; r++)
    for (unsigned long c = 0; c < columns; c++)
      ret[c][r] = mat[r][c];

  return ret;
}

template <class M>
matrix<M> adjacency(const matrix<M> &laplacian) {
  if (isJagged(laplacian))
    throw invalid_argument("Matrix cannot be jagged");

  unsigned long size = laplacian.size();
  matrix<M> ret(size, vector<M>(size));

  for (unsigned long r = 0; r < size; r++)
    for (unsigned long c = 0; c < size; c++)
      ret[r][c] = r == c ? 0 : (laplacian[r][c] == 0 ? 0 : laplacian[r][c]* -1);

  return ret;
}

template <class M>
matrix<M> adjacency(const vector<char> &nodes,
                    const vector<vector<char>> &edges) {
  unsigned long size = nodes.size();
  matrix<M> ret(size, vector<M>(size, 0));

  auto indexOf = [nodes](char e) {
    for (unsigned long i = 0; i < nodes.size(); i++) {
      if (e == nodes[i]) { return i; }
    }

    return (unsigned long)-1;
  };

  for (auto &p : edges) {
    unsigned long
      x = indexOf(p[0]),
      y = indexOf(p[1]);

    if (x == -1 || y == -1) { continue; }

    ret[x][y] = ret[y][x] = (M)1;
  }

  return ret;
}

template <class M>
matrix<M> adjacency(const matrix<M> &mat,
                    const vector<pair<int,int>> &path) {
  unsigned long size = mat.size();
  matrix<M> ret(size, vector<M>(size, (M)0));

  for (auto &p : path)
    ret[p.first][p.second] = ret[p.second][p.first] = mat[p.first][p.second];

  return ret;
}

template <class M>
matrix<M> complement(const matrix<M> &mat) {
  if (isJagged(mat))
    throw invalid_argument("Matrix cannot be jagged");

  unsigned long size = mat.size();

  matrix<M> ret(size, vector<M>(size));

  for (unsigned long r = 0; r < size; r++)
    for (unsigned long c = 0; c < size; c++)
      ret[r][c] = r == c ? (M)0 : !mat[r][c];

  return ret;
}

template <class M>
matrix<M> degree(const matrix<M> &adjacency) {
  if (isJagged(adjacency))
    throw invalid_argument("Matrix cannot be jagged");

  if (!isSquare(adjacency))
    throw invalid_argument("Matrix must be square");

  unsigned long size = adjacency.size();
  matrix<M> ret(size, vector<M>(size, 0));

  for (unsigned long r = 0; r < size; r++) {
    int sum = 0;
    for (unsigned long c = 0; c < size; c++)
      if (adjacency[r][c] != 0) { sum += 1; }

    ret[r][r] = sum;
  }

  return ret;
}

template <class M>
matrix<M> laplacian(const matrix<M> &adjacency, const matrix<M> &degree) {
  if (isJagged(adjacency) || isJagged(degree))
    throw invalid_argument("Matrix cannot be jagged");

  if (!isSquare(adjacency) || !isSquare(degree))
    throw invalid_argument("Matrix must be square");

  return subtract(adjacency, degree);
}

template <class M>
matrix<M> laplacian(const matrix<M> &adjacency) {
  return laplacian(adjacency, degree(adjacency));
}

template <class M>
matrix<M> incidence(const matrix<M> &adjacency) {
  if (isJagged(adjacency))
    throw invalid_argument("Matrix cannot be jagged");

  if (!isSquare(adjacency))
    throw invalid_argument("Matrix must be square");

  unsigned long
    rows = adjacency.size(), r = 0,
    columns = 0, c = 0;

  for (; r < rows; r++)
    for (c = r; c < rows; c++)
      columns += (adjacency[r][c] != 0 ? 1 : 0);

  matrix<M> ret(rows, vector<M>(columns, (M)0));

  unsigned long i = 0;

  for (r = 0; r < rows; r++) {
    for (c = r; c < rows; c++) {
      if (adjacency[r][c] != 0) {
        ret[r][i] = ret[c][i] = 1;
        i++;
      }
    }
  }

  return ret;
}

template <class M>
M algebraicConnectivity(const matrix<M> &mat, bool adjacency) {
  if (isJagged(mat))
    throw invalid_argument("Matrix cannot be jagged");

  if (adjacency && !isSquare(mat))
    throw invalid_argument("Matrix must be square");

  return GSL_REAL(eigenvalues(adjacency ? laplacian(mat) : mat)[1]);
}

template <class M>
gsl_matrix * toGslMatrix(const matrix<M> &mat) {
  if (isJagged(mat))
    throw invalid_argument("Matrix cannot be jagged");

  const unsigned long
    rows = mat.size(),
    columns = mat[0].size();

  gsl_matrix * ret = gsl_matrix_alloc(rows, columns);

  for (auto r = 0; r < rows; r++)
    for (auto c = 0; c < columns; c++)
      gsl_matrix_set(ret, r, c, mat[r][c]);

  return ret;
}

template <class M>
matrix<M> fromGslMatrix(gsl_matrix * mat) {
  const unsigned long
    rows = mat->size1,
    columns = mat->size2;

  matrix<M> ret(rows, vector<M>(columns));

  for (auto r = 0; r < rows; r++)
    for (auto c = 0; c < columns; c++)
      ret[r][c] = gsl_matrix_get(mat, r, c);

  return ret;
}

template <class M>
vector<gsl_complex> eigenvalues(const matrix<M> &mat) {
  if (isJagged(mat))
    throw invalid_argument("Matrix cannot be jagged");

  auto m = toGslMatrix(mat);

  auto ev = eigenvalues(m);
  gsl_matrix_free(m);

  return ev;
}

vector<gsl_complex> eigenvalues(gsl_matrix * m) {
  auto size = m->size1;
  vector<gsl_complex> ret;

  auto eval = gsl_vector_complex_alloc(size);
  auto evec = gsl_matrix_complex_alloc(size, size);
  auto w = gsl_eigen_nonsymmv_alloc(size);

  gsl_eigen_nonsymmv(m, eval, evec, w);
  gsl_eigen_nonsymmv_free(w);

  for (auto i = 0; i < size; i++)
    ret.push_back(gsl_vector_complex_get(eval, i));

  gsl_vector_complex_free (eval);
  gsl_matrix_complex_free (evec);

  sort(ret.begin(), ret.end(), [](auto l, auto r){
    return GSL_REAL(l) < GSL_REAL(r);
  });

  return ret;
}

template <class M>
double determinant(const matrix<M> &mat) {
  if (isJagged(mat))
    throw invalid_argument("Matrix cannot be jagged");

  auto m = toGslMatrix(mat);

  auto d = determinant(m);
  gsl_matrix_free(m);

  return d;
}

double determinant(gsl_matrix * m) {
  double d;
  int signum;

  gsl_permutation * p = gsl_permutation_alloc(m->size1);

  gsl_matrix * tmp = gsl_matrix_alloc(m->size1, m->size2);
  gsl_matrix_memcpy(tmp, m);

  gsl_linalg_LU_decomp(tmp, p, &signum);
  d = gsl_linalg_LU_det(tmp, signum);

  gsl_permutation_free(p);
  gsl_matrix_free(tmp);

  return d;
}

template <class M>
bool connected(const matrix<M> &mat, bool adjacency) {
  if (isJagged(mat))
    throw invalid_argument("Matrix cannot be jagged");

  if (adjacency && !isSquare(mat))
    throw invalid_argument("Matrix must be square");

  return algebraicConnectivity(mat, adjacency) > 0;
}

template <class M>
bool hasEulerCircuit(const matrix<M> &mat) {
  matrix<M> d = degree(mat);
  for (auto &v : d)
    for (auto &e : v)
      if ((int)e % 2 != 0)
        return false;

  return connected(mat);
}

template <class M>
vector<int> eulerCircuit(const matrix<M> &adjacency) {
  if (isJagged(adjacency))
    throw invalid_argument("Matrix cannot be jagged");

  if (!isSquare(adjacency))
    throw invalid_argument("Matrix must be square");

  unsigned long aSize = adjacency.size();
  matrix<M> a(aSize, vector<M>(aSize, (M)0));

  for (unsigned long r = 0; r < aSize; r++)
    for (unsigned long c = 0; c < aSize; c++)
      if (adjacency[r][c] != 0)
        a[r][c] = 1;

  if (!hasEulerCircuit(a)) { return {}; }

  matrix<M> i = incidence(a);

  vector<int> ret;

  unsigned long
    rows = i.size(),
    columns = i[1].size();

  matrix<M> zero(rows, vector<M>(columns, (M)0));

  for (unsigned long r = 0; r < rows; r++) {
    for (unsigned long c = 0; c < columns; c++) {
      if (i[r][c] != 0) {
        if (ret.size() == 0) { ret.push_back(r); }

        for (unsigned long j = 0; j < rows; j++) {
          if (r == j || i[j][c] == 0) { continue; }

          i[r][c] = i[j][c] = 0;
          ret.push_back(j);

          r = j;
          break;
        }
      }

      if (c == columns - 1 && i != zero) { c = 0; }
    }
  }

  return ret;
}

template <class M>
vector<pair<int,int>> minimalSpanningTree(const matrix<M> &adjacency) {
  if (isJagged(adjacency))
    throw invalid_argument("Matrix cannot be jagged");

  if (!isSquare(adjacency))
    throw invalid_argument("Matrix must be square");

  if (numSpanningTrees(adjacency) == 0)
    return {};

  unsigned long aSize = adjacency.size();
  vector<pair<int,int>> ret;

  matrix<M> zero(aSize, vector<M>(aSize, (M)0));

  matrix<M> a = adjacency;

  vector<unsigned long> available = {0};

  struct cell {
    unsigned long r, c;
    double v;

    cell(const unsigned long &r, const unsigned long &c, const double &v):
      r(r),
      c(c),
      v(v)
    {}
  };

  while (a != zero) {
    cell sc = cell(0, 0, 0);
    for (auto &r : available)
      for (unsigned long c = 0; c < aSize; c++)
        if (a[r][c] != 0 && (sc.v == 0 || a[r][c] < sc.v))
          sc = cell(r, c, a[r][c]);

    a[sc.r][sc.c] = a[sc.c][sc.r] = 0;

    bool cTaken = false, rTaken = false;
    for (auto &p : ret) {
      if (p.first == sc.c || p.second == sc.c)
        cTaken = true;
      if (p.first == sc.r || p.second == sc.r)
        rTaken = true;
    }

    if (!(cTaken && rTaken)) {
      ret.push_back(make_pair(sc.r, sc.c));

      cTaken = false;
      rTaken = false;

      for (auto &i : available) {
        if (i == sc.c)
          cTaken = true;
        if (i == sc.r)
          rTaken = true;
      }

      if (!cTaken)
        available.push_back(sc.c);
      if (!rTaken)
        available.push_back(sc.r);
    }
  }

  return ret;
};


template <class M>
vector<pair<int,int>> minimalSpanningTreeBackup(const matrix<M> &adjacency) {
  if (isJagged(adjacency))
    throw invalid_argument("Matrix cannot be jagged");

  if (!isSquare(adjacency))
    throw invalid_argument("Matrix must be square");

  if (numSpanningTrees(adjacency) == 0)
    return {};

  unsigned long aSize = adjacency.size();
  vector<pair<int,int>> ret;

  matrix<M> zero(aSize, vector<M>(aSize, (M)0));

  matrix<M> a(aSize, vector<M>(aSize, (M)0));
  for (unsigned long r = 0; r < aSize; r++)
    for (unsigned long c = r; c < aSize; c++)
      a[r][c] = adjacency[r][c];

  while (a != zero) {
    unsigned long sr = 0, sc = 0;
    M sw = 0;

    for (unsigned long r = 0; r < aSize; r++) {
      for (unsigned long c = r; c < aSize; c++) {
        if (sw == 0 || (a[r][c] != 0 && a[r][c] < sw)) {
          sw = a[r][c];
          sr = r;
          sc = c;
        }
      }
    }

    bool srIn = false;
    bool scIn = false;
    for (auto &p : ret) {
      if (p.first == sr || p.second == sr)
        srIn = true;

      if (p.first == sc || p.second == sc)
        scIn = true;
    }

    if (!srIn || !scIn)
      ret.push_back(make_pair(sr, sc));

    a[sr][sc] = 0;
  }

  return ret;
};

template <class M>
M costOfRoute(const matrix<M> &adjacency, const vector<pair<int,int>> &path) {
  if (isJagged(adjacency))
    throw invalid_argument("Matrix cannot be jagged");

  if (!isSquare(adjacency))
    throw invalid_argument("Matrix must be square");

  M cost = 0;

  for (auto &p : path)
    cost += adjacency[p.first][p.second];

  return cost;
}

template <class M>
gsl_complex spectralGap(const matrix<M> &mat, bool adjacency) {
  if (isJagged(mat))
    throw invalid_argument("Matrix cannot be jagged");

  if (adjacency && !isSquare(mat))
    throw invalid_argument("Matrix must be square");

  for (auto &ev : eigenvalues(adjacency ? laplacian(mat) : mat))
    if (GSL_REAL(ev) > 0)
      return ev;

  throw invalid_argument("No non zero eigenvalue");
}

template <class M>
gsl_complex spectralRadius(const matrix<M> &adjacency) {
  if (isJagged(adjacency))
    throw invalid_argument("Matrix cannot be jagged");

  if (!isSquare(adjacency))
    throw invalid_argument("Matrix must be square");

  auto ev = eigenvalues(adjacency);

  gsl_complex last = ev[ev.size() - 1];

  if (GSL_REAL(last) > 0)
    return last;

  throw invalid_argument("No non zero eigenvalue");
}

template <class M>
unsigned long connectedComponents(const matrix<M> &mat, bool adjacency) {
  if (isJagged(mat))
    throw invalid_argument("Matrix cannot be jagged");

  if (adjacency && !isSquare(mat))
    throw invalid_argument("Matrix must be square");

  unsigned long count = 0;

  for (auto &ev : eigenvalues(adjacency ? laplacian(mat) : mat))
    if (GSL_REAL(ev) == 0)
      count++;

  return count;
}

template <class M>
unsigned long numSpanningTrees(const matrix<M> &mat, bool adjacency) {
  if (isJagged(mat))
    throw invalid_argument("Matrix cannot be jagged");

  if (adjacency && !isSquare(mat))
    throw invalid_argument("Matrix must be square");

  unsigned long size = mat.size();
  matrix<M> a(size, vector<M>(size, (M)0));
  if (adjacency) {
    for (unsigned long r = 0; r < size; r++)
      for (unsigned long c = 0; c < size; c++)
        a[r][c] = mat[r][c] == 0 ? 0 : 1;
  }

  auto evs = eigenvalues(adjacency ? laplacian(a) : mat);

  if (GSL_REAL(evs[1]) < 0)
    return 0;

  double product = 1;
  for (unsigned long i = 1; i < evs.size(); i++) {
    product *= GSL_REAL(evs[i]);
  }

  double oneOverN =  ((double)1 / (double)evs.size());

  return oneOverN * product;
}

template <class M>
bool isSymmetric(const matrix<M> &mat) {
  for (unsigned long r = 0; r < mat.size(); r++)
    for (unsigned long c = 0; c < mat[0].size(); c++)
      if (mat[r][c] != mat[c][r])
        return false;

  return true;
}

template <class M>
bool isSquare(const matrix<M> &mat) {
  return mat.size() == mat[0].size();
}

template <class M>
bool isJagged(const matrix<M> &mat) {
  unsigned long size = mat[0].size();

  for (auto &v : mat)
    if (v.size() != size)
      return true;

  return false;
}
