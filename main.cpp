#include "problems.h"
#include "tests.h"

int main() {
  std::vector<char> nodes = {'A', 'B', 'C', 'D', 'E'};
  std::vector<std::vector<char>> edges =
    {{'A', 'B'}
    ,{'B', 'C'}
    ,{'C', 'D'}
    ,{'D', 'E'}
    ,{'E', 'A'}
    ,{'B', 'D'}};

  matrix<double> a = adjacency<double>(nodes, edges);

  println(a);

  return 0;
}
