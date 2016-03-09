#pragma once

#include <vector>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_permutation.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_eigen.h>
#include <gsl/gsl_vector.h>
#include <utility>

template <class M>
using matrix = std::vector< std::vector< M > >;

template <class V>
V sum(const std::vector<V> &vec);

template <class M>
matrix<M> subtract(const matrix<M> &a, const matrix<M> &b);

template <class M>
matrix<M> transpose(const matrix<M> &mat);

template <class M>
matrix<M> adjacency(const matrix<M> &laplacian);

template <class M>
matrix<M> adjacency(const std::vector<char> &nodes,
                    const std::vector<std::vector<char>> &edges);

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
std::vector<gsl_complex> eigenvalues(const matrix<M> &mat);

std::vector<gsl_complex> eigenvalues(gsl_matrix * m);

template <class M>
bool connected(const matrix<M> &mat, bool adjacency = true);

template <class M>
bool hasEulerCircuit(const matrix<M> &mat);

template <class M>
std::vector<int> eulerCircuit(const matrix<M> &adjacency);

template <class M>
bool isSymmetric(const matrix<M> &mat);

template <class V>
V sum(const std::vector<V> &vec) {
  V ret = 0;
  for (unsigned long i = 0; i < vec.size(); i++)
    ret += vec[i];

  return ret;
}

template <class M>
matrix<M> subtract(const matrix<M> &a, const matrix<M> &b) {
  unsigned long size = a.size();
  matrix<M> ret(size, std::vector<M>(size));

  for (unsigned long r = 0; r < size; r++)
    for (unsigned long c = 0; c < size; c++)
      ret[r][c] = b[r][c] - a[r][c];

  return ret;
}

template <class M>
matrix<M> transpose(const matrix<M> &mat) {
  unsigned long
    rows = mat.size(),
    columns = mat[0].size();

  matrix<M> ret(columns, std::vector<M>(rows));

  for (unsigned long r = 0; r < rows; r++)
    for (unsigned long c = 0; c < columns; c++)
      ret[c][r] = mat[r][c];

  return ret;
}

template <class M>
matrix<M> adjacency(const matrix<M> &laplacian) {
  unsigned long size = laplacian.size();
  matrix<M> ret(size, std::vector<M>(size));

  for (unsigned long r = 0; r < size; r++)
    for (unsigned long c = 0; c < size; c++)
      ret[r][c] = r == c ? 0 : (laplacian[r][c] == 0 ? 0 : laplacian[r][c]* -1);

  return ret;
}

template <class M>
matrix<M> adjacency(const std::vector<char> &nodes,
                    const std::vector<std::vector<char>> &edges) {
  unsigned long size = nodes.size();
  matrix<M> ret(size, std::vector<M>(size, 0));

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
matrix<M> complement(const matrix<M> &mat) {
  unsigned long size = mat.size();

  matrix<M> ret(size, std::vector<M>(size));

  for (unsigned long r = 0; r < size; r++)
    for (unsigned long c = 0; c < size; c++)
      ret[r][c] = r == c ? (M)0 : !mat[r][c];

  return ret;
}

template <class M>
matrix<M> degree(const matrix<M> &adjacency) {
  unsigned long size = adjacency.size();
  matrix<M> ret(size, std::vector<M>(size, 0));

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
  return subtract(adjacency, degree);
}

template <class M>
matrix<M> laplacian(const matrix<M> &adjacency) {
  return laplacian(adjacency, degree(adjacency));
}

template <class M>
matrix<M> incidence(const matrix<M> &adjacency) {
  unsigned long
    rows = adjacency.size(), r = 0,
    columns = 0, c = 0;

  for (; r < rows; r++)
    for (c = r; c < rows; c++)
      columns += (adjacency[r][c] != 0 ? 1 : 0);

  matrix<M> ret(rows, std::vector<M>(columns, (M)0));

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
  return GSL_REAL(eigenvalues(adjacency ? laplacian(mat) : mat)[1]);
}

template <class M>
gsl_matrix * toGslMatrix(const matrix<M> &mat) {
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

  matrix<M> ret(rows, std::vector<M>(columns));

  for (auto r = 0; r < rows; r++)
    for (auto c = 0; c < columns; c++)
      ret[r][c] = gsl_matrix_get(mat, r, c);

  return ret;
}

template <class M>
std::vector<gsl_complex> eigenvalues(const matrix<M> &mat) {
  auto m = toGslMatrix(mat);

  auto ev = eigenvalues(m);
  gsl_matrix_free(m);

  return ev;
}

std::vector<gsl_complex> eigenvalues(gsl_matrix * m) {
  auto size = m->size1;
  std::vector<gsl_complex> ret;

  auto eval = gsl_vector_complex_alloc(size);
  auto evec = gsl_matrix_complex_alloc(size, size);
  auto w = gsl_eigen_nonsymmv_alloc(size);

  gsl_eigen_nonsymmv(m, eval, evec, w);
  gsl_eigen_nonsymmv_free(w);

  for (auto i = 0; i < size; i++)
    ret.push_back(gsl_vector_complex_get(eval, i));

  gsl_vector_complex_free (eval);
  gsl_matrix_complex_free (evec);

  std::sort(ret.begin(), ret.end(), [](auto l, auto r){
    return GSL_REAL(l) < GSL_REAL(r);
  });

  return ret;
}

template <class M>
bool connected(const matrix<M> &mat, bool adjacency) {
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
std::vector<int> eulerCircuit(const matrix<M> &adjacency) {
  if (!hasEulerCircuit(adjacency)) { return {}; }

  matrix<M> i = incidence(adjacency);

  std::vector<int> ret;

  unsigned long
    rows = i.size(),
    columns = i[1].size();

  matrix<M> zero(rows, std::vector<M>(columns, (M)0));

  for (unsigned long r = 0; r < rows; r++) {
    for (unsigned long c = 0; c < columns; c++) {
      if (i[r][c] == 1) {
        if (ret.size() == 0) { ret.push_back(r); }

        for (unsigned long j = 0; j < rows; j++) {
          if (r == j || i[j][c] != 1) { continue; }

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
bool isSymmetric(const matrix<M> &mat) {
  for (unsigned long r = 0; r < mat.size(); r++)
    for (unsigned long c = 0; c < mat[0].size(); c++)
      if (mat[r][c] != mat[c][r])
        return false;

  return true;
}
